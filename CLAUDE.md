# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Goal

Build a **minimal Qualcomm programmer** (msm8909, ARM 32-bit) that runs in EDL mode via Sahara protocol and provides a USB diagnostic console with eMMC read/write, verified flashing, and memory dump capabilities. The ultimate goal is to write the aboot partition, bypassing hardware write protection (CMD28 WP groups).

The programmer is written in Rust (no_std, bare metal ARM Thumb2) and loaded via PBL's Sahara/EDL mode. It inherits the PBL's USB session and page tables.

## Archived Code

The `archive/` directory (not tracked in git) contains previous work:
- `archive/src_fhprg/` — Decompiled original firehose programmer (Ghidra output, reference)
- `archive/src_minimal/` — Previous C implementation of the minimal programmer
- `archive/tools/` — Various analysis/comparison/emulation tools from the decompilation effort
- `archive/client/` — Go-based firehose client
- `archive/bins/` — Binary dumps (PBL, GPT, splash, patched programmers)

When debugging hardware issues, the decompiled original in `archive/src_fhprg/` remains the authoritative reference for how the original programmer drives this SoC.

## Workflow

- **Commit regularly** — after each logical change, stage and commit. Don't let changes accumulate across multiple tasks.
- **Embody what you learn in the source** — when analyzing or debugging, capture what you learned directly in the code: meaningful names, comments, corrected logic.

## Build Commands

```bash
# Build programmer ELF (MBN-wrapped for Sahara)
make            # or: make elf

# Clean build outputs
make clean

# Flash programmer and open interactive console
uv run tools/usb_diag.py --flash src/tmp/minimal_rust.mbn

# Verified flash a partition
uv run tools/usb_diag.py --flash src/tmp/minimal_rust.mbn --flash-partition aboot tmp/aboot.bin

# Dump memory region
uv run tools/usb_diag.py --flash src/tmp/minimal_rust.mbn --dump-memory 0 10000 tmp/pbl.bin
```

## Architecture

### Key Files

- `src/` — Rust programmer source
  - `src/src/lib.rs` — Crate root (module declarations)
  - `src/src/console.rs` — USB diagnostic console (command parser, GPT cache, verified flash)
  - `src/src/emmc.rs` — eMMC state machine (card init, read, write)
  - `src/src/sdcc.rs` — SDCC hardware driver (DMA, command dispatch)
  - `src/src/usb.rs` — USB bulk transport (inherits PBL enumeration)
  - `src/src/gpt.rs` — GPT partition table parser
  - `src/src/sha256.rs` — SHA-256 for verified flash
  - `src/src/platform.rs` — Platform init (clocks, DDR, GPIO/LED)
  - `src/src/regs.rs` — SDCC register definitions
  - `src/src/mmio.rs` — MMIO register access helpers
  - `src/entry.S` — Entry point, hardware init, exception vectors
  - `src/minimal.ld` — Linker script
  - `src/Makefile` — Build: Rust staticlib + assembly → ELF → MBN
- `tools/usb_diag.py` — Host-side USB tool (Sahara upload, interactive console, verified flash, memory dump)
- `tools/mbn_wrap.py` — MBN hash table wrapper for Sahara ELF loading
- `docs/` — Hardware documentation

### Console Commands

| Cmd | Description |
|-----|-------------|
| `r ADDR` | Read 32-bit word |
| `w ADDR VAL` | Write 32-bit word |
| `d ADDR LEN` | Hex dump memory |
| `R ADDR LEN` | Raw memory dump (binary + SHA256, intercepted by Python for file save) |
| `i` | System info (page tables, control registers) |
| `t` | DDR test |
| `e` | Init eMMC |
| `c` | eMMC card status |
| `s SECTOR` | Read eMMC sector |
| `S SECTOR BYTE` | Write eMMC sector (fill byte) |
| `G` | Read GPT partition table |
| `F NAME` | Verified flash (GPT lookup, SHA256 upload check, write+readback verify) |
| `F SECTOR COUNT` | Verified flash (manual sector address) |

### Compiler Settings

Rust nightly cross-compiling for `thumbv7a-none-eabi` (ARMv7-A Thumb2, soft float). Assembly compiled with arm-none-eabi-gcc. `-mno-movt` in Rust target spec forces literal pool loads.

### Documentation Index (`docs/`)

| File | Content |
|------|---------|
| `init_sequence.md` | Full hardware init spec: DDR init, clock config, original vs minimal comparison |
| `led_checkpoints.md` | LED checkpoint map for entry.S debugging, exception handler patterns |
| `minimal_programmer.md` | Unified minimal programmer doc: status, architecture, USB, function mapping, build |
| `ddr_init.md` | DDR initialization details |
| `memory_layout.md` | Memory layout documentation |
| `device_properties.md` | BQ268 device properties and hardware info |
| `sahara_usb_handover.md` | USB session inheritance from PBL |
| `emulating_firehose.md` | Notes on Unicorn emulation of the firehose programmer |
| `partition3_restriction.md` | Partition 3 write restriction analysis |
| `recompilation_plan.md` | Plan for fhprg recompilation and verification |
| `printgpt.md` | GPT partition table dump |

## Hardware Notes

- **Boot chain**: PBL → SBL1 → aboot (LK) → kernel
- **PBL**: 64KB mask ROM at 0x00000000, loads us in EDL mode via Sahara
- **LEDs**: GPIO 68=red, 69=green, active-high, TLMM base 0x01000000
- **DDR**: 533MHz, init via binary blob callbacks (ARM/Thumb mixed mode)
- **eMMC**: SDCC1 controller at 0x07824000, SDHCI reset required before MCI mode
- **USB**: Inherits PBL's enumeration, DMA must use DDR buffers (not OCIMEM)
