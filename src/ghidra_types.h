/* Ghidra decompiler type compatibility header for aboot re-compilation.
 * Provides typedefs for all Ghidra-specific types so the decompiled C
 * can be fed to arm-none-eabi-gcc.
 */
#pragma once
#include <stdint.h>
#include <stddef.h>

/* Ghidra undefined types */
typedef uint8_t  undefined;
typedef uint8_t  undefined1;
typedef uint16_t undefined2;
typedef uint32_t undefined4;
typedef uint64_t undefined8;

/* Ghidra scalar aliases */
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

/* Ghidra CONCAT macros (combine two values into a wider type).
 * CONCATmn: combine m-byte first arg with n-byte second arg. */
#define CONCAT11(a,b)  ((uint16_t)(((uint16_t)(uint8_t)(a)  << 8)  | (uint8_t)(b)))
#define CONCAT12(a,b)  ((uint32_t)(((uint32_t)(uint8_t)(a)  << 16) | (uint16_t)(b)))
#define CONCAT13(a,b)  ((uint32_t)(((uint32_t)(uint8_t)(a)  << 24) | ((uint32_t)(b) & 0xffffffu)))
#define CONCAT14(a,b)  ((uint64_t)(((uint64_t)(uint8_t)(a)  << 32) | (uint32_t)(b)))
#define CONCAT21(a,b)  ((uint32_t)(((uint32_t)(uint16_t)(a) << 8)  | (uint8_t)(b)))
#define CONCAT22(a,b)  ((uint32_t)(((uint32_t)(uint16_t)(a) << 16) | (uint16_t)(b)))
#define CONCAT24(a,b)  ((uint64_t)(((uint64_t)(uint16_t)(a) << 32) | (uint32_t)(b)))
#define CONCAT31(a,b)  ((uint32_t)(((uint32_t)(a)           << 8)  | (uint8_t)(b)))
#define CONCAT41(a,b)  ((uint64_t)(((uint64_t)(uint32_t)(a) << 8)  | (uint8_t)(b)))
#define CONCAT42(a,b)  ((uint64_t)(((uint64_t)(uint32_t)(a) << 16) | (uint16_t)(b)))
#define CONCAT44(a,b)  ((uint64_t)(((uint64_t)(uint32_t)(a) << 32) | (uint32_t)(b)))

/* Ghidra SUB macros (extract sub-field) */
#define SUB41(x,n)  ((uint8_t) ((uint32_t)(x) >> ((n)*8)))
#define SUB42(x,n)  ((uint16_t)((uint32_t)(x) >> ((n)*8)))
#define SUB84(x,n)  ((uint32_t)((uint64_t)(x) >> ((n)*8)))

/* Ghidra SEXT macros (sign extend) */
#define SEXT48(x)   ((int64_t)(int32_t)(x))
#define SEXT28(x)   ((int64_t)(int16_t)(x))
#define SEXT18(x)   ((int64_t)(int8_t)(x))
#define SEXT24(x)   ((int32_t)(int16_t)(x))
#define SEXT14(x)   ((int32_t)(int8_t)(x))

/* Ghidra ZEXT macros (zero extend) */
#define ZEXT48(x)   ((uint64_t)(uint32_t)(x))
#define ZEXT28(x)   ((uint64_t)(uint16_t)(x))
#define ZEXT18(x)   ((uint64_t)(uint8_t)(x))

/* Boolean (only define if not already provided) */
#ifndef __cplusplus
#include <stdbool.h>
#endif

/* Ghidra function pointer type: "code *" must be a callable function pointer type.
 * Returns undefined4 (not void) so vtable call results can be assigned to variables.
 * K&R style () means "unspecified args" so code* can be called with any arguments. */
typedef undefined4 (code)();

/* Ghidra indirect-jump placeholder.
 * K&R style definition: no prototype → any arg count accepted; returns undefined4
 * so its result can be assigned.  Also works as *UNRECOVERED_JUMPTABLE(). */
static undefined4 UNRECOVERED_JUMPTABLE() { return 0; }

/* Ghidra 3-byte integer type (int3 / uint3) */
typedef uint32_t int3;
typedef uint32_t uint3;

/* 24-bit types - use 32-bit for practical purposes */
typedef uint32_t uint24_t;
typedef int32_t int24_t;

/* 3-byte undefined type - use uint32 for simplicity */
typedef uint32_t undefined3;

/* ARM intrinsic stubs (Ghidra emits these as calls) */
static inline void disableFIQinterrupts(void) { __asm__ volatile("cpsid f"); }
static inline void enableFIQinterrupts(void)  { __asm__ volatile("cpsie f"); }
static inline void disableIRQinterrupts(void) { __asm__ volatile("cpsid i"); }
static inline void enableIRQinterrupts(void)  { __asm__ volatile("cpsie i"); }
static inline void disableInterrupts(void)    { __asm__ volatile("cpsid if"); }
static inline void enableInterrupts(void)     { __asm__ volatile("cpsie if"); }
static inline unsigned int getCPSR(void) {
    unsigned int r; __asm__ volatile("mrs %0, cpsr" : "=r"(r)); return r;
}
static inline void setCPSR(unsigned int v) {
    __asm__ volatile("msr cpsr_c, %0" :: "r"(v));
}

/* More ARM/Ghidra intrinsic stubs */
/* Note: msp/psp are Cortex-M only; on Cortex-A we use current SP */
static inline unsigned int getMainStackPointer(void) {
    unsigned int r; __asm__ volatile("mov %0, sp" : "=r"(r)); return r; }
static inline unsigned int getProcessStackPointer(void) {
    unsigned int r; __asm__ volatile("mov %0, sp" : "=r"(r)); return r; }
static inline int  SBORROW4(unsigned int a, unsigned int b) { return (int)a < (int)b; }
static inline int  CARRY4(unsigned int a, unsigned int b)   { return a < b; }
static inline int  SBORROW8(unsigned long long a, unsigned long long b) { return (long long)a < (long long)b; }
static inline int  CARRY8(unsigned long long a, unsigned long long b)   { return a < b; }
/* SCARRY4: signed overflow on 32-bit addition (V flag) */
static inline int  SCARRY4(unsigned int a, unsigned int b)  {
    int sa = (int)a, sb = (int)b, sr = (int)(a+b);
    return (sa >= 0) == (sb >= 0) && (sa >= 0) != (sr >= 0); }
static inline int  isCurrentModePrivileged(void)    { return (getCPSR() & 0x1f) != 0x10; }
static inline int  isThreadModePrivileged(void)     { return (getCPSR() & 0x1f) != 0x10; }
static inline int  isUsingMainStack(void)           { return (getCPSR() & 0x200) == 0; }
static inline int  isIRQinterruptsEnabled(void)     { return !(getCPSR() & 0x80); }
static inline int  isFIQinterruptsEnabled(void)     { return !(getCPSR() & 0x40); }
static inline int  getBasePriority(void)            { return 0; }
static inline int  getCurrentExceptionNumber(void)  { return 0; }
static inline void enterUserMode(void)     { __asm__ volatile("cps #0x10"); }
static inline void enterSupervisorMode(void) { __asm__ volatile("cps #0x13"); }

/* Ghidra _N_M_ field accessor: access M bytes at byte-offset N within a value.
 * Used as: val._offset_size_  e.g. x._4_4_  means uint32 at offset 4.
 * We handle this via a union trick macro:
 *   FIELD(x, offset, type)  reads 'type' at byte offset 'offset' from x.      */
#define _GHIDRA_FIELD(val, off, T) (*(T*)((char*)&(val) + (off)))

/* Suppress unused "unaffected register" variables that Ghidra emits. */
#define UNAFF_DECL(type, name)  volatile type name __attribute__((unused)) = 0

/* aboot load addresses (from aboot.bin ELF program headers) */
#define ABOOT_CODE_BASE  0x8f600000U
#define ABOOT_DATA_BASE  0x8f600000U  /* Single LOAD segment contains code + data */

/* Ghidra BADSPACEBASE - placeholder for invalid memory references */
typedef void BADSPACEBASE;

/* ARM Cortex-A coprocessor / privileged instruction stubs.
 * Ghidra names these as function calls in the decompiled output.
 * The actual implementation is one or two ARM instructions each. */

/* CP15 Control Register (SCTLR) read/write */
static inline unsigned int coproc_movefrom_Control(void) {
    unsigned int r; __asm__ volatile("mrc p15, 0, %0, c1, c0, 0" : "=r"(r)); return r; }
static inline void coproc_moveto_Control(unsigned int v) {
    __asm__ volatile("mcr p15, 0, %0, c1, c0, 0" :: "r"(v) : "memory"); }

/* CP15 Coprocessor Access Control Register (CPACR) read/write */
static inline unsigned int coproc_movefrom_Coprocessor_Access_Control(void) {
    unsigned int r; __asm__ volatile("mrc p15, 0, %0, c1, c0, 2" : "=r"(r)); return r; }
static inline void coproc_moveto_Coprocessor_Access_Control(unsigned int v) {
    __asm__ volatile("mcr p15, 0, %0, c1, c0, 2" :: "r"(v) : "memory"); }

/* Cache maintenance operations */
static inline void coproc_moveto_Invalidate_Entire_Instruction(unsigned int v) {
    __asm__ volatile("mcr p15, 0, %0, c7, c5, 0" :: "r"(v) : "memory"); }
static inline void coproc_moveto_Invalidate_Data_Cache_by_MVA(unsigned int v) {
    __asm__ volatile("mcr p15, 0, %0, c7, c6, 1" :: "r"(v) : "memory"); }
static inline void coproc_moveto_Clean_Data_Cache_by_Index(unsigned int v) {
    __asm__ volatile("mcr p15, 0, %0, c7, c14, 2" :: "r"(v) : "memory"); }

/* Generic coprocessor ops (Ghidra couldn't identify the specific register).
 * Called with varying arg counts across different sites, so use macros.
 * coprocessor_movefromRt(cp, op1, crn, crm, op2, ...) → reads a CP register
 * coprocessor_moveto(cp, op1, crn, crm, op2, val, ...) → writes a CP register
 * Treat as memory barriers to preserve ordering; return 0 for reads. */
#define coprocessor_movefromRt(...) \
    ({ __asm__ volatile("" ::: "memory"); (unsigned int)0; })
#define coprocessor_moveto(...) \
    do { __asm__ volatile("" ::: "memory"); } while(0)

/* Memory barriers */
static inline void DataMemoryBarrier(unsigned int opt) {
    (void)opt; __asm__ volatile("dmb" ::: "memory"); }
static inline void DataSynchronizationBarrier(unsigned int opt) {
    (void)opt; __asm__ volatile("dsb" ::: "memory"); }
static inline void InstructionSynchronizationBarrier(unsigned int opt) {
    (void)opt; __asm__ volatile("isb"); }

/* Count Leading Zeros (CLZ instruction) */
static inline unsigned int LZCOUNT(unsigned int v) {
    unsigned int r; __asm__ volatile("clz %0, %1" : "=r"(r) : "r"(v)); return r; }

/* Clear exclusive monitor (CLREX) */
static inline void ClearExclusiveLocal(void) { __asm__ volatile("clrex"); }

/* Secure Monitor Call — invokes TrustZone secure monitor.
 * SMC is an ARM32 instruction not available in Thumb mode; since we are
 * building for analysis/comparison rather than execution, stub it out.
 * Called with varying arg counts (1..4), so use a variadic macro. */
#define software_smc(id, ...)  ((unsigned int)(id))

/* ARM processor mode switches (write CPSR_c) */
static inline void setFIQMode(void)        { __asm__ volatile("cps #0x11"); }
static inline void setIRQMode(void)        { __asm__ volatile("cps #0x12"); }
static inline void setSupervisorMode(void) { __asm__ volatile("cps #0x13"); }
static inline void setAbortMode(void)      { __asm__ volatile("cps #0x17"); }
static inline void setUndefinedMode(void)  { __asm__ volatile("cps #0x1b"); }
static inline void setSystemMode(void)     { __asm__ volatile("cps #0x1f"); }
static inline void disableDataAbortInterrupts(void) { __asm__ volatile("cpsid a"); }

/* Additional CP15 operations */
static inline void WaitForInterrupt(void) { __asm__ volatile("wfi" ::: "memory"); }
static inline void coproc_moveto_Invalidate_Entire_Data_by_MVA(unsigned int v) {
    /* DCIMVAC — invalidate data cache line by MVA to PoC */
    __asm__ volatile("mcr p15, 0, %0, c7, c6, 1" :: "r"(v) : "memory"); }
static inline void coproc_moveto_Invalidate_unified_TLB_unlocked(unsigned int v) {
    /* TLBIALL — invalidate entire unified TLB */
    __asm__ volatile("mcr p15, 0, %0, c8, c7, 0" :: "r"(v) : "memory"); }
static inline void coproc_moveto_Translation_table_base_0(unsigned int v) {
    /* TTBR0 — Translation Table Base Register 0 */
    __asm__ volatile("mcr p15, 0, %0, c2, c0, 0" :: "r"(v) : "memory"); }
static inline void coproc_moveto_Domain_Access_Control(unsigned int v) {
    /* DACR — Domain Access Control Register */
    __asm__ volatile("mcr p15, 0, %0, c3, c0, 0" :: "r"(v) : "memory"); }

/* Load-exclusive result check: 1 = exclusive access still valid.
 * Takes the address that was load-exclusive'd (ignored in our stub). */
#define hasExclusiveAccess(addr)  (1)

/* CP15 Translation Table Base Register 0 — read (MRC) */
static inline unsigned int coproc_movefrom_Translation_table_base_0(void) {
    unsigned int r; __asm__ volatile("mrc p15, 0, %0, c2, c0, 0" : "=r"(r)); return r; }

/* CP15 Instruction Cache operations — variadic to handle extra Ghidra args */
#define coproc_moveto_Instruction_cache(v, ...) \
    do { unsigned int _v = (v); __asm__ volatile("mcr p15, 0, %0, c7, c5, 0" :: "r"(_v) : "memory"); } while(0)

/* SVC (supervisor call) instruction — Ghidra emits as software_interrupt(imm) */
static inline void software_interrupt(unsigned int svc_num) {
    /* Cannot encode dynamic SVC in inline asm; use SVC #0 as placeholder */
    (void)svc_num;
    __asm__ volatile("svc #0" ::: "memory");
}

/* USAT (unsigned saturate) — Ghidra emits as UnsignedSaturate(val, sat_to)
 * Variadic to handle varying arg counts across call sites. */
#define UnsignedSaturate(val, bits, ...) \
    ({ unsigned int _v = (unsigned int)(val), _m = (1u << (bits)) - 1; _v > _m ? _m : _v; })

/* Ghidra local variable artifacts: sometimes Ghidra creates _local_N
 * symbols for variables it couldn't map to the stack frame.
 * These must NOT be 'static' since src/fhprg.c has 'extern' declarations. */
