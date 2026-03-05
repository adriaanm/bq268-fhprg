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

/* --- String literals (in .rodata of original binary) --- */
extern char DAT_08027710;       /* "data" (log wrapper) */
extern char DAT_08027718;       /* "log" */
extern char DAT_08037180;       /* "data" (response wrapper) */
extern char DAT_08037194;       /* "NAK" */
extern char DAT_080371a0;       /* "ACK" */
extern char DAT_080371a4;       /* "%s" */
extern char DAT_080371a8;       /* "%d" */
extern char DAT_080371ac;       /* "%llu" */
extern char DAT_080371b4;       /* "%c" */
extern char DAT_080390e0;       /* " />" */
extern char DAT_080390fc;       /* "<%s" */
extern char DAT_08039108;       /* "<%s " */
extern char DAT_080391e8;       /* " %s=\"" */
extern char DAT_080391ec;       /* "\"" */

/* --- Dispatch string literals --- */
extern char DAT_0802f2e8;       /* "data" (wrapper tag for dispatch) */
extern char DAT_0802f334;       /* "storagextras" variant 1 */
extern char DAT_0802f338;       /* "storagextras" variant 2 */
extern char DAT_0802f354;       /* "read" */
extern char DAT_0802f394;       /* "peek" */
extern char DAT_0802f39c;       /* "poke" */
extern char DAT_0802f3a4;       /* "nop" */
extern char DAT_0802f3a8;       /* (unknown dispatch tag) */

/* --- Dispatch state --- */
extern uint DAT_0804d3a4;       /* dispatch execution state */

/* --- SDCC/eMMC globals --- */
extern uint DAT_0804e2ac;       /* SDCC slot status table */
extern uint DAT_0804e2b8;       /* SDCC device handle table */
extern char DAT_0804e2c4;       /* SDCC bases initialized flag */
extern uint DAT_0804e2c8;       /* SDCC register base table */
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
void FUN_0802f57c();            /* dispatch loop tick */
void FUN_0802f900();            /* send-and-wait wrapper */

/* ---- handlers.c ---- */
uint handle_configure();        /* 0x08022a00 */
int  handle_program();          /* 0x08024484 */
uint handle_read();             /* 0x08024b04 */
uint handle_benchmark();        /* 0x08022650 */
uint handle_erase();            /* 0x08022ec8 */
uint handle_firmwarewrite();    /* 0x08022ffc */
uint handle_getstorageinfo();   /* 0x080238b8 */
uint handle_nop();              /* 0x080239d0 */
uint handle_patch();            /* 0x080239dc */
uint handle_peek();             /* 0x08023f64 */
uint handle_poke();             /* 0x08024134 */
uint handle_power();            /* 0x08024350 */
uint handle_setbootable();      /* 0x08024efc */
uint handle_storagextras();     /* 0x08025054 */
int  handler_validate_attr();   /* 0x08022178 */
int  handler_poll_usb();        /* 0x08022440 */
undefined4 handler_digest_cmd();/* 0x080233ec */

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
uint str_find_replace();        /* 0x0803725c: find/replace in buffer */

/* ---- storage.c ---- */
uint storage_write_sectors();   /* 0x080381d8: write entry from handlers */
uint storage_select_partition();/* 0x08038206 */
uint parse_uint_from_str();     /* 0x0803823e */
int  safe_strlcat();            /* 0x08038282 */
int  strncasecmp_fh();          /* 0x080382fa: case-insensitive cmp */
uint storage_read_sectors();    /* 0x08038014 */
uint storage_select_and_read(); /* 0x0803803c */
uint storage_select_all();      /* 0x08037c40 */
uint storage_erase_partition(); /* 0x08037c56 */
uint storage_commit();          /* 0x08037c88 */
uint storage_fw_update();       /* 0x08037cb0 */
void storage_log_drive_info();  /* 0x08037e88 */
uint storage_get_sector_count();/* 0x08037f64 */
uint storage_log_partition_info(); /* 0x08037f88 */

/* ---- transport.c ---- */
int  usb_read_complete();       /* 0x08021ca4 */
int  transport_read_data();     /* 0x08031170 */
void transport_set_pending();   /* 0x08030ecc */
int  pmic_set_power();          /* 0x0802d180 */

/* ---- hotplug.c ---- */
int  hfat_open();               /* 0x08025b74 */
int  hfat_read();               /* 0x08025c08 */
int  hfat_close();              /* 0x08025c80 */
int  extfs_open();              /* 0x08013918 */
int  hotplug_parse_mbr();       /* 0x0802ef24 */
void hotplug_partition_init();  /* 0x08026b88 */
void hotplug_dev_alloc();       /* 0x08026af8 */
uint *hotplug_poll_device();    /* 0x08026dd8 */

/* ---- platform.c ---- */
void fatal_error_dma_reset();   /* 0x08019984 */
void fatal_error_halt();        /* 0x0801999c */
uint crc32_update_byte();       /* 0x08019abc */
int  dal_device_dispatch();     /* 0x08013bb0 */
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
int *FUN_080060b0();            /* returns ctype table ptr */
uint FUN_080060c0();            /* __aeabi_uldivmod (64-bit div) */
uint FUN_08031548();            /* bit_reverse for CRC */
longlong thunk_FUN_080071ec();  /* strtoll */
void thunk_FUN_080199b4();      /* delay_us */
void thunk_FUN_0800947c();

/* SDCC register-level functions (MMIO to controller) */
uint FUN_0800bd8c();            /* sdcc_read_status */
void FUN_0800bd20();            /* sdcc_cleanup */
uint FUN_0800be44();            /* sdcc_read_present */
uint FUN_0800be68();            /* sdcc_read_present_state */
void FUN_0800be78();            /* sdcc_read_response */
void FUN_0800bda0();            /* sdcc_enable_clock */
void FUN_0800bbb4();            /* sdcc_set_transfer_mode */
void FUN_0800bfac();            /* sdcc_clear_status */
void FUN_0800c008();            /* sdcc_set_block_count */
void FUN_0800c018();            /* sdcc_set_block_size */
void FUN_0800c0c4();            /* sdcc_set_cmd_arg */
void FUN_0800c0d4();            /* sdcc_fire_cmd */
void FUN_0800c11c();            /* sdcc_set_irq_mask */
void FUN_0800c12c();            /* sdcc_set_transfer_ctrl */
void FUN_0800c154();            /* sdcc_reset_data_line */

/* eMMC higher-level helpers (outside closure) */
int  FUN_08034b88();            /* sdcc_setup_data_xfer */
int  FUN_08035134();            /* sdcc_busy_wait */
void FUN_08034edc();            /* sdcc_pre_cmd_hook */
int  FUN_08034eaa();            /* sdcc_adma_write */
int  FUN_08035040();            /* sdcc_pre_write_setup */
int  FUN_080350ee();            /* sdcc_post_write_check */
int  FUN_08034c14();            /* sdcc_adma_transfer */
int  FUN_08035188();            /* sdcc_pio_transfer */
int  FUN_08032d8c();            /* sdcc_post_write_cleanup */
int  FUN_0803456c();            /* sdcc_wait_complete */
int  FUN_08034314();            /* sdcc_fifo_write */
void FUN_080343c0();            /* sdcc_dma_setup */
void FUN_080329f8();            /* sdcc_event_notify */
int  FUN_08034a40();            /* mmc_switch_cmd6 */

/* Card init (outside closure, called from mmc_open_device) */
int  FUN_08034704();            /* mmc_init_card */
int  FUN_0803460c();            /* mmc_init_fallback */
int  FUN_08033ca0();            /* mmc_get_slot_context */
int  FUN_08034cb4();            /* mmc_read_ext_csd */
int  FUN_08034888();            /* mmc_setup_partitions */
void FUN_080335b4();            /* mmc_finalize_init */
void FUN_080335fc();            /* mmc_release_slot */
char FUN_08033dfc();            /* mmc_classify_error */
int  FUN_080345b8();            /* mmc_config_bus */
int  FUN_08033b30();            /* mmc_identify_card */
void FUN_08032dcc();            /* mmc_set_bus_width */
int  FUN_08032eac();            /* mmc_set_speed */

/* Response/digest builders (outside closure, called from handlers) */
uint FUN_0803649c();            /* digest_finalize */
void FUN_080364e4();            /* digest_init */
uint FUN_08036ee8();            /* digest_update */
int  FUN_0803805c();            /* storage_set_extra_param */

/* Transport/misc (outside closure) */
int  FUN_08027328();            /* hw_reinit */
int  FUN_08030b04();            /* transport_send */
void FUN_08030320();            /* transport_config */
void FUN_08030fa8();            /* transport_poll */
void FUN_080303c4();            /* transport_helper */
void FUN_08030614();            /* transport_helper */
void FUN_0802fc0c();            /* transport_helper */
uint FUN_0802fcd0();            /* transport_helper */
void FUN_08015a50();            /* assert/abort */
void FUN_0801a6a8();            /* UART helper */
void FUN_080275c4();            /* hex dump log */
void FUN_0801daf0();            /* validation reset */
void FUN_080310a0();            /* raw USB receive */
void FUN_0802b248();            /* DAL property set */
void FUN_0802b6b4();            /* DAL device open */
void FUN_0802d0b8();            /* PMIC status check */
uint FUN_08019a70();            /* CRC32 table update */
void qtimer_init();             /* timer init */
void FUN_0801352e();            /* bignum_add */
void FUN_08038338();            /* bignum_sub */
void FUN_08019d98();            /* bignum_compare */
/* handler_validate_attr declared above in handlers section */

/* end of firehose.h */
