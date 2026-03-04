/* Auto-generated: boot_error_handler.c */
/* Functions: 11 */
#include "globals.h"

/* 0x08007410 */
void FUN_08007410()
{
  ((code*)DAT_0804cd60)("boot_error_handler.c",0x20a,0x3034);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08007b10 */
void FUN_08007b10()
{
  ((code*)DAT_0804cd60)("boot_error_handler.c",0x20a,0x3034);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08015a50 */
void FUN_08015a50()
{
  ((code*)DAT_0804cd60)("boot_error_handler.c",0x199,0x302f);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08015a80 */
void FUN_08015a80(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  
  uVar3 = 0;
  if (DAT_00223018 != '\0') {
    FUN_080087d4();
  }
  DAT_0804cd5c = DAT_0804cd5c + 1;
  if (DAT_0804cd5c < 4) {
    if (DAT_0804cd5c == 1) {
      snprintf_buf(&DAT_08051e1c,0x100,"Error code %lx at %s Line %lu",param_3,param_1,param_2);
      boot_log_message(&DAT_08051e1c);
      DAT_08051afc = &DAT_0805c0b4;
      puVar1 = &DAT_0805c0b4;
      DAT_0805c0c0 = &DAT_08015b50;
    }
    else {
      puVar1 = &DAT_0805c0b0 + DAT_0804cd5c * 3;
    }
    DAT_0805c0c4 = DAT_0804cd5c;
    bVar4 = DAT_0804cd5c == 1;
    *puVar1 = param_3;
    puVar1[1] = param_2;
    puVar1[2] = param_1;
    puVar1 = DAT_0804cd54;
    if (bVar4) {
      for (; (puVar1 != (undefined4 *)0x0 && (uVar3 < 0x14)); uVar3 = uVar3 + 1) {
        ((code *)*puVar1)(puVar1[1]);
        puVar1 = (undefined4 *)puVar1[2];
      }
    }
    FUN_08032580();
    iVar2 = FUN_08019964();
    if (iVar2 == 0) {
      thunk_FUN_00220358(0);
    }
    else {
      ((code*)DAT_0804c088)();
    }
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08015b94 */
void FUN_08015b94(param_1)
undefined4 param_1;
{
  int iVar1;
  
  iVar1 = FUN_08015bc0();
                    /* WARNING: Could not recover jumptable at 0x08015ba6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(iVar1 + 4) + 0x28))(param_1);
  return;
}




/* 0x08015ba8 */
void FUN_08015ba8(param_1)
undefined4 param_1;
{
  int iVar1;
  
  iVar1 = FUN_08015bc0();
                    /* WARNING: Could not recover jumptable at 0x08015bba. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(iVar1 + 4) + 8))(param_1);
  return;
}




/* 0x080163a8 */
void FUN_080163a8()
{
  int iVar1;
  
  iVar1 = thunk_FUN_0800de54(&DAT_0804cd58,4);
  if (iVar1 != 0) {
    ((code*)DAT_0804cd60)("boot_error_handler.c",0x244,0x302e);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return;
}




/* 0x080163e8 */
void FUN_080163e8(param_1)
int param_1;
{
  int iVar1;
  
  iVar1 = FUN_0801688c();
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 0x18) = 0;
    *(undefined4 *)(iVar1 + 0x14) = 0;
    if (*(int *)(param_1 + 0x10) == 0) {
      *(undefined4 *)(iVar1 + 0x10) = 0;
      return;
    }
    *(undefined4 *)(iVar1 + 0x10) = *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x10);
  }
  return;
}




/* 0x08016408 */
void FUN_08016408(param_1, param_2, param_3)
int param_1; int param_2; int * param_3;
{
  if ((param_1 != 0) && (param_3 != (int *)0x0)) {
    *param_3 = param_1;
    param_3[1] = param_2;
    param_3[2] = (int)DAT_0804cd54;
    DAT_0804cd54 = param_3;
    return;
  }
  ((code*)DAT_0804cd60)("boot_error_handler.c",0x156,0x3003);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08016484 */
undefined4 FUN_08016484(param_1)
undefined4 param_1;
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0x302e;
  if ((DAT_08052c50 != (code *)0x0) && (iVar1 = ((code*)DAT_08052c50)(1,param_1), iVar1 == 0)) {
    uVar2 = 0;
  }
  return uVar2;
}




/* 0x080164a4 */
void FUN_080164a4(param_1, param_2)
uint * param_1; uint param_2;
{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  
  if (0x4000 < param_2) {
    puVar3 = param_1 + 0x1000;
    DAT_0804cd24 = param_2 - 0x4000 >> 10;
    puVar2 = (uint *)((int)puVar3 + (param_2 - 0x4000));
    DAT_0804cd20 = puVar3;
    do {
      if (*(uint*)DAT_0804cd20 == 0) {
        do {
          if (puVar3 <= param_1) {
            FUN_08007b30();
            return;
          }
          if ((*param_1 & 1) != 0) {
            puVar1 = (uint *)(*param_1 & 0xcff);
            if (DAT_0804cd24 == 0) {
              DAT_0804cd20 = (uint *)0x0;
              return;
            }
            DAT_0804cd24 = DAT_0804cd24 - 1;
            if (DAT_0804cd20 < puVar1) {
              FUN_08030b34(DAT_0804cd20,puVar1,0x400);
              FUN_08007f08(puVar1,0x400,0);
              *param_1 = *param_1 & 0xcff | (uint)DAT_0804cd20 & 0xfffff300;
              while (*(uint*)DAT_0804cd20 != 0) {
                DAT_0804cd20 = DAT_0804cd20 + 0x100;
                if (puVar2 <= DAT_0804cd20) {
                  DAT_0804cd20 = (uint *)0x0;
                  DAT_0804cd24 = 0;
                  return;
                }
              }
            }
          }
          param_1 = param_1 + 1;
        } while( true );
      }
      DAT_0804cd20 = DAT_0804cd20 + 0x100;
    } while (DAT_0804cd20 < puVar2);
  }
  DAT_0804cd24 = 0;
  DAT_0804cd20 = (uint *)0x0;
  return;
}




