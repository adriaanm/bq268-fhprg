# Makefile for Rust minimal programmer
#
# Builds Rust staticlib + assembly, links into ELF, wraps with MBN.

AS       = arm-none-eabi-gcc
LD       = arm-none-eabi-ld
OBJCOPY  = arm-none-eabi-objcopy

# Use GCC to preprocess+assemble (entry.S includes msm8909.h)
ASFLAGS  = -c -march=armv7-a -mthumb -mfloat-abi=soft -I ../archive/src_minimal

# Rust staticlib output
RUST_LIB = target/thumbv7a-none-eabi/release/libbq268_edl_diag.a

# Assembly sources
ASM_SRCS = entry.S ddr_blob.S ddr_config.S
ASM_OBJS = $(addprefix tmp/,$(ASM_SRCS:.S=.o))

# Output
OUTDIR   = tmp
ELF      = $(OUTDIR)/minimal_rust.elf
BIN      = $(OUTDIR)/minimal_rust.bin
MBN      = $(OUTDIR)/minimal_rust.mbn

LDSCRIPT = minimal.ld
MBN_WRAP = ../tools/mbn_wrap.py

.PHONY: all clean rust elf

all: $(MBN)

elf: $(ELF)

# Build Rust staticlib
rust: $(RUST_LIB)

$(RUST_LIB): $(wildcard rust/*.rs) Cargo.toml
	cargo +nightly build --release

# Assemble .S files
$(OUTDIR)/%.o: asm/%.S | $(OUTDIR)
	$(AS) $(ASFLAGS) -o $@ $<

$(OUTDIR):
	mkdir -p $(OUTDIR)

# Link everything
$(ELF): $(ASM_OBJS) $(RUST_LIB) $(LDSCRIPT)
	$(LD) -T $(LDSCRIPT) --gc-sections -o $@ $(ASM_OBJS) $(RUST_LIB)

# Binary extraction
$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

# MBN wrap for Sahara
$(MBN): $(ELF)
	python3 $(MBN_WRAP) $< $@

clean:
	rm -rf $(OUTDIR)
	cargo clean
