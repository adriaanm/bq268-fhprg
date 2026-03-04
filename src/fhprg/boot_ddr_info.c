/* Auto-generated: boot_ddr_info.c */
/* Functions: 5 */
#include "globals.h"

/* 0x080160d0 */
undefined4 * FUN_080160d0()
{
  if (DAT_0804cea4 != '\x01') {
    ((code*)DAT_0804cd60)("boot_ddr_info.c",0x106,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return &DAT_08052ba8;
}




/* 0x08018f2c */
void FUN_08018f2c(param_1)
int * param_1;
{
  undefined4 *puVar1;
  
  if (((param_1 != (int *)0x0) && (*param_1 != 0)) &&
     (puVar1 = *(undefined4 **)(*param_1 + 8), puVar1 != (undefined4 *)0x0)) {
    DAT_08052ba8 = *puVar1;
    DAT_08052bac = puVar1[1];
    DAT_08052bb0 = puVar1[2];
    DAT_0804cea4 = 1;
    return;
  }
  ((code*)DAT_0804cd60)("boot_ddr_info.c",0xe4,0x3003);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08018f7c */
undefined4 FUN_08018f7c(param_1)
int param_1;
{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 == 1) {
    DAT_0804cdf8 = 0x14;
    DAT_0804cdf4 = param_1;
  }
  else if (param_1 == 2) {
    DAT_0804cdf8 = 0x20;
    DAT_0804cdf4 = param_1;
  }
  else {
    uVar1 = 0x305f;
  }
  return uVar1;
}




/* 0x08018fa4 */
void FUN_08018fa4(param_1)
undefined1 param_1;
{
  DAT_0804cdec = param_1;
  return;
}




/* 0x08019094 */
void FUN_08019094(param_1, param_2, param_3)
int * param_1; int * param_2; undefined4 * param_3;
{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  if (param_1 != (int *)0x0) {
    param_1[1] = (int)&DAT_08052aa8;
    param_1[2] = (int)&DAT_08052b28;
    *param_1 = 0;
    if (*param_2 != 0) {
      DAT_08052ab4 = 0;
      iVar1 = param_2[5];
      piVar2 = (int *)(param_1[1] + *param_1 * 0x10);
      DAT_08052ab0 = *param_2;
      *piVar2 = param_2[4];
      piVar2[1] = iVar1;
      *(undefined4 *)(param_1[2] + *param_1 * 0x10) = *param_3;
      puVar3 = (undefined4 *)(param_1[2] + *param_1 * 0x10 + 8);
      *puVar3 = param_3[1];
      puVar3[1] = 0;
      *param_1 = *param_1 + 1;
    }
    if (param_2[1] != 0) {
      piVar2 = (int *)(param_1[1] + *param_1 * 0x10 + 8);
      *piVar2 = param_2[1];
      piVar2[1] = 0;
      iVar1 = param_2[7];
      piVar2 = (int *)(param_1[1] + *param_1 * 0x10);
      *piVar2 = param_2[6];
      piVar2[1] = iVar1;
      *(undefined4 *)(param_1[2] + *param_1 * 0x10) = param_3[2];
      puVar3 = (undefined4 *)(param_1[2] + *param_1 * 0x10 + 8);
      *puVar3 = param_3[3];
      puVar3[1] = 0;
      *param_1 = *param_1 + 1;
    }
    if (param_2[2] != 0) {
      piVar2 = (int *)(param_1[1] + *param_1 * 0x10 + 8);
      *piVar2 = param_2[2];
      piVar2[1] = 0;
      iVar1 = param_2[9];
      piVar2 = (int *)(param_1[1] + *param_1 * 0x10);
      *piVar2 = param_2[8];
      piVar2[1] = iVar1;
      *(undefined4 *)(param_1[2] + *param_1 * 0x10) = param_3[4];
      puVar3 = (undefined4 *)(param_1[2] + *param_1 * 0x10 + 8);
      *puVar3 = param_3[5];
      puVar3[1] = 0;
      *param_1 = *param_1 + 1;
    }
    if (param_2[3] != 0) {
      piVar2 = (int *)(param_1[1] + *param_1 * 0x10 + 8);
      *piVar2 = param_2[3];
      piVar2[1] = 0;
      iVar1 = param_2[0xb];
      piVar2 = (int *)(param_1[1] + *param_1 * 0x10);
      *piVar2 = param_2[10];
      piVar2[1] = iVar1;
      *(undefined4 *)(param_1[2] + *param_1 * 0x10) = param_3[6];
      puVar3 = (undefined4 *)(param_1[2] + *param_1 * 0x10 + 8);
      *puVar3 = param_3[7];
      puVar3[1] = 0;
      *param_1 = *param_1 + 1;
    }
    return;
  }
  ((code*)DAT_0804cd60)("boot_ddr_info.c",0x9d,0x300d);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




