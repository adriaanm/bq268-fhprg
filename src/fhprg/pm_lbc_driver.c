/* Auto-generated: pm_lbc_driver.c */
/* Functions: 2 */
#include "globals.h"

/* 0x0802bdf4 */
void FUN_0802bdf4(param_1, param_2)
undefined4 param_1; uint param_2;
{
  char cVar1;
  int iVar2;
  undefined4 *local_20;
  undefined4 local_1c [2];
  
  local_1c[0] = 0x7e;
  local_1c[1] = 0x80;
  local_20 = *(undefined4 **)(&DAT_0805a3c4 + param_2 * 4);
  if (local_20 == (undefined4 *)0x0) {
    FUN_0802c644(0xc,&local_20);
    *local_20 = param_1;
    iVar2 = FUN_0802e824(0x29);
    local_20[1] = iVar2;
    if (iVar2 == 0) {
      ((code*)DAT_0804cd60)("pm_lbc_driver.c",0x3d,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (1 < param_2) {
      ((code*)DAT_0804cd60)("pm_lbc_driver.c",0x40,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    cVar1 = FUN_0802e848(local_1c[param_2],param_2);
    *(char *)(local_20 + 2) = cVar1;
    if (cVar1 == '\0') {
      ((code*)DAT_0804cd60)("pm_lbc_driver.c",0x43,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *(undefined4 **)(&DAT_0805a3c4 + param_2 * 4) = local_20;
  }
  return;
}




/* 0x0802be90 */
undefined4 FUN_0802be90(param_1)
uint param_1;
{
  if (param_1 < 7) {
    return *(undefined4 *)(&DAT_0805a3c4 + param_1 * 4);
  }
  return 0;
}




