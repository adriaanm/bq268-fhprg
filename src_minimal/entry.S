/*
 * entry.S — Minimal startup for MSM8909 firehose programmer.
 *
 * After PBL loads us via Sahara into OCIMEM (0x08006000), we:
 *   1. Set VBAR (exception vector base)
 *   2. Set up stack pointer
 *   3. Zero BSS
 *   4. Enable GPLL0 and XO clocks
 *   5. Copy DDR driver to IMEM (0x00220000) and call it
 *   6. Map DDR via simple MPU/cache setup
 *   7. Enable GCC SDCC1 clocks (AHB + APPS)
 *   8. Branch to C main()
 *
 * Register addresses from MSM8909 GCC (Global Clock Controller):
 *   GCC base = 0x01800000
 *   GPLL0_MODE          = 0x01821000
 *   GCC_SDCC1_APPS_CBCR = 0x01842004
 *   GCC_SDCC1_AHB_CBCR  = 0x01842008
 *   GCC_SDCC1_APPS_CMD_RCGR = 0x01842000
 *
 * QTimer base = 0x004a0000
 *   CNTFRQ via CP15
 */

    .syntax unified
    .thumb
    .arch armv7-a

    .section .text.entry, "ax", %progbits
    .balign 4
    .global _start
    .thumb_func
_start:
    /*--------------------------------------------------------------
     * 1. Exception vectors — point VBAR at a minimal vector table
     *    (we don't handle exceptions, just set it for safety)
     *--------------------------------------------------------------*/
    ldr     r0, =_vectors
    mcr     p15, 0, r0, c12, c0, 0     /* VBAR = _vectors */
    isb

    /*--------------------------------------------------------------
     * 2. Stack — use top of OCIMEM BSS region
     *--------------------------------------------------------------*/
    ldr     sp, =_stack_top

    /*--------------------------------------------------------------
     * 3. Copy .data from CODE (LMA) to DATA (VMA)
     *--------------------------------------------------------------*/
    ldr     r0, =_data_start    /* dest: DATA VMA */
    ldr     r1, =_data_load     /* src: CODE LMA */
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

    /*--------------------------------------------------------------
     * 4. Clock init — enable GPLL0 (800 MHz reference PLL)
     *
     * The PBL may have already enabled this, but ensure it.
     * GPLL0_MODE: bit 0 = PLL enable, bit 2 = output enable
     * Poll bit 31 (LOCK_DET) for PLL lock.
     *--------------------------------------------------------------*/
    ldr     r0, =0x01821000     /* GPLL0_MODE */
    ldr     r1, [r0]
    orr     r1, r1, #0x7       /* enable + LVMAIN + LVAUX */
    str     r1, [r0]
    dsb
.Lgpll0_wait:
    ldr     r1, [r0]
    tst     r1, #(1 << 31)     /* LOCK_DET */
    beq     .Lgpll0_wait

    /*--------------------------------------------------------------
     * 5. Init DDR
     *
     * The DDR driver blob is loaded directly to IMEM (0x00220000)
     * by Sahara/PBL via ELF program headers — no copy needed.
     *
     * Call DDR init entry point:
     * FUN_00222780(ddr_config_base=0x8600190, config_size)
     * The DDR driver is ARM mode code. We use BLX to switch.
     *--------------------------------------------------------------*/
    ldr     r0, =0x08600190     /* DDR config base (HWIO region) */
    movs    r1, #0              /* config size — filled by DDR driver */
    ldr     r3, =0x00222780     /* DDR init entry (ARM mode) */
    blx     r3

    /*--------------------------------------------------------------
     * 6. DDR region cache/MMU setup
     *
     * Configure MPU region for DDR at 0x80000000.
     * Use CP15 to set up a basic cacheable region.
     *--------------------------------------------------------------*/
    /* For simplicity, we rely on the DDR driver having set up
     * basic memory access. The eMMC DMA engine accesses DDR
     * directly via physical addresses. */

    /*--------------------------------------------------------------
     * 7. Enable GCC SDCC1 clocks
     *
     * SDCC1 needs AHB clock and APPS clock enabled.
     * The clock source (CXO or GPLL0) should already be running.
     *--------------------------------------------------------------*/

    /* Enable SDCC1 AHB clock */
    ldr     r0, =0x01842008     /* GCC_SDCC1_AHB_CBCR */
    ldr     r1, [r0]
    orr     r1, r1, #1          /* CLK_ENABLE */
    str     r1, [r0]
    dsb
.Lahb_wait:
    ldr     r1, [r0]
    tst     r1, r1              /* N flag = bit 31 (CLK_OFF) */
    bmi     .Lahb_wait          /* wait until CLK_OFF=0 */

    /* Enable SDCC1 APPS clock */
    ldr     r0, =0x01842004     /* GCC_SDCC1_APPS_CBCR */
    ldr     r1, [r0]
    orr     r1, r1, #1          /* CLK_ENABLE */
    str     r1, [r0]
    dsb
.Lapps_wait:
    ldr     r1, [r0]
    tst     r1, r1              /* N flag = bit 31 (CLK_OFF) */
    bmi     .Lapps_wait

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
