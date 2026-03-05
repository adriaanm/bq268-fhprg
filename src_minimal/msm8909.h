/*
 * msm8909.h — MSM8909 platform constants for the minimal firehose programmer.
 *
 * Register addresses and bit definitions taken from the LK (Little Kernel)
 * bootloader source: lk_src/platform/msm8909/
 *
 * This header is usable from both C and assembly (via gcc -c preprocessing).
 */

#ifndef MSM8909_H
#define MSM8909_H

/*========================================================================
 * GCC (Global Clock Controller)
 *
 * Reference: lk_src/platform/msm8909/include/platform/iomap.h
 *========================================================================*/

#define CLK_CTL_BASE                0x01800000

/* GPLL0: 800 MHz general-purpose PLL */
#define GPLL0_MODE                  (CLK_CTL_BASE + 0x21000)
#define GPLL0_STATUS                (CLK_CTL_BASE + 0x21024)
#define APCS_GPLL_ENA_VOTE          (CLK_CTL_BASE + 0x45000)
#define APCS_CLOCK_BRANCH_ENA_VOTE  (CLK_CTL_BASE + 0x45004)

/* GPLL1: 614.4 MHz PLL */
#define GPLL1_STATUS                (CLK_CTL_BASE + 0x2001C)

/* SDCC1 clock registers */
#define SDCC1_BCR                   (CLK_CTL_BASE + 0x42000)
#define SDCC1_CMD_RCGR              (CLK_CTL_BASE + 0x42004)
#define SDCC1_CFG_RCGR              (CLK_CTL_BASE + 0x42008)
#define SDCC1_M                     (CLK_CTL_BASE + 0x4200C)
#define SDCC1_N                     (CLK_CTL_BASE + 0x42010)
#define SDCC1_D                     (CLK_CTL_BASE + 0x42014)
#define SDCC1_APPS_CBCR             (CLK_CTL_BASE + 0x42018)
#define SDCC1_AHB_CBCR              (CLK_CTL_BASE + 0x4201C)

/*------------------------------------------------------------------------
 * Clock bit definitions
 *
 * Reference: lk_src/platform/msm_shared/include/clock_lib2.h
 *------------------------------------------------------------------------*/

/* Branch clock control register (CBCR) */
#define CBCR_BRANCH_ENABLE_BIT      (1 << 0)
#define CBCR_BRANCH_OFF_BIT         (1 << 31)

/* Root clock generator command register (CMD_RCGR) */
#define CMD_UPDATE_BIT              (1 << 0)

/* Root clock generator config register (CFG_RCGR) */
#define CFG_SRC_DIV_MASK            0x1F        /* bits [4:0] */
#define CFG_SRC_SEL_SHIFT           8
#define CFG_SRC_SEL_MASK            (0x7 << 8)  /* bits [10:8] */
#define CFG_MODE_SHIFT              12
#define CFG_MODE_MASK               (0x3 << 12) /* bits [13:12] */
#define CFG_MODE_DUAL_EDGE          0x2

/* Clock source select values */
#define SRC_CXO                     0           /* 19.2 MHz crystal */
#define SRC_GPLL0                   1           /* 800 MHz PLL */

/* PLL status bits */
#define GPLL0_LOCK_BIT              (1 << 30)   /* GPLL0_MODE bit 30 */
#define GPLL1_LOCK_BIT              (1 << 17)   /* GPLL1_STATUS bit 17 */

/*========================================================================
 * GCC BIMC (DDR Memory Controller) clocks
 *
 * These registers must be configured before accessing the BIMC DDR
 * controller at 0x0044c000.  Derived from reverse-engineering the
 * original firehose programmer's FUN_0800ac84.
 *========================================================================*/

/* BIMC PLL (PLL1) — provides DDR controller clock */
#define GCC_BIMC_PLL_MODE              (CLK_CTL_BASE + 0x21000)  /* 0x01821000 — shares with GPLL0? */
#define GCC_BIMC_PLL_MODE_ALT          (CLK_CTL_BASE + 0x45000)  /* vote register */
#define BIMC_PLL_CONFIG_BASE           0x01821000
#define BIMC_PLL_L_VAL                 41         /* 0x29 */
#define BIMC_PLL_CONFIG_CTL            0x4001055b
#define BIMC_PLL_ALPHA_H               0xaa000000
#define BIMC_PLL_ALPHA_L               0x000000aa

/* PLL MODE register bits */
#define PLL_BYPASSNL                   (1 << 1)
#define PLL_RESET_N                    (1 << 2)
#define PLL_OUTCTRL                    (1 << 0)
#define PLL_LOCK_DET                   (1 << 31)

/* GCC BIMC clock branch registers (CBCR) */
#define GCC_BIMC_CBCR_0                (CLK_CTL_BASE + 0x31008)  /* 0x01831008 */
#define GCC_BIMC_CBCR_1                (CLK_CTL_BASE + 0x3100C)  /* 0x0183100c */
#define GCC_BIMC_CBCR_2                (CLK_CTL_BASE + 0x31010)  /* 0x01831010 */
#define GCC_BIMC_CBCR_3                (CLK_CTL_BASE + 0x31014)  /* 0x01831014 */
#define GCC_BIMC_CBCR_4                (CLK_CTL_BASE + 0x3101C)  /* 0x0183101c */
#define GCC_BIMC_CBCR_5                (CLK_CTL_BASE + 0x3201C)  /* 0x0183201c */
#define GCC_BIMC_CBCR_6                (CLK_CTL_BASE + 0x32020)  /* 0x01832020 */
#define GCC_BIMC_CBCR_7                (CLK_CTL_BASE + 0x32024)  /* 0x01832024 */

/* GCC BIMC RCG (Root Clock Generator) */
#define GCC_BIMC_DDR_CMD_RCGR          (CLK_CTL_BASE + 0x32004)  /* 0x01832004 */
#define GCC_BIMC_DDR_CFG_RCGR          (CLK_CTL_BASE + 0x32008)  /* 0x01832008 */
#define GCC_BIMC_MISC                  (CLK_CTL_BASE + 0x31018)  /* 0x01831018 */
#define GCC_BIMC_GFX_CMD_RCGR         (CLK_CTL_BASE + 0x37000)  /* 0x01837000 */
#define GCC_BIMC_GFX_CFG_RCGR         (CLK_CTL_BASE + 0x37004)  /* 0x01837004 */

/* GCC PLL USER_CTL registers */
#define GCC_GPLL0_USER_CTL             (CLK_CTL_BASE + 0x36004)  /* 0x01836004 */
#define GCC_BIMC_PLL_USER_CTL          (CLK_CTL_BASE + 0x45004)  /* 0x01845004 */

/* GCC reset registers (written to 0 during clock init) */
#define GCC_RESET_0                    (CLK_CTL_BASE + 0x00000)  /* 0x01800000 */
#define GCC_RESET_1                    (CLK_CTL_BASE + 0x13010)  /* 0x01813010 */
#define GCC_RESET_2                    (CLK_CTL_BASE + 0x1B000)  /* 0x0181b000 */
#define GCC_RESET_3                    (CLK_CTL_BASE + 0x70000)  /* 0x01870000 */
#define GCC_GPLL0_MODE_ALT             (CLK_CTL_BASE + 0x36000)  /* 0x01836000 */

/* TCSR register for chip version detection */
#define TCSR_SOC_VERSION               0x01821000

/* DDR blob function addresses */
#define DDR_SET_PARAMS_ADDR            0x00222780
#define DDR_INIT_ADDR                  0x002224cc

/* DDR config destination in IMEM */
#define DDR_CONFIG_IMEM_ADDR           0x08600190

/*========================================================================
 * SDCC1 (SD/eMMC Controller) data registers
 *
 * Reference: lk_src/platform/msm8909/include/platform/iomap.h
 *========================================================================*/

#define PERIPH_SS_BASE              0x07800000
#define MSM_SDC1_BASE               (PERIPH_SS_BASE + 0x00024000)
#define MSM_SDC1_SDHCI_BASE         (PERIPH_SS_BASE + 0x00024900)

/* SDHCI register offsets (from SDHCI base) */
#define SDCC_MCI_HC_MODE            0x00000078
#define SDCC_HC_PWRCTL_STATUS_REG   0x000000DC
#define SDCC_HC_PWRCTL_MASK_REG     0x000000E0
#define SDCC_HC_PWRCTL_CLEAR_REG    0x000000E4
#define SDCC_HC_PWRCTL_CTL_REG      0x000000E8

/*========================================================================
 * TLMM (Top-Level Mode Mux) — GPIO controller
 *
 * Reference: lk_src/platform/msm8909/include/platform/iomap.h
 *            lk_src/platform/msm8909/include/platform/gpio.h
 *            lk_src/platform/msm8909/gpio.c
 *========================================================================*/

#define TLMM_BASE                   0x01000000
#define GPIO_CFG_ADDR(n)            (TLMM_BASE + (n) * 0x1000)
#define GPIO_IN_OUT_ADDR(n)         (TLMM_BASE + (n) * 0x1000 + 0x4)

/* SDC1 TLMM pad control */
#define SDC1_HDRV_PULL_CTL          (TLMM_BASE + 0x10A000)

/*------------------------------------------------------------------------
 * GPIO_CFG register bit layout:
 *   [1:0]   pull      (GPIO_NO_PULL, GPIO_PULL_DOWN, GPIO_KEEPER, GPIO_PULL_UP)
 *   [5:2]   func      (0 = GPIO, 1..N = alternate functions)
 *   [8:6]   drive     (GPIO_2MA .. GPIO_16MA)
 *   [9]     enable    (0 = enabled, 1 = disabled — inverted!)
 *------------------------------------------------------------------------*/
#define GPIO_PULL_SHIFT             0
#define GPIO_FUNC_SHIFT             2
#define GPIO_DRV_SHIFT              6
#define GPIO_OE_SHIFT               9

/* Pull config */
#define GPIO_NO_PULL                0
#define GPIO_PULL_DOWN              1
#define GPIO_KEEPER                 2
#define GPIO_PULL_UP                3

/* Drive strength */
#define GPIO_2MA                    0
#define GPIO_4MA                    1
#define GPIO_6MA                    2
#define GPIO_8MA                    3
#define GPIO_10MA                   4
#define GPIO_12MA                   5
#define GPIO_14MA                   6
#define GPIO_16MA                   7

/* Output enable (bit 9) — NOTE: LK names are misleading!
 * Hardware: bit 9 = 1 enables output driver, 0 = high-Z (input).
 * LK defines GPIO_ENABLE=0, GPIO_DISABLE=1 but passes GPIO_DISABLE
 * for all output pins.  We use clear names instead. */
#define GPIO_OE_ENABLE              1   /* output driver on */
#define GPIO_OE_DISABLE             0   /* output driver off (input) */

/* GPIO_IN_OUT register bits */
#define GPIO_IN_BIT                 (1 << 0)
#define GPIO_OUT_BIT                (1 << 1)

/*========================================================================
 * Other platform registers
 *========================================================================*/

#define SYSTEM_IMEM_BASE            0x08600000
#define MSM_SHARED_IMEM_BASE        0x08600000
#define SDRAM_START_ADDR            0x80000000

/* PS_HOLD for reset/power-off */
#define MPM2_MPM_PS_HOLD            0x004AB000

/* Sleep timer (timetick) */
#define MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL  0x004A3000

/*========================================================================
 * BQ268 board-specific definitions
 *========================================================================*/

/* LEDs (active-high, GPIO function 0) */
#define LED_RED_GPIO                68
#define LED_GREEN_GPIO              69

#endif /* MSM8909_H */
