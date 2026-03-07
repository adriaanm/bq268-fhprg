/* usb.h — USB driver for MSM8909 minimal programmer.
 *
 * Inherits PBL's USB session (no reset, no re-enumeration).
 * All DMA buffers in DDR — USB DMA cannot access OCIMEM.
 * Uses polling (no interrupts).
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

/*========================================================================
 * Public API
 *========================================================================*/

/* Inherit PBL's USB session. No reset, no re-enumeration.
 * Reads PBL's ENDPOINTLISTADDR, flushes endpoints, prepares for bulk I/O.
 * Returns with usb_online=1 immediately. */
void usb_init(void);

/* Blocking bulk OUT read on EP1.
 * buf may be in OCIMEM or DDR — internally stages through DDR.
 * Returns number of bytes read, or -1 on error. */
int usb_read(void *buf, int maxlen);

/* Blocking bulk IN write on EP1.
 * buf may be in OCIMEM or DDR — internally stages through DDR.
 * Returns number of bytes written, or -1 on error. */
int usb_write(const void *buf, int len);

#endif /* USB_H */
