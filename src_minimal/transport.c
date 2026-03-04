/* transport.c — USB transport layer.
 *
 * The actual USB transport is register-level MMIO to the Qualcomm DWC3
 * USB controller. These are stubs — the real implementations live at
 * 0x0802xxxx and 0x0803xxxx in the original binary, interacting with
 * USB endpoint registers and DMA descriptors.
 *
 * Since we control the client, the transport is not critical for
 * understanding the write path. Data flows:
 *   Client USB -> DWC3 controller -> RAM buffer -> eMMC via SDCC
 *
 * Sources: fhprg_802196c.c, fhprg_8030dac.c, fhprg_802cac4.c
 */
#include "firehose.h"

/* orig: 0x08021ca4 usb_read_complete — called when USB read finishes.
 * In the original, calls transport_read_data() then returns 0. */
int usb_read_complete()
{
    transport_read_data();
    return 0;
}

/* orig: 0x08031170 transport_read_data — receive data from USB host.
 *
 * The full implementation (~200 lines) handles:
 *   - Validation mode: verify SHA-256 hashes of received data
 *   - Normal mode: just receive via USB DMA
 *   - Hash table management for validated transfers
 *
 * Since we control the client and don't use validation, this is stubbed.
 * The critical path: data arrives in a RAM buffer, then handle_program
 * passes that buffer address to storage_write_sectors -> mmc_write_sectors
 * -> sdcc_write_data which DMA's it to the eMMC. */
int transport_read_data()
{
    return 0;
}

/* orig: 0x08030ecc transport_set_pending — set expected transfer size.
 * Calls transport_read_data(0, size, size_lo, size_hi, 0, 1). */
void transport_set_pending(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
    transport_read_data(0, param_2, param_1, param_2, 0, 1);
    return;
}

/* orig: 0x0802d180 pmic_set_power — PMIC power mode control.
 *
 * Controls power rails via the PM8909 PMIC. Used for:
 *   param_2=0: normal mode
 *   param_2=2: DMA reset (called from fatal_error_dma_reset)
 *   param_2=1-8: various power states
 *
 * The implementation uses DAL (Device Abstraction Layer) to talk to
 * the PMIC driver. Not critical for write path understanding. */
int pmic_set_power(param_1, param_2)
undefined4 param_1; uint param_2;
{
    return 0;
}
