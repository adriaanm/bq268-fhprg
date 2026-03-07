/* sdcc_helpers.c — eMMC data transfer helpers.
 *
 * These sit between sdcc_send_cmd (in emmc.c) and the MMIO register
 * wrappers (in sdcc_regs.c). They handle data transfer setup, DMA
 * configuration, FIFO writes, busy-waits, and post-write cleanup.
 *
 * Source: src/fhprg/fhprg_80327f8.c, src/fhprg/fhprg_8007b18.c
 */
#include "firehose.h"

/* Forward declarations for sub-helpers (defined later in this file) */
uint sdcc_get_card_status();
static undefined4 sdcc_wait_card_ready();

/* ---- DMA bounce helpers (from fhprg_8007b18.c) ---- */

/* orig: 0x08006e1a — write uint32 as little-endian bytes */
static void write_le32(param_1, param_2)
undefined4 param_1; undefined1 * param_2;
{
  *param_2 = (char)param_1;
  param_2[1] = (char)((uint)param_1 >> 8);
  param_2[2] = (char)((uint)param_1 >> 0x10);
  param_2[3] = (char)((uint)param_1 >> 0x18);
  return;
}

/* orig: 0x08008ba4 — DMA read: copy words from FIFO to buffer, polling status */
static int dma_read_helper(param_1, param_2, param_3, param_4)
int param_1; int param_2; uint * param_3; uint param_4;
{
  uint *src = (uint *)param_2;
  uint *dst = (uint *)param_1;

  while ((*param_3 & param_4) != 0) {
    /* Copy 8 words (32 bytes) per iteration */
    dst[0] = *src; dst[1] = *src; dst[2] = *src; dst[3] = *src;
    dst[4] = *src; dst[5] = *src; dst[6] = *src; dst[7] = *src;
    dst += 8;
  }
  return (int)dst;
}

/* orig: 0x08008bc4 — DMA write: copy words from buffer to FIFO, decrementing size */
static int dma_write_helper(param_1, param_2, param_3)
int param_1; int param_2; int * param_3;
{
  uint *dst = (uint *)param_1;
  uint *src = (uint *)param_2;
  int remaining = param_3[0];

  while (remaining > 0) {
    /* Write 8 words (32 bytes) per iteration */
    *dst = src[0]; *dst = src[1]; *dst = src[2]; *dst = src[3];
    *dst = src[4]; *dst = src[5]; *dst = src[6]; *dst = src[7];
    src += 8;
    remaining -= 32;
  }
  param_3[0] = remaining;
  return (int)src;
}

/* orig: 0x0800bbec — ADMA bounce read: wrapper around DMA read */
void adma_bounce_read(param_1, param_2, param_3)
int param_1; int param_2; int * param_3;
{
  int iVar1;

  iVar1 = dma_read_helper(param_2,(&DAT_0804e2d0)[param_1] + 0x80,(&DAT_0804e2c8)[param_1] + 0x34,
                       0x8000);
  *param_3 = *param_3 - (iVar1 - param_2);
  return;
}

/* orig: 0x0800bc20 — ADMA bounce write: wrapper around DMA write */
undefined8 adma_bounce_write(param_1, param_2, param_3)
int param_1; int param_2; int * param_3;
{
  int iVar1;
  int local_20;
  undefined4 local_1c;
  int local_18;
  undefined4 local_14;

  local_20 = (int)((&DAT_0804e2c8)[param_1] + 0x34);
  local_1c = 0x4000;
  local_18 = *param_3;
  local_14 = 0x1a;
  iVar1 = dma_write_helper((&DAT_0804e2d0)[param_1] + 0x80,param_2,&local_20);
  *param_3 = *param_3 - (iVar1 - param_2);
  return CONCAT44(local_1c,local_20);
}

/* ---- eMMC higher-level helpers (from fhprg_80327f8.c) ---- */

/* orig: 0x080329f8 sdcc_event_notify — issue data memory barrier if bit set */
void sdcc_event_notify(param_1)
int param_1;
{
  if (param_1 << 0x1d < 0) {
    DataMemoryBarrier(0x1f);
  }
  return;
}

/* orig: 0x08032d8c sdcc_post_write_cleanup — send CMD12 (STOP) if needed, wait ready */
undefined4 sdcc_post_write_cleanup(param_1, param_2, param_3)
undefined4 param_1; int param_2; int param_3;
{
  undefined4 uVar1;
  undefined4 local_30;
  undefined4 local_2c;
  undefined1 local_28;
  uint local_14;
  undefined4 local_c;

  uVar1 = 0;
  if (param_3 == 0) {
    if (param_2 == 1) {
      uVar1 = sdcc_wait_card_ready(param_1);
    }
  }
  else {
    local_30 = 0xc;
    local_28 = 1;
    local_14 = (uint)(param_2 == 1);
    local_2c = 0;
    local_c = 0;
    uVar1 = sdcc_send_cmd(param_1,&local_30);
  }
  return uVar1;
}

/* orig: 0x08034314 sdcc_fifo_write — write data to FIFO, polling for space.
 * Reads or writes word-at-a-time through the FIFO data port at reg+0x20. */
int sdcc_fifo_write(param_1, param_2, param_3, param_4)
int * param_1; int param_2; undefined4 * param_3; uint param_4;
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
  iVar4 = *param_1;
  if (param_1[0x16] == 1) {
    uVar6 = param_1[9];
    uVar5 = param_4 / uVar6;
  }
  else {
    uVar5 = 1;
    uVar6 = param_4;
  }
  uVar6 = uVar6 + 3 >> 2;
  if ((int)(*(uint *)(param_2 + 0x24) << 0x1e) < 0) {
    uVar7 = 0x20;
  }
  else {
    if ((*(uint *)(param_2 + 0x24) & 1) == 0) {
      return 1;
    }
    uVar7 = 0x10;
  }
  do {
    iVar1 = sdcc_wait_complete(iVar4,uVar7,&local_28);
    if (iVar1 != 0) {
      *(undefined4 *)(param_2 + 0x20) = local_28;
      return iVar1;
    }
    sdcc_clear_status(iVar4,uVar7);
    uVar2 = 0;
    if ((int)(*(uint *)(param_2 + 0x24) << 0x1e) < 0) {
      for (; uVar2 < uVar6; uVar2 = uVar2 + 1) {
        *param_3 = *(undefined4 *)((&DAT_0804e2d8)[iVar4] + 0x20);
        param_3 = param_3 + 1;
      }
    }
    else if ((*(uint *)(param_2 + 0x24) & 1) != 0) {
      for (; uVar2 < uVar6; uVar2 = uVar2 + 1) {
        uVar3 = *param_3;
        param_3 = param_3 + 1;
        *(undefined4 *)((&DAT_0804e2d8)[iVar4] + 0x20) = uVar3;
      }
    }
    uVar5 = uVar5 - 1;
  } while (uVar5 != 0);
  return 0;
}

/* orig: 0x080343c0 sdcc_dma_setup — build ADMA2 descriptor table and set ADMA address.
 * Uses DAT_80201000 as the fixed ADMA descriptor table address. */
undefined4 sdcc_dma_setup(param_1, param_2, param_3)
undefined4 param_1; int param_2; uint param_3;
{
  uint uVar1;
  byte *pbVar2;
  uint uVar3;

  sdcc_event_notify(4,0);
  sdcc_event_notify(2,param_2,param_3);
  sdcc_event_notify(4,0);
  pbVar2 = (byte *)0x80201000;
  uVar1 = param_3 >> 0x10;
  if ((param_3 & 0xffff) != 0) {
    uVar1 = uVar1 + 1;
  }
  memset_zero((void *)0x80201000,uVar1 << 3);
  if (param_3 != 0) {
    while( true ) {
      uVar3 = 0x10000;
      if (param_3 < 0x10000) {
        uVar3 = param_3;
      }
      write_le32(param_2,pbVar2 + 4);
      pbVar2[2] = (byte)uVar3;
      pbVar2[3] = (byte)(uVar3 >> 8);
      param_3 = param_3 - uVar3;
      *pbVar2 = 1;
      pbVar2[1] = 0;
      if (uVar3 != 0) {
        *pbVar2 = 0x21;
        pbVar2[1] = 0;
      }
      param_2 = param_2 + uVar3;
      if (param_3 == 0) break;
      pbVar2 = pbVar2 + 8;
    }
    *pbVar2 = *pbVar2 | 2;
    pbVar2[1] = 0;
  }
  sdcc_event_notify(4,0);
  sdcc_event_notify(2,(int)(byte *)0x80201000,uVar1 << 3);
  sdcc_event_notify(4,0);
  sdcc_set_adma_addr_hi(param_1,0);
  sdcc_set_adma_addr_lo(param_1,(undefined4)(byte *)0x80201000);
  return 0;
}

/* orig: 0x0803456c sdcc_wait_complete — poll SDHCI interrupt status for completion or error */
undefined4 sdcc_wait_complete(param_1, param_2, param_3)
undefined4 param_1; uint param_2; uint * param_3;
{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;

  uVar3 = 0;
  if ((param_2 & 0x7ff003f) == 0) {
    uVar2 = 0x14;
  }
  else {
    do {
      uVar1 = sdcc_read_present(param_1);
      if (((param_2 | 0x8000) & uVar1) != 0) {
        *param_3 = uVar1;
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

/* orig: 0x08034a40 mmc_switch_cmd6 — send CMD6 (SWITCH) then CMD13 to verify */
int mmc_switch_cmd6(param_1, param_2)
int param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 local_60;
  int local_5c;
  undefined1 local_58;
  int local_54;
  undefined4 local_44;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined1 local_30;
  undefined4 local_1c;
  undefined4 local_14;

  local_38 = 6;
  local_30 = 1;
  local_1c = 1;
  local_14 = 0;
  uStack_34 = param_2;
  iVar1 = sdcc_send_cmd(param_1,&local_38);
  if (iVar1 == 0) {
    local_60 = 0xd;
    local_58 = 1;
    local_44 = 0;
    local_5c = (uint)*(ushort *)(param_1 + 10) << 0x10;
    local_3c = 0;
    iVar1 = sdcc_send_cmd(param_1,&local_60);
    if (iVar1 == 0) {
      if ((uint)(local_54 << 0x13) >> 0x1c == 4) {
        iVar1 = 0;
        if (local_54 << 0x18 < 0) {
          iVar1 = 0x13;
        }
      }
      else {
        iVar1 = 8;
      }
    }
  }
  return iVar1;
}

/* orig: 0x08034b88 sdcc_setup_data_xfer — poll status after firing command, check for errors */
undefined4 sdcc_setup_data_xfer(param_1, param_2)
int * param_1; int * param_2;
{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;

  iVar4 = *param_1;
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
        param_2[7] = 0;
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
  iVar2 = *param_2;
  if (((iVar2 == 0x29) || (iVar2 == 1)) || (iVar2 == 5)) {
    uVar5 = 0;
  }
  else {
    uVar5 = 4;
  }
  *(undefined4 *)((&DAT_0804e2c8)[iVar4] + 0x38) = 1;
LAB_08034c08:
  param_2[8] = uVar1;
  return uVar5;
}

/* orig: 0x08034c14 sdcc_adma_transfer — read data from FIFO via ADMA or byte-at-a-time */
undefined4 sdcc_adma_transfer(param_1, param_2, param_3)
int * param_1; uint * param_2; int param_3;
{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  undefined4 uVar5;
  bool bVar6;
  int local_20;

  iVar4 = *param_1;
  bVar6 = ((uint)param_2 & 3) != 0;
  uVar5 = 0;
  local_20 = 0;
  if (param_2 == (uint *)0x0) {
    uVar5 = 0xd;
  }
  else {
    while (0 < param_3) {
      uVar1 = sdcc_read_status(iVar4);
      if ((uVar1 & 0x2a) != 0) {
        uVar5 = 0xd;
        goto LAB_08034c9e;
      }
      if (param_3 == 0) break;
      if ((uVar1 & 0x200000) != 0) {
        if (((uVar1 & 0x8000) == 0) || (bVar6)) {
          uVar1 = *(uint *)((&DAT_0804e2c8)[iVar4] + 0x80);
          if (bVar6) {
            uVar2 = 0;
            puVar3 = param_2;
            do {
              param_2 = (uint *)((int)puVar3 + 1);
              *(char *)puVar3 = (char)uVar1;
              uVar1 = uVar1 >> 8;
              uVar2 = uVar2 + 1;
              puVar3 = param_2;
            } while (uVar2 < 4);
          }
          else {
            *param_2 = uVar1;
            param_2 = param_2 + 1;
          }
          param_3 = param_3 + -4;
        }
        else {
          local_20 = param_3;
          adma_bounce_read(iVar4,(int)param_2,&local_20);
          param_2 = (uint *)((int)param_2 + (param_3 - local_20));
          param_3 = local_20;
        }
      }
    }
    if (false) {
LAB_08034c9e:
      /* error path: reset controller */
      mmc_set_bus_width(param_1 + 3,5);
      {
        int iVar2 = *param_1;
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
        mmc_set_bus_width(param_1 + 3,*(char *)((int)param_1 + 0x15) == '\x02');
      }
    }
    sdcc_set_all_irq(iVar4);
  }
  return uVar5;
}

/* orig: 0x08034eaa sdcc_adma_write — send CMD55 (APP_CMD) then the actual data command */
undefined4 sdcc_adma_write(param_1, param_2)
int param_1; undefined4 param_2;
{
  undefined4 local_38;
  int local_34;
  undefined1 local_30;
  undefined4 local_1c;
  undefined4 local_14;

  local_38 = 0x37;
  local_34 = (uint)*(ushort *)(param_1 + 10) << 0x10;
  local_30 = 1;
  local_1c = 0;
  local_14 = 0;
  sdcc_send_cmd(param_1,&local_38);
  sdcc_send_cmd(param_1,param_2);
  return 0;
}

/* orig: 0x08034edc sdcc_pre_cmd_hook — clear pending status, configure command register */
void sdcc_pre_cmd_hook(param_1, param_2)
int * param_1; int * param_2;
{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined2 local_30;
  undefined2 local_2e;
  undefined2 local_2c;
  undefined2 local_28;
  undefined2 local_26;
  undefined2 local_24;
  int local_20;

  iVar4 = *param_1;
  uVar3 = 0;
  memset_zero(&local_30,0x14);
  do {
    *(undefined4 *)((&DAT_0804e2c8)[iVar4] + 0x38) = 0x18007ff;
    uVar3 = uVar3 + 1;
    uVar1 = sdcc_read_status(iVar4);
    if ((uVar1 & 0x18007ff) == 0) goto LAB_08034f26;
  } while (uVar3 < 1000);
  *(uint *)((&DAT_0804e2c8)[iVar4] + 0x2c) = *(uint *)((&DAT_0804e2c8)[iVar4] + 0x2c) & 0xfffffffe;
  sdcc_enable_clock(iVar4);
LAB_08034f26:
  local_24 = (undefined2)*param_2;
  local_2c = 1;
  if (((char)param_2[2] != '\0') && (local_26 = 1, (char)param_2[2] == '\x04')) {
    local_28 = 1;
  }
  if (param_2[7] != 0) {
    local_2e = 1;
  }
  iVar2 = *param_2;
  if ((((iVar2 == 0x35) || (iVar2 == 0x11)) || (iVar2 == 0x12)) ||
     ((iVar2 == 0x18 || (iVar2 == 0x19)))) {
    local_30 = 1;
  }
  local_20 = param_2[1];
  sdcc_cleanup(iVar4,&local_30);
  return;
}

/* orig: 0x08034f80 sdcc_get_card_status — send CMD13 and return card state nibble */
uint sdcc_get_card_status(param_1)
int param_1;
{
  int iVar1;
  uint uVar2;
  undefined4 local_30;
  int local_2c;
  undefined1 local_28;
  int local_24;
  undefined4 local_14;
  undefined4 local_c;

  uVar2 = 9;
  local_30 = 0xd;
  local_28 = 1;
  local_14 = 0;
  local_c = 0;
  local_2c = (uint)*(ushort *)(param_1 + 10) << 0x10;
  iVar1 = sdcc_send_cmd(param_1,&local_30);
  if (iVar1 == 0) {
    uVar2 = (uint)(local_24 << 0x13) >> 0x1c;
  }
  return uVar2;
}

/* orig: 0x080350be sdcc_wait_card_ready — poll CMD13 status until card is in transfer state */
static undefined4 sdcc_wait_card_ready(param_1)
undefined4 param_1;
{
  int iVar1;
  uint uVar2;

  uVar2 = 0;
  while( true ) {
    if (0x7ffff < uVar2) {
      return 8;
    }
    iVar1 = sdcc_get_card_status(param_1);
    if (iVar1 == 4) break;
    thunk_FUN_080199b4(100);
    uVar2 = uVar2 + 1;
  }
  return 0;
}

/* orig: 0x08035040 sdcc_pre_write_setup — calculate timeout and total byte count for write */
int sdcc_pre_write_setup(param_1, param_2, param_3)
undefined4 * param_1; int param_2; int param_3;
{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;

  uVar1 = *param_1;
  uVar3 = 1;
  iVar2 = 5000;
  if ((*(char *)(param_1 + 2) == '\x02') || (*(char *)(param_1 + 2) == '\x06')) {
    if (param_2 != 0) {
      iVar2 = 2000;
    }
  }
  else if (param_2 != 0) {
    iVar2 = 400;
  }
  if (param_1[0x21] == 0) {
    iVar2 = iVar2 * 50000;
  }
  else {
    iVar2 = param_1[0x21] * iVar2;
  }
  *(int *)((&DAT_0804e2c8)[(short)uVar1] + 0x24) = iVar2;
  if (param_1[0x16] == 1) {
    uVar3 = param_1[9] & 0xffff;
  }
  *(uint *)((&DAT_0804e2c8)[(short)uVar1] + 0x28) = uVar3 * param_3;
  return uVar3 * param_3;
}

/* orig: 0x080350ee sdcc_post_write_check — poll status for transfer complete or error */
undefined4 sdcc_post_write_check(param_1)
undefined4 * param_1;
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;

  uVar3 = *param_1;
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
undefined4 sdcc_busy_wait(param_1)
int * param_1;
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;

  iVar4 = *param_1;
  uVar3 = 7;
  uVar2 = 0;
  do {
    if (0x7ffff < uVar2) {
      if ((true) && (iVar4 = sdcc_get_card_status((int)param_1), iVar4 == 4)) {
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
undefined4 sdcc_pio_transfer(param_1, param_2, param_3)
int * param_1; byte * param_2; int param_3;
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

  iVar7 = *param_1;
  uVar8 = 0;
  bVar9 = ((uint)param_2 & 3) != 0;
  uVar6 = 0;
  local_28 = 0;
  if (param_2 == (byte *)0x0) {
    return 0xe;
  }
  sdcc_set_all_irq(iVar7);
LAB_08035234:
  do {
    if (param_3 < 1) goto LAB_08035238;
    uVar6 = sdcc_read_status(iVar7);
    if ((uVar6 & 0x1a) != 0) break;
    if (param_3 == 0) goto LAB_08035238;
    if ((uVar6 & 0x10000) == 0) {
      if ((uVar6 & 0x4000) == 0) {
        if (!bVar9) goto LAB_0803520c;
LAB_08035218:
        uVar4 = 0;
        uVar3 = 0;
        pbVar5 = param_2;
        do {
          param_2 = pbVar5 + 1;
          uVar4 = uVar4 | (uint)*pbVar5 << (uVar3 & 0xff);
          uVar3 = uVar3 + 8;
          pbVar5 = param_2;
        } while (uVar3 < 0x20);
        *(uint *)((&DAT_0804e2c8)[iVar7] + 0x80) = uVar4;
      }
      else {
        if (bVar9) goto LAB_08035218;
        if (0x1f < param_3) {
          local_28 = param_3;
          adma_bounce_write(iVar7,(int)param_2,&local_28);
          iVar1 = local_28;
          param_2 = param_2 + (param_3 - local_28);
          uVar6 = sdcc_read_status(iVar7);
          param_3 = iVar1;
          goto LAB_08035234;
        }
LAB_0803520c:
        uVar2 = *(undefined4 *)param_2;
        param_2 = param_2 + 4;
        *(undefined4 *)((&DAT_0804e2c8)[iVar7] + 0x80) = uVar2;
      }
      param_3 = param_3 + -4;
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
