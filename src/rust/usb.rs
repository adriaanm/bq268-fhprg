/// USB bulk I/O — inherits PBL's USB session.
///
/// Port of usb.c. All DMA buffers in DDR via link_section.
/// USB DMA cannot access OCIMEM (0x0804xxxx).
use crate::mmio::Reg32;
use crate::platform::{MSM_USB_BASE, dsb};

// Register addresses
const USB_USBSTS: u32 = MSM_USB_BASE + 0x0144;
const USB_USBINTR: u32 = MSM_USB_BASE + 0x0148;
const USB_ENDPOINTLISTADDR: u32 = MSM_USB_BASE + 0x0158;
const USB_ENDPTPRIME: u32 = MSM_USB_BASE + 0x01B0;
const USB_ENDPTFLUSH: u32 = MSM_USB_BASE + 0x01B4;
const USB_ENDPTSTAT: u32 = MSM_USB_BASE + 0x01B8;
const USB_ENDPTCOMPLETE: u32 = MSM_USB_BASE + 0x01BC;

// Endpoint bits
const EPT_RX_1: u32 = 1 << 1;
const EPT_TX_1: u32 = 1 << 17;

// Status bits
const STS_URI: u32 = 1 << 6;

// dTD constants
const TERMINATE: u32 = 1;
const INFO_IOC: u32 = 1 << 15;
const INFO_ACTIVE: u32 = 1 << 7;

const USB_BUF_SIZE: usize = 4096;

/// dTD (device Transfer Descriptor) — 32 bytes, 32-byte aligned.
#[repr(C, align(32))]
struct EptQueueItem {
    next: u32,
    info: u32,
    page0: u32,
    page1: u32,
    page2: u32,
    page3: u32,
    page4: u32,
    _reserved: u32,
}

/// DDR-resident buffers — USB DMA can only access DDR.
#[link_section = ".ddr_bss"]
static mut DTD_BULK_OUT: EptQueueItem = EptQueueItem {
    next: 0, info: 0, page0: 0, page1: 0, page2: 0, page3: 0, page4: 0, _reserved: 0,
};
#[link_section = ".ddr_bss"]
static mut DTD_BULK_IN: EptQueueItem = EptQueueItem {
    next: 0, info: 0, page0: 0, page1: 0, page2: 0, page3: 0, page4: 0, _reserved: 0,
};

#[link_section = ".ddr_bss"]
static mut USB_RX_BUF: [u8; USB_BUF_SIZE] = [0u8; USB_BUF_SIZE];
#[link_section = ".ddr_bss"]
static mut USB_TX_BUF: [u8; USB_BUF_SIZE] = [0u8; USB_BUF_SIZE];

static mut USB_ONLINE: bool = false;
static mut DQH_EP1_OUT: u32 = 0; // address of dQH for EP1 OUT
static mut DQH_EP1_IN: u32 = 0;  // address of dQH for EP1 IN

fn readl(addr: u32) -> u32 { Reg32::new(addr).read() }
fn writel(val: u32, addr: u32) { Reg32::new(addr).write(val); }

/// Prime an endpoint: set up dTD, link into dQH, write ENDPTPRIME.
unsafe fn prime_ep(dqh_addr: u32, dtd: *mut EptQueueItem, buf_addr: u32, len: u32, prime_bit: u32) {
    // Wait for previous prime
    while readl(USB_ENDPTPRIME) & prime_bit != 0 {}

    // Flush if active
    if readl(USB_ENDPTSTAT) & prime_bit != 0 {
        writel(prime_bit, USB_ENDPTFLUSH);
        while readl(USB_ENDPTFLUSH) & prime_bit != 0 {}
    }

    // Clear stale completion
    if readl(USB_ENDPTCOMPLETE) & prime_bit != 0 {
        writel(prime_bit, USB_ENDPTCOMPLETE);
    }

    // Set up dTD
    (*dtd).next = TERMINATE;
    (*dtd).info = (len << 16) | INFO_IOC | INFO_ACTIVE;
    (*dtd).page0 = buf_addr;
    (*dtd).page1 = (buf_addr & 0xFFFF_F000) + 0x1000;
    (*dtd).page2 = (buf_addr & 0xFFFF_F000) + 0x2000;
    (*dtd).page3 = (buf_addr & 0xFFFF_F000) + 0x3000;
    (*dtd).page4 = (buf_addr & 0xFFFF_F000) + 0x4000;
    dsb();

    // Link into dQH: current=0, next=dtd, info=0
    let dqh = dqh_addr as *mut u32;
    // dQH layout: [0]=config, [1]=current, [2]=next, [3]=info
    core::ptr::write_volatile(dqh.add(1), 0); // current
    core::ptr::write_volatile(dqh.add(2), dtd as u32); // next
    core::ptr::write_volatile(dqh.add(3), 0); // info (clear overlay)
    dsb();

    // Prime
    writel(prime_bit, USB_ENDPTPRIME);
}

/// Poll until transfer completes or bus reset. Returns true on success.
unsafe fn poll_complete(bit: u32) -> bool {
    loop {
        if readl(USB_USBSTS) & STS_URI != 0 {
            writel(STS_URI, USB_USBSTS);
            USB_ONLINE = false;
            return false;
        }
        if readl(USB_ENDPTCOMPLETE) & bit != 0 {
            writel(bit, USB_ENDPTCOMPLETE);
            return true;
        }
    }
}

/// Initialize USB — inherit PBL's session.
pub fn init() {
    unsafe {
        USB_ONLINE = false;

        let pbl_eplist = readl(USB_ENDPOINTLISTADDR);
        DQH_EP1_OUT = pbl_eplist + 2 * 64;
        DQH_EP1_IN = pbl_eplist + 3 * 64;

        // Disable interrupts
        writel(0, USB_USBINTR);

        // Flush all endpoints
        writel(0xFFFF_FFFF, USB_ENDPTFLUSH);
        while readl(USB_ENDPTFLUSH) != 0 {}

        // Clear status
        writel(readl(USB_USBSTS), USB_USBSTS);
        writel(readl(USB_ENDPTCOMPLETE), USB_ENDPTCOMPLETE);

        USB_ONLINE = true;
    }
}

/// Blocking bulk OUT read on EP1.
pub fn read(buf: &mut [u8]) -> i32 {
    unsafe {
        if !USB_ONLINE { return -1; }
        if buf.is_empty() { return 0; }

        let xfer_len = buf.len().min(USB_BUF_SIZE) as u32;

        prime_ep(DQH_EP1_OUT, &raw mut DTD_BULK_OUT,
                 USB_RX_BUF.as_ptr() as u32, xfer_len, EPT_RX_1);

        if !poll_complete(EPT_RX_1) { return -1; }

        dsb();
        let remaining = (DTD_BULK_OUT.info >> 16) & 0x7FFF;
        let actual = (xfer_len - remaining) as usize;

        for i in 0..actual {
            buf[i] = USB_RX_BUF[i];
        }
        actual as i32
    }
}

/// Blocking bulk IN write on EP1.
pub fn write(buf: &[u8]) -> i32 {
    unsafe {
        if !USB_ONLINE { return -1; }
        if buf.is_empty() { return 0; }

        let xfer_len = buf.len().min(USB_BUF_SIZE) as u32;

        for i in 0..xfer_len as usize {
            USB_TX_BUF[i] = buf[i];
        }
        dsb();

        prime_ep(DQH_EP1_IN, &raw mut DTD_BULK_IN,
                 USB_TX_BUF.as_ptr() as u32, xfer_len, EPT_TX_1);

        if !poll_complete(EPT_TX_1) { return -1; }

        dsb();
        let remaining = (DTD_BULK_IN.info >> 16) & 0x7FFF;
        (xfer_len - remaining) as i32
    }
}

/// Write a string slice over USB.
pub fn write_str(s: &str) -> i32 {
    write(s.as_bytes())
}
