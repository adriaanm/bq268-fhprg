/* Auto-generated: boot_dload_debug.c */
/* Functions: 1 */
#include "globals.h"

/* 0x0801c294 */
undefined4 FUN_0801c294()
{
  int iVar1;
  undefined4 uVar2;
  int local_10;
  
  uVar2 = 0;
  local_10 = 0;
  iVar1 = FUN_08016484(&local_10);
  if (iVar1 != 0) {
    ((code*)DAT_0804cd60)("boot_dload_debug.c",0x2cf,0x302e);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (((local_10 != 1) || (iVar1 = thunk_FUN_08030c10(&DAT_08051b90), iVar1 != 0)) ||
     (iVar1 = thunk_FUN_08030c2c(&DAT_08051b90), iVar1 != 0)) {
    uVar2 = 1;
  }
  return uVar2;
}




