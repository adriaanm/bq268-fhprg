/* main.c — Embedded payload mode: decompress and flash aboot.
 *
 * This runs after entry.S has initialized hardware (DDR, SDCC clocks).
 * The sequence is:
 *   1. Initialize SDCC register bases
 *   2. Open eMMC device (card init, CSD/CID, bus width, speed)
 *   3. Select user partition (partition 0)
 *   4. Decompress gzipped aboot from embedded payload into DDR buffer
 *   5. Write decompressed data to aboot partition
 *   6. Reboot
 *
 * The aboot partition start sector and size must be configured for the
 * target device's GPT layout.
 */

#ifdef MINIMAL_EMBEDDED_PAYLOAD

#include "firehose.h"
#include "msm8909.h"
#include "tinf.h"

/*========================================================================
 * Configuration — adjust for target device GPT layout
 *========================================================================*/

/* Target partition start sector (from GPT).
 * BQ268 UdoSmart (msm8909) partition table:
 *   splash: sector 2663442, 20480 sectors (10 MB) — expendable, use for debugging
 *   aboot:  sector 2623488, 2048 sectors (1 MB) — real target
 */
#ifndef TARGET_START_SECTOR
#define TARGET_START_SECTOR  2663442  /* splash — safe for testing */
/* #define TARGET_START_SECTOR  2623488 */  /* aboot — uncomment for real flash */
#endif

/* Sector size (always 512 for eMMC) */
#define SECTOR_SIZE  512

/* DDR buffer for decompression — 2 MB available at SDRAM_START_ADDR */
#define DDR_BUFFER       ((unsigned char *)SDRAM_START_ADDR)
#define DDR_BUFFER_SIZE  (2 * 1024 * 1024)

/*========================================================================
 * External symbols from aboot_payload.S
 *========================================================================*/
extern const unsigned char aboot_payload_gz[];
extern const unsigned int  aboot_payload_gz_len;

/*========================================================================
 * Storage context — the eMMC driver uses this to track device state
 *========================================================================*/

/* Storage context struct layout (from storage.c analysis):
 *   +0x00: flags
 *   +0x04: device handle for partition 0 (user)
 *   +0x08..+0x24: device handles for partitions 1-8
 *   +0x26: current partition index (byte)
 */
static char storage_ctx[0x100] __attribute__((aligned(4)));

/*========================================================================
 * GPIO LED helpers — MSM8909 TLMM
 *========================================================================*/

#define REG32(addr)  (*(volatile unsigned int *)(addr))

static void led_init(int gpio)
{
    /* Configure as GPIO function 0, output, no pull, 2mA drive */
    REG32(GPIO_CFG_ADDR(gpio)) =
          (GPIO_NO_PULL << GPIO_PULL_SHIFT)
        | (0            << GPIO_FUNC_SHIFT)   /* function 0 = GPIO */
        | (GPIO_2MA     << GPIO_DRV_SHIFT)
        | (GPIO_ENABLE  << GPIO_OE_SHIFT);
}

static void led_on(int gpio)
{
    REG32(GPIO_IN_OUT_ADDR(gpio)) = GPIO_OUT_BIT;
}

static void led_off(int gpio)
{
    REG32(GPIO_IN_OUT_ADDR(gpio)) = 0;
}

static void spin_delay(void)
{
    /* ~0.5s at ~200MHz-ish OCIMEM speed */
    volatile unsigned int i;
    for (i = 0; i < 2000000; i++);
}

static void blink(int gpio, int count)
{
    int j;
    for (j = 0; j < count; j++) {
        led_on(gpio);
        spin_delay();
        led_off(gpio);
        spin_delay();
    }
}

/*========================================================================
 * main — entry point from assembly
 *========================================================================*/
void main(void)
{
    int ret;
    (void)aboot_payload_gz;
    (void)aboot_payload_gz_len;

    /* Red was turned on in entry.S. Turn it off = proof we reached main. */
    led_init(LED_RED_GPIO);
    led_off(LED_RED_GPIO);

    /* Hang here — just testing entry→main transition */
    while (1);
}

#endif /* MINIMAL_EMBEDDED_PAYLOAD */
