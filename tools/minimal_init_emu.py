#!/usr/bin/env python3
"""
Unicorn Engine emulator for the minimal firehose programmer init sequence.

Loads tmp/minimal.elf (before MBN wrapping), starts at _start in ARM mode,
and traces execution through the full boot sequence:
  _start → GPLL0 → BIMC branches → DDR blob (ddr_set_params + ddr_init) →
  SDCC clocks → main()

MMIO registers are simulated minimally: PLL lock bits are auto-set, CBCR
branch-off bits are auto-cleared, etc. The DDR blob executes natively with
its callback stubs (memcpy, memset, memmove, fast_memcpy, get_ttb) in the
CODE segment.

Usage:
    make minimal-elf
    python3 tools/minimal_init_emu.py [--trace] [--calls] [--mmio] [tmp/minimal.elf]
"""

import argparse
import struct
import sys

from unicorn import *
from unicorn.arm_const import *
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB, CS_MODE_ARM
from elftools.elf.elffile import ELFFile

# ---------------------------------------------------------------------------
# Memory regions (must match minimal.ld)
# ---------------------------------------------------------------------------
# RAM regions — mapped with mem_map, loaded from ELF
RAM_REGIONS = {
    'IMEM_CODE':  (0x00220000,  0x3000),
    'IMEM_DATA':  (0x00223000,  0x1000),
    'CODE':       (0x08006000,  0x46000),
    'DATA':       (0x0804C000,  0x11000),
    'DDR':        (0x80000000,  0x200000),
    'SYS_IMEM':   (0x08600000,  0x1000),
    'DDR_HIGH':   (0x87C00000,  0x100000),
}

# MMIO regions — mapped with mmio_map, read/write callbacks
MMIO_REGIONS = {
    'TLMM':       (0x01000000,  0x100000),
    'GCC':        (0x01800000,  0x80000),
    'TIMETICK':   (0x004A0000,  0xC000),   # includes PSHOLD at 0x4AB000
    'BIMC_QOS':   (0x00400000,  0x60000),
    'SDCC':       (0x07800000,  0x30000),
}

# Combined for address lookups
REGIONS = {**{k: (v[0], v[1], UC_PROT_ALL) for k, v in RAM_REGIONS.items()},
           **{k: (v[0], v[1], UC_PROT_ALL) for k, v in MMIO_REGIONS.items()}}

# Entry point
ENTRY_ADDR = 0x08006000

# Key addresses
PSHOLD_ADDR     = 0x004AB000
TIMETICK_ADDR   = 0x004A3000
GPLL0_MODE      = 0x01821000
GPLL0_STATUS    = 0x01821024
APCS_GPLL_VOTE  = 0x01845000
MAIN_ADDR       = None  # resolved from ELF

# GPIO
TLMM_BASE = 0x01000000
LED_RED_GPIO = 68
LED_GREEN_GPIO = 69

# GCC CBCR registers (auto-clear bit 31 on enable)
GCC_CBCR_ADDRS = [
    0x01831008, 0x0183100C, 0x01831010, 0x01831014,
    0x0183101C, 0x0183201C, 0x01832020, 0x01832024,
    0x01842018, 0x0184201C,  # SDCC1 APPS/AHB
]

# GCC CMD_RCGR registers (auto-clear bit 0 on update)
GCC_CMD_RCGR_ADDRS = [
    0x01832004, 0x01837000, 0x01842004,  # BIMC DDR, GFX, SDCC1
]

# DDR blob address range
DDR_BLOB_BASE = 0x00220000
DDR_BLOB_END  = 0x00224000


class MmioState:
    """Track MMIO register state and simulate hardware behavior."""

    def __init__(self):
        self.regs = {}
        self.timetick = 0

    def read(self, addr, size):
        # Sleep timetick — return incrementing counter
        if addr == TIMETICK_ADDR:
            self.timetick += 20000  # advance fast (>16384 per read = instant delays)
            return self.timetick

        # GPLL0 MODE — return lock bit set
        if addr == GPLL0_MODE or addr == GPLL0_STATUS:
            return self.regs.get(addr, 0) | (1 << 30)  # GPLL0_LOCK_BIT

        # CBCR registers — clear bit 31 (CLK_OFF) if bit 0 (enable) is set
        if addr in GCC_CBCR_ADDRS:
            val = self.regs.get(addr, (1 << 31))  # default: clock off
            if val & 1:  # enabled
                val &= ~(1 << 31)  # clear CLK_OFF
            return val

        # CMD_RCGR — clear update bit (bit 0) immediately
        if addr in GCC_CMD_RCGR_ADDRS:
            val = self.regs.get(addr, 0)
            val &= ~1  # clear CMD_UPDATE
            return val

        # PLL lock bits for BIMC PLL
        if addr == 0x01821000:  # BIMC_PLL_CONFIG_BASE (shares with GPLL0_MODE)
            return self.regs.get(addr, 0) | (1 << 31)  # PLL_LOCK_DET

        # BIMC MISC — clear update bit (bit 9)
        if addr == 0x01831018:
            val = self.regs.get(addr, 0)
            val &= ~(1 << 9)
            return val

        # BIMC registers — return last written value, or 0 (not busy)
        if 0x00400000 <= addr < 0x00460000:
            return self.regs.get(addr, 0)

        return self.regs.get(addr, 0)

    def write(self, addr, size, value):
        self.regs[addr] = value


class InitEmulator:
    """Unicorn-based emulator for minimal programmer init sequence."""

    def __init__(self, elf_path, args):
        self.elf_path = elf_path
        self.args = args
        self.symbols = {}
        self.addr_to_sym = {}
        self.mmio = MmioState()
        self.insn_count = 0
        self.max_insns = args.max_insns
        self.cp15_regs = {}  # (CRn, opc1, CRm, opc2) -> value
        self.led_state = {'red': False, 'green': False}
        self.reached_main = False
        self.last_bl_target = 0
        self.stop_reason = None

        # Capstone disassemblers
        self.cs_thumb = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
        self.cs_arm = Cs(CS_ARCH_ARM, CS_MODE_ARM)

        # Initialize Unicorn
        self.uc = Uc(UC_ARCH_ARM, UC_MODE_ARM)
        self._map_memory()
        self._load_elf()
        self._setup_hooks()

    def _map_memory(self):
        """Map RAM with mem_map, MMIO with mmio_map."""
        for name, (base, size) in RAM_REGIONS.items():
            try:
                self.uc.mem_map(base, size, UC_PROT_ALL)
            except UcError as e:
                print(f"  [warn] Failed to map {name} at 0x{base:08x}: {e}")

        for name, (base, size) in MMIO_REGIONS.items():
            try:
                # Create closures that capture region base
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
        """Load ELF segments and extract symbols."""
        global MAIN_ADDR

        with open(self.elf_path, 'rb') as f:
            elf = ELFFile(f)

            # Load LOAD segments
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

            # Extract symbols
            symtab = elf.get_section_by_name('.symtab')
            if symtab:
                for sym in symtab.iter_symbols():
                    if sym['st_value'] and sym.name:
                        addr = sym['st_value'] & ~1  # strip Thumb bit
                        self.symbols[sym.name] = addr
                        self.addr_to_sym[addr] = sym.name

                MAIN_ADDR = self.symbols.get('main')
                if MAIN_ADDR and self.args.verbose:
                    print(f"  [sym] main = 0x{MAIN_ADDR:08x}")

        # Patch out delay loops: replace 4000000 (0x003D0900) constants
        # with 1 so checkpoint_cpu loops execute once instead of 4M times.
        # Also patch bimc_clock_init loop constants (1000, 100000).
        self._patch_delay_constants()

    def _patch_delay_constants(self):
        """Patch delay loop constants in CODE region to speed up emulation.

        The checkpoint_cpu macro loads 4000000 (0x003D0900) from a literal pool.
        The bimc_clock_init PLL wait loads 1000 (0x3E8) and 100000 (0x186A0).
        The main.c spin_delay loads 200000000 (0x0BEBC200).
        Replace all with 1 so loops execute once.
        """
        code_base, code_size, _ = REGIONS['CODE']
        code = bytes(self.uc.mem_read(code_base, code_size))

        patches = {
            0x003D0900: (1, "4000000 (checkpoint_cpu delay)"),
            0x0BEBC200: (1, "200000000 (spin_delay)"),
            # Don't patch 1000/100000 as they're common values
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

    def _sym_at(self, addr):
        """Look up symbol name for an address."""
        addr &= ~1  # strip Thumb bit
        name = self.addr_to_sym.get(addr)
        if name:
            return name
        # Check nearby (within 4 bytes for alignment)
        for off in range(1, 5):
            name = self.addr_to_sym.get(addr - off)
            if name:
                return f"{name}+{off}"
        return None

    def _is_mmio(self, addr):
        """Check if address falls in an MMIO region."""
        for name in ('TLMM', 'GCC', 'TIMETICK', 'BIMC_QOS', 'SDCC'):
            base, size, _ = REGIONS[name]
            if base <= addr < base + size:
                return name
        return None

    def _mmio_read_cb(self, addr, size):
        """mmio_map read callback. addr is absolute (base + offset)."""
        val = self.mmio.read(addr, size)

        if self.args.mmio:
            sym = self._describe_mmio(addr)
            print(f"  [MMIO RD] 0x{addr:08x} ({sym}) = 0x{val:08x}", flush=True)

        return val

    def _mmio_write_cb(self, addr, size, value):
        """mmio_map write callback. addr is absolute."""
        self.mmio.write(addr, size, value)

        if self.args.mmio:
            sym = self._describe_mmio(addr)
            print(f"  [MMIO WR] 0x{addr:08x} ({sym}) = 0x{value:08x}", flush=True)

        self._check_mmio_side_effects_write(addr, value)

    def _check_mmio_side_effects_write(self, addr, value):
        """Handle side effects of MMIO writes."""
        # LED state tracking
        gpio_num = (addr - TLMM_BASE) // 0x1000
        gpio_off = (addr - TLMM_BASE) % 0x1000
        if gpio_num in (LED_RED_GPIO, LED_GREEN_GPIO) and gpio_off == 4:
            color = 'red' if gpio_num == LED_RED_GPIO else 'green'
            on = bool(value & 2)  # GPIO_OUT_BIT
            if on != self.led_state[color]:
                self.led_state[color] = on
                state_str = 'ON' if on else 'OFF'
                print(f"  [LED] {color.upper()} {state_str}", flush=True)

        # PS_HOLD write → stop
        if addr == PSHOLD_ADDR:
            print("  [PSHOLD] Reboot triggered — stopping emulation", flush=True)
            self.stop_reason = "PSHOLD reboot"
            self.uc.emu_stop()

    def _setup_hooks(self):
        """Install Unicorn hooks."""
        # Hook DDR blob entry points — skip execution and return success
        # ddr_set_params at 0x00222780 (Thumb entry 0x00222781)
        self.uc.hook_add(UC_HOOK_CODE, self._hook_ddr_skip,
                         begin=0x00222780, end=0x00222780)
        # ddr_init at 0x002224cc (Thumb entry 0x002224cd)
        self.uc.hook_add(UC_HOOK_CODE, self._hook_ddr_skip,
                         begin=0x002224cc, end=0x002224cc)

        # Code hooks — only full trace mode uses per-instruction hooks
        if self.args.trace:
            self.uc.hook_add(UC_HOOK_CODE, self._hook_code)

        # Interrupt hook (for CP15 MRC/MCR which Unicorn may not handle)
        self.uc.hook_add(UC_HOOK_INTR, self._hook_intr)

        # Invalid memory access
        self.uc.hook_add(UC_HOOK_MEM_UNMAPPED, self._hook_mem_fault)

    def _describe_mmio(self, addr):
        """Human-readable MMIO address description."""
        descs = {
            0x004A3000: "SLEEP_TIMETICK",
            0x004AB000: "PS_HOLD",
            0x01821000: "GPLL0_MODE / BIMC_PLL",
            0x01821024: "GPLL0_STATUS",
            0x01845000: "APCS_GPLL_ENA_VOTE",
            0x01831008: "GCC_BIMC_CBCR_0",
            0x0183100C: "GCC_BIMC_CBCR_1",
            0x01831010: "GCC_BIMC_CBCR_2",
            0x01831014: "GCC_BIMC_CBCR_3",
            0x0183101C: "GCC_BIMC_CBCR_4",
            0x0183201C: "GCC_BIMC_CBCR_5",
            0x01832020: "GCC_BIMC_CBCR_6",
            0x01832024: "GCC_BIMC_CBCR_7",
            0x01831018: "GCC_BIMC_MISC",
            0x01832004: "GCC_BIMC_DDR_CMD_RCGR",
            0x01832008: "GCC_BIMC_DDR_CFG_RCGR",
            0x01837000: "GCC_BIMC_GFX_CMD_RCGR",
            0x01837004: "GCC_BIMC_GFX_CFG_RCGR",
            0x01836000: "GCC_GPLL0_MODE_ALT",
            0x01836004: "GCC_GPLL0_USER_CTL",
            0x01845004: "GCC_BIMC_PLL_USER_CTL",
            0x01842004: "SDCC1_CMD_RCGR",
            0x01842008: "SDCC1_CFG_RCGR",
            0x01842018: "SDCC1_APPS_CBCR",
            0x0184201C: "SDCC1_AHB_CBCR",
        }
        if addr in descs:
            return descs[addr]

        # GPIO
        gpio_num = (addr - TLMM_BASE) // 0x1000
        gpio_off = (addr - TLMM_BASE) % 0x1000
        if 0 <= gpio_num < 256:
            if gpio_off == 0:
                return f"GPIO{gpio_num}_CFG"
            elif gpio_off == 4:
                return f"GPIO{gpio_num}_IN_OUT"

        return f"0x{addr:08x}"

    def _hook_code(self, uc, addr, size, user_data):
        """Full instruction trace."""
        self.insn_count += 1
        if self.insn_count > self.max_insns:
            print(f"\n  [LIMIT] Reached {self.max_insns} instructions — stopping")
            self.stop_reason = "instruction limit"
            uc.emu_stop()
            return

        # Read instruction bytes
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

        self._check_milestones(addr)

    def _check_milestones(self, addr):
        """Check for important execution milestones."""
        global MAIN_ADDR

        # Reached main()
        if MAIN_ADDR and addr == MAIN_ADDR and not self.reached_main:
            self.reached_main = True
            print(f"\n  *** REACHED main() at 0x{addr:08x} after {self.insn_count} instructions ***\n")
            if not self.args.trace:
                self.stop_reason = "reached main()"
                self.uc.emu_stop()

    def _hook_ddr_skip(self, uc, addr, size, user_data):
        """Hook at DDR blob entry points — skip execution and return success.

        The DDR blob can't be properly emulated without full BIMC register
        simulation. Instead, we skip it and return r0=1 (success).
        """
        lr = uc.reg_read(UC_ARM_REG_LR)
        name = {0x00222780: "ddr_set_params", 0x002224cc: "ddr_init"}.get(addr, f"0x{addr:08x}")
        print(f"  [DDR SKIP] {name} at 0x{addr:08x} → returning 1 (success) to 0x{lr:08x}",
              flush=True)
        uc.reg_write(UC_ARM_REG_R0, 1)  # success
        uc.reg_write(UC_ARM_REG_PC, lr & ~1)  # return to caller
        # Ensure correct mode
        if lr & 1:
            cpsr = uc.reg_read(UC_ARM_REG_CPSR)
            uc.reg_write(UC_ARM_REG_CPSR, cpsr | (1 << 5))  # set T bit

    def _hook_intr(self, uc, intno, user_data):
        """Handle interrupts (CP15 access etc.)."""
        # Unicorn fires EXCP_SWI (2) for undefined instructions
        # and EXCP_UDEF for coprocessor access it can't handle
        if intno == 2:  # SWI
            pc = uc.reg_read(UC_ARM_REG_PC)
            if self.args.verbose:
                print(f"  [INTR] SWI at 0x{pc:08x}")
        else:
            pc = uc.reg_read(UC_ARM_REG_PC)
            if self.args.verbose:
                print(f"  [INTR] #{intno} at 0x{pc:08x}")

    def _hook_mem_fault(self, uc, access, addr, size, value, user_data):
        """Handle unmapped memory access."""
        access_type = "READ" if access == UC_MEM_READ_UNMAPPED else "WRITE"
        pc = uc.reg_read(UC_ARM_REG_PC)
        print(f"  [FAULT] Unmapped {access_type} at 0x{addr:08x} (size={size}) from PC=0x{pc:08x}")

        # Auto-map the page so we can continue
        page_base = addr & ~0xFFF
        try:
            uc.mem_map(page_base, 0x1000, UC_PROT_ALL)
            if self.args.verbose:
                print(f"  [FAULT] Auto-mapped 0x{page_base:08x}")
            return True  # continue execution
        except UcError:
            return False

    def run(self):
        """Run the emulation in chunks, checking PC between chunks.

        This avoids the overhead of per-block Python callbacks during
        tight DDR blob computation loops. Between chunks we check PC,
        log milestones, and detect if main() was reached.
        """
        print(f"Starting emulation at 0x{ENTRY_ADDR:08x} (ARM mode)")
        print(f"  ELF: {self.elf_path}")
        print(f"  Symbols: {len(self.symbols)}")
        print(f"  Max instructions: {self.max_insns:,}")
        if MAIN_ADDR:
            print(f"  main() at 0x{MAIN_ADDR:08x}")
        print()

        # Set initial register state
        self.uc.reg_write(UC_ARM_REG_SP, 0x0805D000)  # _stack_top
        self.uc.reg_write(UC_ARM_REG_LR, 0)

        # CPSR: ARM mode, supervisor, no interrupts
        self.uc.reg_write(UC_ARM_REG_CPSR, 0x000001D3)

        # Chunk size: execute this many instructions between PC checks
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
            if sym and sym != last_logged_func and not sym.startswith('$'):
                in_blob = DDR_BLOB_BASE <= pc < DDR_BLOB_END
                if in_blob:
                    print(f"  [DDR BLOB] 0x{pc:08x} {sym}", flush=True)
                elif self.args.calls:
                    print(f"  [FUNC] {sym} (0x{pc:08x})", flush=True)
                last_logged_func = sym

            # Check for main() — exact entry or within main's body
            if MAIN_ADDR and not self.reached_main:
                # main() is small; check if PC is within a reasonable range
                if MAIN_ADDR <= pc < MAIN_ADDR + 0x20:
                    self.reached_main = True
                    print(f"\n  *** REACHED main() at 0x{pc:08x} after {total_insns:,} instructions ***\n",
                          flush=True)
                    self.stop_reason = "reached main()"
                    break

            # Stuck detection: same PC for too many chunks
            if pc == last_pc:
                stuck_count += 1
                if stuck_count > 100:
                    sym = self._sym_at(pc) or "unknown"
                    print(f"\n  [STUCK] PC unchanged at 0x{pc:08x} ({sym}) for {stuck_count} chunks",
                          flush=True)
                    self._dump_regs()
                    self.stop_reason = f"stuck at 0x{pc:08x}"
                    break
            else:
                stuck_count = 0
            last_pc = pc

            # Determine if we need Thumb mode based on CPSR
            cpsr = self.uc.reg_read(UC_ARM_REG_CPSR)
            thumb = bool(cpsr & (1 << 5))
            start_addr = pc | (1 if thumb else 0)  # Thumb bit in address for emu_start

            try:
                self.uc.emu_start(start_addr, 0, count=CHUNK)
            except UcError as e:
                pc = self.uc.reg_read(UC_ARM_REG_PC)
                cpsr = self.uc.reg_read(UC_ARM_REG_CPSR)
                print(f"\n  [ERROR] Emulation error at PC=0x{pc:08x} CPSR=0x{cpsr:08x}: {e}")
                self._dump_regs()
                self.stop_reason = f"error: {e}"
                break

            total_insns += CHUNK

            # Progress every 10M instructions
            if total_insns % 10_000_000 == 0:
                pc = self.uc.reg_read(UC_ARM_REG_PC)
                sym = self._sym_at(pc) or ""
                print(f"  [PROGRESS] {total_insns // 1_000_000}M insns, PC=0x{pc:08x} {sym}",
                      flush=True)

        # Summary
        print(f"\n{'='*60}")
        print(f"Emulation complete: ~{total_insns:,} instructions")
        if self.stop_reason:
            print(f"Stop reason: {self.stop_reason}")
        if self.reached_main:
            print("Result: SUCCESS — main() was reached")
        else:
            pc = self.uc.reg_read(UC_ARM_REG_PC)
            sym = self._sym_at(pc) or "unknown"
            print(f"Result: STOPPED at 0x{pc:08x} ({sym})")
            print("        main() was NOT reached")
        print(f"LED state: red={'ON' if self.led_state['red'] else 'OFF'}, "
              f"green={'ON' if self.led_state['green'] else 'OFF'}")
        print(f"{'='*60}")

    def _dump_regs(self):
        """Dump ARM registers for debugging."""
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
    parser = argparse.ArgumentParser(description='Minimal programmer init emulator')
    parser.add_argument('elf', nargs='?', default='tmp/minimal.elf',
                        help='ELF file to load (default: tmp/minimal.elf)')
    parser.add_argument('--trace', action='store_true',
                        help='Full instruction trace (very verbose)')
    parser.add_argument('--calls', action='store_true',
                        help='Function call trace (BL/BLX targets)')
    parser.add_argument('--mmio', action='store_true',
                        help='Log all MMIO reads/writes')
    parser.add_argument('--verbose', '-v', action='store_true',
                        help='Verbose output')
    parser.add_argument('--max-insns', type=int, default=100_000_000,
                        help='Maximum blocks to execute (default: 100M)')
    args = parser.parse_args()

    emu = InitEmulator(args.elf, args)
    emu.run()


if __name__ == '__main__':
    main()
