/* transport.c — USB transport layer for firehose protocol.
 *
 * Bridges the firehose XML/data protocol to our polling USB driver.
 * The original uses interrupt-driven async USB; we use synchronous reads.
 *
 * Key functions:
 *   send_and_wait()      — send XML response data to host
 *   dispatch_loop_tick()  — no-op (sends are synchronous)
 *   transport_read_data() — receive sector data from host
 *   usb_read_complete()   — read data, set transfer globals
 *
 * Sources: fhprg_802196c.c, fhprg_8030dac.c, fhprg_802cac4.c
 */
#include "firehose.h"

#ifndef MINIMAL_EMBEDDED_PAYLOAD

#include "usb.h"

/* DDR buffer for sector data transfers (handle_program / handle_read).
 * Must be in DDR for potential direct SDCC DMA use.
 * 1 MB matches the original's buffer capacity (DAT_08055fb8). */
static char xfer_buf[0x100000] __attribute__((section(".ddr_bss"), aligned(32)));

/* ---- XML transport (responses/logs → host) ---- */

/* orig: send_and_wait — send data over USB, signal completion.
 * In the original, this starts an async write and a callback sets
 * DAT_08055f99. We do it synchronously.
 *
 * param_1 = buffer pointer, param_2 = size,
 * param_3 = callback (ignored), param_4 = error ptr (ignored). */
void send_and_wait(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; uint param_3; uint param_4;
{
    int remaining = (int)param_2;
    const char *ptr = (const char *)param_1;

    (void)param_3; (void)param_4;

    while (remaining > 0) {
        int n = usb_write(ptr, remaining);
        if (n <= 0) break;
        ptr += n;
        remaining -= n;
    }

    /* Signal completion (xml_send_and_wait polls this) */
    DAT_08055f99 = 1;
}

/* dispatch_loop_tick — poll for USB completion.
 * No-op since our sends are synchronous. */
void dispatch_loop_tick()
{
    return;
}

/* ---- Data transport (sector data from host) ---- */

/* orig: 0x08021ca4 usb_read_complete — receive data from USB host.
 *
 * In the original binary, this is a simple wrapper that passes ARM
 * registers through to transport_read_data(). For our C implementation,
 * we read data synchronously and set the transfer globals.
 *
 * param_1 = output: pointer to received data buffer.
 * The transfer size is read from DAT_08055f90 after transfer_callback. */
int usb_read_complete(param_1)
uint *param_1;
{
    uint expected;
    uint total;
    int n;

    /* Expected transfer size: use buffer capacity, capped at our buffer */
    expected = DAT_08055fb8;
    if (expected > sizeof(xfer_buf))
        expected = sizeof(xfer_buf);

    /* Read data in chunks (usb_read caps at 4KB per call) */
    total = 0;
    while (total < expected) {
        int chunk = expected - total;
        n = usb_read(xfer_buf + total, chunk);
        if (n < 0) {
            transfer_callback(total, -1);
            return -1;
        }
        if (n == 0) break;
        total += n;
        if (n < chunk) break;  /* short packet = end of transfer */
    }

    /* Output: data buffer pointer */
    if (param_1)
        *param_1 = (uint)xfer_buf;

    /* Update transfer counters via callback */
    transfer_callback(total, 0);

    return 0;
}

/* orig: 0x08031170 transport_read_data — receive data from USB host.
 * Called by usb_read_complete and transport_set_pending.
 * For our synchronous implementation, this is a no-op since
 * usb_read_complete handles the actual read. */
int transport_read_data()
{
    return 0;
}

/* orig: 0x08030ecc transport_set_pending — set expected transfer size.
 * In the original, this primes the next async USB read.
 * For our synchronous model, set the buffer capacity so the next
 * usb_read_complete knows how much to read.
 * param_1 = size_lo, param_2 = size_hi. */
void transport_set_pending(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
    (void)param_2;
    DAT_08055fb8 = (uint)param_1;
    DAT_08055fbc = 0;
    return;
}

/* orig: 0x0802d180 pmic_set_power — PMIC power mode control.
 * Stub — not needed for eMMC access. */
int pmic_set_power(param_1, param_2)
undefined4 param_1; uint param_2;
{
    return 0;
}

#endif /* !MINIMAL_EMBEDDED_PAYLOAD */
