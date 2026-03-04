#!/usr/bin/env python3
"""
Patch Qualcomm Firehose programmer to clear eMMC USER_WP before writes.

The eMMC hardware has write-protect groups set on critical partitions
(aboot, sbl1, tz, rpm). The firehose programmer's code-level WP check
passes, but the eMMC controller silently discards writes to protected
groups.

This patch injects a CMD6 SWITCH call to set EXT_CSD[171] (USER_WP) = 0
before each write, disabling write-protect enforcement at the eMMC level.

Patch details:
  - Code cave at 0x0803dc8c (in unused zero-fill region)
  - Redirect: FUN_080381d8's bl FUN_08034228 → bl code_cave
  - Code cave: save args, call FUN_08034a40(dev_handle, 0x03AB0000),
    restore args, tail-call FUN_08034228

Usage:
    python3 tools/patch_wp_clear.py <input.bin> <output.bin>
"""

import struct
import sys


def encode_thumb2_bl(from_addr, to_addr):
    """Encode a Thumb2 BL (branch with link) instruction."""
    offset = to_addr - (from_addr + 4)  # PC is +4 ahead
    if offset < -(1 << 24) or offset >= (1 << 24):
        raise ValueError(f"BL offset {offset} out of range")

    s = 1 if offset < 0 else 0
    if offset < 0:
        offset += (1 << 25)  # two's complement in 25-bit space

    imm10 = (offset >> 12) & 0x3ff
    imm11 = (offset >> 1) & 0x7ff
    i1 = (offset >> 23) & 1
    i2 = (offset >> 22) & 1
    j1 = (~(i1 ^ s)) & 1
    j2 = (~(i2 ^ s)) & 1

    hw1 = 0xf000 | (s << 10) | imm10
    hw2 = 0xd000 | (j1 << 13) | (j2 << 11) | imm11

    return struct.pack('<HH', hw1, hw2)


def encode_thumb2_b(from_addr, to_addr):
    """Encode a Thumb2 B.W (unconditional branch, wide) instruction."""
    offset = to_addr - (from_addr + 4)
    if offset < -(1 << 24) or offset >= (1 << 24):
        raise ValueError(f"B.W offset {offset} out of range")

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
    hw2 = 0x9000 | (j1 << 13) | (j2 << 11) | imm11

    return struct.pack('<HH', hw1, hw2)


# Addresses
CAVE_ADDR       = 0x0803dc8c
FN_08034a40     = 0x08034a40  # CMD6 SWITCH helper
FN_08034228     = 0x08034228  # Original write function
BL_SITE         = 0x080381f4  # bl FUN_08034228 in FUN_080381d8

# EXT_CSD[171] = USER_WP, CMD6 argument = 0x03AB0000
# Access=0x03 (write byte), Index=0xAB (171), Value=0x00
CMD6_USER_WP_CLEAR = 0x03AB0000


def build_code_cave():
    """Build the Thumb2 code cave.

    On entry: r0=device_handle, r1=start_sector, r2=buf, r3=num_sectors
    (same args that were going to FUN_08034228)

    Code:
        push {r0, r1, r2, r3, lr}   ; save all args + return addr
        ; r0 = device_handle (already correct for FUN_08034a40)
        movw r1, #0x0000             ; CMD6 arg low half
        movt r1, #0x03AB             ; CMD6 arg high half = 0x03AB0000
        bl   FUN_08034a40            ; send CMD6 SWITCH EXT_CSD[171]=0
        pop  {r0, r1, r2, r3, lr}   ; restore args + return addr
        b.w  FUN_08034228            ; tail-call original write function
    """
    code = bytearray()

    # push {r0, r1, r2, r3, lr}  = STMDB SP!, {R0-R3, LR}
    # Encoding: 0xE92D 0x400F
    code += struct.pack('<HH', 0xe92d, 0x400f)

    # movw r1, #0x0000
    # Encoding: 0xF240 0x0100
    imm16 = CMD6_USER_WP_CLEAR & 0xffff
    imm4 = (imm16 >> 12) & 0xf
    i = (imm16 >> 11) & 1
    imm3 = (imm16 >> 8) & 0x7
    imm8 = imm16 & 0xff
    hw1 = 0xf240 | (i << 10) | imm4
    hw2 = (imm3 << 12) | 0x0100 | imm8
    code += struct.pack('<HH', hw1, hw2)

    # movt r1, #0x03AB
    imm16 = (CMD6_USER_WP_CLEAR >> 16) & 0xffff
    imm4 = (imm16 >> 12) & 0xf
    i = (imm16 >> 11) & 1
    imm3 = (imm16 >> 8) & 0x7
    imm8 = imm16 & 0xff
    hw1 = 0xf2c0 | (i << 10) | imm4
    hw2 = (imm3 << 12) | 0x0100 | imm8
    code += struct.pack('<HH', hw1, hw2)

    # bl FUN_08034a40
    bl_from = CAVE_ADDR + len(code)
    code += encode_thumb2_bl(bl_from, FN_08034a40)

    # pop {r0, r1, r2, r3, lr}  = LDMIA SP!, {R0-R3, LR}
    # Encoding: 0xE8BD 0x400F
    code += struct.pack('<HH', 0xe8bd, 0x400f)

    # b.w FUN_08034228
    b_from = CAVE_ADDR + len(code)
    code += encode_thumb2_b(b_from, FN_08034228)

    return bytes(code)


def va_to_file(va):
    """Convert virtual address to file offset (code segment)."""
    return va - 0x08006000 + 0x3000


def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <input.bin> <output.bin>")
        sys.exit(1)

    input_path, output_path = sys.argv[1], sys.argv[2]

    with open(input_path, 'rb') as f:
        data = bytearray(f.read())

    # Verify original BL instruction at 0x080381f4
    bl_off = va_to_file(BL_SITE)
    orig_bl = bytes(data[bl_off:bl_off+4])
    expected_bl = encode_thumb2_bl(BL_SITE, FN_08034228)
    if orig_bl != expected_bl:
        print(f"ERROR: Expected BL at 0x{BL_SITE:08x} to be {expected_bl.hex()}, "
              f"got {orig_bl.hex()}")
        print("Binary may already be patched or is different from expected.")
        sys.exit(1)

    # Verify code cave is empty
    cave_off = va_to_file(CAVE_ADDR)
    cave_code = build_code_cave()
    cave_region = bytes(data[cave_off:cave_off+len(cave_code)])
    if any(b != 0 for b in cave_region):
        print(f"ERROR: Code cave at 0x{CAVE_ADDR:08x} is not empty")
        sys.exit(1)

    print(f"Code cave: {len(cave_code)} bytes at 0x{CAVE_ADDR:08x}")
    print(f"  Hex: {cave_code.hex()}")

    # Write code cave
    data[cave_off:cave_off+len(cave_code)] = cave_code
    print(f"  Written to file offset 0x{cave_off:x}")

    # Redirect BL: FUN_080381d8's bl FUN_08034228 → bl code_cave
    new_bl = encode_thumb2_bl(BL_SITE, CAVE_ADDR)
    data[bl_off:bl_off+4] = new_bl
    print(f"\nBL redirect: 0x{BL_SITE:08x}")
    print(f"  Old: {orig_bl.hex()} (bl 0x{FN_08034228:08x})")
    print(f"  New: {new_bl.hex()} (bl 0x{CAVE_ADDR:08x})")

    with open(output_path, 'wb') as f:
        f.write(data)
    print(f"\nWritten to {output_path}")


if __name__ == '__main__':
    main()
