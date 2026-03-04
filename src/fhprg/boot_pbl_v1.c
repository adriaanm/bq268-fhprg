/* Auto-generated: boot_pbl_v1.c */
/* Functions: 9 */
#include "globals.h"

/* 0x08016e20 */
undefined4 FUN_08016e20()
{
  if (DAT_08051df4 == 0) {
    ((code*)DAT_0804cd60)("boot_pbl_v1.c",0xbf,0x3003);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return 0;
}




/* 0x08016e54 */
undefined4 FUN_08016e54()
{
  if (DAT_08051df4 != (undefined4 *)0x0) {
    return *(uint*)DAT_08051df4;
  }
  ((code*)DAT_0804cd60)("boot_pbl_v1.c",0x9d,0x3003);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08016e88 */
bool FUN_08016e88(param_1)
int param_1;
{
  if (param_1 != 0) {
    FUN_08030b34(&DAT_08051dc8,param_1,0x54);
  }
  return param_1 != 0;
}




/* 0x08016ea0 */
undefined4 FUN_08016ea0()
{
  undefined4 local_8;
  
  local_8 = 0;
  (**(code **)(DAT_08051df8 + 0x60))(1,&local_8);
  return local_8;
}




/* 0x08016ebc */
void FUN_08016ebc(param_1)
int param_1;
{
  uint uVar1;
  uint *puVar2;
  double dVar3;
  
  uVar1 = 0;
  puVar2 = (uint *)(param_1 + 0x34);
  do {
    dVar3 = (double)*puVar2 * 5.208333333333333e-08 * 1000000.0;
    FUN_08016adc((&DAT_0804cd28)[uVar1],(uint)(0.0 < dVar3) * (int)(longlong)dVar3,0x42,0);
    uVar1 = uVar1 + 1;
    puVar2 = puVar2 + 1;
  } while (uVar1 < 8);
  return;
}




/* 0x08016f18 */
void FUN_08016f18(param_1)
undefined1 param_1;
{
  FUN_0802d074(param_1);
  return;
}




/* 0x08016f26 */
int FUN_08016f26(param_1)
undefined4 param_1;
{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar1 = FUN_0802c31c();
  if (iVar1 != 5) {
    uVar2 = FUN_0802c31c();
    iVar3 = FUN_0802c2a0(0,uVar2,param_1);
    if (iVar3 == 0) {
      iVar3 = FUN_0802c2a0(0,1,param_1);
    }
  }
  return iVar3;
}




/* 0x08016f60 */
int FUN_08016f60(param_1, param_2, param_3, param_4)
char param_1; int param_2; undefined4 param_3; uint param_4;
{
  int iVar1;
  uint local_10;
  
  local_10 = param_4 & 0xffffff00;
  if (param_2 == 0) {
    iVar1 = 0x73;
  }
  else {
    if (param_1 != '\0') {
      return 0xe;
    }
    if ((DAT_0804d288 != '\0') || (iVar1 = FUN_0802d0b8(), iVar1 == 0)) {
      iVar1 = FUN_0802b1e8(0,0x88d,&local_10);
      if (iVar1 == 0) {
        local_10 = (uint)((byte)local_10 & 1);
      }
      *(bool *)param_2 = (byte)local_10 != '\0';
      return iVar1;
    }
  }
  return iVar1;
}




/* 0x08016f66 */
int FUN_08016f66(param_1)
char param_1;
{
  int iVar1;
  
  if (param_1 == '\0') {
    if ((DAT_0804d288 != '\0') || (iVar1 = FUN_0802d0b8(), iVar1 == 0)) {
      iVar1 = FUN_0802b282(0,0x88d,1,0,0);
      return iVar1;
    }
  }
  else {
    iVar1 = 0xe;
  }
  return iVar1;
}




