#!/usr/bin/env python3
"""
Patch Qualcomm Firehose programmer to bypass eMMC write protection.

Patch modes (can be combined):
  --nop:            2-byte NOP of the WP check in FUN_08034228 (CBZ → B).
  --configure-diag: Hook configure handler to log WP status + CMD6/CMD29.
  --minimal:        Write-path code cave: zero WP byte + tail-call write.
  --full:           Write-path code cave: WP byte + CMD6 + CMD29 + log.

Recommended: --nop --configure-diag
  The NOP bypasses the software WP check unconditionally.
  The configure diagnostics log EXT_CSD values and attempt hardware WP clear.

Usage:
    python3 tools/patch_wp_clear.py <input.bin> <output.bin> [--nop] [--configure-diag] [--minimal] [--full]
"""

import struct
import subprocess
import sys
import tempfile
import os


def encode_thumb2_bl(from_addr, to_addr):
    """Encode a Thumb2 BL (branch with link) instruction."""
    offset = to_addr - (from_addr + 4)
    if offset < -(1 << 24) or offset >= (1 << 24):
        raise ValueError(f"BL offset {offset} out of range")

    s = 1 if offset < 0 else 0
    if offset < 0:
        offset += (1 << 25)

    imm10 = (offset >> 12) & 0x3ff
    imm11 = (offset >> 1) & 0x7ff
    i1 = (offset >> 23) & 1
    i2 = (offset >> 22) & 1
    j1 = (~(i1 ^ s)) & 1
    j2 = (~(i2 ^ s)) & 1

    hw1 = 0xf000 | (s << 10) | imm10
    hw2 = 0xd000 | (j1 << 13) | (j2 << 11) | imm11

    return struct.pack('<HH', hw1, hw2)


def encode_thumb2_bw(from_addr, to_addr):
    """Encode a Thumb2 B.W (unconditional branch, no link) instruction."""
    offset = to_addr - (from_addr + 4)
    if offset < -(1 << 24) or offset >= (1 << 24):
        raise ValueError(f"B.W offset {offset} out of range")

    s = 1 if offset < 0 else 0
    offset_enc = offset + (1 << 25) if offset < 0 else offset

    imm10 = (offset_enc >> 12) & 0x3ff
    imm11 = (offset_enc >> 1) & 0x7ff
    i1 = (offset_enc >> 23) & 1
    i2 = (offset_enc >> 22) & 1
    j1 = (~(i1 ^ s)) & 1
    j2 = (~(i2 ^ s)) & 1
    hw1 = 0xf000 | (s << 10) | imm10
    hw2 = 0x9000 | (j1 << 13) | (j2 << 11) | imm11
    return struct.pack('<HH', hw1, hw2)


# Addresses
CAVE_ADDR       = 0x0803dc8c
FN_CMD6_SWITCH  = 0x08034a40
FN_SDCC_CMD     = 0x08032b94
FN_WRITE        = 0x08034228
FN_LOG          = 0x08027674
WRITE_BL_SITE   = 0x080381f4   # BL in FUN_080381d8 → FUN_08034228
CONFIG_BL_SITE  = 0x08022bf4   # BL in FUN_08022a00 → FUN_08027674 (logbuf log)
DEV_TABLE_ADDR  = 0x08058430   # Global device table struct
ABOOT_SECTOR    = 0x00280800   # aboot partition start sector

# WP check instruction location
WP_CHECK_ADDR   = 0x0803424c
WP_CHECK_ORIG   = bytes([0x09, 0xb1])  # cbz r1, 0x8034252
WP_CHECK_PATCH  = bytes([0x01, 0xe0])  # b   0x8034252

CMD6_USER_WP_CLEAR = 0x03AB0000


def va_to_file(va):
    """Convert virtual address to file offset (code segment)."""
    return va - 0x08006000 + 0x3000


def assemble_thumb2(asm_source, base_addr):
    """Assemble Thumb2 code using the cross-compiler toolchain."""
    with tempfile.TemporaryDirectory() as tmpdir:
        asm_path = os.path.join(tmpdir, 'cave.s')
        obj_path = os.path.join(tmpdir, 'cave.o')
        bin_path = os.path.join(tmpdir, 'cave.bin')

        with open(asm_path, 'w') as f:
            f.write(asm_source)

        subprocess.check_call([
            'arm-linux-gnueabihf-as',
            '-march=armv7-a', '-mthumb',
            '-o', obj_path, asm_path
        ])

        subprocess.check_call([
            'arm-linux-gnueabihf-objcopy',
            '-O', 'binary', '-j', '.text',
            obj_path, bin_path
        ])

        with open(bin_path, 'rb') as f:
            code = f.read()

        result = subprocess.run([
            'arm-linux-gnueabihf-objdump', '-d', obj_path
        ], capture_output=True, text=True)
        print("Assembled code:")
        for line in result.stdout.split('\n'):
            if line.strip() and not line.startswith(obj_path):
                print(f"  {line}")

        return code


def patch_placeholders(code, base_addr, bl_targets, bw_targets):
    """Find and patch BL/B.W self-referencing placeholders."""
    code = bytearray(code)
    self_bl = struct.pack('<HH', 0xf7ff, 0xfffe)
    self_b  = struct.pack('<HH', 0xf7ff, 0xbffe)

    bl_offsets = []
    b_offsets = []
    for i in range(0, len(code) - 3, 2):
        if bytes(code[i:i+4]) == self_bl:
            bl_offsets.append(i)
        elif bytes(code[i:i+4]) == self_b:
            b_offsets.append(i)

    if len(bl_offsets) != len(bl_targets):
        raise RuntimeError(f"Expected {len(bl_targets)} BL placeholders, found {len(bl_offsets)}")
    if len(b_offsets) != len(bw_targets):
        raise RuntimeError(f"Expected {len(bw_targets)} B.W placeholders, found {len(b_offsets)}")

    for off, (target, name) in zip(bl_offsets, bl_targets):
        va = base_addr + off
        code[off:off+4] = encode_thumb2_bl(va, target)
        print(f"  Patch BL {name:15s} at cave+{off:#x} (VA {va:#010x}) → {target:#010x}")

    for off, (target, name) in zip(b_offsets, bw_targets):
        va = base_addr + off
        code[off:off+4] = encode_thumb2_bw(va, target)
        print(f"  Patch B.W {name:15s} at cave+{off:#x} (VA {va:#010x}) → {target:#010x}")

    return bytes(code)


def build_minimal_cave():
    """Build minimal code cave: just zero EXT_CSD[160] and tail-call write."""
    asm = """\
.syntax unified
.thumb
.text

.org 0
cave_start:
    push    {r4, lr}
    mov     r4, r0

    ldr     r0, [r4]            @ r0 = dev_struct
    ldr     r0, [r0, #0x90]    @ r0 = ext_csd_ptr (dev_struct[0x24])
    mov     r4, #0
    strb    r4, [r0, #0xA0]    @ ext_csd[160] = 0

    pop     {r4, lr}
b_write:
    b.w     b_write             @ placeholder → FN_WRITE
"""
    code = assemble_thumb2(asm, CAVE_ADDR)
    return patch_placeholders(code, CAVE_ADDR,
                              bl_targets=[],
                              bw_targets=[(FN_WRITE, "WRITE")])


def build_full_cave():
    """Build full code cave: zero WP byte, CMD6, CMD29, log, tail-call write."""
    asm = f"""\
.syntax unified
.thumb
.text

.org 0
cave_start:
    push    {{r4, r5, r6, r7, lr}}
    sub     sp, sp, #52

    mov     r4, r0              @ device_handle_ptr
    mov     r5, r1              @ start_sector
    mov     r6, r2              @ buf
    mov     r7, r3              @ num_sectors

    @ Log first to prove code cave executed
    ldr     r0, [r4]            @ dev_struct
    ldr     r1, [r0, #0x90]    @ ext_csd_ptr
    ldrb    r1, [r1, #0xA0]    @ r1 = original EXT_CSD[160]
    str     r1, [sp, #44]       @ save for later
    adr     r0, fmt_string
bl_log:
    bl      bl_log              @ placeholder → FN_LOG

    @ Zero the WP check byte
    ldr     r0, [r4]            @ dev_struct
    ldr     r1, [r0, #0x90]    @ ext_csd_ptr
    mov     r2, #0
    strb    r2, [r1, #0xA0]    @ ext_csd[160] = 0

    @ CMD6: clear USER_WP (EXT_CSD[171] = 0)
    ldr     r0, [r4]            @ dev_struct
    movw    r1, #0x{CMD6_USER_WP_CLEAR & 0xffff:04x}
    movt    r1, #0x{(CMD6_USER_WP_CLEAR >> 16) & 0xffff:04x}
bl_cmd6:
    bl      bl_cmd6             @ placeholder → FN_CMD6_SWITCH
    str     r0, [sp, #40]       @ save CMD6 result

    @ CMD29: clear WP group for start_sector
    ldr     r0, [r4]            @ dev_struct
    mov     r1, #29
    str     r1, [sp, #0]        @ cmd[0] = CMD29
    str     r5, [sp, #4]        @ cmd[1] = start_sector
    mov     r1, #1
    str     r1, [sp, #8]        @ cmd[2] = R1B
    str     r1, [sp, #28]       @ cmd[7] = busy wait
    mov     r1, #0
    str     r1, [sp, #12]
    str     r1, [sp, #16]
    str     r1, [sp, #20]
    str     r1, [sp, #24]
    str     r1, [sp, #32]
    str     r1, [sp, #36]
    mov     r1, sp
bl_sdcc:
    bl      bl_sdcc             @ placeholder → FN_SDCC_CMD

    @ Restore and tail-call
    mov     r0, r4
    mov     r1, r5
    mov     r2, r6
    mov     r3, r7
    add     sp, sp, #52
    pop     {{r4, r5, r6, r7, lr}}
b_write:
    b.w     b_write             @ placeholder → FN_WRITE

    .align 2
fmt_string:
    .asciz  "WP [160]=%x"
"""
    code = assemble_thumb2(asm, CAVE_ADDR)
    return patch_placeholders(code, CAVE_ADDR,
                              bl_targets=[
                                  (FN_LOG, "LOG"),
                                  (FN_CMD6_SWITCH, "CMD6"),
                                  (FN_SDCC_CMD, "SDCC (CMD29)"),
                              ],
                              bw_targets=[(FN_WRITE, "WRITE")])


def build_configure_diag_cave():
    """Build configure-phase diagnostic code cave.

    Replaces the BL to FN_LOG at CONFIG_BL_SITE in FUN_08022a00.
    On entry: r0 = fmt string, r1 = &logbuf, r2 = &fh_struct (args for log).
    Must preserve r4-r11 (callee-saved, live in configure handler).

    Actions:
      1. Call original log function (logbuf@0x%08X fh@0x%08X)
      2. Load device table, get device struct
      3. Read EXT_CSD[160] and EXT_CSD[171]
      4. CMD6 SWITCH: clear USER_WP (EXT_CSD[171] = 0)
      5. CMD29 CLR_WRITE_PROT for aboot sector
      6. Log: "WP160=%x WP171=%x c6=%d c29=%d"
      7. Return to configure handler
    """
    asm = f"""\
.syntax unified
.thumb
.text

.org 0
cave_start:
    @ Save callee-saved regs we'll use + lr
    push    {{r4, r5, r6, r7, lr}}
    sub     sp, sp, #44         @ 40 bytes cmd struct + 4 padding

    @ Step 1: Call original log with args already in r0/r1/r2
bl_orig_log:
    bl      bl_orig_log         @ placeholder → FN_LOG

    @ Step 2: Get device struct from global table
    ldr     r4, dev_table_lit
    ldrb    r0, [r4, #0x26]    @ device selector byte
    add     r4, r4, r0, lsl #2
    ldr     r4, [r4, #4]       @ device handle ptr
    ldr     r4, [r4]           @ device struct

    @ Step 3: Read EXT_CSD values
    ldr     r5, [r4, #0x90]    @ ext_csd_ptr
    ldrb    r6, [r5, #0xA0]    @ EXT_CSD[160] (WP check byte)
    ldrb    r7, [r5, #0xAB]    @ EXT_CSD[171] (USER_WP)

    @ Step 4: Zero EXT_CSD[160] in cached buffer (bypass software check)
    mov     r0, #0
    strb    r0, [r5, #0xA0]

    @ Step 5: CMD6 SWITCH clear USER_WP (EXT_CSD[171] = 0)
    mov     r0, r4
    movw    r1, #0x{CMD6_USER_WP_CLEAR & 0xffff:04x}
    movt    r1, #0x{(CMD6_USER_WP_CLEAR >> 16) & 0xffff:04x}
bl_cmd6:
    bl      bl_cmd6             @ placeholder → FN_CMD6_SWITCH
    mov     r5, r0              @ save CMD6 result

    @ Step 6: CMD29 CLR_WRITE_PROT for aboot sector
    @ Build SDCC command struct on stack (10 words = 40 bytes)
    mov     r0, #0
    str     r0, [sp, #12]      @ cmd[3] = 0
    str     r0, [sp, #16]      @ cmd[4] = 0
    str     r0, [sp, #20]      @ cmd[5] = 0
    str     r0, [sp, #24]      @ cmd[6] = 0
    str     r0, [sp, #32]      @ cmd[8] = 0
    str     r0, [sp, #36]      @ cmd[9] = 0
    mov     r0, #29
    str     r0, [sp, #0]       @ cmd[0] = CMD29
    ldr     r0, aboot_sect_lit
    str     r0, [sp, #4]       @ cmd[1] = aboot sector
    mov     r0, #1
    str     r0, [sp, #8]       @ cmd[2] = R1B (response type)
    str     r0, [sp, #28]      @ cmd[7] = busy wait

    mov     r0, r4              @ dev_struct
    mov     r1, sp              @ &cmd_struct
bl_sdcc:
    bl      bl_sdcc             @ placeholder → FN_SDCC_CMD

    @ Step 7: Log results
    @ "WP160=%x WP171=%x c6=%d c29=%d"
    @ r0=result pushed as 5th arg (stack), r1=wp160, r2=wp171, r3=cmd6
    str     r0, [sp, #0]       @ 5th arg: CMD29 result on stack
    adr     r0, diag_fmt
    mov     r1, r6              @ EXT_CSD[160] original value
    mov     r2, r7              @ EXT_CSD[171] original value
    mov     r3, r5              @ CMD6 result
bl_diag_log:
    bl      bl_diag_log         @ placeholder → FN_LOG

    @ Return to configure handler
    add     sp, sp, #44
    pop     {{r4, r5, r6, r7, pc}}

    .align 2
dev_table_lit:
    .word   0x{DEV_TABLE_ADDR:08x}
aboot_sect_lit:
    .word   0x{ABOOT_SECTOR:08x}
diag_fmt:
    .asciz  "WP160=%x WP171=%x c6=%d c29=%d"
"""
    code = assemble_thumb2(asm, CAVE_ADDR)
    return patch_placeholders(code, CAVE_ADDR,
                              bl_targets=[
                                  (FN_LOG, "LOG (original)"),
                                  (FN_CMD6_SWITCH, "CMD6"),
                                  (FN_SDCC_CMD, "SDCC (CMD29)"),
                                  (FN_LOG, "LOG (diag)"),
                              ],
                              bw_targets=[])


def apply_nop_patch(data):
    """Apply 2-byte NOP patch: CBZ → unconditional B at WP check."""
    off = va_to_file(WP_CHECK_ADDR)
    orig = bytes(data[off:off+2])
    if orig != WP_CHECK_ORIG:
        if orig == WP_CHECK_PATCH:
            print(f"  NOP patch already applied at 0x{WP_CHECK_ADDR:08x}")
            return
        print(f"ERROR: Expected {WP_CHECK_ORIG.hex()} at 0x{WP_CHECK_ADDR:08x}, "
              f"got {orig.hex()}")
        sys.exit(1)

    data[off:off+2] = WP_CHECK_PATCH
    print(f"  0x{WP_CHECK_ADDR:08x}: {WP_CHECK_ORIG.hex()} → {WP_CHECK_PATCH.hex()}")
    print(f"    cbz r1, 0x8034252  →  b 0x8034252  (always proceed to write)")


def apply_write_cave(data, cave_code):
    """Apply write-path code cave + BL redirect at WRITE_BL_SITE."""
    # Verify original BL at write site
    bl_off = va_to_file(WRITE_BL_SITE)
    orig_bl = bytes(data[bl_off:bl_off+4])
    expected_bl = encode_thumb2_bl(WRITE_BL_SITE, FN_WRITE)
    if orig_bl != expected_bl:
        print(f"ERROR: Expected BL at 0x{WRITE_BL_SITE:08x} to be {expected_bl.hex()}, "
              f"got {orig_bl.hex()}")
        sys.exit(1)

    # Verify cave region is empty
    cave_off = va_to_file(CAVE_ADDR)
    cave_region = bytes(data[cave_off:cave_off+len(cave_code)])
    if any(b != 0 for b in cave_region):
        print(f"ERROR: Code cave at 0x{CAVE_ADDR:08x} is not empty "
              f"(need {len(cave_code)} bytes)")
        sys.exit(1)

    # Write cave
    data[cave_off:cave_off+len(cave_code)] = cave_code
    print(f"  Code cave: {len(cave_code)} bytes at 0x{CAVE_ADDR:08x} (file 0x{cave_off:x})")

    # Redirect BL
    new_bl = encode_thumb2_bl(WRITE_BL_SITE, CAVE_ADDR)
    data[bl_off:bl_off+4] = new_bl
    print(f"  BL redirect: 0x{WRITE_BL_SITE:08x}: {orig_bl.hex()} → {new_bl.hex()}")


def apply_configure_cave(data, cave_code):
    """Apply configure-phase code cave + BL redirect at CONFIG_BL_SITE."""
    # Verify original BL at configure log site
    bl_off = va_to_file(CONFIG_BL_SITE)
    orig_bl = bytes(data[bl_off:bl_off+4])
    expected_bl = encode_thumb2_bl(CONFIG_BL_SITE, FN_LOG)
    if orig_bl != expected_bl:
        print(f"ERROR: Expected BL at 0x{CONFIG_BL_SITE:08x} to be {expected_bl.hex()}, "
              f"got {orig_bl.hex()}")
        print(f"  Expected: {expected_bl.hex()}, got: {orig_bl.hex()}")
        sys.exit(1)

    # Verify cave region is empty
    cave_off = va_to_file(CAVE_ADDR)
    cave_region = bytes(data[cave_off:cave_off+len(cave_code)])
    if any(b != 0 for b in cave_region):
        print(f"ERROR: Code cave at 0x{CAVE_ADDR:08x} is not empty "
              f"(need {len(cave_code)} bytes)")
        sys.exit(1)

    # Write cave
    data[cave_off:cave_off+len(cave_code)] = cave_code
    print(f"  Code cave: {len(cave_code)} bytes at 0x{CAVE_ADDR:08x} (file 0x{cave_off:x})")

    # Redirect BL
    new_bl = encode_thumb2_bl(CONFIG_BL_SITE, CAVE_ADDR)
    data[bl_off:bl_off+4] = new_bl
    print(f"  BL redirect: 0x{CONFIG_BL_SITE:08x}: {orig_bl.hex()} → {new_bl.hex()}")


def main():
    flags = set()
    args = []
    for a in sys.argv[1:]:
        if a.startswith('--'):
            flags.add(a)
        else:
            args.append(a)

    if len(args) != 2:
        print(f"Usage: {sys.argv[0]} <input.bin> <output.bin> [--nop] [--configure-diag] [--minimal] [--full]")
        print()
        print("Modes (can combine --nop with --configure-diag or write-path caves):")
        print("  --nop              2-byte patch: CBZ → B at WP check (recommended)")
        print("  --configure-diag   Hook configure handler for WP diagnostics")
        print("  --minimal          Write-path cave: zero WP byte + tail-call")
        print("  --full             Write-path cave: WP byte + CMD6 + CMD29 + log")
        print()
        print("If no flags given, defaults to --minimal (legacy behavior).")
        sys.exit(1)

    input_path, output_path = args[0], args[1]

    with open(input_path, 'rb') as f:
        data = bytearray(f.read())

    # Determine modes
    use_nop = '--nop' in flags
    use_config = '--configure-diag' in flags
    use_minimal = '--minimal' in flags
    use_full = '--full' in flags

    # Default to minimal if nothing specified
    if not any([use_nop, use_config, use_minimal, use_full]):
        use_minimal = True

    # Can't use both write-path caves
    if use_minimal and use_full:
        print("ERROR: --minimal and --full are mutually exclusive")
        sys.exit(1)

    # Can't use write-path cave AND configure cave (same code cave region)
    if (use_minimal or use_full) and use_config:
        print("ERROR: Write-path caves (--minimal/--full) and --configure-diag use the same")
        print("       code cave region. Use --nop --configure-diag instead.")
        sys.exit(1)

    patches_applied = []

    # Apply NOP patch
    if use_nop:
        print("=== NOP PATCH: CBZ → B at WP check ===")
        apply_nop_patch(data)
        patches_applied.append("NOP")
        print()

    # Apply write-path code cave
    if use_minimal:
        print("=== WRITE-PATH CAVE: minimal (zero WP byte) ===")
        cave_code = build_minimal_cave()
        apply_write_cave(data, cave_code)
        patches_applied.append("write-cave-minimal")
        print()
    elif use_full:
        print("=== WRITE-PATH CAVE: full (WP byte + CMD6 + CMD29 + log) ===")
        cave_code = build_full_cave()
        apply_write_cave(data, cave_code)
        patches_applied.append("write-cave-full")
        print()

    # Apply configure-phase diagnostics
    if use_config:
        print("=== CONFIGURE-PHASE DIAGNOSTICS ===")
        cave_code = build_configure_diag_cave()
        apply_configure_cave(data, cave_code)
        patches_applied.append("configure-diag")
        print()

    # Write output
    with open(output_path, 'wb') as f:
        f.write(data)

    print(f"Patches applied: {', '.join(patches_applied)}")
    print(f"Written to {output_path}")
    print(f"\nNext: python3 tools/fix_hashes.py {output_path} {output_path}")


if __name__ == '__main__':
    main()
