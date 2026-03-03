#!/usr/bin/env python3
"""
Compare original aboot disassembly vs recompiled binary.
Scores per-function similarity and highlights divergence.

Usage:
    python3 tools/diff_asm.py [--orig tmp/aboot_orig.asm] [--new tmp/aboot_recompiled.asm]
"""
import argparse
import difflib
import json
import re
import sys
from pathlib import Path

ABOOT_DIR    = Path(__file__).parent.parent
DEFAULT_ORIG = ABOOT_DIR / "tmp" / "aboot_orig.asm"
DEFAULT_NEW  = ABOOT_DIR / "tmp" / "aboot_recompiled.asm"
FUNCS_JSON   = ABOOT_DIR / "tmp" / "functions.json"


def parse_asm(path: Path) -> dict[str, list[str]]:
    """Parse objdump -d output into {func_name: [instruction_lines]}."""
    funcs: dict[str, list[str]] = {}
    current = None
    for line in path.read_text().splitlines():
        # Function header: "00200008 <func_name>:"
        m = re.match(r'^([0-9a-f]+)\s+<([^>]+)>:', line)
        if m:
            current = m.group(2)
            funcs[current] = []
        elif current and line.strip():
            # Strip address prefix, keep opcode+operands
            m2 = re.match(r'^\s+[0-9a-f]+:\s+(?:[0-9a-f]{2} )+\s*(.*)', line)
            if m2:
                funcs[current].append(m2.group(1).strip())
    return funcs


def score_funcs(orig: dict, new: dict) -> list[dict]:
    results = []
    all_names = sorted(set(list(orig.keys()) + list(new.keys())))
    for name in all_names:
        if name not in orig:
            results.append({"name": name, "score": 0.0, "status": "only_in_new"})
            continue
        if name not in new:
            results.append({"name": name, "score": 0.0, "status": "only_in_orig"})
            continue
        a = orig[name]
        b = new[name]
        ratio = difflib.SequenceMatcher(None, a, b).ratio()
        results.append({
            "name": name,
            "score": round(ratio, 4),
            "orig_lines": len(a),
            "new_lines": len(b),
            "status": "match" if ratio == 1.0 else "diff",
        })
    return results


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--orig", default=str(DEFAULT_ORIG))
    parser.add_argument("--new",  default=str(DEFAULT_NEW))
    parser.add_argument("--show-diffs", action="store_true",
                        help="Print unified diff for non-matching functions")
    parser.add_argument("--min-score", type=float, default=0.0,
                        help="Only show functions below this score")
    args = parser.parse_args()

    orig_path = Path(args.orig)
    new_path  = Path(args.new)
    if not orig_path.exists():
        print(f"ERROR: {orig_path} not found. Run arm-none-eabi-objdump first.")
        sys.exit(1)
    if not new_path.exists():
        print(f"ERROR: {new_path} not found. Compile first.")
        sys.exit(1)

    print(f"[*] Parsing {orig_path.name}...")
    orig = parse_asm(orig_path)
    print(f"[*] Parsing {new_path.name}...")
    new = parse_asm(new_path)

    print(f"[*] Orig: {len(orig)} funcs,  New: {len(new)} funcs")

    results = score_funcs(orig, new)
    results.sort(key=lambda r: r["score"])

    perfect = sum(1 for r in results if r.get("score", 0) == 1.0)
    total   = len(results)
    avg     = sum(r.get("score", 0) for r in results) / total if total else 0

    print(f"\n=== Summary ===")
    print(f"  Perfect matches : {perfect}/{total} ({100*perfect//total if total else 0}%)")
    print(f"  Average score   : {avg:.3f}")
    print(f"\n=== Worst matches ===")
    for r in results[:20]:
        if r.get("score", 0) >= (args.min_score or 1.0):
            break
        print(f"  {r['score']:.3f}  {r['name']}  [{r.get('status','')}]")

    if args.show_diffs:
        for r in results:
            if r.get("status") == "diff" and r.get("score", 0) < (args.min_score or 1.0):
                name = r["name"]
                diff = list(difflib.unified_diff(
                    orig.get(name, []), new.get(name, []),
                    fromfile=f"orig/{name}", tofile=f"new/{name}", lineterm=""))
                if diff:
                    print("\n" + "\n".join(diff[:60]))

    out = ABOOT_DIR / "tmp" / "asm_diff.json"
    out.write_text(json.dumps(results, indent=2))
    print(f"\n[*] Full results → {out}")


if __name__ == "__main__":
    main()
