/* Auto-generated: boot_raw_partition_ramdump.c */
/* Functions: 2 */
#include "globals.h"

/* 0x08017950 */
undefined4 FUN_08017950()
{
  FUN_08015a3c(1);
  ((code*)DAT_0804cd60)("boot_raw_partition_ramdump.c",0x73,0x3060);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08019848 */
void FUN_08019848(param_1)
uint param_1;
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  
  uVar2 = FUN_0801c260();
  uVar3 = FUN_0801c238(param_1 & 0xff);
  iVar1 = param_1 * 0x40;
  if (uVar2 < 0x1000) {
    FUN_08006e1a(3,iVar1 + -0x7838cafc);
  }
  else {
    if (uVar2 < 0x8000000) {
      uVar4 = 3;
    }
    else {
      uVar4 = 1;
    }
    FUN_08006e1a(uVar4,iVar1 + -0x7838cafc);
    FUN_08006e5e(uVar3,0,param_1 * 0x40 + -0x7838cae8);
  }
  FUN_08006e1a(0x1000,iVar1 + -0x7838cb00);
  FUN_08006e5e(DAT_0804ce20,DAT_0804ce24,iVar1 + -0x7838caf8);
  FUN_08006e5e(uVar2,0,iVar1 + -0x7838caf0);
  iVar5 = FUN_0801bfdc(param_1 & 0xff);
  if (iVar5 != 0) {
    FUN_080382c2(iVar1 + -0x7838cad8,iVar5,0x14);
    return;
  }
  ((code*)DAT_0804cd60)("boot_raw_partition_ramdump.c",0x139,0x300d);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

