# bq268-edl-diag

**This is untested, work-in-progress research software.** It targets a single
device (BQ268/ABBREE GP-268, MSM8909) and has never been validated outside of that
context. Use at your own risk. The authors accept no liability for bricked
devices, lost data, or any other outcome.

## What this is

A bare-metal ARM diagnostic tool for the MSM8909 SoC, written in Rust
(no_std). It is loaded via Qualcomm's EDL (Emergency Download) mode using the
Sahara protocol and provides an interactive USB console for low-level hardware
access: register peek/poke, memory dumps, eMMC read/write, GPT partition
inspection, and verified partition flashing with SHA-256 checksums.

The eMMC driver and hardware init sequences were reverse-engineered from the
stock Qualcomm Firehose programmer binary using Ghidra. DDR initialization
uses a binary blob extracted from the original.

The project was built almost entirely with [Claude Code](https://claude.ai/code).

## Building

Requires: Rust nightly (`thumbv7a-none-eabi` target), `arm-none-eabi-gcc`,
`arm-none-eabi-ld`.

```bash
make            # Build MBN-wrapped ELF for Sahara upload
make clean      # Clean build artifacts
```

## Usage

```bash
# Upload programmer and open interactive console
uv run tools/usb_diag.py --flash target/bq268_edl_diag.mbn

# Upload and flash a partition image (verified)
uv run tools/usb_diag.py --flash target/bq268_edl_diag.mbn --flash-partition aboot aboot.bin
```

## Console Commands

| Cmd | Description |
|-----|-------------|
| `r ADDR` | Read 32-bit word |
| `w ADDR VAL` | Write 32-bit word |
| `d ADDR LEN` | Hex dump memory |
| `R ADDR LEN` | Raw memory dump to file (binary + SHA-256) |
| `i` | System info (page tables, control regs) |
| `t` | DDR memory test |
| `e` | Init eMMC |
| `c` | eMMC card status |
| `s SECTOR` | Read eMMC sector (hex dump) |
| `S SECTOR BYTE` | Write eMMC sector (fill with byte) |
| `G` | Read GPT partition table |
| `F NAME` | Verified flash partition (GPT lookup + SHA-256) |
| `F SECTOR COUNT` | Verified flash (manual hex sector + count) |

## Provenance

The eMMC driver was decompiled from the stock Qualcomm Firehose programmer
binary using Ghidra, then manually cleaned up and rewritten in Rust. The DDR
initialization blob (`src/blobs/`) is extracted verbatim from the original
binary. Register definitions are derived from the
[Little Kernel](https://source.codeaurora.org/quic/la/kernel/lk/) source for
MSM8909.

## License

This project is released under the [Unlicense](https://unlicense.org/) — public
domain. See `LICENSE` for the full text.
