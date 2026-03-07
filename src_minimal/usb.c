/* usb.c — USB driver for MSM8909 minimal programmer.
 *
 * Inherits PBL's USB session — no controller reset, no re-enumeration.
 * PBL already enumerated the device and left RS=1 (D+ asserted).
 * We flush stale transfers, then use PBL's dQH table in-place.
 *
 * Critical constraint: USB DMA cannot access OCIMEM (0x0804xxxx).
 * All dTDs and data buffers must be in DDR (0x80000000+).
 * PBL's dQH table (in PBL SRAM) is used as-is — we don't swap it.
 *
 * Hardware: ChipIdea USB 2.0 HS controller at 0x078D9000.
 */

#include "usb.h"
#include "msm8909.h"

#define REG32(addr)  (*(volatile unsigned int *)(addr))
#define readl(addr)  REG32(addr)
#define writel(v, addr) do { REG32(addr) = (v); } while(0)

/*========================================================================
 * Cache maintenance — required for USB DMA coherency
 *========================================================================*/
static void cache_flush_inv(void *addr, unsigned int len)
{
    unsigned int line;
    unsigned int start = (unsigned int)addr & ~31u;
    unsigned int end = (unsigned int)addr + len;
    for (line = start; line < end; line += 32)
        __asm__ volatile("mcr p15, 0, %0, c7, c14, 1" :: "r"(line));
    __asm__ volatile("dsb" ::: "memory");
}

static void cache_inv(void *addr, unsigned int len)
{
    unsigned int line;
    unsigned int start = (unsigned int)addr & ~31u;
    unsigned int end = (unsigned int)addr + len;
    for (line = start; line < end; line += 32)
        __asm__ volatile("mcr p15, 0, %0, c7, c6, 1" :: "r"(line));
    __asm__ volatile("dsb" ::: "memory");
}

/*========================================================================
 * DDR-resident buffers — USB DMA can only access DDR, not OCIMEM.
 * These go in .ddr_bss section (mapped to DDR region in linker script).
 *========================================================================*/

/* dTDs for bulk endpoints — one per direction */
static struct ept_queue_item dtd_bulk_out __attribute__((aligned(32), section(".ddr_bss")));
static struct ept_queue_item dtd_bulk_in  __attribute__((aligned(32), section(".ddr_bss")));

/* Staging buffers for DMA — callers may pass OCIMEM pointers */
#define USB_BUF_SIZE  4096
static unsigned char usb_rx_buf[USB_BUF_SIZE] __attribute__((aligned(32), section(".ddr_bss")));
static unsigned char usb_tx_buf[USB_BUF_SIZE] __attribute__((aligned(32), section(".ddr_bss")));

/*========================================================================
 * State
 *========================================================================*/
static int usb_online;

/* Pointers to PBL's dQH entries for EP1 bulk endpoints */
static struct ept_queue_head *dqh_ep1_out;  /* index 2: EP1 OUT (host→device) */
static struct ept_queue_head *dqh_ep1_in;   /* index 3: EP1 IN  (device→host) */

/*========================================================================
 * Internal: queue a transfer on a PBL dQH entry
 *========================================================================*/
static void queue_transfer(struct ept_queue_head *dqh,
                           struct ept_queue_item *dtd,
                           void *buf, int len)
{
    unsigned int buf_addr = (unsigned int)buf;

    /* Set up dTD */
    dtd->next  = TERMINATE;
    dtd->info  = INFO_BYTES(len) | INFO_IOC | INFO_ACTIVE;
    dtd->page0 = buf_addr;
    dtd->page1 = (buf_addr & 0xFFFFF000u) + 0x1000;
    dtd->page2 = (buf_addr & 0xFFFFF000u) + 0x2000;
    dtd->page3 = (buf_addr & 0xFFFFF000u) + 0x3000;
    dtd->page4 = (buf_addr & 0xFFFFF000u) + 0x4000;
    cache_flush_inv(dtd, sizeof(*dtd));

    /* Link dTD into PBL's dQH */
    dqh->next = (unsigned int)dtd;
    dqh->info = 0;  /* clear overlay status */
    cache_flush_inv(dqh, sizeof(*dqh));
}

/*========================================================================
 * usb_init — Inherit PBL's USB session
 *
 * PBL has fully enumerated the device for Sahara and left:
 *   - RS=1 (controller running, D+ asserted)
 *   - Active transfers primed (ENDPTSTAT non-zero)
 *   - dQH table in PBL SRAM (not OCIMEM)
 *   - Device address assigned, EP1 configured
 *
 * We just flush stale transfers and prepare for bulk I/O.
 *========================================================================*/
void usb_init(void)
{
    unsigned int pbl_eplist;

    usb_online = 0;

    /* 1. Read PBL's ENDPOINTLISTADDR to find dQH table */
    pbl_eplist = readl(USB_ENDPOINTLISTADDR);

    /* dQH entries: index 2 = EP1 OUT, index 3 = EP1 IN (64 bytes each) */
    dqh_ep1_out = (struct ept_queue_head *)(pbl_eplist + 2 * 64);
    dqh_ep1_in  = (struct ept_queue_head *)(pbl_eplist + 3 * 64);

    /* 2. Disable USB interrupts (PBL may have them enabled) */
    writel(0, USB_USBINTR);

    /* 3. Flush all endpoints (clear PBL's pending Sahara transfers) */
    writel(0xFFFFFFFF, USB_ENDPTFLUSH);
    while (readl(USB_ENDPTFLUSH));

    /* 4. Clear pending status bits */
    writel(readl(USB_USBSTS), USB_USBSTS);
    writel(readl(USB_ENDPTCOMPLETE), USB_ENDPTCOMPLETE);

    /* Online immediately — PBL already enumerated, host handle is live */
    usb_online = 1;
}

/*========================================================================
 * usb_read — Blocking bulk OUT read on EP1
 *
 * DMA goes to DDR staging buffer, then memcpy to caller's buffer.
 * Returns number of bytes received, or -1 on error.
 *========================================================================*/
int usb_read(void *buf, int maxlen)
{
    unsigned int bit = EPT_RX(1);
    int xfer_len, remaining, actual, i;

    if (!usb_online)
        return -1;
    if (maxlen <= 0)
        return 0;

    /* Cap to staging buffer size */
    xfer_len = maxlen;
    if (xfer_len > USB_BUF_SIZE)
        xfer_len = USB_BUF_SIZE;

    /* Invalidate rx staging buffer */
    cache_flush_inv(usb_rx_buf, xfer_len);

    /* Queue bulk OUT transfer on PBL's dQH[2] */
    queue_transfer(dqh_ep1_out, &dtd_bulk_out, usb_rx_buf, xfer_len);
    writel(bit, USB_ENDPTPRIME);

    /* Poll for completion */
    for (;;) {
        unsigned int sts = readl(USB_USBSTS);

        if (sts & STS_URI) {
            /* USB bus reset — session lost */
            writel(STS_URI, USB_USBSTS);
            usb_online = 0;
            return -1;
        }

        if (sts & (STS_UI | STS_UEI)) {
            writel(sts & (STS_UI | STS_UEI), USB_USBSTS);

            if (readl(USB_ENDPTCOMPLETE) & bit) {
                writel(bit, USB_ENDPTCOMPLETE);
                break;
            }
        }
    }

    /* Read actual transfer size from dTD */
    cache_inv(&dtd_bulk_out, sizeof(dtd_bulk_out));
    remaining = (dtd_bulk_out.info >> 16) & 0x7FFF;
    actual = xfer_len - remaining;

    /* Copy from DDR staging buffer to caller's buffer */
    cache_inv(usb_rx_buf, actual);
    {
        unsigned char *dst = (unsigned char *)buf;
        for (i = 0; i < actual; i++)
            dst[i] = usb_rx_buf[i];
    }

    return actual;
}

/*========================================================================
 * usb_write — Blocking bulk IN write on EP1
 *
 * Copies caller's data to DDR staging buffer, then DMA from there.
 * Returns number of bytes sent, or -1 on error.
 *========================================================================*/
int usb_write(const void *buf, int len)
{
    unsigned int bit = EPT_TX(1);
    int xfer_len, remaining, i;

    if (!usb_online)
        return -1;
    if (len <= 0)
        return 0;

    /* Cap to staging buffer size */
    xfer_len = len;
    if (xfer_len > USB_BUF_SIZE)
        xfer_len = USB_BUF_SIZE;

    /* Copy caller's data to DDR staging buffer */
    {
        const unsigned char *src = (const unsigned char *)buf;
        for (i = 0; i < xfer_len; i++)
            usb_tx_buf[i] = src[i];
    }
    cache_flush_inv(usb_tx_buf, xfer_len);

    /* Queue bulk IN transfer on PBL's dQH[3] */
    queue_transfer(dqh_ep1_in, &dtd_bulk_in, usb_tx_buf, xfer_len);
    writel(bit, USB_ENDPTPRIME);

    /* Poll for completion */
    for (;;) {
        unsigned int sts = readl(USB_USBSTS);

        if (sts & STS_URI) {
            writel(STS_URI, USB_USBSTS);
            usb_online = 0;
            return -1;
        }

        if (sts & (STS_UI | STS_UEI)) {
            writel(sts & (STS_UI | STS_UEI), USB_USBSTS);

            if (readl(USB_ENDPTCOMPLETE) & bit) {
                writel(bit, USB_ENDPTCOMPLETE);
                break;
            }
        }
    }

    cache_inv(&dtd_bulk_in, sizeof(dtd_bulk_in));
    remaining = (dtd_bulk_in.info >> 16) & 0x7FFF;
    return xfer_len - remaining;
}
