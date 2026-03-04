/* Auto-generated: boot_logger_ram.c */
/* Functions: 1 */
#include "globals.h"

/* 0x08016760 */
void FUN_08016760(param_1, param_2, param_3, param_4, param_5, param_6)
int * param_1; int param_2; uint param_3; int * param_4; int param_5; uint param_6;
{
  if ((((param_2 != 0) && (param_1 != (int *)0x0)) && (param_5 != 0)) &&
     ((param_4 != (int *)0x0 && (param_6 <= param_3)))) {
    FUN_08030b34(param_1,param_4,0x1c);
    FUN_08030b34(param_2,param_5,param_6);
    FUN_08007f08(param_2 + param_6,0,param_3 - param_6);
    param_1[2] = param_3;
    *param_1 = param_2;
    param_1[1] = (param_4[1] - *param_4) + param_2;
    return;
  }
  ((code*)DAT_0804cd60)("boot_logger_ram.c",0x198,0x300d);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




