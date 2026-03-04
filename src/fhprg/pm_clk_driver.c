/* Auto-generated: pm_clk_driver.c */
/* Functions: 3 */
#include "globals.h"

/* 0x0802af30 */
void FUN_0802af30(param_1, param_2, param_3)
undefined4 param_1; ushort * param_2; int param_3;
{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *local_28;
  
  local_28 = *(undefined4 **)(&DAT_0805a168 + param_3 * 4);
  if (local_28 == (undefined4 *)0x0) {
    FUN_0802c644(0x34,&local_28);
    *local_28 = param_1;
    iVar2 = FUN_0802e824(1);
    local_28[10] = iVar2;
    if (iVar2 == 0) {
      ((code*)DAT_0804cd60)("pm_clk_driver.c",0x49,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar2 = FUN_0802e824(0x16);
    local_28[0xb] = iVar2;
    if (iVar2 == 0) {
      ((code*)DAT_0804cd60)("pm_clk_driver.c",0x4d,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar2 = FUN_0802e824(0x17);
    local_28[0xc] = iVar2;
    if (iVar2 == 0) {
      ((code*)DAT_0804cd60)("pm_clk_driver.c",0x51,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar2 = FUN_0802e824(0x18);
    puVar1 = local_28;
    local_28[9] = iVar2;
    if (iVar2 == 0) {
      ((code*)DAT_0804cd60)("pm_clk_driver.c",0x56,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    local_28[1] = 0xe;
    uVar4 = 0;
    FUN_08006cc0((int)local_28 + 0x16,0xd,99);
    do {
      uVar3 = (uint)*(byte *)(puVar1[9] + uVar4);
      if (uVar3 < 0xd) {
        *(char *)((int)puVar1 + uVar3 + 0x16) = (char)uVar4;
      }
      uVar4 = uVar4 + 1 & 0xff;
    } while (uVar4 < 0xe);
    iVar2 = FUN_0802b68c(param_3);
    if (iVar2 == 8) {
      *(undefined1 *)((int)local_28 + 0x22) = 2;
      *(undefined1 *)(local_28 + 7) = 99;
    }
    FUN_08006d14(local_28 + 2,0xe);
    *(undefined4 **)(&DAT_0805a168 + param_3 * 4) = local_28;
    if (local_28 == (undefined4 *)0x0) {
      return;
    }
  }
  uVar4 = (uint)*(ushort *)local_28[10];
  if (*param_2 < uVar4) {
    ((code*)DAT_0804cd60)("pm_clk_driver.c",0x72,0x3060);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar4 = (int)(*param_2 - uVar4) / (int)(uint)((ushort *)local_28[10])[1];
  if (uVar4 < 0xe) {
    *(undefined1 *)((int)local_28 + uVar4 + 8) = *(undefined1 *)((int)param_2 + 3);
    return;
  }
  ((code*)DAT_0804cd60)("pm_clk_driver.c",0x78,0x3060);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x0802b064 */
undefined4 FUN_0802b064(param_1)
uint param_1;
{
  if (param_1 < 7) {
    return *(undefined4 *)(&DAT_0805a168 + param_1 * 4);
  }
  return 0;
}




/* 0x0802b078 */
undefined4 FUN_0802b078(param_1, param_2, param_3, param_4)
undefined4 param_1; int param_2; int param_3; uint param_4;
{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  
  puVar2 = (undefined4 *)FUN_0802b064();
  uVar5 = 0;
  if (((puVar2 != (undefined4 *)0x0) && ((undefined4 *)*puVar2 != (undefined4 *)0x0)) &&
     (param_2 == 0)) {
    uVar4 = (uint)*(byte *)((int)puVar2 + 0x16);
    if (((uVar4 == 99) || (0xd < uVar4)) ||
       (cVar1 = *(char *)((int)puVar2 + uVar4 + 8), cVar1 == '\0')) {
      return 0x3c;
    }
    if (cVar1 == '\f') {
      if (param_3 == 1) {
        uVar5 = 0x80;
      }
      uVar3 = FUN_0802b282(*(undefined4 *)*puVar2,
                           (uint)*(ushort *)puVar2[0xb] +
                           uVar4 * ((ushort *)puVar2[10])[1] + (uint)*(ushort *)puVar2[10] & 0xffff,
                           0x83,uVar5 | param_4,0);
      return uVar3;
    }
  }
  return 0x16;
}




