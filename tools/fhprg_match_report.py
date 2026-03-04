#!/usr/bin/env python3
"""fhprg_match_report.py — Per-function match dashboard for fhprg decompilation

Compiles, links, and compares all functions in fhprg against the original binary.
Categorizes each function and produces a JSON report + summary stats.

Categories:
  byte-identical  — same bytes at same size
  insn-equivalent — same normalised instruction sequence
  similar         — >80% instruction similarity
  needs-review    — <80% similarity or size mismatch
  missing         — not found in recompiled binary

Usage:
    python3 tools/fhprg_match_report.py [--rebuild] [--output tmp/fhprg_report.json]
"""

import argparse
import difflib
import json
import subprocess
import sys
import tempfile
import re
from pathlib import Path
from typing import Dict, List, Tuple

PROJ = Path(__file__).parent.parent
ORIG_BIN = PROJ / "fhprg_peek.bin"
RECOMP_ELF = PROJ / "tmp" / "fhprg_linked.elf"
SYMS_FILE = PROJ / "tmp" / "fhprg_syms.txt"
REPORT_FILE = PROJ / "tmp" / "fhprg_report.json"

OBJDUMP = "arm-none-eabi-objdump"

# Import ELF reader and disasm helpers from hybrid_diff
sys.path.insert(0, str(PROJ / "tools"))
from hybrid_diff import ELF, disasm_bytes, disasm_elf, _parse_objdump, load_functions


def build_if_needed(rebuild: bool) -> bool:
    """Build fhprg if needed. Returns True on success."""
    if rebuild or not RECOMP_ELF.exists():
        print("[*] Building fhprg...")
        r = subprocess.run(["make", "fhprg"], capture_output=True, text=True,
                           cwd=str(PROJ), timeout=300)
        if r.returncode != 0:
            print(f"Build failed:\n{r.stderr}", file=sys.stderr)
            return False
    return True


def generate_report(args) -> dict:
    """Generate per-function match report."""
    orig = ELF(ORIG_BIN)
    recomp = ELF(RECOMP_ELF)
    funcs = load_functions(SYMS_FILE)

    # Code segment: 0x08006000..0x0803e440
    code_segs = orig.code_segments()
    main_seg = max(code_segs, key=lambda s: s['p_filesz'])
    code_start = main_seg['p_vaddr']
    code_end = main_seg['p_vaddr'] + main_seg['p_filesz']

    # Build orig name->addr map
    orig_v2n = {int(f['address'], 16): f['name'] for f in funcs}

    # Disassemble recompiled ELF
    print("[*] Disassembling recompiled ELF...")
    recomp_raw = disasm_elf(RECOMP_ELF, thumb=True)
    recomp_v2n = {vaddr & ~1: name for name, (vaddr, _) in recomp_raw.items()}

    code_funcs = sorted(
        [f for f in funcs
         if code_start <= int(f['address'], 16) < code_end
         and f.get('size', 0) > 0],
        key=lambda f: int(f['address'], 16),
    )

    results = []
    stats = {
        'byte_identical': 0,
        'insn_equivalent': 0,
        'similar': 0,
        'needs_review': 0,
        'missing': 0,
        'total': len(code_funcs),
    }

    for fn in code_funcs:
        orig_vaddr = int(fn['address'], 16)
        orig_size = fn['size']
        name = fn['name']

        entry = {
            'name': name,
            'address': f'0x{orig_vaddr:08x}',
            'orig_size': orig_size,
        }

        sym = recomp.symbols.get(name)
        if sym is None or name not in recomp_raw:
            entry['category'] = 'missing'
            stats['missing'] += 1
            results.append(entry)
            continue

        recomp_vaddr = sym[0] & ~1
        recomp_sym_size = sym[1]
        entry['recomp_size'] = recomp_sym_size

        ob = orig.read(orig_vaddr, orig_size)
        if ob is None:
            entry['category'] = 'missing'
            stats['missing'] += 1
            results.append(entry)
            continue

        # Byte-identical check
        rb = recomp.read(recomp_vaddr, orig_size)
        if rb is not None and ob == rb:
            entry['category'] = 'byte_identical'
            entry['similarity'] = 1.0
            stats['byte_identical'] += 1
            results.append(entry)
            continue

        # Instruction comparison
        oa = disasm_bytes(ob, orig_vaddr, orig_size, orig_v2n, thumb=True)
        recomp_lines = recomp_raw[name][1]
        r_size = recomp_sym_size if recomp_sym_size > 0 else orig_size
        ra = _parse_objdump(recomp_lines, recomp_vaddr, r_size, recomp_v2n)

        entry['orig_insns'] = len(oa)
        entry['recomp_insns'] = len(ra)

        if oa and ra and oa == ra:
            entry['category'] = 'insn_equivalent'
            entry['similarity'] = 1.0
            stats['insn_equivalent'] += 1
        elif oa and ra:
            sim = difflib.SequenceMatcher(None, oa, ra).ratio()
            entry['similarity'] = round(sim, 4)
            if sim >= 0.8:
                entry['category'] = 'similar'
                stats['similar'] += 1
            else:
                entry['category'] = 'needs_review'
                stats['needs_review'] += 1
        else:
            entry['category'] = 'needs_review'
            entry['similarity'] = 0.0
            stats['needs_review'] += 1

        results.append(entry)

    return {
        'stats': stats,
        'functions': results,
    }


def print_summary(report: dict) -> None:
    s = report['stats']
    total = s['total']
    ok = s['byte_identical'] + s['insn_equivalent']
    print()
    print("=" * 60)
    print("  fhprg Match Report")
    print("=" * 60)
    print(f"  Total functions     : {total}")
    print(f"  Byte-identical      : {s['byte_identical']:5d}  ({100*s['byte_identical']/total:.1f}%)")
    print(f"  Insn-equivalent     : {s['insn_equivalent']:5d}  ({100*s['insn_equivalent']/total:.1f}%)")
    print(f"  Similar (>80%)      : {s['similar']:5d}  ({100*s['similar']/total:.1f}%)")
    print(f"  Needs review        : {s['needs_review']:5d}  ({100*s['needs_review']/total:.1f}%)")
    print(f"  Missing             : {s['missing']:5d}  ({100*s['missing']/total:.1f}%)")
    print(f"  ─────────────────────────────")
    print(f"  OK (byte+insn)      : {ok:5d}  ({100*ok/total:.1f}%)")
    print("=" * 60)

    # Show distribution by similarity bucket
    funcs = report['functions']
    buckets = {'0-20%': 0, '20-40%': 0, '40-60%': 0, '60-80%': 0, '80-99%': 0, '100%': 0}
    for f in funcs:
        sim = f.get('similarity', 0)
        if sim >= 1.0:
            buckets['100%'] += 1
        elif sim >= 0.8:
            buckets['80-99%'] += 1
        elif sim >= 0.6:
            buckets['60-80%'] += 1
        elif sim >= 0.4:
            buckets['40-60%'] += 1
        elif sim >= 0.2:
            buckets['20-40%'] += 1
        else:
            buckets['0-20%'] += 1
    print("\n  Similarity distribution:")
    for bucket, count in buckets.items():
        bar = '#' * (count * 40 // total)
        print(f"    {bucket:>6s}: {count:5d}  {bar}")


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--rebuild', action='store_true',
                    help='Force rebuild before generating report')
    ap.add_argument('--output', default=str(REPORT_FILE),
                    help='Output JSON report path')
    args = ap.parse_args()

    if not build_if_needed(args.rebuild):
        sys.exit(1)

    report = generate_report(args)

    Path(args.output).write_text(json.dumps(report, indent=2))
    print(f"\n[*] Report written to {args.output}")

    print_summary(report)


if __name__ == '__main__':
    main()
