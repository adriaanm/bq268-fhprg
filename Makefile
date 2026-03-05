# aboot - Qualcomm LK bootloader decompilation for msm8909
#
# This Makefile builds the decompiled aboot C source into an object file
# compatible with the original binary.

CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-ld
OBJDUMP = arm-none-eabi-objdump
OBJCOPY = arm-none-eabi-objcopy

# -ffunction-sections/-fdata-sections give the linker fine-grained control
# over section placement (required to guarantee FUN_8f600000 is first).
CFLAGS = -std=gnu89 -marm -march=armv7-a -mfloat-abi=soft -O2 \
         -ffunction-sections -fdata-sections
CWARN  = -w -Wno-incompatible-pointer-types -Wno-int-conversion

SRC    = src/aboot.c src/strings.c
OBJ    = aboot.o strings.o
TYPES  = src/ghidra_types.h
BINARY = aboot.bin

ORIG_ASM     = tmp/aboot_orig.asm
RECOMP_ASM   = tmp/aboot_recompiled.asm
DIFF_JSON    = tmp/asm_diff.json
FUNCS_JSON   = tmp/functions.json

# Linker output
DATA_BIN     = tmp/aboot_data.bin
PROVIDES_LD  = tmp/aboot_provides.ld
DATA_OBJ     = tmp/aboot_data.o
LINKED_ELF   = aboot_linked.elf
LINKED_BIN   = aboot_linked.bin

# Python venv for Ghidra analysis
VENV_DIR = tmp/pyghidra_venv
VENV_PY = $(VENV_DIR)/bin/python3
GHIDRA_INSTALL = /opt/homebrew/Cellar/ghidra/12.0.3/libexec

# ── fhprg (firehose programmer) ──────────────────────────────────────────────
FHPRG_CC     = clang
FHPRG_CFLAGS = --target=arm-none-eabi -mthumb -march=armv7-a -mfloat-abi=soft \
               -mno-movt -Oz -fomit-frame-pointer -std=gnu89 -Wno-everything \
               -ffreestanding -ffunction-sections -fdata-sections
FHPRG_SPLIT_SRC = $(wildcard src/fhprg/*.c)
FHPRG_SPLIT_OBJ = $(patsubst src/fhprg/%.c,tmp/fhprg_%.o,$(FHPRG_SPLIT_SRC))
FHPRG_ELF    = tmp/fhprg_linked.elf
FHPRG_ORIG   = fhprg_peek.bin
FHPRG_FUNCS  = tmp/fhprg_syms.txt
FHPRG_PROV   = tmp/fhprg_provides.ld
FHPRG_LD     = src/fhprg.ld
FHPRG_MAP    = tmp/fhprg_linked.map

.PHONY: all clean preprocess analyze diff-asm match-symbols extract-code \
        disasm-orig disasm-recomp venv strings extract-data link hybrid-diff \
        fhprg fhprg-diff fhprg-regen fhprg-provides

all: $(OBJ)

aboot.o: src/aboot.c $(TYPES)
	$(CC) $(CFLAGS) $(CWARN) -ffreestanding -include $(TYPES) src/aboot.c -c -o $@

strings.o: src/strings.c
	$(CC) $(CFLAGS) $(CWARN) -c src/strings.c -o $@

# Extract raw data blob and generate linker symbol provides
extract-data: $(DATA_BIN) $(PROVIDES_LD)
$(DATA_BIN) $(PROVIDES_LD): $(BINARY) $(FUNCS_JSON) tools/extract_data.py
	@mkdir -p tmp
	python3 tools/extract_data.py

# Assemble the raw data blob into a relocatable object
$(DATA_OBJ): src/aboot_data.S $(DATA_BIN)
	$(CC) $(CFLAGS) -x assembler-with-cpp -c src/aboot_data.S -o $@

# Link: compiled code + data blob → ELF at original virtual addresses.
# Strings come from the blob (not strings.o) so all s_xxx symbols resolve
# via PROVIDE() to their original addresses within the data section.
# -L . adds aboot/ to ld's search path so INCLUDE "tmp/aboot_provides.ld" works.
link: $(LINKED_ELF) $(LINKED_BIN)
$(LINKED_ELF): aboot.o $(DATA_OBJ) src/aboot.ld $(PROVIDES_LD)
	$(LD) -T src/aboot.ld -L . -o $@ aboot.o $(DATA_OBJ) \
	    -Map tmp/aboot_linked.map
	@echo "[*] Linked ELF: $@"

# Flat binary for byte-level comparison against original code region
$(LINKED_BIN): $(LINKED_ELF)
	$(OBJCOPY) -O binary --only-section=.text $< $@
	@echo "[*] Code binary: $@ ($$(wc -c < $@) bytes vs 0x52e80=$(shell printf '%d' 0x52e80) original)"

# Disassemble original binary with function labels from Ghidra
$(ORIG_ASM): $(BINARY) $(FUNCS_JSON) tools/disasm_orig.py
	@mkdir -p tmp
	python3 tools/disasm_orig.py --elf $(BINARY) --funcs $(FUNCS_JSON) -o $@

# Disassemble recompiled object
$(RECOMP_ASM): $(OBJ)
	@mkdir -p tmp
	$(OBJDUMP) -d $(OBJ) > $@

# Full diff-asm pipeline: disasm orig, compile, disasm recomp, compare
diff-asm: $(ORIG_ASM) $(RECOMP_ASM)
	python3 tools/diff_asm.py --orig $(ORIG_ASM) --new $(RECOMP_ASM)

# Just regenerate disassemblies without running diff
disasm: $(ORIG_ASM) $(RECOMP_ASM)

# Regenerate src/aboot.c from Ghidra decompiled output
preprocess:
	python3 tools/preprocess.py

# Extract string definitions from aboot.bin
strings:
	python3 tools/extract_strings.py

# Full regeneration: both strings and preprocessed C
regen: strings preprocess

# Set up PyGhidra virtual environment
$(VENV_PY):
	@mkdir -p tmp
	python3 -m venv $(VENV_DIR)
	$(VENV_PY) -m pip install --upgrade pip
	$(VENV_PY) -m pip install pyghidra
	@echo "PyGhidra venv created at $(VENV_DIR)"

venv: $(VENV_PY)

# Run Ghidra analysis (requires PyGhidra venv)
analyze: $(VENV_PY)
	$(VENV_PY) tools/ghidra_analyze.py --ghidra $(GHIDRA_INSTALL)

# Re-run analysis on existing Ghidra project (faster)
analyze-reuse: $(VENV_PY)
	$(VENV_PY) tools/ghidra_analyze.py --reuse --ghidra $(GHIDRA_INSTALL)

# Match functions against LK reference symbols
match-symbols:
	python3 tools/match_lk_symbols.py

# Extract raw code segment for byte comparison
extract-code:
	python3 tools/extract_code_segment.py

# Hybrid diff: byte-identical for data; assembly-equivalent per function for code
hybrid-diff: $(LINKED_ELF)
	python3 tools/hybrid_diff.py --orig $(BINARY) --recomp $(LINKED_ELF) --funcs $(FUNCS_JSON)

# ── fhprg targets ────────────────────────────────────────────────────────────

# Compile each split module → object file
tmp/fhprg_%.o: src/fhprg/%.c src/fhprg/globals.h $(TYPES)
	$(FHPRG_CC) $(FHPRG_CFLAGS) -I src -I src/fhprg -c $< -o $@

# Generate PROVIDE() symbols + per-function section placements
fhprg-provides: $(FHPRG_SPLIT_OBJ) $(FHPRG_FUNCS)
	python3 tools/gen_fhprg_provides.py

# Split monolithic fhprg.c into per-module files
fhprg-split:
	python3 tools/split_fhprg.py

# Link with per-function placement
FHPRG_LIBGCC = $(shell arm-none-eabi-gcc -mthumb -march=armv7-a -mfloat-abi=soft --print-libgcc-file-name)

$(FHPRG_ELF): $(FHPRG_SPLIT_OBJ) $(FHPRG_LD) $(FHPRG_PROV)
	$(LD) -T $(FHPRG_LD) -L . -o $@ $(FHPRG_SPLIT_OBJ) $(FHPRG_LIBGCC) -Map $(FHPRG_MAP) \
	    --noinhibit-exec 2>&1 | grep -v 'overlaps section' || true
	@echo "[*] fhprg linked: $@ (overlaps expected for oversized functions)"

# Note: flat binary not useful for fhprg (per-function sections span wide address range)
# Use fhprg-diff or fhprg-report for comparison instead

# Compile + link
fhprg: $(FHPRG_ELF)

# Per-function hybrid diff against original
fhprg-diff: $(FHPRG_ELF)
	python3 tools/hybrid_diff.py --orig $(FHPRG_ORIG) --recomp $(FHPRG_ELF) \
	    --funcs $(FHPRG_FUNCS) --thumb

# Match report dashboard (JSON + summary)
fhprg-report: $(FHPRG_ELF)
	python3 tools/fhprg_match_report.py

# Re-run Ghidra + preprocess for fhprg
fhprg-regen:
	python3 tools/preprocess_fhprg.py

# ── minimal (stripped-down firehose for analysis) ────────────────────────────
MINIMAL_CC     = clang
MINIMAL_CFLAGS = --target=arm-none-eabi -mthumb -march=armv7-a -mfloat-abi=soft \
                 -mno-movt -Oz -fomit-frame-pointer -std=gnu89 \
                 -DMINIMAL_EMBEDDED_PAYLOAD \
                 -Wall -Wextra \
                 -Wunused-function -Wunused-variable \
                 -Warray-bounds -Wformat -Wformat-security \
                 -Wimplicit-function-declaration \
                 -Wno-unused-parameter -Wno-sign-compare \
                 -Wno-missing-field-initializers -Wno-old-style-definition \
                 -Wno-deprecated-non-prototype \
                 -ffreestanding -ffunction-sections -fdata-sections \
                 -I src_minimal
MINIMAL_SRC = $(wildcard src_minimal/*.c)
MINIMAL_OBJ = $(patsubst src_minimal/%.c,tmp/minimal_%.o,$(MINIMAL_SRC))

# Assembly sources (entry point, DDR blobs, payload)
MINIMAL_ASM_SRC = src_minimal/entry.S src_minimal/ddr_blob.S src_minimal/aboot_payload.S
MINIMAL_ASM_OBJ = $(patsubst src_minimal/%.S,tmp/minimal_%.o,$(MINIMAL_ASM_SRC))

MINIMAL_LIBGCC = $(shell arm-none-eabi-gcc -mthumb -march=armv7-a -mfloat-abi=soft --print-libgcc-file-name)
MINIMAL_LD_SCRIPT = src_minimal/minimal.ld
MINIMAL_ELF = tmp/minimal.elf
MINIMAL_BIN = tmp/minimal.bin
MINIMAL_MAP = tmp/minimal.map

.PHONY: minimal minimal-elf minimal-clean

tmp/minimal_%.o: src_minimal/%.c src_minimal/firehose.h src_minimal/libc_glue.h
	@mkdir -p tmp
	$(MINIMAL_CC) $(MINIMAL_CFLAGS) -c $< -o $@

tmp/minimal_%.o: src_minimal/%.S
	@mkdir -p tmp
	arm-none-eabi-as -march=armv7-a -mthumb -mfloat-abi=soft -o $@ $<

minimal: $(MINIMAL_OBJ) $(MINIMAL_ASM_OBJ)
	@echo "[*] Minimal build: $(words $(MINIMAL_OBJ)) C objects, $(words $(MINIMAL_ASM_OBJ)) ASM objects"
	@echo "[*] Checking undefined symbols..."
	@arm-none-eabi-nm -u $(MINIMAL_OBJ) $(MINIMAL_ASM_OBJ) | sort -u | head -40

minimal-elf: $(MINIMAL_OBJ) $(MINIMAL_ASM_OBJ)
	@echo "[*] Linking minimal ELF..."
	$(LD) -T $(MINIMAL_LD_SCRIPT) -o $(MINIMAL_ELF) $(MINIMAL_OBJ) $(MINIMAL_ASM_OBJ) \
		$(MINIMAL_LIBGCC) -Map $(MINIMAL_MAP)
	@echo "[*] ELF size: $$(stat -c %s $(MINIMAL_ELF)) bytes"
	@echo "[*] CODE segment: $$(arm-none-eabi-size -A $(MINIMAL_ELF) | awk '/.text/{t+=$$2} /.rodata/{t+=$$2} /.payload/{t+=$$2} END{print t}') bytes (limit: 294912)"
	@echo "[*] Sahara loads ELF directly — no flat binary needed"

# ── minimal-emu (emulator-friendly build, no inline asm) ──────────────────────
MINIMAL_EMU_CFLAGS = $(MINIMAL_CFLAGS) -DEMU_BUILD
MINIMAL_EMU_OBJ = $(patsubst src_minimal/%.c,tmp/minimal_emu_%.o,$(MINIMAL_SRC))
MINIMAL_EMU_ELF = tmp/minimal_emu.elf
MINIMAL_EMU_MAP = tmp/minimal_emu.map

# Dummy payload for emu build (no real aboot needed)
MINIMAL_EMU_PAYLOAD_OBJ = tmp/minimal_emu_payload.o

.PHONY: minimal-emu

tmp/minimal_emu_%.o: src_minimal/%.c src_minimal/firehose.h src_minimal/libc_glue.h
	@mkdir -p tmp
	$(MINIMAL_CC) $(MINIMAL_EMU_CFLAGS) -c $< -o $@

# Generate a small dummy gzip payload for emulator testing
$(MINIMAL_EMU_PAYLOAD_OBJ): tools/gen_emu_payload.py
	@mkdir -p tmp
	python3 tools/gen_emu_payload.py
	arm-none-eabi-as -march=armv7-a -mthumb -mfloat-abi=soft -o $@ tmp/emu_payload.S

minimal-emu: $(MINIMAL_EMU_OBJ) $(MINIMAL_EMU_PAYLOAD_OBJ)
	@echo "[*] Linking minimal-emu ELF..."
	$(LD) -T $(MINIMAL_LD_SCRIPT) -o $(MINIMAL_EMU_ELF) $(MINIMAL_EMU_OBJ) $(MINIMAL_EMU_PAYLOAD_OBJ) \
		$(MINIMAL_LIBGCC) -Map $(MINIMAL_EMU_MAP)
	@echo "[*] minimal-emu ELF: $$(stat -c %s $(MINIMAL_EMU_ELF)) bytes"

minimal-clean:
	rm -f tmp/minimal_*.o tmp/minimal_emu_*.o $(MINIMAL_ELF) $(MINIMAL_BIN) $(MINIMAL_MAP)
	rm -f $(MINIMAL_EMU_ELF) $(MINIMAL_EMU_MAP) tmp/emu_payload.bin.gz tmp/emu_payload.S

# ── clean ────────────────────────────────────────────────────────────────────
clean:
	rm -f $(OBJ) $(ORIG_ASM) $(RECOMP_ASM) $(DIFF_JSON)
	rm -f $(DATA_OBJ) $(LINKED_ELF) $(LINKED_BIN) tmp/aboot_linked.map
	rm -f src/aboot.c
	# Keep tmp/ (contains Ghidra analysis and generated blobs)
	# Keep src/strings.c (tracked in git)

fhprg-clean:
	rm -f tmp/fhprg_*.o $(FHPRG_ELF) $(FHPRG_MAP)
