#!/usr/bin/env python3
"""
Post-process Ghidra decompiled C output to make it compilable by arm-none-eabi-gcc.

Usage:
    cd loader/decompiled && python3 tools/preprocess_fhprg.py
    # Writes src/fhprg.c
"""
import json
import re
import sys
import time
from pathlib import Path

# Paths relative to this script
FHPRG_DIR  = Path(__file__).parent.parent
DECOMP_DIR = FHPRG_DIR / "tmp" / "decompiled"
FUNCS_JSON = FHPRG_DIR / "tmp" / "functions.json"
BINARY     = FHPRG_DIR / ".." / "fhprg_peek.bin"
OUT_C      = FHPRG_DIR / "src" / "fhprg.c"
TYPES_H    = Path("ghidra_types.h")  # relative include in output C

# ELF load address mapping for fhprg_peek.bin
# Main LOAD segment: file offset 0x3000 → vaddr 0x08006000
ELF_VADDR_BASE = 0x08006000
ELF_FILE_OFFSET = 0x3000

# Cache for binary data
_binary_data: bytes | None = None


def get_binary_data() -> bytes:
    """Load and cache binary data."""
    global _binary_data
    if _binary_data is None:
        _binary_data = BINARY.read_bytes()
    return _binary_data


def vaddr_to_file_offset(vaddr: int) -> int:
    """Convert virtual address to file offset in fhprg_peek.bin."""
    return vaddr - ELF_VADDR_BASE + ELF_FILE_OFFSET


def read_string_from_binary(vaddr: int, max_len: int = 256) -> str | None:
    """Read null-terminated string from binary at given virtual address."""
    try:
        data = get_binary_data()
        offset = vaddr_to_file_offset(vaddr)
        if offset < 0 or offset >= len(data):
            return None
        end = min(offset + max_len, len(data))
        chunk = data[offset:end]
        # Find null terminator
        null_pos = chunk.find(b'\x00')
        if null_pos >= 0:
            chunk = chunk[:null_pos]
        # Decode as latin-1 (preserves all bytes)
        return chunk.decode('latin-1')
    except (OSError, ValueError):
        return None


def escape_c_string(s: str) -> str:
    """Escape string for C string literal."""
    result = []
    for c in s:
        if c == '\\':
            result.append('\\\\')
        elif c == '"':
            result.append('\\"')
        elif c == '\n':
            result.append('\\n')
        elif c == '\r':
            result.append('\\r')
        elif c == '\t':
            result.append('\\t')
        elif ord(c) < 32 or ord(c) > 126:
            result.append(f'\\x{ord(c):02x}')
        else:
            result.append(c)
    return ''.join(result)


def collect_dat_refs(all_c: str) -> set[str]:
    """Return set of addr_hex strings for all DAT_xxx references."""
    refs = set()
    for m in re.finditer(r'DAT_([0-9a-f]{8})', all_c):
        refs.add(m.group(1))
    return refs


# Regex for Ghidra's RAM/Stack/Param variable names
_GHIDRA_MEM_VAR_RE = re.compile(
    r'\b((?:pp?|)[ucisbdq](?:Ram|Stack)(?:0x)?[0-9a-f_]+)\b'
)

# Map from Ghidra type prefix to C type
_PREFIX_TYPES = {
    'u': 'uint', 'i': 'int', 'c': 'char', 'b': 'byte',
    'p': 'uint *', 'pi': 'int *', 'pc': 'char *', 'pu': 'uint *', 'pb': 'byte *',
    'ppu': 'uint **', 'ppi': 'int **', 'ppc': 'char **', 'ppb': 'byte **',
    's': 'short', 'ui': 'uint', 'q': 'ulonglong',
}


def infer_mem_var_type(name: str) -> str:
    """Infer C type from Ghidra RAM/Stack variable name prefix."""
    for prefix in sorted(_PREFIX_TYPES.keys(), key=len, reverse=True):
        if name.startswith(prefix) and name[len(prefix):len(prefix)+3] in ('Ram', 'Sta'):
            return _PREFIX_TYPES[prefix]
    return 'uint'


def collect_mem_var_refs(all_c: str) -> set[str]:
    """Collect all Ghidra-style RAM/Stack variable names."""
    return {m.group(1) for m in _GHIDRA_MEM_VAR_RE.finditer(all_c)}


def infer_dat_type(addr_hex: str, all_c: str) -> str:
    """Heuristically guess the type of a DAT_ reference from context."""
    pattern = r'DAT_' + addr_hex
    contexts = []
    for m in re.finditer(pattern, all_c):
        start = max(0, m.start() - 60)
        end = min(len(all_c), m.end() + 60)
        contexts.append(all_c[start:end])

    ctx = " ".join(contexts)

    # Check for array subscript usage first (e.g., DAT_xxx[2])
    if re.search(rf'DAT_{addr_hex}\s*\[', ctx):
        if "(int *)" in ctx or "(int)" in ctx:
            return "int *"
        if "(uint *)" in ctx or "(uint)" in ctx:
            return "uint *"
        if "(byte *)" in ctx or "(byte)" in ctx:
            return "byte *"
        if "(char *)" in ctx or "(char)" in ctx:
            return "char *"
        return "uint *"  # Default pointer for array access

    if "(uint *)" in ctx or "(uint)" in ctx:
        return "uint"
    if "(int *)" in ctx or "(int)" in ctx:
        return "int"
    if "(byte *)" in ctx or "(byte)" in ctx:
        return "byte"
    if "(char *)" in ctx or "(char)" in ctx:
        return "char"
    if "= DAT_" in ctx or "DAT_" + addr_hex + " =" in ctx:
        return "uint"
    return "uint"


def collect_func_refs(all_c: str, known_funcs: set[str]) -> set[tuple[str, str]]:
    """Collect all FUN_xxxxxxxx and thunk_FUN_xxxxxxxx calls that need prototypes."""
    refs = set()
    for m in re.finditer(r'\b((?:thunk_)?FUN_[0-9a-f]{8})\b', all_c):
        name = m.group(1)
        if name in known_funcs:
            refs.add(name)
    return refs


def parse_func_signature(name: str, c_source: str) -> tuple[str, str]:
    """Extract (return_type, params_str) from the function definition header."""
    pat = (r'^([\w\s\*]+?)\s+' + re.escape(name) +
           r'\s*\(([^{]*?)\)\s*\n\{')
    m = re.search(pat, c_source, re.MULTILINE | re.DOTALL)
    if m:
        ret = m.group(1).strip()
        params = re.sub(r'\s+', ' ', m.group(2).strip())
        return ret, params
    return "undefined4", "void"


def sanitize_symbol(name: str) -> str:
    """Replace invalid C identifier characters in Ghidra symbol names."""
    return name.replace('>', '_gt_').replace('<', '_lt_').replace(' ', '_').replace('?', '_q_')


def collect_string_syms(all_c: str) -> set[str]:
    """Collect all string symbol names (sanitized) from decompiled source."""
    syms = set()
    for m in re.finditer(r'\b(s_[\w<>?]*_[0-9a-f]{8})\b', all_c):
        syms.add(sanitize_symbol(m.group(0)))
    return syms


def transform_source(c_source: str) -> str:
    """Apply transformations to a single function's decompiled source."""

    # 0. Sanitize symbol names with invalid characters (>, <, ?)
    def sanitize_match(m):
        return sanitize_symbol(m.group(0))
    c_source = re.sub(r'\b(s_[A-Za-z0-9_]*(?:[><\?][A-Za-z0-9_]*)*_?[0-9a-f]{8})\b',
                      sanitize_match, c_source)

    # 0b. Fix malformed function declarations like "void processEntry entry()" -> "void processEntry_entry()"
    c_source = re.sub(r'\b(processEntry)\s+(entry)\s*\(', r'\1_\2(', c_source)

    # 1. Replace unaff_* and in_* variable declarations with = 0 initialisers.
    def init_implicit_var(m):
        typ = m.group(1)
        name = m.group(2)
        return f"{typ} {name} = 0;"

    c_source = re.sub(
        r'\b((?:undefined\d*|uint|int|byte|char|longlong|ulonglong)'
        r'(?:\s*\*)?)\s+((?:unaff|in)_\w+)\s*;',
        init_implicit_var,
        c_source
    )

    # 2. Replace "in_Q" (ARM Q-flag byte) similarly
    c_source = re.sub(r'\bbyte\s+(in_\w+)\s*;', r'byte \1 = 0;', c_source)

    # 3. Change "funcname(void) {" definitions to "funcname() {" (K&R style).
    c_source = re.sub(
        r'(\w+)\s*\(\s*void\s*\)\s*\n\{',
        r'\1()\n{',
        c_source
    )

    # 4. Replace Ghidra _offset_size_ field accessors on local variables.
    _size_type = {'1': 'byte', '2': 'ushort', '4': 'uint', '8': 'ulonglong'}
    def replace_field(m):
        var   = m.group(1)
        off   = m.group(2)
        size  = m.group(3)
        typ   = _size_type.get(size, f'uint{int(size)*8}_t')
        return f'_GHIDRA_FIELD({var}, {off}, {typ})'
    c_source = re.sub(
        r'(\w+(?:\[\d+\])*)\._(\d+)_(\d+)_',
        replace_field,
        c_source
    )

    # 5. DAT_ subscript: DAT_xxx[i] → ((uint*)&DAT_xxx)[i]
    c_source = re.sub(
        r'\b(DAT_[0-9a-f]{8})\[',
        r'((uint*)&\1)[',
        c_source
    )

    # 6-7. Unary dereference fixes.
    _UNARY_KEYWORDS = {
        'return', 'sizeof', 'typeof', 'if', 'while', 'for', 'switch', 'do',
        'else', 'goto', 'case', 'void', 'uint', 'int', 'char', 'byte',
        'undefined4', 'undefined1', 'undefined', 'code',
    }

    def _is_unary_context(before_text):
        stripped = before_text.rstrip()
        if not stripped:
            return True
        last_char = stripped[-1]
        if last_char in '([{}=,;!~^|&<>+-*/':
            return True
        if last_char == ')':
            if re.search(r'\([\w][\w\s\*]*\)\s*$', stripped):
                return True
            return False
        word_m = re.search(r'\b(\w+)\s*$', stripped)
        if word_m and word_m.group(1) in _UNARY_KEYWORDS:
            return True
        return False

    def _fix_unary_deref(src, pattern, cast_type):
        def replacer(m):
            if _is_unary_context(src[:m.start()]):
                return f'*({cast_type}){m.group(1)}'
            return m.group(0)
        return re.sub(pattern, replacer, src)

    # Targeted fixes for cast-then-deref patterns
    c_source = re.sub(
        r'(\(\w+(?:\s+\w+)*\s*\*\s*\))\*(DAT_[0-9a-f]{8})\b(?!\s*\[)',
        r'\1*(uint*)\2',
        c_source
    )
    c_source = re.sub(
        r'\breturn\s+\*(DAT_[0-9a-f]{8})\b(?!\s*\[)',
        r'return *(uint*)\1',
        c_source
    )

    c_source = _fix_unary_deref(
        c_source, r'\*\s*(DAT_[0-9a-f]{8})\b(?!\s*\[)', 'uint*')
    c_source = _fix_unary_deref(
        c_source, r'\*\s*(_DAT_[0-9a-f]{8})\b(?!\s*\[)', 'uint*')
    c_source = _fix_unary_deref(
        c_source, r'\*\s*(uVar\d+)\b(?!\s*\[)', 'uint*')
    c_source = _fix_unary_deref(
        c_source, r'\*\s*(iVar\d+)\b(?!\s*\[)', 'int*')

    # 8. Fix function pointer call patterns
    c_source = re.sub(
        r'\(\*\(uint\*\)(DAT_[0-9a-f]{8})\)',
        r'((code*)\1)',
        c_source
    )
    c_source = c_source.replace('(*(code *)', '((code *)')

    # 9. LAB_xxx_1 → LAB_xxx
    c_source = re.sub(r'\bLAB_([0-9a-f]+)_\d+\b', r'LAB_\1', c_source)

    return c_source


def to_knr_definition(c_source: str, func_name: str) -> str:
    """Convert ANSI-style function definition to K&R (old-style) definition."""
    pat = (r'([\w\s\*]+?)\s+' + re.escape(func_name) +
           r'\s*\(([^{]*?)\)\s*\{')
    m = re.search(pat, c_source, re.MULTILINE | re.DOTALL)
    if not m:
        return c_source

    ret_type = m.group(1).strip()
    params_raw = m.group(2).strip()

    if not params_raw or params_raw == 'void':
        return c_source

    params = [p.strip() for p in params_raw.split(',') if p.strip()]
    param_names = []
    param_decls = []

    for p in params:
        p = re.sub(r'\s+', ' ', p).strip()
        parts = p.rsplit(' ', 1)
        if len(parts) == 2:
            ptype, pname = parts
            while pname.startswith('*'):
                ptype = ptype.rstrip() + ' *'
                pname = pname[1:]
            param_names.append(pname)
            param_decls.append(f"{ptype.strip()} {pname};")
        else:
            param_names.append(p)
            param_decls.append(f"int {p};")

    names_str = ', '.join(param_names)
    decls_str = ' '.join(param_decls)

    old = m.group(0)
    new = f"{ret_type} {func_name}({names_str})\n{decls_str}\n{{"
    return c_source.replace(old, new, 1)


def main():
    if not FUNCS_JSON.exists():
        print("Run ghidra_analyze_fhprg.py first")
        sys.exit(1)

    funcs = json.loads(FUNCS_JSON.read_text())
    func_names = {f["name"] for f in funcs}

    func_sources: dict[str, str] = {}
    for f in funcs:
        addr = f["address"]
        name = f["name"]
        safe = name.replace("/", "_").replace(" ", "_")
        path = DECOMP_DIR / f"{addr}_{safe}.c"
        if path.exists():
            func_sources[name] = path.read_text()

    all_c = "\n".join(func_sources.values())

    # Collect DAT_ references
    dat_addrs = collect_dat_refs(all_c)
    for m in re.finditer(r'_DAT_([0-9a-f]{8})', all_c):
        dat_addrs.add(m.group(1))
    print(f"[*] Found {len(dat_addrs)} unique DAT_ references")

    dat_decls = []
    for addr in sorted(dat_addrs):
        typ = infer_dat_type(addr, all_c)
        dat_decls.append(f"extern {typ} DAT_{addr};")
        dat_decls.append(f"#define _DAT_{addr} DAT_{addr}")

    # Collect RAM/Stack variables
    mem_vars = collect_mem_var_refs(all_c)
    extra_mem = set()
    for m in re.finditer(r'\b([ld]Ram[0-9a-f_]+|[ld]Stack_[0-9a-f_]+)\b', all_c):
        extra_mem.add(m.group(1))
    for m in re.finditer(r'\b(ram0x[0-9a-f]+)\b', all_c):
        extra_mem.add(m.group(1))
    mem_vars |= extra_mem

    # Find variables used as function pointers: (*varname)(args)
    func_ptr_vars = set()
    for m in re.finditer(r'\(\*\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*\)\s*\(', all_c):
        func_ptr_vars.add(m.group(1))

    mem_decls = []
    for name in sorted(mem_vars):
        if name in func_ptr_vars:
            typ = 'code *'
        else:
            typ = infer_mem_var_type(name)
        if name.startswith('l') and name[1:4] in ('Ram', 'Sta'):
            typ = 'longlong'
        elif name.startswith('d') and name[1:4] in ('Ram', 'Sta'):
            typ = 'ulonglong'
        mem_decls.append(f"extern {typ} {name};")
    print(f"[*] Found {len(mem_vars)} RAM/Stack variable references")

    # Collect misc Ghidra symbols
    t0 = time.time()
    misc_decls = []
    for m in re.finditer(r'\b(UNK_[0-9a-f]{8})\b', all_c):
        misc_decls.append(f"extern uint {m.group(1)};")
    for m in re.finditer(r'\b(SUB_[0-9a-f]{8})\b', all_c):
        misc_decls.append(f"extern uint {m.group(1)};")
    for m in re.finditer(r'\b(PTR_FUN_\w+)\b', all_c):
        misc_decls.append(f"extern code *{m.group(1)};")
    for m in re.finditer(r'\b(PTR_DAT_[0-9a-f]{8})\b', all_c):
        misc_decls.append(f"extern uint *{m.group(1)};")
    for m in re.finditer(r'\b(PTR_entry_[0-9a-f]{8})\b', all_c):
        misc_decls.append(f"extern code *{m.group(1)};")
    for m in re.finditer(r'\b(PTR_s_\w+)\b', all_c):
        misc_decls.append(f"extern const char *{m.group(1)};")
    for m in re.finditer(r'\b(PTR_LAB_[0-9a-f]{8}(?:_[0-9]+_[0-9a-f]+)?)\b', all_c):
        misc_decls.append(f"extern uint *{m.group(1)};")
    for m in re.finditer(r'\b(register0x[0-9a-f]+)\b', all_c):
        misc_decls.append(f"extern uint {m.group(1)};")
    for m in re.finditer(r'\b(stack0x[0-9a-f]+)\b', all_c):
        misc_decls.append(f"extern undefined4 {m.group(1)};")
    for m in re.finditer(r'\b(_[0-9a-f]{8})\b', all_c):
        misc_decls.append(f"extern uint {m.group(1)};")
    # _local_xx variables
    for m in re.finditer(r'\b(_local_[0-9a-f]+)\b', all_c):
        misc_decls.append(f"extern uint {m.group(1)};")
    print(f"[*] Collected misc symbols in {time.time()-t0:.2f}s")

    # Collect string symbols
    t0 = time.time()
    all_string_syms = sorted(collect_string_syms(all_c))
    string_externs = [f"extern const char {sym}[];" for sym in all_string_syms]
    print(f"[*] Found {len(all_string_syms)} string symbols in {time.time()-t0:.2f}s")

    seen_misc = set()
    unique_misc = []
    for d in misc_decls:
        if d not in seen_misc:
            seen_misc.add(d)
            unique_misc.append(d)
    misc_decls = unique_misc
    if misc_decls:
        print(f"[*] Declaring {len(misc_decls)} misc Ghidra symbols")

    # Find void functions to upgrade
    void_funcs = set()
    for name, src in func_sources.items():
        ret, _ = parse_func_signature(name, src)
        if ret.strip() == "void":
            void_funcs.add(name)

    upgrade_to_u4 = set()
    simple_patterns = [
        r'= ((?:thunk_)?FUN_[0-9a-f]{8})\s*\(',
        r'return ((?:thunk_)?FUN_[0-9a-f]{8})\s*\(',
        r',\s*((?:thunk_)?FUN_[0-9a-f]{8})\s*\(',
        r'\)\s*((?:thunk_)?FUN_[0-9a-f]{8})\s*\(',
    ]
    for pat in simple_patterns:
        for m in re.finditer(pat, all_c):
            fname = m.group(1)
            if fname in void_funcs:
                upgrade_to_u4.add(fname)
    print(f"[*] Upgrading {len(upgrade_to_u4)} void→undefined4 return types")

    proto_decls = []
    for name, src in func_sources.items():
        ret, _ = parse_func_signature(name, src)
        if name in upgrade_to_u4:
            ret = "undefined4"
        proto_decls.append(f"{ret} {name}();")

    # Collect LAB_ references
    lab_addr_refs = set()
    for m in re.finditer(r'&(LAB_[0-9a-f]+)(?:_\d+)?\b', all_c):
        lab_addr_refs.add(m.group(1))
    lab_decls = [f"extern uint {lab};" for lab in sorted(lab_addr_refs)]
    if lab_decls:
        print(f"[*] Declaring {len(lab_decls)} LAB_ address references")

    # Transform functions
    transformed = []
    for name, src in func_sources.items():
        src = transform_source(src)
        if name in upgrade_to_u4:
            src = re.sub(
                r'^void\s+(' + re.escape(name) + r')\s*\(',
                r'undefined4 \1(',
                src,
                count=1,
                flags=re.MULTILINE
            )
            src = src.replace("  return;\n", "  return 0;\n")
        src = to_knr_definition(src, name)
        transformed.append(src)

    # Assemble output
    lines = [
        "/* Auto-generated: fhprg_peek decompiled + preprocessed for arm-none-eabi-gcc */",
        f'#include "{TYPES_H}"',
        "",
        "/* ===== String literals (extern, defined in strings.c) ===== */",
    ] + string_externs + [
        "",
        "/* ===== DAT_ globals ===== */",
    ] + dat_decls + [
        "",
        "/* ===== RAM/Stack variables ===== */",
    ] + mem_decls + [
        "",
        "/* ===== Misc symbols ===== */",
    ] + misc_decls + [
        "",
        "/* ===== LAB_ references ===== */",
    ] + lab_decls + [
        "",
        "/* ===== Forward declarations ===== */",
    ] + proto_decls + [
        "",
        "/* ===== Function bodies ===== */",
    ] + transformed

    OUT_C.parent.mkdir(parents=True, exist_ok=True)
    OUT_C.write_text("\n".join(lines))
    print(f"[*] Written {OUT_C} ({OUT_C.stat().st_size:,} bytes)")
    print(f"    {len(transformed)} functions")


if __name__ == "__main__":
    main()
