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

.PHONY: all clean preprocess analyze diff-asm match-symbols extract-code \
        disasm-orig disasm-recomp venv strings extract-data link hybrid-diff

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

clean:
	rm -f $(OBJ) $(ORIG_ASM) $(RECOMP_ASM) $(DIFF_JSON)
	rm -f $(DATA_OBJ) $(LINKED_ELF) $(LINKED_BIN) tmp/aboot_linked.map
	rm -f src/aboot.c
	# Keep tmp/ (contains Ghidra analysis and generated blobs)
	# Keep src/strings.c (tracked in git)
