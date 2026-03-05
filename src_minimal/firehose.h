/* firehose.h — Shared types, constants, and forward declarations for the
 * minimal firehose programmer extraction.
 *
 * Every function preserves a comment: orig: 0xADDRESS
 * for traceability back to the full decompilation in src/fhprg/.
 *
 * NOTE: All forward declarations use K&R-style empty parentheses ()
 * to be compatible with the decompiled K&R function definitions.
 * In -std=gnu89, () means "unspecified arguments".
 */
#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

#include "libc_glue.h"

/*========================================================================
 * Ghidra type compatibility (subset of src/ghidra_types.h)
 *========================================================================*/

typedef uint8_t  undefined;
typedef uint8_t  undefined1;
typedef uint16_t undefined2;
typedef uint32_t undefined4;
typedef uint64_t undefined8;

typedef uint8_t  byte;
typedef int8_t   sbyte;
typedef uint16_t word;
typedef uint32_t dword;
typedef uint64_t qword;

typedef uint8_t  uchar;
typedef uint16_t ushort;
typedef uint32_t uint;
typedef uint64_t ulong;
typedef int64_t  longlong;
typedef uint64_t ulonglong;

/* Ghidra CONCAT macros */
#define CONCAT11(a,b)  ((uint16_t)(((uint16_t)(uint8_t)(a)  << 8)  | (uint8_t)(b)))
#define CONCAT12(a,b)  ((uint32_t)(((uint32_t)(uint8_t)(a)  << 16) | (uint16_t)(b)))
#define CONCAT13(a,b)  ((uint32_t)(((uint32_t)(uint8_t)(a)  << 24) | ((uint32_t)(b) & 0xffffffu)))
#define CONCAT14(a,b)  ((uint64_t)(((uint64_t)(uint8_t)(a)  << 32) | (uint32_t)(b)))
#define CONCAT22(a,b)  ((uint32_t)(((uint32_t)(uint16_t)(a) << 16) | (uint16_t)(b)))
#define CONCAT31(a,b)  ((uint32_t)(((uint32_t)(a)           << 8)  | (uint8_t)(b)))
#define CONCAT44(a,b)  ((uint64_t)(((uint64_t)(uint32_t)(a) << 32) | (uint32_t)(b)))

/* Ghidra SUB macros */
#define SUB41(x,n)  ((uint8_t) ((uint32_t)(x) >> ((n)*8)))
#define SUB42(x,n)  ((uint16_t)((uint32_t)(x) >> ((n)*8)))
#define SUB84(x,n)  ((uint32_t)((uint64_t)(x) >> ((n)*8)))

/* Ghidra sign/zero extend */
#define SEXT48(x)   ((int64_t)(int32_t)(x))
#define SEXT14(x)   ((int32_t)(int8_t)(x))
#define ZEXT48(x)   ((uint64_t)(uint32_t)(x))

/* Ghidra field accessor */
#define _GHIDRA_FIELD(val, off, T) (*(T*)((char*)&(val) + (off)))

/* Ghidra carry/borrow helpers */
static inline int CARRY4(unsigned int a, unsigned int b) { return (a + b) < a; }
static inline int SBORROW4(unsigned int a, unsigned int b) { return (int)a < (int)b; }

/* Ghidra function pointer type */
typedef undefined4 (code)();

/* 3-byte types */
typedef uint32_t uint3;
typedef uint32_t uint24_t;
typedef uint32_t undefined3;

/*========================================================================
 * ARM intrinsics (stubs for analysis, not execution)
 *========================================================================*/

static inline void DataMemoryBarrier(unsigned int opt) {
    (void)opt; __asm__ volatile("dmb" ::: "memory"); }
static inline void DataSynchronizationBarrier(unsigned int opt) {
    (void)opt; __asm__ volatile("dsb" ::: "memory"); }
static inline void InstructionSynchronizationBarrier(unsigned int opt) {
    (void)opt; __asm__ volatile("isb"); }

#define coprocessor_movefromRt(...) \
    ({ __asm__ volatile("" ::: "memory"); (unsigned int)0; })
#define coprocessor_moveto(...) \
    do { __asm__ volatile("" ::: "memory"); } while(0)

/*========================================================================
 * Globals (extern, provided by data blob at link time)
 *========================================================================*/

/* Stack canary */
extern int DAT_0804cd58;

/* --- Firehose state --- */
extern uint DAT_08054e90;       /* firehose main context */
extern uint DAT_08055ea0;       /* xml_parser state */
extern uint DAT_08055f18;       /* xml_writer state */
extern uint DAT_08055f28;       /* xml_writer param a */
extern uint DAT_08055f2c;       /* xml_writer param b */
extern char DAT_08055f88;       /* transfer error code */
extern char DAT_08055f99;       /* xml send-and-wait done flag */
extern uint DAT_08058430;       /* storage context (device table) */
extern uint DAT_08058428;       /* log ring buffer index */
extern uint DAT_0805842c;       /* log flag */
extern uint DAT_08058028;       /* log ring buffer */

/* --- Transfer counters (updated by transfer_callback) --- */
extern uint DAT_08055f90;       /* last transfer size */
extern uint DAT_08055f94;       /* transfer pending flag */
extern uint DAT_08055f98;       /* transfer complete flag */
extern uint DAT_08055fb0;       /* total bytes transferred (lo) */
extern uint DAT_08055fb4;       /* total bytes transferred (hi) */
extern uint DAT_08055fb8;       /* buffer capacity (lo) */
extern uint DAT_08055fbc;       /* buffer capacity (hi) */
extern uint DAT_08055fc0;       /* error transfer count (lo) */
extern uint DAT_08055fc4;       /* error transfer count (hi) */
extern uint DAT_08055fc8;       /* success transfer count (lo) */
extern uint DAT_08055fcc;       /* success transfer count (hi) */

/* --- Validation/digest state --- */
extern uint DAT_08057fe0;       /* hash table offset (lo) */
extern uint DAT_08057fe4;       /* hash table offset (hi) */
extern uint DAT_08057fe8;       /* hash index (lo) */
extern uint DAT_08057fec;       /* hash index (hi) */
extern uint DAT_08057ff0;       /* hash table size (lo) */
extern uint DAT_08057ff4;       /* hash table size (hi) */
extern uint DAT_08057ff8;       /* max digest size (lo) */
extern uint DAT_08057ffc;       /* max digest size (hi) */
extern uint DAT_08058000;       /* hash round counter (lo) */
extern uint DAT_08058004;       /* hash round counter (hi) */
extern char DAT_08055fd8;       /* validation enabled flag */
extern char DAT_08055fd9;       /* validation state */
extern uint DAT_08055fda;       /* hash data buffer base */

/* --- Configure options --- */
extern uint DAT_08058458;       /* disk sector size */
extern uint DAT_0805845c;       /* disk sector size high */
extern char DAT_08058480;       /* skip_write flag */
extern char DAT_08058481;       /* always_validate flag */
extern char DAT_08058482;       /* verbose flag */
extern int  DAT_08058484;       /* ack_raw_data_every_num_packets */
extern int  DAT_08055fd4;       /* storage device index offset */
extern char DAT_08055e90;       /* device extra state base */

/* --- String literals (defined in globals.c) --- */
extern char DAT_08027710[];     /* "data" (log wrapper) */
extern char DAT_08027718[];     /* "log" */
extern char DAT_08037180[];     /* "data" (response wrapper) */
extern char DAT_08037194[];     /* "NAK" */
extern char DAT_080371a0[];     /* "ACK" */
extern char DAT_080371a4[];     /* "%s" */
extern char DAT_080371a8[];     /* "%d" */
extern char DAT_080371ac[];     /* "%llu" */
extern char DAT_080371b4[];     /* "%c" */
extern char DAT_080390e0[];     /* " />" */
extern char DAT_080390fc[];     /* "<%s" */
extern char DAT_08039108[];     /* "<%s>" */
extern char DAT_080391e8[];     /* " %s=\"" */
extern char DAT_080391ec[];     /* "\"" */

/* --- Handler string literals (defined in globals.c) --- */
extern char DAT_08022e28[];     /* "8909" (target name) */
extern char DAT_08022ea0[];     /* "eMMC" (memory name) */
extern char DAT_08024e68[];     /* "true" (rawmode) */

/* --- Dispatch string literals (defined in globals.c) --- */
extern char DAT_0802f2e8[];     /* "data" (wrapper tag for dispatch) */
extern char DAT_0802f354[];     /* "read" */
extern char DAT_0802f3a8[];     /* "?xml" */

/* --- Dispatch state --- */
extern char DAT_0804d3a4;       /* dispatch execution state (0=idle, 1=pending, 2=executing) */

/* --- SDCC/eMMC globals (defined in globals.c) --- */
extern int  DAT_0804e2ac[2];    /* SDCC slot status table */
extern uint DAT_0804e2b8[2];    /* SDCC device handle table */
extern char DAT_0804e2c4;       /* SDCC bases initialized flag */
extern uint DAT_0804e2c8[2];    /* SDCC register base table */
extern uint DAT_0804e2d0;       /* SDCC register base table (alt) */
extern uint DAT_0804e2d8;       /* SDCC FIFO base table */
extern uint DAT_0804e2e0;       /* SDCC FIFO base table (alt) */

/* --- PMIC/DAL globals --- */
extern char DAT_0804d288;       /* PMIC initialized flag */
extern uint DAT_0804d28a;       /* PMIC power setting */
extern uint DAT_0804d28c;       /* PMIC rail config */
extern uint DAT_0804d28e;       /* PMIC default mode */

/* --- Hotplug/partition globals --- */
extern uint DAT_0805a440;       /* hotplug device handle (lo) */
extern uint DAT_0805a444;       /* hotplug device handle (hi) */
extern uint DAT_0805a448;       /* hotplug sector size */
extern uint DAT_0805a44c;       /* hotplug total sectors */
extern uint DAT_0805a450;       /* hotplug buf size */
extern uint DAT_0805a454;       /* hotplug max sectors */
extern uint DAT_0805124c;       /* hotplug buffer size constant */
extern uint DAT_08051250;       /* hotplug max transfer constant */
extern uint DAT_0805a8ac;       /* global context struct */

/* --- Memory pool / misc --- */
extern uint DAT_0804d188;       /* memory pool state */
extern uint DAT_0804d178;
extern uint DAT_0804d17c;
extern uint DAT_0804d180;
extern uint DAT_0804d18c;
extern uint DAT_0804d190;

/* Code labels used as callback addresses */
extern char LAB_08028888;       /* callback for xml send-and-wait */

/*========================================================================
 * Forward declarations — organized by file / subsystem
 *
 * All use K&R-style empty parentheses (). In gnu89, () = unspecified args.
 *========================================================================*/

/* ---- sdcc_regs.c ---- */
void sdcc_set_transfer_mode();            /* 0x0800bbb4: sdcc_set_transfer_mode */
void sdcc_cleanup();            /* 0x0800bd20: sdcc_cleanup/configure */
void sdcc_set_all_irq();            /* 0x0800bd78: sdcc_set_all_irq */
uint sdcc_read_status();            /* 0x0800bd8c: sdcc_read_status */
void sdcc_enable_clock();            /* 0x0800bda0: sdcc_enable_clock */
uint sdcc_read_present();            /* 0x0800be44: sdcc_read_present */
uint sdcc_read_present_state();            /* 0x0800be68: sdcc_read_present_state */
void sdcc_read_response();            /* 0x0800be78: sdcc_read_response */
void sdcc_clear_status();            /* 0x0800bfac: sdcc_clear_status */
void sdcc_set_block_count();            /* 0x0800c008: sdcc_set_block_count */
void sdcc_set_block_size();            /* 0x0800c018: sdcc_set_block_size */
void sdcc_set_cmd_arg();            /* 0x0800c0c4: sdcc_set_cmd_arg */
void sdcc_fire_cmd();            /* 0x0800c0d4: sdcc_fire_cmd */
void sdcc_set_irq_mask();            /* 0x0800c11c: sdcc_set_irq_mask */
void sdcc_set_transfer_ctrl();            /* 0x0800c12c: sdcc_set_transfer_ctrl */
void sdcc_reset_data_line();            /* 0x0800c154: sdcc_reset_data_line */
/* Extra reg functions used by card_init */
void sdcc_set_clock_divider();            /* 0x0800c0a8: sdcc_set_clock_divider */
void sdcc_set_adma_addr_lo();            /* 0x0800bfe8: sdcc_set_adma_addr_lo */
void sdcc_set_adma_addr_hi();            /* 0x0800bff8: sdcc_set_adma_addr_hi */
void sdcc_set_8bit_mode();            /* 0x0800bdbc: sdcc_set_8bit_mode */
void sdcc_trigger_vendor_reset();            /* 0x0800bdd8: sdcc_trigger_vendor_reset */
void sdcc_set_clock_mode();            /* 0x0800bdf8: sdcc_set_clock_mode */
void sdcc_set_hs_mode();            /* 0x0800be10: sdcc_set_hs_mode */
void sdcc_read_caps();            /* 0x0800be2c: sdcc_read_caps */
byte sdcc_read_power_mode();            /* 0x0800be54: sdcc_read_power_mode */
void sdcc_wait_pll_lock();            /* 0x0800beb8: sdcc_wait_pll_lock */
void sdcc_set_int_enable();            /* 0x0800bf18: sdcc_set_int_enable */
void sdcc_set_int_signal();            /* 0x0800bf34: sdcc_set_int_signal */
uint sdcc_read_clock_stable();            /* 0x0800bf74: sdcc_read_clock_stable */
void sdcc_set_led();            /* 0x0800bf88: sdcc_set_led */
void sdcc_set_dma_mode();            /* 0x0800c028: sdcc_set_dma_mode */
void sdcc_setup_caps();            /* 0x0800c058: sdcc_setup_caps */
void sdcc_set_bus_power();            /* 0x0800c104: sdcc_set_bus_power */
void sdcc_set_voltage();            /* 0x0800c180: sdcc_set_voltage */
void sdcc_set_bus_width_bit();            /* 0x0800bc64: sdcc_set_bus_width_bit */
void sdcc_init_bases();            /* 0x0800bc84: sdcc_init_bases */
void sdcc_set_flow_control();            /* 0x0800bccc: sdcc_set_flow_control */
void sdcc_set_bus_speed();            /* 0x0800bcec: sdcc_set_bus_speed */

/* ---- sdcc_helpers.c ---- */
void adma_bounce_read();            /* 0x0800bbec: ADMA bounce read */
undefined8 adma_bounce_write();      /* 0x0800bc20: ADMA bounce write */
void sdcc_event_notify();            /* 0x080329f8: sdcc_event_notify */
undefined4 sdcc_post_write_cleanup();      /* 0x08032d8c: sdcc_post_write_cleanup */
int  sdcc_fifo_write();            /* 0x08034314: sdcc_fifo_write */
undefined4 sdcc_dma_setup();      /* 0x080343c0: sdcc_dma_setup */
undefined4 sdcc_wait_complete();      /* 0x0803456c: sdcc_wait_complete */
int  mmc_switch_cmd6();            /* 0x08034a40: mmc_switch_cmd6 */
undefined4 sdcc_setup_data_xfer();      /* 0x08034b88: sdcc_setup_data_xfer */
undefined4 sdcc_adma_transfer();      /* 0x08034c14: sdcc_adma_transfer */
undefined4 sdcc_adma_write();      /* 0x08034eaa: sdcc_adma_write */
void sdcc_pre_cmd_hook();            /* 0x08034edc: sdcc_pre_cmd_hook */
int  sdcc_pre_write_setup();            /* 0x08035040: sdcc_pre_write_setup */
undefined4 sdcc_post_write_check();      /* 0x080350ee: sdcc_post_write_check */
undefined4 sdcc_busy_wait();      /* 0x08035134: sdcc_busy_wait */
undefined4 sdcc_pio_transfer();      /* 0x08035188: sdcc_pio_transfer */
uint sdcc_get_card_status();    /* 0x08034f80: send CMD13, return state */

/* ---- card_init.c ---- */
void sdcc_clock_setup();            /* 0x08032a04: clock source setup */
void mmc_set_bus_width();            /* 0x08032dcc: mmc_set_bus_width */
int  mmc_set_speed();            /* 0x08032eac: mmc_set_speed */
int  mmc_get_slot_context();            /* 0x08033ca0: mmc_get_slot_context */
void mmc_finalize_init();            /* 0x080335b4: mmc_finalize_init */
void mmc_release_slot();            /* 0x080335fc: mmc_release_slot */
char mmc_classify_error();            /* 0x08033dfc: mmc_classify_error */
int  mmc_identify_card();            /* 0x08033b30: mmc_identify_card */
int  mmc_config_bus();            /* 0x080345b8: mmc_config_bus */
undefined4 mmc_init_card();      /* 0x08034704: mmc_init_card */
int *mmc_read_ext_csd();            /* 0x08034cb4: mmc_read_ext_csd */
undefined4 mmc_setup_partitions();      /* 0x08034888: mmc_setup_partitions */

/* ---- xml.c ---- */
int  xml_advance();             /* 0x08038db4: tokenizer state machine */
bool xml_get_attr_value();      /* 0x08038d38 */
bool xml_get_tag_name();        /* 0x08038d76 */
uint xml_attr_match();          /* 0x0803906c */
uint xml_tag_match();           /* 0x08039092 */
void xml_wr_close_self();       /* 0x080390d8: write " />" */
void xml_wr_close_tag();        /* 0x080390e4: write "</tag>" */
void xml_wr_tag_name();         /* 0x080390f4: write "<tag" */
void xml_wr_open_tag();         /* 0x08039100: write "<tag " */
void xml_wr_attr_start();       /* 0x08039110 */
uint xml_wr_attr();             /* 0x08039122 */
bool xml_wr_attr_value();       /* 0x0803918c */
uint xml_wr_init();             /* 0x080391f0 */
void xml_wr_attr_quoted();      /* 0x08039174 */
void xml_wr_reset();            /* 0x08039234 */
uint xml_send_and_wait();       /* 0x08038c24 */
bool xml_get_attr_name();       /* 0x08038cfa */

/* ---- protocol.c ---- */
void firehose_log();            /* 0x08027674: printf -> XML log */
uint bounded_memcpy();          /* 0x08027bf8 */
uint bounded_memmove();         /* 0x08027c12 */
void bounded_memset();          /* 0x080287e2 */
void transfer_callback();       /* 0x08028810: USB transfer done */
undefined4 eval_sector_expression(); /* 0x080288b0: shunting-yard (stub) */
uint parse_sector_value();      /* 0x08028c10: parse sector num (stub) */

/* ---- dispatch.c ---- */
undefined4 firehose_dispatch(); /* 0x0802f130: command router */
void dispatch_set_state();      /* 0x0802f838 */
void dispatch_loop_tick();            /* dispatch loop tick */
void send_and_wait();            /* send-and-wait wrapper */

/* ---- handlers.c (minimal: configure, program, read, digest stub) ---- */
uint handle_configure();        /* 0x08022a00 */
int  handle_program();          /* 0x08024484 */
uint handle_read();             /* 0x08024b04 */
int  handler_validate_attr();   /* 0x08022178 */
int  handler_poll_usb();        /* 0x08022440 */
undefined4 handler_digest_cmd();/* 0x080233ec: stub, v2 */

/* ---- emmc.c ---- */
uint sdcc_get_device();         /* 0x08032ae4: get device from slot table */
uint sdcc_get_slot_status();    /* 0x08032af8: get slot status flags */
int  sdcc_send_cmd();           /* 0x08032b94: send eMMC command */
void sdcc_write_complete_notify(); /* 0x08033654: write done thunk */
int  sdcc_write_data();         /* 0x08033656: block data transfer */
uint mmc_get_card_type();       /* 0x08033cbc */
uint mmc_close_handle();        /* 0x08033d28: close device */
int  mmc_erase_range();         /* 0x08033d44: erase sectors */
uint mmc_get_partition_info();  /* 0x08033ee8: fill partition info */
int  mmc_open_device();         /* 0x08033fe0: init & open device */
int  mmc_write_blocks();        /* 0x08034170: write via CMD24/CMD25 */
int  mmc_switch_partition();    /* 0x08034202: CMD6 partition switch */
int  mmc_write_sectors();       /* 0x08034228: write with WP check */
uint mmc_get_capacity();        /* 0x080348e0: get partition capacity */
uint mmc_is_partition_active(); /* 0x08034966: check if partition selected */
int  mmc_ensure_partition();    /* 0x08034fb0: select correct partition */
uint handle_response();         /* 0x0803707c: send XML response */
uint send_xml_response();       /* 0x08037084: build & send response */
uint flush_xml_to_usb();        /* 0x080371b8: flush xml to USB */

/* ---- storage.c ---- */
uint storage_write_sectors();   /* 0x080381d8: write entry from handlers */
uint storage_select_partition();/* 0x08038206 */
uint parse_uint_from_str();     /* 0x0803823e */
int  strncasecmp_fh();          /* 0x080382fa: case-insensitive cmp */
uint storage_read_sectors();    /* 0x08038014 */
uint storage_get_sector_count();/* 0x08037f64 */

/* ---- transport.c ---- */
int  usb_read_complete();       /* 0x08021ca4 */
int  transport_read_data();     /* 0x08031170 */
void transport_set_pending();   /* 0x08030ecc */
int  pmic_set_power();          /* 0x0802d180 */

/* ---- platform.c ---- */
void fatal_error_dma_reset();   /* 0x08019984 */
void fatal_error_halt();        /* 0x0801999c */
uint crc32_update_byte();       /* 0x08019abc */
void debug_log();               /* 0x0801b6bc */
void transport_error_loop();    /* 0x0801b85c */
int  is_digit();                /* 0x08013520 */
void *get_global_context();     /* 0x08007450 */
void stack_canary_fail();       /* 0x08010960 */
int  dal_device_copy();         /* 0x08013078 */
uint sha256_hash();             /* 0x0800d59c */
uint bignum_divmod();           /* 0x0801be1c */

/*========================================================================
 * External functions (outside the 131-function closure)
 *
 * These are called from within our minimal code but live outside
 * the closure. They resolve at link time against the original binary.
 *========================================================================*/

/* libc-like */
int *get_ctype_table();            /* returns ctype table ptr */
/* FUN_080060c0 (__aeabi_uldivmod) replaced with C / and % operators */
uint bit_reverse();            /* bit_reverse for CRC */
longlong thunk_FUN_080071ec();  /* strtoll */
void thunk_FUN_080199b4();      /* delay_us */
void thunk_FUN_0800947c();

/* (SDCC register functions moved to sdcc_regs.c)
 * (eMMC helper functions moved to sdcc_helpers.c) */

/* (Card init functions moved to card_init.c) */

/* Transport/misc (outside closure) */
int  transport_send();            /* transport_send */
void transport_config();            /* transport_config */
void transport_poll();            /* transport_poll */
void transport_helper_03c4();            /* transport_helper */
void transport_helper_0614();            /* transport_helper */
void transport_helper_fc0c();            /* transport_helper */
uint transport_helper_fcd0();            /* transport_helper */
void assert_abort();            /* assert/abort */
void uart_helper();            /* UART helper */
void hex_dump_log();            /* hex dump log */
void validation_reset();            /* validation reset */
void raw_usb_receive();            /* raw USB receive */
void dal_property_set();            /* DAL property set */
void dal_device_open();            /* DAL device open */
void pmic_status_check();            /* PMIC status check */
void qtimer_init();             /* timer init */

/* end of firehose.h */
