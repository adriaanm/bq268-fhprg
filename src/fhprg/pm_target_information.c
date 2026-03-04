/* Auto-generated: pm_target_information.c */
/* Functions: 3 */
#include "globals.h"

/* 0x0802ea74 */
undefined4 FUN_0802ea74(param_1)
undefined4 param_1;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 auStack_28 [8];
  undefined4 *local_20;
  undefined1 auStack_1c [8];
  
  uVar2 = 0;
  iVar1 = dal_device_attach(param_1,auStack_1c);
  if (iVar1 != 0) {
    ((code*)DAT_0804cd60)("pm_target_information.c",0x52,0x3060);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar1 = thunk_FUN_080106aa(auStack_1c,0,0x7d,auStack_28);
  if (iVar1 != 0) {
    ((code*)DAT_0804cd60)("pm_target_information.c",0x56,0x3060);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar3 = *local_20;
  iVar1 = thunk_FUN_080106aa(auStack_1c,0,0x7c,auStack_28);
  if (iVar1 != 0) {
    ((code*)DAT_0804cd60)("pm_target_information.c",0x5b,0x3060);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar1 = FUN_0800e614(1);
  if ((iVar1 == 0) && (iVar1 = FUN_0800e5f4(local_20,uVar3), iVar1 != 0)) {
    uVar2 = 9;
  }
  return uVar2;
}




/* 0x0802eb04 */
uint FUN_0802eb04(param_1, param_2, param_3)
uint param_1; int param_2; int param_3;
{
  uint uVar1;
  uint uVar2;
  
  uVar2 = param_3 - 1U & 0xff;
  if (param_1 == 0) {
    uVar2 = 0;
  }
  else if (*(uint *)(param_2 + param_3 * 4 + -4) != param_1) {
    for (uVar1 = 0; (int)uVar1 < (int)(param_3 - 1U); uVar1 = uVar1 + 1 & 0xff) {
      if ((*(uint *)(param_2 + uVar1 * 4) < param_1) &&
         (param_1 <= *(uint *)(param_2 + uVar1 * 4 + 4))) {
        return uVar1 + 1 & 0xff;
      }
    }
  }
  return uVar2;
}




/* 0x0802eb4c */
undefined4 FUN_0802eb4c()
{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  int local_28;
  
  iVar1 = DAT_0804cd58;
  local_28 = DAT_0804cd58;
  uVar6 = 0;
  uVar5 = 0;
  local_34 = 0;
  uVar4 = 0;
  local_30 = 0;
  local_2c = 0;
  if (DAT_0804dc30 == '\0') {
    FUN_08006cc0(&DAT_080586a4,0x1c,0xff);
    do {
      iVar2 = FUN_0802b20e(uVar5,0x102,4,&local_2c,0);
      if ((iVar2 == 0) && (_GHIDRA_FIELD(local_2c, 2, byte) == 'Q')) {
        (&DAT_08058634)[uVar4 * 3] = local_2c >> 0x18;
        (&DAT_08058638)[uVar4 * 3] = local_2c >> 8 & 0xff;
        (&DAT_0805863c)[uVar4 * 3] = local_2c & 0xff;
        uVar6 = FUN_0802b20e(uVar5,0x100,6,&local_34,0);
        iVar2 = FUN_08006e04((int)&local_34 + 1);
        (&DAT_08058688)[uVar4] = local_34 & 0xff | iVar2 << 8;
        (&DAT_080586a4)[uVar4] = uVar5;
        uVar3 = (&DAT_08058638)[uVar4 * 3];
        if ((&DAT_08058634)[uVar4 * 3] == 1) {
          if (uVar3 < 2) {
            iVar2 = uVar3 + 1;
            goto LAB_0802ec22;
          }
        }
        else if (uVar3 == 0) {
          iVar2 = 1;
LAB_0802ec22:
          (&DAT_08058638)[uVar4 * 3] = iVar2;
        }
      }
      else {
        uVar6 = 0;
      }
      uVar5 = uVar5 + 2;
      uVar4 = uVar4 + 1 & 0xff;
    } while ((uVar5 < 0xe) && (uVar4 < 7));
    DAT_0804dc30 = '\x01';
  }
  if (local_28 != iVar1) {
    FUN_08010960();
  }
  return uVar6;
}




