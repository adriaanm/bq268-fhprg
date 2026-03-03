# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Goal

Create a **patched Qualcomm Firehose programmer** (`fhprg_peek.bin`, msm8909, ARM 32-bit) that can write the aboot partition. The approach is to decompile the original binary via Ghidra, recompile it to a matching binary, then patch the relevant partition-write restrictions.

The `aboot.bin` (Qualcomm LK bootloader) tooling in `tools/preprocess.py` and `src/aboot.ld` is from earlier work on the same infrastructure.

## Build Commands

```bash
# Compile decompiled C → object file
make all

# Full regeneration: extract strings + preprocess Ghidra output → src/fhprg.c
make regen

# Preprocess only (Ghidra C → compilable C)
make preprocess          # aboot target
python3 tools/preprocess_fhprg.py  # fhprg target

# Link compiled code + data blob → ELF at original addresses
make link

# Disassemble and diff original vs recompiled
make diff-asm

# Byte-level + per-function comparison against original
make hybrid-diff

# Run Ghidra headless analysis (requires PyGhidra venv)
make analyze             # fresh analysis
make analyze-reuse       # reuse existing Ghidra project (faster)

# Set up PyGhidra virtual environment
make venv
```

## Architecture

### Pipeline

1. **Ghidra analysis** (`tools/ghidra_analyze.py` / `ghidra_analyze_fhprg.py`) — Headless decompile of the binary via PyGhidra. Exports per-function C files to `tmp/decompiled/` and function metadata to `tmp/functions.json`.
2. **Preprocessing** (`tools/preprocess.py` / `preprocess_fhprg.py`) — Transforms raw Ghidra C into compilable C: resolves string references, fixes DAT_ globals, handles Ghidra field accessors (`_N_M_` syntax), forward-declares functions, and orders definitions by address.
3. **Compilation** — `arm-none-eabi-gcc` with flags: `-std=gnu89 -marm -march=armv7-a -mfloat-abi=soft -O2`. The type compatibility header `src/ghidra_types.h` is force-included.
4. **Linking** — Custom linker script (`src/fhprg.ld` or `src/aboot.ld`) places code at original virtual addresses. Data blob extracted from the binary provides globals/strings at their original addresses.
5. **Verification** — `tools/hybrid_diff.py` does per-function assembly comparison; `tools/diff_asm.py` does assembly similarity scoring.

### Key Files

- `src/ghidra_types.h` — Type compatibility header mapping all Ghidra-emitted types (undefined4, code*, CONCAT macros, SUB/SEXT/ZEXT macros) and ARM intrinsic stubs (CP15 ops, cache maintenance, barriers, SMC) to real implementations.
- `src/fhprg.c` — **Generated file** (do not edit directly). Produced by `preprocess_fhprg.py` from Ghidra output. Edit the preprocessor script to change output.
- `tmp/functions.json` — Function address/size/name index from Ghidra analysis.
- `tmp/decompiled/` — Individual per-function `.c` files from Ghidra.

### Compiler Settings

The target toolchain is `arm-none-eabi-gcc` compiling for ARMv7-A (ARM mode, soft float). The `-std=gnu89` flag matches the K&R-style function declarations Ghidra emits. Warnings are suppressed (`-w`) since Ghidra output is inherently messy.

### Matching Strategy

Functions are compared individually against the original binary. The preprocessor scripts are the main lever for improving match rates — they transform Ghidra's decompiled output to produce code that gcc compiles to matching assembly. Common fixes include: correcting type widths, rewriting field accesses, adjusting cast sequences, and handling Ghidra artifacts like UNRECOVERED_JUMPTABLE.
