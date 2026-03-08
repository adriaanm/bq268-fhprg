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
  uint uVar1;

  uVar1 = 0;
  if (slot < 2) {
    uVar1 = sdcc_device_table[slot];
  }
  return uVar1;
}

/* orig: 0x08032af8 sdcc_get_slot_status — get slot status flags.
 * The slot status table at sdcc_slot_status holds per-slot status.
 * bit 0: card present, bit 1: initialized, etc. */
uint sdcc_get_slot_status(uint slot)
{
    uint uVar1 = 0;
    if (slot < 2) {
        uVar1 = (uint)sdcc_slot_status[slot];
    }
    return uVar1;
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
  int iVar3;
  uint uVar4;
  int iVar7;
  uint uVar8;
  /* 20-byte cleanup state for sdcc_cleanup. */
  sdcc_cmd_config_t local_28;

  if ((dev == (mmc_dev_t *)0x0) || (cmd == (mmc_cmd_t *)0x0)) {
    return 0x14;
  }
  /* eMMC path (card[0x23] != 1, not SPI mode) */
  iVar7 = 0;
  sdcc_pre_cmd_hook(dev, cmd);
  if (cmd->cmd_num == 0) {
    /* CMD0 (GO_IDLE_STATE): poll until card responds */
    iVar7 = *dev; /* slot number */
    uVar8 = 0;
    while ((uVar4 = uVar8 + 1, uVar8 < 800 &&
            (uVar8 = sdcc_read_status(iVar7), (uVar8 & 0x80) == 0)))
    {
      delay_us(10); /* delay 10us */
      uVar8 = uVar4;
    }
    if (uVar4 < 800) {
      MCI_REG(iVar7, MCI_CLEAR) = 0x80;
      while (uVar4 < 800) {
        uVar8 = sdcc_read_status(iVar7);
        if ((uVar8 & 0x80) == 0) {
          return 0;
        }
        delay_us(10);
        uVar4 = uVar4 + 1;
      }
    }
    iVar7 = 6; /* CMD0 timeout */
  }
  else {
    /* Non-CMD0: set up data transfer if needed */
    if ((char)cmd->resp_type != '\0') {
      iVar3 = sdcc_setup_data_xfer(dev,cmd);
      if (iVar3 != 0) {
        return iVar3;
      }
      /* Read response from controller */
      if ((char)cmd->resp_type != '\0') {
        if ((char)cmd->resp_type == '\x04') {
          uVar8 = 4; /* R2: 4 words */
        }
        else {
          uVar8 = 1; /* R1/R1B: 1 word */
        }
        for (uVar4 = 0; uVar4 < uVar8; uVar4 = uVar4 + 1) {
          cmd->resp[uVar4] = MCI_REG(*dev, MCI_RESP_0 + uVar4 * 4);
        }
        /* Check R1 error bits for CMD52 (0x34) and CMD53 (0x35) */
        if ((cmd->cmd_num == 0x34 || cmd->cmd_num == 0x35) && (cmd->resp[0] & 0xcf00U) != 0) {
          iVar7 = 0xb; /* R1 error */
        }
      }
    }
    /* Wait for busy if requested */
    if ((cmd->busy_wait != 0) && (iVar7 == 0)) {
      iVar7 = sdcc_busy_wait(dev);
    }
    memset_zero(&local_28, sizeof(local_28));
    sdcc_cleanup(*dev, &local_28);
  }
  return iVar7;
}

/* orig: 0x08033654 sdcc_write_complete_notify — write completion thunk.
 * Empty in original binary. Called after partition info fill. */
void sdcc_write_complete_notify(void)
{
  return;
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
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar8;
  /* Transfer mode struct: 8 bytes, passed as ushort* to sdcc_set_transfer_mode.
   * Layout (matching Ghidra's local_40/local_3c contiguous pair):
   *   byte 0-1 (short[0]): block count (low 16 bits of num_blocks)
   *   byte 2   (char):     DMA enable (1 if ADMA supported)
   *   byte 3   (char):     auto CMD (unused, 0)
   *   byte 4-5 (short[2]): direction + flags (0x100=write, 0x101=multi-block write)
   *   byte 6-7:            block count enable */
  uint xfer_mode[2];
  uint local_38;

  /* eMMC path (card[0x23] != 1, not SPI mode) */
  {
    uVar4 = cmd->flags;
    iVar5 = dev[DEV_HOTPLUG_DESC]; /* hotplug/ADMA context */
    iVar8 = 0;
    local_38 = (int)(uVar4 << 0x1e) >> 0x1f; /* bit 1 of flags: reliable write */
    iVar6 = 0;

    /* Pre-write DMA/buffer setup */
    iVar1 = sdcc_pre_write_setup(dev,local_38 + 1,num_blocks);
    if (iVar1 == 0) {
      dev[DEV_LAST_ERROR] = 0x14;
      return 0x14;
    }
    /* Custom sector mode: replace block count with sector size.
     * sdcc_set_transfer_mode encodes this into MCI_DATA_CTL bits [7:4].
     * In standard mode (dev[0x16]=0), num_blocks stays as the count. */
    if (dev[DEV_CUSTOM_SECTOR] != 0) {
      num_blocks = dev[DEV_SECTOR_SIZE];
    }
    xfer_mode[0] = num_blocks & 0xffff;  /* block count in low 16 bits */
    xfer_mode[1] = 0x100; /* transfer mode: write */
    /* Check if ADMA is supported (EXT_CSD+0xA4 != 0) */
    if (*(int *)(iVar5 + 0xa4) != 0) {
      /* Set DMA enable flag (byte 2) and keep block count (bytes 0-1) */
      xfer_mode[0] = (uint)CONCAT12(1,(short)num_blocks) & 0x00ffffff;
    }
    /* Reliable write: set multi-block flag */
    if ((int)(uVar4 << 0x1e) < 0) {
      xfer_mode[1] = 0x101; /* multi-block write */
      sdcc_set_transfer_mode(*dev,(ushort *)xfer_mode);
    }
    /* Send the command (CMD17/CMD18 for read, CMD24/CMD25 for write) */
    if ((int)(uVar4 << 0x1d) < 0) {
      iVar2 = sdcc_adma_write(dev, cmd);
    }
    else {
      iVar2 = sdcc_send_cmd(dev, cmd);
    }
    /* Check R1 address out of range bit */
    if (((uint)cmd->resp[0] >> 0x1a & 1) != 0) {
      dev[DEV_LAST_ERROR] = 0x1d; /* address out of range */
      return 0x1d;
    }
    if (iVar2 == 0) {
      /* ADMA data transfer path */
      if (*(int *)(iVar5 + 0xa4) != 0) {
        if ((int)(uVar4 << 0x1e) < 0) {
          uVar3 = 1;
        }
        else {
          uVar3 = 2;
        }
        /* Call ADMA engine via function pointer at EXT_CSD+0xAC */
        iVar6 = (**(code **)(iVar5 + 0xac))(iVar5,buf,iVar1,uVar3);
        if (iVar6 == 0) {
          if ((uVar4 & 1) != 0) {
            sdcc_set_transfer_mode(*dev,(ushort *)xfer_mode);
          }
          iVar8 = sdcc_post_write_check(dev);
        }
        if ((*(int *)(iVar5 + 0xa4) != 0) && (iVar6 == 0)) goto LAB_0803376e;
      }
      /* PIO/SDMA transfer path.
       *
       * iVar1 = return from sdcc_pre_write_setup:
       *   - dev[0x16]=0 (standard): iVar1 = num_blocks (block count)
       *   - dev[0x16]=1 (custom):   iVar1 = sector_size * num_blocks (byte count)
       *
       * sdcc_adma_transfer/sdcc_pio_transfer expect a byte count.
       * When ADMA is enabled (+0xA4 != 0), the ADMA function pointer
       * path handles block→byte conversion internally. When ADMA is
       * disabled (our case), we must convert here.
       */
      {
        int xfer_bytes = (dev[DEV_CUSTOM_SECTOR] != 0) ? iVar1
                         : iVar1 * (int)dev[DEV_SECTOR_SIZE];
        if ((int)(uVar4 << 0x1e) < 0) {
          iVar8 = sdcc_adma_transfer((mmc_dev_t *)iVar5,(uint *)buf,xfer_bytes);
        }
        else {
          /* Clear DMA enable flag, keep block count */
          xfer_mode[0] = (uint)(ushort)xfer_mode[0];
          sdcc_set_transfer_mode(*dev,(ushort *)xfer_mode);
          iVar8 = sdcc_pio_transfer((mmc_dev_t *)iVar5,(byte *)buf,xfer_bytes);
        }
      }
      xfer_mode[0] = 0;
      xfer_mode[1] = 0;
      sdcc_set_transfer_mode(*dev,(ushort *)xfer_mode);
    }
LAB_0803376e:
    /* Post-write: send stop command if needed (CMD12 for multi-block) */
    if (((int)(uVar4 << 0x1d) < 0) || ((cmd->cmd_num != 0x12 && (cmd->cmd_num != 0x19)))) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1; /* need CMD12 STOP */
    }
    iVar1 = sdcc_post_write_cleanup(dev, local_38 + 1, uVar3);
    /* ADMA completion callback */
    if ((*(int *)(iVar5 + 0xa4) != 0) && (iVar6 == 0)) {
      if ((int)(uVar4 << 0x1e) < 0) {
        uVar3 = 1;
      }
      else {
        uVar3 = 2;
      }
      iVar8 = (**(code **)(iVar5 + 0xb0))(iVar5,uVar3); /* ADMA done callback */
    }
    if (iVar8 == 0) {
      iVar8 = iVar1;
    }
    dev[DEV_LAST_ERROR] = iVar8; /* store result in device struct */
    return iVar8;
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

  if ((handle != (mmc_handle_t *)0x0) && (*handle != 0)) {
    local_10 = handle;
    mmc_release_slot(&local_10);
    return 0;
  }
  return 0x14;
}

/* orig: 0x08033d44 mmc_erase_range — erase a range of sectors.
 *
 * Uses the eMMC erase sequence:
 *   CMD35 (ERASE_GROUP_START) → start sector
 *   CMD36 (ERASE_GROUP_END)   → end sector
 *   CMD38 (ERASE)             → execute
 *
 * handle = device handle (ptr to ptr to device struct)
 * sector = start sector
 * count = sector count
 */
int mmc_erase_range(mmc_handle_t *handle, int sector, int count)
{
  int iVar1;
  uint *puVar2;
  mmc_cmd_t cmd; /* command struct (reused for CMD35/36/38) */

  if (((handle == (uint *)0x0) || (puVar2 = (uint *)*handle, puVar2 == (uint *)0x0)) ||
     (2 < *puVar2)) {
    iVar1 = 0x14;
  }
  else if (((char)puVar2[DEV_CARD_TYPE] == '\x06') || ((char)puVar2[DEV_CARD_TYPE] == '\x02')) {
    /* Card must be MMC or eMMC (type 2 or 6) */
    iVar1 = mmc_ensure_partition(handle);
    if (iVar1 == 0) {
      /* CMD35: ERASE_GROUP_START */
      memset_zero(&cmd, sizeof(cmd));
      cmd.cmd_num = 0x23;                          /* CMD35 */
      cmd.cmd_arg = sector;                        /* start address */
      /* NOTE: for non-HC (type 2) cards, CMD35 arg should be byte address
       * (sector * 0x200), but this path is never taken on msm8909 where the
       * device is always type 6 (eMMC/HC). Faithfully reproduced from original
       * FUN_08033d44 which also passes sector unconverted for CMD35. */
      *(uint8_t *)&cmd.resp_type = 1;              /* resp_type: R1 */
      iVar1 = sdcc_send_cmd(puVar2, &cmd);
      if (iVar1 == 0) {
        /* CMD36: ERASE_GROUP_END */
        if ((char)puVar2[DEV_CARD_TYPE] == '\x06') {
          cmd.cmd_arg = sector + count + -1;       /* HC: sector-addressed */
        }
        else {
          /* non-HC: byte-addressed end = sector + (count-1)*512.
           * Inconsistent with CMD35 which should also use byte address. */
          cmd.cmd_arg = sector + count * 0x200 + -0x200;
        }
        cmd.cmd_num = 0x24;                        /* CMD36 */
        iVar1 = sdcc_send_cmd(puVar2, &cmd);
        if (iVar1 == 0) {
          /* CMD38: ERASE */
          memset_zero(&cmd, sizeof(cmd));
          cmd.cmd_num = 0x26;                      /* CMD38 */
          *(uint8_t *)&cmd.resp_type = 1;          /* resp_type: R1 */
          cmd.busy_wait = 1;                       /* busy_wait */
          iVar1 = sdcc_send_cmd(puVar2, &cmd);
          if (iVar1 == 0) {
            if ((cmd.resp[0] & 0xfdff8000) == 0) { /* check R1 error bits */
              return 0; /* success */
            }
          }
          else {
            if (iVar1 != 7) {
              return iVar1;
            }
            /* Busy timeout — keep waiting */
            if ((cmd.resp[0] & 0xfdff8000) == 0) {
              do {
                iVar1 = sdcc_busy_wait(puVar2);
              } while (iVar1 == 7);
              return iVar1;
            }
          }
          iVar1 = 0xf; /* erase error */
        }
      }
    }
  }
  else {
    iVar1 = 0x16; /* wrong card type */
  }
  return iVar1;
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
    uint *puVar3;
    uint uVar2;
    uint uVar4 = 0;
    uint local_28 = 0;
    uint local_24 = 0;

    if (((handle == (uint *)0x0) || (puVar3 = (uint *)*handle, puVar3 == (uint *)0x0)) ||
        (2 < *puVar3) || (info == (char *)0x0)) {
        return 0x14;
    }
    memset_zero(info, 0x40); /* memset(info, 0, 64) */
    *info = (char)puVar3[DEV_CARD_TYPE]; /* card type */
    *(uint *)(info + 0xc) = puVar3[DEV_SECTOR_SIZE]; /* sector size */
    uVar2 = sdcc_get_slot_status(*(uint *)*handle);
    if ((uVar2 & 1) == 0) {
        info[0x18] = '\0';  /* card not present */
    } else {
        info[0x18] = '\x01'; /* card present */
    }
    /* eMMC only: get capacity from partition table */
    uVar4 = mmc_get_capacity(handle, &local_28, &local_24);
    *(uint *)(info + 4) = local_28; /* total sectors */
    info[0x10] = (char)puVar3[0x18]; /* num physical partitions (DEV+0x60) */
    *(uint *)(info + 0x14) = puVar3[DEV_BLOCK_COUNT]; /* block count */
    {
        char cVar1 = mmc_is_partition_active(handle);
        info[0x24] = cVar1; /* is active */
    }
    *(uint *)(info + 8) = puVar3[DEV_CARD_ID]; /* card identifier */
    *(uint *)(info + 0x20) = local_24; /* partition type */
    *(uint *)(info + 0x1c) = puVar3[DEV_RELIABLE_WR_CNT]; /* reliable write count */
    *(uint16_t *)(info + 0x26) = *(uint16_t *)((int)puVar3 + 0x3e); /* speed class */
    *(short *)(info + 0x28) = (short)puVar3[DEV_SPEED_MODE]; /* speed mode */
    memcpy(info + 0x2a, (char *)puVar3 + 0x42, 7); /* manufacturer ID */
    info[0x31] = *(char *)((int)puVar3 + 0x49); /* product revision */
    *(uint *)(info + 0x34) = puVar3[0x13]; /* GPP1 size */
    *(uint *)(info + 0x38) = puVar3[0x14]; /* GPP2 size */
    *(uint *)(info + 0x3c) = puVar3[0x15]; /* GPP3 size */
    sdcc_write_complete_notify();
    return uVar4;
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
  char cVar1;
  int iVar2;
  uint *puVar3;
  mmc_cmd_t cmd;

  if (((handle == (uint *)0x0) || (puVar3 = (uint *)*handle, puVar3 == (uint *)0x0)) ||
     (2 < *puVar3)) {
    iVar2 = 0x14;
  }
  /* >>> WP CHECK REMOVED — allow writes regardless of EXT_CSD[160] <<< */
  else if (1) {
    cVar1 = (char)puVar3[DEV_CARD_TYPE]; /* card type */
    if (cVar1 == '\0') {
      iVar2 = 0x15; /* no card */
    }
    else if (((cVar1 == '\x01') || (cVar1 == '\x05')) || ((cVar1 == '\x02' || (cVar1 == '\x06')))) {
      /* Card is SD/SDHC/MMC/eMMC — proceed with read */
      iVar2 = mmc_ensure_partition(handle);
      if (iVar2 == 0) {
        memset_zero(&cmd, sizeof(cmd));
        /* Build command struct */
        if (num_blocks == 1) {
          cmd.cmd_num = 0x11; /* CMD17: READ_SINGLE_BLOCK */
        }
        else {
          cmd.cmd_num = 0x12; /* CMD18: READ_MULTIPLE_BLOCK */
        }
        *(uint8_t *)&cmd.resp_type = 1; /* resp_type: R1 */
        cmd.busy_wait = 0;              /* reserved */
        cmd.cmd_arg = sector;           /* cmd_arg */
        /* Convert sector number to byte address for non-HC cards */
        if (((char)puVar3[DEV_CARD_TYPE] != '\x05') && ((char)puVar3[DEV_CARD_TYPE] != '\x06')) {
          cmd.cmd_arg = sector * puVar3[DEV_SECTOR_SIZE]; /* sector * sector_size */
        }
        cmd.flags = 2;                  /* flags: bit 1 = data transfer */
        iVar2 = sdcc_write_data(puVar3, &cmd, buf, num_blocks);
      }
    }
    else {
      iVar2 = 0x10; /* unsupported card type */
    }
  }
  else {
    iVar2 = 0x1b; /* WRITE PROTECTED — EXT_CSD[160] != 0 */
  }
  return iVar2;
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
  int iVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;

  if (((handle == (mmc_handle_t *)0x0) || (puVar2 = (mmc_dev_t *)*handle, puVar2 == (mmc_dev_t *)0x0)) ||
     (2 < *puVar2)) {
    return 0x14;
  }
  /* Must be MMC (type 2) or eMMC (type 6) */
  if (((char)puVar2[DEV_CARD_TYPE] != '\x02') && ((char)puVar2[DEV_CARD_TYPE] != '\x06')) {
    return 0x16;
  }
  iVar3 = (int)*handle; /* device struct */
  uVar4 = handle[1]; /* requested partition */
  if (uVar4 == 0xffffffff) {
    uVar4 = 0; /* default to user partition */
  }
  /* Validate partition index against max partitions */
  if (*(uint *)(iVar3 + 0x34) <= uVar4) {
    return 0x14;
  }
  /* Check if already on the right partition */
  iVar1 = mmc_is_partition_active(handle);
  if (iVar1 == 1) {
    iVar1 = 0; /* already active, nothing to do */
  }
  else {
    /* Restore current partition field first if needed */
    if ((*(int *)(iVar3 + 4) != 0) &&
       (iVar1 = mmc_switch_cmd6((mmc_dev_t *)iVar3,(uint)*(byte *)(iVar3 + DEV_BYTE_PART_CONFIG) << 0xb | 0x3b30000), iVar1 != 0)) {
      /* CMD6 SWITCH: Access=3 (write), Index=0xB3 (PARTITION_CONFIG),
       * Value=current partition << 3, Cmd_set=0 */
      return iVar1;
    }
    /* Switch to requested partition */
    if (uVar4 == 0) {
      uVar4 = 7; /* user partition = config value 7 */
    }
    /* CMD6 arg: 0x03B30000 | (dev[4] | partition_idx << 3) << 8
     * This writes PARTITION_CONFIG in EXT_CSD[179]:
     *   bits[2:0] = PARTITION_ACCESS (which partition to access)
     *   bits[5:3] = BOOT_PARTITION_ENABLE
     *   bit[6]    = BOOT_ACK */
    iVar1 = mmc_switch_cmd6((mmc_dev_t *)iVar3,(*(uint *)(iVar3 + 4) | uVar4 << 3) << 8 | 0x3b30000);
    if (iVar1 == 0) {
      *(char *)(iVar3 + DEV_BYTE_PART_CONFIG) = (char)uVar4; /* update cached partition */
      return 0;
    }
  }
  return iVar1;
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
    uint *puVar3;
    char cVar1;
    int iVar2;
    mmc_cmd_t cmd;

    if (((handle == (uint *)0x0) || (puVar3 = (uint *)*handle, puVar3 == (uint *)0x0)) ||
        (2 < *puVar3)) {
        return 0x14;
    }
    /* >>> WP CHECK REMOVED — allow writes regardless of EXT_CSD[160] <<< */
    cVar1 = (char)puVar3[DEV_CARD_TYPE];
    if (cVar1 == '\0') {
        return 0x15;
    }
    if (((cVar1 == '\x01') || (cVar1 == '\x05')) || ((cVar1 == '\x02' || (cVar1 == '\x06')))) {
        iVar2 = mmc_ensure_partition(handle);
        if (iVar2 == 0) {
            memset_zero(&cmd, sizeof(cmd));
            /* Build command struct */
            if (num_blocks == 1) {
                cmd.cmd_num = 0x18;     /* CMD24: WRITE_SINGLE_BLOCK */
            } else {
                cmd.cmd_num = 0x19;     /* CMD25: WRITE_MULTIPLE_BLOCK */
            }
            *(uint8_t *)&cmd.resp_type = 1; /* resp_type: R1 */
            cmd.busy_wait = 0;               /* reserved */
            cmd.cmd_arg = sector;
            /* Convert to byte address for non-HC cards */
            if (((char)puVar3[DEV_CARD_TYPE] != '\x05') && ((char)puVar3[DEV_CARD_TYPE] != '\x06')) {
                cmd.cmd_arg = sector * puVar3[DEV_SECTOR_SIZE];  /* sector * sector_size */
            }
            cmd.flags = 1;                   /* flags: bit 0 = write direction */
            iVar2 = sdcc_write_data(puVar3, &cmd, buf, num_blocks);
        }
    } else {
        iVar2 = 0x10;
    }
    return iVar2;
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
  uint uVar1;
  uint uVar2;
  int iVar3;

  iVar3 = *handle;       /* device struct */
  uVar1 = handle[1];     /* partition index */
  if (uVar1 == 0xffffffff) {
    uVar1 = 0;
  }
  /* Non-user partitions require partition switching support */
  if ((uVar1 != 0) && (*(char *)(iVar3 + DEV_BYTE_PART_SWITCH) == '\0')) {
    return 0x16;
  }
  /* Check partition exists (bitmask at dev+0x7C) */
  if ((1 << (uVar1 & 0xff) & *(uint *)(iVar3 + DEV_WORD_PART_MASK)) == 0) {
    return 0x14;
  }
  if (uVar1 == 0) {
    *sectors = *(uint *)(iVar3 + 0x1c); /* user area: total sectors from CSD */
    uVar2 = 0;
  }
  else {
    if (uVar1 == 1) {
      /* Boot partition 1: EXT_CSD[226-227] * 128KB / 512 */
      *sectors = (uint)(*(int *)(iVar3 + 100) << 10) >> 9;
      *part_type = 1;
      return 0;
    }
    if (uVar1 == 2) {
      /* Boot partition 2: same size as boot1 */
      *sectors = (uint)(*(int *)(iVar3 + 100) << 10) >> 9;
      uVar2 = 2;
    }
    else if (uVar1 == 4) {
      *sectors = *(uint *)(iVar3 + 0x68); /* GP1 */
      uVar2 = 4;
    }
    else if (uVar1 == 5) {
      *sectors = *(uint *)(iVar3 + 0x6c); /* GP2 */
      uVar2 = 5;
    }
    else if (uVar1 == 6) {
      *sectors = *(uint *)(iVar3 + 0x70); /* GP3 */
      uVar2 = 6;
    }
    else {
      if (uVar1 != 7) {
        return 0x14;
      }
      *sectors = *(uint *)(iVar3 + 0x74); /* GP4 */
      uVar2 = 7;
    }
  }
  *part_type = uVar2;
  return 0;
}

/* orig: 0x08034966 mmc_is_partition_active — check if requested partition
 * is already the currently selected one.
 *
 * Compares handle[1] (requested partition) against the cached current
 * partition at dev+0x78. Returns 1 if already active, 0 otherwise. */
uint mmc_is_partition_active(mmc_handle_t *handle)
{
  char cVar1;
  int iVar2;

  iVar2 = handle[1]; /* requested partition */
  if (iVar2 == -1) {
    iVar2 = 0;
  }
  cVar1 = *(char *)(*handle + DEV_BYTE_PART_CONFIG); /* current partition */
  if (cVar1 == '\x01') {
    if (iVar2 == 1) {
      return 1; /* boot1 already active */
    }
  }
  else if (cVar1 == '\x02') {
    if (iVar2 == 2) {
      return 1; /* boot2 already active */
    }
  }
  else if ((cVar1 == '\a') && (iVar2 == 0)) {
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
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;

  if (handle == (mmc_handle_t *)0x0) {
    return 0x14;
  }
  iVar3 = handle[1]; /* requested partition */
  if (iVar3 == -1) {
    iVar3 = 0;
  }
  /* Already on the right partition? */
  if (*(int *)(*handle + 4) == iVar3) {
    return 0;
  }
  /* Must be MMC/eMMC for partition switching */
  cVar1 = *(char *)(*handle + DEV_BYTE_CARD_TYPE);
  if ((cVar1 != '\x02') && (cVar1 != '\x06')) {
    return 0x16;
  }
  iVar3 = *handle;
  uVar4 = handle[1];
  if (uVar4 == 0xffffffff) {
    uVar4 = 0;
  }
  if ((uVar4 != 0) && (*(char *)(iVar3 + DEV_BYTE_PART_SWITCH) == '\0')) {
    return 0x16; /* device doesn't support partition switching */
  }
  if ((1 << (uVar4 & 0xff) & *(uint *)(iVar3 + DEV_WORD_PART_MASK)) == 0) {
    return 0x14; /* partition doesn't exist */
  }
  /* CMD6 SWITCH: write PARTITION_CONFIG
   * Arg format: 0x03B30000 | (boot_config | partition_access) << 8
   * boot_config = dev+0x78 current config, shifted left 3 bits
   * partition_access = requested partition index */
  iVar2 = mmc_switch_cmd6((mmc_dev_t *)iVar3,(uVar4 | (uint)*(byte *)(iVar3 + DEV_BYTE_PART_CONFIG) << 3) << 8 | 0x3b30000);
  if (iVar2 == 0) {
    *(uint *)(iVar3 + 4) = uVar4; /* cache new partition */
  }
  return iVar2;
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
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_20;

  local_20 = 0;
  if (slot < 3) {
    iVar2 = mmc_init_card(slot);
    if (iVar2 == 0) {
      return 0;
    }
    iVar2 = mmc_get_slot_context(slot);
    if (iVar2 != 0) {
      iVar4 = iVar2 + 0xc;
      local_20 = (int)mmc_alloc_handle(slot,flags);
      if (local_20 == 0) {
        iVar2 = mmc_setup_partitions(iVar4);
        if (iVar2 != 0) {
          return local_20;
        }
        mmc_finalize_init(iVar4);
        return local_20;
      }
      /* Error handling: classify and potentially recover */
      cVar1 = *(char *)(iVar2 + 0x14);
      if (cVar1 != '\x04') {
        if (cVar1 == '\x01') { return local_20; }
        if (cVar1 == '\x05') { return local_20; }
        if (cVar1 == '\x02') { return local_20; }
        if (cVar1 == '\x06') { return local_20; }
        cVar1 = mmc_classify_error((mmc_handle_t *)local_20);
        *(char *)(iVar2 + 0x14) = cVar1;
        *(char *)(iVar2 + 0x24) = cVar1;
        if (cVar1 != '\0') {
          if (cVar1 == '\x04') goto LAB_08034086;
          iVar3 = mmc_config_bus(iVar4);
          if (iVar3 == 0) {
            if (*(char *)(iVar2 + 0x98) == '\0') {
              MCI_REG(slot, MCI_CLK) =
                   MCI_REG(slot, MCI_CLK) | 0x1000;
              sdcc_enable_clock(slot);
            }
            iVar3 = mmc_identify_card(iVar4);
            if (iVar3 == 0) {
              mmc_set_bus_width((uint *)iVar4,1,0,0);
              iVar4 = mmc_set_speed((mmc_dev_t *)iVar4);
              if (iVar4 == 0) {
                *(uint8_t *)(iVar2 + SLOT_CTX_INIT_STATE) = 2;
                *(uint8_t *)(iVar2 + 0xa0) = 0;
                return local_20;
              }
              *(int *)(iVar2 + 0x1c) = iVar4;
              *(uint8_t *)(iVar2 + 0x14) = 0;
              goto LAB_080340c6;
            }
          }
          *(int *)(iVar2 + 0x1c) = iVar3;
        }
LAB_080340c6:
        mmc_close_handle((mmc_handle_t *)local_20);
        return 0;
      }
LAB_08034086:
      mmc_release_slot((mmc_handle_t **)&local_20);
      return local_20;
    }
  }
  return 0;
}

/* str_find_replace (0x0803725c) — REMOVED, only used by handle_patch */
