/* Auto-generated: pm_app_led.c */
/* Functions: 5 */
#include "globals.h"

/* 0x0802c17c */
undefined4 FUN_0802c17c(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; int param_3; uint param_4;
{
  byte bVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  byte *pbVar5;
  int iVar6;
  undefined4 unaff_r4 = 0;
  int iVar7;
  undefined4 unaff_r5 = 0;
  undefined4 unaff_lr = 0;
  
  if (4 < param_2) {
    return 0xf;
  }
  if (param_2 == 0) {
    iVar6 = FUN_0802a8a8(param_1,param_3,param_3,param_4);
    if (iVar6 == 1) {
      puVar2 = (undefined4 *)FUN_0802be90(param_1 & 0xff);
      if (puVar2 != (undefined4 *)0x0) {
        uVar3 = FUN_0802b282(*(undefined4 *)*puVar2,*(short *)puVar2[1] + ((short *)puVar2[1])[9],1,
                             param_3 != 0,0,unaff_r4,unaff_r5,unaff_lr);
        return uVar3;
      }
      return 0x16;
    }
    if (iVar6 != 0) {
      return 0x16;
    }
    puVar2 = (undefined4 *)FUN_0802e594();
    if (puVar2 != (undefined4 *)0x0) {
      uVar3 = FUN_0802b282(*(undefined4 *)*puVar2,*(short *)puVar2[1] + ((short *)puVar2[1])[6],1,
                           param_3 != 0,0,unaff_r4,unaff_r5,unaff_lr);
      return uVar3;
    }
    return 0x16;
  }
  puVar2 = (undefined4 *)FUN_0802c32c();
  if (puVar2 == (undefined4 *)0x0) {
    ((code*)DAT_0804cd60)("pm_app_led.c",0x98,0x3060);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  pbVar5 = (byte *)*puVar2;
  if (pbVar5 == (byte *)0x0) {
    ((code*)DAT_0804cd60)("pm_app_led.c",0x9b,0x3060);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  while( true ) {
    bVar1 = *pbVar5;
    if (bVar1 == 5) {
      return 0x7b;
    }
    if (bVar1 == param_2) break;
    pbVar5 = pbVar5 + 4;
  }
  if (bVar1 == 5) {
    return 0x7b;
  }
  if (param_2 == 1) {
    if (param_4 < 8) {
      bVar1 = pbVar5[1];
joined_r0x0802c1fc:
      if (param_3 != 0) {
        uVar3 = FUN_0802c7ce(param_1,bVar1,param_4 & 0xff,1);
        return uVar3;
      }
      uVar3 = FUN_0802c9b0(param_1,bVar1,0);
      return uVar3;
    }
  }
  else {
    if (((param_2 != 2) && (param_2 != 3)) && (param_2 != 4)) {
      return 0;
    }
    bVar1 = pbVar5[1];
    if (bVar1 < 8) {
      if (param_4 < 8) goto joined_r0x0802c1fc;
    }
    else {
      if (((bVar1 != 8) && (bVar1 != 9)) && (bVar1 != 10)) {
        return 0;
      }
      if (param_4 < 0x1ff) {
        if (bVar1 == 8) {
          iVar6 = 1;
        }
        else if (bVar1 == 9) {
          iVar6 = 2;
        }
        else {
          iVar6 = 4;
        }
        iVar7 = puVar2[1];
        if (iVar7 == 0) {
          ((code*)DAT_0804cd60)("pm_app_led.c",0xf3,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        uVar4 = 0;
        do {
          if (*(int *)(iVar7 + uVar4 * 8) == iVar6) break;
          uVar4 = uVar4 + 1 & 0xff;
        } while (uVar4 < 3);
        if (uVar4 == 3) {
          uVar3 = 0x7c;
        }
        else {
          iVar7 = iVar7 + uVar4 * 8;
          uVar3 = FUN_0802d7d0(param_1,iVar6,*(undefined1 *)(iVar7 + 4),*(undefined1 *)(iVar7 + 5),
                               param_4,param_3);
        }
        return uVar3;
      }
    }
  }
  return 0x11;
}




/* 0x0802c2a0 */
undefined4 FUN_0802c2a0(param_1, param_2, param_3)
uint param_1; uint param_2; int param_3;
{
  byte bVar1;
  int iVar2;
  undefined4 *puVar3;
  byte *pbVar4;
  undefined4 uVar5;
  undefined4 unaff_r4 = 0;
  undefined4 unaff_r5 = 0;
  undefined4 unaff_lr = 0;
  
  if (param_2 < 5) {
    if (param_2 == 0) {
      iVar2 = FUN_0802a8a8();
      if (iVar2 == 1) {
        puVar3 = (undefined4 *)FUN_0802be90(param_1 & 0xff);
        if (puVar3 == (undefined4 *)0x0) {
          return 0x16;
        }
        uVar5 = FUN_0802b282(*(undefined4 *)*puVar3,*(short *)puVar3[1] + ((short *)puVar3[1])[9],1,
                             param_3 != 0,0,unaff_r4,unaff_r5,unaff_lr);
        return uVar5;
      }
      if (iVar2 == 0) {
        puVar3 = (undefined4 *)FUN_0802e594();
        if (puVar3 == (undefined4 *)0x0) {
          return 0x16;
        }
        uVar5 = FUN_0802b282(*(undefined4 *)*puVar3,*(short *)puVar3[1] + ((short *)puVar3[1])[6],1,
                             param_3 != 0,0,unaff_r4,unaff_r5,unaff_lr);
        return uVar5;
      }
      return 0x16;
    }
    puVar3 = (undefined4 *)FUN_0802c32c();
    if (puVar3 == (undefined4 *)0x0) {
      ((code*)DAT_0804cd60)("pm_app_led.c",0x38,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    pbVar4 = (byte *)*puVar3;
    if (pbVar4 == (byte *)0x0) {
      ((code*)DAT_0804cd60)("pm_app_led.c",0x3b);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    while( true ) {
      bVar1 = *pbVar4;
      if (bVar1 == 5) break;
      if (bVar1 == param_2) {
        if (bVar1 == 5) {
          return 0x7b;
        }
        uVar5 = FUN_0802c17c(param_1,param_2,param_3,*(undefined2 *)(pbVar4 + 2));
        return uVar5;
      }
      pbVar4 = pbVar4 + 4;
    }
  }
  return 0x7b;
}




/* 0x0802c31c */
undefined1 FUN_0802c31c()
{
  int iVar1;
  undefined1 uVar2;
  
  uVar2 = 5;
  iVar1 = FUN_0802c32c();
  if (iVar1 != 0) {
    uVar2 = *(undefined1 *)(iVar1 + 8);
  }
  return uVar2;
}




/* 0x0802c32c */
undefined4 FUN_0802c32c()
{
  if (DAT_0804d280 == '\0') {
    DAT_0804d284 = FUN_0802e86c(0x3a);
    DAT_0804d280 = '\x01';
  }
  return DAT_0804d284;
}




/* 0x0802c348 */
undefined4 FUN_0802c348(param_1, param_2, param_3, param_4, param_5, param_6)
undefined1 param_1; uint param_2; int param_3; int param_4; int param_5; uint param_6;
{
  undefined4 *puVar1;
  undefined4 uVar2;
  ushort *puVar3;
  
  puVar1 = (undefined4 *)FUN_0802c440(param_1);
  if (puVar1 == (undefined4 *)0x0) {
    uVar2 = 0x16;
  }
  else if ((param_2 < 9) && (param_2 != 0)) {
    if (param_6 < 4) {
      puVar3 = (ushort *)puVar1[1];
      uVar2 = FUN_0802b282(*(undefined4 *)*puVar1,
                           (uint)puVar3[6] + puVar3[1] * param_2 + (uint)*puVar3 & 0xffff,0x2f,
                           (param_3 << 5 | param_4 << 3 | param_5 << 2 | param_6) & 0xff,0);
    }
    else {
      uVar2 = 0x13;
    }
  }
  else {
    uVar2 = 0xf;
  }
  return uVar2;
}




