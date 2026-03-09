# MSM8909 Firehose Programmer Init Sequence

Hardware init spec derived from decompiling the original programmer (`fhprg_peek.bin`)
and verified against our minimal programmer (`src_minimal/`).

## Boot Flow Overview

```
PBL (ROM) → Sahara protocol → loads ELF segments to RAM → jumps to e_entry

processEntry_entry (ARM mode, 0x08008780)
  ├── MCR p15 VBAR = 0x08006000
  ├── FUN_08031f88 (sbl1_mc — main boot config loop)
  │   ├── read timetick, hw_id, watchdog, cache/mmu
  │   ├── spin: wait for DAT_08600944 != "GBDS"
  │   ├── qtimer_init, clock_init, boot_log
  │   ├── tlmm_init, efs_cookies, flash_dev_init, flash_target_init
  │   ├── cache/mmu enable
  │   ├── boot_config table processing
  │   │   └── boot_load_image (iterate boot config entries)
  │   └── sbl1_hw_init → DDR init (see below)
  │       sbl1_post_init → TSENS, PMIC, clock_post
  │       boot_qsee_exec → sbl1_main_ctl → firehose_dispatch
  └── ...
```

## DDR Init Sequence (sbl1_hw_init @ 0x08031840)

This is the critical path. The original programmer does:

### Step 1: Get DDR config parameters
```
FUN_08016020() → returns pointer to DDR config data (760 bytes)
FUN_08030b34(0x08600190, ...) → copy config to SYSTEM_IMEM
```

### Step 2: ddr_set_params
```
thunk_FUN_00222780(0x08600190, config_size)
  → DDR blob @ 0x00222780 (Thumb entry: 0x00222781)
  → Must return 1, else assert("sbl1_hw.c", 0x229)
```

### Step 3: DDR post-params (FUN_08031d18)
```
thunk_FUN_002225f4() → DDR blob query
If success + FUN_08014da8() == 0:
  thunk_FUN_002225e4(&local) → get geometry info
  FUN_08031d74(0x8081000, local) → copy to IMEM
  thunk_FUN_00222650(0x8081000, local) → validate geometry
```

### Step 4: DDR geometry query
```
thunk_FUN_00222248(stack_buffer)
  → DDR blob @ 0x00222248 (Thumb entry: 0x00222249)
  → Returns DDR geometry (56 bytes) into stack buffer
memcpy(another_buffer, geometry, 0x38)
```

### Step 5: Pre-DDR clock init (bimc_clock_init @ FUN_0800ac84)
```
FUN_0800ac40():  ← reset clock sources
  bit20 = TCSR_SOC_VERSION[20]   (read 0x01821000 bit 20)
  write bit20 → 0x01836000, 0x01845000
  write 0 → 0x01813010, 0x0181b000, 0x01870000, 0x01800000

FUN_0800ac84():
  1. PLL USER_CTL config
     0x01836004 &= 0x3f7ff; |= 0x20040  (GPLL0 USER_CTL)
     0x01845004 &= 0x217ff; |= 0x1e000  (BIMC PLL USER_CTL)

  2. Enable 8 BIMC branch clocks (CBCR set bit 0, poll bit 31 clear)
     0x01832024, 0x0183201c, 0x01832020  (DDR clocks)
     0x01831008, 0x0183100c, 0x01831010, 0x01831014, 0x0183101c  (BIMC clocks)

  3. BIMC MISC RCG switch (0x01831018)
     write: &= 0x3f0f00 | 0x500
     set update bit 9, poll until clear

  4. GFX RCG switch (via FUN_0800a54c with config struct from DAT_080398d0)

  Must return 1, else assert("sbl1_hw.c", 0x241)
```

### Step 6: ICB (Interconnect Bus) config
```
thunk_FUN_0800d330("/dev/icbcfg/boot")
  → DAL framework device attach + ICB arbitration config
  → 32 BIMC QoS register writes (0x004xxxxx range)
  → Must return 0, else assert("sbl1_hw.c", 0x246)
```

### Step 7: ddr_init (called later, from FUN_08031768)
```
thunk_FUN_002224cc(0)  ← clock_speed param
  → DDR blob @ 0x002224cc (Thumb entry: 0x002224cd)
  → Second geometry query after init
  → Additional blob calls: FUN_002225f4, FUN_00222088
```

## DDR Blob Callbacks

The DDR blob at 0x00220000 contains thunks that call back to hardcoded
addresses in the programmer's code space. All must be valid Thumb functions:

| Address    | Function    | Signature                         |
|------------|-------------|-----------------------------------|
| 0x08006b04 | memmove     | (dest, src, len) → overlap-safe   |
| 0x08006bdc | memcpy      | (dest, src, len) → forward copy   |
| 0x08006c40 | fast_memcpy | (dest, src, len) → aligned copy   |
| 0x08006d14 | memset_zero | (dest, len) → zero fill           |
| 0x08007edc | get_ttb     | () → TTBR0 & 0xFFFFC000          |

## DDR Blob Entry Points

All are Thumb code (bit 0 must be set when calling via BLX):

| Address    | Function          | Arguments                |
|------------|-------------------|--------------------------|
| 0x00222780 | ddr_set_params    | (config_addr, size)      |
| 0x002224cc | ddr_init          | (clock_speed)            |
| 0x00222248 | ddr_geometry_query| (out_buf_56bytes)        |
| 0x002225e4 | get_geometry_info | (&out_word)              |
| 0x002225f4 | ddr_query_flag    | () → 0 or 1             |
| 0x00222650 | validate_geometry | (imem_addr, size)        |
| 0x00222088 | ddr_post_init     | ()                       |
| 0x002223bc | get_ddr_info      | (out_buf)                |
| 0x00222448 | get_ddr_info2     | (out_buf)                |

## GPLL0 Enable

Both the original and minimal programmer use the vote register approach:

```
APCS_GPLL_ENA_VOTE (0x01845000) |= BIT(0)    ← vote for GPLL0
DSB
Poll GPLL0_MODE (0x01821000) BIT(30) until set  ← wait for lock
```

## Comparison: Original vs Minimal Programmer

### What the original does that we DON'T:

| Step | Original | Minimal | Risk |
|------|----------|---------|------|
| VBAR setup | MCR p15 c12 = 0x08006000 | MCR p15 c12 = _vectors | ✅ equivalent |
| HW ID read | FUN_080089e0(0x100) | skip | low |
| Watchdog init | FUN_08007ef0(0x55555555) | skip | low (PBL watchdog OK) |
| Cache/MMU init | FUN_0800a790(), FUN_0800b5e0() | skip | **medium** |
| GBDS wait | spin: DAT_08600944 != 0x53444247 | skip | low (SBL1-specific) |
| QTimer init | thunk_qtimer_init() | skip | low (we use timetick) |
| Clock init | FUN_08016918() (full GCC setup) | GPLL0 vote only | **POSSIBLE GAP** |
| Boot log | FUN_08016c80, FUN_08016adc | skip | none |
| TLMM init | FUN_08032280() | LED GPIOs only | low |
| Flash init | FUN_08018dec(), FUN_08018f7c() | skip (pre-DDR) | none |
| Cache enable | FUN_0800b604() | skip | **medium** |
| PLL USER_CTL | writes to 0x01836004, 0x01845004 | ✅ bimc_clock_init does this | ✅ |
| 8 BIMC CBCRs | FUN_0800b140() × 8 | ✅ bimc_branch_clocks_enable | ✅ |
| BIMC MISC switch | 0x01831018 config | ✅ bimc_clock_init Phase 5 | ✅ |
| GFX RCG switch | FUN_0800a54c(gfx_config) | ✅ bimc_clock_init Phase 6 | ✅ |
| GCC reset regs | write 0 → 4 reset addrs | ✅ bimc_clock_init Phase 1 | ✅ |
| ICB config | DAL attach + 32 BIMC QoS regs | icb_config() in main.c | ✅ |
| ddr_set_params | blob @ 0x00222780 | ✅ ddr_config_and_init | ✅ |
| ddr_post_params | FUN_08031d18 (geometry queries) | skip | low (non-essential) |
| bimc_clock_init | Before ddr_init | ✅ Before ddr_init | ✅ |
| ddr_init | blob @ 0x002224cc | ✅ ddr_config_and_init | ✅ |
| SDCC1 clocks | (done later in firehose init) | ✅ entry.S step 7 | ✅ |

### Key difference: Clock init ordering

**Original** (from `sbl1_hw_init`):
```
1. ddr_set_params       ← configure DDR params in IMEM
2. ddr_post_params      ← optional geometry query
3. bimc_clock_init      ← PLLs + branches + RCG switch
4. ICB config           ← BIMC bus arbitration
   ... (other SBL1 init steps) ...
5. ddr_init             ← actually initialize DDR
```

**Minimal** (from `entry.S`):
```
1. GPLL0 enable         ← ensure PLL is locked
2. bimc_branch_clocks   ← CBCR enables only (skip PLL reconfig)
3. ddr_set_params       ← configure DDR params in IMEM
4. ddr_init             ← actually initialize DDR
5. ICB config           ← BIMC bus arbitration (in main.c)
6. SDCC1 clocks         ← for eMMC access
```

### Potential issues in minimal programmer

1. **bimc_clock_init vs bimc_branch_clocks_enable**: The minimal programmer
   only calls `bimc_branch_clocks_enable` (CBCR enables only) because the
   full `bimc_clock_init` writes PLL config to `0x01821000` which is GPLL0_MODE,
   corrupting the running PLL. However, the original programmer calls the FULL
   `FUN_0800ac84` which includes:
   - PLL USER_CTL configuration (0x01836004, 0x01845004)
   - BIMC MISC RCG mux switch (0x01831018)
   - GFX RCG switch (0x01837000/0x01837004)

   **NOTE**: `bimc_clock_init` in entry.S DOES include these phases (Phases 4-6)
   in addition to the branch enables. But entry.S calls `bimc_branch_clocks_enable`
   which is the STRIPPED version. The full `bimc_clock_init` routine is present
   in entry.S but is NOT called from the main flow.

   **FIX**: The entry.S main flow calls `bl bimc_branch_clocks_enable` at line 184.
   It should call `bl bimc_clock_init` instead — but only if the GPLL0 corruption
   issue is resolved. The corruption happens because `BIMC_PLL_CONFIG_BASE` is
   defined as `0x01821000` which IS `GPLL0_MODE`. This is WRONG — the BIMC PLL
   is a separate PLL, not GPLL0. The address `0x01821000` is either:
   - A coincidence (BIMC PLL at same offset as GPLL0 in a different domain)
   - A hardware alias
   - A bug in our address analysis

   **The original programmer calls `FUN_0800ac40` which reads bit 20 from
   `0x01821000` (TCSR_SOC_VERSION in msm8909.h) and stores it. This register
   might NOT be GPLL0_MODE — it could be a TCSR register that's at the same
   address in the GCC address space.**

2. **Clock init before DDR**: The original does a full `FUN_08016918()` (clock
   framework init) before DDR. Our minimal programmer only votes for GPLL0.
   This is probably fine since PBL has basic clocks running.

3. **Cache/MMU**: The original enables cache/MMU before DDR init. Our minimal
   programmer runs without cache. This might affect DDR init timing but
   shouldn't cause failures.

4. **ICB config timing**: The original does ICB config BEFORE ddr_init (it's
   between bimc_clock_init and the ddr_init call). Our minimal does it AFTER
   in main.c. This ordering difference might matter.

## Critical Address Confusion: 0x01821000

The address `0x01821000` appears in TWO roles:

1. `GPLL0_MODE` = `CLK_CTL_BASE + 0x21000` = `0x01800000 + 0x21000` = `0x01821000`
2. `BIMC_PLL_CONFIG_BASE` = `0x01821000` (from entry.S Phase 4)
3. `TCSR_SOC_VERSION` = `0x01821000` (from msm8909.h)

The original programmer's `FUN_0800ac40()` does:
```c
bit20 = *(volatile uint32_t*)0x01821000;  // read "TCSR_SOC_VERSION" bit 20
bit20 = (bit20 >> 20) & 1;
*(volatile uint32_t*)0x01836000 = bit20;  // GCC_GPLL0_MODE_ALT
*(volatile uint32_t*)0x01845000 = bit20;  // APCS_GPLL_ENA_VOTE
```

Then `FUN_0800ac84` writes PLL config registers starting at `0x01821000`:
```c
*(0x01821000 + 0x04) = 0x4001055b;  // config_ctl
*(0x01821000 + 0x08) = 0x000000aa;  // alpha_l
*(0x01821000 + 0x0c) = 0xaa000000;  // alpha_h
*(0x01821000 + 0x10) = 41;          // L value
// Then PLL lock sequence on *(0x01821000)
```

**This IS writing to GPLL0_MODE (0x01821000).** The original programmer
reconfigures GPLL0 as part of BIMC clock init. It can do this because it's
running from OCIMEM (not DDR) and the clock framework handles the transition.

Our minimal programmer CANNOT do this safely because:
- We voted for GPLL0 via APCS_GPLL_ENA_VOTE and it's already locked
- Reconfiguring GPLL0 MODE/alpha/L registers while it's running corrupts it
- The original programmer's clock framework (FUN_08016918) may set up GPLL0
  differently or handle the transition gracefully

**RESOLUTION**: The minimal programmer should either:
1. NOT vote for GPLL0 first (let bimc_clock_init handle it), OR
2. Skip Phases 4-6 of bimc_clock_init (PLL reconfig + RCG switch) and only
   enable branch clocks — which is what `bimc_branch_clocks_enable` does

Option 2 is what we currently do, and DDR init IS confirmed working on hardware
(checkpoint GREEN #8 reached, DDR read/write verified at 0x80000000). The
question is whether the SDCC clocks or subsequent code has issues.

## SDCC1 Clock Configuration

**Original**: Done inside the firehose protocol init, using the full clock
framework with RCG configuration, MND dividers, and branch enables.

**Minimal** (entry.S step 7):
```
1. CFG_RCGR (0x01842008): SRC=CXO, DIV=1
2. CMD_RCGR (0x01842004): set update bit, poll until clear
3. AHB_CBCR (0x0184201C): enable, poll CLK_OFF clear
4. APPS_CBCR (0x01842018): enable, poll CLK_OFF clear
```

This configures SDCC1 at CXO rate (19.2 MHz) which is correct for initial
eMMC enumeration. Higher speeds are configured later by the eMMC driver.

## SDCC Register Architecture (MCI vs SDHCI)

The SDCC controller at `0x07824000` has two parallel register interfaces:
- **MCI** (legacy PL180) at base+0x000 — selected by `MCI_HC_MODE` bit 0 = 0
- **SDHCI** (standard host controller) at base+0x900 — selected by bit 0 = 1

The **original** firehose programmer uses SDHCI mode: `mmc_init_card` (FUN_08034704)
enables SDHCI via `sdcc_set_bus_width_bit(slot, 1)`, then all command dispatch goes
through SDHCI registers (HC_CMD, HC_NRML_INT_STS, HC_RESP).

The **minimal** programmer uses MCI legacy mode: `sdcc_pre_init_slot` clears
HC_MODE bit 0, following LK's `mmc_boot_init()`. Our command dispatch functions
(`sdcc_pre_cmd_hook`, `sdcc_cleanup`, `sdcc_setup_data_xfer`) use MCI registers
(MCI_CMD, MCI_STATUS, MCI_RESP_0).

MCI controller init sequence (in `sdcc_pre_init_slot`):
1. Disable SDHCI mode (`MCI_HC_MODE &= ~1`)
2. Software reset (`MCI_POWER |= 0x80`)
3. Clear MCI_CMD and MCI_DATA_CTL
4. Clear status, disable interrupts
5. Power on (`MCI_POWER = 0x03`)
6. Configure MCI_CLK: CLK_ENABLE(8), feedback(15), vendor bit(21)
7. Clear vendor status bit 22

`mmc_init_card` is bypassed via `init_state=1` — its SDHCI setup code has been
removed from the minimal build. Card identification is handled by `mmc_classify_error`
(CMD0→CMD1→CMD2→CMD3→CMD9→CMD7→CMD16), which uses MCI registers throughout.

## Summary: What Could Block the Minimal Programmer

If the minimal programmer gets stuck between DDR init and main():

1. **SDCC1 CBCR CLK_OFF not clearing**: If the SDCC1 clock source isn't
   properly configured, the CBCR enable won't take effect and the poll
   at `.Lahb_wait` / `.Lapps_wait` will spin forever.

   **Debug**: Add checkpoint between SDCC steps to identify which poll hangs.

2. **Exception during SDCC setup**: A data abort from accessing SDCC registers
   while clocks are off would jump to the exception handler (both LEDs on).

3. **DDR init returned but DDR isn't actually working**: The `ddr_test()` in
   main.c verifies DDR, but if entry.S hangs before reaching main(), we never
   get to verify. Add a DDR write/read test right after `ddr_config_and_init`
   returns (before SDCC setup).

4. **bimc_clock_init Phase 4 (PLL reconfig) needed for DDR**: Unlikely since
   DDR test passes, but if ddr_init succeeds but DDR is unstable, later
   accesses could fail silently.
