/// SDCC command dispatch and data transfer — the hardware abstraction layer.
///
/// Implements the SdccHw trait for real hardware via SdccDriver.
/// Port of sdcc_helpers.c, sdcc_regs.c command path, and parts of emmc.c.
use crate::regs::{self, SdccRegs, status};
use crate::platform::delay_us;

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum Error {
    Timeout,
    CrcFail,
    CardNotResponding,
    R1Error(u32),
    DataError(u32),   // carries MCI_STATUS that triggered it
    InvalidState,
    WriteProtected,
    InvalidParam,
    BusyTimeout,
}

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum RespType {
    None,
    R1,
    R1b,
    R2,
    R3,
}

#[derive(Debug, Clone, Copy)]
pub struct CmdFlags {
    pub write: bool,
    pub data_xfer: bool,
    pub app_cmd: bool,
}

impl CmdFlags {
    pub const fn empty() -> Self {
        Self { write: false, data_xfer: false, app_cmd: false }
    }
    pub const fn data() -> Self {
        Self { write: false, data_xfer: true, app_cmd: false }
    }
    pub const fn write() -> Self {
        Self { write: true, data_xfer: false, app_cmd: false }
    }
}

#[derive(Debug, Clone, Copy)]
pub struct MmcCmd {
    pub index: u8,
    pub arg: u32,
    pub resp_type: RespType,
    pub flags: CmdFlags,
}

#[derive(Debug, Clone, Copy, Default)]
pub struct CmdResponse {
    pub words: [u32; 4],
    pub status: u32,
}

// Typed command constructors
pub fn cmd0() -> MmcCmd {
    MmcCmd { index: 0, arg: 0, resp_type: RespType::None, flags: CmdFlags::empty() }
}
pub fn cmd1(ocr: u32) -> MmcCmd {
    MmcCmd { index: 1, arg: ocr, resp_type: RespType::R3, flags: CmdFlags::empty() }
}
pub fn cmd2() -> MmcCmd {
    MmcCmd { index: 2, arg: 0, resp_type: RespType::R2, flags: CmdFlags::empty() }
}
pub fn cmd3(rca: u16) -> MmcCmd {
    MmcCmd { index: 3, arg: (rca as u32) << 16, resp_type: RespType::R1, flags: CmdFlags::empty() }
}
pub fn cmd6(arg: u32) -> MmcCmd {
    MmcCmd { index: 6, arg, resp_type: RespType::R1, flags: CmdFlags { write: false, data_xfer: false, app_cmd: false } }
}
pub fn cmd7(rca: u16) -> MmcCmd {
    MmcCmd { index: 7, arg: (rca as u32) << 16, resp_type: RespType::R1, flags: CmdFlags::empty() }
}
pub fn cmd9(rca: u16) -> MmcCmd {
    MmcCmd { index: 9, arg: (rca as u32) << 16, resp_type: RespType::R2, flags: CmdFlags::empty() }
}
pub fn cmd12() -> MmcCmd {
    MmcCmd { index: 12, arg: 0, resp_type: RespType::R1, flags: CmdFlags::empty() }
}
pub fn cmd13(rca: u16) -> MmcCmd {
    MmcCmd { index: 13, arg: (rca as u32) << 16, resp_type: RespType::R1, flags: CmdFlags::empty() }
}
pub fn cmd16(blocklen: u32) -> MmcCmd {
    MmcCmd { index: 16, arg: blocklen, resp_type: RespType::R1, flags: CmdFlags::empty() }
}
pub fn cmd17(sector: u32) -> MmcCmd {
    MmcCmd { index: 17, arg: sector, resp_type: RespType::R1, flags: CmdFlags::data() }
}
pub fn cmd18(sector: u32) -> MmcCmd {
    MmcCmd { index: 18, arg: sector, resp_type: RespType::R1, flags: CmdFlags::data() }
}
pub fn cmd24(sector: u32) -> MmcCmd {
    MmcCmd { index: 24, arg: sector, resp_type: RespType::R1, flags: CmdFlags::write() }
}
pub fn cmd25(sector: u32) -> MmcCmd {
    MmcCmd { index: 25, arg: sector, resp_type: RespType::R1, flags: CmdFlags::write() }
}
pub fn cmd35(sector: u32) -> MmcCmd {
    MmcCmd { index: 35, arg: sector, resp_type: RespType::R1, flags: CmdFlags::empty() }
}
pub fn cmd36(sector: u32) -> MmcCmd {
    MmcCmd { index: 36, arg: sector, resp_type: RespType::R1, flags: CmdFlags::empty() }
}
pub fn cmd38() -> MmcCmd {
    MmcCmd { index: 38, arg: 0, resp_type: RespType::R1, flags: CmdFlags::empty() }
}

/// The hardware command interface.
pub trait SdccHw {
    fn send_cmd(&mut self, cmd: &MmcCmd) -> Result<CmdResponse, Error>;
    fn read_data(&mut self, cmd: &MmcCmd, buf: &mut [u8]) -> Result<(), Error>;
    fn write_data(&mut self, cmd: &MmcCmd, buf: &[u8]) -> Result<(), Error>;
    fn wait_busy(&mut self) -> Result<(), Error>;
    fn wait_card_ready(&mut self, rca: u16) -> Result<(), Error>;
    fn set_clock(&mut self, khz: u32);
    fn init_controller(&mut self) -> Result<(), Error>;
    fn get_card_state(&mut self, rca: u16) -> Result<u8, Error>;
}

/// Real hardware SDCC driver.
pub struct SdccDriver {
    pub regs: SdccRegs,
}

impl SdccDriver {
    pub fn new(regs: SdccRegs) -> Self {
        Self { regs }
    }

    /// Map RespType to the MCI resp_type byte used in pre_cmd_hook.
    fn resp_type_byte(rt: RespType) -> u8 {
        match rt {
            RespType::None => 0,
            RespType::R1 | RespType::R1b | RespType::R3 => 1,
            RespType::R2 => 4,
        }
    }

    /// pre_cmd_hook: clear status, build command config, fire via sdcc_cleanup.
    fn pre_cmd_hook(&mut self, cmd: &MmcCmd) {
        let regs = &self.regs;
        // Clear pending status
        for _ in 0..1000 {
            regs.mci_clear().write(status::ALL_CLEAR);
            if regs.read_status() & status::ALL_CLEAR == 0 {
                break;
            }
        }

        // Build MCI_CMD value
        let mut mci_cmd: u32 = cmd.index as u32 & 0x3F;

        let rt = Self::resp_type_byte(cmd.resp_type);
        if rt != 0 {
            mci_cmd |= 0x40;  // CRC check → bit 6
            if rt == 4 {
                mci_cmd |= 0x80; // index check → bit 7 (for R2)
            }
        }
        // Data present for CMD17/18/24/25/53
        match cmd.index {
            17 | 18 | 24 | 25 | 53 => mci_cmd |= 0x1000, // bit 12: data-path enable
            _ => {}
        }
        // Busy signal for R1b
        if matches!(cmd.resp_type, RespType::R1b) {
            mci_cmd |= 0x800; // bit 11: CCS enable
        }
        mci_cmd |= 0x400; // bit 10: data present (has_response flag)

        regs.mci_argument().write(cmd.arg);
        regs.mci_cmd().write(mci_cmd);
        regs.wait_mclk_stable();
    }

    /// sdcc_setup_data_xfer: poll MCI_STATUS until CMD_RESPONSE_END, timeout, or CRC fail.
    fn setup_data_xfer(&mut self, cmd: &MmcCmd) -> Result<(CmdResponse, bool), Error> {
        let regs = &self.regs;
        let mut busy_clear = false;

        for i in 0..0x80000u32 {
            let st = regs.read_status();

            if st & status::CMD_RESP_END != 0 {
                regs.mci_clear().write(status::CMD_RESP_END);
                if st & status::PROG_DONE != 0 {
                    regs.mci_clear().write(status::PROG_DONE);
                    busy_clear = true;
                }
                let mut resp = CmdResponse { words: [0; 4], status: st };
                let nwords = if Self::resp_type_byte(cmd.resp_type) == 4 { 4 } else { 1 };
                for j in 0..nwords {
                    resp.words[j as usize] = regs.mci_resp(j).read();
                }
                return Ok((resp, busy_clear));
            }
            if st & status::CMD_TIMEOUT != 0 {
                regs.mci_clear().write(status::CMD_TIMEOUT);
                return Err(Error::Timeout);
            }
            if st & status::CMD_CRC_FAIL != 0 {
                regs.mci_clear().write(status::CMD_CRC_FAIL);
                // CMD1/CMD41/CMD5 use R3/R4: CRC fail is expected
                if cmd.index == 1 || cmd.index == 41 || cmd.index == 5 {
                    let mut resp = CmdResponse { words: [0; 4], status: st };
                    resp.words[0] = regs.mci_resp(0).read();
                    return Ok((resp, false));
                }
                return Err(Error::CrcFail);
            }
            let _ = i; // avoid unused warning
        }
        Err(Error::Timeout)
    }

    /// sdcc_cleanup: write a zeroed command config to stop the command engine.
    fn cleanup(&mut self) {
        let regs = &self.regs;
        regs.mci_argument().write(0);
        regs.mci_cmd().write(0);
        regs.wait_mclk_stable();
    }

    /// Poll PROG_DONE or fall back to CMD13 for busy wait.
    fn busy_wait_inner(&mut self, rca: u16) -> Result<(), Error> {
        let regs = &self.regs;
        for _ in 0..0x80000u32 {
            let st = regs.read_status();
            if st & status::PROG_DONE != 0 {
                regs.mci_clear().write(status::PROG_DONE);
                return Ok(());
            }
            delay_us(10);
        }
        // Fallback: CMD13
        let state = self.get_card_state_inner(rca)?;
        if state == 4 { Ok(()) } else { Err(Error::BusyTimeout) }
    }

    fn get_card_state_inner(&mut self, rca: u16) -> Result<u8, Error> {
        let c = cmd13(rca);
        self.pre_cmd_hook(&c);
        let (resp, _) = self.setup_data_xfer(&c)?;
        self.cleanup();
        Ok(((resp.words[0] >> 9) & 0xF) as u8)
    }

    /// PIO burst read: read 8 words from FIFO while RX_FIFO_HFULL.
    fn pio_burst_read(&self, buf: &mut [u32]) -> usize {
        let regs = &self.regs;
        let mut offset = 0;
        while regs.read_status() & status::RX_FIFO_HFULL != 0 && offset + 8 <= buf.len() {
            let fifo = regs.dma_fifo();
            for i in 0..8 {
                buf[offset + i] = fifo.read();
            }
            offset += 8;
        }
        offset * 4 // bytes read
    }

    /// PIO burst write: write 8 words to FIFO while TX_FIFO_HFULL.
    fn pio_burst_write(&self, buf: &[u32]) -> usize {
        let regs = &self.regs;
        let mut offset = 0;
        // Write first burst
        if offset + 8 <= buf.len() {
            let fifo = regs.dma_fifo();
            for i in 0..8 {
                fifo.write(buf[offset + i]);
            }
            offset += 8;
        }
        // Continue while FIFO has room
        while offset + 8 <= buf.len() {
            loop {
                let st = regs.read_status();
                if st & status::WRITE_ERRORS != 0 { return offset * 4; }
                if st & status::TX_FIFO_HFULL != 0 { break; }
            }
            let fifo = regs.dma_fifo();
            for i in 0..8 {
                fifo.write(buf[offset + i]);
            }
            offset += 8;
        }
        offset * 4
    }

    /// Pre-write setup: set DATA_TIMER and DATA_LENGTH.
    fn pre_write_setup(&mut self, sector_size: u32, clock_khz: u32, num_blocks: u32) -> u32 {
        let regs = &self.regs;
        let timeout_ms: u32 = if clock_khz == 0 { 5000 * 50000 } else { clock_khz * 5000 };
        regs.mci_data_timer().write(timeout_ms);
        let total = sector_size * num_blocks;
        regs.mci_data_length().write(total);
        total
    }

    /// Set transfer mode in MCI_DATA_CTL.
    /// sector_size goes into bits [16:4] as the block size (typically 512 = 0x200).
    fn set_transfer_mode(&mut self, sector_size: u32, is_read: bool) {
        let regs = &self.regs;
        let mut val = sector_size << 4; // bits [16:4] = block size
        val |= 1; // bit 0: data path ENABLE
        if is_read {
            val |= 2; // bit 1: direction = read
        }
        regs.mci_data_ctl().write(val);
        regs.wait_mclk_stable();
    }

    /// Wait for DATA_END after a transfer, checking for errors.
    fn wait_data_end(&self) -> Result<(), Error> {
        let regs = &self.regs;
        for _ in 0..0x80000u32 {
            let st = regs.read_status();
            if st & status::WRITE_ERRORS != 0 { return Err(Error::DataError(st)); }
            if st & status::READ_ERRORS != 0 { return Err(Error::DataError(st)); }
            if st & status::DATA_END != 0 {
                regs.clear_all_status();
                return Ok(());
            }
        }
        Err(Error::Timeout)
    }

    /// Debug helper: dump key MCI registers over USB.
    fn dbg_status(label: &str, regs: &SdccRegs) {
        use crate::usb;
        let mut tmp = [0u8; 128];
        let mut p = 0usize;
        for &b in label.as_bytes() { tmp[p] = b; p += 1; }
        for &b in b": S=" { tmp[p] = b; p += 1; }
        p = Self::fmt_hex32(&mut tmp, p, regs.read_status());
        for &b in b" D=" { tmp[p] = b; p += 1; }
        p = Self::fmt_hex32(&mut tmp, p, regs.mci_data_ctl().read());
        for &b in b" C=" { tmp[p] = b; p += 1; }
        p = Self::fmt_hex32(&mut tmp, p, regs.mci_cmd().read());
        for &b in b" L=" { tmp[p] = b; p += 1; }
        p = Self::fmt_hex32(&mut tmp, p, regs.mci_data_length().read());
        tmp[p] = b'\r'; p += 1;
        tmp[p] = b'\n'; p += 1;
        usb::write(&tmp[..p]);
    }

    fn fmt_hex32(buf: &mut [u8], pos: usize, val: u32) -> usize {
        let hex = b"0123456789abcdef";
        let mut p = pos;
        for i in (0..8).rev() {
            buf[p] = hex[((val >> (i * 4)) & 0xF) as usize];
            p += 1;
        }
        p
    }
}

impl SdccHw for SdccDriver {
    fn send_cmd(&mut self, cmd: &MmcCmd) -> Result<CmdResponse, Error> {
        self.pre_cmd_hook(cmd);

        if cmd.index == 0 {
            // CMD0: poll for CMD_SENT
            let regs = &self.regs;
            for i in 0..800u32 {
                let st = regs.read_status();
                if st & status::CMD_SENT != 0 {
                    regs.mci_clear().write(status::CMD_SENT);
                    // Wait for CMD_SENT to clear
                    for _ in i..800 {
                        let st2 = regs.read_status();
                        if st2 & status::CMD_SENT == 0 {
                            return Ok(CmdResponse::default());
                        }
                        delay_us(10);
                    }
                    return Err(Error::Timeout);
                }
                delay_us(10);
            }
            return Err(Error::Timeout);
        }

        let (resp, busy_clear) = self.setup_data_xfer(cmd)?;

        // Busy wait if needed
        if matches!(cmd.resp_type, RespType::R1b) && !busy_clear {
            // We need rca from the response or from the caller
            // For CMD6/CMD12, rca is in the cmd.arg or we use 2 (standard eMMC RCA)
            // This is a simplification — the real code passes dev->rca
            // For now, we just poll PROG_DONE
            let regs = &self.regs;
            for _ in 0..0x80000u32 {
                let st = regs.read_status();
                if st & status::PROG_DONE != 0 {
                    regs.mci_clear().write(status::PROG_DONE);
                    break;
                }
                delay_us(10);
            }
        }

        self.cleanup();
        Ok(resp)
    }

    fn read_data(&mut self, cmd: &MmcCmd, buf: &mut [u8]) -> Result<(), Error> {
        let total = buf.len() as u32;
        let num_blocks = total / 512;

        self.pre_write_setup(512, 0, num_blocks);

        // Arm data path BEFORE the command (matches C code)
        self.set_transfer_mode(512, true);

        // Send the read command
        self.pre_cmd_hook(cmd);
        let (_resp, _) = self.setup_data_xfer(cmd)?;

        // Cleanup command engine
        self.cleanup();

        // PIO read from FIFO
        let regs = &self.regs;
        let mut byte_count = total as i32;
        let buf_words = unsafe {
            core::slice::from_raw_parts_mut(buf.as_mut_ptr() as *mut u32, buf.len() / 4)
        };
        let mut word_idx = 0;

        while byte_count > 0 {
            let st = regs.read_status();
            if st & status::READ_ERRORS != 0 {
                regs.clear_all_status();
                self.cleanup();
                return Err(Error::DataError(st));
            }
            if st & status::RX_DATA_AVAIL != 0 {
                if st & status::RX_FIFO_HFULL != 0 && word_idx + 8 <= buf_words.len() {
                    // Burst read 8 words
                    let fifo = regs.dma_fifo();
                    for i in 0..8 {
                        buf_words[word_idx + i] = fifo.read();
                    }
                    word_idx += 8;
                    byte_count -= 32;
                } else if word_idx < buf_words.len() {
                    buf_words[word_idx] = regs.mci_fifo().read();
                    word_idx += 1;
                    byte_count -= 4;
                }
            }
        }

        regs.clear_all_status();

        // Clear transfer mode
        regs.mci_data_ctl().write(0);
        regs.wait_mclk_stable();

        self.cleanup();
        Ok(())
    }


    fn write_data(&mut self, cmd: &MmcCmd, buf: &[u8]) -> Result<(), Error> {
        let total = buf.len() as u32;
        let num_blocks = total / 512;

        self.pre_write_setup(512, 0, num_blocks);
        self.set_transfer_mode(512, false);

        // Send the command
        self.pre_cmd_hook(cmd);
        let (_resp, _) = self.setup_data_xfer(cmd)?;

        // PIO write to FIFO
        let regs = &self.regs;
        let buf_words = unsafe {
            core::slice::from_raw_parts(buf.as_ptr() as *const u32, buf.len() / 4)
        };

        regs.clear_all_status();
        let mut word_idx = 0;
        let mut byte_count = total as i32;

        while byte_count > 0 {
            let st = regs.read_status();
            if st & status::WRITE_ERRORS != 0 {
                regs.clear_all_status();
                self.cleanup();
                return Err(Error::DataError(st));
            }
            if st & status::DATA_BLK_END != 0 {
                continue; // skip block boundary
            }
            if st & status::TX_FIFO_HFULL != 0 {
                if word_idx + 8 <= buf_words.len() && byte_count >= 32 {
                    // Burst write 8 words
                    let fifo = regs.dma_fifo();
                    for i in 0..8 {
                        fifo.write(buf_words[word_idx + i]);
                    }
                    word_idx += 8;
                    byte_count -= 32;
                    continue;
                }
            }
            // Single word write
            if word_idx < buf_words.len() {
                regs.mci_fifo().write(buf_words[word_idx]);
                word_idx += 1;
                byte_count -= 4;
            }
        }

        // Wait for DATA_END
        self.wait_data_end()?;

        // Clear transfer mode
        regs.mci_data_ctl().write(0);
        regs.wait_mclk_stable();

        self.cleanup();
        Ok(())
    }

    fn wait_busy(&mut self) -> Result<(), Error> {
        self.busy_wait_inner(2) // default eMMC RCA = 2
    }

    fn wait_card_ready(&mut self, rca: u16) -> Result<(), Error> {
        for _ in 0..0x80000u32 {
            let state = self.get_card_state_inner(rca)?;
            if state == 4 { return Ok(()); }
            delay_us(100);
        }
        Err(Error::Timeout)
    }

    fn set_clock(&mut self, khz: u32) {
        crate::platform::sdcc_set_clock_rate(khz);
    }

    fn init_controller(&mut self) -> Result<(), Error> {
        let regs = &self.regs;

        // TLMM pad config
        let pad0 = crate::mmio::Reg32::new(0x0110_a000);
        let pad1 = crate::mmio::Reg32::new(0x0111_1000);
        pad0.write((pad0.read() & 0x6000) + 0x1fdb);
        pad1.write(pad1.read() | 2);

        // Enable SDHCI mode
        regs.mci_hc_mode().modify(|v| v | 1);

        // SDHCI software reset
        regs.hc_reset().write(1);
        for _ in 0..100_000u32 {
            if regs.hc_reset().read() & 1 == 0 { break; }
            delay_us(1);
        }

        // Switch back to MCI mode
        regs.mci_hc_mode().modify(|v| v & !1);
        regs.wait_mclk_stable();

        // Clear command and data state
        regs.mci_cmd().write(0);
        regs.wait_mclk_stable();
        regs.mci_data_ctl().write(0);
        regs.wait_mclk_stable();

        // Clear all status
        regs.mci_clear().write(status::ALL_CLEAR);

        // Configure MCI_CLK
        regs.mci_clk().modify(|v| {
            let mut c = v;
            c |= 0x100;     // bit 8: CLK_ENABLE
            c |= 0x200;     // bit 9: FLOW_CTRL (set by mmc_classify_error in C)
            c |= 0x1000;    // bit 12: FLOW_ENA
            c |= 0x8000;    // bit 15: SELECT_IN feedback
            c |= 0x20_0000; // bit 21: vendor
            c &= !0xC00;    // bits 11:10: WIDEBUS = 00
            c
        });
        regs.wait_mclk_stable();

        // Clear vendor status, disable interrupts
        regs.mci_clear().write(0x40_0000);
        regs.mci_int_mask0().write(0);

        // Power on
        regs.mci_power().modify(|v| v | 1);
        regs.wait_mclk_stable();

        Ok(())
    }

    fn get_card_state(&mut self, rca: u16) -> Result<u8, Error> {
        self.get_card_state_inner(rca)
    }
}
