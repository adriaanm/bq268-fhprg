/* Auto-generated: boot_authenticator.c */
/* Functions: 7 */
#include "globals.h"

/* Non-extern globals defined here (declared extern in globals.h) */
uint _local_10;
uint _local_18;
uint _local_20;
uint _local_24;
uint _local_60;

/* 0x08014364 */
void FUN_08014364(param_1)
int param_1;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  if (param_1 == 0) {
    ((code*)DAT_0804cd60)("boot_authenticator.c",0x18e,0x3003);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar2 = *(uint *)(param_1 + 0x20);
  uVar1 = *(uint *)(param_1 + 0xc);
  if (((uVar2 < uVar1) || (uVar3 = *(int *)(param_1 + 0x24) + uVar2, uVar3 < uVar2)) ||
     (uVar5 = uVar1 + *(int *)(param_1 + 0x10), uVar5 < uVar3)) {
    ((code*)DAT_0804cd60)("boot_authenticator.c",0x192);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar3 = *(uint *)(param_1 + 0x18);
  if (((uVar3 < uVar1) || (uVar4 = *(int *)(param_1 + 0x1c) + uVar3, uVar4 < uVar3)) ||
     (uVar5 < uVar4)) {
    ((code*)DAT_0804cd60)("boot_authenticator.c",0x198,0x3064);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (CARRY4(uVar1,*(uint *)(param_1 + 0x14))) {
    ((code*)DAT_0804cd60)("boot_authenticator.c",0x19e,0x3006);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (uVar3 < uVar1 + *(uint *)(param_1 + 0x14)) {
    ((code*)DAT_0804cd60)("boot_authenticator.c",0x1a0);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (uVar2 < uVar4) {
    ((code*)DAT_0804cd60)("boot_authenticator.c",0x1a6,0x3065);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_08007f08(&DAT_08052bc0,0,0x28);
  DAT_08052bc0 = param_1;
  DAT_08052bc4 = 0x28;
  DAT_08052bc8 = *(undefined4 *)(param_1 + 0xc);
  DAT_08052bcc = *(undefined4 *)(param_1 + 0x14);
  DAT_08052bd0 = *(undefined4 *)(param_1 + 0x20);
  DAT_08052bd4 = *(undefined4 *)(param_1 + 0x24);
  DAT_08052bd8 = *(undefined4 *)(param_1 + 0x18);
  DAT_08052bdc = *(undefined4 *)(param_1 + 0x1c);
  return;
}




/* 0x08014480 */
void FUN_08014480()
{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  while ((iVar1 = thunk_boot_temp_check_init(), iVar1 == 4 || (iVar1 == 3))) {
    thunk_FUN_080199b4(500000);
    uVar2 = uVar2 + 1;
    if (0x27 < uVar2) {
      if (false) {
        return;
      }
      ((code *)&LAB_00220310)();
      return;
    }
  }
  return;
}




/* 0x08019408 */
void FUN_08019408(param_1, param_2)
int * param_1; int param_2;
{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int local_20;
  
  iVar1 = DAT_0804cea0;
  piVar3 = (int *)(DAT_0804cea0 + 0x834);
  piVar4 = *(int **)(*param_1 + 0x20);
  local_20 = 0;
  iVar2 = FUN_08016484(&local_20);
  if (iVar2 != 0) {
    ((code*)DAT_0804cd60)("boot_authenticator.c",0x23f,0x302e);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (local_20 == 1) {
    if (piVar4 == (int *)0x0) {
      ((code*)DAT_0804cd60)("boot_authenticator.c",0x245,0x300d);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (piVar4 <= piVar3) {
      ((code*)DAT_0804cd60)("boot_authenticator.c",0x246);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if ((int *)(iVar1 + 0x934) <= piVar4) {
      ((code*)DAT_0804cd60)("boot_authenticator.c",0x24a);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if ((int *)(iVar1 + 0x934) <= piVar3) {
      ((code*)DAT_0804cd60)("boot_authenticator.c",0x24e);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (((int)piVar3 - (int)piVar4 & 0xffU) < 0x2c) {
      ((code*)DAT_0804cd60)("boot_authenticator.c",0x256,0x305b);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    FUN_08030b34(piVar4,param_2 + 0x1c,0x2c);
    *(int **)(*param_1 + 0x20) = piVar4 + 0xb;
    *piVar3 = *piVar3 + 1;
  }
  return;
}




/* 0x080194dc */
int FUN_080194dc(param_1)
char * param_1;
{
  char *pcVar1;
  
  for (pcVar1 = param_1; *pcVar1 != '\0'; pcVar1 = pcVar1 + 1) {
  }
  return (int)pcVar1 - (int)param_1;
}




/* 0x08019524 */
undefined4 FUN_08019524()
{
  undefined4 uVar1;
  
  uVar1 = 1;
  DAT_0804ced0 = FUN_08016180();
  if (DAT_0804cedc <= (uint)(DAT_0804ced0 - DAT_0804ced4)) {
    DAT_0804ced8 = (uint)(DAT_0804ced8 == 0);
    uVar1 = FUN_08015a3c();
    DAT_0804ced4 = DAT_0804ced0;
  }
  return uVar1;
}




/* 0x08019558 */
void FUN_08019558()
{
  DAT_0804ced4 = FUN_08016180();
  return;
}




/* 0x080195a4 */
void FUN_080195a4(param_1)
uint param_1;
{
  uint uVar1;
  
  if (param_1 == 0) {
    ((code*)DAT_0804cd60)("boot_authenticator.c",0x1f9,0x3003);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar1 = param_1 + 0x28;
  if (uVar1 < param_1) {
    ((code*)DAT_0804cd60)("boot_authenticator.c",0x1fb);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (CARRY4(DAT_08052bc8,DAT_08052bcc)) {
    ((code*)DAT_0804cd60)("boot_authenticator.c",0x1fd);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (CARRY4(DAT_08052bd8,DAT_08052bdc)) {
    ((code*)DAT_0804cd60)("boot_authenticator.c",0x1ff,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  DAT_08052bc8 = uVar1;
  DAT_08052bd8 = uVar1 + DAT_08052bcc;
  DAT_08052bd0 = uVar1 + DAT_08052bcc + DAT_08052bdc;
  return;
}



/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

