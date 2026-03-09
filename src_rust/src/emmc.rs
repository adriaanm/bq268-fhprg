/// eMMC state machine — card init, read, write, erase.
///
/// Generic over SdccHw so it's testable with mocks.
/// Port of card_init.c + emmc.c.
use crate::sdcc::*;

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum CardType {
    None,
    Mmc,      // type 2
    Emmc,     // type 6 (sector-addressed)
}

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum CardState {
    Idle,
    Ready,
    Identification,
    Standby,
    Transfer,
}

pub struct MmcDev {
    pub card_type: CardType,
    pub rca: u16,
    pub card_state: CardState,
    pub sector_size: u32,
    pub clock_khz: u32,
    pub speed_grade: u8,
}

impl MmcDev {
    fn new() -> Self {
        Self {
            card_type: CardType::None,
            rca: 0,
            card_state: CardState::Idle,
            sector_size: 512,
            clock_khz: 0,
            speed_grade: 2,
        }
    }
}

pub struct Emmc<H: SdccHw> {
    pub hw: H,
    pub dev: MmcDev,
    inited: bool,
}

impl<H: SdccHw> Emmc<H> {
    pub fn new(hw: H) -> Self {
        Self {
            hw,
            dev: MmcDev::new(),
            inited: false,
        }
    }

    pub fn is_inited(&self) -> bool {
        self.inited
    }

    /// Full init: controller init + card identification (CMD0→CMD1→CMD2→CMD3→CMD7→CMD16).
    pub fn open(&mut self) -> Result<(), Error> {
        if self.inited {
            return Ok(());
        }

        // Initialize controller (SDHCI reset + MCI config)
        self.hw.init_controller()?;

        // Set initial clock to 400kHz
        self.hw.set_clock(400);

        // Enable MCI_POWER, flow control
        // (already done in init_controller)

        // CMD0: GO_IDLE_STATE
        self.hw.send_cmd(&cmd0())?;
        self.dev.card_state = CardState::Idle;

        // CMD1: SEND_OP_COND — poll until card ready
        let mut card_type = CardType::Mmc;
        for _ in 0..20u32 {
            let resp = self.hw.send_cmd(&cmd1(0x40FF_8000))?;
            if resp.words[0] & 0x8000_0000 != 0 {
                // Card ready
                if resp.words[0] & 0x4000_0000 != 0 && resp.words[0] & 0x2000_0000 == 0 {
                    card_type = CardType::Emmc; // sector-addressed
                }
                self.dev.card_type = card_type;
                self.dev.card_state = CardState::Ready;
                break;
            }
            crate::platform::delay_us(50_000);
        }
        if self.dev.card_state != CardState::Ready {
            return Err(Error::CardNotResponding);
        }

        // CMD2: ALL_SEND_CID
        let _cid = self.hw.send_cmd(&cmd2())?;
        self.dev.card_state = CardState::Identification;

        // CMD3: SEND_RELATIVE_ADDR (for eMMC, we assign RCA=2)
        let rca: u16 = 2;
        let _resp = self.hw.send_cmd(&cmd3(rca))?;
        self.dev.rca = rca;
        self.dev.card_state = CardState::Standby;

        // CMD9: SEND_CSD (get card parameters)
        let _csd = self.hw.send_cmd(&cmd9(rca))?;
        self.dev.speed_grade = 3; // assume HS52 capable

        // CMD7: SELECT_CARD → transfer state
        let _resp = self.hw.send_cmd(&cmd7(rca))?;
        self.dev.card_state = CardState::Transfer;

        // CMD16: SET_BLOCKLEN = 512
        let _resp = self.hw.send_cmd(&cmd16(512))?;
        self.dev.sector_size = 512;

        // Speed up clock
        self.hw.set_clock(26_000);
        self.dev.clock_khz = 26_000;

        self.inited = true;
        Ok(())
    }

    /// Read sectors into buf. buf.len() must be a multiple of 512.
    pub fn read(&mut self, sector: u32, buf: &mut [u8]) -> Result<(), Error> {
        if !self.inited { return Err(Error::InvalidState); }
        let num_blocks = buf.len() / 512;
        let cmd = if num_blocks == 1 { cmd17(sector) } else { cmd18(sector) };
        self.hw.read_data(&cmd, buf)?;
        if num_blocks > 1 {
            // CMD12 STOP for multi-block
            let _ = self.hw.send_cmd(&cmd12());
        }
        Ok(())
    }

    /// Write sectors from buf. buf.len() must be a multiple of 512.
    pub fn write(&mut self, sector: u32, buf: &[u8]) -> Result<(), Error> {
        if !self.inited { return Err(Error::InvalidState); }
        let num_blocks = buf.len() / 512;
        let cmd = if num_blocks == 1 { cmd24(sector) } else { cmd25(sector) };
        self.hw.write_data(&cmd, buf)?;
        if num_blocks > 1 {
            let _ = self.hw.send_cmd(&cmd12());
        }
        // Wait for card to return to transfer state
        self.hw.wait_card_ready(self.dev.rca)?;
        Ok(())
    }

    /// Erase sectors: CMD35 → CMD36 → CMD38.
    pub fn erase(&mut self, start: u32, count: u32) -> Result<(), Error> {
        if !self.inited { return Err(Error::InvalidState); }

        self.hw.send_cmd(&cmd35(start))?;
        self.hw.send_cmd(&cmd36(start + count - 1))?;

        // CMD38 with busy wait
        let c = MmcCmd {
            index: 38, arg: 0,
            resp_type: RespType::R1b,
            flags: CmdFlags::empty(),
        };
        self.hw.send_cmd(&c)?;
        self.hw.wait_card_ready(self.dev.rca)?;
        Ok(())
    }

    /// Get card state via CMD13.
    pub fn status(&mut self) -> Result<u8, Error> {
        self.hw.get_card_state(self.dev.rca)
    }
}
