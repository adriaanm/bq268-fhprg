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
 * PBL maps DDR as Device memory (uncached) — no cache maintenance needed.
 * Just DSB barriers to ensure store visibility before priming DMA.
 *
 * Hardware: ChipIdea USB 2.0 HS controller at 0x078D9000.
 */

#include "usb.h"
#include "msm8909.h"

#define REG32(addr)  (*(volatile unsigned int *)(addr))
#define readl(addr)  REG32(addr)
#define writel(v, addr) do { REG32(addr) = (v); } while(0)

static inline void dsb(void)
{
    __asm__ volatile("dsb" ::: "memory");
}

/*========================================================================
 * DDR-resident buffers — USB DMA can only access DDR, not OCIMEM.
 * These go in .ddr_bss section (mapped to DDR region in linker script).
 *========================================================================*/

/* dTDs for bulk endpoints — one per direction */
static volatile struct ept_queue_item dtd_bulk_out __attribute__((aligned(32), section(".ddr_bss")));
static volatile struct ept_queue_item dtd_bulk_in  __attribute__((aligned(32), section(".ddr_bss")));

/* Staging buffers for DMA — callers may pass OCIMEM pointers */
#define USB_BUF_SIZE  4096
static volatile unsigned char usb_rx_buf[USB_BUF_SIZE] __attribute__((aligned(32), section(".ddr_bss")));
static volatile unsigned char usb_tx_buf[USB_BUF_SIZE] __attribute__((aligned(32), section(".ddr_bss")));

/*========================================================================
 * State
 *========================================================================*/
static int usb_online;

/* Pointers to PBL's dQH entries for EP1 bulk endpoints.
 * Volatile because hardware (DMA) also reads/writes these. */
static volatile struct ept_queue_head *dqh_ep1_out;  /* index 2 */
static volatile struct ept_queue_head *dqh_ep1_in;   /* index 3 */

/*========================================================================
 * Internal: set up dTD and link into dQH, matching probe's approach
 *========================================================================*/
static void prime_ep(volatile struct ept_queue_head *dqh,
                     volatile struct ept_queue_item *dtd,
                     unsigned int buf_addr, int len,
                     unsigned int prime_bit)
{
    /* Wait for any previous prime on this endpoint to finish */
    while (readl(USB_ENDPTPRIME) & prime_bit);

    /* Flush this endpoint if it's still active from a previous transfer */
    if (readl(USB_ENDPTSTAT) & prime_bit) {
        writel(prime_bit, USB_ENDPTFLUSH);
        while (readl(USB_ENDPTFLUSH) & prime_bit);
    }

    /* Clear any stale completion for this endpoint */
    if (readl(USB_ENDPTCOMPLETE) & prime_bit)
        writel(prime_bit, USB_ENDPTCOMPLETE);

    /* Set up dTD */
    dtd->next  = TERMINATE;
    dtd->info  = INFO_BYTES(len) | INFO_IOC | INFO_ACTIVE;
    dtd->page0 = buf_addr;
    dtd->page1 = (buf_addr & 0xFFFFF000u) + 0x1000;
    dtd->page2 = (buf_addr & 0xFFFFF000u) + 0x2000;
    dtd->page3 = (buf_addr & 0xFFFFF000u) + 0x3000;
    dtd->page4 = (buf_addr & 0xFFFFF000u) + 0x4000;
    dsb();

    /* Link dTD into dQH.
     * Clear 'current' first — if it still points to the same dTD from the
     * previous transfer, current==next is undefined behavior per ChipIdea spec. */
    dqh->current = 0;
    dqh->next = (unsigned int)dtd;
    dqh->info = 0;  /* clear overlay token to remove stale ACTIVE bit */
    dsb();

    /* Prime */
    writel(prime_bit, USB_ENDPTPRIME);
}

/*========================================================================
 * Internal: poll until transfer completes or bus reset
 * Returns 0 on success, -1 on bus reset.
 *========================================================================*/
static int poll_complete(unsigned int bit)
{
    for (;;) {
        /* Check for USB reset — bail out */
        if (readl(USB_USBSTS) & STS_URI) {
            writel(STS_URI, USB_USBSTS);
            usb_online = 0;
            return -1;
        }

        /* Poll ENDPTCOMPLETE directly — don't gate on STS_UI.
         * Gating on STS_UI has a race: if we clear STS_UI before
         * checking ENDPTCOMPLETE, and the transfer completes between
         * those two reads, we miss the completion forever. */
        if (readl(USB_ENDPTCOMPLETE) & bit) {
            writel(bit, USB_ENDPTCOMPLETE);
            return 0;
        }
    }
}

/*========================================================================
 * usb_init — Inherit PBL's USB session
 *========================================================================*/
void usb_init(void)
{
    unsigned int pbl_eplist;

    usb_online = 0;

    /* 1. Read PBL's ENDPOINTLISTADDR to find dQH table */
    pbl_eplist = readl(USB_ENDPOINTLISTADDR);

    /* dQH entries: index 2 = EP1 OUT, index 3 = EP1 IN (64 bytes each) */
    dqh_ep1_out = (volatile struct ept_queue_head *)(pbl_eplist + 2 * 64);
    dqh_ep1_in  = (volatile struct ept_queue_head *)(pbl_eplist + 3 * 64);

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
 *========================================================================*/
int usb_read(void *buf, int maxlen)
{
    unsigned int bit = EPT_RX(1);
    int xfer_len, remaining, actual, i;

    if (!usb_online)
        return -1;
    if (maxlen <= 0)
        return 0;

    xfer_len = maxlen;
    if (xfer_len > USB_BUF_SIZE)
        xfer_len = USB_BUF_SIZE;

    prime_ep(dqh_ep1_out, &dtd_bulk_out,
             (unsigned int)usb_rx_buf, xfer_len, bit);

    if (poll_complete(bit) < 0)
        return -1;

    /* Read actual transfer size from dTD */
    dsb();
    remaining = (dtd_bulk_out.info >> 16) & 0x7FFF;
    actual = xfer_len - remaining;

    /* Copy from DDR staging buffer to caller's buffer */
    {
        unsigned char *dst = (unsigned char *)buf;
        for (i = 0; i < actual; i++)
            dst[i] = usb_rx_buf[i];
    }

    return actual;
}

/*========================================================================
 * usb_write — Blocking bulk IN write on EP1
 *========================================================================*/
int usb_write(const void *buf, int len)
{
    unsigned int bit = EPT_TX(1);
    int xfer_len, remaining, i;

    if (!usb_online)
        return -1;
    if (len <= 0)
        return 0;

    xfer_len = len;
    if (xfer_len > USB_BUF_SIZE)
        xfer_len = USB_BUF_SIZE;

    /* Copy caller's data to DDR staging buffer */
    {
        const unsigned char *src = (const unsigned char *)buf;
        for (i = 0; i < xfer_len; i++)
            usb_tx_buf[i] = src[i];
    }
    dsb();

    prime_ep(dqh_ep1_in, &dtd_bulk_in,
             (unsigned int)usb_tx_buf, xfer_len, bit);

    if (poll_complete(bit) < 0)
        return -1;

    dsb();
    remaining = (dtd_bulk_in.info >> 16) & 0x7FFF;
    return xfer_len - remaining;
}
