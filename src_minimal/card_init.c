/* card_init.c — eMMC card identification and initialization.
 *
 * These functions handle the eMMC card bring-up sequence:
 *   mmc_init_card -> mmc_config_bus -> mmc_identify_card
 *   -> mmc_set_bus_width -> mmc_set_speed -> mmc_finalize_init
 *
 * The programmer runs AFTER the bootloader has already initialized the eMMC,
 * so much of this code path is only exercised during handle_configure's
 * call to mmc_open_device. The device is typically already in transfer state.
 *
 * Source: src/fhprg/fhprg_80327f8.c
 */
#include "firehose.h"
#include "msm8909.h"
#include "usb.h"

/* Temporary trace: write short string to USB for debugging */
static void _trace(const char *s) {
  int n = 0;
  while (s[n]) n++;
  usb_write(s, n);
}

#define REG32(addr)  (*(volatile unsigned int *)(addr))

/* Sub-function forward declarations */
static uint csd_parse_mmc(int *resp, int dev);
static uint csd_get_rca(int dev);
static undefined4 cmd7_select_card(int dev, int select);
static undefined4 clock_set_divider(void);
static undefined4 clock_set_sdr_mode(void);

/* ---- SDCC1 clock configuration ---- */

/* Write SDCC1 GCC registers for a given frequency.
 * Frequency table from lk_src/platform/msm8909/msm8909-clock.c.
 * GPLL0 runs at ~787.2 MHz (L_VAL=41 * 19.2 MHz CXO). */
static void sdcc_set_clock_rate(uint freq_khz)
{
  uint cfg, m, n, d;

  if (freq_khz <= 400) {
    /* 400 KHz: CXO(0) / 12, M=1 N=4 dual-edge */
    m = 1; n = 0xFFFFFFFD; d = 0xFFFFFFFC;
    cfg = 0x2017;
  } else if (freq_khz <= 50000) {
    /* 50 MHz: GPLL0(1) / 16, no MND */
    m = 0; n = 0; d = 0;
    cfg = 0x011F;
  } else if (freq_khz <= 100000) {
    /* 100 MHz: GPLL0(1) / 8, no MND */
    m = 0; n = 0; d = 0;
    cfg = 0x010F;
  } else {
    /* 200 MHz: GPLL0(1) / 4, no MND */
    m = 0; n = 0; d = 0;
    cfg = 0x0107;
  }

  /* Write M/N/D registers */
  REG32(SDCC1_M) = m;
  REG32(SDCC1_N) = n;
  REG32(SDCC1_D) = d;

  /* Write CFG_RCGR: source + divider + mode */
  REG32(SDCC1_CFG_RCGR) = cfg;

  /* Trigger RCG update, poll until complete */
  REG32(SDCC1_CMD_RCGR) = REG32(SDCC1_CMD_RCGR) | CMD_UPDATE_BIT;
  while (REG32(SDCC1_CMD_RCGR) & CMD_UPDATE_BIT)
    ;
}

/* orig: 0x0800af10 — set GCC clock source mux.
 * Called from sdcc_clock_setup for lower speed ranges:
 *   1 → 400 kHz, 2 → 25 MHz (use 50 MHz), 3 → 50 MHz */
static void gcc_clock_mux_set(undefined4 mode)
{
  switch ((uint)mode) {
  case 1: sdcc_set_clock_rate(400); break;
  case 2: sdcc_set_clock_rate(50000); break;
  case 3: sdcc_set_clock_rate(50000); break;
  }
}

/* orig: 0x0800af38 — set GCC clock divider with source.
 * Called from sdcc_clock_setup for higher speed ranges.
 * freq = target frequency in kHz. */
static void gcc_clock_divider_set(undefined4 freq, undefined4 source)
{
  (void)source;
  sdcc_set_clock_rate((uint)freq);
}

/* Partition table: 32 entries × 3 words each.
 * In the original binary at 0x08059efc; in our build, allocated in globals.c.
 * Ghidra decompiled the loop bound as the hardcoded address 0x0805a071 —
 * we replace that with partition_table_end (= &DAT_08059efc + 96). */
extern uint DAT_08059efc[96];   /* partition table: 32 entries × 3 words */
#define partition_table_end  ((int *)(DAT_08059efc + 96))
extern int DAT_0804e2a8;        /* free partition slot counter (init: 0x20) */

/* MMIO timer for qtimer_init */
extern uint _DAT_004a1000;

/* ---- Simple utility functions ---- */

/* orig: 0x08032acc — get ADMA transfer mode (always 0x20 = ADMA2) */
static undefined4 sdcc_get_adma_mode(void)
{
  return 0x20;
}

/* orig: 0x08032ad0 — get max clock speed for slot */
static undefined4 sdcc_get_max_clock(int slot)
{
  if (slot != 0) {
    return 200000;
  }
  return 0x2b368;  /* 177000 kHz */
}

/* orig: 0x08032b0c — enable SDCC clock for slot.
 * slot = slot (0 for eMMC), enable = enable (1) / disable (0).
 * Configures RCG at 400 KHz and enables/disables branch clocks. */
static undefined4 sdcc_enable_slot(uint slot, uint enable)
{
  (void)slot;
  if (enable) {
    /* Configure RCG at 400 KHz identification rate */
    sdcc_set_clock_rate(400);

    /* Enable SDCC1 branch clocks */
    REG32(SDCC1_APPS_CBCR) = CBCR_BRANCH_ENABLE_BIT;
    while (REG32(SDCC1_APPS_CBCR) & CBCR_BRANCH_OFF_BIT)
      ;
    REG32(SDCC1_AHB_CBCR) = CBCR_BRANCH_ENABLE_BIT;
    while (REG32(SDCC1_AHB_CBCR) & CBCR_BRANCH_OFF_BIT)
      ;
  } else {
    /* Disable SDCC1 branch clocks */
    REG32(SDCC1_APPS_CBCR) = 0;
    REG32(SDCC1_AHB_CBCR) = 0;
  }
  return 0;
}

/* sdcc_clock_init — called from main() to enable SDCC1 clocks.
 * Must be called before any SDCC register access (0x0782xxxx). */
void sdcc_clock_init(void)
{
  sdcc_enable_slot(0, 1);
}

/* sdcc_pre_init_slot — pre-populate slot context so mmc_init_card skips
 * the full SDCC controller reinit.
 *
 * PBL has already initialized the eMMC and left it in transfer state.
 * mmc_init_card checks byte 0x15 of the slot context: if '\x01' (card
 * identified), it skips directly to return 1. But the slot context also
 * needs to have the device struct fields set up for subsequent functions
 * (mmc_read_ext_csd, mmc_setup_partitions, etc.).
 *
 * This function sets up:
 *   - SDCC register base addresses (sdcc_init_bases)
 *   - Slot context: init_state=1, slot number, self-pointer
 *   - Device struct: slot=0, card_type=6 (eMMC), sector_size=512
 *   - Device handle table entry (DAT_0804e2b8)
 *   - Hotplug descriptor stub (dev[0x24]) for sdcc_write_data
 *
 * Must be called after sdcc_clock_init() and before mmc_open_device().
 *
 * Slot context layout (0xBC bytes):
 *   +0x00 (word 0):  slot number
 *   +0x04 (word 1):  init phase (byte at +0x04)
 *   +0x0C (word 3):  device struct start (0x94 bytes)
 *     dev+0x00: slot number
 *     dev+0x04: cached partition (current)
 *     dev+0x08: card type (byte: 6=eMMC)
 *     dev+0x24: sector size
 *     dev+0x90: hotplug descriptor ptr (used by sdcc_write_data)
 *   +0x15 (byte):    init_state (0=none, 1=identified, 2=ready)
 *   +0x9C (word 0x27): self-pointer (back-reference to context)
 *
 * Hotplug descriptor (pointed to by dev[0x24], byte offset 0x90):
 *   sdcc_write_data reads from this struct at several offsets:
 *     [0]   = slot number (used by sdcc_pio_transfer, sdcc_adma_transfer)
 *     +0xA4 = ADMA mode flag (0=disabled → use PIO path)
 *     +0xAC = ADMA transfer function pointer (unused when +0xA4=0)
 *     +0xB0 = ADMA completion callback (unused when +0xA4=0)
 *   With +0xA4=0, sdcc_write_data uses PIO for data transfer.
 */

/* Hotplug descriptor stub — zeroed except [0]=slot.
 * Must be at least 0xB4 bytes (covers offset 0xB0). */
static uint hotplug_desc_stub[0xB4 / 4];

void sdcc_pre_init_slot(int slot)
{
  int *ctx = (int *)mmc_get_slot_context(slot);
  int *dev = ctx + 3;  /* device struct at context + 0x0C */

  /* Set up SDCC register bases first */
  sdcc_init_bases();

  /* Slot context header */
  ctx[0] = slot;
  *(char *)((char *)ctx + SLOT_CTX_INIT_STATE) = '\x01';  /* already identified */
  ctx[SLOT_CTX_SELF_PTR] = (int)ctx;

  /* Device struct — minimal fields for ext_csd and partition setup */
  dev[DEV_SLOT] = slot;
  dev[DEV_CUR_PARTITION] = 0;  /* user partition */
  *(char *)&dev[DEV_CARD_TYPE] = '\x06';  /* eMMC */
  dev[DEV_SECTOR_SIZE] = 0x200;  /* 512 bytes */

  /* Hotplug descriptor stub — slot number at [0], ADMA disabled (+0xA4=0).
   * sdcc_write_data dereferences dev[0x24] for PIO/ADMA transfer config. */
  hotplug_desc_stub[0] = slot;
  dev[DEV_EXT_CSD_PTR] = (int)hotplug_desc_stub;

  /* Register device in slot handle table */
  DAT_0804e2b8[slot] = (uint)(int)dev;
}

/* orig: 0x08032b64 — init qtimer and enable global timer */
static void sdcc_qtimer_init(void)
{
  qtimer_init();
  _DAT_004a1000 = 1;
  return;
}

/* orig: 0x08032b7c — release a partition slot entry */
static void sdcc_release_partition(int *entry)
{
  /* Clear the partition table entry and increment free counter */
  *entry = 0;
  entry[1] = 0;
  entry[2] = 0;
  DAT_0804e2a8 = DAT_0804e2a8 + 1;
  return;
}

/* ---- Clock/bus speed setup ---- */

/* orig: 0x08032a04 — configure clock source for slot.
 * mode: 1=disable, 2=reset, 4=set speed */
void sdcc_clock_setup(int slot, uint *freq, int mode)
{
  uint uVar3;

  if (mode == 1) {
    /* Clock disable — no-op (clocks managed by SBL) */
    return;
  }
  if (mode == 2) {
    /* HC reset via GCC */
    *(uint *)(slot * 0x40 + 0x1842000) = 1;
    thunk_FUN_080199b4(500);
    *(uint *)(slot * 0x40 + 0x1842000) = 0;
    return;
  }
  /* mode == 4: set clock speed */
  if (freq != (uint *)0x0) {
    uVar3 = *freq;
    if (uVar3 < 0x191) {
      gcc_clock_mux_set(1);
    }
    else if (uVar3 < 0x6591) {
      gcc_clock_mux_set(2);
    }
    else if (uVar3 <= 52000) {
      gcc_clock_mux_set(3);
    }
    else {
      undefined4 uVar1;
      undefined4 uVar2;
      if (uVar3 < 0x186a1) {
        uVar1 = 100000;
      }
      else if (slot == 0) {
        uVar1 = 0x2b368;
        uVar2 = 1;
        gcc_clock_divider_set(uVar1,uVar2);
        return;
      }
      else {
        uVar1 = 200000;
      }
      uVar2 = (slot == 0) ? 1 : 2;
      gcc_clock_divider_set(uVar1,uVar2);
      return;
    }
  }
  return;
}

/* orig: 0x08032f98 — set bus speed mode register */
static undefined4 sdcc_set_bus_speed_mode(int slot, undefined4 speed)
{
  int iVar1;
  undefined4 uVar2;

  switch(speed) {
  case 0:
    uVar2 = 0;
    break;
  case 1:
  case 5:
    uVar2 = 1;
    break;
  case 2:
  case 6:
    /* FUN_0800bd9c always returns 1 (SDR mode check) */
    uVar2 = 2;
    break;
  default:
    return 0;
  }
  sdcc_set_bus_speed(slot,uVar2);
  return 1;
}

/* ---- CSD/response parsing ---- */

/* orig: 0x080331e0 — get RCA (relative card address) after CMD3 */
static uint csd_get_rca(int dev)
{
  uint uVar1;
  int cmd[10];

  memset_zero(cmd, sizeof(cmd));
  cmd[0] = 3;                                      /* CMD3: SEND_RELATIVE_ADDR */
  *(undefined1 *)&cmd[2] = 1;                      /* resp_type: R1 */
  if ((*(char *)(dev + 8) == '\x02') || (*(char *)(dev + 8) == '\x06')) {
    uVar1 = 2;
    cmd[1] = 0x20000;                              /* MMC: assigned RCA */
    sdcc_send_cmd((int *)dev, cmd);
  }
  else {
    cmd[1] = 0;
    sdcc_send_cmd((int *)dev, cmd);
    uVar1 = (uint)cmd[3] >> 0x10;                  /* SD: RCA from response */
  }
  return uVar1;
}

/* orig: 0x080333ba — parse CSD for MMC cards */
static uint csd_parse_mmc(int *resp, int dev)
{
  uint uVar3;
  int iVar2;
  int iVar4;

  if ((resp == (int *)0x0) || (dev == 0)) {
    return 0;
  }
  *(ushort *)(dev + 0x3e) = (ushort)(byte)((uint)*resp >> 0x18);
  *(byte *)(dev + 0x5c) = (byte)((uint)(*resp << 0xe) >> 0x1e);
  *(ushort *)(dev + 0x40) = (ushort)(byte)((uint)*resp >> 8);
  *(char *)(dev + 0x42) = (char)*resp;
  uVar3 = resp[1];
  iVar2 = 4;
  do {
    iVar4 = dev + iVar2;
    iVar2 = iVar2 + -1;
    *(char *)(iVar4 + 0x42) = (char)uVar3;
    uVar3 = uVar3 >> 8;
  } while (0 < iVar2);
  *(char *)(dev + 0x47) = (char)((uint)resp[2] >> 0x18);
  *(undefined1 *)(dev + 0x48) = 0;
  *(char *)(dev + 0x49) = (char)((uint)resp[2] >> 0x10);
  *(uint *)(dev + 0x4c) = resp[2] << 0x10 | (uint)resp[3] >> 0x10;
  return 1;
}

/* csd_parse_sd removed — eMMC only */

/* orig: 0x0803351c — parse EXT_CSD byte stream into structured fields */
static undefined4 mmc_parse_ext_csd(byte *data, short *out)
{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint uVar5;

  if (out != (short *)0x0) {
    bVar1 = *data;
    *out = (ushort)bVar1 << 8;
    *out = CONCAT11(bVar1,data[1]);
    uVar5 = 2;
    iVar4 = 5;
    do {
      bVar1 = data[uVar5];
      uVar5 = uVar5 + 1 & 0xff;
      out[iVar4 + 1] = (ushort)bVar1 << 8;
      iVar3 = (int)(char)((char)iVar4 + -1);
      out[iVar4 + 1] = CONCAT11(bVar1,data[uVar5]);
      uVar5 = uVar5 + 1 & 0xff;
      iVar4 = iVar3;
    } while (-1 < iVar3);
    uVar5 = 0xe;
    iVar4 = 5;
    do {
      bVar1 = data[uVar5];
      cVar2 = (char)iVar4;
      *(byte *)((int)out + iVar4 + 0xe) = bVar1 >> 4;
      iVar4 = (int)(char)(cVar2 + -2);
      *(byte *)((int)out + (char)(cVar2 + -1) + 0xe) = bVar1 & 0xf;
      uVar5 = uVar5 + 1 & 0xff;
    } while (0 < iVar4);
    uVar5 = 0x12;
    *(byte *)(out + 10) = data[0x11];
    iVar4 = 5;
    do {
      bVar1 = data[uVar5];
      out[iVar4 + 0xb] = (ushort)bVar1 << 8;
      uVar5 = uVar5 + 1 & 0xff;
      out[iVar4 + 0xb] = CONCAT11(bVar1,data[uVar5]);
      iVar4 = (int)(char)((char)iVar4 + -1);
      uVar5 = uVar5 + 1 & 0xff;
    } while (-1 < iVar4);
    return 1;
  }
  return 0;
}

/* ---- Card init sub-steps ---- */

/* orig: 0x08034e78 — send CMD7 (SELECT_CARD) to move card to transfer state */
static undefined4 cmd7_select_card(int dev, int select)
{
  undefined4 uVar1;
  int cmd[10];

  memset_zero(cmd, sizeof(cmd));
  cmd[0] = 7;                                      /* CMD7: SELECT/DESELECT */
  cmd[1] = (select != 0) ? ((uint)*(ushort *)(dev + 10) << 0x10) : 0;
  *(undefined1 *)&cmd[2] = 1;                      /* resp_type: R1 */
  uVar1 = sdcc_send_cmd((int *)dev, cmd);
  if (select == 0) {
    uVar1 = 0;
  }
  return uVar1;
}

/* orig: 0x08033aac — send CMD10 (SEND_CID) and parse */
static int mmc_send_cid(int dev)
{
  int iVar1;
  int iVar2;
  int cmd[10];

  memset_zero(cmd, sizeof(cmd));
  cmd[0] = 10;                                     /* CMD10: SEND_CID */
  cmd[1] = (uint)*(ushort *)(dev + 10) << 0x10;    /* RCA */
  *(undefined1 *)&cmd[2] = 4;                      /* resp_type: R2 */
  iVar1 = sdcc_send_cmd((int *)dev, cmd);
  /* eMMC only: always MMC type '\x02' or '\x06' */
  if ((iVar1 == 0) &&
     (iVar2 = csd_parse_mmc(cmd + 3, dev), iVar2 == 0)) {
    iVar1 = 0x14;
  }
  return iVar1;
}

/* orig: 0x0803321e — extract CSD capacity/timing fields (stubbed) */
static void mmc_parse_csd_fields(int dev, undefined1 *csd, char *out)
{
  /* CSD field extraction into local struct.
   * Complex bit manipulation. Stubbed — capacity info is
   * also available from EXT_CSD which we read later. */
  (void)dev; (void)csd; (void)out;
  return;
}

/* orig: 0x08033d0a — calculate capacity from CSD fields (stubbed) */
static void mmc_calc_capacity(int dev, int c_size_mult, int read_bl_len, int c_size)
{
  /* Capacity calculation from CSD c_size/c_size_mult/read_bl_len.
   * Stubbed — capacity comes from EXT_CSD SEC_COUNT. */
  (void)dev; (void)c_size_mult; (void)read_bl_len; (void)c_size;
  return;
}

/* ---- Main card init functions ---- */

/* Slot context array — allocated in globals.c (was hardcoded at 0x08059cc8
 * in the original binary, but that address is outside our BSS). */
extern uint slot_contexts[];

/* orig: 0x08033ca0 mmc_get_slot_context — get per-slot context struct.
 * Returns pointer to per-slot context (0xBC bytes each). */
int mmc_get_slot_context(uint slot)
{
  if (2 < slot) {
    return 0;
  }
  return (int)((char *)slot_contexts + slot * 0xbc);
}

/* orig: 0x080345b8 mmc_config_bus — send CMD2 and parse CSD to get RCA */
int mmc_config_bus(int dev)
{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  int cmd[10];

  memset_zero(cmd, sizeof(cmd));
  cmd[0] = 2;                                      /* CMD2: ALL_SEND_CID */
  *(undefined1 *)&cmd[2] = 4;                      /* resp_type: R2 */
  iVar2 = sdcc_send_cmd((int *)dev, cmd);
  if (iVar2 == 0) {
    iVar3 = csd_parse_mmc(cmd + 3, dev);
    if (iVar3 == 0) {
      iVar2 = 0x14;
    }
    else {
      uVar1 = csd_get_rca(dev);
      *(undefined2 *)(dev + 10) = uVar1;
    }
  }
  return iVar2;
}

/* orig: 0x08033b30 mmc_identify_card — send CMD9, extract CSD capacity fields */
int mmc_identify_card(int dev)
{
  int iVar2;
  int iVar3;
  undefined1 uVar4;
  /* CSD parsed output struct — 0x28 bytes, contiguous for memset_zero.
   * Layout: [0x04]=speed_class, [0x08]=c_size_mult, [0x10]=c_size, [0x18]=read_bl_len */
  char csd_parsed[0x28];
  int cmd[10];  /* command struct for CMD9 */

  iVar2 = sdcc_get_card_status((int *)dev);
  iVar3 = 9;
  if (iVar2 == 3) {
    memset_zero(cmd, sizeof(cmd));
    cmd[0] = 9;                                    /* CMD9: SEND_CSD */
    cmd[1] = (uint)*(ushort *)(dev + 10) << 0x10;  /* RCA */
    *(undefined1 *)&cmd[2] = 4;                    /* resp_type: R2 */
    iVar3 = sdcc_send_cmd((int *)dev, cmd);
    if (iVar3 == 0) {
      memset_zero(csd_parsed, 0x28);
      mmc_parse_csd_fields(dev, (undefined1 *)(cmd + 3), csd_parsed);
      /* eMMC only: card type is always '\x02' (MMC) or '\x06' (eMMC) */
      uVar4 = 3;
      if (*(char *)(dev + 8) != '\x06') {
        mmc_calc_capacity(dev, (sbyte)csd_parsed[0x08],
                          (undefined1)csd_parsed[0x18], *(int *)(csd_parsed + 0x10));
      }
      if (csd_parsed[0x04] != '2') {
        *(undefined1 *)(dev + 0x5f) = 2;
        return 0;
      }
      *(undefined1 *)(dev + 0x5f) = uVar4;
    }
  }
  return iVar3;
}

/* orig: 0x08032dcc mmc_set_bus_width — configure clock speed based on card type */
void mmc_set_bus_width(undefined4 *dev, undefined4 speed_mode, undefined4 unused1, uint freq_hint)
{
  char cVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint local_18;

  uVar4 = *dev;
  cVar1 = *(char *)(dev + 2);
  local_18 = freq_hint;
  uVar2 = sdcc_get_max_clock(uVar4);
  uVar3 = 20000;
  switch(speed_mode) {
  case 0:
    uVar3 = 400;
    *(undefined1 *)((int)dev + 0x5f) = 2;
    break;
  case 1:
  case 2:
  case 3:
  case 5:
switchD_caseD_1:
    if ((cVar1 == '\x02') || (cVar1 == '\x06')) {
      if (*(char *)((int)dev + 0x5f) == '\x04') {
        uVar3 = 52000;
      }
      else if (*(char *)((int)dev + 0x5f) == '\x03') {
        uVar3 = 26000;
      }
      break;
    }
    goto LAB_08032e26;
  case 4:
    if ((cVar1 == '\x02') || (cVar1 == '\x06')) {
      *(undefined1 *)((int)dev + 0x5f) = 4;
      goto switchD_caseD_1;
    }
    if ((cVar1 != '\x01') && (cVar1 != '\x05')) break;
    *(undefined1 *)((int)dev + 0x5f) = 1;
LAB_08032e26:
    if ((cVar1 == '\x01') || (cVar1 == '\x05')) {
      if (*(char *)((int)dev + 0x5f) == '\x01') {
        uVar3 = 50000;
      }
      else {
        uVar3 = 25000;
      }
    }
    break;
  case 6:
    if (((cVar1 == '\x02') || (cVar1 == '\x06')) && (*(char *)((int)dev + 0x5f) == '\x04')) {
      uVar3 = 100000;
    }
    break;
  }
  /* eMMC mode clock setup */
  local_18 = uVar3;
  if (uVar2 <= uVar3) {
    local_18 = uVar2;
  }
  sdcc_clock_setup(uVar4,&local_18,4);
  dev[0x21] = local_18;
  return;
}

/* orig: 0x08032eac mmc_set_speed — switch to high-speed mode after init */
int mmc_set_speed(int *dev)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int cmd[10];

  iVar3 = *dev;
  iVar2 = cmd7_select_card((int)dev,1);
  if (iVar2 != 0) {
    return iVar2;
  }
  *(undefined1 *)((int)dev + 9) = 2;
  dev[0x16] = 1;
  memset_zero(cmd, sizeof(cmd));
  cmd[0] = 0x10;       /* CMD16 SET_BLOCKLEN */
  cmd[1] = 0x200;      /* arg: 512 bytes */
  cmd[2] = 1;          /* resp_type: R1 */
  iVar2 = sdcc_send_cmd(dev,(undefined4 *)cmd);
  if (iVar2 == 0) {
    dev[9] = 0x200;
    *(uint *)(DAT_0804e2c8[*dev] + 0x2c) =
         *(uint *)(DAT_0804e2c8[*dev] + 0x2c) & 0xfffe000f | 0x2000;
    sdcc_enable_clock(*dev);
  }
  cVar1 = (char)dev[2];
  if ((cVar1 == '\x02') || (cVar1 == '\x06')) {
    if (*(byte *)((int)dev + 0x5d) < 4) {
      sdcc_set_bus_speed_mode(iVar3,0);
    }
    else {
      /* FUN_08032fd0 — DDR mode init. For eMMC on MSM8909 we typically
       * use SDR mode. Stub to return 0 (success). */
      iVar2 = 0;
    }
  }
  /* SD card speed branch removed — eMMC only */
  /* Check card is in transfer state */
  iVar3 = sdcc_get_card_status(dev);
  if (iVar3 != 4) {
    iVar2 = 9;
  }
  return iVar2;
}

/* orig: 0x080335b4 mmc_finalize_init — disable clock and clear device state.
 *
 * dev+0x90 points to a "slot context" struct: [0]=slot_num, [1]=active_flag.
 * If this pointer wasn't populated during init (some init sub-functions we
 * call may not set it up), dereferencing it causes a data abort (DFSR=8). */
void mmc_finalize_init(int dev)
{
  int *piVar1;
  int iVar2;

  piVar1 = *(int **)(dev + 0x90);
  iVar2 = *piVar1;
  if (*(char *)(dev + 9) != '\0') {
    if ((char)piVar1[1] != '\0') {
      *(uint *)DAT_0804e2c8[iVar2] = *(uint *)DAT_0804e2c8[iVar2] & 0xfffffffe;
      sdcc_enable_clock(iVar2);
      sdcc_enable_slot(iVar2,0);
      *(undefined1 *)(piVar1 + 1) = 0;
    }
    *(undefined1 *)(dev + 8) = 0;
    *(undefined1 *)(dev + 9) = 0;
    *(undefined4 *)(dev + 0x84) = 0;
  }
  return;
}

/* orig: 0x080335fc mmc_release_slot — release device handle and partition entries */
void mmc_release_slot(undefined4 *handle)
{
  int *piVar1;
  int iVar2;

  piVar1 = (int *)*handle;
  if (piVar1 != (int *)0x0) {
    if ((char)((int *)*piVar1)[2] == '\0') {
      iVar2 = *(int *)*piVar1;
      for (piVar1 = (int *)&DAT_08059efc; piVar1 < partition_table_end; piVar1 = piVar1 + 3) {
        if (((int *)*piVar1 != (int *)0x0) && (*(int *)*piVar1 == iVar2)) {
          sdcc_release_partition(piVar1);
        }
        if (DAT_0804e2a8 == 0x20) break;
      }
    }
    else {
      sdcc_release_partition(piVar1);
    }
    *handle = 0;
  }
  return;
}

/* orig: 0x08033dfc mmc_classify_error — identify card type after reset.
 * Sends CMD0, CMD1/ACMD41 sequence to detect MMC vs SD vs SDHC. */
char mmc_classify_error(int *handle)
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int cmd[10];

  uVar2 = *(uint *)*handle;
  if (2 < uVar2) {
    return 0;
  }
  *(uint *)DAT_0804e2c8[uVar2] = *(uint *)DAT_0804e2c8[uVar2] | 1;
  sdcc_enable_clock(uVar2);
  if (*(char *)(*handle + 0x8c) == '\0') {
    *(uint *)(DAT_0804e2c8[uVar2] + 4) = *(uint *)(DAT_0804e2c8[uVar2] + 4) | 0x100;
    sdcc_enable_clock(uVar2);
    sdcc_set_flow_control(uVar2,0);
    thunk_FUN_080199b4(1000);
    sdcc_set_flow_control(uVar2,1);
    thunk_FUN_080199b4(1000);
    *(uint *)(DAT_0804e2c8[uVar2] + 4) =
         *(uint *)(DAT_0804e2c8[uVar2] + 4) & 0xffff3fff | 0x8000;
    sdcc_enable_clock(uVar2);
  }
  else {
    sdcc_set_led(uVar2,0);
    thunk_FUN_080199b4(1000);
    sdcc_set_led(uVar2,1);
  }
  mmc_set_bus_width((undefined4 *)*handle,0,0,0);
  uVar2 = sdcc_get_slot_status(uVar2);
  if ((uVar2 & 1) != 0) {
    /* MMC detection path: CMD0 (GO_IDLE) then CMD1 (SEND_OP_COND) loop */
    iVar4 = *handle;
    memset_zero(cmd, sizeof(cmd));
    /* CMD0: no response */
    sdcc_send_cmd((int *)iVar4,(undefined4 *)cmd);
    uVar2 = 0;
    while( true ) {
      memset_zero(cmd, sizeof(cmd));
      cmd[0] = 1;            /* CMD1 SEND_OP_COND */
      cmd[1] = 0x40ff8000;   /* arg: sector mode + voltage window */
      cmd[2] = 1;            /* resp_type: R3 (uses R1 code) */
      iVar1 = sdcc_send_cmd((int *)iVar4,(undefined4 *)cmd);
      if (iVar1 != 0) {
        return 0;
      }
      if ((int)cmd[3] < 0) break;  /* busy bit set = ready */
      thunk_FUN_080199b4(50000);
      uVar2 = uVar2 + 1;
      if (0x13 < uVar2) {
        return 0;
      }
    }
    if ((((uint)cmd[3] >> 0x1e & 1) != 0) && (((uint)cmd[3] >> 0x1d & 1) == 0)) {
      return 6;   /* sector-mode MMC */
    }
    return 2;      /* byte-mode MMC */
  }
  /* SD detection path: CMD0, CMD8, then CMD55+ACMD41 loop */
  iVar4 = *handle;
  uVar3 = 0xff8000;
  memset_zero(cmd, sizeof(cmd));
  /* CMD0: no response */
  sdcc_send_cmd((int *)iVar4,(undefined4 *)cmd);
  uVar2 = 0;
  do {
    memset_zero(cmd, sizeof(cmd));
    cmd[0] = 8;       /* CMD8 SEND_IF_COND */
    cmd[1] = 0x1aa;   /* arg: voltage + check pattern */
    cmd[2] = 1;       /* resp_type: R7 (uses R1 code) */
    iVar1 = sdcc_send_cmd((int *)iVar4,(undefined4 *)cmd);
    if (iVar1 == 0) {
      if (cmd[3] != 0x1aa) {   /* check pattern mismatch */
        return 0;
      }
      uVar3 = 0x40ff8000;   /* SD 2.0: request HCS */
      break;
    }
    thunk_FUN_080199b4(1000);
    uVar2 = uVar2 + 1;
  } while (uVar2 < 3);
  uVar2 = 0;
  do {
    /* CMD55 APP_CMD (prefix for ACMD) */
    memset_zero(cmd, sizeof(cmd));
    cmd[0] = 0x37;    /* CMD55 */
    cmd[2] = 1;       /* resp_type: R1 */
    iVar1 = sdcc_send_cmd((int *)iVar4,(undefined4 *)cmd);
    if (iVar1 != 0) {
      return 0;
    }
    /* ACMD41 SD_SEND_OP_COND */
    memset_zero(cmd, sizeof(cmd));
    cmd[0] = 0x29;    /* ACMD41 */
    cmd[1] = uVar3;   /* arg: HCS + voltage window */
    cmd[2] = 1;       /* resp_type: R3 (uses R1 code) */
    iVar1 = sdcc_send_cmd((int *)iVar4,(undefined4 *)cmd);
    if (iVar1 != 0) {
      return 0;
    }
    if (cmd[3] < 0) {   /* busy bit set = ready */
      if (cmd[3] << 1 < 0) {
        return 5;   /* SDHC */
      }
      return 1;     /* SD */
    }
    thunk_FUN_080199b4(50000);
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x14);
  return 0;
}

/* orig: 0x08034888 mmc_setup_partitions — check if partition entry exists */
undefined4 mmc_setup_partitions(int dev)
{
  int *piVar1;

  piVar1 = (int *)&DAT_08059efc;
  if (DAT_0804e2a8 != 0x20) {
    for (; piVar1 < partition_table_end; piVar1 = piVar1 + 3) {
      if ((*piVar1 != 0) && (*piVar1 == dev)) {
        return 1;
      }
    }
  }
  return 0;
}

/* orig: 0x08034cb4 mmc_read_ext_csd — allocate partition table entry */
int *mmc_read_ext_csd(short slot, int flags)
{
  int iVar1;
  int *piVar2;

  if (DAT_0804e2a8 < 1) {
    _trace("EC:full\r\n");  /* no free partition slots */
    return (int *)0x0;
  }
  for (piVar2 = (int *)&DAT_08059efc; piVar2 < partition_table_end; piVar2 = piVar2 + 3) {
    if (*piVar2 == 0) goto LAB_08034cd8;
  }
  _trace("EC:noslot\r\n");  /* all entries occupied */
  piVar2 = (int *)0x0;
LAB_08034cd8:
  if (piVar2 != (int *)0x0) {
    iVar1 = mmc_get_slot_context((int)slot);
    if (iVar1 == 0) {
      _trace("EC:noctx\r\n");  /* slot context not found */
      return (int *)0x0;
    }
    *piVar2 = iVar1 + 0xc;
    piVar2[1] = flags;
    DAT_0804e2a8 = DAT_0804e2a8 + -1;
  }
  return piVar2;
}


/* orig: 0x08034704 mmc_init_card — full card init with identification */
undefined4 mmc_init_card(int slot)
{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  bool bVar5;
  undefined4 local_28;

  local_28 = 0;
  piVar1 = (int *)mmc_get_slot_context(slot);
  if (piVar1 == (int *)0x0) {
    uVar3 = 0;
  }
  else {
    piVar1[0x27] = (int)piVar1;
    piVar4 = piVar1 + 3;
    bVar5 = *(char *)((int)piVar1 + 0x15) == '\x01';
    do {
      if (bVar5) goto LAB_08034876;
      bVar5 = true;
    } while (*(char *)((int)piVar1 + 0x15) == '\x02');
    if ((char)piVar1[1] == '\0') {
      memset_zero(piVar4,0x94);
      *piVar4 = slot;
      piVar1[0x27] = (int)piVar1;
      *piVar1 = slot;
      *(undefined1 *)(piVar1 + 1) = 1;
      *(undefined1 *)(piVar1 + 0x26) = 1;
    }
    sdcc_enable_slot(slot,1);
    sdcc_qtimer_init();
    local_28 = sdcc_get_max_clock(slot);
    sdcc_clock_setup(slot,&local_28,4);
    mmc_set_bus_width(piVar4,5,0,0);
    thunk_FUN_080199b4(1000);
    sdcc_init_bases();
    *(undefined4 *)(DAT_0804e2c8[slot] + 0xc) = 0;
    sdcc_enable_clock(slot);
    *(undefined4 *)(DAT_0804e2c8[slot] + 0x2c) = 0;
    sdcc_enable_clock(slot);
    *(undefined4 *)(DAT_0804e2c8[slot] + 0x38) = 0x18007ff;
    *(uint *)(DAT_0804e2c8[slot] + 4) = *(uint *)(DAT_0804e2c8[slot] + 4) | 0x200000;
    *(uint *)(DAT_0804e2c8[slot] + 4) = *(uint *)(DAT_0804e2c8[slot] + 4) & 0xfffff3ff;
    sdcc_enable_clock(slot);
    *(undefined4 *)(DAT_0804e2c8[slot] + 0x38) = 0x400000;
    *(undefined4 *)(DAT_0804e2c8[slot] + 0x3c) = 0;
    *piVar4 = slot;
    *(undefined1 *)((int)piVar1 + 0x15) = 1;
    iVar2 = sdcc_get_adma_mode();
    piVar1[0x19] = 1;
    piVar1[0x25] = iVar2;
    *(uint *)DAT_0804e2c8[slot] = *(uint *)DAT_0804e2c8[slot] | 1;
    sdcc_enable_clock(slot);
    sdcc_set_bus_width_bit(slot,1);
    sdcc_reset_data_line(slot,1);
    sdcc_setup_caps(slot);
    sdcc_read_caps(slot,piVar1 + 0x2d);
    sdcc_set_int_enable(slot,0x7ff003f,0);
    sdcc_set_int_signal(slot,0x7ff003f,1);
    sdcc_clear_status(slot,0x7ff003f);
    *(byte *)((int)piVar1 + 0x99) = (byte)((uint)(piVar1[0x2e] << 0x1d) >> 0x1f);
    bVar5 = -1 < piVar1[0x2d] << 0xc;
    if (bVar5) {
      *(undefined1 *)((int)piVar1 + 0x9a) = 0;
    }
    else {
      *(undefined1 *)((int)piVar1 + 0x9a) = 1;
    }
    sdcc_set_8bit_mode(slot,!bVar5);
LAB_08034876:
    uVar3 = 1;
  }
  return uVar3;
}
