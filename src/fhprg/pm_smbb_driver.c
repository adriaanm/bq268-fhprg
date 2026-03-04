/* Auto-generated: pm_smbb_driver.c */
/* Functions: 4 */
#include "globals.h"

/* 0x0802e4f4 */
void FUN_0802e4f4(param_1, param_2)
undefined4 param_1; uint param_2;
{
  char cVar1;
  int iVar2;
  undefined4 *local_20;
  undefined4 local_1c [2];
  
  local_1c[0] = 0x7f;
  local_1c[1] = 0x81;
  local_20 = *(undefined4 **)(&DAT_0805a3e0 + param_2 * 4);
  if (local_20 == (undefined4 *)0x0) {
    FUN_0802c644(0xc,&local_20);
    *local_20 = param_1;
    iVar2 = FUN_0802e824(0x2a);
    local_20[1] = iVar2;
    if (iVar2 == 0) {
      ((code*)DAT_0804cd60)("pm_smbb_driver.c",0x3e,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (1 < param_2) {
      ((code*)DAT_0804cd60)("pm_smbb_driver.c",0x41,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    cVar1 = FUN_0802e848(local_1c[param_2],param_2);
    *(char *)(local_20 + 2) = cVar1;
    if (cVar1 == '\0') {
      ((code*)DAT_0804cd60)("pm_smbb_driver.c",0x44,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *(undefined4 **)(&DAT_0805a3e0 + param_2 * 4) = local_20;
  }
  return;
}




/* 0x0802e594 */
undefined4 FUN_0802e594(param_1)
uint param_1;
{
  if (param_1 < 7) {
    return *(undefined4 *)(&DAT_0805a3e0 + param_1 * 4);
  }
  return 0;
}




/* 0x0802e5a8 */
uint thunk_FUN_0802e5a8(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  uStack_10 = param_3;
  uStack_c = param_4;
  uVar1 = FUN_0802cec0();
  uStack_10 = 0;
  uStack_c = 0;
  uVar2 = FUN_0802d074(0,&uStack_10);
  if (uVar2 == 0) {
    puVar3 = (undefined4 *)FUN_080373b8(0x193,8);
    if (puVar3 == (undefined4 *)0x0) {
      uVar2 = 0x7e;
    }
    else {
      *puVar3 = uStack_10;
      puVar3[1] = uStack_c;
      uVar2 = 0;
    }
  }
  return uVar2 | uVar1;
}




/* 0x0802e5a8 */
uint FUN_0802e5a8(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 local_10;
  undefined4 uStack_c;
  
  local_10 = param_3;
  uStack_c = param_4;
  uVar1 = FUN_0802cec0();
  local_10 = 0;
  uStack_c = 0;
  uVar2 = FUN_0802d074(0,&local_10);
  if (uVar2 == 0) {
    puVar3 = (undefined4 *)FUN_080373b8(0x193,8);
    if (puVar3 == (undefined4 *)0x0) {
      uVar2 = 0x7e;
    }
    else {
      *puVar3 = local_10;
      puVar3[1] = uStack_c;
      uVar2 = 0;
    }
  }
  return uVar2 | uVar1;
}




