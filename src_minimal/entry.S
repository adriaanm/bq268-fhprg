/*
 * entry.S — Minimal startup for MSM8909 firehose programmer.
 *
 * After PBL loads us via Sahara into OCIMEM (0x08006000), we:
 *   1. Set VBAR (exception vector base)
 *   2. Set up stack pointer
 *   3. Copy .data, zero BSS
 *   4. Enable GPLL0 PLL via vote register
 *   5. Early clock init (BIMC AHB clock)
 *   6. DDR init: ddr_set_params → bimc_clock_init → icb_config → ddr_init
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
    mov     r1, #(GPIO_OE_ENABLE << GPIO_OE_SHIFT)
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
     * Checkpoint macro: blink green LED once (0.5s on, 0.5s off)
     * Uses hardware sleep timetick (32768 Hz) for reliable timing.
     * Uses r4, r5 (caller-saved at this point, no C ABI yet)
     *--------------------------------------------------------------*/
    .macro checkpoint
    /* Configure green LED as output */
    ldr     r4, =GPIO_CFG_ADDR(LED_GREEN_GPIO)
    mov     r5, #(GPIO_OE_ENABLE << GPIO_OE_SHIFT)
    str     r5, [r4]
    /* Green ON */
    ldr     r4, =GPIO_IN_OUT_ADDR(LED_GREEN_GPIO)
    movs    r5, #GPIO_OUT_BIT
    str     r5, [r4]
    /* Delay 0.5s using sleep timetick (16384 ticks = 500ms) */
    ldr     r4, =MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL
    ldr     r5, [r4]            /* start tick */
99: ldr     r6, [r4]
    sub     r6, r6, r5
    ldr     r7, =16384          /* 32768 Hz * 0.5s */
    cmp     r6, r7
    blo     99b
    /* Green OFF */
    ldr     r4, =GPIO_IN_OUT_ADDR(LED_GREEN_GPIO)
    movs    r5, #0
    str     r5, [r4]
    /* Delay 0.5s gap */
    ldr     r4, =MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL
    ldr     r5, [r4]
98: ldr     r6, [r4]
    sub     r6, r6, r5
    ldr     r7, =16384
    cmp     r6, r7
    blo     98b
    .endm

    /*--------------------------------------------------------------
     * checkpoint_cpu: uses HW sleep timetick (same as checkpoint).
     * Originally used CPU loops, but at 800 MHz (after GPLL0) those
     * are too fast to see (~10ms).  The 32768 Hz timetick is clock-
     * independent and confirmed working.  Keeping the name to avoid
     * churn in the checkpoint comments.
     *--------------------------------------------------------------*/
    .macro checkpoint_cpu
    /* Configure green LED as output */
    ldr     r4, =GPIO_CFG_ADDR(LED_GREEN_GPIO)
    mov     r5, #(GPIO_OE_ENABLE << GPIO_OE_SHIFT)
    str     r5, [r4]
    /* Green ON */
    ldr     r4, =GPIO_IN_OUT_ADDR(LED_GREEN_GPIO)
    movs    r5, #GPIO_OUT_BIT
    str     r5, [r4]
    /* Delay 0.5s using sleep timetick (16384 ticks = 500ms) */
    ldr     r4, =MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL
    ldr     r5, [r4]            /* start tick */
96: ldr     r6, [r4]
    sub     r6, r6, r5
    ldr     r7, =16384          /* 32768 Hz * 0.5s */
    cmp     r6, r7
    blo     96b
    /* Green OFF */
    ldr     r4, =GPIO_IN_OUT_ADDR(LED_GREEN_GPIO)
    movs    r5, #0
    str     r5, [r4]
    /* Delay 0.5s gap */
    ldr     r4, =MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL
    ldr     r5, [r4]
95: ldr     r6, [r4]
    sub     r6, r6, r5
    ldr     r7, =16384
    cmp     r6, r7
    blo     95b
    .endm

    /*--------------------------------------------------------------
     * 1. Exception vectors + DACR
     *
     * Set VBAR for our exception handler.
     * Set DACR to 0x55555555 (Client mode for all domains) —
     * the original programmer does this early (FUN_08007ef0).
     * PBL may leave a restrictive DACR that blocks some domains.
     *--------------------------------------------------------------*/
    ldr     r0, =_vectors
    mcr     p15, 0, r0, c12, c0, 0     /* VBAR = _vectors */

    /* Keep MMU ON (PBL's page table provides device-memory attributes).
     * Set DACR to Manager — bypasses all domain permission checks. */
    ldr     r0, =0xFFFFFFFF
    mcr     p15, 0, r0, c3, c0, 0      /* DACR = all Manager */

    /* Set TTBCR.N=0 so TTBR0 covers all 4GB (16KB table).
     * PBL may have N>0, making high addresses (0x80000000+) use TTBR1.
     * We need TTBR0 to cover DDR at 0x80000000. */
    movs    r0, #0
    mcr     p15, 0, r0, c2, c0, 2      /* TTBCR = 0 (N=0) */
    isb

    checkpoint              /* GREEN #1: VBAR done */

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

    checkpoint              /* GREEN #2: stack + data + BSS done */

    /* Early page table removed — PBL's page table works fine
     * (timetick, GPIO, GPLL0 all work with it).  setup_page_table()
     * in main() handles remapping after DDR init. */

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

    checkpoint              /* GREEN #3: GPLL0 locked */

    /*--------------------------------------------------------------
     * 6. Early clock init (FUN_0800a790 equivalent)
     *
     * The original programmer calls this BEFORE any DDR work.
     * Writes 1 to GCC register 0x01830038 — likely enables the
     * BIMC config/AHB clock needed for register access at 0x004xxxxx.
     * Also sets initial bits in PLL USER_CTL registers.
     *--------------------------------------------------------------*/
    ldr     r0, =0x01830038
    movs    r1, #1
    str     r1, [r0]

    /* Set bit 8 in APCS_CLOCK_BRANCH_ENA_VOTE (0x01845004) */
    ldr     r0, =0x01845004
    ldr     r1, [r0]
    ldr     r2, =0x0003f7ff
    and     r1, r1, r2
    orr     r1, r1, #0x100
    str     r1, [r0]

    /* Set bit 6 in GCC_GPLL0_USER_CTL (0x01836004) */
    ldr     r0, =0x01836004
    ldr     r1, [r0]
    ldr     r2, =0x0003f7ff
    and     r1, r1, r2
    orr     r1, r1, #0x40
    str     r1, [r0]
    dsb

    checkpoint_cpu          /* GREEN #4: early clock init done */

    /*--------------------------------------------------------------
     * 7. DDR init sequence — matches original sbl1_hw_init order:
     *    ddr_set_params → bimc_clock_init → icb_config → ddr_init
     *--------------------------------------------------------------*/
    bl      ddr_set_params_only
    checkpoint_cpu          /* GREEN #5: ddr_set_params done */

    bl      bimc_clock_init
    checkpoint_cpu          /* GREEN #6: bimc_clock_init done */

    bl      icb_config
    checkpoint_cpu          /* GREEN #7: icb_config done */

    bl      ddr_init_only
    checkpoint_cpu          /* GREEN #8: ddr_init done */

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

/*==============================================================
 * bimc_clock_init — Full BIMC clock setup (Phases 1-2-3-5-6)
 *
 * Must be called BEFORE ddr_set_params — the DDR blob modifies
 * BIMC state that blocks the RCG switch if done afterward.
 *
 * Clobbers: r0-r2
 *==============================================================*/
    .thumb_func
bimc_clock_init:
    push    {lr}

    /* --- Phase 1: Clear GCC reset registers --- */
    movs    r1, #0
    ldr     r0, =GCC_RESET_0
    str     r1, [r0]
    ldr     r0, =GCC_RESET_1
    str     r1, [r0]
    ldr     r0, =GCC_RESET_2
    str     r1, [r0]
    ldr     r0, =GCC_RESET_3
    str     r1, [r0]

    /* Check TCSR bit 20 → determines PLL reset value */
    ldr     r0, =TCSR_SOC_VERSION
    ldr     r1, [r0]
    ubfx    r1, r1, #20, #1
    ldr     r0, =GCC_GPLL0_MODE_ALT    /* 0x01836000 */
    str     r1, [r0]
    ldr     r0, =0x01845000
    str     r1, [r0]
    dsb

    /* --- Phase 2: Configure PLL USER_CTL registers --- */
    ldr     r0, =GCC_GPLL0_USER_CTL    /* 0x01836004 */
    ldr     r1, [r0]
    ldr     r2, =0x0003f7ff
    and     r1, r1, r2
    orr     r1, r1, #0x20000
    str     r1, [r0]
    ldr     r1, [r0]
    and     r1, r1, r2
    orr     r1, r1, #0x40
    str     r1, [r0]

    ldr     r0, =GCC_BIMC_PLL_USER_CTL /* 0x01845004 */
    ldr     r1, [r0]
    ldr     r2, =0x000217ff
    and     r1, r1, r2
    ldr     r2, =0x1e000
    orr     r1, r1, r2
    str     r1, [r0]
    dsb

    /* --- Phase 3: Enable 8 BIMC branch clocks --- */
    ldr     r0, =GCC_BIMC_CBCR_7       /* 0x01832024 */
    bl      .Lcbcr_enable
    ldr     r0, =GCC_BIMC_CBCR_5       /* 0x0183201c */
    bl      .Lcbcr_enable
    ldr     r0, =GCC_BIMC_CBCR_6       /* 0x01832020 */
    bl      .Lcbcr_enable
    ldr     r0, =GCC_BIMC_CBCR_0       /* 0x01831008 */
    bl      .Lcbcr_enable
    ldr     r0, =GCC_BIMC_CBCR_1       /* 0x0183100c */
    bl      .Lcbcr_enable
    ldr     r0, =GCC_BIMC_CBCR_2       /* 0x01831010 */
    bl      .Lcbcr_enable
    ldr     r0, =GCC_BIMC_CBCR_3       /* 0x01831014 */
    bl      .Lcbcr_enable
    ldr     r0, =GCC_BIMC_CBCR_4       /* 0x0183101c */
    bl      .Lcbcr_enable

    /* --- Phase 5: Switch BIMC DDR RCG to GPLL0, div=2 --- */
    ldr     r0, =GCC_BIMC_DDR_CFG_RCGR /* 0x01832008 */
    ldr     r1, [r0]
    ldr     r2, =0xFFFFC8E0
    and     r1, r1, r2
    orr     r1, r1, #(1 << 8)         /* source = 1 (GPLL0) */
    orr     r1, r1, #1                /* divider = 2-1 = 1 */
    str     r1, [r0]

    ldr     r0, =GCC_BIMC_DDR_CMD_RCGR /* 0x01832004 */
    ldr     r1, [r0]
    orr     r1, r1, #CMD_UPDATE_BIT
    str     r1, [r0]
    dsb
.Lbimc_cmd_wait:
    ldr     r1, [r0]
    tst     r1, #CMD_UPDATE_BIT
    bne     .Lbimc_cmd_wait

    /* Switch BIMC MISC mux */
    ldr     r0, =GCC_BIMC_MISC         /* 0x01831018 */
    ldr     r1, [r0]
    ldr     r2, =0x003f0f00
    and     r1, r1, r2
    orr     r1, r1, #0x500
    str     r1, [r0]
    orr     r1, r1, #0x200             /* trigger update */
    str     r1, [r0]
    dsb
.Lbimc_misc_wait:
    ldr     r1, [r0]
    tst     r1, #0x200
    bne     .Lbimc_misc_wait

    /* --- Phase 6: Switch GFX RCG to GPLL0, div=5 --- */
    ldr     r0, =GCC_BIMC_GFX_CFG_RCGR /* 0x01837004 */
    ldr     r1, [r0]
    ldr     r2, =0xFFFFC8E0
    and     r1, r1, r2
    orr     r1, r1, #(1 << 8)         /* source = 1 (GPLL0) */
    orr     r1, r1, #4                /* divider = 5-1 = 4 */
    str     r1, [r0]

    ldr     r0, =GCC_BIMC_GFX_CMD_RCGR /* 0x01837000 */
    ldr     r1, [r0]
    orr     r1, r1, #CMD_UPDATE_BIT
    str     r1, [r0]
    dsb
.Lgfx_cmd_wait:
    ldr     r1, [r0]
    tst     r1, #CMD_UPDATE_BIT
    bne     .Lgfx_cmd_wait

    pop     {pc}

/* Helper: enable a CBCR clock branch.  r0 = CBCR address. */
    .thumb_func
.Lcbcr_enable:
    ldr     r1, [r0]
    orr     r1, r1, #CBCR_BRANCH_ENABLE_BIT
    str     r1, [r0]
    dsb
.Lcbcr_poll:
    ldr     r1, [r0]
    tst     r1, r1                    /* bit 31 = CLK_OFF → N flag */
    bmi     .Lcbcr_poll
    bx      lr

/*==============================================================
 * bimc_branch_clocks_enable — Enable BIMC clock branches only
 *
 * Safe subset of bimc_clock_init: just enable the 8 BIMC CBCR
 * branch clocks without touching any PLLs or RCGs.  PBL already
 * has the clock source (GPLL0) configured and running.
 *
 * Clobbers: r0-r1
 *==============================================================*/
    .thumb_func
bimc_branch_clocks_enable:
    push    {lr}

    ldr     r0, =GCC_BIMC_CBCR_7       /* 0x01832024 */
    bl      .Lcbcr_enable
    ldr     r0, =GCC_BIMC_CBCR_5       /* 0x0183201c */
    bl      .Lcbcr_enable
    ldr     r0, =GCC_BIMC_CBCR_6       /* 0x01832020 */
    bl      .Lcbcr_enable
    ldr     r0, =GCC_BIMC_CBCR_0       /* 0x01831008 */
    bl      .Lcbcr_enable
    ldr     r0, =GCC_BIMC_CBCR_1       /* 0x0183100c */
    bl      .Lcbcr_enable
    ldr     r0, =GCC_BIMC_CBCR_2       /* 0x01831010 */
    bl      .Lcbcr_enable
    ldr     r0, =GCC_BIMC_CBCR_3       /* 0x01831014 */
    bl      .Lcbcr_enable
    ldr     r0, =GCC_BIMC_CBCR_4       /* 0x0183101c */
    bl      .Lcbcr_enable

    pop     {pc}

/*==============================================================
 * ddr_set_params_only — Copy DDR config to IMEM and call ddr_set_params
 *
 * 1. memcpy(0x08600190, ddr_config_data, 760)
 * 2. Verify DDR blob is present in IMEM
 * 3. ddr_set_params(0x08600190, 760)  @ 0x00222780
 *
 * Clobbers: r0-r6
 *==============================================================*/
    .thumb_func
ddr_set_params_only:
    push    {r4-r6, lr}

    /* 1. Copy DDR config to IMEM at 0x08600190 */
    ldr     r0, =DDR_CONFIG_IMEM_ADDR  /* dest = 0x08600190 */
    ldr     r1, =ddr_config_data       /* src */
    ldr     r2, =ddr_config_data_len
    ldr     r2, [r2]                   /* r2 = byte count (760) */
    bl      _memcpy32

    /* Verify DDR blob was loaded to IMEM by reading first word */
    ldr     r0, =0x00220000
    ldr     r1, [r0]            /* data abort here → blob not loaded */
    ldr     r2, =0xe321f0d6     /* expected first instruction */
    cmp     r1, r2
    bne     .Lddr_blob_bad

    /* Verify DDR data region is writable */
    ldr     r0, =0x00223024
    ldr     r1, [r0]            /* read current value */
    str     r1, [r0]            /* write it back (data abort if not writable) */

    /* 2. Call ddr_set_params(config_addr, size) */
    ldr     r0, =DDR_CONFIG_IMEM_ADDR
    ldr     r1, =ddr_config_data_len
    ldr     r1, [r1]
    ldr     r4, =DDR_SET_PARAMS_ADDR
    blx     r4

    pop     {r4-r6, pc}

/*==============================================================
 * ddr_init_only — Call ddr_init blob
 *
 * Must be called AFTER: ddr_set_params, bimc_clock_init, icb_config
 * (matching original sbl1_hw_init order)
 *
 * Clobbers: r0-r4
 *==============================================================*/
    .thumb_func
ddr_init_only:
    push    {r4, lr}

    ldr     r0, =0x61A80               /* clock speed = 400 MHz (GPLL0/2 = 800/2) */
    ldr     r4, =DDR_INIT_ADDR
    blx     r4

    pop     {r4, pc}

/* Error: DDR blob not loaded (first word mismatch) — fast red blinks (200ms) */
.Lddr_blob_bad:
    ldr     r4, =GPIO_CFG_ADDR(LED_RED_GPIO)
    mov     r5, #(GPIO_OE_ENABLE << GPIO_OE_SHIFT)
    str     r5, [r4]
    ldr     r6, =MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL
    ldr     r3, =6554              /* 200ms at 32768 Hz */
.Lddr_blink_loop:
    ldr     r4, =GPIO_IN_OUT_ADDR(LED_RED_GPIO)
    movs    r5, #GPIO_OUT_BIT
    str     r5, [r4]
    ldr     r5, [r6]
97: ldr     r7, [r6]
    sub     r7, r7, r5
    cmp     r7, r3
    blo     97b
    movs    r5, #0
    str     r5, [r4]
    ldr     r5, [r6]
96: ldr     r7, [r6]
    sub     r7, r7, r5
    cmp     r7, r3
    blo     96b
    b       .Lddr_blink_loop

/*--------------------------------------------------------------
 * Minimal exception vector table
 * Exceptions blink both LEDs rapidly to signal a crash.
 * Vector table MUST be ARM mode (entered without BX).
 *--------------------------------------------------------------*/
    .balign 32
    .global _vectors
    .arm
_vectors:
    b       .Larm_hang      /* Reset */
    b       .Lexception     /* Undefined */
    b       .Larm_hang      /* SVC */
    b       .Lexception     /* Prefetch abort */
    b       .Lexception     /* Data abort */
    b       .Larm_hang      /* Reserved */
    b       .Larm_hang      /* IRQ */
    b       .Larm_hang      /* FIQ */

.Larm_hang:
    wfi
    b       .Larm_hang

/* Exception handler (ARM mode): diagnostic blink using DFSR.
 * Pattern: 3×red, 1×green, N×red (fault code), 1×green, 2s pause, repeat.
 * The green blinks delimit the fault code so you just count red blinks
 * between the two green flashes.
 * Fault types (DFSR[3:0]):
 *   1 = alignment, 5 = translation (section), 7 = translation (page),
 *   8 = external abort, 13 = permission (section), 15 = permission (page)
 * Uses HW timetick (32768 Hz) — CPU loops are invisible at 800 MHz. */
.Lexception:
    /* Read fault status registers */
    mrc     p15, 0, r8, c5, c0, 0   /* DFSR */
    mrc     p15, 0, r9, c6, c0, 0   /* DFAR (saved for future use) */

    /* Extract fault type: DFSR[3:0] */
    and     r10, r8, #0xF

    /* Configure LEDs */
    ldr     r0, =GPIO_CFG_ADDR(LED_RED_GPIO)
    mov     r1, #(GPIO_OE_ENABLE << GPIO_OE_SHIFT)
    str     r1, [r0]
    ldr     r0, =GPIO_CFG_ADDR(LED_GREEN_GPIO)
    str     r1, [r0]
    /* Both OFF */
    ldr     r0, =GPIO_IN_OUT_ADDR(LED_GREEN_GPIO)
    mov     r1, #0
    str     r1, [r0]
    ldr     r0, =GPIO_IN_OUT_ADDR(LED_RED_GPIO)
    str     r1, [r0]

    ldr     r4, =MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL
    ldr     r5, =9830               /* 300ms at 32768 Hz */

.Lexc_repeat:
    /* --- Preamble: 3× red blinks --- */
    mov     r11, #3
    ldr     r0, =GPIO_IN_OUT_ADDR(LED_RED_GPIO)
.Lexc_pre:
    mov     r1, #GPIO_OUT_BIT
    str     r1, [r0]
    bl      .Lexc_delay
    mov     r1, #0
    str     r1, [r0]
    bl      .Lexc_delay
    subs    r11, r11, #1
    bne     .Lexc_pre

    /* --- Delimiter: 1× green blink --- */
    ldr     r0, =GPIO_IN_OUT_ADDR(LED_GREEN_GPIO)
    mov     r1, #GPIO_OUT_BIT
    str     r1, [r0]
    bl      .Lexc_delay
    mov     r1, #0
    str     r1, [r0]
    bl      .Lexc_delay

    /* --- Fault code: N× red blinks (N = DFSR[3:0]) --- */
    mov     r11, r10
    cmp     r11, #0
    beq     .Lexc_end_delim         /* skip if fault code = 0 */
    ldr     r0, =GPIO_IN_OUT_ADDR(LED_RED_GPIO)
.Lexc_code:
    mov     r1, #GPIO_OUT_BIT
    str     r1, [r0]
    bl      .Lexc_delay
    mov     r1, #0
    str     r1, [r0]
    bl      .Lexc_delay
    subs    r11, r11, #1
    bne     .Lexc_code

.Lexc_end_delim:
    /* --- End delimiter: 1× green blink --- */
    ldr     r0, =GPIO_IN_OUT_ADDR(LED_GREEN_GPIO)
    mov     r1, #GPIO_OUT_BIT
    str     r1, [r0]
    bl      .Lexc_delay
    mov     r1, #0
    str     r1, [r0]

    /* --- Long pause (2s) before repeating --- */
    ldr     r6, [r4]
    ldr     r5, =65536              /* 2s at 32768 Hz */
5:  ldr     r7, [r4]
    sub     r7, r7, r6
    cmp     r7, r5
    blo     5b
    ldr     r5, =9830               /* restore 300ms for next round */
    b       .Lexc_repeat

/* Delay subroutine: 300ms using HW timetick. Preserves r0, r4, r5, r10, r11. */
.Lexc_delay:
    ldr     r6, [r4]
3:  ldr     r7, [r4]
    sub     r7, r7, r6
    cmp     r7, r5
    blo     3b
    bx      lr

/*==============================================================
 * DDR blob callback stubs
 *
 * The DDR init blob contains thunks that call back to fixed
 * addresses in the programmer's code space:
 *   0x002203dc → thunk to 0x08006bdc (memcpy)
 *   0x00220410 → thunk to 0x08006d14 (memset_zero)
 *
 * These MUST be Thumb functions at exactly those addresses,
 * otherwise ddr_init crashes by jumping into unrelated code.
 *
 * Full callback list (from DDR blob thunk scan):
 *   0x08006b04 — memmove (overlap-safe copy)
 *   0x08006bdc — memcpy
 *   0x08006c40 — fast_memcpy (aligned 32-byte chunk copy)
 *   0x08006d14 — memset_zero
 *   0x08007edc — get_ttb (returns TTBR0 & 0xFFFFC000)
 *==============================================================*/

    .section .ddr_cb_memmove, "ax", %progbits
    .thumb
    .balign 4
    .global ddr_memmove
    .thumb_func
ddr_memmove:
    /* memmove(r0=dest, r1=src, r2=len) — overlap-safe copy */
    push    {r4, lr}
    cbz     r2, 2f
    cmp     r0, r1
    bls     .Lmemmove_fwd          /* dest <= src: forward copy */
    /* Backward copy (dest > src, might overlap) */
    add     r0, r0, r2
    add     r1, r1, r2
3:  ldrb    r3, [r1, #-1]!
    strb    r3, [r0, #-1]!
    subs    r2, r2, #1
    bne     3b
    b       2f
.Lmemmove_fwd:
1:  ldrb    r3, [r1], #1
    strb    r3, [r0], #1
    subs    r2, r2, #1
    bne     1b
2:  pop     {r4, pc}

    .section .ddr_cb_memcpy, "ax", %progbits
    .thumb
    .balign 4
    .global ddr_memcpy
    .thumb_func
ddr_memcpy:
    /* memcpy(r0=dest, r1=src, r2=len) — simple byte copy */
    push    {r4, lr}
    cbz     r2, 2f
1:  ldrb    r3, [r1], #1
    strb    r3, [r0], #1
    subs    r2, r2, #1
    bne     1b
2:  pop     {r4, pc}

    .section .ddr_cb_memset, "ax", %progbits
    .thumb
    .balign 4
    .global ddr_memset_zero
    .thumb_func
ddr_memset_zero:
    /* memset_zero(r0=dest, r1=len) — zero fill */
    push    {r4, lr}
    movs    r2, #0
    cbz     r1, 2f
1:  strb    r2, [r0], #1
    subs    r1, r1, #1
    bne     1b
2:  pop     {r4, pc}

    .section .ddr_cb_fast_memcpy, "ax", %progbits
    .thumb
    .balign 4
    .global ddr_fast_memcpy
    .thumb_func
ddr_fast_memcpy:
    /* fast_memcpy(r0=dest, r1=src, r2=len) — aligned copy */
    /* Original uses 32-byte chunks; simple byte copy is fine for us */
    push    {r4, lr}
    cbz     r2, 2f
1:  ldrb    r3, [r1], #1
    strb    r3, [r0], #1
    subs    r2, r2, #1
    bne     1b
2:  pop     {r4, pc}

    .section .ddr_cb_get_ttb, "ax", %progbits
    .thumb
    .balign 4
    .global ddr_get_ttb
    .thumb_func
ddr_get_ttb:
    /* get_ttb() — returns TTBR0 & 0xFFFFC000 */
    mrc     p15, 0, r0, c2, c0, 0  /* read TTBR0 */
    bic     r0, r0, #0x3F00
    bic     r0, r0, #0x00FF        /* r0 &= 0xFFFFC000 */
    bx      lr
