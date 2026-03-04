#!/usr/bin/env python3
"""
Fix SHA-256 hash table in a patched Qualcomm MBN/ELF firehose programmer.

Recalculates segment hashes and updates the hash table so the PBL
accepts the modified image.

Usage:
    python3 tools/fix_hashes.py <input.bin> <output.bin>
    python3 tools/fix_hashes.py fhprg_unsafe.bin loader/fhprg_unsafe.bin
"""

import struct
import hashlib
import sys
import shutil


def parse_elf_phdrs(data):
    """Parse ELF32 program headers."""
    e_phoff = struct.unpack_from('<I', data, 0x1c)[0]
    e_phentsize = struct.unpack_from('<H', data, 0x2a)[0]
    e_phnum = struct.unpack_from('<H', data, 0x2c)[0]

    phdrs = []
    for i in range(e_phnum):
        off = e_phoff + i * e_phentsize
        fields = struct.unpack_from('<IIIIIIII', data, off)
        phdrs.append({
            'type': fields[0],
            'offset': fields[1],
            'vaddr': fields[2],
            'paddr': fields[3],
            'filesz': fields[4],
            'memsz': fields[5],
            'flags': fields[6],
            'align': fields[7],
        })
    return phdrs


def find_hash_segment(phdrs):
    """Find the hash table segment (NULL type with QC metadata flags)."""
    for i, p in enumerate(phdrs):
        if p['type'] == 0 and p['filesz'] > 0 and i > 0:
            return i, p
    return None, None


def fix_hashes(input_path, output_path):
    with open(input_path, 'rb') as f:
        data = bytearray(f.read())

    phdrs = parse_elf_phdrs(data)
    hash_idx, hash_phdr = find_hash_segment(phdrs)

    if hash_phdr is None:
        print("ERROR: Could not find hash table segment")
        sys.exit(1)

    hash_seg_off = hash_phdr['offset']
    hash_seg_size = hash_phdr['filesz']
    num_segments = len(phdrs)

    # MBN hash table header is 40 bytes, then 32 bytes per segment
    HEADER_SIZE = 40
    HASH_SIZE = 32  # SHA-256

    print(f"Hash segment: PHDR[{hash_idx}] at file offset 0x{hash_seg_off:x}, size 0x{hash_seg_size:x}")
    print(f"Segments: {num_segments}")
    print()

    updated = 0
    for i, p in enumerate(phdrs):
        entry_off = hash_seg_off + HEADER_SIZE + i * HASH_SIZE

        if entry_off + HASH_SIZE > hash_seg_off + hash_seg_size:
            print(f"  Seg[{i}]: hash entry beyond hash segment, skipping")
            continue

        # Skip the hash table segment itself (circular dependency - its own
        # hash entry is always zero in QC MBN format)
        if i == hash_idx:
            print(f"  Seg[{i}]: SKIP (hash table segment, self-referential)")
            continue

        stored = bytes(data[entry_off:entry_off + HASH_SIZE])

        # Compute hash of segment data
        if p['filesz'] > 0:
            seg_data = bytes(data[p['offset']:p['offset'] + p['filesz']])
            computed = hashlib.sha256(seg_data).digest()
        else:
            # Zero-size segments have zero hash
            computed = b'\x00' * HASH_SIZE

        if stored == computed:
            print(f"  Seg[{i}]: OK (vaddr=0x{p['vaddr']:08x})")
        elif stored == b'\x00' * HASH_SIZE and p['filesz'] == 0:
            print(f"  Seg[{i}]: OK (zero-size, zero hash)")
        else:
            print(f"  Seg[{i}]: MISMATCH (vaddr=0x{p['vaddr']:08x}, filesz=0x{p['filesz']:x})")
            print(f"    stored:   {stored.hex()}")
            print(f"    computed: {computed.hex()}")
            data[entry_off:entry_off + HASH_SIZE] = computed
            updated += 1
            print(f"    -> FIXED")

    if updated == 0:
        print("\nAll hashes already correct, no changes needed.")
    else:
        print(f"\nFixed {updated} hash(es).")

    with open(output_path, 'wb') as f:
        f.write(data)
    print(f"Written to {output_path}")


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <input.bin> <output.bin>")
        sys.exit(1)
    fix_hashes(sys.argv[1], sys.argv[2])
