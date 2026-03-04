#!/usr/bin/env python3
"""
Disassemble the original aboot ELF binary with function labels from Ghidra.

The aboot ELF has no section headers (stripped), so standard objdump doesn't work.
This tool:
1. Extracts the code segment from the ELF
2. Creates a new ELF with proper sections using the linker
3. Adds function symbols from Ghidra's functions.json
4. Disassembles with objdump -D (binary is ARM-32, not Thumb)
5. Inserts function label lines at the correct addresses

Usage:
    python3 tools/disasm_orig.py [-o tmp/aboot_orig.asm]
"""
import argparse
import json
import subprocess
import sys
from pathlib import Path

ABOOT_DIR = Path(__file__).parent.parent
DEFAULT_ELF = ABOOT_DIR / "aboot_elf.bin"
DEFAULT_FUNCS = ABOOT_DIR / "tmp" / "functions.json"
DEFAULT_OUT = ABOOT_DIR / "tmp" / "aboot_orig.asm"
CODE_BIN = ABOOT_DIR / "tmp" / "code_segment.bin"
CODE_O = ABOOT_DIR / "tmp" / "code.o"
SYMS_LD = ABOOT_DIR / "tmp" / "symbols.ld"
WITH_SYMS_ELF = ABOOT_DIR / "tmp" / "aboot_with_syms.elf"
FINAL_ELF = ABOOT_DIR / "tmp" / "aboot_final.elf"


def extract_code_segment(elf_path: Path) -> tuple[int, int]:
    """Extract executable LOAD segment from ELF to raw binary."""
    import struct
    data = elf_path.read_bytes()

    # Parse ELF program headers
    e_phoff = struct.unpack('<I', data[28:32])[0]
    e_phentsize = struct.unpack('<H', data[42:44])[0]
    e_phnum = struct.unpack('<H', data[44:46])[0]

    vaddr = 0
    size = 0

    for i in range(e_phnum):
        offset = e_phoff + i * e_phentsize
        p_type = struct.unpack('<I', data[offset:offset+4])[0]
        p_offset = struct.unpack('<I', data[offset+4:offset+8])[0]
        p_vaddr = struct.unpack('<I', data[offset+8:offset+12])[0]
        p_filesz = struct.unpack('<I', data[offset+16:offset+20])[0]
        p_flags = struct.unpack('<I', data[offset+24:offset+28])[0]

        # PT_LOAD = 1, PF_X = 0x1
        if p_type == 1 and (p_flags & 1):
            code = data[p_offset:p_offset + p_filesz]
            CODE_BIN.parent.mkdir(parents=True, exist_ok=True)
            CODE_BIN.write_bytes(code)
            vaddr = p_vaddr
            size = p_filesz
            break

    return vaddr, size


def create_object_with_symbols(funcs: list[dict]):
    """Create object file from binary using linker to add symbols as absolute."""
    # Generate linker script
    lines = [
        'ENTRY(_start)',
        'SECTIONS',
        '{',
        '    . = 0x0;',
        '    .text : {',
        '        *(.text)',
        '    }',
        '',
    ]
    for func in funcs:
        addr = int(func['address'], 16)
        name = func['name']
        lines.append(f'    {name} = 0x{addr:x};')
    lines.extend(['    _end = .;', '}', ''])

    SYMS_LD.parent.mkdir(parents=True, exist_ok=True)
    SYMS_LD.write_text('\n'.join(lines))

    # Step 1: Create object from binary (creates .data section)
    CODE_RAW_O = ABOOT_DIR / "tmp" / "code_raw.o"
    subprocess.run([
        'arm-none-eabi-objcopy', '-I', 'binary', '-O', 'elf32-littlearm', '-B', 'arm',
        str(CODE_BIN), str(CODE_RAW_O)
    ], check=True)

    # Step 2: Rename .data to .text and set flags (must be done together to preserve data)
    subprocess.run([
        'arm-none-eabi-objcopy',
        '--rename-section', '.data=.text',
        '--set-section-flags', '.text=alloc,load,readonly,code',
        str(CODE_RAW_O), str(CODE_O)
    ], check=True)

    # Step 3: Link with symbol definitions
    subprocess.run([
        'arm-none-eabi-ld', '-T', str(SYMS_LD),
        '-o', str(WITH_SYMS_ELF), str(CODE_O)
    ], check=True, capture_output=True)

    # Step 4: Ensure section flags are set
    subprocess.run([
        'arm-none-eabi-objcopy',
        '--set-section-flags', '.text=alloc,load,readonly,code',
        str(WITH_SYMS_ELF), str(FINAL_ELF)
    ], check=True)


def disassemble_with_labels(funcs: list[dict]) -> list[str]:
    """Disassemble and insert function label lines."""
    # Run objdump
    result = subprocess.run([
        'arm-none-eabi-objdump', '-D',
        str(FINAL_ELF)
    ], capture_output=True, text=True, check=True)

    # Build address -> function name map
    func_addrs = {int(f['address'], 16): f['name'] for f in funcs}

    # Process output, inserting function labels
    output_lines = []
    for line in result.stdout.splitlines():
        output_lines.append(line)
        # Check if this is an instruction line at a function boundary
        # Format: "      8:	f3af 8000 	nop.w"
        if line.strip() and ':' in line:
            parts = line.split(':')
            if len(parts) >= 2:
                try:
                    addr = int(parts[0].strip(), 16)
                    if addr in func_addrs:
                        # Insert function label BEFORE next instruction
                        # Actually, we need to look ahead or process differently
                        pass
                except ValueError:
                    pass

    # Better approach: process line by line and insert labels
    final_lines = []
    pending_label = None

    for line in result.stdout.splitlines():
        stripped = line.strip()

        # Check if this line starts with an address (instruction line)
        if stripped and ':' in stripped:
            try:
                addr_str = stripped.split(':')[0]
                addr = int(addr_str, 16)

                # Insert function label if we're at a function boundary
                if addr in func_addrs:
                    final_lines.append(f"{addr:08x} <{func_addrs[addr]}>:")
            except (ValueError, IndexError):
                pass

        final_lines.append(line)

    return final_lines


def main():
    parser = argparse.ArgumentParser(description='Disassemble aboot ELF with symbols')
    parser.add_argument('--elf', default=str(DEFAULT_ELF), help='Input ELF binary')
    parser.add_argument('--funcs', default=str(DEFAULT_FUNCS), help='functions.json from Ghidra')
    parser.add_argument('-o', '--output', default=str(DEFAULT_OUT), help='Output disassembly')
    args = parser.parse_args()

    elf_path = Path(args.elf)
    funcs_path = Path(args.funcs)
    out_path = Path(args.output)

    if not elf_path.exists():
        print(f"ERROR: {elf_path} not found", file=sys.stderr)
        sys.exit(1)

    if not funcs_path.exists():
        print(f"ERROR: {funcs_path} not found", file=sys.stderr)
        sys.exit(1)

    # Load functions
    funcs = json.loads(funcs_path.read_text())
    print(f"[*] Loaded {len(funcs)} functions from {funcs_path}")

    # Extract code segment
    print(f"[*] Extracting code segment from {elf_path}...")
    vaddr, size = extract_code_segment(elf_path)
    print(f"[*] Code segment: vaddr=0x{vaddr:x}, size=0x{size:x}")

    # Create object with symbols
    print(f"[*] Creating ELF with function symbols...")
    create_object_with_symbols(funcs)

    # Disassemble with labels
    print(f"[*] Disassembling with objdump...")
    lines = disassemble_with_labels(funcs)

    # Write output
    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_text('\n'.join(lines) + '\n')
    print(f"[*] Wrote {len(lines)} lines to {out_path}")


if __name__ == "__main__":
    main()
