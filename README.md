# qc_firehose

**This is untested, work-in-progress research software.** It targets a single
device (BQ Aquaris M5, MSM8909) and has never been validated outside of that
context. Use at your own risk. The authors accept no liability for bricked
devices, lost data, or any other outcome.

## What this is

A custom Qualcomm Firehose programmer for the MSM8909 SoC, built by
decompiling the stock programmer in Ghidra and reimplementing the subset
needed to read and write eMMC partitions over EDL (Emergency Download) mode.

The project was built almost entirely with [Claude Code](https://claude.ai/code).

There are two main pieces:

### Minimal programmer (`src_minimal/`)

A bare-metal ARM program loaded by the SoC's Primary Boot Loader (PBL) via the
Sahara protocol. It initializes DDR, clocks, eMMC, and USB, then speaks the
Firehose XML protocol to accept read/write commands from the host.

Build:

```bash
make minimal-elf    # produces tmp/minimal.elf (MBN-wrapped for Sahara)
```

### Host client (`client/`)

A Go CLI (`bq268-edl`) that handles the Sahara handshake, uploads the
programmer, and issues Firehose commands (backup, restore, read, write,
verify, print GPT).

Build:

```bash
cd client && go build -o bq268-edl .
```

Usage:

```bash
bq268-edl --loader tmp/minimal.elf backup aboot aboot_backup.bin
bq268-edl --loader tmp/minimal.elf restore aboot aboot_new.bin
bq268-edl --loader tmp/minimal.elf printgpt
```

### Supporting tools (`tools/`)

- `tools/usb_diag.py` — interactive USB console for the programmer's
  diagnostic mode (register peek/poke, memory dump, DDR test)
- `tools/mbn_wrap.py` — wraps a raw ELF into Qualcomm MBN format with hash
  table segments for Sahara
- `tools/fhprg_init_emu.py` — Unicorn-based emulator tracing the original
  programmer's init sequence
- `tools/ghidra_analyze_fhprg.py` — headless Ghidra decompilation pipeline

## Provenance

The eMMC driver code in `src_minimal/` was decompiled from the stock Qualcomm
Firehose programmer binary for the MSM8909 using Ghidra, then manually cleaned
up and restructured. The DDR initialization blob (`src_minimal/ddr_blob.S`) is
extracted verbatim from the original binary. Register definitions in
`src_minimal/msm8909.h` are derived from the
[Little Kernel](https://source.codeaurora.org/quic/la/kernel/lk/) source for
MSM8909.

## License

This project is released under the [Unlicense](https://unlicense.org/) — public
domain. See `LICENSE` for the full text.

The Go client in `client/` is separately licensed under GPL-3.0.
