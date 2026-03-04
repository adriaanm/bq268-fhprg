/* Auto-generated: boot_mc.c */
/* Functions: 3 */
#include "globals.h"

/* 0x08014e28 */
void FUN_08014e28(param_1, param_2)
int param_1; undefined4 * param_2;
{
  if (param_1 == 0) {
    ((code*)DAT_0804cd60)("boot_mc.c",0x5b,0x300d);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_2 != (undefined4 *)0x0) {
    for (; (code *)*param_2 != (code *)0x0; param_2 = param_2 + 1) {
      ((code *)*param_2)(param_1);
    }
  }
  return;
}




/* 0x08014e78 */
undefined4 FUN_08014e78(param_1, param_2, param_3)
undefined4 param_1; int param_2; undefined2 param_3;
{
  undefined2 uVar1;
  
  uVar1 = 0;
  if (param_2 << 0x19 < 0) {
    uVar1 = param_3;
  }
  FUN_0801d058(param_1,param_2,uVar1);
  return 0;
}




/* 0x08014ea0 */
void FUN_08014ea0(param_1, param_2, param_3)
undefined4 param_1; int param_2; int param_3;
{
  int iVar1;
  undefined4 *puVar2;
  
  while( true ) {
    if (param_3 == 0) {
      return;
    }
    FUN_08019524();
    iVar1 = thunk_FUN_0801d304(param_1,param_2,param_3);
    if (iVar1 < 0) break;
    param_3 = param_3 - iVar1;
    param_2 = param_2 + iVar1;
  }
  puVar2 = (undefined4 *)FUN_0801cd9a();
  DAT_0805261c = *puVar2;
  return;
}




