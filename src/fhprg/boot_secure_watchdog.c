/* Auto-generated: boot_secure_watchdog.c */
/* Functions: 1 */
#include "globals.h"

/* 0x08018e18 */
void FUN_08018e18()
{
  int iVar1;
  undefined4 local_8;
  
  local_8 = 0;
  iVar1 = FUN_08016484(&local_8);
  if (iVar1 != 0) {
    ((code*)DAT_0804cd60)("boot_secure_watchdog.c",0x4c,0x302e);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  _DAT_01814000 = _DAT_01814000 & 0xcfffff;
  _DAT_01940000 = &DAT_00220000;
  return;
}




