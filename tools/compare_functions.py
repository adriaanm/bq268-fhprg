#!/usr/bin/env python3
"""
Compare original vs recompiled fhprg functions.

For a sample of functions from functions.json, extracts original bytes
from fhprg_peek.bin, disassembles both original and recompiled, and
compares the assembly instruction-by-instruction.

Uses multiple comparison strategies:
1. Strict positional comparison (instruction-by-instruction)
2. Mnemonic-sequence LCS (longest common subsequence) similarity
3. Instruction bag-of-words similarity (ignoring order)
4. Pattern analysis (movw/movt vs ldr-pool, register allocation, etc.)
"""

import json
import subprocess
import re
import sys
import tempfile
import os
from collections import Counter
from difflib import SequenceMatcher

ORIG_BIN = "fhprg_peek.bin"
RECOMP_ELF = "tmp/fhprg_linked.elf"
FUNCS_JSON = "tmp/functions.json"

# From ELF program headers: LOAD 0x003000 -> 0x08006000, size 0x38440
CODE_VMA = 0x08006000
CODE_FILE_OFF = 0x3000
CODE_SIZE = 0x38440


def load_functions():
    with open(FUNCS_JSON) as f:
        funcs = json.load(f)
    return [
        fn for fn in funcs
        if fn["address"].startswith("0800")
        and fn["size"] > 4
        and fn.get("status") == "ok"
        and not fn["name"].startswith("thunk_")
    ]


def pick_sample(funcs, n_small=4, n_med=3, n_large=3):
    """Pick representative functions of different sizes."""
    small = [f for f in funcs if f["size"] < 50]
    med = [f for f in funcs if 50 <= f["size"] <= 200]
    large = [f for f in funcs if f["size"] > 200]

    picked = []
    for pool, count in [(small, n_small), (med, n_med), (large, n_large)]:
        if len(pool) <= count:
            picked.extend(pool)
        else:
            step = len(pool) // count
            for i in range(count):
                picked.append(pool[i * step])

    return picked


def disasm_original(addr, size):
    """Extract bytes from original binary and disassemble as Thumb."""
    file_off = addr - CODE_VMA + CODE_FILE_OFF

    with open(ORIG_BIN, "rb") as f:
        f.seek(file_off)
        data = f.read(size)

    with tempfile.NamedTemporaryFile(suffix=".bin", delete=False) as tmp:
        tmp.write(data)
        tmp_path = tmp.name

    try:
        result = subprocess.run(
            ["arm-none-eabi-objdump", "-D", "-b", "binary",
             "-m", "arm", "-M", "force-thumb", tmp_path],
            capture_output=True, text=True,
        )
        return result.stdout
    finally:
        os.unlink(tmp_path)


def get_recomp_disasm():
    """Get full disassembly of recompiled ELF (cached)."""
    if not hasattr(get_recomp_disasm, "_cache"):
        result = subprocess.run(
            ["arm-none-eabi-objdump", "-d", RECOMP_ELF],
            capture_output=True, text=True,
        )
        get_recomp_disasm._cache = result.stdout
    return get_recomp_disasm._cache


def extract_recomp_function(name):
    """Extract disassembly for a specific function from recompiled ELF."""
    full = get_recomp_disasm()
    pattern = re.compile(rf"^[0-9a-f]+ <{re.escape(name)}>:", re.MULTILINE)
    match = pattern.search(full)
    if not match:
        return None

    next_func = re.search(r"^[0-9a-f]+ <\w+>:", full[match.end():], re.MULTILINE)
    if next_func:
        end = match.end() + next_func.start()
    else:
        end = len(full)

    return full[match.start():end]


def parse_instructions(disasm_text):
    """Parse disassembly into structured instruction list."""
    insns = []
    for line in disasm_text.split("\n"):
        line = line.strip()
        # objdump format: "   0:\t4904      \tldr\tr1, [pc, #16]\t@ (0x14)"
        # Split on tabs: [addr+hex, mnemonic, operands, comment...]
        m = re.match(r"^\s*([0-9a-f]+):\s+([0-9a-f ]+)\t(\S+)(?:\t(.+?))?(?:\t@.*)?$", line)
        if not m:
            continue

        addr_str = m.group(1)
        hex_bytes = m.group(2).strip()
        mnemonic_raw = m.group(3).strip()
        operands_raw = (m.group(4) or "").strip()
        insn_and_ops = (mnemonic_raw + " " + operands_raw).strip()
        comment = ""

        # We already have mnemonic and operands from regex
        mnemonic = mnemonic_raw
        operands = operands_raw
        # Remove any inline comments that slipped through
        operands = re.sub(r"\s*@\s*\(.*?\)", "", operands)
        operands = re.sub(r"\s*@\s*0x[0-9a-f]+", "", operands)
        operands = re.sub(r"\s*@\s*\d+", "", operands)

        # Normalize mnemonic: strip .n/.w width suffixes
        mnemonic_base = re.sub(r"\.(n|w)$", "", mnemonic)

        # Skip literal pool data
        if mnemonic in (".word", ".short", ".byte"):
            continue

        insns.append({
            "mnemonic": mnemonic,
            "mnemonic_base": mnemonic_base,
            "operands": operands,
            "full": (mnemonic + " " + operands).strip(),
            "hex": hex_bytes,
        })
    return insns


def mnemonic_lcs_similarity(orig_insns, recomp_insns):
    """Compute similarity based on longest common subsequence of mnemonics."""
    orig_mn = [i["mnemonic_base"] for i in orig_insns]
    recomp_mn = [i["mnemonic_base"] for i in recomp_insns]

    sm = SequenceMatcher(None, orig_mn, recomp_mn)
    ratio = sm.ratio()
    return ratio


def bag_of_mnemonics_similarity(orig_insns, recomp_insns):
    """Compute similarity based on instruction frequency (bag of words)."""
    orig_bag = Counter(i["mnemonic_base"] for i in orig_insns)
    recomp_bag = Counter(i["mnemonic_base"] for i in recomp_insns)

    # Intersection / union
    all_mn = set(orig_bag) | set(recomp_bag)
    if not all_mn:
        return 1.0

    intersection = sum(min(orig_bag[m], recomp_bag[m]) for m in all_mn)
    union = sum(max(orig_bag[m], recomp_bag[m]) for m in all_mn)
    return intersection / union if union else 1.0


def analyze_address_loading(insns):
    """Count movw/movt pairs vs ldr [pc] (literal pool) patterns."""
    movw_count = sum(1 for i in insns if i["mnemonic_base"] == "movw")
    movt_count = sum(1 for i in insns if i["mnemonic_base"] == "movt")
    ldr_pc = sum(1 for i in insns if i["mnemonic_base"] == "ldr" and "pc" in i["operands"])
    adr_count = sum(1 for i in insns if i["mnemonic_base"] in ("adr", "add") and "pc" in i["operands"])
    return {
        "movw_movt_pairs": min(movw_count, movt_count),
        "ldr_pc_pool": ldr_pc,
        "adr_pc": adr_count,
    }


def strict_positional_match(orig_insns, recomp_insns):
    """Strict instruction-by-instruction comparison."""
    def normalize(insn):
        text = insn["mnemonic_base"] + " " + insn["operands"]
        # Normalize branch targets
        text = re.sub(r"\b(bl?|b\w+)\s+(?:0x)?[0-9a-f]+", r"\1 <target>", text)
        # Normalize PC-relative loads
        text = re.sub(r"ldr\s+(r\d+),\s*\[pc,\s*#\d+\]", r"ldr \1, [pc, #IMM]", text)
        return text

    orig_norm = [normalize(i) for i in orig_insns]
    recomp_norm = [normalize(i) for i in recomp_insns]

    min_len = min(len(orig_norm), len(recomp_norm))
    matching = sum(1 for i in range(min_len) if orig_norm[i] == recomp_norm[i])
    total = max(len(orig_norm), len(recomp_norm))
    return matching / total if total else 1.0


def compare_function(name, addr, size):
    """Full comparison of a single function. Returns dict with results."""
    orig_disasm = disasm_original(addr, size)
    orig_insns = parse_instructions(orig_disasm)

    recomp_disasm = extract_recomp_function(name)
    if recomp_disasm is None:
        return {"name": name, "addr": addr, "size": size, "status": "missing"}

    recomp_insns = parse_instructions(recomp_disasm)

    if not orig_insns:
        return {"name": name, "addr": addr, "size": size, "status": "no_orig_insns"}

    # Check for exact byte match first
    orig_hex = " ".join(i["hex"] for i in orig_insns)
    recomp_hex = " ".join(i["hex"] for i in recomp_insns)
    byte_identical = (orig_hex == recomp_hex)

    # Metrics
    strict_pct = strict_positional_match(orig_insns, recomp_insns)
    lcs_sim = mnemonic_lcs_similarity(orig_insns, recomp_insns)
    bag_sim = bag_of_mnemonics_similarity(orig_insns, recomp_insns)

    orig_addr_info = analyze_address_loading(orig_insns)
    recomp_addr_info = analyze_address_loading(recomp_insns)

    # Count register usage differences
    def get_regs(insns):
        regs = Counter()
        for i in insns:
            for r in re.findall(r'\br(\d+)\b', i["operands"]):
                regs[f"r{r}"] += 1
        return regs

    orig_regs = get_regs(orig_insns)
    recomp_regs = get_regs(recomp_insns)

    return {
        "name": name,
        "addr": addr,
        "size": size,
        "status": "compared",
        "byte_identical": byte_identical,
        "orig_insn_count": len(orig_insns),
        "recomp_insn_count": len(recomp_insns),
        "insn_count_ratio": len(recomp_insns) / len(orig_insns) if orig_insns else 0,
        "strict_match_pct": round(strict_pct * 100, 1),
        "lcs_similarity": round(lcs_sim * 100, 1),
        "bag_similarity": round(bag_sim * 100, 1),
        "orig_addr_loading": orig_addr_info,
        "recomp_addr_loading": recomp_addr_info,
        "orig_insns": orig_insns,
        "recomp_insns": recomp_insns,
    }


def main():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("--all", action="store_true", help="Compare ALL functions (slow)")
    parser.add_argument("--sample", type=int, default=10, help="Sample size per category")
    parser.add_argument("--verbose", "-v", action="store_true")
    args = parser.parse_args()

    print("=" * 80)
    print("fhprg Function Comparison: Original vs Recompiled")
    print("=" * 80)

    funcs = load_functions()
    print(f"\nTotal functions in 0x0800xxxx range (non-thunk): {len(funcs)}")

    if args.all:
        sample = funcs
        print(f"Comparing ALL {len(sample)} functions...")
    else:
        n = max(1, args.sample // 3)
        sample = pick_sample(funcs, n_small=n+1, n_med=n, n_large=n)
        print(f"Selected {len(sample)} functions for comparison")

    # Pre-load recompiled disassembly
    print("Loading recompiled disassembly...", end=" ", flush=True)
    get_recomp_disasm()
    print("done.")

    results = []
    for i, fn in enumerate(sample):
        addr = int(fn["address"], 16)
        r = compare_function(fn["name"], addr, fn["size"])
        results.append(r)
        if (i + 1) % 50 == 0:
            print(f"  ...compared {i+1}/{len(sample)}", flush=True)

    # Filter to successfully compared
    compared = [r for r in results if r["status"] == "compared"]
    missing = [r for r in results if r["status"] == "missing"]

    print(f"\n\n{'=' * 80}")
    print(f"RESULTS")
    print(f"{'=' * 80}")

    # --- Byte-identical ---
    byte_identical = [r for r in compared if r["byte_identical"]]
    print(f"\n  Byte-identical functions: {len(byte_identical)}/{len(compared)}")
    if byte_identical:
        for r in byte_identical[:10]:
            print(f"    {r['name']} ({r['size']} bytes)")

    # --- Per-function table ---
    print(f"\n  {'Function':<22s} {'Size':>5s} {'#Orig':>5s} {'#Rec':>5s} {'Ratio':>6s} "
          f"{'Strict':>7s} {'LCS':>6s} {'Bag':>6s} "
          f"{'OPool':>5s} {'RMov':>5s}")
    print(f"  {'-'*22} {'-'*5} {'-'*5} {'-'*5} {'-'*6} {'-'*7} {'-'*6} {'-'*6} {'-'*5} {'-'*5}")

    for r in compared:
        opool = r["orig_addr_loading"]["ldr_pc_pool"]
        rmov = r["recomp_addr_loading"]["movw_movt_pairs"]
        print(f"  {r['name']:<22s} {r['size']:>5d} {r['orig_insn_count']:>5d} {r['recomp_insn_count']:>5d} "
              f"{r['insn_count_ratio']:>5.2f}x "
              f"{r['strict_match_pct']:>6.1f}% {r['lcs_similarity']:>5.1f}% {r['bag_similarity']:>5.1f}% "
              f"{opool:>5d} {rmov:>5d}")

    if missing:
        print(f"\n  Missing from recompiled ELF: {len(missing)}")
        for r in missing[:10]:
            print(f"    {r['name']} ({r['size']} bytes)")

    # --- Aggregate stats ---
    print(f"\n\n{'=' * 80}")
    print(f"AGGREGATE STATISTICS")
    print(f"{'=' * 80}")

    if compared:
        avg_strict = sum(r["strict_match_pct"] for r in compared) / len(compared)
        avg_lcs = sum(r["lcs_similarity"] for r in compared) / len(compared)
        avg_bag = sum(r["bag_similarity"] for r in compared) / len(compared)
        avg_ratio = sum(r["insn_count_ratio"] for r in compared) / len(compared)

        print(f"\n  Average strict positional match:  {avg_strict:.1f}%")
        print(f"  Average mnemonic LCS similarity:  {avg_lcs:.1f}%")
        print(f"  Average mnemonic bag similarity:  {avg_bag:.1f}%")
        print(f"  Average insn count ratio (rec/orig): {avg_ratio:.2f}x")
        print(f"  Byte-identical: {len(byte_identical)}/{len(compared)} ({100*len(byte_identical)/len(compared):.1f}%)")

        # Address loading pattern summary
        total_orig_pool = sum(r["orig_addr_loading"]["ldr_pc_pool"] for r in compared)
        total_recomp_pool = sum(r["recomp_addr_loading"]["ldr_pc_pool"] for r in compared)
        total_orig_movw = sum(r["orig_addr_loading"]["movw_movt_pairs"] for r in compared)
        total_recomp_movw = sum(r["recomp_addr_loading"]["movw_movt_pairs"] for r in compared)

        print(f"\n  Address loading patterns:")
        print(f"    Original:   {total_orig_pool:4d} ldr [pc] (pool),  {total_orig_movw:4d} movw/movt pairs")
        print(f"    Recompiled: {total_recomp_pool:4d} ldr [pc] (pool),  {total_recomp_movw:4d} movw/movt pairs")

        # --- Similarity distribution ---
        print(f"\n  LCS Similarity Distribution:")
        buckets = [(90, 100), (70, 90), (50, 70), (30, 50), (0, 30)]
        for lo, hi in buckets:
            count = sum(1 for r in compared if lo <= r["lcs_similarity"] < hi or (hi == 100 and r["lcs_similarity"] == 100))
            pct = 100 * count / len(compared)
            bar = "#" * int(pct / 2)
            print(f"    {lo:3d}-{hi:3d}%: {count:4d} ({pct:5.1f}%) {bar}")

        # --- Size category breakdown ---
        print(f"\n  By size category:")
        for label, lo, hi in [("Small (<50B)", 0, 50), ("Medium (50-200B)", 50, 201), ("Large (>200B)", 201, 99999)]:
            cat = [r for r in compared if lo <= r["size"] < hi]
            if cat:
                avg_l = sum(r["lcs_similarity"] for r in cat) / len(cat)
                avg_b = sum(r["bag_similarity"] for r in cat) / len(cat)
                avg_s = sum(r["strict_match_pct"] for r in cat) / len(cat)
                print(f"    {label:20s}: n={len(cat):3d}  strict={avg_s:5.1f}%  LCS={avg_l:5.1f}%  bag={avg_b:5.1f}%")

    # --- Verbose per-function details ---
    if args.verbose and compared:
        print(f"\n\n{'=' * 80}")
        print(f"DETAILED PER-FUNCTION COMPARISON")
        print(f"{'=' * 80}")

        for r in compared:
            size_cat = "small" if r["size"] < 50 else ("medium" if r["size"] <= 200 else "LARGE")
            print(f"\n{'~' * 70}")
            print(f"  {r['name']} @ 0x{r['addr']:08x}  ({r['size']} bytes, {size_cat})")
            print(f"  Strict: {r['strict_match_pct']}%  LCS: {r['lcs_similarity']}%  Bag: {r['bag_similarity']}%")

            if r["size"] < 80:
                print(f"\n  --- Original ({r['orig_insn_count']} insns) ---")
                for insn in r["orig_insns"][:20]:
                    print(f"    {insn['mnemonic']:10s} {insn['operands']}")
                print(f"  --- Recompiled ({r['recomp_insn_count']} insns) ---")
                for insn in r["recomp_insns"][:20]:
                    print(f"    {insn['mnemonic']:10s} {insn['operands']}")


if __name__ == "__main__":
    main()
