#!/usr/bin/env python3
"""split_fhprg.py — Split monolithic fhprg.c into per-module files

Reads src/fhprg.c and splits it into:
  src/fhprg/globals.h   — all extern declarations, #defines, forward decls
  src/fhprg/thunks.c    — 0x002xxxxx veneer/thunk functions
  src/fhprg/<name>.c    — functions grouped by original source file

Original source filenames are recovered from assert/error-handler strings
(e.g. ((code*)DAT_0804cd60)("smem.c", ...)).  Functions from the same
original file are clustered together in the binary, so untagged functions
between two tagged anchors are assigned to the preceding anchor's file.
Large untagged regions (>MAX_UNTAGGED_RUN consecutive untagged functions)
are kept as separate "fhprg_XXXX" modules named by start address.

Usage:
    python3 tools/split_fhprg.py
"""

import re
import sys
from pathlib import Path

PROJ = Path(__file__).parent.parent
SRC = PROJ / "src" / "fhprg.c"
OUT_DIR = PROJ / "src" / "fhprg"

# Non-extern global variable names (defined in globals.h without extern)
LOCAL_GLOBALS = set()

# Regex to detect function body start (K&R or ANSI style)
FUNC_DEF_RE = re.compile(
    r'^[a-z]\S*(?:\s*\*)?\s+'
    r'((?:thunk_)?FUN_([0-9a-fA-F]{8}))\s*\('
)

# Regex to find original source filenames in assert/error strings
FILENAME_RE = re.compile(r'"([a-z][a-z0-9_]*\.c)"')

# Thunk address range
THUNK_START = 0x00220000
THUNK_END   = 0x00230000

# If a tagged file would absorb more than this many consecutive untagged
# functions, the untagged prefix is split into its own module instead.
MAX_UNTAGGED_RUN = 8


def parse_source():
    """Parse fhprg.c into preamble + function bodies."""
    text = SRC.read_text()
    lines = text.split('\n')

    body_start = None
    for i, line in enumerate(lines):
        if '/* ===== Function bodies =====' in line:
            body_start = i
            break

    if body_start is None:
        print("ERROR: Could not find '/* ===== Function bodies =====' marker")
        sys.exit(1)

    return lines[:body_start], lines[body_start:]


def extract_functions(body_lines):
    """Extract individual functions from the body section.

    Returns list of (address, name, lines, source_file_or_None) tuples.
    """
    functions = []
    current_func = None
    current_addr = 0
    current_lines = []
    current_files = set()
    brace_depth = 0
    in_func = False

    def _save():
        if current_func:
            src = sorted(current_files)[0] if current_files else None
            functions.append((current_addr, current_func, current_lines, src))

    for line in body_lines:
        m = FUNC_DEF_RE.match(line)
        if m and not in_func:
            _save()
            current_func = m.group(1)
            current_addr = int(m.group(2), 16)
            current_lines = [line]
            current_files = set()
            brace_depth = 0
            in_func = False
            continue

        current_lines.append(line)

        for fm in FILENAME_RE.finditer(line):
            current_files.add(fm.group(1))

        for ch in line:
            if ch == '{':
                brace_depth += 1
                in_func = True
            elif ch == '}':
                brace_depth -= 1
                if brace_depth == 0 and in_func:
                    in_func = False

    _save()
    return functions


def _make_addr_module(addr):
    """Generate a module name for an untagged region starting at addr."""
    return f"fhprg_{addr:04x}"


def assign_modules(functions):
    """Assign each function to a module using filename clustering.

    Algorithm:
      1. Separate thunks (0x002xxxxx) into their own module.
      2. Sort remaining functions by address.
      3. Walk the sorted list.  When a function has a known source filename,
         set that as the "current" module.  Untagged functions inherit the
         current module — unless there are more than MAX_UNTAGGED_RUN
         consecutive untagged functions, in which case they become their
         own "fhprg_XXXX" module.
    """
    thunks = []
    main_funcs = []

    for addr, name, lines, src in functions:
        if THUNK_START <= addr < THUNK_END:
            thunks.append((addr, name, lines, src))
        else:
            main_funcs.append((addr, name, lines, src))

    main_funcs.sort(key=lambda x: x[0])

    # Build raw tag list: index -> source_file or None
    raw_tags = [src.replace('.c', '') if src else None for _, _, _, src in main_funcs]

    # Pass 1: identify tagged anchors and measure untagged gaps between them
    # An "anchor" is any index where raw_tags[i] is not None.
    anchors = [i for i, t in enumerate(raw_tags) if t is not None]

    assignments = [None] * len(main_funcs)

    # Tag anchors themselves
    for i in anchors:
        assignments[i] = raw_tags[i]

    # Fill gaps between consecutive anchors
    # For each pair (prev_anchor, next_anchor), the gap is the indices between them.
    # A gap before the first anchor or after the last anchor is treated as edge.
    boundaries = [-1] + anchors + [len(main_funcs)]

    for b in range(len(boundaries) - 1):
        start = boundaries[b] + 1
        end = boundaries[b + 1]  # exclusive (or anchor index)

        if start >= end:
            continue  # no gap

        gap_len = end - start
        if gap_len <= MAX_UNTAGGED_RUN:
            # Small gap: assign to the nearest anchor
            if b > 0 and boundaries[b] >= 0:
                # Prefer preceding anchor
                tag = assignments[boundaries[b]]
            elif end < len(main_funcs) and assignments[end] is not None:
                # Use following anchor (leading edge)
                tag = assignments[end]
            else:
                tag = _make_addr_module(main_funcs[start][0])
            for i in range(start, end):
                assignments[i] = tag
        else:
            # Large gap: make a new module named by start address
            tag = _make_addr_module(main_funcs[start][0])
            for i in range(start, end):
                assignments[i] = tag

    # Any remaining None (shouldn't happen) gets a fallback
    for i in range(len(assignments)):
        if assignments[i] is None:
            assignments[i] = _make_addr_module(main_funcs[i][0])

    # Build module dict
    modules = {}
    if thunks:
        modules["thunks"] = [(a, n, l) for a, n, l, _ in thunks]

    for i, (addr, name, lines, _) in enumerate(main_funcs):
        mod = assignments[i]
        modules.setdefault(mod, []).append((addr, name, lines))

    return modules


def write_globals_header(preamble_lines):
    """Write src/fhprg/globals.h from the preamble."""
    header = [
        "/* Auto-generated: fhprg globals, externs, and forward declarations */",
        "/* Split from src/fhprg.c by tools/split_fhprg.py */",
        "#pragma once",
        '#include "ghidra_types.h"',
        "",
    ]

    non_extern_re = re.compile(
        r'^(uint|int|char|byte|short|ushort|bool|undefined[0-9]*)\s+(_local_\w+);')
    extern_local_re = re.compile(
        r'^extern\s+(uint|int|char|byte|short|ushort|bool|undefined[0-9]*)\s+(_local_\w+);')

    for line in preamble_lines[1:]:
        m = non_extern_re.match(line)
        m2 = extern_local_re.match(line)
        if m:
            LOCAL_GLOBALS.add(m.group(2))
            header.append(f"extern {m.group(1)} {m.group(2)};")
        elif m2:
            LOCAL_GLOBALS.add(m2.group(2))
            header.append(line)
        else:
            header.append(line)

    path = OUT_DIR / "globals.h"
    path.write_text('\n'.join(header) + '\n')
    print(f"  {path}: {len(header)} lines")


def write_module(name, func_list, define_locals=False):
    """Write a module .c file."""
    lines = [
        f"/* Auto-generated: {name}.c */",
        f"/* Functions: {len(func_list)} */",
        '#include "globals.h"',
        "",
    ]

    if define_locals:
        lines.append("/* Non-extern globals defined here (declared extern in globals.h) */")
        for local_name in sorted(LOCAL_GLOBALS):
            lines.append(f"uint {local_name};")
        lines.append("")

    for addr, fname, flines in sorted(func_list, key=lambda x: x[0]):
        lines.append(f"/* 0x{addr:08x} */")
        lines.extend(flines)
        lines.append("")

    path = OUT_DIR / f"{name}.c"
    path.write_text('\n'.join(lines) + '\n')
    print(f"  {path}: {len(func_list)} functions, {len(lines)} lines")


def main():
    OUT_DIR.mkdir(parents=True, exist_ok=True)

    # Remove old generated .c files (but not globals.h which is regenerated)
    for old in list(OUT_DIR.glob("mod_*.c")) + list(OUT_DIR.glob("fhprg_*.c")):
        old.unlink()
        print(f"  removed {old}")
    # Also remove any named-module files from a previous run
    for old in OUT_DIR.glob("*.c"):
        if old.name == "globals.h":
            continue
        old.unlink()
        print(f"  removed {old}")

    print("[*] Parsing src/fhprg.c...")
    preamble, body = parse_source()
    print(f"    Preamble: {len(preamble)} lines")
    print(f"    Body: {len(body)} lines")

    print("[*] Extracting functions...")
    functions = extract_functions(body)
    tagged = sum(1 for _, _, _, s in functions if s is not None)
    print(f"    Found {len(functions)} function bodies ({tagged} with source file tags)")

    print("[*] Assigning modules by filename clustering...")
    modules = assign_modules(functions)
    print(f"    {len(modules)} modules")

    print(f"\n[*] Writing {len(modules) + 1} files to {OUT_DIR}/")
    write_globals_header(preamble)

    sorted_mods = sorted(modules.keys())
    for i, mod_name in enumerate(sorted_mods):
        write_module(mod_name, modules[mod_name], define_locals=(i == 0))

    total_funcs = sum(len(v) for v in modules.values())
    print(f"\n[*] Done: {total_funcs} functions across {len(modules)} modules + globals.h")


if __name__ == '__main__':
    main()
