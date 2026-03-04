/* Auto-generated: fs_blockdev_sd_driver.c */
/* Functions: 7 */
#include "globals.h"

/* 0x08013d48 */
void FUN_08013d48(param_1, param_2)
undefined4 * param_1; short * param_2;
{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  
  FUN_08013d44();
  iVar3 = FUN_08013f00();
  if (iVar3 != 0) {
    iVar5 = 3;
    do {
      iVar1 = iVar5 * 0x18;
      iVar2 = iVar5 * 6;
      *(short *)(iVar1 + 0x80511fa) = *param_2;
      *param_2 = *param_2 + 1;
      *(int *)(iVar1 + 0x80511f0) = iVar3;
      uVar4 = FUN_08013dc8(iVar5);
      *(undefined4 *)(iVar1 + 0x80511fc) = uVar4;
      iVar5 = iVar5 + -1;
      *(undefined4 *)(iVar1 + 0x80511f4) = *param_1;
      *param_1 = &PTR_s__hdev_sdc1_080511ec + iVar2;
    } while (-1 < iVar5);
    return;
  }
  ((code*)DAT_0804cd60)("fs_blockdev_sd_driver.c",0x57,0x302f);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08013dc8 */
int FUN_08013dc8(param_1)
uint param_1;
{
  if (3 < param_1) {
    FUN_08015a50();
  }
  return param_1 * 4 + 0x80514ac;
}



undefined ** FUN_08013f00()
{
  return &PTR_LAB_08013fc4_1_080514bc;
}




/* 0x080141ec */
undefined4 FUN_080141ec(param_1, param_2, param_3, param_4, param_5)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4; undefined4 param_5;
{
  undefined4 uVar1;
  
  if ((param_1 == 0) || (*(int *)(param_1 + 0x14) != 0xd00cafe)) {
    uVar1 = 0xffffffff;
  }
  else {
    FUN_08025eb4(1,param_5,param_3,param_4,param_4);
    uVar1 = (**(code **)(*(int *)(param_1 + 4) + 0x10))(param_1,param_2,param_3,param_4,param_5);
  }
  return uVar1;
}




/* 0x0801422c */
undefined4 FUN_0801422c(param_1, param_2, param_3, param_4, param_5)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4; undefined4 param_5;
{
  undefined4 uVar1;
  
  if ((param_1 == 0) || (*(int *)(param_1 + 0x14) != 0xd00cafe)) {
    uVar1 = 0xffffffff;
  }
  else {
    FUN_08025eb4(1,param_5,param_3,param_4,param_4);
    uVar1 = (**(code **)(*(int *)(param_1 + 4) + 0xc))(param_1,param_2,param_3,param_4,param_5);
  }
  return uVar1;
}




/* 0x08014298 */
void FUN_08014298(param_1)
int param_1;
{
                    /* WARNING: Could not recover jumptable at 0x0801429c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(param_1 + 4) + 0x34))();
  return;
}




/* 0x0801429e */
void FUN_0801429e(param_1)
int param_1;
{
                    /* WARNING: Could not recover jumptable at 0x080142a2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(param_1 + 4) + 0x30))();
  return;
}




/* 0x080142b8 */
int FUN_080142b8(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  int iVar1;
  undefined1 auStack_220 [512];
  undefined4 local_20 [2];
  
  FUN_08006d14(auStack_220,0x200);
  local_20[0] = 0;
  if (((DAT_08052c68 == (code *)0x0) || (DAT_08052c6c == (code *)0x0)) || (DAT_08052c70 == 0)) {
    iVar1 = 0x3003;
  }
  else {
    FUN_08007f08(&DAT_08052c00,0,0x50);
    iVar1 = FUN_08017a2c(param_2,local_20);
    if (iVar1 == 0) {
      DAT_08052be4 = local_20[0];
      DAT_08052be0 = param_2;
      iVar1 = ((code*)DAT_08052c68)(0,auStack_220);
      if (((iVar1 == 0) &&
          (iVar1 = FUN_080354d0(1,&DAT_08052bc0,&DAT_08052c00,&DAT_08052c68,&DAT_08052c50,0),
          iVar1 == 0)) && (iVar1 = ((code*)DAT_08052c6c)(auStack_220), iVar1 == 0)) {
        FUN_08019408(param_1,&DAT_08052c00);
        iVar1 = FUN_08017b04(param_2,DAT_08052c0c);
        return iVar1;
      }
      iVar1 = 0x302e;
    }
  }
  return iVar1;
}




