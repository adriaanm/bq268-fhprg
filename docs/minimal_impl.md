# Minimal Firehose Programmer (src_minimal/)

## Context

The WP bypass patch doesn't work — writes don't persist despite bypassing the software WP check. We need to understand the full write path to find what else is blocking writes. The full decompilation is ~60K LoC / 1880 functions — too large to review meaningfully.

Dynamic tracing (Unicorn emulator running configure + read + write) shows only **52 functions** execute at runtime, expanding to **131 functions** in the static call closure — **~6,500 LoC (11%)**. Of those, ~24 are standard libc, leaving **~107 functions** to actually port.

`src_minimal/` contains clean, readable C organized by functional layer. Every function keeps a `/* orig: 0xADDRESS */` comment for traceability to the full decompilation in `src/fhprg/`.

## Libc Replacements (~24 functions -> libc)

Use standard libc instead of decompiled implementations:

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
| FUN_0800789c, FUN_08007a1c, FUN_0800795c | divmod10 helpers | inline or remove |

A `libc_glue.h` maps old symbol names to libc for any code that calls them by their FUN_ name.

## File Structure

```
src_minimal/
├── firehose.h        # Types, constants, forward decls, extern globals
├── libc_glue.h       # Maps FUN_08006906 -> strlen, etc.
├── emmc.c            # SDCC/eMMC driver: commands, WP check (20 functions)
├── storage.c         # Partition select, read/write wrappers (14 functions)
├── transport.c       # USB transport, DMA (4 functions)
├── handlers.c        # configure/program/read handlers (17 functions)
├── dispatch.c        # Command dispatch table (2 functions)
├── protocol.c        # Logging, response building, attr parsing (7 functions)
├── hotplug.c         # Storage enumeration (8 functions)
├── platform.c        # Timer, clock, boot helpers (12 functions)
└── xml.c             # XML parser + writer (17 functions)
```

## Build

```bash
make minimal          # compile all src_minimal/ -> tmp/minimal_*.o
make minimal-clean    # remove objects
```

Cross-reference any function back to full decompilation:
```bash
grep '0x08034228' src/fhprg/fhprg_80327f8.c   # full decompiled version
```

## Function Mapping by File

`D` = dynamically traced, `S` = static closure only.

### emmc.c — eMMC/SDCC driver
Source: `src/fhprg/fhprg_80327f8.c`

| | Address | Name | Status | Role |
|---|---------|------|--------|------|
| D | 0x08032af8 | FUN_08032af8 | complete | Get SDCC slot handle from global array |
| D | 0x08032b94 | sdcc_command | **partial** | Low-level SDCC command dispatch (~200 lines HW logic elided) |
| D | 0x08033654 | FUN_08033654 | **stub** | Write dispatch thunk (empty) |
| D | 0x08033656 | mmc_write_dispatch | **stub** | eMMC block write (ADMA/PIO, CMD24/CMD25) |
| S | 0x08033cbc | FUN_08033cbc | **stub** | Read dispatch |
| D | 0x08033ee8 | FUN_08033ee8 | complete | Get partition info struct |
| D | 0x08034228 | mmc_write_with_wp_check | complete | **THE WP GATE**: checks EXT_CSD[160], returns 0x1b if protected |
| D | 0x080348e0 | FUN_080348e0 | **stub** | eMMC capacity helper |
| D | 0x08034966 | FUN_08034966 | **stub** | Partition config helper |
| S | 0x08032ae4 | FUN_08032ae4 | **stub** | SDCC slot init |
| D | 0x0803707c | handle_response | complete | Send XML response |
| D | 0x08037084 | FUN_08037084 | complete | Build/send XML response (ACK/NAK) |
| D | 0x080371b8 | FUN_080371b8 | complete | Flush XML writer to USB |

### storage.c — Partition & I/O abstraction
Source: `src/fhprg/fhprg_8037820.c`

| | Address | Name | Status | Role |
|---|---------|------|--------|------|
| S | 0x080381d8 | mmc_write_wrapper | complete | **Write entry point** from handlers |
| D | 0x08038206 | FUN_08038206 | complete | Partition select by index |
| D | 0x0803823e | FUN_0803823e | complete | Parse integer from string |
| S | 0x08038282 | FUN_08038282 | complete | strlcat-like string concat |
| D | 0x080382fa | strncmp_fh | complete | Case-insensitive strcmp |
| S | 0x08038014 | FUN_08038014 | complete | Read sectors wrapper |
| S | 0x0803803c | FUN_0803803c | complete | Read helper |
| S | 0x08037c40 | FUN_08037c40 | complete | Partition selector (set to "all") |
| S | 0x08037c56 | FUN_08037c56 | complete | Erase entire partition |
| S | 0x08037c88 | FUN_08037c88 | **stub** | Commit function (logs only) |
| S | 0x08037cb0 | FUN_08037cb0 | complete | Firmware update orchestrator |
| S | 0x08037e88 | FUN_08037e88 | complete | Log drive size info |
| S | 0x08037f64 | FUN_08037f64 | complete | Get partition sector count |
| S | 0x08037f88 | FUN_08037f88 | complete | Log partition info |

### transport.c — USB / DMA
Sources: `fhprg_802196c.c`, `fhprg_8030dac.c`, `fhprg_802cac4.c`

| | Address | Name | Status | Role |
|---|---------|------|--------|------|
| S | 0x08021ca4 | FUN_08021ca4 | **stub** | USB raw read |
| S | 0x08031170 | FUN_08031170 | **stub** | Transport read |
| S | 0x08030ecc | FUN_08030ecc | **stub** | Set pending transfer size |
| S | 0x0802d180 | FUN_0802d180 | **stub** | DMA helper |

### handlers.c — Command handlers
Source: `src/fhprg/fhprg_8021ff0.c`

| | Address | Name | Status | Role |
|---|---------|------|--------|------|
| D | 0x08022a00 | handle_configure | complete | Storage init, set params |
| D | 0x08024484 | handle_program | complete | Write sectors from USB |
| D | 0x08024b04 | handle_read | complete | Read sectors to USB |
| S | 0x08022650 | handle_benchmark | complete | Benchmark |
| S | 0x08022ec8 | handle_erase | complete | Erase sectors |
| S | 0x08022ffc | handle_firmwarewrite | complete | Firmware write |
| S | 0x080238b8 | handle_getstorageinfo | complete | Storage info query |
| S | 0x080239d0 | handle_nop | complete | NOP |
| S | 0x080239dc | handle_patch | complete | Patch bytes |
| S | 0x08023f64 | handle_peek | complete | Memory peek |
| S | 0x08024134 | handle_poke | complete | Memory poke |
| S | 0x08024350 | handle_power | complete | Reset/power |
| S | 0x08024efc | handle_setbootable | complete | Set bootable drive |
| S | 0x08025054 | handle_storagextras | complete | Storage extras |
| S | 0x08022178 | FUN_08022178 | complete | Handler helper |
| S | 0x08022440 | FUN_08022440 | complete | Handler helper |
| S | 0x080233ec | FUN_080233ec | complete | Handler helper |

### dispatch.c — Command router
Source: `src/fhprg/fhprg_802efa4.c`

| | Address | Name | Status | Role |
|---|---------|------|--------|------|
| D | 0x0802f130 | firehose_dispatch | complete | Main XML command router |
| S | 0x0802f838 | FUN_0802f838 | complete | Dispatch state setter |

### protocol.c — Firehose protocol
Source: `src/fhprg/fhprg_8026f54.c`

| | Address | Name | Status | Role |
|---|---------|------|--------|------|
| D | 0x08027674 | firehose_log | complete | printf -> XML log message |
| D | 0x08027bf8 | FUN_08027bf8 | complete | Bounded memcpy |
| S | 0x08027c12 | FUN_08027c12 | complete | Bounded memmove |
| S | 0x080287e2 | FUN_080287e2 | complete | memset wrapper |
| S | 0x08028810 | FUN_08028810 | **stub** | Attr parser |
| S | 0x080288b0 | FUN_080288b0 | **stub** | Attr parser |
| S | 0x08028c10 | FUN_08028c10 | **stub** | Parse sector number |

### hotplug.c — Storage enumeration
Sources: `fs_ext_hfat.c`, `fs_extfs.c`, `fs_hotplug_parser.c`, `fs_hotplug_partition.c`

| | Address | Name | Status | Role |
|---|---------|------|--------|------|
| S | 0x08025b74 | FUN_08025b74 | **stub** | fs_ext_hfat |
| S | 0x08025c08 | FUN_08025c08 | **stub** | fs_ext_hfat |
| S | 0x08025c80 | FUN_08025c80 | **stub** | fs_ext_hfat |
| S | 0x08013918 | FUN_08013918 | **stub** | fs_extfs |
| S | 0x0802ef24 | FUN_0802ef24 | **stub** | fs_hotplug_parser |
| S | 0x08026b88 | FUN_08026b88 | **stub** | fs_hotplug_partition |
| S | 0x08026af8 | FUN_08026af8 | **stub** | hotplug device alloc |
| S | 0x08026dd8 | FUN_08026dd8 | complete | hotplug poll/detect |

### platform.c — Timer, clock, boot
Sources: `fhprg_8019930.c`, `fhprg_801a5f0.c`, `fhprg_801bd00.c`, `fhprg_8013b70.c`

| | Address | Name | Status | Role |
|---|---------|------|--------|------|
| S | 0x08019984 | FUN_08019984 | complete | Fatal halt (loop) |
| S | 0x0801999c | FUN_0801999c | complete | Fatal halt variant |
| S | 0x08019abc | FUN_08019abc | complete | CRC32 |
| S | 0x08013bb0 | FUN_08013bb0 | complete | Device magic check |
| S | 0x0801b6bc | FUN_0801b6bc | **stub** | debug_log (ring buffer) |
| S | 0x0801b85c | FUN_0801b85c | complete | transport_error loop |
| D | 0x08013520 | FUN_08013520 | complete | is_digit |
| D | 0x08007450 | FUN_08007450 | complete | Global ptr getter |
| S | 0x08010960 | FUN_08010960 | complete | canary_fail (loop) |
| S | 0x08013078 | FUN_08013078 | **stub** | Boot helper (complex) |
| S | 0x0800d59c | FUN_0800d59c | **stub** | hash/checksum |
| S | 0x0801be1c | FUN_0801be1c | **stub** | 96-bit division |

### xml.c — XML parser & writer
Source: `src/fhprg/fhprg_8037820.c`

| | Address | Name | Status | Role |
|---|---------|------|--------|------|
| D | 0x08038db4 | FUN_08038db4 | complete | xml_advance (tokenizer) |
| D | 0x08038d38 | FUN_08038d38 | complete | xml_get_attr_value |
| S | 0x08038d76 | xml_get_tag_name | complete | xml_get_tag_name |
| D | 0x0803906c | FUN_0803906c | complete | xml_attr_match |
| D | 0x08039092 | xml_tag_match | complete | xml_tag_match |
| D | 0x080390d8 | FUN_080390d8 | complete | xml_wr_close_self |
| D | 0x080390e4 | FUN_080390e4 | complete | xml_wr_close_elem |
| D | 0x080390f4 | FUN_080390f4 | complete | xml_wr_elem_name |
| D | 0x08039100 | FUN_08039100 | complete | xml_wr_open |
| D | 0x08039110 | FUN_08039110 | complete | xml_wr_attr_start |
| D | 0x08039122 | FUN_08039122 | complete | xml_wr_attr |
| D | 0x0803918c | FUN_0803918c | complete | xml_wr_attr_value |
| D | 0x080391f0 | FUN_080391f0 | complete | xml_wr_init |
| S | 0x08039174 | FUN_08039174 | complete | xml_wr_attr_quoted |
| S | 0x08039234 | FUN_08039234 | complete | xml_wr helper |
| S | 0x08038c24 | FUN_08038c24 | complete | xml send-and-wait |
| S | 0x08038cfa | FUN_08038cfa | complete | xml get attr name |

---

## Phase 2: Self-Contained Build (COMPLETE)

All external dependencies resolved. Zero unresolved cross-object symbols.

### New files added

| File | Functions | Lines | Content |
|------|-----------|-------|---------|
| `sdcc_regs.c` | 38 | ~580 | MMIO register wrappers (SDHCI) |
| `sdcc_helpers.c` | 21 | ~570 | Data transfer, DMA, ADMA2, polling |
| `card_init.c` | 29 | ~1000 | Card identification, CSD/EXT_CSD, bus setup |
| `globals.c` | — | ~95 | 32 string literals + 6 SDCC state vars + MMIO timer |

Transport/USB (already in `transport.c`), dispatch loop (already in `dispatch.c`),
and stubs (already in `platform.c`) were already self-contained from Phase 1.

---

## Phase 1 Task List — Status (COMPLETE)

All files complete. 101 functions with `orig: 0x` traceability. Build clean.

### 1. emmc.c — DONE
- [x] Full port: sdcc_send_cmd, sdcc_write_data, mmc_write_blocks, mmc_switch_partition,
  mmc_ensure_partition, mmc_close_handle, mmc_erase_range, mmc_open_device,
  mmc_get_capacity, mmc_is_partition_active, mmc_get_card_type (20 functions)
- [x] All FUN_/DAT_ renamed to eMMC spec names

### 2. transport.c — DONE (stubs with names)
- [x] usb_read_complete, transport_read_data, transport_set_pending, pmic_set_power
- [x] Stubs kept — register-level USB outside scope

### 3. storage.c — DONE
- [x] All renamed: storage_write_sectors, storage_select_partition, storage_read_sectors, etc. (14 functions)

### 4. protocol.c — DONE
- [x] transfer_callback fully implemented, bounded_memcpy/memmove renamed
- [x] eval_sector_expression/parse_sector_value stubbed (client sends plain numbers)

### 5. handlers.c — DONE
- [x] All FUN_ call sites renamed (storage_write_sectors, xml_advance, etc.)

### 6. dispatch.c — DONE
- [x] dispatch_set_state, handler_digest_cmd references updated

### 7. platform.c — DONE
- [x] All renamed: fatal_error_dma_reset, stack_canary_fail, debug_log, etc. (12 functions)

### 8. hotplug.c — DONE
- [x] All renamed: hfat_open, hotplug_poll_device, etc. (8 functions)

### 9. xml.c — DONE
- [x] All renamed: xml_advance, xml_attr_match, xml_wr_close_self, xml_wr_attr_value, etc. (17 functions)

### 10. firehose.h — DONE
- [x] All forward declarations updated, globals organized by subsystem
- [x] External functions declared with descriptive comments
