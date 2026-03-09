/// Volatile MMIO register access — the single unsafe boundary for all
/// hardware register reads and writes.

#[derive(Clone, Copy)]
pub struct Reg32(u32);

impl Reg32 {
    pub const fn new(addr: u32) -> Self {
        Self(addr)
    }

    #[inline(always)]
    pub fn read(self) -> u32 {
        unsafe { core::ptr::read_volatile(self.0 as *const u32) }
    }

    #[inline(always)]
    pub fn write(self, val: u32) {
        unsafe { core::ptr::write_volatile(self.0 as *mut u32, val) }
    }

    #[inline(always)]
    pub fn modify(self, f: impl FnOnce(u32) -> u32) {
        self.write(f(self.read()))
    }
}

#[derive(Clone, Copy)]
pub struct Reg16(u32);

impl Reg16 {
    pub const fn new(addr: u32) -> Self {
        Self(addr)
    }

    #[inline(always)]
    pub fn read(self) -> u16 {
        unsafe { core::ptr::read_volatile(self.0 as *const u16) }
    }

    #[inline(always)]
    pub fn write(self, val: u16) {
        unsafe { core::ptr::write_volatile(self.0 as *mut u16, val) }
    }
}

#[derive(Clone, Copy)]
pub struct Reg8(u32);

impl Reg8 {
    pub const fn new(addr: u32) -> Self {
        Self(addr)
    }

    #[inline(always)]
    pub fn read(self) -> u8 {
        unsafe { core::ptr::read_volatile(self.0 as *const u8) }
    }

    #[inline(always)]
    pub fn write(self, val: u8) {
        unsafe { core::ptr::write_volatile(self.0 as *mut u8, val) }
    }
}
