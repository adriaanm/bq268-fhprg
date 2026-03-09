# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**bq268-edl-diag** — a bare-metal Rust diagnostic tool for the MSM8909 SoC (BQ268/ABBREE GP-268). Loaded via PBL's Sahara/EDL mode, it provides a USB console for register access, memory dumps, eMMC read/write, and verified partition flashing. Hardware init sequences were reverse-engineered from the stock Qualcomm Firehose programmer.

## Workflow

- **Commit regularly** — after each logical change, stage and commit.
- **Embody what you learn in the source** — when analyzing or debugging, capture what you learned directly in the code: meaningful names, comments, corrected logic.

## Build Commands

```bash
make            # Build MBN-wrapped ELF for Sahara upload
make clean      # Clean build artifacts

# Flash programmer and open interactive console
uv run tools/usb_diag.py --flash src/tmp/minimal_rust.mbn

# Verified flash a partition
uv run tools/usb_diag.py --flash src/tmp/minimal_rust.mbn --flash-partition aboot aboot.bin
```

## Key Files

- `src/rust/` — Rust source (no_std staticlib)
  - `console.rs` — USB command parser, GPT cache, verified flash (`G`, `F`, `R` commands)
  - `emmc.rs` — eMMC state machine (card init, sector read/write)
  - `sdcc.rs` — SDCC hardware driver (DMA, command dispatch)
  - `usb.rs` — USB bulk transport (inherits PBL enumeration)
  - `gpt.rs` — GPT partition table parser
  - `sha256.rs` — SHA-256 for verified flash
  - `platform.rs` — Platform init (clocks, DDR, GPIO/LED)
  - `regs.rs` — SDCC register definitions
  - `mmio.rs` — MMIO register access helpers
  - `lib.rs` — Crate root
- `src/asm/` — ARM assembly
  - `entry.S` — Entry point, hardware init, exception vectors, DDR blob callbacks
  - `ddr_blob.S` / `ddr_config.S` — DDR binary blob includes
- `src/blobs/` — DDR binary blobs extracted from original programmer
- `src/minimal.ld` — Linker script
- `src/Makefile` — Build: Rust staticlib + assembly → ELF → MBN
- `tools/usb_diag.py` — Host-side USB tool (Sahara upload, interactive console, verified flash)
- `tools/mbn_wrap.py` — MBN hash table wrapper for Sahara ELF loading

## Compiler Settings

Rust nightly cross-compiling for `thumbv7a-none-eabi` (ARMv7-A Thumb2, soft float). Assembly compiled with `arm-none-eabi-gcc`. `-mno-movt` in the Rust target spec forces literal pool loads.

## Hardware Notes

- **Boot chain**: PBL → SBL1 → aboot (LK) → kernel
- **PBL**: 64KB mask ROM at 0x00000000, loads us in EDL mode via Sahara
- **LEDs**: GPIO 68=red, 69=green, active-high, TLMM base 0x01000000
- **DDR**: 533MHz, init via binary blob callbacks (ARM/Thumb mixed mode)
- **eMMC**: SDCC1 controller at 0x07824000, SDHCI reset required before MCI mode
- **USB**: Inherits PBL's enumeration, DMA must use DDR buffers (not OCIMEM)

## Documentation (`docs/`)

| File | Content |
|------|---------|
| `init_sequence.md` | Full hardware init spec: DDR init, clock config |
| `led_checkpoints.md` | LED checkpoint map for entry.S debugging |
| `minimal_programmer.md` | Programmer architecture, USB protocol, function mapping |
| `ddr_init.md` | DDR initialization details |
| `memory_layout.md` | Memory layout documentation |
| `device_properties.md` | BQ268 device properties and hardware info |
| `sahara_usb_handover.md` | USB session inheritance from PBL |
| `printgpt.md` | GPT partition table dump |
