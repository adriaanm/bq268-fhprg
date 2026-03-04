#!/usr/bin/env python3
"""
Compile individual decompiled functions and compare to original.
Iterates over functions from tmp/decompiled/, tries to compile each one,
and reports which produce matching bytes.

Usage:
    python3 tools/compile_check.py [--func FUN_0000030c] [--all]
"""
import argparse
import json
import os
import re
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

ABOOT_DIR   = Path(__file__).parent.parent
DECOMP_DIR  = ABOOT_DIR / "tmp" / "decompiled"
COMPILE_DIR = ABOOT_DIR / "tmp" / "compile"
ORIG_ELF    = ABOOT_DIR / "aboot_elf.bin"
FUNCS_JSON  = ABOOT_DIR / "tmp" / "functions.json"
TYPES_H     = ABOOT_DIR / "src" / "ghidra_types.h"

# ARM cross-compiler — try multiple GCC versions for best match
GCC_CANDIDATES = [
    "arm-none-eabi-gcc",
]

# Compiler flag sets to try (binary is ARM-32, not Thumb)
FLAG_SETS = [
    ["-O0", "-marm", "-march=armv7-a", "-mfloat-abi=soft"],
    ["-O1", "-marm", "-march=armv7-a", "-mfloat-abi=soft"],
    ["-O2", "-marm", "-march=armv7-a", "-mfloat-abi=soft"],
    ["-Os", "-marm", "-march=armv7-a", "-mfloat-abi=soft"],
    ["-O2", "-marm", "-mcpu=cortex-a7", "-mfloat-abi=soft"],
    ["-Os", "-marm", "-mcpu=cortex-a7", "-mfloat-abi=soft"],
]


def load_elf_code_bytes() -> tuple[bytes, int]:
    """Return (code_bytes, base_paddr) for the r-x LOAD segment."""
    data = ORIG_ELF.read_bytes()
    e_phoff = struct.unpack_from("<I", data, 0x1c)[0]
    e_phentsize = struct.unpack_from("<H", data, 0x2a)[0]
    e_phnum = struct.unpack_from("<H", data, 0x2c)[0]
    for i in range(e_phnum):
        off = e_phoff + i * e_phentsize
        p_type, p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_flags, _ = \
            struct.unpack_from("<IIIIIIII", data, off)
        if p_type == 1 and (p_flags & 1) and not (p_flags & 2):  # PT_LOAD, X, !W
            return data[p_offset:p_offset + p_filesz], p_paddr
    raise RuntimeError("No r-x LOAD segment found")


def get_func_orig_bytes(func_addr_hex: str, func_size: int,
                        code_bytes: bytes, base_paddr: int) -> bytes:
    """Extract original bytes for a function (given vaddr = paddr - base_paddr for this ELF)."""
    # In the ELF: vaddr=0, paddr=base_paddr; so func at vaddr X → paddr = base_paddr + X
    vaddr = int(func_addr_hex, 16)
    offset = vaddr  # offset within code segment (vaddr 0 maps to start of segment)
    return code_bytes[offset : offset + func_size]


def try_compile(func_name: str, c_source: str, gcc: str, flags: list[str]) -> bytes | None:
    """Try to compile a single function, return raw object bytes or None."""
    with tempfile.TemporaryDirectory() as tmp:
        src = Path(tmp) / "func.c"
        obj = Path(tmp) / "func.o"
        src.write_text(f'#include "{TYPES_H.absolute()}"\n' + c_source)
        cmd = [gcc] + flags + [
            "-c", "-ffreestanding", "-nostdlib",
            "-fno-stack-protector",
            "-fno-common",
            "-ffunction-sections",
            str(src), "-o", str(obj),
        ]
        result = subprocess.run(cmd, capture_output=True, text=True)
        if result.returncode != 0:
            return None
        # Extract .text section bytes
        r2 = subprocess.run(
            ["arm-none-eabi-objcopy", "--dump-section", f".text.{func_name}=/dev/stdout",
             str(obj)],
            capture_output=True
        )
        if r2.returncode == 0 and r2.stdout:
            return r2.stdout
        # Try generic .text (binary is ARM-32, no -M force-thumb)
        r3 = subprocess.run(
            ["arm-none-eabi-objdump", "-d", str(obj)],
            capture_output=True, text=True
        )
        if r3.returncode == 0:
            return r3.stdout.encode()
    return None


def compile_function(func: dict, code_bytes: bytes, base_paddr: int,
                     gcc: str = "arm-none-eabi-gcc") -> dict:
    """Try all flag sets, return best result."""
    addr = func["address"]
    name = func["name"]
    size = func["size"]
    orig_bytes = get_func_orig_bytes(addr, size, code_bytes, base_paddr)

    c_file = DECOMP_DIR / f"{addr}_{name}.c"
    if not c_file.exists():
        return {"name": name, "addr": addr, "result": "no_source"}

    c_src = c_file.read_text()
    best = {"name": name, "addr": addr, "result": "compile_fail",
            "best_flags": None, "best_score": 0.0}

    for flags in FLAG_SETS:
        compiled = try_compile(name, c_src, gcc, flags)
        if compiled is None:
            continue
        # Compare bytes (heuristic if compiled is disasm text)
        if isinstance(compiled, bytes) and not compiled.startswith(b"/"):
            n = min(len(orig_bytes), len(compiled))
            matches = sum(1 for a, b in zip(orig_bytes, compiled) if a == b)
            score = matches / max(len(orig_bytes), len(compiled))
            if score > best.get("best_score", 0):
                best.update({
                    "result": "compiled",
                    "best_flags": flags,
                    "best_score": round(score, 4),
                    "orig_size": len(orig_bytes),
                    "compiled_size": len(compiled),
                })
        else:
            # Just record that it compiled
            if best["result"] == "compile_fail":
                best.update({"result": "compiled", "best_flags": flags})

    return best


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--func", help="Compile only this function (name or addr)")
    parser.add_argument("--all", action="store_true", help="Compile all functions")
    parser.add_argument("--gcc", default="arm-none-eabi-gcc")
    parser.add_argument("--flags", help="Override flags (comma-separated)")
    args = parser.parse_args()

    if not FUNCS_JSON.exists():
        print("Run ghidra_analyze.py first"); sys.exit(1)

    funcs = json.loads(FUNCS_JSON.read_text())
    code_bytes, base_paddr = load_elf_code_bytes()
    print(f"[*] Code segment: base_paddr={base_paddr:#x}, size={len(code_bytes):#x}")

    COMPILE_DIR.mkdir(exist_ok=True)

    if args.func:
        funcs = [f for f in funcs
                 if f["name"] == args.func or f["address"] == args.func]
        if not funcs:
            print(f"Function '{args.func}' not found"); sys.exit(1)
    elif not args.all:
        # Default: compile first 20 small functions as a smoke test
        funcs = [f for f in sorted(funcs, key=lambda x: x["size"])
                 if 4 <= f["size"] <= 100][:20]
        print(f"[*] Smoke test: {len(funcs)} small functions")

    results = []
    for f in funcs:
        r = compile_function(f, code_bytes, base_paddr, args.gcc)
        results.append(r)
        score = r.get("best_score", 0)
        print(f"  {r['addr']}  {r['result']:15s}  score={score:.3f}  {r['name']}")

    out = ABOOT_DIR / "tmp" / "compile_results.json"
    out.write_text(json.dumps(results, indent=2))
    print(f"\n[*] Results → {out}")
    compiled = sum(1 for r in results if r["result"] == "compiled")
    print(f"[*] {compiled}/{len(results)} compiled successfully")


if __name__ == "__main__":
    main()
