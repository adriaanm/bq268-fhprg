/* protocol.c — Firehose protocol: logging, response building, attribute parsing.
 *
 * Source: src/fhprg/fhprg_8026f54.c
 */
#include "firehose.h"

/* orig: 0x08027674 firehose_log — format message and send as XML log element */
void firehose_log(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; uint param_3; uint param_4;
{
    int iVar1;
    uint uVar2;
    undefined1 auStack_128[256];
    int local_28;
    uint uStack_c;
    uint uStack_8;
    uint uStack_4;

    iVar1 = DAT_0804cd58;
    local_28 = DAT_0804cd58;
    uStack_c = param_2;
    uStack_8 = param_3;
    uStack_4 = param_4;
    FUN_08006d14(auStack_128, 0x100);
    FUN_08006418((char *)auStack_128, 0x100, (const char *)param_1, (va_list *)&uStack_c);
    uVar2 = FUN_08006906("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>");
    FUN_080391f0((int *)&DAT_08055f18, (uint)"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>", uVar2, 0);
    FUN_08039100((uint)&DAT_08055f18, (uint)&DAT_08027710);
    FUN_080390f4((uint)&DAT_08055f18, (uint)&DAT_08027718);
    FUN_0803918c((int)&DAT_08055f18, (uint)"value", (uint)auStack_128, 0, 0, 0);
    FUN_080390d8((uint)&DAT_08055f18);
    FUN_080390e4((uint)&DAT_08055f18, (uint)&DAT_08027710);
    FUN_080371b8(0, 0);
    if (local_28 != iVar1) {
        FUN_08010960();
    }
}

/* orig: 0x08027bf8 FUN_08027bf8 — bounded memcpy (truncates to dst size) */
uint FUN_08027bf8(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; uint param_3; uint param_4;
{
    if (param_2 <= param_4) {
        param_4 = param_2;
    }
    memcpy((void *)param_1, (void *)param_3, param_4);
    return param_4;
}

/* orig: 0x08027c12 FUN_08027c12 — bounded memcpy (no truncation variant) */
uint FUN_08027c12(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; uint param_3; uint param_4;
{
    if (param_2 <= param_4) {
        param_4 = param_2;
    }
    memmove((void *)param_1, (void *)param_3, param_4);
    return param_4;
}

/* orig: 0x080287e2 FUN_080287e2 — memset wrapper */
void FUN_080287e2(param_1, param_2, param_3)
uint param_1; uint param_2; uint param_3;
{
    memset((void *)param_1, (int)param_2, param_3);
}

/* orig: 0x08028810 FUN_08028810 — attribute parser stub */
void FUN_08028810(param_1, param_2)
uint param_1; uint param_2;
{
    /* Attribute parsing — called from dispatch, details TBD */
}

/* orig: 0x080288b0 FUN_080288b0 — attribute parser stub */
void FUN_080288b0(param_1, param_2)
uint param_1; uint param_2;
{
    /* Attribute parsing — called from dispatch, details TBD */
}

/* orig: 0x08028c10 FUN_08028c10 — parse sector number stub */
uint FUN_08028c10()
{
    /* Parse sector number from XML attributes — details TBD */
    return 0;
}
