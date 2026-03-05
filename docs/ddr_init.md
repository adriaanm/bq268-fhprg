# DDR Initialization for MSM8909 Minimal Programmer

## Overview

The MSM8909 uses a BIMC (Bus Integrated Memory Controller) to interface with
LPDDR2/LPDDR3 SDRAM. DDR initialization is normally performed by SBL1 (Secondary
Boot Loader 1) before the application bootloader (aboot/LK) runs. In our minimal
firehose programmer, we must perform DDR init ourselves since we're loaded directly
by PBL via Sahara protocol, bypassing SBL1 entirely.

SDRAM at 0x80000000 is needed as a decompression buffer for the embedded aboot
payload (2 MB).

## Architecture

### Memory Map

| Region | Address | Size | Description |
|--------|---------|------|-------------|
| DDR blob code | 0x00220000 | ~10.5 KB | DDR driver functions (loaded by Sahara) |
| DDR blob data | 0x00223000 | ~2.4 KB | DDR driver BSS/data (loaded by Sahara) |
| BIMC registers | 0x00400000 | 256 KB | Bus Interconnect Memory Controller |
| DDR controller | 0x0044c000 | ~8 KB | BIMC SCMO/DPE/SHKE registers |
| GCC (clocks) | 0x01800000 | 512 KB | Global Clock Controller |
| OCIMEM | 0x08600000 | 128 KB | On-chip IMEM (shared, used for DDR config) |
| SDRAM | 0x80000000 | 512 MB | DDR memory (target) |

### DDR Blob (0x00220000)

The DDR driver is a self-contained blob loaded as two ELF segments by Sahara:
- CODE segment: 0x00220000, ~10516 bytes (IMEM_CODE region)
- DATA segment: 0x00223000, ~2416 bytes (IMEM_DATA region)

Key functions in the blob:

| Address | Function | Description |
|---------|----------|-------------|
| 0x00222780 | ddr_set_params | Validate DDR config, store pointers in driver data |
| 0x002224cc | ddr_init | Main DDR controller initialization |
| 0x00222484 | ddr_driver_init | Early driver setup (timing tables, register bases) |
| 0x00220b2c | ddr_init_channel | Per-channel PHY + controller init |
| 0x002225f4 | ddr_training_needed | Always returns 0 (training pre-done for this device) |
| 0x00222248 | ddr_get_info | Read DDR geometry/sizing post-init |
| 0x00221f3c | thunk_ddr_init | Thunk that calls ddr_init (boot config callback) |

### DDR Config Data (from CDT)

The original programmer embeds a CDT (Configuration Data Table) blob containing
device-specific DDR parameters. The DDR config is at CDT entry[1]:

- **CDT magic**: 0x544443 ("CDT")
- **DDR config offset**: 0x1c (28 bytes into CDT)
- **DDR config size**: 0x02f8 (760 bytes)
- **DDR config layout**:
  - `[0]` = 1 (version)
  - `[4]` = 0x44445200 ("DDR\0" magic)
  - `[12]` = number of interfaces
  - `[20]` = extended config pointer
  - `[24]` = start of per-interface config data
  - `[32]` = 5 (DDR type: LPDDR3)

The config is copied to IMEM at 0x08600190 before calling ddr_set_params().

### ddr_set_params (0x00222780) Details

Validates the config blob and stores pointers in driver data section:

```
Input:  r0 = config address (0x08600190), r1 = size (760)
Output: r0 = 1 (success) or 0 (failure)

Validation:
  - config != NULL
  - size != 0
  - config[0] == 1 (version)
  - config[1] == 0x44445200 (magic "DDR\0")

Stores:
  DAT_00223024 = config + 24  (per-interface config data pointer)
  DAT_00223030 = config[3]    (number of interfaces/chip selects)
  DAT_00223034 = 0xb8         (per-interface struct size, for LPDDR3 type 5)
  DAT_00223040 = config[5]    (extended config, conditional)
```

### ddr_init (0x002224cc) Details

The actual DDR controller initialization sequence:

1. Check init-done flag (`DAT_00223018`), return if already '\x01'
2. Call `ddr_driver_init` (0x00222484) — set up timing tables and register bases
3. Check channel 0 rank presence flags (`DAT_00223934`, `DAT_00223938`)
4. Call `ddr_init_channel(0, mode, clock)` (0x00220b2c) for channel 0
5. Check channel 1 rank presence flags (`DAT_0022393c`, `DAT_00223940`)
6. Call `ddr_init_channel(1, mode, clock)` for channel 1
7. Re-read rank presence from DDR controller status registers
8. Copy config structs to working location (`FUN_002225f8`)
9. Set init-done flag

Each `ddr_init_channel` call programs ~20 sub-functions that write BIMC registers:
- PHY initialization (4 steps)
- Refresh timer configuration
- BIMC timing registers (18-register block at 0x44c144)
- DDR mode register writes (MR commands to DRAM chip)
- DRAM geometry detection (ranks, density, bus width)
- Finalization and post-init config

## Required Init Sequence (Minimal)

### Phase 1: BIMC Clock Init (replacing FUN_0800ac84)

The BIMC DDR controller needs its clock tree enabled before any register access.
The original uses a complex clock driver; we hardcode the register writes.

Sequence:
1. Reset clock sources (write 0 to several GCC registers)
2. Configure GCC PLL USER_CTL registers
3. Enable 8 BIMC clock branches (set CBCR bit 0, poll bit 31)
4. Enable BIMC PLL (PLL1): write config, set MODE bits, poll lock
5. Switch RCG clock source to PLL1

GCC registers written:

| Address | Operation | Description |
|---------|-----------|-------------|
| 0x01800000 | Write 0 | GCC reset |
| 0x01813010 | Write 0 | GCC reset |
| 0x0181b000 | Write 0 | GCC reset |
| 0x01870000 | Write 0 | GCC reset |
| 0x01836000 | Write 0/1 | GCC_GPLL0_MODE (based on TCSR bit 20) |
| 0x01836004 | RMW | GCC_GPLL0 USER_CTL |
| 0x01845000 | Write 0/1 | GCC_BIMC_PLL_MODE |
| 0x01845004 | RMW | GCC_BIMC_PLL USER_CTL |
| 0x01831008 | CBCR enable | GCC BIMC branch clock |
| 0x0183100c | CBCR enable | GCC BIMC branch clock |
| 0x01831010 | CBCR enable | GCC BIMC branch clock |
| 0x01831014 | CBCR enable | GCC BIMC branch clock |
| 0x0183101c | CBCR enable | GCC BIMC branch clock |
| 0x0183201c | CBCR enable | GCC BIMC branch clock |
| 0x01832020 | CBCR enable | GCC BIMC branch clock |
| 0x01832024 | CBCR enable | GCC BIMC branch clock |
| 0x01831018 | RMW | RCG mux switch |
| 0x01832004+0/+4 | RMW | RCG source=PLL1, div=2 |
| 0x01837000+0/+4 | RMW | RCG source=PLL1, div=5 |

BIMC PLL1 config (from ROM at 0x0804d668):
- MODE base: 0x01821000
- L value: 41 (0x29)
- Config: 0x4001055b
- Alpha high: 0xaa000000
- Alpha low: 0x000000aa
- Lock sequence: MODE |= 2, wait 5us, MODE |= 6, poll lock, MODE |= 7

### Phase 2: DDR Config Setup

1. Embed the 760-byte DDR config blob (extracted from original binary CDT)
2. Copy to IMEM at 0x08600190
3. Call `ddr_set_params(0x08600190, 760)` at 0x00222780

### Phase 3: DDR Controller Init

Call `ddr_init()` at 0x002224cc. This runs entirely within the DDR blob
and programs BIMC registers at 0x0044c000-0x0044d0xx.

### Phase 4: ICB Config (Optional)

32 BIMC QoS/arbitration register writes. These tune bus bandwidth allocation
and are likely not required for basic DDR access. Can be added if DDR doesn't
work without them.

ICB register writes (all simple 32-bit stores to BIMC at 0x004xxxxx):

| Address | Value | Description |
|---------|-------|-------------|
| 0x00449210 | 0x00000001 | QoS config |
| 0x00450230 | 0x00000000 | Bandwidth config |
| 0x00408210 | 0x00000012 | DDR0 port 0 arb |
| 0x0040c210 | 0x00000012 | DDR0 port 1 arb |
| 0x00410210 | 0x00000012 | DDR1 port 0 arb |
| 0x00414210 | 0x00000012 | DDR1 port 1 arb |
| 0x00418210 | 0x80000012 | APP port arb |
| 0x0041c210 | 0x00000012 | APP port 1 arb |
| 0x00420210 | 0x00000012 | SYS port arb |
| 0x00408270 | 0x00043210 | Priority map low |
| 0x00408274 | 0x00043210 | Priority map high |
| 0x00408a04 | 0x00000014 | BKE_HEALTH_0 |
| 0x00408a08 | 0x00000064 | BKE_HEALTH_1 |
| 0x00408a24 | 0x0000ffce | BKE_HEALTH_2 |
| 0x00408a28 | 0x0000ff9c | BKE_HEALTH_3 |
| 0x00408a40 | 0x80000000 | BKE enable |
| 0x00408300 | 0x01000000 | Arbitration mode |
| 0x00408800 | 0x02000000 | Mode |
| 0x00408a00 | 0xfc000001 | BKE control |
| 0x00410a04 | 0x00000014 | DDR1 BKE_HEALTH_0 |
| 0x00410a08 | 0x00000064 | DDR1 BKE_HEALTH_1 |
| 0x00410a24 | 0x0000ffce | DDR1 BKE_HEALTH_2 |
| 0x00410a28 | 0x0000ff9c | DDR1 BKE_HEALTH_3 |
| 0x00410a40 | 0x80000000 | DDR1 BKE enable |
| 0x00410300 | 0x01000000 | DDR1 Arbitration mode |
| 0x00410800 | 0x02000000 | DDR1 Mode |
| 0x00410a00 | 0xfc000001 | DDR1 BKE control |
| 0x00400904 | 0x00000206 | SEG_CFG_0 |
| 0x00400908 | 0x00600060 | SEG_CFG_1 |
| 0x0040090c | 0x00270027 | SEG_CFG_2 |
| 0x00400940 | 0x00000010 | GLOBAL_CFG |
| 0x00400900 | 0x00000001 | SEG_ENABLE |

## Risks and Fallbacks

1. **Clock init order matters**: BIMC clocks must be running before any BIMC
   register access. If the PLL doesn't lock, DDR init will hang.

2. **PBL may have partial init done**: Some GCC clocks may already be enabled
   by PBL. The RMW operations should handle this gracefully.

3. **DDR config is device-specific**: The 760-byte config blob is specific to
   the BQ268 UdoSmart board's LPDDR3 chip. Different boards need different configs.

4. **ICB config may be required**: If DDR reads/writes hang or return garbage
   after successful ddr_init, try adding the ICB config writes.

## Verification

After DDR init, test with a simple memory write/read:
```c
volatile unsigned int *ddr = (volatile unsigned int *)0x80000000;
ddr[0] = 0xDEADBEEF;
ddr[1] = 0xCAFEBABE;
dsb();
if (ddr[0] == 0xDEADBEEF && ddr[1] == 0xCAFEBABE) {
    // DDR works — blink green LED
}
```

Use LED blink patterns to indicate success/failure at each phase.
