/* firehose.h — Shared types, constants, and forward declarations for the
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
 * Forward declarations — organized by file / subsystem
 *
 * All use K&R-style empty parentheses (). In gnu89, () = unspecified args.
 *========================================================================*/

/* ---- sdcc_regs.c ---- */
void     sdcc_set_transfer_mode(int slot, ushort *mode);
void     sdcc_cleanup(int slot, short *cmd_config);
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
void adma_bounce_read(int slot, int buf, int *remaining);
void adma_bounce_write(int slot, int buf, int *remaining);
void sdcc_event_notify(int flags, int addr, uint size);
uint sdcc_post_write_cleanup(int *dev, int need_busy, int need_stop);
int  sdcc_fifo_write(int *dev, int cmd_config, uint *buf, uint byte_count);
uint sdcc_dma_setup(int slot, int buf, uint byte_count);
uint sdcc_wait_complete(int slot, uint mask, uint *out_status);
int  mmc_switch_cmd6(int *dev, uint cmd6_arg);
uint sdcc_setup_data_xfer(int *dev, int *cmd);
uint sdcc_adma_transfer(int *dev, uint *buf, int byte_count);
uint sdcc_adma_write(int *dev, uint *cmd);
void sdcc_pre_cmd_hook(int *dev, int *cmd);
int  sdcc_pre_write_setup(uint *dev, int is_reliable, int num_blocks);
uint sdcc_post_write_check(uint *dev);
uint sdcc_busy_wait(int *dev);
uint sdcc_pio_transfer(int *dev, byte *buf, int byte_count);
uint sdcc_get_card_status(int *dev);

/* ---- card_init.c ---- */
void sdcc_pre_init_slot(int slot);
void sdcc_clock_setup(int slot, uint *freq, int mode);
void mmc_set_bus_width(uint *dev, uint speed_mode, uint unused1, uint freq_hint);
int  mmc_set_speed(int *dev);
int  mmc_get_slot_context(uint slot);
void mmc_finalize_init(int dev);
void mmc_release_slot(uint *handle);
char mmc_classify_error(int *handle);
int  mmc_identify_card(int dev);
int  mmc_config_bus(int dev);
uint mmc_init_card(int slot);
int *mmc_alloc_handle(short slot, int flags);
uint mmc_setup_partitions(int dev);


/*========================================================================
 * eMMC driver types and struct field indices
 *========================================================================*/
typedef uint  mmc_dev_t;     /* word-indexed device struct (use as mmc_dev_t*) */
typedef uint  mmc_handle_t;  /* word-indexed partition handle (use as mmc_handle_t*) */
typedef int   mmc_cmd_t;     /* word-indexed command struct (use as mmc_cmd_t[10]) */

/* mmc_dev_t field indices (word offsets unless noted).
 * Device struct is 0x94 bytes, embedded in slot context at +0x0C.
 *
 * Layout (word index → byte offset → content):
 *   [0]    +0x00  slot            SDCC slot number (0=eMMC, 1=SD)
 *   [1]    +0x04  cur_partition   cached current partition index (0-7)
 *   [2]    +0x08  card_type(byte) +0x09=init_phase(byte) +0x0A=rca(short)
 *   [4]    +0x10  last_error      last error code from sdcc_write_data
 *   [7]    +0x1C  user_sectors    total user-area sector count
 *   [8]    +0x20  card_id         card identifier
 *   [9]    +0x24  sector_size     sector size in bytes (typically 0x200)
 *   [0xB]  +0x2C  block_count     total block count
 *   [0xD]  +0x34  reliable_wr_cnt reliable write sector count
 *   [0x10] +0x40  speed_mode      speed mode (low 16 bits)
 *   [0x16] +0x58  custom_sector   non-zero = use dev[9] for byte count
 *   [0x18] +0x60  phys_part_count (byte) number of physical partitions
 *   [0x21] +0x84  clock_khz       current clock frequency in kHz
 *   [0x24] +0x90  hotplug_desc    pointer to hotplug/ADMA context struct
 * Byte-offset fields (not word-aligned):
 *   +0x09  init_phase     0=unready, 2=active (set by mmc_set_speed)
 *   +0x0A  rca            Relative Card Address (uint16_t)
 *   +0x5D  bus_width_sup  EXT_CSD bus-width capability (<4=SDR, >=4=DDR)
 *   +0x5F  speed_grade    2=HS26(26MHz), 3=HS52(52MHz), 4=DDR
 *   +0x61  part_switch    non-zero = device supports partition switching
 *   +0x78  partition_cfg  cached PARTITION_CONFIG (EXT_CSD[179])
 *   +0x7C  partition_mask bitmask of existing partitions (uint32_t)
 */
#define DEV_SLOT               0      /* +0x00: SDCC slot number (0 or 1) */
#define DEV_CUR_PARTITION      1      /* +0x04: cached current partition index */
#define DEV_CARD_TYPE          2      /* +0x08: card type byte (0=none 1=SD 2=MMC 5=SDHC 6=eMMC) */
#define DEV_LAST_ERROR         4      /* +0x10: last error code from sdcc_write_data */
#define DEV_USER_SECTORS       7      /* +0x1C: total user-area sectors (CSD/EXT_CSD) */
#define DEV_CARD_ID            8      /* +0x20: card identifier */
#define DEV_SECTOR_SIZE        9      /* +0x24: sector size in bytes (typically 0x200) */
#define DEV_BLOCK_COUNT        0x0B   /* +0x2C: total block count */
#define DEV_RELIABLE_WR_CNT    0x0D   /* +0x34: reliable write sector count */
#define DEV_SPEED_MODE         0x10   /* +0x40: speed mode (low 16 bits used as short) */
#define DEV_CUSTOM_SECTOR      0x16   /* +0x58: non-zero = use dev[9] for byte count */
#define DEV_CLOCK_KHZ          0x21   /* +0x84: current clock frequency in kHz */
#define DEV_HOTPLUG_DESC       0x24   /* +0x90: ptr to hotplug/ADMA context struct */

/* mmc_dev_t byte offsets (accessed via *(char*)(dev + offset) or *(uint*)(dev + offset)) */
#define DEV_BYTE_CARD_TYPE     0x08   /* byte: card type (same as low byte of dev[2]) */
#define DEV_BYTE_INIT_PHASE    0x09   /* byte: init phase (0=unready, 2=active) */
#define DEV_HALF_RCA           0x0A   /* uint16_t: Relative Card Address */
#define DEV_BYTE_BUS_WIDTH     0x5D   /* byte: bus-width support from EXT_CSD */
#define DEV_BYTE_SPEED_GRADE   0x5F   /* byte: speed grade (2=HS26, 3=HS52, 4=DDR) */
#define DEV_BYTE_PART_SWITCH   0x61   /* byte: partition switch support flag */
#define DEV_BYTE_PART_CONFIG   0x78   /* byte: cached PARTITION_CONFIG (EXT_CSD[179]) */
#define DEV_WORD_PART_MASK     0x7C   /* uint32_t: bitmask of existing partitions */

/* mmc_handle_t field indices (word offsets).
 * Handle is a 3-word (12-byte) struct from partition table (partition_table[]).
 *   [0] = pointer to mmc_dev_t
 *   [1] = partition index (0-7, -1=user)
 *   [2] = open flags */
#define HANDLE_DEV_PTR         0     /* pointer to mmc_dev_t (device struct) */
#define HANDLE_PARTITION_IDX   1     /* partition index (0-7, -1=user) */
#define HANDLE_FLAGS           2     /* open flags */

/* mmc_cmd_t field indices (word offsets).
 * Command struct is 10 words (40 bytes):
 *   [0] cmd_num     MMC command number (CMD0=0, CMD17=0x11, CMD24=0x18...)
 *   [1] cmd_arg     command argument (sector addr, RCA<<16, CMD6 arg...)
 *   [2] resp_type   response type byte (0=none, 1=R1/R1B, 4=R2)
 *   [3..6] resp     response data (R1: [3]=status, R2: [3..6]=128-bit)
 *   [7] busy_wait   1=wait for DAT0 busy signal to clear
 *   [8] status      MCI_STATUS on return (filled by sdcc_setup_data_xfer)
 *   [9] flags       bit0=write/stop, bit1=data xfer, bit2=ADMA */
#define CMD_NUM                0
#define CMD_ARG                1
#define CMD_RESP_TYPE          2
#define CMD_RESP_DATA          3     /* 4 words: [3]-[6] */
#define CMD_BUSY_WAIT          7
#define CMD_STATUS             8
#define CMD_FLAGS              9

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
