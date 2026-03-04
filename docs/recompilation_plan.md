# Full fhprg Decompilation to Matching C

## Goal
Create a byte-close reproduction of `fhprg_peek.bin` (Qualcomm MSM8909 firehose
programmer, 230KB Thumb2 code, 1,880 functions). Every non-matching function
examined case-by-case for functional equivalence.

---

## Phase 1: Toolchain & Build Infrastructure

### 1a. Identify and acquire the original compiler — DONE
**Decision**: Use clang 19 with `-mno-movt`.

**What worked**:
- `apt install clang lld` → clang 19.1.7
- `clang --target=arm-none-eabi -mthumb -march=armv7-a -mfloat-abi=soft -mno-movt -O2`
- `-mno-movt` forces literal pool generation, matching original binary's dominant pattern
- `-Wno-everything` needed (clang treats int-to-ptr as error even with `-w`)
- Compiles full 67K-line fhprg.c cleanly

**What didn't work**:
- GCC 14 has NO `-mno-movt` for armv7-a (only Cortex-M has `-mslow-flash-data`)
- GCC produces movw/movt pairs → ~30% code inflation, fundamentally different from original

**Numbers**:
- clang -O2 -mno-movt: 298KB .text (literal pools inflate it past original's 230KB)
- clang -Os -mno-movt: 219KB .text (closer to 230KB but may not match patterns)
- GCC -O2 -mthumb: 240KB .text (movw/movt, wrong pattern)
- Proceeding with -O2 since instruction pattern matching > size matching

### 1b. Create proper fhprg Makefile targets — DONE
Added: `make fhprg`, `make fhprg-diff`, `make fhprg-report`, `make fhprg-provides`,
`make fhprg-clean`, `make fhprg-regen`.

### 1c. Fix linker script for per-function placement — DONE
**What worked**:
- `-ffunction-sections` + generated `tmp/fhprg_sections.ld` with one entry per function
- `SUBALIGN(1)` prevents padding between sections
- `--noinhibit-exec` to proceed despite overlaps (recompiled functions larger than originals)
- libgcc linked for `__aeabi_uidiv` etc. runtime calls

**What didn't work**:
- Flat binary extraction via objcopy (sections span 0x002xxxxx–0x0803xxxx → 132MB file)
  Solution: skip flat binary, use ELF directly for comparison

**Generated files**: `tmp/fhprg_provides.ld` (1146 PROVIDE symbols),
`tmp/fhprg_sections.ld` (1879/1880 function placements)

---

## Phase 2: Adapt Verification Tooling for fhprg

### 2a. Make hybrid_diff work for fhprg — DONE
Rewrote `tools/hybrid_diff.py` to be generic (ARM-32 and Thumb2).

**What worked**:
- Auto-detect code/data ranges from ELF program headers
- Syms.txt format support (address gaps → inferred function sizes)
- `--thumb` flag for Thumb2 disassembly

**Critical bug found**: objdump `-d -M force-thumb` is IGNORED for ELF files
lacking `$t` mapping symbols. Our linked ELF has no mapping symbols because
clang's `.text.FUN_xxx` sections lose them during objcopy/ld roundtrip.
**Fix**: Use `-D -j .text -M force-thumb` instead of `-d`.

**What didn't work**:
- Binary disasm (`-b binary -m arm`) starts at address 0, so branch targets
  are wrong (e.g., `bl 0xde8` instead of `bl 0x8006e98`).
  **Fix**: Wrap raw bytes in temp ELF at correct VMA via objcopy+ld, then `-D -j .text`.

### 2b. Create per-function match dashboard — DONE
`tools/fhprg_match_report.py` — JSON report + summary stats.

Categories: byte-identical / insn-equivalent / similar (>80%) / needs-review / missing.

### 2c. Baseline results (clang -mno-movt -O2)
```
Total functions     : 1777
Byte-identical      :    23  (1.3%)
Insn-equivalent     :    45  (2.5%)
Similar (>80%)      :    23  (1.3%)
Needs review        :  1683  (94.7%)
Missing             :     3  (0.2%)
OK (byte+insn)      :    68  (3.8%)

Similarity distribution:
   0-20%:  1388
  20-40%:   221
  40-60%:    50
  60-80%:    27
  80-99%:    23
    100%:    68
```

Up from ~0.5% with GCC. The 3.8% matching functions are mostly small leaf
functions (2-18 bytes). Key remaining differences:
- Register allocation (clang vs original armcc)
- IT blocks vs conditional branches
- Dead code elimination differences
- Control flow restructuring

---

## Phase 3: Split Monolithic fhprg.c — DONE

### 3a. Split by address range — DONE
Split 67K-line `src/fhprg.c` into 14 modules + globals header:
```
src/fhprg/globals.h   — 4531 lines (all extern decls, forward decls, #defines)
src/fhprg/thunks.c    — 97 functions  (0x00220000-0x00223000, veneer stubs)
src/fhprg/mod_00.c    — 115 functions (0x08006000-0x0800a000)
src/fhprg/mod_01.c    — 235 functions (0x0800a000-0x0800e000)
...
src/fhprg/mod_12.c    — 103 functions (0x08036000-0x0803a000)
```
1777 function bodies extracted. Even 0x4000 address chunks, ~100-235 functions each.

**What worked**:
- Simple regex `^[a-z]\S*(?:\s*\*)?\s+((?:thunk_)?FUN_([0-9a-fA-F]{8}))\s*\(` catches all
  return types including `char *`, `undefined4`, etc.
- Brace-depth tracking to find function body end

**What didn't work**:
- Initial regex missed `char *` return type (only matched single-word types)
- `_local_*` non-extern globals in globals.h caused multiple definition errors when
  linking split modules. **Fix**: convert to `extern` in globals.h, define in mod_00.c only.

### 3b. Splitter tool — DONE
`tools/split_fhprg.py` reads src/fhprg.c, finds "Function bodies" marker,
extracts each function by brace-depth, assigns to module by address range.

### 3c. Per-module build — DONE
`make fhprg` now compiles 14 .c files → 14 .o files → linked ELF.
`gen_fhprg_provides.py` updated to scan multiple object files and
exclude cross-module refs from PROVIDE() generation.

### 3d. Results after split
```
  OK (byte+insn)      :    71  (4.0%)
  Byte-identical      :    25  (1.4%)
  Insn-equivalent     :    46  (2.6%)
  Similar (>80%)      :    23  (1.3%)
  Needs review        :  1680  (94.5%)

  Similarity distribution:
     0-20%:  1229
    20-40%:   331
    40-60%:    91
    60-80%:    32
    80-99%:    23
      100%:    71
```
Slight improvement over monolithic (71 vs 68 OK). Similarity shifted right
(more functions in 20-60% bucket). Per-module compilation gives slightly
different optimization decisions.

---

## Phase 4: Second Ghidra Pass with Symbols — DONE

### 4a. Feed known symbols back to Ghidra — DONE
Installed Ghidra 12.0.4 on aarch64 Linux. Built native decompiler from source
(`ghidra_opt` target, NOT `decomp_opt` — the latter is standalone console, not
the process Ghidra spawns via Java).

**What worked**:
- `apt install openjdk-21-jdk` for Java 21
- Downloaded Ghidra 12.0.4 to `/opt/ghidra_12.0.4_PUBLIC`
- Built native decompiler: `cd .../Decompiler/src/decompile/cpp && make OSDIR=linux_arm_64 ARCH_TYPE= ghidra_opt`
- Installed as `Ghidra/Features/Decompiler/os/linux_arm_64/decompile`
- PyGhidra 3.0.2 in venv: `tmp/pyghidra_venv/bin/python3`
- Imported 1880 function symbols + DAT_ + string symbols via PyGhidra API
- Re-decompiled all 1908 functions (28 more than previous analysis)

**What didn't work**:
- `make decomp_opt` builds standalone console decompiler (consolemain.cc) — NOT what Ghidra calls
  Must use `make ghidra_opt` which builds from ghidra_process.cc
- Ghidra project from previous version was empty `.gpr` file — had to re-create from scratch
- DecompInterface.openProgram() returns False silently when native binary is wrong
  Debug: check `getLastMessage()` → "Decompiler process failed to launch"

**Bug fixed**: preprocessor `_is_unary_context()` didn't handle `:` (label separator)
as valid context for unary `*`. Added `:` to accepted chars.

**Bug fixed**: `processEntry entry()` prototype not fixed (only body was fixed).
Added special case to prototype generation.

**Bug fixed**: `_local_*` extern vars not defined in split modules.
Updated split_fhprg.py to detect `extern ... _local_*` patterns.

### 4b. Match against Qualcomm LK source — SKIPPED
No `tools/match_lk_symbols.py` exists. Skipped for now.

### 4c. Re-run decompilation and diff — DONE
```
Total functions     : 1777
Byte-identical      :    25  (1.4%)
Insn-equivalent     :    46  (2.6%)
Similar (>80%)      :    23  (1.3%)
Needs review        :  1680  (94.5%)
Missing             :     3  (0.2%)
OK (byte+insn)      :    71  (4.0%)
```
Same as Phase 3 results. The fresh Ghidra decompilation with symbols didn't change
match rates — the bottleneck is compiler differences (clang vs armcc), not decompilation quality.

---

## Phase 4b: Compiler Flag Experiments & Diff Analysis — DONE

### Compiler flag sweep
Tested 20+ flag combinations with clang. Results ranged 71-76 raw OK (out of 1777):

| Flags | Raw OK |
|-------|--------|
| `-O2` (baseline) | 71 |
| `-O1` | 71 |
| `-Os` | 72 |
| `-Oz` | 74 |
| **`-Oz -fomit-frame-pointer`** | **76** (best) |
| `-O0` | 52 |
| `-fPIC` | 63 (harmful) |

Most `-fno-*` flags have zero effect. Updated Makefile to `-Oz -fomit-frame-pointer`.

### Diff categorization
Analyzed all 1,698 failing functions:
- **38% different instructions** — fundamentally different code gen (mov vs ldr: 502 occurrences)
- **34% extra recomp code** — clang emits more instructions
- **17% missing recomp code** — original has code clang optimizes away differently
- **2% register allocation** — same instructions, different registers
- **2% IT block** — conditional execution encoding differences

Dominant patterns in non-matching functions:
- Code shrink (clang more aggressive): 731 functions
- Code bloat (clang less efficient): 469 functions
- IT conversion (if-conversion): 201 functions
- Other codegen differences: 166 functions
- NOP variant only: 19 functions

### Semantic normalization
Added `--normalize` flag to `hybrid_diff.py` with 6 cumulative levels:

| Level | What | =100% | >=90% | >=80% |
|-------|------|-------|-------|-------|
| 0 | raw | 76 | 76 | 104 |
| 1 | mnemonic aliases | 78 | 78 | 107 |
| 2 | **register allocation** | **104** | 111 | 145 |
| 3 | literal pool offsets | 104 | 111 | 146 |
| 4 | branch targets | 104 | 111 | 158 |
| 5 | strip trailing litpool | 105 | 110 | 159 |

Register normalization is the biggest win (+28 exact matches). Level 5 (litpool strip) adds
minimal value. 204 functions have same instruction count but zero have the same mnemonic
bag — differences are fundamental code generation choices, not cosmetic.

### Key insight
The ceiling for "matching via normalization" is ~104 functions (5.9%). The remaining 1,673
functions differ due to genuinely different code generation strategies:
- Loop strength reduction (clang transforms index*scale into pointer increment)
- If-conversion (IT blocks vs conditional branches)
- Different instruction selection (ubfx vs mask+shift)
- Different control flow structure

These cannot be resolved by assembly-level normalization. They require either:
1. Manual C source adjustments per function to guide clang toward the original pattern
2. Accepting the clang output as functionally equivalent after review
3. Injecting original bytes for critical functions

---

## Phase 5: Iterative Per-Function Matching — TODO

### 5a. Revised strategy
Given the analysis above, the realistic approach is:
1. **76 byte-identical + 28 register-only** = 104 "proven equivalent" functions
2. **54 functions at 80-99% normalized similarity** — review diffs, likely acceptable
3. **~200 small leaf functions** — try manual C tweaks for common patterns
4. **Remaining ~1,400** — document as "functionally equivalent, different code generation"
5. Focus manual effort on **security-critical functions** (write, erase, auth checks)

### 5b. Per-function compiler flag tuning — UNLIKELY TO HELP
Flags make <5 function difference across the board. Not worth per-function tuning.

### 5c. Handle impossible-to-match functions
Document, verify functional equivalence, mark as "reviewed-equivalent".

---

## Phase 6: Data Segment & Final Binary — TODO

### 6a. Extract and include data segment
Original data at 0x0804c000 (23KB initialized).

### 6b. Handle the thunk region (0x002xxxxx)
103 thunk functions need their own segment.

### 6c. Produce final binary
Link all modules + data + thunks → flat binary → byte-compare.

---

## Execution Order
```
[DONE] Phase 1b (Makefile)
[DONE] Phase 1c (linker placement)
[DONE] Phase 2a (fix hybrid_diff)
[DONE] Phase 2b (match dashboard)
[DONE] Phase 1a (clang -mno-movt)
[DONE] Phase 3  (split fhprg.c)
[DONE] Phase 4  (second Ghidra pass)
[    ] Phase 5  (per-function work)    ← NEXT
[    ] Phase 6  (final binary)
```
