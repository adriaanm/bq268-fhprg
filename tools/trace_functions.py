#!/usr/bin/env python3
"""
Trace which functions are called during firehose operations.

Uses Unicorn to emulate the original binary with MINIMAL stubbing — only
hardware I/O boundaries (USB, MMIO, SDCC registers) are faked. Everything
else runs natively so we see the real call graph light up.

Then computes the static call closure and estimates LoC for a minimal programmer.

Usage:
    python3 tools/trace_functions.py [--verbose]
"""

import os
import re
import struct
import sys
from collections import defaultdict
from pathlib import Path

from unicorn import *
from unicorn.arm_const import *
from elftools.elf.elffile import ELFFile

# ---------------------------------------------------------------------------
# Load function map from syms file
# ---------------------------------------------------------------------------

def load_syms(path="tmp/fhprg_syms.txt"):
    """Load function addresses and names. Returns sorted list of (addr, name)."""
    funcs = []
    for line in Path(path).read_text().splitlines():
        parts = line.strip().split()
        if len(parts) >= 3:
            addr = int(parts[0], 16)
            name = parts[2]
            funcs.append((addr, name))
    return sorted(funcs, key=lambda x: x[0])


# ---------------------------------------------------------------------------
# Emulator with function tracing — minimal stubs
# ---------------------------------------------------------------------------

class TracingEmulator:
    """Emulator that records function entries. Only stubs true I/O."""

    # Key data addresses
    ADDR_XML_PARSER      = 0x08055ea0
    ADDR_XML_WRITER      = 0x08055f18
    ADDR_STORAGE_DEV     = 0x08058430
    ADDR_SECTOR_SZ       = 0x08058458
    ADDR_SECTOR_SZ_HI    = 0x0805845c
    ADDR_SKIP_WRITE      = 0x08058480
    ADDR_ACK_RAW         = 0x08058481
    ADDR_VERBOSE         = 0x08058482
    ADDR_ACK_EVERY       = 0x08058484
    ADDR_VALIDATION      = 0x08055fd8
    ADDR_MAX_SECT_LO     = 0x08055fb8
    ADDR_MAX_SECT_HI     = 0x08055fbc
    ADDR_STACK_CANARY    = 0x0804cd58
    ADDR_CONTEXT         = 0x08055e90
    ADDR_USB_DMA_BASE    = 0x08054e90
    ADDR_USB_RX_BUF      = 0x08055e98

    FN_DISPATCHER        = 0x0802f130

    FAKE_XML_BUF         = 0x80100400
    FAKE_CARD_INFO       = 0x80100000
    FAKE_EXT_CSD         = 0x80100100
    FAKE_DEV_HANDLE      = 0x80100200
    FAKE_SECTOR_DATA     = 0x80300000
    FAKE_XML_WR_BUF      = 0x80500000
    STACK_BASE           = 0x81000000
    STACK_SIZE           = 0x10000
    STACK_TOP            = STACK_BASE + STACK_SIZE
    RETURN_ADDR          = 0x7fff0000

    # Only stub the absolute minimum — true hardware I/O boundaries.
    # Everything else runs natively in the binary.
    IO_STUBS = {
        # USB layer — no real hardware
        0x08021ca4: 'usb_read',       # FUN_08021ca4 — USB raw read
        0x080371b8: 'usb_flush',      # FUN_080371b8 — USB flush
        0x08037084: 'send_response',  # FUN_08037084 — send XML response
        0x0803707c: 'send_resp_wrap', # FUN_0803707c — send response wrapper

        # SDCC/eMMC hardware — no real MMIO registers
        0x08032b94: 'sdcc_cmd',       # sdcc_command — low-level SDCC register I/O
        0x08033656: 'emmc_write_cmd', # FUN_08033656 — actual SDCC write
        0x08034a40: 'cmd6_switch',    # FUN_08034a40 — CMD6 SWITCH

        # Transport / DMA — hardware
        0x0801b85c: 'transport_err',  # FUN_0801b85c — transport error handler
        0x08030ecc: 'set_pending',    # FUN_08030ecc — set pending transfer size

        # Thunks to ROM/external — not in our binary
    }

    # Thunk region: 0x00220000..0x00224000 — calls into PBL ROM, stub all
    THUNK_RANGE = (0x00220000, 0x00224000)

    def __init__(self, elf_path, syms, verbose=False):
        self.elf_path = elf_path
        self.syms = syms
        self.verbose = verbose
        self.func_addrs = set()
        self.addr_to_name = {}
        for addr, name in syms:
            self.func_addrs.add(addr)
            self.addr_to_name[addr] = name
        self.called_funcs = set()
        self.insn_count = 0
        self.max_insns = 5_000_000  # safety limit
        self.uc = Uc(UC_ARCH_ARM, UC_MODE_THUMB)
        self.usb_read_count = 0
        self.total_bytes = 0
        self.bytes_delivered = 0
        self.sector_data_size = 0
        self._load_elf()
        self._setup()

    def _align_down(self, addr, align=0x1000):
        return addr & ~(align - 1)

    def _map_range(self, start, size, perms=UC_PROT_ALL):
        s = self._align_down(start)
        e = (start + size + 0xfff) & ~0xfff
        for page in range(s, e, 0x1000):
            try:
                self.uc.mem_map(page, 0x1000, perms)
            except UcError:
                pass

    def _load_elf(self):
        with open(self.elf_path, 'rb') as f:
            elf = ELFFile(f)
            for seg in elf.iter_segments():
                if seg.header.p_type != 'PT_LOAD':
                    continue
                vaddr = seg.header.p_vaddr
                memsz = seg.header.p_memsz
                filesz = seg.header.p_filesz
                if memsz == 0:
                    continue
                self._map_range(vaddr, memsz)
                if filesz > 0:
                    self.uc.mem_write(vaddr, seg.data()[:filesz])

    def _setup(self):
        self._map_range(self.STACK_BASE, self.STACK_SIZE)
        self._map_range(self.RETURN_ADDR, 0x1000)
        self.uc.mem_write(self.RETURN_ADDR, b'\xfe\xe7')
        self.uc.hook_add(UC_HOOK_CODE, self._code_hook)
        self.uc.hook_add(UC_HOOK_MEM_READ_UNMAPPED | UC_HOOK_MEM_WRITE_UNMAPPED,
                         self._mem_fault_hook)

    def _w32(self, addr, val):
        self.uc.mem_write(addr, struct.pack('<I', val & 0xffffffff))

    def _w8(self, addr, val):
        self.uc.mem_write(addr, struct.pack('<B', val & 0xff))

    def _r32(self, addr):
        return struct.unpack('<I', bytes(self.uc.mem_read(addr, 4)))[0]

    def _read_cstring(self, addr, maxlen=256):
        try:
            data = bytes(self.uc.mem_read(addr, maxlen))
        except UcError:
            return ""
        end = data.find(b'\x00')
        return data[:end if end >= 0 else maxlen].decode('ascii', errors='replace')

    def _do_return(self, uc, retval=0):
        uc.reg_write(UC_ARM_REG_R0, retval & 0xffffffff)
        lr = uc.reg_read(UC_ARM_REG_LR)
        uc.reg_write(UC_ARM_REG_PC, lr & ~1)
        cpsr = uc.reg_read(UC_ARM_REG_CPSR)
        if lr & 1:
            uc.reg_write(UC_ARM_REG_CPSR, cpsr | (1 << 5))
        else:
            uc.reg_write(UC_ARM_REG_CPSR, cpsr & ~(1 << 5))

    def _do_return64(self, uc, r0, r1):
        """Return with r0:r1 pair (for 64-bit returns)."""
        uc.reg_write(UC_ARM_REG_R0, r0 & 0xffffffff)
        uc.reg_write(UC_ARM_REG_R1, r1 & 0xffffffff)
        lr = uc.reg_read(UC_ARM_REG_LR)
        uc.reg_write(UC_ARM_REG_PC, lr & ~1)
        cpsr = uc.reg_read(UC_ARM_REG_CPSR)
        if lr & 1:
            uc.reg_write(UC_ARM_REG_CPSR, cpsr | (1 << 5))

    def _mem_fault_hook(self, uc, access, addr, size, value, user_data):
        page = self._align_down(addr)
        try:
            uc.mem_map(page, 0x1000, UC_PROT_ALL)
        except UcError:
            pass
        return True

    def _code_hook(self, uc, addr, size, user_data):
        self.insn_count += 1
        if self.insn_count > self.max_insns:
            uc.emu_stop()
            return

        # Record function entry
        if addr in self.func_addrs:
            self.called_funcs.add(addr)

        # Stub thunks (PBL ROM calls)
        if self.THUNK_RANGE[0] <= addr < self.THUNK_RANGE[1]:
            if addr in self.func_addrs:
                name = self.addr_to_name[addr]
                if self.verbose:
                    print(f"  THUNK stub: {name} @ 0x{addr:08x}")
            self._do_return(uc, 0)
            return

        # Stub I/O functions
        if addr in self.IO_STUBS:
            stub_name = self.IO_STUBS[addr]
            if stub_name == 'usb_read':
                self._hook_usb_read(uc)
            elif stub_name == 'usb_flush':
                self._do_return(uc, 0)
            elif stub_name == 'send_response':
                self._hook_send_response(uc)
            elif stub_name == 'send_resp_wrap':
                self._hook_send_response(uc)
            elif stub_name == 'sdcc_cmd':
                self._hook_sdcc_cmd(uc)
            elif stub_name == 'emmc_write_cmd':
                self._do_return(uc, 0)  # success
            elif stub_name == 'cmd6_switch':
                self._do_return(uc, 0)  # success
            elif stub_name == 'transport_err':
                self._do_return(uc, 0)
            elif stub_name == 'set_pending':
                self._do_return(uc, 0)
            return

        # Sentinel
        if addr == self.RETURN_ADDR:
            uc.emu_stop()

    def _hook_usb_read(self, uc):
        """USB read — supply fake sector data."""
        out_ptr = uc.reg_read(UC_ARM_REG_R0)
        remaining = self.total_bytes - self.bytes_delivered
        if remaining <= 0:
            self._do_return(uc, 1)  # error = no more data
            return
        chunk = min(remaining, self.sector_data_size)
        self.bytes_delivered += chunk
        self._w32(out_ptr, self.FAKE_SECTOR_DATA)
        self._w32(out_ptr + 0x0c, chunk)
        self._w32(out_ptr + 0x10, 0)
        self.usb_read_count += 1
        self._do_return(uc, 0)

    def _hook_send_response(self, uc):
        """Send XML response — just return, no real USB."""
        self._do_return(uc, 0)

    def _hook_sdcc_cmd(self, uc):
        """Low-level SDCC command — fake success with plausible response."""
        # r0 = dev_struct, r1 = cmd_struct_ptr
        r1 = uc.reg_read(UC_ARM_REG_R1)
        # cmd_struct: [0]=cmd_num, [1]=arg, [2]=resp_type, ...
        # Write success response
        self._w32(r1 + 0x20, 0)  # status = success
        self._do_return(uc, 0)

    def setup_globals(self):
        """Initialize global state for firehose operation."""
        # ctype table
        CTYPE_TABLE = 0x80130000
        self._map_range(CTYPE_TABLE, 0x200)
        table = bytearray(256)
        for c in b' \t\n\r\x0b\x0c':
            table[c] = 0x01
        for c in range(ord('a'), ord('z') + 1):
            table[c] = 0x08 | 0x80
        for c in range(ord('A'), ord('Z') + 1):
            table[c] = 0x08 | 0x80
        for c in range(ord('0'), ord('9') + 1):
            table[c] = 0x10 | 0x80
        table[ord('_')] = 0x20 | 0x80
        table[ord('-')] = 0x20
        table[ord('.')] = 0x20
        table[ord(':')] = 0x20
        self.uc.mem_write(CTYPE_TABLE, bytes(table))
        self._w32(0x0805a89c, CTYPE_TABLE)

        canary = self._r32(self.ADDR_STACK_CANARY)
        if canary == 0:
            self._w32(self.ADDR_STACK_CANARY, 0x00040a0d)

        self._w32(self.ADDR_SECTOR_SZ, 0x200)
        self._w32(self.ADDR_SECTOR_SZ_HI, 0)
        self._w32(self.ADDR_MAX_SECT_LO, 0x100000)
        self._w32(self.ADDR_MAX_SECT_HI, 0)
        self._w8(self.ADDR_SKIP_WRITE, 0)
        self._w8(self.ADDR_ACK_RAW, 0)
        self._w8(self.ADDR_VERBOSE, 1)
        self._w32(self.ADDR_ACK_EVERY, 0)
        self._w8(self.ADDR_VALIDATION, 0)
        self._w32(self.ADDR_USB_DMA_BASE, 0x80000000)
        self._w32(self.ADDR_USB_RX_BUF, 0x80200000)
        self._w8(self.ADDR_CONTEXT + 0x148, 0)

        # Storage device struct
        self._map_range(self.FAKE_CARD_INFO, 0x200)
        self._map_range(self.FAKE_EXT_CSD, 0x200)
        self._map_range(self.FAKE_DEV_HANDLE, 0x200)

        # Card info
        self._w32(self.FAKE_CARD_INFO + 0x08, 0x02)      # card type = eMMC
        self._w32(self.FAKE_CARD_INFO + 0x24, 1)          # sector multiplier
        self._w32(self.FAKE_CARD_INFO + 0x1c, 0xFFFFFF)   # total sectors
        self._w32(self.FAKE_CARD_INFO + 0x20, 0x200)      # sector size
        self._w32(self.FAKE_CARD_INFO + 0x34, 8)          # num partitions
        self._w8(self.FAKE_EXT_CSD + 0xa0, 0)             # WP off
        self._w32(self.FAKE_CARD_INFO + 0x90, self.FAKE_EXT_CSD)

        # Device handle indirection
        self._w32(self.FAKE_DEV_HANDLE, self.FAKE_CARD_INFO)
        self._w32(self.FAKE_DEV_HANDLE + 4, 0)

        # Storage dev struct at 0x08058430
        self._w8(self.ADDR_STORAGE_DEV, 0)
        for slot in range(8):
            self._w32(self.ADDR_STORAGE_DEV + 4 + slot * 4, self.FAKE_DEV_HANDLE)
        self._w32(self.ADDR_STORAGE_DEV + 0x24, 0x02)  # eMMC
        self._w8(self.ADDR_STORAGE_DEV + 0x26, 0xFF)    # no partition selected
        self._w32(self.ADDR_STORAGE_DEV + 0x28, 0x200)
        self._w32(self.ADDR_STORAGE_DEV + 0x2c, 0)

        # XML writer buffer
        self._map_range(self.FAKE_XML_WR_BUF, 0x10000)
        self._w32(self.ADDR_XML_WRITER, self.FAKE_XML_WR_BUF)

    def setup_xml(self, xml_bytes):
        self._map_range(self.FAKE_XML_BUF, 0x1000)
        self.uc.mem_write(self.FAKE_XML_BUF, xml_bytes + b'\x00')
        xml_len = len(xml_bytes)
        self._w32(self.ADDR_XML_PARSER + 0x00, self.FAKE_XML_BUF)
        self._w32(self.ADDR_XML_PARSER + 0x04, 0)
        self._w32(self.ADDR_XML_PARSER + 0x08, xml_len)
        self._w32(self.ADDR_XML_PARSER + 0x0c, 0)
        self._w8(self.ADDR_XML_PARSER + 0x10, 0)
        self._w32(self.ADDR_XML_PARSER + 0x14, 0)
        self._w32(self.ADDR_XML_PARSER + 0x18, 0)
        self._w32(self.ADDR_XML_PARSER + 0x1c, 0)
        self._w32(self.ADDR_XML_PARSER + 0x20, 0)
        self._w32(self.ADDR_XML_PARSER + 0x24, 0)

    def run_command(self, xml_str, num_sectors=16):
        """Run a single XML command through the dispatcher."""
        self.called_funcs.clear()
        self.insn_count = 0

        self.setup_globals()
        self.setup_xml(xml_str.encode('ascii'))

        # Setup sector data
        sector_size = 0x200
        self.total_bytes = num_sectors * sector_size
        self.sector_data_size = min(self.total_bytes, 0x100000)
        self.bytes_delivered = 0
        self.usb_read_count = 0
        self._map_range(self.FAKE_SECTOR_DATA, self.sector_data_size + 0x1000)
        self.uc.mem_write(self.FAKE_SECTOR_DATA, b'\xAA' * self.sector_data_size)

        self.uc.reg_write(UC_ARM_REG_SP, self.STACK_TOP - 0x100)
        self.uc.reg_write(UC_ARM_REG_LR, self.RETURN_ADDR | 1)
        cpsr = self.uc.reg_read(UC_ARM_REG_CPSR)
        self.uc.reg_write(UC_ARM_REG_CPSR, cpsr | (1 << 5))

        try:
            self.uc.emu_start(self.FN_DISPATCHER | 1, self.RETURN_ADDR,
                              timeout=30_000_000, count=0)
        except UcError as e:
            pc = self.uc.reg_read(UC_ARM_REG_PC)
            if self.verbose:
                print(f"  EMU ERROR: {e} at PC=0x{pc:08x}")

        return set(self.called_funcs)


# ---------------------------------------------------------------------------
# Static call closure from source
# ---------------------------------------------------------------------------

def compute_closure_from_source(entry_funcs, src_dir="src/fhprg"):
    """Compute transitive closure of function references starting from entry_funcs."""
    globals_h = (Path(src_dir) / "globals.h").read_text()

    # Collect all function names from globals.h
    all_funcs = set()
    for m in re.finditer(r'\b((?:FUN_[0-9a-fA-F]+|thunk_\w+|[a-z]\w+))\s*\(', globals_h):
        all_funcs.add(m.group(1))
    all_funcs.update(entry_funcs)

    # Parse function bodies from source
    func_bodies = {}
    for cfile in sorted(Path(src_dir).glob("*.c")):
        text = cfile.read_text()
        parts = re.split(r'/\*\s*0x[0-9a-fA-F]+\s*\*/', text)
        for part in parts[1:]:
            func_match = re.search(r'\b(\w+)\s*\([^)]*\)\s*[;{]', part)
            if func_match:
                fname = func_match.group(1)
                func_bodies[fname] = part

    # BFS
    closure = set()
    queue = list(entry_funcs)
    while queue:
        func = queue.pop(0)
        if func in closure:
            continue
        closure.add(func)
        body = func_bodies.get(func, "")
        for other in all_funcs:
            if other != func and other in body and other not in closure:
                queue.append(other)

    return closure


def count_loc(func_names, src_dir="src/fhprg"):
    """Count total lines of C source for the given function set."""
    total_lines = 0
    matched = set()

    for cfile in sorted(Path(src_dir).glob("*.c")):
        text = cfile.read_text()
        lines = text.splitlines()
        i = 0
        while i < len(lines):
            if lines[i].strip().startswith('/* 0x'):
                func_start = i
                j = i + 1
                while j < len(lines) and not lines[j].strip():
                    j += 1
                if j < len(lines):
                    m = re.search(r'\b(\w+)\s*\(', lines[j])
                    if m:
                        fname = m.group(1)
                        depth = 0
                        k = j
                        found_open = False
                        while k < len(lines):
                            depth += lines[k].count('{')
                            if depth > 0:
                                found_open = True
                            depth -= lines[k].count('}')
                            if found_open and depth <= 0:
                                if fname in func_names:
                                    total_lines += (k + 1 - func_start)
                                    matched.add(fname)
                                break
                            k += 1
            i += 1

    return total_lines, matched


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main():
    verbose = '--verbose' in sys.argv or '-v' in sys.argv

    syms = load_syms()
    addr_to_name = {addr: name for addr, name in syms}
    print(f"Loaded {len(syms)} functions from syms file\n")

    elf_path = "fhprg_peek.bin"
    if not os.path.exists(elf_path):
        print(f"ERROR: {elf_path} not found")
        sys.exit(1)

    # Core operations: configure (required setup), read, write
    commands = {
        "configure": '<configure MemoryName="eMMC" '
                     'ZLPAwareHost="1" SkipWrite="0" '
                     'SkipStorageInit="0" MaxPayloadSizeToTargetInBytes="49152" />',
        "program": '<program SECTOR_SIZE_IN_BYTES="512" '
                   'num_partition_sectors="16" '
                   'physical_partition_number="0" '
                   'start_sector="2663442" />',
        "read": '<read SECTOR_SIZE_IN_BYTES="512" '
                'num_partition_sectors="16" '
                'physical_partition_number="0" '
                'start_sector="2663442" />',
    }

    all_dynamic = set()  # union of all dynamically-called function names
    per_command = {}

    for cmd_name, xml in commands.items():
        print(f"--- {cmd_name} ", end="", flush=True)

        emu = TracingEmulator(elf_path, syms, verbose=verbose)
        called = emu.run_command(xml)
        called_names = {addr_to_name[a] for a in called if a in addr_to_name}
        insns = emu.insn_count

        print(f"→ {len(called_names)} functions, {insns} insns")
        per_command[cmd_name] = called_names
        all_dynamic.update(called_names)

        if verbose:
            for name in sorted(called_names):
                addr = next(a for a, n in syms if n == name)
                print(f"    0x{addr:08x} {name}")

    print(f"\n{'='*70}")
    print(f"Combined dynamic trace: {len(all_dynamic)} unique functions")
    print(f"{'='*70}")

    # Show per-command unique functions
    for cmd_name, funcs in sorted(per_command.items()):
        unique = funcs - set().union(*(v for k, v in per_command.items() if k != cmd_name))
        if unique:
            print(f"\n  Only in <{cmd_name}>: {len(unique)}")
            for n in sorted(unique):
                print(f"    {n}")

    # Common across all commands
    common = set.intersection(*per_command.values()) if per_command else set()
    print(f"\n  Common to all commands: {len(common)}")

    # Static closure
    print(f"\nComputing static call closure from {len(all_dynamic)} dynamic entries...")
    closure = compute_closure_from_source(all_dynamic)
    print(f"Static closure: {len(closure)} functions")

    # LoC
    closure_loc, closure_matched = count_loc(closure)
    all_names = {name for _, name in syms}
    total_loc, _ = count_loc(all_names)

    print(f"\nEstimated lines of C for minimal programmer:")
    print(f"  Dynamic only:    {len(all_dynamic)} functions")
    print(f"  Static closure:  {len(closure)} functions")
    print(f"  Closure LoC:     {closure_loc}")
    print(f"  Total LoC:       {total_loc}")
    print(f"  Reduction:       {closure_loc}/{total_loc} = {closure_loc/max(total_loc,1)*100:.1f}%")
    print(f"  Unmatched:       {closure - closure_matched}")

    # Breakdown by source file
    print(f"\nClosure functions by source module:")
    file_counts = defaultdict(list)
    for cfile in sorted(Path("src/fhprg").glob("*.c")):
        text = cfile.read_text()
        for m in re.finditer(r'/\*\s*0x[0-9a-fA-F]+\s*\*/\s*\n\s*\w+\s+(\w+)\s*\(', text):
            fname = m.group(1)
            if fname in closure:
                file_counts[cfile.name].append(fname)
    for fname, funcs in sorted(file_counts.items(), key=lambda x: -len(x[1])):
        print(f"  {fname:40s} {len(funcs):4d} functions")


if __name__ == '__main__':
    main()
