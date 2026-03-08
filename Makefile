# Minimal Qualcomm firehose programmer for msm8909 (ARM Thumb2)

CC      = clang
LD      = arm-none-eabi-ld
AS      = arm-none-eabi-gcc

CFLAGS  = --target=arm-none-eabi -mthumb -march=armv7-a -mfloat-abi=soft \
           -mno-movt -Oz -fomit-frame-pointer -std=gnu89 \
           -Wall -Wextra \
           -Wunused-function -Wunused-variable \
           -Warray-bounds -Wformat -Wformat-security \
           -Wimplicit-function-declaration \
           -Wno-unused-parameter -Wno-sign-compare \
           -Wno-missing-field-initializers -Wno-old-style-definition \
           -Wno-deprecated-non-prototype \
           -ffreestanding -ffunction-sections -fdata-sections \
           -I src_minimal

LIBGCC    = $(shell arm-none-eabi-gcc -mthumb -march=armv7-a -mfloat-abi=soft --print-libgcc-file-name)
LD_SCRIPT = src_minimal/minimal.ld
ELF       = tmp/minimal.elf
MAP       = tmp/minimal.map
DEBUG_ELF = tmp/minimal_debug.elf

# C sources (auto-discovered)
SRC     = $(wildcard src_minimal/*.c)
OBJ     = $(patsubst src_minimal/%.c,tmp/minimal_%.o,$(SRC))

# Assembly sources
ASM_SRC = src_minimal/entry.S src_minimal/ddr_blob.S src_minimal/ddr_config.S
ASM_OBJ = $(patsubst src_minimal/%.S,tmp/minimal_%.o,$(ASM_SRC))

.PHONY: all elf debug-elf clean

all: elf

# C compilation
tmp/minimal_%.o: src_minimal/%.c src_minimal/globals.h src_minimal/libc_glue.h
	@mkdir -p tmp
	$(CC) $(CFLAGS) -c $< -o $@

# Assembly compilation
tmp/minimal_%.o: src_minimal/%.S src_minimal/msm8909.h
	@mkdir -p tmp
	$(AS) -c -march=armv7-a -mthumb -mfloat-abi=soft -I src_minimal -o $@ $<

# Link + MBN wrap for Sahara loading
elf: $(OBJ) $(ASM_OBJ)
	@echo "[*] Linking minimal ELF..."
	$(LD) -T $(LD_SCRIPT) -o $(ELF) $(OBJ) $(ASM_OBJ) \
		$(LIBGCC) -Map $(MAP) --no-warn-execstack
	@echo "[*] CODE segment: $$(arm-none-eabi-size -A $(ELF) | awk '/.text/{t+=$$2} /.rodata/{t+=$$2} END{print t}') bytes (limit: 294912)"
	@echo "[*] Adding MBN hash table for Sahara..."
	python3 tools/mbn_wrap.py $(ELF)
	@echo "[*] Final ELF: $$(stat -c %s $(ELF)) bytes"

# Debug ELF with symbols preserved (no MBN wrapping) — for emulator use
debug-elf: $(OBJ) $(ASM_OBJ)
	@echo "[*] Linking minimal debug ELF (with symbols, no MBN)..."
	$(LD) -T $(LD_SCRIPT) -o $(DEBUG_ELF) $(OBJ) $(ASM_OBJ) \
		$(LIBGCC) -Map $(MAP) --no-warn-execstack
	@echo "[*] Debug ELF: $(DEBUG_ELF) ($$(stat -c %s $(DEBUG_ELF)) bytes)"

clean:
	rm -f tmp/minimal_*.o $(ELF) $(DEBUG_ELF) $(MAP)
