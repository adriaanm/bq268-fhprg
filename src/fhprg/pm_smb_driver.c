/* Auto-generated: pm_smb_driver.c */
/* Functions: 1 */
#include "globals.h"

/* 0x0802dc48 */
void pm_smb1360_init()
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_08021cb4();
  iVar2 = FUN_08021cfc();
  if (DAT_0805085c == (int *)0x0) {
    FUN_0802c644(8,&DAT_0805085c);
    iVar3 = FUN_0802e86c(0x3d);
    if (iVar3 == 0) {
      ((code*)DAT_0804cd60)("pm_smb_driver.c",0x7f,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *(uint*)DAT_0805085c = iVar3;
    iVar3 = FUN_0802dce0(*(undefined1 *)(iVar3 + 0x10));
    ((uint*)&DAT_0805085c)[1] = iVar3;
  }
  if (iVar1 == 0 && iVar2 == 0) {
    *(undefined1 *)*(uint*)DAT_0805085c = 0x70;
    boot_log_message("smb1360:LT32_EVT slave_address=0x70");
    return;
  }
  return;
}




