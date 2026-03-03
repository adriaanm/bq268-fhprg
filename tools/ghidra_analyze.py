#!/usr/bin/env python3
"""
Ghidra headless analysis of aboot.bin via PyGhidra.
Exports decompiled C for every function to tmp/decompiled/.
Also exports function info to tmp/functions.json.

Usage:
    tmp/pyghidra_venv/bin/python3 tools/ghidra_analyze.py [--reuse]

    --reuse: skip re-import and re-analysis (reuse existing Ghidra project)
"""
import argparse
import json
import sys
import warnings
from pathlib import Path

from jpype import JClass

ABOOT_DIR  = Path(__file__).parent.parent
BINARY     = ABOOT_DIR / "aboot.bin"
OUT_DIR    = ABOOT_DIR / "tmp" / "decompiled"
PROJ_DIR   = ABOOT_DIR / "tmp" / "ghidra_proj"
FUNCS_JSON = ABOOT_DIR / "tmp" / "functions.json"
VENV_PY    = ABOOT_DIR / "tmp" / "pyghidra_venv" / "bin" / "python3"

# Ghidra installation - check common locations
for _candidate in [
    Path("/opt/homebrew/Cellar/ghidra/12.0.3/libexec"),
    Path("/usr/local/Cellar/ghidra/12.0.3/libexec"),
    Path.home() / "ghidra_12.0.3",
]:
    if _candidate.exists():
        GHIDRA_INSTALL = _candidate
        break
else:
    GHIDRA_INSTALL = Path("/opt/homebrew/Cellar/ghidra/12.0.3/libexec")

# ARM32 Thumb language for msm8909 / Cortex-A7
LANGUAGE = "ARM:LE:32:v8"
COMPILER = "default"

# Code region boundaries from plan.md (aboot.bin PT_LOAD segment)
CODE_START = 0x8f600000
CODE_END   = 0x8f652e80


def _configure_analyzers(program):
    """
    Configure Ghidra analyzers to preserve all code blocks.

    By default, Ghidra's decompiler removes "unreachable" blocks, which
    causes the decompiled C to not match the original binary. For ROM
    reconstruction, we need to preserve ALL code.
    """
    # Get options from the "Analyzers" category
    options = program.getOptions("Analyzers")
    all_opts = list(options.getOptionNames())
    print(f"    Found {len(all_opts)} analyzer options")

    # Print ALL options to see what's available
    disabled = []
    for opt in all_opts:
        try:
            current = options.getBoolean(opt, True)
            # Disable analyzers that might remove code
            opt_lower = opt.lower()
            if any(kw in opt_lower for kw in ["dead", "unreachable", "remove", "eliminate",
                                                "simplify", "propagate", "constant"]):
                options.setBoolean(opt, False)
                disabled.append(opt)
        except Exception:
            pass

    if disabled:
        print(f"    Disabled analyzers: {disabled}")
    else:
        print("    No relevant analyzers found to disable")


def _force_disasm_all(program):
    """
    Force disassembly of the entire code region.

    NOTE: Disabled for now due to Ghidra 12 API changes.
    The decompiler fix (setEliminateUnreachable) is the key change.
    """
    print("[*] Force-disassembly skipped (not needed with decompiler fix)")
    pass


def run_analysis(reuse: bool):
    import pyghidra

    OUT_DIR.mkdir(parents=True, exist_ok=True)
    PROJ_DIR.mkdir(parents=True, exist_ok=True)

    print(f"[*] Starting Ghidra JVM (install_dir={GHIDRA_INSTALL})...")
    pyghidra.start(install_dir=GHIDRA_INSTALL)

    print(f"[*] Importing {BINARY} ...")
    # open_program is deprecated in 3.x but still fully functional
    with warnings.catch_warnings():
        warnings.simplefilter("ignore", DeprecationWarning)
        import pyghidra.core as _core
        project, program = _core._setup_project(
            binary_path=BINARY,
            project_location=PROJ_DIR,
            project_name="aboot",
            language=None if reuse else LANGUAGE,
            compiler=None if reuse else COMPILER,
            nested_project_location=False,
        )

    print(f"[*] Program: {program.getName()}")
    print(f"[*] Language: {program.getLanguage().getLanguageID()}")

    if not reuse:
        print("[*] Configuring analyzers to preserve all code...")
        _configure_analyzers(program)

        print("[*] Running auto-analysis (this may take a few minutes)...")
        from pyghidra.api import analyze, transaction, task_monitor
        with transaction(program, "Auto-analyze"):
            log = analyze(program)
        if log:
            (ABOOT_DIR / "tmp" / "ghidra_analysis.log").write_text(log)
            print(f"[*] Analysis log written to tmp/ghidra_analysis.log")

        # Force disassembly of any code gaps missed by auto-analysis
        _force_disasm_all(program)

    _decompile_all(program)

    # Cleanup — GhidraProject manages its own program lifecycle; just close project
    try:
        project.close()
    except Exception:
        pass  # JVM cleanup noise on exit is harmless


def _decompile_all(program):
    # Use explicit Java imports to be clear about API usage
    DecompInterface = JClass("ghidra.app.decompiler.DecompInterface")
    DecompileOptions = JClass("ghidra.app.decompiler.DecompileOptions")
    TaskMonitor = JClass("ghidra.util.task.TaskMonitor")

    func_mgr = program.getFunctionManager()
    funcs = list(func_mgr.getFunctions(True))
    print(f"[*] Found {len(funcs)} functions — decompiling...")

    decomp = DecompInterface()
    opts = DecompileOptions()

    # Critical: Disable elimination of unreachable code in decompiler
    # This preserves all basic blocks, even if Ghidra thinks they're unreachable
    # API: ghidra.app.decompiler.DecompileOptions.setEliminateUnreachable(boolean)
    opts.setEliminateUnreachable(False)
    print("[*] setEliminateUnreachable(False) called")

    opts.setMaxPayloadMBytes(100)  # Allow larger decompilation results

    decomp.setOptions(opts)
    decomp.toggleCCode(True)
    decomp.toggleSyntaxTree(True)
    decomp.setSimplificationStyle("decompile")
    decomp.openProgram(program)

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

    combined = ABOOT_DIR / "tmp" / "aboot_decompiled.c"
    combined.write_text("\n".join(combined_parts))
    print(f"[*] Combined C  → {combined}")

    FUNCS_JSON.write_text(json.dumps(func_data, indent=2))
    print(f"[*] Function index → {FUNCS_JSON}")
    print(f"[*] Done: {ok}/{len(func_data)} decompiled OK, individual files in {OUT_DIR}/")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Decompile aboot.bin via PyGhidra")
    parser.add_argument("--reuse", action="store_true",
                        help="Reuse existing Ghidra project (skip import+analysis)")
    parser.add_argument("--ghidra", type=Path, default=None,
                        help="Path to Ghidra installation directory")
    args = parser.parse_args()

    if args.ghidra:
        GHIDRA_INSTALL = args.ghidra

    try:
        import pyghidra  # noqa: F401
    except ImportError:
        print("ERROR: pyghidra not importable. Run with:")
        print("  tmp/pyghidra_venv/bin/python3 tools/ghidra_analyze.py")
        sys.exit(1)

    run_analysis(args.reuse)
