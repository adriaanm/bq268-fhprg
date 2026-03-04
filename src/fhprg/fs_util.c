/* Auto-generated: fs_util.c */
/* Functions: 7 */
#include "globals.h"

/* 0x08020e68 */
void FUN_08020e68(param_1, param_2, param_3, param_4)
uint param_1; undefined4 param_2; uint param_3; int param_4;
{
  int iVar1;
  
  if (param_1 == 0) {
    FUN_08015a50();
  }
  if (param_3 == 0) {
    FUN_08015a50();
  }
  if (((param_1 < param_3) || (param_3 + param_4 <= param_1)) &&
     ((param_3 < param_1 || (param_1 + param_4 <= param_3)))) {
    iVar1 = FUN_08027bf8(param_1,param_2,param_3,param_4);
    if (iVar1 != param_4) {
      ((code*)DAT_0804cd60)("fs_util.c",0x2f8,0x302f);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    return;
  }
  ((code*)DAT_0804cd60)("fs_util.c",0x2f4,0x302f);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08020edc */
void FUN_08020edc(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; int param_3; int param_4;
{
  int iVar1;
  
  if (param_1 == 0) {
    FUN_08015a50();
  }
  if (param_3 == 0) {
    FUN_08015a50();
  }
  iVar1 = FUN_08027c12(param_1,param_2,param_3,param_4);
  if (iVar1 != param_4) {
    FUN_08015a50();
    return;
  }
  return;
}




/* 0x08020f10 */
int FUN_08020f10(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 * param_3;
{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  bVar1 = false;
  iVar4 = 0;
  for (iVar3 = 0; iVar3 < DAT_0804d638; iVar3 = iVar3 + 1) {
    iVar2 = FUN_08006d64(param_1,(&DAT_87c282cc)[iVar3 * 5]);
    if (iVar2 == 0) {
      bVar1 = true;
      if ((&DAT_87c282c4)[iVar3 * 5] == 0) break;
    }
  }
  if (iVar3 == DAT_0804d638) {
    if (bVar1) {
      iVar4 = -0x400;
    }
    else {
      iVar4 = -0x3fb;
    }
  }
  else if (true) {
    *(short *)((&DAT_87c282c8)[iVar3 * 5] + 4) = (short)iVar3;
    iVar4 = ((code *)**(undefined4 **)(&DAT_87c282c8)[iVar3 * 5])
                      ((undefined4 *)(&DAT_87c282c8)[iVar3 * 5],param_2);
    if (iVar4 == 0) {
      iVar4 = (**(code **)(*(int *)(&DAT_87c282c8)[iVar3 * 5] + 8))
                        ((int *)(&DAT_87c282c8)[iVar3 * 5],&DAT_87c282c4 + iVar3 * 5);
      if (iVar4 == 0) {
        *param_3 = &DAT_87c282bc + iVar3 * 10;
        *(int *)((&DAT_87c282c8)[iVar3 * 5] + 8) = *(int *)((&DAT_87c282c8)[iVar3 * 5] + 8) + 1;
      }
      else {
        FUN_08015a50();
      }
    }
  }
  return iVar4;
}




/* 0x08020fac */
void FUN_08020fac()
{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  do {
    iVar2 = iVar1 + 1;
    (&DAT_87c282bc)[iVar1 * 10] = 0xffff;
    (&DAT_87c282c4)[iVar1 * 5] = 0;
    (&DAT_87c282cc)[iVar1 * 5] = 0;
    (&DAT_87c282c8)[iVar1 * 5] = 0;
    iVar1 = iVar2;
  } while (iVar2 < 10);
  DAT_0804d638 = 0;
  return;
}




/* 0x08020fe0 */
undefined4 FUN_08020fe0(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; undefined2 * param_4;
{
  int iVar1;
  undefined2 *local_10;
  
  local_10 = param_4;
  iVar1 = FUN_08020f10(param_2,param_3,&local_10);
  if (iVar1 == 0) {
    *local_10 = *(undefined2 *)(param_1 + 4);
    *(undefined4 *)(local_10 + 2) = *(undefined4 *)(param_1 + 8);
  }
  return 0;
}




/* 0x08021000 */
void FUN_08021000(param_1, param_2)
undefined4 param_1; int param_2;
{
  if (9 < DAT_0804d638) {
    FUN_08015a50();
  }
  (&DAT_87c282c8)[DAT_0804d638 * 5] = param_2;
  (&DAT_87c282cc)[DAT_0804d638 * 5] = param_1;
  *(undefined4 *)(param_2 + 8) = 1;
  DAT_0804d638 = DAT_0804d638 + 1;
  return;
}




/* 0x08021034 */
undefined4 FUN_08021034(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; int param_4;
{
  int iVar1;
  int local_8;
  
  local_8 = param_4;
  iVar1 = FUN_08020f10(param_1,param_2,&local_8);
  if (iVar1 == 0) {
    DAT_0804d63c = *(int *)(local_8 + 0xc);
    DAT_0804d634 = *(undefined2 *)(DAT_0804d63c + 4);
    DAT_0804d640 = *(undefined4 *)(local_8 + 8);
  }
  return 0;
}




