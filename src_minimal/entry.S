/*
 * entry.S — Minimal startup for MSM8909 firehose programmer.
 *
 * After PBL loads us via Sahara into OCIMEM (0x08006000), we:
 *   1. Set VBAR (exception vector base)
 *   2. Set up stack pointer
 *   3. Copy .data, zero BSS
 *   4. Enable GPLL0 PLL via vote register
 *   5. Init DDR (call blob at 0x00222780)
 *   6. Enable GCC SDCC1 clocks (RCG + AHB + APPS branches)
 *   7. Branch to C main()
 *
 * Register definitions from lk_src/platform/msm8909/.
 */

#include "msm8909.h"

    .syntax unified
    .arch armv7-a

    /*==============================================================
     * ARM-mode entry stub
     *
     * The PBL jumps to e_entry without BX, so we must start in ARM
     * mode (original fhprg_peek.bin entry is ARM at 0x08008780).
     * We turn on the red LED immediately, then switch to Thumb.
     *==============================================================*/
    .section .text.entry, "ax", %progbits
    .balign 4
    .global _start
    .arm
_start:
    /* 0. Immediate LED — red on to prove we're running */
    ldr     r0, =GPIO_CFG_ADDR(LED_RED_GPIO)
    mov     r1, #(GPIO_ENABLE << GPIO_OE_SHIFT)
    str     r1, [r0]
    ldr     r0, =GPIO_IN_OUT_ADDR(LED_RED_GPIO)
    mov     r1, #GPIO_OUT_BIT
    str     r1, [r0]

    /* Switch to Thumb mode for the rest */
    adr     r0, _thumb_entry + 1
    bx      r0

    .thumb
    .thumb_func
_thumb_entry:

    /*--------------------------------------------------------------
     * Checkpoint macro: blink green LED once (~0.5s on, ~0.5s off)
     * Uses r4, r5 (caller-saved at this point, no C ABI yet)
     *--------------------------------------------------------------*/
    .macro checkpoint
    /* Configure green LED as output */
    ldr     r4, =GPIO_CFG_ADDR(LED_GREEN_GPIO)
    mov     r5, #(GPIO_ENABLE << GPIO_OE_SHIFT)
    str     r5, [r4]
    /* Green ON */
    ldr     r4, =GPIO_IN_OUT_ADDR(LED_GREEN_GPIO)
    movs    r5, #GPIO_OUT_BIT
    str     r5, [r4]
    /* Delay ~0.5s */
    ldr     r5, =2000000
99:
    subs    r5, #1
    bne     99b
    /* Green OFF */
    ldr     r4, =GPIO_IN_OUT_ADDR(LED_GREEN_GPIO)
    movs    r5, #0
    str     r5, [r4]
    /* Delay ~0.5s gap */
    ldr     r5, =2000000
98:
    subs    r5, #1
    bne     98b
    .endm

    /*--------------------------------------------------------------
     * 1. Exception vectors — point VBAR at a minimal vector table
     *--------------------------------------------------------------*/
    ldr     r0, =_vectors
    mcr     p15, 0, r0, c12, c0, 0     /* VBAR = _vectors */
    isb

    checkpoint              /* BLINK 1: VBAR done */

    /*--------------------------------------------------------------
     * 2. Stack — use top of OCIMEM DATA region
     *--------------------------------------------------------------*/
    ldr     sp, =_stack_top

    /*--------------------------------------------------------------
     * 3. Copy .data from CODE (LMA) to DATA (VMA)
     *--------------------------------------------------------------*/
    ldr     r0, =_data_start
    ldr     r1, =_data_load
    ldr     r2, =_data_end
.Ldata_loop:
    cmp     r0, r2
    bge     .Ldata_done
    ldr     r3, [r1], #4
    str     r3, [r0], #4
    b       .Ldata_loop
.Ldata_done:

    /*--------------------------------------------------------------
     * 4. Zero BSS
     *--------------------------------------------------------------*/
    ldr     r0, =__bss_start
    ldr     r1, =__bss_end
    movs    r2, #0
.Lbss_loop:
    cmp     r0, r1
    bge     .Lbss_done
    str     r2, [r0], #4
    b       .Lbss_loop
.Lbss_done:

    checkpoint              /* BLINK 2: stack + data + BSS done */

    /*--------------------------------------------------------------
     * 5. Enable GPLL0 (800 MHz) via vote register
     *
     * LK uses the vote register (APCS_GPLL_ENA_VOTE) with BIT(0)
     * and polls GPLL0_MODE BIT(30) for lock.  The direct MODE
     * register write we had before also works but the vote approach
     * matches LK and the original SBL1.
     *--------------------------------------------------------------*/
    ldr     r0, =APCS_GPLL_ENA_VOTE
    ldr     r1, [r0]
    orr     r1, r1, #1             /* BIT(0) = GPLL0 vote */
    str     r1, [r0]
    dsb
    ldr     r0, =GPLL0_MODE
.Lgpll0_wait:
    ldr     r1, [r0]
    tst     r1, #GPLL0_LOCK_BIT    /* BIT(30) */
    beq     .Lgpll0_wait

    checkpoint              /* BLINK 3: GPLL0 locked */

    /*--------------------------------------------------------------
     * 6. Init DDR — SKIPPED for now
     *
     * DDR init at 0x00222780 hangs (needs valid DDR config struct
     * at 0x08600190 with magic 0x44445200 and non-zero size param).
     * Not needed until we do eMMC writes with large buffers.
     *--------------------------------------------------------------*/

    checkpoint              /* BLINK 4: (DDR skipped) */

    /*--------------------------------------------------------------
     * 7. Enable GCC SDCC1 clocks
     *
     * Sequence (from lk_src/platform/msm_shared/clock_lib2.c):
     *   a) Configure RCG: set source + divider in CFG_RCGR
     *   b) Trigger CMD_RCGR update, wait for completion
     *   c) Enable AHB branch clock, wait for CLK_OFF to clear
     *   d) Enable APPS branch clock, wait for CLK_OFF to clear
     *
     * Initial clock: CXO (19.2 MHz), no divider.
     * The eMMC driver will reconfigure for higher speeds later.
     *--------------------------------------------------------------*/

    /* a) Configure RCG: source = CXO, divider = 1 */
    ldr     r0, =SDCC1_CFG_RCGR
    ldr     r1, [r0]
    bic     r1, r1, #CFG_SRC_SEL_MASK  /* clear source select */
    bic     r1, r1, #CFG_SRC_DIV_MASK  /* clear divider = div 1 */
    /* SRC_CXO = 0, so no need to OR in source */
    str     r1, [r0]

    /* b) Trigger CMD_RCGR update */
    ldr     r0, =SDCC1_CMD_RCGR
    ldr     r1, [r0]
    orr     r1, r1, #CMD_UPDATE_BIT
    str     r1, [r0]
    dsb
.Lcmd_wait:
    ldr     r1, [r0]
    tst     r1, #CMD_UPDATE_BIT
    bne     .Lcmd_wait

    /* c) Enable SDCC1 AHB branch clock */
    ldr     r0, =SDCC1_AHB_CBCR
    ldr     r1, [r0]
    orr     r1, r1, #CBCR_BRANCH_ENABLE_BIT
    str     r1, [r0]
    dsb
.Lahb_wait:
    ldr     r1, [r0]
    tst     r1, r1              /* N flag = bit 31 (CBCR_BRANCH_OFF) */
    bmi     .Lahb_wait

    /* d) Enable SDCC1 APPS branch clock */
    ldr     r0, =SDCC1_APPS_CBCR
    ldr     r1, [r0]
    orr     r1, r1, #CBCR_BRANCH_ENABLE_BIT
    str     r1, [r0]
    dsb
.Lapps_wait:
    ldr     r1, [r0]
    tst     r1, r1              /* N flag = bit 31 (CBCR_BRANCH_OFF) */
    bmi     .Lapps_wait

    checkpoint              /* BLINK 5: SDCC clocks done */

    /*--------------------------------------------------------------
     * 8. Jump to C main
     *--------------------------------------------------------------*/
    bl      main

    /* Should not return, but hang if it does */
.Lhang:
    wfi
    b       .Lhang

/*--------------------------------------------------------------
 * Helper: 32-bit aligned memcpy
 * r0 = dest, r1 = src, r2 = byte count
 *--------------------------------------------------------------*/
    .thumb_func
_memcpy32:
    push    {r4, lr}
.Lcopy_loop:
    cmp     r2, #0
    beq     .Lcopy_done
    ldr     r4, [r1], #4
    str     r4, [r0], #4
    subs    r2, r2, #4
    b       .Lcopy_loop
.Lcopy_done:
    pop     {r4, pc}

/*--------------------------------------------------------------
 * Minimal exception vector table
 * All exceptions just hang (infinite loop).
 *--------------------------------------------------------------*/
    .balign 32
    .global _vectors
_vectors:
    b       .Lhang      /* Reset */
    b       .Lhang      /* Undefined */
    b       .Lhang      /* SVC */
    b       .Lhang      /* Prefetch abort */
    b       .Lhang      /* Data abort */
    b       .Lhang      /* Reserved */
    b       .Lhang      /* IRQ */
    b       .Lhang      /* FIQ */
