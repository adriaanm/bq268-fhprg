# Makefile for bq268-edl-diag
#
# Builds Rust staticlib + assembly, links into ELF, wraps with MBN.

AS       = arm-none-eabi-gcc
LD       = arm-none-eabi-ld
OBJCOPY  = arm-none-eabi-objcopy

# Use GCC to preprocess+assemble (entry.S includes msm8909.h)
ASFLAGS  = -c -march=armv7-a -mthumb -mfloat-abi=soft -I ../archive/src_minimal

# All build output goes to ../target
export CARGO_TARGET_DIR := ../target
OUTDIR   = ../target

# Rust staticlib output
RUST_LIB = $(OUTDIR)/thumbv7a-none-eabi/release/libbq268_edl_diag.a

# Assembly sources
ASM_SRCS = entry.S ddr_blob.S ddr_config.S
ASM_OBJS = $(addprefix $(OUTDIR)/,$(ASM_SRCS:.S=.o))

# Output
ELF      = $(OUTDIR)/bq268_edl_diag.elf
BIN      = $(OUTDIR)/bq268_edl_diag.bin
MBN      = $(OUTDIR)/bq268_edl_diag.mbn

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
	rm -f $(ASM_OBJS) $(ELF) $(BIN) $(MBN)
	cargo clean
