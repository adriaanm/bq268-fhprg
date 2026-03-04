/* Auto-generated: pm_lpg_driver.c */
/* Functions: 8 */
#include "globals.h"

/* 0x0802c3a4 */
void FUN_0802c3a4(param_1, param_2)
undefined4 param_1; uint param_2;
{
  char cVar1;
  int iVar2;
  undefined4 *local_20;
  undefined4 local_1c [2];
  
  local_1c[0] = 0x72;
  local_1c[1] = 0x73;
  local_20 = *(undefined4 **)(&DAT_0805a210 + param_2 * 4);
  if (local_20 == (undefined4 *)0x0) {
    FUN_0802c644(0xc,&local_20);
    *local_20 = param_1;
    iVar2 = FUN_0802e824(0x1c);
    local_20[1] = iVar2;
    if (iVar2 == 0) {
      ((code*)DAT_0804cd60)("pm_lpg_driver.c",0x3c,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (1 < param_2) {
      ((code*)DAT_0804cd60)("pm_lpg_driver.c",0x3f,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    cVar1 = FUN_0802e848(local_1c[param_2],param_2);
    *(char *)(local_20 + 2) = cVar1;
    if (cVar1 == '\0') {
      ((code*)DAT_0804cd60)("pm_lpg_driver.c",0x42,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *(undefined4 **)(&DAT_0805a210 + param_2 * 4) = local_20;
  }
  return;
}




/* 0x0802c440 */
undefined4 FUN_0802c440(param_1)
uint param_1;
{
  if (param_1 < 7) {
    return *(undefined4 *)(&DAT_0805a210 + param_1 * 4);
  }
  return 0;
}




/* 0x0802c454 */
undefined4 FUN_0802c454(param_1, param_2, param_3, param_4, param_5, param_6, param_7)
undefined1 param_1; uint param_2; int param_3; int param_4; int param_5; int param_6; uint param_7;
{
  undefined4 *puVar1;
  undefined4 uVar2;
  ushort *puVar3;
  
  puVar1 = (undefined4 *)FUN_0802c440(param_1,&stack0x0000000c,param_3,param_4,param_4);
  if (puVar1 == (undefined4 *)0x0) {
    uVar2 = 0x16;
  }
  else if ((param_2 < 9) && (param_2 != 0)) {
    puVar3 = (ushort *)puVar1[1];
    uVar2 = FUN_0802b282(*(undefined4 *)*puVar1,
                         (uint)puVar3[3] + puVar3[1] * param_2 + (uint)*puVar3 & 0xffff,0x1f,
                         (param_3 << 4 | param_4 << 3 | param_5 << 2 | param_6 << 1 | param_7) &
                         0xff,0);
  }
  else {
    uVar2 = 0xf;
  }
  return uVar2;
}




/* 0x0802c4b0 */
undefined4 FUN_0802c4b0(param_1, param_2, param_3)
undefined1 param_1; uint param_2; undefined4 param_3;
{
  undefined4 *puVar1;
  undefined4 uVar2;
  ushort *puVar3;
  
  puVar1 = (undefined4 *)FUN_0802c440(param_1);
  if (puVar1 == (undefined4 *)0x0) {
    return 0x16;
  }
  if ((param_2 < 9) && (param_2 != 0)) {
    puVar3 = (ushort *)puVar1[1];
    uVar2 = FUN_0802b282(*(undefined4 *)*puVar1,
                         (uint)puVar3[4] + puVar3[1] * param_2 + (uint)*puVar3 & 0xffff,3,param_3,0)
    ;
    return uVar2;
  }
  return 0xf;
}




/* 0x0802c4ee */
undefined4 FUN_0802c4ee(param_1, param_2, param_3)
undefined1 param_1; uint param_2; int param_3;
{
  undefined4 *puVar1;
  ushort *puVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  puVar1 = (undefined4 *)FUN_0802c440(param_1);
  if (puVar1 == (undefined4 *)0x0) {
    return 0x16;
  }
  if ((param_2 < 9) && (param_2 != 0)) {
    puVar2 = (ushort *)puVar1[1];
    if (param_3 != 0) {
      uVar3 = 0xe4;
    }
    uVar3 = FUN_0802b282(*(undefined4 *)*puVar1,
                         (uint)puVar2[9] + puVar2[1] * param_2 + (uint)*puVar2 & 0xffff,0xe4,uVar3,0
                        );
    return uVar3;
  }
  return 0xf;
}




/* 0x0802c532 */
undefined4 FUN_0802c532(param_1, param_2, param_3, param_4)
undefined1 param_1; uint param_2; char param_3; byte param_4;
{
  undefined4 *puVar1;
  undefined4 uVar2;
  ushort *puVar3;
  
  puVar1 = (undefined4 *)FUN_0802c440(param_1);
  if (puVar1 == (undefined4 *)0x0) {
    return 0x16;
  }
  if ((param_2 < 9) && (param_2 != 0)) {
    puVar3 = (ushort *)puVar1[1];
    uVar2 = FUN_0802b282(*(undefined4 *)*puVar1,
                         (uint)puVar3[5] + puVar3[1] * param_2 + (uint)*puVar3 & 0xffff,0x67,
                         param_4 | param_3 << 5,0);
    return uVar2;
  }
  return 0xf;
}




/* 0x0802c576 */
uint FUN_0802c576(param_1, param_2, param_3)
undefined1 param_1; uint param_2; uint param_3;
{
  ushort uVar1;
  undefined4 *puVar2;
  ushort *puVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  
  puVar2 = (undefined4 *)FUN_0802c440(param_1);
  if (puVar2 == (undefined4 *)0x0) {
    uVar5 = 0x16;
  }
  else if ((param_2 < 9) && (param_2 != 0)) {
    puVar3 = (ushort *)puVar2[1];
    iVar6 = puVar3[1] * param_2 + (uint)*puVar3;
    uVar1 = puVar3[8];
    if (0x1ff < param_3) {
      param_3 = 0x1ff;
    }
    uVar4 = FUN_0802b282(*(undefined4 *)*puVar2,(uint)puVar3[7] + iVar6 & 0xffff,0xff,param_3 & 0xff
                         ,0);
    uVar5 = FUN_0802b282(*(undefined4 *)*puVar2,(uint)uVar1 + iVar6 & 0xffff,1,param_3 >> 8,0);
    uVar5 = uVar5 | uVar4;
  }
  else {
    uVar5 = 0xf;
  }
  return uVar5;
}




/* 0x0802c5e4 */
uint FUN_0802c5e4(param_1, param_2, param_3)
undefined1 param_1; uint param_2; int param_3;
{
  ushort uVar1;
  undefined4 *puVar2;
  ushort *puVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  
  puVar2 = (undefined4 *)FUN_0802c440(param_1);
  if (puVar2 == (undefined4 *)0x0) {
    return 0x16;
  }
  if ((param_2 < 9) && (param_2 != 0)) {
    puVar3 = (ushort *)puVar2[1];
    iVar6 = param_2 * puVar3[1] + (uint)*puVar3;
    uVar1 = puVar3[10];
    uVar4 = FUN_0802b282(*(undefined4 *)*puVar2,(uint)puVar3[4] + iVar6 & 0xffff,0x10,param_3 != 0,0
                        );
    uVar5 = FUN_0802b282(*(undefined4 *)*puVar2,(uint)uVar1 + iVar6 & 0xffff,1,1,0);
    return uVar5 | uVar4;
  }
  return 0xf;
}




