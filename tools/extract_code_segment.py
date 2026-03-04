#!/usr/bin/env python3
"""
Extract the raw code segment from aboot_elf.bin (and optionally a recompiled ELF)
for byte-level comparison.

The LOAD r-x segment lives at file offset 0x3000, paddr 0x200000, size 0x1ea1c.

Usage:
    python3 tools/extract_code_segment.py [--recompiled tmp/compile/aboot_recompiled.elf]
"""
import argparse
import struct
import sys
from pathlib import Path

ABOOT_DIR = Path(__file__).parent.parent
ORIG_ELF  = ABOOT_DIR / "aboot_elf.bin"
OUT_ORIG  = ABOOT_DIR / "tmp" / "orig_code.bin"
OUT_RECOMPILED = ABOOT_DIR / "tmp" / "recompiled_code.bin"


def read_elf_segments(path: Path):
    """Return list of (p_type, p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_flags) for PT_LOAD."""
    data = path.read_bytes()
    e_phoff  = struct.unpack_from("<I", data, 0x1c)[0]
    e_phentsize = struct.unpack_from("<H", data, 0x2a)[0]
    e_phnum  = struct.unpack_from("<H", data, 0x2c)[0]
    segments = []
    for i in range(e_phnum):
        off = e_phoff + i * e_phentsize
        p_type, p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_flags, p_align = \
            struct.unpack_from("<IIIIIIII", data, off)
        segments.append((p_type, p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_flags))
    return data, segments


PT_LOAD = 1
PF_X = 0x1
PF_W = 0x2
PF_R = 0x4


def extract_code(elf_path: Path, out_path: Path):
    data, segs = read_elf_segments(elf_path)
    for (p_type, p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_flags) in segs:
        if p_type == PT_LOAD and (p_flags & PF_X) and not (p_flags & PF_W):
            code = data[p_offset : p_offset + p_filesz]
            out_path.write_bytes(code)
            print(f"  Extracted code segment: {p_filesz:#x} bytes "
                  f"(paddr={p_paddr:#x}, vaddr={p_vaddr:#x}) → {out_path}")
            return p_paddr, p_filesz
    print(f"  ERROR: no r-x LOAD segment found in {elf_path}")
    return None, None


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--recompiled", default=str(ABOOT_DIR / "tmp" / "compile" / "aboot_recompiled.elf"))
    args = parser.parse_args()

    print(f"[*] Extracting original code segment from {ORIG_ELF.name}...")
    paddr, size = extract_code(ORIG_ELF, OUT_ORIG)

    recomp = Path(args.recompiled)
    if recomp.exists():
        print(f"[*] Extracting recompiled code segment from {recomp.name}...")
        extract_code(recomp, OUT_RECOMPILED)

        # Byte comparison
        orig_bytes = OUT_ORIG.read_bytes()
        new_bytes  = OUT_RECOMPILED.read_bytes()
        min_len = min(len(orig_bytes), len(new_bytes))
        diffs = sum(1 for a, b in zip(orig_bytes, new_bytes) if a != b)
        pct = 100 * (min_len - diffs) / min_len if min_len else 0
        print(f"\n  Byte comparison: {diffs} differences in {min_len} bytes "
              f"({pct:.1f}% match)")

        if diffs > 0:
            print("  First 10 differences:")
            shown = 0
            for i, (a, b) in enumerate(zip(orig_bytes, new_bytes)):
                if a != b:
                    print(f"    offset {i:#010x}: orig={a:#04x}  new={b:#04x}")
                    shown += 1
                    if shown >= 10:
                        break
    else:
        print(f"[*] No recompiled binary at {recomp} — skipping comparison")


if __name__ == "__main__":
    main()
