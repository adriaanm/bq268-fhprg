/* Auto-generated: fhprg_801bd00.c */
/* Functions: 13 */
#include "globals.h"

/* 0x0801bd00 */
void FUN_0801bd00(param_1)
undefined4 param_1;
{
  undefined4 uVar1;
  int iVar2;
  int extraout_r2;
  int iVar3;
  int unaff_r4 = 0;
  undefined1 *puVar4;
  int unaff_r5 = 0;
  int unaff_r6 = 0;
  int unaff_r7 = 0;
  char in_CY = 0;
  undefined1 auStack_114 [256];
  int iStack_14;
  undefined4 uStack_c;
  
  DAT_0804d260 = param_1;
  FUN_0801be0c();
  FUN_0801bd14();
  uVar1 = FUN_08027724();
  iVar3 = DAT_0804cd58;
  if (in_CY != '\0') {
    *(undefined4 *)(unaff_r4 + 0x30) = uVar1;
    puVar4 = *(undefined1 **)(unaff_r5 + 0x74);
    *(int *)(unaff_r7 + 0x60) = extraout_r2;
    *(char *)(unaff_r5 + 0x11) = (char)*(undefined4 *)(unaff_r5 + 100);
    *puVar4 = 0x6c;
    iVar2 = *(int *)(unaff_r5 + 0x14);
    iVar3 = extraout_r2 + -99;
    *(int *)(puVar4 + 0x14) = unaff_r6;
    *(char *)(iVar2 + 0x11) = (char)*(undefined4 *)(iVar2 + 100);
    puVar4[0xc] = (char)puVar4;
    *(int *)(unaff_r6 + 0x14) = iVar3;
    *(int *)(*(int *)(unaff_r6 + 0x74) + 0x54) = unaff_r7;
    *(int *)(unaff_r7 + 0x60) = iVar3;
    FUN_08006cd0(0x87c70000,0x6f600,iVar3,0xd8);
    return;
  }
  uStack_c = 0;
  iStack_14 = DAT_0804cd58;
  FUN_08006d14(auStack_114,0x100);
  FUN_08027274();
  iVar2 = FUN_0800aa60(1);
  if (iVar2 == 0) {
    FUN_08038282(auStack_114,&DAT_0801bdd0,0x100);
  }
  FUN_08006840(0x1f,0x801bde4);
  iVar2 = FUN_0802d044();
  if (iVar2 != 0) {
    FUN_08038282(auStack_114,0x801bde8,0x100);
  }
  iVar2 = FUN_08027314();
  if (iVar2 == 0) {
    FUN_08038282(auStack_114,0x801bdf8,0x100);
  }
  iVar2 = FUN_0800aa60(3);
  if (iVar2 == 0) {
    FUN_08038282(auStack_114,&DAT_0801bdd0,0x100);
  }
  FUN_0802d228(0,0,0x388,500,1);
  FUN_0802d3d0(0,0,1);
  FUN_08027320();
  iVar2 = FUN_08006906(auStack_114);
  if (iVar2 != 0) {
    do {
      firehose_log(auStack_114);
      FUN_0801b85c(2);
    } while( true );
  }
  if (iStack_14 != iVar3) {
    FUN_08010960();
    return;
  }
  return;
}




/* 0x0801bd14 */
void FUN_0801bd14()
{
  int iVar1;
  int iVar2;
  undefined1 auStack_114 [256];
  int local_14;
  
  iVar1 = DAT_0804cd58;
  local_14 = DAT_0804cd58;
  FUN_08006d14(auStack_114,0x100);
  FUN_08027274();
  iVar2 = FUN_0800aa60(1);
  if (iVar2 == 0) {
    FUN_08038282(auStack_114,&DAT_0801bdd0,0x100);
  }
  FUN_08006840(0x1f,0x801bde4);
  iVar2 = FUN_0802d044();
  if (iVar2 != 0) {
    FUN_08038282(auStack_114,0x801bde8,0x100);
  }
  iVar2 = FUN_08027314();
  if (iVar2 == 0) {
    FUN_08038282(auStack_114,0x801bdf8,0x100);
  }
  iVar2 = FUN_0800aa60(3);
  if (iVar2 == 0) {
    FUN_08038282(auStack_114,&DAT_0801bdd0,0x100);
  }
  FUN_0802d228(0,0,0x388,500,1);
  FUN_0802d3d0(0,0,1);
  FUN_08027320();
  iVar2 = FUN_08006906(auStack_114);
  if (iVar2 != 0) {
    do {
      firehose_log(auStack_114);
      FUN_0801b85c(2);
    } while( true );
  }
  if (local_14 != iVar1) {
    FUN_08010960();
    return;
  }
  return;
}




/* 0x0801be0c */
void FUN_0801be0c()
{
  FUN_08006cd0(0x87c70000,0x6f600);
  return;
}




/* 0x0801be1c */
undefined4 FUN_0801be1c(param_1, param_2, param_3)
uint * param_1; uint * param_2; uint * param_3;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar5 = param_2[2];
  uVar2 = param_3[1];
  if ((uVar2 <= uVar5) && ((uVar5 != uVar2 || (*param_3 <= param_2[1])))) {
    return 0xffffffff;
  }
  uVar1 = uVar5;
  if (uVar2 != 0xffffffff) {
    if (uVar2 == 0) {
      uVar2 = *param_3;
      if (uVar2 == 0) {
        return 0xffffffff;
      }
      uVar3 = *param_2;
      uVar1 = param_2[1];
    }
    else {
      if (uVar5 == uVar2) {
        uVar1 = 0xffffffff;
        goto LAB_0801be6e;
      }
      uVar3 = param_2[1];
    }
    uVar1 = FUN_080060c0(uVar3,uVar1,uVar2,0);
  }
LAB_0801be6e:
  uVar3 = *param_2;
  uVar2 = (uint)((ulonglong)uVar1 * (ulonglong)*param_3);
  uVar6 = (uint)((ulonglong)uVar1 * (ulonglong)*param_3 >> 0x20);
  *param_2 = uVar3 - uVar2;
  uVar2 = -(uint)(uVar3 < uVar2);
  uVar3 = uVar2 - uVar6;
  uVar4 = param_2[1] + uVar3;
  uVar7 = (uint)((ulonglong)uVar1 * (ulonglong)param_3[1]);
  uVar5 = uVar5 + ((((((int)uVar2 >> 0x1f) - (uint)(uVar2 < uVar6)) + (uint)CARRY4(param_2[1],uVar3)
                    ) - (uint)(uVar4 < uVar7)) -
                  (int)((ulonglong)uVar1 * (ulonglong)param_3[1] >> 0x20));
  param_2[1] = uVar4 - uVar7;
  param_2[2] = uVar5;
  if ((int)uVar5 < 0) {
    do {
      uVar5 = *param_2;
      uVar3 = *param_3;
      uVar1 = uVar1 - 1;
      *param_2 = uVar5 + uVar3;
      uVar2 = param_2[1];
      uVar5 = (uint)CARRY4(uVar5,uVar3);
      uVar4 = param_3[1];
      uVar3 = uVar2 + uVar4;
      param_2[1] = uVar3 + uVar5;
      uVar5 = param_2[2] + (uint)CARRY4(uVar2,uVar4) + (uint)CARRY4(uVar3,uVar5);
      param_2[2] = uVar5;
    } while (uVar5 != 0);
  }
  else {
    while (((uVar5 != 0 || (param_3[1] < param_2[1])) ||
           ((param_2[1] == param_3[1] && (*param_3 < *param_2))))) {
      uVar3 = *param_2;
      uVar2 = *param_3;
      uVar1 = uVar1 + 1;
      *param_2 = uVar3 - uVar2;
      uVar4 = param_2[1];
      uVar2 = -(uint)(uVar3 < uVar2);
      uVar6 = param_3[1];
      uVar3 = uVar4 - uVar6;
      param_2[1] = uVar3 + uVar2;
      uVar5 = uVar5 + ((((int)uVar2 >> 0x1f) + (uint)CARRY4(uVar3,uVar2)) - (uint)(uVar4 < uVar6));
      param_2[2] = uVar5;
    }
  }
  *param_1 = uVar1;
  return 0;
}




/* 0x0801bf34 */
void FUN_0801bf34(param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8)
undefined1 param_1; undefined4 param_2; uint param_3; undefined4 param_4; uint param_5; undefined4 param_6; undefined4 param_7; undefined4 param_8;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar2 = DAT_0804cd6c;
  uVar3 = FUN_08006906(param_7);
  uVar4 = FUN_08006906(param_8);
  if (((uVar3 < 0x14) && (uVar4 < 0x14)) && (uVar2 < 0x1a)) {
    iVar1 = uVar2 * 0x34;
    *(undefined1 *)(uVar2 * 0x34 + -0x7838de70) = param_1;
    *(uint *)(iVar1 + -0x7838de6c) = param_3 & 0xfffffffc;
    *(uint *)(iVar1 + -0x7838de68) = param_5 & 0xfffffffc;
    FUN_080382c2(iVar1 + -0x7838de64,param_7,0x14);
    FUN_080382c2(iVar1 + -0x7838de50,param_8,0x14);
    DAT_0804cd6c = DAT_0804cd6c + 1;
  }
  return;
}




/* 0x0801bfac */
void FUN_0801bfac(param_1, param_2, param_3, param_4)
uint param_1; undefined4 param_2; uint param_3; undefined4 param_4;
{
  int iVar1;
  
  if (DAT_0804cd70 < 0x1a) {
    iVar1 = DAT_0804cd70 * 0x10;
    DAT_0804cd70 = DAT_0804cd70 + 1;
    *(uint *)(iVar1 + -0x7838d928) = param_1 & 0xfffffffc;
    *(undefined4 *)(iVar1 + -0x7838d924) = param_2;
    *(uint *)(iVar1 + -0x7838d920) = param_3 & 0xfffffffc;
    *(undefined4 *)(iVar1 + -0x7838d91c) = param_4;
  }
  return;
}




/* 0x0801bfdc */
int FUN_0801bfdc(param_1)
uint param_1;
{
  if (param_1 < DAT_0804cd6c) {
    return param_1 * 0x34 + -0x7838de50;
  }
  return 0;
}




/* 0x0801c004 */
undefined8 FUN_0801c004(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  
  DAT_0804cd6c = 0;
  FUN_08007f08(0x87c72190,0,0x548,param_4,param_1,param_2,param_3,param_4);
  DAT_0804cd68 = 0;
  FUN_0801c2f8();
  iVar1 = snprintf_buf(0x87c71990,0x800,"; Build ID: %s\n","8909A-DAADANAZA-10139");
  iVar5 = 0x800 - iVar1;
  iVar2 = iVar5;
  if (iVar5 < 1) {
    iVar2 = 0;
  }
  iVar2 = snprintf_buf(iVar1 + -0x7838e670,iVar2,"; Time Stamp unavailable from boot loader.\n");
  iVar1 = iVar1 + -0x7838e670 + iVar2;
  iVar5 = iVar5 - iVar2;
  for (uVar6 = 0; uVar6 < DAT_0804cd6c; uVar6 = uVar6 + 1) {
    iVar4 = uVar6 * 0x34 + -0x7838de50;
    iVar2 = iVar5;
    if (iVar5 < 1) {
      iVar2 = 0;
    }
    iVar2 = snprintf_buf(iVar1,iVar2,"if OS.FILE(%s)\n(\n  d.load.binary %s 0x%lx /noclear\n)\n",
                         iVar4,iVar4,*(undefined4 *)(uVar6 * 0x34 + -0x7838de6c));
    iVar5 = iVar5 - iVar2;
    iVar1 = iVar1 + iVar2;
  }
  if (iVar5 < 1) {
    iVar5 = 0;
  }
  snprintf_buf(iVar1,iVar5,&DAT_0801c13c);
  uVar3 = FUN_08006906(0x87c71990);
  uVar7 = 0;
  FUN_0801bf34(2,0,0x87c71990,0,uVar3,0,"CMM Script","load.cmm");
  return CONCAT44(uVar7,uVar3);
}




/* 0x0801c158 */
undefined1 FUN_0801c158()
{
  undefined1 uVar1;
  
  uVar1 = thunk_FUN_08030c2c(&DAT_08051b90);
  return uVar1;
}




/* 0x0801c22c */
void FUN_0801c22c()
{
  DAT_0804cd68 = 1;
  return;
}




/* 0x0801c238 */
undefined4 FUN_0801c238(param_1)
uint param_1;
{
  undefined4 uVar1;
  
  if (param_1 < DAT_0804cd6c) {
    uVar1 = *(undefined4 *)(param_1 * 0x34 + -0x7838de6c);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}




/* 0x0801c260 */
undefined4 FUN_0801c260(param_1)
uint param_1;
{
  undefined4 uVar1;
  
  if (param_1 < DAT_0804cd6c) {
    uVar1 = *(undefined4 *)(param_1 * 0x34 + -0x7838de68);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}




/* 0x0801c288 */
undefined4 FUN_0801c288()
{
  return DAT_0804cd6c;
}




