/* Auto-generated: fs_blockdev_devnull_driver.c */
/* Functions: 1 */
#include "globals.h"

/* 0x08013acc */
void FUN_08013acc(param_1, param_2)
undefined4 * param_1; short * param_2;
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_08013ab0();
  if (iVar1 != 0) {
    iVar2 = 0;
    do {
      iVar3 = iVar2 + -1;
      (&DAT_080511c2)[iVar2 * 0xc] = *param_2;
      *param_2 = *param_2 + 1;
      (&DAT_080511b8)[iVar2 * 6] = iVar1;
      (&DAT_080511bc)[iVar2 * 6] = *param_1;
      *param_1 = &DAT_080511b4 + iVar2 * 0x18;
      iVar2 = iVar3;
    } while (-1 < iVar3);
    return;
  }
  ((code*)DAT_0804cd60)("fs_blockdev_devnull_driver.c",0x45,0x302f);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




