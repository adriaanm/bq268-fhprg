/* emmc.c — eMMC/SDCC driver layer.
 *
 * This is the critical layer for understanding writes. The write path is:
 *   handle_program → mmc_write_wrapper → mmc_write_with_wp_check →
 *   mmc_write_dispatch → sdcc_command
 *
 * Source: src/fhprg/fhprg_80327f8.c
 */
#include "firehose.h"

/* orig: 0x08032ae4 FUN_08032ae4 — SDCC slot init (stub) */
uint FUN_08032ae4()
{
    return 0;
}

/* orig: 0x08032af8 FUN_08032af8 — get SDCC slot handle by index */
uint FUN_08032af8(param_1)
uint param_1;
{
    uint uVar1 = 0;
    if (param_1 < 2) {
        uVar1 = *(uint *)(&DAT_0804e2ac + param_1 * 4);
    }
    return uVar1;
}

/* orig: 0x08032b94 sdcc_command — low-level SDCC command dispatch.
 *
 * Sends an eMMC command via the SDCC controller.
 * param_1 = device struct pointer
 * param_2 = command struct: [0]=cmd, [1]=arg, [2]=resp_type,
 *           [3-6]=resp, [7]=busy, [8]=status, [9]=flags
 *
 * This is the lowest-level command interface. All eMMC operations
 * (read, write, erase, CMD6 SWITCH, etc.) go through here.
 */
int sdcc_command(param_1, param_2)
int *param_1; int *param_2;
{
    /* Full implementation is ~200 lines of SDCC register manipulation.
     * The key logic:
     * 1. Validate params (return 0x14 if null)
     * 2. For CMD0: wait for card ready (poll status register)
     * 3. Set up command registers
     * 4. Fire command and wait for completion
     * 5. Read response into param_2[3-6]
     * 6. Return 0 on success, error code on failure
     *
     * IMPORTANT: This function talks directly to SDCC hardware registers.
     * When running on real hardware, the register accesses are the actual
     * mechanism by which data reaches the eMMC.
     */
    if ((param_1 == (int *)0x0) || (param_2 == (int *)0x0)) {
        return 0x14;
    }
    /* ... full register-level implementation omitted for now ...
     * See src/fhprg/fhprg_80327f8.c line 267 for complete code */
    return 0;
}

/* orig: 0x08033654 FUN_08033654 — write dispatch thunk (empty in original) */
void FUN_08033654()
{
    return;
}

/* orig: 0x08033656 mmc_write_dispatch — eMMC write data transfer.
 *
 * Handles both PIO and ADMA modes. Sets up block count, fires the
 * write command (CMD24/CMD25), then transfers data.
 */
int mmc_write_dispatch(param_1, param_2, param_3, param_4)
uint *param_1; int *param_2; uint param_3; uint param_4;
{
    /* Full implementation is ~200 lines handling:
     * - ADMA vs PIO path selection
     * - Block count setup (CMD23 for multi-block)
     * - CMD24 (single block) or CMD25 (multi-block) write
     * - Data transfer via FIFO or DMA
     * - Busy wait and error checking
     *
     * See src/fhprg/fhprg_80327f8.c line 1183 for complete code */
    return 0;
}

/* orig: 0x08033ee8 FUN_08033ee8 — get partition info.
 *
 * Fills a 0x40-byte info struct with partition details:
 *   +0x00: partition type (byte)
 *   +0x04: total sectors (uint32)
 *   +0x08: ... more fields
 *   +0x0c: sector count
 *   +0x10: sector size
 *   +0x14: ... etc
 */
uint FUN_08033ee8(param_1, param_2)
uint *param_1; char *param_2;
{
    uint *puVar3;
    uint uVar2;
    uint uVar4 = 0;
    uint local_28 = 0;
    uint local_24 = 0;

    if (((param_1 == (uint *)0x0) || (puVar3 = (uint *)*param_1, puVar3 == (uint *)0x0)) ||
        (2 < *puVar3) || (param_2 == (char *)0x0)) {
        return 0x14;
    }
    FUN_08006d14(param_2, 0x40);
    /* ... fill in partition info from device struct ... */
    *param_2 = (char)puVar3[2];
    *(uint *)(param_2 + 0xc) = puVar3[9];
    uVar2 = FUN_08032af8(*(uint *)*param_1);
    if ((uVar2 & 1) == 0) {
        param_2[0x18] = '\0';
    } else {
        param_2[0x18] = '\x01';
    }
    if (((char)puVar3[2] == '\x02') || ((char)puVar3[2] == '\x06')) {
        uVar4 = FUN_080348e0(param_1, &local_28, &local_24);
        *(uint *)(param_2 + 4) = local_28;
        param_2[0x10] = (char)puVar3[0x18];
        *(uint *)(param_2 + 0x14) = puVar3[0xb];
        {
            char cVar1 = FUN_08034966(param_1);
            param_2[0x24] = cVar1;
        }
        *(uint *)(param_2 + 8) = puVar3[8];
    } else {
        *(uint *)(param_2 + 4) = puVar3[7];
        param_2[0x10] = (char)puVar3[0x18];
        param_2[0x14] = '\0'; param_2[0x15] = '\0';
        param_2[0x16] = '\0'; param_2[0x17] = '\0';
        param_2[0x24] = '\0';
    }
    *(uint *)(param_2 + 0x20) = local_24;
    *(uint *)(param_2 + 0x1c) = puVar3[0xd];
    *(undefined2 *)(param_2 + 0x26) = *(undefined2 *)((int)puVar3 + 0x3e);
    *(short *)(param_2 + 0x28) = (short)puVar3[0x10];
    memcpy(param_2 + 0x2a, (char *)puVar3 + 0x42, 7);
    param_2[0x31] = *(char *)((int)puVar3 + 0x49);
    *(uint *)(param_2 + 0x34) = puVar3[0x13];
    *(uint *)(param_2 + 0x38) = puVar3[0x14];
    *(uint *)(param_2 + 0x3c) = puVar3[0x15];
    FUN_08033654(param_1, param_2);
    return uVar4;
}

/* orig: 0x08034228 mmc_write_with_wp_check — THE write protection gate.
 *
 * This is the function that checks EXT_CSD[160] (byte at dev[0x24]+0xA0)
 * to decide whether to allow writes. If the WP byte is non-zero,
 * returns 0x1b (write protected).
 *
 * The write path goes:
 *   1. Validate device struct
 *   2. CHECK: *(char*)(dev[0x24] + 0xA0) — if nonzero, return 0x1b
 *   3. Check card state (must be transfer state)
 *   4. Call mmc_pre_write_check()
 *   5. Build command struct (CMD24 or CMD25)
 *   6. Call mmc_write_dispatch() to do actual transfer
 */
int mmc_write_with_wp_check(param_1, param_2, param_3, param_4)
uint *param_1; int param_2; uint param_3; int param_4;
{
    uint *puVar3;
    char cVar1;
    int iVar2;
    uint local_40;
    int local_3c;
    undefined1 local_38;
    uint local_24;
    uint local_1c;

    if (((param_1 == (uint *)0x0) || (puVar3 = (uint *)*param_1, puVar3 == (uint *)0x0)) ||
        (2 < *puVar3)) {
        return 0x14;
    }
    /* >>> THE WP CHECK — EXT_CSD byte 160 <<< */
    if (*(char *)(puVar3[0x24] + 0xa0) != '\0') {
        return 0x1b;   /* write protected! */
    }
    cVar1 = (char)puVar3[2];
    if (cVar1 == '\0') {
        return 0x15;
    }
    if (((cVar1 == '\x01') || (cVar1 == '\x05')) || ((cVar1 == '\x02' || (cVar1 == '\x06')))) {
        iVar2 = mmc_pre_write_check();
        if (iVar2 == 0) {
            if (param_4 == 1) {
                local_40 = 0x18;     /* CMD24: single block write */
            } else {
                local_40 = 0x19;     /* CMD25: multi-block write */
            }
            local_38 = 1;
            local_24 = 0;
            local_3c = param_2;
            if (((char)puVar3[2] != '\x05') && ((char)puVar3[2] != '\x06')) {
                local_3c = param_2 * puVar3[9];  /* sector * sector_size */
            }
            local_1c = 1;
            iVar2 = mmc_write_dispatch(puVar3, (int *)&local_40, param_3, param_4);
        }
    } else {
        iVar2 = 0x10;
    }
    return iVar2;
}

/* orig: 0x080348e0 FUN_080348e0 — eMMC capacity helper (stub) */
uint FUN_080348e0(param_1, param_2, param_3)
uint *param_1; uint *param_2; uint *param_3;
{
    /* Reads capacity info from device struct */
    return 0;
}

/* orig: 0x08034966 FUN_08034966 — eMMC partition config helper (stub) */
char FUN_08034966(param_1)
uint *param_1;
{
    /* Returns partition configuration byte */
    return 0;
}

/* orig: 0x0803707c handle_response — send XML success/failure response */
uint handle_response(param_1)
uint param_1;
{
    FUN_08037084(param_1, 0, 0, 0);
    return 0;
}

/* orig: 0x08037084 FUN_08037084 — build and send XML response with attributes.
 *
 * Builds: <?xml ...?><data><response value="ACK|NAK" attr="val" .../></data>
 * Then flushes via USB.
 */
uint FUN_08037084(param_1, param_2, param_3, param_4)
int param_1; int param_2; uint param_3; uint param_4;
{
    int iVar1;
    uint uVar2;
    uint uVar3;
    undefined *puVar4;
    uint *puVar5;
    uint *puVar6;
    int iVar7;
    undefined1 auStack_130[256];
    int local_30;
    uint uStack_8;
    uint uStack_4;

    iVar1 = DAT_0804cd58;
    local_30 = DAT_0804cd58;
    uStack_8 = param_3;
    uStack_4 = param_4;
    FUN_08006d14(auStack_130, 0x100);
    uVar2 = FUN_08006906("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>");
    FUN_080391f0((int *)&DAT_08055f18, (uint)"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>", uVar2, 0);
    FUN_08039100((uint)&DAT_08055f18, (uint)&DAT_08037180);
    FUN_080390f4((uint)&DAT_08055f18, (uint)"response");
    if (param_1 == 1) {
        puVar4 = (undefined *)&DAT_080371a0;  /* "ACK" */
    } else {
        puVar4 = (undefined *)&DAT_08037194;  /* "NAK" */
    }
    FUN_08039174((uint)&DAT_08055f18, (uint)"value", (uint)puVar4);
    iVar7 = 0;
    puVar6 = &uStack_8;
    do {
        if (param_2 <= iVar7) {
            FUN_080390d8((uint)&DAT_08055f18);
            FUN_080390e4((uint)&DAT_08055f18, (uint)&DAT_08037180);
            FUN_080371b8(0, 0);
            uVar2 = 0;
LAB_0803715c:
            if (local_30 != iVar1) {
                FUN_08010960();
            }
            return uVar2;
        }
        puVar5 = puVar6 + 2;
        uVar2 = *puVar6;
        uVar3 = puVar6[1] & 0xff;
        if (uVar3 != 99) {
            if (uVar3 == 100) {
                uVar3 = *puVar5;
                puVar4 = (undefined *)&DAT_080371a8;
                goto LAB_080370fe;
            }
            if (uVar3 == 0x73) {
                uVar3 = *puVar5;
                puVar4 = (undefined *)&DAT_080371a4;
                goto LAB_080370fe;
            }
            if (uVar3 == 0x74) {
                puVar6 = (uint *)(((int)puVar6 + 0xfU & 0xfffffff8) + 8);
                uVar3 = snprintf_buf((char *)auStack_130, 0x100, (const char *)&DAT_080371ac);
                goto LAB_08037120;
            }
LAB_08037124:
            uVar2 = 1;
            goto LAB_0803715c;
        }
        puVar4 = (undefined *)&DAT_080371b4;
        uVar3 = *puVar5 & 0xff;
LAB_080370fe:
        puVar6 = puVar6 + 3;
        uVar3 = snprintf_buf((char *)auStack_130, 0x100, (const char *)puVar4, uVar3);
LAB_08037120:
        if (0xff < uVar3) goto LAB_08037124;
        FUN_0803918c((int)&DAT_08055f18, uVar2, (uint)auStack_130, 0, 0, 0);
        iVar7 = iVar7 + 1;
    } while (true);
}

/* orig: 0x080371b8 FUN_080371b8 — flush XML writer to USB */
uint FUN_080371b8(param_1, param_2)
uint param_1; uint param_2;
{
    uint uVar1;
    uVar1 = FUN_08038c24(DAT_08055f18, param_2, DAT_08055f28, DAT_08055f2c);
    FUN_08039234((int)&DAT_08055f18);
    return uVar1;
}

/* orig: 0x0803725c FUN_0803725c — find and replace in string buffer */
uint FUN_0803725c(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
    int iVar1;
    uint uVar2;
    uint uVar3;
    int iVar4;

    if (((param_1 != 0) && (param_2 != 0)) && (param_3 != 0)) {
        iVar1 = strlen((char *)param_1);
        uVar2 = strlen((char *)param_2);
        uVar3 = strlen((char *)param_3);
        if (uVar3 <= uVar2) {
            iVar4 = param_1 + iVar1;
            while ((param_1 = (int)strstr((char *)param_1, (char *)param_2)), param_1 != 0) {
                FUN_08027bf8(param_1, iVar1, param_3, uVar3);
                param_1 = param_1 + uVar3;
                FUN_08027c12(param_1, iVar1, (uVar2 - uVar3) + param_1, iVar4 - param_1);
            }
            return 1;
        }
    }
    return 0;
}
