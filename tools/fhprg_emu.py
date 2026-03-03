#!/usr/bin/env python3
"""
Unicorn Engine harness for Qualcomm Firehose programmer (fhprg_peek.bin).

Emulates just enough of the binary to trace the <program> command path
and compare behavior for different partition writes (e.g. splash vs aboot).

Usage:
    python3 tools/fhprg_emu.py [--start-sector N] [--num-sectors N] [--partition N] [--verbose]

Examples:
    # Test splash write (should succeed)
    python3 tools/fhprg_emu.py --start-sector 2663442 --num-sectors 2048

    # Test aboot write (expected to be blocked)
    python3 tools/fhprg_emu.py --start-sector 2623488 --num-sectors 8192

    # Compare both
    python3 tools/fhprg_emu.py --compare
"""

import argparse
import struct
import sys
import os

from unicorn import *
from unicorn.arm_const import *
from elftools.elf.elffile import ELFFile
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

# ---------------------------------------------------------------------------
# Constants
# ---------------------------------------------------------------------------

ELF_PATH = os.path.join(os.path.dirname(__file__), '..', 'fhprg_peek.bin')

# Key addresses (from Ghidra analysis)
ADDR_XML_PARSER      = 0x08055ea0  # DAT_08055ea0 - XML parser state struct
ADDR_XML_WRITER      = 0x08055f18  # DAT_08055f18 - XML writer state
ADDR_STORAGE_DEV     = 0x08058430  # DAT_08058430 - storage device struct
ADDR_SECTOR_SZ       = 0x08058458  # DAT_08058458 - expected sector size (low)
ADDR_SECTOR_SZ_HI    = 0x0805845c  # DAT_0805845c - expected sector size (high)
ADDR_SKIP_WRITE      = 0x08058480  # DAT_08058480 - SkipWrite flag
ADDR_ACK_RAW         = 0x08058481  # DAT_08058481 - AckRawData flag
ADDR_VERBOSE         = 0x08058482  # DAT_08058482 - Verbose flag
ADDR_ACK_EVERY       = 0x08058484  # DAT_08058484 - AckRawDataEveryNumPackets
ADDR_VALIDATION      = 0x08055fd8  # DAT_08055fd8 - validation_enabled
ADDR_MAX_SECT_LO     = 0x08055fb8  # DAT_08055fb8 - max sectors low
ADDR_MAX_SECT_HI     = 0x08055fbc  # DAT_08055fbc - max sectors high
ADDR_STACK_CANARY    = 0x0804cd58  # DAT_0804cd58 - stack canary value
ADDR_CONTEXT         = 0x08055e90  # DAT_08055e90 - context struct
ADDR_USB_DMA_BASE    = 0x08054e90  # DAT_08054e90 - USB DMA buf base ptr
ADDR_USB_RX_BUF      = 0x08055e98  # DAT_08055e98 - USB RX buffer pointer

# Function addresses
FN_DISPATCHER        = 0x0802f130  # FUN_0802f130 - XML command dispatcher
FN_PROGRAM_HANDLER   = 0x08024484  # FUN_08024484 - <program> handler
FN_XML_INIT          = 0x08039030  # FUN_08039030 - XML parser init
FN_XML_ADVANCE       = 0x08038db4  # FUN_08038db4 - XML parser advance
FN_XML_TAG_CMP       = 0x08039092  # FUN_08039092 - compare tag name
FN_XML_ATTR_CMP      = 0x0803906c  # FUN_0803906c - compare attr name
FN_XML_ATTR_VAL      = 0x08038d38  # FUN_08038d38 - extract attr value
FN_XML_TAG_NAME      = 0x08038d76  # FUN_08038d76 - extract tag name
FN_PARTITION_SEL     = 0x08038206  # FUN_08038206 - partition selector/gate
FN_WRITE_WRAPPER     = 0x080381d8  # FUN_080381d8 - storage write wrapper
FN_READ_WRAPPER      = 0x08038014  # FUN_08038014 - storage read wrapper
FN_SEND_RESPONSE     = 0x08037084  # FUN_08037084 - send XML response
FN_SEND_RESP_WRAP    = 0x0803707c  # FUN_0803707c - send response wrapper
FN_LOG_MSG           = 0x08027674  # FUN_08027674 - log message sender
FN_DEBUG_LOG         = 0x0801b6bc  # FUN_0801b6bc - debug ring buffer
FN_CANARY_FAIL       = 0x08010960  # FUN_08010960 - stack canary panic
FN_USB_READ          = 0x08021ca4  # FUN_08021ca4 - USB raw read
FN_MEMSET            = 0x08006d14  # FUN_08006d14 - memset (zero-fill)
FN_STRLEN            = 0x08006906  # FUN_08006906 - strlen
FN_VSNPRINTF         = 0x08006418  # FUN_08006418 - vsnprintf
FN_SNPRINTF          = 0x0800644c  # FUN_0800644c - snprintf
FN_MEMCMP            = 0x08006898  # FUN_08006898 - memcmp
FN_MEMCPY            = 0x08006a30  # FUN_08006a30 - memcpy
FN_DIVMOD64          = 0x080060c0  # FUN_080060c0 - 64-bit divide
FN_PARSE_INT         = 0x0803823e  # FUN_0803823e - parse integer from string
FN_PARSE_SECTOR      = 0x08028c10  # FUN_08028c10 - parse sector number
FN_GET_PART_INFO     = 0x08033ee8  # FUN_08033ee8 - get partition info
FN_USB_FLUSH         = 0x080371b8  # FUN_080371b8 - flush USB output
FN_XML_WR_INIT       = 0x080391f0  # XML writer init
FN_XML_WR_OPEN       = 0x08039100  # XML writer open element
FN_XML_WR_ELEM       = 0x080390f4  # XML writer element name
FN_XML_WR_ATTR_Q     = 0x08039174  # XML writer attr (quoted)
FN_XML_WR_ATTR       = 0x0803918c  # XML writer attr
FN_XML_WR_CLOSE1     = 0x080390d8  # XML writer close self
FN_XML_WR_CLOSE2     = 0x080390e4  # XML writer close element
FN_HASH_CALC         = 0x0800d59c  # hash/checksum
FN_SET_PENDING       = 0x08030ecc  # FUN_08030ecc - set pending transfer size
FN_TRANSPORT_ERR     = 0x0801b85c  # FUN_0801b85c - transport error handler

# Fake data locations in scratch RAM
FAKE_CARD_INFO       = 0x80100000
FAKE_EXT_CSD         = 0x80100100
FAKE_USB_BUF         = 0x80100200  # fake USB receive buffer
FAKE_XML_BUF         = 0x80100400  # where we put our XML
FAKE_SECTOR_DATA     = 0x80300000  # fake sector data for USB reads (up to 1MB)
FAKE_XML_WR_BUF      = 0x80500000  # fake XML writer output buffer

# Stack
STACK_BASE           = 0x81000000
STACK_SIZE           = 0x10000     # 64 KB
STACK_TOP            = STACK_BASE + STACK_SIZE

# Return sentinel — we map a page here and put a BX LR or sentinel
RETURN_ADDR          = 0x7fff0000


# ---------------------------------------------------------------------------
# Trace log
# ---------------------------------------------------------------------------

class TraceLog:
    """Collects hook events for later comparison."""

    def __init__(self, verbose=False):
        self.events = []
        self.verbose = verbose

    def log(self, tag, msg):
        self.events.append((tag, msg))
        if self.verbose:
            print(f"  [{tag}] {msg}")

    def summary(self):
        lines = []
        for tag, msg in self.events:
            lines.append(f"  [{tag}] {msg}")
        return '\n'.join(lines)


# ---------------------------------------------------------------------------
# Emulator
# ---------------------------------------------------------------------------

class FHProgramEmulator:
    def __init__(self, elf_path=ELF_PATH, verbose=False):
        self.elf_path = os.path.abspath(elf_path)
        self.verbose = verbose
        self.trace = TraceLog(verbose)
        self.uc = Uc(UC_ARCH_ARM, UC_MODE_THUMB)
        self.usb_read_count = 0
        self.sector_data_size = 0  # bytes per USB read
        self.num_sectors = 0
        self.total_bytes = 0
        self.bytes_delivered = 0

        self._load_elf()
        self._setup_stack()
        self._setup_return_sentinel()
        self._install_hooks()

    def _align_down(self, addr, align=0x1000):
        return addr & ~(align - 1)

    def _align_up(self, addr, align=0x1000):
        return (addr + align - 1) & ~(align - 1)

    def _map_range(self, start, size, perms=UC_PROT_ALL):
        """Map a range, page-aligned, skipping already-mapped pages."""
        start_aligned = self._align_down(start)
        end_aligned = self._align_up(start + size)
        sz = end_aligned - start_aligned
        if sz <= 0:
            return
        try:
            self.uc.mem_map(start_aligned, sz, perms)
        except UcError:
            # Might overlap with existing mapping; map page by page
            for page in range(start_aligned, end_aligned, 0x1000):
                try:
                    self.uc.mem_map(page, 0x1000, perms)
                except UcError:
                    pass  # already mapped

    def _load_elf(self):
        """Load ELF LOAD segments into Unicorn memory."""
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
                    data = seg.data()
                    self.uc.mem_write(vaddr, data[:filesz])
                # memsz > filesz is already zero (Unicorn zero-fills mapped memory)

        if self.verbose:
            print("[emu] ELF loaded")

    def _setup_stack(self):
        """Map stack memory."""
        self._map_range(STACK_BASE, STACK_SIZE)
        self.uc.reg_write(UC_ARM_REG_SP, STACK_TOP - 0x100)

    def _setup_return_sentinel(self):
        """Map a return address page. When PC hits here, we stop."""
        self._map_range(RETURN_ADDR, 0x1000)
        # Write Thumb infinite loop (b . = 0xe7fe) as sentinel
        self.uc.mem_write(RETURN_ADDR, b'\xfe\xe7')

    def _read_cstring(self, addr, maxlen=256):
        """Read a null-terminated string from Unicorn memory."""
        try:
            data = self.uc.mem_read(addr, maxlen)
        except UcError:
            return f"<unreadable@0x{addr:08x}>"
        end = bytes(data).find(b'\x00')
        if end < 0:
            end = maxlen
        return bytes(data[:end]).decode('ascii', errors='replace')

    def _write_u32(self, addr, val):
        self.uc.mem_write(addr, struct.pack('<I', val & 0xffffffff))

    def _write_u8(self, addr, val):
        self.uc.mem_write(addr, struct.pack('<B', val & 0xff))

    def _read_u32(self, addr):
        return struct.unpack('<I', bytes(self.uc.mem_read(addr, 4)))[0]

    def _do_return(self, uc, retval=0):
        """Simulate function return: set r0, pop to LR, set PC = LR.
        For Thumb mode, we set the T bit in CPSR and use LR with bit 0 set."""
        uc.reg_write(UC_ARM_REG_R0, retval & 0xffffffff)
        lr = uc.reg_read(UC_ARM_REG_LR)
        # In Thumb mode, BX LR uses bit 0 of LR to determine mode.
        # We need to write PC = LR & ~1, and ensure CPSR.T is set.
        uc.reg_write(UC_ARM_REG_PC, lr & ~1)
        # Ensure Thumb bit is set in CPSR
        cpsr = uc.reg_read(UC_ARM_REG_CPSR)
        if lr & 1:
            uc.reg_write(UC_ARM_REG_CPSR, cpsr | (1 << 5))  # T bit
        else:
            uc.reg_write(UC_ARM_REG_CPSR, cpsr & ~(1 << 5))

    # -- Hooks ---------------------------------------------------------------

    def _install_hooks(self):
        """Install code hooks at function entry points."""
        # We use a single UC_HOOK_CODE callback and dispatch by address.
        # For efficiency, we also patch some function prologues to BX LR
        # for functions we want to completely stub.

        # Hook every instruction (filtered to code regions)
        self.uc.hook_add(UC_HOOK_CODE, self._code_hook)

        # Hook unmapped memory accesses to provide graceful failure
        self.uc.hook_add(UC_HOOK_MEM_READ_UNMAPPED | UC_HOOK_MEM_WRITE_UNMAPPED,
                         self._mem_fault_hook)

    def _mem_fault_hook(self, uc, access, addr, size, value, user_data):
        """Handle unmapped memory by mapping on demand."""
        self.trace.log("MEM_FAULT", f"access={access} addr=0x{addr:08x} size={size}")
        # Auto-map the page
        page = self._align_down(addr)
        try:
            uc.mem_map(page, 0x1000, UC_PROT_ALL)
        except UcError:
            pass
        return True

    def _code_hook(self, uc, addr, size, user_data):
        """Dispatch hooks by address."""
        # Trace XML parser calls
        if addr == FN_XML_ADVANCE:
            self._hook_trace_xml_advance(uc)
            return
        if addr == FN_MEMSET:
            self._hook_memset(uc)
            return
        if addr == FN_GET_PART_INFO:
            self._hook_get_part_info(uc)
            return
        if addr == FN_PARTITION_SEL:
            self._hook_partition_sel(uc)
            return
        if addr == FN_PARSE_SECTOR:
            self._hook_parse_sector(uc)
            return
        if addr == FN_STRLEN:
            self._hook_strlen(uc)
            return
        if addr == FN_VSNPRINTF:
            self._hook_vsnprintf(uc)
            return
        if addr == FN_SNPRINTF:
            self._hook_snprintf(uc)
            return
        if addr == FN_MEMCMP:
            self._hook_memcmp(uc)
            return
        if addr == FN_MEMCPY:
            self._hook_memcpy(uc)
            return
        if addr == FN_DIVMOD64:
            self._hook_divmod64(uc)
            return
        if addr == FN_PARSE_INT:
            self._hook_parse_int(uc)
            return
        if addr == FN_XML_TAG_CMP:
            self._hook_trace_tag_cmp(uc)
            return  # let it run natively after logging
        if addr == FN_CANARY_FAIL:
            self._hook_canary_fail(uc)
        elif addr == FN_USB_READ:
            self._hook_usb_read(uc)
        elif addr == FN_WRITE_WRAPPER:
            self._hook_write_wrapper(uc)
        elif addr == FN_READ_WRAPPER:
            self._hook_read_wrapper(uc)
        elif addr == FN_SEND_RESPONSE:
            self._hook_send_response(uc)
        elif addr == FN_SEND_RESP_WRAP:
            self._hook_send_resp_wrap(uc)
        elif addr == FN_LOG_MSG:
            self._hook_log_msg(uc)
        elif addr == FN_DEBUG_LOG:
            self._hook_debug_log(uc)
        elif addr == FN_USB_FLUSH:
            self._hook_usb_flush(uc)
        elif addr == FN_TRANSPORT_ERR:
            self._hook_transport_err(uc)
        elif addr == FN_SET_PENDING:
            self._hook_set_pending(uc)
        elif addr == FN_HASH_CALC:
            self._hook_hash_calc(uc)
        elif addr == RETURN_ADDR:
            uc.emu_stop()

    def _hook_trace_tag_cmp(self, uc):
        """Trace FUN_08039092 calls to see tag matching."""
        if not self.verbose:
            return  # Only trace in verbose mode
        r0 = uc.reg_read(UC_ARM_REG_R0)  # parser struct
        r1 = uc.reg_read(UC_ARM_REG_R1)  # search string
        tag_start = self._read_u32(r0 + 0x28)
        tag_end = self._read_u32(r0 + 0x30)
        buf_ptr = self._read_u32(r0)
        search = self._read_cstring(r1)
        tag_len = tag_end - tag_start
        tag = ""
        if buf_ptr and tag_len > 0 and tag_len < 256:
            try:
                raw = bytes(uc.mem_read(buf_ptr + tag_start, tag_len))
                tag = raw.decode('ascii', errors='replace')
            except UcError:
                tag = "<err>"
        self.trace.log("TAG_CMP", f"tag='{tag}' vs '{search}'")
        # Don't intercept - let it run natively

    def _hook_trace_xml_advance(self, uc):
        """Trace FUN_08038db4 calls - don't intercept, just log."""
        if not self.verbose:
            return  # Only trace in verbose mode
        r0 = uc.reg_read(UC_ARM_REG_R0)
        pos_lo = self._read_u32(ADDR_XML_PARSER + 0x18)
        buf_len = self._read_u32(ADDR_XML_PARSER + 0x08)
        state = struct.unpack('B', bytes(uc.mem_read(ADDR_XML_PARSER + 0x10, 1)))[0]
        buf_ptr = self._read_u32(ADDR_XML_PARSER)
        snippet = ""
        if buf_ptr and pos_lo < buf_len:
            try:
                raw = bytes(uc.mem_read(buf_ptr + pos_lo, min(20, buf_len - pos_lo)))
                snippet = raw.decode('ascii', errors='replace')
            except UcError:
                snippet = "<err>"
        self.trace.log("XML_ADV", f"pos={pos_lo}/{buf_len} state={state} next='{snippet}'")
        # Let it run natively - don't return

    def _hook_memset(self, uc):
        """FUN_08006d14 - memset to zero. Implement in hook for reliability."""
        r0 = uc.reg_read(UC_ARM_REG_R0)
        r1 = uc.reg_read(UC_ARM_REG_R1)
        try:
            uc.mem_write(r0, b'\x00' * r1)
        except UcError:
            pass
        self._do_return(uc, r0)

    def _hook_canary_fail(self, uc):
        """Stack canary check - just return."""
        self.trace.log("CANARY", "Stack canary check bypassed")
        self._do_return(uc, 0)

    def _hook_usb_read(self, uc):
        """USB read - supply fake sector data.
        FUN_08021ca4(int *out_info) - wraps FUN_08031170
        The program handler calls: iVar12 = FUN_08021ca4(&local_320)
        where local_320 is a struct:
          local_320 = buffer pointer
          local_308 = bytes read (low)
          uStack_304 = bytes read (high)
        """
        # r0 = pointer to output struct
        out_ptr = uc.reg_read(UC_ARM_REG_R0)

        remaining = self.total_bytes - self.bytes_delivered
        if remaining <= 0:
            # No more data - return error to break loop
            self.trace.log("USB_READ", "No more data, returning error")
            self._do_return(uc, 1)
            return

        chunk = min(remaining, self.sector_data_size)
        self.bytes_delivered += chunk

        # Write output struct: the program handler reads local_320 as buffer ptr
        # From decompiled code analysis:
        # local_320 = out_ptr[0] = buffer pointer
        # local_308 = out_ptr[3] = bytes received (low)
        # uStack_304 = out_ptr[4] = bytes received (high)
        self._write_u32(out_ptr, FAKE_SECTOR_DATA)   # buffer pointer
        self._write_u32(out_ptr + 0x0c, chunk)        # bytes read low
        self._write_u32(out_ptr + 0x10, 0)            # bytes read high

        self.usb_read_count += 1
        self.trace.log("USB_READ", f"#{self.usb_read_count}: {chunk} bytes "
                       f"({self.bytes_delivered}/{self.total_bytes})")
        self._do_return(uc, 0)  # success

    def _hook_write_wrapper(self, uc):
        """FUN_080381d8 - storage write. Log and return success."""
        # params: r0=dev_struct, r1=buf_ptr, r2=start_sector_lo, r3=start_sector_hi
        # stack: [sp+0]=num_sectors(u16), [sp+4]=???, [sp+8]=errno_ptr
        r0 = uc.reg_read(UC_ARM_REG_R0)
        r1 = uc.reg_read(UC_ARM_REG_R1)
        r2 = uc.reg_read(UC_ARM_REG_R2)
        r3 = uc.reg_read(UC_ARM_REG_R3)
        sp = uc.reg_read(UC_ARM_REG_SP)
        num_sect = struct.unpack('<H', bytes(uc.mem_read(sp, 2)))[0]

        start_sector = r2 | (r3 << 32)
        self.trace.log("WRITE", f"sector={start_sector} (0x{start_sector:x}), "
                       f"nsectors={num_sect}, buf=0x{r1:08x}")
        # Return 1 (success) - the function returns 1 on success, 0 on failure
        self._do_return(uc, 1)

    def _hook_read_wrapper(self, uc):
        """FUN_08038014 - storage read. Return success."""
        r2 = uc.reg_read(UC_ARM_REG_R2)
        r3 = uc.reg_read(UC_ARM_REG_R3)
        start_sector = r2 | (r3 << 32)
        self.trace.log("READ", f"sector={start_sector} (readback verify)")
        self._do_return(uc, 1)

    def _hook_send_response(self, uc):
        """FUN_08037084 - XML response builder. Log ACK/NAK."""
        success = uc.reg_read(UC_ARM_REG_R0)
        num_attrs = uc.reg_read(UC_ARM_REG_R1)
        result = "ACK" if success == 1 else "NAK"
        self.trace.log("RESPONSE", f"{result} (attrs={num_attrs})")
        self._do_return(uc, 0)

    def _hook_send_resp_wrap(self, uc):
        """FUN_0803707c - wrapper, calls FUN_08037084(param_1, 0)."""
        success = uc.reg_read(UC_ARM_REG_R0)
        result = "ACK" if success == 1 else "NAK"
        self.trace.log("RESPONSE_W", f"{result}")
        self._do_return(uc, 0)

    def _hook_log_msg(self, uc):
        """FUN_08027674 - log/diagnostic message. Extract format + args."""
        fmt_addr = uc.reg_read(UC_ARM_REG_R0)
        r1 = uc.reg_read(UC_ARM_REG_R1)
        r2 = uc.reg_read(UC_ARM_REG_R2)
        r3 = uc.reg_read(UC_ARM_REG_R3)

        fmt = self._read_cstring(fmt_addr)
        # Simple format string substitution for common patterns
        msg = self._format_log(fmt, r1, r2, r3)
        self.trace.log("LOG", msg)
        self._do_return(uc, 0)

    def _hook_debug_log(self, uc):
        """FUN_0801b6bc - debug ring buffer. Extract format + args."""
        fmt_addr = uc.reg_read(UC_ARM_REG_R0)
        r1 = uc.reg_read(UC_ARM_REG_R1)
        r2 = uc.reg_read(UC_ARM_REG_R2)
        r3 = uc.reg_read(UC_ARM_REG_R3)

        fmt = self._read_cstring(fmt_addr)
        msg = self._format_log(fmt, r1, r2, r3)
        self.trace.log("DEBUG", msg)
        self._do_return(uc, 0)

    def _hook_usb_flush(self, uc):
        """FUN_080371b8 - USB flush. NOP."""
        self._do_return(uc, 0)

    def _hook_transport_err(self, uc):
        """FUN_0801b85c - transport error handler. NOP."""
        self._do_return(uc, 0)

    def _hook_set_pending(self, uc):
        """FUN_08030ecc - set pending transfer size. NOP."""
        self._do_return(uc, 0)

    def _hook_hash_calc(self, uc):
        """FUN_0800d59c - hash/checksum calc. NOP."""
        self._do_return(uc, 0)

    def _hook_partition_sel(self, uc):
        """FUN_08038206 - partition selector/gate.
        param_1 (r0) = &DAT_08058430 (storage dev struct)
        param_2 (r1) = physical_partition_number
        Returns 64-bit in r0:r1:
          r0 = 1 (success) or 0 (fail)
          r1 = secondary return value (used by caller)

        THIS IS THE KEY RESTRICTION GATE.
        Real code checks: (param_2 < 8) && (param_2 != 3) && partition_info_ok
        We emulate the REAL check to show the restriction."""
        r0_dev = uc.reg_read(UC_ARM_REG_R0)
        part_num = uc.reg_read(UC_ARM_REG_R1)

        # Apply the real restriction logic
        if part_num >= 8:
            self.trace.log("PART_SEL", f"partition={part_num}: BLOCKED (>= 8)")
            uc.reg_write(UC_ARM_REG_R0, 0)
            uc.reg_write(UC_ARM_REG_R1, 0)
        elif part_num == 3:
            self.trace.log("PART_SEL", f"partition={part_num}: BLOCKED (== 3, aboot protection)")
            uc.reg_write(UC_ARM_REG_R0, 0)
            uc.reg_write(UC_ARM_REG_R1, 0)
        else:
            self.trace.log("PART_SEL", f"partition={part_num}: ALLOWED")
            # Set selected_partition byte
            self._write_u8(r0_dev + 0x26, part_num)
            uc.reg_write(UC_ARM_REG_R0, 1)
            uc.reg_write(UC_ARM_REG_R1, 0)

        lr = uc.reg_read(UC_ARM_REG_LR)
        uc.reg_write(UC_ARM_REG_PC, lr & ~1)
        cpsr = uc.reg_read(UC_ARM_REG_CPSR)
        if lr & 1:
            uc.reg_write(UC_ARM_REG_CPSR, cpsr | (1 << 5))

    def _hook_get_part_info(self, uc):
        """FUN_08033ee8 - get partition info. Fill output buffer.
        param_1 (r0) = device handle ptr
        param_2 (r1) = output buffer (0x40 bytes)
        Returns 0 on success.
        Output buffer layout:
          [0x00] (byte)  = card type (2 = eMMC)
          [0x04] (uint)  = total sectors
          [0x08] (uint)  = sector size
          [0x0c] (uint)  = sector multiplier
          [0x10] (byte)  = something
          [0x14] (uint)  = something
          [0x18] (byte)  = secure flag
          [0x1c] (uint)  = num_partitions (becomes local_34 in FUN_08038206)
          [0x20] (uint)  = something
          [0x24] (byte)  = write-protect byte
        """
        r1 = uc.reg_read(UC_ARM_REG_R1)
        # Zero-fill output
        uc.mem_write(r1, b'\x00' * 0x40)
        # Card type = eMMC
        self._write_u8(r1 + 0x00, 0x02)
        # Total sectors (large number)
        self._write_u32(r1 + 0x04, 0x00E90000)  # ~7.4 GB
        # Sector size
        self._write_u32(r1 + 0x08, 0x200)
        # Sector multiplier
        self._write_u32(r1 + 0x0c, 1)
        # Num partitions (must be > partition_number)
        self._write_u32(r1 + 0x1c, 8)
        # Write-protect = 0 (off)
        self._write_u8(r1 + 0x24, 0)

        self.trace.log("PART_INFO", f"Filled partition info at 0x{r1:08x}")
        self._do_return(uc, 0)  # success

    def _hook_strlen(self, uc):
        """strlen implementation."""
        r0 = uc.reg_read(UC_ARM_REG_R0)
        s = self._read_cstring(r0, 1024)
        self._do_return(uc, len(s))

    def _hook_vsnprintf(self, uc):
        """FUN_08006418 - vsnprintf(buf, size, fmt, va_list).
        Simplified: just copy fmt string to buf."""
        r0 = uc.reg_read(UC_ARM_REG_R0)  # buf
        r1 = uc.reg_read(UC_ARM_REG_R1)  # size
        r2 = uc.reg_read(UC_ARM_REG_R2)  # fmt
        # r3 = va_list pointer
        fmt = self._read_cstring(r2, r1)
        # Write fmt to buf (simplified - no format substitution)
        data = fmt.encode('ascii', errors='replace')[:r1-1] + b'\x00'
        try:
            uc.mem_write(r0, data)
        except UcError:
            pass
        self._do_return(uc, len(data) - 1)

    def _hook_snprintf(self, uc):
        """FUN_0800644c - snprintf(buf, size, fmt, ...).
        Simplified: just copy fmt string to buf."""
        r0 = uc.reg_read(UC_ARM_REG_R0)
        r1 = uc.reg_read(UC_ARM_REG_R1)
        r2 = uc.reg_read(UC_ARM_REG_R2)
        fmt = self._read_cstring(r2, r1)
        data = fmt.encode('ascii', errors='replace')[:r1-1] + b'\x00'
        try:
            uc.mem_write(r0, data)
        except UcError:
            pass
        self._do_return(uc, len(data) - 1)

    def _hook_memcmp(self, uc):
        """memcmp(a, b, n)."""
        r0 = uc.reg_read(UC_ARM_REG_R0)
        r1 = uc.reg_read(UC_ARM_REG_R1)
        r2 = uc.reg_read(UC_ARM_REG_R2)
        try:
            a = bytes(uc.mem_read(r0, r2))
            b = bytes(uc.mem_read(r1, r2))
            if a < b:
                self._do_return(uc, 0xffffffff)  # -1
            elif a > b:
                self._do_return(uc, 1)
            else:
                self._do_return(uc, 0)
        except UcError:
            self._do_return(uc, 0)

    def _hook_memcpy(self, uc):
        """memcpy(dst, src, n)."""
        r0 = uc.reg_read(UC_ARM_REG_R0)
        r1 = uc.reg_read(UC_ARM_REG_R1)
        r2 = uc.reg_read(UC_ARM_REG_R2)
        try:
            data = bytes(uc.mem_read(r1, r2))
            uc.mem_write(r0, data)
        except UcError:
            pass
        self._do_return(uc, r0)

    def _hook_divmod64(self, uc):
        """FUN_080060c0 - 64-bit divide. Returns quotient in r0:r1."""
        # Called as FUN_080060c0(dividend_lo, dividend_hi, divisor_lo, divisor_hi)
        r0 = uc.reg_read(UC_ARM_REG_R0)
        r1 = uc.reg_read(UC_ARM_REG_R1)
        r2 = uc.reg_read(UC_ARM_REG_R2)
        r3 = uc.reg_read(UC_ARM_REG_R3)
        dividend = r0 | (r1 << 32)
        divisor = r2 | (r3 << 32)
        if divisor == 0:
            self._do_return(uc, 0)
            return
        quotient = dividend // divisor
        remainder = dividend % divisor
        uc.reg_write(UC_ARM_REG_R0, quotient & 0xffffffff)
        uc.reg_write(UC_ARM_REG_R1, (quotient >> 32) & 0xffffffff)
        uc.reg_write(UC_ARM_REG_R2, remainder & 0xffffffff)
        uc.reg_write(UC_ARM_REG_R3, (remainder >> 32) & 0xffffffff)
        lr = uc.reg_read(UC_ARM_REG_LR)
        uc.reg_write(UC_ARM_REG_PC, lr & ~1)
        cpsr = uc.reg_read(UC_ARM_REG_CPSR)
        if lr & 1:
            uc.reg_write(UC_ARM_REG_CPSR, cpsr | (1 << 5))

    def _hook_parse_sector(self, uc):
        """FUN_08028c10 - parse sector number from string buffer.
        r0 = string buffer ptr
        r1 = (unused)
        r2 = buffer size (0x40)
        r3 = 0
        [sp+0] = output pointer for 64-bit parsed value

        Parses string to integer, writes 64-bit result to output ptr.
        Returns 1 on success, 0 on failure.
        """
        r0 = uc.reg_read(UC_ARM_REG_R0)  # string buffer
        sp = uc.reg_read(UC_ARM_REG_SP)

        # Read output pointer from stack (5th arg)
        out_ptr = self._read_u32(sp)

        # Read the string to parse
        s = self._read_cstring(r0)
        try:
            val = int(s)
        except ValueError:
            val = 0
            self.trace.log("PARSE_SECT", f"'{s}' -> FAIL")
            self._do_return(uc, 0)
            return

        # Write 64-bit value to output pointer
        self._write_u32(out_ptr, val & 0xffffffff)
        self._write_u32(out_ptr + 4, (val >> 32) & 0xffffffff)

        self.trace.log("PARSE_SECT", f"'{s}' -> {val} (stored at 0x{out_ptr:08x})")
        self._do_return(uc, 1)

    def _hook_parse_int(self, uc):
        """FUN_0803823e - parse integer from string.
        r0 = string buffer, r1 = success flag ptr
        Returns parsed uint in r0, writes success byte to *r1."""
        r0 = uc.reg_read(UC_ARM_REG_R0)
        r1 = uc.reg_read(UC_ARM_REG_R1)
        s = self._read_cstring(r0)
        try:
            val = int(s)
            if r1:
                self._write_u8(r1, 1)  # success
            self.trace.log("PARSE_INT", f"'{s}' -> {val}")
            self._do_return(uc, val & 0xffffffff)
        except (ValueError, OverflowError):
            if r1:
                self._write_u8(r1, 0)  # failure
            self.trace.log("PARSE_INT", f"'{s}' -> FAIL")
            self._do_return(uc, 0)

    def _format_log(self, fmt, r1, r2, r3):
        """Best-effort printf-style format with available register args."""
        args = [r1, r2, r3]
        result = []
        i = 0
        arg_idx = 0
        while i < len(fmt):
            if fmt[i] == '%' and i + 1 < len(fmt):
                i += 1
                # Skip flags/width
                while i < len(fmt) and fmt[i] in '0123456789-+ #l':
                    i += 1
                if i < len(fmt):
                    spec = fmt[i]
                    if spec == 'd' or spec == 'i':
                        if arg_idx < len(args):
                            val = args[arg_idx]
                            # Sign-extend 32-bit
                            if val >= 0x80000000:
                                val -= 0x100000000
                            result.append(str(val))
                            arg_idx += 1
                        else:
                            result.append('%d')
                    elif spec == 'u':
                        if arg_idx < len(args):
                            result.append(str(args[arg_idx]))
                            arg_idx += 1
                        else:
                            result.append('%u')
                    elif spec == 'x' or spec == 'X':
                        if arg_idx < len(args):
                            result.append(f"0x{args[arg_idx]:x}")
                            arg_idx += 1
                        else:
                            result.append('%x')
                    elif spec == 's':
                        if arg_idx < len(args):
                            result.append(self._read_cstring(args[arg_idx]))
                            arg_idx += 1
                        else:
                            result.append('%s')
                    elif spec == '%':
                        result.append('%')
                    else:
                        # Unknown spec, just show raw
                        result.append(f'%{spec}')
                        if arg_idx < len(args):
                            arg_idx += 1
                    i += 1
            else:
                result.append(fmt[i])
                i += 1
        return ''.join(result)

    # -- State setup ---------------------------------------------------------

    def _setup_ctype_table(self):
        """Set up the C library ctype character classification table.
        FUN_08006e98 returns ptr at 0x0805a898.
        FUN_080060b0 returns 0x0805a898 + 4 = 0x0805a89c.
        Code then does: ldr r0, [r0] -> loads *0x0805a89c -> table base
        Then: ldrb r0, [table_base, char] -> classification byte

        The table is 256 bytes, indexed by character value.
        Bit 0 (0x01) = space/whitespace (checked by lsls r0, r0, #0x1f -> tests bit 0)
        """
        CTYPE_TABLE = 0x80130000  # put table in scratch RAM
        self._map_range(CTYPE_TABLE, 0x200)

        # Build ctype table. The XML parser uses these bit tests:
        #   bit 0 (0x01) = isspace (tested via lsls r0, r0, #0x1f)
        #   bits 3-5 (0x38) = valid XML name char (letter/digit/underscore)
        #     tested via tst.w r0, #0x38
        #   bits 3,4,7 (0x98) = tested in state 3 (tst.w r0, #0x98)
        #     likely: isalnum + special chars for text content
        table = bytearray(256)
        for c in b' \t\n\r\x0b\x0c':
            table[c] = 0x01  # space
        for c in range(ord('a'), ord('z') + 1):
            table[c] = 0x08 | 0x80  # alpha (bit 3 + bit 7)
        for c in range(ord('A'), ord('Z') + 1):
            table[c] = 0x08 | 0x80  # alpha
        for c in range(ord('0'), ord('9') + 1):
            table[c] = 0x10 | 0x80  # digit (bit 4 + bit 7)
        table[ord('_')] = 0x20 | 0x80  # underscore (bit 5)
        table[ord('-')] = 0x20  # hyphen
        table[ord('.')] = 0x20  # dot
        table[ord(':')] = 0x20  # colon (XML namespace)
        self.uc.mem_write(CTYPE_TABLE, bytes(table))

        # 0x0805a89c (= 0x0805a898 + 4) must point to our table
        # FUN_080060b0: returns 0x0805a898 + 4, then code does ldr r0, [r0]
        self._write_u32(0x0805a89c, CTYPE_TABLE)

    def setup_globals(self):
        """Pre-populate global state the program handler expects."""
        self._setup_ctype_table()

        # Stack canary - read from the data section (should be 0x00040a0d)
        canary = self._read_u32(ADDR_STACK_CANARY)
        if canary == 0:
            # If BSS, set a known value
            canary = 0x00040a0d
            self._write_u32(ADDR_STACK_CANARY, canary)
        if self.verbose:
            print(f"[emu] Stack canary: 0x{canary:08x}")

        # Sector size
        self._write_u32(ADDR_SECTOR_SZ, 0x200)
        self._write_u32(ADDR_SECTOR_SZ_HI, 0)

        # Max sectors (generous limit)
        self._write_u32(ADDR_MAX_SECT_LO, 0x100000)
        self._write_u32(ADDR_MAX_SECT_HI, 0)

        # Flags
        self._write_u8(ADDR_SKIP_WRITE, 0)
        self._write_u8(ADDR_ACK_RAW, 0)
        self._write_u8(ADDR_VERBOSE, 1)  # enable verbose for more trace
        self._write_u32(ADDR_ACK_EVERY, 0)
        self._write_u8(ADDR_VALIDATION, 0)

        # USB DMA buffer base
        self._write_u32(ADDR_USB_DMA_BASE, 0x80000000)
        self._write_u32(ADDR_USB_RX_BUF, 0x80200000)

        # Context struct - set validation mode byte to 0
        # DAT_08055e90 + 0x148 = validation mode byte
        self._write_u8(ADDR_CONTEXT + 0x148, 0)

        # Setup fake storage device structure
        self._setup_storage_device()

        # Setup fake XML writer buffer
        self._map_range(FAKE_XML_WR_BUF, 0x10000)
        self._write_u32(ADDR_XML_WRITER, FAKE_XML_WR_BUF)

    def _setup_storage_device(self):
        """Set up fake storage device at DAT_08058430.
        Layout:
          +0x00: type byte (0 = eMMC)
          +0x04: handlers[0] - device handle for partition 0
          +0x08: handlers[1]
          ...
          +0x24: storage_type (short)
          +0x26: selected_partition (byte) - init to 0xff (invalid)
          +0x28: sector_size
        """
        # Map fake card info area
        self._map_range(FAKE_CARD_INFO, 0x200)
        self._map_range(FAKE_EXT_CSD, 0x200)

        # Fake card info structure (what *device_handle points to)
        # puVar3 = (uint*)*device_handle
        # puVar3[0] = device_id, puVar3[2] = card_type, puVar3[9] = sector_mult
        # puVar3[0x24] + 0xa0 = write-protect byte
        self._write_u32(FAKE_CARD_INFO + 0x00, 0)       # device id
        self._write_u32(FAKE_CARD_INFO + 0x04, 0)
        self._write_u32(FAKE_CARD_INFO + 0x08, 0x02)    # card type = eMMC (byte at puVar3[2])
        self._write_u32(FAKE_CARD_INFO + 0x24, 1)       # sector multiplier at [9]
        # puVar3[7] = total sectors for non-eMMC path
        self._write_u32(FAKE_CARD_INFO + 0x1c, 0xFFFFFF)
        # puVar3[8] = sector size
        self._write_u32(FAKE_CARD_INFO + 0x20, 0x200)
        # puVar3[0xb] = something
        self._write_u32(FAKE_CARD_INFO + 0x2c, 0)
        # puVar3[0xd] = number of partitions (used in FUN_08038206 as local_34)
        self._write_u32(FAKE_CARD_INFO + 0x34, 8)
        # puVar3[0x18] = something
        self._write_u32(FAKE_CARD_INFO + 0x60, 0)

        # EXT_CSD: write-protect byte at offset 0xa0 = 0 (WP off)
        self._write_u8(FAKE_EXT_CSD + 0xa0, 0)

        # puVar3[0x24] (offset 0x90 in card info) = pointer to ext_csd
        self._write_u32(FAKE_CARD_INFO + 0x90, FAKE_EXT_CSD)

        # Storage device struct at DAT_08058430:
        #   +0x00: type (byte)
        self._write_u8(ADDR_STORAGE_DEV + 0x00, 0)

        #   +0x04: handlers[0..7] - each is a pointer to a device handle
        # The handler chain: FUN_080381d8 reads *(int*)(param_1 + slot*4 + 4)
        # which should be a device handle ptr.
        # FUN_08033ee8 dereferences: puVar3 = (uint*)*param_1  where param_1 = handler ptr
        # So handler[slot] -> points to a struct whose first word points to card_info.
        # Let's put the handler struct at FAKE_CARD_INFO - 4:
        # Actually, the handler IS FAKE_CARD_INFO itself in the simplest case.
        # FUN_08033ee8(*(undefined4 *)(param_1 + 4), ...) - passes handlers[0]
        # Then: puVar3 = (uint *)*param_1 -- dereferences the handler to get card ptr
        # So handlers[0] must point to a location whose first word points to FAKE_CARD_INFO.

        # Create indirection: handlers[0] -> FAKE_USB_BUF, *FAKE_USB_BUF -> FAKE_CARD_INFO
        self._write_u32(FAKE_USB_BUF, FAKE_CARD_INFO)     # first word = ptr to card info
        self._write_u32(FAKE_USB_BUF + 4, 0)              # second word (partition index?)

        for slot in range(8):
            self._write_u32(ADDR_STORAGE_DEV + 4 + slot * 4, FAKE_USB_BUF)

        #   +0x24: storage_type
        self._write_u32(ADDR_STORAGE_DEV + 0x24, 0x02)  # eMMC

        #   +0x26: selected_partition (byte)
        self._write_u8(ADDR_STORAGE_DEV + 0x26, 0xFF)   # invalid until set by FUN_08038206

        #   +0x28: sector_size
        self._write_u32(ADDR_STORAGE_DEV + 0x28, 0x200)
        self._write_u32(ADDR_STORAGE_DEV + 0x2c, 0)

    def setup_xml(self, xml_bytes):
        """Write XML into Unicorn memory and initialize the parser."""
        self._map_range(FAKE_XML_BUF, 0x1000)
        self.uc.mem_write(FAKE_XML_BUF, xml_bytes + b'\x00')

        # Call FUN_08039030(&DAT_08055ea0, FAKE_XML_BUF, len, 0)
        # to initialize the parser state.
        # We do this by directly writing the struct fields:
        xml_len = len(xml_bytes)
        self._write_u32(ADDR_XML_PARSER + 0x00, FAKE_XML_BUF)  # buf_ptr
        self._write_u32(ADDR_XML_PARSER + 0x04, 0)              # padding
        self._write_u32(ADDR_XML_PARSER + 0x08, xml_len)        # buf_len_lo
        self._write_u32(ADDR_XML_PARSER + 0x0c, 0)              # buf_len_hi
        self._write_u8(ADDR_XML_PARSER + 0x10, 0)               # state = 0
        self._write_u32(ADDR_XML_PARSER + 0x14, 0)              # padding
        self._write_u32(ADDR_XML_PARSER + 0x18, 0)              # pos_lo
        self._write_u32(ADDR_XML_PARSER + 0x1c, 0)              # pos_hi
        self._write_u32(ADDR_XML_PARSER + 0x20, 0)              # depth_lo
        self._write_u32(ADDR_XML_PARSER + 0x24, 0)              # depth_hi

        if self.verbose:
            print(f"[emu] XML ({xml_len} bytes) at 0x{FAKE_XML_BUF:08x}")

    def setup_sector_data(self, num_sectors, sector_size=0x200):
        """Prepare fake sector data for USB reads."""
        self.num_sectors = num_sectors
        self.sector_data_size = min(num_sectors * sector_size, 0x100000)  # max 1MB per read
        self.total_bytes = num_sectors * sector_size
        self.bytes_delivered = 0
        self.usb_read_count = 0

        # Map and fill fake sector data
        self._map_range(FAKE_SECTOR_DATA, self.sector_data_size + 0x1000)
        # Fill with pattern
        pattern = b'\xAA' * self.sector_data_size
        self.uc.mem_write(FAKE_SECTOR_DATA, pattern)

    # -- Execution -----------------------------------------------------------

    def call_dispatcher(self):
        """Call FUN_0802f130() - the XML command dispatcher.
        This parses the next XML token and dispatches to the appropriate handler.
        """
        self.trace.log("EMU", "Calling FUN_0802f130 (dispatcher)")

        # Set LR to return sentinel (with Thumb bit set)
        self.uc.reg_write(UC_ARM_REG_LR, RETURN_ADDR | 1)

        # Ensure CPSR has Thumb bit set
        cpsr = self.uc.reg_read(UC_ARM_REG_CPSR)
        self.uc.reg_write(UC_ARM_REG_CPSR, cpsr | (1 << 5))

        # Reset SP for each call
        self.uc.reg_write(UC_ARM_REG_SP, STACK_TOP - 0x100)

        try:
            # emu_start with addr|1 to indicate Thumb mode
            self.uc.emu_start(FN_DISPATCHER | 1, RETURN_ADDR, timeout=10_000_000, count=0)
        except UcError as e:
            pc = self.uc.reg_read(UC_ARM_REG_PC)
            self.trace.log("EMU_ERR", f"{e} at PC=0x{pc:08x}")

        r0 = self.uc.reg_read(UC_ARM_REG_R0)
        self.trace.log("EMU", f"Dispatcher returned {r0}")
        return r0

    def run_program_test(self, start_sector, num_sectors, partition=0, sector_size=512):
        """Run a full <program> command test.

        Args:
            start_sector: LBA start sector
            num_sectors: number of sectors to write
            partition: physical partition number
            sector_size: bytes per sector (default 512)
        """
        self.trace = TraceLog(self.verbose)

        print(f"\n{'='*70}")
        print(f"Testing <program> write: partition={partition}, "
              f"start_sector={start_sector}, num_sectors={num_sectors}")
        print(f"{'='*70}")

        # Reset state
        self.setup_globals()

        # Build XML payload
        # The real firehose protocol sends individual XML commands.
        # The outer loop (FUN_08030fa8) calls the dispatcher once per
        # top-level tag. We skip <?xml?> and <data> wrappers.
        xml = (
            f'<program SECTOR_SIZE_IN_BYTES="{sector_size}" '
            f'num_partition_sectors="{num_sectors}" '
            f'physical_partition_number="{partition}" '
            f'start_sector="{start_sector}" />'
        ).encode('ascii')

        self.setup_xml(xml)
        self.setup_sector_data(num_sectors, sector_size)

        # The dispatcher calls FUN_08038db4() which advances the parser.
        # We need to advance past <?xml...?> and <data> first to reach <program>.
        # Instead of manually advancing, let's call the dispatcher in a loop:
        # - First call: sees <?xml...?> processing instruction -> returns
        # - Second call: sees <data> open tag -> unrecognized, ACK
        # - Third call: sees <program> -> dispatches to FUN_08024484

        # Actually, looking at the dispatcher more carefully:
        # FUN_08038db4() is the tokenizer that returns token type.
        # The XML "<?xml...?>" is handled as comments/PIs (type 5 or 0).
        # "<data>" is an open tag (type 1) which won't match "program" ->
        #   falls through to unrecognized tag handler.
        # "<program .../>" is an open tag (type 1) matching "program".
        #
        # But the dispatcher is called by an outer loop (FUN_08030fa8).
        # Let's just call the dispatcher repeatedly until we see the program
        # handler fire or we run out of tokens.

        max_calls = 10
        for i in range(max_calls):
            self.trace.log("EMU", f"--- Dispatcher call #{i+1} ---")
            ret = self.call_dispatcher()
            if ret == 1:
                # Check if we got any WRITE or RESPONSE events
                writes = [e for e in self.trace.events if e[0] == 'WRITE']
                responses = [e for e in self.trace.events if e[0] in ('RESPONSE', 'RESPONSE_W')]
                if writes or any('NAK' in e[1] for e in responses):
                    break
                # ret=1 could mean "continue" or "done"
                # If we see log events, something happened
                recent_logs = [e for e in self.trace.events if e[0] == 'LOG' and
                               'Ignoring unrecognized' not in e[1] and
                               'Invalid physical' in e[1]]
                if recent_logs:
                    break
            elif ret == 0:
                # Error or done
                break

        # Print summary
        print(f"\n--- Trace Summary ---")
        writes = [e for e in self.trace.events if e[0] == 'WRITE']
        reads = [e for e in self.trace.events if e[0] == 'READ']
        responses = [e for e in self.trace.events if e[0] in ('RESPONSE', 'RESPONSE_W')]
        logs = [e for e in self.trace.events if e[0] == 'LOG']
        debugs = [e for e in self.trace.events if e[0] == 'DEBUG']
        usb_reads = [e for e in self.trace.events if e[0] == 'USB_READ']
        errors = [e for e in self.trace.events if e[0] == 'EMU_ERR']

        print(f"  Writes attempted: {len(writes)}")
        for _, msg in writes:
            print(f"    {msg}")
        print(f"  Reads (verify):   {len(reads)}")
        print(f"  USB reads:        {len(usb_reads)}")
        print(f"  Responses:        {len(responses)}")
        for _, msg in responses:
            print(f"    {msg}")
        print(f"  Log messages:     {len(logs)}")
        for _, msg in logs:
            print(f"    {msg}")
        if debugs:
            print(f"  Debug messages:   {len(debugs)}")
            for _, msg in debugs:
                print(f"    {msg}")
        if errors:
            print(f"  Errors:           {len(errors)}")
            for _, msg in errors:
                print(f"    {msg}")

        return self.trace


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(
        description='Unicorn Engine harness for Firehose programmer')
    parser.add_argument('--start-sector', type=int, default=2663442,
                        help='Start sector LBA (default: 2663442 = splash)')
    parser.add_argument('--num-sectors', type=int, default=2048,
                        help='Number of sectors (default: 2048)')
    parser.add_argument('--partition', type=int, default=0,
                        help='Physical partition number (default: 0)')
    parser.add_argument('--verbose', '-v', action='store_true',
                        help='Verbose trace output')
    parser.add_argument('--compare', action='store_true',
                        help='Compare splash vs aboot writes')
    args = parser.parse_args()

    if args.compare:
        # Compare partition 0 (allowed) vs partition 3 (blocked)
        print("=" * 70)
        print("COMPARISON: partition 0 (allowed) vs partition 3 (aboot, restricted)")
        print("=" * 70)

        emu = FHProgramEmulator(verbose=args.verbose)

        # Partition 0: should succeed
        p0_trace = emu.run_program_test(
            start_sector=2663442, num_sectors=2048, partition=0)

        # Re-create emulator for clean state
        emu = FHProgramEmulator(verbose=args.verbose)

        # Partition 3: should be blocked by FUN_08038206
        p3_trace = emu.run_program_test(
            start_sector=2663442, num_sectors=2048, partition=3)

        print(f"\n{'='*70}")
        print("COMPARISON RESULT")
        print(f"{'='*70}")

        def trace_summary(name, trace):
            writes = [e for e in trace.events if e[0] == 'WRITE']
            naks = [e for e in trace.events
                    if e[0] in ('RESPONSE', 'RESPONSE_W') and 'NAK' in e[1]]
            acks = [e for e in trace.events
                    if e[0] in ('RESPONSE', 'RESPONSE_W') and 'ACK' in e[1]]
            part_sel = [e for e in trace.events if e[0] == 'PART_SEL']
            logs = [e for e in trace.events if e[0] == 'LOG']
            print(f"\n  {name}:")
            print(f"    Partition gate: {part_sel[0][1] if part_sel else 'not reached'}")
            print(f"    Writes: {len(writes)}, ACKs: {len(acks)}, NAKs: {len(naks)}")
            for _, msg in logs:
                print(f"    Log: {msg}")

        trace_summary("Partition 0 (normal)", p0_trace)
        trace_summary("Partition 3 (aboot)", p3_trace)

        p0_writes = [e for e in p0_trace.events if e[0] == 'WRITE']
        p3_writes = [e for e in p3_trace.events if e[0] == 'WRITE']
        p3_blocked = [e for e in p3_trace.events if e[0] == 'PART_SEL' and 'BLOCKED' in e[1]]

        if len(p0_writes) > 0 and p3_blocked:
            print(f"\n  CONFIRMED: FUN_08038206 at 0x08038206 blocks partition 3 writes.")
            print(f"  The check is: (param_2 != 3) in the partition selector.")
            print(f"  Patch target: remove the partition 3 exclusion in FUN_08038206.")
        elif len(p0_writes) > 0 and len(p3_writes) > 0:
            print(f"\n  Both partitions write. Filtering is deeper.")
        else:
            print(f"\n  Unexpected result. Check harness setup.")
    else:
        emu = FHProgramEmulator(verbose=args.verbose)
        emu.run_program_test(
            start_sector=args.start_sector,
            num_sectors=args.num_sectors,
            partition=args.partition)


if __name__ == '__main__':
    main()
