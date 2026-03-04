/* Auto-generated: boot_flash_trans_sdcc.c */
/* Functions: 4 */
#include "globals.h"

/* 0x08015e58 */
void FUN_08015e58(param_1)
int * param_1;
{
  short sVar1;
  int iVar2;
  
  if (param_1 == (int *)0x0) {
    ((code*)DAT_0804cd60)("boot_flash_trans_sdcc.c",0x151,0x3003);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  while (*param_1 != 0x80543ac) {
    if (true) {
      ((code*)DAT_0804cd60)("boot_flash_trans_sdcc.c",0x16e,0x302f);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
  }
  if (DAT_080543f0 == '\0') {
    ((code*)DAT_0804cd60)("boot_flash_trans_sdcc.c",0x157);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (DAT_080543e4 == 1) {
    sVar1 = (short)DAT_080543e0;
    iVar2 = FUN_08015c88();
    (**(code **)(*(int *)(iVar2 + 4) + 0x24))((int)sVar1);
  }
  if (DAT_080543e4 == 0) {
    iVar2 = FUN_08015c88();
    (**(code **)(*(int *)(iVar2 + 4) + 0x20))(0x1b);
  }
  DAT_080543f0 = 0;
  *param_1 = 0;
  return;
}




/* 0x08015f10 */
undefined4 * FUN_08015f10()
{
  if (DAT_0804d3e4 == '\0') {
    DAT_080543a4 = &DAT_08039968;
    DAT_080543a8 = &DAT_0804d3e8;
    FUN_08007f08(&DAT_080543f0,0,1);
    DAT_0804d3e4 = '\x01';
  }
  return &DAT_080543a4;
}




/* 0x08015f40 */
undefined4 * FUN_08015f40(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)0x0;
  do {
    if (DAT_080543f0 == '\0') {
      puVar1 = (undefined4 *)0x80543ac;
      DAT_080543f0 = '\x01';
      break;
    }
  } while (false);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = &DAT_08039960;
    puVar1[1] = &DAT_0804d3f0;
    FUN_0801476c(puVar1 + 2);
    puVar1[0xd] = param_1;
    puVar1[0xe] = param_2;
    puVar1[0xf] = 0;
    puVar1[0x10] = 0;
    return puVar1;
  }
  ((code*)DAT_0804cd60)("boot_flash_trans_sdcc.c",0x12a,0x3045);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08015fcc */
undefined4 FUN_08015fcc(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; int param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar2 = 0;
  if (param_1 != 0) {
    iVar1 = FUN_08014694(param_1 + 8,param_2,param_4,param_4,param_4);
    uVar2 = 0;
    if (iVar1 != 0) {
      if (param_4 == 0) {
        uVar2 = 1;
      }
      else {
        uVar3 = *(undefined4 *)(param_1 + 0x34);
        uVar2 = *(undefined4 *)(param_1 + 0x38);
        iVar1 = FUN_08015c88();
        uVar2 = (**(code **)(*(int *)(iVar1 + 4) + 0x2c))(param_2,param_3,param_4,uVar3,uVar2);
      }
      if (*(code **)(param_1 + 0x3c) != (code *)0x0) {
        (**(code **)(param_1 + 0x3c))(*(undefined4 *)(param_1 + 0x40),param_2,param_4);
      }
    }
  }
  return uVar2;
}




