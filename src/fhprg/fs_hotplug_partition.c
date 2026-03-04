/* Auto-generated: fs_hotplug_partition.c */
/* Functions: 4 */
#include "globals.h"

/* 0x08026b44 */
void FUN_08026b44(param_1)
int * param_1;
{
  if (param_1 == (int *)0x0) {
    ((code*)DAT_0804cd60)("fs_hotplug_partition.c",0x4b,0x302f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (*param_1 < 1) {
    ((code*)DAT_0804cd60)("fs_hotplug_partition.c",0x4c);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  *param_1 = *param_1 + 1;
  return;
}




/* 0x08026b88 */
void FUN_08026b88(param_1)
int * param_1;
{
  int iVar1;
  
  if (param_1 == (int *)0x0) {
    ((code*)DAT_0804cd60)("fs_hotplug_partition.c",0x54,0x302f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (*param_1 < 1) {
    ((code*)DAT_0804cd60)("fs_hotplug_partition.c",0x55);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar1 = *param_1 + -1;
  *param_1 = iVar1;
  if (iVar1 < 1) {
    if (DAT_0804e2a4 < 1) {
      FUN_08015a50();
    }
    DAT_0804e2a4 = DAT_0804e2a4 + -1;
    FUN_08006d14(param_1,0x4c);
    return;
  }
  return;
}




/* 0x08026bf4 */
int thunk_FUN_08026bf4(param_1, param_2)
int param_1; undefined4 param_2;
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = -1;
  if (param_1 != 0) {
    iVar1 = FUN_0801cc80();
    if (iVar1 != 0) {
      FUN_08015a50();
    }
    iVar1 = FUN_08026d00(param_1,param_2);
    if (iVar1 != 0) {
      FUN_08015a50();
    }
    iVar1 = FUN_080267cc(param_1,3,param_2);
    if (iVar1 != 0) {
      do {
        iVar2 = FUN_080265a8(iVar1);
        if (iVar2 == 0) break;
        iVar3 = FUN_0801cfc8(&DAT_08026c5c,"/mmc1","extfs",0,iVar2);
      } while (iVar3 != 0);
      FUN_08026594(iVar1);
    }
  }
  return iVar3;
}




/* 0x08026bf4 */
int FUN_08026bf4(param_1, param_2)
int param_1; undefined4 param_2;
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = -1;
  if (param_1 != 0) {
    iVar1 = FUN_0801cc80();
    if (iVar1 != 0) {
      FUN_08015a50();
    }
    iVar1 = FUN_08026d00(param_1,param_2);
    if (iVar1 != 0) {
      FUN_08015a50();
    }
    iVar1 = FUN_080267cc(param_1,3,param_2);
    if (iVar1 != 0) {
      do {
        iVar2 = FUN_080265a8(iVar1);
        if (iVar2 == 0) break;
        iVar3 = FUN_0801cfc8(&DAT_08026c5c,"/mmc1","extfs",0,iVar2);
      } while (iVar3 != 0);
      FUN_08026594(iVar1);
    }
  }
  return iVar3;
}




