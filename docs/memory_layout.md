# Boot Memory Layout — BQ268 UdoSmart (msm8909) ODM aboot

Reverse-engineered from `aboot.bin` (tag `LA.UM.6.6.c25-01000-89xx.0` + ODM patches).
All addresses and constants verified against ARM32 disassembly.

## Physical Memory Map

```
Address         Region                    Size        Source
──────────────  ────────────────────────  ──────────  ──────────────────────
0x00000000      Peripherals / MMIO                    SoC registers
...
0x80000000      DDR START                             SDRAM_START_ADDR (iomap.h)
                ┌───────────────────────┐
0x80008000      │ ← kernel loaded here  │ ~7.5 MB    ABOOT_FORCE_KERNEL_ADDR (ARM32)
                │   (zImage + appended  │             BFI construction @ 0x8f625ae0
                │    DTB within this)   │
0x8079xxxx      │ ← kernel end (varies) │
                │                       │
                │   ... free gap ...    │  ~25 MB
                │                       │
0x82100000      │ ← DTB copied here     │ ~200 KB    ABOOT_FORCE_TAGS_ADDR
                │   (tags_addr)         │             movt #0x8210 @ 0x8f625b04
                │                       │
0x82300000      │ ← ramdisk loaded here │ ~1 MB      ABOOT_FORCE_RAMDISK_ADDR
                │   (ramdisk_addr)      │             movt #0x8230 @ 0x8f625af8
0x8240xxxx      │ ← ramdisk end (varies)│
                │                       │
                │   ... free DDR ...    │  ~211 MB
                │                       │
0x8F600000      ├───────────────────────┤             MEMBASE (target/msm8909/rules.mk)
                │ aboot (LK bootloader) │  1 MB       MEMSIZE = 0x00100000
                │ LOAD segment:         │
                │   FileSiz = 0x80c4c   │  ~527 KB actual code+data
                │   MemSiz  = 0xb44e8   │  ~738 KB with BSS
0x8F700000      ├───────────────────────┤             MEMBASE + MEMSIZE
                │   ... gap ...         │  ~16 MB
0x90000000      │ SCRATCH_ADDR (stock)  │             target/msm8909/rules.mk
0x90100000      ├───────────────────────┤             target_get_scratch_address()
                │ Scratch region        │  250 MB     @ 0x8f6014c8: movt #0x9010
                │ (boot.img loaded here │             target_get_max_flash_size()
                │  from eMMC before     │             @ 0x8f601504: mov #0xFA00000
                │  being copied to      │
                │  final addresses)     │
0x9FB00000      └───────────────────────┘             scratch + max_flash_size
```

### Key constants (from disassembly)

| Constant | Value | Source |
|----------|-------|--------|
| `SDRAM_START_ADDR` | `0x80000000` | `platform/msm8909/include/platform/iomap.h` |
| `MEMBASE` | `0x8F600000` | `target/msm8909/rules.mk:8` |
| `MEMSIZE` | `0x00100000` (1 MB) | `target/msm8909/rules.mk:9` |
| `BASE_ADDR` | `0x80000000` | `target/msm8909/rules.mk:11` |
| `SCRATCH_ADDR` | `0x90000000` | `target/msm8909/rules.mk:12` (stock) |
| ODM scratch | `0x90100000` | `target_get_scratch_address()` @ 0x8f6014c8 |
| ODM max flash | `0x0FA00000` (250 MB) | `target_get_max_flash_size()` @ 0x8f601504 |
| Kernel (ARM32) | `0x80008000` | Forced @ 0x8f625ad8-0x8f625ae8 |
| Kernel (ARM64) | `0x00080000` | Forced @ 0x8f625adc |
| Ramdisk | `0x82300000` | Forced @ 0x8f625af4-0x8f625afc |
| Tags/DTB | `0x82100000` | Forced @ 0x8f625b00-0x8f625b08 |

### VA/PA mapping

`platform_get_virt_to_phys_mapping()` at `platform/msm8909/platform.c:165` is a
**1:1 identity mapping** — virtual addresses equal physical addresses.

The ODM `boot_linux_from_mmc` calls `FUN_8f602dc8` three times on the forced
addresses (kernel, ramdisk, tags). This function is a **stack canary check**, not a
VA translation — `r0` passes through unchanged. The forced physical addresses are
the final addresses used for memcpy and the kernel jump.

## Boot Flow: `boot_linux_from_mmc` (0x8f62557c, 2640 bytes)

### Phase 1: Read image into scratch

1. Read `boot` (or `recovery`) partition from eMMC
2. Entire `boot.img` lands at `scratch = 0x90100000`
3. Parse `ANDROID!` header at scratch

### Phase 2: Compute layout in scratch buffer

```
scratch + 0              → ANDROID! header (1 page = 2048 bytes)
scratch + page_size      → kernel data (kernel_actual bytes, page-aligned)
scratch + ps + ka        → ramdisk data (ramdisk_actual bytes, page-aligned)
scratch + ps + ka + ra   → second data (second_actual bytes, if any)
scratch + ps + ka + ra + sa → dt_size section (dt_actual bytes, IGNORED by ODM)
```

Where:
- `kernel_actual  = ROUND_UP(kernel_size,  page_size)`
- `ramdisk_actual = ROUND_UP(ramdisk_size, page_size)`
- `second_actual  = ROUND_UP(second_size,  page_size)`
- `dt_actual      = ROUND_UP(dt_size,      page_size)`

### Phase 3: Size & overflow validation

```
imagesize_actual = page_size + kernel_actual + ramdisk_actual + second_actual + dt_actual

Checks:
  imagesize_actual ≤ 0xFFFFFFFF                        (integer overflow)
  imagesize_actual ≤ target_get_max_flash_size()        (fits in scratch, 250 MB)
  [scratch, scratch + imagesize_actual) ∩ aboot = ∅     (no overlap with aboot)
```

Error string: `"booimage  size is greater than DDR can hold"` @ 0x8f65b330

### Phase 4: Signature verification

If device is locked (`!device.is_unlocked`), verify boot image signature via
`boot_verify_image()`. **Device is unlocked → SKIPPED.**

### Phase 5: Kernel format detection

Starting at `kptr = scratch + page_size`:

1. **gzip check**: `is_gzip_package()` — if `kptr[0:2] == 0x1f8b`, decompress
   to `scratch + imagesize_actual + page_size`. Updates `kernel_start_addr` and
   `kernel_size` to point to decompressed data. `dtb_offset` set by decompressor.

2. **UNCOMPRESSED_IMG check**: `memcmp(kptr, "UNCOMPRESSED_IMG", 16)` @ 0x8f625a88.
   If matched, skip 20-byte header: `dtb_offset = *(kptr+16)`,
   `kernel_start_addr = kptr + 20`.

3. **Raw kernel**: Use as-is. `dtb_offset = 0` (will be read from zImage+0x2C later).

### Phase 6: ARM64 detection & address forcing

At 0x8f625ac8:

```arm
ldr   r1, [r8, #0x38]           @ load potential ARM64 magic
movw  r3, #0x5241               @ r3 = 'ARMd' = 0x644d5241
movt  r3, #0x644d
cmp   r1, r3
```

If **ARM64** (`kptr[0x38] == 0x644d5241`):
- `kernel_addr = 0x80000` (stored via `mov r0, #0x80000`)

If **ARM32** (not ARM64):
- `kernel_addr = 0x80008000` (BFI construction: `mov r3, #0x8000; bfi r3, r3, #16, #16`)

**Unconditional** (both paths):
- `ramdisk_addr = 0x82300000` (`mov r3, #0; movt r3, #0x8230`)
- `tags_addr    = 0x82100000` (`mov r3, #0; movt r3, #0x8210`)

The header's `kernel_addr`, `ramdisk_addr`, and `tags_addr` are **overwritten** — the
values in the boot.img header have no effect on where things actually land.

### Phase 7: DDR bounds checks

For each of kernel, ramdisk, tags — two checks:

**`check_aboot_addr_range_overlap(start, size)`** @ FUN_8f625434:
```
if (start + size) wraps 32-bit         → FAIL
if (start < MEMBASE) && (start+size ≤ MEMBASE) → OK (below aboot)
if (start ≥ MEMBASE + MEMSIZE)          → OK (above aboot)
else                                     → FAIL (overlaps aboot)
```

**DDR upper bound** (inline checks at 0x8f625b5c-0x8f625b78):
```
if start > 0x8F5FFFFF                   → out of range (try 0x8F7FFFFF fallback)
if (start + size) > 0x8F600000          → FAIL
```
Error string: `"kernel/ramdisk addresses are not valid."` @ 0x8f65b3e8
Error string: `"Device tree addresses are not valid."` @ 0x8f65b414
Error string: `"Boot image buffer address overlaps with aboot addresses."` @ 0x8f65b468

### Phase 8: Memory copies

```c
memcpy(kernel_addr,  scratch + page_size,                    kernel_actual);
memcpy(ramdisk_addr, scratch + page_size + kernel_actual,    ramdisk_size);
```

For ARM32: `memcpy(0x80008000, 0x90100800, ~7.5MB)` — source and dest don't overlap.

### Phase 9: Appended DTB search

```c
dev_tree_appended(
    kernel_addr + dtb_search_offset,   // 0x80008000 + offset (after memcpy, kernel is here)
    hdr->kernel_size,                  // bounds for scanning
    dtb_offset,                        // from decompressor or 0
    tags_addr                          // 0x82100000 — destination for DTB copy
);
```

The function (@ 0x8f6187d8) scans within the **already-copied kernel** at its final
address (0x80008000+) for FDT magic `0xD00DFEED`. The scan starts at `zImage_end`
(read from `kernel+0x2C`).

For each candidate DTB:
1. `fdt_check_header()` validates FDT structure
2. Parse `qcom,msm-id`, `qcom,board-id`, `qcom,pmic-id` via `fdt_getprop()`
3. `platform_dt_absolute_match()` checks against device's actual board info
4. `platform_dt_match_best()` selects best-matching DTB
5. Best DTB is copied to `tags_addr = 0x82100000`

**CRITICAL:** No QCDT path exists. The dt_size section is never read for DT purposes.
Error string: `"ERROR: Appended Device Tree Blob not found"` @ 0x8f65b43c

### Phase 10: update_device_tree

```c
update_device_tree(tags_addr=0x82100000, cmdline, ramdisk_addr, ramdisk_size);
```

At 0x8f6197f0:
1. `fdt_open_into(dtb, dtb, dtb_size + DTB_PAD_SIZE)` with `DTB_PAD_SIZE = 1024`
2. Sets `/memory` node via `target_dev_tree_mem()`
3. Sets `/chosen/bootargs` = final cmdline
4. Sets `/chosen/linux,initrd-start` = ramdisk_addr
5. Sets `/chosen/linux,initrd-end` = ramdisk_addr + ramdisk_size

No ODM-specific properties added. Identical to stock CAF.

### Phase 11: Final boot

```c
boot_linux(kernel_addr=0x80008000, tags_addr=0x82100000, cmdline,
           board_machtype(), ramdisk_addr=0x82300000, ramdisk_size);
```

At FUN_8f625170:
1. `entry = (void(*)(uint, uint, uint*))PA(kernel_addr)` — identity on msm8909
2. `update_device_tree()` patches the DTB at tags_addr
3. `update_cmdline()` builds final cmdline
4. `target_uninit()` — deinitialize target hardware
5. `target_display_shutdown()` — turn off splash
6. `enter_critical_section()` — disable interrupts
7. `platform_uninit()` — platform-level cleanup
8. `arch_disable_cache(UCACHE)` — flush and disable caches
9. `arch_disable_mmu()` — disable MMU
10. **`entry(0, machtype, tags_phys)`** — jump to `0x80008000`

For ARM64 kernel: `scm_elexec_call()` instead (EL switch via SCM).

## Overlap Analysis

### Fixed layout for a typical 7.5 MB ARM32 kernel + 1 MB ramdisk

```
Region          Start        End          Size
──────────────  ──────────── ──────────── ──────────
kernel          0x80008000   0x80798800   ~7.5 MB
  [gap]         0x80798800   0x82100000   ~25.6 MB
tags (DTB)      0x82100000   0x82130000   ~190 KB
  [gap]         0x82130000   0x82300000   ~1.8 MB
ramdisk         0x82300000   0x823FA000   ~1 MB
  [gap]         0x823FA000   0x8F600000   ~211 MB
aboot           0x8F600000   0x8F700000   1 MB
  [gap]         0x8F700000   0x90100000   ~16 MB
scratch         0x90100000   0x9FB00000   250 MB
```

**No overlaps.** The gaps are substantial. A kernel would need to be >33 MB to
reach the tags region, or >35 MB to reach the ramdisk — neither is realistic.

### DDR capacity constraint

Usable DDR below aboot: `0x8F600000 - 0x80000000 = 0x0F600000` = **246 MB**.

Kernel + ramdisk + DTB must fit within this 246 MB region. Typical usage is <15 MB,
leaving >230 MB free for the Linux kernel's own use after boot.

### Scratch-to-DDR copy safety

Source: `scratch + page_size = 0x90100800`
Dest:   `kernel_addr = 0x80008000`

These regions are 256 MB apart with no overlap. The memcpy is safe.

## dt_size Field Handling (ODM quirk)

The ODM repurposes the dt_size header field. At 0x8f625714-0x8f625750:

```arm
ldr  r3, [r4, #0x24]      @ r3 = hdr->dt_size
cmp  r3, #0
beq  skip                  @ dt_size == 0 → use device page_size
ldr  r2, [r5]              @ r2 = current page_size
cmp  r3, r2
beq  skip                  @ dt_size == page_size → no change
cmp  r3, #0x1000
bhi  error                 @ dt_size > 4096 → "Invalid page size" (but this is
                           @   unreachable in practice since FDT blobs are >4096)
@ dt_size 1-4096: adopt as page_size override
str  r3, [r5]
sub  r2, r3, #1
str  r2, [r0]              @ page_mask = dt_size - 1
```

In practice: dt_size is always the FDT blob size (100-200 KB), so the `bhi error`
at `cmp r3, #0x1000` triggers — but this falls through to the error path that
actually just continues execution (it's a dead-code artifact, not a real failure).

**Bottom line:** dt_size has no functional effect. It's not used to locate or
validate any DT data. All DTB discovery is through `dev_tree_appended()`.

## Error Strings Reference

All error strings from `boot_linux_from_mmc`, decoded from movw/movt pairs:

| Address | String | Triggered by |
|---------|--------|-------------|
| 0x8f65b258 | `ANDROID!` | Header magic comparison |
| 0x8f65b264 | `ERROR: No %s partition found` | Partition lookup failure |
| 0x8f65b284 | `ERROR: Cannot read boot image header` | MMC read failure |
| 0x8f65b2ac | `ERROR: Invalid boot image header` | ANDROID! magic mismatch |
| 0x8f65b2d0 | `ERROR: Invalid page size` | dt_size > 4096 (dead path) |
| 0x8f65b2ec | `Integer overflow detected in bootimage header fields at %u in %s` | Size calculation overflow |
| 0x8f65b330 | `booimage  size is greater than DDR can hold` | Image > scratch size |
| 0x8f65b360 | `ERROR: Cannot read boot image` | MMC read failure (full image) |
| 0x8f65b380 | `ERROR: Cannot read boot image signature` | Signature MMC read failure |
| 0x8f65b3ac | `decompressing kernel image failed!!!` | gzip decompression error |
| 0x8f65b3e8 | `kernel/ramdisk addresses are not valid.` | DDR bounds / aboot overlap |
| 0x8f65b414 | `Device tree addresses are not valid.` | Tags DDR bounds / overlap |
| 0x8f65b43c | `ERROR: Appended Device Tree Blob not found` | No FDT in kernel image |
| 0x8f65b468 | `Boot image buffer address overlaps with aboot addresses.` | Scratch overlaps aboot |
| 0x8f65b4a4 | `Signature read buffer address overlaps with aboot addresses.` | Sig buffer overlap |
