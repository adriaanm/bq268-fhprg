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
