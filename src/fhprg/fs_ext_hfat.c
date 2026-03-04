/* Auto-generated: fs_ext_hfat.c */
/* Functions: 10 */
#include "globals.h"

/* 0x0801c92c */
undefined4 FUN_0801c92c(param_1, param_2)
int * param_1; int param_2;
{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  
  iVar1 = param_1[0x1d4];
  if (iVar1 == 0) {
    param_1[0x1d4] = 1;
    puVar3 = &DAT_0801c9d8;
  }
  else {
    if (iVar1 != 1) {
      if (iVar1 != 2) {
        FUN_08015a50();
        return 0;
      }
      iVar1 = FUN_080258b8(param_1);
      if (iVar1 == 0) {
        FUN_08027ec2(param_2 + 0x94,*(undefined1 *)((int)param_1 + 0x20f));
        *(int *)(param_2 + 0x98) = param_1[0x85];
        *(undefined4 *)(param_2 + 0xb8) = 0x4020;
        if (DAT_0804e27a == '\0') {
          DAT_0804e27a = 1;
          (**(code **)(DAT_08050d08 + 4))(param_1 + 1,&DAT_87c29d18,0x10c);
          FUN_080382c2(param_2,&DAT_87c29d18,0x89);
          DAT_0804e27a = 0;
          *param_1 = *param_1 + 1;
          return 0;
        }
        ((code*)DAT_0804cd60)("fs_ext_hfat.c",0x34e,0x302f);
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      uVar2 = FUN_08025820();
      return uVar2;
    }
    param_1[0x1d4] = 2;
    puVar3 = &DAT_0801c9dc;
  }
  FUN_080382c2(param_2,puVar3,0x89);
  return 0;
}




/* 0x0801ca00 */
void FUN_0801ca00(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  int iVar1;
  
  if (DAT_0804e278 != '\0') {
    ((code*)DAT_0804cd60)("fs_ext_hfat.c",0x265);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (DAT_0804e279 != '\0') {
    ((code*)DAT_0804cd60)("fs_ext_hfat.c",0x266,0x302f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  DAT_0804e278 = 1;
  DAT_0804e279 = 1;
  iVar1 = ((code *)*(uint*)DAT_08050d08)(param_1,&DAT_87c29bb0,0x59);
  if ((iVar1 == 0) && (iVar1 = ((code *)*(uint*)DAT_08050d08)(param_2,&DAT_87c29c64,0x59), iVar1 == 0)) {
    FUN_0801e3ce(&DAT_87c29bb0,&DAT_87c29c64);
    FUN_08025820();
  }
  DAT_0804e278 = 0;
  DAT_0804e279 = 0;
  return;
}




/* 0x080258b8 */
int FUN_080258b8(param_1, param_2, param_3, param_4)
int * param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  
  if (*param_1 == 0) {
    if (DAT_0804e279 != '\0') {
      ((code*)DAT_0804cd60)("fs_ext_hfat.c",0x2c6,0x302f);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    DAT_0804e279 = 1;
    iVar1 = ((code *)*(uint*)DAT_08050d08)(param_1 + 0x18e,&DAT_87c29c64,0x59);
    if (iVar1 == 0) {
      iVar1 = FUN_0801e336(&DAT_87c29c64,param_1 + 1);
    }
    DAT_0804e279 = 0;
    return iVar1;
  }
  iVar1 = FUN_0801e554(&stack0xfffffff0);
  if (iVar1 != 0) {
    return 0x16;
  }
  iVar1 = FUN_0801f172(param_4,param_1 + 1);
  FUN_0801268c(param_4);
  return iVar1;
}




/* 0x080259b0 */
undefined8 FUN_080259b0(param_1, param_2, param_3)
int param_1; undefined4 param_2; uint param_3;
{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 local_30;
  uint local_2c;
  undefined4 local_28;
  
  iVar4 = 0;
  iVar5 = -1;
  local_30 = 0;
  local_2c = param_3 & 0xffff0000;
  local_28 = 0;
  uVar6 = *(undefined4 *)(param_1 + 0x1c);
  uVar1 = FUN_08013bd4(uVar6,0);
  iVar2 = FUN_08013c84(uVar6,&local_28,uVar1);
  if (iVar2 == 0) {
    iVar2 = FUN_08013bb0(uVar6,local_28,&local_30,&local_2c);
    iVar5 = FUN_08013a7c(uVar6,local_28);
  }
  if ((iVar2 == 0 && iVar5 == 0) && (iVar4 = FUN_08026af8(), iVar4 != 0)) {
    uVar3 = FUN_080382c2(iVar4 + 0x14,param_1 + 8,0x14);
    if (0x14 < uVar3) {
      FUN_08015a50();
    }
    *(undefined4 *)(iVar4 + 0x10) = 0;
    *(undefined1 *)(iVar4 + 0x2a) = 1;
    *(char *)(iVar4 + 0x28) = (char)uVar1;
    *(undefined1 *)(iVar4 + 0x29) = 0;
    *(undefined4 *)(iVar4 + 0x2c) = 0;
    *(undefined4 *)(iVar4 + 0x30) = 0;
    *(undefined4 *)(iVar4 + 0x34) = 0;
    *(undefined4 *)(iVar4 + 0x38) = 0;
    *(undefined4 *)(iVar4 + 0x3c) = 0;
    *(undefined4 *)(iVar4 + 0x40) = local_30;
    *(int *)(iVar4 + 0x44) = param_1;
    FUN_08025c80(param_1,iVar4);
  }
  return CONCAT44(local_30,iVar4);
}




/* 0x08025a54 */
int FUN_08025a54(param_1, param_2)
undefined4 param_1; int param_2;
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_08026af8();
  if (iVar1 != 0) {
    *(undefined1 *)(iVar1 + 0x2a) = 5;
    *(undefined1 *)(iVar1 + 0x28) = *(undefined1 *)(param_2 + 0x28);
    *(undefined1 *)(iVar1 + 0x29) = 0;
    *(undefined4 *)(iVar1 + 0x2c) = 0;
    *(undefined4 *)(iVar1 + 0x30) = 0;
    *(undefined4 *)(iVar1 + 0x34) = 0;
    *(undefined4 *)(iVar1 + 0x38) = 0;
    *(undefined4 *)(iVar1 + 0x3c) = *(undefined4 *)(param_2 + 0x3c);
    *(undefined4 *)(iVar1 + 0x40) = *(undefined4 *)(param_2 + 0x40);
    *(undefined4 *)(iVar1 + 0x10) = 0;
    uVar2 = snprintf_buf(iVar1 + 0x14,0x14,"%sp%lu",param_2 + 0x14,param_1);
    if (uVar2 < 0x14) {
      uVar3 = *(undefined4 *)(param_2 + 0x44);
      *(undefined4 *)(iVar1 + 0x44) = uVar3;
      FUN_08025c80(uVar3,iVar1);
      return iVar1;
    }
    FUN_08026b88(iVar1);
  }
  return 0;
}




/* 0x08025ac4 */
int FUN_08025ac4(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; int param_3; undefined4 param_4;
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = FUN_08026af8();
  if (iVar1 != 0) {
    *(undefined1 *)(iVar1 + 0x2a) = 3;
    *(undefined1 *)(iVar1 + 0x28) = *(undefined1 *)(param_3 + 0x28);
    uVar2 = FUN_08006e30(param_1 + 0x30);
    *(byte *)(iVar1 + 0x29) = (byte)(uVar2 >> 2) & 1;
    FUN_08020e68(iVar1 + 0x2c,0x10,param_1,0x10,param_4);
    uVar3 = FUN_08006e04();
    *(undefined4 *)(iVar1 + 0x3c) = uVar3;
    iVar4 = FUN_08006e30(param_1 + 0x28);
    iVar5 = FUN_08006e30(param_1 + 0x20);
    *(int *)(iVar1 + 0x40) = (iVar4 - iVar5) + 1;
    *(undefined4 *)(iVar1 + 0x10) = 0;
    uVar2 = snprintf_buf(iVar1 + 0x14,0x14,"%sp%lu",param_3 + 0x14,param_2);
    if (uVar2 < 0x14) {
      uVar3 = *(undefined4 *)(param_3 + 0x44);
      *(undefined4 *)(iVar1 + 0x44) = uVar3;
      FUN_08025c80(uVar3,iVar1);
    }
    else {
      FUN_08026b88(iVar1);
      iVar1 = 0;
    }
  }
  return iVar1;
}




/* 0x08025b74 */
longlong FUN_08025b74(param_1, param_2, param_3, param_4)
int param_1; uint param_2; uint param_3; uint param_4;
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint local_20;
  uint local_1c;
  uint local_18;
  
  local_1c = param_3;
  local_18 = param_4;
  iVar1 = FUN_08013bb0(*(undefined4 *)(*(int *)(param_1 + 0x44) + 0x1c),param_2,&local_1c,&local_18)
  ;
  local_20 = param_2;
  if ((((iVar1 == 0) && (local_1c != 0)) && ((local_18 & 0xffff) != 0)) &&
     (iVar1 = FUN_08026af8(), iVar1 != 0)) {
    uVar2 = snprintf_buf(iVar1 + 0x14,0x14,"%sh%d",param_1 + 0x14);
    if (uVar2 < 0x14) {
      *(undefined4 *)(iVar1 + 0x10) = 0;
      *(undefined1 *)(iVar1 + 0x2a) = 2;
      *(char *)(iVar1 + 0x28) = (char)param_3;
      *(undefined1 *)(iVar1 + 0x29) = 0;
      *(undefined4 *)(iVar1 + 0x2c) = 0;
      *(undefined4 *)(iVar1 + 0x30) = 0;
      *(undefined4 *)(iVar1 + 0x34) = 0;
      *(undefined4 *)(iVar1 + 0x38) = 0;
      *(undefined4 *)(iVar1 + 0x3c) = 0;
      *(uint *)(iVar1 + 0x40) = local_1c;
      uVar3 = *(undefined4 *)(param_1 + 0x44);
      *(undefined4 *)(iVar1 + 0x44) = uVar3;
      FUN_08025c80(uVar3,iVar1);
      return CONCAT44(param_3,iVar1);
    }
    FUN_08026b88(iVar1);
    local_20 = param_3;
  }
  return (ulonglong)local_20 << 0x20;
}




/* 0x08025bf0 */
void FUN_08025bf0(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x30);
  if (*(int *)(param_1 + 0x30) != 0) {
    do {
      iVar2 = iVar1;
      iVar1 = *(int *)(iVar2 + 0x1c);
    } while (iVar1 != 0);
    *(int *)(iVar2 + 0x1c) = param_2;
    *(undefined4 *)(param_2 + 0x1c) = 0;
    return;
  }
  *(int *)(param_1 + 0x30) = param_2;
  return;
}




/* 0x08025c08 */
int FUN_08025c08(param_1, param_2, param_3, param_4)
undefined1 * param_1; undefined4 param_2; undefined4 param_3; int param_4;
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_08026af8();
  if (iVar1 != 0) {
    *(undefined1 *)(iVar1 + 0x2a) = 4;
    *(undefined1 *)(iVar1 + 0x28) = *(undefined1 *)(param_4 + 0x28);
    *(undefined1 *)(iVar1 + 0x29) = *param_1;
    *(uint *)(iVar1 + 0x2c) = (uint)(byte)param_1[1];
    *(undefined4 *)(iVar1 + 0x3c) = *(undefined4 *)(param_1 + 4);
    *(undefined4 *)(iVar1 + 0x40) = *(undefined4 *)(param_1 + 8);
    *(undefined4 *)(iVar1 + 0x10) = 0;
    uVar2 = snprintf_buf(iVar1 + 0x14,0x14,"%s%c%lu",param_4 + 0x14,param_3,param_2);
    if (uVar2 < 0x14) {
      uVar3 = *(undefined4 *)(param_4 + 0x44);
      *(undefined4 *)(iVar1 + 0x44) = uVar3;
      FUN_08025c80(uVar3,iVar1);
    }
    else {
      FUN_08026b88(iVar1);
      iVar1 = 0;
    }
  }
  return iVar1;
}




/* 0x08025c80 */
void FUN_08025c80(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x2c);
  if (*(int *)(param_1 + 0x2c) != 0) {
    do {
      iVar2 = iVar1;
      iVar1 = *(int *)(iVar2 + 0x48);
    } while (iVar1 != 0);
    *(int *)(iVar2 + 0x48) = param_2;
    *(undefined4 *)(param_2 + 0x48) = 0;
    return;
  }
  *(int *)(param_1 + 0x2c) = param_2;
  return;
}




