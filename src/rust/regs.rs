/// SDCC register bank — typed accessors for MCI and SDHCI registers.
///
/// Hardcoded to slot 0 (eMMC). All MMIO access goes through mmio::Reg32.
use crate::mmio::{Reg32, Reg16, Reg8};

// MCI register offsets
pub const MCI_POWER: u32 = 0x00;
pub const MCI_CLK: u32 = 0x04;
pub const MCI_ARGUMENT: u32 = 0x08;
pub const MCI_CMD: u32 = 0x0C;
pub const MCI_RESP_0: u32 = 0x14;
pub const MCI_DATA_TIMER: u32 = 0x24;
pub const MCI_DATA_LENGTH: u32 = 0x28;
pub const MCI_DATA_CTL: u32 = 0x2C;
pub const MCI_STATUS: u32 = 0x34;
pub const MCI_CLEAR: u32 = 0x38;
pub const MCI_INT_MASK0: u32 = 0x3C;
pub const MCI_FIFO_COUNT: u32 = 0x44;
pub const MCI_STATUS2: u32 = 0x6C;
pub const MCI_HC_MODE: u32 = 0x78;
pub const MCI_FIFO: u32 = 0x80;
pub const MCI_PLL_STATUS: u32 = 0xDC;
pub const MCI_PLL_DIVIDER: u32 = 0xE4;
pub const MCI_PLL_MODE: u32 = 0xE8;

// MCI_STATUS bit definitions
pub mod status {
    pub const CMD_CRC_FAIL: u32 = 1 << 0;
    pub const DATA_CRC_FAIL: u32 = 1 << 1;
    pub const CMD_TIMEOUT: u32 = 1 << 2;
    pub const DATA_TIMEOUT: u32 = 1 << 3;
    pub const TX_UNDERRUN: u32 = 1 << 4;
    pub const RX_OVERRUN: u32 = 1 << 5;
    pub const CMD_RESP_END: u32 = 1 << 6;
    pub const CMD_SENT: u32 = 1 << 7;
    pub const DATA_END: u32 = 1 << 8;
    pub const TX_FIFO_HFULL: u32 = 1 << 14;
    pub const RX_FIFO_HFULL: u32 = 1 << 15;
    pub const DATA_BLK_END: u32 = 1 << 16;
    pub const RX_DATA_AVAIL: u32 = 1 << 21;
    pub const PROG_DONE: u32 = 1 << 23;

    /// All clearable status bits
    pub const ALL_CLEAR: u32 = 0x0180_07FF;

    /// Read-path error mask
    pub const READ_ERRORS: u32 = DATA_CRC_FAIL | DATA_TIMEOUT | RX_OVERRUN; // 0x2a
    /// Write-path error mask
    pub const WRITE_ERRORS: u32 = DATA_CRC_FAIL | DATA_TIMEOUT | TX_UNDERRUN; // 0x1a
}

// SDHCI HC register offsets (from hc_base)
pub const HC_RESET: u32 = 0x2F;

pub struct SdccRegs {
    pub mci_base: u32,
    pub hc_base: u32,
    pub dma_base: u32,
}

impl SdccRegs {
    pub const fn slot0() -> Self {
        Self {
            mci_base: 0x0782_4000,
            hc_base: 0x0782_4900,
            dma_base: 0x0782_4000,
        }
    }

    // MCI register accessors
    pub fn mci_power(&self) -> Reg32 { Reg32::new(self.mci_base + MCI_POWER) }
    pub fn mci_clk(&self) -> Reg32 { Reg32::new(self.mci_base + MCI_CLK) }
    pub fn mci_argument(&self) -> Reg32 { Reg32::new(self.mci_base + MCI_ARGUMENT) }
    pub fn mci_cmd(&self) -> Reg32 { Reg32::new(self.mci_base + MCI_CMD) }
    pub fn mci_resp(&self, idx: u32) -> Reg32 { Reg32::new(self.mci_base + MCI_RESP_0 + idx * 4) }
    pub fn mci_data_timer(&self) -> Reg32 { Reg32::new(self.mci_base + MCI_DATA_TIMER) }
    pub fn mci_data_length(&self) -> Reg32 { Reg32::new(self.mci_base + MCI_DATA_LENGTH) }
    pub fn mci_data_ctl(&self) -> Reg32 { Reg32::new(self.mci_base + MCI_DATA_CTL) }
    pub fn mci_status(&self) -> Reg32 { Reg32::new(self.mci_base + MCI_STATUS) }
    pub fn mci_clear(&self) -> Reg32 { Reg32::new(self.mci_base + MCI_CLEAR) }
    pub fn mci_int_mask0(&self) -> Reg32 { Reg32::new(self.mci_base + MCI_INT_MASK0) }
    pub fn mci_fifo(&self) -> Reg32 { Reg32::new(self.mci_base + MCI_FIFO) }
    pub fn mci_status2(&self) -> Reg32 { Reg32::new(self.mci_base + MCI_STATUS2) }
    pub fn mci_hc_mode(&self) -> Reg32 { Reg32::new(self.mci_base + MCI_HC_MODE) }
    pub fn mci_pll_status(&self) -> Reg32 { Reg32::new(self.mci_base + MCI_PLL_STATUS) }
    pub fn mci_pll_divider(&self) -> Reg32 { Reg32::new(self.mci_base + MCI_PLL_DIVIDER) }
    pub fn mci_pll_mode(&self) -> Reg32 { Reg32::new(self.mci_base + MCI_PLL_MODE) }

    // DMA/FIFO (same base as MCI for this controller)
    pub fn dma_fifo(&self) -> Reg32 { Reg32::new(self.dma_base + MCI_FIFO) }
    pub fn dma_status(&self) -> Reg32 { Reg32::new(self.mci_base + MCI_STATUS) }

    // SDHCI HC accessors
    pub fn hc_reset(&self) -> Reg8 { Reg8::new(self.hc_base + HC_RESET) }

    /// Poll MCI_STATUS2 bit 0 until clear (up to 1000 iterations).
    /// Called after writing POWER, CLK, CMD, DATA_CTL.
    pub fn wait_mclk_stable(&self) {
        for _ in 0..1000 {
            if self.mci_status2().read() & 1 == 0 {
                return;
            }
        }
    }

    /// Clear all pending MCI status bits.
    pub fn clear_all_status(&self) {
        self.mci_clear().write(status::ALL_CLEAR);
    }

    /// Read MCI_STATUS register.
    pub fn read_status(&self) -> u32 {
        self.mci_status().read()
    }
}
