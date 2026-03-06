/* usb.c — Minimal ChipIdea USB device driver for MSM8909.
 *
 * Implements USB device enumeration + bulk IN/OUT transfers using polling.
 * All buffers in OCIMEM — no DDR required.
 *
 * Based on LK's hsusb.c (platform/msm_shared/).
 *
 * Hardware: ChipIdea USB 2.0 HS controller at 0x07FD9000.
 * PBL already initialized clocks and PHY for Sahara protocol.
 * We reset the controller and re-enumerate as a new device.
 */

#include "usb.h"
#include "msm8909.h"

#define REG32(addr)  (*(volatile unsigned int *)(addr))
#define readl(addr)  REG32(addr)
#define writel(v, addr) do { REG32(addr) = (v); } while(0)

/*========================================================================
 * Debug checkpoint — blink red LED N times (100ms on/off) using timetick
 * Used to narrow down which USB register access faults.
 * Remove once USB is working.
 *========================================================================*/
static void usb_cp(int n)
{
    volatile unsigned int *tick =
        (volatile unsigned int *)0x004A3000; /* MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL */
    volatile unsigned int *cfg =
        (volatile unsigned int *)0x01044000; /* GPIO_CFG_ADDR(68) red LED */
    volatile unsigned int *out =
        (volatile unsigned int *)0x01044004; /* GPIO_IN_OUT_ADDR(68) */
    unsigned int start;
    int i;
    *cfg = (1 << 9); /* OE=output, GPIO_OE_ENABLE<<GPIO_OE_SHIFT */
    for (i = 0; i < n; i++) {
        *out = 2;             /* GPIO_OUT_BIT = bit 1 */
        start = *tick;
        while ((*tick - start) < 3277);  /* 100ms at 32768 Hz */
        *out = 0;
        start = *tick;
        while ((*tick - start) < 3277);
    }
    /* 500ms gap after sequence */
    start = *tick;
    while ((*tick - start) < 16384);
}

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
 * Static allocations — all in OCIMEM (BSS or data)
 *========================================================================*/

/* dQH table: 16 endpoints × 2 directions = 32 entries × 64 bytes = 2KB.
 * Must be 2KB-aligned (HW requirement). We use 4KB for safety. */
static struct ept_queue_head dqh_table[32] __attribute__((aligned(4096)));

/* dTD items for each endpoint direction we use */
static struct ept_queue_item dtd_ep0_in  __attribute__((aligned(32)));
static struct ept_queue_item dtd_bulk_out __attribute__((aligned(32)));
static struct ept_queue_item dtd_bulk_in  __attribute__((aligned(32)));

/* EP0 data buffer (for setup responses) */
static unsigned char ep0_buf[64] __attribute__((aligned(32)));

/* State */
static int usb_online;
static int usb_highspeed;

/*========================================================================
 * Hardcoded USB descriptors
 *========================================================================*/

/* Device descriptor — VID:PID = 05C6:F001 (Qualcomm diagnostic) */
static const unsigned char dev_desc[18] = {
    18,             /* bLength */
    DESC_DEVICE,    /* bDescriptorType */
    0x00, 0x02,     /* bcdUSB = 2.00 */
    0xFF,           /* bDeviceClass = vendor-specific */
    0x00,           /* bDeviceSubClass */
    0x00,           /* bDeviceProtocol */
    64,             /* bMaxPacketSize0 */
    0xC6, 0x05,     /* idVendor = 0x05C6 */
    0x01, 0xF0,     /* idProduct = 0xF001 */
    0x00, 0x01,     /* bcdDevice = 1.00 */
    1,              /* iManufacturer = string 1 */
    2,              /* iProduct = string 2 */
    0,              /* iSerialNumber */
    1,              /* bNumConfigurations */
};

/* Configuration descriptor (9) + Interface descriptor (9) +
 * Endpoint 1 OUT (7) + Endpoint 1 IN (7) = 32 bytes total */
static const unsigned char cfg_desc[32] = {
    /* Configuration descriptor */
    9,              /* bLength */
    DESC_CONFIGURATION, /* bDescriptorType */
    32, 0,          /* wTotalLength = 32 */
    1,              /* bNumInterfaces */
    1,              /* bConfigurationValue */
    0,              /* iConfiguration */
    0x80,           /* bmAttributes = bus-powered */
    250,            /* bMaxPower = 500mA */

    /* Interface descriptor */
    9,              /* bLength */
    4,              /* bDescriptorType = INTERFACE */
    0,              /* bInterfaceNumber */
    0,              /* bAlternateSetting */
    2,              /* bNumEndpoints */
    0xFF,           /* bInterfaceClass = vendor-specific */
    0x00,           /* bInterfaceSubClass */
    0x00,           /* bInterfaceProtocol */
    0,              /* iInterface */

    /* Endpoint 1 OUT (bulk) */
    7,              /* bLength */
    5,              /* bDescriptorType = ENDPOINT */
    0x01,           /* bEndpointAddress = EP1 OUT */
    0x02,           /* bmAttributes = bulk */
    0x00, 0x02,     /* wMaxPacketSize = 512 (HS) — patched at runtime */
    0,              /* bInterval */

    /* Endpoint 1 IN (bulk) */
    7,              /* bLength */
    5,              /* bDescriptorType = ENDPOINT */
    0x81,           /* bEndpointAddress = EP1 IN */
    0x02,           /* bmAttributes = bulk */
    0x00, 0x02,     /* wMaxPacketSize = 512 (HS) — patched at runtime */
    0,              /* bInterval */
};

/* String descriptor 0 — language ID */
static const unsigned char str_desc_0[4] = {
    4, DESC_STRING, 0x09, 0x04  /* US English */
};

/* String descriptor 1 — manufacturer "QC" */
static const unsigned char str_desc_1[8] = {
    8, DESC_STRING, 'Q', 0, 'C', 0, ' ', 0
};

/* String descriptor 2 — product "DIAG" */
static const unsigned char str_desc_2[10] = {
    10, DESC_STRING, 'D', 0, 'I', 0, 'A', 0, 'G', 0
};

/*========================================================================
 * Delay — use MPM2 sleep timetick (32768 Hz)
 *========================================================================*/
static void delay_ms(unsigned int ms)
{
    volatile unsigned int *tick = (volatile unsigned int *)MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL;
    unsigned int ticks = (ms * 32768) / 1000;
    unsigned int start = *tick;
    while ((*tick - start) < ticks);
}

/*========================================================================
 * Internal: queue a transfer on an endpoint
 *========================================================================*/
static void queue_transfer(int ep_idx, struct ept_queue_item *dtd,
                           void *buf, int len)
{
    struct ept_queue_head *dqh = &dqh_table[ep_idx];

    /* Set up dTD */
    dtd->next  = TERMINATE;
    dtd->info  = INFO_BYTES(len) | INFO_IOC | INFO_ACTIVE;
    dtd->page0 = (unsigned int)buf;
    dtd->page1 = ((unsigned int)buf & 0xFFFFF000u) + 0x1000;
    dtd->page2 = ((unsigned int)buf & 0xFFFFF000u) + 0x2000;
    dtd->page3 = ((unsigned int)buf & 0xFFFFF000u) + 0x3000;
    dtd->page4 = ((unsigned int)buf & 0xFFFFF000u) + 0x4000;
    cache_flush_inv(dtd, sizeof(*dtd));

    /* Link to dQH */
    dqh->next = (unsigned int)dtd;
    dqh->info = 0;
    cache_flush_inv(dqh, sizeof(*dqh));
}

/*========================================================================
 * Internal: EP0 setup response (IN transfer on EP0)
 *========================================================================*/
static void ep0_send(const void *data, int len)
{
    unsigned int i;
    const unsigned char *src = (const unsigned char *)data;

    /* Copy to DMA-safe buffer */
    for (i = 0; i < (unsigned)len && i < sizeof(ep0_buf); i++)
        ep0_buf[i] = src[i];
    cache_flush_inv(ep0_buf, sizeof(ep0_buf));

    /* Queue IN transfer on EP0 (index 1 = ep0 IN) */
    queue_transfer(1, &dtd_ep0_in, ep0_buf, len);
    writel(EPT_TX(0), USB_ENDPTPRIME);
}

/* Send zero-length ACK on EP0 IN */
static void ep0_ack(void)
{
    ep0_send(ep0_buf, 0);
}

/*========================================================================
 * Internal: handle SETUP packet
 *========================================================================*/
static void handle_setup(void)
{
    struct ept_queue_head *dqh = &dqh_table[0]; /* EP0 OUT */
    unsigned char setup[8];
    unsigned int type, request, value, index, length;
    const unsigned char *desc_data;
    unsigned int desc_len;

    cache_inv(dqh, sizeof(*dqh));

    /* Copy setup data */
    setup[0] = dqh->setup_data[0];
    setup[1] = dqh->setup_data[1];
    setup[2] = dqh->setup_data[2];
    setup[3] = dqh->setup_data[3];
    setup[4] = dqh->setup_data[4];
    setup[5] = dqh->setup_data[5];
    setup[6] = dqh->setup_data[6];
    setup[7] = dqh->setup_data[7];

    /* Clear setup status */
    writel(EPT_RX(0), USB_ENDPTSETUPSTAT);

    /* Wait for setup tripwire to clear */
    while (readl(USB_ENDPTSETUPSTAT) & EPT_RX(0));

    /* Flush EP0 */
    writel(EPT_RX(0) | EPT_TX(0), USB_ENDPTFLUSH);
    while (readl(USB_ENDPTFLUSH) & (EPT_RX(0) | EPT_TX(0)));

    type    = setup[0];
    request = setup[1];
    value   = setup[2] | (setup[3] << 8);
    index   = setup[4] | (setup[5] << 8);
    length  = setup[6] | (setup[7] << 8);
    (void)index;

    if (type == DEVICE_READ && request == GET_DESCRIPTOR) {
        unsigned int desc_type = value >> 8;
        unsigned int desc_idx  = value & 0xFF;
        desc_data = 0;
        desc_len  = 0;

        if (desc_type == DESC_DEVICE) {
            desc_data = dev_desc;
            desc_len  = sizeof(dev_desc);
        } else if (desc_type == DESC_CONFIGURATION) {
            /* Patch max packet size based on speed */
            static unsigned char cfg_copy[32];
            unsigned int pkt = usb_highspeed ? 512 : 64;
            unsigned int i;
            for (i = 0; i < sizeof(cfg_desc); i++)
                cfg_copy[i] = cfg_desc[i];
            /* EP1 OUT wMaxPacketSize at offset 22-23 */
            cfg_copy[22] = pkt & 0xFF;
            cfg_copy[23] = pkt >> 8;
            /* EP1 IN wMaxPacketSize at offset 29-30 */
            cfg_copy[29] = pkt & 0xFF;
            cfg_copy[30] = pkt >> 8;
            desc_data = cfg_copy;
            desc_len  = sizeof(cfg_copy);
        } else if (desc_type == DESC_STRING) {
            if (desc_idx == 0) {
                desc_data = str_desc_0;
                desc_len  = sizeof(str_desc_0);
            } else if (desc_idx == 1) {
                desc_data = str_desc_1;
                desc_len  = sizeof(str_desc_1);
            } else if (desc_idx == 2) {
                desc_data = str_desc_2;
                desc_len  = sizeof(str_desc_2);
            }
        }

        if (desc_data) {
            if (desc_len > length)
                desc_len = length;
            ep0_send(desc_data, desc_len);
        } else {
            /* STALL */
            writel((1 << 16) | 1, USB_ENDPTCTRL(0));
        }
        return;
    }

    if (type == DEVICE_READ && request == GET_STATUS) {
        /* Return 0x0000 (self-powered=0, remote-wakeup=0) */
        ep0_buf[0] = 0;
        ep0_buf[1] = 0;
        cache_flush_inv(ep0_buf, sizeof(ep0_buf));
        ep0_send(ep0_buf, 2);
        return;
    }

    if (type == DEVICE_WRITE && request == SET_ADDRESS) {
        /* Address takes effect after status phase */
        writel((value << 25) | (1 << 24), USB_DEVICEADDR);
        ep0_ack();
        return;
    }

    if (type == DEVICE_WRITE && request == SET_CONFIGURATION) {
        if (value == 1) {
            unsigned int pkt = usb_highspeed ? 512 : 64;
            /* Configure EP1 bulk IN + OUT */
            dqh_table[2].config = CONFIG_MAX_PKT(pkt) | CONFIG_ZLT;  /* EP1 OUT */
            dqh_table[3].config = CONFIG_MAX_PKT(pkt) | CONFIG_ZLT;  /* EP1 IN */
            cache_flush_inv(&dqh_table[2], sizeof(struct ept_queue_head));
            cache_flush_inv(&dqh_table[3], sizeof(struct ept_queue_head));

            /* Enable EP1 with bulk type, reset data toggle */
            writel(CTRL_TXE | CTRL_TXR | CTRL_TXT_BULK |
                   CTRL_RXE | CTRL_RXR | CTRL_RXT_BULK,
                   USB_ENDPTCTRL(1));

            usb_online = 1;
        } else {
            writel(0, USB_ENDPTCTRL(1));
            usb_online = 0;
        }
        ep0_ack();
        return;
    }

    if (type == ENDPOINT_WRITE && request == CLEAR_FEATURE) {
        /* Clear endpoint halt — just re-enable */
        unsigned int ep_num = index & 0x0F;
        if (ep_num == 1) {
            writel(CTRL_TXE | CTRL_TXR | CTRL_TXT_BULK |
                   CTRL_RXE | CTRL_RXR | CTRL_RXT_BULK,
                   USB_ENDPTCTRL(1));
        }
        ep0_ack();
        return;
    }

    /* Unknown request — STALL */
    writel((1 << 16) | 1, USB_ENDPTCTRL(0));
}

/*========================================================================
 * USB clock enable — GCC registers for USB HS clocks
 *
 * PBL enables these for Sahara but may gate them before jumping to us.
 * USB core clock = GPLL0/10 = 80 MHz (RCG already configured by PBL).
 *========================================================================*/
#define GCC_USB_HS_BCR              0x01841000
#define GCC_USB_HS_SYSTEM_CBCR     0x01841004
#define GCC_USB_HS_AHB_CBCR        0x01841008
#define GCC_USB_HS_SYSTEM_CMD_RCGR 0x01841010
#define GCC_USB_HS_SYSTEM_CFG_RCGR 0x01841014

static void usb_clock_init(void)
{
    /* Configure RCG: source = GPLL0 (src_sel=1), divider = 10
     * CFG_RCGR: bits [8:8] = src_sel=1, bits [4:0] = 2*div-1 = 19 */
    writel((1 << 8) | 19, GCC_USB_HS_SYSTEM_CFG_RCGR);

    /* Trigger RCG update */
    writel(1, GCC_USB_HS_SYSTEM_CMD_RCGR);
    while (readl(GCC_USB_HS_SYSTEM_CMD_RCGR) & 1);  /* wait for update */

    /* Enable branch clocks (bit 0 = enable) */
    writel(readl(GCC_USB_HS_SYSTEM_CBCR) | 1, GCC_USB_HS_SYSTEM_CBCR);
    writel(readl(GCC_USB_HS_AHB_CBCR) | 1, GCC_USB_HS_AHB_CBCR);

    /* Wait for clocks to stabilize (bit 31 = CLK_OFF, should clear) */
    while (readl(GCC_USB_HS_SYSTEM_CBCR) & (1u << 31));
    while (readl(GCC_USB_HS_AHB_CBCR) & (1u << 31));

    /* Block reset: assert then deassert */
    writel(1, GCC_USB_HS_BCR);
    delay_ms(5);
    writel(0, GCC_USB_HS_BCR);
    delay_ms(5);

    /* Re-enable after reset */
    writel(readl(GCC_USB_HS_SYSTEM_CBCR) | 1, GCC_USB_HS_SYSTEM_CBCR);
    writel(readl(GCC_USB_HS_AHB_CBCR) | 1, GCC_USB_HS_AHB_CBCR);
    while (readl(GCC_USB_HS_SYSTEM_CBCR) & (1u << 31));
    while (readl(GCC_USB_HS_AHB_CBCR) & (1u << 31));
}

/*========================================================================
 * usb_init — Reset controller and start device mode
 *========================================================================*/
void usb_init(void)
{
    unsigned int i;

    usb_online = 0;
    usb_highspeed = 0;

    usb_cp(1);  /* CP1: entering usb_init */

    /* Enable USB clocks (PBL may have gated them before jumping to us) */
    usb_clock_init();

    usb_cp(2);  /* CP2: usb_clock_init done */

    /* Reset controller */
    writel(0x00080002, USB_USBCMD);  /* RST + ITC=8 */
    delay_ms(20);
    while (readl(USB_USBCMD) & 2);  /* wait for reset complete */

    usb_cp(3);  /* CP3: controller reset complete, USB regs accessible */

    /* Select ULPI PHY */
    writel(0x80000000, USB_PORTSC);

    /* AHB config */
    writel(0x0, USB_SBUSCFG);
    writel(0x08, USB_AHB_MODE);

    /* Clear dQH table */
    for (i = 0; i < sizeof(dqh_table); i++)
        ((unsigned char *)dqh_table)[i] = 0;

    /* Configure EP0 queue heads */
    dqh_table[0].config = CONFIG_MAX_PKT(64) | CONFIG_ZLT | CONFIG_IOS; /* EP0 OUT */
    dqh_table[1].config = CONFIG_MAX_PKT(64) | CONFIG_ZLT;               /* EP0 IN */
    cache_flush_inv(dqh_table, sizeof(dqh_table));

    /* Set endpoint list address */
    writel((unsigned int)dqh_table, USB_ENDPOINTLISTADDR);

    /* Select device mode */
    writel(0x02, USB_USBMODE);

    /* Disable interrupts (we poll) */
    writel(0, USB_USBINTR);

    /* Flush all endpoints */
    writel(0xFFFFFFFF, USB_ENDPTFLUSH);
    delay_ms(5);

    /* Start controller (D+ pullup enable) */
    writel(0x00080001, USB_USBCMD);  /* RUN + ITC=8 */

    usb_cp(4);  /* CP4: USBCMD.RUN set — D+ now asserted */
}

/*========================================================================
 * usb_poll — Handle USB events (setup, port change, reset)
 *
 * Returns 1 when device is online (SET_CONFIGURATION received).
 *========================================================================*/
int usb_poll(void)
{
    unsigned int sts = readl(USB_USBSTS);

    if (sts & (STS_URI | STS_PCI | STS_UI | STS_UEI)) {
        /* Clear handled status bits */
        writel(sts & (STS_URI | STS_PCI | STS_UI | STS_UEI | STS_SLI),
               USB_USBSTS);

        if (sts & STS_URI) {
            /* USB Reset */
            writel(readl(USB_ENDPTCOMPLETE), USB_ENDPTCOMPLETE);
            writel(readl(USB_ENDPTSETUPSTAT), USB_ENDPTSETUPSTAT);
            writel(0xFFFFFFFF, USB_ENDPTFLUSH);
            writel(0, USB_ENDPTCTRL(1));
            usb_online = 0;
        }

        if (sts & STS_PCI) {
            /* Port change — detect speed */
            unsigned int spd = (readl(USB_PORTSC) >> 26) & 3;
            usb_highspeed = (spd == 2) ? 1 : 0;
        }

        if ((sts & STS_UI) || (sts & STS_UEI)) {
            /* Check for setup packet on EP0 */
            if (readl(USB_ENDPTSETUPSTAT) & EPT_RX(0)) {
                handle_setup();
            }
        }
    }

    return usb_online;
}

/*========================================================================
 * usb_read — Blocking bulk OUT read on EP1
 *
 * Returns number of bytes received, or -1 on USB reset.
 *========================================================================*/
int usb_read(void *buf, int maxlen)
{
    unsigned int bit = EPT_RX(1);
    int remaining;

    if (!usb_online)
        return -1;
    if (maxlen <= 0)
        return 0;

    /* Flush destination buffer cache */
    cache_flush_inv(buf, maxlen);

    /* Queue bulk OUT transfer */
    queue_transfer(2, &dtd_bulk_out, buf, maxlen);  /* index 2 = EP1 OUT */
    writel(bit, USB_ENDPTPRIME);

    /* Wait for completion */
    for (;;) {
        unsigned int sts = readl(USB_USBSTS);

        /* Handle bus events while waiting */
        if (sts & STS_URI) {
            writel(STS_URI, USB_USBSTS);
            usb_online = 0;
            return -1;
        }
        if (sts & STS_PCI) {
            writel(STS_PCI, USB_USBSTS);
            usb_highspeed = ((readl(USB_PORTSC) >> 26) & 3) == 2;
        }
        if (sts & (STS_UI | STS_UEI)) {
            writel(sts & (STS_UI | STS_UEI), USB_USBSTS);

            /* Handle any setup packets (host may send control requests) */
            if (readl(USB_ENDPTSETUPSTAT) & EPT_RX(0))
                handle_setup();

            /* Check our bulk transfer */
            if (readl(USB_ENDPTCOMPLETE) & bit) {
                writel(bit, USB_ENDPTCOMPLETE);
                break;
            }
        }
    }

    /* Read actual transfer size */
    cache_inv(&dtd_bulk_out, sizeof(dtd_bulk_out));
    remaining = (dtd_bulk_out.info >> 16) & 0x7FFF;

    /* Invalidate received data in cache */
    cache_inv(buf, maxlen - remaining);

    return maxlen - remaining;
}

/*========================================================================
 * usb_write — Blocking bulk IN write on EP1
 *
 * Returns number of bytes sent, or -1 on USB reset.
 *========================================================================*/
int usb_write(const void *buf, int len)
{
    unsigned int bit = EPT_TX(1);
    int remaining;

    if (!usb_online)
        return -1;
    if (len <= 0)
        return 0;

    /* Flush source buffer to memory */
    cache_flush_inv((void *)buf, len);

    /* Queue bulk IN transfer */
    queue_transfer(3, &dtd_bulk_in, (void *)buf, len);  /* index 3 = EP1 IN */
    writel(bit, USB_ENDPTPRIME);

    /* Wait for completion */
    for (;;) {
        unsigned int sts = readl(USB_USBSTS);

        if (sts & STS_URI) {
            writel(STS_URI, USB_USBSTS);
            usb_online = 0;
            return -1;
        }
        if (sts & STS_PCI) {
            writel(STS_PCI, USB_USBSTS);
            usb_highspeed = ((readl(USB_PORTSC) >> 26) & 3) == 2;
        }
        if (sts & (STS_UI | STS_UEI)) {
            writel(sts & (STS_UI | STS_UEI), USB_USBSTS);

            if (readl(USB_ENDPTSETUPSTAT) & EPT_RX(0))
                handle_setup();

            if (readl(USB_ENDPTCOMPLETE) & bit) {
                writel(bit, USB_ENDPTCOMPLETE);
                break;
            }
        }
    }

    cache_inv(&dtd_bulk_in, sizeof(dtd_bulk_in));
    remaining = (dtd_bulk_in.info >> 16) & 0x7FFF;
    return len - remaining;
}
