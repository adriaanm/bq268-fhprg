/* sdcc_regs.c — SDCC controller MMIO register access wrappers.
 *
 * The Qualcomm SDCC controller exposes two distinct register windows per slot:
 *
 *   DAT_0804e2c8[slot]  MCI core base  (slot 0 = 0x07824000, slot 1 = 0x07864000)
 *   DAT_0804e2d8[slot]  SDHCI HC base  (slot 0 = 0x07824900, slot 1 = 0x07864900)
 *
 * MCI core registers (offsets from DAT_0804e2c8[slot]):
 *   +0x00  MCI_POWER
 *   +0x04  MCI_CLK              — clock config, bus speed, flow control (bit 9)
 *   +0x08  MCI_ARGUMENT
 *   +0x0C  MCI_CMD
 *   +0x10  MCI_RESP_CMD
 *   +0x14  MCI_RESP_0
 *   +0x18  MCI_RESP_1
 *   +0x1C  MCI_RESP_2
 *   +0x20  MCI_RESP_3
 *   +0x24  MCI_DATA_TIMER
 *   +0x28  MCI_DATA_LENGTH
 *   +0x2C  MCI_DATA_CTL
 *   +0x30  MCI_DATA_COUNT
 *   +0x34  MCI_STATUS           — status bits (read-only):
 *            bit 0  CMD_CRC_FAIL   bit 1  DATA_CRC_FAIL
 *            bit 2  CMD_TIMEOUT    bit 3  DATA_TIMEOUT
 *            bit 4  TX_UNDERRUN    bit 5  RX_OVERRUN
 *            bit 6  CMD_RESP_END   bit 7  CMD_SENT
 *            bit 8  DATA_END       bit 14 TX_FIFO_HFULL
 *            bit 15 RX_FIFO_HFULL bit 20 TX_DATA_AVAIL
 *            bit 21 RX_DATA_AVAIL bit 23 PROG_DONE
 *   +0x38  MCI_CLEAR            — write 1 to clear MCI_STATUS bits
 *   +0x3C  MCI_INT_MASK0
 *   +0x44  MCI_FIFO_COUNT
 *   +0x50  MCI_VERSION
 *   +0x6C  MCI_STATUS2          — bit 0: clock-stable / internal clock ready
 *   +0x78  MCI_HC_MODE          — bit 0: 8-bit bus width enable
 *   +0x80  MCI_FIFO             — data FIFO
 *   +0xDC  (PLL status latch)
 *   +0xE4  (PLL divider latch)
 *   +0xE8  (PLL mode select)
 *
 * SDHCI HC registers (offsets from DAT_0804e2d8[slot]):
 *   +0x04  BLKSZ_REG            — block size (16-bit)
 *   +0x06  BLK_CNT_REG          — block count (16-bit)
 *   +0x08  ARGUMENT_REG         — command argument (32-bit)
 *   +0x0C  TRANS_MODE_REG       — transfer mode (16-bit):
 *            bit 0  BLK_CNT_EN   bit 1  DIR_READ    bit 2-3 AUTO_CMD
 *            bit 4  DMA_EN       bit 5  MULTI_BLK
 *   +0x0E  CMD_REG              — command register (16-bit):
 *            bits 0-1  RESP_TYPE  bit 3  CRC_CHECK  bit 4  IDX_CHECK
 *            bit 5  DATA_PRESENT  bits 6-7 CMD_TYPE  bits 8-15 CMD_INDEX
 *   +0x10  RESP_REG             — response words at +0x10, +0x14, +0x18, +0x1C
 *   +0x24  PRESENT_STATE_REG    — present state (read-only)
 *   +0x28  HOST_CTRL1_REG       — host control 1 (byte):
 *            bit 1-2  DMA_SEL (0=SDMA, 1=ADMA32, 2=ADMA64)
 *            bit 3    HS_EN    bit 4  DATA_8BIT    bit 5  DATA_4BIT
 *   +0x29  PWR_CTRL_REG         — power control (byte):
 *            bit 0   SD_BUS_POWER   bits 1-3 SD_BUS_VLT (1=1.8V, 5=2.5V, 7=3.3V)
 *   +0x2C  CLK_CTRL_REG         — clock control (16-bit):
 *            bit 0   INTERNAL_CLK_EN  bit 1  INTERNAL_CLK_STABLE  bit 2  SD_CLK_EN
 *            bits 8-15  SDCLK_FREQ_SEL (divider)
 *   +0x2E  TIMEOUT_REG          — timeout control (byte)
 *   +0x2F  RESET_REG            — software reset (byte):
 *            bit 0  RESET_ALL   bit 1  RESET_CMD   bit 2  RESET_DATA
 *   +0x30  NRML_INT_STS_REG     — normal interrupt status (32-bit, write 1 to clear)
 *   +0x34  NRML_INT_STS_EN_REG  — normal interrupt status enable (32-bit)
 *   +0x38  NRML_INT_SIG_EN_REG  — normal interrupt signal enable (32-bit)
 *   +0x3E  HOST_CTRL2_REG       — host control 2 (16-bit), UHS mode select in bits 0-2
 *   +0x40  CAPS_REG1            — capabilities 1 (32-bit, read-only)
 *   +0x44  CAPS_REG2            — capabilities 2 (32-bit, read-only)
 *   +0x58  ADM_ADDR_REG         — ADMA system address lo (32-bit)
 *   +0x5C  (ADMA system address hi, 32-bit)
 *
 * Vendor-specific registers (offsets from DAT_0804e2d8[slot]):
 *   +0x100  DLL_CONFIG_REG           — DLL/vendor control:
 *              bit 29 DLL_RST  bit 30 DLL_PDN (power down)
 *   +0x108  REG_DLL_STATUS
 *   +0x10C  VENDOR_SPECIFIC_FUNC     — vendor function register:
 *              bit 1  HC_SELECT (LED enable in this context)
 *   +0x11C  VENDOR_SPECIFIC_CAPABILITIES0  — shadow of CAPS_REG1 (writable)
 *   +0x120  (shadow of CAPS_REG2, writable)
 *
 * Source: src/fhprg/fhprg_8007b18.c (lines 5734–6630)
 */
#include "firehose.h"

/* Register base arrays:
 *   DAT_0804e2c8[slot] = MCI core base  (slot 0 = 0x07824000)
 *   DAT_0804e2d8[slot] = SDHCI HC base  (slot 0 = 0x07824900)
 */

/* orig: 0x0800bbb4 sdcc_set_transfer_mode — build and write TRANS_MODE_REG (HC+0x2C).
 *
 * Encodes a transfer-mode descriptor struct into the SDHCI TRANS_MODE_REG
 * 16-bit field and commits it.  After writing, calls sdcc_enable_clock() to
 * poll MCI_STATUS2 bit 0 (internal-clock-stable) before returning.
 *
 * mode[] layout (array of ushort, accessed as individual bytes):
 *   mode[0]       multi_blk   → TRANS_MODE_REG bit 5  (MULTI_BLK_SEL)
 *   mode[1] lo    dma_en      → TRANS_MODE_REG bit 3  (DMA_EN / auto-CMD12)
 *   mode[2] lo    dir_read    → TRANS_MODE_REG bit 1  (DATA_XFER_DIR: 1=read)
 *   mode[0]+3 lo  auto_cmd    → TRANS_MODE_REG bit 2  (AUTO_CMD_EN)
 *   mode[0]+5 lo  blk_cnt_en  → TRANS_MODE_REG bit 0  (BLK_CNT_EN)
 *
 * Register written: MCI_DATA_CTL (MCI core+0x2C) — note: despite the HC
 * description above, the write target here is DAT_0804e2c8[slot]+0x2C which
 * is MCI_DATA_CTL, the legacy transfer-control register, not the SDHCI
 * TRANS_MODE_REG at HC+0x0C.  The bit encoding matches MCI_DATA_CTL:
 *   bit 0  ENABLE   bit 1  DIR(1=read)  bit 3  DMA_EN  bit 4..7  BLOCK_SIZE
 */
void sdcc_set_transfer_mode(int slot, ushort *mode)
{
  uint uVar1;

  /* bit 4: multi-block flag into MCI_DATA_CTL[7:4] (block-size field) */
  uVar1 = (uint)*mode << 4;
  if ((char)mode[1] != '\0') {
    uVar1 = uVar1 | 8;   /* MCI_DATA_CTL bit 3: DMA_EN */
  }
  if ((char)mode[2] == '\x01') {
    uVar1 = uVar1 | 2;   /* MCI_DATA_CTL bit 1: DIR=1 (host-to-card write = 0, card-to-host read = 1) */
  }
  if (*(char *)((int)mode + 3) != '\0') {
    uVar1 = uVar1 | 4;   /* MCI_DATA_CTL bit 2: unused / auto-CMD */
  }
  if (*(char *)((int)mode + 5) != '\0') {
    uVar1 = uVar1 | 1;   /* MCI_DATA_CTL bit 0: ENABLE */
  }
  /* MCI_DATA_CTL = MCI core base + 0x2C */
  *(uint *)(DAT_0804e2c8[slot] + 0x2c) = uVar1;
  sdcc_enable_clock(slot);
  return;
}

/* orig: 0x0800bd20 sdcc_cleanup — build and write MCI_CMD (MCI core+0x0C) from descriptor.
 *
 * Assembles the MCI_CMD 32-bit register from a packed command-config struct,
 * also copies the argument to MCI_ARGUMENT (MCI core+0x08), then calls
 * sdcc_enable_clock() to let the controller latch the values.
 *
 * cmd_config[] layout (array of short, byte-level access for some fields):
 *   cmd_config[0]   dpe         → MCI_CMD bit 12 (PROG_ENA / data-path-enable)
 *   cmd_config[1]   ccs_enable  → MCI_CMD bit 11 (interrupt-mode / CCS)
 *   cmd_config[2]   data_present→ MCI_CMD bit 10 (data-present/expected)
 *   cmd_config[4]   idx_check   → MCI_CMD bit  7 (enable command index check)
 *   cmd_config[5]   crc_check   → MCI_CMD bit  6 (enable CRC check)
 *   cmd_config[6]   resp_type   → MCI_CMD bits 0-1 (00=no rsp, 01=R1, 10=R2, 11=R3)
 *   cmd_config[8]   cmd_timeout  (passed as 32-bit word to MCI_ARGUMENT via +8 byte offset)
 *
 * Registers written:
 *   MCI_ARGUMENT  = MCI core base + 0x08
 *   MCI_CMD       = MCI core base + 0x0C
 */
void sdcc_cleanup(int slot, short *cmd_config)
{
  uint uVar1;

  if (cmd_config != (short *)0x0) {
    uVar1 = (uint)(ushort)cmd_config[6];        /* resp_type → bits 0-1 */
    if (cmd_config[2] == 1) {
      uVar1 = uVar1 | 0x400;  /* bit 10: data present */
    }
    if (cmd_config[5] == 1) {
      uVar1 = uVar1 | 0x40;   /* bit 6: CRC_CHECK_EN */
    }
    if (cmd_config[4] == 1) {
      uVar1 = uVar1 | 0x80;   /* bit 7: CMD_IDX_CHECK_EN */
    }
    if (cmd_config[1] == 1) {
      uVar1 = uVar1 | 0x800;  /* bit 11: CCS_ENABLE (interrupt mode) */
    }
    if (*cmd_config == 1) {
      uVar1 = uVar1 | 0x1000; /* bit 12: PROG_ENA (data-path enable) */
    }
    /* MCI_ARGUMENT (MCI core+0x08) ← cmd_config[8] (32-bit word at byte offset 16) */
    *(uint *)(DAT_0804e2c8[slot] + 8) = *(uint *)(cmd_config + 8);
    /* MCI_CMD (MCI core+0x0C) */
    *(uint *)(DAT_0804e2c8[slot] + 0xc) = uVar1;
    sdcc_enable_clock(slot);
    return;
  }
  return;
}

/* orig: 0x0800bd78 sdcc_set_all_irq — write MCI_CLEAR (MCI core+0x38) to clear all status bits.
 *
 * Writes the constant 0x018007FF which covers all clearable MCI_STATUS bits:
 *   bits 0-8   command/data error and completion flags
 *   bits 10-19 FIFO / data-available flags (0x7FF mask)
 *   bit 23     PROG_DONE (0x800000)
 *   bit 24     ATA_CMD_CMPL
 *
 * MCI_CLEAR = MCI core base + 0x38
 */
void sdcc_set_all_irq(int slot)
{
  *(uint *)(DAT_0804e2c8[slot] + 0x38) = 0x18007ff;
  return;
}

/* orig: 0x0800bd8c sdcc_read_status — read MCI_STATUS (MCI core+0x34).
 *
 * Returns the 32-bit MCI_STATUS register.  Callers mask specific bits:
 *   bit 7   CMD_SENT (command sent without response)
 *   bit 6   CMD_RESP_END (command response received)
 *   bit 2   CMD_TIMEOUT
 *   bit 0   CMD_CRC_FAIL
 *
 * MCI_STATUS = MCI core base + 0x34
 */
uint sdcc_read_status(int slot)
{
  return *(uint *)(DAT_0804e2c8[slot] + 0x34);
}

/* orig: 0x0800bda0 sdcc_enable_clock — poll MCI_STATUS2 bit 0 until clear (up to 1000 iterations).
 *
 * MCI_STATUS2 bit 0 is the "internal clock not stable" / "bus-busy" indicator
 * for the legacy MCI interface.  The loop waits up to 1000 iterations (no
 * sleep between them) for the bit to deassert before returning.
 *
 * MCI_STATUS2 = MCI core base + 0x6C
 */
void sdcc_enable_clock(int slot)
{
  int iVar1;
  bool bVar2;

  iVar1 = 1000;
  do {
    bVar2 = iVar1 == 0;
    iVar1 = iVar1 + -1;
    if (bVar2) {
      return;
    }
    /* MCI_STATUS2 bit 0: 1 = clock not yet stable / bus busy */
  } while ((*(uint *)(DAT_0804e2c8[slot] + 0x6c) & 1) != 0);
  return;
}

/* orig: 0x0800be44 sdcc_read_present — read NRML_INT_STS_REG (HC+0x30).
 *
 * Returns the 32-bit SDHCI normal-interrupt-status register.  Callers mask
 * bits matching the SDCC interrupt status layout (writable-clear on write).
 * Used by sdcc_clear_status() to confirm bits have been cleared.
 *
 * NRML_INT_STS_REG = SDHCI HC base + 0x30
 */
uint sdcc_read_present(int slot)
{
  return *(uint *)(DAT_0804e2d8[slot] + 0x30);
}

/* orig: 0x0800be68 sdcc_read_present_state — read PRESENT_STATE_REG (HC+0x24).
 *
 * Returns the 32-bit SDHCI present-state register (read-only).  Common bits:
 *   bit 0   CMD_INHIBIT_CMD   bit 1  CMD_INHIBIT_DAT
 *   bit 2   DAT_LINE_ACTIVE   bit 10 BUFFER_WRITE_ENABLE
 *   bit 11  BUFFER_READ_ENABLE
 *
 * PRESENT_STATE_REG = SDHCI HC base + 0x24
 */
uint sdcc_read_present_state(int slot)
{
  return *(uint *)(DAT_0804e2d8[slot] + 0x24);
}

/* orig: 0x0800be78 sdcc_read_response — read 1 or 4 response words from RESP_REG (HC+0x10..0x1C).
 *
 * For R1/R1B (is_r2 == 0): copies RESP_REG[0] (HC+0x10) directly to resp[0].
 *
 * For R2 (is_r2 != 0): the SDHCI controller stores the 128-bit R2 response
 * shifted left by 8 bits relative to the MMC spec layout (CRC stripped).
 * This function reconstructs the natural MMC byte order by merging adjacent
 * words with an 8-bit rotate:
 *   resp[0] = (HC+0x1C << 8) | (HC+0x18 >> 24)   ← most significant word
 *   resp[1] = (HC+0x18 << 8) | (HC+0x14 >> 24)
 *   resp[2] = (HC+0x14 << 8) | (HC+0x10 >> 24)
 *   resp[3] = (HC+0x10 << 8)                      ← least significant word
 *
 * RESP_REG = SDHCI HC base + 0x10 (128-bit, four consecutive 32-bit words)
 */
void sdcc_read_response(int slot, uint *resp, int is_r2)
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;

  iVar1 = DAT_0804e2d8[slot];
  uVar3 = *(uint *)(iVar1 + 0x10);  /* RESP_REG word 0 (HC+0x10) */
  *resp = uVar3;
  if (is_r2 != 0) {
    uVar2 = *(uint *)(iVar1 + 0x14); /* RESP_REG word 1 (HC+0x14) */
    resp[1] = uVar2;
    uVar4 = *(uint *)(iVar1 + 0x18); /* RESP_REG word 2 (HC+0x18) */
    resp[2] = uVar4;
    /* Reassemble with 8-bit left-shift to recover MMC natural byte order */
    *resp    = *(uint *)(iVar1 + 0x1c) << 8 | uVar4 >> 0x18; /* HC+0x1C (MSW) */
    resp[1]  = uVar4 << 8 | uVar2 >> 0x18;
    resp[2]  = uVar2 << 8 | uVar3 >> 0x18;
    resp[3]  = uVar3 << 8;
  }
  return;
}

/* orig: 0x0800bfac sdcc_clear_status — clear bits in NRML_INT_STS_REG (HC+0x30) and poll until clear.
 *
 * Writes (mask & 0x07FF003F) to NRML_INT_STS_REG to clear the requested
 * status bits (SDHCI: write-1-to-clear).  Repeats up to 100000 iterations
 * (with 1 µs delays) until the masked bits read back as zero.
 *
 * The constant 0x07FF003F selects:
 *   bits 0-5    command/response completion bits
 *   bits 16-26  error status bits
 *
 * NRML_INT_STS_REG = SDHCI HC base + 0x30
 */
void sdcc_clear_status(int slot, uint mask)
{
  uint uVar1;
  int iVar2;
  bool bVar3;

  iVar2 = 100000;
  do {
    /* Write 1 to clear the requested bits in NRML_INT_STS_REG */
    *(uint *)(DAT_0804e2d8[slot] + 0x30) = mask & 0x7ff003f;
    uVar1 = sdcc_read_present(slot);
    if ((mask & 0x7ff003f & uVar1) == 0) {
      return;
    }
    thunk_FUN_080199b4(1);  /* delay_us(1) */
    bVar3 = iVar2 != 0;
    iVar2 = iVar2 + -1;
  } while (bVar3);
  return;
}

/* orig: 0x0800c008 sdcc_set_block_count — write BLK_CNT_REG (HC+0x06).
 *
 * Sets the 16-bit block count for the next multi-block transfer.
 *
 * BLK_CNT_REG = SDHCI HC base + 0x06
 */
void sdcc_set_block_count(int slot, uint16_t count)
{
  *(uint16_t *)(DAT_0804e2d8[slot] + 6) = count;
  return;
}

/* orig: 0x0800c018 sdcc_set_block_size — write BLKSZ_REG (HC+0x04).
 *
 * Sets the 16-bit block size for the next transfer.  Typically 0x200 (512
 * bytes) for eMMC.  Bits 12-14 of this register select SDMA buffer boundary.
 *
 * BLKSZ_REG = SDHCI HC base + 0x04
 */
void sdcc_set_block_size(int slot, uint16_t size)
{
  *(uint16_t *)(DAT_0804e2d8[slot] + 4) = size;
  return;
}

/* orig: 0x0800c0c4 sdcc_set_cmd_arg — write ARGUMENT_REG (HC+0x08).
 *
 * Writes the 32-bit command argument before firing a command via
 * sdcc_fire_cmd().
 *
 * ARGUMENT_REG = SDHCI HC base + 0x08
 */
void sdcc_set_cmd_arg(int slot, uint arg)
{
  *(uint *)(DAT_0804e2d8[slot] + 8) = arg;
  return;
}

/* orig: 0x0800c0d4 sdcc_fire_cmd — write CMD_REG (HC+0x0E) to issue a command.
 *
 * Assembles and writes the 16-bit SDHCI CMD_REG from a 6-byte descriptor:
 *   cmd_desc[0]  cmd_index    → CMD_REG bits 8-13  (command index)
 *   cmd_desc[1]  cmd_type     → CMD_REG bits 6-7   (0=normal, 1=suspend, 2=resume, 3=abort)
 *   cmd_desc[2]  data_present → CMD_REG bit 5      (1=data transfer expected)
 *   cmd_desc[3]  idx_check    → CMD_REG bit 4      (1=enable command index check)
 *   cmd_desc[4]  crc_check    → CMD_REG bit 3      (1=enable CRC check)
 *   cmd_desc[5]  resp_type    → CMD_REG bits 0-1   (0=no resp, 1=136-bit, 2=48-bit, 3=48-bit+busy)
 *
 * Writing this register starts command execution in the SDHCI controller.
 *
 * CMD_REG = SDHCI HC base + 0x0E
 */
void sdcc_fire_cmd(int slot, byte *cmd_desc)
{
  *(uint16_t *)(DAT_0804e2d8[slot] + 0xe) =
       (ushort)*cmd_desc << 8     |  /* cmd_index    → bits 8-13 (shifted to 15:8) */
       (ushort)cmd_desc[1] << 6   |  /* cmd_type     → bits 7-6 */
       (ushort)cmd_desc[2] << 5   |  /* data_present → bit 5 */
       (ushort)cmd_desc[3] << 4   |  /* idx_check    → bit 4 */
       (ushort)cmd_desc[4] << 3   |  /* crc_check    → bit 3 */
       (ushort)cmd_desc[5];          /* resp_type    → bits 1-0 */
  return;
}

/* orig: 0x0800c11c sdcc_set_irq_mask — write TIMEOUT_REG (HC+0x2E).
 *
 * Despite the name "irq_mask", the target offset +0x2E is TIMEOUT_REG
 * (the 8-bit data timeout counter value), NOT an interrupt mask.  The
 * name is a Ghidra decompiler artifact; this sets the timeout exponent
 * (value = TMCLK * 2^(N+13), N=0xE → ~1 second at typical TMCLK).
 *
 * TIMEOUT_REG = SDHCI HC base + 0x2E
 */
void sdcc_set_irq_mask(int slot, uint8_t mask)
{
  *(uint8_t *)(DAT_0804e2d8[slot] + 0x2e) = mask;
  return;
}

/* orig: 0x0800c12c sdcc_set_transfer_ctrl — write TRANS_MODE_REG (HC+0x0C) from descriptor.
 *
 * Assembles and writes the 16-bit SDHCI TRANS_MODE_REG from a 5-byte array:
 *   ctrl[0]  dma_en      → TRANS_MODE_REG bit 0  (DMA_ENABLE)
 *            NOTE: bit 0 of TRANS_MODE_REG is BLK_CNT_EN per SDHCI spec;
 *            the original maps dma_en → bit 0 which may be controller-specific.
 *   ctrl[1]  blk_cnt_en  → TRANS_MODE_REG bit 1  (BLK_CNT_EN? or DMA_EN?)
 *   ctrl[2]  auto_cmd    → TRANS_MODE_REG bits 2-3  (AUTO_CMD12/23 enable)
 *   ctrl[3]  direction   → TRANS_MODE_REG bit 4  (DATA_XFER_DIR: 1=read)
 *   ctrl[4]  multi_blk   → TRANS_MODE_REG bit 5  (MULTI_BLK_SEL)
 *
 * Note: bit ordering here differs from sdcc_set_transfer_mode() — that function
 * targets MCI_DATA_CTL (MCI+0x2C) while this one targets SDHCI TRANS_MODE_REG (HC+0x0C).
 *
 * TRANS_MODE_REG = SDHCI HC base + 0x0C
 */
void sdcc_set_transfer_ctrl(int slot, byte *ctrl)
{
  *(uint16_t *)(DAT_0804e2d8[slot] + 0xc) =
       (ushort)*ctrl    << 5 |  /* dma_en    (or multi_blk?)  → bit 5? see note */
       (ushort)ctrl[1]  << 4 |  /* blk_cnt_en → bit 4 */
       (ushort)ctrl[2]  << 2 |  /* auto_cmd   → bits 3-2 */
       (ushort)ctrl[3]  << 1 |  /* direction  → bit 1 */
       (ushort)ctrl[4];         /* multi_blk  → bit 0 */
  return;
}

/* orig: 0x0800c154 sdcc_reset_data_line — write RESET_REG (HC+0x2F) and poll until clear.
 *
 * Issues a software reset by writing `bits` to RESET_REG, then spins up to
 * 100000 iterations (with 1 µs delays) until those same bits read back as 0,
 * indicating the reset has completed.
 *
 * Common values for `bits`:
 *   0x01  RESET_ALL   — full controller reset
 *   0x02  RESET_CMD   — reset command circuit only
 *   0x04  RESET_DATA  — reset data circuit only
 *
 * RESET_REG = SDHCI HC base + 0x2F
 */
void sdcc_reset_data_line(int slot, byte bits)
{
  int iVar1;
  int iVar2;
  bool bVar3;

  iVar1 = 100000;
  iVar2 = DAT_0804e2d8[slot];
  *(uint8_t *)(iVar2 + 0x2f) = bits;   /* RESET_REG: initiate reset */
  while ((bVar3 = iVar1 != 0, iVar1 = iVar1 + -1, bVar3 &&
         ((*(uint8_t *)(iVar2 + 0x2f) & bits) != 0))) {
    thunk_FUN_080199b4(1);  /* delay_us(1): wait for reset to complete */
  }
  return;
}

/* orig: 0x0800c0a8 sdcc_set_clock_divider — write CLK_CTRL_REG (HC+0x2C).
 *
 * Programs the SDHCI clock divider and enables the internal clock.
 * The SDHCI spec (ver 2.0) 10-bit divided clock mode encoding:
 *   bits 15-8  SDCLK_FREQ_SEL[7:0]   — lower 8 bits of the 10-bit divider
 *   bits 7-6   SDCLK_FREQ_SEL[9:8]   — upper 2 bits (from (divider & 0x300) >> 2)
 *   bit 0      INTERNAL_CLK_EN       — must be set to start clock
 *
 * The formula is: SD clock = base_clock / (2 * divider), or divider=0 means
 * bypass (base_clock).
 *
 * CLK_CTRL_REG = SDHCI HC base + 0x2C
 */
void sdcc_set_clock_divider(int slot, uint divider)
{
  *(uint16_t *)(DAT_0804e2d8[slot] + 0x2c) =
       (ushort)(divider << 8)           |  /* SDCLK_FREQ_SEL[7:0] → bits 15:8 */
       (ushort)((divider & 0x300) >> 2) |  /* SDCLK_FREQ_SEL[9:8] → bits 7:6 */
       1;                                   /* INTERNAL_CLK_EN → bit 0 */
  return;
}

/* orig: 0x0800bfe8 sdcc_set_adma_addr_lo — write ADM_ADDR_REG low word (HC+0x58).
 *
 * Sets the lower 32 bits of the ADMA system address (descriptor list base).
 * For 32-bit ADMA, this is the complete address.
 *
 * ADM_ADDR_REG = SDHCI HC base + 0x58
 */
void sdcc_set_adma_addr_lo(int slot, uint addr)
{
  *(uint *)(DAT_0804e2d8[slot] + 0x58) = addr;
  return;
}

/* orig: 0x0800bff8 sdcc_set_adma_addr_hi — write ADMA system address high word (HC+0x5C).
 *
 * Sets the upper 32 bits of the 64-bit ADMA system address.  Zero for all
 * 32-bit physical memory systems (MSM8909 has 32-bit physical addressing).
 *
 * ADMA addr hi = SDHCI HC base + 0x5C
 */
void sdcc_set_adma_addr_hi(int slot, uint addr)
{
  *(uint *)(DAT_0804e2d8[slot] + 0x5c) = addr;
  return;
}

/* orig: 0x0800bdbc sdcc_set_8bit_mode — set or clear the 8-bit-bus bit in HOST_CTRL1_REG (HC+0x28).
 *
 * HOST_CTRL1_REG bit 4 (0x10): DATA_WIDTH_8BIT
 *   0 = 1-bit or 4-bit bus width (controlled by bit 1)
 *   1 = 8-bit bus width (eMMC only)
 *
 * The read-modify-write preserves bits 7-6 and 3-0 (mask 0xE7).
 *
 * HOST_CTRL1_REG = SDHCI HC base + 0x28
 */
void sdcc_set_8bit_mode(int slot, int enable)
{
  uint8_t bVar1;

  bVar1 = 0;
  if (enable != 0) {
    bVar1 = 0x10;  /* HOST_CTRL1_REG bit 4: DATA_WIDTH_8BIT */
  }
  *(uint8_t *)(DAT_0804e2d8[slot] + 0x28) =
       *(uint8_t *)(DAT_0804e2d8[slot] + 0x28) & 0xe7 | bVar1;
  return;
}

/* orig: 0x0800bdd8 sdcc_trigger_vendor_reset — write DLL_CONFIG_REG (HC+0x100) to reset DLL.
 *
 * Issues a two-step DLL reset sequence via the Qualcomm vendor register:
 *   Step 1: set bit 29 (DLL_RST) → assert DLL reset
 *   Step 2: set bit 29 + bit 30 (DLL_PDN, DLL power-down) → full power-down
 *
 * The read-modify-write approach preserves other bits (e.g. DLL_EN, tuning
 * parameters) while toggling the reset/power-down bits.
 *
 * DLL_CONFIG_REG = SDHCI HC base + 0x100
 */
void sdcc_trigger_vendor_reset(int slot)
{
  uint *puVar1;
  uint uVar2;

  puVar1 = (uint *)(DAT_0804e2d8[slot] + 0x100);  /* DLL_CONFIG_REG */
  uVar2 = *puVar1;
  *puVar1 = uVar2 | 0x20000000;  /* set bit 29: DLL_RST */
  *puVar1 = uVar2 | 0x60000000;  /* set bit 29 + bit 30: DLL_RST | DLL_PDN */
  return;
}

/* orig: 0x0800bdf8 sdcc_set_clock_mode — set UHS mode bits in HOST_CTRL2_REG (HC+0x3E).
 *
 * Reads the current HOST_CTRL2_REG, clears bits 2-0 (UHS_MODE_SEL), then
 * writes back with bits 2-0 = 0x4 (UHS_MODE_SEL = SDR104 or HS200 depending
 * on context).  The add-instead-of-OR is a Ghidra decompiler artifact: since
 * bits 0-2 were cleared to 0, adding 4 is equivalent to ORing 4.
 *
 * HOST_CTRL2_REG UHS_MODE_SEL encoding (bits 2-0):
 *   0x0  SDR12     0x1  SDR25     0x2  SDR50
 *   0x3  SDR104    0x4  DDR50     0x5-0x7  reserved / vendor HS200
 *
 * HOST_CTRL2_REG = SDHCI HC base + 0x3E
 */
void sdcc_set_clock_mode(int slot)
{
  *(uint16_t *)(DAT_0804e2d8[slot] + 0x3e) =
       (*(uint16_t *)(DAT_0804e2d8[slot] + 0x3e) & 0xfff8) + 4;  /* UHS_MODE_SEL = 4 (DDR50/HS200) */
  return;
}

/* orig: 0x0800be10 sdcc_set_hs_mode — set or clear HS_EN bit in CLK_CTRL_REG low byte (HC+0x2C).
 *
 * CLK_CTRL_REG byte 0 bit 2 (0x04): HS_EN
 *   0 = normal speed mode (≤25 MHz)
 *   1 = high-speed mode (≤52 MHz / 50 MHz)
 *
 * The read-modify-write masks out bit 2 (& 0xFB) and ORs in (enable << 2).
 * Note: `enable` is passed as `char`; caller should pass 0 or 1 only.
 *
 * CLK_CTRL_REG byte 0 = SDHCI HC base + 0x2C
 */
void sdcc_set_hs_mode(int slot, char enable)
{
  *(uint8_t *)(DAT_0804e2d8[slot] + 0x2c) =
       *(uint8_t *)(DAT_0804e2d8[slot] + 0x2c) & 0xfb | (uint8_t)(enable << 2);
  return;
}

/* orig: 0x0800be2c sdcc_read_caps — read CAPS_REG1 and CAPS_REG2 (HC+0x40, HC+0x44).
 *
 * Copies the two 32-bit hardware capability registers into caller's array:
 *   caps[0] = CAPS_REG1 (HC+0x40): supported voltages, speed, DMA, etc.
 *   caps[1] = CAPS_REG2 (HC+0x44): max current, re-tuning support, etc.
 *
 * CAPS_REG1 = SDHCI HC base + 0x40
 * CAPS_REG2 = SDHCI HC base + 0x44
 */
void sdcc_read_caps(int slot, uint *caps)
{
  caps[0] = *(uint *)(DAT_0804e2d8[slot] + 0x40);  /* CAPS_REG1 */
  caps[1] = *(uint *)(DAT_0804e2d8[slot] + 0x44);  /* CAPS_REG2 */
  return;
}

/* orig: 0x0800be54 sdcc_read_power_mode — read low nibble of PWR_CTRL_REG (HC+0x29).
 *
 * Returns bits 3-0 of PWR_CTRL_REG:
 *   bit 0      SD_BUS_POWER (1 = bus powered)
 *   bits 3-1   SD_BUS_VLT   (bus voltage: 1=1.8V, 5=2.5V, 7=3.3V)
 *
 * PWR_CTRL_REG = SDHCI HC base + 0x29
 */
uint8_t sdcc_read_power_mode(int slot)
{
  return *(uint8_t *)(DAT_0804e2d8[slot] + 0x29) & 0xf;
}

/* orig: 0x0800beb8 sdcc_wait_pll_lock — wait for PLL lock via MCI core +0xDC, then configure.
 *
 * This function manages the Qualcomm-specific MCI PLL lock-and-configure
 * sequence using three undocumented MCI core registers:
 *
 *   MCI+0xDC  PLL_STATUS  — PLL lock status (non-zero = locked or active)
 *   MCI+0xE4  PLL_DIVIDER — PLL feedback divider latch
 *   MCI+0xE8  PLL_MODE    — PLL mode select (1=integer, 4=fractional?)
 *
 * Phase 1: Poll MCI+0xDC up to 100000 × with 1 µs delay until non-zero
 *          (PLL has locked or asserted).
 * Phase 2: Latch the PLL status into MCI+0xE4.
 *          If bits 1-0 of the status are 0, write 4 to MCI+0xE8 (fractional
 *          or bypass mode); otherwise write 1 (integer-N mode).
 * Phase 3: Poll MCI+0xDC again up to 100000 × until it reads 0
 *          (PLL config has been consumed / acknowledged).
 *
 * Note: the second loop polls for *zero* (opposite of phase 1), suggesting
 * the register is a handshake flag: the hardware sets it when data is ready,
 * the driver latches and clears it by writing MCI+0xE4/0xE8.
 *
 * MCI+0xDC = MCI core base + 0xDC
 * MCI+0xE4 = MCI core base + 0xE4
 * MCI+0xE8 = MCI core base + 0xE8
 */
void sdcc_wait_pll_lock(int slot)
{
  uint uVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;

  /* Phase 1: wait for PLL status to become non-zero */
  iVar3 = 100000;
  do {
    uVar2 = *(uint *)(DAT_0804e2c8[slot] + 0xdc);  /* MCI+0xDC: PLL_STATUS */
    if (uVar2 != 0) break;
    thunk_FUN_080199b4(1);  /* delay_us(1) */
    bVar4 = iVar3 != 0;
    iVar3 = iVar3 + -1;
  } while (bVar4);

  /* Phase 2: latch status and select PLL mode */
  *(uint *)(DAT_0804e2c8[slot] + 0xe4) = uVar2;  /* MCI+0xE4: PLL_DIVIDER latch */
  if ((uVar2 & 3) == 0) {
    uVar1 = 4;   /* bits 1:0 == 0: select fractional/bypass mode */
  }
  else {
    uVar1 = 1;   /* bits 1:0 != 0: select integer-N mode */
  }
  *(uint *)(DAT_0804e2c8[slot] + 0xe8) = uVar1;  /* MCI+0xE8: PLL_MODE */

  /* Phase 3: wait for PLL status to return to zero (handshake acknowledge) */
  iVar3 = 100000;
  do {
    if (*(uint *)(DAT_0804e2c8[slot] + 0xdc) == 0) {
      return;
    }
    thunk_FUN_080199b4(1);  /* delay_us(1) */
    bVar4 = iVar3 != 0;
    iVar3 = iVar3 + -1;
  } while (bVar4);
  return;
}

/* orig: 0x0800bf18 sdcc_set_int_enable — set or clear bits in NRML_INT_SIG_EN_REG (HC+0x38).
 *
 * Read-modify-write on the SDHCI normal-interrupt signal-enable register.
 * If enable==1, the masked bits are set (signals routed to IRQ pin).
 * If enable!=1, the masked bits are cleared.
 *
 * NRML_INT_SIG_EN_REG = SDHCI HC base + 0x38
 */
void sdcc_set_int_enable(int slot, uint mask, int enable)
{
  uint uVar1;

  uVar1 = *(uint *)(DAT_0804e2d8[slot] + 0x38) & ~mask;  /* NRML_INT_SIG_EN_REG */
  if (enable == 1) {
    uVar1 = uVar1 | mask;
  }
  *(uint *)(DAT_0804e2d8[slot] + 0x38) = uVar1;
  return;
}

/* orig: 0x0800bf34 sdcc_set_int_signal — set or clear bits in NRML_INT_STS_EN_REG (HC+0x34) with polling.
 *
 * Controls whether interrupt status bits are captured (status-enable register).
 * When enabling: retries up to 100000 × with 1 µs delay, reading back to
 * confirm the bits took effect (some bits may be hardware-forced to 0).
 * When disabling: single write, no polling.
 *
 * NRML_INT_STS_EN_REG = SDHCI HC base + 0x34
 */
void sdcc_set_int_signal(int slot, uint mask, int enable)
{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;

  iVar3 = 100000;
  puVar1 = (uint *)(DAT_0804e2d8[slot] + 0x34);  /* NRML_INT_STS_EN_REG */
  uVar2 = *puVar1;
  if (enable == 0) {
    *puVar1 = uVar2 & ~mask;  /* clear bits: single write, no readback check */
  }
  else {
    do {
      *puVar1 = uVar2 & ~mask | mask;  /* set bits */
      uVar2 = *puVar1;
      if ((mask & ~uVar2) == 0) {  /* verify all requested bits are now set */
        return;
      }
      thunk_FUN_080199b4(1);  /* delay_us(1) */
      bVar4 = iVar3 != 0;
      iVar3 = iVar3 + -1;
    } while (bVar4);
  }
  return;
}

/* orig: 0x0800bf74 sdcc_read_clock_stable — read INTERNAL_CLK_STABLE bit from CLK_CTRL_REG (HC+0x2C).
 *
 * Extracts CLK_CTRL_REG bit 1 (INTERNAL_CLK_STABLE):
 *   0 = clock not yet stable (still settling after enabling)
 *   1 = clock is stable and safe to use
 *
 * The bit extraction uses shifts: (byte << 30) >> 31 isolates bit 1 → returns 0 or 1.
 *
 * CLK_CTRL_REG byte 0 = SDHCI HC base + 0x2C
 */
uint sdcc_read_clock_stable(int slot)
{
  /* Isolate CLK_CTRL_REG bit 1 (INTERNAL_CLK_STABLE): shift bit 1 to bit 31, then >> 31 → 0 or 1 */
  return ((uint)*(uint8_t *)(DAT_0804e2d8[slot] + 0x2c) << 0x1e) >> 0x1f;
}

/* orig: 0x0800bf88 sdcc_set_led — set or clear HC_SELECT/LED bit in VENDOR_SPECIFIC_FUNC (HC+0x10C).
 *
 * VENDOR_SPECIFIC_FUNC bit 1 (0x2): HC_SELECT
 *   In this context used as an activity LED signal:
 *   1 = LED on / host controller selected
 *   0 = LED off
 *
 * VENDOR_SPECIFIC_FUNC = SDHCI HC base + 0x10C
 */
void sdcc_set_led(int slot, int enable)
{
  uint uVar1;

  uVar1 = *(uint *)(DAT_0804e2d8[slot] + 0x10c);  /* VENDOR_SPECIFIC_FUNC */
  if (enable == 1) {
    uVar1 = uVar1 | 2;           /* bit 1: HC_SELECT/LED on */
  }
  else {
    uVar1 = uVar1 & 0xfffffffd;  /* bit 1: HC_SELECT/LED off */
  }
  *(uint *)(DAT_0804e2d8[slot] + 0x10c) = uVar1;
  return;
}

/* orig: 0x0800c028 sdcc_set_dma_mode — configure DMA_SEL bits in HOST_CTRL1_REG (HC+0x28).
 *
 * HOST_CTRL1_REG bits 4-3 (0x18) = DMA_SEL:
 *   mode 0: SDMA          — DMA_SEL = 0b00, clears both bits (mask 0xDD keeps bits 7,6,4,3,2,1,0 minus 1 and 5)
 *   mode 1: 32-bit ADMA2  — DMA_SEL = 0b01 (bit 3 set, bit 4 clear)
 *   mode 2: 64-bit ADMA2  — DMA_SEL = 0b10 (bit 4 set via OR 0x20? — but 0x20 = bit 5 = DATA_WIDTH_4BIT)
 *
 * NOTE: the mask 0xDD = 1101_1101b preserves bits 7,6,4,3,1,0 and clears bits 5,1.
 * This looks like a decompiler artifact — the correct mask for clearing DMA_SEL (bits 4-3)
 * should be 0xE7.  As-is: mode 0 clears bits 1 and 5 in addition to bits 4-3, which
 * may inadvertently clear DATA_WIDTH_4BIT or other bits.  mode 1 adds 2 (sets bit 1
 * instead of bit 3), which is another likely Ghidra artifact.
 *
 * HOST_CTRL1_REG = SDHCI HC base + 0x28
 */
void sdcc_set_dma_mode(int slot, int mode)
{
  uint8_t bVar1;

  bVar1 = *(uint8_t *)(DAT_0804e2d8[slot] + 0x28);  /* HOST_CTRL1_REG */
  if (mode == 0) {
    bVar1 = bVar1 & 0xdd;          /* SDMA: clear DMA_SEL bits (see NOTE above) */
  }
  else if (mode == 1) {
    bVar1 = (bVar1 & 0xdd) + 2;   /* 32-bit ADMA2: set bit 1 (see NOTE) */
  }
  else {
    if (mode != 2) {
      return;
    }
    bVar1 = bVar1 | 0x20;          /* 64-bit ADMA2: set bit 5 (see NOTE) */
  }
  *(uint8_t *)(DAT_0804e2d8[slot] + 0x28) = bVar1;
  return;
}

/* orig: 0x0800c058 sdcc_setup_caps — write shadow capability registers (HC+0x11C, HC+0x120).
 *
 * Reads the hardware CAPS_REG1/2 (HC+0x40, HC+0x44), optionally ORs in
 * additional capability bits based on sdcc_get_slot_status(0), then writes
 * the result to the writable shadow registers VENDOR_SPECIFIC_CAPABILITIES0
 * (HC+0x11C) and its companion (HC+0x120).
 *
 * Slot status bit 0 (bit 1-0 = UHS capable?):
 *   If (status & 3) != 0: OR in CAPS_REG1 |= 0x280000 (DDR50 + SDR104 support),
 *                         CAPS_REG2 |= 0x7 (max-current fields)
 *   If (status & 1) == 0 and bit 1 set (status & 2):
 *                         CAPS_REG1 = (CAPS_REG1 & 0x3BFFFFFF) | 0x3000000
 *   If (status & 1) != 0: CAPS_REG1 = (CAPS_REG1 & 0x38FFFFFF) | 0x44040000
 *
 * VENDOR_SPECIFIC_CAPABILITIES0 = SDHCI HC base + 0x11C
 * (shadow of CAPS_REG2)          = SDHCI HC base + 0x120
 */
void sdcc_setup_caps(int slot)
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;

  uVar1 = sdcc_get_slot_status(0);
  iVar4 = DAT_0804e2d8[slot];
  uVar2 = *(uint *)(iVar4 + 0x40);  /* CAPS_REG1 (HC+0x40) */
  uVar3 = *(uint *)(iVar4 + 0x44);  /* CAPS_REG2 (HC+0x44) */
  if ((uVar1 & 3) != 0) {
    uVar2 = uVar2 | 0x280000;  /* add DDR50 (bit 19) + SDR104 (bit 23) support */
    uVar3 = uVar3 | 7;         /* add max-current capability bits 2-0 */
  }
  if ((uVar1 & 1) == 0) {
    if ((int)(uVar1 << 0x1e) < 0) {
      /* bit 1 set, bit 0 clear: set voltage bits for 1.8V-only operation */
      uVar2 = uVar2 & 0x3bffffff | 0x3000000;
    }
  }
  else {
    /* bit 0 set: set high-speed/voltage capability fields */
    uVar2 = uVar2 & 0x38ffffff | 0x44040000;
  }
  *(uint *)(iVar4 + 0x11c) = uVar2;              /* VENDOR_SPECIFIC_CAPABILITIES0 */
  *(uint *)(DAT_0804e2d8[slot] + 0x120) = uVar3; /* shadow of CAPS_REG2 */
  return;
}

/* orig: 0x0800c104 sdcc_set_bus_power — set or clear SD_BUS_POWER bit in PWR_CTRL_REG (HC+0x29).
 *
 * PWR_CTRL_REG bit 0 (SD_BUS_POWER):
 *   0 = bus power off (safe to change voltage)
 *   1 = bus power on
 *
 * The read-modify-write preserves bits 7-1 (voltage select etc.) while
 * toggling only bit 0.
 *
 * PWR_CTRL_REG = SDHCI HC base + 0x29
 */
void sdcc_set_bus_power(int slot, uint8_t enable)
{
  *(uint8_t *)(DAT_0804e2d8[slot] + 0x29) =
       *(uint8_t *)(DAT_0804e2d8[slot] + 0x29) & 0xfe | enable;
  return;
}

/* orig: 0x0800c180 sdcc_set_voltage — write SD_BUS_VLT bits in PWR_CTRL_REG (HC+0x29).
 *
 * PWR_CTRL_REG bits 3-1 (SD_BUS_VLT): bus voltage select
 *   Preserved via mask 0xF1 (keeps bits 7-4 and bit 0, clears bits 3-1).
 *   `voltage` should be a pre-shifted value for bits 3-1:
 *     0x02 = 1.8V (001b << 1)    0x0A = 2.5V (101b << 1)    0x0E = 3.3V (111b << 1)
 *
 * PWR_CTRL_REG = SDHCI HC base + 0x29
 */
void sdcc_set_voltage(int slot, uint8_t voltage)
{
  *(uint8_t *)(DAT_0804e2d8[slot] + 0x29) =
       *(uint8_t *)(DAT_0804e2d8[slot] + 0x29) & 0xf1 | voltage;
  return;
}

/* orig: 0x0800bc64 sdcc_set_bus_width_bit — set or clear bit 0 of MCI_HC_MODE (MCI+0x78).
 *
 * MCI_HC_MODE bit 0: bus-width override for the legacy MCI interface.
 *   0 = 1-bit bus width (legacy default)
 *   1 = 8-bit bus width (eMMC wide bus mode)
 *
 * This is distinct from sdcc_set_8bit_mode() which sets the SDHCI
 * HOST_CTRL1_REG bit — both registers must agree for correct operation.
 *
 * MCI_HC_MODE = MCI core base + 0x78
 */
void sdcc_set_bus_width_bit(int slot, int enable)
{
  uint uVar1;

  uVar1 = *(uint *)(DAT_0804e2c8[slot] + 0x78);  /* MCI_HC_MODE */
  if (enable == 1) {
    uVar1 = uVar1 | 1;           /* bit 0: 8-bit bus width */
  }
  else {
    uVar1 = uVar1 & 0xfffffffe;  /* bit 0: 1-bit bus width */
  }
  *(uint *)(DAT_0804e2c8[slot] + 0x78) = uVar1;
  return;
}

/* orig: 0x0800bc84 sdcc_init_bases — initialize MCI core and SDHCI HC base address tables.
 *
 * Idempotent: guarded by the DAT_0804e2c4 flag (set to 1 after first call).
 *
 * Sets four base address arrays for two slots:
 *   DAT_0804e2c8[0] = 0x07824000  MCI core base, slot 0 (eMMC)
 *   DAT_0804e2c8[1] = 0x07864000  MCI core base, slot 1 (SD)
 *   DAT_0804e2d0[0] = 0x07824000  DMA/FIFO base (same as MCI core for this controller)
 *   DAT_0804e2d0[1] = 0x07864000
 *   DAT_0804e2d8[0] = 0x07824900  SDHCI HC base, slot 0  (MCI core + 0x900)
 *   DAT_0804e2d8[1] = 0x07864900  SDHCI HC base, slot 1
 *   DAT_0804e2e0[0] = 0x07824900  SDHCI HC base (alt/duplicate), slot 0
 *   DAT_0804e2e0[1] = 0x07864900
 */
void sdcc_init_bases(void)
{
  if (DAT_0804e2c4 != '\x01') {
    DAT_0804e2c8[0] = 0x7824000;   /* slot 0 MCI core base */
    DAT_0804e2d0[0] = 0x7824000;   /* slot 0 DMA/FIFO base */
    DAT_0804e2c8[1] = 0x7864000;   /* slot 1 MCI core base */
    DAT_0804e2d0[1] = 0x7864000;   /* slot 1 DMA/FIFO base */
    DAT_0804e2d8[0] = 0x7824900;   /* slot 0 SDHCI HC base */
    DAT_0804e2e0[0] = 0x7824900;   /* slot 0 SDHCI HC base (alt) */
    DAT_0804e2d8[1] = 0x7864900;   /* slot 1 SDHCI HC base */
    DAT_0804e2e0[1] = 0x7864900;   /* slot 1 SDHCI HC base (alt) */
    DAT_0804e2c4 = '\x01';         /* mark as initialized */
  }
  return;
}

/* orig: 0x0800bccc sdcc_set_flow_control — set or clear flow-control bit in MCI_CLK (MCI+0x04).
 *
 * MCI_CLK bit 9 (FLOW_ENA): enables hardware flow control between the
 * MCI FIFO and the bus interface.  Should be enabled during data transfers
 * to prevent FIFO underrun/overrun.
 *
 * MCI_CLK = MCI core base + 0x04
 */
void sdcc_set_flow_control(int slot, int enable)
{
  uint uVar1;

  uVar1 = *(uint *)(DAT_0804e2c8[slot] + 4);  /* MCI_CLK */
  if (enable == 0) {
    uVar1 = uVar1 & 0xfffffdff;  /* clear bit 9: FLOW_ENA off */
  }
  else {
    uVar1 = uVar1 | 0x200;      /* set bit 9: FLOW_ENA on */
  }
  *(uint *)(DAT_0804e2c8[slot] + 4) = uVar1;
  sdcc_enable_clock(slot);
  return;
}

/* orig: 0x0800bcec sdcc_set_bus_speed — set bus speed mode bits in MCI_CLK (MCI+0x04).
 *
 * MCI_CLK bits 11-10 (BUS_SPEED): legacy Qualcomm bus speed select:
 *   speed 0: SDR12  → bits 11-10 = 0b00 (cleared, 0x000)
 *   speed 1: SDR25  → bits 11-10 = 0b10 (0x800)
 *   speed 2: SDR50  → bits 11-10 = 0b11 (0xC00)
 *
 * Read-modify-write: mask 0xFFFFF3FF clears bits 11-10, then OR the value.
 *
 * MCI_CLK = MCI core base + 0x04
 */
void sdcc_set_bus_speed(int slot, int speed)
{
  uint uVar1;

  uVar1 = 0;
  if (speed != 0) {
    if (speed == 1) {
      uVar1 = 0x800;   /* bits 11-10 = 0b10: SDR25 */
    }
    else {
      if (speed != 2) {
        return;
      }
      uVar1 = 0xc00;   /* bits 11-10 = 0b11: SDR50 */
    }
  }
  /* MCI_CLK: clear BUS_SPEED bits then write new value */
  *(uint *)(DAT_0804e2c8[slot] + 4) =
       *(uint *)(DAT_0804e2c8[slot] + 4) & 0xfffff3ff | uVar1;
  sdcc_enable_clock(slot);
  return;
}
