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
        | (GPIO_OE_ENABLE << GPIO_OE_SHIFT);
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
    /* Pure CPU loop. We need this to be visible.
     * At 800 MHz, ~5 cycles/iter: 200M iters ≈ 1.25s
     * At 200 MHz: ≈ 5s.  At 19.2 MHz: ≈ 52s (too long but safe).
     * Start big so we can see SOMETHING, then tune down. */
    volatile unsigned int i;
    for (i = 0; i < 200000000; i++);
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
 * ICB config — BIMC QoS/arbitration registers
 *
 * These 32 writes replace FUN_0800d330 + DAL framework.
 * They configure BIMC bus arbitration for DDR slave ports.
 * May not be required for basic DDR access, but included for safety.
 *========================================================================*/
void icb_config(void)
{
    REG32(0x00449210) = 0x00000001;
    REG32(0x00450230) = 0x00000000;

    /* Slave port arbitration config */
    REG32(0x00408210) = 0x00000012;
    REG32(0x0040c210) = 0x00000012;
    REG32(0x00410210) = 0x00000012;
    REG32(0x00414210) = 0x00000012;
    REG32(0x00418210) = 0x80000012;
    REG32(0x0041c210) = 0x00000012;
    REG32(0x00420210) = 0x00000012;

    /* DDR0 priority + bandwidth */
    REG32(0x00408270) = 0x00043210;
    REG32(0x00408274) = 0x00043210;
    REG32(0x00408a04) = 0x00000014;
    REG32(0x00408a08) = 0x00000064;
    REG32(0x00408a24) = 0x0000ffce;
    REG32(0x00408a28) = 0x0000ff9c;
    REG32(0x00408a40) = 0x80000000;
    REG32(0x00408300) = 0x01000000;
    REG32(0x00408800) = 0x02000000;
    REG32(0x00408a00) = 0xfc000001;

    /* DDR1 priority + bandwidth (mirror of DDR0) */
    REG32(0x00410a04) = 0x00000014;
    REG32(0x00410a08) = 0x00000064;
    REG32(0x00410a24) = 0x0000ffce;
    REG32(0x00410a28) = 0x0000ff9c;
    REG32(0x00410a40) = 0x80000000;
    REG32(0x00410300) = 0x01000000;
    REG32(0x00410800) = 0x02000000;
    REG32(0x00410a00) = 0xfc000001;

    /* BIMC global segment config */
    REG32(0x00400904) = 0x00000206;
    REG32(0x00400908) = 0x00600060;
    REG32(0x0040090c) = 0x00270027;
    REG32(0x00400940) = 0x00000010;
    REG32(0x00400900) = 0x00000001;
}

/*========================================================================
 * DDR memory test — write/read pattern to verify DDR is working
 *========================================================================*/
static int ddr_test(void)
{
    volatile unsigned int *ddr = (volatile unsigned int *)SDRAM_START_ADDR;

    ddr[0] = 0xDEADBEEF;
    ddr[1] = 0xCAFEBABE;
    ddr[2] = 0x12345678;
    ddr[3] = 0x00000000;
    __asm__ volatile ("dsb" ::: "memory");

    if (ddr[0] != 0xDEADBEEF) return 0;
    if (ddr[1] != 0xCAFEBABE) return 0;
    if (ddr[2] != 0x12345678) return 0;
    if (ddr[3] != 0x00000000) return 0;
    return 1;
}

/*========================================================================
 * main — entry point from assembly
 *
 * At this point entry.S has already:
 *   - Initialized BIMC clocks
 *   - Copied DDR config and called ddr_set_params + ddr_init
 *   - Enabled SDCC1 clocks
 *========================================================================*/
void main(void)
{
    (void)aboot_payload_gz;
    (void)aboot_payload_gz_len;

    /* GREEN #10: both LEDs ON (red+green = orange/yellow).
     * Entry.S never has both on simultaneously, so this is unique.
     * No delays, no loops — just set and hang. */
    led_init(LED_RED_GPIO);
    led_init(LED_GREEN_GPIO);
    led_on(LED_RED_GPIO);
    led_on(LED_GREEN_GPIO);
    while (1);
}

#endif /* MINIMAL_EMBEDDED_PAYLOAD */
