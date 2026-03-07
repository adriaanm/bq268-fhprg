/* usb.h — Minimal ChipIdea USB device driver for MSM8909.
 *
 * Provides bulk read/write over USB without requiring DDR.
 * All buffers live in OCIMEM. Uses polling (no interrupts).
 *
 * Based on LK's hsusb.h/hsusb.c (platform/msm_shared/).
 */
#ifndef USB_H
#define USB_H

/*========================================================================
 * USB Controller base (ChipIdea HS USB in MSM8909)
 *========================================================================*/
#define MSM_USB_BASE  0x078D9000

/*========================================================================
 * Register offsets
 *========================================================================*/
#define USB_SBUSCFG          (MSM_USB_BASE + 0x0090)
#define USB_AHB_MODE         (MSM_USB_BASE + 0x0098)
#define USB_USBCMD           (MSM_USB_BASE + 0x0140)
#define USB_USBSTS           (MSM_USB_BASE + 0x0144)
#define USB_USBINTR          (MSM_USB_BASE + 0x0148)
#define USB_DEVICEADDR       (MSM_USB_BASE + 0x0154)
#define USB_ENDPOINTLISTADDR (MSM_USB_BASE + 0x0158)
#define USB_PORTSC           (MSM_USB_BASE + 0x0184)
#define USB_USBMODE          (MSM_USB_BASE + 0x01A8)
#define USB_ENDPTSETUPSTAT   (MSM_USB_BASE + 0x01AC)
#define USB_ENDPTPRIME       (MSM_USB_BASE + 0x01B0)
#define USB_ENDPTFLUSH       (MSM_USB_BASE + 0x01B4)
#define USB_ENDPTSTAT        (MSM_USB_BASE + 0x01B8)
#define USB_ENDPTCOMPLETE    (MSM_USB_BASE + 0x01BC)
#define USB_ENDPTCTRL(n)     (MSM_USB_BASE + 0x01C0 + (4 * (n)))

/*========================================================================
 * Endpoint Queue Head (dQH) — 64 bytes each, table must be 2KB-aligned
 *========================================================================*/
struct ept_queue_head {
    unsigned int config;
    unsigned int current;
    unsigned int next;
    unsigned int info;
    unsigned int page0;
    unsigned int page1;
    unsigned int page2;
    unsigned int page3;
    unsigned int page4;
    unsigned int reserved_0;
    unsigned char setup_data[8];
    unsigned int reserved_1;
    unsigned int reserved_2;
    unsigned int reserved_3;
    unsigned int reserved_4;
};

/*========================================================================
 * Endpoint Transfer Descriptor (dTD) — 32 bytes each, 32-byte aligned
 *========================================================================*/
struct ept_queue_item {
    unsigned int next;
    unsigned int info;
    unsigned int page0;
    unsigned int page1;
    unsigned int page2;
    unsigned int page3;
    unsigned int page4;
    unsigned int reserved;
};

/*========================================================================
 * Constants
 *========================================================================*/
#define CONFIG_MAX_PKT(n)  ((n) << 16)
#define CONFIG_ZLT         (1 << 29)
#define CONFIG_IOS         (1 << 15)

#define INFO_BYTES(n)      ((n) << 16)
#define INFO_IOC           (1 << 15)
#define INFO_ACTIVE        (1 << 7)
#define INFO_HALTED        (1 << 6)

#define TERMINATE          1

#define EPT_TX(n)          (1 << ((n) + 16))
#define EPT_RX(n)          (1 << (n))

#define STS_URI            (1 << 6)  /* USB Reset */
#define STS_PCI            (1 << 2)  /* Port Change */
#define STS_UI             (1 << 0)  /* USB Interrupt (transfer complete) */
#define STS_UEI            (1 << 1)  /* USB Error */
#define STS_SLI            (1 << 8)  /* Suspend */

#define CTRL_TXE           (1 << 23)
#define CTRL_TXR           (1 << 22)
#define CTRL_TXT_BULK      (2 << 18)
#define CTRL_RXE           (1 << 7)
#define CTRL_RXR           (1 << 6)
#define CTRL_RXT_BULK      (2 << 2)

/* USB setup packet types */
#define DEVICE_READ        0x80
#define DEVICE_WRITE       0x00
#define ENDPOINT_WRITE     0x02
#define INTERFACE_WRITE    0x01

/* USB standard requests */
#define GET_STATUS         0
#define CLEAR_FEATURE      1
#define SET_FEATURE        3
#define SET_ADDRESS        5
#define GET_DESCRIPTOR     6
#define SET_CONFIGURATION  9

/* Descriptor types */
#define DESC_DEVICE        1
#define DESC_CONFIGURATION 2
#define DESC_STRING        3

/*========================================================================
 * Public API
 *========================================================================*/

/* BCR reset + ULPI PHY config + fresh dQH + RS=1.
 * Replicates original firehose programmer's init sequence.
 * Returns with controller running; call usb_poll() for enumeration. */
void usb_init(void);

/* Poll USB events and handle enumeration.
 * Returns 1 when SET_CONFIGURATION received (device is online).
 * Returns 0 if still waiting.
 * Call in a loop until it returns 1. */
int usb_poll(void);

/* Blocking bulk OUT read.
 * Returns number of bytes read, or -1 on error. */
int usb_read(void *buf, int maxlen);

/* Blocking bulk IN write.
 * Returns number of bytes written, or -1 on error. */
int usb_write(const void *buf, int len);

/* Return bitmask of USBSTS events seen since usb_init().
 * STS_URI=reset, STS_PCI=port change, STS_UI=transfer activity, 0=nothing */
unsigned int usb_get_status(void);

#endif /* USB_H */
