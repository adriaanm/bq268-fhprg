#!/usr/bin/env python3
"""
Ghidra headless analysis of fhprg_peek.bin via PyGhidra 3.0.
Exports decompiled C for every function to tmp/decompiled/.
Also exports function info to tmp/functions.json.

Phase 4 mode (--import-symbols): imports function names from fhprg_syms.txt
and DAT_ symbols from the decompiled source, then re-decompiles.

Usage:
    tmp/pyghidra_venv/bin/python3 tools/ghidra_analyze_fhprg.py
    tmp/pyghidra_venv/bin/python3 tools/ghidra_analyze_fhprg.py --import-symbols
    tmp/pyghidra_venv/bin/python3 tools/ghidra_analyze_fhprg.py --skip-analysis
"""
import json
import re
import sys
import subprocess
from pathlib import Path

FHPRG_DIR  = Path(__file__).parent.parent
BINARY     = FHPRG_DIR / "fhprg_peek.bin"
OUT_DIR    = FHPRG_DIR / "tmp" / "decompiled"
PROJ_DIR   = FHPRG_DIR / "tmp" / "ghidra_proj"
FUNCS_JSON = FHPRG_DIR / "tmp" / "functions.json"
SYMS_FILE  = FHPRG_DIR / "tmp" / "fhprg_syms.txt"
GHIDRA_INSTALL = Path("/opt/ghidra_12.0.4_PUBLIC")


def run_headless_analysis():
    """Run Ghidra headless analyzer to import and analyze the binary."""
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    PROJ_DIR.mkdir(parents=True, exist_ok=True)

    cmd = [
        str(GHIDRA_INSTALL / "support" / "analyzeHeadless"),
        str(PROJ_DIR),
        "fhprg_peek",
        "-import", str(BINARY),
        "-overwrite",
    ]

    print(f"[*] Running: {' '.join(cmd)}")
    result = subprocess.run(cmd, capture_output=False)
    return result.returncode


def parse_syms_file():
    """Parse fhprg_syms.txt: 'ADDR T NAME' per line."""
    funcs = []
    if not SYMS_FILE.exists():
        return funcs
    for line in SYMS_FILE.read_text().splitlines():
        parts = line.strip().split()
        if len(parts) >= 3:
            addr = int(parts[0], 16)
            name = parts[2]
            funcs.append((addr, name))
    return sorted(funcs, key=lambda x: x[0])


def collect_dat_symbols():
    """Collect DAT_ symbol addresses from existing decompiled source."""
    dat_syms = {}
    fhprg_c = FHPRG_DIR / "src" / "fhprg.c"
    if fhprg_c.exists():
        text = fhprg_c.read_text()
        for m in re.finditer(r'\bDAT_([0-9a-fA-F]{8})\b', text):
            addr = int(m.group(1), 16)
            dat_syms[addr] = f"DAT_{m.group(1)}"
    return dat_syms


def import_symbols(prog):
    """Import function and data symbols into Ghidra program."""
    from jpype import JClass

    AddressSpace = JClass("ghidra.program.model.address.AddressSpace")
    SymbolTable = JClass("ghidra.program.model.symbol.SymbolTable")
    SourceType = JClass("ghidra.program.model.symbol.SourceType")

    sym_table = prog.getSymbolTable()
    func_mgr = prog.getFunctionManager()
    addr_factory = prog.getAddressFactory()
    default_space = addr_factory.getDefaultAddressSpace()

    # Import function names from syms file
    func_syms = parse_syms_file()
    print(f"[*] Importing {len(func_syms)} function symbols...")

    imported_funcs = 0
    created_funcs = 0
    for addr_int, name in func_syms:
        addr = default_space.getAddress(addr_int)
        # For Thumb2, set the address with Thumb bit
        func = func_mgr.getFunctionAt(addr)
        if func is not None:
            old_name = func.getName()
            if old_name != name:
                func.setName(name, SourceType.USER_DEFINED)
                imported_funcs += 1
        else:
            # Create function if it doesn't exist
            try:
                func = func_mgr.createFunction(
                    name, addr, None, SourceType.USER_DEFINED
                )
                if func is not None:
                    created_funcs += 1
            except Exception as e:
                pass  # Function body overlap, etc.

    print(f"  Renamed: {imported_funcs}, Created: {created_funcs}")

    # Import DAT_ data symbols
    dat_syms = collect_dat_symbols()
    print(f"[*] Importing {len(dat_syms)} DAT_ symbols...")

    imported_dat = 0
    for addr_int, name in dat_syms.items():
        addr = default_space.getAddress(addr_int)
        existing = sym_table.getPrimarySymbol(addr)
        if existing is None or existing.getName().startswith("DAT_") == False:
            try:
                sym_table.createLabel(addr, name, SourceType.USER_DEFINED)
                imported_dat += 1
            except Exception:
                pass

    print(f"  Imported: {imported_dat} data symbols")

    # Import string symbols (s_xxx_ADDR)
    str_count = 0
    fhprg_c = FHPRG_DIR / "src" / "fhprg.c"
    if fhprg_c.exists():
        text = fhprg_c.read_text()
        for m in re.finditer(r'\b(s_\w+_([0-9a-fA-F]{8}))\b', text):
            name = m.group(1)
            addr_int = int(m.group(2), 16)
            addr = default_space.getAddress(addr_int)
            try:
                sym_table.createLabel(addr, name, SourceType.USER_DEFINED)
                str_count += 1
            except Exception:
                pass
    print(f"  Imported: {str_count} string symbols")

    return imported_funcs + created_funcs + imported_dat


def _decompile_all(prog):
    from jpype import JClass

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

    OUT_DIR.mkdir(parents=True, exist_ok=True)

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


def run_pyghidra(import_symbols_flag=False, skip_analysis=False):
    """Use PyGhidra to open project, optionally import symbols, and decompile."""
    import pyghidra

    print(f"[*] Starting Ghidra JVM (install: {GHIDRA_INSTALL})...")
    pyghidra.start(install_dir=GHIDRA_INSTALL)

    from jpype import JClass

    proj_path = PROJ_DIR.resolve()

    # Check if project exists
    gpr_file = proj_path / "fhprg_peek.gpr"
    if not gpr_file.exists():
        print(f"[!] No existing Ghidra project at {gpr_file}")
        print("[!] Run without --skip-analysis first to create the project")
        sys.exit(1)

    print(f"[*] Opening existing project: {gpr_file}")

    # Open existing project
    GhidraProject = JClass("ghidra.base.project.GhidraProject")
    project = GhidraProject.openProject(str(proj_path), "fhprg_peek")

    # Get the program
    prog = project.openProgram("/", "fhprg_peek.bin", False)
    if prog is None:
        # Try without .bin extension
        prog = project.openProgram("/", "fhprg_peek", False)

    if prog is None:
        print("[!] Could not open program in project")
        sys.exit(1)

    print(f"[*] Opened program: {prog.getName()}")

    if import_symbols_flag:
        # Need a transaction for modifications
        txn = prog.startTransaction("Import symbols")
        try:
            count = import_symbols(prog)
            print(f"[*] Total symbols imported/updated: {count}")
            prog.endTransaction(txn, True)

            # Re-run auto-analysis after symbol import
            print("[*] Re-running auto-analysis with new symbols...")
            AutoAnalysisManager = JClass("ghidra.app.plugin.core.analysis.AutoAnalysisManager")
            TaskMonitor = JClass("ghidra.util.task.TaskMonitor")
            aam = AutoAnalysisManager.getAnalysisManager(prog)
            aam.reAnalyzeAll(None)
            aam.startAnalysis(TaskMonitor.DUMMY)
            print("[*] Auto-analysis complete")
        except Exception as e:
            prog.endTransaction(txn, False)
            print(f"[!] Error importing symbols: {e}")
            raise

    # Decompile all functions
    _decompile_all(prog)

    # Save and close
    project.save(prog)
    project.close()


if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser(description="Decompile fhprg_peek.bin via PyGhidra 3.0")
    parser.add_argument("--skip-analysis", action="store_true",
                        help="Skip headless analysis (use existing project)")
    parser.add_argument("--import-symbols", action="store_true",
                        help="Import function/data symbols before decompiling (Phase 4)")
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
    run_pyghidra(
        import_symbols_flag=args.import_symbols,
        skip_analysis=args.skip_analysis,
    )
