/* globals.c — Self-hosted global variables and string literals.
 *
 * In the original binary these live in .text (string literals) and .data/.bss
 * (state variables). For the self-contained minimal build, we define them here
 * so they don't need to resolve against the original binary at link time.
 *
 * String values verified against fhprg_peek.bin ELF at their original VAs.
 * State variable initial values taken from the .data segment.
 */
#include "firehose.h"

/*========================================================================
 * MMIO timer register (hardware, read-only at runtime)
 *
 * QTIMER counter at physical 0x004a3000. Defined as a real variable here
 * so the symbol resolves; the linker script or loader must place it at the
 * correct MMIO address. For now it's a placeholder — code that reads it
 * will get 0 (which is fine for non-timing-critical paths).
 *========================================================================*/
volatile uint mmio_timer __attribute__((section(".mmio_timer"))) = 0;

/*========================================================================
 * State variables — originally in .data / .bss
 *
 * Initial values from the binary's .data segment at 0x0804xxxx.
 *========================================================================*/

/* SDCC slot allocation counter — initial value 0x20 (32 max slots) */
int sdcc_free_slots = 0x20;

/* SDCC per-slot status table [2]: slot0=0x21, slot1=0x02 */
int sdcc_slot_status[2] = { 0x21, 0x02 };

/* SDCC device handle table [2]: zero until populated by init */
uint sdcc_device_table[2] = { 0, 0 };

/* SDCC register bases initialized flag — starts uninitialized */
char sdcc_bases_inited = 0;

/* SDCC register base table [2]: filled at runtime by sdcc_init_bases() */
uint sdcc_mci_base[2] = { 0, 0 };

/* SDCC FIFO/HC base tables: filled at runtime by sdcc_init_bases().
 * Declared as uint[2] so (&arr)[slot] and arr[slot] index by 4 bytes (not 8). */
uint sdcc_dma_base[2] = { 0, 0 };
uint sdcc_hc_base[2] = { 0, 0 };
uint sdcc_hc_base_alt[2] = { 0, 0 };

/* Partition table: 32 entries × 3 words */
uint partition_table[96] = { 0 };

/*========================================================================
 * Slot context — always needed (both embedded and firehose modes).
 *
 * 2 slots × 0xBC bytes each = 0x178 bytes total.
 * In the original binary this lives at hardcoded 0x08059cc8.
 * mmc_get_slot_context() returns &slot_contexts[slot * 0xBC/4].
 *========================================================================*/
uint slot_contexts[2 * (0xBC / 4)] = { 0 };
