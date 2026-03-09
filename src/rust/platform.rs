/// MSM8909 platform constants, GPIO/LED control, delay, libc stubs.
use crate::mmio::Reg32;

// GCC (Global Clock Controller)
pub const CLK_CTL_BASE: u32 = 0x0180_0000;
pub const GPLL0_MODE: u32 = CLK_CTL_BASE + 0x21000;
pub const APCS_GPLL_ENA_VOTE: u32 = CLK_CTL_BASE + 0x45000;

// SDCC1 clock registers
pub const SDCC1_CMD_RCGR: u32 = CLK_CTL_BASE + 0x42004;
pub const SDCC1_CFG_RCGR: u32 = CLK_CTL_BASE + 0x42008;
pub const SDCC1_M: u32 = CLK_CTL_BASE + 0x4200C;
pub const SDCC1_N: u32 = CLK_CTL_BASE + 0x42010;
pub const SDCC1_D: u32 = CLK_CTL_BASE + 0x42014;
pub const SDCC1_APPS_CBCR: u32 = CLK_CTL_BASE + 0x42018;
pub const SDCC1_AHB_CBCR: u32 = CLK_CTL_BASE + 0x4201C;

// Clock bit defs
pub const CBCR_BRANCH_ENABLE_BIT: u32 = 1 << 0;
pub const CBCR_BRANCH_OFF_BIT: u32 = 1 << 31;
pub const CMD_UPDATE_BIT: u32 = 1 << 0;

// TLMM GPIO
pub const TLMM_BASE: u32 = 0x0100_0000;
pub const fn gpio_cfg_addr(n: u32) -> u32 { TLMM_BASE + n * 0x1000 }
pub const fn gpio_in_out_addr(n: u32) -> u32 { TLMM_BASE + n * 0x1000 + 0x4 }

pub const GPIO_OE_ENABLE: u32 = 1;
pub const GPIO_OE_SHIFT: u32 = 9;
pub const GPIO_OUT_BIT: u32 = 1 << 1;

// BQ268 LEDs
pub const LED_RED_GPIO: u32 = 68;
pub const LED_GREEN_GPIO: u32 = 69;

// DDR
pub const SDRAM_START_ADDR: u32 = 0x8000_0000;

// USB base
pub const MSM_USB_BASE: u32 = 0x078D_9000;

// SDCC
pub const MSM_SDC1_BASE: u32 = 0x0782_4000;
pub const MSM_SDC1_SDHCI_BASE: u32 = 0x0782_4900;

pub fn led_init(gpio: u32) {
    Reg32::new(gpio_cfg_addr(gpio)).write(GPIO_OE_ENABLE << GPIO_OE_SHIFT);
}

pub fn led_on(gpio: u32) {
    Reg32::new(gpio_in_out_addr(gpio)).write(GPIO_OUT_BIT);
}

pub fn led_off(gpio: u32) {
    Reg32::new(gpio_in_out_addr(gpio)).write(0);
}

/// Data synchronization barrier
#[inline(always)]
pub fn dsb() {
    unsafe { core::arch::asm!("dsb", options(nostack, preserves_flags)) }
}

/// Data memory barrier
#[inline(always)]
pub fn dmb() {
    unsafe { core::arch::asm!("dmb", options(nostack, preserves_flags)) }
}

/// Instruction synchronization barrier
#[inline(always)]
pub fn isb() {
    unsafe { core::arch::asm!("isb", options(nostack)) }
}

/// Read SCTLR (System Control Register)
pub fn read_sctlr() -> u32 {
    let val: u32;
    unsafe { core::arch::asm!("mrc p15, 0, {}, c1, c0, 0", out(reg) val, options(nostack, nomem)) }
    val
}

/// Read TTBR0
pub fn read_ttbr0() -> u32 {
    let val: u32;
    unsafe { core::arch::asm!("mrc p15, 0, {}, c2, c0, 0", out(reg) val, options(nostack, nomem)) }
    val
}

/// Read TTBR1
pub fn read_ttbr1() -> u32 {
    let val: u32;
    unsafe { core::arch::asm!("mrc p15, 0, {}, c2, c0, 1", out(reg) val, options(nostack, nomem)) }
    val
}

/// Read TTBCR
pub fn read_ttbcr() -> u32 {
    let val: u32;
    unsafe { core::arch::asm!("mrc p15, 0, {}, c2, c0, 2", out(reg) val, options(nostack, nomem)) }
    val
}

/// Read DACR
pub fn read_dacr() -> u32 {
    let val: u32;
    unsafe { core::arch::asm!("mrc p15, 0, {}, c3, c0, 0", out(reg) val, options(nostack, nomem)) }
    val
}

/// Read DFSR
pub fn read_dfsr() -> u32 {
    let val: u32;
    unsafe { core::arch::asm!("mrc p15, 0, {}, c5, c0, 0", out(reg) val, options(nostack, nomem)) }
    val
}

/// Read DFAR
pub fn read_dfar() -> u32 {
    let val: u32;
    unsafe { core::arch::asm!("mrc p15, 0, {}, c6, c0, 0", out(reg) val, options(nostack, nomem)) }
    val
}

/// Read VBAR
pub fn read_vbar() -> u32 {
    let val: u32;
    unsafe { core::arch::asm!("mrc p15, 0, {}, c12, c0, 0", out(reg) val, options(nostack, nomem)) }
    val
}

/// Microsecond delay using ARM generic timer (CNTPCT at 19.2 MHz).
pub fn delay_us(us: u32) {
    let (lo, hi): (u32, u32);
    unsafe { core::arch::asm!("mrrc p15, 0, {lo}, {hi}, c14", lo = out(reg) lo, hi = out(reg) hi, options(nostack, nomem)) }
    let start = ((hi as u64) << 32) | (lo as u64);
    let target = start + (us as u64) * 19;
    loop {
        let (lo2, hi2): (u32, u32);
        unsafe { core::arch::asm!("mrrc p15, 0, {lo}, {hi}, c14", lo = out(reg) lo2, hi = out(reg) hi2, options(nostack, nomem)) }
        let now = ((hi2 as u64) << 32) | (lo2 as u64);
        if now >= target {
            break;
        }
    }
}

/// SDCC1 clock rate configuration.
/// Writes M/N/D and CFG_RCGR, then triggers CMD_RCGR update.
pub fn sdcc_set_clock_rate(freq_khz: u32) {
    let (cfg, m, n, d) = if freq_khz <= 400 {
        // 400 KHz: CXO/12, M=1 N=4 dual-edge
        (0x2017u32, 1u32, 0xFFFF_FFFDu32, 0xFFFF_FFFCu32)
    } else if freq_khz <= 50_000 {
        // 50 MHz: GPLL0/16
        (0x011F, 0, 0, 0)
    } else if freq_khz <= 100_000 {
        // 100 MHz: GPLL0/8
        (0x010F, 0, 0, 0)
    } else {
        // 200 MHz: GPLL0/4
        (0x0107, 0, 0, 0)
    };

    Reg32::new(SDCC1_M).write(m);
    Reg32::new(SDCC1_N).write(n);
    Reg32::new(SDCC1_D).write(d);
    Reg32::new(SDCC1_CFG_RCGR).write(cfg);

    // Trigger update, poll until complete
    let cmd_rcgr = Reg32::new(SDCC1_CMD_RCGR);
    cmd_rcgr.write(cmd_rcgr.read() | CMD_UPDATE_BIT);
    while cmd_rcgr.read() & CMD_UPDATE_BIT != 0 {}
}

/// Enable SDCC1 branch clocks at 400kHz identification rate.
pub fn sdcc_clock_init() {
    sdcc_set_clock_rate(400);

    let apps = Reg32::new(SDCC1_APPS_CBCR);
    apps.write(CBCR_BRANCH_ENABLE_BIT);
    while apps.read() & CBCR_BRANCH_OFF_BIT != 0 {}

    let ahb = Reg32::new(SDCC1_AHB_CBCR);
    ahb.write(CBCR_BRANCH_ENABLE_BIT);
    while ahb.read() & CBCR_BRANCH_OFF_BIT != 0 {}
}

// ---- libc stubs required by the linker ----

#[no_mangle]
pub unsafe extern "C" fn memset(s: *mut u8, c: i32, n: usize) -> *mut u8 {
    let mut p = s;
    for _ in 0..n {
        *p = c as u8;
        p = p.add(1);
    }
    s
}

#[no_mangle]
pub unsafe extern "C" fn memcpy(dest: *mut u8, src: *const u8, n: usize) -> *mut u8 {
    let mut d = dest;
    let mut s = src;
    for _ in 0..n {
        *d = *s;
        d = d.add(1);
        s = s.add(1);
    }
    dest
}

#[no_mangle]
pub unsafe extern "C" fn memcmp(s1: *const u8, s2: *const u8, n: usize) -> i32 {
    for i in 0..n {
        let a = *s1.add(i);
        let b = *s2.add(i);
        if a != b {
            return (a as i32) - (b as i32);
        }
    }
    0
}

// Called from entry.S
#[no_mangle]
pub extern "C" fn delay_us_export(us: u32) {
    delay_us(us);
}

#[no_mangle]
pub extern "C" fn qtimer_init() {}

// Page table and ICB config called from entry.S — keep as C-callable stubs
// The actual implementations are in entry.S / main.c in the C version;
// for the Rust port, entry.S calls setup_early_page_table and icb_config
// which we define here.

#[no_mangle]
pub static mut page_table: [u32; 4096] = [0u32; 4096];

const fn sect_dev(addr: u32) -> u32 {
    (addr & 0xFFF0_0000) | (3 << 10) | (1 << 2) | 2
}
const fn sect_mem(addr: u32) -> u32 {
    (addr & 0xFFF0_0000) | (3 << 10) | (1 << 3) | (1 << 2) | 2
}

#[no_mangle]
pub extern "C" fn setup_early_page_table() {
    unsafe {
        // Clear all entries
        for i in 0..4096 {
            page_table[i] = 0;
        }
        // IO: 0x00000000-0x07FFFFFF
        for i in 0..0x80u32 {
            page_table[i as usize] = sect_dev(i << 20);
        }
        // OCIMEM
        page_table[0x80] = sect_mem(0x0800_0000);
        // SYSTEM_IMEM
        page_table[0x86] = sect_dev(0x0860_0000);

        // Clean D-cache for page table
        let base = page_table.as_ptr() as u32;
        let mut a = base;
        while a < base + core::mem::size_of_val(&page_table) as u32 {
            core::arch::asm!("mcr p15, 0, {}, c7, c14, 1", in(reg) a, options(nostack));
            a += 32;
        }
        dsb();

        // Switch TTBR0
        let ttbr0_val = base | (1 << 0) | (1 << 3);
        core::arch::asm!("mcr p15, 0, {}, c2, c0, 0", in(reg) ttbr0_val, options(nostack));

        // Invalidate TLB
        core::arch::asm!("mcr p15, 0, {}, c8, c7, 0", in(reg) 0u32, options(nostack));
        dsb();
        isb();
    }
}

#[no_mangle]
pub extern "C" fn icb_config() {
    let w = |addr: u32, val: u32| Reg32::new(addr).write(val);
    w(0x00449210, 0x00000001);
    w(0x00450230, 0x00000000);
    w(0x00408210, 0x00000012);
    w(0x0040c210, 0x00000012);
    w(0x00410210, 0x00000012);
    w(0x00414210, 0x00000012);
    w(0x00418210, 0x80000012);
    w(0x0041c210, 0x00000012);
    w(0x00420210, 0x00000012);
    w(0x00408270, 0x00043210);
    w(0x00408274, 0x00043210);
    w(0x00408a04, 0x00000014);
    w(0x00408a08, 0x00000064);
    w(0x00408a24, 0x0000ffce);
    w(0x00408a28, 0x0000ff9c);
    w(0x00408a40, 0x80000000);
    w(0x00408300, 0x01000000);
    w(0x00408800, 0x02000000);
    w(0x00408a00, 0xfc000001);
    w(0x00410a04, 0x00000014);
    w(0x00410a08, 0x00000064);
    w(0x00410a24, 0x0000ffce);
    w(0x00410a28, 0x0000ff9c);
    w(0x00410a40, 0x80000000);
    w(0x00410300, 0x01000000);
    w(0x00410800, 0x02000000);
    w(0x00410a00, 0xfc000001);
    w(0x00400904, 0x00000206);
    w(0x00400908, 0x00600060);
    w(0x0040090c, 0x00270027);
    w(0x00400940, 0x00000010);
    w(0x00400900, 0x00000001);
}

/// Panic handler — required for no_std
#[panic_handler]
fn panic(_info: &core::panic::PanicInfo) -> ! {
    // Red LED on, hang
    led_on(LED_RED_GPIO);
    loop {}
}
