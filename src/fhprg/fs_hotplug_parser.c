/* Auto-generated: fs_hotplug_parser.c */
/* Functions: 1 */
#include "globals.h"

/* 0x0802ef24 */
undefined4 FUN_0802ef24(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; undefined4 * param_3; uint param_4;
{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = param_3[4];
  if (param_4 == 0) {
    ((code*)DAT_0804cd60)("fs_hotplug_parser.c",0x135,0x302f,DAT_0804cd60,0);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if ((uint)param_3[5] < param_4) {
    param_4 = param_3[5];
  }
  if (param_2 == 0 && ((uint)param_3[3] <= param_1) <= param_2) {
    uVar1 = param_3[3] - param_1;
    if (uVar1 < param_4) {
      param_4 = uVar1;
    }
    param_3[6] = 0;
    iVar2 = FUN_08013ca4(*param_3,param_3[1],param_1,uVar3,param_4 & 0xffff);
    if (iVar2 == 0) {
      param_3[6] = param_4;
      param_3[8] = param_1;
      param_3[9] = param_2;
      return uVar3;
    }
  }
  return 0;
}




