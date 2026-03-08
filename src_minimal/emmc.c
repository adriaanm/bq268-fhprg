/* emmc.c — eMMC/SDCC driver layer.
 *
 * This is the critical layer for understanding writes. The write path is:
 *   handle_program -> storage_write_sectors -> mmc_write_sectors ->
 *   sdcc_write_data -> sdcc_send_cmd
 *
 * SDCC = Secure Digital Card Controller (Qualcomm's SD/eMMC controller IP).
 * Commands follow the eMMC JEDEC spec (CMD0, CMD6, CMD24, CMD25, etc.).
 *
 * Source: src/fhprg/fhprg_80327f8.c
 */
#include "globals.h"

/*========================================================================
 * SDCC controller interface
 *
 * These functions talk directly to the SDCC controller's memory-mapped
 * registers. They are NOT in our minimal closure — they live at 0x0800xxxx
 * and are declared as externs in globals.h.
 *
 * Key register-level functions:
 *   sdcc_read_status(slot)          — read controller status register
 *   sdcc_clear_status(slot, ...)    — clear status/interrupt bits
 *   sdcc_set_irq_mask(slot, mask)   — configure interrupt mask
 *   sdcc_set_cmd_arg(slot, arg)     — write command argument register
 *   sdcc_fire_cmd(slot, &cmd)       — write command register and fire
 *   sdcc_wait_complete(slot, type, &status) — poll for completion
 *   sdcc_read_response(slot, resp, is_r2)  — read response register
 *   sdcc_read_present(slot)         — read present state register
 *========================================================================*/

/* orig: 0x08032ae4 sdcc_get_device — get device handle from slot table.
 * The SDCC slot table at sdcc_device_table holds pointers to device structs
 * for up to 2 slots. Only slot 0 (eMMC) is used. */
uint sdcc_get_device(uint slot)
{
  if (slot < 2)
    return sdcc_device_table[slot];
  return 0;
}

/* orig: 0x08032af8 sdcc_get_slot_status — get slot status flags.
 * The slot status table at sdcc_slot_status holds per-slot status.
 * bit 0: card present, bit 1: initialized, etc. */
uint sdcc_get_slot_status(uint slot)
{
  if (slot < 2)
    return (uint)sdcc_slot_status[slot];
  return 0;
}

/* orig: 0x08032b94 sdcc_send_cmd — send an eMMC command via SDCC controller.
 *
 * This is the lowest-level command interface. ALL eMMC operations go through
 * here: reads, writes, erases, CMD6 SWITCH, etc.
 *
 * dev = device struct:
 *   [0]    = SDCC slot number (0 or 1)
 *   [0x24] = pointer to EXT_CSD data (512 bytes)
 *
 * cmd = mmc_cmd_t struct (40 bytes):
 *   cmd_num   = command number (CMD0=0, CMD6=6, CMD24=0x18, CMD25=0x19, etc.)
 *   cmd_arg   = command argument
 *   resp_type = response type (0=none, 1=R1/R1B, 4=R2)
 *   resp[4]   = response data (filled on return)
 *   busy_wait = busy wait flag (1=wait for busy signal to clear)
 *   status    = status (filled on return)
 *   flags     = flags (bit 0-1: ADMA/DMA mode)
 *
 * Returns: 0=success, 0x14=invalid params, 3=timeout, 6=CMD0 timeout,
 *          7=busy timeout, 0xb=R1 error bits set
 */
int sdcc_send_cmd(mmc_dev_t *dev, mmc_cmd_t *cmd)
{
  int ret;
  uint status;
  uint iter;
  uint resp_words;
  /* 20-byte cleanup state for sdcc_cleanup. */
  sdcc_cmd_config_t cleanup_cfg;

  if (dev == NULL || cmd == NULL)
    return 0x14;

  /* eMMC path (card[0x23] != 1, not SPI mode) */
  ret = 0;
  sdcc_pre_cmd_hook(dev, cmd);
  if (cmd->cmd_num == 0) {
    /* CMD0 (GO_IDLE_STATE): poll until card responds */
    int slot = dev->slot;
    iter = 0;
    while ((status = iter + 1, iter < 800 &&
            (iter = sdcc_read_status(slot), (iter & 0x80) == 0)))
    {
      delay_us(10);
      iter = status;
    }
    if (status < 800) {
      MCI_REG(slot, MCI_CLEAR) = 0x80;
      while (status < 800) {
        uint reg = sdcc_read_status(slot);
        if ((reg & 0x80) == 0)
          return 0;
        delay_us(10);
        status = status + 1;
      }
    }
    ret = 6; /* CMD0 timeout */
  }
  else {
    /* Non-CMD0: set up data transfer if needed */
    if ((char)cmd->resp_type != '\0') {
      int xfer_ret = sdcc_setup_data_xfer(dev, cmd);
      if (xfer_ret != 0)
        return xfer_ret;
      /* Read response from controller */
      if ((char)cmd->resp_type != '\0') {
        if ((char)cmd->resp_type == '\x04')
          resp_words = 4; /* R2: 4 words */
        else
          resp_words = 1; /* R1/R1B: 1 word */
        for (iter = 0; iter < resp_words; iter = iter + 1)
          cmd->resp[iter] = MCI_REG(dev->slot, MCI_RESP_0 + iter * 4);
        /* Check R1 error bits for CMD52 (0x34) and CMD53 (0x35) */
        if ((cmd->cmd_num == 0x34 || cmd->cmd_num == 0x35) && (cmd->resp[0] & 0xcf00U) != 0)
          ret = 0xb; /* R1 error */
      }
    }
    /* Wait for busy if requested */
    if (cmd->busy_wait != 0 && ret == 0)
      ret = sdcc_busy_wait(dev);
    memset_zero(&cleanup_cfg, sizeof(cleanup_cfg));
    sdcc_cleanup(dev->slot, &cleanup_cfg);
  }
  return ret;
}

/* orig: 0x08033654 sdcc_write_complete_notify — write completion thunk.
 * Empty in original binary. Called after partition info fill. */
void sdcc_write_complete_notify(void)
{
}

/* orig: 0x08033656 sdcc_write_data — eMMC block data transfer (write).
 *
 * Handles the actual data transfer for writes. Two paths:
 *   - ADMA mode: DMA engine reads from memory, writes to eMMC
 *   - PIO mode: CPU writes data word-by-word through FIFO register
 *
 * dev = device struct
 * cmd = command struct (CMD24/CMD25 already built)
 * buf = data buffer address
 * num_blocks = block count
 *
 * This function does NOT check write protection — that's done by
 * mmc_write_sectors() before calling this.
 */
int sdcc_write_data(mmc_dev_t *dev, mmc_cmd_t *cmd, uint buf, uint num_blocks)
{
  int setup_ret;
  int cmd_ret;
  uint need_stop;
  uint adma_mode;
  int hotplug = dev->hotplug_desc; /* hotplug/ADMA context */
  int result = 0;
  int adma_err = 0;
  /* Transfer mode struct: 8 bytes, passed as ushort* to sdcc_set_transfer_mode.
   * Layout (matching Ghidra's local_40/local_3c contiguous pair):
   *   byte 0-1 (short[0]): block count (low 16 bits of num_blocks)
   *   byte 2   (char):     DMA enable (1 if ADMA supported)
   *   byte 3   (char):     auto CMD (unused, 0)
   *   byte 4-5 (short[2]): direction + flags (0x100=write, 0x101=multi-block write)
   *   byte 6-7:            block count enable */
  uint xfer_mode[2];
  uint cmd_flags = cmd->flags;
  uint reliable_write = (int)(cmd_flags << 0x1e) >> 0x1f; /* bit 1 of flags */

  /* eMMC path (card[0x23] != 1, not SPI mode) */
  {
    /* Pre-write DMA/buffer setup */
    setup_ret = sdcc_pre_write_setup(dev, reliable_write + 1, num_blocks);
    if (setup_ret == 0) {
      dev->last_error = 0x14;
      return 0x14;
    }
    /* Custom sector mode: replace block count with sector size.
     * sdcc_set_transfer_mode encodes this into MCI_DATA_CTL bits [7:4].
     * In standard mode (dev[0x16]=0), num_blocks stays as the count. */
    if (dev->custom_sector != 0)
      num_blocks = dev->sector_size;
    xfer_mode[0] = num_blocks & 0xffff;  /* block count in low 16 bits */
    xfer_mode[1] = 0x100; /* transfer mode: write */
    /* Check if ADMA is supported (EXT_CSD+0xA4 != 0) */
    if (*(int *)(hotplug + 0xa4) != 0) {
      /* Set DMA enable flag (byte 2) and keep block count (bytes 0-1) */
      xfer_mode[0] = (uint)CONCAT12(1,(short)num_blocks) & 0x00ffffff;
    }
    /* Reliable write: set multi-block flag */
    if ((int)(cmd_flags << 0x1e) < 0) {
      xfer_mode[1] = 0x101; /* multi-block write */
      sdcc_set_transfer_mode(dev->slot, (ushort *)xfer_mode);
    }
    /* Send the command (CMD17/CMD18 for read, CMD24/CMD25 for write) */
    if ((int)(cmd_flags << 0x1d) < 0)
      cmd_ret = sdcc_adma_write(dev, cmd);
    else
      cmd_ret = sdcc_send_cmd(dev, cmd);
    /* Check R1 address out of range bit */
    if (((uint)cmd->resp[0] >> 0x1a & 1) != 0) {
      dev->last_error = 0x1d; /* address out of range */
      return 0x1d;
    }
    if (cmd_ret == 0) {
      /* ADMA data transfer path */
      if (*(int *)(hotplug + 0xa4) != 0) {
        adma_mode = ((int)(cmd_flags << 0x1e) < 0) ? 1 : 2;
        /* Call ADMA engine via function pointer at EXT_CSD+0xAC */
        adma_err = (**(code **)(hotplug + 0xac))(hotplug, buf, setup_ret, adma_mode);
        if (adma_err == 0) {
          if ((cmd_flags & 1) != 0)
            sdcc_set_transfer_mode(dev->slot, (ushort *)xfer_mode);
          result = sdcc_post_write_check(dev);
        }
        if (*(int *)(hotplug + 0xa4) != 0 && adma_err == 0)
          goto LAB_0803376e;
      }
      /* PIO/SDMA transfer path.
       *
       * setup_ret = return from sdcc_pre_write_setup:
       *   - dev[0x16]=0 (standard): setup_ret = num_blocks (block count)
       *   - dev[0x16]=1 (custom):   setup_ret = sector_size * num_blocks (byte count)
       *
       * sdcc_adma_transfer/sdcc_pio_transfer expect a byte count.
       * When ADMA is enabled (+0xA4 != 0), the ADMA function pointer
       * path handles block->byte conversion internally. When ADMA is
       * disabled (our case), we must convert here.
       */
      {
        int xfer_bytes = (dev->custom_sector != 0) ? setup_ret
                         : setup_ret * (int)dev->sector_size;
        if ((int)(cmd_flags << 0x1e) < 0) {
          result = sdcc_adma_transfer((uint *)hotplug, (uint *)buf, xfer_bytes);
        }
        else {
          /* Clear DMA enable flag, keep block count */
          xfer_mode[0] = (uint)(ushort)xfer_mode[0];
          sdcc_set_transfer_mode(dev->slot, (ushort *)xfer_mode);
          result = sdcc_pio_transfer((uint *)hotplug, (byte *)buf, xfer_bytes);
        }
      }
      xfer_mode[0] = 0;
      xfer_mode[1] = 0;
      sdcc_set_transfer_mode(dev->slot, (ushort *)xfer_mode);
    }
LAB_0803376e:
    /* Post-write: send stop command if needed (CMD12 for multi-block) */
    if ((int)(cmd_flags << 0x1d) < 0 || (cmd->cmd_num != 0x12 && cmd->cmd_num != 0x19))
      need_stop = 0;
    else
      need_stop = 1; /* need CMD12 STOP */
    int cleanup_ret = sdcc_post_write_cleanup(dev, reliable_write + 1, need_stop);
    /* ADMA completion callback */
    if (*(int *)(hotplug + 0xa4) != 0 && adma_err == 0) {
      adma_mode = ((int)(cmd_flags << 0x1e) < 0) ? 1 : 2;
      result = (**(code **)(hotplug + 0xb0))(hotplug, adma_mode); /* ADMA done callback */
    }
    if (result == 0)
      result = cleanup_ret;
    dev->last_error = result; /* store result in device struct */
    return result;
  }

  /* SPI mode path removed — eMMC only */
  return 0x14;
}

/* orig: 0x08033cbc mmc_get_card_type — always MMC for eMMC-only build */
uint mmc_get_card_type(uint slot, uint8_t *type_out, uint8_t *subtype_out)
{
  *type_out = 0; /* MMC */
  *subtype_out = 0; /* MMC */
  return 0;
}

/* orig: 0x08033d28 mmc_close_handle — close a device handle.
 * Deinitializes and releases the SDCC slot. */
uint mmc_close_handle(mmc_handle_t *handle)
{
  mmc_handle_t *local_10;

  if (handle != NULL && handle->dev_ptr != 0) {
    local_10 = handle;
    mmc_release_slot(&local_10);
    return 0;
  }
  return 0x14;
}

/* orig: 0x08033d44 mmc_erase_range — erase a range of sectors.
 *
 * Uses the eMMC erase sequence:
 *   CMD35 (ERASE_GROUP_START) -> start sector
 *   CMD36 (ERASE_GROUP_END)   -> end sector
 *   CMD38 (ERASE)             -> execute
 *
 * handle = device handle (ptr to ptr to device struct)
 * sector = start sector
 * count = sector count
 */
int mmc_erase_range(mmc_handle_t *handle, int sector, int count)
{
  int ret;
  mmc_dev_t *dev;
  mmc_cmd_t cmd; /* command struct (reused for CMD35/36/38) */

  if (handle == NULL || (dev = (mmc_dev_t *)handle->dev_ptr, dev == NULL) ||
     2 < dev->slot)
    return 0x14;

  if (dev->card_type != 6 && dev->card_type != 2)
    return 0x16; /* wrong card type */

  /* Card must be MMC or eMMC (type 2 or 6) */
  ret = mmc_ensure_partition(handle);
  if (ret != 0)
    return ret;

  /* CMD35: ERASE_GROUP_START */
  memset_zero(&cmd, sizeof(cmd));
  cmd.cmd_num = 0x23;                          /* CMD35 */
  cmd.cmd_arg = sector;                        /* start address */
  /* NOTE: for non-HC (type 2) cards, CMD35 arg should be byte address
   * (sector * 0x200), but this path is never taken on msm8909 where the
   * device is always type 6 (eMMC/HC). Faithfully reproduced from original
   * FUN_08033d44 which also passes sector unconverted for CMD35. */
  *(uint8_t *)&cmd.resp_type = 1;              /* resp_type: R1 */
  ret = sdcc_send_cmd(dev, &cmd);
  if (ret != 0)
    return ret;

  /* CMD36: ERASE_GROUP_END */
  if (dev->card_type == 6)
    cmd.cmd_arg = sector + count + -1;       /* HC: sector-addressed */
  else
    /* non-HC: byte-addressed end = sector + (count-1)*512.
     * Inconsistent with CMD35 which should also use byte address. */
    cmd.cmd_arg = sector + count * 0x200 + -0x200;
  cmd.cmd_num = 0x24;                        /* CMD36 */
  ret = sdcc_send_cmd(dev, &cmd);
  if (ret != 0)
    return ret;

  /* CMD38: ERASE */
  memset_zero(&cmd, sizeof(cmd));
  cmd.cmd_num = 0x26;                      /* CMD38 */
  *(uint8_t *)&cmd.resp_type = 1;          /* resp_type: R1 */
  cmd.busy_wait = 1;
  ret = sdcc_send_cmd(dev, &cmd);
  if (ret == 0) {
    if ((cmd.resp[0] & 0xfdff8000) == 0)
      return 0; /* success */
    return 0xf; /* erase error — R1 error bits set */
  }
  if (ret != 7)
    return ret;
  /* Busy timeout -- keep waiting */
  if ((cmd.resp[0] & 0xfdff8000) == 0) {
    do {
      ret = sdcc_busy_wait(dev);
    } while (ret == 7);
    return ret;
  }
  return 0xf; /* erase error */
}

/* orig: 0x08033ee8 mmc_get_partition_info — fill partition info struct.
 *
 * Fills a 0x40-byte struct with partition details from the device struct.
 * Layout:
 *   +0x00: card type (byte: 0=none, 1=SD, 2=MMC, 5=SDHC, 6=eMMC)
 *   +0x04: total sectors
 *   +0x08: card identifier
 *   +0x0C: sector size (from dev[9])
 *   +0x10: num physical partitions (byte)
 *   +0x14: block count
 *   +0x18: card present flag
 *   +0x1C: reliable write sector count (dev[0xD])
 *   +0x20: partition type code
 *   +0x24: is_active partition flag
 *   +0x26: speed class (2 bytes)
 *   +0x28: speed mode (short)
 *   +0x2A: manufacturer ID (7 bytes, from dev+0x42)
 *   +0x31: product revision (from dev+0x49)
 *   +0x34-0x3C: GPP sizes
 */
uint mmc_get_partition_info(mmc_handle_t *handle, char *info)
{
    mmc_dev_t *dev;
    uint slot_status;
    uint capacity_ret = 0;
    uint total_sectors = 0;
    uint part_type = 0;

    if (handle == NULL || (dev = (mmc_dev_t *)handle->dev_ptr, dev == NULL) ||
        2 < dev->slot || info == NULL)
        return 0x14;

    memset_zero(info, 0x40); /* memset(info, 0, 64) */
    *info = (char)dev->card_type; /* card type */
    *(uint *)(info + 0xc) = dev->sector_size; /* sector size */
    slot_status = sdcc_get_slot_status(((mmc_dev_t *)handle->dev_ptr)->slot);
    if ((slot_status & 1) == 0)
        info[0x18] = 0;  /* card not present */
    else
        info[0x18] = 1;  /* card present */
    /* eMMC only: get capacity from partition table */
    capacity_ret = mmc_get_capacity(handle, &total_sectors, &part_type);
    *(uint *)(info + 4) = total_sectors; /* total sectors */
    info[0x10] = (char)dev->phys_part_count; /* num physical partitions (DEV+0x60) */
    *(uint *)(info + 0x14) = dev->block_count; /* block count */
    {
        char is_active = mmc_is_partition_active(handle);
        info[0x24] = is_active;
    }
    *(uint *)(info + 8) = dev->card_id; /* card identifier */
    *(uint *)(info + 0x20) = part_type; /* partition type */
    *(uint *)(info + 0x1c) = dev->reliable_wr_cnt; /* reliable write count */
    *(uint16_t *)(info + 0x26) = dev->csd_spec_vers; /* speed class */
    *(short *)(info + 0x28) = (short)dev->speed_mode; /* speed mode */
    memcpy(info + 0x2a, dev->mfr_id, 7); /* manufacturer ID */
    info[0x31] = (char)dev->product_rev; /* product revision */
    *(uint *)(info + 0x34) = dev->gpp_attr[0]; /* GPP1 size */
    *(uint *)(info + 0x38) = dev->gpp_attr[1]; /* GPP2 size */
    *(uint *)(info + 0x3c) = dev->gpp_attr[2]; /* GPP3 size */
    sdcc_write_complete_notify();
    return capacity_ret;
}

/* orig: 0x08034170 mmc_read_blocks — read sectors via CMD17/CMD18.
 *
 * Builds the MMC command struct and calls sdcc_write_data() to perform
 * the transfer. Despite the "write" naming in the data path, this
 * function uses CMD17 (READ_SINGLE) / CMD18 (READ_MULTIPLE).
 *
 * handle = device handle (ptr to ptr to device struct)
 * sector = start sector
 * buf = data buffer (must be DMA-accessible, i.e. DDR)
 * num_blocks = block count (1=CMD17 single, >1=CMD18 multi)
 */
int mmc_read_blocks(mmc_handle_t *handle, int sector, uint buf, int num_blocks)
{
  int ret;
  mmc_dev_t *dev;
  mmc_cmd_t cmd;

  if (handle == NULL || (dev = (mmc_dev_t *)handle->dev_ptr, dev == NULL) ||
     2 < dev->slot)
    return 0x14;

  /* >>> WP CHECK REMOVED — allow writes regardless of EXT_CSD[160] <<< */
  if (1) {
    int card_type = (char)dev->card_type;
    if (card_type == 0)
      return 0x15; /* no card */

    if (card_type == 1 || card_type == 5 || card_type == 2 || card_type == 6) {
      /* Card is SD/SDHC/MMC/eMMC — proceed with read */
      ret = mmc_ensure_partition(handle);
      if (ret != 0)
        return ret;
      memset_zero(&cmd, sizeof(cmd));
      /* Build command struct */
      if (num_blocks == 1)
        cmd.cmd_num = 0x11; /* CMD17: READ_SINGLE_BLOCK */
      else
        cmd.cmd_num = 0x12; /* CMD18: READ_MULTIPLE_BLOCK */
      *(uint8_t *)&cmd.resp_type = 1; /* resp_type: R1 */
      cmd.busy_wait = 0;              /* reserved */
      cmd.cmd_arg = sector;
      /* Convert sector number to byte address for non-HC cards */
      if (dev->card_type != 5 && dev->card_type != 6)
        cmd.cmd_arg = sector * dev->sector_size;
      cmd.flags = 2;                  /* flags: bit 1 = data transfer */
      ret = sdcc_write_data(dev, &cmd, buf, num_blocks);
    }
    else {
      ret = 0x10; /* unsupported card type */
    }
  }
  else {
    ret = 0x1b; /* WRITE PROTECTED — EXT_CSD[160] != 0 */
  }
  return ret;
}

/* orig: 0x08034202 mmc_switch_partition — select eMMC hardware partition via CMD6.
 *
 * Uses CMD6 (SWITCH) to write PARTITION_CONFIG (EXT_CSD[179]) to select
 * the active partition for subsequent read/write commands.
 *
 * eMMC partitions: 0=user, 1=boot1, 2=boot2, 4-7=GP1-GP4
 *
 * handle = device handle (ptr to ptr to device struct)
 *   handle[0] = ptr to device struct
 *   handle[1] = requested partition (-1 or 0..7)
 */
int mmc_switch_partition(mmc_handle_t *handle)
{
  int ret;
  mmc_dev_t *dev;
  uint part_idx;

  if (handle == NULL || (dev = (mmc_dev_t *)handle->dev_ptr, dev == NULL) ||
     2 < dev->slot)
    return 0x14;

  /* Must be MMC (type 2) or eMMC (type 6) */
  if (dev->card_type != 2 && dev->card_type != 6)
    return 0x16;

  part_idx = handle->partition_idx; /* requested partition */
  if (part_idx == 0xffffffff)
    part_idx = 0; /* default to user partition */

  /* Validate partition index against max partitions */
  if (dev->reliable_wr_cnt <= part_idx)
    return 0x14;

  /* Check if already on the right partition */
  ret = mmc_is_partition_active(handle);
  if (ret == 1) {
    ret = 0; /* already active, nothing to do */
  }
  else {
    /* Restore current partition field first if needed */
    if (dev->cur_partition != 0 &&
       (ret = mmc_switch_cmd6(dev, (uint)dev->partition_cfg << 0xb | 0x3b30000), ret != 0)) {
      /* CMD6 SWITCH: Access=3 (write), Index=0xB3 (PARTITION_CONFIG),
       * Value=current partition << 3, Cmd_set=0 */
      return ret;
    }
    /* Switch to requested partition */
    if (part_idx == 0)
      part_idx = 7; /* user partition = config value 7 */
    /* CMD6 arg: 0x03B30000 | (dev[4] | partition_idx << 3) << 8
     * This writes PARTITION_CONFIG in EXT_CSD[179]:
     *   bits[2:0] = PARTITION_ACCESS (which partition to access)
     *   bits[5:3] = BOOT_PARTITION_ENABLE
     *   bit[6]    = BOOT_ACK */
    ret = mmc_switch_cmd6(dev, (dev->cur_partition | part_idx << 3) << 8 | 0x3b30000);
    if (ret == 0) {
      dev->partition_cfg = (uint8_t)part_idx; /* update cached partition */
      return 0;
    }
  }
  return ret;
}

/* orig: 0x08034228 mmc_write_sectors — THE write protection gate.
 *
 * This is the function that checks EXT_CSD[160] to decide whether to
 * allow writes. If the WP byte is non-zero, returns 0x1b (write protected).
 *
 * The write path goes:
 *   1. Validate device struct
 *   2. CHECK: *(char*)(dev[0x24] + 0xA0) — if nonzero, return 0x1b
 *   3. Check card type
 *   4. Call mmc_ensure_partition(handle) — switch to correct HW partition
 *   5. Build command struct (CMD24 single or CMD25 multi block)
 *   6. Call sdcc_write_data() for actual transfer
 *
 * EXT_CSD[160] = SEC_TRIM_MULT / WR_REL_SET area. The firmware uses this
 * byte as a general "write permitted" flag.
 */
int mmc_write_sectors(mmc_handle_t *handle, int sector, uint buf, int num_blocks)
{
    mmc_dev_t *dev;
    int card_type;
    int ret;
    mmc_cmd_t cmd;

    if (handle == NULL || (dev = (mmc_dev_t *)handle->dev_ptr, dev == NULL) ||
        2 < dev->slot)
        return 0x14;

    /* >>> WP CHECK REMOVED — allow writes regardless of EXT_CSD[160] <<< */
    card_type = (char)dev->card_type;
    if (card_type == 0)
        return 0x15;

    if (card_type == 1 || card_type == 5 || card_type == 2 || card_type == 6) {
        ret = mmc_ensure_partition(handle);
        if (ret != 0)
            return ret;
        memset_zero(&cmd, sizeof(cmd));
        /* Build command struct */
        if (num_blocks == 1)
            cmd.cmd_num = 0x18;     /* CMD24: WRITE_SINGLE_BLOCK */
        else
            cmd.cmd_num = 0x19;     /* CMD25: WRITE_MULTIPLE_BLOCK */
        *(uint8_t *)&cmd.resp_type = 1; /* resp_type: R1 */
        cmd.busy_wait = 0;               /* reserved */
        cmd.cmd_arg = sector;
        /* Convert to byte address for non-HC cards */
        if (dev->card_type != 5 && dev->card_type != 6)
            cmd.cmd_arg = sector * dev->sector_size;
        cmd.flags = 1;                   /* flags: bit 0 = write direction */
        ret = sdcc_write_data(dev, &cmd, buf, num_blocks);
    } else {
        ret = 0x10;
    }
    return ret;
}

/* orig: 0x080348e0 mmc_get_capacity — get partition capacity in sectors.
 *
 * Reads the capacity from the device struct's partition table.
 * For user partition (0): uses dev[0x1C] (total sectors from CSD).
 * For boot/GP partitions: calculates from EXT_CSD fields.
 *
 * *sectors = sector count (output)
 * *part_type = partition type code (output)
 */
uint mmc_get_capacity(mmc_handle_t *handle, uint *sectors, uint *part_type)
{
  mmc_dev_t *dev = (mmc_dev_t *)handle->dev_ptr;
  uint part_idx = handle->partition_idx;
  uint type;

  if (part_idx == 0xffffffff)
    part_idx = 0;

  /* Non-user partitions require partition switching support */
  if (part_idx != 0 && dev->part_switch == 0)
    return 0x16;

  /* Check partition exists (bitmask at dev->partition_mask) */
  if ((1 << (part_idx & 0xff) & dev->partition_mask) == 0)
    return 0x14;

  if (part_idx == 0) {
    *sectors = dev->user_sectors; /* user area: total sectors from CSD */
    type = 0;
  }
  else if (part_idx == 1) {
    /* Boot partition 1: EXT_CSD[226-227] * 128KB / 512 */
    *sectors = (uint)((int)dev->boot_part_size << 10) >> 9;
    *part_type = 1;
    return 0;
  }
  else if (part_idx == 2) {
    /* Boot partition 2: same size as boot1 */
    *sectors = (uint)((int)dev->boot_part_size << 10) >> 9;
    type = 2;
  }
  else if (part_idx == 4) {
    *sectors = dev->gp_sectors[0]; /* GP1 */
    type = 4;
  }
  else if (part_idx == 5) {
    *sectors = dev->gp_sectors[1]; /* GP2 */
    type = 5;
  }
  else if (part_idx == 6) {
    *sectors = dev->gp_sectors[2]; /* GP3 */
    type = 6;
  }
  else if (part_idx == 7) {
    *sectors = dev->gp_sectors[3]; /* GP4 */
    type = 7;
  }
  else {
    return 0x14;
  }
  *part_type = type;
  return 0;
}

/* orig: 0x08034966 mmc_is_partition_active — check if requested partition
 * is already the currently selected one.
 *
 * Compares handle[1] (requested partition) against the cached current
 * partition at dev+0x78. Returns 1 if already active, 0 otherwise. */
uint mmc_is_partition_active(mmc_handle_t *handle)
{
  int requested = handle->partition_idx;
  if (requested == -1)
    requested = 0;

  int cur_cfg = (char)((mmc_dev_t *)handle->dev_ptr)->partition_cfg;
  if (cur_cfg == 1) {
    if (requested == 1)
      return 1; /* boot1 already active */
  }
  else if (cur_cfg == 2) {
    if (requested == 2)
      return 1; /* boot2 already active */
  }
  else if (cur_cfg == 7 && requested == 0) {
    return 1; /* user partition already active (config val 7) */
  }
  return 0;
}

/* orig: 0x08034fb0 mmc_ensure_partition — ensure correct partition is selected.
 *
 * If the device's current partition doesn't match the requested one,
 * sends CMD6 SWITCH to change PARTITION_CONFIG (EXT_CSD[179]).
 *
 * This is called before every read/write/erase operation to make sure
 * we're talking to the right partition.
 */
int mmc_ensure_partition(mmc_handle_t *handle)
{
  int ret;
  mmc_dev_t *dev;
  uint part_idx;

  if (handle == NULL)
    return 0x14;

  {
    int requested = handle->partition_idx;
    if (requested == -1)
      requested = 0;
    /* Already on the right partition? */
    if ((int)((mmc_dev_t *)handle->dev_ptr)->cur_partition == requested)
      return 0;
  }
  /* Must be MMC/eMMC for partition switching */
  int card_type = (char)((mmc_dev_t *)handle->dev_ptr)->card_type;
  if (card_type != 2 && card_type != 6)
    return 0x16;

  dev = (mmc_dev_t *)handle->dev_ptr;
  part_idx = handle->partition_idx;
  if (part_idx == 0xffffffff)
    part_idx = 0;
  if (part_idx != 0 && dev->part_switch == 0)
    return 0x16; /* device doesn't support partition switching */
  if ((1 << (part_idx & 0xff) & dev->partition_mask) == 0)
    return 0x14; /* partition doesn't exist */
  /* CMD6 SWITCH: write PARTITION_CONFIG
   * Arg format: 0x03B30000 | (boot_config | partition_access) << 8
   * boot_config = dev->partition_cfg current config, shifted left 3 bits
   * partition_access = requested partition index */
  ret = mmc_switch_cmd6(dev, (part_idx | (uint)dev->partition_cfg << 3) << 8 | 0x3b30000);
  if (ret == 0)
    dev->cur_partition = part_idx; /* cache new partition */
  return ret;
}

/* orig: 0x08033fe0 mmc_open_device — initialize and open an eMMC device.
 *
 * Called during handle_configure to set up the storage device.
 * Complex initialization: card detect, CSD/CID read, EXT_CSD read,
 * bus width configuration, speed setup, partition enumeration.
 *
 * slot = slot number (0 or 1)
 * flags = open flags
 *
 * Many sub-functions are outside our closure (card init, CSD parsing,
 * bus width negotiation, etc.). The key insight: after this function
 * succeeds, the device struct is fully populated and subsequent
 * read/write commands can proceed.
 */
int mmc_open_device(int slot, uint flags)
{
  char init_state;
  int slot_ctx;
  int err;
  mmc_dev_t *pDev;
  int handle = 0;

  if (slot >= 3)
    return 0;

  slot_ctx = mmc_init_card(slot);
  if (slot_ctx == 0)
    return 0;

  slot_ctx = mmc_get_slot_context(slot);
  if (slot_ctx == 0)
    return 0;

  pDev = (mmc_dev_t *)(slot_ctx + 0xc);
  handle = (int)mmc_alloc_handle(slot, flags);
  if (handle == 0) {
    err = mmc_setup_partitions(pDev);
    if (err != 0)
      return handle;
    mmc_finalize_init(pDev);
    return handle;
  }
  /* Error handling: classify and potentially recover */
  init_state = *(char *)(slot_ctx + 0x14);
  if (init_state == '\x04')
    goto LAB_08034086;
  if (init_state == '\x01' || init_state == '\x05' ||
      init_state == '\x02' || init_state == '\x06')
    return handle;

  init_state = mmc_classify_error((mmc_handle_t *)handle);
  *(char *)(slot_ctx + 0x14) = init_state;
  *(char *)(slot_ctx + 0x24) = init_state;
  if (init_state == '\0') {
    goto LAB_080340c6;
  }
  if (init_state == '\x04')
    goto LAB_08034086;

  err = mmc_config_bus(pDev);
  if (err == 0) {
    if (*(char *)(slot_ctx + 0x98) == '\0') {
      MCI_REG(slot, MCI_CLK) =
           MCI_REG(slot, MCI_CLK) | 0x1000;
      sdcc_enable_clock(slot);
    }
    err = mmc_identify_card(pDev);
    if (err == 0) {
      mmc_set_bus_width(pDev, 1, 0, 0);
      err = mmc_set_speed(pDev);
      if (err == 0) {
        *(uint8_t *)(slot_ctx + SLOT_CTX_INIT_STATE) = 2;
        *(uint8_t *)(slot_ctx + 0xa0) = 0;
        return handle;
      }
      *(int *)(slot_ctx + 0x1c) = err;
      *(uint8_t *)(slot_ctx + 0x14) = 0;
      goto LAB_080340c6;
    }
  }
  *(int *)(slot_ctx + 0x1c) = err;
LAB_080340c6:
  mmc_close_handle((mmc_handle_t *)handle);
  return 0;

LAB_08034086:
  mmc_release_slot((mmc_handle_t **)&handle);
  return handle;
}

/* str_find_replace (0x0803725c) — REMOVED, only used by handle_patch */
