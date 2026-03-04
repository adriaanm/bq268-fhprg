/* Auto-generated: fhprg_801d840.c */
/* Functions: 13 */
#include "globals.h"

/* 0x0801d840 */
undefined4 FUN_0801d840(param_1)
int param_1;
{
  byte bVar1;
  undefined4 uVar2;
  
  bVar1 = *(byte *)(param_1 + 0x14);
  uVar2 = (**(code **)(*(int *)(param_1 + 0x10) + 4))(param_1 + 0x14);
  FUN_08020684(bVar1 - 0x61);
  FUN_08025d64();
  return uVar2;
}




/* 0x0801d85e */
void FUN_0801d85e(param_1, param_2)
int * param_1; undefined4 param_2;
{
  int iVar1;
  int iVar2;
  
  iVar2 = *param_1;
  iVar1 = FUN_0801d708(param_1,2);
  if (-1 < iVar1) {
                    /* WARNING: Could not recover jumptable at 0x0801d87e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(int *)(iVar2 + 0x10) + 0x4c))(param_1[0x55],param_2);
    return;
  }
  return;
}




/* 0x0801d882 */
undefined4 FUN_0801d882(param_1)
int param_1;
{
  undefined4 uVar1;
  
  uVar1 = (**(code **)(*(int *)(**(int **)(param_1 + 0xc) + 0x10) + 0x34))
                    (*(int *)(param_1 + 0x10) + 0x24);
  FUN_08021c68(*(undefined4 *)(param_1 + 0x10));
  *(undefined4 *)(param_1 + 0x10) = 0;
  return uVar1;
}




/* 0x0801d8ae */
void FUN_0801d8ae(param_1, param_2)
int param_1; int param_2;
{
  if (*(int *)(param_2 + 0x158) != 0) {
    (**(code **)(*(int *)(param_1 + 0x10) + 0x28))(*(undefined4 *)(param_2 + 0x154));
    *(undefined4 *)(param_2 + 0x158) = 0;
    *(undefined4 *)(param_2 + 0x154) = 0xffffffff;
  }
  return;
}




/* 0x0801d8d2 */
void FUN_0801d8d2(param_1, param_2, param_3, param_4, param_5)
int * param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4; undefined4 param_5;
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *param_1;
  iVar1 = FUN_0801d708(param_1,2);
  if (-1 < iVar1) {
    iVar3 = param_1[0x55];
    iVar1 = (**(code **)(*(int *)(iVar2 + 0x10) + 0x18))(iVar3,param_2,param_5);
    if (-1 < iVar1) {
                    /* WARNING: Could not recover jumptable at 0x0801d910. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*(int *)(iVar2 + 0x10) + 0x20))(iVar3,param_3,param_4);
      return;
    }
  }
  return;
}




/* 0x0801d916 */
undefined4 FUN_0801d916()
{
  FUN_08015a50();
  return 0xfffffffb;
}




/* 0x0801d922 */
undefined4 FUN_0801d922(param_1)
undefined4 * param_1;
{
  *param_1 = 0;
  return 0;
}




/* 0x0801d92a */
undefined4 FUN_0801d92a(param_1)
undefined4 * param_1;
{
  *param_1 = 0;
  return 0;
}




/* 0x0801d932 */
undefined4 FUN_0801d932(param_1)
int * param_1;
{
  if (*param_1 != 0) {
    return 1;
  }
  *param_1 = 1;
  return 0;
}




/* 0x0801d942 */
undefined4 FUN_0801d942(param_1)
undefined4 * param_1;
{
  *param_1 = 0;
  return 0;
}




/* 0x0801d94c */
undefined4 FUN_0801d94c(param_1)
uint param_1;
{
  if (7 < param_1) {
    FUN_08015a50();
  }
  return (&DAT_87c2accc)[param_1];
}




/* 0x0801d964 */
void FUN_0801d964(param_1, param_2, param_3, param_4)
undefined1 * param_1; uint param_2; int param_3; int param_4;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = (param_2 - 1) * 0xd;
  FUN_08006cc0(param_1,0x20,0xff);
  if (*(byte *)(param_3 + 0x20a) == param_2) {
    param_2 = param_2 + 0x40;
  }
  *param_1 = (char)param_2;
  uVar3 = uVar4 + 0xd;
  param_1[0xd] = *(undefined1 *)(param_3 + 0x20b);
  param_1[0xb] = 0xf;
  param_1[0xc] = 0;
  param_1[0x1a] = 0;
  param_1[0x1b] = 0;
  iVar1 = 1;
  for (; (uVar4 < uVar3 && (uVar4 <= *(uint *)(param_3 + 0x214))); uVar4 = uVar4 + 1) {
    iVar2 = param_4 + uVar4 * 2;
    param_1[iVar1] = (char)*(undefined2 *)(iVar2 + 0x204);
    param_1[iVar1 + 1] = (char)((ushort)*(undefined2 *)(iVar2 + 0x204) >> 8);
    iVar1 = iVar1 + 2;
    if (iVar1 == 0xb) {
      iVar1 = 0xe;
    }
    else if (iVar1 == 0x1a) {
      iVar1 = 0x1c;
    }
  }
  return;
}




/* 0x0801d9e0 */
int FUN_0801d9e0(param_1, param_2)
int param_1; uint param_2;
{
  uint uVar1;
  int iVar2;
  
  if (0x3fffffe < param_2) {
    return -2;
  }
  while( true ) {
    if (param_2 == 0) {
      return -1;
    }
    if (*(int *)(param_1 + param_2 * 4 + -4) != 0) break;
    param_2 = param_2 - 1;
  }
  iVar2 = 0;
  uVar1 = *(uint *)(param_1 + param_2 * 4 + -4);
  if (uVar1 >> 0x10 == 0) {
    uVar1 = uVar1 << 0x10;
    iVar2 = 0x10;
  }
  if (uVar1 >> 0x18 == 0) {
    uVar1 = uVar1 << 8;
    iVar2 = iVar2 + 8;
  }
  if (uVar1 >> 0x1c == 0) {
    uVar1 = uVar1 << 4;
    iVar2 = iVar2 + 4;
  }
  if (uVar1 >> 0x1e == 0) {
    uVar1 = uVar1 << 2;
    iVar2 = iVar2 + 2;
  }
  if (-1 < (int)uVar1) {
    iVar2 = iVar2 + 1;
  }
  return (param_2 * 0x20 - iVar2) + -1;
}




