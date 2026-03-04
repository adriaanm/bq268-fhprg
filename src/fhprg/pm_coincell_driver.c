/* Auto-generated: pm_coincell_driver.c */
/* Functions: 9 */
#include "globals.h"

/* 0x0802b0d4 */
void FUN_0802b0d4(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; int param_3;
{
  char cVar1;
  int iVar2;
  undefined4 *local_20;
  
  local_20 = (&DAT_0805a184)[param_3];
  if (local_20 == (undefined4 *)0x0) {
    FUN_0802c644(0xc,&local_20);
    *local_20 = param_1;
    iVar2 = FUN_0802e824(0x3e);
    local_20[1] = iVar2;
    if (iVar2 == 0) {
      ((code*)DAT_0804cd60)("pm_coincell_driver.c",0x3c,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (param_3 != 0) {
      ((code*)DAT_0804cd60)("pm_coincell_driver.c",0x3f,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    cVar1 = FUN_0802e848(0x88,0);
    *(char *)(local_20 + 2) = cVar1;
    if (cVar1 == '\0') {
      ((code*)DAT_0804cd60)("pm_coincell_driver.c",0x42,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    DAT_0805a184 = local_20;
  }
  return;
}




/* 0x0802b170 */
int FUN_0802b170(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  
  iVar1 = FUN_0802b5d8();
  return DAT_0804dc04 + (param_1 * iVar1 + param_2) * 0xc;
}




/* 0x0802b190 */
void FUN_0802b190()
{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  uVar4 = 0;
  iVar5 = 0;
  uVar1 = FUN_0802b5d8();
  FUN_0802c644((short)uVar1 * 0x54,&DAT_0804dc04);
  do {
    for (uVar3 = 0; uVar3 < uVar1; uVar3 = uVar3 + 1) {
      iVar2 = DAT_0804dc04 + iVar5 * 0xc;
      *(undefined1 *)(iVar2 + 8) = 0;
      *(uint *)(iVar2 + 4) = uVar4;
      FUN_0802b6b4(uVar4,uVar3 & 0xff);
      iVar5 = iVar5 + 1;
    }
    uVar4 = uVar4 + 1 & 0xff;
  } while (uVar4 < 7);
  return;
}




/* 0x0802b1e8 */
undefined8 FUN_0802b1e8(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 local_10;
  
  uVar2 = 0;
  local_10 = 0;
  uVar3 = 1;
  iVar1 = FUN_0800e564(param_1,param_4,param_2,param_3,1,&local_10);
  if (iVar1 != 0) {
    uVar2 = 9;
  }
  return CONCAT44(uVar3,uVar2);
}




/* 0x0802b20e */
undefined8 FUN_0802b20e(param_1, param_2, param_3, param_4, param_5)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4; undefined4 param_5;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  
  uVar2 = 0;
  local_10 = 0;
  iVar1 = FUN_0800e564(param_1,param_5,param_2,param_4,param_3,&local_10);
  if (iVar1 != 0) {
    uVar2 = 9;
  }
  return CONCAT44(param_3,uVar2);
}




/* 0x0802b22c */
undefined4 FUN_0802b22c(param_1, param_2, param_3, param_4, param_5)
undefined4 param_1; undefined4 param_2; byte param_3; byte * param_4; undefined4 param_5;
{
  int iVar1;
  
  iVar1 = FUN_0802b1e8(param_1,param_2,param_4,param_5);
  if (iVar1 != 0) {
    return 9;
  }
  *param_4 = *param_4 & param_3;
  return 0;
}




/* 0x0802b248 */
undefined4 FUN_0802b248(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  uVar2 = 0;
  uStack_10 = param_3;
  uStack_c = param_4;
  iVar1 = FUN_0800e57a(param_1,param_4,param_2,&uStack_10,1);
  if (iVar1 != 0) {
    uVar2 = 9;
  }
  return uVar2;
}




/* 0x0802b26a */
undefined4 FUN_0802b26a(param_1, param_2, param_3, param_4, param_5)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4; undefined4 param_5;
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0800e57a(param_1,param_5,param_2,param_4,param_3);
  if (iVar1 != 0) {
    uVar2 = 9;
  }
  return uVar2;
}



/* WARNING: Type propagation algorithm not settling */

/* 0x0802b282 */
undefined4 FUN_0802b282(param_1, param_2, param_3, param_4, param_5)
undefined4 param_1; undefined4 param_2; uint param_3; byte param_4; undefined4 param_5;
{
  int iVar1;
  undefined4 uVar2;
  uint local_28 [2];
  
  uVar2 = 0;
  local_28[1] = 1;
  local_28[0] = param_3 & 0xffffff00;
  iVar1 = FUN_0800e564(param_1,param_5,param_2,local_28,1,local_28 + 1);
  if (iVar1 == 0) {
    local_28[0] = CONCAT31(_GHIDRA_FIELD(local_28[0], 1, uint24_t),
                           param_4 & (byte)param_3 | (byte)local_28[0] & ~(byte)param_3);
    iVar1 = FUN_0800e57a(param_1,param_5,param_2,local_28,1);
    if (iVar1 != 0) {
      uVar2 = 9;
    }
  }
  return uVar2;
}




