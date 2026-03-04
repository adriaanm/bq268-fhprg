#!/usr/bin/env python3
"""
Patch a recompiled function into fhprg_peek.bin.

Takes a linked ELF containing a single function placed at a code cave address,
and patches it into the original binary with a BL redirect.

Usage:
    python3 tools/patch_recompiled_fn.py <original.bin> <function.bin> <output.bin> \
        --cave-addr 0x0803dc8c --bl-site 0x080381f4 --orig-target 0x08034228

The --bl-site is the address of the BL instruction to redirect.
The --orig-target is what the BL originally called (for verification).
"""

import struct
import sys


def encode_thumb2_bl(from_addr, to_addr):
    """Encode a Thumb2 BL instruction."""
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


def va_to_file(va):
    """Convert virtual address to file offset."""
    return va - 0x08006000 + 0x3000


def main():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('original', help='Original fhprg_peek.bin')
    parser.add_argument('function_bin', help='Recompiled function flat binary')
    parser.add_argument('output', help='Output patched binary')
    parser.add_argument('--cave-addr', type=lambda x: int(x, 0), default=0x0803dc8c)
    parser.add_argument('--bl-site', type=lambda x: int(x, 0), default=0x080381f4)
    parser.add_argument('--orig-target', type=lambda x: int(x, 0), default=0x08034228)
    args = parser.parse_args()

    with open(args.original, 'rb') as f:
        data = bytearray(f.read())

    with open(args.function_bin, 'rb') as f:
        func_code = f.read()

    cave_addr = args.cave_addr
    bl_site = args.bl_site
    orig_target = args.orig_target

    print(f"Function: {len(func_code)} bytes at 0x{cave_addr:08x}")

    # 1. Verify original BL at bl_site
    bl_off = va_to_file(bl_site)
    orig_bl = bytes(data[bl_off:bl_off+4])
    expected_bl = encode_thumb2_bl(bl_site, orig_target)
    if orig_bl != expected_bl:
        print(f"WARNING: BL at 0x{bl_site:08x} is {orig_bl.hex()}, "
              f"expected {expected_bl.hex()} (bl 0x{orig_target:08x})")
        print("Binary may already be patched or differs from expected.")

    # 2. Verify cave region is empty
    cave_off = va_to_file(cave_addr)
    cave_region = bytes(data[cave_off:cave_off+len(func_code)])
    nonzero = sum(1 for b in cave_region if b != 0)
    if nonzero > 0:
        print(f"WARNING: Code cave at 0x{cave_addr:08x} has {nonzero} non-zero bytes")
        print(f"         (need {len(func_code)} bytes)")

    # 3. Write function code into cave
    data[cave_off:cave_off+len(func_code)] = func_code
    print(f"  Written {len(func_code)} bytes at file offset 0x{cave_off:x}")

    # 4. Redirect BL
    # The cave contains a complete replacement for the original function,
    # so the BL at bl_site should now call the cave address.
    # Cave address needs +1 for Thumb bit in the BL target.
    new_bl = encode_thumb2_bl(bl_site, cave_addr)
    data[bl_off:bl_off+4] = new_bl
    print(f"  BL redirect: 0x{bl_site:08x}: {orig_bl.hex()} → {new_bl.hex()}")
    print(f"    Was: bl 0x{orig_target:08x}")
    print(f"    Now: bl 0x{cave_addr:08x}")

    # 5. Write output
    with open(args.output, 'wb') as f:
        f.write(data)
    print(f"\nWritten to {args.output}")
    print(f"Next: python3 tools/fix_hashes.py {args.output} {args.output}")


if __name__ == '__main__':
    main()
