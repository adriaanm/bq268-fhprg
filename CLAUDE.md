# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Goal

Create a **patched Qualcomm Firehose programmer** (`fhprg_peek.bin`, msm8909, ARM 32-bit) that can write the aboot partition. The current WP bypass patch (code cave at 0x0803dc8c) does not work — writes still don't persist due to hardware write protection (CMD28 WP groups). The approach now is to **fully decompile** the original binary via Ghidra into readable, correct C so we can understand the write path end-to-end and craft a working patch.

Byte-for-byte reproduction of the original binary is **not a goal**. The original was compiled with ARM Compiler v5 (armcc/RVCT), which we don't have access to. Clang with `-mno-movt` gets literal pool loads right but register allocation and instruction scheduling will never match. Tweaking compiler flags (`-Oz`, `-Os`, `-O1`, `-O2`) does not meaningfully change match rates. The recompilation exists as a verification tool to confirm the decompiled C is functionally correct, not to produce a drop-in replacement.

The `aboot.bin` (Qualcomm LK bootloader) tooling in `tools/preprocess.py` and `src/aboot.ld` is from earlier work on the same infrastructure.

## Minimal Programmer: Replicate the Original

The minimal programmer (`src_minimal/`) must be developed by **studying and replicating the original firehose programmer** (`src/fhprg/` decompiled source). The original is the only known-working reference for this SoC. Every hardware subsystem (USB, clocks, DDR, eMMC) should match the original's register sequences and init order for the subset of functionality we use.

**Do not invent alternative approaches** (skipping init steps, inheriting PBL state instead of reinitializing, etc.) without explicit user approval. When something doesn't work, always check what the original does first.

## Workflow

- **Commit regularly** — after each logical change (rename batch, tool fix, build fix, etc.), stage and commit. Don't let changes accumulate across multiple tasks.
- **Embody what you learn in the source** — when analyzing a function (debugging, tracing, reviewing), always capture what you learned directly in the code: rename locals to meaningful names, update comments, fix misleading Ghidra artifacts. Local changes (variable names, comments, correcting a function's own name) are always welcome. Avoid changes that ripple through the codebase (renaming a widely-used extern, changing a struct layout) unless that's the task at hand.
- **`memset_zero` / `memset` must use `sizeof(target)`** — never pass a hardcoded size larger than the actual variable. Ghidra often emits `memset_zero(local_68, 0x28)` where `local_68` is only `char[4]` — the 0x28 was the original contiguous struct size. Always fix the variable to match the size (e.g. `char buf[0x28]`) or use `sizeof(buf)`.
- **DANGER: Ghidra `local_XX` names encode stack layout** — Ghidra's `local_40, local_3c, local_38, ...` names indicate specific stack offsets (FP-0x40, FP-0x3c, etc.). When multiple locals are passed as `&local_40` to a function that indexes them as an array (e.g. `cmd[0]`, `cmd[1]`, `cmd[9]`), they form a **contiguous struct on the stack with unnamed gaps**. Renaming them to separate variables (e.g. `cmd_num, cmd_arg, cmd_flags`) lets the compiler pack them differently, breaking the array layout. **Always use `int arr[N]` with explicit index assignments when locals are accessed as an array.**
- **DANGER: Debug code in `src_minimal/` can break code layout** — adding static functions, string literals, or data tables (e.g. `dbg()`, `hex_chars[]`) to files like `emmc.c` shifts code/data placement enough to cause data aborts during eMMC init. The init path relies on data structures at fixed addresses in the `.data` blob; layout changes can misalign them. **Keep debug tracing in `main.c` only** (which is not part of the eMMC driver closure) or use LED-only debugging from `entry.S`.

## Build Commands

```bash
# Build minimal programmer ELF (MBN-wrapped for Sahara)
make            # or: make elf

# Build debug ELF with symbols (no MBN wrapping, for emulator)
make debug-elf

# Clean build outputs
make clean
```

## Architecture

### Key Files

- `src_minimal/` — Minimal programmer source (C + assembly)
- `src_minimal/globals.h` — Central header with type definitions and forward declarations
- `src_minimal/entry.S` — Entry point, hardware init, exception vectors
- `src_minimal/main.c` — Diagnostic console (USB command loop)
- `src_minimal/emmc.c` — eMMC read/write/erase operations
- `src_minimal/card_init.c` — eMMC card identification and initialization
- `src_minimal/sdcc_helpers.c` — SDCC data transfer helpers (DMA, command dispatch)
- `src_minimal/sdcc_regs.c` — SDCC controller MMIO register access
- `src_minimal/usb.c` — USB bulk transport (inherits PBL enumeration)
- `src_minimal/globals.c` — Global variable definitions
- `src_minimal/minimal.ld` — Linker script
- `src_minimal/address_map.txt` — Maps functions to original binary addresses for cross-referencing `src/fhprg/`
- `src/fhprg/` — Decompiled original programmer (reference, not built)

### Compiler Settings

Clang 19 cross-compiling for ARMv7-A Thumb2 mode with soft float. `-mno-movt` forces literal pool loads. `-std=gnu89` for K&R compatibility. GCC does not support `-mno-movt` for armv7-a, making Clang required.

### Documentation Index (`docs/`)

| File | Content |
|------|---------|
| `init_sequence.md` | Full hardware init spec: DDR init, clock config, original vs minimal comparison |
| `led_checkpoints.md` | LED checkpoint map for entry.S debugging, exception handler patterns |
| `minimal_programmer.md` | Unified minimal programmer doc: status, architecture, USB, function mapping, build |
| `ddr_init.md` | DDR initialization details |
| `memory_layout.md` | Memory layout documentation |
| `device_properties.md` | BQ268 device properties and hardware info |
| `emulating_firehose.md` | Notes on Unicorn emulation of the firehose programmer |
| `partition3_restriction.md` | Partition 3 write restriction analysis |
| `recompilation_plan.md` | Plan for fhprg recompilation and verification |
| `printgpt.md` | GPT partition table dump |
