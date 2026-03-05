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

/* DDR buffer for decompression — 2 MB available at 0x80000000 */
#define DDR_BUFFER  ((unsigned char *)0x80000000)
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
 * main — entry point from assembly
 *========================================================================*/
void main(void)
{
    int ret;
    unsigned int decompressed_len;
    unsigned int num_sectors;

    /* 1. Initialize SDCC controller register bases.
     *    sdcc_init_bases() sets DAT_0804e2c8[] with controller addresses.
     *    Slot 0 = 0x07824000 (SDCC1, eMMC). */
    sdcc_init_bases();

    /* 2. Open eMMC device.
     *    mmc_open_device does the full card init sequence:
     *    CMD0 (reset) → CMD1 (OCR) → CMD2 (CID) → CMD3 (RCA) →
     *    CMD7 (select) → CMD8 (EXT_CSD) → bus width → speed setup.
     *
     *    Slot 0, open flags 0. */
    ret = mmc_open_device(0, 0);
    if (ret == 0) {
        /* Init failed — hang (no USB to report errors in embedded mode).
         * mmc_open_device returns 0 on failure, non-zero (partition entry
         * pointer) on success. */
        while (1);
    }

    /* 3. Set up storage context for partition access.
     *    mmc_open_device returned a partition entry pointer (ret != 0).
     *    The partition entry has [0] = device struct pointer.
     *    mmc_write_sectors expects the partition entry pointer directly:
     *      puVar3 = (uint *)*param_1  // entry[0] = device struct ptr
     *    Store it at ctx+0x04 for the write loop to retrieve. */
    memset(storage_ctx, 0, sizeof(storage_ctx));
    *(unsigned int *)(storage_ctx + 0x04) = (unsigned int)ret;
    storage_ctx[0x26] = 0;  /* partition 0 = user area */

    /* 4. Decompress gzipped aboot from embedded payload.
     *    Destination: DDR buffer at 0x80000000.
     *    The tinf library handles gzip header parsing and inflate. */
    decompressed_len = DDR_BUFFER_SIZE;
    ret = tinf_gzip_uncompress(DDR_BUFFER, &decompressed_len,
                               aboot_payload_gz, aboot_payload_gz_len);
    if (ret != TINF_OK) {
        while (1);  /* Decompression failed */
    }

    /* 5. Write decompressed data to aboot partition.
     *    Write in chunks — mmc_write_sectors handles CMD24/CMD25. */
    num_sectors = (decompressed_len + SECTOR_SIZE - 1) / SECTOR_SIZE;

    {
        unsigned int sectors_written = 0;
        unsigned int chunk;
        /* The partition entry pointer (from mmc_open_device) is passed
         * directly to mmc_write_sectors. It does:
         *   puVar3 = (uint *)*param_1   // entry[0] = device struct ptr
         *   slot = *puVar3              // dev_struct[0] = slot number
         * This matches how storage_write_sectors calls it. */
        unsigned int *part_entry = (unsigned int *)*(unsigned int *)(storage_ctx + 0x04);

        while (sectors_written < num_sectors) {
            /* Write up to 128 sectors (64 KB) at a time */
            chunk = num_sectors - sectors_written;
            if (chunk > 128) {
                chunk = 128;
            }

            ret = mmc_write_sectors(
                part_entry,
                TARGET_START_SECTOR + sectors_written,
                (unsigned int)(DDR_BUFFER + sectors_written * SECTOR_SIZE),
                chunk
            );

            if (ret != 0) {
                /* Write failed — hang */
                while (1);
            }

            sectors_written += chunk;
        }
    }

    /* 6. Done — reboot.
     *    Use PMIC to trigger a warm reset, or just hang and let
     *    the user power cycle. */

    /* Try PSHOLD reset (direct MMIO — MSM8909 PSHOLD at 0x004ab000) */
    *(volatile unsigned int *)0x004ab000 = 0;

    /* If PSHOLD didn't work, hang */
    while (1);
}

#endif /* MINIMAL_EMBEDDED_PAYLOAD */
