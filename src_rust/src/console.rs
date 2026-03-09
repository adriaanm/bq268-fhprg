/// USB diagnostic console — command parser and dispatch.
///
/// Port of main.c command loop. All formatting done with no_std helpers.
use crate::usb;
use crate::emmc::Emmc;
use crate::sdcc::SdccHw;
use crate::platform::{self, SDRAM_START_ADDR};
use crate::mmio::Reg32;

const RESP_SIZE: usize = 4096;
const CMD_BUF_SIZE: usize = 512;
const SECTOR_SIZE: usize = 512;
const BULK_BUF_SIZE: usize = 0x10_0000; // 1 MB

/// DDR-resident buffers for eMMC data transfers.
#[link_section = ".ddr_bss"]
static mut SECTOR_BUF: [u8; SECTOR_SIZE] = [0u8; SECTOR_SIZE];
#[link_section = ".ddr_bss"]
static mut BULK_BUF: [u8; BULK_BUF_SIZE] = [0u8; BULK_BUF_SIZE];

const HEX_CHARS: &[u8; 16] = b"0123456789abcdef";

struct Fmt<'a> {
    buf: &'a mut [u8],
    pos: usize,
}

impl<'a> Fmt<'a> {
    fn new(buf: &'a mut [u8]) -> Self {
        Self { buf, pos: 0 }
    }

    fn hex32(&mut self, val: u32) {
        for i in (0..8).rev() {
            self.buf[self.pos] = HEX_CHARS[((val >> (i * 4)) & 0xF) as usize];
            self.pos += 1;
        }
    }

    fn hex8(&mut self, val: u8) {
        self.buf[self.pos] = HEX_CHARS[(val >> 4) as usize];
        self.pos += 1;
        self.buf[self.pos] = HEX_CHARS[(val & 0xF) as usize];
        self.pos += 1;
    }

    fn str(&mut self, s: &str) {
        for &b in s.as_bytes() {
            self.buf[self.pos] = b;
            self.pos += 1;
        }
    }

    fn dec(&mut self, val: u32) {
        if val == 0 {
            self.buf[self.pos] = b'0';
            self.pos += 1;
            return;
        }
        let mut tmp = [0u8; 10];
        let mut i = 0;
        let mut v = val;
        while v > 0 {
            tmp[i] = b'0' + (v % 10) as u8;
            v /= 10;
            i += 1;
        }
        while i > 0 {
            i -= 1;
            self.buf[self.pos] = tmp[i];
            self.pos += 1;
        }
    }

    fn flush(&mut self) {
        if self.pos > 0 {
            usb::write(&self.buf[..self.pos]);
            self.pos = 0;
        }
    }

    fn flush_if_full(&mut self) {
        if self.pos > 3800 {
            self.flush();
        }
    }
}

fn parse_hex(s: &[u8]) -> u32 {
    let mut val: u32 = 0;
    for &c in s {
        match c {
            b'0'..=b'9' => val = (val << 4) | (c - b'0') as u32,
            b'a'..=b'f' => val = (val << 4) | (c - b'a' + 10) as u32,
            b'A'..=b'F' => val = (val << 4) | (c - b'A' + 10) as u32,
            _ => break,
        }
    }
    val
}

fn skip_ws(s: &[u8]) -> &[u8] {
    let mut i = 0;
    while i < s.len() && (s[i] == b' ' || s[i] == b'\t') {
        i += 1;
    }
    &s[i..]
}

fn skip_nonws(s: &[u8]) -> &[u8] {
    let mut i = 0;
    while i < s.len() && s[i] != b' ' && s[i] != b'\t' && s[i] != b'\r' && s[i] != b'\n' {
        i += 1;
    }
    &s[i..]
}

pub struct Console<'a, H: SdccHw> {
    emmc: &'a mut Emmc<H>,
    resp: [u8; RESP_SIZE],
    cmd_buf: [u8; CMD_BUF_SIZE],
}

impl<'a, H: SdccHw> Console<'a, H> {
    pub fn new(emmc: &'a mut Emmc<H>) -> Self {
        Self {
            emmc,
            resp: [0u8; RESP_SIZE],
            cmd_buf: [0u8; CMD_BUF_SIZE],
        }
    }

    pub fn run(&mut self) -> ! {
        let banner = "=== MSM8909 Diag Console (Rust) ===\r\n\
                       \x20 r ADDR          read 32-bit word\r\n\
                       \x20 w ADDR VAL      write 32-bit word\r\n\
                       \x20 d ADDR LEN      hex dump\r\n\
                       \x20 i               system info\r\n\
                       \x20 t               DDR test\r\n\
                       \x20 e               init eMMC\r\n\
                       \x20 c               eMMC card status\r\n\
                       \x20 s SECTOR        read sector (hex)\r\n\
                       \x20 S SECTOR BYTE   write sector fill\r\n\
                       \x20 W SECTOR COUNT  bulk write\r\n\
                       > ";
        usb::write(banner.as_bytes());

        loop {
            let n = usb::read(&mut self.cmd_buf);
            if n <= 0 { continue; }
            let mut len = n as usize;
            self.cmd_buf[len] = 0;

            // Strip trailing newlines
            while len > 0 && (self.cmd_buf[len - 1] == b'\r' || self.cmd_buf[len - 1] == b'\n') {
                len -= 1;
                self.cmd_buf[len] = 0;
            }

            if len == 0 {
                usb::write(b"> ");
                continue;
            }

            platform::led_on(platform::LED_RED_GPIO);

            // Copy args to local buffer to avoid borrow conflict
            let cmd_byte = self.cmd_buf[0];
            let mut args = [0u8; CMD_BUF_SIZE];
            let args_len = if len > 1 { len - 1 } else { 0 };
            args[..args_len].copy_from_slice(&self.cmd_buf[1..len]);

            match cmd_byte {
                b'i' | b'I' => self.cmd_info(),
                b'r' => self.cmd_read(&args[..args_len]),
                b'w' => self.cmd_write_word(&args[..args_len]),
                b'W' => self.cmd_bulk_write(&args[..args_len]),
                b'd' | b'D' => self.cmd_dump(&args[..args_len]),
                b't' => self.cmd_ddr_test(),
                b'e' => self.cmd_emmc_init(),
                b'c' => self.cmd_emmc_status(),
                b's' => self.cmd_sector_read(&args[..args_len]),
                b'S' => self.cmd_sector_write(&args[..args_len]),
                _ => {
                    usb::write(b"? unknown cmd\r\n> ");
                }
            }

            platform::led_off(platform::LED_RED_GPIO);
        }
    }

    fn cmd_info(&mut self) {
        let mut f = Fmt::new(&mut self.resp);
        f.str("=== MSM8909 Diagnostic Console ===\r\n");

        f.str("SCTLR:  "); f.hex32(platform::read_sctlr()); f.str("\r\n");
        f.str("TTBR0:  "); f.hex32(platform::read_ttbr0()); f.str("\r\n");
        f.str("TTBR1:  "); f.hex32(platform::read_ttbr1()); f.str("\r\n");
        f.str("TTBCR:  "); f.hex32(platform::read_ttbcr()); f.str("\r\n");
        f.str("DACR:   "); f.hex32(platform::read_dacr()); f.str("\r\n");
        f.str("DFSR:   "); f.hex32(platform::read_dfsr()); f.str("\r\n");
        f.str("DFAR:   "); f.hex32(platform::read_dfar()); f.str("\r\n");
        f.str("VBAR:   "); f.hex32(platform::read_vbar()); f.str("\r\n");

        let ttbr0 = platform::read_ttbr0() & 0xFFFF_C000;
        let ttbcr_n = platform::read_ttbcr() & 7;
        f.str("\r\nPage table base: ");
        f.hex32(ttbr0);
        f.str(" (N="); f.dec(ttbcr_n); f.str(")\r\n");

        // Page table entries for key addresses
        let addrs: [(u32, &str); 12] = [
            (0x0000_0000, "0x000 (boot ROM)"),
            (0x0020_0000, "0x002 (IMEM)"),
            (0x0040_0000, "0x004 (BIMC)"),
            (0x0080_0000, "0x008 (LPASS)"),
            (0x0100_0000, "0x010 (TLMM)"),
            (0x0180_0000, "0x018 (GCC)"),
            (0x0780_0000, "0x078 (PERIPH)"),
            (0x07F0_0000, "0x07F (USB)"),
            (0x0800_0000, "0x080 (OCIMEM)"),
            (0x8000_0000, "0x800 (DDR)"),
            (0x8010_0000, "0x801 (DDR+1M)"),
            (0x87C0_0000, "0x87C (DDR hi)"),
        ];
        f.str("\r\nL1 page table entries:\r\n");
        for &(addr, name) in &addrs {
            let idx = addr >> 20;
            let pte = Reg32::new(ttbr0 + idx * 4).read();
            f.str("  ["); f.str(name); f.str("] = "); f.hex32(pte); f.str("\r\n");
        }

        f.str("> ");
        f.flush();
    }

    fn cmd_read(&mut self, args: &[u8]) {
        let args = skip_ws(args);
        let addr = parse_hex(args);
        platform::dsb();
        let val = Reg32::new(addr).read();

        let mut f = Fmt::new(&mut self.resp);
        f.hex32(addr); f.str(": "); f.hex32(val); f.str("\r\n> ");
        f.flush();
    }

    fn cmd_write_word(&mut self, args: &[u8]) {
        let p1 = skip_ws(args);
        let addr = parse_hex(p1);
        let p2 = skip_ws(skip_nonws(p1));
        let val = parse_hex(p2);

        Reg32::new(addr).write(val);
        platform::dsb();

        let mut f = Fmt::new(&mut self.resp);
        f.str("OK "); f.hex32(addr); f.str(" = "); f.hex32(val); f.str("\r\n> ");
        f.flush();
    }

    fn cmd_dump(&mut self, args: &[u8]) {
        let p1 = skip_ws(args);
        let addr = parse_hex(p1);
        let p2 = skip_ws(skip_nonws(p1));
        let mut len = parse_hex(p2);
        if len == 0 { len = 0x40; }
        if len > 0x400 { len = 0x400; }

        let mut f = Fmt::new(&mut self.resp);
        for i in 0..len {
            if (i & 0xF) == 0 {
                if i > 0 { f.str("\r\n"); }
                f.hex32(addr + i);
                f.str(": ");
            }
            let byte = unsafe { core::ptr::read_volatile((addr + i) as *const u8) };
            f.hex8(byte);
            f.str(" ");
            f.flush_if_full();
        }
        f.str("\r\n> ");
        f.flush();
    }

    fn cmd_ddr_test(&mut self) {
        let ddr = SDRAM_START_ADDR as *mut u32;
        let ttbr0 = platform::read_ttbr0() & 0xFFFF_C000;
        let pte = Reg32::new(ttbr0 + 0x800 * 4).read();

        let mut f = Fmt::new(&mut self.resp);
        f.str("DDR test at "); f.hex32(SDRAM_START_ADDR); f.str("\r\n");
        f.str("PTE[0x800] = "); f.hex32(pte); f.str("\r\n");

        if pte & 3 == 0 {
            f.str("FAULT: no page table entry for DDR!\r\n");
            f.str("> ");
            f.flush();
            return;
        }

        unsafe {
            core::ptr::write_volatile(ddr, 0xDEAD_BEEF);
            core::ptr::write_volatile(ddr.add(1), 0xCAFE_BABE);
            core::ptr::write_volatile(ddr.add(2), 0x1234_5678);
            core::ptr::write_volatile(ddr.add(3), 0x0000_0000);
            platform::dsb();

            let v0 = core::ptr::read_volatile(ddr);
            let v1 = core::ptr::read_volatile(ddr.add(1));
            let v2 = core::ptr::read_volatile(ddr.add(2));
            let v3 = core::ptr::read_volatile(ddr.add(3));

            f.str("  [0] = "); f.hex32(v0);
            f.str(if v0 == 0xDEAD_BEEF { " OK\r\n" } else { " FAIL\r\n" });
            f.str("  [1] = "); f.hex32(v1);
            f.str(if v1 == 0xCAFE_BABE { " OK\r\n" } else { " FAIL\r\n" });
            f.str("  [2] = "); f.hex32(v2);
            f.str(if v2 == 0x1234_5678 { " OK\r\n" } else { " FAIL\r\n" });
            f.str("  [3] = "); f.hex32(v3);
            f.str(if v3 == 0x0000_0000 { " OK\r\n" } else { " FAIL\r\n" });
        }

        f.str("> ");
        f.flush();
    }

    fn cmd_emmc_init(&mut self) {
        let mut f = Fmt::new(&mut self.resp);

        if self.emmc.is_inited() {
            f.str("eMMC already initialized\r\n> ");
            f.flush();
            return;
        }

        f.str("eMMC init: enabling SDCC1 clocks...\r\n");
        f.flush();

        platform::sdcc_clock_init();

        f.str("eMMC init: opening device...\r\n");
        f.flush();

        match self.emmc.open() {
            Ok(()) => {
                f.str("eMMC init OK\r\n");
            }
            Err(e) => {
                f.str("eMMC init FAILED: ");
                match e {
                    crate::sdcc::Error::Timeout => f.str("timeout"),
                    crate::sdcc::Error::CrcFail => f.str("CRC fail"),
                    crate::sdcc::Error::CardNotResponding => f.str("card not responding"),
                    crate::sdcc::Error::DataError(st) => { f.str("data err STAT="); f.hex32(st); },
                    _ => f.str("unknown error"),
                }
                f.str("\r\n");
            }
        }
        f.str("> ");
        f.flush();
    }

    fn cmd_emmc_status(&mut self) {
        let mut f = Fmt::new(&mut self.resp);

        if !self.emmc.is_inited() {
            f.str("eMMC not initialized. Run 'e' first.\r\n> ");
            f.flush();
            return;
        }

        match self.emmc.status() {
            Ok(state) => {
                let names = ["idle","ready","ident","stby","tran","data","rcv","prg",
                             "dis","?9","?10","?11","?12","?13","?14","?15"];
                f.str("Card state: ");
                f.dec(state as u32);
                f.str(" (");
                f.str(if (state as usize) < 16 { names[state as usize] } else { "?" });
                f.str(")\r\n");
            }
            Err(_) => {
                f.str("CMD13 failed\r\n");
            }
        }
        f.str("> ");
        f.flush();
    }

    fn cmd_sector_read(&mut self, args: &[u8]) {
        let args = skip_ws(args);
        let sector = parse_hex(args);

        let mut f = Fmt::new(&mut self.resp);

        if !self.emmc.is_inited() {
            f.str("eMMC not initialized. Run 'e' first.\r\n> ");
            f.flush();
            return;
        }

        let buf = unsafe { &mut SECTOR_BUF };
        for b in buf.iter_mut() { *b = 0; }

        match self.emmc.read(sector, buf) {
            Ok(()) => {
                f.str("Read sector "); f.hex32(sector); f.str(":\r\n");
                f.flush();

                // Hex dump
                for i in 0..SECTOR_SIZE {
                    if (i & 0xF) == 0 {
                        if i > 0 { f.str("\r\n"); }
                        f.hex32(i as u32);
                        f.str(": ");
                    }
                    f.hex8(buf[i]);
                    f.str(" ");
                    f.flush_if_full();
                }
                f.str("\r\n");
            }
            Err(e) => {
                f.str("READ FAILED: ");
                match e {
                    crate::sdcc::Error::Timeout => f.str("timeout"),
                    crate::sdcc::Error::CrcFail => f.str("CRC fail"),
                    crate::sdcc::Error::CardNotResponding => f.str("card not responding"),
                    crate::sdcc::Error::DataError(st) => { f.str("data err STAT="); f.hex32(st); },
                    crate::sdcc::Error::InvalidState => f.str("invalid state"),
                    crate::sdcc::Error::R1Error(v) => { f.str("R1 err="); f.hex32(v); },
                    _ => f.str("other"),
                }
                f.str("\r\n");
                // Dump post-read MCI state
                let mb: u32 = 0x0782_4000;
                f.str("POST: STAT="); f.hex32(Reg32::new(mb + 0x34).read());
                f.str(" RESP0="); f.hex32(Reg32::new(mb + 0x14).read());
                f.str(" DCTL="); f.hex32(Reg32::new(mb + 0x2C).read());
                f.str(" DLEN="); f.hex32(Reg32::new(mb + 0x28).read());
                f.str("\r\n");
            }
        }
        f.str("> ");
        f.flush();
    }

    fn cmd_sector_write(&mut self, args: &[u8]) {
        let p1 = skip_ws(args);
        let sector = parse_hex(p1);
        let p2 = skip_ws(skip_nonws(p1));
        let fill = parse_hex(p2) as u8;

        let mut f = Fmt::new(&mut self.resp);

        if !self.emmc.is_inited() {
            f.str("eMMC not initialized. Run 'e' first.\r\n> ");
            f.flush();
            return;
        }

        let buf = unsafe { &mut SECTOR_BUF };
        for b in buf.iter_mut() { *b = fill; }

        match self.emmc.write(sector, buf) {
            Ok(()) => {
                f.str("Write sector "); f.hex32(sector);
                f.str(" fill="); f.hex8(fill); f.str(": OK\r\n");
            }
            Err(_) => {
                f.str("WRITE FAILED\r\n");
            }
        }
        f.str("> ");
        f.flush();
    }

    fn cmd_bulk_write(&mut self, args: &[u8]) {
        let p1 = skip_ws(args);
        let sector = parse_hex(p1);
        let p2 = skip_ws(skip_nonws(p1));
        let count = parse_hex(p2);
        let total = count as usize * SECTOR_SIZE;

        let mut f = Fmt::new(&mut self.resp);

        if !self.emmc.is_inited() {
            f.str("ERR eMMC not initialized\r\n");
            f.flush();
            return;
        }
        if count == 0 || total > BULK_BUF_SIZE {
            f.str("ERR invalid count (max ");
            f.hex32((BULK_BUF_SIZE / SECTOR_SIZE) as u32);
            f.str(" sectors)\r\n");
            f.flush();
            return;
        }

        // Signal ready
        f.str("READY "); f.hex32(sector); f.str(" "); f.hex32(count); f.str("\r\n");
        f.flush();

        // Receive raw data into DDR
        let bulk = unsafe { &mut BULK_BUF[..total] };
        let mut received: usize = 0;
        while received < total {
            let n = usb::read(&mut bulk[received..]);
            if n > 0 {
                received += n as usize;
            }
        }

        // Write to eMMC in chunks (64 sectors = 32 KB)
        let mut written: u32 = 0;
        while written < count {
            let chunk = if count - written > 64 { 64 } else { count - written };
            let offset = (written as usize) * SECTOR_SIZE;
            let data = &bulk[offset..offset + chunk as usize * SECTOR_SIZE];
            match self.emmc.write(sector + written, data) {
                Ok(()) => {}
                Err(_) => {
                    f.str("ERR write failed at sector ");
                    f.hex32(sector + written);
                    f.str("\r\n");
                    f.flush();
                    return;
                }
            }
            written += chunk;
        }

        f.str("OK "); f.hex32(count); f.str("\r\n");
        f.flush();
    }
}
