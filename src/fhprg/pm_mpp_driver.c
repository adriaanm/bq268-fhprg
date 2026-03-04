/* Auto-generated: pm_mpp_driver.c */
/* Functions: 5 */
#include "globals.h"

/* 0x0802c8ac */
void FUN_0802c8ac(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; uint param_3;
{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined4 *local_28;
  undefined4 local_24 [2];
  
  local_24[0] = 0x70;
  local_24[1] = 0x71;
  local_28 = *(undefined4 **)(&DAT_0805a22c + param_3 * 4);
  if (local_28 == (undefined4 *)0x0) {
    FUN_0802c644(0x20,&local_28);
    *local_28 = param_1;
    iVar2 = FUN_0802e824(0x1a);
    local_28[1] = iVar2;
    if (iVar2 == 0) {
      ((code*)DAT_0804cd60)("pm_mpp_driver.c",0x3b,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (1 < param_3) {
      ((code*)DAT_0804cd60)("pm_mpp_driver.c",0x3e,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    cVar1 = FUN_0802e848(local_24[param_3],param_3);
    *(char *)(local_28 + 7) = cVar1;
    if (cVar1 == '\0') {
      ((code*)DAT_0804cd60)("pm_mpp_driver.c",0x42,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar2 = FUN_0802e86c(0x23);
    local_28[2] = iVar2;
    if (iVar2 == 0) {
      ((code*)DAT_0804cd60)("pm_mpp_driver.c",0x45,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    FUN_0802c644((uint)*(byte *)(local_28 + 7) << 2,local_28 + 4);
    uVar3 = 0;
    while( true ) {
      if (*(byte *)(local_28 + 7) <= uVar3) break;
      *(undefined4 *)(local_28[4] + uVar3 * 4) = 0;
      uVar3 = uVar3 + 1 & 0xff;
    }
    FUN_0802c644((uint)*(byte *)(local_28[2] + 2) << 2,local_28 + 3);
    for (uVar3 = 0; uVar3 < *(byte *)(local_28[2] + 2); uVar3 = uVar3 + 1 & 0xff) {
      *(uint *)(local_28[3] + uVar3 * 4) = (uint)*(byte *)(local_28 + 7);
    }
    *(undefined4 **)(&DAT_0805a22c + param_3 * 4) = local_28;
  }
  return;
}




/* 0x0802c9b0 */
undefined4 FUN_0802c9b0(param_1, param_2, param_3)
undefined1 param_1; short param_2; int param_3;
{
  undefined4 *puVar1;
  short *psVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  puVar1 = (undefined4 *)FUN_0802c9f0(param_1);
  if (puVar1 == (undefined4 *)0x0) {
    return 0x16;
  }
  psVar2 = (short *)puVar1[1];
  if (param_3 == 1) {
    uVar3 = 0x80;
  }
  uVar3 = FUN_0802b282(*(undefined4 *)*puVar1,psVar2[0x12] + psVar2[1] * param_2 + *psVar2,0x80,
                       uVar3,0);
  return uVar3;
}




/* 0x0802c9f0 */
undefined4 FUN_0802c9f0(param_1)
uint param_1;
{
  if (param_1 < 7) {
    return *(undefined4 *)(&DAT_0805a22c + param_1 * 4);
  }
  return 0;
}




/* 0x0802ca04 */
undefined4 thunk_FUN_0802ca04()
{
  FUN_0802b078(0,0,0,0);
  return 0;
}




/* 0x0802ca04 */
undefined4 FUN_0802ca04()
{
  FUN_0802b078(0,0,0,0);
  return 0;
}




