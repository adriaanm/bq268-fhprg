/* sdcc_regs.c — SDCC controller MMIO register wrappers.
 *
 * These functions read/write SDHCI-compatible registers on the Qualcomm
 * SDCC controller. Each slot has a register base in DAT_0804e2c8[slot]
 * and a FIFO/HC base in DAT_0804e2d8[slot].
 *
 * Source: src/fhprg/fhprg_8007b18.c (lines 5734–6630)
 */
#include "firehose.h"

/* Register base arrays:
 *   DAT_0804e2c8[slot] = SDCC core register base  (offsets: +0x04 config, +0x0C cmd, +0x34 status, +0x38 clear, +0x80 FIFO, etc.)
 *   DAT_0804e2d8[slot] = SDHCI host controller base (offsets: +0x04 blk_size, +0x06 blk_count, +0x08 arg, +0x0C xfer_mode, +0x0E cmd, +0x10..0x1C resp, +0x20 data, +0x24 present_state, +0x28..0x2F host_ctrl, +0x30 normal_int_status, +0x34..0x38 int_enable, +0x3E clock_ctrl, +0x58/0x5C ADMA, +0x100 vendor)
 */

/* orig: 0x0800bbb4 sdcc_set_transfer_mode — configure transfer mode register.
 * mode points to a struct of shorts: [0]=multi_blk, [1]=dma_en, [2]=dir_read, [3]=auto_cmd, [5]=blk_cnt_en */
void sdcc_set_transfer_mode(int slot, ushort *mode)
{
  uint uVar1;

  uVar1 = (uint)*mode << 4;
  if ((char)mode[1] != '\0') {
    uVar1 = uVar1 | 8;
  }
  if ((char)mode[2] == '\x01') {
    uVar1 = uVar1 | 2;
  }
  if (*(char *)((int)mode + 3) != '\0') {
    uVar1 = uVar1 | 4;
  }
  if (*(char *)((int)mode + 5) != '\0') {
    uVar1 = uVar1 | 1;
  }
  *(uint *)(DAT_0804e2c8[slot] + 0x2c) = uVar1;
  sdcc_enable_clock(slot);
  return;
}

/* orig: 0x0800bd20 sdcc_cleanup — write command config register from struct.
 * cmd_config = short[]: [0]=dpe, [1]=ccs_enable, [2]=data_present, [4]=idx_check, [5]=crc_check, [6]=resp_type, [8]=cmd_timeout */
void sdcc_cleanup(int slot, short *cmd_config)
{
  uint uVar1;

  if (cmd_config != (short *)0x0) {
    uVar1 = (uint)(ushort)cmd_config[6];
    if (cmd_config[2] == 1) {
      uVar1 = uVar1 | 0x400;
    }
    if (cmd_config[5] == 1) {
      uVar1 = uVar1 | 0x40;
    }
    if (cmd_config[4] == 1) {
      uVar1 = uVar1 | 0x80;
    }
    if (cmd_config[1] == 1) {
      uVar1 = uVar1 | 0x800;
    }
    if (*cmd_config == 1) {
      uVar1 = uVar1 | 0x1000;
    }
    *(undefined4 *)(DAT_0804e2c8[slot] + 8) = *(undefined4 *)(cmd_config + 8);
    *(uint *)(DAT_0804e2c8[slot] + 0xc) = uVar1;
    sdcc_enable_clock(slot);
    return;
  }
  return;
}

/* orig: 0x0800bd78 sdcc_set_all_irq — set interrupt status to 0x18007ff (all bits) */
void sdcc_set_all_irq(int slot)
{
  *(undefined4 *)(DAT_0804e2c8[slot] + 0x38) = 0x18007ff;
  return;
}

/* orig: 0x0800bd8c sdcc_read_status — read SDCC status register */
undefined4 sdcc_read_status(int slot)
{
  return *(undefined4 *)(DAT_0804e2c8[slot] + 0x34);
}

/* orig: 0x0800bda0 sdcc_enable_clock — busy-wait for clock stable (up to 1000 iterations) */
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
  } while ((*(uint *)(DAT_0804e2c8[slot] + 0x6c) & 1) != 0);
  return;
}

/* orig: 0x0800be44 sdcc_read_present — read SDHCI normal interrupt status */
undefined4 sdcc_read_present(int slot)
{
  return *(undefined4 *)(DAT_0804e2d8[slot] + 0x30);
}

/* orig: 0x0800be68 sdcc_read_present_state — read SDHCI present state register */
undefined4 sdcc_read_present_state(int slot)
{
  return *(undefined4 *)(DAT_0804e2d8[slot] + 0x24);
}

/* orig: 0x0800be78 sdcc_read_response — read 1 or 4 response words (R1 vs R2).
 * For R2 (is_r2!=0), bytes are shifted to match CID/CSD format. */
void sdcc_read_response(int slot, uint *resp, int is_r2)
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;

  iVar1 = DAT_0804e2d8[slot];
  uVar3 = *(uint *)(iVar1 + 0x10);
  *resp = uVar3;
  if (is_r2 != 0) {
    uVar2 = *(uint *)(iVar1 + 0x14);
    resp[1] = uVar2;
    uVar4 = *(uint *)(iVar1 + 0x18);
    resp[2] = uVar4;
    *resp = *(int *)(iVar1 + 0x1c) << 8 | uVar4 >> 0x18;
    resp[1] = uVar4 << 8 | uVar2 >> 0x18;
    resp[2] = uVar2 << 8 | uVar3 >> 0x18;
    resp[3] = uVar3 << 8;
  }
  return;
}

/* orig: 0x0800bfac sdcc_clear_status — clear interrupt bits, poll until clear */
void sdcc_clear_status(int slot, uint mask)
{
  uint uVar1;
  int iVar2;
  bool bVar3;

  iVar2 = 100000;
  do {
    *(uint *)(DAT_0804e2d8[slot] + 0x30) = mask & 0x7ff003f;
    uVar1 = sdcc_read_present(slot);
    if ((mask & 0x7ff003f & uVar1) == 0) {
      return;
    }
    thunk_FUN_080199b4(1);
    bVar3 = iVar2 != 0;
    iVar2 = iVar2 + -1;
  } while (bVar3);
  return;
}

/* orig: 0x0800c008 sdcc_set_block_count — write SDHCI block count register */
void sdcc_set_block_count(int slot, undefined2 count)
{
  *(undefined2 *)(DAT_0804e2d8[slot] + 6) = count;
  return;
}

/* orig: 0x0800c018 sdcc_set_block_size — write SDHCI block size register */
void sdcc_set_block_size(int slot, undefined2 size)
{
  *(undefined2 *)(DAT_0804e2d8[slot] + 4) = size;
  return;
}

/* orig: 0x0800c0c4 sdcc_set_cmd_arg — write SDHCI argument register */
void sdcc_set_cmd_arg(int slot, undefined4 arg)
{
  *(undefined4 *)(DAT_0804e2d8[slot] + 8) = arg;
  return;
}

/* orig: 0x0800c0d4 sdcc_fire_cmd — write SDHCI command register to start command.
 * cmd_desc = byte[6]: [0]=cmd_index, [1]=cmd_type, [2]=data_present, [3]=idx_check, [4]=crc_check, [5]=resp_type */
void sdcc_fire_cmd(int slot, byte *cmd_desc)
{
  *(ushort *)(DAT_0804e2d8[slot] + 0xe) =
       (ushort)*cmd_desc << 8 | (ushort)cmd_desc[1] << 6 | (ushort)cmd_desc[2] << 5 |
       (ushort)cmd_desc[3] << 4 | (ushort)cmd_desc[4] << 3 | (ushort)cmd_desc[5];
  return;
}

/* orig: 0x0800c11c sdcc_set_irq_mask — write SDHCI interrupt signal enable register */
void sdcc_set_irq_mask(int slot, undefined1 mask)
{
  *(undefined1 *)(DAT_0804e2d8[slot] + 0x2e) = mask;
  return;
}

/* orig: 0x0800c12c sdcc_set_transfer_ctrl — write SDHCI transfer mode register.
 * ctrl = byte[5]: [0]=dma_en, [1]=blk_cnt_en, [2]=auto_cmd, [3]=direction, [4]=multi_blk */
void sdcc_set_transfer_ctrl(int slot, byte *ctrl)
{
  *(ushort *)(DAT_0804e2d8[slot] + 0xc) =
       (ushort)*ctrl << 5 | (ushort)ctrl[1] << 4 | (ushort)ctrl[2] << 2 |
       (ushort)ctrl[3] << 1 | (ushort)ctrl[4];
  return;
}

/* orig: 0x0800c154 sdcc_reset_data_line — write and poll reset bit(s) */
void sdcc_reset_data_line(int slot, byte bits)
{
  int iVar1;
  int iVar2;
  bool bVar3;

  iVar1 = 100000;
  iVar2 = DAT_0804e2d8[slot];
  *(byte *)(iVar2 + 0x2f) = bits;
  while ((bVar3 = iVar1 != 0, iVar1 = iVar1 + -1, bVar3 &&
         ((*(byte *)(iVar2 + 0x2f) & bits) != 0))) {
    thunk_FUN_080199b4(1);
  }
  return;
}

/* orig: 0x0800c0a8 sdcc_set_clock_divider — write clock control register */
void sdcc_set_clock_divider(int slot, uint divider)
{
  *(ushort *)(DAT_0804e2d8[slot] + 0x2c) =
       (ushort)(divider << 8) | (ushort)((divider & 0x300) >> 2) | 1;
  return;
}

/* orig: 0x0800bfe8 sdcc_set_adma_addr_lo */
void sdcc_set_adma_addr_lo(int slot, undefined4 addr)
{
  *(undefined4 *)(DAT_0804e2d8[slot] + 0x58) = addr;
  return;
}

/* orig: 0x0800bff8 sdcc_set_adma_addr_hi */
void sdcc_set_adma_addr_hi(int slot, undefined4 addr)
{
  *(undefined4 *)(DAT_0804e2d8[slot] + 0x5c) = addr;
  return;
}

/* orig: 0x0800bdbc sdcc_set_8bit_mode — set/clear bit 4 of FIFO+0x28 */
void sdcc_set_8bit_mode(int slot, int enable)
{
  byte bVar1;

  bVar1 = 0;
  if (enable != 0) {
    bVar1 = 0x10;
  }
  *(byte *)(DAT_0804e2d8[slot] + 0x28) =
       *(byte *)(DAT_0804e2d8[slot] + 0x28) & 0xe7 | bVar1;
  return;
}

/* orig: 0x0800bdd8 sdcc_trigger_vendor_reset — set bits in vendor register +0x100 */
void sdcc_trigger_vendor_reset(int slot)
{
  uint *puVar1;
  uint uVar2;

  puVar1 = (uint *)(DAT_0804e2d8[slot] + 0x100);
  uVar2 = *puVar1;
  *puVar1 = uVar2 | 0x20000000;
  *puVar1 = uVar2 | 0x60000000;
  return;
}

/* orig: 0x0800bdf8 sdcc_set_clock_mode — modify clock control +0x3e bits */
void sdcc_set_clock_mode(int slot)
{
  *(ushort *)(DAT_0804e2d8[slot] + 0x3e) =
       (*(ushort *)(DAT_0804e2d8[slot] + 0x3e) & 0xfff8) + 4;
  return;
}

/* orig: 0x0800be10 sdcc_set_hs_mode — set/clear bit 2 of +0x2c */
void sdcc_set_hs_mode(int slot, char enable)
{
  *(byte *)(DAT_0804e2d8[slot] + 0x2c) =
       *(byte *)(DAT_0804e2d8[slot] + 0x2c) & 0xfb | enable << 2;
  return;
}

/* orig: 0x0800be2c sdcc_read_caps — read capability registers (+0x40, +0x44) */
void sdcc_read_caps(int slot, undefined4 *caps)
{
  *caps = *(undefined4 *)(DAT_0804e2d8[slot] + 0x40);
  caps[1] = *(undefined4 *)(DAT_0804e2d8[slot] + 0x44);
  return;
}

/* orig: 0x0800be54 sdcc_read_power_mode — read low nibble of +0x29 */
byte sdcc_read_power_mode(int slot)
{
  return *(byte *)(DAT_0804e2d8[slot] + 0x29) & 0xf;
}

/* orig: 0x0800beb8 sdcc_wait_pll_lock — wait for clock stable via +0xdc polling */
void sdcc_wait_pll_lock(int slot)
{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;

  iVar3 = 100000;
  do {
    uVar2 = *(uint *)(DAT_0804e2c8[slot] + 0xdc);
    if (uVar2 != 0) break;
    thunk_FUN_080199b4(1);
    bVar4 = iVar3 != 0;
    iVar3 = iVar3 + -1;
  } while (bVar4);
  *(uint *)(DAT_0804e2c8[slot] + 0xe4) = uVar2;
  if ((uVar2 & 3) == 0) {
    uVar1 = 4;
  }
  else {
    uVar1 = 1;
  }
  *(undefined4 *)(DAT_0804e2c8[slot] + 0xe8) = uVar1;
  iVar3 = 100000;
  do {
    if (*(int *)(DAT_0804e2c8[slot] + 0xdc) == 0) {
      return;
    }
    thunk_FUN_080199b4(1);
    bVar4 = iVar3 != 0;
    iVar3 = iVar3 + -1;
  } while (bVar4);
  return;
}

/* orig: 0x0800bf18 sdcc_set_int_enable — set/clear interrupt enable bits */
void sdcc_set_int_enable(int slot, uint mask, int enable)
{
  uint uVar1;

  uVar1 = *(uint *)(DAT_0804e2d8[slot] + 0x38) & ~mask;
  if (enable == 1) {
    uVar1 = uVar1 | mask;
  }
  *(uint *)(DAT_0804e2d8[slot] + 0x38) = uVar1;
  return;
}

/* orig: 0x0800bf34 sdcc_set_int_signal — set/clear interrupt signal bits with polling */
void sdcc_set_int_signal(int slot, uint mask, int enable)
{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;

  iVar3 = 100000;
  puVar1 = (uint *)(DAT_0804e2d8[slot] + 0x34);
  uVar2 = *puVar1;
  if (enable == 0) {
    *puVar1 = uVar2 & ~mask;
  }
  else {
    do {
      *puVar1 = uVar2 & ~mask | mask;
      uVar2 = *puVar1;
      if ((mask & ~uVar2) == 0) {
        return;
      }
      thunk_FUN_080199b4(1);
      bVar4 = iVar3 != 0;
      iVar3 = iVar3 + -1;
    } while (bVar4);
  }
  return;
}

/* orig: 0x0800bf74 sdcc_read_clock_stable — check if internal clock is stable */
uint sdcc_read_clock_stable(int slot)
{
  return ((uint)*(byte *)(DAT_0804e2d8[slot] + 0x2c) << 0x1e) >> 0x1f;
}

/* orig: 0x0800bf88 sdcc_set_led — set/clear bit 1 of +0x10c */
void sdcc_set_led(int slot, int enable)
{
  uint uVar1;

  uVar1 = *(uint *)(DAT_0804e2d8[slot] + 0x10c);
  if (enable == 1) {
    uVar1 = uVar1 | 2;
  }
  else {
    uVar1 = uVar1 & 0xfffffffd;
  }
  *(uint *)(DAT_0804e2d8[slot] + 0x10c) = uVar1;
  return;
}

/* orig: 0x0800c028 sdcc_set_dma_mode — configure DMA mode in +0x28 */
void sdcc_set_dma_mode(int slot, int mode)
{
  byte bVar1;

  bVar1 = *(byte *)(DAT_0804e2d8[slot] + 0x28);
  if (mode == 0) {
    bVar1 = bVar1 & 0xdd;
  }
  else if (mode == 1) {
    bVar1 = (bVar1 & 0xdd) + 2;
  }
  else {
    if (mode != 2) {
      return;
    }
    bVar1 = bVar1 | 0x20;
  }
  *(byte *)(DAT_0804e2d8[slot] + 0x28) = bVar1;
  return;
}

/* orig: 0x0800c058 sdcc_setup_caps — configure vendor capability registers */
void sdcc_setup_caps(int slot)
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;

  uVar1 = sdcc_get_slot_status(0);
  iVar4 = DAT_0804e2d8[slot];
  uVar2 = *(uint *)(iVar4 + 0x40);
  uVar3 = *(uint *)(iVar4 + 0x44);
  if ((uVar1 & 3) != 0) {
    uVar2 = uVar2 | 0x280000;
    uVar3 = uVar3 | 7;
  }
  if ((uVar1 & 1) == 0) {
    if ((int)(uVar1 << 0x1e) < 0) {
      uVar2 = uVar2 & 0x3bffffff | 0x3000000;
    }
  }
  else {
    uVar2 = uVar2 & 0x38ffffff | 0x44040000;
  }
  *(uint *)(iVar4 + 0x11c) = uVar2;
  *(uint *)(DAT_0804e2d8[slot] + 0x120) = uVar3;
  return;
}

/* orig: 0x0800c104 sdcc_set_bus_power — set/clear bit 0 of +0x29 */
void sdcc_set_bus_power(int slot, byte enable)
{
  *(byte *)(DAT_0804e2d8[slot] + 0x29) =
       *(byte *)(DAT_0804e2d8[slot] + 0x29) & 0xfe | enable;
  return;
}

/* orig: 0x0800c180 sdcc_set_voltage — write voltage bits of +0x29 */
void sdcc_set_voltage(int slot, byte voltage)
{
  *(byte *)(DAT_0804e2d8[slot] + 0x29) =
       *(byte *)(DAT_0804e2d8[slot] + 0x29) & 0xf1 | voltage;
  return;
}

/* orig: 0x0800bc64 sdcc_set_bus_width_bit — set/clear bit 0 of +0x78 */
void sdcc_set_bus_width_bit(int slot, int enable)
{
  uint uVar1;

  uVar1 = *(uint *)(DAT_0804e2c8[slot] + 0x78);
  if (enable == 1) {
    uVar1 = uVar1 | 1;
  }
  else {
    uVar1 = uVar1 & 0xfffffffe;
  }
  *(uint *)(DAT_0804e2c8[slot] + 0x78) = uVar1;
  return;
}

/* orig: 0x0800bc84 sdcc_init_bases — initialize register base addresses for slot 0 and 1 */
void sdcc_init_bases(void)
{
  if (DAT_0804e2c4 != '\x01') {
    DAT_0804e2c8[0] = 0x7824000;
    DAT_0804e2d0[0] = 0x7824000;
    DAT_0804e2c8[1] = 0x7864000;
    DAT_0804e2d0[1] = 0x7864000;
    DAT_0804e2d8[0] = 0x7824900;
    DAT_0804e2e0[0] = 0x7824900;
    DAT_0804e2d8[1] = 0x7864900;
    DAT_0804e2e0[1] = 0x7864900;
    DAT_0804e2c4 = '\x01';
  }
  return;
}

/* orig: 0x0800bccc sdcc_set_flow_control — set/clear bit 9 of config+4 */
void sdcc_set_flow_control(int slot, int enable)
{
  uint uVar1;

  uVar1 = *(uint *)(DAT_0804e2c8[slot] + 4);
  if (enable == 0) {
    uVar1 = uVar1 & 0xfffffdff;
  }
  else {
    uVar1 = uVar1 | 0x200;
  }
  *(uint *)(DAT_0804e2c8[slot] + 4) = uVar1;
  sdcc_enable_clock(slot);
  return;
}

/* orig: 0x0800bcec sdcc_set_bus_speed — set bus speed mode bits in config+4 */
void sdcc_set_bus_speed(int slot, int speed)
{
  uint uVar1;

  uVar1 = 0;
  if (speed != 0) {
    if (speed == 1) {
      uVar1 = 0x800;
    }
    else {
      if (speed != 2) {
        return;
      }
      uVar1 = 0xc00;
    }
  }
  *(uint *)(DAT_0804e2c8[slot] + 4) =
       *(uint *)(DAT_0804e2c8[slot] + 4) & 0xfffff3ff | uVar1;
  sdcc_enable_clock(slot);
  return;
}
