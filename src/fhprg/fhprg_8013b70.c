/* Auto-generated: fhprg_8013b70.c */
/* Functions: 13 */
#include "globals.h"

/* 0x08013b70 */
undefined4 FUN_08013b70()
{
  return 3;
}




/* 0x08013b74 */
int FUN_08013b74(param_1, param_2)
uint param_1; int param_2;
{
  int iVar1;
  
  iVar1 = DAT_0804e2a0;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_2 + 8);
  }
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if ((false) || (*(int *)(iVar1 + 0x14) != 0xd00cafe)) break;
    if (((*(byte *)(iVar1 + 0xc) == param_1) || (param_1 == 8)) && (*(char *)(iVar1 + 0xd) == '\0'))
    {
      return iVar1;
    }
    iVar1 = *(int *)(iVar1 + 8);
  }
  return 0;
}




/* 0x08013bb0 */
undefined4 FUN_08013bb0(param_1)
int param_1;
{
  undefined4 uVar1;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x14) == 0xd00cafe)) {
                    /* WARNING: Could not recover jumptable at 0x08013bcc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*(int *)(param_1 + 4) + 0x28))();
    return uVar1;
  }
  return 0xffffffff;
}




/* 0x08013bd4 */
undefined4 FUN_08013bd4(param_1)
int param_1;
{
  undefined4 uVar1;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x14) == 0xd00cafe)) {
                    /* WARNING: Could not recover jumptable at 0x08013be6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*(int *)(param_1 + 4) + 0x30))();
    return uVar1;
  }
  return 0;
}




/* 0x08013bec */
undefined4 FUN_08013bec(param_1)
undefined4 * param_1;
{
  if ((param_1 != (undefined4 *)0x0) && (param_1[5] == 0xd00cafe)) {
    return *param_1;
  }
  return 0;
}




/* 0x08013c04 */
undefined1 FUN_08013c04(param_1)
int param_1;
{
  if ((param_1 != 0) && (*(int *)(param_1 + 0x14) == 0xd00cafe)) {
    return *(undefined1 *)(param_1 + 0xc);
  }
  return 0;
}




/* 0x08013c1c */
void FUN_08013c1c()
{
  int iVar1;
  uint in_r3 = 0;
  uint local_10;
  
  local_10 = in_r3 & 0xffff0000;
  DAT_0804e2a0 = 0;
  iVar1 = FUN_08013b70();
  for (iVar1 = iVar1 + -2; -1 < iVar1; iVar1 = iVar1 + -1) {
    (**(code **)(*(int *)(&DAT_08050ed0 + iVar1 * 4) + 8))(&DAT_0804e2a0,&local_10);
  }
  return;
}




/* 0x08013c4c */
undefined4 FUN_08013c4c(param_1)
int param_1;
{
  undefined4 uVar1;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x14) == 0xd00cafe)) {
                    /* WARNING: Could not recover jumptable at 0x08013c60. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*(int *)(param_1 + 4) + 0x38))();
    return uVar1;
  }
  return 0xffffffff;
}




/* 0x08013c68 */
undefined4 FUN_08013c68(param_1)
int param_1;
{
  undefined4 uVar1;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x14) == 0xd00cafe)) {
                    /* WARNING: Could not recover jumptable at 0x08013c7c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*(int *)(param_1 + 4) + 0x24))();
    return uVar1;
  }
  return 0xffffffff;
}




/* 0x08013c84 */
undefined4 FUN_08013c84(param_1)
int param_1;
{
  undefined4 uVar1;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x14) == 0xd00cafe)) {
                    /* WARNING: Could not recover jumptable at 0x08013c9e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = ((code *)**(undefined4 **)(param_1 + 4))();
    return uVar1;
  }
  return 0xffffffff;
}




/* 0x08013ca4 */
undefined4 FUN_08013ca4(param_1, param_2, param_3, param_4, param_5)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4; undefined4 param_5;
{
  undefined4 uVar1;
  
  if ((param_1 == 0) || (*(int *)(param_1 + 0x14) != 0xd00cafe)) {
    uVar1 = 0xffffffff;
  }
  else {
    FUN_08025eb4(0,param_5,param_3,param_4,param_4);
    uVar1 = (**(code **)(*(int *)(param_1 + 4) + 8))(param_1,param_2,param_3,param_4,param_5);
  }
  return uVar1;
}




/* 0x08013ce4 */
undefined4 FUN_08013ce4(param_1)
int param_1;
{
  undefined4 uVar1;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x14) == 0xd00cafe)) {
                    /* WARNING: Could not recover jumptable at 0x08013cf8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*(int *)(param_1 + 4) + 0x1c))();
    return uVar1;
  }
  return 0xffffffff;
}




/* 0x08013d44 */
void FUN_08013d44()
{
  return;
}




