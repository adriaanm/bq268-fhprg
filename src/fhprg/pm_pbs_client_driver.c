/* Auto-generated: pm_pbs_client_driver.c */
/* Functions: 1 */
#include "globals.h"

/* 0x0802ca18 */
void FUN_0802ca18(param_1, param_2, param_3)
undefined4 param_1; int param_2; uint param_3;
{
  char cVar1;
  int iVar2;
  undefined4 *local_20;
  undefined4 local_1c [2];
  
  local_1c[0] = 0x7a;
  local_1c[1] = 0x7b;
  if ((*(char *)(param_2 + 3) == '\b') &&
     (local_20 = *(undefined4 **)(&DAT_0805a248 + param_3 * 4), local_20 == (undefined4 *)0x0)) {
    FUN_0802c644(0xc,&local_20);
    *local_20 = param_1;
    iVar2 = FUN_0802e824(0x1f);
    local_20[1] = iVar2;
    if (iVar2 == 0) {
      ((code*)DAT_0804cd60)("pm_pbs_client_driver.c",0x3f,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (1 < param_3) {
      ((code*)DAT_0804cd60)("pm_pbs_client_driver.c",0x42,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    cVar1 = FUN_0802e848(local_1c[param_3],param_3);
    *(char *)(local_20 + 2) = cVar1;
    if (cVar1 == '\0') {
      ((code*)DAT_0804cd60)("pm_pbs_client_driver.c",0x45,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *(undefined4 **)(&DAT_0805a248 + param_3 * 4) = local_20;
  }
  return;
}




