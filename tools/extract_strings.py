#!/usr/bin/env python3
"""
Extract string definitions from aboot.bin for all s_xxx symbols found in decompiled code.

Usage:
    python3 tools/extract_strings.py
    # Writes src/strings.c
"""
import re
from pathlib import Path

ABOOT_DIR = Path(__file__).parent.parent
BINARY = ABOOT_DIR / "aboot.bin"
DECOMP_DIR = ABOOT_DIR / "tmp" / "decompiled"
OUT_C = ABOOT_DIR / "src" / "strings.c"

# ELF load address mapping
ELF_VADDR_BASE = 0x8f600000
ELF_FILE_OFFSET = 0x8000


def vaddr_to_offset(vaddr: int) -> int:
    return vaddr - ELF_VADDR_BASE + ELF_FILE_OFFSET


def read_string(binary_data: bytes, vaddr: int, max_len: int = 256) -> str | None:
    offset = vaddr_to_offset(vaddr)
    if offset < 0 or offset >= len(binary_data):
        return None
    end = min(offset + max_len, len(binary_data))
    chunk = binary_data[offset:end]
    null_pos = chunk.find(b'\x00')
    if null_pos >= 0:
        chunk = chunk[:null_pos]
    return chunk.decode('latin-1')


def escape_c(s: str) -> str:
    result = []
    for c in s:
        if c == '\\': result.append('\\\\')
        elif c == '"': result.append('\\"')
        elif c == '\n': result.append('\\n')
        elif c == '\r': result.append('\\r')
        elif c == '\t': result.append('\\t')
        elif ord(c) < 32 or ord(c) > 126: result.append(f'\\x{ord(c):02x}')
        else: result.append(c)
    return ''.join(result)


def sanitize_symbol(name: str) -> str:
    """Replace invalid C identifier characters (mirrors preprocess.py)."""
    return name.replace('>', '_gt_').replace('<', '_lt_').replace(' ', '_').replace('?', '_q_')


def collect_string_syms(source: str) -> dict[str, str]:
    """Return mapping of sanitized_name -> original_name for all s_xxx symbols."""
    result = {}
    for m in re.finditer(r'\b(s_[\w<>?]*_[0-9a-f]{8})\b', source):
        raw = m.group(1)
        result[sanitize_symbol(raw)] = raw
    return result


def main():
    # Collect all decompiled C source
    if not DECOMP_DIR.exists():
        print("Run ghidra_analyze.py first (no decompiled/ dir found)")
        raise SystemExit(1)
    all_c = "\n".join(p.read_text() for p in DECOMP_DIR.glob("*.c"))

    # Find all string symbols (handles special chars like <, >, ?)
    sym_map = collect_string_syms(all_c)  # sanitized_name -> original_name
    print(f"[*] Found {len(sym_map)} string symbols")

    # Read binary
    binary_data = BINARY.read_bytes()

    # Extract strings — define under sanitized name, comment shows original
    defs = []
    _addr_re = re.compile(r'_([0-9a-f]{8})$')
    for sanitized, original in sorted(sym_map.items()):
        m = _addr_re.search(original)
        if not m:
            continue
        vaddr = int(m.group(1), 16)
        s = read_string(binary_data, vaddr)
        comment = f" /* {original} */" if sanitized != original else ""
        if s is not None:
            defs.append(f'const char {sanitized}[] = "{escape_c(s)}";{comment}')
        else:
            defs.append(f'/* not found in binary: {sanitized} */')

    # Write output
    OUT_C.parent.mkdir(parents=True, exist_ok=True)
    with open(OUT_C, 'w') as f:
        f.write("/* String definitions extracted from aboot.bin */\n")
        f.write("/* Regenerate with: make strings */\n\n")
        f.write('\n'.join(defs))
        f.write('\n')

    print(f"[*] Written {OUT_C} ({len(defs)} strings)")


if __name__ == "__main__":
    main()
