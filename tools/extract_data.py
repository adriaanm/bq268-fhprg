#!/usr/bin/env python3
"""
Extract the data section from aboot.bin and generate linker symbol provides.

aboot.bin LOAD segment layout:
  file offset 0x8000 → vaddr 0x8f600000
  filesz 0x80c4c  → code+data through vaddr 0x8f680c4c
  memsz  0xb44e8  → BSS extends to vaddr 0x8f6b44e8

This script produces:
  tmp/aboot_data.bin   — raw data blob (vaddr 0x8f652e80..0x8f680c4c)
  tmp/aboot_provides.ld — PROVIDE() statements for all extern symbols

Usage:
    cd aboot && python3 tools/extract_data.py
    # or:  make extract-data
"""
import json
import re
from pathlib import Path

ABOOT_DIR   = Path(__file__).parent.parent
BINARY      = ABOOT_DIR / "aboot.bin"
FUNCS_JSON  = ABOOT_DIR / "tmp" / "functions.json"
DECOMP_DIR  = ABOOT_DIR / "tmp" / "decompiled"
OUT_BLOB    = ABOOT_DIR / "tmp" / "aboot_data.bin"
OUT_LD      = ABOOT_DIR / "tmp" / "aboot_provides.ld"

# LOAD segment parameters (from aboot.bin ELF headers)
ELF_VADDR_BASE  = 0x8f600000
ELF_FILE_OFFSET = 0x8000
LOAD_FILESZ     = 0x80c4c
LOAD_MEMSZ      = 0xb44e8

# Boundary between code and data (first string in the binary)
DATA_START_VADDR = 0x8f652e80
LOAD_END_VADDR   = ELF_VADDR_BASE + LOAD_FILESZ   # 0x8f680c4c
BSS_END_VADDR    = ELF_VADDR_BASE + LOAD_MEMSZ    # 0x8f6b44e8


def vaddr_to_offset(vaddr: int) -> int:
    return vaddr - ELF_VADDR_BASE + ELF_FILE_OFFSET


def sanitize_symbol(name: str) -> str:
    """Mirror of preprocess.py sanitize_symbol."""
    return (name.replace('>', '_gt_')
                .replace('<', '_lt_')
                .replace(' ', '_')
                .replace('?', '_q_'))


def main():
    data = BINARY.read_bytes()

    # ----------------------------------------------------------------
    # 1. Extract raw data blob
    # ----------------------------------------------------------------
    blob_start = vaddr_to_offset(DATA_START_VADDR)
    blob_end   = vaddr_to_offset(LOAD_END_VADDR)
    blob = data[blob_start:blob_end]
    OUT_BLOB.parent.mkdir(parents=True, exist_ok=True)
    OUT_BLOB.write_bytes(blob)
    print(f"[*] Data blob: vaddr 0x{DATA_START_VADDR:08x}..0x{LOAD_END_VADDR:08x}"
          f"  file 0x{blob_start:06x}..0x{blob_end:06x}  {len(blob):,} bytes → {OUT_BLOB}")

    # ----------------------------------------------------------------
    # 2. Load decompiled source for symbol extraction
    # ----------------------------------------------------------------
    if not DECOMP_DIR.exists():
        print("Warning: tmp/decompiled/ not found — run 'make analyze' first")
        all_c = ""
    else:
        all_c = "\n".join(p.read_text() for p in sorted(DECOMP_DIR.glob("*.c")))

    # ----------------------------------------------------------------
    # 3. Generate PROVIDE() statements
    # ----------------------------------------------------------------
    lines = [
        "/* Auto-generated PROVIDE() statements for aboot.ld",
        " * Regenerate with: make extract-data",
        " * All PROVIDE() are no-ops for symbols already defined by .o files.",
        " */",
        "",
    ]

    # ---- String symbols ----
    lines.append("/* String literals in data blob (vaddr 0x8f652e80+) */")
    str_syms: dict[str, int] = {}   # sanitized_name → vaddr
    for m in re.finditer(r'\b(s_[\w<>?]*_[0-9a-f]{8})\b', all_c):
        raw = m.group(1)
        vaddr = int(raw[-8:], 16)
        str_syms[sanitize_symbol(raw)] = vaddr
    for sym, vaddr in sorted(str_syms.items(), key=lambda x: x[1]):
        lines.append(f"PROVIDE({sym} = 0x{vaddr:08x});")
    print(f"[*] {len(str_syms)} string symbol provides")
    lines.append("")

    # ---- DAT_ globals ----
    lines.append("/* DAT_ global variables */")
    dat_addrs: set[int] = set()
    for m in re.finditer(r'\b_?DAT_([0-9a-f]{8})\b', all_c):
        dat_addrs.add(int(m.group(1), 16))
    for vaddr in sorted(dat_addrs):
        lines.append(f"PROVIDE(DAT_{vaddr:08x} = 0x{vaddr:08x});")
        lines.append(f"PROVIDE(_DAT_{vaddr:08x} = 0x{vaddr:08x});")
    print(f"[*] {len(dat_addrs)} DAT_ symbol provides")
    lines.append("")

    # ---- UNK_ symbols ----
    unk_addrs: set[int] = set()
    for m in re.finditer(r'\bUNK_([0-9a-f]{8})\b', all_c):
        unk_addrs.add(int(m.group(1), 16))
    if unk_addrs:
        lines.append("/* UNK_ symbols */")
        for vaddr in sorted(unk_addrs):
            lines.append(f"PROVIDE(UNK_{vaddr:08x} = 0x{vaddr:08x});")
        lines.append("")

    # ---- PTR_ symbols ----
    ptr_syms: dict[str, int] = {}
    for m in re.finditer(r'\b(PTR_(?:FUN|DAT|s|LAB|entry)_\w+)\b', all_c):
        name = m.group(1)
        am = re.search(r'([0-9a-f]{8})$', name)
        if am:
            ptr_syms[name] = int(am.group(1), 16)
    if ptr_syms:
        lines.append("/* PTR_ pointer table symbols */")
        for name, vaddr in sorted(ptr_syms.items(), key=lambda x: x[1]):
            lines.append(f"PROVIDE({name} = 0x{vaddr:08x});")
        lines.append("")

    # ---- RAM/Stack variables ----
    # These are memory-mapped hardware addresses.
    # The address is encoded in the variable name by Ghidra.
    ram_syms: dict[str, int] = {}
    # Updated regex to match ppu, ppi, ppc, ppb, pu, pi, pc, pb prefixes
    mem_re = re.compile(r'\b((?:pp?|)[ucisbdq](?:Ram|Stack)(?:0x)?([0-9a-f][0-9a-f_]*))\b')
    for m in mem_re.finditer(all_c):
        name = m.group(1)
        addr_str = m.group(2).replace('_', '')
        try:
            ram_syms[name] = int(addr_str, 16)
        except ValueError:
            pass
    # Extra patterns: lRam, dRam, ram0x...
    for m in re.finditer(r'\b([ld]Ram[0-9a-f_]+)\b', all_c):
        name = m.group(1)
        am = re.search(r'Ram([0-9a-f_]+)$', name)
        if am:
            try:
                ram_syms[name] = int(am.group(1).replace('_', ''), 16)
            except ValueError:
                pass
    for m in re.finditer(r'\b(ram0x([0-9a-f]+))\b', all_c):
        ram_syms[m.group(1)] = int(m.group(2), 16)
    if ram_syms:
        lines.append("/* RAM/Stack hardware-mapped variables */")
        for name, vaddr in sorted(ram_syms.items(), key=lambda x: x[1]):
            lines.append(f"PROVIDE({name} = 0x{vaddr:08x});")
        lines.append("")

    # ---- register0x / stack0x offset symbols ----
    misc_syms: dict[str, int] = {}
    for m in re.finditer(r'\b(register0x([0-9a-f]+))\b', all_c):
        misc_syms[m.group(1)] = int(m.group(2), 16)
    for m in re.finditer(r'\b(stack0x([0-9a-f]+))\b', all_c):
        misc_syms[m.group(1)] = int(m.group(2), 16)
    if misc_syms:
        lines.append("/* register/stack offset pseudo-symbols */")
        for name, vaddr in sorted(misc_syms.items(), key=lambda x: x[1]):
            lines.append(f"PROVIDE({name} = 0x{vaddr:08x});")
        lines.append("")

    # ---- Function symbols (thunks, cross-references) ----
    # PROVIDE() is a no-op for functions defined by the compiled objects,
    # so it's safe to include all of them.  Thumb functions need bit 0 set.
    fun_syms: dict[str, int] = {}
    for m in re.finditer(r'\b((?:thunk_)?FUN_([0-9a-f]{8}))\b', all_c):
        fun_syms[m.group(1)] = int(m.group(2), 16)
    if fun_syms:
        lines.append("/* Function symbols (Thumb: bit 0 set) */")
        for name, vaddr in sorted(fun_syms.items(), key=lambda x: x[1]):
            lines.append(f"PROVIDE({name} = 0x{vaddr:08x} + 1);")
        lines.append("")

    # ---- LAB_ address-taken labels ----
    lab_syms: dict[str, int] = {}
    for m in re.finditer(r'&(LAB_([0-9a-f]+))(?:_\d+)?\b', all_c):
        lab_syms[m.group(1)] = int(m.group(2), 16)
    if lab_syms:
        lines.append("/* LAB_ address-taken labels */")
        for name, vaddr in sorted(lab_syms.items(), key=lambda x: x[1]):
            lines.append(f"PROVIDE({name} = 0x{vaddr:08x});")
        lines.append("")

    OUT_LD.write_text("\n".join(lines) + "\n")
    print(f"[*] Written {OUT_LD}  ({sum(1 for l in lines if l.startswith('PROVIDE'))} provides)")


if __name__ == "__main__":
    main()
