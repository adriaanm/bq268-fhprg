#!/usr/bin/env python3
"""
Unicorn Engine emulator for the original firehose programmer (fhprg_peek.bin)
init sequence, to compare against the minimal programmer's boot flow.

Loads fhprg_peek.bin ELF, starts at processEntry_entry (0x08008780) in ARM
mode, and traces through the init sequence:
  processEntry_entry → FUN_08031f88 (sbl1_mc) → sbl1_hw_init (DDR) →
  boot_qsee_exec → sbl1_main_ctl → firehose_dispatch

Symbols loaded from tmp/fhprg_syms.txt (no .symtab in stripped ELF).
DDR blob calls are skipped (same approach as minimal_init_emu.py).
Complex subsystem init functions (DAL, PMIC, TSENS, etc.) are stubbed.

Usage:
    python3 tools/fhprg_init_emu.py [--trace] [--calls] [--mmio] [fhprg_peek.bin]
"""

import argparse
import struct
import sys

from unicorn import *
from unicorn.arm_const import *
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB, CS_MODE_ARM
from elftools.elf.elffile import ELFFile

# ---------------------------------------------------------------------------
# Memory regions (from fhprg_peek.bin ELF program headers)
# ---------------------------------------------------------------------------
RAM_REGIONS = {
    'NULL_PAGE':  (0x00000000,  0x4000),   # NULL page (catch null derefs gracefully)
    'IMEM_CODE':  (0x00220000,  0x3000),   # DDR blob code
    'IMEM_DATA':  (0x00223000,  0x1000),   # DDR blob data
    'CODE':       (0x08006000,  0x40000),  # main code (up to 0x08046000)
    'CODE_BSS':   (0x08046000,  0x6000),   # CODE BSS (stack lives here)
    'DATA':       (0x0804C000,  0x11000),  # initialized data + BSS
    'SCRATCH':    (0x80000000,  0x202000), # USB/heap scratch RAM
    'SYS_IMEM':   (0x08600000,  0x100000), # system IMEM (DDR config + hash)
    'DDR_HIGH':   (0x87C00000,  0x400000), # QSEE/TZ region
    'DDR_HIGH2':  (0x87800000,  0x400000), # QSEE extended
}

# MMIO regions — mapped with mmio_map, read/write callbacks
MMIO_REGIONS = {
    'TLMM':       (0x01000000,  0x100000),  # GPIO
    'GCC':        (0x01800000,  0x80000),   # clock control
    'TIMETICK':   (0x004A0000,  0xC000),    # sleep timetick + PSHOLD
    'BIMC_QOS':   (0x00400000,  0x60000),   # BIMC bus arb
    'USB':        (0x078D9000,  0x1000),    # USB controller (CI13xxx)
    'SDCC':       (0x07800000,  0xD9000),   # eMMC SDCC (below USB region)
    'TCSR':       (0x01900000,  0x80000),   # TCSR misc
    'MPM':        (0x00004000,  0x4000),    # MPM2
    'SPMI':       (0x02000000,  0x100000),  # SPMI (PMIC bus)
    'CRYPTO':     (0x00700000,  0x100000),  # crypto engine
    'QTIMER':     (0x00200000,  0x10000),   # QTimer (arch timer)
    'APCS':       (0x0B000000,  0x100000),  # APCS (CPU subsys)
    'RPM_MSG':    (0x00060000,  0x10000),   # RPM message RAM
    'SECURITY':   (0x000A0000,  0x10000),   # security control
    'PRNG':       (0x00022000,  0x1000),   # PRNG FIFO (hw rng for stack canary)
}

# Entry point
ENTRY_ADDR = 0x08008780

# Key addresses
PSHOLD_ADDR     = 0x004AB000
TIMETICK_ADDR   = 0x004A3000
GPLL0_MODE      = 0x01821000
GPLL0_STATUS    = 0x01821024
APCS_GPLL_VOTE  = 0x01845000

# Target milestone addresses (resolved from syms)
TARGET_ADDRS = {}

# GPIO
TLMM_BASE = 0x01000000

# GCC CBCR registers (auto-clear bit 31 on enable)
GCC_CBCR_ADDRS = set()

# GCC CMD_RCGR registers (auto-clear bit 0 on update)
GCC_CMD_RCGR_ADDRS = set()

# DDR blob address range
DDR_BLOB_BASE = 0x00220000
DDR_BLOB_END  = 0x00224000

# All DDR blob entry points that should be skipped
DDR_BLOB_SKIP = {
    0x00222780: "ddr_set_params",
    0x002224cc: "ddr_init",
    0x00222248: "ddr_geometry_query",
    0x002225e4: "FUN_002225e4",
    0x002225f4: "FUN_002225f4",
    0x00222650: "FUN_00222650",
    0x00222680: "FUN_00222680",
    0x00222684: "FUN_00222684",
    0x00222088: "FUN_00222088",
    0x002223bc: "FUN_002223bc",
    0x00222448: "FUN_00222448",
}

# Functions to stub out (return 0 or 1 as specified)
# These access complex hardware subsystems we can't emulate
STUB_FUNCTIONS = {
    # (address, return_value, name)
}


def load_syms(path):
    """Load symbol table from fhprg_syms.txt format: 'addr T name'."""
    syms = {}
    addr_to_sym = {}
    try:
        with open(path) as f:
            for line in f:
                parts = line.strip().split()
                if len(parts) >= 3:
                    addr = int(parts[0], 16)
                    name = parts[2]
                    syms[name] = addr
                    addr_to_sym[addr] = name
    except FileNotFoundError:
        print(f"  [warn] Symbol file not found: {path}")
    return syms, addr_to_sym


class MmioState:
    """Track MMIO register state and simulate hardware behavior."""

    def __init__(self):
        self.regs = {}
        self.timetick = 0
        self.qtimer = 0
        self.prng_counter = 0x00040A0D  # stack canary seed

    def read(self, addr, size):
        # Sleep timetick — return incrementing counter
        if addr == TIMETICK_ADDR:
            self.timetick += 20000
            return self.timetick

        # PRNG FIFO — stack canary reads from 0x00022000 + status at 0x00022004
        if addr == 0x00022004:
            return 1  # FIFO ready (bit 0 set)
        if addr == 0x00022000:
            self.prng_counter = (self.prng_counter * 1103515245 + 12345) & 0xFFFFFFFF
            return self.prng_counter

        # QTimer — incrementing counter
        if 0x00200000 <= addr < 0x00210000:
            self.qtimer += 1000
            return self.qtimer

        # GPLL0 MODE/STATUS — return lock bit set
        if addr in (GPLL0_MODE, GPLL0_STATUS):
            return self.regs.get(addr, 0) | (1 << 30)

        # Any PLL MODE register in GCC range — set lock bits
        if 0x01820000 <= addr < 0x01870000:
            offset = addr & 0xFFF
            if offset == 0x000:  # *_MODE
                return self.regs.get(addr, 0) | (1 << 31) | (1 << 30)
            if offset == 0x024:  # *_STATUS
                return self.regs.get(addr, 0) | (1 << 30)

        # USB GCC CBCR registers — specific addresses
        if addr in (0x01841000, 0x01841004, 0x01841008, 0x01841030,
                     0x01841034, 0x0184103C):
            val = self.regs.get(addr, (1 << 31))
            if val & 1:
                val &= ~(1 << 31)
            return val

        # USB GCC CMD_RCGR — clear update bit 0
        if addr == 0x01841010:
            return self.regs.get(addr, 0) & ~1

        # CBCR registers — clear bit 31 (CLK_OFF) when bit 0 (enable) is set
        if 0x01800000 <= addr < 0x01880000:
            offset = addr & 0xFFF
            if offset in (0x008, 0x00C, 0x010, 0x014, 0x018, 0x01C, 0x020, 0x024):
                val = self.regs.get(addr, (1 << 31))
                if val & 1:
                    val &= ~(1 << 31)
                return val
            # CMD_RCGR — clear update bit
            if offset == 0x004:
                return self.regs.get(addr, 0) & ~1

        # GCC_BIMC_MISC (0x01831018) — clear update bit 9
        if addr == 0x01831018:
            return self.regs.get(addr, 0) & ~(1 << 9)

        # BIMC registers — return stored value
        if 0x00400000 <= addr < 0x00460000:
            return self.regs.get(addr, 0)

        # USB controller (CI13xxx) at 0x078D9000
        if 0x078D9000 <= addr < 0x078DA000:
            # ULPI viewport (0x078D9170): clear bit 30 = operation complete
            if addr == 0x078D9170:
                val = self.regs.get(addr, 0)
                return val & ~(1 << 30)
            # PORTSC (0x078D9184): return high-speed connected
            # PSPD bits [27:26] = 10 (high-speed), CCS bit 0 = 1 (connected)
            if addr == 0x078D9184:
                val = self.regs.get(addr, 0)
                return val | (2 << 26) | 1
            # USBSTS (0x078D9144): return idle (no pending interrupts)
            if addr == 0x078D9144:
                return 0
            # USBCMD (0x078D9140): return stored value
            if addr == 0x078D9140:
                return self.regs.get(addr, 0)
            # ENDPOINTLISTADDR (0x078D9158): return stored value
            if addr == 0x078D9158:
                return self.regs.get(addr, 0)
            return self.regs.get(addr, 0)

        # SDCC — basic simulation
        if 0x07800000 <= addr < 0x078D9000:
            offset = addr & 0xFFF
            # MCI_STATUS: ready + no errors
            if offset == 0x034:
                return 0x00000000
            return self.regs.get(addr, 0)

        # TCSR — return stored or 0
        if 0x01900000 <= addr < 0x01980000:
            return self.regs.get(addr, 0)

        # SPMI — return stored or 0
        if 0x02000000 <= addr < 0x02100000:
            return self.regs.get(addr, 0)

        # Security control — return reasonable values
        if 0x000A0000 <= addr < 0x000B0000:
            return self.regs.get(addr, 0)

        # RPM message RAM
        if 0x00060000 <= addr < 0x00070000:
            return self.regs.get(addr, 0)

        # SYSTEM_IMEM special register at 0x08600944 — NOT 0x53444247 ("GBDS")
        # FUN_08031f88 spins: do {} while (_DAT_08600944 == 0x53444247);
        # Return 0 so it exits immediately
        if addr == 0x08600944:
            return 0

        return self.regs.get(addr, 0)

    def write(self, addr, size, value):
        self.regs[addr] = value


class InitEmulator:
    """Unicorn-based emulator for fhprg_peek.bin init sequence."""

    def __init__(self, elf_path, args):
        self.elf_path = elf_path
        self.args = args
        self.symbols = {}
        self.addr_to_sym = {}
        self.mmio = MmioState()
        self.insn_count = 0
        self.max_insns = args.max_insns
        self.led_state = {}
        self.reached_target = False
        self.target_name = None
        self.stop_reason = None
        self.stub_addrs = {}  # addr -> (return_value, name)
        self.func_call_log = []  # track function call sequence

        # Capstone disassemblers
        self.cs_thumb = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
        self.cs_arm = Cs(CS_ARCH_ARM, CS_MODE_ARM)

        # Initialize Unicorn
        self.uc = Uc(UC_ARCH_ARM, UC_MODE_ARM)
        self._load_symbols()
        self._identify_stubs()
        self._map_memory()
        self._load_elf()
        self._patch_stubs()
        self._setup_hooks()

    def _load_symbols(self):
        """Load symbols from fhprg_syms.txt."""
        self.symbols, self.addr_to_sym = load_syms('tmp/fhprg_syms.txt')
        print(f"  Symbols: {len(self.symbols)} from tmp/fhprg_syms.txt")

        # Identify target milestone
        targets = ['sbl1_main_ctl', 'firehose_dispatch']
        for name in targets:
            if name in self.symbols:
                TARGET_ADDRS[name] = self.symbols[name]
        if TARGET_ADDRS:
            print(f"  Milestones: {', '.join(f'{n}=0x{a:08x}' for n, a in TARGET_ADDRS.items())}")

    def _identify_stubs(self):
        """Identify functions that should be stubbed out.

        These are functions that access hardware subsystems we can't emulate
        (PMIC, TSENS, crypto, etc.) or infinite-loop on assert.
        """
        # Functions that need stubbing — return value, and reason.
        # Strategy: stub only leaf functions that touch hardware we can't
        # emulate. Let data structure init, memcpy/memset, and call chain
        # dispatch run natively so the control flow is visible.
        stubs = {
            # Hardware init that needs real peripherals
            'thunk_qtimer_init':       (0, "qtimer init"),
            'thunk_tsens_init':        (0, "thermal sensor"),
            'thunk_pm_device_init_core': (0, "PMIC init"),
            'thunk_FUN_0800d330':      (0, "ICB/DAL attach"),
            'thunk_FUN_0800ac84':      (1, "bimc_clock_init"),
            'thunk_FUN_0800b5e0':      (0, "cache_mmu_init"),
            'thunk_FUN_0800b604':      (0, "cache_enable"),
            'thunk_FUN_0800aa5c':      (0, "clock_post_init"),
            'thunk_FUN_080192b8':      (0, "boot profiler"),
            'thunk_FUN_00220358':      (0, "ddr blob misc"),

            # VFP-using functions (Unicorn doesn't handle vpush/vldr)
            'FUN_08016ebc':            (0, "PBL timestamp log — VFP"),

            # Functions that read from complex peripherals
            'FUN_080089e0':            (0, "early hw id"),
            'FUN_0800a790':            (0, "cache_mmu_init"),
            'FUN_08007ef0':            (0, "watchdog/intr init"),

            # Boot logging (touches DAL timer)
            'FUN_08016c80':            (0, "boot_log_init"),
            'FUN_08016adc':            (0, "boot_log_message"),
            'FUN_08016c94':            (0, "boot_log_delta"),
            'FUN_08016844':            (0, "boot_log_delta_time"),

            # Clock/PMIC init
            'FUN_08016918':            (0, "boot_clock_init"),

            # Flash/storage init
            'FUN_08019200':            (0, "boot_config_data_table"),
            'FUN_08032280':            (0, "sbl1_tlmm_init"),
            'FUN_08032114':            (0, "sbl1_efs_handle_cookies"),
            'FUN_08018dec':            (0, "boot_flash_dev_init"),
            'FUN_08018f7c':            (1, "boot_flash_target_init"),
            'FUN_08019408':            (0, "boot_config_default_tbl"),
            'FUN_08017aa4':            (0, "boot_dload_check"),
            'FUN_08014dbc':            (0, "boot_secure_check"),
            'FUN_080144b4':            (0, "cache_invalidate_region"),
            'FUN_08014480':            (0, "boot_smem_init"),

            # sbl1_hw_init sub-functions that need real HW
            'FUN_08016020':            (1, "get_ddr_param_data"),

            # boot_qsee_exec sub-functions
            'FUN_08007de0':            (0, "boot_shared_info"),

            # sbl1_main_ctl sub-functions (post-DDR)
            'FUN_08019330':            (0, "throughput_log"),
            'FUN_080167dc':            (0, "boot_clock_shutdown"),
            'FUN_08016872':            (0, "boot_smem_store"),
            'FUN_08016874':            (0, "boot_jump_handler"),

            # Error handler — log and continue (don't spin)
            # Note: NOT using stub mechanism — has special handler below

            # DDR post-params (calls DDR blob geometry, needs real DDR)
            'FUN_08031d18':            (0, "ddr_post_params"),

            # DAL device driver lookup (scans huge uninitialized tables)
            'FUN_08010618':            (0xFFFFFFFF, "DAL device lookup"),
            'FUN_08010668':            (0, "DAL device attach"),
            'FUN_080106aa':            (0, "DAL driver init"),

            # Timing
            'FUN_080199b4':            (0, "busywait_us"),
            'FUN_080300bc':            (0, "msleep"),

            # Hash/integrity check (reads entire memory region)
            'FUN_0800d59c':            (0, "hash_calc"),
            'FUN_0800fa46':            (0, "boot_hash_verify"),

            # SDCC/eMMC polling loops (poll HW status bits that never clear)
            'FUN_0800bfac':            (0, "sdcc_irq_clear_poll"),
            'FUN_0800c154':            (0, "sdcc_flag_clear_poll"),
            'FUN_0800a54c':            (1, "sdcc_cmd_submit_poll"),
            # 'FUN_08030528' — ULPI viewport read (un-stubbed)
            # 'FUN_0803056c' — ULPI viewport write (un-stubbed)
            # 'FUN_0803015c' — USB PORTSC speed read (un-stubbed)
            'FUN_0803456c':            (0, "sdcc_cmd_status_poll"),
            'FUN_0800b140':            (1, "cbcr_clock_enable_poll"),

            # eMMC card init — USB-related functions UN-STUBBED for tracing
            # 'FUN_0801aba0' — USB init (un-stubbed)
            # 'FUN_0801ab18' — dQH init (un-stubbed)
            # 'FUN_0801a704' — USB clock gate enable (un-stubbed)
            # 'FUN_0801a728' — USB clock gate disable (un-stubbed)
            # 'FUN_0801a948' — USB endpoint config (un-stubbed)

            # USB enumeration polling (would loop forever without real host)
            'FUN_0802f9ea':            (0, "usb_enum_poll"),

            # Firehose protocol init polling
            'FUN_0802f57c':            (0, "xml_response_poll"),
            'FUN_08030a40':            (0, "device_state_copy"),
            'FUN_08030ac4':            (0, "firehose_ctrl_write"),
            'FUN_08030af4':            (0, "firehose_ctrl_read"),

            # Top-level card/firehose init
            # 'FUN_0803016c' — USB card init toplevel (un-stubbed)
            # 'FUN_08030704' — firehose init wrapper (un-stubbed for USB tracing)
        }

        for name, (retval, reason) in stubs.items():
            if name in self.symbols:
                addr = self.symbols[name]
                self.stub_addrs[addr] = (retval, name, reason)

        # Also stub all thunk_FUN_002xxxxx DDR blob thunks (called via CODE thunks)
        # The CODE-side thunks at 0x08008axx are veneer functions that BLX into IMEM
        # We skip at the IMEM side via DDR_BLOB_SKIP

        if self.stub_addrs:
            print(f"  Stubs: {len(self.stub_addrs)} functions")

    def _map_memory(self):
        """Map RAM with mem_map, MMIO with mmio_map."""
        for name, (base, size) in RAM_REGIONS.items():
            try:
                self.uc.mem_map(base, size, UC_PROT_ALL)
            except UcError as e:
                print(f"  [warn] Failed to map {name} at 0x{base:08x}: {e}")

        for name, (base, size) in MMIO_REGIONS.items():
            try:
                region_base = base
                def make_read(rb):
                    def read_cb(uc, offset, size, user_data):
                        return self._mmio_read_cb(rb + offset, size)
                    return read_cb
                def make_write(rb):
                    def write_cb(uc, offset, size, value, user_data):
                        self._mmio_write_cb(rb + offset, size, value)
                    return write_cb
                self.uc.mmio_map(base, size,
                                 make_read(region_base), None,
                                 make_write(region_base), None)
            except UcError as e:
                print(f"  [warn] Failed to mmio_map {name} at 0x{base:08x}: {e}")

    def _load_elf(self):
        """Load ELF segments."""
        with open(self.elf_path, 'rb') as f:
            elf = ELFFile(f)
            for seg in elf.iter_segments():
                if seg['p_type'] != 'PT_LOAD':
                    continue
                addr = seg['p_vaddr']
                data = seg.data()
                if len(data) == 0:
                    continue
                try:
                    self.uc.mem_write(addr, data)
                    if self.args.verbose:
                        print(f"  [load] 0x{addr:08x} +0x{len(data):x} ({len(data)} bytes)")
                except UcError as e:
                    print(f"  [warn] Failed to write segment at 0x{addr:08x}: {e}")

        self._patch_delay_constants()
        self._patch_spin_loops()

    def _patch_spin_loops(self):
        """Find and NOP all 'b .' (infinite spin) instructions in CODE.

        Qualcomm SBL1 asserts: call error handler, then `b .` forever.
        Replace with NOP (0xBF00 in Thumb) so execution continues.
        """
        code_base = 0x08006000
        code_size = 0x40000
        code = bytes(self.uc.mem_read(code_base, code_size))

        # Thumb: `b .` encodes as 0xE7FE (b #-2, i.e. branch to self)
        pattern = b'\xfe\xe7'
        nop = b'\x00\xbf'  # Thumb NOP
        count = 0
        offset = 0
        while True:
            idx = code.find(pattern, offset)
            if idx < 0:
                break
            # Verify it's at an aligned offset (Thumb = 2-byte aligned)
            if idx % 2 == 0:
                addr = code_base + idx
                self.uc.mem_write(addr, nop)
                count += 1
            offset = idx + 2
        if count > 0:
            print(f"  [patch] Replaced {count} 'b .' spin loops with NOP")

    def _patch_delay_constants(self):
        """Patch delay loop constants to speed up emulation."""
        code_base = 0x08006000
        code_size = 0x40000
        code = bytes(self.uc.mem_read(code_base, code_size))

        patches = {
            0x003D0900: (1, "4000000"),
            0x0BEBC200: (1, "200000000"),
        }

        for pattern, (replacement, desc) in patches.items():
            pattern_bytes = struct.pack('<I', pattern)
            replacement_bytes = struct.pack('<I', replacement)
            offset = 0
            count = 0
            while True:
                idx = code.find(pattern_bytes, offset)
                if idx < 0:
                    break
                addr = code_base + idx
                self.uc.mem_write(addr, replacement_bytes)
                count += 1
                offset = idx + 4
            if count > 0:
                print(f"  [patch] Replaced {count}x {desc} with {replacement}")

        # Also patch IMEM delay constants
        imem_base = 0x00220000
        imem_size = 0x3000
        imem = bytes(self.uc.mem_read(imem_base, imem_size))
        for pattern, (replacement, desc) in patches.items():
            pattern_bytes = struct.pack('<I', pattern)
            replacement_bytes = struct.pack('<I', replacement)
            offset = 0
            count = 0
            while True:
                idx = imem.find(pattern_bytes, offset)
                if idx < 0:
                    break
                addr = imem_base + idx
                self.uc.mem_write(addr, replacement_bytes)
                count += 1
                offset = idx + 4
            if count > 0:
                print(f"  [patch] IMEM: Replaced {count}x {desc} with {replacement}")

    def _patch_stubs(self):
        """Patch stub functions' prologues to 'movs r0, #N; bx lr'.

        More reliable than Unicorn hooks, which can miss some addresses.
        Thumb encodings:
          movs r0, #0  = 0x2000
          movs r0, #1  = 0x2001
          mvns r0, r0  = 0x43C0
          bx lr        = 0x4770
        """
        count = 0
        for addr, (retval, name, reason) in self.stub_addrs.items():
            if retval == 0:
                # movs r0, #0; bx lr
                patch = b'\x00\x20\x70\x47'
            elif retval == 1:
                # movs r0, #1; bx lr
                patch = b'\x01\x20\x70\x47'
            elif retval == 0xFFFFFFFF:
                # movs r0, #0; mvns r0, r0; bx lr
                patch = b'\x00\x20\xc0\x43\x70\x47'
            elif 0 < retval < 256:
                # movs r0, #N; bx lr
                patch = struct.pack('<HH', 0x2000 | retval, 0x4770)
            else:
                # For other values, use movs r0, #0; bx lr (close enough)
                patch = b'\x00\x20\x70\x47'
            try:
                self.uc.mem_write(addr, patch)
                count += 1
            except UcError as e:
                print(f"  [warn] Failed to patch stub {name} at 0x{addr:08x}: {e}")
        print(f"  [patch] Patched {count} stub function prologues")

        # Verify critical stubs
        for name in ('FUN_080199b4', 'FUN_080300bc'):
            if name in self.symbols:
                a = self.symbols[name]
                mem = bytes(self.uc.mem_read(a, 8))
                print(f"  [verify] {name} @ 0x{a:08x}: {mem[:4].hex()} {mem[4:8].hex()}")

    def _sym_at(self, addr):
        """Look up symbol name for an address."""
        addr &= ~1
        name = self.addr_to_sym.get(addr)
        if name:
            return name
        for off in range(1, 5):
            name = self.addr_to_sym.get(addr - off)
            if name:
                return f"{name}+{off}"
        return None

    def _mmio_read_cb(self, addr, size):
        val = self.mmio.read(addr, size)
        if self.args.mmio:
            sym = self._describe_mmio(addr)
            print(f"  [MMIO RD] 0x{addr:08x} ({sym}) = 0x{val:08x}", flush=True)
        return val

    def _mmio_write_cb(self, addr, size, value):
        self.mmio.write(addr, size, value)
        if self.args.mmio:
            sym = self._describe_mmio(addr)
            print(f"  [MMIO WR] 0x{addr:08x} ({sym}) = 0x{value:08x}", flush=True)

        # LED tracking
        gpio_num = (addr - TLMM_BASE) // 0x1000
        gpio_off = (addr - TLMM_BASE) % 0x1000
        if 0 <= gpio_num < 256 and gpio_off == 4:
            on = bool(value & 2)
            prev = self.led_state.get(gpio_num)
            if on != prev:
                self.led_state[gpio_num] = on
                state_str = 'ON' if on else 'OFF'
                print(f"  [LED] GPIO{gpio_num} {state_str}", flush=True)

        # PSHOLD
        if addr == PSHOLD_ADDR:
            print("  [PSHOLD] Reboot triggered — stopping", flush=True)
            self.stop_reason = "PSHOLD reboot"
            self.uc.emu_stop()

    def _describe_mmio(self, addr):
        descs = {
            0x004A3000: "SLEEP_TIMETICK",
            0x004AB000: "PS_HOLD",
            0x01821000: "GPLL0_MODE",
            0x01821024: "GPLL0_STATUS",
            0x01845000: "APCS_GPLL_ENA_VOTE",
            # USB GCC clock registers
            0x01841000: "USB_HS_BCR",
            0x01841004: "USB_HS_SYSTEM_CBCR",
            0x01841008: "USB_HS_AHB_CBCR",
            0x01841010: "USB_HS_SYSTEM_CMD_RCGR",
            0x01841014: "USB_HS_SYSTEM_CFG_RCGR",
            0x01841030: "USB_HS_PHY_CFG_AHB_CBCR",
            0x01841034: "USB2A_PHY_SLEEP_CBCR",
            0x0184103C: "USB2_HS_PHY_ONLY_CBCR",
            # USB controller registers
            0x078D9098: "USB_SBUSCFG",
            0x078D90A0: "USB_AHB_BURST",
            0x078D9140: "USB_USBCMD",
            0x078D9144: "USB_USBSTS",
            0x078D9148: "USB_USBINTR",
            0x078D9158: "USB_ENDPOINTLISTADDR",
            0x078D9170: "USB_ULPI_VIEWPORT",
            0x078D9184: "USB_PORTSC",
            0x078D91A8: "USB_USBMODE",
            0x078D91AC: "USB_ENDPTSETUPSTAT",
            0x078D91C0: "USB_ENDPTCTRL0",
            0x078D91C4: "USB_ENDPTCTRL1",
        }
        if addr in descs:
            return descs[addr]
        gpio_num = (addr - TLMM_BASE) // 0x1000
        gpio_off = (addr - TLMM_BASE) % 0x1000
        if 0 <= gpio_num < 256:
            if gpio_off == 0:
                return f"GPIO{gpio_num}_CFG"
            elif gpio_off == 4:
                return f"GPIO{gpio_num}_IN_OUT"
        return f"0x{addr:08x}"

    def _setup_hooks(self):
        """Install Unicorn hooks."""
        # DDR blob entry point skip hooks
        for addr in DDR_BLOB_SKIP:
            self.uc.hook_add(UC_HOOK_CODE, self._hook_ddr_skip,
                             begin=addr, end=addr + 1)

        # Note: stub functions are patched in _patch_stubs() instead of hooks

        # Error handler hook — log error and return cleanly
        err_handler = self.symbols.get('FUN_08015a80')
        if err_handler:
            self.uc.hook_add(UC_HOOK_CODE, self._hook_error_handler,
                             begin=err_handler, end=err_handler + 1)

        # Full instruction trace
        if self.args.trace:
            self.uc.hook_add(UC_HOOK_CODE, self._hook_code)

        # Interrupt hook
        self.uc.hook_add(UC_HOOK_INTR, self._hook_intr)

        # Invalid memory access
        self.uc.hook_add(UC_HOOK_MEM_UNMAPPED, self._hook_mem_fault)

    def _hook_ddr_skip(self, uc, addr, size, user_data):
        """Skip DDR blob entry points, return success."""
        lr = uc.reg_read(UC_ARM_REG_LR)
        name = DDR_BLOB_SKIP.get(addr, f"0x{addr:08x}")
        print(f"  [DDR SKIP] {name} at 0x{addr:08x} → returning 1 to 0x{lr:08x}", flush=True)
        uc.reg_write(UC_ARM_REG_R0, 1)
        uc.reg_write(UC_ARM_REG_PC, lr & ~1)
        if lr & 1:
            cpsr = uc.reg_read(UC_ARM_REG_CPSR)
            uc.reg_write(UC_ARM_REG_CPSR, cpsr | (1 << 5))

    def _hook_error_handler(self, uc, addr, size, user_data):
        """Hook boot_error_handler (FUN_08015a80) — log error, return to
        caller's caller (skip the assert block + spin loop).

        Error handler signature: FUN_08015a80(filename, line, errcode)
        After this, the calling code does `b .` (spin forever).
        We return from the ERROR HANDLER'S CALLER instead, popping the
        assert block's stack frame entirely.
        """
        # Read error info from registers (r0=filename ptr, r1=line, r2=errcode)
        r0 = uc.reg_read(UC_ARM_REG_R0)
        r1 = uc.reg_read(UC_ARM_REG_R1)
        r2 = uc.reg_read(UC_ARM_REG_R2)

        # Try to read filename string
        filename = ""
        try:
            raw = bytes(uc.mem_read(r0, 40))
            filename = raw.split(b'\x00', 1)[0].decode('ascii', errors='replace')
        except:
            filename = f"0x{r0:08x}"

        if not hasattr(self, '_error_count'):
            self._error_count = 0
        self._error_count += 1

        lr = uc.reg_read(UC_ARM_REG_LR)
        if self._error_count <= 10:
            print(f"  [ASSERT] {filename}:{r1} err=0x{r2:04x} (from 0x{lr:08x})", flush=True)
        elif self._error_count == 11:
            print(f"  [ASSERT] ... suppressing further assert messages", flush=True)

        # Return 0 from error handler
        uc.reg_write(UC_ARM_REG_R0, 0)
        uc.reg_write(UC_ARM_REG_PC, lr & ~1)
        if lr & 1:
            cpsr = uc.reg_read(UC_ARM_REG_CPSR)
            uc.reg_write(UC_ARM_REG_CPSR, cpsr | (1 << 5))

    def _hook_stub(self, uc, addr, size, user_data):
        """Stub out complex hardware init functions."""
        if addr not in self.stub_addrs:
            return
        retval, name, reason = self.stub_addrs[addr]
        lr = uc.reg_read(UC_ARM_REG_LR)
        if not hasattr(self, '_stub_seen'):
            self._stub_seen = {}
        count = self._stub_seen.get(addr, 0) + 1
        self._stub_seen[addr] = count
        if count <= 2 or self.args.verbose:
            print(f"  [STUB] {name} (0x{addr:08x}) → {retval} ({reason})", flush=True)
        uc.reg_write(UC_ARM_REG_R0, retval)
        uc.reg_write(UC_ARM_REG_PC, lr & ~1)
        if lr & 1:
            cpsr = uc.reg_read(UC_ARM_REG_CPSR)
            uc.reg_write(UC_ARM_REG_CPSR, cpsr | (1 << 5))

    def _hook_code(self, uc, addr, size, user_data):
        """Full instruction trace."""
        self.insn_count += 1
        if self.insn_count > self.max_insns:
            self.stop_reason = "instruction limit"
            uc.emu_stop()
            return
        code = uc.mem_read(addr, size)
        cpsr = uc.reg_read(UC_ARM_REG_CPSR)
        thumb = bool(cpsr & (1 << 5))
        cs = self.cs_thumb if thumb else self.cs_arm
        mode = "T" if thumb else "A"
        disasm = ""
        for insn in cs.disasm(bytes(code), addr):
            disasm = f"{insn.mnemonic} {insn.op_str}"
            break
        sym = self._sym_at(addr)
        sym_str = f" <{sym}>" if sym and '+' not in sym else ""
        print(f"  [{mode}] 0x{addr:08x}{sym_str}: {disasm}")

    def _hook_intr(self, uc, intno, user_data):
        if self.args.verbose:
            pc = uc.reg_read(UC_ARM_REG_PC)
            print(f"  [INTR] #{intno} at 0x{pc:08x}")

    def _hook_mem_fault(self, uc, access, addr, size, value, user_data):
        access_type = "READ" if access == UC_MEM_READ_UNMAPPED else "WRITE"
        pc = uc.reg_read(UC_ARM_REG_PC)
        sym = self._sym_at(pc) or ""
        if not hasattr(self, '_fault_count'):
            self._fault_count = 0
        self._fault_count += 1
        if self._fault_count <= 20:
            print(f"  [FAULT] Unmapped {access_type} at 0x{addr:08x} (size={size}) from PC=0x{pc:08x} {sym}")
        elif self._fault_count == 21:
            print(f"  [FAULT] ... suppressing further fault messages")

        # Auto-map 64K page to reduce fragmentation
        page_base = addr & ~0xFFFF
        try:
            self.uc.mem_map(page_base, 0x10000, UC_PROT_ALL)
            return True
        except UcError:
            return False

    def run(self):
        """Run emulation in chunks."""
        print(f"\nStarting emulation at 0x{ENTRY_ADDR:08x} (ARM mode)")
        print(f"  ELF: {self.elf_path}")
        print(f"  Max instructions: {self.max_insns:,}")
        print()

        # Initial register state — processEntry_entry sets its own SP/CPSR
        # but we set reasonable defaults
        self.uc.reg_write(UC_ARM_REG_SP, 0x08048000)
        self.uc.reg_write(UC_ARM_REG_LR, 0)
        # ARM mode, supervisor, IRQs disabled
        self.uc.reg_write(UC_ARM_REG_CPSR, 0x000001D3)

        CHUNK = 100_000
        total_insns = 0
        last_pc = 0
        stuck_count = 0
        last_logged_func = None
        next_pc = ENTRY_ADDR
        is_first = True

        while total_insns < self.max_insns and not self.stop_reason:
            if is_first:
                pc = next_pc
                is_first = False
            else:
                pc = self.uc.reg_read(UC_ARM_REG_PC)

            # Log function entries
            sym = self._sym_at(pc)
            if sym and sym != last_logged_func and '+' not in sym:
                in_blob = DDR_BLOB_BASE <= pc < DDR_BLOB_END
                if in_blob:
                    print(f"  [DDR BLOB] 0x{pc:08x} {sym}", flush=True)
                elif self.args.calls:
                    print(f"  [FUNC] {sym} (0x{pc:08x})", flush=True)
                last_logged_func = sym

                # Track call sequence for milestones
                self.func_call_log.append((total_insns, pc, sym))

            # Check milestones
            for tname, taddr in TARGET_ADDRS.items():
                if pc == taddr and not self.reached_target:
                    self.reached_target = True
                    self.target_name = tname
                    print(f"\n  *** REACHED {tname}() at 0x{pc:08x} after {total_insns:,} instructions ***\n",
                          flush=True)
                    if not self.args.trace:
                        self.stop_reason = f"reached {tname}()"
                        break

            if self.stop_reason:
                break

            # Stuck detection
            if pc == last_pc:
                stuck_count += 1
                if stuck_count > 200:
                    sym = self._sym_at(pc) or "unknown"
                    print(f"\n  [STUCK] PC=0x{pc:08x} ({sym}) for {stuck_count} chunks", flush=True)
                    self._dump_regs()
                    self.stop_reason = f"stuck at 0x{pc:08x}"
                    break
            else:
                stuck_count = 0
            last_pc = pc

            # Determine Thumb/ARM mode
            cpsr = self.uc.reg_read(UC_ARM_REG_CPSR)
            thumb = bool(cpsr & (1 << 5))
            start_addr = pc | (1 if thumb else 0)

            try:
                self.uc.emu_start(start_addr, 0, count=CHUNK)
            except UcError as e:
                pc = self.uc.reg_read(UC_ARM_REG_PC)
                cpsr = self.uc.reg_read(UC_ARM_REG_CPSR)
                sym = self._sym_at(pc) or ""
                print(f"\n  [ERROR] PC=0x{pc:08x} CPSR=0x{cpsr:08x} {sym}: {e}")
                self._dump_regs()
                self.stop_reason = f"error: {e}"
                break

            total_insns += CHUNK

            # Progress
            if total_insns % 1_000_000 == 0:
                pc = self.uc.reg_read(UC_ARM_REG_PC)
                sym = self._sym_at(pc) or ""
                print(f"  [PROGRESS] {total_insns // 1_000_000}M insns, PC=0x{pc:08x} {sym}",
                      flush=True)

        # Summary
        print(f"\n{'='*60}")
        print(f"Emulation complete: ~{total_insns:,} instructions")
        if self.stop_reason:
            print(f"Stop reason: {self.stop_reason}")
        if self.reached_target:
            print(f"Result: SUCCESS — {self.target_name}() was reached")
        else:
            pc = self.uc.reg_read(UC_ARM_REG_PC)
            sym = self._sym_at(pc) or "unknown"
            print(f"Result: STOPPED at 0x{pc:08x} ({sym})")
        print(f"LED state: {self.led_state}")
        print(f"{'='*60}")

        # Print function call trace summary
        if self.func_call_log:
            print(f"\nFunction call trace ({len(self.func_call_log)} entries):")
            for insns, addr, name in self.func_call_log[-40:]:
                marker = ""
                if addr in TARGET_ADDRS.values():
                    marker = " <<<< MILESTONE"
                elif DDR_BLOB_BASE <= addr < DDR_BLOB_END:
                    marker = " [DDR BLOB]"
                print(f"  {insns:>10,} insns  0x{addr:08x}  {name}{marker}")

    def _dump_regs(self):
        regs = [
            ('r0', UC_ARM_REG_R0), ('r1', UC_ARM_REG_R1),
            ('r2', UC_ARM_REG_R2), ('r3', UC_ARM_REG_R3),
            ('r4', UC_ARM_REG_R4), ('r5', UC_ARM_REG_R5),
            ('r6', UC_ARM_REG_R6), ('r7', UC_ARM_REG_R7),
            ('r8', UC_ARM_REG_R8), ('r9', UC_ARM_REG_R9),
            ('r10', UC_ARM_REG_R10), ('r11', UC_ARM_REG_R11),
            ('r12', UC_ARM_REG_R12), ('sp', UC_ARM_REG_SP),
            ('lr', UC_ARM_REG_LR), ('pc', UC_ARM_REG_PC),
        ]
        print("  Registers:")
        for i in range(0, len(regs), 4):
            line = "    "
            for name, reg in regs[i:i+4]:
                val = self.uc.reg_read(reg)
                line += f"{name}=0x{val:08x}  "
            print(line)


def main():
    parser = argparse.ArgumentParser(
        description='fhprg_peek.bin init sequence emulator')
    parser.add_argument('elf', nargs='?', default='fhprg_peek.bin',
                        help='ELF file to load (default: fhprg_peek.bin)')
    parser.add_argument('--trace', action='store_true',
                        help='Full instruction trace')
    parser.add_argument('--calls', action='store_true',
                        help='Log function entries')
    parser.add_argument('--mmio', action='store_true',
                        help='Log MMIO reads/writes')
    parser.add_argument('--verbose', '-v', action='store_true',
                        help='Verbose output')
    parser.add_argument('--max-insns', type=int, default=100_000_000,
                        help='Max instructions (default: 100M)')
    args = parser.parse_args()

    emu = InitEmulator(args.elf, args)
    emu.run()


if __name__ == '__main__':
    main()
