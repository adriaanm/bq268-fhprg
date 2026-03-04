#!/usr/bin/env python3
"""Compare original and recompiled binaries using capstone disassembler."""
import json
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM

# Original binary: ELF with code at file offset 0x3000, vaddr 0x08006000
ORIG_CODE_OFFSET = 0x3000
ORIG_CODE_VADDR = 0x08006000

def read_orig_bytes(path, vaddr, size):
    """Read bytes from original binary at virtual address."""
    file_offset = vaddr - ORIG_CODE_VADDR + ORIG_CODE_OFFSET
    with open(path, 'rb') as f:
        f.seek(file_offset)
        return f.read(size)

def read_linked_bytes(path, vaddr, size):
    """Read bytes from linked ELF at virtual address."""
    # .text section is at file offset 0x6000, vaddr 0x08006000
    file_offset = vaddr - ORIG_CODE_VADDR + 0x6000
    with open(path, 'rb') as f:
        f.seek(file_offset)
        return f.read(size)

def disasm_bytes(code, vaddr):
    """Disassemble bytes and return list of (address, mnemonic, op_str)."""
    md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
    md.detail = False
    instructions = []
    for insn in md.disasm(code, vaddr):
        instructions.append((insn.address, insn.mnemonic, insn.op_str))
    return instructions

def normalize_instruction(mnemonic, op_str):
    """Normalize instruction for comparison (ignore immediates/addresses)."""
    import re
    # Replace hex immediates with placeholder
    op_str = re.sub(r'#-?0x[0-9a-f]+', '#imm', op_str)
    op_str = re.sub(r'#-?\d+', '#imm', op_str)
    # Replace addresses with placeholder
    op_str = re.sub(r'0x[0-9a-f]+', 'addr', op_str)
    return mnemonic, op_str

def compare_function(orig_path, linked_path, vaddr, size):
    """Compare a function between original and recompiled."""
    try:
        orig_bytes = read_orig_bytes(orig_path, vaddr, size)
        linked_bytes = read_linked_bytes(linked_path, vaddr, size)
    except Exception as e:
        return None, None, str(e)

    orig_instrs = disasm_bytes(orig_bytes, vaddr)
    linked_instrs = disasm_bytes(linked_bytes, vaddr)

    if not orig_instrs or not linked_instrs:
        return 0, 0, "no instructions"

    # Normalize and compare
    min_len = min(len(orig_instrs), len(linked_instrs))
    matches = 0
    for i in range(min_len):
        o_norm = normalize_instruction(orig_instrs[i][1], orig_instrs[i][2])
        l_norm = normalize_instruction(linked_instrs[i][1], linked_instrs[i][2])
        if o_norm == l_norm:
            matches += 1

    return matches, min_len, orig_instrs[:3], linked_instrs[:3]

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
    print(f"Functions in main code region: {len(code_funcs)}")
    print()

    # Show entry point disassembly
    print("=== Entry Point (0x8008780) ===")
    entry = 0x8008780
    orig_bytes = read_orig_bytes(orig_path, entry, 64)
    linked_bytes = read_linked_bytes(linked_path, entry, 64)

    print("Original:")
    for addr, mnem, op in disasm_bytes(orig_bytes, entry)[:8]:
        print(f"  {addr:08x}: {mnem:8s} {op}")

    print("\nRecompiled:")
    for addr, mnem, op in disasm_bytes(linked_bytes, entry)[:8]:
        print(f"  {addr:08x}: {mnem:8s} {op}")
    print()

    # Function-by-function comparison
    print("=== Function Comparison (first 30) ===")
    exact = good = partial = poor = 0

    for func in code_funcs[:30]:
        vaddr = int(func['address'], 16)
        size = func.get('size', 32) or 32

        matches, total, *extra = compare_function(orig_path, linked_path, vaddr, size)
        if matches is None:
            continue

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

        print(f"  {func['name']}: {matches}/{total} ({pct:.0f}%) {status}")

    print()
    print(f"=== Summary ===")
    print(f"Exact (100%): {exact}")
    print(f"Good (>80%): {good}")
    print(f"Partial (50-80%): {partial}")
    print(f"Poor (<50%): {poor}")

if __name__ == '__main__':
    main()
