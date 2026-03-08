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
volatile uint DAT_004a3000 __attribute__((section(".mmio_timer"))) = 0;

/*========================================================================
 * String literals — originally in .text of the ELF
 *
 * The decompiled code references these as &DAT_xxx (address-of a char),
 * so they must be defined as char arrays (not pointers).
 *========================================================================*/

#ifndef MINIMAL_EMBEDDED_PAYLOAD
/* protocol.c / firehose_log */
char DAT_08027710[] = "data";       /* XML wrapper: <data>...</data> */
char DAT_08027718[] = "log";        /* XML tag: <log .../> */

/* handlers.c strings (only those used by kept handlers) */
char DAT_08022e28[] = "8909";       /* target name (configure) */
char DAT_08022ea0[] = "eMMC";       /* MemoryName (configure) */
char DAT_08024e68[] = "true";       /* rawmode attr (read) */

/* dispatch.c strings */
char DAT_0802f2e8[] = "data";       /* XML wrapper tag match */
char DAT_0802f354[] = "read";       /* command tag match */
char DAT_0802f3a8[] = "?xml";       /* XML declaration match */

/* emmc.c / send_xml_response strings */
char DAT_08037180[] = "data";       /* XML wrapper for response */
char DAT_08037194[] = "NAK";        /* negative acknowledge */
char DAT_080371a0[] = "ACK";        /* acknowledge */
char DAT_080371a4[] = "%s";         /* string attribute format */
char DAT_080371a8[] = "%d";         /* integer attribute format */
char DAT_080371ac[] = "%llu";       /* 64-bit attribute format */
char DAT_080371b4[] = "%c";         /* char attribute format */

/* xml.c strings */
char DAT_080390e0[] = " />";        /* self-closing tag suffix */
char DAT_080390fc[] = "<%s";        /* tag opening format */
char DAT_08039108[] = "<%s>";       /* tag opening with close bracket */
char DAT_080391e8[] = " %s=\"";     /* attribute: space + name + =" */
char DAT_080391ec[] = "\"";         /* closing double-quote */
#endif /* !MINIMAL_EMBEDDED_PAYLOAD */

/*========================================================================
 * State variables — originally in .data / .bss
 *
 * Initial values from the binary's .data segment at 0x0804xxxx.
 *========================================================================*/

/* Dispatch execution state: 0=idle, 1=pending, 2=executing */
char DAT_0804d3a4 = 0;

/* SDCC slot allocation counter — initial value 0x20 (32 max slots) */
int DAT_0804e2a8 = 0x20;

/* SDCC per-slot status table [2]: slot0=0x21, slot1=0x02 */
int DAT_0804e2ac[2] = { 0x21, 0x02 };

/* SDCC device handle table [2]: zero until populated by init */
uint DAT_0804e2b8[2] = { 0, 0 };

/* SDCC register bases initialized flag — starts uninitialized */
char DAT_0804e2c4 = 0;

/* SDCC register base table [2]: filled at runtime by sdcc_init_bases() */
uint DAT_0804e2c8[2] = { 0, 0 };

/* SDCC FIFO/HC base tables: filled at runtime by sdcc_init_bases() */
uint DAT_0804e2d0 = 0;
uint DAT_0804e2d8 = 0;
uint DAT_0804e2e0 = 0;

/* Global context struct — referenced by get_global_context() */
uint DAT_0805a8ac = 0;

/*========================================================================
 * Firehose protocol state — needed for firehose mode
 * (not used in embedded payload / diag console mode)
 *========================================================================*/

#ifndef MINIMAL_EMBEDDED_PAYLOAD

/* Stack canary value */
int DAT_0804cd58 = 0;

/* Firehose main context — double-buffered data pointers [2].
 * Buffer 0 at DAT_08054e90, buffer 1 at DAT_08054e94. */
uint DAT_08054e90 = 0;

/* Firehose XML receive buffer (4 KB) */
uint DAT_08054e98 = 0;

/* XML parser state struct (28 words) */
uint DAT_08055ea0 = 0;
static uint _parser_pad[27];  /* rest of parser struct */

/* Device extra state (0x150 bytes) */
char DAT_08055e90 = 0;
static char _dev_extra_pad[0x14F];

/* XML writer state struct (28 words) */
uint DAT_08055f18 = 0;
static uint _writer_pad[27];

/* XML writer position fields — accessed as globals by flush_xml_to_usb */
uint DAT_08055f28 = 0;  /* writer current pos (lo) — at writer[4] */
uint DAT_08055f2c = 0;  /* writer current pos (hi) — at writer[5] */

/* Transfer state */
char DAT_08055f88 = 0;         /* transfer error code */
uint DAT_08055f90 = 0;         /* last transfer size */
uint DAT_08055f94 = 0;         /* transfer pending flag */
uint DAT_08055f98 = 0;         /* transfer complete flag */
char DAT_08055f99 = 0;         /* xml send-and-wait done flag */
uint DAT_08055fb0 = 0;         /* total bytes transferred (lo) */
uint DAT_08055fb4 = 0;         /* total bytes transferred (hi) */
uint DAT_08055fb8 = 0x100000;  /* buffer capacity (lo) = 1 MB */
uint DAT_08055fbc = 0;         /* buffer capacity (hi) */
uint DAT_08055fc0 = 0;         /* error transfer count (lo) */
uint DAT_08055fc4 = 0;         /* error transfer count (hi) */
uint DAT_08055fc8 = 0;         /* success transfer count (lo) */
uint DAT_08055fcc = 0;         /* success transfer count (hi) */

/* Validation/digest state (stubs — not using validation) */
uint DAT_08057fe0 = 0;
uint DAT_08057fe4 = 0;
uint DAT_08057fe8 = 0;
uint DAT_08057fec = 0;
uint DAT_08057ff0 = 0;
uint DAT_08057ff4 = 0;
uint DAT_08057ff8 = 0;
uint DAT_08057ffc = 0;
uint DAT_08058000 = 0;
uint DAT_08058004 = 0;
char DAT_08055fd8 = 0;         /* validation enabled = no */
char DAT_08055fd9 = 0;
uint DAT_08055fda = 0;
int  DAT_08055fd4 = 0;         /* storage device index offset */

/* Configure options */
uint DAT_08058458 = 0x200;     /* disk sector size = 512 */
uint DAT_0805845c = 0;         /* disk sector size (hi) */
char DAT_08058480 = 0;         /* skip_write = no */
char DAT_08058481 = 0;         /* always_validate = no */
char DAT_08058482 = 0;         /* verbose = no */
int  DAT_08058484 = 0;         /* ack_raw_data_every_num_packets */

/* Storage context / device table */
uint DAT_08058430 = 0;
uint DAT_08058428 = 0;         /* log ring buffer index */
uint DAT_0805842c = 0;         /* log flag */
uint DAT_08058028 = 0;         /* log ring buffer */

/* Hotplug / partition state */
uint DAT_0805a440 = 0;
uint DAT_0805a444 = 0;
uint DAT_0805a448 = 0;
uint DAT_0805a44c = 0;
uint DAT_0805a450 = 0;
uint DAT_0805a454 = 0;
uint DAT_0805124c = 0;
uint DAT_08051250 = 0;

/* Partition table: 32 entries × 3 words */
uint DAT_08059efc[96] = { 0 };

/* Memory pool / misc */
uint DAT_0804d188 = 0;
uint DAT_0804d178 = 0;
uint DAT_0804d17c = 0;
uint DAT_0804d180 = 0;
uint DAT_0804d18c = 0;
uint DAT_0804d190 = 0;

/* PMIC state */
char DAT_0804d288 = 0;
uint DAT_0804d28a = 0;
uint DAT_0804d28c = 0;
uint DAT_0804d28e = 0;

/* Code label used as callback — placeholder */
char LAB_08028888 = 0;

#endif /* !MINIMAL_EMBEDDED_PAYLOAD */

/*========================================================================
 * Slot context — always needed (both embedded and firehose modes).
 *
 * 2 slots × 0xBC bytes each = 0x178 bytes total.
 * In the original binary this lives at hardcoded 0x08059cc8.
 * mmc_get_slot_context() returns &slot_contexts[slot * 0xBC/4].
 *========================================================================*/
uint slot_contexts[2 * (0xBC / 4)] = { 0 };
