/* Auto-generated: boot_ram_partition.c */
/* Functions: 4 */
#include "globals.h"

/* 0x080135fc */
undefined4 FUN_080135fc(param_1)
int param_1;
{
  uint *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int *piVar7;
  int iVar8;
  undefined4 *puVar9;
  
  uVar5 = 0;
  puVar1 = (uint *)FUN_080160d0();
  iVar2 = param_1 + *(int *)(param_1 + 0x10) * 0x40 + 0x18;
  while( true ) {
    if (*puVar1 <= uVar5) {
      return 0;
    }
    if (0x1f < *(uint *)(param_1 + 0x10)) break;
    if (puVar1[1] == 0) {
      ((code*)DAT_0804cd60)("boot_ram_partition.c",0xf7,0x300d);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    piVar7 = (int *)(puVar1[1] + uVar5 * 0x10);
    *(undefined4 *)(iVar2 + 0x24) = 0xe;
    iVar3 = *piVar7;
    iVar4 = piVar7[1];
    *(int *)(iVar2 + 0x10) = iVar3;
    *(int *)(iVar2 + 0x14) = iVar4;
    uVar6 = piVar7[2];
    iVar8 = piVar7[3];
    *(uint *)(iVar2 + 0x18) = uVar6 << 0x14;
    *(uint *)(iVar2 + 0x1c) = iVar8 << 0x14 | uVar6 >> 0xc;
    *(undefined4 *)(iVar2 + 0x20) = 1;
    *(undefined4 *)(iVar2 + 0x28) = 0;
    *(undefined4 *)(iVar2 + 0x2c) = 1;
    if (puVar1[2] != 0) {
      puVar9 = (undefined4 *)(puVar1[2] + uVar5 * 0x10);
      if (puVar9[2] != iVar3 || puVar9[3] != iVar4) {
        return 5;
      }
      *(undefined4 *)(iVar2 + 0x30) = *puVar9;
    }
    iVar2 = iVar2 + 0x40;
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
    uVar5 = uVar5 + 1;
  }
  return 0;
}




/* 0x08016f6c */
void FUN_08016f6c()
{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)thunk_FUN_080373b8(0x192,0x818);
  if (puVar1 == (undefined4 *)0x0) {
    iVar2 = 1;
  }
  else if ((puVar1 < (undefined4 *)0x87d00001) || ((undefined4 *)0x87e00000 < puVar1 + 0x206)) {
    iVar2 = 2;
  }
  else {
    iVar2 = 0;
    puVar1[4] = 0;
  }
  if ((iVar2 == 0) && (puVar1 != (undefined4 *)0x0)) {
    iVar2 = FUN_0801355c();
    if (iVar2 != 0) {
      ((code*)DAT_0804cd60)("boot_ram_partition.c",0x21f,0x3042);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *puVar1 = 0x9da5e0a8;
    puVar1[1] = 0xaf9ec4e2;
    puVar1[2] = 1;
    return;
  }
  ((code*)DAT_0804cd60)("boot_ram_partition.c",0x219,0x3041);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08017030 */
void FUN_08017030()
{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_0801c288();
  DAT_0804ce10 = uVar1;
  if (0x14 < uVar1) {
    uVar1 = FUN_08017950();
  }
  uVar1 = uVar1 * 0x40 + 0x38;
  FUN_080176c4();
  FUN_0801c56c();
  if ((uint)-DAT_0804ce1c < (uint)(DAT_0804ce18 <= uVar1)) {
    FUN_08006e5e(0x38,0,0x87c734e8);
  }
  else {
    FUN_08019558(-(uint)(DAT_0804ce18 > uVar1) - DAT_0804ce1c,uVar1 - DAT_0804ce18);
    FUN_08006e5e(uVar1,0,0x87c734e8);
    FUN_0801c584();
    iVar2 = FUN_080170b8();
    if (iVar2 == 1) {
      uVar1 = FUN_08006e04(0x87c734d0);
      uVar1 = uVar1 | 1;
      goto LAB_08017094;
    }
  }
  uVar1 = FUN_08006e04(0x87c734d0);
  uVar1 = uVar1 | 2;
LAB_08017094:
  FUN_08006e1a(uVar1,0x87c734d0);
  FUN_0801c56c();
  return;
}




/* 0x080170b8 */
undefined4 FUN_080170b8()
{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  bool bVar8;
  longlong lVar9;
  
  uVar4 = 0;
  DAT_0804ce20 = DAT_0804ce10 * 0x40 + 0x38;
  DAT_0804ce24 = 0;
  uVar5 = DAT_0804ce18 - DAT_0804ce20;
  uVar6 = DAT_0804ce1c - (uint)(DAT_0804ce18 < DAT_0804ce20);
  while( true ) {
    if (DAT_0804ce10 <= uVar4) {
      return 1;
    }
    uVar1 = FUN_0801c260();
    uVar2 = FUN_0801c238(uVar4 & 0xff);
    FUN_08019848(uVar4);
    if (uVar6 == 0 && (uVar1 <= uVar5) <= uVar6) break;
    FUN_08017760(uVar2,extraout_r1,DAT_0804ce20,DAT_0804ce24,uVar1);
    iVar7 = uVar4 * 0x40 + -0x7838cb04;
    uVar3 = FUN_08006e04(iVar7);
    FUN_08006e1a(uVar3 | 1,iVar7);
    lVar9 = FUN_08006e30(0x87c734e8);
    FUN_08006e5e((int)(lVar9 + (ulonglong)uVar1),(int)(lVar9 + (ulonglong)uVar1 >> 0x20),0x87c734e8)
    ;
    iVar7 = FUN_08006e04(0x87c734f8);
    FUN_08006e1a(iVar7 + 1,0x87c734f8);
    bVar8 = CARRY4(DAT_0804ce20,uVar1);
    DAT_0804ce20 = DAT_0804ce20 + uVar1;
    DAT_0804ce24 = DAT_0804ce24 + (uint)bVar8;
    bVar8 = uVar5 < uVar1;
    uVar5 = uVar5 - uVar1;
    uVar6 = uVar6 - bVar8;
    FUN_0801c56c();
    FUN_0801c584();
    uVar4 = uVar4 + 1;
  }
  iVar7 = uVar4 * 0x40 + -0x7838cb04;
  uVar1 = FUN_08006e04(iVar7);
  FUN_08006e1a(uVar1 | 2,iVar7);
  FUN_08006e5e(uVar5,uVar6,uVar4 * 0x40 + -0x7838caf0);
  FUN_08017760(uVar2,extraout_r1_00,DAT_0804ce20,DAT_0804ce24,uVar5);
  lVar9 = FUN_08006e30(0x87c734e8);
  lVar9 = lVar9 + CONCAT44(uVar6,uVar5);
  FUN_08006e5e((int)lVar9,(int)((ulonglong)lVar9 >> 0x20),0x87c734e8);
  iVar7 = FUN_08006e04(0x87c734f8);
  FUN_08006e1a(iVar7 + 1,0x87c734f8);
  FUN_0801c584();
  return 0;
}




