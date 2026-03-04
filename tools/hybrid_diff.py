#!/usr/bin/env python3
"""hybrid_diff.py — Hybrid binary diff for decompilation verification

Compares a recompiled ELF against the original binary, per-function.
Supports both ARM-32 (aboot) and Thumb2 (fhprg) binaries.

Comparison rules
----------------
  code region:
    each function compared BY NAME: look up in recompiled ELF symbol
    table, disassemble, normalise branch targets, compare.

  data region (if present): byte-identical check.

  gaps between functions: literal pool / padding analysis.

Function list formats:
  - JSON (functions.json): [{"address": "8f600000", "name": "FUN_...", "size": N}, ...]
  - Syms text (fhprg_syms.txt): "ADDR T NAME" per line (sizes inferred from gaps)

Exit 0 if all functions pass, 1 otherwise.

Usage
-----
    # aboot (ARM-32, explicit addresses):
    python3 tools/hybrid_diff.py --orig aboot.bin --recomp aboot_linked.elf \\
        --funcs tmp/functions.json

    # fhprg (Thumb2, auto-detect):
    python3 tools/hybrid_diff.py --orig fhprg_peek.bin --recomp tmp/fhprg_linked.elf \\
        --funcs tmp/fhprg_syms.txt --thumb
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
PROJ_DIR   = Path(__file__).parent.parent
DEF_ORIG   = PROJ_DIR / "aboot.bin"
DEF_RECOMP = PROJ_DIR / "aboot_linked.elf"
DEF_FUNCS  = PROJ_DIR / "tmp" / "functions.json"

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
_COMMENT_RE  = re.compile(r'\s*[@;].*$')
_LABEL_RE    = re.compile(r'\s*<[^>]*>')
_HEX_ADDR_RE = re.compile(r'\b([0-9a-f]{6,8})\b')

SHT_SYMTAB = 2
STT_FUNC   = 2
STT_NOTYPE = 0

_W = 44  # column width for function names in output


# ── ELF reader ────────────────────────────────────────────────────────────────

class ELF:
    """Minimal 32-bit LE ELF: vaddr->bytes + symbol table."""

    def __init__(self, path: Path) -> None:
        self.path = path
        self.data = path.read_bytes()
        if self.data[:4] != b'\x7fELF':
            raise ValueError(f"{path}: not an ELF file")
        self.segs: List[dict] = self._load_phdrs()
        self.symbols: Dict[str, Tuple[int, int]] = {}  # name -> (vaddr, size)
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
            pt, poff, pva, _, pfsz, pmsz, pflags, _ = struct.unpack_from('<8I', d, o)
            if pt == 1:
                segs.append(dict(p_offset=poff, p_vaddr=pva,
                                 p_filesz=pfsz, p_memsz=pmsz, p_flags=pflags))
        return segs

    def _load_symtab(self) -> None:
        d = self.data
        shoff = struct.unpack_from('<I', d, 0x20)[0]
        shesz = struct.unpack_from('<H', d, 0x2E)[0]
        shnum = struct.unpack_from('<H', d, 0x30)[0]
        shstr = struct.unpack_from('<H', d, 0x32)[0]
        if shoff == 0 or shnum == 0:
            return
        sno = shoff + shstr * shesz
        strtab_raw = d[struct.unpack_from('<I', d, sno+0x10)[0] :
                       struct.unpack_from('<I', d, sno+0x10)[0] +
                       struct.unpack_from('<I', d, sno+0x14)[0]]
        for i in range(shnum):
            o = shoff + i * shesz
            if struct.unpack_from('<I', d, o+0x04)[0] != SHT_SYMTAB:
                continue
            sym_off  = struct.unpack_from('<I', d, o+0x10)[0]
            sym_sz   = struct.unpack_from('<I', d, o+0x14)[0]
            sym_link = struct.unpack_from('<I', d, o+0x18)[0]
            sym_ent  = struct.unpack_from('<I', d, o+0x24)[0] or 16
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
                # For Thumb, strip bit 0 for lookup
                lookup_addr = st_value & ~1
                if lookup_addr not in self.vaddr_to_name:
                    self.vaddr_to_name[lookup_addr] = name
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

    def code_segments(self) -> List[dict]:
        """Return LOAD segments with execute flag (PF_X=1)."""
        return [s for s in self.segs if s['p_flags'] & 1]

    def data_segments(self) -> List[dict]:
        """Return LOAD segments without execute flag."""
        return [s for s in self.segs if not (s['p_flags'] & 1) and s['p_filesz'] > 0]


# ── Function list loading ─────────────────────────────────────────────────────

def load_functions(path: Path) -> List[dict]:
    """Load function list from JSON or syms.txt format."""
    text = path.read_text().strip()
    if text.startswith('['):
        # JSON format
        return json.loads(text)

    # Syms text format: "ADDR T NAME" per line
    funcs = []
    for line in text.splitlines():
        parts = line.strip().split()
        if len(parts) >= 3:
            addr = int(parts[0], 16)
            name = parts[2]
            funcs.append({'address': f'{addr:08x}', 'name': name, 'size': 0})

    # Infer sizes from gaps between consecutive functions in same address range
    funcs.sort(key=lambda f: int(f['address'], 16))
    for i in range(len(funcs) - 1):
        addr_i = int(funcs[i]['address'], 16)
        addr_next = int(funcs[i+1]['address'], 16)
        # Only infer size if same address range (both 0x08xxx or both 0x002xxx)
        if (addr_i >> 20) == (addr_next >> 20):
            funcs[i]['size'] = addr_next - addr_i
        else:
            funcs[i]['size'] = 64  # placeholder for last func in a range
    if funcs:
        funcs[-1]['size'] = 64  # placeholder

    return funcs


# ── Disassembly ───────────────────────────────────────────────────────────────

def _parse_objdump(lines: List[str], fn_vaddr: int,
                   fn_size: int, vaddr_to_name: Dict[int, str]) -> List[str]:
    """Parse objdump output, normalise branch targets."""
    result = []
    for line in lines:
        parts = line.split('\t')
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
        ops = _COMMENT_RE.sub('', ops)
        ops = _LABEL_RE.sub('', ops).strip()

        # Normalise branch targets
        mn_base = mnemonic.lower().rstrip('.wn')
        if mn_base in _BRANCH_BASES:
            ops = _HEX_ADDR_RE.sub(
                lambda mo: _norm_target(
                    int(mo.group(1), 16), fn_vaddr, fn_size, vaddr_to_name),
                ops)

        result.append(f'{mnemonic}\t{ops}' if ops else mnemonic)
    return result


def _norm_target(target: int, fn_vaddr: int, fn_size: int,
                 vaddr_to_name: Dict[int, str]) -> str:
    addr = target & ~1
    if fn_vaddr <= addr < fn_vaddr + fn_size:
        d = addr - fn_vaddr
        return f'<+{d:#x}>'
    if addr in vaddr_to_name:
        return f'<{vaddr_to_name[addr]}>'
    d = addr - fn_vaddr
    return f'<ext{d:+#x}>'


def disasm_bytes(code: bytes, vaddr: int, fn_size: int,
                 vaddr_to_name: Dict[int, str], thumb: bool = False) -> List[str]:
    """Disassemble raw bytes at vaddr; return normalised instruction list.

    Creates a temp ELF at the correct VMA so objdump computes correct
    absolute branch targets.
    """
    if not code:
        return []
    raw_bin = Path(tempfile.mktemp(suffix='.bin'))
    raw_o   = Path(tempfile.mktemp(suffix='.o'))
    out_elf = Path(tempfile.mktemp(suffix='.elf'))
    ld_scr  = Path(tempfile.mktemp(suffix='.ld'))

    raw_bin.write_bytes(code)
    try:
        # Create ELF at correct VMA for proper branch target computation
        subprocess.run([OBJCOPY, '-I', 'binary', '-O', 'elf32-littlearm', '-B', 'arm',
                        str(raw_bin), str(raw_o)],
                       check=True, capture_output=True)
        subprocess.run([OBJCOPY, '--rename-section', '.data=.text',
                        str(raw_o), str(raw_o)],
                       check=True, capture_output=True)
        ld_scr.write_text(f'SECTIONS {{ . = 0x{vaddr:x}; .text : ALIGN(1) {{ *(.text) }} }}')
        subprocess.run([LD, '-T', str(ld_scr), '-o', str(out_elf), str(raw_o)],
                       capture_output=True)
        subprocess.run([OBJCOPY, '--set-section-flags', '.text=alloc,readonly,code',
                        str(out_elf), str(out_elf)],
                       capture_output=True)

        # Use -D (all sections) because -d ignores -M force-thumb on ELF files
        # without $t mapping symbols. Filter to .text section lines only.
        cmd = [OBJDUMP, '-D', '-j', '.text']
        if thumb:
            cmd.extend(['-M', 'force-thumb'])
        cmd.append(str(out_elf))
        r = subprocess.run(cmd, capture_output=True, text=True, timeout=15)
        lines = r.stdout.splitlines()
    finally:
        for p in (raw_bin, raw_o, out_elf, ld_scr):
            p.unlink(missing_ok=True)

    return _parse_objdump(lines, vaddr, fn_size, vaddr_to_name)


def disasm_elf(elf_path: Path, thumb: bool = False) -> dict:
    """Disassemble entire linked ELF. Returns {name: (vaddr, raw_lines)}."""
    # Use -D for Thumb binaries lacking $t mapping symbols
    cmd = [OBJDUMP, '-D' if thumb else '-d']
    if thumb:
        cmd.extend(['-M', 'force-thumb'])
    cmd.append(str(elf_path))
    r = subprocess.run(cmd, capture_output=True, text=True, timeout=120)

    funcs = {}
    label_re = re.compile(r'^([0-9a-f]+)\s+<([^>]+)>:')
    section_re = re.compile(r'^Disassembly of section ([^:]+):')
    current_name = None
    in_text = False
    for line in r.stdout.splitlines():
        sm = section_re.match(line)
        if sm:
            sec = sm.group(1)
            in_text = sec.startswith('.text')
            current_name = None
            continue
        if not in_text:
            continue
        m = label_re.match(line)
        if m:
            current_vaddr = int(m.group(1), 16)
            current_name = m.group(2)
            funcs[current_name] = (current_vaddr, [])
        elif current_name and '\t' in line:
            funcs[current_name][1].append(line)
    return funcs


# ── Data region ───────────────────────────────────────────────────────────────

def check_data(orig: ELF, recomp: ELF, code_end: int, data_end: int,
               max_show: int) -> bool:
    if data_end <= code_end:
        print('  (no data region to check)')
        return True
    size = data_end - code_end
    ob = orig.read(code_end, size)
    rb = recomp.read(code_end, size)
    label = f'0x{code_end:08x}..0x{data_end:08x} ({size:#x} B)'
    if ob is None:
        print(f'  {label}: SKIP (not in original)')
        return True
    if rb is None:
        print(f'  {label}: SKIP (not mapped in recompiled)')
        return True
    diffs = [(i, a, b) for i, (a, b) in enumerate(zip(ob, rb)) if a != b]
    if not diffs and len(ob) == len(rb):
        print(f'  {label}: PASS')
        return True
    extra = f', size orig={len(ob):#x} recomp={len(rb):#x}' if len(ob) != len(rb) else ''
    print(f'  {label}: FAIL  ({len(diffs)} byte diffs{extra})')
    for i, a, b in diffs[:max_show]:
        print(f'    0x{code_end+i:08x}: orig=0x{a:02x}  recomp=0x{b:02x}')
    if len(diffs) > max_show:
        print(f'    ... ({len(diffs)-max_show} more)')
    return False


# ── Gap analysis ──────────────────────────────────────────────────────────────

def analyze_gaps(orig: ELF, functions: List[dict],
                 code_start: int, code_end: int, args) -> Tuple[int, int]:
    fns = sorted(
        [f for f in functions
         if code_start <= int(f['address'], 16) < code_end
         and f.get('size', 0) > 0],
        key=lambda f: int(f['address'], 16),
    )
    total_gap = 0
    nonzero_gap = 0
    prev_end = code_start

    def _report(start: int, end: int) -> None:
        nonlocal total_gap, nonzero_gap
        if start >= end:
            return
        sz = end - start
        raw = orig.read(start, sz)
        if raw is None:
            return
        total_gap += sz
        nz = sum(1 for b in raw if b != 0)
        if nz == 0:
            return
        if sz % 2 == 0 and all(raw[i:i+2] == b'\x00\xbf' for i in range(0, sz, 2)):
            return
        nonzero_gap += sz
        if args.show_gaps:
            print(f'  GAP  0x{start:08x}  {sz:#6x} B  {nz}/{sz} non-zero bytes')

    for fn in fns:
        vaddr = int(fn['address'], 16)
        _report(prev_end, vaddr)
        prev_end = vaddr + fn['size']
    _report(prev_end, code_end)
    return total_gap, nonzero_gap


# ── Semantic normalization ────────────────────────────────────────────────────

_WIDTH_SUFFIX_RE = re.compile(r'\.[nw]$')

def _norm_mnemonic(insn: str) -> str:
    """Level 1: normalize mnemonic encoding variants."""
    parts = insn.split('\t', 1)
    mnem = parts[0]
    ops = parts[1] if len(parts) > 1 else ''

    # Strip .n/.w width suffix
    mnem = _WIDTH_SUFFIX_RE.sub('', mnem)

    # NOP variants: movs r0, r0 → nop
    if mnem == 'movs' and ops.strip() == 'r0, r0':
        return 'nop\t'

    # push/stmdb, pop/ldmia equivalence
    if mnem == 'stmdb' and ops.startswith('sp!'):
        regs = ops.split('{', 1)[1].rstrip('}').strip() if '{' in ops else ops
        return f'push\t{{{regs}}}'
    if mnem in ('ldmia', 'ldmia.w') and ops.startswith('sp!'):
        regs = ops.split('{', 1)[1].rstrip('}').strip() if '{' in ops else ops
        return f'pop\t{{{regs}}}'

    # 3-op → 2-op folding: adds rX, rX, #imm → adds rX, #imm
    if mnem in ('adds', 'add', 'subs', 'sub', 'orrs', 'orr', 'ands', 'and',
                'eors', 'eor', 'lsls', 'lsl', 'lsrs', 'lsr', 'asrs', 'asr',
                'bics', 'bic', 'rors', 'ror'):
        ps = [x.strip() for x in ops.split(',')]
        if len(ps) == 3 and ps[0] == ps[1]:
            ops = f'{ps[0]}, {ps[2]}'

    # Flag-setting normalization: movs→mov, adds→add etc.
    _NO_FLAG = {'mov', 'add', 'sub', 'orr', 'and', 'eor', 'lsl', 'lsr',
                'asr', 'bic', 'mvn', 'ror', 'mul', 'adc', 'sbc', 'rsb'}
    if mnem.endswith('s') and mnem[:-1] in _NO_FLAG:
        mnem = mnem[:-1]

    return f'{mnem}\t{ops}' if ops else mnem


def _norm_regs(insn: str) -> str:
    """Level 2: normalize general-purpose register names to positional tokens.

    Leaves sp, lr, pc untouched.  Maps rN/fp/ip/sl to RNN for uniform comparison.
    NOTE: this is applied per-instruction, NOT per-function, so register identity
    across instructions is intentionally NOT preserved — we only care whether the
    *shape* of each instruction is the same.
    """
    parts = insn.split('\t', 1)
    mnem = parts[0]
    ops = parts[1] if len(parts) > 1 else ''
    ops = re.sub(r'\bfp\b', 'r11', ops)
    ops = re.sub(r'\bip\b', 'r12', ops)
    ops = re.sub(r'\bsl\b', 'r10', ops)
    # Replace rN with generic token preserving position order
    seen = {}
    counter = [0]
    def _map(m):
        r = m.group(0)
        if r not in seen:
            seen[r] = f'R{counter[0]}'
            counter[0] += 1
        return seen[r]
    ops = re.sub(r'\br\d+\b', _map, ops)
    return f'{mnem}\t{ops}' if ops else mnem


def _norm_litpool(insn: str) -> str:
    """Level 3: normalize literal pool offsets — ldr rX, [pc, #Y] → ldr rX, [pc, #LIT]."""
    parts = insn.split('\t', 1)
    mnem = parts[0]
    ops = parts[1] if len(parts) > 1 else ''
    if mnem == 'ldr' and '[pc,' in ops:
        reg = ops.split(',')[0].strip()
        return f'{mnem}\t{reg}, [pc, #LIT]'
    return insn


def _norm_branch_target(insn: str) -> str:
    """Level 4: normalize branch targets."""
    parts = insn.split('\t', 1)
    mnem = parts[0]
    ops = parts[1] if len(parts) > 1 else ''
    mn_base = mnem.lower().rstrip('.wn')
    if mn_base in _BRANCH_BASES:
        ops = re.sub(r'<[^>]+>', '<TGT>', ops)
    return f'{mnem}\t{ops}' if ops else mnem


def _strip_trailing_litpool(insns: List[str]) -> List[str]:
    """Level 5: strip decoded literal pool data after the last return/branch.

    Thumb2 functions have literal pools placed right after the code body.
    The disassembler decodes these as garbage instructions (movs r0, r0,
    bcs.n, lsrs, adds, etc.).  Find the last real return instruction
    (bx lr, pop {..., pc}, b/b.w unconditional) and strip everything after it.
    """
    # Find last instruction that is a function return or tail call
    last_real = len(insns) - 1
    for i in range(len(insns) - 1, -1, -1):
        parts = insns[i].split('\t', 1)
        mnem = parts[0].strip().rstrip('.nw')
        ops = parts[1].strip() if len(parts) > 1 else ''
        # bx lr = return
        if mnem == 'bx' and ops == 'lr':
            last_real = i
            break
        # pop {..., pc} = return
        if mnem in ('pop', 'ldmia') and 'pc' in ops:
            last_real = i
            break
        # unconditional b/b.w = tail call (but not conditional branches)
        if mnem == 'b' and '<' in ops:
            last_real = i
            break
    return insns[:last_real + 1]


def normalize_at_level(insns: List[str], level: int) -> List[str]:
    """Apply cumulative normalization up to `level`.

    Level 0: raw (no extra normalization — already has branch target normalization)
    Level 1: mnemonic normalization (push/stmdb, movs/mov, 3op→2op, flag variants)
    Level 2: + register normalization (per-instruction positional)
    Level 3: + literal pool offset normalization
    Level 4: + branch target normalization (all targets → <TGT>)
    Level 5: + strip trailing literal pool data
    """
    result = insns
    if level >= 1:
        result = [_norm_mnemonic(i) for i in result]
    if level >= 2:
        result = [_norm_regs(i) for i in result]
    if level >= 3:
        result = [_norm_litpool(i) for i in result]
    if level >= 4:
        result = [_norm_branch_target(i) for i in result]
    if level >= 5:
        result = _strip_trailing_litpool(result)
    return result


# ── Code region ───────────────────────────────────────────────────────────────

def check_code(orig: ELF, recomp: ELF, recomp_path: Path,
               functions: List[dict], code_start: int, code_end: int,
               thumb: bool, args) -> Tuple[int, int, int, int]:
    """
    Compare each function by name.
    Returns (ok, fail, miss, byte_identical).
    """
    orig_v2n: Dict[int, str] = {
        int(f['address'], 16): f['name']
        for f in functions
    }

    print('  [*] Disassembling entire recompiled ELF...', flush=True)
    recomp_raw = disasm_elf(recomp_path, thumb=thumb)
    recomp_v2n: Dict[int, str] = {
        vaddr & ~1: name for name, (vaddr, _) in recomp_raw.items()
    }

    code_funcs = sorted(
        [f for f in functions
         if code_start <= int(f['address'], 16) < code_end
         and f.get('size', 0) > 0],
        key=lambda f: int(f['address'], 16),
    )

    ok = fail = miss = byte_identical = 0

    # Normalization tracking (if --normalize)
    NORM_LEVELS = 6  # levels 0..5
    norm_ok = [0] * NORM_LEVELS  # exact match at each level
    norm_90 = [0] * NORM_LEVELS  # >=90% similarity at each level
    norm_80 = [0] * NORM_LEVELS  # >=80% similarity at each level

    for fn in code_funcs:
        orig_vaddr = int(fn['address'], 16)
        orig_size  = fn['size']
        name       = fn['name']

        # Try exact name, then with $t suffix stripped
        sym = recomp.symbols.get(name)
        found_in_asm = name in recomp_raw
        if sym is None or not found_in_asm:
            miss += 1
            if args.verbose:
                print(f'  MISS {name:{_W}} 0x{orig_vaddr:08x} ({orig_size:#x} B)')
            continue

        recomp_vaddr_raw, recomp_sym_size = sym
        recomp_vaddr = recomp_vaddr_raw & ~1  # strip Thumb bit
        recomp_vaddr_from_asm, recomp_lines = recomp_raw[name]
        r_size = recomp_sym_size if recomp_sym_size > 0 else orig_size

        # Read original function bytes
        ob = orig.read(orig_vaddr, orig_size)
        if ob is None:
            continue

        # Byte-identical check first
        rb = recomp.read(recomp_vaddr, orig_size)
        if rb is not None and ob == rb:
            byte_identical += 1
            ok += 1
            if getattr(args, 'normalize', False):
                for lvl in range(NORM_LEVELS):
                    norm_ok[lvl] += 1
                    norm_90[lvl] += 1
                    norm_80[lvl] += 1
            if args.verbose:
                print(f'  BYTE {name:{_W}} '
                      f'0x{orig_vaddr:08x} ({orig_size:#x} B) byte-identical')
            continue

        # Disassemble and compare
        oa = disasm_bytes(ob, orig_vaddr, orig_size, orig_v2n, thumb=thumb)
        ra = _parse_objdump(recomp_lines, recomp_vaddr, r_size, recomp_v2n)

        if not oa or not ra:
            fail += 1
            print(f'  FAIL {name:{_W}} 0x{orig_vaddr:08x} '
                  f'orig={len(oa)} insns  recomp={len(ra)} insns  (empty!)')
            continue

        if oa == ra:
            ok += 1
            if getattr(args, 'normalize', False):
                for lvl in range(NORM_LEVELS):
                    norm_ok[lvl] += 1
                    norm_90[lvl] += 1
                    norm_80[lvl] += 1
            if args.verbose:
                print(f'  OK   {name:{_W}} '
                      f'0x{orig_vaddr:08x} ({orig_size:#x} B) {len(oa)} insns')
            continue

        # Check normalized equivalence at each level
        if getattr(args, 'normalize', False):
            for lvl in range(NORM_LEVELS):
                oa_n = normalize_at_level(oa, lvl)
                ra_n = normalize_at_level(ra, lvl)
                if oa_n == ra_n:
                    norm_ok[lvl] += 1
                    norm_90[lvl] += 1
                    norm_80[lvl] += 1
                else:
                    s = difflib.SequenceMatcher(None, oa_n, ra_n).ratio()
                    if s >= 0.90:
                        norm_90[lvl] += 1
                        norm_80[lvl] += 1
                    elif s >= 0.80:
                        norm_80[lvl] += 1

        fail += 1
        sim = difflib.SequenceMatcher(None, oa, ra).ratio()
        print(f'  FAIL {name:{_W}} '
              f'0x{orig_vaddr:08x} ({orig_size:#x} B)'
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

    # Print normalization report
    if getattr(args, 'normalize', False):
        total_compared = ok + fail
        level_names = [
            'Level 0: raw',
            'Level 1: + mnemonic norm (push/stm, mov/movs, 3op→2op)',
            'Level 2: + register normalization',
            'Level 3: + literal pool normalization',
            'Level 4: + branch target normalization',
            'Level 5: + strip trailing literal pool data',
        ]
        print()
        print('=== Normalization analysis ===')
        print(f'  {"Level":{55}} {"=100%":>10s} {">=90%":>10s} {">=80%":>10s}')
        for lvl in range(NORM_LEVELS):
            cnt = norm_ok[lvl]
            c90 = norm_90[lvl]
            c80 = norm_80[lvl]
            print(f'  {level_names[lvl]:55s} {cnt:5d}      {c90:5d}      {c80:5d}')

    return ok, fail, miss, byte_identical


# ── Entry point ───────────────────────────────────────────────────────────────

def main() -> None:
    ap = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    ap.add_argument('--orig',   default=str(DEF_ORIG),   metavar='ELF')
    ap.add_argument('--recomp', default=str(DEF_RECOMP), metavar='ELF')
    ap.add_argument('--funcs',  default=str(DEF_FUNCS),  metavar='FILE',
                    help='Function list (JSON or syms.txt)')
    ap.add_argument('--thumb', action='store_true',
                    help='Disassemble as Thumb2 (default: auto-detect from funcs path)')
    ap.add_argument('--code-start', type=lambda x: int(x, 0), default=None)
    ap.add_argument('--code-end',   type=lambda x: int(x, 0), default=None)
    ap.add_argument('--data-end',   type=lambda x: int(x, 0), default=None)
    ap.add_argument('--show-diffs', action='store_true')
    ap.add_argument('--show-gaps', action='store_true')
    ap.add_argument('--normalize', action='store_true',
                    help='Apply semantic normalizations and report at multiple levels')
    ap.add_argument('--verbose', '-v', action='store_true')
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

    funcs = load_functions(Path(args.funcs))
    print(f'[*] Functions         : {len(funcs)} entries')

    # Auto-detect Thumb mode from funcs file name
    thumb = args.thumb or 'fhprg' in args.funcs

    # Auto-detect code/data ranges from original ELF segments
    code_segs = orig.code_segments()
    data_segs = orig.data_segments()

    if args.code_start is not None:
        code_start = args.code_start
    elif code_segs:
        # Use the largest code segment
        main_seg = max(code_segs, key=lambda s: s['p_filesz'])
        code_start = main_seg['p_vaddr']
    else:
        code_start = 0x8F600000

    if args.code_end is not None:
        code_end = args.code_end
    elif code_segs:
        main_seg = max(code_segs, key=lambda s: s['p_filesz'])
        code_end = main_seg['p_vaddr'] + main_seg['p_filesz']
    else:
        code_end = 0x8F652E80

    if args.data_end is not None:
        data_end = args.data_end
    elif data_segs:
        last_data = max(data_segs, key=lambda s: s['p_vaddr'] + s['p_filesz'])
        data_end = last_data['p_vaddr'] + last_data['p_filesz']
    else:
        data_end = code_end

    print(f'[*] Code range        : 0x{code_start:08x}..0x{code_end:08x} ({code_end-code_start:#x} B)')
    print(f'[*] Data end          : 0x{data_end:08x}')
    print(f'[*] Mode              : {"Thumb2" if thumb else "ARM-32"}')
    print()

    # ── Data region ──────────────────────────────────────────────────────────
    print('=== Data region (byte-identical) ===')
    data_ok = check_data(orig, recomp, code_end, data_end, args.max_diffs)
    print()

    # ── Gap analysis ─────────────────────────────────────────────────────────
    print('=== Gap analysis (original code region) ===')
    total_gap, nonzero_gap = analyze_gaps(orig, funcs, code_start, code_end, args)
    zero_gap = total_gap - nonzero_gap
    print(f'  Total gap  : {total_gap:#x} B')
    print(f'  Non-zero   : {nonzero_gap:#x} B  (literal pools expected)')
    print()

    # ── Code region ──────────────────────────────────────────────────────────
    print('=== Code region (per-function, matched by name) ===')
    ok, fail, miss, byte_id = check_code(
        orig, recomp, Path(args.recomp), funcs,
        code_start, code_end, thumb, args)
    total = ok + fail + miss
    pct = 100 * ok / total if total else 0
    print()

    # ── Summary ───────────────────────────────────────────────────────────────
    print('=== Summary ===')
    print(f'  Data       : {"PASS" if data_ok else "FAIL" if data_end > code_end else "N/A"}')
    print(f'  Functions  : {ok}/{total} OK ({pct:.1f}%)  —  {fail} fail, {miss} missing')
    print(f'  Byte-ident : {byte_id}')
    print(f'  Gaps       : {total_gap:#x} B total, {nonzero_gap:#x} B non-zero')
    overall = fail == 0
    print(f'\n  Overall: {"PASS" if overall else "FAIL"}')
    sys.exit(0 if overall else 1)


if __name__ == '__main__':
    main()
