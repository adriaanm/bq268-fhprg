/* Auto-generated: fhprg_801610c.c */
/* Functions: 15 */
#include "globals.h"

/* 0x0801610c */
int FUN_0801610c(param_1)
uint param_1;
{
  uint uVar1;
  int iVar2;
  
  iVar2 = -1;
  if (((param_1 != 0xffffffff) && (uVar1 = FUN_08016180(), uVar1 != 0xffffffff)) &&
     (param_1 <= uVar1)) {
    iVar2 = uVar1 - param_1;
  }
  return iVar2;
}




/* 0x0801612c */
undefined1 FUN_0801612c()
{
  return DAT_0804d128;
}




/* 0x08016138 */
undefined8 FUN_08016138()
{
  if (DAT_0804d128 != '\x02') {
    return 0;
  }
  return 0;
}




/* 0x0801615c */
undefined4 FUN_0801615c()
{
  return 0xa000;
}




/* 0x08016164 */
undefined * FUN_08016164()
{
  return &DAT_87c1b440;
}




/* 0x0801616c */
undefined1 FUN_0801616c()
{
  return DAT_0804cdec;
}




/* 0x08016178 */
undefined * FUN_08016178()
{
  return &DAT_08052c00;
}




/* 0x08016180 */
int FUN_08016180()
{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = FUN_0801688c();
  uVar2 = FUN_080161b0();
  if (uVar2 < 0x8421214) {
    iVar3 = uVar2 * 0x1e + (uVar2 >> 1);
    if (iVar1 != 0) {
      iVar3 = iVar3 - *(int *)(iVar1 + 0x10);
    }
    return iVar3;
  }
  return -1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08016180 */
int thunk_FUN_08016180()
{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = FUN_0801688c();
  uVar2 = FUN_080161b0();
  if (uVar2 < 0x8421214) {
    iVar3 = uVar2 * 0x1e + (uVar2 >> 1);
    if (iVar1 != 0) {
      iVar3 = iVar3 - *(int *)(iVar1 + 0x10);
    }
    return iVar3;
  }
  return -1;
}




/* 0x080161b0 */
undefined4 FUN_080161b0()
{
  do {
  } while (false);
  return 0;
}




/* 0x080161c0 */
undefined4 FUN_080161c0()
{
  int iVar1;
  int local_10;
  
  local_10 = 0;
  iVar1 = FUN_0800b7b4(0x2000020,&local_10);
  if (((iVar1 == 0) && (iVar1 = (**(code **)(*(int *)(local_10 + 4) + 0x38))(), iVar1 == 0)) &&
     (iVar1 = FUN_0800b874(local_10), iVar1 == 0)) {
    return 1;
  }
  return 0;
}




/* 0x080161f8 */
undefined4 FUN_080161f8(param_1, param_2, param_3, param_4, param_5)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4; undefined4 param_5;
{
  int iVar1;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  
  uStack_20 = param_3;
  uStack_1c = param_4;
  iVar1 = FUN_080162dc(&uStack_20,param_1);
  if ((iVar1 == 0) && (iVar1 = FUN_08016338(&uStack_20,param_2,param_3), iVar1 == 0)) {
    FUN_0801622c(&uStack_20,param_4,param_5);
  }
  return 0;
}




/* 0x0801622c */
undefined4 FUN_0801622c(param_1, param_2, param_3)
char * param_1; int param_2; uint param_3;
{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 *local_58;
  undefined4 uStack_54;
  undefined1 auStack_50 [4];
  undefined1 auStack_4c [4];
  undefined1 auStack_48 [32];
  int local_28;
  char *pcStack_24;
  int iStack_20;
  uint local_1c;
  
  iVar2 = DAT_0804cd58;
  local_28 = DAT_0804cd58;
  local_58 = auStack_50;
  uVar5 = 0;
  uStack_54 = 1;
  pcStack_24 = param_1;
  iStack_20 = param_2;
  local_1c = param_3;
  FUN_08006e1a(auStack_48,local_58);
  FUN_08006e1a(0x20,auStack_4c);
  if ((param_1 == (char *)0x0) || (param_2 == 0)) {
    uVar5 = 0x3003;
    goto LAB_080162c4;
  }
  cVar1 = *param_1;
  if (cVar1 == '\x01') {
    if (0x13 < local_1c) {
LAB_08016282:
      local_1c = 0x14;
LAB_0801628c:
      iVar3 = thunk_FUN_08009830(*(undefined4 *)(param_1 + 4),&local_58);
      if (iVar3 == 0) {
        uVar4 = FUN_08006e04(local_58);
        FUN_08030b34(param_2,uVar4,local_1c);
        FUN_08007f08(auStack_48,0,0x20);
        thunk_FUN_08009804(param_1 + 4);
        iVar3 = thunk_FUN_0800947c();
        if (iVar3 == 0) goto LAB_080162c4;
      }
    }
  }
  else if (cVar1 == '\x02') {
    if (0x1f < local_1c) {
LAB_0801628a:
      local_1c = 0x20;
      goto LAB_0801628c;
    }
  }
  else {
    if (cVar1 == '\x01') goto LAB_08016282;
    if (cVar1 == '\x02') goto LAB_0801628a;
  }
  uVar5 = 0x302e;
LAB_080162c4:
  if (local_28 != iVar2) {
    FUN_08010960();
  }
  return uVar5;
}




/* 0x080162dc */
undefined4 FUN_080162dc(param_1, param_2)
undefined1 * param_1; int param_2;
{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_18;
  
  if (param_1 == (undefined1 *)0x0) {
    uVar2 = 0x3003;
  }
  else {
    if (param_2 == 1) {
      local_18 = 1;
      DAT_0804cdf8 = 0x14;
    }
    else {
      if (param_2 != 2) {
        return 0x3037;
      }
      local_18 = 2;
      DAT_0804cdf8 = 0x20;
    }
    iVar1 = thunk_FUN_08009de0();
    if (iVar1 == 0) {
      *param_1 = local_18;
      *(undefined4 *)(param_1 + 4) = 0;
      iVar1 = thunk_FUN_08009980(param_1 + 4);
      if (iVar1 == 0) {
        return 0;
      }
    }
    uVar2 = 0x302e;
  }
  return uVar2;
}




/* 0x08016338 */
undefined4 FUN_08016338(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  
  uVar2 = 0;
  uStack_20 = param_3;
  uStack_1c = param_4;
  FUN_08006e1a(param_2,&uStack_20);
  FUN_08006e1a(param_3,&uStack_1c);
  if (param_1 == 0) {
    uVar2 = 0x3003;
  }
  else {
    iVar1 = thunk_FUN_08009af4(*(undefined4 *)(param_1 + 4),&uStack_20,1);
    if (iVar1 != 0) {
      uVar2 = 0x302e;
    }
  }
  return uVar2;
}




