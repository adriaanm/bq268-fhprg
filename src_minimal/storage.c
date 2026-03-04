/* storage.c — Partition selection and I/O abstraction.
 *
 * This layer sits between the firehose handlers and the eMMC driver.
 * Key function: mmc_write_wrapper — the entry point from handle_program.
 *
 * Source: src/fhprg/fhprg_8037820.c (0x08037xxx–0x08038xxx range)
 */
#include "firehose.h"

/* orig: 0x08037c40 FUN_08037c40 — select "all" partition (index 8) */
uint FUN_08037c40(param_1)
int param_1;
{
    if (*(char *)(param_1 + 0x26) != '\b') {
        *(undefined1 *)(param_1 + 0x26) = 8;
        return 1;
    }
    return 0;
}

/* orig: 0x08037c56 FUN_08037c56 — erase entire current partition */
uint FUN_08037c56(param_1)
int param_1;
{
    int iVar1;
    uint uVar2;
    int iVar3;
    undefined1 auStack_48[4];
    int local_44;

    iVar3 = *(int *)(param_1 + (uint)*(byte *)(param_1 + 0x26) * 4 + 4);
    if (((iVar3 == 0) || (iVar1 = FUN_08033ee8(iVar3, (char *)auStack_48), iVar1 != 0)) ||
        (iVar3 = FUN_08033d44(iVar3, 0, local_44 + -1), iVar3 != 0)) {
        uVar2 = 0;
    } else {
        uVar2 = 1;
    }
    return uVar2;
}

/* orig: 0x08037c88 FUN_08037c88 — commit stub (logs but does nothing) */
uint FUN_08037c88()
{
    firehose_log((uint)"would have committed here", 0, 0, 0);
    return 1;
}

/* orig: 0x08037cb0 FUN_08037cb0 — firmware update orchestrator */
uint FUN_08037cb0(param_1)
int param_1;
{
    int iVar1;
    int iVar2;
    char *pcVar3;
    uint uVar4;
    int *in_stack_00000000;

    iVar1 = FUN_08033fe0(0, 0);
    if (iVar1 == 0) {
        firehose_log((uint)"Could not open User partition. Check card.", 0, 0, 0);
        if (in_stack_00000000 != (int *)0x0) {
            *in_stack_00000000 = 1;
        }
    } else {
        FUN_08033d28();
        uVar4 = 0;
        do {
            iVar1 = param_1 + uVar4 * 4;
            if ((*(int *)(iVar1 + 4) != 0) && (iVar2 = FUN_08033d28(), iVar2 != 0)) {
                if (*in_stack_00000000 != 0) {
                    *in_stack_00000000 = iVar2;
                }
                firehose_log((uint)"Failed to close all handles and deinit device", 0, 0, 0);
                if (in_stack_00000000 == (int *)0x0) {
                    return 0;
                }
                firehose_log((uint)"Deinit error %d", (uint)*in_stack_00000000, 0, 0);
                return 0;
            }
            *(uint *)(iVar1 + 4) = 0;
            uVar4 = uVar4 + 1;
        } while (uVar4 < 8);
        iVar1 = FUN_08027328(param_1);
        if (iVar1 == 0) {
            pcVar3 = "Failed to Re-Initialize HW. Please Powercycle device and try";
        } else {
            iVar1 = FUN_08033fe0(0, 0);
            if (iVar1 != 0) {
                firehose_log((uint)"FW Update Successful. FW Version updated from '0x%X' to '0x%X'", 0, 0, 0);
                FUN_08033d28(iVar1);
                return 1;
            }
            pcVar3 = "Could not open User partition after reset. Check card.";
        }
        firehose_log((uint)pcVar3, 0, 0, 0);
        if (in_stack_00000000 != (int *)0x0) {
            *in_stack_00000000 = 1;
        }
    }
    return 0;
}

/* orig: 0x08037e88 FUN_08037e88 — log drive size info */
void FUN_08037e88(param_1)
int param_1;
{
    firehose_log((uint)"DRIVE4_SIZE_IN_KB %d", *(uint *)(param_1 + 0x30) >> 1, 0, 0);
    firehose_log((uint)"DRIVE5_SIZE_IN_KB %d", *(uint *)(param_1 + 0x34) >> 1, 0, 0);
    firehose_log((uint)"DRIVE6_SIZE_IN_KB %d", *(uint *)(param_1 + 0x38) >> 1, 0, 0);
    firehose_log((uint)"DRIVE7_SIZE_IN_KB %d", *(uint *)(param_1 + 0x3c) >> 1, 0, 0);
    firehose_log((uint)"ENH_SIZE %d", *(uint *)(param_1 + 0x40), 0, 0);
    firehose_log((uint)"ENH_START_ADDR %d", *(uint *)(param_1 + 0x44), 0, 0);
    firehose_log((uint)"GPP_ENH_FLAG %d", *(undefined1 *)(param_1 + 0x48), 0, 0);
}

/* orig: 0x08037f64 FUN_08037f64 — get partition sector count */
uint FUN_08037f64(param_1)
int param_1;
{
    int iVar1;
    undefined1 auStack_48[4];
    uint local_44;

    iVar1 = *(int *)(param_1 + (uint)*(byte *)(param_1 + 0x26) * 4 + 4);
    if ((iVar1 == 0) || (iVar1 = FUN_08033ee8(iVar1, (char *)auStack_48), iVar1 != 0)) {
        local_44 = 0;
    }
    return local_44;
}

/* orig: 0x08037f88 FUN_08037f88 — log partition info */
uint FUN_08037f88(param_1)
int param_1;
{
    int iVar1;
    uint uVar2;
    undefined1 auStack_48[4];
    uint local_44;
    uint local_3c;
    uint local_2c;

    iVar1 = *(int *)(param_1 + (uint)*(byte *)(param_1 + 0x26) * 4 + 4);
    uVar2 = 0;
    if (iVar1 != 0) {
        iVar1 = FUN_08033ee8(iVar1, (char *)auStack_48);
        if (iVar1 == 0) {
            firehose_log((uint)"num_partition_sectors=%d", local_44, 0, 0);
            firehose_log((uint)"SECTOR_SIZE_IN_BYTES=%d", local_3c, 0, 0);
            firehose_log((uint)"num_physical_partitions=%d", local_2c, 0, 0);
            uVar2 = 1;
        }
    }
    return uVar2;
}

/* orig: 0x08038014 FUN_08038014 — read sectors from current partition */
uint FUN_08038014(param_1, param_2, param_3, param_4, param_5)
int param_1; uint param_2; uint param_3; uint param_4; uint16_t param_5;
{
    int iVar1;
    iVar1 = *(int *)(param_1 + (uint)*(byte *)(param_1 + 0x26) * 4 + 4);
    if ((iVar1 != 0) && (iVar1 = FUN_08034170(iVar1, param_3, param_2, param_5), iVar1 == 0)) {
        return 1;
    }
    return 0;
}

/* orig: 0x0803803c FUN_0803803c — read helper */
uint FUN_0803803c(param_1)
int param_1;
{
    int iVar1;
    if ((*(int *)(param_1 + (uint)*(byte *)(param_1 + 0x26) * 4 + 4) != 0) &&
        (iVar1 = FUN_08034202(), iVar1 == 0)) {
        return 1;
    }
    return 0;
}

/* orig: 0x080381d8 mmc_write_wrapper — THE write entry point from handlers.
 *
 * Called by handle_program. Selects the device handle for the current
 * partition (via byte at ctx+0x26), then calls mmc_write_with_wp_check.
 *
 * ctx+0x26 = partition index (0=user, 1=boot1, 2=boot2, etc.)
 * The device handle table starts at ctx+4, indexed by partition.
 */
uint mmc_write_wrapper(param_1, param_2, param_3, param_4, param_5, param_6, param_7)
int param_1; uint param_2; uint param_3; uint param_4;
uint16_t param_5; uint param_6; int *param_7;
{
    int iVar1;

    iVar1 = *(int *)(param_1 + (uint)*(byte *)(param_1 + 0x26) * 4 + 4);
    if (iVar1 != 0) {
        iVar1 = mmc_write_with_wp_check((uint *)iVar1, param_3, param_2, param_5);
        if (iVar1 == 0) {
            return 1;
        }
        if (param_7 != (int *)0x0) {
            *param_7 = iVar1;
        }
    }
    return 0;
}

/* orig: 0x08038206 FUN_08038206 — select partition by index */
uint FUN_08038206(param_1, param_2)
int param_1; uint param_2;
{
    int iVar1;
    uint uVar2;
    undefined1 auStack_50[28];
    int local_34;

    if ((((param_2 < 8) && (param_2 != 3)) &&
         (iVar1 = FUN_08033ee8(*(uint *)(param_1 + 4), auStack_50), iVar1 == 0)) &&
        (param_2 <= (uint)(local_34 - 1))) {
        uVar2 = 1;
        *(char *)(param_1 + 0x26) = (char)param_2;
    } else {
        uVar2 = 0;
    }
    return uVar2;
}

/* orig: 0x0803823e FUN_0803823e — parse integer from string */
uint FUN_0803823e(param_1, param_2, param_3, param_4)
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

/* orig: 0x08038282 FUN_08038282 — strlcat-like string concatenation */
int FUN_08038282(param_1, param_2, param_3)
char *param_1; char *param_2; int param_3;
{
    char *pcVar1;
    char *pcVar2;
    char *pcVar3;
    char *pcVar4;
    int iVar5;
    bool bVar6;

    iVar5 = param_3;
    for (pcVar1 = param_1; (bVar6 = iVar5 != 0, iVar5 = iVar5 + -1, bVar6 && (*pcVar1 != '\0'));
         pcVar1 = pcVar1 + 1) {
    }
    param_3 = param_3 - ((int)pcVar1 - (int)param_1);
    pcVar3 = pcVar1;
    pcVar4 = param_2;
    if (param_3 == 0) {
        iVar5 = strlen(param_2);
    } else {
        for (; *pcVar4 != '\0'; pcVar4 = pcVar4 + 1) {
            pcVar2 = pcVar3;
            if (param_3 != 1) {
                param_3 = param_3 + -1;
                pcVar2 = pcVar3 + 1;
                *pcVar3 = *pcVar4;
            }
            pcVar3 = pcVar2;
        }
        *pcVar3 = '\0';
        iVar5 = (int)pcVar4 - (int)param_2;
    }
    return iVar5 + ((int)pcVar1 - (int)param_1);
}

/* orig: 0x080382fa strncmp_fh — case-insensitive string compare */
int strncmp_fh(param_1, param_2, param_3)
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
            uVar1 = uVar2 + 0x20 & 0xff;
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
