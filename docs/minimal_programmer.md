# Minimal Firehose Programmer

## Guiding Principle

**Replicate the original firehose programmer.** The original `fhprg_peek.bin` is a
known-working reference that boots, initializes hardware, and communicates over USB on
this exact SoC. Every subsystem in the minimal programmer (USB, clocks, DDR, eMMC)
must be implemented by studying the decompiled original (`src/fhprg/`) and replicating
its register sequences, init order, and protocol handling for the subset of functionality
we need.

Do not invent alternative approaches (e.g., "skip the PHY config", "inherit PBL state
instead of reinitializing") without explicit user consent. Deviating from the original's
proven behavior is the primary source of hard-to-debug hardware failures on this platform.
When something doesn't work, the first question is always: "what does the original do?"

## Goal & Current Status

A self-contained programmer for **MSM8909** (BQ268 UdoSmart) loaded via **EDL/Sahara** mode.
Currently operates as a **USB diagnostic console** — interactive register/memory access over
USB bulk transfers. Future: embed a gzipped aboot image and flash it directly.

**Why**: The stock firehose programmer (`fhprg_peek.bin`) has a software write-protection
check in the eMMC write path (EXT_CSD byte 160). This minimal programmer removes that
check, allowing writes to WP-protected partitions.

**Current status**: DDR init confirmed working. USB driver inherits PBL's session
(no reset, no re-enumeration). Interactive diagnostic console over USB bulk transfers.

All source lives in `src_minimal/`. Build with `make minimal-elf`.

### Target Device

- **Device**: BQ268 UdoSmart
- **SoC**: Qualcomm MSM8909 (Snapdragon 210), ARMv7-A, 32-bit
- **Bootloader**: unlocked (`fastboot: unlocked=yes, secure=no`)
- **eMMC**: 3.6 GiB, 7634944 sectors x 512 bytes

### Key Partitions

| Partition  | Start Sector | Sectors | Size  | Notes |
|------------|-------------|---------|-------|-------|
| `splash`   | 2663442     | 20480   | 10 MB | Debug target (expendable) |
| `aboot`    | 2623488     | 2048    | 1 MB  | Real target |
| `abootbak` | 2625536     | 2048    | 1 MB  | Backup aboot |
| `boot`     | 269408      | 65536   | 32 MB | Kernel boot image |

## Architecture

### Memory Map

```
Address         Region              Size        Content
--------------  ------------------  ----------  ----------------------
0x00220000      IMEM_CODE (SRAM)    12 KB       DDR driver code (loaded by Sahara)
0x00223000      IMEM_DATA (SRAM)    4 KB        DDR driver data (loaded by Sahara)
0x004ab000      PSHOLD              4 bytes     Write 0 to trigger reset
0x01821000      GPLL0_MODE          MMIO        PLL enable register
0x07824000      SDCC1               MMIO        eMMC controller registers
0x078D9000      USB HS              MMIO        ChipIdea USB 2.0 controller
0x08006000      CODE (OCIMEM)       ~100 KB     .text + .rodata
0x0804c000      DATA (OCIMEM)       68 KB       .data + .bss + stack
0x80000000      DDR                 128 MB      Working memory (NOLOAD)
```

### Boot Sequence (entry.S -> main())

1. Red LED on (USB stays alive with PBL's config)
2. VBAR + DACR + TTBCR
3. Stack + .data copy + BSS zero
4. GPLL0 PLL lock
5. Early clock init (GCC registers)
6. ddr_set_params
7. bimc_clock_init (branch clocks only, not PLL)
8. ddr_init (533 MHz)
9. SDCC1 clock enable
10. `main()` -> page table -> usb_init -> usb_poll -> banner -> command loop

See `docs/init_sequence.md` for full hardware init details.

### Source File Map (src_minimal/)

#### Core files (always compiled)

| File | Purpose |
|------|---------|
| `entry.S` | ARM startup: clocks, DDR init, SDCC clocks, branch to main |
| `main.c` | USB diagnostic console (register/memory commands) |
| `usb.c` | ChipIdea USB device driver (polling, bulk IN/OUT) |
| `usb.h` | USB driver API and register definitions |
| `msm8909.h` | Platform register definitions |
| `ddr_blob.S` | `.incbin` of DDR driver code+data |
| `aboot_payload.S` | `.incbin` of `aboot_new.bin.gz` embedded payload |
| `minimal.ld` | Linker script with IMEM/CODE/DATA/DDR memory regions |
| `libc_impl.c` | `memset`, `memcpy`, `bit_reverse`, delay, `strtoll` |
| `firehose.h` | Common types and function declarations |
| `libc_glue.h` | FUN_ name -> libc mapping |

#### eMMC driver stack (always compiled)

| File | Purpose |
|------|---------|
| `card_init.c` | eMMC card initialization (CMD0/1/2/3/7/8, bus width, speed) |
| `emmc.c` | eMMC read/write/erase, **WP check removed** |
| `sdcc_helpers.c` | SDCC controller helpers (clock config, reset, FIFO) |
| `sdcc_regs.c` | SDCC register base address table |
| `storage.c` | Partition management, storage context |
| `platform.c` | Platform/board detection stubs |
| `globals.c` | Global variables |

#### Firehose protocol (compiled out by MINIMAL_EMBEDDED_PAYLOAD)

| File | Purpose |
|------|---------|
| `dispatch.c` | Firehose command router |
| `handlers.c` | Command handlers (configure, program, read, digest) |
| `protocol.c` | Logging, response building, transfer callbacks |
| `xml.c` | XML parser & writer |
| `transport.c` | USB transport stubs |

## Function Mapping

### Libc Replacements (~24 functions -> libc)

| Original | Address | libc |
|----------|---------|------|
| FUN_08006906 | 0x08006906 | `strlen` |
| FUN_08006a30 | 0x08006a30 | `memcpy` |
| FUN_08006898 | 0x08006898 | `memcmp` |
| FUN_08006d14 | 0x08006d14 | `memset` |
| FUN_08006bdc | 0x08006bdc | `memmove` |
| FUN_08006860 | 0x08006860 | `strchr` |
| FUN_08006874 | 0x08006874 | `strstr` |
| FUN_080068f0 | 0x080068f0 | `strrchr` |
| FUN_080060c0 | 0x080060c0 | C `/` `%` on `uint64_t` |
| snprintf_buf (0x0800644c) | 0x0800644c | `snprintf` |
| printf engine (14 functions) | 0x08006020..0x08007268 | `vsnprintf` |

### emmc.c -- eMMC/SDCC driver

Source: `src/fhprg/fhprg_80327f8.c`

| | Address | Name | Status | Role |
|---|---------|------|--------|------|
| D | 0x08032af8 | FUN_08032af8 | complete | Get SDCC slot handle |
| D | 0x08032b94 | sdcc_command | **partial** | Low-level SDCC command dispatch |
| D | 0x08033654 | FUN_08033654 | **stub** | Write dispatch thunk |
| D | 0x08033656 | mmc_write_dispatch | **stub** | eMMC block write (ADMA/PIO) |
| S | 0x08033cbc | FUN_08033cbc | **stub** | Read dispatch |
| D | 0x08033ee8 | FUN_08033ee8 | complete | Get partition info struct |
| D | 0x08034228 | mmc_write_with_wp_check | complete | **THE WP GATE** (check removed) |
| D | 0x080348e0 | FUN_080348e0 | **stub** | eMMC capacity helper |
| D | 0x08034966 | FUN_08034966 | **stub** | Partition config helper |
| S | 0x08032ae4 | FUN_08032ae4 | **stub** | SDCC slot init |

### storage.c -- Partition & I/O abstraction

Source: `src/fhprg/fhprg_8037820.c`

| | Address | Name | Status | Role |
|---|---------|------|--------|------|
| S | 0x080381d8 | mmc_write_wrapper | complete | Write entry point from handlers |
| D | 0x08038206 | FUN_08038206 | complete | Partition select by index |
| D | 0x0803823e | FUN_0803823e | complete | Parse integer from string |
| S | 0x08038282 | FUN_08038282 | complete | strlcat-like string concat |
| D | 0x080382fa | strncmp_fh | complete | Case-insensitive strcmp |
| S | 0x08038014 | FUN_08038014 | complete | Read sectors wrapper |
| S | 0x08037c40 | FUN_08037c40 | complete | Partition selector (set to "all") |

### handlers.c -- Command handlers

Source: `src/fhprg/fhprg_8021ff0.c`

| | Address | Name | Status | Role |
|---|---------|------|--------|------|
| D | 0x08022a00 | handle_configure | complete | Storage init, set params |
| D | 0x08024484 | handle_program | complete | Write sectors from USB |
| D | 0x08024b04 | handle_read | complete | Read sectors to USB |
| S | 0x08022ec8 | handle_erase | complete | Erase sectors |
| S | 0x08023f64 | handle_peek | complete | Memory peek |
| S | 0x08024134 | handle_poke | complete | Memory poke |
| S | 0x08024350 | handle_power | complete | Reset/power |

### dispatch.c, protocol.c, xml.c, transport.c, platform.c, hotplug.c

All complete or stubbed. See `docs/minimal_impl.md` git history for full tables.

## USB Communication

### How It Works

The programmer **inherits PBL's USB session** — no controller reset, no re-enumeration.
PBL leaves the ChipIdea USB controller running (RS=1, D+ asserted) after Sahara upload.
The host handle from Sahara remains valid; the device appears continuously connected.

Critical constraint: **USB DMA cannot access OCIMEM** (0x0804xxxx). All USB buffers
(dTDs, data) must reside in DDR (0x80000000+). PBL's dQH table (in PBL SRAM) is used as-is.

See `docs/sahara_usb_handover.md` for the full investigation and hardware probing results.

#### Sequence

1. PBL loads our ELF via Sahara (same USB connection)
2. entry.S boots (~1-2s): DDR init with 50ms LED pulses
3. `main()` sets up page table (maps DDR), calls `usb_init()`
4. `usb_init()` flushes stale transfers, goes online immediately
5. Banner sent, interactive command loop — no enumeration delay

#### Host Side (tools/usb_diag.py)

```
usb_diag.py --flash tmp/minimal.elf
  1. Open USB device (05C6:9008)
  2. Sahara protocol (HELLO -> transfer -> DONE)
  3. Keep same handle (no disconnect/reconnect)
  4. Sleep 3s (configurable with --wait)
  5. Interactive mode on same bulk endpoints
```

#### Device Side (usb.c)

```
usb_init():
  1. Read ENDPOINTLISTADDR → PBL's dQH table
  2. Disable USB interrupts (USBINTR=0)
  3. Flush all endpoints (clear PBL's Sahara transfers)
  4. Clear USBSTS + ENDPTCOMPLETE
  5. Online immediately (usb_online=1)

usb_read() / usb_write():
  1. Copy data to/from DDR staging buffer (USB DMA can't reach OCIMEM)
  2. Queue dTD (in DDR) on PBL's dQH entry
  3. Prime endpoint, poll ENDPTCOMPLETE
```

#### Troubleshooting

- **No response after flash**: Increase boot wait with `--wait 5`.
- **USB reset during operation**: Driver returns -1, command loop retries.
- **DMA failures**: Verify DDR is initialized and page table maps 0x80000000+.

## Embedded Payload Mode

When `MINIMAL_EMBEDDED_PAYLOAD` is defined, `main.c` switches to autonomous flash mode:

1. `sdcc_init_bases()` -- set SDCC controller register base addresses
2. `mmc_open_device(0, 0)` -- full eMMC card init
3. `tinf_gzip_uncompress()` -- decompress embedded `aboot_new.bin.gz` into DDR at 0x80000000
4. Write decompressed data to eMMC in 128-sector (64 KB) chunks
5. Reboot via PSHOLD

Target partition configurable via `TARGET_START_SECTOR` (currently splash @ 2663442 for testing).

### Write Protection Bypass

In `emmc.c`:
- **`mmc_write_sectors`** (0x08034228): Deleted `EXT_CSD[160]` check that returned 0x1b on WP.
- **`mmc_write_blocks`** (0x08034170): Changed WP conditional to `else if (1)`.

## Build & Test

### Build

```bash
make minimal-elf    # compile + link -> tmp/minimal.elf
make minimal        # compile only, show undefined symbols
make minimal-clean  # remove build artifacts
```

Toolchain:
- **C compiler**: `clang --target=arm-none-eabi -mthumb -march=armv7-a -mfloat-abi=soft -mno-movt -Oz`
- **Assembler**: `arm-none-eabi-as -march=armv7-a -mthumb -mfloat-abi=soft`
- **Linker**: `arm-none-eabi-ld` with `libgcc.a` (for `__aeabi_uidiv`)
- **No newlib** -- `memset`/`memcpy` provided by `libc_impl.c`

### Test

```bash
# Upload and connect
uv run tools/usb_diag.py --flash tmp/minimal.elf

# If handle doesn't survive:
uv run tools/usb_diag.py --flash tmp/minimal.elf --reconnect

# With longer boot wait:
uv run tools/usb_diag.py --flash tmp/minimal.elf --wait 5

# Single command:
uv run tools/usb_diag.py --flash tmp/minimal.elf -c "i"
```

Expected LED behavior:
- Green pulses (fast, <1s) -> solid green -> **red** = success
- Green pulses -> solid green -> alternating red/green = USB timeout (try `--reconnect`)
- Green pulses -> solid green -> N x red blinks = specific USB error (see LED checkpoint docs)

### Sahara ELF Requirements

The PBL enforces structural requirements on the ELF even on unlocked devices:

- **MBN hash table**: Two `PT_NULL` segments with QC-specific `p_flags` (0x07000000, 0x02200000)
- **Section headers**: `e_shoff=0`, `e_shnum=0`, but `e_shentsize=0x28`
- **ELF flags**: `0x05000002` (Version5 EABI)
- **Entry point**: ARM mode (no Thumb bit) -- ARM stub switches to Thumb
- **Main code segment**: `p_flags` bit 31 set (0x80000005)
- **All `p_paddr` = `p_vaddr`**

`tools/mbn_wrap.py` handles all post-processing automatically.

### ELF Structure (tmp/minimal.elf)

```
Segment  Type   VirtAddr     FileSiz  MemSiz   Flg         Content
NULL     header 0x00000000   0x00174  0x00000  0x07000000  ELF + phdr table
NULL     hashes 0x87c5a000   0x01a68  0x02000  0x02200000  MBN hash table
LOAD            0x00220000   0x02914  0x02914  0x00000005  DDR driver code
LOAD            0x00223000   0x00970  0x00970  0x00000006  DDR driver data
LOAD            0x08006000   varies   varies   0x80000005  .text + .rodata
LOAD            0x08046000   0x00000  0x06000  0x00000006  BSS region
LOAD            0x0804c000   0x00010  0x00010  0x00000006  .data
LOAD            0x80000000   0x00000  0x201400 0x00000006  DDR buffer
LOAD            0x87c00000   0x00000  0x59e98  0x00000006  DDR region 2
```

## Working Notes

### Resolved Issues

- **DDR init**: Confirmed working at 533 MHz. Order: GPLL0 -> early_clock_init -> ddr_set_params -> bimc_clock_init -> ddr_init.
- **DDR blob callbacks**: 4 ARM + 5 Thumb mode callbacks with correct ISA encoding.
- **ICB config**: Skipped (was causing ddr_init alignment faults). DDR works without it.
- **PBL dQH location**: Below our BSS at 0x08046000. No conflict.
- **Checkpoint timing**: Reduced from 0.5s (8s total, killed USB) to 50ms pulses (<1s total).
- **SDCC clock registers**: Fixed wrong offsets (BCR vs CMD_RCGR).

### Open Questions

- **USB communication**: VID/PID fix applied (0x9008). Need hardware test to confirm host handle survives.
- **Hardware WP (CMD28 groups)**: Software WP check removed, but writes may still not persist. CMD29 CLR_WRITE_PROT may be needed.
- **eMMC clock speed**: Using CXO (19.2 MHz) default. High-speed modes may need GPLL0-derived clocks.

### Files Outside src_minimal/

- `aboot_new.bin.gz` -- The gzipped aboot payload (repo root)
- `tmp/ddr_driver.bin` -- DDR driver code extracted from fhprg_peek.bin
- `tmp/ddr_data.bin` -- DDR driver data extracted from fhprg_peek.bin
- `tmp/minimal.elf` -- Build output
- `tmp/minimal.map` -- Linker map file

### Key Design Decisions

1. **Sahara loads IMEM directly** -- DDR blobs have VMA == LMA. No runtime copy.
2. **No flat binary** -- Sahara loads ELFs. Address gap would produce 132 MB file.
3. **`.data` LMA in CODE** -- Standard embedded: init data stored in ROM, copied to RAM by entry.S.
4. **Debug target = splash** -- Expendable partition for testing. Switch to aboot when verified.
