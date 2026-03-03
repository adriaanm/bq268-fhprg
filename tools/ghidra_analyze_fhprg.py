#!/usr/bin/env python3
"""
Ghidra headless analysis of fhprg_peek.bin via PyGhidra 3.0.
Exports decompiled C for every function to tmp/decompiled/.
Also exports function info to tmp/functions.json.

Usage:
    tmp/pyghidra_venv/bin/python3 tools/ghidra_analyze_fhprg.py
"""
import json
import sys
import subprocess
from pathlib import Path

from jpype import JClass

FHPRG_DIR  = Path(__file__).parent.parent
BINARY     = FHPRG_DIR / ".." / "fhprg_peek.bin"
OUT_DIR    = FHPRG_DIR / "tmp" / "decompiled"
PROJ_DIR   = FHPRG_DIR / "tmp" / "ghidra_proj"
FUNCS_JSON = FHPRG_DIR / "tmp" / "functions.json"
GHIDRA_INSTALL = Path("/opt/ghidra/ghidra_12.0.3_PUBLIC")


def run_headless_analysis():
    """Run Ghidra headless analyzer to import and analyze the binary."""
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    PROJ_DIR.mkdir(parents=True, exist_ok=True)

    # Run Ghidra headless analyzer
    cmd = [
        str(GHIDRA_INSTALL / "support" / "analyzeHeadless"),
        str(PROJ_DIR),
        "fhprg_peek",
        "-import", str(BINARY),
        "-overwrite",
        "-postScript", str(Path(__file__).parent / "decompile_export.py"),
    ]

    print(f"[*] Running: {' '.join(cmd)}")
    result = subprocess.run(cmd, capture_output=False)
    return result.returncode


def run_pyghidra_decompile():
    """Use PyGhidra to decompile all functions."""
    import pyghidra
    from pyghidra import open_project, program_context

    print(f"[*] Starting Ghidra JVM...")
    pyghidra.start(install_dir=GHIDRA_INSTALL)

    proj_path = PROJ_DIR.resolve()

    with open_project(str(proj_path), 'fhprg_peek') as project:
        with program_context(project, '/fhprg_peek.bin') as prog:
            _decompile_all(prog)


def _decompile_all(prog):
    DecompInterface = JClass("ghidra.app.decompiler.DecompInterface")
    DecompileOptions = JClass("ghidra.app.decompiler.DecompileOptions")
    TaskMonitor = JClass("ghidra.util.task.TaskMonitor")

    func_mgr = prog.getFunctionManager()
    funcs = list(func_mgr.getFunctions(True))
    print(f"[*] Found {len(funcs)} functions — decompiling...")

    if len(funcs) == 0:
        print("[!] No functions found! The binary may need to be analyzed first.")
        return

    decomp = DecompInterface()
    opts = DecompileOptions()
    opts.setEliminateUnreachable(False)
    opts.setMaxPayloadMBytes(100)
    decomp.setOptions(opts)
    decomp.toggleCCode(True)
    decomp.toggleSyntaxTree(True)
    decomp.setSimplificationStyle("decompile")
    decomp.openProgram(prog)

    print("[*] Decompiler configured: eliminateUnreachable=False")

    func_data = []
    combined_parts = []
    ok = 0

    for i, func in enumerate(funcs):
        entry   = func.getEntryPoint()
        name    = func.getName()
        size    = func.getBody().getNumAddresses()
        addr_str = str(entry)

        try:
            res = decomp.decompileFunction(func, 60, TaskMonitor.DUMMY)
            if res.decompileCompleted():
                c_code = res.getDecompiledFunction().getC()
                status = "ok"
                ok += 1
            else:
                c_code = f"/* decompile failed: {res.getErrorMessage()} */\n"
                status = "failed"
        except Exception as e:
            c_code = f"/* exception: {e} */\n"
            status = "error"

        # Individual file per function
        safe_name = name.replace("/", "_").replace(" ", "_")
        out_file = OUT_DIR / f"{addr_str}_{safe_name}.c"
        out_file.write_text(c_code)

        combined_parts.append(f"/* ===== {addr_str}  {name} ===== */\n{c_code}")
        func_data.append({
            "address": addr_str,
            "name": name,
            "size": size,
            "status": status,
        })

        if (i + 1) % 100 == 0:
            print(f"  {i+1}/{len(funcs)} ({ok} ok)...")

    decomp.dispose()

    combined = FHPRG_DIR / "tmp" / "fhprg_decompiled.c"
    combined.write_text("\n".join(combined_parts))
    print(f"[*] Combined C  → {combined}")

    FUNCS_JSON.write_text(json.dumps(func_data, indent=2))
    print(f"[*] Function index → {FUNCS_JSON}")
    print(f"[*] Done: {ok}/{len(func_data)} decompiled OK, individual files in {OUT_DIR}/")


if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser(description="Decompile fhprg_peek.bin via PyGhidra 3.0")
    parser.add_argument("--skip-analysis", action="store_true",
                        help="Skip headless analysis (use existing project)")
    args = parser.parse_args()

    try:
        import pyghidra  # noqa: F401
    except ImportError:
        print("ERROR: pyghidra not importable. Run with:")
        print("  tmp/pyghidra_venv/bin/python3 tools/ghidra_analyze_fhprg.py")
        sys.exit(1)

    if not args.skip_analysis:
        print("[*] Running headless analysis...")
        ret = run_headless_analysis()
        if ret != 0:
            print(f"[!] Headless analysis returned {ret}")

    print("[*] Running decompilation...")
    run_pyghidra_decompile()
