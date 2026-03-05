/* storage.c — Partition selection and I/O abstraction.
 *
 * This layer sits between the firehose handlers and the eMMC driver.
 * Key function: storage_write_sectors — the entry point from handle_program.
 *
 * The storage context struct (at DAT_08058430) contains:
 *   +0x00: flags/state
 *   +0x04: device handle for partition 0 (user)
 *   +0x08: device handle for partition 1 (boot1)
 *   +0x0C: device handle for partition 2 (boot2)
 *   +0x10-0x24: device handles for partitions 3-8
 *   +0x26: current partition index (byte)
 *
 * Removed (dead after handler pruning): storage_select_all, storage_erase_partition,
 *   storage_commit, storage_fw_update, storage_log_drive_info, storage_log_partition_info,
 *   storage_select_and_read, safe_strlcat
 *
 * Source: src/fhprg/fhprg_8037820.c (0x08037xxx–0x08038xxx range)
 */
#include "firehose.h"

/* orig: 0x08037f64 storage_get_sector_count — get total sectors for current partition */
uint storage_get_sector_count(param_1)
int param_1;
{
    int iVar1;
    undefined1 auStack_48[4];
    uint local_44;

    iVar1 = *(int *)(param_1 + (uint)*(byte *)(param_1 + 0x26) * 4 + 4);
    if ((iVar1 == 0) || (iVar1 = mmc_get_partition_info(iVar1, (char *)auStack_48), iVar1 != 0)) {
        local_44 = 0;
    }
    return local_44;
}

/* orig: 0x08038014 storage_read_sectors — read sectors from current partition.
 *
 * Looks up the device handle for the current partition (ctx+0x26),
 * then calls mmc_write_blocks to do the actual read (CMD17/CMD18). */
uint storage_read_sectors(param_1, param_2, param_3, param_4, param_5)
int param_1; uint param_2; uint param_3; uint param_4; uint16_t param_5;
{
    int iVar1;
    iVar1 = *(int *)(param_1 + (uint)*(byte *)(param_1 + 0x26) * 4 + 4);
    if ((iVar1 != 0) && (iVar1 = mmc_write_blocks(iVar1, param_3, param_2, param_5), iVar1 == 0)) {
        return 1;
    }
    return 0;
}

/* orig: 0x080381d8 storage_write_sectors — THE write entry point from handlers.
 *
 * Called by handle_program. Selects the device handle for the current
 * partition (via byte at ctx+0x26), then calls mmc_write_sectors.
 *
 * ctx+0x26 = partition index (0=user, 1=boot1, 2=boot2, etc.)
 * The device handle table starts at ctx+4, indexed by partition.
 *
 * Write path continues:
 *   storage_write_sectors -> mmc_write_sectors (WP check) ->
 *   sdcc_write_data -> sdcc_send_cmd
 */
uint storage_write_sectors(param_1, param_2, param_3, param_4, param_5, param_6, param_7)
int param_1; uint param_2; uint param_3; uint param_4;
uint16_t param_5; uint param_6; int *param_7;
{
    int iVar1;

    iVar1 = *(int *)(param_1 + (uint)*(byte *)(param_1 + 0x26) * 4 + 4);
    if (iVar1 != 0) {
        iVar1 = mmc_write_sectors((uint *)iVar1, param_3, param_2, param_5);
        if (iVar1 == 0) {
            return 1;
        }
        if (param_7 != (int *)0x0) {
            *param_7 = iVar1;
        }
    }
    return 0;
}

/* orig: 0x08038206 storage_select_partition — select partition by index.
 * Validates that the partition exists and sets ctx+0x26. */
uint storage_select_partition(param_1, param_2)
int param_1; uint param_2;
{
    int iVar1;
    uint uVar2;
    undefined1 auStack_50[28];
    int local_34;

    if ((((param_2 < 8) && (param_2 != 3)) &&
         (iVar1 = mmc_get_partition_info(*(uint *)(param_1 + 4), auStack_50), iVar1 == 0)) &&
        (param_2 <= (uint)(local_34 - 1))) {
        uVar2 = 1;
        *(char *)(param_1 + 0x26) = (char)param_2;
    } else {
        uVar2 = 0;
    }
    return uVar2;
}

/* orig: 0x0803823e parse_uint_from_str — parse unsigned integer from string */
uint parse_uint_from_str(param_1, param_2, param_3, param_4)
char *param_1; uint8_t *param_2; uint param_3; char *param_4;
{
    longlong lVar1;
    char *local_10;

    if (param_2 != (uint8_t *)0x0) {
        if (*param_1 != '\0') {
            local_10 = param_4;
            lVar1 = thunk_FUN_080071ec(param_1, &local_10, 0);
            if ((*local_10 == '\0') && (lVar1 != -0x80000000LL) && (lVar1 != 0x7fffffffLL)) {
                *param_2 = 1;
                return 0;
            }
            *param_2 = 0;
            return 0;
        }
        *param_2 = 0;
    }
    return 0;
}

/* orig: 0x080382fa strncasecmp_fh — case-insensitive string compare */
int strncasecmp_fh(param_1, param_2, param_3)
uint8_t *param_1; uint8_t *param_2; int param_3;
{
    uint uVar1;
    uint uVar2;
    uint uVar3;

    while (true) {
        if (param_3 == 0) {
            return 0;
        }
        uVar2 = (uint)*param_1;
        uVar3 = (uint)*param_2;
        uVar1 = uVar2;
        if (uVar2 - 0x41 < 0x1a) {
            uVar1 = uVar2 + 0x20 & 0xff; /* tolower */
        }
        if (uVar3 - 0x41 < 0x1a) {
            uVar3 = uVar3 + 0x20 & 0xff;
        }
        if (uVar1 - uVar3 != 0) break;
        if (uVar2 == 0) {
            return 0;
        }
        param_3 = param_3 + -1;
        param_1 = param_1 + 1;
        param_2 = param_2 + 1;
    }
    return uVar1 - uVar3;
}
