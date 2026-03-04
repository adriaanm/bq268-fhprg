#!/usr/bin/env python3
"""Compare original and recompiled binaries at byte and instruction level."""
import json
import subprocess
import struct

# Original binary: ELF with code at file offset 0x3000, vaddr 0x08006000, size 0x38440
ORIG_CODE_OFFSET = 0x3000
ORIG_CODE_VADDR = 0x08006000
ORIG_CODE_SIZE = 0x38440

def read_elf_segment(binary_path, vaddr, size):
    """Read bytes from ELF at given virtual address."""
    # For the original, we know the mapping
    if 'fhprg_peek.bin' in binary_path:
        file_offset = vaddr - ORIG_CODE_VADDR + ORIG_CODE_OFFSET
        with open(binary_path, 'rb') as f:
            f.seek(file_offset)
            return f.read(size)

    # For linked ELF, read from .text section
    result = subprocess.run(['arm-none-eabi-objcopy', '-O', 'binary',
        '--only-section=.text', binary_path, '/dev/stdout'],
        capture_output=True)
    if result.returncode != 0:
        return None
    data = result.stdout
    offset = vaddr - ORIG_CODE_VADDR
    if offset < 0 or offset + size > len(data):
        return None
    return data[offset:offset+size]

def compare_function(orig_path, linked_path, vaddr, size):
    """Compare a function between original and recompiled."""
    orig_bytes = read_elf_segment(orig_path, vaddr, size)
    linked_bytes = read_elf_segment(linked_path, vaddr, size)

    if not orig_bytes or not linked_bytes:
        return None, None

    # Byte-level comparison
    min_len = min(len(orig_bytes), len(linked_bytes))
    if min_len == 0:
        return 0, 0

    matches = sum(1 for a, b in zip(orig_bytes[:min_len], linked_bytes[:min_len]) if a == b)
    return matches, min_len

def main():
    orig_path = '../fhprg_peek.bin'
    linked_path = 'tmp/fhprg_linked.elf'
    functions_path = 'tmp/functions.json'

    with open(functions_path) as f:
        functions = json.load(f)

    # Filter to functions in main code region with reasonable size
    code_funcs = [f for f in functions
                  if f['address'].startswith('08006') and (f.get('size') or 0) >= 16]

    print(f"Original binary: {orig_path}")
    print(f"Linked ELF: {linked_path}")
    print(f"Total functions in main code region: {len(code_funcs)}")
    print()

    # Compare overall code regions
    print("=== Overall Code Region Comparison ===")
    orig_code = read_elf_segment(orig_path, ORIG_CODE_VADDR, ORIG_CODE_SIZE)
    linked_code = read_elf_segment(linked_path, ORIG_CODE_VADDR, ORIG_CODE_SIZE)

    print(f"Original code size: {len(orig_code)} bytes")
    print(f"Linked code size: {len(linked_code)} bytes")

    # Compare what we can
    min_size = min(len(orig_code), len(linked_code))
    byte_matches = sum(1 for a, b in zip(orig_code[:min_size], linked_code[:min_size]) if a == b)
    print(f"Byte matches in first {min_size} bytes: {byte_matches} ({byte_matches/min_size*100:.1f}%)")
    print()

    # Function-by-function comparison
    print("=== Function-by-Function Comparison ===")
    exact = 0
    good = 0
    partial = 0
    poor = 0
    total_funcs = 0

    for func in code_funcs[:100]:  # Sample first 100
        vaddr = int(func['address'], 16)
        size = func.get('size', 32) or 32

        matches, total = compare_function(orig_path, linked_path, vaddr, size)
        if matches is None:
            continue

        total_funcs += 1
        pct = matches / total * 100 if total > 0 else 0

        if pct == 100:
            exact += 1
            status = "EXACT"
        elif pct > 80:
            good += 1
            status = "good"
        elif pct > 50:
            partial += 1
            status = "partial"
        else:
            poor += 1
            status = "poor"

        if total_funcs <= 20:
            print(f"  {func['name']}: {matches}/{total} ({pct:.0f}%) {status}")

    print()
    print(f"=== Summary ({total_funcs} functions analyzed) ===")
    print(f"Exact matches (100%): {exact}")
    print(f"Good matches (>80%): {good}")
    print(f"Partial matches (50-80%): {partial}")
    print(f"Poor matches (<50%): {poor}")

    # Show some byte samples
    print()
    print("=== Sample Bytes at Key Addresses ===")
    samples = [0x8006000, 0x8006020, 0x8008780]  # Code start, first function, entry point
    for addr in samples:
        orig_bytes = read_elf_segment(orig_path, addr, 32)
        linked_bytes = read_elf_segment(linked_path, addr, 32)
        print(f"\nAddress 0x{addr:08x}:")
        print(f"  Original:  {orig_bytes.hex() if orig_bytes else 'N/A'}")
        print(f"  Recompiled: {linked_bytes.hex() if linked_bytes else 'N/A'}")

if __name__ == '__main__':
    main()
