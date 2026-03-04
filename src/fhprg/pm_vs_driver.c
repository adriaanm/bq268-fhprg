/* Auto-generated: pm_vs_driver.c */
/* Functions: 3 */
#include "globals.h"

/* 0x0802ed04 */
void FUN_0802ed04(param_1, param_2, param_3)
undefined4 param_1; ushort * param_2; uint param_3;
{
  int iVar1;
  uint uVar2;
  undefined4 *local_28;
  undefined4 local_24 [2];
  
  local_24[0] = 0x69;
  local_24[1] = 0x6d;
  local_28 = *(undefined4 **)(&DAT_0805a330 + param_3 * 4);
  if (local_28 == (undefined4 *)0x0) {
    FUN_0802c644(0x10,&local_28);
    *local_28 = param_1;
    iVar1 = FUN_0802e824(4);
    local_28[1] = iVar1;
    if (iVar1 == 0) {
      ((code*)DAT_0804cd60)("pm_vs_driver.c",0x41,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (1 < param_3) {
      ((code*)DAT_0804cd60)("pm_vs_driver.c",0x44,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar1 = FUN_0802e848(local_24[param_3],param_3);
    local_28[2] = iVar1;
    if (iVar1 == 0) {
      ((code*)DAT_0804cd60)("pm_vs_driver.c",0x49,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    FUN_0802c644(iVar1 * 0xc,local_28 + 3);
    if (local_28[3] == 0) {
      ((code*)DAT_0804cd60)("pm_vs_driver.c",0x4e,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *(ushort *)(local_28[3] + 8) = *param_2;
    *(undefined4 **)(&DAT_0805a330 + param_3 * 4) = local_28;
    if (local_28 == (undefined4 *)0x0) {
      return;
    }
  }
  uVar2 = (uint)*(ushort *)(local_28[3] + 8);
  if (*param_2 < uVar2) {
    ((code*)DAT_0804cd60)("pm_vs_driver.c",0x5c,0x3060);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar2 = (int)(*param_2 - uVar2) / (int)(uint)*(ushort *)(local_28[1] + 2) & 0xffff;
  if (uVar2 < (uint)local_28[2]) {
    *(char *)(local_28[3] + uVar2 * 0xc + 10) = (char)param_2[1];
    *(ushort *)(local_28[3] + uVar2 * 0xc + 8) = *param_2;
    return;
  }
  ((code*)DAT_0804cd60)("pm_vs_driver.c",0x62,0x3060);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x0802ee94 */
undefined4 thunk_FUN_0802ee94(param_1)
int param_1;
{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    uVar1 = 0;
  }
  else if (param_1 == 1) {
    uVar1 = 4;
  }
  else {
    if (param_1 != 2) {
      return 0x16;
    }
    uVar1 = 1;
  }
  uVar1 = FUN_0802d180(7,uVar1);
  return uVar1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0802ee94 */
undefined4 FUN_0802ee94(param_1)
int param_1;
{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    uVar1 = 0;
  }
  else if (param_1 == 1) {
    uVar1 = 4;
  }
  else {
    if (param_1 != 2) {
      return 0x16;
    }
    uVar1 = 1;
  }
  uVar1 = FUN_0802d180(7,uVar1);
  return uVar1;
}




