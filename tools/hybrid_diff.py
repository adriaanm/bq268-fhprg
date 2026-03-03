#!/usr/bin/env python3
"""hybrid_diff.py — Hybrid binary diff for aboot decompilation

Comparison rules
----------------
  data region  0x8f652e80 .. 0x8f680c4c   → byte-identical

  code region  0x8f600000 .. 0x8f652e80:
    • each function (boundaries from functions.json) compared BY NAME:
        look up the function name in the recompiled ELF symbol table,
        read its bytes wherever the linker placed it, then compare
        normalised disassembly.
        Branch targets are replaced with:
          <func_name>   for calls to known functions
          <+0xNN>       for internal jumps (same offset iff code matches)
          <ext±0xNN>    for unresolved externals
    • gaps between functions in the original code region are reported:
        - all-zero / NOP → harmless padding (expected)
        - non-zero       → literal pool or potentially missed function

Exit 0 if data passes and no function fails, 1 otherwise.

Usage
-----
    python3 tools/hybrid_diff.py [--orig aboot.bin] [--recomp aboot_linked.elf]
                                  [--funcs tmp/functions.json]
                                  [--show-diffs] [--show-gaps] [--verbose]
"""

import argparse
import difflib
import json
import re
import struct
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Dict, List, Optional, Tuple

# ── defaults ──────────────────────────────────────────────────────────────────
ABOOT_DIR  = Path(__file__).parent.parent
DEF_ORIG   = ABOOT_DIR / "aboot.bin"
DEF_RECOMP = ABOOT_DIR / "aboot_linked.elf"
DEF_FUNCS  = ABOOT_DIR / "tmp" / "functions.json"

CODE_START = 0x8F600000
CODE_END   = 0x8F652E80
DATA_END   = 0x8F680C4C

OBJDUMP  = "arm-none-eabi-objdump"
OBJCOPY  = "arm-none-eabi-objcopy"
LD       = "arm-none-eabi-ld"

# Branch mnemonics (base, without .w / .n suffixes)
_BRANCH_BASES = frozenset([
    'b', 'bl', 'blx', 'bx',
    'beq', 'bne', 'bcs', 'bcc', 'bmi', 'bpl', 'bvs', 'bvc',
    'bhi', 'bls', 'bge', 'blt', 'bgt', 'ble',
    'cbz', 'cbnz',
])
# ARM objdump uses @ for inline comments; the label after a branch address is in <>
_COMMENT_RE  = re.compile(r'\s*@.*$')
_LABEL_RE    = re.compile(r'\s*<[^>]*>')      # strip "<name+0xNN>" labels
_HEX_ADDR_RE = re.compile(r'\b([0-9a-f]{6,8})\b')

SHT_SYMTAB = 2
STT_FUNC   = 2
STT_NOTYPE = 0

_W = 44  # column width for function names in output


# ── ELF reader ────────────────────────────────────────────────────────────────

class ELF:
    """Minimal 32-bit LE ELF: vaddr→bytes + symbol table."""

    def __init__(self, path: Path) -> None:
        self.path = path
        self.data = path.read_bytes()
        if self.data[:4] != b'\x7fELF':
            raise ValueError(f"{path}: not an ELF file")
        self.segs: List[dict] = self._load_phdrs()
        self.symbols: Dict[str, Tuple[int, int]] = {}  # name → (vaddr, size)
        self.vaddr_to_name: Dict[int, str] = {}
        self._load_symtab()

    def _load_phdrs(self) -> List[dict]:
        d = self.data
        phoff = struct.unpack_from('<I', d, 0x1C)[0]
        phesz = struct.unpack_from('<H', d, 0x2A)[0]
        phnum = struct.unpack_from('<H', d, 0x2C)[0]
        segs = []
        for i in range(phnum):
            o = phoff + i * phesz
            pt, poff, pva, _, pfsz, pmsz, _, _ = struct.unpack_from('<8I', d, o)
            if pt == 1:
                segs.append(dict(p_offset=poff, p_vaddr=pva,
                                 p_filesz=pfsz, p_memsz=pmsz))
        return segs

    def _load_symtab(self) -> None:
        d = self.data
        shoff = struct.unpack_from('<I', d, 0x20)[0]
        shesz = struct.unpack_from('<H', d, 0x2E)[0]
        shnum = struct.unpack_from('<H', d, 0x30)[0]
        shstr = struct.unpack_from('<H', d, 0x32)[0]
        if shoff == 0 or shnum == 0:
            return
        # String table for section names
        sno = shoff + shstr * shesz
        strtab_raw = d[struct.unpack_from('<I', d, sno+0x10)[0] :
                       struct.unpack_from('<I', d, sno+0x10)[0] +
                       struct.unpack_from('<I', d, sno+0x14)[0]]
        # Find SHT_SYMTAB
        for i in range(shnum):
            o = shoff + i * shesz
            if struct.unpack_from('<I', d, o+0x04)[0] != SHT_SYMTAB:
                continue
            sym_off  = struct.unpack_from('<I', d, o+0x10)[0]
            sym_sz   = struct.unpack_from('<I', d, o+0x14)[0]
            sym_link = struct.unpack_from('<I', d, o+0x18)[0]
            sym_ent  = struct.unpack_from('<I', d, o+0x24)[0] or 16
            # Symbol string table
            sto = shoff + sym_link * shesz
            sym_strtab = d[struct.unpack_from('<I', d, sto+0x10)[0] :
                           struct.unpack_from('<I', d, sto+0x10)[0] +
                           struct.unpack_from('<I', d, sto+0x14)[0]]
            sym_data = d[sym_off : sym_off + sym_sz]
            for j in range(len(sym_data) // sym_ent):
                entry = sym_data[j*sym_ent : (j+1)*sym_ent]
                st_name, st_value, st_size, st_info, _, _ = \
                    struct.unpack_from('<IIIBBh', entry)
                st_type = st_info & 0xF
                if st_name == 0 or st_value == 0:
                    continue
                if st_type not in (STT_FUNC, STT_NOTYPE):
                    continue
                name = sym_strtab[st_name:].split(b'\x00', 1)[0].decode('ascii', 'replace')
                if not name:
                    continue
                self.symbols[name] = (st_value, st_size)
                if st_value not in self.vaddr_to_name:
                    self.vaddr_to_name[st_value] = name
            break

    def read(self, vaddr: int, size: int) -> Optional[bytes]:
        for s in self.segs:
            base = s['p_vaddr']
            if base <= vaddr < base + s['p_memsz']:
                foff  = s['p_offset'] + (vaddr - base)
                avail = (s['p_offset'] + s['p_filesz']) - foff
                if avail <= 0:
                    return b'\x00' * size
                raw = self.data[foff : foff + min(size, avail)]
                return raw + b'\x00' * (size - len(raw))
        return None


# ── Disassembly ───────────────────────────────────────────────────────────────

def _wrap_in_elf(code: bytes, vaddr: int) -> Path:
    """
    Wrap raw bytes in an elf32-littlearm ELF at the given VMA so that
    arm-none-eabi-objdump can disassemble it with correct addresses.
    Returns path to a temp ELF file (caller must delete).

    Note: Uses objcopy + ld approach, then objcopy again to set execute flag.
    The --set-section-flags code option doesn't work correctly during binary conversion,
    but applying it to the final ELF does work.
    """
    raw_bin = Path(tempfile.mktemp(suffix='.bin'))
    raw_o   = Path(tempfile.mktemp(suffix='.o'))
    out_elf = Path(tempfile.mktemp(suffix='.elf'))
    ld_scr  = Path(tempfile.mktemp(suffix='.ld'))

    raw_bin.write_bytes(code)
    subprocess.run([OBJCOPY, '-I', 'binary', '-O', 'elf32-littlearm', '-B', 'arm',
                    str(raw_bin), str(raw_o)],
                   check=True, capture_output=True)
    subprocess.run([OBJCOPY,
                    '--rename-section', '.data=.text',
                    str(raw_o), str(raw_o)],
                   check=True, capture_output=True)
    ld_scr.write_text(f'SECTIONS {{ . = 0x{vaddr:x}; .text : ALIGN(8) {{ *(.text) }} }}')
    subprocess.run([LD, '-T', str(ld_scr), '-o', str(out_elf), str(raw_o)],
                   capture_output=True)

    # Apply execute flag to the final ELF (objcopy works correctly on existing ELF)
    subprocess.run([OBJCOPY,
                    '--set-section-flags', '.text=alloc,readonly,code',
                    str(out_elf), str(out_elf)],
                   capture_output=True)

    for p in (raw_bin, raw_o, ld_scr):
        p.unlink(missing_ok=True)
    return out_elf


def _parse_objdump(lines: List[str], fn_vaddr: int,
                   fn_size: int, vaddr_to_name: Dict[int, str]) -> List[str]:
    """
    Parse arm-none-eabi-objdump -d output (tab-delimited format).

    Each instruction line looks like one of:
        8f600000:\tf240 1220 \tmovw\tr2, #288\t@ 0x120
        8f60003a:\td00c      \tbeq.n\t8f600056 <entry+0x56>

    We:
      1. Split on tabs to get [address_field, hex_bytes, mnemonic, operands?, comment?]
      2. Strip ARM inline comments (@ ...) and angle-bracket labels (<name>)
      3. Normalise branch targets to function names or ±delta
    """
    result = []
    for line in lines:
        parts = line.split('\t')
        # Need at least: "  addr:", hex_field, mnemonic
        if len(parts) < 3:
            continue
        addr_field = parts[0].strip()
        if not addr_field.endswith(':'):
            continue
        try:
            addr = int(addr_field[:-1], 16)
        except ValueError:
            continue

        mnemonic = parts[2].strip()
        if not mnemonic:
            continue
        ops = parts[3].strip() if len(parts) > 3 else ''

        # Strip ARM inline comment and redundant angle-bracket label
        ops = _COMMENT_RE.sub('', ops)
        ops = _LABEL_RE.sub('', ops).strip()

        # Normalise branch targets
        mn_base = mnemonic.lower().rstrip('.wn')  # strip .w / .n suffixes
        if mn_base in _BRANCH_BASES:
            ops = _HEX_ADDR_RE.sub(
                lambda mo: _norm_target(
                    int(mo.group(1), 16), fn_vaddr, fn_size, vaddr_to_name),
                ops)

        result.append(f'{mnemonic}\t{ops}' if ops else mnemonic)
    return result


def _norm_target(target: int, fn_vaddr: int, fn_size: int,
                 vaddr_to_name: Dict[int, str]) -> str:
    addr = target & ~1  # strip Thumb interworking bit
    if fn_vaddr <= addr < fn_vaddr + fn_size:
        d = addr - fn_vaddr
        return f'<+{d:#x}>'
    if addr in vaddr_to_name:
        return f'<{vaddr_to_name[addr]}>'
    d = addr - fn_vaddr
    return f'<ext{d:+#x}>'


def disasm_bytes(code: bytes, vaddr: int, fn_size: int,
                 vaddr_to_name: Dict[int, str]) -> List[str]:
    """
    Disassemble raw ARM-32 bytes at vaddr; return normalised instruction list.

    Uses direct binary disassembly with -b binary -m arm to avoid
    objcopy section flag issues. This correctly decodes ARM-32 bytes
    without wrapping them in a problematic ELF structure.
    """
    if not code:
        return []
    # Write bytes to temp file and disassemble as binary
    raw_bin = Path(tempfile.mktemp(suffix='.bin'))
    raw_bin.write_bytes(code)
    try:
        r = subprocess.run(
            [OBJDUMP, '-D', '-b', 'binary', '-m', 'arm', str(raw_bin)],
            capture_output=True, text=True, timeout=15,
        )
        lines = r.stdout.splitlines()
    finally:
        raw_bin.unlink(missing_ok=True)
    return _parse_objdump(lines, vaddr, fn_size, vaddr_to_name)


def disasm_elf(elf_path: Path) -> Dict[str, List[str]]:
    """
    Disassemble an entire linked ELF once.
    Returns {func_name: [normalised_instruction, ...]}.
    Branch normalisation uses the per-function vaddr_to_name built from the ELF
    symbol table (looked up on-the-fly per function section).
    Raw output is stored; normalisation happens per-function in check_code.
    Returns raw {func_name: (vaddr, fn_size, raw_lines)}.
    """
    # No -M force-thumb: binary is ARM-32 (A32) throughout.
    r = subprocess.run(
        [OBJDUMP, '-d', str(elf_path)],
        capture_output=True, text=True, timeout=60,
    )
    # Parse into per-function buckets: label lines "addr <name>:" start each
    funcs: Dict[str, Tuple[int, int, List[str]]] = {}
    label_re = re.compile(r'^([0-9a-f]+)\s+<([^>]+)>:')
    current_name = None
    current_vaddr = 0
    for line in r.stdout.splitlines():
        m = label_re.match(line)
        if m:
            current_vaddr = int(m.group(1), 16)
            current_name  = m.group(2)
            funcs[current_name] = (current_vaddr, [])
        elif current_name and '\t' in line:
            funcs[current_name][1].append(line)
    return funcs  # {name: (vaddr, raw_lines)}


# ── Data region ───────────────────────────────────────────────────────────────

def check_data(orig: ELF, recomp: ELF, max_show: int) -> bool:
    size  = DATA_END - CODE_END
    ob    = orig.read(CODE_END, size)
    rb    = recomp.read(CODE_END, size)
    label = f'0x{CODE_END:08x}..0x{DATA_END:08x} ({size:#x} B)'
    if ob is None:
        print(f'  {label}: SKIP (not in original)')
        return True
    if rb is None:
        print(f'  {label}: FAIL (not mapped in recompiled)')
        return False
    diffs = [(i, a, b) for i, (a, b) in enumerate(zip(ob, rb)) if a != b]
    if not diffs and len(ob) == len(rb):
        print(f'  {label}: PASS')
        return True
    extra = f', size orig={len(ob):#x} recomp={len(rb):#x}' if len(ob) != len(rb) else ''
    print(f'  {label}: FAIL  ({len(diffs)} byte diffs{extra})')
    for i, a, b in diffs[:max_show]:
        print(f'    0x{CODE_END+i:08x}: orig=0x{a:02x}  recomp=0x{b:02x}')
    if len(diffs) > max_show:
        print(f'    ... ({len(diffs)-max_show} more)')
    return False


# ── Gap analysis ──────────────────────────────────────────────────────────────

def analyze_gaps(orig: ELF, functions: List[dict], args) -> Tuple[int, int]:
    """
    Bytes in the original code region not covered by any function.

    Literal pools (.word constants after each function, referenced by
    ldr rN,[pc,#offset]) are always non-zero — that is expected.
    Alignment pads are usually zero or Thumb NOP (0xbf00).
    Anything that disassembles to valid-looking Thumb instructions is
    suspicious: Ghidra may have missed a function there.

    Returns (total_gap_bytes, nonzero_gap_bytes).
    """
    fns = sorted(
        [f for f in functions
         if f.get('status', 'ok') == 'ok'
         and CODE_START <= int(f['address'], 16) < CODE_END
         and f.get('size', 0) > 0],
        key=lambda f: int(f['address'], 16),
    )
    total_gap = 0
    nonzero_gap = 0
    prev_end = CODE_START

    def _report(start: int, end: int) -> None:
        nonlocal total_gap, nonzero_gap
        if start >= end:
            return
        sz  = end - start
        raw = orig.read(start, sz)
        if raw is None:
            return
        total_gap += sz
        nz = sum(1 for b in raw if b != 0)
        if nz == 0:
            if args.verbose:
                print(f'  GAP  0x{start:08x}  {sz:#6x} B  all-zero padding')
            return
        if sz % 2 == 0 and all(raw[i:i+2] == b'\xbf\x00' for i in range(0, sz, 2)):
            if args.verbose:
                print(f'  GAP  0x{start:08x}  {sz:#6x} B  Thumb NOP padding')
            return
        nonzero_gap += sz
        print(f'  GAP  0x{start:08x}  {sz:#6x} B  {nz}/{sz} non-zero bytes')
        if not args.show_gaps:
            return
        show = raw[:min(sz, 64)]
        for off in range(0, len(show), 16):
            row = show[off:off+16]
            print(f'    0x{start+off:08x}: {" ".join(f"{b:02x}" for b in row)}')
        if sz > 64:
            print(f'    ... ({sz-64} more bytes)')
        # Thumb disassembly hint via ELF wrap
        if sz >= 2:
            elf = _wrap_in_elf(raw, start)
            try:
                r = subprocess.run([OBJDUMP, '-d', str(elf)],
                                   capture_output=True, text=True, timeout=10)
                insn_lines = [l for l in r.stdout.splitlines() if '\t' in l and ':' in l.split('\t')[0]]
                if insn_lines:
                    print(f'    [Thumb disassembly:]')
                    for il in insn_lines[:20]:
                        print(f'      {il.strip()}')
                    if len(insn_lines) > 20:
                        print(f'      ... ({len(insn_lines)-20} more)')
            finally:
                elf.unlink(missing_ok=True)

    for fn in fns:
        vaddr = int(fn['address'], 16)
        _report(prev_end, vaddr)
        prev_end = vaddr + fn['size']
    _report(prev_end, CODE_END)
    return total_gap, nonzero_gap


# ── Code region ───────────────────────────────────────────────────────────────

def check_code(orig: ELF, recomp: ELF, recomp_path: Path,
               functions: List[dict], args) -> Tuple[int, int, int]:
    """
    Compare each function by name.

    Strategy:
    - Disassemble the entire recompiled ELF once (fast: one objdump call).
    - For each function in functions.json, wrap its original bytes in a
      temp ELF and disassemble (one objdump call per function).
    - Normalise branch targets in both using the respective vaddr→name maps.
    - Compare resulting instruction lists.

    Returns (ok, fail, miss).
    """
    orig_v2n: Dict[int, str] = {
        int(f['address'], 16): f['name']
        for f in functions if f.get('status', 'ok') == 'ok'
    }

    print('  [*] Disassembling entire recompiled ELF...', flush=True)
    recomp_raw = disasm_elf(recomp_path)   # {name: (vaddr, raw_lines)}
    recomp_v2n: Dict[int, str] = {
        vaddr: name for name, (vaddr, _) in recomp_raw.items()
    }

    code_funcs = sorted(
        [f for f in functions
         if f.get('status', 'ok') == 'ok'
         and CODE_START <= int(f['address'], 16) < CODE_END
         and f.get('size', 0) > 0],
        key=lambda f: int(f['address'], 16),
    )

    ok = fail = miss = 0

    for fn in code_funcs:
        orig_vaddr = int(fn['address'], 16)
        orig_size  = fn['size']
        name       = fn.get('name', f"FUN_{fn['address']}")

        sym = recomp.symbols.get(name)
        if sym is None or name not in recomp_raw:
            miss += 1
            if args.verbose:
                print(f'  MISS {name:{_W}} 0x{orig_vaddr:08x} ({orig_size:#x} B)'
                      f'  — not in recompiled binary')
            continue

        recomp_vaddr, recomp_sym_size = sym
        recomp_vaddr_from_asm, recomp_lines = recomp_raw[name]
        r_size = recomp_sym_size if recomp_sym_size > 0 else orig_size

        # Read original function bytes and disassemble
        ob = orig.read(orig_vaddr, orig_size)
        if ob is None:
            if args.verbose:
                print(f'  SKIP {name:{_W}} 0x{orig_vaddr:08x}  — not in original')
            continue

        oa = disasm_bytes(ob, orig_vaddr, orig_size, orig_v2n)
        ra = _parse_objdump(recomp_lines, recomp_vaddr, r_size, recomp_v2n)

        # Guard: if both produce no instructions, we can't verify equivalence
        if not oa and not ob:
            if args.verbose:
                print(f'  SKIP {name:{_W}} 0x{orig_vaddr:08x}  — no disassembly')
            continue
        if not oa or not ra:
            fail += 1
            print(f'  FAIL {name:{_W}} 0x{orig_vaddr:08x}→0x{recomp_vaddr:08x}'
                  f'  orig={len(oa)} insns  recomp={len(ra)} insns  (empty!)')
            continue

        if oa == ra:
            ok += 1
            if args.verbose:
                print(f'  OK   {name:{_W}} '
                      f'0x{orig_vaddr:08x}→0x{recomp_vaddr:08x} ({orig_size:#x} B)'
                      f'  {len(oa)} insns')
            continue

        fail += 1
        sim = difflib.SequenceMatcher(None, oa, ra).ratio()
        print(f'  FAIL {name:{_W}} '
              f'0x{orig_vaddr:08x}→0x{recomp_vaddr:08x} ({orig_size:#x} B)'
              f'  {len(oa)} vs {len(ra)} insns  sim={sim:.1%}')
        if args.show_diffs:
            diff = list(difflib.unified_diff(
                oa, ra,
                fromfile=f'orig/{name}', tofile=f'recomp/{name}',
                lineterm='',
            ))
            for line in diff[:80]:
                print(f'    {line}')
            if len(diff) > 80:
                print(f'    ... ({len(diff)-80} more lines)')

    return ok, fail, miss



# ── Entry point ───────────────────────────────────────────────────────────────

def main() -> None:
    ap = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    ap.add_argument('--orig',   default=str(DEF_ORIG),   metavar='ELF')
    ap.add_argument('--recomp', default=str(DEF_RECOMP), metavar='ELF')
    ap.add_argument('--funcs',  default=str(DEF_FUNCS),  metavar='JSON')
    ap.add_argument('--show-diffs', action='store_true',
                    help='Print unified asm diff for each failing function')
    ap.add_argument('--show-gaps', action='store_true',
                    help='Print hex + Thumb disassembly of non-zero gaps')
    ap.add_argument('--verbose', '-v', action='store_true',
                    help='Print one line per function (OK / MISS / SKIP)')
    ap.add_argument('--max-diffs', type=int, default=8, metavar='N')
    args = ap.parse_args()

    for p in (Path(args.orig), Path(args.recomp), Path(args.funcs)):
        if not p.exists():
            print(f'ERROR: {p} not found', file=sys.stderr)
            sys.exit(1)

    print(f'[*] Loading original  : {args.orig}')
    orig = ELF(Path(args.orig))
    print(f'[*] Loading recompiled: {args.recomp}')
    recomp = ELF(Path(args.recomp))
    print(f'[*] Recompiled symbols: {len(recomp.symbols)}')
    funcs = json.loads(Path(args.funcs).read_text())
    print(f'[*] functions.json    : {len(funcs)} entries')
    print()

    # ── Data region ──────────────────────────────────────────────────────────
    print('=== Data region (byte-identical) ===')
    data_ok = check_data(orig, recomp, args.max_diffs)
    print()

    # ── Gap analysis ─────────────────────────────────────────────────────────
    print('=== Gap analysis (original code region) ===')
    print('    Literal pools (.word constants) are always non-zero — expected.')
    print('    Non-zero content that disassembles cleanly may be a missed function.')
    total_gap, nonzero_gap = analyze_gaps(orig, funcs, args)
    zero_gap = total_gap - nonzero_gap
    print(f'  Total gap  : {total_gap:#x} B')
    print(f'  Zero/NOP   : {zero_gap:#x} B  — harmless padding')
    if nonzero_gap:
        print(f'  Non-zero   : {nonzero_gap:#x} B  — literal pools + possible missed functions')
        if not args.show_gaps:
            print('  (re-run with --show-gaps for hex + disassembly)')
    else:
        print('  Non-zero   : 0 B')
    print()

    # ── Code region ──────────────────────────────────────────────────────────
    print('=== Code region (per-function, matched by name) ===')
    ok, fail, miss = check_code(orig, recomp, Path(args.recomp), funcs, args)
    total = ok + fail + miss
    pct   = 100 * ok // total if total else 0
    print()

    # ── Summary ───────────────────────────────────────────────────────────────
    print('=== Summary ===')
    print(f'  Data  : {"PASS" if data_ok else "FAIL"}')
    print(f'  Funcs : {ok}/{total} OK ({pct}%)  —  {fail} fail, {miss} not in recompiled')
    print(f'  Gaps  : {total_gap:#x} B total, {nonzero_gap:#x} B non-zero')
    overall = data_ok and fail == 0
    print(f'\n  Overall: {"PASS" if overall else "FAIL"}')
    sys.exit(0 if overall else 1)


if __name__ == '__main__':
    main()
