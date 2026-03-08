/* globals.h — Shared types, constants, and forward declarations for the
 * minimal programmer.
 *
 * Every function preserves a comment: orig: 0xADDRESS
 * for traceability back to the full decompilation in src/fhprg/.
 *
 * Functions in the eMMC driver layer (sdcc_regs, sdcc_helpers, card_init,
 * emmc) use ANSI prototypes with meaningful parameter names. Functions
 * outside that layer still use K&R-style empty parentheses ().
 */
#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "libc_glue.h"

/*========================================================================
 * Ghidra type compatibility (subset of src/ghidra_types.h)
 *========================================================================*/

typedef uint8_t  undefined1;
typedef uint8_t  byte;
typedef int8_t   sbyte;
typedef uint16_t ushort;
typedef uint32_t uint;
typedef uint32_t (code)();
typedef int64_t  longlong;

/* Ghidra CONCAT macros (only those actually used) */
#define CONCAT11(a,b)  ((uint16_t)(((uint16_t)(uint8_t)(a)  << 8)  | (uint8_t)(b)))
#define CONCAT12(a,b)  ((uint32_t)(((uint32_t)(uint8_t)(a)  << 16) | (uint16_t)(b)))


/*========================================================================
 * ARM intrinsics (stubs for analysis, not execution)
 *========================================================================*/

#ifdef EMU_BUILD
/* EMU_BUILD: no inline asm — runs under Unicorn, not real ARM */
static inline void DataMemoryBarrier(unsigned int opt) { (void)opt; }
static inline void DataSynchronizationBarrier(unsigned int opt) { (void)opt; }
static inline void InstructionSynchronizationBarrier(unsigned int opt) { (void)opt; }
#define coprocessor_movefromRt(...) ((unsigned int)0)
#define coprocessor_moveto(...) do { } while(0)
#else
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
#endif

/*========================================================================
 * Globals (extern, provided by globals.c)
 *========================================================================*/

/* --- SDCC/eMMC globals (defined in globals.c) --- */
extern int  sdcc_slot_status[2];    /* SDCC slot status table */
extern uint sdcc_device_table[2];  /* SDCC device handle table */
extern char sdcc_bases_inited;     /* SDCC bases initialized flag */
extern uint sdcc_mci_base[2];      /* SDCC MCI core register base [slot] */
extern uint sdcc_dma_base[2];      /* SDCC DMA/FIFO base table [slot] */
extern uint sdcc_hc_base[2];       /* SDCC SDHCI host-controller base [slot] */
extern uint sdcc_hc_base_alt[2];   /* SDCC SDHCI host-controller base (alt) [slot] */

/*========================================================================
 * MMIO register access macros
 *
 * Lvalue macros for SDCC register access. Each casts base+offset to a
 * volatile typed pointer, usable on both sides of assignment.
 *========================================================================*/
#define MCI_REG(slot, off)   (*(volatile uint32_t *)(sdcc_mci_base[slot] + (off)))
#define HC_REG32(slot, off)  (*(volatile uint32_t *)(sdcc_hc_base[slot] + (off)))
#define HC_REG16(slot, off)  (*(volatile uint16_t *)(sdcc_hc_base[slot] + (off)))
#define HC_REG8(slot, off)   (*(volatile uint8_t  *)(sdcc_hc_base[slot] + (off)))
#define DMA_REG(slot, off)   (*(volatile uint32_t *)(sdcc_dma_base[slot] + (off)))

/* MCI core register offsets (from sdcc_mci_base[slot]) */
#define MCI_POWER       0x00
#define MCI_CLK         0x04
#define MCI_ARGUMENT    0x08
#define MCI_CMD         0x0C
#define MCI_RESP_CMD    0x10
#define MCI_RESP_0      0x14   /* response word 0 (+ 0x18, 0x1C, 0x20 for words 1-3) */
#define MCI_DATA_TIMER  0x24
#define MCI_DATA_LENGTH 0x28
#define MCI_DATA_CTL    0x2C
#define MCI_STATUS      0x34
#define MCI_CLEAR       0x38
#define MCI_INT_MASK0   0x3C
#define MCI_FIFO_COUNT  0x44
#define MCI_VERSION     0x50
#define MCI_STATUS2     0x6C
#define MCI_HC_MODE     0x78
#define MCI_FIFO        0x80
#define MCI_PLL_STATUS  0xDC
#define MCI_PLL_DIVIDER 0xE4
#define MCI_PLL_MODE    0xE8

/* SDHCI HC register offsets (from sdcc_hc_base[slot]) */
#define HC_BLKSZ        0x04
#define HC_BLK_CNT      0x06
#define HC_ARGUMENT      0x08
#define HC_TRANS_MODE    0x0C
#define HC_CMD           0x0E
#define HC_RESP0         0x10   /* response words at +0x10, +0x14, +0x18, +0x1C */
#define HC_BUF_DATA      0x20
#define HC_PRESENT_STATE 0x24
#define HC_HOST_CTRL1    0x28
#define HC_PWR_CTRL      0x29
#define HC_CLK_CTRL      0x2C
#define HC_TIMEOUT       0x2E
#define HC_RESET         0x2F
#define HC_NRML_INT_STS  0x30
#define HC_NRML_INT_STS_EN 0x34
#define HC_NRML_INT_SIG_EN 0x38
#define HC_HOST_CTRL2    0x3E
#define HC_CAPS1         0x40
#define HC_CAPS2         0x44
#define HC_ADMA_ADDR_LO  0x58
#define HC_ADMA_ADDR_HI  0x5C
#define HC_DLL_CONFIG    0x100
#define HC_DLL_STATUS    0x108
#define HC_VENDOR_FUNC   0x10C
#define HC_VENDOR_CAPS0  0x11C
#define HC_VENDOR_CAPS1  0x120

/*========================================================================
 * eMMC driver types
 *========================================================================*/

/* mmc_dev_t — 0x94-byte device struct, embedded in slot context at +0x0C.
 *
 * Layout (byte offset → field name → content):
 *   +0x00  slot              SDCC slot number (0=eMMC, 1=SD)
 *   +0x04  cur_partition     cached current partition index (0-7)
 *   +0x08  card_type(byte)   +0x09=init_phase(byte) +0x0A=rca(short)
 *   +0x10  last_error        last error code from sdcc_write_data
 *   +0x15  init_state_dup    init state byte (checked in error recovery)
 *   +0x1C  user_sectors      total user-area sector count
 *   +0x20  card_id           card identifier
 *   +0x24  sector_size       sector size in bytes (typically 0x200)
 *   +0x2C  block_count       total block count
 *   +0x34  reliable_wr_cnt   reliable write sector count
 *   +0x3E  csd_spec_vers     CSD spec version (from CSD parse)
 *   +0x40  speed_mode        speed mode / CSD TAAC (low 16 bits)
 *   +0x42  mfr_id[7]         manufacturer ID (7 bytes, from CID)
 *   +0x49  product_rev       product revision byte
 *   +0x4C  gpp_attr[3]       GPP size attributes (3 words)
 *   +0x58  custom_sector     non-zero = use sector_size for byte count
 *   +0x5C  speed_class       CSD speed class byte
 *   +0x5D  bus_width_sup     EXT_CSD bus-width capability
 *   +0x5F  speed_grade       2=HS26, 3=HS52, 4=DDR
 *   +0x60  phys_part_count   number of physical partitions (byte)
 *   +0x61  part_switch       partition switch support flag (byte)
 *   +0x64  boot_part_size    boot partition size (EXT_CSD[226-227])
 *   +0x68  gp_sectors[4]     GP1-GP4 sector counts
 *   +0x78  partition_cfg     cached PARTITION_CONFIG (EXT_CSD[179]) (byte)
 *   +0x7C  partition_mask    bitmask of existing partitions (uint32_t)
 *   +0x84  clock_khz         current clock frequency in kHz
 *   +0x8C  spi_mode          SPI mode flag (byte, checked in mmc_classify_error)
 *   +0x90  hotplug_desc      pointer to hotplug/ADMA context struct
 */
typedef struct {
    uint     slot;              /* +0x00 [0]:  SDCC slot number (0 or 1) */
    uint     cur_partition;     /* +0x04 [1]:  cached current partition index */
    uint8_t  card_type;         /* +0x08:      card type (0=none 1=SD 2=MMC 5=SDHC 6=eMMC) */
    uint8_t  init_phase;        /* +0x09:      0=unready, 2=active */
    uint16_t rca;               /* +0x0A:      Relative Card Address */
    uint     _pad0C;            /* +0x0C [3]:  unused/unknown */
    uint     last_error;        /* +0x10 [4]:  last error code from sdcc_write_data */
    uint8_t  _pad14;            /* +0x14:      unused */
    uint8_t  init_state_dup;    /* +0x15:      init state byte (error recovery) */
    uint8_t  _pad16[2];         /* +0x16:      unused */
    uint     _pad18;            /* +0x18 [6]:  unused */
    uint     user_sectors;      /* +0x1C [7]:  total user-area sector count */
    uint     card_id;           /* +0x20 [8]:  card identifier */
    uint     sector_size;       /* +0x24 [9]:  sector size in bytes (typically 0x200) */
    uint     _pad28;            /* +0x28 [0xA]: unused */
    uint     block_count;       /* +0x2C [0xB]: total block count */
    uint     _pad30;            /* +0x30 [0xC]: unused */
    uint     reliable_wr_cnt;   /* +0x34 [0xD]: reliable write sector count */
    uint     _pad38;            /* +0x38 [0xE]: unused */
    uint16_t _pad3C;            /* +0x3C:      unused */
    uint16_t csd_spec_vers;     /* +0x3E:      CSD spec version */
    uint16_t speed_mode;        /* +0x40 [0x10]: speed mode / CSD TAAC (low 16 bits) */
    uint8_t  mfr_id[7];        /* +0x42:      manufacturer ID (7 bytes) */
    uint8_t  product_rev;       /* +0x49:      product revision byte */
    uint16_t _pad4A;            /* +0x4A:      unused */
    uint     gpp_attr[3];       /* +0x4C [0x13..0x15]: GPP size attributes */
    uint     custom_sector;     /* +0x58 [0x16]: non-zero = use sector_size for byte count */
    uint8_t  speed_class;       /* +0x5C:      CSD speed class byte */
    uint8_t  bus_width_sup;     /* +0x5D:      EXT_CSD bus-width capability */
    uint8_t  _pad5E;            /* +0x5E:      unused */
    uint8_t  speed_grade;       /* +0x5F:      speed grade (2=HS26, 3=HS52, 4=DDR) */
    uint8_t  phys_part_count;   /* +0x60 [0x18]: number of physical partitions */
    uint8_t  part_switch;       /* +0x61:      partition switch support flag */
    uint8_t  _pad62[2];         /* +0x62:      unused */
    uint     boot_part_size;    /* +0x64 [0x19]: boot partition size (EXT_CSD[226-227]) */
    uint     gp_sectors[4];     /* +0x68 [0x1A..0x1D]: GP1-GP4 sector counts */
    uint8_t  partition_cfg;     /* +0x78:      cached PARTITION_CONFIG (EXT_CSD[179]) */
    uint8_t  _pad79[3];        /* +0x79:      unused */
    uint     partition_mask;    /* +0x7C [0x1F]: bitmask of existing partitions */
    uint     _pad80;            /* +0x80 [0x20]: unused */
    uint     clock_khz;         /* +0x84 [0x21]: current clock frequency in kHz */
    uint     _pad88;            /* +0x88 [0x22]: unused */
    uint8_t  spi_mode;          /* +0x8C [0x23]: SPI mode flag byte */
    uint8_t  _pad8D[3];        /* +0x8D:      unused */
    uint     hotplug_desc;      /* +0x90 [0x24]: ptr to hotplug/ADMA context struct */
} mmc_dev_t;
_Static_assert(sizeof(mmc_dev_t) == 0x94, "mmc_dev_t must be 0x94 bytes");

/* Partition handle — 3-word (12-byte) struct from partition_table[].
 * Previously: typedef uint mmc_handle_t with [0]=dev_ptr, [1]=partition, [2]=flags. */
typedef struct {
    uint dev_ptr;         /* pointer to mmc_dev_t (stored as uint) */
    uint partition_idx;   /* partition index (0-7, -1=user) */
    uint flags;           /* open flags */
} mmc_handle_t;

/* eMMC command struct (40 bytes, 10 words).
 * Passed to sdcc_send_cmd and related functions. */
typedef struct {
    int cmd_num;        /* [0] MMC command number (CMD0=0, CMD17=0x11, CMD24=0x18...) */
    int cmd_arg;        /* [1] command argument (sector addr, RCA<<16, CMD6 arg...) */
    int resp_type;      /* [2] response type byte (0=none, 1=R1/R1B, 4=R2) */
    int resp[4];        /* [3..6] response data (R1: resp[0]=status, R2: all 4 words) */
    int busy_wait;      /* [7] 1=wait for DAT0 busy signal to clear */
    int status;         /* [8] MCI_STATUS on return (filled by sdcc_setup_data_xfer) */
    int flags;          /* [9] bit0=write/stop, bit1=data xfer, bit2=ADMA */
} mmc_cmd_t;

/* SDCC command config struct (20 bytes, 10 shorts).
 * Built by sdcc_pre_cmd_hook, consumed by sdcc_cleanup to form MCI_CMD register. */
typedef struct {
    short dpe;          /* [0] data-path enable → MCI_CMD bit 12 (CMD17/18/24/25/53) */
    short ccs_enable;   /* [1] CCS/busy signal → MCI_CMD bit 11 */
    short data_present; /* [2] data present → MCI_CMD bit 10 */
    short _reserved3;   /* [3] unused */
    short idx_check;    /* [4] index check → MCI_CMD bit 7 */
    short crc_check;    /* [5] CRC check → MCI_CMD bit 6 */
    short cmd_index;    /* [6] command index → MCI_CMD bits [5:0] */
    short _reserved7;   /* [7] unused */
    int   cmd_arg;      /* [8..9] command argument (32-bit, overlaid at byte offset 16) */
} sdcc_cmd_config_t;

/*========================================================================
 * Forward declarations — organized by file / subsystem
 *========================================================================*/

/* ---- sdcc_regs.c ---- */
void     sdcc_set_transfer_mode(int slot, ushort *mode);
void     sdcc_cleanup(int slot, sdcc_cmd_config_t *cmd_config);
void     sdcc_set_all_irq(int slot);
uint     sdcc_read_status(int slot);        /* MCI_STATUS (MCI+0x34) */
void     sdcc_enable_clock(int slot);       /* poll MCI_STATUS2 bit 0 */
uint     sdcc_read_present(int slot);       /* NRML_INT_STS_REG (HC+0x30) */
uint     sdcc_read_present_state(int slot); /* PRESENT_STATE_REG (HC+0x24) */
void     sdcc_read_response(int slot, uint *resp, int is_r2);
void     sdcc_clear_status(int slot, uint mask);
void     sdcc_set_block_count(int slot, uint16_t count);
void     sdcc_set_block_size(int slot, uint16_t size);
void     sdcc_set_cmd_arg(int slot, uint arg);
void     sdcc_fire_cmd(int slot, byte *cmd_desc);
void     sdcc_set_irq_mask(int slot, uint8_t mask); /* TIMEOUT_REG (HC+0x2E) */
void     sdcc_set_transfer_ctrl(int slot, byte *ctrl);
void     sdcc_reset_data_line(int slot, byte bits); /* RESET_REG (HC+0x2F) */
void     sdcc_set_clock_divider(int slot, uint divider);
void     sdcc_set_adma_addr_lo(int slot, uint addr);
void     sdcc_set_adma_addr_hi(int slot, uint addr);
void     sdcc_set_8bit_mode(int slot, int enable);
void     sdcc_trigger_vendor_reset(int slot);
void     sdcc_set_clock_mode(int slot);
void     sdcc_set_hs_mode(int slot, char enable);
void     sdcc_read_caps(int slot, uint *caps);
uint8_t  sdcc_read_power_mode(int slot);
void     sdcc_wait_pll_lock(int slot);
void     sdcc_set_int_enable(int slot, uint mask, int enable);  /* NRML_INT_SIG_EN_REG (HC+0x38) */
void     sdcc_set_int_signal(int slot, uint mask, int enable);  /* NRML_INT_STS_EN_REG (HC+0x34) */
uint     sdcc_read_clock_stable(int slot);
void     sdcc_set_led(int slot, int enable);
void     sdcc_set_dma_mode(int slot, int mode);
void     sdcc_setup_caps(int slot);
void     sdcc_set_bus_power(int slot, uint8_t enable);
void     sdcc_set_voltage(int slot, uint8_t voltage);
void     sdcc_set_bus_width_bit(int slot, int enable);
void     sdcc_init_bases(void);
void     sdcc_set_flow_control(int slot, int enable);
void     sdcc_set_bus_speed(int slot, int speed);

/* ---- sdcc_helpers.c ---- */
void adma_bounce_read(int slot, uint *buf, int *remaining);
void adma_bounce_write(int slot, uint *buf, int *remaining);
void sdcc_event_notify(int flags, uint addr, uint size);
uint sdcc_post_write_cleanup(mmc_dev_t *dev, int need_busy, int need_stop);
int  sdcc_fifo_write(mmc_dev_t *dev, mmc_cmd_t *cmd, uint *buf, uint byte_count);
uint sdcc_dma_setup(int slot, uint buf_phys, uint byte_count);
uint sdcc_wait_complete(int slot, uint mask, uint *out_status);
int  mmc_switch_cmd6(mmc_dev_t *dev, uint cmd6_arg);
uint sdcc_setup_data_xfer(mmc_dev_t *dev, mmc_cmd_t *cmd);
uint sdcc_adma_transfer(uint *hotplug, uint *buf, int byte_count);
uint sdcc_adma_write(mmc_dev_t *dev, mmc_cmd_t *cmd);
void sdcc_pre_cmd_hook(mmc_dev_t *dev, mmc_cmd_t *cmd);
int  sdcc_pre_write_setup(mmc_dev_t *dev, int is_reliable, int num_blocks);
uint sdcc_post_write_check(mmc_dev_t *dev);
uint sdcc_busy_wait(mmc_dev_t *dev);
uint sdcc_pio_transfer(uint *hotplug, byte *buf, int byte_count);
uint sdcc_get_card_status(mmc_dev_t *dev);

/* ---- card_init.c ---- */
void sdcc_pre_init_slot(int slot);
void sdcc_clock_setup(int slot, uint *freq, int mode);
void mmc_set_bus_width(mmc_dev_t *dev, uint speed_mode, uint unused1, uint freq_hint);
int  mmc_set_speed(mmc_dev_t *dev);
int  mmc_get_slot_context(uint slot);
void mmc_finalize_init(mmc_dev_t *dev);
void mmc_release_slot(mmc_handle_t **handle_ptr);
char mmc_classify_error(mmc_handle_t *handle);
int  mmc_identify_card(mmc_dev_t *dev);
int  mmc_config_bus(mmc_dev_t *dev);
uint mmc_init_card(int slot);
mmc_handle_t *mmc_alloc_handle(short slot, int partition_idx);
uint mmc_setup_partitions(mmc_dev_t *dev);


/* mmc_handle_t field layout now encoded in the struct definition above.
 * Old HANDLE_DEV_PTR/PARTITION_IDX/FLAGS defines removed. */

/* mmc_cmd_t field layout is documented in the struct definition above.
 * Old #define CMD_NUM/CMD_ARG/etc. indices replaced by struct fields. */

/* Slot context layout (0xBC bytes per slot).
 * Contains header fields + embedded device struct at +0x0C.
 *   +0x00  slot_num         slot number
 *   +0x04  hw_enabled(byte) 1 when SDCC hardware is enabled
 *   +0x0C  dev[...]         embedded mmc_dev_t (0x94 bytes)
 *   +0x15  init_state(byte) = dev.init_phase: 0=uninit, 1=identified, 2=ready
 *   +0x94  adma_mode        ADMA mode from sdcc_get_adma_mode (0x20)
 *   +0x98  init_flag(byte)  flag set during mmc_init_card
 *   +0x9C  self_ptr         self-reference pointer back to slot_context base
 *   +0xB4  caps[2]          SDHCI capabilities (CAPS_REG1, CAPS_REG2) */
#define SLOT_CTX_INIT_STATE    0x15  /* byte offset: init state (1=identified) */
#define SLOT_CTX_SELF_PTR      0x27  /* word index: self-reference pointer */

/* ---- emmc.c ---- */
uint sdcc_get_device(uint slot);
uint sdcc_get_slot_status(uint slot);
int  sdcc_send_cmd(mmc_dev_t *dev, mmc_cmd_t *cmd);
void sdcc_write_complete_notify(void);
int  sdcc_write_data(mmc_dev_t *dev, mmc_cmd_t *cmd, uint buf, uint num_blocks);
uint mmc_get_card_type(uint slot, undefined1 *type_out, undefined1 *subtype_out);
uint mmc_close_handle(mmc_handle_t *handle);
int  mmc_erase_range(mmc_handle_t *handle, int sector, int count);
uint mmc_get_partition_info(mmc_handle_t *handle, char *info);
int  mmc_open_device(int slot, uint flags);
int  mmc_read_blocks(mmc_handle_t *handle, int sector, uint buf, int num_blocks);
int  mmc_switch_partition(mmc_handle_t *handle);
int  mmc_write_sectors(mmc_handle_t *handle, int sector, uint buf, int num_blocks);
uint mmc_get_capacity(mmc_handle_t *handle, uint *sectors, uint *part_type);
uint mmc_is_partition_active(mmc_handle_t *handle);
int  mmc_ensure_partition(mmc_handle_t *handle);
/* ---- libc_impl.c ---- */
void delay_us();
void qtimer_init();             /* stub */

/* end of firehose.h */
