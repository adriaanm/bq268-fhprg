# Minimal Firehose Programmer — Implementation Status

## What This Is

A self-contained firehose programmer for **MSM8909** (BQ268 UdoSmart) that gets loaded
onto the device via **EDL/Sahara** mode. Instead of using the firehose XML protocol to
receive data over USB, it embeds a gzipped aboot image directly in the ELF. The runtime
sequence is: init clocks → init DDR → init eMMC → decompress payload → write to partition → reboot.

**Why**: The stock firehose programmer (`fhprg_peek.bin`) has a software write-protection
check in the eMMC write path (EXT_CSD byte 160). This minimal programmer removes that
check, allowing writes to WP-protected partitions.

All source lives in `src_minimal/`. Build with `make minimal-elf`.

## Implementation Status: COMPLETE (all 9 tasks done)

The ELF links and produces a valid binary. **Not yet tested on hardware.**

## Target Device

- **Device**: BQ268 UdoSmart
- **SoC**: Qualcomm MSM8909 (Snapdragon 210), ARMv7-A, 32-bit
- **Bootloader**: unlocked (`fastboot: unlocked=yes, secure=no`)
- **eMMC**: 3.6 GiB, 7634944 sectors × 512 bytes

## GPT Partition Table (from `docs/printgpt.md`)

Key partitions:

| Partition  | Start Sector | Sectors | Size  | Notes |
|------------|-------------|---------|-------|-------|
| `splash`   | 2663442     | 20480   | 10 MB | **Current debug target** (expendable) |
| `aboot`    | 2623488     | 2048    | 1 MB  | Real target (uncomment in main.c) |
| `abootbak` | 2625536     | 2048    | 1 MB  | Backup aboot |
| `boot`     | 269408      | 65536   | 32 MB | Kernel boot image |

The `TARGET_START_SECTOR` in `main.c` currently points to **splash** for safe debugging.
Change to 2623488 for the real aboot flash.

## How Sahara Loading Works

1. Device enters EDL mode (USB VID:PID `05c6:9008`)
2. PBL (Primary Boot Loader) speaks Sahara protocol over USB
3. Host sends our ELF file (`tmp/minimal.elf`)
4. PBL parses ELF program headers and loads each LOAD segment to its VirtAddr
5. PBL jumps to the ELF entry point (`0x08006001`, Thumb mode)

The ELF must have the same segment layout as the original `fhprg_peek.bin` — IMEM
segments loaded directly to 0x00220000/0x00223000, main code to OCIMEM at 0x08006000.

## Memory Map

```
Address         Region              Size        Content
──────────────  ──────────────────  ──────────  ──────────────────────
0x00220000      IMEM_CODE (SRAM)    12 KB       DDR driver code (loaded by Sahara)
0x00223000      IMEM_DATA (SRAM)    4 KB        DDR driver data (loaded by Sahara)
0x004ab000      PSHOLD              4 bytes     Write 0 to trigger reset
0x01821000      GPLL0_MODE          MMIO        PLL enable register
0x01842004      GCC_SDCC1_APPS      MMIO        SDCC1 APPS clock enable
0x01842008      GCC_SDCC1_AHB       MMIO        SDCC1 AHB clock enable
0x07824000      SDCC1               MMIO        eMMC controller registers
0x08006000      CODE (OCIMEM)       280 KB      .text + .rodata + embedded payload
0x0804c000      DATA (OCIMEM)       68 KB       .data (24 bytes) + .bss (296 bytes)
0x80000000      DDR                 2 MB        Decompression buffer (NOLOAD)
```

## Sahara ELF Requirements

The Qualcomm PBL (Primary Boot Loader) loads programmer ELFs via the Sahara protocol.
Even on **unlocked devices** (`secure=no`), the PBL enforces structural requirements
on the ELF beyond what a standard toolchain produces. Failing these causes either
`END_TRANSFER` with status `0x23` (explicit rejection) or **silent failure** (PBL
loads all data but never transfers control — manifests as a USB timeout with no
error code).

### MBN Hash Table (required)

The PBL requires an **MBN hash table segment** in the ELF. Without it, Sahara
rejects the image immediately after reading the program headers with status
`0x23` (`kSaharaStatusHashTableNotFound`).

The hash table is carried in two `PT_NULL` program headers that must appear
**before** any `PT_LOAD` headers:

| Segment | Type   | Content | Notes |
|---------|--------|---------|-------|
| NULL 0  | Header | ELF header + program header table | `filesz` = ehdr + all phdrs, `vaddr` = 0, **`p_flags` = `0x07000000`** |
| NULL 1  | Hashes | 40-byte MBN header + SHA-256 hashes + signature + cert chain | `vaddr` = `0x87c5a000`, align `0x1000`, **`p_flags` = `0x02200000`** |

**Critical**: The `p_flags` values on the NULL segments are Qualcomm-specific and
**must** be set exactly as shown. `readelf` does not display flags for NULL segments,
so they appear blank, but the PBL uses them to identify the hash table. Setting them
to zero results in the same `0x23` (HashTableNotFound) rejection.

**MBN hash header** (40 bytes at start of NULL 1 data):

| Offset | Field | Value | Notes |
|--------|-------|-------|-------|
| 0x00 | image_id | `0x15` | Firehose programmer image type |
| 0x04 | version | `3` | MBN format version |
| 0x08 | sw_id | `0` | Unused on unlocked devices |
| 0x0C | hash_addr | base + 40 | VA of hash data (right after header) |
| 0x10 | hash_size | varies | Total bytes after header (hashes + sig + cert) |
| 0x14 | sig_offset | N × 32 | Offset from hash_addr to signature |
| 0x18 | sig_addr | base + 40 + N×32 | VA of signature block |
| 0x1C | sig_size | `0x100` | 256 bytes (zeros on unlocked) |
| 0x20 | cert_chain_addr | sig_addr + 0x100 | VA of cert chain |
| 0x24 | cert_chain_size | `0x1800` | 6144 bytes (zeros on unlocked) |

After the header: one 32-byte SHA-256 hash per program header (including the
NULL headers themselves), then `0x100` bytes of signature, then `0x1800` bytes
of certificate chain. On unlocked devices the hash values, signature, and cert
chain can all be zeros — the PBL checks that the **structure exists** but skips
cryptographic verification.

### Section Headers

The ELF must have **no section headers** (`e_shoff = 0`, `e_shnum = 0`).
The stock `fhprg_peek.bin` is fully stripped. The linker produces section
headers by default; `mbn_wrap.py` removes them.

**However**, `e_shentsize` must be `0x28` (40), matching the original — even
though `e_shnum = 0`. Setting it to 0 causes silent rejection.

### ELF Flags

The ELF flags field must be `0x05000002` (Version5 EABI). The linker's default
`0x05000200` (soft-float ABI flag) differs and may cause rejection.

### Entry Point

The entry point must be **ARM mode** (no Thumb bit set). The PBL jumps to the
entry address directly without using `BX`, so Thumb code at the entry point
will be executed as ARM instructions and crash. Use an ARM-mode stub that
switches to Thumb via `BX` if the rest of the code is Thumb.

### Segment Flags and Alignment

Segment flags and alignment values must match what the PBL expects. The linker
may set incorrect flags (e.g., `R` instead of `R E` for executable IMEM code).

**Critical**: The main code segment at `0x08006000` requires `p_flags` bit 31
set (`0x80000005` instead of `0x00000005`). This is a Qualcomm-specific flag
marking the primary executable segment. `readelf` displays this as `R E` (same
as without bit 31), hiding the difference. Without it, the PBL silently fails
to transfer control.

All `p_paddr` values must equal `p_vaddr`. The linker may set `p_paddr` to the
LMA (load address in CODE region) for `.data` sections using `AT>` directives.
The PBL uses `p_paddr` to determine where to load segment data.

Required values (from `fhprg_peek.bin`):

| VirtAddr | Flags | Align | Content |
|----------|-------|-------|---------|
| 0x00220000 | `0x00000005` (R E) | 0x10 | DDR driver code (IMEM) |
| 0x00223000 | `0x00000006` (RW) | 0x8 | DDR driver data (IMEM) |
| 0x08006000 | `0x80000005` (R E + QC) | 0x20 | Main program code (OCIMEM) |
| 0x08046000 | `0x00000006` (RW) | 0x4 | BSS region (filesz=0, memsz=0x6000) |
| 0x0804c000 | `0x00000006` (RW) | 0x1000 | Initialized data + BSS |

### Zero-Sized Segments

The original ELF includes three `PT_LOAD` segments with `filesz = 0` that
reserve memory regions. All three are required:

| VirtAddr | MemSiz | Align | Purpose |
|----------|--------|-------|---------|
| 0x08046000 | 0x6000 | 0x4 | BSS / uninitialized data |
| 0x80000000 | 0x201400 | 0x1000 | DDR working memory |
| 0x87c00000 | 0x59e98 | 0x4000 | DDR region 2 |

### Post-Processing

`tools/mbn_wrap.py` handles all of the above: it takes the linker output,
strips section headers, inserts the two NULL segments with a valid MBN hash
table, fixes segment flags/alignment/paddr, adds the zero-sized segments,
and sets `e_shentsize` and `e_flags`. It is invoked automatically by
`make minimal-elf`.

## ELF Structure (`tmp/minimal.elf`)

After MBN wrapping, the final ELF matches the original's 9-segment structure:

```
Segment  Type   VirtAddr     PhysAddr     FileSiz  MemSiz   Flg         Content
───────  ────── ──────────── ──────────── ──────── ──────── ─────────── ───────────────────
NULL     header 0x00000000   0x00000000   0x00154  0x00000  0x07000000  ELF + phdr table
NULL     hashes 0x87c5a000   0x87c5a000   0x01a48  0x02000  0x02200000  MBN hash table
LOAD            0x00220000   0x00220000   0x02914  0x02914  0x00000005  DDR driver code
LOAD            0x00223000   0x00223000   0x00970  0x00970  0x00000006  DDR driver data
LOAD            0x08006000   0x08006000   varies   varies   0x80000005  .text + .rodata
LOAD            0x08046000   0x08046000   0x00000  0x06000  0x00000006  BSS region
LOAD            0x0804c000   0x0804c000   0x00010  0x002c0  0x00000006  .data + .bss
LOAD            0x80000000   0x80000000   0x00000  0x201400 0x00000006  DDR buffer
LOAD            0x87c00000   0x87c00000   0x00000  0x59e98  0x00000006  DDR region 2
```

Entry point: `0x08006000` (ARM mode, no Thumb bit — ARM stub switches to Thumb)

### Size Budget (actual)

| Section     | Size      | Notes |
|-------------|-----------|-------|
| .text       | 9,052 B   | entry.S + all C code |
| .rodata     | 239,712 B | embedded payload (239,148 B gz) + constants |
| .ddr_code   | 10,516 B  | DDR driver binary blob |
| .ddr_data   | 2,416 B   | DDR driver data blob |
| .data       | 24 B      | SDCC state vars, ctype pointer |
| .bss        | 296 B     | Zeroed at startup |
| **CODE total** | **248,764 B** | **limit: 294,912 B (46 KB headroom)** |

## Boot Sequence (`entry.S` → `main()`)

### Assembly startup (`entry.S`)

1. Set VBAR (exception vector base → minimal hang-on-exception table)
2. Set SP to top of DATA region (`_stack_top = 0x0804c000 + 0x11000`)
3. Copy `.data` section from LMA (in CODE) to VMA (in DATA) — 24 bytes
4. Zero BSS (`__bss_start` to `__bss_end`) — 296 bytes
5. Enable GPLL0 PLL: set bits [2:0] at `0x01821000`, poll bit 31 for lock
6. Call DDR init: `BLX 0x00222780` with r0=0x08600190 (DDR config base)
   - DDR driver was already loaded to IMEM by Sahara — no copy needed
   - BLX switches from Thumb to ARM mode (DDR driver is ARM code)
7. Enable SDCC1 AHB clock: set bit 0 at `0x01842008`, poll bit 31 for CLK_OFF=0
8. Enable SDCC1 APPS clock: set bit 0 at `0x01842004`, poll bit 31 for CLK_OFF=0
9. `BL main`

### C main (`main.c`, guarded by `#ifdef MINIMAL_EMBEDDED_PAYLOAD`)

1. `sdcc_init_bases()` — set SDCC controller register base addresses
2. `mmc_open_device(0, 0)` — full eMMC card init: CMD0→CMD1→CMD2→CMD3→CMD7→CMD8→bus width→speed
3. Set up storage context: device handle at ctx+0x04, partition index 0 at ctx+0x26
4. `tinf_gzip_uncompress()` — decompress embedded `aboot_new.bin.gz` into DDR buffer at 0x80000000
5. Write decompressed data to eMMC in 128-sector (64 KB) chunks via `mmc_write_sectors()`
   - Target: `TARGET_START_SECTOR` (currently splash @ 2663442)
6. Reboot via PSHOLD (`*(volatile uint *)0x004ab000 = 0`)
7. Hang if PSHOLD didn't work

On any error (init fail, decompress fail, write fail): infinite loop (`while(1)`).
No error reporting — there's no USB transport in embedded mode.

## Source File Map (`src_minimal/`)

### Core files (always compiled)

| File | Lines | Purpose |
|------|-------|---------|
| `entry.S` | 183 | ARM startup: clocks, DDR init, SDCC clocks, branch to main |
| `main.c` | 153 | Decompress + write logic (guarded `#ifdef MINIMAL_EMBEDDED_PAYLOAD`) |
| `ddr_blob.S` | 30 | `.incbin` of DDR driver code+data extracted from fhprg_peek.bin |
| `aboot_payload.S` | 22 | `.incbin` of `aboot_new.bin.gz` embedded payload |
| `minimal.ld` | 101 | Linker script with IMEM/CODE/DATA/DDR memory regions |
| `tinf.c` | 786 | Jørgen Ibsen's tinf gzip decompressor (zlib license) |
| `tinf.h` | 20 | tinf API: `tinf_gzip_uncompress()`, `TINF_OK`, etc. |
| `libc_impl.c` | 193 | `memset`, `memcpy`, `bit_reverse`, `thunk_FUN_080199b4` (delay), `strtoll`, `get_ctype_table` |
| `firehose.h` | — | Common types and function declarations |
| `libc_glue.h` | — | Additional type/function declarations |

### eMMC driver stack (always compiled)

| File | Purpose |
|------|---------|
| `card_init.c` | eMMC card initialization (CMD0/1/2/3/7/8, bus width, speed) |
| `emmc.c` | eMMC read/write/erase, **WP check removed** from `mmc_write_sectors` and `mmc_write_blocks` |
| `sdcc_helpers.c` | SDCC controller helpers (clock config, reset, FIFO) |
| `sdcc_regs.c` | SDCC register base address table |
| `storage.c` | Partition management, storage context |
| `platform.c` | Platform/board detection stubs |
| `globals.c` | Global variables (SDCC state + protocol strings when not embedded) |

### Firehose protocol (compiled out by `MINIMAL_EMBEDDED_PAYLOAD`)

| File | Purpose |
|------|---------|
| `dispatch.c` | Firehose command router |
| `handlers.c` | Command handlers (configure, program, read, digest) |
| `protocol.c` | Logging, response building, transfer callbacks |
| `xml.c` | XML parser & writer |
| `transport.c` | USB transport stubs |

These files are wrapped in `#ifndef MINIMAL_EMBEDDED_PAYLOAD`. They compile to nothing
in embedded mode but remain available for a hypothetical USB-transport fallback build.

## Write Protection Bypass

The core change is in `emmc.c`:

**`mmc_write_sectors`** (orig addr 0x08034228): Deleted the `if (*(char *)(puVar3[0x24] + 0xa0) != '\0') return 0x1b;` check. This checked EXT_CSD byte 160 (WP status) and refused writes if WP was set.

**`mmc_write_blocks`** (orig addr 0x08034170): Changed `else if (*(char *)(puVar3[0x24] + 0xa0) == '\0')` to `else if (1)` — unconditionally takes the write path.

## Build

```bash
make minimal-elf    # compile + link → tmp/minimal.elf
make minimal        # compile only, show undefined symbols
make minimal-clean  # remove build artifacts
```

Toolchain:
- **C compiler**: `clang --target=arm-none-eabi -mthumb -march=armv7-a -mfloat-abi=soft -mno-movt -Oz`
- **Assembler**: `arm-none-eabi-as -march=armv7-a -mthumb -mfloat-abi=soft`
- **Linker**: `arm-none-eabi-ld` with `libgcc.a` (for `__aeabi_uidiv`)
- **No newlib** — `memset`/`memcpy` provided by `libc_impl.c`

## Key Design Decisions

1. **Sahara loads IMEM directly** — The DDR driver blobs have VMA == LMA in the ELF
   (0x00220000 and 0x00223000). Sahara/PBL loads each LOAD segment to its VirtAddr.
   No runtime copy needed. This matches the original `fhprg_peek.bin` layout.

2. **No flat binary** — Sahara loads ELF files, not raw binaries. The `objcopy -O binary`
   step was removed because the address gap between IMEM (0x00220000) and CODE (0x08006000)
   would produce a 132 MB file filled with zeros.

3. **`.data` LMA in CODE** — The 24-byte `.data` section is stored at its LMA within the
   CODE region and copied to its VMA in DATA by entry.S at startup. This is standard
   for embedded systems where initialized data lives in ROM but runs from RAM.

4. **No hash fixup** — The original plan included `tools/fix_hashes.py` but this applies
   to patched versions of the stock binary. Our ELF is built from scratch and doesn't
   have the original's hash table structure.

5. **Debug target = splash** — The splash partition (10 MB, expendable) is used as the
   write target during testing. Switch `TARGET_START_SECTOR` to 2623488 for real aboot.

## Known Risks / Open Questions

1. **DDR init parameters** — `entry.S` calls DDR init with `r0=0x08600190` (HWIO base).
   This was extracted from the original binary's call site. If the DDR driver expects
   different parameters or pre-conditions we haven't set up, DDR init may fail silently
   and writes to 0x80000000 will fault.

2. **Clock configuration** — We only enable GPLL0 and SDCC1 clocks. The original binary
   does a much more elaborate init sequence (XO, BIMC, QTimer, MPU regions, DLL/PHY config).
   If SDCC1 needs a specific clock frequency or DLL calibration, card init may fail.

3. **No error feedback** — All errors result in `while(1)` hangs. The device will appear
   to do nothing. Consider toggling a GPIO (LED) or using the QTimer to distinguish
   failure points by hang time.

4. **Decompression buffer overlap** — DDR buffer at 0x80000000 is used for decompression.
   The DDR driver itself may use DDR for training data. If there's overlap, decompression
   may corrupt DDR driver state (unlikely since DDR init should be complete before main).

5. **CMD timing** — The SDCC clock source may default to CXO (19.2 MHz) without the full
   clock tree setup. This is slow but should work for initialization. High-speed modes
   (HS200/HS400) may fail if GPLL0-derived clocks aren't properly routed to SDCC.

## Files Outside `src_minimal/`

- `aboot_new.bin.gz` — The gzipped aboot payload (239,148 bytes). Must exist at repo root.
- `tmp/ddr_driver.bin` — DDR driver code extracted from fhprg_peek.bin (10,516 bytes)
- `tmp/ddr_data.bin` — DDR driver data extracted from fhprg_peek.bin (2,416 bytes)
- `tmp/minimal.elf` — Build output (388 KB ELF)
- `tmp/minimal.map` — Linker map file

## Testing Plan

1. Load `tmp/minimal.elf` via Sahara using the Go client
2. First test target: splash partition (2663442) — verify writes persist by reading back
3. If writes work: switch to aboot partition (2623488) and flash real payload
4. Verify by reading back the partition content and comparing SHA256
5. If writes don't persist: investigate whether hardware WP (CMD28 groups) blocks writes
   even with the software check removed — may need CMD29 CLR_WRITE_PROT
