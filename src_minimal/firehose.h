/* firehose.h — Shared types, constants, and forward declarations for the
 * minimal firehose programmer extraction.
 *
 * Every function preserves a comment: orig: 0xADDRESS FUN_xxx
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
 * Key DAT_ globals (extern, provided by data blob at link time)
 *========================================================================*/

/* Firehose state structures */
extern uint DAT_08054e90;       /* fh_state — main firehose context */
extern uint DAT_08055ea0;       /* xml_parser state */
extern uint DAT_08055f18;       /* xml_writer state */
extern uint DAT_08055f28;       /* xml_writer param */
extern uint DAT_08055f2c;       /* xml_writer param */
extern char DAT_08055f88;       /* xml response flag */
extern char DAT_08055f99;       /* xml done flag */
extern uint DAT_08058430;       /* device table (storage context) */
extern uint DAT_08058428;       /* log ring buffer index */
extern uint DAT_0805842c;       /* log flag */
extern uint DAT_08058028;       /* log ring buffer */
extern uint DAT_08058458;       /* disk sector size */
extern uint DAT_0805845c;       /* disk sector size high word */
extern uint DAT_08055fb8;       /* buffer capacity low */
extern uint DAT_08055fbc;       /* buffer capacity high */
extern uint DAT_08057ff8;       /* max digest table size low */
extern uint DAT_08057ffc;       /* max digest table size high */
extern char DAT_08058480;       /* skip_write flag */
extern char DAT_08058481;       /* always_validate flag */
extern char DAT_08058482;       /* verbose flag */
extern int  DAT_08058484;       /* ack_raw_data_every_num_packets */
extern int  DAT_08055fd4;       /* storage device index offset */
extern char DAT_08055e90;       /* device extra state base */

/* Stack canary */
extern int DAT_0804cd58;

/* String literals referenced by protocol code */
extern char DAT_08027710;       /* "data" */
extern char DAT_08027718;       /* "log" */
extern char DAT_08037180;       /* "data" (response) */
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

/* Dispatch string literals */
extern char DAT_0802f2e8;       /* "configure" */
extern char DAT_0802f334;       /* "program" */
extern char DAT_0802f338;       /* "firmwarewrite" */
extern char DAT_0802f354;       /* "patch" */
extern char DAT_0802f394;       /* "setbootablestoragedrive" */
extern char DAT_0802f39c;       /* "storagextras" */
extern char DAT_0802f3a4;       /* "power" */
extern char DAT_0802f3a8;       /* "benchmark" */

/* Dispatch state */
extern uint DAT_0804d3a4;       /* dispatch execution state */

/* SDCC/eMMC globals */
extern uint DAT_0804e2ac;       /* SDCC slot table */
extern uint DAT_0804e2d8;       /* SDCC FIFO base table */

/* Storage extras string compare names */
extern char DAT_0803cad4;       /* hash init constant */
extern uint DAT_0803c9d4;       /* SHA-256 K constants */

/* Hotplug/partition globals */
extern uint DAT_0805a440;       /* hotplug state */
extern uint DAT_0805a444;
extern uint DAT_0805a448;
extern uint DAT_0805a44c;
extern uint DAT_0805a450;
extern uint DAT_0805a454;
extern uint DAT_0805124c;
extern uint DAT_08051250;
extern uint DAT_0805a8ac;       /* global ptr target */

/* Code labels used as callback addresses */
extern char LAB_08028888;       /* callback for xml send-and-wait */

/* Dispatch table */
extern uint DAT_0804d188;       /* memory pool state */
extern uint DAT_0804d178;
extern uint DAT_0804d17c;
extern uint DAT_0804d180;
extern uint DAT_0804d18c;
extern uint DAT_0804d190;

/*========================================================================
 * Forward declarations
 *
 * All use K&R-style empty parentheses for compatibility with the
 * decompiled function definitions. In gnu89, () = unspecified args.
 *========================================================================*/

/* xml.c */
int  FUN_08038db4();            /* xml_advance */
bool FUN_08038d38();            /* xml_get_attr_value */
bool xml_get_tag_name();
uint FUN_0803906c();            /* xml_attr_match */
uint xml_tag_match();
void FUN_080390d8();            /* xml_wr_close_self */
void FUN_080390e4();            /* xml_wr_close_elem */
void FUN_080390f4();            /* xml_wr_elem_name */
void FUN_08039100();            /* xml_wr_open */
void FUN_08039110();            /* xml_wr_attr_start (variadic) */
uint FUN_08039122();            /* xml_wr_attr */
bool FUN_0803918c();            /* xml_wr_attr_value */
uint FUN_080391f0();            /* xml_wr_append */
void FUN_08039174();            /* xml_wr_attr_quoted */
void FUN_08039234();            /* xml_wr_reset */
uint FUN_08038c24();            /* xml_send_and_wait */
bool FUN_08038cfa();            /* xml_get_attr_name */

/* protocol.c */
void firehose_log();            /* printf → XML log */
uint FUN_08027bf8();            /* bounded_memcpy */
uint FUN_08027c12();            /* bounded_memcpy_notrunc */
uint FUN_08028046();            /* attr_parse_u32 */
void FUN_080280e2();            /* attr parser */
void FUN_080287e2();            /* memset wrapper */
void FUN_08028810();            /* attr parser */
void FUN_080288b0();            /* attr parser */
uint FUN_08028c10();            /* parse_sector_number */

/* dispatch.c */
undefined4 firehose_dispatch(); /* command router */
void FUN_0802f838();
void FUN_0802f57c();            /* dispatch loop tick */
void FUN_0802f900();            /* send-and-wait wrapper */

/* handlers.c */
uint FUN_08022a00();            /* handle_configure */
int  handle_program();          /* handle_program */
uint FUN_08024b04();            /* handle_read */
uint FUN_08022650();            /* handle_benchmark */
uint FUN_08022ec8();            /* handle_erase */
uint FUN_08022ffc();            /* handle_firmwarewrite */
uint FUN_080238b8();            /* handle_getstorageinfo */
uint FUN_080239d0();            /* handle_nop */
uint FUN_080239dc();            /* handle_patch */
uint FUN_08023f64();            /* handle_peek */
uint FUN_08024134();            /* handle_poke */
uint FUN_08024350();            /* handle_power */
uint FUN_08024efc();            /* handle_setbootable */
uint FUN_08025054();            /* handle_storagextras */
int  FUN_08022178();            /* handler helper */
int  FUN_08022440();            /* handler helper */
undefined4 FUN_080233ec();      /* handler helper */

/* emmc.c */
uint FUN_08032ae4();            /* SDCC init */
uint FUN_08032af8();            /* SDCC get slot */
int  sdcc_command();            /* SDCC cmd dispatch */
int  mmc_write_dispatch();      /* write dispatch */
int  mmc_write_with_wp_check(); /* write + WP check */
int  mmc_pre_write_check();
uint FUN_08033ee8();            /* get_partition_info */
uint FUN_080348e0();            /* eMMC helper */
char FUN_08034966();            /* eMMC helper */
int  FUN_080358a4();            /* eMMC config */
int  FUN_08035962();            /* eMMC config */
int  FUN_08035ae0();            /* eMMC config */
int  FUN_08035af6();            /* eMMC config */
void FUN_0803649c();            /* response builder */
void FUN_08036ee8();            /* SHA update */
void FUN_080364e4();            /* response init */
void FUN_0803650c();            /* response builder */
void FUN_080365b8();            /* SHA-256 compress */
uint handle_response();         /* send XML response */
uint FUN_08037084();            /* response impl */
uint FUN_080371b8();            /* USB flush */
uint FUN_0803725c();            /* string replace */

/* storage.c */
uint mmc_write_wrapper();
uint FUN_08038206();            /* partition_select */
uint FUN_0803823e();            /* parse_int */
int  FUN_08038282();            /* strlcat-like */
int  strncmp_fh();              /* case-insensitive cmp */
uint FUN_08038014();            /* read_wrapper */
uint FUN_0803803c();            /* read helper */
uint FUN_0803805c();            /* storage extras parse */
uint FUN_08037c40();            /* storage helper */
uint FUN_08037c56();            /* storage helper */
uint FUN_08037c88();            /* commit stub */
uint FUN_08037cb0();            /* firmware update */
void FUN_08037e88();            /* log drive sizes */
uint FUN_08037f64();            /* get partition count */
uint FUN_08037f88();            /* log partition info */
int  FUN_08034170();            /* read dispatch */
int  FUN_08034202();            /* read helper */
int  FUN_08033d44();            /* erase range */
int  FUN_08033d28();            /* close/deinit */
int  FUN_08033fe0();            /* open partition */
int  FUN_08027328();            /* re-init HW */
int  FUN_08038236();            /* string match helper */

/* transport.c */
int  FUN_08021ca4();            /* USB raw read */
int  FUN_08031170();            /* transport read */
void FUN_08030ecc();            /* set pending transfer size */
int  FUN_0802d180();            /* DMA helper */
int  FUN_08030b04();            /* transport send */
void FUN_08030320();            /* transport config */
void FUN_08030fa8();            /* transport poll */
void FUN_080303c4();            /* transport helper */
void FUN_08030614();            /* transport helper */

/* hotplug.c */
int  FUN_08025b74();
int  FUN_08025c08();
int  FUN_08025c80();
int  FUN_08013918();
int  FUN_0802ef24();
void FUN_08026b88();
void FUN_08026af8();
uint *FUN_08026dd8();

/* platform.c */
void FUN_08019984();            /* fatal_halt (with DMA reset) */
void FUN_0801999c();            /* fatal_halt */
uint FUN_08019abc();            /* CRC32 */
uint FUN_08019a70();            /* CRC32 update */
uint FUN_0801be1c();            /* 96-bit divmod */
int  FUN_08013bb0();            /* dev dispatch */
void FUN_0801b6bc();            /* debug_log (ring buffer) */
void FUN_0801b85c();            /* transport_error */
int  FUN_08013520();            /* is_digit */
void *FUN_08007450();           /* global_ptr_getter */
uint FUN_0800d59c();            /* hash/checksum */
void FUN_08010960();            /* canary_fail (infinite loop) */
int  FUN_08013078();            /* boot helper */
uint FUN_08031548();            /* bit_reverse */
void thunk_FUN_080199b4();      /* delay_us */
void FUN_0802fc0c();            /* transport helper */
uint FUN_0802fcd0();            /* transport helper */
void FUN_08015a50();            /* assert/abort */
void FUN_0801a6a8();            /* UART helper */
void qtimer_init();             /* timer init */

/* libc-replaced functions (ctype table, printf engine) */
int *FUN_080060b0();            /* returns ctype table ptr */
uint FUN_080060c0();            /* 64-bit division */

/* thunk wrappers */
longlong thunk_FUN_080071ec();
void thunk_FUN_0800947c();

/* Misc functions called from decompiled code (not in closure) */
void FUN_0800bbb4();
uint FUN_0800bd8c();
uint FUN_0800be44();
void FUN_0800be10();
void FUN_0800bdf8();
void FUN_0800bf34();
void FUN_0800bfac();
void FUN_0800c008();
void FUN_0800c018();
void FUN_0800c028();
void FUN_0800c12c();
void FUN_0800c154();
void FUN_08006e1a();
void FUN_08009de0();
void FUN_08009980();
void FUN_08009af4();
void FUN_08009830();
void FUN_08009804();
int  FUN_0801622c();
void FUN_080162dc();
int  FUN_08016338();
void FUN_08032644();
int  FUN_08034eaa();            /* ADMA write */
void FUN_08034edc();            /* pre-command hook */
int  FUN_08034f80();            /* get card type */
int  FUN_08035040();            /* pre-write setup */
int  FUN_080350ee();            /* post-write check */
int  FUN_08034c14();            /* ADMA transfer */
int  FUN_08035188();            /* PIO transfer */
int  FUN_08032d8c();            /* post-write cleanup */
int  FUN_080333ba();            /* CSD parse helper */
int  FUN_0803456c();            /* wait for transfer */
int  FUN_08034314();            /* FIFO transfer */
void FUN_080343c0();            /* DMA setup */
void FUN_0800d58c();            /* hash helper */

/* end of firehose.h */
