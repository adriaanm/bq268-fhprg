/* Auto-generated: fhprg_802b5a8.c */
/* Functions: 22 */
#include "globals.h"

/* 0x0802b5a8 */
undefined4 thunk_FUN_0802b5a8()
{
  FUN_0802d61a();
  FUN_0802b5b8();
  return 0;
}




/* 0x0802b5a8 */
undefined4 FUN_0802b5a8()
{
  FUN_0802d61a();
  FUN_0802b5b8();
  return 0;
}




/* 0x0802b5b8 */
uint FUN_0802b5b8()
{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = FUN_0800bb1c();
  if ((iVar3 != 0xf) && (iVar3 = FUN_0800bb1c(), iVar3 != 0x10)) {
    DAT_0804dbfc = 0;
    DAT_0804dbfd = 0;
    DAT_0804dc00 = 0;
    DAT_0804dbb8 = FUN_0802e86c(0x2b);
    DAT_0804dbb4 = &DAT_0804dbbc;
    uVar1 = pm_charge_init();
    uVar2 = FUN_0802aa1c();
    if ((uVar2 | uVar1) != 0) {
      FUN_08015a50();
    }
    return uVar2 | uVar1;
  }
  return 0;
}




/* 0x0802b5d8 */
undefined4 FUN_0802b5d8()
{
  return 2;
}




/* 0x0802b5dc */
undefined4 FUN_0802b5dc(param_1, param_2)
uint param_1; int param_2;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  if ((((param_2 != 0) && (param_1 < 7)) && (DAT_0804dc08 != '\0')) &&
     (iVar1 = param_1 * 0x30, *(int *)(&DAT_08058490 + iVar1) == 4)) {
    thunk_FUN_08027bf8(param_2,0xc,iVar1 + 0x8058494);
    *(undefined4 *)(param_2 + 0xc) = *(undefined4 *)(&DAT_080584a0 + iVar1);
    *(undefined4 *)(param_2 + 0x10) = *(undefined4 *)(&DAT_080584a4 + iVar1);
    *(undefined4 *)(param_2 + 0x14) = *(undefined4 *)(&DAT_080584a8 + iVar1);
    *(undefined4 *)(param_2 + 0x18) = *(undefined4 *)(&DAT_080584ac + iVar1);
    *(undefined4 *)(param_2 + 0x1c) = *(undefined4 *)(&DAT_080584b0 + iVar1);
    *(undefined4 *)(param_2 + 0x20) = *(undefined4 *)(&DAT_080584b4 + iVar1);
    *(undefined4 *)(param_2 + 0x24) = *(undefined4 *)(&DAT_080584b8 + iVar1);
    uVar4 = *(uint *)(param_2 + 0x28);
    uVar2 = *(uint *)(&DAT_080584bc + iVar1) & 0xf;
    *(uint *)(param_2 + 0x28) = uVar4 & 0xfffffff0 | uVar2;
    uVar3 = ((uint)(*(int *)(&DAT_080584bc + iVar1) << 0x19) >> 0x1d) << 4;
    *(uint *)(param_2 + 0x28) = uVar4 & 0xffffff80 | uVar2 | uVar3;
    *(uint *)(param_2 + 0x28) =
         uVar4 & 0xffffff00 | uVar2 | uVar3 |
         ((uint)(*(int *)(&DAT_080584bc + iVar1) << 0x18) >> 0x1f) << 7;
    return 0;
  }
  return 0x16;
}




/* 0x0802b658 */
undefined4 FUN_0802b658(param_1, param_2)
uint param_1; undefined4 * param_2;
{
  if (((param_2 != (undefined4 *)0x0) && (DAT_0804dc30 != '\0')) && (param_1 < 7)) {
    *param_2 = (&DAT_08058634)[param_1 * 3];
    param_2[1] = (&DAT_08058638)[param_1 * 3];
    param_2[2] = (&DAT_0805863c)[param_1 * 3];
    return 0;
  }
  return 0x16;
}




/* 0x0802b68c */
undefined4 FUN_0802b68c(param_1)
uint param_1;
{
  if ((DAT_0804dc30 != '\0') && (param_1 < 7)) {
    return (&DAT_08058634)[param_1 * 3];
  }
  return 0x7fffffff;
}




/* 0x0802b6b4 */
undefined4 FUN_0802b6b4(param_1, param_2, param_3)
uint param_1; uint param_2; uint * param_3;
{
  int iVar1;
  
  if (((param_3 == (uint *)0x0) || (DAT_0804dc30 == '\0')) || (1 < param_2)) {
    return 0x16;
  }
  if (param_1 == 7) {
    *param_3 = param_2 + 0xe;
  }
  else {
    if (6 < param_1) {
      return 0x16;
    }
    iVar1 = (&DAT_080586a4)[param_1];
    *param_3 = iVar1 + param_2;
    if (0xd < iVar1 + param_2) {
      return 0x16;
    }
  }
  return 0;
}




/* 0x0802b878 */
undefined4 FUN_0802b878(param_1, param_2, param_3, param_4)
undefined4 param_1; uint param_2; byte * param_3; byte * param_4;
{
  undefined4 *puVar1;
  undefined4 uVar2;
  ushort *puVar3;
  uint local_18;
  
  local_18 = (uint)param_4 & 0xffffff00;
  puVar1 = (undefined4 *)FUN_0802be90();
  puVar3 = (ushort *)puVar1[1];
  if (puVar1 == (undefined4 *)0x0) {
    return 0x16;
  }
  if (*(byte *)(puVar1 + 2) <= param_2) {
    return 0x79;
  }
  if (param_3 != (byte *)0x0) {
    uVar2 = FUN_0802b1e8(*(undefined4 *)*puVar1,
                         param_2 * puVar3[1] + 0x200 + (uint)*puVar3 + (uint)puVar3[0x11] & 0xffff,
                         &local_18,0);
    *param_3 = (byte)local_18 >> 7;
    *param_4 = (byte)((local_18 << 0x1f) >> 0x1f);
    return uVar2;
  }
  return 0x73;
}




/* 0x0802b8d4 */
uint FUN_0802b8d4(param_1, param_2, param_3, param_4)
undefined4 param_1; uint param_2; byte * param_3; uint param_4;
{
  undefined4 *puVar1;
  ushort *puVar2;
  uint uVar3;
  uint uVar4;
  uint local_18;
  
  local_18 = param_4 & 0xffffff00;
  puVar1 = (undefined4 *)FUN_0802be90();
  puVar2 = (ushort *)puVar1[1];
  if (puVar1 == (undefined4 *)0x0) {
    return 0x16;
  }
  if (param_2 < *(byte *)(puVar1 + 2)) {
    if (param_3 == (byte *)0x0) {
      return 0x73;
    }
    uVar4 = FUN_0802b1e8(*(undefined4 *)*puVar1,
                         puVar2[1] * param_2 + 0x300 + (uint)*puVar2 + (uint)puVar2[0x12] & 0xffff,
                         &local_18,0);
    *param_3 = (byte)local_18 >> 7;
  }
  else {
    uVar4 = 0x79;
  }
  if (*param_3 == 0) {
    uVar3 = FUN_0802b1e8(*(undefined4 *)*puVar1,0x810,&local_18,0);
    uVar4 = uVar4 | uVar3;
    if (uVar4 == 0) {
      *param_3 = (byte)((local_18 << 0x1d) >> 0x1f);
    }
    if (*param_3 == 1) {
      thunk_FUN_080199b4(50000);
      uVar3 = FUN_0802b1e8(*(undefined4 *)*puVar1,0x810,&local_18,0);
      uVar4 = uVar4 | uVar3;
      if (uVar4 == 0) {
        *param_3 = (byte)((local_18 << 0x1d) >> 0x1f);
      }
    }
  }
  return uVar4;
}




/* 0x0802b97c */
undefined4 FUN_0802b97c(param_1, param_2, param_3, param_4)
undefined4 param_1; uint param_2; byte * param_3; uint param_4;
{
  undefined4 *puVar1;
  undefined4 uVar2;
  ushort *puVar3;
  uint local_10;
  
  local_10 = param_4 & 0xffffff00;
  puVar1 = (undefined4 *)FUN_0802be90();
  puVar3 = (ushort *)puVar1[1];
  if (puVar1 == (undefined4 *)0x0) {
    return 0x16;
  }
  if (*(byte *)(puVar1 + 2) <= param_2) {
    return 0x79;
  }
  if (param_3 != (byte *)0x0) {
    uVar2 = FUN_0802b1e8(*(undefined4 *)*puVar1,
                         puVar3[1] * param_2 + (uint)*puVar3 + (uint)puVar3[2] & 0xffff,&local_10,0)
    ;
    *param_3 = (byte)local_10 >> 7;
    return uVar2;
  }
  return 0x73;
}




/* 0x0802b9c8 */
undefined4 FUN_0802b9c8(param_1, param_2, param_3, param_4)
undefined4 param_1; uint param_2; byte * param_3; uint param_4;
{
  undefined4 *puVar1;
  undefined4 uVar2;
  ushort *puVar3;
  uint local_10;
  
  local_10 = param_4 & 0xffffff00;
  puVar1 = (undefined4 *)FUN_0802be90();
  puVar3 = (ushort *)puVar1[1];
  if (puVar1 == (undefined4 *)0x0) {
    return 0x16;
  }
  if (*(byte *)(puVar1 + 2) <= param_2) {
    return 0x79;
  }
  if (param_3 != (byte *)0x0) {
    uVar2 = FUN_0802b1e8(*(undefined4 *)*puVar1,
                         param_2 * puVar3[1] + 0x300 + (uint)*puVar3 + (uint)puVar3[0x12] & 0xffff,
                         &local_10,0);
    *param_3 = (byte)((local_10 << 0x1a) >> 0x1f);
    return uVar2;
  }
  return 0x73;
}




/* 0x0802ba1a */
undefined4 FUN_0802ba1a(param_1, param_2, param_3, param_4)
undefined4 param_1; uint param_2; char * param_3; uint param_4;
{
  undefined4 *puVar1;
  undefined4 uVar2;
  ushort *puVar3;
  uint local_10;
  
  local_10 = param_4 & 0xffffff00;
  puVar1 = (undefined4 *)FUN_0802be90();
  puVar3 = (ushort *)puVar1[1];
  if (puVar1 == (undefined4 *)0x0) {
    return 0x16;
  }
  if (*(byte *)(puVar1 + 2) <= param_2) {
    return 0x79;
  }
  uVar2 = FUN_0802b1e8(*(undefined4 *)*puVar1,
                       param_2 * puVar3[1] + 0x300 + (uint)*puVar3 + (uint)puVar3[0x14] & 0xffff,
                       &local_10,0);
  *param_3 = (char)((int)(local_10 << 0x1f) >> 0x1f) + '\x01';
  return uVar2;
}




/* 0x0802baa0 */
uint FUN_0802baa0(param_1, param_2, param_3, param_4)
undefined4 param_1; uint param_2; uint param_3; uint param_4;
{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  undefined4 *puVar6;
  ushort *puVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  
  puVar6 = (undefined4 *)FUN_0802be90();
  puVar7 = (ushort *)puVar6[1];
  uVar1 = puVar7[1];
  uVar2 = *puVar7;
  uVar3 = puVar7[10];
  uVar4 = puVar7[0xb];
  if (puVar6 == (undefined4 *)0x0) {
    uVar8 = 0x16;
  }
  else if (param_2 < *(byte *)(puVar6 + 2)) {
    iVar9 = FUN_0802e86c(0x2b);
    if (iVar9 == 0) {
      uVar8 = 0x73;
    }
    else if ((param_3 < *(ushort *)(iVar9 + 0x26)) || (*(ushort *)(iVar9 + 0x28) < param_3)) {
      uVar8 = 0xe;
    }
    else {
      uVar5 = *(ushort *)(iVar9 + 0x2a);
      if ((param_4 < uVar5) || (*(ushort *)(iVar9 + 0x2c) < param_4)) {
        uVar8 = 0xf;
      }
      else {
        uVar10 = FUN_0802b282(*(undefined4 *)*puVar6,
                              (uint)uVar2 + (uint)uVar3 + uVar1 * param_2 & 0xffff,0x1f,
                              ((param_3 - *(ushort *)(iVar9 + 0x26)) * 100 + 100) / 0x61a & 0xff,0);
        uVar8 = FUN_0802b282(*(undefined4 *)*puVar6,
                             (uint)uVar4 + (uint)uVar2 + uVar1 * param_2 & 0xffff,0x1f,
                             ((param_4 - uVar5) * 100 + 100) / 0x753 & 0xff,0);
        uVar8 = uVar8 | uVar10;
      }
    }
  }
  else {
    uVar8 = 0x79;
  }
  return uVar8;
}




/* 0x0802bb6a */
undefined4 FUN_0802bb6a(param_1, param_2)
undefined4 param_1; uint param_2;
{
  undefined4 *puVar1;
  undefined4 uVar2;
  ushort *puVar3;
  
  puVar1 = (undefined4 *)FUN_0802be90();
  puVar3 = (ushort *)puVar1[1];
  if (puVar1 == (undefined4 *)0x0) {
    return 0x16;
  }
  if (*(byte *)(puVar1 + 2) <= param_2) {
    return 0x79;
  }
  uVar2 = FUN_0802b282(*(undefined4 *)*puVar1,
                       param_2 * puVar3[1] + 0x600 + (uint)*puVar3 + (uint)puVar3[0x15] & 0xffff,
                       0x80,0x80,0);
  return uVar2;
}




/* 0x0802bba8 */
uint FUN_0802bba8(param_1, param_2, param_3)
undefined4 param_1; short param_2; int param_3;
{
  short sVar1;
  short sVar2;
  short sVar3;
  undefined4 *puVar4;
  short *psVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  
  puVar4 = (undefined4 *)FUN_0802be90();
  psVar5 = (short *)puVar4[1];
  sVar1 = psVar5[1];
  sVar2 = *psVar5;
  sVar3 = psVar5[0x10];
  if (puVar4 == (undefined4 *)0x0) {
    uVar7 = 0x16;
  }
  else {
    uVar6 = FUN_0802b282(*(undefined4 *)*puVar4,psVar5[0xf] + sVar2 + sVar1 * param_2,0xff,0xa5,0);
    if (param_3 == 0) {
      uVar8 = 0;
    }
    else {
      uVar8 = 0x20;
    }
    uVar7 = FUN_0802b282(*(undefined4 *)*puVar4,sVar3 + sVar2 + sVar1 * param_2,0xff,uVar8,0);
    uVar7 = uVar7 | uVar6;
  }
  return uVar7;
}




/* 0x0802bc08 */
undefined4 FUN_0802bc08(param_1, param_2, param_3)
undefined4 param_1; uint param_2; uint param_3;
{
  undefined4 *puVar1;
  undefined4 uVar2;
  ushort *puVar3;
  
  puVar1 = (undefined4 *)FUN_0802be90();
  puVar3 = (ushort *)puVar1[1];
  if (puVar1 == (undefined4 *)0x0) {
    return 0x16;
  }
  if (*(byte *)(puVar1 + 2) <= param_2) {
    return 0x79;
  }
  uVar2 = FUN_0802b282(*(undefined4 *)*puVar1,
                       puVar3[1] * param_2 + (uint)*puVar3 + (uint)puVar3[0xc] & 0xffff,0xf,
                       param_3 / 0x5a - 1 & 0xff,0);
  return uVar2;
}




/* 0x0802bc4c */
undefined4 FUN_0802bc4c(param_1, param_2, param_3)
undefined4 param_1; uint param_2; uint param_3;
{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  undefined4 *puVar4;
  ushort *puVar5;
  int iVar6;
  undefined4 uVar7;
  
  puVar4 = (undefined4 *)FUN_0802be90();
  puVar5 = (ushort *)puVar4[1];
  uVar1 = *puVar5;
  uVar2 = puVar5[5];
  uVar3 = puVar5[1];
  if (puVar4 == (undefined4 *)0x0) {
    return 0x16;
  }
  if (*(byte *)(puVar4 + 2) <= param_2) {
    return 0x79;
  }
  iVar6 = FUN_0802e86c(0x2b);
  if (iVar6 == 0) {
    return 0x73;
  }
  if ((param_3 <= *(ushort *)(iVar6 + 0x1c)) && (*(ushort *)(iVar6 + 0x1e) <= param_3)) {
    uVar7 = FUN_0802b282(*(undefined4 *)*puVar4,uVar3 * param_2 + (uint)uVar1 + (uint)uVar2 & 0xffff
                         ,0xf,(param_3 - *(ushort *)(iVar6 + 0x1e)) /
                              (uint)*(ushort *)(iVar6 + 0x20) & 0xff,0);
    return uVar7;
  }
  return 0xe;
}




/* 0x0802bcb0 */
undefined4 FUN_0802bcb0(param_1, param_2, param_3)
undefined4 param_1; uint param_2; uint param_3;
{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  undefined4 *puVar4;
  ushort *puVar5;
  int iVar6;
  undefined4 uVar7;
  
  puVar4 = (undefined4 *)FUN_0802be90();
  puVar5 = (ushort *)puVar4[1];
  uVar1 = *puVar5;
  uVar2 = puVar5[6];
  uVar3 = puVar5[1];
  if (puVar4 == (undefined4 *)0x0) {
    return 0x16;
  }
  if (*(byte *)(puVar4 + 2) <= param_2) {
    return 0x79;
  }
  iVar6 = FUN_0802e86c(0x2b);
  if (iVar6 == 0) {
    return 0x73;
  }
  if ((param_3 <= *(ushort *)(iVar6 + 0x1c)) && (*(ushort *)(iVar6 + 0x1e) <= param_3)) {
    uVar7 = FUN_0802b282(*(undefined4 *)*puVar4,uVar3 * param_2 + (uint)uVar1 + (uint)uVar2 & 0xffff
                         ,0xf,(param_3 - *(ushort *)(iVar6 + 0x1e)) /
                              (uint)*(ushort *)(iVar6 + 0x20) & 0xff,0);
    return uVar7;
  }
  return 0xe;
}




/* 0x0802bd14 */
undefined4 FUN_0802bd14(param_1, param_2, param_3)
undefined4 param_1; uint param_2; uint param_3;
{
  undefined4 *puVar1;
  undefined4 uVar2;
  ushort *puVar3;
  undefined4 uVar4;
  
  puVar1 = (undefined4 *)FUN_0802be90();
  puVar3 = (ushort *)puVar1[1];
  if (puVar1 == (undefined4 *)0x0) {
    return 0x16;
  }
  if (param_2 < *(byte *)(puVar1 + 2)) {
    if (1 < param_3) {
      return 0xe;
    }
    if (param_3 == 0) {
      uVar4 = 1;
      uVar2 = *(undefined4 *)*puVar1;
    }
    else {
      if (param_3 != 1) {
        return 0xe;
      }
      uVar4 = 0x80;
      uVar2 = *(undefined4 *)*puVar1;
    }
    uVar2 = FUN_0802b282(uVar2,puVar3[1] * param_2 + (uint)*puVar3 + (uint)puVar3[8] & 0xffff,0x81,
                         uVar4,0);
    return uVar2;
  }
  return 0x79;
}




/* 0x0802bd68 */
undefined4 FUN_0802bd68(param_1, param_2, param_3)
undefined4 param_1; uint param_2; int param_3;
{
  undefined4 *puVar1;
  undefined4 uVar2;
  ushort *puVar3;
  
  puVar1 = (undefined4 *)FUN_0802be90();
  puVar3 = (ushort *)puVar1[1];
  if (*(byte *)(puVar1 + 2) <= param_2) {
    return 0x79;
  }
  if (0x345 < param_3 - 0x1068U) {
    return 0xe;
  }
  uVar2 = FUN_0802b282(*(undefined4 *)*puVar1,
                       puVar3[1] * param_2 + (uint)*puVar3 + (uint)puVar3[7] & 0xffff,0x1f,
                       (param_3 - 0x1068U) / 0x1b & 0xff,0);
  return uVar2;
}




/* 0x0802bdb6 */
undefined4 FUN_0802bdb6(param_1, param_2)
undefined4 param_1; uint param_2;
{
  undefined4 *puVar1;
  undefined4 uVar2;
  ushort *puVar3;
  
  puVar1 = (undefined4 *)FUN_0802be90();
  puVar3 = (ushort *)puVar1[1];
  if (puVar1 == (undefined4 *)0x0) {
    return 0x16;
  }
  if (*(byte *)(puVar1 + 2) <= param_2) {
    return 0x79;
  }
  uVar2 = FUN_0802b282(*(undefined4 *)*puVar1,
                       param_2 * puVar3[1] + 0x300 + (uint)*puVar3 + (uint)puVar3[0x14] & 0xffff,1,1
                       ,0);
  return uVar2;
}




