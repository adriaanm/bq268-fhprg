/* sdcc_helpers.c — eMMC data transfer helpers.
 *
 * These sit between sdcc_send_cmd (in emmc.c) and the MMIO register
 * wrappers (in sdcc_regs.c). They handle data transfer setup, DMA
 * configuration, FIFO writes, busy-waits, and post-write cleanup.
 *
 * Source: src/fhprg/fhprg_80327f8.c, src/fhprg/fhprg_8007b18.c
 */
#include "firehose.h"

/* Forward declarations for functions defined later in this file */
static undefined4 sdcc_wait_card_ready(int *dev);

/* ---- DMA bounce helpers (from fhprg_8007b18.c) ---- */

/* orig: 0x08006e1a — write uint32 as little-endian bytes */
static void write_le32(undefined4 val, undefined1 *buf)
{
  *buf = (char)val;
  buf[1] = (char)((uint)val >> 8);
  buf[2] = (char)((uint)val >> 0x10);
  buf[3] = (char)((uint)val >> 0x18);
  return;
}

/* orig: 0x08008ba4 — DMA read: burst-read 8 words from FIFO to buffer.
 * Polls status register for data-available bit between bursts.
 *   dst        = destination buffer (RAM)
 *   fifo       = FIFO data port base (8 consecutive MMIO words)
 *   status_reg = SDCC status register (volatile MMIO)
 *   mask       = data-available bitmask (0x8000 = RXDATA_AVAIL) */
static int dma_read_helper(int dst, int fifo, volatile uint *status_reg, uint mask)
{
  uint *src = (uint *)fifo;
  uint *out = (uint *)dst;

  while ((*status_reg & mask) != 0) {
    /* Read 8 words (32 bytes) from FIFO port */
    out[0] = src[0]; out[1] = src[1]; out[2] = src[2]; out[3] = src[3];
    out[4] = src[4]; out[5] = src[5]; out[6] = src[6]; out[7] = src[7];
    out += 8;
  }
  return (int)out;
}

/* DMA descriptor for dma_write_helper: 4 contiguous words.
 *   [0] = status register address (FIFO status, volatile MMIO)
 *   [1] = FIFO-ready bitmask (0x4000 = TXDATA_AVAIL)
 *   [2] = byte count remaining (decremented by 32 each burst)
 *   [3] = error bitmask (0x1a = error/overflow bits, causes early exit) */
typedef struct {
  uint status_reg_addr;
  uint ready_mask;
  int  remaining;
  uint error_mask;
} dma_write_desc_t;

/* orig: 0x08008bc4 — DMA write: burst-write 8 words from buffer to FIFO.
 * Polls FIFO status register between bursts for space and errors.
 *   fifo = FIFO data port base (single MMIO word, writes auto-advance)
 *   src  = source buffer (RAM)
 *   desc = 4-word descriptor (see dma_write_desc_t) */
static int dma_write_helper(int fifo, int src, dma_write_desc_t *desc)
{
  uint *dst = (uint *)fifo;
  uint *in = (uint *)src;
  int rem = desc->remaining;
  volatile uint *status_reg = (volatile uint *)desc->status_reg_addr;
  uint ready_mask = desc->ready_mask;
  uint error_mask = desc->error_mask;

  while (1) {
    /* Write 8 words (32 bytes) to FIFO */
    *dst = in[0]; *dst = in[1]; *dst = in[2]; *dst = in[3];
    *dst = in[4]; *dst = in[5]; *dst = in[6]; *dst = in[7];
    in += 8;
    rem -= 0x20;
    if (rem < 0x20) break;
    /* Poll: wait for FIFO space, break on error */
    do {
      if ((*status_reg & error_mask) != 0) goto done;
    } while ((*status_reg & ready_mask) == 0);
  }
done:
  desc->remaining = rem;
  return (int)in;
}

/* orig: 0x0800bbec — ADMA bounce read: wrapper around DMA read */
void adma_bounce_read(int slot, int buf, int *remaining)
{
  int iVar1;

  iVar1 = dma_read_helper(buf,(&DAT_0804e2d0)[slot] + 0x80,(&DAT_0804e2c8)[slot] + 0x34,
                       0x8000);
  *remaining = *remaining - (iVar1 - buf);
  return;
}

/* orig: 0x0800bc20 — ADMA bounce write: burst-write via DMA descriptor */
void adma_bounce_write(int slot, int buf, int *remaining)
{
  int iVar1;
  dma_write_desc_t desc;

  desc.status_reg_addr = ((uint *)&DAT_0804e2c8)[slot] + 0x34;
  desc.ready_mask = 0x4000;
  desc.remaining = *remaining;
  desc.error_mask = 0x1a;
  iVar1 = dma_write_helper((&DAT_0804e2d0)[slot] + 0x80, buf, &desc);
  *remaining = *remaining - (iVar1 - buf);
}

/* ---- eMMC higher-level helpers (from fhprg_80327f8.c) ---- */

/* orig: 0x080329f8 sdcc_event_notify — issue data memory barrier if bit set.
 * addr/size are for cache maintenance but unused in this simplified version. */
void sdcc_event_notify(int flags, int addr, uint size)
{
  (void)addr; (void)size;
  if (flags << 0x1d < 0) {
    DataMemoryBarrier(0x1f);
  }
  return;
}

/* orig: 0x08032d8c sdcc_post_write_cleanup — send CMD12 (STOP) if needed, wait ready.
 *
 * After a multi-block transfer, sends CMD12 (STOP_TRANSMISSION) to
 * terminate the transfer. For reliable writes, also waits for the
 * card to return to transfer state via CMD13.
 */
undefined4 sdcc_post_write_cleanup(int *dev, int need_busy, int need_stop)
{
  undefined4 uVar1;
  int cmd[10]; /* command struct for CMD12 */

  uVar1 = 0;
  if (need_stop == 0) {
    if (need_busy == 1) {
      uVar1 = sdcc_wait_card_ready(dev);
    }
  }
  else {
    memset_zero(cmd, sizeof(cmd));
    cmd[0] = 0xc;                                 /* CMD12: STOP_TRANSMISSION */
    *(undefined1 *)&cmd[2] = 1;                   /* resp_type: R1 */
    cmd[7] = (need_busy == 1) ? 1 : 0;            /* busy_wait */
    uVar1 = sdcc_send_cmd(dev, cmd);
  }
  return uVar1;
}

/* orig: 0x08034314 sdcc_fifo_write — write data to FIFO, polling for space.
 * Reads or writes word-at-a-time through the FIFO data port at reg+0x20. */
int sdcc_fifo_write(int *dev, int cmd_config, undefined4 *buf, uint byte_count)
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 local_28;

  local_28 = 0;
  iVar4 = *dev;
  if (dev[0x16] == 1) {
    uVar6 = dev[9];
    uVar5 = byte_count / uVar6;
  }
  else {
    uVar5 = 1;
    uVar6 = byte_count;
  }
  uVar6 = uVar6 + 3 >> 2;
  if ((int)(*(uint *)(cmd_config + 0x24) << 0x1e) < 0) {
    uVar7 = 0x20;
  }
  else {
    if ((*(uint *)(cmd_config + 0x24) & 1) == 0) {
      return 1;
    }
    uVar7 = 0x10;
  }
  do {
    iVar1 = sdcc_wait_complete(iVar4,uVar7,&local_28);
    if (iVar1 != 0) {
      *(undefined4 *)(cmd_config + 0x20) = local_28;
      return iVar1;
    }
    sdcc_clear_status(iVar4,uVar7);
    uVar2 = 0;
    if ((int)(*(uint *)(cmd_config + 0x24) << 0x1e) < 0) {
      for (; uVar2 < uVar6; uVar2 = uVar2 + 1) {
        *buf = *(undefined4 *)((&DAT_0804e2d8)[iVar4] + 0x20);
        buf = buf + 1;
      }
    }
    else if ((*(uint *)(cmd_config + 0x24) & 1) != 0) {
      for (; uVar2 < uVar6; uVar2 = uVar2 + 1) {
        uVar3 = *buf;
        buf = buf + 1;
        *(undefined4 *)((&DAT_0804e2d8)[iVar4] + 0x20) = uVar3;
      }
    }
    uVar5 = uVar5 - 1;
  } while (uVar5 != 0);
  return 0;
}

/* ADMA2 descriptor table — must be in DDR for DMA access.
 * Each descriptor is 8 bytes. Max descriptors = ceil(transfer_size / 64KB).
 * 128 entries handles up to 8MB transfers (more than enough). */
static byte adma_desc_table[128 * 8]
    __attribute__((section(".ddr_bss"), aligned(32)));

/* orig: 0x080343c0 sdcc_dma_setup — build ADMA2 descriptor table and set ADMA address.
 * Original used hardcoded 0x80201000; we use a properly allocated DDR buffer. */
undefined4 sdcc_dma_setup(int slot, int buf, uint byte_count)
{
  uint uVar1;
  byte *pbVar2;
  uint uVar3;

  sdcc_event_notify(4,0,0);
  sdcc_event_notify(2,buf,byte_count);
  sdcc_event_notify(4,0,0);
  pbVar2 = adma_desc_table;
  uVar1 = byte_count >> 0x10;
  if ((byte_count & 0xffff) != 0) {
    uVar1 = uVar1 + 1;
  }
  memset_zero((void *)adma_desc_table,uVar1 << 3);
  if (byte_count != 0) {
    while( true ) {
      uVar3 = 0x10000;
      if (byte_count < 0x10000) {
        uVar3 = byte_count;
      }
      write_le32(buf,pbVar2 + 4);
      pbVar2[2] = (byte)uVar3;
      pbVar2[3] = (byte)(uVar3 >> 8);
      byte_count = byte_count - uVar3;
      *pbVar2 = 1;
      pbVar2[1] = 0;
      if (uVar3 != 0) {
        *pbVar2 = 0x21;
        pbVar2[1] = 0;
      }
      buf = buf + uVar3;
      if (byte_count == 0) break;
      pbVar2 = pbVar2 + 8;
    }
    *pbVar2 = *pbVar2 | 2;
    pbVar2[1] = 0;
  }
  sdcc_event_notify(4,0,0);
  sdcc_event_notify(2,(int)adma_desc_table,uVar1 << 3);
  sdcc_event_notify(4,0,0);
  sdcc_set_adma_addr_hi(slot,0);
  sdcc_set_adma_addr_lo(slot,(undefined4)adma_desc_table);
  return 0;
}

/* orig: 0x0803456c sdcc_wait_complete — poll SDHCI interrupt status for completion or error */
undefined4 sdcc_wait_complete(int slot, uint mask, uint *out_status)
{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;

  uVar3 = 0;
  if ((mask & 0x7ff003f) == 0) {
    uVar2 = 0x14;
  }
  else {
    do {
      uVar1 = sdcc_read_present(slot);
      if (((mask | 0x8000) & uVar1) != 0) {
        *out_status = uVar1;
        if ((uVar1 & 0x7ff0000) == 0) {
          return 0;
        }
        return 1;
      }
      thunk_FUN_080199b4(100);
      uVar3 = uVar3 + 100;
    } while (uVar3 < 5000000);
    uVar2 = 3;
  }
  return uVar2;
}

/* orig: 0x08034a40 mmc_switch_cmd6 — send CMD6 (SWITCH) then CMD13 to verify.
 *
 * CMD6 (SWITCH) modifies the EXT_CSD register. After switching, CMD13
 * (SEND_STATUS) verifies the card is back in transfer state (state 4)
 * and checks the SWITCH_ERROR bit (bit 7 of status).
 *
 * cmd6_arg encodes: [25:24]=access, [23:16]=index, [15:8]=value, [7:0]=cmd_set
 * For partition switch: access=3 (write), index=179 (PARTITION_CONFIG)
 */
int mmc_switch_cmd6(int *dev, undefined4 cmd6_arg)
{
  int ret;
  int cmd[10]; /* command struct (reused for CMD6 then CMD13) */

  /* CMD6: SWITCH */
  memset_zero(cmd, sizeof(cmd));
  cmd[0] = 6;                                     /* CMD6: SWITCH */
  cmd[1] = (int)cmd6_arg;                         /* switch argument */
  *(undefined1 *)&cmd[2] = 1;                     /* resp_type: R1 */
  cmd[7] = 1;                                     /* busy_wait */
  ret = sdcc_send_cmd(dev, cmd);
  if (ret == 0) {
    /* CMD13: SEND_STATUS — verify switch completed */
    memset_zero(cmd, sizeof(cmd));
    cmd[0] = 0xd;                                 /* CMD13: SEND_STATUS */
    cmd[1] = (uint)*(ushort *)((int)dev + 10) << 0x10; /* RCA */
    *(undefined1 *)&cmd[2] = 1;                   /* resp_type: R1 */
    ret = sdcc_send_cmd(dev, cmd);
    if (ret == 0) {
      if ((uint)(cmd[3] << 0x13) >> 0x1c == 4) {  /* state == transfer? */
        ret = 0;
        if (cmd[3] << 0x18 < 0) {                 /* SWITCH_ERROR bit? */
          ret = 0x13;
        }
      }
      else {
        ret = 8; /* not in transfer state */
      }
    }
  }
  return ret;
}

/* orig: 0x08034b88 sdcc_setup_data_xfer — poll status after firing command, check for errors */
undefined4 sdcc_setup_data_xfer(int *dev, int *cmd)
{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;

  iVar4 = *dev;
  uVar5 = 1;
  uVar1 = 0;
  uVar3 = 0;
  do {
    if (0x7ffff < uVar3) goto LAB_08034c08;
    uVar1 = sdcc_read_status(iVar4);
    if ((uVar1 & 0x40) != 0) {
      *(undefined4 *)((&DAT_0804e2c8)[iVar4] + 0x38) = 0x40;
      uVar5 = 0;
      if ((uVar1 & 0x800000) != 0) {
        *(undefined4 *)((&DAT_0804e2c8)[iVar4] + 0x38) = 0x800000;
        cmd[7] = 0;
      }
      goto LAB_08034c08;
    }
    if ((uVar1 & 4) != 0) {
      *(undefined4 *)((&DAT_0804e2c8)[iVar4] + 0x38) = 4;
      uVar5 = 2;
      goto LAB_08034c08;
    }
    uVar3 = uVar3 + 1;
  } while ((uVar1 & 1) == 0);
  iVar2 = *cmd;
  if (((iVar2 == 0x29) || (iVar2 == 1)) || (iVar2 == 5)) {
    uVar5 = 0;
  }
  else {
    uVar5 = 4;
  }
  *(undefined4 *)((&DAT_0804e2c8)[iVar4] + 0x38) = 1;
LAB_08034c08:
  cmd[8] = uVar1;
  return uVar5;
}

/* orig: 0x08034c14 sdcc_adma_transfer — read data from FIFO via ADMA or byte-at-a-time */
undefined4 sdcc_adma_transfer(int *dev, uint *buf, int byte_count)
{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  undefined4 uVar5;
  bool bVar6;
  int local_20;

  iVar4 = *dev;
  bVar6 = ((uint)buf & 3) != 0;
  uVar5 = 0;
  local_20 = 0;
  if (buf == (uint *)0x0) {
    uVar5 = 0xd;
  }
  else {
    while (0 < byte_count) {
      uVar1 = sdcc_read_status(iVar4);
      if ((uVar1 & 0x2a) != 0) {
        uVar5 = 0xd;
        goto LAB_08034c9e;
      }
      if (byte_count == 0) break;
      if ((uVar1 & 0x200000) != 0) {
        if (((uVar1 & 0x8000) == 0) || (bVar6)) {
          uVar1 = *(uint *)((&DAT_0804e2c8)[iVar4] + 0x80);
          if (bVar6) {
            uVar2 = 0;
            puVar3 = buf;
            do {
              buf = (uint *)((int)puVar3 + 1);
              *(char *)puVar3 = (char)uVar1;
              uVar1 = uVar1 >> 8;
              uVar2 = uVar2 + 1;
              puVar3 = buf;
            } while (uVar2 < 4);
          }
          else {
            *buf = uVar1;
            buf = buf + 1;
          }
          byte_count = byte_count + -4;
        }
        else {
          local_20 = byte_count;
          adma_bounce_read(iVar4,(int)buf,&local_20);
          buf = (uint *)((int)buf + (byte_count - local_20));
          byte_count = local_20;
        }
      }
    }
    if (false) {
LAB_08034c9e:
      /* error path: reset controller */
      mmc_set_bus_width(dev + 3,5,0,0);
      {
        int iVar2 = *dev;
        undefined4 *puVar1 = (undefined4 *)(&DAT_0804e2c8)[iVar2];
        undefined4 uVar3 = puVar1[1];
        undefined4 uVar4a = *puVar1;
        undefined4 uVar5a = puVar1[0xf];
        sdcc_clock_setup(iVar2,0,2);
        *(undefined4 *)((&DAT_0804e2c8)[iVar2] + 4) = uVar3;
        sdcc_enable_clock(iVar2);
        *(undefined4 *)(&DAT_0804e2c8)[iVar2] = uVar4a;
        sdcc_enable_clock(iVar2);
        *(undefined4 *)((&DAT_0804e2c8)[iVar2] + 0x3c) = uVar5a;
        mmc_set_bus_width(dev + 3,*(char *)((int)dev + 0x15) == '\x02',0,0);
      }
    }
    sdcc_set_all_irq(iVar4);
  }
  return uVar5;
}

/* orig: 0x08034eaa sdcc_adma_write — send CMD55 (APP_CMD) then the actual data command.
 *
 * Sends CMD55 (APP_CMD) with RCA, then the actual data command.
 * CMD55 signals that the next command is an application-specific command.
 *
 * Command struct layout: [0]=cmd_num, [1]=arg, [2]=resp_type (byte),
 *   [3-6]=resp_data, [7]=busy_wait, [8]=status, [9]=flags
 */
undefined4 sdcc_adma_write(int *dev, undefined4 *cmd)
{
  int app_cmd[10];

  memset_zero(app_cmd, sizeof(app_cmd));
  app_cmd[0] = 0x37;                             /* CMD55: APP_CMD */
  app_cmd[1] = (uint)*(ushort *)((int)dev + 10) << 0x10; /* RCA */
  *(undefined1 *)&app_cmd[2] = 1;                /* resp_type: R1 */
  sdcc_send_cmd(dev, app_cmd);
  sdcc_send_cmd(dev, (int *)cmd);
  return 0;
}

/* orig: 0x08034edc sdcc_pre_cmd_hook — clear pending status, configure command register */
/* sdcc_pre_cmd_hook — clear pending SDCC status, then build and fire
 * the hardware command register via sdcc_cleanup().
 *
 * The cmd_config struct passed to sdcc_cleanup is 10 shorts (20 bytes):
 *   [0] = data_present_enable (1 for CMD17/18/24/25/53)
 *   [1] = busy_signal_enable (from cmd[7])
 *   [2] = has_response (1 if resp_type != 0)
 *   [3] = (unused)
 *   [4] = index_check (1 for R2 response)
 *   [5] = crc_check (1 if resp_type != 0)
 *   [6] = command_index (CMD number)
 *   [7] = (unused)
 *   [8..9] = command_argument (32-bit, overlaid as int at byte offset 16)
 *
 * IMPORTANT: These must be contiguous in memory — sdcc_cleanup reads
 * them by array index. Using separate locals would let the compiler
 * reorder them, breaking the layout.
 */
void sdcc_pre_cmd_hook(int *dev, int *cmd)
{
  uint uVar1;
  int cmd_num;
  uint uVar3;
  int slot;
  /* cmd_config: 10 shorts = 20 bytes, contiguous for sdcc_cleanup */
  short cmd_config[10];

  slot = *dev;
  uVar3 = 0;
  memset_zero(cmd_config, 0x14);
  do {
    *(undefined4 *)((&DAT_0804e2c8)[slot] + 0x38) = 0x18007ff;
    uVar3 = uVar3 + 1;
    uVar1 = sdcc_read_status(slot);
    if ((uVar1 & 0x18007ff) == 0) goto status_clear;
  } while (uVar3 < 1000);
  *(uint *)((&DAT_0804e2c8)[slot] + 0x2c) = *(uint *)((&DAT_0804e2c8)[slot] + 0x2c) & 0xfffffffe;
  sdcc_enable_clock(slot);
status_clear:
  cmd_config[6] = (short)*cmd;          /* command index */
  cmd_config[2] = 1;                     /* has_response */
  if ((char)cmd[2] != '\0') {
    cmd_config[5] = 1;                   /* crc_check */
    if ((char)cmd[2] == '\x04') {
      cmd_config[4] = 1;                 /* index_check (R2) */
    }
  }
  if (cmd[7] != 0) {
    cmd_config[1] = 1;                   /* busy_signal_enable */
  }
  cmd_num = *cmd;
  if (cmd_num == 0x35 || cmd_num == 0x11 || cmd_num == 0x12 ||
      cmd_num == 0x18 || cmd_num == 0x19) {
    cmd_config[0] = 1;                   /* data_present_enable */
  }
  *(int *)(cmd_config + 8) = cmd[1];    /* command argument (32-bit at offset 16) */
  sdcc_cleanup(slot, cmd_config);
}

/* orig: 0x08034f80 sdcc_get_card_status — send CMD13 and return R1 state nibble.
 *
 * Sends CMD13 (SEND_STATUS) with RCA and extracts the card state
 * from bits [12:9] of the R1 response (CURRENT_STATE field).
 * Returns: 0=idle, 3=standby, 4=transfer, 5=data, 6=receive, 7=program
 * Returns 9 on failure.
 */
uint sdcc_get_card_status(int *dev)
{
  int ret;
  uint state;
  int cmd[10]; /* command struct: [0]=num [1]=arg [2]=resp [3-6]=resp_data ... */

  state = 9;
  memset_zero(cmd, sizeof(cmd));
  cmd[0] = 0xd;                                   /* CMD13: SEND_STATUS */
  cmd[1] = (uint)*(ushort *)((int)dev + 10) << 0x10; /* RCA in bits [31:16] */
  *(undefined1 *)&cmd[2] = 1;                     /* resp_type: R1 */
  ret = sdcc_send_cmd(dev, cmd);
  if (ret == 0) {
    state = (uint)(cmd[3] << 0x13) >> 0x1c;       /* bits [12:9] = CURRENT_STATE */
  }
  return state;
}

/* orig: 0x080350be sdcc_wait_card_ready — poll CMD13 status until card is in transfer state */
undefined4 sdcc_wait_card_ready(int *dev)
{
  int iVar1;
  uint uVar2;

  uVar2 = 0;
  while( true ) {
    if (0x7ffff < uVar2) {
      return 8;
    }
    iVar1 = sdcc_get_card_status(dev);
    if (iVar1 == 4) break;
    thunk_FUN_080199b4(100);
    uVar2 = uVar2 + 1;
  }
  return 0;
}

/* orig: 0x08035040 sdcc_pre_write_setup — calculate timeout and total byte count for write */
int sdcc_pre_write_setup(undefined4 *dev, int is_reliable, int num_blocks)
{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;

  uVar1 = *dev;
  uVar3 = 1;
  iVar2 = 5000;
  if ((*(char *)(dev + 2) == '\x02') || (*(char *)(dev + 2) == '\x06')) {
    if (is_reliable != 0) {
      iVar2 = 2000;
    }
  }
  else if (is_reliable != 0) {
    iVar2 = 400;
  }
  if (dev[0x21] == 0) {
    iVar2 = iVar2 * 50000;
  }
  else {
    iVar2 = dev[0x21] * iVar2;
  }
  *(int *)((&DAT_0804e2c8)[(short)uVar1] + 0x24) = iVar2;
  if (dev[0x16] == 1) {
    uVar3 = dev[9] & 0xffff;
  }
  *(uint *)((&DAT_0804e2c8)[(short)uVar1] + 0x28) = uVar3 * num_blocks;
  return uVar3 * num_blocks;
}

/* orig: 0x080350ee sdcc_post_write_check — poll status for transfer complete or error */
undefined4 sdcc_post_write_check(undefined4 *dev)
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;

  uVar3 = *dev;
  uVar2 = 0;
  do {
    if (0x7ffff < uVar2) {
      return 8;
    }
    uVar1 = sdcc_read_status(uVar3);
    if ((uVar1 & 0x1a) != 0) {
      return 0xe;
    }
    if ((uVar1 & 0x2a) != 0) {
      return 0xd;
    }
    uVar2 = uVar2 + 1;
  } while ((uVar1 & 0x100) == 0);
  sdcc_set_all_irq(uVar3);
  return 0;
}

/* orig: 0x08035134 sdcc_busy_wait — wait for busy completion (CMD13 check as fallback) */
undefined4 sdcc_busy_wait(int *dev)
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;

  iVar4 = *dev;
  uVar3 = 7;
  uVar2 = 0;
  do {
    if (0x7ffff < uVar2) {
      if ((true) && (iVar4 = sdcc_get_card_status(dev), iVar4 == 4)) {
LAB_0803517c:
        uVar3 = 0;
      }
      return uVar3;
    }
    uVar1 = sdcc_read_status(iVar4);
    if ((uVar1 & 0x800000) != 0) {
      *(undefined4 *)((&DAT_0804e2c8)[iVar4] + 0x38) = 0x800000;
      goto LAB_0803517c;
    }
    thunk_FUN_080199b4(10);
    uVar2 = uVar2 + 1;
  } while( true );
}

/* orig: 0x08035188 sdcc_pio_transfer — write data word-by-word via PIO (FIFO at +0x80) */
undefined4 sdcc_pio_transfer(int *dev, byte *buf, int byte_count)
{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  byte *pbVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  bool bVar9;
  int local_28;

  iVar7 = *dev;
  uVar8 = 0;
  bVar9 = ((uint)buf & 3) != 0;
  uVar6 = 0;
  local_28 = 0;
  if (buf == (byte *)0x0) {
    return 0xe;
  }
  sdcc_set_all_irq(iVar7);
LAB_08035234:
  do {
    if (byte_count < 1) goto LAB_08035238;
    uVar6 = sdcc_read_status(iVar7);
    if ((uVar6 & 0x1a) != 0) break;
    if (byte_count == 0) goto LAB_08035238;
    if ((uVar6 & 0x10000) == 0) {
      if ((uVar6 & 0x4000) == 0) {
        if (!bVar9) goto LAB_0803520c;
LAB_08035218:
        uVar4 = 0;
        uVar3 = 0;
        pbVar5 = buf;
        do {
          buf = pbVar5 + 1;
          uVar4 = uVar4 | (uint)*pbVar5 << (uVar3 & 0xff);
          uVar3 = uVar3 + 8;
          pbVar5 = buf;
        } while (uVar3 < 0x20);
        *(uint *)((&DAT_0804e2c8)[iVar7] + 0x80) = uVar4;
      }
      else {
        if (bVar9) goto LAB_08035218;
        if (0x1f < byte_count) {
          local_28 = byte_count;
          adma_bounce_write(iVar7,(int)buf,&local_28);
          iVar1 = local_28;
          buf = buf + (byte_count - local_28);
          uVar6 = sdcc_read_status(iVar7);
          byte_count = iVar1;
          goto LAB_08035234;
        }
LAB_0803520c:
        uVar2 = *(undefined4 *)buf;
        buf = buf + 4;
        *(undefined4 *)((&DAT_0804e2c8)[iVar7] + 0x80) = uVar2;
      }
      byte_count = byte_count + -4;
    }
  } while( true );
  /* LAB_080351ca: */
  uVar8 = 0xe;
  goto LAB_08035254;
LAB_08035238:
  if (true) {
    while ((uVar6 & 0x100) == 0) {
      if ((uVar6 & 0x1a) != 0) {
        uVar8 = 0xe;
        goto LAB_08035254;
      }
      uVar6 = sdcc_read_status(iVar7);
    }
  }
LAB_08035254:
  sdcc_set_all_irq(iVar7);
  return uVar8;
}
