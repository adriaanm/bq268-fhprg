/* sdcc_helpers.c — eMMC data transfer helpers.
 *
 * These sit between sdcc_send_cmd (in emmc.c) and the MMIO register
 * wrappers (in sdcc_regs.c). They handle data transfer setup, DMA
 * configuration, FIFO writes, busy-waits, and post-write cleanup.
 *
 * Source: src/fhprg/fhprg_80327f8.c, src/fhprg/fhprg_8007b18.c
 *
 * Register bases (per slot, initialized by sdcc_init_bases):
 *   sdcc_mci_base[slot] = MCI core base  (slot 0: 0x7824000, slot 1: 0x7864000)
 *   sdcc_dma_base[slot] = MCI core base  (duplicate, alias for DMA/FIFO use)
 *   sdcc_hc_base[slot] = SDHCI HC base  (slot 0: 0x7824900, slot 1: 0x7864900)
 *
 * Key MCI registers (offsets from sdcc_mci_base[slot]):
 *   +0x00  MCI_POWER       — power control
 *   +0x04  MCI_CLK         — clock control
 *   +0x08  MCI_ARGUMENT    — command argument
 *   +0x0C  MCI_CMD         — command register
 *   +0x24  MCI_DATA_TIMER  — data timeout counter
 *   +0x28  MCI_DATA_LENGTH — total data length in bytes
 *   +0x2C  MCI_DATA_CTL    — data control (dir, enable, block size)
 *   +0x34  MCI_STATUS      — controller status (read-only)
 *   +0x38  MCI_CLEAR       — status bit clear (write-1-to-clear)
 *   +0x3C  MCI_INT_MASK0   — interrupt mask 0
 *   +0x6C  MCI_TEST        — clock stall / test register (bit 0 = busy)
 *   +0x78  MCI_VERSION     — bus width control (bit 0)
 *   +0x80  MCI_FIFO        — FIFO data port (16 words deep, 64 bytes)
 *
 * MCI_STATUS bit definitions (+0x34):
 *   bit 0  (0x000001) = CMD_CRC_FAIL
 *   bit 1  (0x000002) = DATA_CRC_FAIL
 *   bit 2  (0x000004) = CMD_TIMEOUT
 *   bit 3  (0x000008) = DATA_TIMEOUT
 *   bit 4  (0x000010) = TX_UNDERRUN
 *   bit 5  (0x000020) = RX_OVERRUN
 *   bit 6  (0x000040) = CMD_RESPONSE_END
 *   bit 7  (0x000080) = CMD_SENT        (no-response commands)
 *   bit 8  (0x000100) = DATA_END        (all data transferred)
 *   bit 14 (0x004000) = TX_FIFO_HFULL  (FIFO half-full: room for 8+ words)
 *   bit 15 (0x008000) = RX_FIFO_HFULL  (FIFO has 8+ words ready to read)
 *   bit 16 (0x010000) = DATA_BLK_END   (one block boundary crossed)
 *   bit 21 (0x200000) = RX_DATA_AVAIL  (any data in receive FIFO)
 *   bit 23 (0x800000) = PROG_DONE      (card programming complete)
 *
 * Combined error masks used in this file:
 *   0x2a = DATA_CRC_FAIL | CMD_TIMEOUT | RX_OVERRUN   (read-path errors)
 *   0x1a = DATA_CRC_FAIL | DATA_TIMEOUT | TX_UNDERRUN (write-path errors)
 */
#include "globals.h"

/* Forward declarations for functions defined later in this file */
static uint sdcc_wait_card_ready(mmc_dev_t *dev);

/* ---- DMA bounce helpers (from fhprg_8007b18.c) ---- */

/* orig: 0x08006e1a — write uint32 as little-endian bytes.
 *
 * val  — 32-bit value to serialize
 * buf  — destination byte buffer (must have room for 4 bytes)
 *
 * Used by sdcc_dma_setup to fill ADMA2 descriptor address fields
 * byte-by-byte, as the descriptor table is a packed byte array.
 */
static void write_le32(uint val, uint8_t *buf)
{
  *buf = (char)val;
  buf[1] = (char)(val >> 8);
  buf[2] = (char)(val >> 0x10);
  buf[3] = (char)(val >> 0x18);
}

/* orig: 0x08008ba4 — dma_read_helper: burst-read 8 words (32 bytes) from
 * the MCI FIFO into RAM, repeating while the status bit stays set.
 *
 * dst        — destination RAM buffer (written in 8-word bursts)
 * fifo       — MCI_FIFO (+0x80): MMIO FIFO data port (reads auto-advance)
 * status_reg — MCI_STATUS (+0x34): volatile MMIO status register
 * mask       — status bit to check before each burst:
 *                0x8000 = RX_FIFO_HFULL (FIFO contains >= 8 words = 32 bytes)
 *
 * Returns: pointer to one-past-last byte written (= dst + bytes_read).
 *
 * The FIFO is 16 words (64 bytes) deep. When RX_FIFO_HFULL is set, at
 * least 8 words are available, so reading 8 words per burst is safe.
 */
static uint *dma_read_helper(uint *dst, volatile uint *fifo, volatile uint *status_reg, uint mask)
{
  while ((*status_reg & mask) != 0) {
    /* Read 8 words (32 bytes) from MCI_FIFO (+0x80) in one burst */
    dst[0] = fifo[0]; dst[1] = fifo[1]; dst[2] = fifo[2]; dst[3] = fifo[3];
    dst[4] = fifo[4]; dst[5] = fifo[5]; dst[6] = fifo[6]; dst[7] = fifo[7];
    dst += 8;
  }
  return dst;
}

/* DMA write descriptor passed to dma_write_helper.
 * The four fields must remain contiguous — dma_write_helper reads them
 * by struct member, and the layout is fixed by the original ABI. */
typedef struct {
  volatile uint *status_reg; /* MCI_STATUS (+0x34): MMIO status register */
  uint ready_mask;           /* 0x4000 = TX_FIFO_HFULL: FIFO has room for 8+ words */
  int  remaining;            /* byte count remaining (decremented by 32 per burst) */
  uint error_mask;           /* 0x1a = DATA_CRC_FAIL|DATA_TIMEOUT|TX_UNDERRUN: abort on any */
} dma_write_desc_t;

/* orig: 0x08008bc4 — dma_write_helper: burst-write 8 words (32 bytes) from
 * RAM into the MCI FIFO, polling between bursts for space and errors.
 *
 * fifo — MCI_FIFO (+0x80): MMIO FIFO data port (single address; the
 *         controller dequeues words sequentially from successive writes)
 * src  — source RAM buffer (read in 8-word bursts)
 * desc — write descriptor (see dma_write_desc_t above)
 *
 * Returns: pointer to one-past-last byte read from src.
 * Updates desc->remaining with bytes not yet written.
 *
 * The inner poll loop checks MCI_STATUS (+0x34):
 *   - if error_mask (0x1a) is set: abort early (goto done)
 *   - if ready_mask (0x4000 = TX_FIFO_HFULL) is clear: keep polling
 * TX_FIFO_HFULL means the FIFO is at least half empty (has space for 8
 * words); we wait for that before writing another 8-word burst.
 */
static uint *dma_write_helper(volatile uint *fifo, uint *src, dma_write_desc_t *desc)
{
  int rem = desc->remaining;
  volatile uint *status_reg = desc->status_reg; /* MCI_STATUS (+0x34) */
  uint ready_mask = desc->ready_mask;   /* TX_FIFO_HFULL = 0x4000 */
  uint error_mask = desc->error_mask;   /* write errors  = 0x1a   */

  while (1) {
    /* Burst-write 8 words (32 bytes) to MCI_FIFO (+0x80) */
    *fifo = src[0]; *fifo = src[1]; *fifo = src[2]; *fifo = src[3];
    *fifo = src[4]; *fifo = src[5]; *fifo = src[6]; *fifo = src[7];
    src += 8;
    rem -= 0x20;
    if (rem < 0x20) break;
    /* Poll MCI_STATUS (+0x34): wait for FIFO space, abort on error */
    do {
      if ((*status_reg & error_mask) != 0) goto done; /* DATA_CRC_FAIL|DATA_TIMEOUT|TX_UNDERRUN */
    } while ((*status_reg & ready_mask) == 0);         /* wait for TX_FIFO_HFULL (0x4000) */
  }
done:
  desc->remaining = rem;
  return src;
}

/* orig: 0x0800bbec — adma_bounce_read: read a burst of data from the MCI
 * FIFO into a RAM buffer.
 *
 * slot      — SDCC slot index (0 or 1)
 * buf       — destination RAM buffer address (must be 4-byte aligned)
 * remaining — in/out: byte count; decremented by the number of bytes read
 *
 * Uses sdcc_dma_base[slot] + 0x80 (MCI_FIFO) as the source FIFO address.
 * Polls sdcc_mci_base[slot] + 0x34 (MCI_STATUS) for RX_FIFO_HFULL (0x8000).
 *
 * Note: called only when buf is word-aligned AND RX_FIFO_HFULL (0x8000)
 * is set; the caller (sdcc_adma_transfer) checks both before dispatching here.
 */
void adma_bounce_read(int slot, uint *buf, int *remaining)
{
  /* MCI_FIFO    = sdcc_dma_base[slot] + 0x80
   * MCI_STATUS  = sdcc_mci_base[slot] + 0x34
   * poll mask   = 0x8000 (RX_FIFO_HFULL: >= 8 words available) */
  uint *end = dma_read_helper(buf, &DMA_REG(slot, MCI_FIFO),
                              &MCI_REG(slot, MCI_STATUS), 0x8000);
  *remaining = *remaining - (int)((char *)end - (char *)buf);
}

/* orig: 0x0800bc20 — adma_bounce_write: write a burst of data from a RAM
 * buffer to the MCI FIFO.
 *
 * slot      — SDCC slot index (0 or 1)
 * buf       — source RAM buffer address (must be 4-byte aligned)
 * remaining — in/out: byte count; decremented by the number of bytes written
 *
 * Builds a dma_write_desc_t on the stack:
 *   status_reg_addr = sdcc_mci_base[slot] + 0x34 (MCI_STATUS)
 *   ready_mask      = 0x4000 (TX_FIFO_HFULL: FIFO has room for 8+ words)
 *   remaining       = *remaining
 *   error_mask      = 0x1a (DATA_CRC_FAIL | DATA_TIMEOUT | TX_UNDERRUN)
 */
void adma_bounce_write(int slot, uint *buf, int *remaining)
{
  dma_write_desc_t desc;
  desc.status_reg = &MCI_REG(slot, MCI_STATUS);
  desc.ready_mask = 0x4000;                     /* TX_FIFO_HFULL */
  desc.remaining  = *remaining;
  desc.error_mask = 0x1a;                       /* DATA_CRC_FAIL | DATA_TIMEOUT | TX_UNDERRUN */
  uint *end = dma_write_helper(&DMA_REG(slot, MCI_FIFO), buf, &desc); /* MCI_FIFO (+0x80) */
  *remaining = *remaining - (int)((char *)end - (char *)buf);
}

/* ---- eMMC higher-level helpers (from fhprg_80327f8.c) ---- */

/* orig: 0x080329f8 sdcc_event_notify — issue a data memory barrier if the
 * barrier bit is set in flags.
 *
 * flags — bitmask; bit 2 (0x4): issue full DMB (inner-shareable).
 *         Other bits are reserved for cache maintenance; addr/size are
 *         provided for that purpose but are unused in this simplified version.
 * addr  — (unused) cache region start address
 * size  — (unused) cache region byte count
 *
 * The test `flags << 0x1d < 0` shifts bit 2 into the sign position to test
 * it with a single signed comparison. When set, DataMemoryBarrier(0x1f) is
 * issued to ensure all preceding MMIO writes are visible before any DMA
 * descriptor programming that follows.
 */
void sdcc_event_notify(int flags, uint addr, uint size)
{
  (void)addr; (void)size;
  if (flags << 0x1d < 0)   /* bit 2 set = barrier required */
    DataMemoryBarrier(0x1f);
}

/* orig: 0x08032d8c sdcc_post_write_cleanup — send CMD12 (STOP_TRANSMISSION)
 * if needed, then optionally poll until the card returns to transfer state.
 *
 * dev        — pointer to mmc_dev_t device struct
 * need_busy  — 1 = poll card ready (via sdcc_wait_card_ready) after stop or
 *                  after data end (for single-block writes with busy signalling)
 * need_stop  — 1 = send CMD12 (STOP_TRANSMISSION) first
 *
 * Returns: 0 on success, non-zero error code on failure.
 *
 * After a multi-block write (CMD25), CMD12 terminates the transfer.
 * If need_stop is 0 but need_busy is 1, only polls for card ready
 * (used for single-block writes with R1b busy signalling on DAT0).
 */
uint sdcc_post_write_cleanup(mmc_dev_t *dev, int need_busy, int need_stop)
{
  uint ret = 0;
  mmc_cmd_t cmd;

  if (need_stop == 0) {
    if (need_busy == 1)
      ret = sdcc_wait_card_ready(dev);
  }
  else {
    memset_zero(&cmd, sizeof(cmd));
    cmd.cmd_num = 0xc;                             /* CMD12: STOP_TRANSMISSION */
    *(uint8_t *)&cmd.resp_type = 1;                /* resp_type: R1 */
    cmd.busy_wait = (need_busy == 1) ? 1 : 0;     /* busy_wait: 1 = wait for DAT0 deassert */
    ret = sdcc_send_cmd(dev, &cmd);
  }
  return ret;
}

/* orig: 0x08034314 sdcc_fifo_write — transfer one or more blocks through
 * the SDHCI data buffer port (PIO via SDHCI, not via MCI FIFO).
 *
 * dev        — pointer to mmc_dev_t device struct; dev[0] = slot index
 * cmd        — pointer to mmc_cmd_t; uses flags (direction) and status (error out)
 * buf        — data buffer (source for write, destination for read)
 * byte_count — total bytes to transfer
 *
 * Returns: 0 on success, non-zero error code on failure.
 *
 * For multi-block transfers (dev[DEV_CUSTOM_SECTOR] == 1), the loop
 * iterates (byte_count / sector_size) times, transferring one sector
 * per iteration. Each iteration waits for SDHCI buffer-ready via
 * sdcc_wait_complete, then clears the status, then transfers uVar6 words.
 *
 * SDHCI data buffer port: sdcc_hc_base[slot] + 0x20 (SDHCI_BUF_DATA).
 * sdcc_wait_complete wait masks:
 *   0x20 = SDHCI BUFF_READ_READY  (read direction)
 *   0x10 = SDHCI BUFF_WRITE_READY (write direction)
 *
 * Returns 1 immediately if neither read nor write bit is set in flags.
 */
int sdcc_fifo_write(mmc_dev_t *dev, mmc_cmd_t *cmd, uint *buf, uint byte_count)
{
  uint out_status = 0;
  int slot = dev->slot;
  uint words_per_block;
  uint num_blocks;

  if (dev->custom_sector == 1) {                  /* custom_sector: multi-block mode */
    uint sector_sz = dev->sector_size;
    num_blocks = byte_count / sector_sz;
    words_per_block = (sector_sz + 3) >> 2;       /* round up to word count */
  }
  else {
    num_blocks = 1;
    words_per_block = (byte_count + 3) >> 2;      /* round up to word count */
  }

  /* Decode transfer direction from cmd flags */
  uint wait_mask;
  if ((int)(cmd->flags << 0x1e) < 0)
    wait_mask = 0x20;                    /* READ: wait for SDHCI BUFF_READ_READY */
  else if ((cmd->flags & 1) != 0)
    wait_mask = 0x10;                    /* WRITE: wait for SDHCI BUFF_WRITE_READY */
  else
    return 1;                            /* neither read nor write: invalid config */

  do {
    int ret = sdcc_wait_complete(slot, wait_mask, &out_status);
    if (ret != 0) {
      cmd->status = out_status;          /* save error status for caller */
      return ret;
    }
    sdcc_clear_status(slot, wait_mask);
    uint i = 0;
    if ((int)(cmd->flags << 0x1e) < 0) {
      /* READ: pull words from SDHCI_BUF_DATA (sdcc_hc_base[slot] + 0x20) */
      for (; i < words_per_block; i++) {
        *buf = HC_REG32(slot, HC_BUF_DATA); /* SDHCI_BUF_DATA (+0x20) */
        buf = buf + 1;
      }
    }
    else if ((cmd->flags & 1) != 0) {
      /* WRITE: push words to SDHCI_BUF_DATA (sdcc_hc_base[slot] + 0x20) */
      for (; i < words_per_block; i++) {
        uint word = *buf;
        buf = buf + 1;
        HC_REG32(slot, HC_BUF_DATA) = word; /* SDHCI_BUF_DATA (+0x20) */
      }
    }
    num_blocks = num_blocks - 1;
  } while (num_blocks != 0);
  return 0;
}

/* ADMA2 descriptor table — must be in DDR for DMA access (USB DMA and
 * SDCC DMA both cannot access OCIMEM at 0x0804xxxx).
 * Each descriptor is 8 bytes: [0]=attr, [1]=reserved, [2-3]=length_le16,
 *   [4-7]=address_le32.
 * 128 entries handles up to 8 MB (128 × 64 KB) per transfer. */
static byte adma_desc_table[128 * 8]
    __attribute__((section(".ddr_bss"), aligned(32)));

/* orig: 0x080343c0 sdcc_dma_setup — build an ADMA2 descriptor table for a
 * data transfer and program the SDHCI ADMA address registers.
 *
 * slot       — SDCC slot index (0 or 1)
 * buf        — physical address of the data buffer (must be in DDR)
 * byte_count — total transfer size in bytes
 *
 * Returns: 0 always.
 *
 * ADMA2 descriptor format (8 bytes each):
 *   byte 0    = attribute: 0x21 = valid(bit0) + tran(bit5), 0x01 = nop
 *               bit 1 (0x02) is OR'd onto the last entry as end-of-list marker
 *   byte 1    = reserved (always 0)
 *   bytes 2-3 = transfer length, little-endian uint16 (0 means 64 KB)
 *   bytes 4-7 = buffer physical address, little-endian uint32
 *
 * Each descriptor covers up to 64 KB (0x10000 bytes). Transfers larger
 * than 64 KB are split across multiple descriptors.
 *
 * sdcc_event_notify(4,...) issues DMB (barrier) before and after each
 * region of work (flags bit 2 → DataMemoryBarrier).
 * sdcc_event_notify(2,...) is a cache maintenance stub; addr/size are
 * used when full cache ops are compiled in.
 *
 * ADMA address registers programmed:
 *   SDHCI_ADMA_ADDRESS_HI (+0x5C) = 0         (32-bit DMA only)
 *   SDHCI_ADMA_ADDRESS_LO (+0x58) = adma_desc_table
 *
 * Original code used hardcoded 0x80201000; we use a .ddr_bss buffer.
 */
uint sdcc_dma_setup(int slot, uint buf_phys, uint byte_count)
{
  sdcc_event_notify(4, 0, 0);                    /* DMB before descriptor table build */
  sdcc_event_notify(2, buf_phys, byte_count);    /* cache flush: data buffer */
  sdcc_event_notify(4, 0, 0);                    /* DMB after cache flush */
  byte *desc = adma_desc_table;
  uint num_descs = byte_count >> 0x10;            /* number of full 64 KB chunks */
  if ((byte_count & 0xffff) != 0)
    num_descs = num_descs + 1;                    /* one extra descriptor for remainder */
  memset_zero((void *)adma_desc_table, num_descs << 3); /* zero only the used descriptor slots */
  if (byte_count != 0) {
    while (true) {
      uint chunk = 0x10000;                       /* max 64 KB per descriptor */
      if (byte_count < 0x10000)
        chunk = byte_count;                       /* final (partial) chunk */
      write_le32(buf_phys, desc + 4);             /* descriptor address field (LE32, bytes 4-7) */
      desc[2] = (byte)chunk;                      /* length low byte */
      desc[3] = (byte)(chunk >> 8);               /* length high byte (0 = 64 KB) */
      byte_count = byte_count - chunk;
      *desc = 1;                                  /* default: nop (overwritten if chunk non-zero) */
      desc[1] = 0;
      if (chunk != 0) {
        *desc = 0x21;                             /* attr: valid (bit0) + tran (bit5) */
        desc[1] = 0;
      }
      buf_phys = buf_phys + chunk;
      if (byte_count == 0) break;
      desc = desc + 8;                            /* advance to next 8-byte descriptor */
    }
    *desc = *desc | 2;                            /* set end-of-list bit on last descriptor */
    desc[1] = 0;
  }
  sdcc_event_notify(4, 0, 0);                    /* DMB before programming ADMA address */
  sdcc_event_notify(2, (uint)adma_desc_table, num_descs << 3); /* cache flush: descriptor table */
  sdcc_event_notify(4, 0, 0);                    /* DMB after cache flush */
  sdcc_set_adma_addr_hi(slot, 0);                /* SDHCI_ADMA_ADDRESS_HI (+0x5C) = 0 */
  sdcc_set_adma_addr_lo(slot, (uint)adma_desc_table); /* SDHCI_ADMA_ADDRESS_LO (+0x58) */
  return 0;
}

/* orig: 0x0803456c sdcc_wait_complete — poll SDHCI normal interrupt status
 * register (+0x30) for a completion or error condition.
 *
 * slot       — SDCC slot index (0 or 1)
 * mask       — bits to wait for in SDHCI normal interrupt status (+0x30):
 *                0x10 = BUFF_WRITE_READY
 *                0x20 = BUFF_READ_READY
 *                0x01 = COMMAND_COMPLETE
 *                0x02 = TRANSFER_COMPLETE
 * out_status — receives the raw interrupt status word when a bit matches
 *
 * Returns: 0  — success (matched bit, no error)
 *          1  — error bits present in status (bits [26:16] = SDHCI error fields)
 *          3  — timeout (5 000 000 µs = 5 seconds elapsed without match)
 *          20 (0x14) — invalid mask (no actionable bits)
 *
 * Polls sdcc_read_present() (SDHCI normal interrupt status at +0x30).
 * Also ORs 0x8000 (CARD_REMOVAL) into the check mask to detect hot-unplug.
 * Error bits are in the upper 16 bits of the 32-bit word returned by
 * sdcc_read_present (this controller packs the SDHCI error status register
 * at +0x32 into the upper half of the 32-bit read from +0x30).
 */
uint sdcc_wait_complete(int slot, uint mask, uint *out_status)
{
  if ((mask & 0x7ff003f) == 0)
    return 0x14;                         /* 20: invalid mask — no actionable bits */

  uint elapsed = 0;
  do {
    uint status = sdcc_read_present(slot); /* SDHCI normal interrupt status (+0x30) */
    if (((mask | 0x8000) & status) != 0) { /* matched requested bits, or CARD_REMOVAL */
      *out_status = status;
      if ((status & 0x7ff0000) == 0)     /* bits [26:16] = SDHCI error status (packed) */
        return 0;                        /* success: no errors */
      return 1;                          /* error bits set */
    }
    delay_us(100);                       /* delay 100 µs */
    elapsed = elapsed + 100;
  } while (elapsed < 5000000);           /* timeout after 5 seconds */
  return 3;                              /* timeout */
}

/* orig: 0x08034a40 mmc_switch_cmd6 — send CMD6 (SWITCH) to modify one byte
 * of EXT_CSD, then verify with CMD13 (SEND_STATUS).
 *
 * dev      — pointer to mmc_dev_t device struct
 * cmd6_arg — CMD6 argument:
 *              bits [25:24] = access mode (3 = write byte)
 *              bits [23:16] = byte index (e.g. 179 = EXT_CSD[179] PARTITION_CONFIG,
 *                                              185 = EXT_CSD[185] BOOT_CONFIG_PROT,
 *                                              171 = EXT_CSD[171] USER_WP)
 *              bits [15:8]  = value to write
 *              bits [7:0]   = command set (usually 0)
 *
 * Returns: 0  — success
 *          8  — card not in transfer state after CMD13
 *         19 (0x13) — SWITCH_ERROR bit set in CMD13 R1 response (R1[7])
 *         other — sdcc_send_cmd error from CMD6 or CMD13
 *
 * CMD6 is issued with busy_wait=1 to wait for the card to deassert DAT0
 * (the busy line) before returning. CMD13 is then used to confirm the card
 * is back in state==4 (transfer) and that SWITCH_ERROR (R1[7]) is clear.
 *
 * State extraction: (cmd[3] << 0x13) >> 0x1c  ==  (cmd[3] >> 9) & 0xF
 */
int mmc_switch_cmd6(mmc_dev_t *dev, uint cmd6_arg)
{
  int ret;
  mmc_cmd_t cmd; /* reused for CMD6 then CMD13 */

  /* CMD6: SWITCH — modify one EXT_CSD byte */
  memset_zero(&cmd, sizeof(cmd));
  cmd.cmd_num = 6;                                 /* CMD6: SWITCH */
  cmd.cmd_arg = (int)cmd6_arg;                     /* switch argument */
  *(uint8_t *)&cmd.resp_type = 1;                  /* resp_type: R1b */
  cmd.busy_wait = 1;                               /* busy_wait: wait for DAT0 deassert */
  ret = sdcc_send_cmd(dev, &cmd);
  if (ret == 0) {
    /* CMD13: SEND_STATUS — verify card returned to transfer state */
    memset_zero(&cmd, sizeof(cmd));
    cmd.cmd_num = 0xd;                             /* CMD13: SEND_STATUS */
    cmd.cmd_arg = (uint)dev->rca << 0x10; /* RCA in bits [31:16] */
    *(uint8_t *)&cmd.resp_type = 1;                /* resp_type: R1 */
    ret = sdcc_send_cmd(dev, &cmd);
    if (ret == 0) {
      if ((uint)(cmd.resp[0] << 0x13) >> 0x1c == 4) {  /* R1[12:9] CURRENT_STATE == 4 (transfer)? */
        ret = 0;
        if (cmd.resp[0] << 0x18 < 0) {             /* R1[7] SWITCH_ERROR set? */
          ret = 0x13;
        }
      }
      else {
        ret = 8;                                   /* card not in transfer state */
      }
    }
  }
  return ret;
}

/* orig: 0x08034b88 sdcc_setup_data_xfer — fire a command and poll MCI_STATUS
 * (+0x34) until CMD_RESPONSE_END, CMD_TIMEOUT, or CMD_CRC_FAIL is seen.
 *
 * dev — pointer to mmc_dev_t device struct; dev[0] = slot index
 * cmd — command struct: [0]=cmd_num, [7]=busy_wait (cleared if PROG_DONE),
 *       [8]=status (receives MCI_STATUS snapshot on return)
 *
 * Returns: 0 — CMD_RESPONSE_END (0x40): command completed, transfer may proceed
 *          1 — CMD_TIMEOUT (0x4): no response within timeout
 *          2 — command sent (CMD_SENT), meaning no response expected (not used
 *              as a return value here — Ghidra initializes uVar5=1 but the
 *              CMD_SENT path is not present; this may be dead code)
 *          4 — CMD_CRC_FAIL (0x1) on a command that is not CMD41/CMD1/CMD5
 *
 * MCI_STATUS bits checked:
 *   0x1      = CMD_CRC_FAIL  → error (except for CMD41/CMD1/CMD5 which use R3/R4)
 *   0x4      = CMD_TIMEOUT   → return 2 (timeout)
 *   0x40     = CMD_RESPONSE_END → success; also checks for PROG_DONE
 *   0x800000 = PROG_DONE     → if seen with CMD_RESPONSE_END, clears cmd[7] (busy_wait)
 *
 * Each matched bit is cleared in MCI_CLEAR (+0x38) before returning.
 * cmd[8] (CMD_STATUS) is updated with the final MCI_STATUS snapshot.
 */
uint sdcc_setup_data_xfer(mmc_dev_t *dev, mmc_cmd_t *cmd)
{
  int slot = dev->slot;
  uint result = 1;
  uint status = 0;
  uint iter = 0;

  do {
    if (0x7ffff < iter) goto LAB_08034c08;
    status = sdcc_read_status(slot);     /* MCI_STATUS (+0x34) */
    if ((status & 0x40) != 0) {          /* CMD_RESPONSE_END (0x40): command completed */
      MCI_REG(slot, MCI_CLEAR) = 0x40;  /* MCI_CLEAR (+0x38): ack CMD_RESPONSE_END */
      result = 0;
      if ((status & 0x800000) != 0) {    /* PROG_DONE (0x800000): card already done */
        MCI_REG(slot, MCI_CLEAR) = 0x800000; /* MCI_CLEAR (+0x38): ack PROG_DONE */
        cmd->busy_wait = 0;             /* clear busy_wait: no need to poll card busy */
      }
      goto LAB_08034c08;
    }
    if ((status & 4) != 0) {            /* CMD_TIMEOUT (0x4) */
      MCI_REG(slot, MCI_CLEAR) = 4;     /* MCI_CLEAR (+0x38): ack CMD_TIMEOUT */
      result = 2;
      goto LAB_08034c08;
    }
    iter = iter + 1;
  } while ((status & 1) == 0);          /* CMD_CRC_FAIL (0x1): poll until seen or loop exits */
  int cmd_num = cmd->cmd_num;
  if (cmd_num == 0x29 || cmd_num == 1 || cmd_num == 5)
    /* CMD41/CMD1/CMD5 use R3/R4 (no CRC): CRC_FAIL is expected, treat as success */
    result = 0;
  else
    result = 4;                          /* genuine CRC error on other commands */
  MCI_REG(slot, MCI_CLEAR) = 1;         /* MCI_CLEAR (+0x38): ack CMD_CRC_FAIL */
LAB_08034c08:
  cmd->status = status;                  /* save MCI_STATUS snapshot */
  return result;
}

/* orig: 0x08034c14 sdcc_adma_transfer — read data from the MCI FIFO into
 * a caller-supplied buffer, using burst DMA or word-at-a-time PIO depending
 * on FIFO fill level and buffer alignment.
 *
 * dev        — pointer to mmc_dev_t device struct; dev[0] = slot index
 * buf        — destination buffer; may be unaligned
 * byte_count — total bytes to read
 *
 * Returns: 0 on success, 13 (0xd) on error.
 *
 * The main loop polls MCI_STATUS (+0x34) and dispatches to one of three
 * read paths based on status bits and buf alignment:
 *
 *   1. Error check first: if bits 0x2a (DATA_CRC_FAIL | CMD_TIMEOUT | RX_OVERRUN)
 *      are set → error recovery (goto LAB_08034c9e, return 0xd)
 *
 *   2. Check RX_DATA_AVAIL (0x200000): any data ready in FIFO?
 *        a. RX_FIFO_HFULL (0x8000) set AND buf is word-aligned:
 *             → adma_bounce_read(): 8-word (32-byte) burst from MCI_FIFO (+0x80)
 *        b. Otherwise (FIFO not half-full, or unaligned buf):
 *             → one word at a time from MCI_FIFO (+0x80):
 *                - unaligned buf: scatter word byte-by-byte into buf
 *                - aligned buf:   store word directly as uint32
 *
 * Error recovery block (LAB_08034c9e):
 *   This block is guarded by `if (false)` in the decompiled output — a
 *   Ghidra artifact where the goto target fell inside a conditional that
 *   Ghidra could not express as a fall-through. The block IS compiled and
 *   IS reachable at runtime via the goto inside the while loop. Do not
 *   remove it. The compiler emits the block correctly regardless.
 *
 *   Recovery saves MCI_POWER (+0x00), MCI_CLK (+0x04), MCI_INT_MASK0 (+0x3C),
 *   calls sdcc_clock_setup to reset the clock, then restores the registers.
 *   The `dev + 3` passed to mmc_set_bus_width is a pointer to the device
 *   struct's third word (bus width / speed configuration).
 */
uint sdcc_adma_transfer(uint *hotplug, uint *buf, int byte_count)
{
  int slot = *hotplug;                   /* slot index */
  bool unaligned = ((uint)buf & 3) != 0; /* true if buffer is NOT word-aligned */
  uint ret = 0;
  int remaining = 0;

  if (buf == (uint *)0x0) {
    ret = 0xd;
  }
  else {
    while (0 < byte_count) {
      uint status = sdcc_read_status(slot); /* MCI_STATUS (+0x34) */
      if ((status & 0x2a) != 0) {
        /* 0x2a = DATA_CRC_FAIL (0x2) | CMD_TIMEOUT (0x8) | RX_OVERRUN (0x20) */
        ret = 0xd;
        goto LAB_08034c9e;
      }
      if (byte_count == 0) break;
      if ((status & 0x200000) != 0) {    /* RX_DATA_AVAIL (0x200000): data in FIFO? */
        if (((status & 0x8000) == 0) || (unaligned)) {
          /* RX_FIFO_HFULL not set, or unaligned buf: read one word from MCI_FIFO (+0x80) */
          uint fifo_word = MCI_REG(slot, MCI_FIFO); /* MCI_FIFO (+0x80) */
          if (unaligned) {
            /* Unaligned buffer: scatter the 32-bit FIFO word byte-by-byte */
            uint byte_idx = 0;
            uint *dst = buf;
            do {
              buf = (uint *)((int)dst + 1);
              *(char *)dst = (char)fifo_word;
              fifo_word = fifo_word >> 8;
              byte_idx = byte_idx + 1;
              dst = buf;
            } while (byte_idx < 4);
          }
          else {
            /* Word-aligned buffer: store directly */
            *buf = fifo_word;
            buf = buf + 1;
          }
          byte_count = byte_count + -4;
        }
        else {
          /* RX_FIFO_HFULL (0x8000) set AND buf is word-aligned:
           * burst read 8 words (32 bytes) via adma_bounce_read */
          remaining = byte_count;
          adma_bounce_read(slot, buf, &remaining);
          buf = (uint *)((char *)buf + (byte_count - remaining));
          byte_count = remaining;
        }
      }
    }
    /*
     * LAB_08034c9e — error recovery path (only reachable via goto above).
     *
     * `if (false)` is a Ghidra decompilation artifact: the label is
     * reached solely via goto and Ghidra could not represent it as a
     * fall-through, so it wrapped it in a dead conditional. The block
     * IS compiled correctly by the C compiler and IS reachable at runtime.
     * Do not remove the `if (false)` guard or the block inside it.
     */
    if (false) {
LAB_08034c9e:
      /* Save MCI register state, reset clock, then restore registers */
      mmc_set_bus_width((mmc_dev_t *)(hotplug + 3), 5, 0, 0);
      {
        int err_slot = *hotplug;
        uint saved_clk  = MCI_REG(err_slot, MCI_CLK);       /* MCI_CLK   (+0x04): save before reset */
        uint saved_pwr  = MCI_REG(err_slot, MCI_POWER);     /* MCI_POWER (+0x00): save before reset */
        uint saved_mask = MCI_REG(err_slot, MCI_INT_MASK0);  /* MCI_INT_MASK0 (+0x3C): save before reset */
        sdcc_clock_setup(err_slot, 0, 2);
        MCI_REG(err_slot, MCI_CLK)       = saved_clk;  /* MCI_CLK: restore */
        sdcc_enable_clock(err_slot);
        MCI_REG(err_slot, MCI_POWER)     = saved_pwr;  /* MCI_POWER: restore */
        sdcc_enable_clock(err_slot);
        MCI_REG(err_slot, MCI_INT_MASK0) = saved_mask; /* MCI_INT_MASK0: restore */
        mmc_set_bus_width((mmc_dev_t *)(hotplug + 3), *(char *)((int)hotplug + 0x15) == 2, 0, 0);
      }
    }
    sdcc_set_all_irq(slot);              /* MCI_CLEAR (+0x38) = 0x18007ff: clear all status bits */
  }
  return ret;
}

/* orig: 0x08034eaa sdcc_adma_write — issue CMD55 (APP_CMD) prefix then the
 * actual application command (ACMD).
 *
 * dev — pointer to mmc_dev_t device struct
 * cmd — command struct to send after CMD55:
 *         [0]=cmd_num, [1]=arg, [2]=resp_type, [7]=busy_wait, etc.
 *
 * Returns: 0 always (errors from sdcc_send_cmd calls are ignored).
 *
 * CMD55 (APP_CMD, 0x37) signals to the card that the next command is an
 * application-specific command (ACMD). RCA is placed in bits [31:16] of
 * the CMD55 argument, read as a ushort from byte offset 10 of the device
 * struct. After CMD55 (result ignored), the caller's ACMD is fired.
 *
 * Note: this function is misnamed — it does not perform a DMA write
 * itself; it is simply the CMD55+ACMD dispatch wrapper.
 */
uint sdcc_adma_write(mmc_dev_t *dev, mmc_cmd_t *cmd)
{
  mmc_cmd_t app_cmd;

  memset_zero(&app_cmd, sizeof(app_cmd));
  app_cmd.cmd_num = 0x37;                         /* CMD55: APP_CMD (precedes all ACMDs) */
  app_cmd.cmd_arg = (uint)dev->rca << 0x10; /* RCA in bits [31:16] */
  *(uint8_t *)&app_cmd.resp_type = 1;             /* resp_type: R1 */
  sdcc_send_cmd(dev, &app_cmd);
  sdcc_send_cmd(dev, cmd);                        /* fire the actual ACMD */
  return 0;
}

/* orig: 0x08034edc sdcc_pre_cmd_hook — clear pending MCI_STATUS bits, then
 * build a command config array and fire the command via sdcc_cleanup().
 *
 * dev — pointer to mmc_dev_t device struct; dev[0] = slot index
 * cmd — command struct:
 *         [0] = cmd_num   (command index, placed in cmd_config[6])
 *         [1] = arg       (32-bit argument, placed at cmd_config byte offset 16)
 *         [2] = resp_type (byte: 0=none, 1=R1/R1b, 4=R2)
 *         [7] = busy_wait (1 = assert busy_signal_enable)
 *
 * cmd_config[] layout (10 shorts = 20 bytes, contiguous for sdcc_cleanup):
 *   [0] = data_present_enable (1 for CMD53/CMD17/CMD18/CMD24/CMD25)
 *   [1] = busy_signal_enable  (from cmd[7]; waits for DAT0 deassert)
 *   [2] = has_response        (1 for any non-zero resp_type)
 *   [3] = (unused)
 *   [4] = index_check         (1 for R2/resp_type==4, which has no index)
 *   [5] = crc_check           (1 for resp_type != 0)
 *   [6] = command_index       (6-bit CMD number)
 *   [7] = (unused)
 *   [8..9] = command argument (int32 overlaid at byte offset 16)
 *
 * IMPORTANT: cmd_config must be a contiguous array — sdcc_cleanup() reads
 * fields by array index. Separate locals would break the layout.
 *
 * Status clearing: polls MCI_STATUS (+0x34) up to 1000 times writing
 * 0x18007ff to MCI_CLEAR (+0x38) until all bits clear. On timeout,
 * disables the clock-enable bit in MCI_DATA_CTL (+0x2c) bit 0 then
 * calls sdcc_enable_clock to re-enable.
 *
 * Commands that set data_present_enable (cmd_config[0] = 1):
 *   0x35 = CMD53 (SDIO_RW_EXTENDED), 0x11 = CMD17 (READ_SINGLE_BLOCK),
 *   0x12 = CMD18 (READ_MULTIPLE_BLOCK), 0x18 = CMD24 (WRITE_BLOCK),
 *   0x19 = CMD25 (WRITE_MULTIPLE_BLOCK)
 */
void sdcc_pre_cmd_hook(mmc_dev_t *dev, mmc_cmd_t *cmd)
{
  int slot = dev->slot;
  uint iter = 0;
  sdcc_cmd_config_t cfg;

  memset_zero(&cfg, sizeof(cfg));
  do {
    /* MCI_CLEAR (+0x38) = 0x18007ff: write-1-to-clear all status bits */
    MCI_REG(slot, MCI_CLEAR) = 0x18007ff;
    iter = iter + 1;
    uint status = sdcc_read_status(slot); /* MCI_STATUS (+0x34) */
    if ((status & 0x18007ff) == 0) goto status_clear;
  } while (iter < 1000);
  /* Timeout: disable MCI_DATA_CTL (+0x2c) bit 0 (clock enable) then re-enable */
  MCI_REG(slot, MCI_DATA_CTL) = MCI_REG(slot, MCI_DATA_CTL) & 0xfffffffe;
  sdcc_enable_clock(slot);
status_clear:
  cfg.cmd_index = (short)cmd->cmd_num;  /* command index */
  cfg.data_present = 1;                 /* has_response: set for all commands initially */
  if ((char)cmd->resp_type != 0) {      /* resp_type != 0: a response is expected */
    cfg.crc_check = 1;                  /* crc_check: enable for R1/R1b */
    if ((char)cmd->resp_type == 4)      /* resp_type == 4: R2 (136-bit CID/CSD) */
      cfg.idx_check = 1;               /* index_check: R2 carries no command index */
  }
  if (cmd->busy_wait != 0)
    cfg.ccs_enable = 1;                 /* busy_signal_enable: wait for DAT0 deassert */
  int cmd_num = cmd->cmd_num;
  if (cmd_num == 0x35 || cmd_num == 0x11 || cmd_num == 0x12 ||
      cmd_num == 0x18 || cmd_num == 0x19)
    cfg.dpe = 1;                        /* data_present_enable: CMD53/17/18/24/25 */
  cfg.cmd_arg = cmd->cmd_arg;           /* command argument */
  sdcc_cleanup(slot, &cfg);
}

/* orig: 0x08034f80 sdcc_get_card_status — send CMD13 (SEND_STATUS) and
 * return the CURRENT_STATE nibble from the R1 response.
 *
 * dev — pointer to mmc_dev_t device struct
 *
 * Returns: card state nibble from R1[12:9]:
 *   0 = idle, 1 = ready, 2 = ident, 3 = stby, 4 = tran (transfer),
 *   5 = data, 6 = rcv, 7 = prg (programming), 8 = dis
 * Returns 9 on failure (sdcc_send_cmd error).
 *
 * CMD13 argument: RCA in bits [31:16]. The RCA is a ushort stored at
 * byte offset 10 of the device struct.
 * State extraction: (cmd[3] << 0x13) >> 0x1c  ==  (cmd[3] >> 9) & 0xF
 */
uint sdcc_get_card_status(mmc_dev_t *dev)
{
  int ret;
  uint state;
  mmc_cmd_t cmd;

  state = 9;   /* default: error / unknown */
  memset_zero(&cmd, sizeof(cmd));
  cmd.cmd_num = 0xd;                               /* CMD13: SEND_STATUS */
  cmd.cmd_arg = (uint)dev->rca << 0x10; /* RCA in bits [31:16] */
  *(uint8_t *)&cmd.resp_type = 1;                  /* resp_type: R1 */
  ret = sdcc_send_cmd(dev, &cmd);
  if (ret == 0) {
    state = (uint)(cmd.resp[0] << 0x13) >> 0x1c;  /* R1[12:9] = CURRENT_STATE */
  }
  return state;
}

/* orig: 0x080350be sdcc_wait_card_ready — poll CMD13 (SEND_STATUS) until
 * the card reports CURRENT_STATE == 4 (transfer state).
 *
 * dev — pointer to mmc_dev_t device struct
 *
 * Returns: 0 — success (card reached transfer state).
 *          8 — timeout (0x7ffff = 524287 iterations at 100 µs = ~52 seconds).
 *
 * Called after a write command or CMD6 SWITCH to confirm the card is
 * ready for the next command. Delays 100 µs between CMD13 polls.
 */
uint sdcc_wait_card_ready(mmc_dev_t *dev)
{
  uint iter = 0;
  while (true) {
    if (0x7ffff < iter)
      return 8;                          /* timeout */
    int state = sdcc_get_card_status(dev);
    if (state == 4) break;               /* state == transfer (4): card ready */
    delay_us(100);                       /* delay 100 µs */
    iter = iter + 1;
  }
  return 0;
}

/* orig: 0x08035040 sdcc_pre_write_setup — compute the data timeout and
 * total byte count for a write, and program them into MCI hardware.
 *
 * dev         — pointer to mmc_dev_t device struct; dev[0] = slot index
 * is_reliable — 1 = reliable write mode (shorter per-block timeout)
 * num_blocks  — number of 512-byte blocks to transfer
 *
 * Returns: total byte count (sector_size × num_blocks).
 *
 * Writes to two MCI registers:
 *   MCI_DATA_TIMER  (sdcc_mci_base[slot] + 0x24) = timeout counter value
 *   MCI_DATA_LENGTH (sdcc_mci_base[slot] + 0x28) = total transfer bytes
 *
 * Timeout computation:
 *   Base (ms per block):
 *     Card type 0x02 or 0x06 (SD/SDHC):  5000 ms normal, 2000 ms reliable
 *     Other (MMC/eMMC):                   5000 ms normal,  400 ms reliable
 *   Multiplier:
 *     dev[DEV_CLOCK_KHZ] == 0: use 50000 (fallback when device clock is unknown)
 *     otherwise:      dev[DEV_CLOCK_KHZ] (device-reported max clock ticks per ms)
 *
 * Card type is read from *(char*)(dev + 2) (the low byte of dev[2]).
 *
 * Sector size:
 *   dev[DEV_CUSTOM_SECTOR] (dev[DEV_CUSTOM_SECTOR]) == 1: use dev[DEV_SECTOR_SIZE] (dev[DEV_SECTOR_SIZE])
 *   otherwise: 1 (single-word transfer, non-block mode)
 *
 * Note: the slot index is cast to (short) for the register base array
 * lookup — this matches the original binary which stored slot as a short.
 */
int sdcc_pre_write_setup(mmc_dev_t *dev, int is_reliable, int num_blocks)
{
  uint slot = dev->slot;
  uint sector_sz = 1;
  int timeout_ms = 5000;                  /* default timeout base (ms per block) */

  if ((dev->card_type == 2) || (dev->card_type == 6)) {
    /* SD or SDHC card type (0x02 = SD, 0x06 = eMMC subtype mapped to SD path?) */
    if (is_reliable != 0)
      timeout_ms = 2000;                  /* reliable write: tighter per-block timeout */
  }
  else if (is_reliable != 0) {
    /* MMC/eMMC card type, reliable write */
    timeout_ms = 400;
  }
  if (dev->clock_khz == 0)
    timeout_ms = timeout_ms * 50000;      /* unknown clock: use large fallback multiplier */
  else
    timeout_ms = dev->clock_khz * timeout_ms; /* scale by device max clock ticks per ms */

  /* MCI_DATA_TIMER (+0x24): data transfer timeout in controller clock ticks */
  MCI_REG((short)slot, MCI_DATA_TIMER) = timeout_ms;
  if (dev->custom_sector == 1)                    /* custom_sector: multi-block device */
    sector_sz = dev->sector_size & 0xffff;        /* sector_size: low 16 bits */
  /* MCI_DATA_LENGTH (+0x28): total byte count for this transfer */
  MCI_REG((short)slot, MCI_DATA_LENGTH) = sector_sz * num_blocks;
  return sector_sz * num_blocks;
}

/* orig: 0x080350ee sdcc_post_write_check — poll MCI_STATUS (+0x34) after a
 * write command fires, waiting for DATA_END or an error condition.
 *
 * dev — pointer to mmc_dev_t device struct; dev[0] = slot index
 *
 * Returns: 0  — DATA_END (0x100) seen: data transfer complete
 *         14 (0xe) — write-path error: 0x1a = DATA_CRC_FAIL (0x2) |
 *                    DATA_TIMEOUT (0x8) | TX_UNDERRUN (0x10)
 *         13 (0xd) — generic error: 0x2a = DATA_CRC_FAIL (0x2) |
 *                    CMD_TIMEOUT (0x8) | RX_OVERRUN (0x20)
 *          8       — timeout (0x7ffff iterations without DATA_END)
 *
 * The 0x1a mask is checked before 0x2a because the two overlap on bits
 * DATA_CRC_FAIL (0x2) and CMD/DATA_TIMEOUT (0x8 is CMD_TIMEOUT in 0x2a
 * but DATA_TIMEOUT in 0x1a — these are different bits and do not actually
 * overlap; the distinction is: 0x1a catches TX_UNDERRUN, 0x2a catches
 * RX_OVERRUN).
 *
 * On DATA_END: calls sdcc_set_all_irq() to write MCI_CLEAR (+0x38) =
 * 0x18007ff, clearing all status bits.
 */
uint sdcc_post_write_check(mmc_dev_t *dev)
{
  uint slot = dev->slot;
  uint iter = 0;
  uint status;
  do {
    if (0x7ffff < iter)
      return 8;                          /* timeout */
    status = sdcc_read_status(slot);     /* MCI_STATUS (+0x34) */
    if ((status & 0x1a) != 0)
      /* 0x1a = DATA_CRC_FAIL (0x2) | DATA_TIMEOUT (0x8) | TX_UNDERRUN (0x10) */
      return 0xe;                        /* write-path error */
    if ((status & 0x2a) != 0)
      /* 0x2a = DATA_CRC_FAIL (0x2) | CMD_TIMEOUT (0x8) | RX_OVERRUN (0x20) */
      return 0xd;                        /* generic error */
    iter = iter + 1;
  } while ((status & 0x100) == 0);       /* loop until DATA_END (0x100) */
  sdcc_set_all_irq(slot);                /* MCI_CLEAR (+0x38) = 0x18007ff: clear all */
  return 0;
}

/* orig: 0x08035134 sdcc_busy_wait — wait for the card to finish programming
 * by polling MCI_STATUS (+0x34) for PROG_DONE (0x800000), with a CMD13
 * SEND_STATUS fallback if the hardware busy poll times out.
 *
 * dev — pointer to mmc_dev_t device struct; dev[0] = slot index
 *
 * Returns: 0 — card is ready (PROG_DONE seen, or CMD13 confirmed state==4).
 *          7 — timeout and CMD13 failed or returned non-transfer state.
 *
 * Primary path: polls MCI_STATUS (+0x34) for PROG_DONE (0x800000) with
 * 10 µs delays. On PROG_DONE: writes MCI_CLEAR (+0x38) = 0x800000 to
 * acknowledge it, then returns success.
 *
 * Fallback (after 0x7ffff = ~524287 iterations at 10 µs ≈ 5 seconds):
 * Issues CMD13 to query card state. Returns 0 if state==4 (transfer).
 *
 * Note: `(true) &&` in the fallback branch is a Ghidra artifact from
 * a conditional expression that always evaluates true; it has no effect.
 */
uint sdcc_busy_wait(mmc_dev_t *dev)
{
  int slot = dev->slot;
  uint ret = 7;                           /* default return: timeout/error */
  uint iter = 0;

  do {
    if (0x7ffff < iter) {
      /* Hardware busy timeout: fall back to CMD13 card status check */
      if ((true) && (slot = sdcc_get_card_status(dev), slot == 4)) {
LAB_0803517c:
        ret = 0;                         /* card in transfer state: success */
      }
      return ret;
    }
    uint status = sdcc_read_status(slot); /* MCI_STATUS (+0x34) */
    if ((status & 0x800000) != 0) {      /* PROG_DONE (0x800000): card done programming */
      MCI_REG(slot, MCI_CLEAR) = 0x800000; /* MCI_CLEAR (+0x38): ack PROG_DONE */
      goto LAB_0803517c;
    }
    delay_us(10);                        /* delay 10 µs */
    iter = iter + 1;
  } while (true);
}

/* orig: 0x08035188 sdcc_pio_transfer — write a buffer to the MCI FIFO using
 * programmed I/O, with burst fallback via adma_bounce_write.
 *
 * dev        — pointer to mmc_dev_t device struct; dev[0] = slot index
 * buf        — source data buffer; may be unaligned
 * byte_count — total bytes to write
 *
 * Returns: 0 on success (DATA_END seen after all data sent).
 *         14 (0xe) on error (write errors or timeout waiting for DATA_END).
 *
 * Three write paths, selected by MCI_STATUS (+0x34) bits and alignment:
 *
 *   1. TX_FIFO_HFULL (0x4000) set, buf word-aligned, >= 32 bytes remain:
 *        → adma_bounce_write(): 8-word burst write to MCI_FIFO (+0x80)
 *
 *   2. TX_FIFO_HFULL (0x4000) not set, or < 32 bytes, buf word-aligned:
 *        → single word read from buf, write to MCI_FIFO (+0x80)  [LAB_0803520c]
 *
 *   3. Unaligned buf (bVar9 == true, any TX state):
 *        → assemble word byte-by-byte from buf, write to MCI_FIFO (+0x80) [LAB_08035218]
 *
 * MCI_STATUS bit 0x10000 (DATA_BLK_END): when set, a block boundary was
 * just crossed; the loop skips writing until it clears.
 *
 * Error check: bits 0x1a (DATA_CRC_FAIL | DATA_TIMEOUT | TX_UNDERRUN)
 * cause an immediate break and return of 0xe.
 *
 * After all data is written, the function waits for DATA_END (0x100) in
 * MCI_STATUS while checking for 0x1a errors during the wait.
 *
 * sdcc_set_all_irq (MCI_CLEAR = 0x18007ff) is called at start and end.
 *
 * Note: `if (true)` around the DATA_END wait loop is a Ghidra artifact
 * (always-true guard on a do-while → while transformation); no effect.
 */
uint sdcc_pio_transfer(uint *hotplug, byte *buf, int byte_count)
{
  int slot = *hotplug;                   /* slot index */
  uint ret = 0;
  bool unaligned = ((uint)buf & 3) != 0; /* true if buffer is NOT word-aligned */
  uint status = 0;
  int remaining = 0;

  if (buf == (byte *)0x0)
    return 0xe;                          /* null buffer: error */
  sdcc_set_all_irq(slot);               /* MCI_CLEAR (+0x38) = 0x18007ff: clear all status bits */
LAB_08035234:
  do {
    if (byte_count < 1) goto LAB_08035238;
    status = sdcc_read_status(slot);     /* MCI_STATUS (+0x34) */
    if ((status & 0x1a) != 0) break;     /* 0x1a = DATA_CRC_FAIL|DATA_TIMEOUT|TX_UNDERRUN */
    if (byte_count == 0) goto LAB_08035238;
    if ((status & 0x10000) == 0) {       /* DATA_BLK_END (0x10000): skip if block boundary */
      if ((status & 0x4000) == 0) {      /* TX_FIFO_HFULL (0x4000) not set: write one word */
        if (!unaligned) goto LAB_0803520c;
LAB_08035218:
        /* Unaligned write path: assemble one 32-bit word from 4 bytes in buf */
        {
          uint word = 0;
          uint shift = 0;
          byte *src = buf;
          do {
            buf = src + 1;
            word = word | (uint)*src << (shift & 0xff); /* pack byte into word */
            shift = shift + 8;
            src = buf;
          } while (shift < 0x20);
          MCI_REG(slot, MCI_FIFO) = word; /* MCI_FIFO (+0x80): write assembled word */
        }
      }
      else {
        /* TX_FIFO_HFULL (0x4000) is set */
        if (unaligned) goto LAB_08035218; /* unaligned buf: use byte-assembly path */
        if (0x1f < byte_count) {
          /* Word-aligned buf, >= 32 bytes: use burst write via adma_bounce_write */
          remaining = byte_count;
          adma_bounce_write(slot, (uint *)buf, &remaining);
          int after = remaining;
          buf = buf + (byte_count - remaining);
          status = sdcc_read_status(slot); /* MCI_STATUS (+0x34): re-read after burst */
          byte_count = after;
          goto LAB_08035234;
        }
LAB_0803520c:
        /* Word-aligned buf, < 32 bytes or FIFO not half-full: write one word */
        {
          uint word = *(uint *)buf;
          buf = buf + 4;
          MCI_REG(slot, MCI_FIFO) = word; /* MCI_FIFO (+0x80): write one word */
        }
      }
      byte_count = byte_count + -4;
    }
  } while (true);
  /* Write-path error: 0x1a bits detected */
  ret = 0xe;
  goto LAB_08035254;
LAB_08035238:
  /* All data written: poll for DATA_END (0x100) in MCI_STATUS (+0x34) */
  if (true) {                            /* Ghidra artifact: always-true guard */
    while ((status & 0x100) == 0) {      /* DATA_END (0x100) not yet seen */
      if ((status & 0x1a) != 0) {        /* 0x1a error while waiting for DATA_END */
        ret = 0xe;
        goto LAB_08035254;
      }
      status = sdcc_read_status(slot);   /* MCI_STATUS (+0x34): poll */
    }
  }
LAB_08035254:
  sdcc_set_all_irq(slot);               /* MCI_CLEAR (+0x38) = 0x18007ff: clear all status bits */
  return ret;
}
