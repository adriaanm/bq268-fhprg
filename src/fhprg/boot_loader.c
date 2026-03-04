/* Auto-generated: boot_loader.c */
/* Functions: 1 */
#include "globals.h"

/* 0x080165d8 */
void FUN_080165d8(param_1, param_2)
int param_1; int * param_2;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int local_48;
  int local_44 [10];
  
  uVar5 = 0;
  if (param_2 == (int *)0x0) {
    param_2 = local_44;
  }
  local_48 = FUN_08015c72();
  if (local_48 == 0) {
    ((code*)DAT_0804cd60)("boot_loader.c",0xb5,0x300d);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar1 = FUN_08015bc0();
  iVar1 = (**(code **)(*(int *)(iVar1 + 4) + 0x10))(param_1,param_2);
  if (iVar1 == 0) {
    FUN_0801453c(local_48 + 8,param_2,0x28);
    iVar1 = FUN_08015e28(local_48,param_2,0,0x28);
    FUN_080147d4(local_48 + 8,param_2,0x28);
    if ((param_1 != 0x1b) && ((iVar1 == 0 || (*param_2 != param_1)))) {
      ((code*)DAT_0804cd60)("boot_loader.c",0xd1,0x302f);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    uVar5 = param_2[2] + 0x28;
    if (uVar5 <= (uint)param_2[2]) {
      ((code*)DAT_0804cd60)("boot_loader.c",0xd8,0x3007);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
  }
  uVar4 = param_2[4];
  if (uVar4 == 0) {
    ((code*)DAT_0804cd60)("boot_loader.c",0xde,0x3005);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar2 = param_2[9] + param_2[5];
  if (((uint)param_2[5] <= uVar2) && (uVar3 = uVar2 + param_2[7], !CARRY4(uVar2,param_2[7]))) {
    if ((uVar3 & 3) == 0) {
      if (uVar4 != uVar3) {
        ((code*)DAT_0804cd60)("boot_loader.c",0xf2,0x3007);
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
    }
    else if (uVar4 != (uVar3 - (uVar3 & 3)) + 4) {
      ((code*)DAT_0804cd60)("boot_loader.c",0xf7,0x3007);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar1 = FUN_08015e28(local_48,param_2[3],uVar5);
    if (iVar1 == 0) {
      ((code*)DAT_0804cd60)("boot_loader.c",0x105,0x302f);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    FUN_08015ba8(&local_48);
    return;
  }
  ((code*)DAT_0804cd60)("boot_loader.c",0xe5,0x3006);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




