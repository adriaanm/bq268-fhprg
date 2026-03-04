/* Auto-generated: boot_flash_dev_if.c */
/* Functions: 5 */
#include "globals.h"

/* 0x08015bc0 */
undefined4 FUN_08015bc0()
{
  if (DAT_0804ce08 == 0) {
    ((code*)DAT_0804cd60)("boot_flash_dev_if.c",0x2a,0x300d);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return 0;
}




/* 0x08015c34 */
void FUN_08015c34(param_1)
int param_1;
{
  if ((DAT_0804ce04 == '\0') && (param_1 != 0)) {
    DAT_0804ce08 = param_1;
    return;
  }
  ((code*)DAT_0804cd60)("boot_flash_dev_if.c",0x2a,0x300d);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08015c72 */
undefined4 FUN_08015c72(param_1)
undefined4 param_1;
{
  int iVar1;
  
  iVar1 = FUN_08015bc0();
                    /* WARNING: Could not recover jumptable at 0x08015c84. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code *)**(undefined4 **)(iVar1 + 4))(param_1);
  return 0;
}




/* 0x08015dc4 */
void FUN_08015dc4(param_1)
int param_1;
{
  int iVar1;
  undefined4 unaff_r4 = 0;
  undefined4 unaff_lr = 0;
  
  if (param_1 == 0) {
    ((code*)DAT_0804cd60)("boot_flash_target.c",0x59,0x3003);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar1 = FUN_08016e54();
  if ((iVar1 != 2) && (((iVar1 == 4 || (iVar1 == 5)) || (iVar1 == 8)))) {
    FUN_08015d0c(iVar1,0x8015f11,param_1);
  }
  iVar1 = FUN_08019964();
  if (iVar1 != 0) {
    if (DAT_0804ce08 == 0) {
      ((code*)DAT_0804cd60)("boot_flash_dev_if.c",0x2a,0x300d,DAT_0804cd60,unaff_r4,unaff_lr);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    DAT_0804ce04 = 1;
    return;
  }
  return;
}




/* 0x08015e28 */
int FUN_08015e28(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  
  FUN_080192d0();
  iVar1 = ((code *)**(undefined4 **)(param_1 + 4))(param_1,param_2,param_3,param_4);
  if (iVar1 != 0) {
    FUN_080192e0(param_4);
  }
  return iVar1;
}




