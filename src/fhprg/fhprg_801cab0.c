/* Auto-generated: fhprg_801cab0.c */
/* Functions: 11 */
#include "globals.h"

/* 0x0801cab0 */
void FUN_0801cab0(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  undefined4 uVar1;
  
  uVar1 = FUN_08025740();
  FUN_0801e2ea(uVar1,param_2);
  FUN_08025820();
  return;
}




/* 0x0801caf4 */
undefined4 FUN_0801caf4(param_1, param_2)
undefined4 param_1; undefined4 * param_2;
{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_30;
  undefined4 local_2c;
  
  uVar1 = FUN_08025740();
  iVar2 = FUN_0801e20a(uVar1,&local_40);
  if (iVar2 == 0) {
    uVar4 = FUN_080060c0(local_3c,local_2c,0x200,0);
    uVar1 = (undefined4)uVar4;
    if ((int)((ulonglong)uVar4 >> 0x20) != 0) {
      uVar1 = 0xffffffff;
    }
    param_2[2] = uVar1;
    uVar4 = FUN_080060c0(local_40,local_30,0x200,0);
    uVar3 = 0xffffffff;
    if ((int)((ulonglong)uVar4 >> 0x20) == 0) {
      uVar3 = (int)uVar4;
    }
    param_2[3] = uVar1;
    param_2[4] = 0xffffffff;
    param_2[5] = 0xffffffff;
    param_2[6] = 0xffffffff;
    param_2[7] = 1;
    param_2[8] = 0;
    param_2[9] = 0x55;
    param_2[10] = 0x10000;
    param_2[0xb] = 0xffffffff;
    param_2[0xe] = 0;
    param_2[0xc] = 0xffffffff;
    param_2[0xd] = 0x58;
    param_2[0xf] = 1;
    param_2[0x10] = 0xffffffff;
    param_2[0x11] = 1;
    param_2[0x12] = 8;
    *param_2 = 0x200;
    param_2[1] = uVar3;
    *(undefined1 *)(param_2 + 0x13) = 2;
    *(undefined1 *)((int)param_2 + 0x4d) = 2;
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_08025820();
  }
  return uVar1;
}




/* 0x0801cbb8 */
void FUN_0801cbb8(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_0801d94c();
  iVar2 = FUN_0801e1e2(uVar1,param_2);
  if (iVar2 != 0) {
    FUN_08025820();
    return;
  }
  return;
}




/* 0x0801cc00 */
void FUN_0801cc00(param_1, param_2)
undefined4 param_1; undefined4 * param_2;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  iVar1 = ((code *)*(uint*)DAT_08050d08)(param_1,&DAT_87c29afc,0x59);
  if (iVar1 == 0) {
    if (param_2 == (undefined4 *)0x0) {
      uVar4 = FUN_080219a8();
      uVar3 = uVar4;
    }
    else {
      uVar4 = param_2[1];
      uVar3 = *param_2;
    }
    uVar2 = FUN_080213c0(uVar4);
    uVar4 = FUN_08021380(uVar4);
    uVar3 = FUN_08021380(uVar3);
    FUN_0801e4ce(&DAT_87c29afc,uVar2,uVar4,uVar3);
    FUN_08025820();
    return;
  }
  return;
}




/* 0x0801cc58 */
void FUN_0801cc58(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; uint param_3;
{
  undefined4 uVar1;
  
  if (0x10000 < param_3) {
    param_3 = 0x10000;
  }
  uVar1 = FUN_0801d94c(param_1);
  FUN_0801e476(param_2,1,param_3,uVar1);
  return;
}




/* 0x0801cc80 */
int FUN_0801cc80()
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (DAT_0804d25c != 0) {
    return 0;
  }
  DAT_0804d25c = 1;
  FUN_08020d50();
  FUN_08020cac();
  FUN_08020d4c();
  DAT_0804d254 = 0;
  FUN_08020c84();
  FUN_08021a00();
  FUN_08020fac();
  FUN_0802196c();
  FUN_08021278();
  FUN_08020cb0();
  thunk_FUN_0801e790(0);
  DAT_0804d258 = 1;
  iVar1 = FUN_08021034("romfs",&DAT_08039838);
  if (iVar1 != 0) {
    FUN_08015a50();
  }
  iVar2 = 0;
  do {
    iVar3 = iVar2 + 1;
    (&DAT_87c279f4)[iVar2 * 0x32] = 0;
    iVar2 = iVar3;
  } while (iVar3 < 2);
  FUN_08020d64();
  return iVar1;
}




/* 0x0801cd04 */
int thunk_FUN_0801cd04(param_1)
undefined4 param_1;
{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  FUN_08020d4c();
  iVar1 = FUN_08020c90(param_1);
  if (iVar1 == 0) {
    iVar2 = -0x3f1;
  }
  else {
    iVar2 = ((code *)**(undefined4 **)(iVar1 + 0x18))(iVar1);
    FUN_08020c7c(iVar1);
  }
  iVar1 = -iVar2;
  FUN_08020d64();
  if (iVar2 < 0) {
    piVar3 = (int *)FUN_0801cd9a();
    iVar2 = -1;
    *piVar3 = iVar1;
  }
  return iVar2;
}




/* 0x0801cd04 */
int FUN_0801cd04(param_1)
undefined4 param_1;
{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  FUN_08020d4c();
  iVar1 = FUN_08020c90(param_1);
  if (iVar1 == 0) {
    iVar2 = -0x3f1;
  }
  else {
    iVar2 = ((code *)**(undefined4 **)(iVar1 + 0x18))(iVar1);
    FUN_08020c7c(iVar1);
  }
  iVar1 = -iVar2;
  FUN_08020d64();
  if (iVar2 < 0) {
    piVar3 = (int *)FUN_0801cd9a();
    iVar2 = -1;
    *piVar3 = iVar1;
  }
  return iVar2;
}




/* 0x0801cd44 */
undefined4 thunk_FUN_0801cd44(param_1)
int * param_1;
{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  FUN_08020d4c();
  uVar3 = 0xffffffff;
  if ((param_1 == (int *)0x0) || (*param_1 == 0)) {
    piVar2 = (int *)FUN_0801cd9a();
    iVar1 = 5;
  }
  else {
    iVar1 = (**(code **)(*(int *)(param_1[0x31] + 0x14) + 0x2c))(param_1[0x31],param_1[1]);
    *param_1 = 0;
    FUN_08021c68(param_1[0x31]);
    if (-1 < iVar1) {
      uVar3 = 0;
      goto LAB_0801cd8a;
    }
    piVar2 = (int *)FUN_0801cd9a();
    iVar1 = -iVar1;
  }
  *piVar2 = iVar1;
LAB_0801cd8a:
  FUN_0801cd9a();
  FUN_08020d64();
  return uVar3;
}



/* WARNING: Type propagation algorithm not settling */

/* 0x0801cd44 */
undefined4 FUN_0801cd44(param_1)
int * param_1;
{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  FUN_08020d4c();
  uVar3 = 0xffffffff;
  if ((param_1 == (int *)0x0) || (*param_1 == 0)) {
    piVar2 = (int *)FUN_0801cd9a();
    iVar1 = 5;
  }
  else {
    iVar1 = (**(code **)(*(int *)(param_1[0x31] + 0x14) + 0x2c))(param_1[0x31],param_1[1]);
    *param_1 = 0;
    FUN_08021c68(param_1[0x31]);
    if (-1 < iVar1) {
      uVar3 = 0;
      goto LAB_0801cd8a;
    }
    piVar2 = (int *)FUN_0801cd9a();
    iVar1 = -iVar1;
  }
  *piVar2 = iVar1;
LAB_0801cd8a:
  FUN_0801cd9a();
  FUN_08020d64();
  return uVar3;
}




/* 0x0801cd9a */
int FUN_0801cd9a()
{
  int iVar1;
  
  iVar1 = FUN_080212a4();
  if (iVar1 == 0) {
    FUN_08015a50();
  }
  return iVar1;
}



/* WARNING: Type propagation algorithm not settling */

