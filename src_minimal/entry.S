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
     * 6. Init DDR
     *
     * PBL already has BIMC core clocks running (it loaded our code
     * into OCIMEM via BIMC), but not all DDR branch clocks.
     * Enable the BIMC branch clocks, then call the DDR blob.
     *
     * NOTE: We skip the full bimc_clock_init because it writes
     * PLL config to 0x01821000 which is GPLL0_MODE — corrupting
     * the running system PLL.  Only the branch enables (Phase 3)
     * are safe.
     *--------------------------------------------------------------*/
    bl      bimc_branch_clocks_enable

    checkpoint              /* BLINK 3b: BIMC branches enabled */

    bl      ddr_config_and_init

    checkpoint              /* BLINK 4: DDR init done */

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
     * 9. Jump to C main
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

/*==============================================================
 * bimc_clock_init — Enable GCC clocks for the BIMC DDR controller
 *
 * Replaces FUN_0800ac84 from the original programmer.
 * Programs GCC PLL and branch clock registers so that the BIMC
 * controller at 0x0044c000 is accessible.
 *
 * Clobbers: r0-r5
 *==============================================================*/
    .thumb_func
bimc_clock_init:
    push    {lr}

    /* --- Phase 1: Reset clock sources --- */
    movs    r1, #0
    ldr     r0, =GCC_RESET_0
    str     r1, [r0]
    ldr     r0, =GCC_RESET_1
    str     r1, [r0]
    ldr     r0, =GCC_RESET_2
    str     r1, [r0]
    ldr     r0, =GCC_RESET_3
    str     r1, [r0]

    /* Check TCSR bit 20 for chip version → determines PLL reset value */
    ldr     r0, =TCSR_SOC_VERSION
    ldr     r1, [r0]
    ubfx    r1, r1, #20, #1        /* extract bit 20 → 0 or 1 */
    ldr     r0, =GCC_GPLL0_MODE_ALT
    str     r1, [r0]
    ldr     r0, =GCC_BIMC_PLL_USER_CTL  /* 0x01845000 = BIMC PLL MODE */
    sub     r0, r0, #4             /* 0x01845000 is USER_CTL, MODE is at 0x01845000-4? */
    /* Actually: GCC_BIMC_PLL_MODE is at CLK_CTL_BASE + 0x45000 - but that's the vote reg.
     * The actual BIMC PLL mode register from the analysis is at 0x01845000.
     * Let's just use the literal addresses from the analysis. */
    ldr     r0, =0x01845000
    str     r1, [r0]
    dsb

    /* --- Phase 2: Configure PLL USER_CTL registers --- */
    ldr     r0, =GCC_GPLL0_USER_CTL    /* 0x01836004 */
    ldr     r1, [r0]
    ldr     r2, =0x0003f7ff
    and     r1, r1, r2
    orr     r1, r1, #0x20000      /* set bit 17 */
    str     r1, [r0]
    ldr     r1, [r0]
    and     r1, r1, r2
    orr     r1, r1, #0x40         /* set bit 6 */
    str     r1, [r0]

    ldr     r0, =GCC_BIMC_PLL_USER_CTL /* 0x01845004 */
    ldr     r1, [r0]
    ldr     r2, =0x000217ff
    and     r1, r1, r2
    ldr     r2, =0x1e000
    orr     r1, r1, r2            /* set bits 16:13 */
    str     r1, [r0]
    dsb

    /* --- Phase 3: Enable 8 BIMC clock branches --- */
    /* Pattern: set bit 0, poll until bit 31 clears */
    ldr     r0, =GCC_BIMC_CBCR_7       /* 0x01832024 — start with outermost */
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

    /* --- Phase 4: Enable BIMC PLL1 --- */
    /* PLL config registers at BIMC_PLL_CONFIG_BASE (0x01821000) */
    ldr     r0, =BIMC_PLL_CONFIG_BASE

    /* Write config_ctl (+0x04) */
    ldr     r1, =BIMC_PLL_CONFIG_CTL   /* 0x4001055b */
    str     r1, [r0, #0x04]

    /* Write alpha_l (+0x08) */
    ldr     r1, =BIMC_PLL_ALPHA_L      /* 0x000000aa */
    str     r1, [r0, #0x08]

    /* Write alpha_h (+0x0c) */
    ldr     r1, =BIMC_PLL_ALPHA_H      /* 0xaa000000 */
    str     r1, [r0, #0x0c]

    /* Write L value into user_ctl (+0x10) */
    ldr     r1, =BIMC_PLL_L_VAL        /* 41 */
    str     r1, [r0, #0x10]

    /* PLL lock sequence: MODE |= BYPASSNL, wait, MODE |= RESET_N, poll lock, MODE |= OUTCTRL */
    ldr     r1, [r0]                   /* read current MODE */
    bic     r1, r1, #0xFF             /* clear low bits */
    orr     r1, r1, #PLL_BYPASSNL     /* bit 1 */
    str     r1, [r0]
    dsb

    /* Wait ~5us at ~200 MHz = ~1000 cycles */
    ldr     r2, =1000
.Lpll_wait1:
    subs    r2, #1
    bne     .Lpll_wait1

    orr     r1, r1, #(PLL_BYPASSNL | PLL_RESET_N)  /* bits 2:1 */
    str     r1, [r0]
    dsb

    /* Poll for PLL lock (bit 31) — timeout ~50us */
    ldr     r2, =100000
.Lpll_lock_wait:
    ldr     r3, [r0]
    tst     r3, r3                    /* check bit 31 (N flag) */
    bmi     .Lpll_locked
    subs    r2, #1
    bne     .Lpll_lock_wait
    /* Timeout — continue anyway */
.Lpll_locked:

    orr     r1, r1, #(PLL_BYPASSNL | PLL_RESET_N | PLL_OUTCTRL)  /* bits 2:1:0 */
    str     r1, [r0]
    dsb

    /* --- Phase 5: Switch BIMC DDR RCG to PLL1, div=2 --- */
    ldr     r0, =GCC_BIMC_DDR_CFG_RCGR /* 0x01832008 */
    ldr     r1, [r0]
    ldr     r2, =0xFFFFC8E0
    and     r1, r1, r2
    orr     r1, r1, #(1 << 8)         /* source = 1 (PLL1) */
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
    /* Trigger update (bit 9), poll until clear */
    orr     r1, r1, #0x200
    str     r1, [r0]
    dsb
.Lbimc_misc_wait:
    ldr     r1, [r0]
    tst     r1, #0x200
    bne     .Lbimc_misc_wait

    /* --- Phase 6: Switch GFX RCG to PLL1, div=5 --- */
    ldr     r0, =GCC_BIMC_GFX_CFG_RCGR /* 0x01837004 */
    ldr     r1, [r0]
    ldr     r2, =0xFFFFC8E0
    and     r1, r1, r2
    orr     r1, r1, #(1 << 8)         /* source = 1 (PLL1) */
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
 * ddr_config_and_init — Copy DDR config to IMEM and call DDR blob
 *
 * 1. memcpy(0x08600190, ddr_config_data, 760)
 * 2. ddr_set_params(0x08600190, 760)  @ 0x00222780
 * 3. ddr_init()                        @ 0x002224cc
 *
 * Clobbers: r0-r3
 *==============================================================*/
    .thumb_func
ddr_config_and_init:
    push    {r4-r6, lr}

    /* 1. Copy DDR config to IMEM at 0x08600190 */
    ldr     r0, =DDR_CONFIG_IMEM_ADDR  /* dest = 0x08600190 */
    ldr     r1, =ddr_config_data       /* src */
    ldr     r2, =ddr_config_data_len
    ldr     r2, [r2]                   /* r2 = byte count (760) */
    bl      _memcpy32

    checkpoint              /* BLINK 3c: config copied to IMEM */

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

    checkpoint              /* BLINK 3c2: DDR blob verified in IMEM */

    /* 2. Call ddr_set_params(config_addr, size) */
    ldr     r0, =DDR_CONFIG_IMEM_ADDR
    ldr     r1, =ddr_config_data_len
    ldr     r1, [r1]
    ldr     r4, =DDR_SET_PARAMS_ADDR
    blx     r4
    /* r0 = 1 on success, 0 on failure — could check but continue anyway */

    checkpoint              /* BLINK 3d: ddr_set_params done */

    /* 3. Call ddr_init() */
    ldr     r0, =0                     /* clock speed param (stored but not critical) */
    ldr     r4, =DDR_INIT_ADDR
    blx     r4

    pop     {r4-r6, pc}

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

/* Exception handler (ARM mode): fast alternating red/green blinks */
.Lexception:
    ldr     r0, =GPIO_CFG_ADDR(LED_RED_GPIO)
    mov     r1, #(GPIO_OE_ENABLE << GPIO_OE_SHIFT)
    str     r1, [r0]
    ldr     r0, =GPIO_CFG_ADDR(LED_GREEN_GPIO)
    str     r1, [r0]
.Lexc_loop:
    /* Red ON, green OFF */
    ldr     r0, =GPIO_IN_OUT_ADDR(LED_RED_GPIO)
    mov     r1, #GPIO_OUT_BIT
    str     r1, [r0]
    ldr     r0, =GPIO_IN_OUT_ADDR(LED_GREEN_GPIO)
    mov     r1, #0
    str     r1, [r0]
    ldr     r2, =MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL
    ldr     r5, =4915              /* 150ms at 32768 Hz */
    ldr     r3, [r2]
.Lexc_d1:
    ldr     r4, [r2]
    sub     r4, r4, r3
    cmp     r4, r5
    blo     .Lexc_d1
    /* Green ON, red OFF */
    ldr     r0, =GPIO_IN_OUT_ADDR(LED_GREEN_GPIO)
    mov     r1, #GPIO_OUT_BIT
    str     r1, [r0]
    ldr     r0, =GPIO_IN_OUT_ADDR(LED_RED_GPIO)
    mov     r1, #0
    str     r1, [r0]
    ldr     r3, [r2]
.Lexc_d2:
    ldr     r4, [r2]
    sub     r4, r4, r3
    cmp     r4, r5
    blo     .Lexc_d2
    b       .Lexc_loop
