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

#define REG32(addr)  (*(volatile unsigned int *)(addr))

/* Sub-function forward declarations */
static uint csd_parse_mmc();
static uint csd_get_rca();
static undefined4 cmd7_select_card();
static undefined4 clock_set_divider();
static undefined4 clock_set_sdr_mode();

/* ---- SDCC1 clock configuration ---- */

/* Write SDCC1 GCC registers for a given frequency.
 * Frequency table from lk_src/platform/msm8909/msm8909-clock.c.
 * GPLL0 runs at ~787.2 MHz (L_VAL=41 * 19.2 MHz CXO). */
static void sdcc_set_clock_rate(freq_khz)
uint freq_khz;
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
static void gcc_clock_mux_set(param_1)
undefined4 param_1;
{
  switch ((uint)param_1) {
  case 1: sdcc_set_clock_rate(400); break;
  case 2: sdcc_set_clock_rate(50000); break;
  case 3: sdcc_set_clock_rate(50000); break;
  }
}

/* orig: 0x0800af38 — set GCC clock divider with source.
 * Called from sdcc_clock_setup for higher speed ranges.
 * param_1 = target frequency in kHz. */
static void gcc_clock_divider_set(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  (void)param_2;
  sdcc_set_clock_rate((uint)param_1);
}

/* Slot context base: 0x8059cc8, 0xbc bytes per slot, 2 slots.
 * Partition table: DAT_08059efc (array of 3-word entries).
 * These are in the SDCC driver's BSS. */
extern uint DAT_08059efc[96];   /* partition table: 32 entries × 3 words */
extern int DAT_0804e2a8;        /* free partition slot counter */

/* MMIO timer for qtimer_init */
extern uint _DAT_004a1000;

/* ---- Simple utility functions ---- */

/* orig: 0x08032acc — get ADMA transfer mode (always 0x20 = ADMA2) */
static undefined4 sdcc_get_adma_mode()
{
  return 0x20;
}

/* orig: 0x08032ad0 — get max clock speed for slot */
static undefined4 sdcc_get_max_clock(param_1)
int param_1;
{
  if (param_1 != 0) {
    return 200000;
  }
  return 0x2b368;  /* 177000 kHz */
}

/* orig: 0x08032b0c — enable SDCC clock for slot.
 * param_1 = slot (0 for eMMC), param_2 = enable (1) / disable (0).
 * Configures RCG at 400 KHz and enables/disables branch clocks. */
static undefined4 sdcc_enable_slot(param_1, param_2)
uint param_1; uint param_2;
{
  (void)param_1;
  if (param_2) {
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
void sdcc_clock_init()
{
  sdcc_enable_slot(0, 1);
}

/* orig: 0x08032b64 — init qtimer and enable global timer */
static void sdcc_qtimer_init()
{
  qtimer_init();
  _DAT_004a1000 = 1;
  return;
}

/* orig: 0x08032b7c — release a partition slot entry */
static void sdcc_release_partition(param_1)
int * param_1;
{
  /* Clear the partition table entry and increment free counter */
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  DAT_0804e2a8 = DAT_0804e2a8 + 1;
  return;
}

/* ---- Clock/bus speed setup ---- */

/* orig: 0x08032a04 — configure clock source for slot.
 * param_3: 1=disable, 2=reset, 4=set speed */
void sdcc_clock_setup(param_1, param_2, param_3)
int param_1; uint * param_2; int param_3;
{
  uint uVar3;

  if (param_3 == 1) {
    /* Clock disable — no-op (clocks managed by SBL) */
    return;
  }
  if (param_3 == 2) {
    /* HC reset via GCC */
    *(uint *)(param_1 * 0x40 + 0x1842000) = 1;
    thunk_FUN_080199b4(500);
    *(uint *)(param_1 * 0x40 + 0x1842000) = 0;
    return;
  }
  /* param_3 == 4: set clock speed */
  if (param_2 != (uint *)0x0) {
    uVar3 = *param_2;
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
      else if (param_1 == 0) {
        uVar1 = 0x2b368;
        uVar2 = 1;
        gcc_clock_divider_set(uVar1,uVar2);
        return;
      }
      else {
        uVar1 = 200000;
      }
      uVar2 = (param_1 == 0) ? 1 : 2;
      gcc_clock_divider_set(uVar1,uVar2);
      return;
    }
  }
  return;
}

/* orig: 0x08032f98 — set bus speed mode register */
static undefined4 sdcc_set_bus_speed_mode(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 uVar2;

  switch(param_2) {
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
  sdcc_set_bus_speed(param_1,uVar2);
  return 1;
}

/* ---- CSD/response parsing ---- */

/* orig: 0x080331e0 — get RCA (relative card address) after CMD3 */
static uint csd_get_rca(param_1)
int param_1;
{
  uint uVar1;
  undefined4 local_30;
  undefined4 local_2c;
  undefined1 local_28;
  uint local_24;
  undefined4 local_14;
  undefined4 local_c;

  local_30 = 3;
  local_28 = 1;
  local_14 = 0;
  local_c = 0;
  if ((*(char *)(param_1 + 8) == '\x02') || (*(char *)(param_1 + 8) == '\x06')) {
    uVar1 = 2;
    local_2c = 0x20000;
    sdcc_send_cmd(param_1,&local_30);
  }
  else {
    local_2c = 0;
    sdcc_send_cmd(param_1,&local_30);
    uVar1 = local_24 >> 0x10;
  }
  return uVar1;
}

/* orig: 0x080333ba — parse CSD for MMC cards */
static uint csd_parse_mmc(param_1, param_2)
int * param_1; int param_2;
{
  uint uVar3;
  int iVar2;
  int iVar4;

  if ((param_1 == (int *)0x0) || (param_2 == 0)) {
    return 0;
  }
  *(ushort *)(param_2 + 0x3e) = (ushort)(byte)((uint)*param_1 >> 0x18);
  *(byte *)(param_2 + 0x5c) = (byte)((uint)(*param_1 << 0xe) >> 0x1e);
  *(ushort *)(param_2 + 0x40) = (ushort)(byte)((uint)*param_1 >> 8);
  *(char *)(param_2 + 0x42) = (char)*param_1;
  uVar3 = param_1[1];
  iVar2 = 4;
  do {
    iVar4 = param_2 + iVar2;
    iVar2 = iVar2 + -1;
    *(char *)(iVar4 + 0x42) = (char)uVar3;
    uVar3 = uVar3 >> 8;
  } while (0 < iVar2);
  *(char *)(param_2 + 0x47) = (char)((uint)param_1[2] >> 0x18);
  *(undefined1 *)(param_2 + 0x48) = 0;
  *(char *)(param_2 + 0x49) = (char)((uint)param_1[2] >> 0x10);
  *(uint *)(param_2 + 0x4c) = param_1[2] << 0x10 | (uint)param_1[3] >> 0x10;
  return 1;
}

/* csd_parse_sd removed — eMMC only */

/* orig: 0x0803351c — parse EXT_CSD byte stream into structured fields */
static undefined4 mmc_parse_ext_csd(param_1, param_2)
byte * param_1; short * param_2;
{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint uVar5;

  if (param_2 != (short *)0x0) {
    bVar1 = *param_1;
    *param_2 = (ushort)bVar1 << 8;
    *param_2 = CONCAT11(bVar1,param_1[1]);
    uVar5 = 2;
    iVar4 = 5;
    do {
      bVar1 = param_1[uVar5];
      uVar5 = uVar5 + 1 & 0xff;
      param_2[iVar4 + 1] = (ushort)bVar1 << 8;
      iVar3 = (int)(char)((char)iVar4 + -1);
      param_2[iVar4 + 1] = CONCAT11(bVar1,param_1[uVar5]);
      uVar5 = uVar5 + 1 & 0xff;
      iVar4 = iVar3;
    } while (-1 < iVar3);
    uVar5 = 0xe;
    iVar4 = 5;
    do {
      bVar1 = param_1[uVar5];
      cVar2 = (char)iVar4;
      *(byte *)((int)param_2 + iVar4 + 0xe) = bVar1 >> 4;
      iVar4 = (int)(char)(cVar2 + -2);
      *(byte *)((int)param_2 + (char)(cVar2 + -1) + 0xe) = bVar1 & 0xf;
      uVar5 = uVar5 + 1 & 0xff;
    } while (0 < iVar4);
    uVar5 = 0x12;
    *(byte *)(param_2 + 10) = param_1[0x11];
    iVar4 = 5;
    do {
      bVar1 = param_1[uVar5];
      param_2[iVar4 + 0xb] = (ushort)bVar1 << 8;
      uVar5 = uVar5 + 1 & 0xff;
      param_2[iVar4 + 0xb] = CONCAT11(bVar1,param_1[uVar5]);
      iVar4 = (int)(char)((char)iVar4 + -1);
      uVar5 = uVar5 + 1 & 0xff;
    } while (-1 < iVar4);
    return 1;
  }
  return 0;
}

/* ---- Card init sub-steps ---- */

/* orig: 0x08034e78 — send CMD7 (SELECT_CARD) to move card to transfer state */
static undefined4 cmd7_select_card(param_1, param_2)
int param_1; int param_2;
{
  undefined4 uVar1;
  undefined4 local_30;
  int local_2c;
  undefined1 local_28;
  undefined4 local_14;
  undefined4 local_c;

  if (param_2 == 0) {
    local_2c = 0;
  }
  else {
    local_2c = (uint)*(ushort *)(param_1 + 10) << 0x10;
  }
  local_30 = 7;
  local_28 = 1;
  local_14 = 0;
  local_c = 0;
  uVar1 = sdcc_send_cmd(param_1,&local_30);
  if (param_2 == 0) {
    uVar1 = 0;
  }
  return uVar1;
}

/* orig: 0x08033aac — send CMD10 (SEND_CID) and parse */
static int mmc_send_cid(param_1)
int param_1;
{
  int iVar1;
  int iVar2;
  undefined4 local_38;
  int local_34;
  undefined1 local_30;
  undefined1 auStack_2c[16];
  undefined4 local_1c;
  undefined4 local_14;

  local_38 = 10;
  local_34 = (uint)*(ushort *)(param_1 + 10) << 0x10;
  local_30 = 4;
  local_1c = 0;
  local_14 = 0;
  iVar1 = sdcc_send_cmd(param_1,&local_38);
  /* eMMC only: always MMC type '\x02' or '\x06' */
  if ((iVar1 == 0) &&
     (iVar2 = csd_parse_mmc(auStack_2c,param_1), iVar2 == 0)) {
    iVar1 = 0x14;
  }
  return iVar1;
}

/* orig: 0x0803321e — extract CSD capacity/timing fields (stubbed) */
static void mmc_parse_csd_fields(param_1, param_2, param_3)
int param_1; undefined1 * param_2; char * param_3;
{
  /* CSD field extraction into local struct.
   * Complex bit manipulation. Stubbed — capacity info is
   * also available from EXT_CSD which we read later. */
  (void)param_1; (void)param_2; (void)param_3;
  return;
}

/* orig: 0x08033d0a — calculate capacity from CSD fields (stubbed) */
static void mmc_calc_capacity(param_1, param_2, param_3, param_4)
int param_1; int param_2; int param_3; int param_4;
{
  /* Capacity calculation from CSD c_size/c_size_mult/read_bl_len.
   * Stubbed — capacity comes from EXT_CSD SEC_COUNT. */
  (void)param_1; (void)param_2; (void)param_3; (void)param_4;
  return;
}

/* ---- Main card init functions ---- */

/* orig: 0x08033ca0 mmc_get_slot_context — get per-slot context struct */
int mmc_get_slot_context(param_1)
uint param_1;
{
  if (2 < param_1) {
    return 0;
  }
  return param_1 * 0xbc + 0x8059cc8;
}

/* orig: 0x080345b8 mmc_config_bus — send CMD2 and parse CSD to get RCA */
int mmc_config_bus(param_1)
int param_1;
{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  undefined4 local_38;
  undefined4 local_34;
  undefined1 local_30;
  undefined1 auStack_2c[16];
  undefined4 local_1c;
  undefined4 local_14;

  local_38 = 2;
  local_30 = 4;
  local_34 = 0;
  local_1c = 0;
  local_14 = 0;
  iVar2 = sdcc_send_cmd(param_1,&local_38);
  if (iVar2 == 0) {
    iVar3 = csd_parse_mmc(auStack_2c,param_1);
    if (iVar3 == 0) {
      iVar2 = 0x14;
    }
    else {
      uVar1 = csd_get_rca(param_1);
      *(undefined2 *)(param_1 + 10) = uVar1;
    }
  }
  return iVar2;
}

/* orig: 0x08033b30 mmc_identify_card — send CMD9, extract CSD capacity fields */
int mmc_identify_card(param_1)
int param_1;
{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined1 uVar4;
  char local_68[4];
  char local_64;
  sbyte local_60;
  int local_58;
  undefined1 local_50;
  undefined4 local_40;
  int local_3c;
  undefined1 local_38;
  undefined1 auStack_34[16];
  undefined4 local_24;
  undefined4 local_1c;

  iVar2 = sdcc_get_card_status(param_1);
  iVar3 = 9;
  if (iVar2 == 3) {
    local_40 = 9;
    local_38 = 4;
    uVar4 = 0;
    local_24 = 0;
    local_1c = 0;
    local_3c = (uint)*(ushort *)(param_1 + 10) << 0x10;
    iVar3 = sdcc_send_cmd(param_1,&local_40);
    if (iVar3 == 0) {
      memset_zero(local_68,0x28);
      mmc_parse_csd_fields(param_1,auStack_34,local_68);
      /* eMMC only: card type is always '\x02' (MMC) or '\x06' (eMMC) */
      uVar4 = 3;
      if (*(char *)(param_1 + 8) != '\x06') {
        mmc_calc_capacity(param_1,local_60,local_50,local_58);
      }
      if (local_64 != '2') {
        *(undefined1 *)(param_1 + 0x5f) = 2;
        return 0;
      }
      *(undefined1 *)(param_1 + 0x5f) = uVar4;
    }
  }
  return iVar3;
}

/* orig: 0x08032dcc mmc_set_bus_width — configure clock speed based on card type */
void mmc_set_bus_width(param_1, param_2, param_3, param_4)
undefined4 * param_1; undefined4 param_2; undefined4 param_3; uint param_4;
{
  char cVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint local_18;

  uVar4 = *param_1;
  cVar1 = *(char *)(param_1 + 2);
  local_18 = param_4;
  uVar2 = sdcc_get_max_clock(uVar4);
  uVar3 = 20000;
  switch(param_2) {
  case 0:
    uVar3 = 400;
    *(undefined1 *)((int)param_1 + 0x5f) = 2;
    break;
  case 1:
  case 2:
  case 3:
  case 5:
switchD_caseD_1:
    if ((cVar1 == '\x02') || (cVar1 == '\x06')) {
      if (*(char *)((int)param_1 + 0x5f) == '\x04') {
        uVar3 = 52000;
      }
      else if (*(char *)((int)param_1 + 0x5f) == '\x03') {
        uVar3 = 26000;
      }
      break;
    }
    goto LAB_08032e26;
  case 4:
    if ((cVar1 == '\x02') || (cVar1 == '\x06')) {
      *(undefined1 *)((int)param_1 + 0x5f) = 4;
      goto switchD_caseD_1;
    }
    if ((cVar1 != '\x01') && (cVar1 != '\x05')) break;
    *(undefined1 *)((int)param_1 + 0x5f) = 1;
LAB_08032e26:
    if ((cVar1 == '\x01') || (cVar1 == '\x05')) {
      if (*(char *)((int)param_1 + 0x5f) == '\x01') {
        uVar3 = 50000;
      }
      else {
        uVar3 = 25000;
      }
    }
    break;
  case 6:
    if (((cVar1 == '\x02') || (cVar1 == '\x06')) && (*(char *)((int)param_1 + 0x5f) == '\x04')) {
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
  param_1[0x21] = local_18;
  return;
}

/* orig: 0x08032eac mmc_set_speed — switch to high-speed mode after init */
int mmc_set_speed(param_1)
int * param_1;
{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined1 local_48;
  undefined4 local_34;
  undefined4 local_2c;

  iVar3 = *param_1;
  iVar2 = cmd7_select_card((int)param_1,1);
  if (iVar2 != 0) {
    return iVar2;
  }
  *(undefined1 *)((int)param_1 + 9) = 2;
  param_1[0x16] = 1;
  local_48 = 1;
  local_34 = 0;
  local_50 = 0x10;
  uStack_4c = 0x200;
  local_2c = 0;
  iVar2 = sdcc_send_cmd(param_1,&local_50);
  if (iVar2 == 0) {
    param_1[9] = 0x200;
    *(uint *)((&DAT_0804e2c8)[*param_1] + 0x2c) =
         *(uint *)((&DAT_0804e2c8)[*param_1] + 0x2c) & 0xfffe000f | 0x2000;
    sdcc_enable_clock(*param_1);
  }
  cVar1 = (char)param_1[2];
  if ((cVar1 == '\x02') || (cVar1 == '\x06')) {
    if (*(byte *)((int)param_1 + 0x5d) < 4) {
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
  iVar3 = sdcc_get_card_status(param_1);
  if (iVar3 != 4) {
    iVar2 = 9;
  }
  return iVar2;
}

/* orig: 0x080335b4 mmc_finalize_init — disable clock and clear device state */
void mmc_finalize_init(param_1)
int param_1;
{
  int *piVar1;
  int iVar2;

  piVar1 = *(int **)(param_1 + 0x90);
  iVar2 = *piVar1;
  if (*(char *)(param_1 + 9) != '\0') {
    if ((char)piVar1[1] != '\0') {
      *(uint *)(&DAT_0804e2c8)[iVar2] = *(uint *)(&DAT_0804e2c8)[iVar2] & 0xfffffffe;
      sdcc_enable_clock(iVar2);
      sdcc_enable_slot(iVar2,0);
      *(undefined1 *)(piVar1 + 1) = 0;
    }
    *(undefined1 *)(param_1 + 8) = 0;
    *(undefined1 *)(param_1 + 9) = 0;
    *(undefined4 *)(param_1 + 0x84) = 0;
  }
  return;
}

/* orig: 0x080335fc mmc_release_slot — release device handle and partition entries */
void mmc_release_slot(param_1)
undefined4 * param_1;
{
  int *piVar1;
  int iVar2;

  piVar1 = (int *)*param_1;
  if (piVar1 != (int *)0x0) {
    if ((char)((int *)*piVar1)[2] == '\0') {
      iVar2 = *(int *)*piVar1;
      for (piVar1 = &DAT_08059efc; piVar1 < (int *)0x805a071; piVar1 = piVar1 + 3) {
        if (((int *)*piVar1 != (int *)0x0) && (*(int *)*piVar1 == iVar2)) {
          sdcc_release_partition(piVar1);
        }
        if (DAT_0804e2a8 == 0x20) break;
      }
    }
    else {
      sdcc_release_partition(piVar1);
    }
    *param_1 = 0;
  }
  return;
}

/* orig: 0x08033dfc mmc_classify_error — identify card type after reset.
 * Sends CMD0, CMD1/ACMD41 sequence to detect MMC vs SD vs SDHC. */
char mmc_classify_error(param_1)
int * param_1;
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 local_50;
  undefined4 local_4c;
  uint local_48;
  int local_44;
  undefined1 local_40;
  uint local_3c;
  undefined4 local_34;
  undefined4 local_2c;
  undefined4 local_24;

  uVar2 = *(uint *)*param_1;
  if (2 < uVar2) {
    return 0;
  }
  *(uint *)(&DAT_0804e2c8)[uVar2] = *(uint *)(&DAT_0804e2c8)[uVar2] | 1;
  sdcc_enable_clock(uVar2);
  if (*(char *)(*param_1 + 0x8c) == '\0') {
    *(uint *)((&DAT_0804e2c8)[uVar2] + 4) = *(uint *)((&DAT_0804e2c8)[uVar2] + 4) | 0x100;
    sdcc_enable_clock(uVar2);
    sdcc_set_flow_control(uVar2,0);
    thunk_FUN_080199b4(1000);
    sdcc_set_flow_control(uVar2,1);
    thunk_FUN_080199b4(1000);
    *(uint *)((&DAT_0804e2c8)[uVar2] + 4) =
         *(uint *)((&DAT_0804e2c8)[uVar2] + 4) & 0xffff3fff | 0x8000;
    sdcc_enable_clock(uVar2);
  }
  else {
    sdcc_set_led(uVar2,0);
    thunk_FUN_080199b4(1000);
    sdcc_set_led(uVar2,1);
  }
  mmc_set_bus_width((undefined4 *)*param_1,0);
  uVar2 = sdcc_get_slot_status(uVar2);
  if ((uVar2 & 1) != 0) {
    /* MMC detection path */
    iVar4 = *param_1;
    local_40 = 0;
    local_48 = 0;
    local_44 = 0;
    local_2c = 0;
    local_24 = 0;
    sdcc_send_cmd(iVar4,&local_48);
    uVar2 = 0;
    while( true ) {
      local_40 = 1;
      local_2c = 0;
      local_48 = 1;
      local_44 = 0x40ff8000;
      local_24 = 0;
      iVar1 = sdcc_send_cmd(iVar4,&local_48);
      if (iVar1 != 0) {
        return 0;
      }
      if ((int)local_3c < 0) break;
      thunk_FUN_080199b4(50000);
      uVar2 = uVar2 + 1;
      if (0x13 < uVar2) {
        return 0;
      }
    }
    if (((local_3c >> 0x1e & 1) != 0) && ((local_3c >> 0x1d & 1) == 0)) {
      return 6;
    }
    return 2;
  }
  /* SD detection path */
  iVar4 = *param_1;
  uVar3 = 0xff8000;
  local_48 = local_48 & 0xffffff00;
  local_50 = 0;
  local_4c = 0;
  local_34 = 0;
  local_2c = 0;
  sdcc_send_cmd(iVar4,&local_50);
  uVar2 = 0;
  do {
    local_48 = CONCAT31(_GHIDRA_FIELD(local_48, 1, uint24_t),1);
    local_50 = 8;
    local_4c = 0x1aa;
    local_34 = 0;
    local_2c = 0;
    iVar1 = sdcc_send_cmd(iVar4,&local_50);
    if (iVar1 == 0) {
      if (local_44 != 0x1aa) {
        return 0;
      }
      uVar3 = 0x40ff8000;
      break;
    }
    thunk_FUN_080199b4(1000);
    uVar2 = uVar2 + 1;
  } while (uVar2 < 3);
  uVar2 = 0;
  do {
    _GHIDRA_FIELD(local_48, 0, byte) = 1;
    local_50 = 0x37;
    local_4c = 0;
    local_34 = 0;
    local_2c = 0;
    iVar1 = sdcc_send_cmd(iVar4,&local_50);
    if (iVar1 != 0) {
      return 0;
    }
    local_48 = CONCAT31(_GHIDRA_FIELD(local_48, 1, uint24_t),1);
    local_50 = 0x29;
    local_34 = 0;
    local_2c = 0;
    local_4c = uVar3;
    iVar1 = sdcc_send_cmd(iVar4,&local_50);
    if (iVar1 != 0) {
      return 0;
    }
    if (local_44 < 0) {
      if (local_44 << 1 < 0) {
        return 5;
      }
      return 1;
    }
    thunk_FUN_080199b4(50000);
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x14);
  return 0;
}

/* orig: 0x08034888 mmc_setup_partitions — check if partition entry exists */
undefined4 mmc_setup_partitions(param_1)
int param_1;
{
  int *piVar1;

  piVar1 = &DAT_08059efc;
  if (DAT_0804e2a8 != 0x20) {
    for (; piVar1 < (int *)0x805a071; piVar1 = piVar1 + 3) {
      if ((*piVar1 != 0) && (*piVar1 == param_1)) {
        return 1;
      }
    }
  }
  return 0;
}

/* orig: 0x08034cb4 mmc_read_ext_csd — allocate partition table entry */
int * mmc_read_ext_csd(param_1, param_2)
short param_1; int param_2;
{
  int iVar1;
  int *piVar2;

  if (DAT_0804e2a8 < 1) {
    return (int *)0x0;
  }
  for (piVar2 = &DAT_08059efc; piVar2 < (int *)0x805a071; piVar2 = piVar2 + 3) {
    if (*piVar2 == 0) goto LAB_08034cd8;
  }
  piVar2 = (int *)0x0;
LAB_08034cd8:
  if (piVar2 != (int *)0x0) {
    iVar1 = mmc_get_slot_context((int)param_1);
    if (iVar1 == 0) {
      return (int *)0x0;
    }
    *piVar2 = iVar1 + 0xc;
    piVar2[1] = param_2;
    DAT_0804e2a8 = DAT_0804e2a8 + -1;
  }
  return piVar2;
}


/* orig: 0x08034704 mmc_init_card — full card init with identification */
undefined4 mmc_init_card(param_1)
int param_1;
{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  bool bVar5;
  undefined4 local_28;

  local_28 = 0;
  piVar1 = (int *)mmc_get_slot_context(param_1);
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
      *piVar4 = param_1;
      piVar1[0x27] = (int)piVar1;
      *piVar1 = param_1;
      *(undefined1 *)(piVar1 + 1) = 1;
      *(undefined1 *)(piVar1 + 0x26) = 1;
    }
    sdcc_enable_slot(param_1,1);
    sdcc_qtimer_init();
    local_28 = sdcc_get_max_clock(param_1);
    sdcc_clock_setup(param_1,&local_28,4);
    mmc_set_bus_width(piVar4,5);
    thunk_FUN_080199b4(1000);
    sdcc_init_bases();
    *(undefined4 *)((&DAT_0804e2c8)[param_1] + 0xc) = 0;
    sdcc_enable_clock(param_1);
    *(undefined4 *)((&DAT_0804e2c8)[param_1] + 0x2c) = 0;
    sdcc_enable_clock(param_1);
    *(undefined4 *)((&DAT_0804e2c8)[param_1] + 0x38) = 0x18007ff;
    *(uint *)((&DAT_0804e2c8)[param_1] + 4) = *(uint *)((&DAT_0804e2c8)[param_1] + 4) | 0x200000;
    *(uint *)((&DAT_0804e2c8)[param_1] + 4) = *(uint *)((&DAT_0804e2c8)[param_1] + 4) & 0xfffff3ff;
    sdcc_enable_clock(param_1);
    *(undefined4 *)((&DAT_0804e2c8)[param_1] + 0x38) = 0x400000;
    *(undefined4 *)((&DAT_0804e2c8)[param_1] + 0x3c) = 0;
    *piVar4 = param_1;
    *(undefined1 *)((int)piVar1 + 0x15) = 1;
    iVar2 = sdcc_get_adma_mode();
    piVar1[0x19] = 1;
    piVar1[0x25] = iVar2;
    *(uint *)(&DAT_0804e2c8)[param_1] = *(uint *)(&DAT_0804e2c8)[param_1] | 1;
    sdcc_enable_clock(param_1);
    sdcc_set_bus_width_bit(param_1,1);
    sdcc_reset_data_line(param_1,1);
    sdcc_setup_caps(param_1);
    sdcc_read_caps(param_1,piVar1 + 0x2d);
    /* FUN_08034508 — clock tuning, safe to skip if already in SDR mode */
    sdcc_set_int_enable(param_1,0x7ff003f,0);
    sdcc_set_int_signal(param_1,0x7ff003f,1);
    sdcc_clear_status(param_1,0x7ff003f);
    *(byte *)((int)piVar1 + 0x99) = (byte)((uint)(piVar1[0x2e] << 0x1d) >> 0x1f);
    bVar5 = -1 < piVar1[0x2d] << 0xc;
    if (bVar5) {
      *(undefined1 *)((int)piVar1 + 0x9a) = 0;
    }
    else {
      *(undefined1 *)((int)piVar1 + 0x9a) = 1;
    }
    sdcc_set_8bit_mode(param_1,!bVar5);
LAB_08034876:
    uVar3 = 1;
  }
  return uVar3;
}

