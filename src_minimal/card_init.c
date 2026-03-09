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
#include "globals.h"
#include "msm8909.h"

#define REG32(addr)  (*(volatile unsigned int *)(addr))

/* Sub-function forward declarations */
static uint csd_parse_mmc(int *resp, mmc_dev_t *dev);
static uint csd_get_rca(mmc_dev_t *dev);
static uint cmd7_select_card(mmc_dev_t *dev, int select);
/* ---- SDCC1 clock configuration ---- */

/* Write SDCC1 GCC registers for a given frequency.
 * Frequency table from lk_src/platform/msm8909/msm8909-clock.c.
 * GPLL0 runs at 800 MHz (lk_src/platform/msm8909/msm8909-clock.c: rate=800000000). */
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
    /* 200 MHz: GPLL0(1) / 4, no MND.
     * NOTE: LK uses cfg=0x0108 (GPLL0/4.5=177.77 MHz) for slot 0 max clock,
     * but original binary appears to use 0x0107 (GPLL0/4=200 MHz).
     * Matches original binary behavior. */
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
static void gcc_clock_mux_set(uint mode)
{
  switch (mode) {
  case 1: sdcc_set_clock_rate(400); break;
  case 2: sdcc_set_clock_rate(50000); break;
  case 3: sdcc_set_clock_rate(50000); break;
  }
}

/* orig: 0x0800af38 — set GCC clock divider with source.
 * Called from sdcc_clock_setup for higher speed ranges.
 * freq = target frequency in kHz. */
static void gcc_clock_divider_set(uint freq, uint source)
{
  (void)source;
  sdcc_set_clock_rate(freq);
}

/* Partition table: 32 entries, each an mmc_handle_t (12 bytes).
 * In the original binary at 0x08059efc; in our build, allocated in globals.c. */
extern mmc_handle_t partition_table[32];
#define partition_table_end  (&partition_table[32])
extern int sdcc_free_slots;        /* free partition slot counter (init: 0x20) */

/* MMIO timer for qtimer_init */
/* QTimer MMIO at 0x004a1000 — mapped by linker script */
volatile uint mmio_qtimer __attribute__((section(".mmio_qtimer"))) = 0;

/* Forward declarations */
static void sdcc_qtimer_init(void);

/* ---- Simple utility functions ---- */

/* orig: 0x08032ad0 — get max clock speed for slot */
static uint sdcc_get_max_clock(int slot)
{
  if (slot != 0)
    return 200000;
  return 177770;  /* 177770 kHz = 177.77 MHz = GPLL0(800)/4.5 (lk: F(177770000,gpll0,4.5,0,0)) */
}

/* orig: 0x08032b0c — enable SDCC clock for slot.
 * slot = slot (0 for eMMC), enable = enable (1) / disable (0).
 * Configures RCG at 400 KHz and enables/disables branch clocks. */
static uint sdcc_enable_slot(uint slot, uint enable)
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

/* sdcc_pre_init_slot — initialize SDCC controller and set up data structures.
 *
 * In EDL mode, PBL loads the programmer over USB and never touches SDCC/eMMC.
 * We must initialize the controller from power-on-reset state.
 *
 * The original binary (FUN_08034704) does: TLMM pad config → MCI register
 * config → HC_MODE |= 1 → SDHCI Software Reset → SDHCI vendor config.
 * Then mmc_classify_error reconfigures MCI_POWER/MCI_CLK before CMD0/CMD1.
 *
 * Our sequence (reordered so MCI config survives the reset):
 *   1. TLMM/SDCC pad config (original: FUN_08032b0c)
 *   2. Init qtimer
 *   3. HC_MODE |= 1 (enable SDHCI interface)
 *   4. SDHCI Software Reset (SDHCI+0x2F) — initializes command engine
 *      NOTE: this clears MCI registers (POWER, CLK, etc.) to defaults
 *   5. HC_MODE &= ~1 (switch back to MCI for our command dispatch)
 *   6. Clear MCI_CMD and MCI_DATA_CTL
 *   7. Configure MCI_CLK: CLK_ENABLE(8), FLOW_ENA(12), feedback(15), vendor(21)
 *   8. Clear status, disable interrupts
 *   9. MCI_POWER |= 1 (bit 0 only, matching original)
 *
 * Sets init_state=1 so mmc_init_card skips its SDHCI path.
 * Leaves card_type=0 so mmc_open_device falls through to mmc_classify_error
 * for full card identification (CMD0→CMD1→CMD2→CMD3→CMD7→CMD16).
 *
 * Must be called after sdcc_clock_init() and before mmc_open_device().
 */
void sdcc_pre_init_slot(int slot)
{
  int *ctx = (int *)mmc_get_slot_context(slot);
  mmc_dev_t *dev = (mmc_dev_t *)(ctx + 3);  /* device struct at context + 0x0C */

  /* Set up SDCC register bases */
  sdcc_init_bases();

  /* --- SDCC controller init ---
   *
   * Derived from the original binary (FUN_08034704 lines 2704-2735),
   * reordered so MCI config comes after the SDHCI reset (which clears
   * MCI registers).  See function header comment for full sequence.
   *
   * We reorder: do SDHCI reset first, then configure MCI registers,
   * so diagnostic CMD0/CMD1 work immediately after init.
   */

  /* 1. TLMM/SDCC pad config (original: FUN_08032b0c at line 2704). */
  {
    volatile uint *pad0 = (volatile uint *)0x0110a000;
    volatile uint *pad1 = (volatile uint *)0x01111000;
    *pad0 = (*pad0 & 0x6000) + 0x1fdb;
    *pad1 = *pad1 | 2;
  }

  /* 2. Init qtimer (original: FUN_08032b64 at line 2705) */
  sdcc_qtimer_init();

  /* 3. Enable SDHCI mode (original: FUN_0800bc64(slot,1) at line 2728). */
  MCI_REG(slot, MCI_HC_MODE) = MCI_REG(slot, MCI_HC_MODE) | 1;

  /* 4. SDHCI software reset (original: FUN_0800c154(slot,1) at line 2729).
   *    Write 1 to SDHCI Software Reset register (SDHCI_BASE + 0x2F),
   *    poll until the bit self-clears.  This properly initializes the
   *    SDCC command engine.  It also clears MCI registers (POWER, CLK,
   *    etc.) to defaults — so all MCI config must come AFTER this. */
  {
    int timeout = 100000;
    HC_REG8(slot, 0x2f) = 1;
    while (timeout-- > 0 && (HC_REG8(slot, 0x2f) & 1) != 0)
      delay_us(1);
  }

  /* 4b. Switch back to MCI mode for command dispatch.
   *     With HC_MODE[0]=1 (SDHCI), MCI commands don't clock out —
   *     CMD_ACTIVE stays stuck.  The original keeps SDHCI enabled
   *     but its command path may differ.  Our sdcc_send_cmd uses MCI
   *     registers, so we need MCI mode active. */
  MCI_REG(slot, MCI_HC_MODE) = MCI_REG(slot, MCI_HC_MODE) & ~1u;
  sdcc_enable_clock(slot);

  /* 5. Clear command and data state machines (original: lines 2711-2714) */
  MCI_REG(slot, MCI_CMD) = 0;
  sdcc_enable_clock(slot);
  MCI_REG(slot, MCI_DATA_CTL) = 0;
  sdcc_enable_clock(slot);

  /* 6. Clear all pending status bits (original: line 2715) */
  MCI_REG(slot, MCI_CLEAR) = 0x18007ff;

  /* 7. Configure MCI_CLK (original: lines 2716-2717 + mmc_classify_error):
   *    - bit 8:  CLK_ENABLE (clock output to card)
   *    - bit 12: FLOW_ENA (hardware flow control)
   *    - bit 15: SELECT_IN feedback clock
   *    - bit 21: Qualcomm vendor bit
   *    - bits 11:10: WIDEBUS = 00 (1-bit for identification) */
  {
    uint clk = MCI_REG(slot, MCI_CLK);
    clk |= 0x100;      /* bit 8:  CLK_ENABLE */
    clk |= 0x1000;     /* bit 12: FLOW_ENA */
    clk |= 0x8000;     /* bit 15: SELECT_IN feedback clock */
    clk |= 0x200000;   /* bit 21: vendor-specific */
    clk &= ~0xC00u;    /* bits 11:10: WIDEBUS = 00 */
    MCI_REG(slot, MCI_CLK) = clk;
    sdcc_enable_clock(slot);
  }

  /* 8. Clear vendor status bit 22, disable interrupts (original: lines 2719-2720) */
  MCI_REG(slot, MCI_CLEAR) = 0x400000;
  MCI_REG(slot, MCI_INT_MASK0) = 0;

  /* 9. Power: set bit 0 (original: line 2726 + mmc_classify_error line 653). */
  MCI_REG(slot, MCI_POWER) = MCI_REG(slot, MCI_POWER) | 1;
  sdcc_enable_clock(slot);

  /* --- Data structure setup --- */

  ctx[0] = slot;
  *(uint8_t *)(ctx + 1) = 1;  /* mark context as allocated (original line 2701) */
  *(char *)((char *)ctx + SLOT_CTX_INIT_STATE) = '\x01';  /* skip mmc_init_card full path */
  ctx[0x19] = 1;               /* flags (original line 2724) */
  ctx[SLOT_CTX_SELF_PTR] = (int)ctx;  /* hotplug desc = ctx itself */

  /* Device struct — card_type left as 0 so mmc_open_device falls through
   * to mmc_classify_error for full card identification. */
  dev->slot = slot;

  /* Register device in slot handle table */
  sdcc_device_table[slot] = (uint)dev;
}

/* orig: 0x08032b64 — init qtimer and enable global timer */
static void sdcc_qtimer_init(void)
{
  qtimer_init();
  mmio_qtimer = 1;
}

/* orig: 0x08032b7c — release a partition slot entry */
static void sdcc_release_partition(mmc_handle_t *entry)
{
  /* Clear the partition table entry and increment free counter */
  entry->dev_ptr = 0;
  entry->partition_idx = 0;
  entry->flags = 0;
  sdcc_free_slots++;
}

/* ---- Clock/bus speed setup ---- */

/* orig: 0x08032a04 — configure clock source for slot.
 * mode: 1=disable, 2=reset, 4=set speed */
void sdcc_clock_setup(int slot, uint *freq, int mode)
{
  if (mode == 1)
    return;  /* Clock disable — no-op (clocks managed by SBL) */

  if (mode == 2) {
    /* HC reset via GCC */
    *(uint *)(slot * 0x40 + 0x1842000) = 1;
    delay_us(500);
    *(uint *)(slot * 0x40 + 0x1842000) = 0;
    return;
  }
  /* mode == 4: set clock speed */
  if (freq == NULL)
    return;

  uint target_khz = *freq;
  if (target_khz < 0x191) {
    gcc_clock_mux_set(1);
  } else if (target_khz < 0x6591) {
    gcc_clock_mux_set(2);
  } else if (target_khz <= 52000) {
    gcc_clock_mux_set(3);
  } else {
    uint rate;
    uint source;
    if (target_khz < 0x186a1) {
      rate = 100000;
    } else if (slot == 0) {
      gcc_clock_divider_set(0x2b368, 1);
      return;
    } else {
      rate = 200000;
    }
    source = (slot == 0) ? 1 : 2;
    gcc_clock_divider_set(rate, source);
  }
}

/* orig: 0x08032f98 — set bus speed mode register */
static uint sdcc_set_bus_speed_mode(int slot, uint speed)
{
  uint hw_mode;

  switch (speed) {
  case 0:
    hw_mode = 0;
    break;
  case 1:
  case 5:
    hw_mode = 1;
    break;
  case 2:
  case 6:
    /* FUN_0800bd9c always returns 1 (SDR mode check) */
    hw_mode = 2;
    break;
  default:
    return 0;
  }
  sdcc_set_bus_speed(slot, hw_mode);
  return 1;
}

/* ---- CSD/response parsing ---- */

/* orig: 0x080331e0 — get RCA (relative card address) after CMD3 */
static uint csd_get_rca(mmc_dev_t *dev)
{
  uint rca;
  mmc_cmd_t cmd;

  memset_zero(&cmd, sizeof(cmd));
  cmd.cmd_num = 3;                                 /* CMD3: SEND_RELATIVE_ADDR */
  *(uint8_t *)&cmd.resp_type = 1;                  /* resp_type: R1 */
  if ((dev->card_type == 2) || (dev->card_type == 6)) {
    rca = 2;
    cmd.cmd_arg = 0x20000;                         /* MMC: assigned RCA */
    sdcc_send_cmd(dev, &cmd);
  } else {
    cmd.cmd_arg = 0;
    sdcc_send_cmd(dev, &cmd);
    rca = (uint)cmd.resp[0] >> 0x10;               /* SD: RCA from response */
  }
  return rca;
}

/* orig: 0x080333ba — parse CSD for MMC cards */
static uint csd_parse_mmc(int *resp, mmc_dev_t *dev)
{
  uint word;
  int i;
  uint8_t *base;

  if (resp == NULL || dev == NULL)
    return 0;

  dev->csd_spec_vers = (ushort)(byte)((uint)*resp >> 0x18);
  dev->speed_class = (byte)((uint)(*resp << 0xe) >> 0x1e);
  dev->speed_mode = (ushort)(byte)((uint)*resp >> 8);
  dev->mfr_id[0] = (char)*resp;
  word = resp[1];
  /* Write bytes 1..4 of mfr_id from resp[1] (little-endian scatter) */
  base = (uint8_t *)dev;
  i = 4;
  do {
    base[i + 0x42] = (char)word;
    i--;
    word >>= 8;
  } while (i > 0);
  /* mfr_id[5] from resp[2] high byte */
  dev->mfr_id[5] = (char)((uint)resp[2] >> 0x18);
  dev->mfr_id[6] = 0;
  dev->product_rev = (char)((uint)resp[2] >> 0x10);
  dev->gpp_attr[0] = resp[2] << 0x10 | (uint)resp[3] >> 0x10;
  return 1;
}

/* csd_parse_sd removed — eMMC only */

/* ---- Card init sub-steps ---- */

/* orig: 0x08034e78 — send CMD7 (SELECT_CARD) to move card to transfer state */
static uint cmd7_select_card(mmc_dev_t *dev, int select)
{
  mmc_cmd_t cmd;

  memset_zero(&cmd, sizeof(cmd));
  cmd.cmd_num = 7;                                 /* CMD7: SELECT/DESELECT */
  cmd.cmd_arg = (select != 0) ? ((uint)dev->rca << 0x10) : 0;
  *(uint8_t *)&cmd.resp_type = 1;                  /* resp_type: R1 */
  uint ret = sdcc_send_cmd(dev, &cmd);
  if (select == 0)
    ret = 0;
  return ret;
}

/* orig: 0x0803321e — extract CSD capacity/timing fields (stubbed) */
static void mmc_parse_csd_fields(mmc_dev_t *dev, uint8_t *csd, char *out)
{
  /* CSD field extraction into local struct.
   * Complex bit manipulation. Stubbed — capacity info is
   * also available from EXT_CSD which we read later. */
  (void)dev; (void)csd; (void)out;
}

/* orig: 0x08033d0a — calculate capacity from CSD fields (stubbed) */
static void mmc_calc_capacity(mmc_dev_t *dev, int c_size_mult, int read_bl_len, int c_size)
{
  /* Capacity calculation from CSD c_size/c_size_mult/read_bl_len.
   * Stubbed — capacity comes from EXT_CSD SEC_COUNT. */
  (void)dev; (void)c_size_mult; (void)read_bl_len; (void)c_size;
}

/* ---- Main card init functions ---- */

/* Slot context array — allocated in globals.c (was hardcoded at 0x08059cc8
 * in the original binary, but that address is outside our BSS). */
extern uint slot_contexts[];

/* orig: 0x08033ca0 mmc_get_slot_context — get per-slot context struct.
 * Returns pointer to per-slot context (0xBC bytes each). */
int mmc_get_slot_context(uint slot)
{
  if (slot > 2)
    return 0;
  return (int)((char *)slot_contexts + slot * 0xbc);
}

/* orig: 0x080345b8 mmc_config_bus — send CMD2 and parse CSD to get RCA */
int mmc_config_bus(mmc_dev_t *dev)
{
  mmc_cmd_t cmd;

  memset_zero(&cmd, sizeof(cmd));
  cmd.cmd_num = 2;                                 /* CMD2: ALL_SEND_CID */
  *(uint8_t *)&cmd.resp_type = 4;                  /* resp_type: R2 */
  int ret = sdcc_send_cmd(dev, &cmd);
  if (ret == 0) {
    if (csd_parse_mmc(cmd.resp, dev) == 0) {
      ret = 0x14;
    } else {
      dev->rca = csd_get_rca(dev);
    }
  }
  return ret;
}

/* orig: 0x08033b30 mmc_identify_card — send CMD9, extract CSD capacity fields */
int mmc_identify_card(mmc_dev_t *dev)
{
  /* CSD parsed output struct — 0x28 bytes, contiguous for memset_zero.
   * Layout: [0x04]=speed_class, [0x08]=c_size_mult, [0x10]=c_size, [0x18]=read_bl_len */
  char csd_parsed[0x28];
  mmc_cmd_t cmd;

  int card_state = sdcc_get_card_status(dev);
  int ret = 9;
  if (card_state == 3) {
    memset_zero(&cmd, sizeof(cmd));
    cmd.cmd_num = 9;                               /* CMD9: SEND_CSD */
    cmd.cmd_arg = (uint)dev->rca << 0x10;          /* RCA */
    *(uint8_t *)&cmd.resp_type = 4;                /* resp_type: R2 */
    ret = sdcc_send_cmd(dev, &cmd);
    if (ret == 0) {
      memset_zero(csd_parsed, 0x28);
      mmc_parse_csd_fields(dev, (uint8_t *)cmd.resp, csd_parsed);
      /* eMMC only: card type is always '\x02' (MMC) or '\x06' (eMMC) */
      uint8_t grade = 3;
      if (dev->card_type != 6)
        mmc_calc_capacity(dev, (sbyte)csd_parsed[0x08],
                          (uint8_t)csd_parsed[0x18], *(int *)(csd_parsed + 0x10));
      if (csd_parsed[0x04] != '2') {
        dev->speed_grade = 2;
        return 0;
      }
      dev->speed_grade = grade;
    }
  }
  return ret;
}

/* orig: 0x08032dcc mmc_set_bus_width — configure clock speed based on card type */
void mmc_set_bus_width(mmc_dev_t *dev, uint speed_mode, uint unused1, uint freq_hint)
{
  char ct = (char)dev->card_type;
  uint slot_num = dev->slot;
  uint clk_khz = freq_hint;
  uint max_clk = sdcc_get_max_clock(slot_num);
  uint target = 20000;

  switch (speed_mode) {
  case 0:
    target = 400;
    dev->speed_grade = 2;
    break;
  case 1:
  case 2:
  case 3:
  case 5:
switchD_caseD_1:
    if ((ct == '\x02') || (ct == '\x06')) {
      if (dev->speed_grade == 4)
        target = 52000;
      else if (dev->speed_grade == 3)
        target = 26000;
      break;
    }
    goto LAB_08032e26;
  case 4:
    if ((ct == '\x02') || (ct == '\x06')) {
      dev->speed_grade = 4;
      goto switchD_caseD_1;
    }
    if ((ct != '\x01') && (ct != '\x05')) break;
    dev->speed_grade = 1;
LAB_08032e26:
    if ((ct == '\x01') || (ct == '\x05')) {
      if (dev->speed_grade == 1)
        target = 50000;
      else
        target = 25000;
    }
    break;
  case 6:
    if (((ct == '\x02') || (ct == '\x06')) && (dev->speed_grade == 4))
      target = 100000;
    break;
  }
  /* eMMC mode clock setup */
  clk_khz = target;
  if (max_clk <= target)
    clk_khz = max_clk;
  sdcc_clock_setup(slot_num, &clk_khz, 4);
  dev->clock_khz = clk_khz;
}

/* orig: 0x08032eac mmc_set_speed — switch to high-speed mode after init */
int mmc_set_speed(mmc_dev_t *dev)
{
  char ct;
  int ret;
  mmc_cmd_t cmd;

  int slot_num = dev->slot;
  ret = cmd7_select_card(dev, 1);
  if (ret != 0)
    return ret;

  dev->init_phase = 2;
  dev->custom_sector = 1;
  memset_zero(&cmd, sizeof(cmd));
  cmd.cmd_num = 0x10;       /* CMD16 SET_BLOCKLEN */
  cmd.cmd_arg = 0x200;      /* arg: 512 bytes */
  cmd.resp_type = 1;        /* resp_type: R1 */
  ret = sdcc_send_cmd(dev, &cmd);
  if (ret == 0) {
    dev->sector_size = 0x200;
    MCI_REG(dev->slot, MCI_DATA_CTL) =
         (MCI_REG(dev->slot, MCI_DATA_CTL) & 0xfffe000f) | 0x2000;
    sdcc_enable_clock(dev->slot);
  }
  ct = (char)dev->card_type;
  if ((ct == '\x02') || (ct == '\x06')) {
    if (dev->bus_width_sup < 4)
      sdcc_set_bus_speed_mode(slot_num, 0);
    else
      /* FUN_08032fd0 — DDR mode init. For eMMC on MSM8909 we typically
       * use SDR mode. Stub to return 0 (success). */
      ret = 0;
  }
  /* SD card speed branch removed — eMMC only */
  /* Check card is in transfer state */
  int card_state = sdcc_get_card_status(dev);
  if (card_state != 4)
    ret = 9;
  return ret;
}

/* orig: 0x080335b4 mmc_finalize_init — disable clock and clear device state.
 *
 * dev+0x90 points to a "slot context" struct: [0]=slot_num, [1]=active_flag.
 * If this pointer wasn't populated during init (some init sub-functions we
 * call may not set it up), dereferencing it causes a data abort (DFSR=8). */
void mmc_finalize_init(mmc_dev_t *dev)
{
  int *desc = (int *)dev->hotplug_desc;
  int slot_num = *desc;

  if (dev->init_phase != 0) {
    if ((char)desc[1] != 0) {
      MCI_REG(slot_num, MCI_POWER) = MCI_REG(slot_num, MCI_POWER) & 0xfffffffe;
      sdcc_enable_clock(slot_num);
      sdcc_enable_slot(slot_num, 0);
      *(uint8_t *)(desc + 1) = 0;
    }
    dev->card_type = 0;
    dev->init_phase = 0;
    dev->clock_khz = 0;
  }
}

/* orig: 0x080335fc mmc_release_slot — release device handle and partition entries.
 * Takes a pointer to a handle variable (double-pointer pattern):
 *   *handle_ptr = the handle (partition entry pointer as uint)
 *   The function zeroes *handle_ptr on release. */
void mmc_release_slot(mmc_handle_t **handle_ptr)
{
  mmc_handle_t *h = *handle_ptr;

  if (h == NULL)
    return;

  if (((mmc_dev_t *)h->dev_ptr)->card_type == 0) {
    int slot_num = ((mmc_dev_t *)h->dev_ptr)->slot;
    mmc_handle_t *pt;
    for (pt = partition_table; pt < partition_table_end; pt++) {
      if (pt->dev_ptr != 0 && (int)((mmc_dev_t *)pt->dev_ptr)->slot == slot_num)
        sdcc_release_partition(pt);
      if (sdcc_free_slots == 0x20) break;
    }
  } else {
    sdcc_release_partition(h);
  }
  *handle_ptr = 0;
}

/* orig: 0x08033dfc mmc_classify_error — identify card type after reset.
 * Sends CMD0, CMD1/ACMD41 sequence to detect MMC vs SD vs SDHC. */
char mmc_classify_error(mmc_handle_t *handle)
{
  int ret;
  uint slot_num;
  uint ocr_arg;
  int dev_ptr;
  mmc_cmd_t cmd;

  slot_num = ((mmc_dev_t *)handle->dev_ptr)->slot;
  if (slot_num > 2)
    return 0;

  MCI_REG(slot_num, MCI_POWER) = MCI_REG(slot_num, MCI_POWER) | 1;
  sdcc_enable_clock(slot_num);
  if (((mmc_dev_t *)handle->dev_ptr)->spi_mode == 0) {
    MCI_REG(slot_num, MCI_CLK) = MCI_REG(slot_num, MCI_CLK) | 0x100;
    sdcc_enable_clock(slot_num);
    sdcc_set_flow_control(slot_num, 0);
    delay_us(1000);
    sdcc_set_flow_control(slot_num, 1);
    delay_us(1000);
    MCI_REG(slot_num, MCI_CLK) =
         (MCI_REG(slot_num, MCI_CLK) & 0xffff3fff) | 0x8000;
    sdcc_enable_clock(slot_num);
  } else {
    sdcc_set_led(slot_num, 0);
    delay_us(1000);
    sdcc_set_led(slot_num, 1);
  }
  mmc_set_bus_width((mmc_dev_t *)handle->dev_ptr, 0, 0, 0);
  uint status = sdcc_get_slot_status(slot_num);
  if ((status & 1) != 0) {
    /* MMC detection path: CMD0 (GO_IDLE) then CMD1 (SEND_OP_COND) loop */
    dev_ptr = handle->dev_ptr;
    memset_zero(&cmd, sizeof(cmd));
    /* CMD0: no response */
    sdcc_send_cmd((mmc_dev_t *)dev_ptr, &cmd);
    uint retry = 0;
    while (1) {
      memset_zero(&cmd, sizeof(cmd));
      cmd.cmd_num = 1;            /* CMD1 SEND_OP_COND */
      cmd.cmd_arg = 0x40ff8000;   /* arg: sector mode + voltage window */
      cmd.resp_type = 1;          /* resp_type: R3 (uses R1 code) */
      ret = sdcc_send_cmd((mmc_dev_t *)dev_ptr, &cmd);
      if (ret != 0)
        return 0;
      if ((int)cmd.resp[0] < 0) break;  /* busy bit set = ready */
      delay_us(50000);
      retry++;
      if (retry > 0x13)
        return 0;
    }
    if ((((uint)cmd.resp[0] >> 0x1e & 1) != 0) && (((uint)cmd.resp[0] >> 0x1d & 1) == 0))
      return 6;   /* sector-mode MMC */
    return 2;      /* byte-mode MMC */
  }
  /* SD detection path: CMD0, CMD8, then CMD55+ACMD41 loop */
  dev_ptr = handle->dev_ptr;
  ocr_arg = 0xff8000;
  memset_zero(&cmd, sizeof(cmd));
  /* CMD0: no response */
  sdcc_send_cmd((mmc_dev_t *)dev_ptr, &cmd);
  uint retry = 0;
  do {
    memset_zero(&cmd, sizeof(cmd));
    cmd.cmd_num = 8;       /* CMD8 SEND_IF_COND */
    cmd.cmd_arg = 0x1aa;   /* arg: voltage + check pattern */
    cmd.resp_type = 1;     /* resp_type: R7 (uses R1 code) */
    ret = sdcc_send_cmd((mmc_dev_t *)dev_ptr, &cmd);
    if (ret == 0) {
      if (cmd.resp[0] != 0x1aa)   /* check pattern mismatch */
        return 0;
      ocr_arg = 0x40ff8000;   /* SD 2.0: request HCS */
      break;
    }
    delay_us(1000);
    retry++;
  } while (retry < 3);
  retry = 0;
  do {
    /* CMD55 APP_CMD (prefix for ACMD) */
    memset_zero(&cmd, sizeof(cmd));
    cmd.cmd_num = 0x37;    /* CMD55 */
    cmd.resp_type = 1;     /* resp_type: R1 */
    ret = sdcc_send_cmd((mmc_dev_t *)dev_ptr, &cmd);
    if (ret != 0)
      return 0;
    /* ACMD41 SD_SEND_OP_COND */
    memset_zero(&cmd, sizeof(cmd));
    cmd.cmd_num = 0x29;    /* ACMD41 */
    cmd.cmd_arg = ocr_arg; /* arg: HCS + voltage window */
    cmd.resp_type = 1;     /* resp_type: R3 (uses R1 code) */
    ret = sdcc_send_cmd((mmc_dev_t *)dev_ptr, &cmd);
    if (ret != 0)
      return 0;
    if (cmd.resp[0] < 0) {   /* busy bit set = ready */
      if (cmd.resp[0] << 1 < 0)
        return 5;   /* SDHC */
      return 1;     /* SD */
    }
    delay_us(50000);
    retry++;
  } while (retry < 0x14);
  return 0;
}

/* orig: 0x08034888 mmc_setup_partitions — check if partition entry exists */
uint mmc_setup_partitions(mmc_dev_t *dev)
{
  if (sdcc_free_slots != 0x20) {
    mmc_handle_t *pt;
    for (pt = partition_table; pt < partition_table_end; pt++) {
      if (pt->dev_ptr != 0 && pt->dev_ptr == (uint)dev)
        return 1;
    }
  }
  return 0;
}

/* orig: 0x08034cb4 mmc_alloc_handle — allocate partition table entry */
mmc_handle_t *mmc_alloc_handle(short slot, int partition_idx)
{
  if (sdcc_free_slots < 1)
    return NULL;

  mmc_handle_t *h;
  for (h = partition_table; h < partition_table_end; h++) {
    if (h->dev_ptr == 0)
      break;
  }
  if (h >= partition_table_end)
    h = NULL;

  if (h != NULL) {
    int ctx = mmc_get_slot_context((int)slot);
    if (ctx == 0)
      return NULL;
    h->dev_ptr = ctx + 0xc;
    h->partition_idx = partition_idx;
    sdcc_free_slots--;
  }
  return h;
}


/* orig: 0x08034704 mmc_init_card — card initialization entry point.
 *
 * Called by mmc_open_device.  In the original binary, this does full SDHCI-mode
 * controller setup (HC_MODE=1, RESET_ALL, capabilities, interrupts, 8-bit bus).
 * We bypass all of that via init_state=1 (set by sdcc_pre_init_slot), since our
 * command dispatch uses MCI registers which require MCI legacy mode (HC_MODE=0).
 *
 * The full SDHCI init code from the original (FUN_08034704 lines 2696-2746) has
 * been removed — see git history or src/fhprg/fhprg_80327f8.c for reference.
 */
uint mmc_init_card(int slot)
{
  int *ctx = (int *)mmc_get_slot_context(slot);

  if (ctx == NULL)
    return 0;

  ctx[0x27] = (int)ctx;  /* self-pointer for hotplug descriptor */

  /* sdcc_pre_init_slot sets init_state=1.  Return immediately. */
  if (*(char *)((int)ctx + 0x15) == 1 || *(char *)((int)ctx + 0x15) == 2)
    return 1;

  /* init_state is 0 — should not happen if sdcc_pre_init_slot was called.
   * Return failure rather than falling into SDHCI init that would break
   * our MCI-mode command dispatch. */
  return 0;
}
