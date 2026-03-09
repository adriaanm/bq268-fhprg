/// Entry point — called from entry.S after hardware init.
///
/// Wires up USB, eMMC driver, and console. Never returns.
use crate::platform::{self, LED_RED_GPIO, LED_GREEN_GPIO};
use crate::usb;
use crate::sdcc::SdccDriver;
use crate::regs::SdccRegs;
use crate::emmc::Emmc;
use crate::console::Console;

#[no_mangle]
pub extern "C" fn main() -> ! {
    // LED init
    platform::led_init(LED_RED_GPIO);
    platform::led_init(LED_GREEN_GPIO);
    platform::led_off(LED_RED_GPIO);
    platform::led_off(LED_GREEN_GPIO);

    // Inherit PBL's USB session
    usb::init();

    // Create eMMC driver stack (monomorphized, zero overhead)
    let driver = SdccDriver::new(SdccRegs::slot0());
    let mut emmc: Emmc<SdccDriver> = Emmc::new(driver);

    // Run console (never returns)
    let mut console = Console::new(&mut emmc);
    console.run();
}
