/* Auto-generated: boot_rollback_version.c */
/* Functions: 4 */
#include "globals.h"

/* 0x080179a8 */
int FUN_080179a8(param_1)
int param_1;
{
  int iVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  puVar3 = *(uint **)(param_1 + 0x14);
  uVar5 = 0;
  iVar4 = 0;
  uVar6 = 0;
  if (puVar3 != (uint *)0x0) {
    uVar6 = *puVar3 & *(uint *)(param_1 + 0x18);
  }
  if (*(int *)(param_1 + 0x20) != 0) {
    if ((puVar3 != (uint *)0x0) && (4 < (uint)(*(int *)(param_1 + 0x20) - (int)puVar3))) {
      while (puVar3 = puVar3 + 1, puVar3 < *(uint **)(param_1 + 0x20)) {
        if (puVar3 == (uint *)0x0) {
          ((code*)DAT_0804cd60)("boot_rollback_version.c",0xe8,0x300d);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        iVar1 = FUN_08014c60(*puVar3);
        iVar4 = iVar4 + iVar1;
      }
    }
    uVar5 = **(uint **)(param_1 + 0x20) & *(uint *)(param_1 + 0x24);
  }
  iVar1 = FUN_08014c60(uVar6);
  iVar2 = FUN_08014c60(uVar5);
  return iVar2 + iVar1 + iVar4;
}




/* 0x08017a2c */
undefined4 FUN_08017a2c(param_1, param_2)
undefined4 param_1; undefined4 * param_2;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  iVar1 = FUN_08017a64();
  if (iVar1 == 0) {
    uVar4 = 0x3059;
  }
  else {
    if ((DAT_0804ceb0 == 1) && (iVar2 = FUN_08017aec(iVar1), iVar2 != 0)) {
      uVar3 = FUN_080179a8(iVar1);
    }
    else {
      uVar3 = 0;
    }
    *param_2 = uVar3;
  }
  return uVar4;
}




/* 0x08017a64 */
int FUN_08017a64(param_1)
int param_1;
{
  uint uVar1;
  uint uVar2;
  
  if ((DAT_0804cea8 != 0) && (DAT_0804ceac != 0)) {
    for (uVar2 = 0; uVar2 < DAT_0804ceac; uVar2 = uVar2 + 1) {
      uVar1 = 0;
      do {
        if (*(int *)(DAT_0804cea8 + uVar2 * 0x30 + uVar1 * 4) == param_1) {
          return DAT_0804cea8 + uVar2 * 0x30;
        }
        uVar1 = uVar1 + 1;
      } while (uVar1 < 3);
    }
  }
  return 0;
}




/* 0x08017aa4 */
void FUN_08017aa4(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  int iVar1;
  
  DAT_0804cea8 = param_2;
  DAT_0804ceac = param_3;
  iVar1 = FUN_08016484(&DAT_0804ceb0);
  if (iVar1 != 0) {
    ((code*)DAT_0804cd60)("boot_rollback_version.c",0x244,0x302e);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return;
}




