/* Auto-generated: boot_flash_dev_sdcc_if.c */
/* Functions: 2 */
#include "globals.h"

/* 0x08015c88 */
undefined4 FUN_08015c88()
{
  if (DAT_0804df08 == 0) {
    ((code*)DAT_0804cd60)("boot_flash_dev_sdcc_if.c",0x2a,0x300d);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return 0;
}




/* 0x08015cc8 */
void FUN_08015cc8(param_1)
int param_1;
{
  if ((DAT_0804df04 == '\0') && (param_1 != 0)) {
    DAT_0804df08 = param_1;
    return;
  }
  ((code*)DAT_0804cd60)("boot_flash_dev_sdcc_if.c",0x2a,0x300d);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




