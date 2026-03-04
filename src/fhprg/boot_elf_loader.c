/* Auto-generated: boot_elf_loader.c */
/* Functions: 19 */
#include "globals.h"

/* 0x08014ed8 */
undefined4 FUN_08014ed8()
{
  int iVar1;
  int local_8;
  
  local_8 = 0;
  iVar1 = FUN_08016484(&local_8);
  if (iVar1 != 0) {
    ((code*)DAT_0804cd60)("boot_elf_loader.c",0x110,0x302e);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if ((local_8 != 0) && (DAT_0804d12a != '\0')) {
    return 1;
  }
  return 0;
}




/* 0x08014f28 */
void FUN_08014f28()
{
  int iVar1;
  uint uVar2;
  undefined *puVar3;
  undefined4 uVar4;
  undefined4 local_18;
  
  uVar2 = 0;
  local_18 = DAT_0804d134;
  while( true ) {
    if (DAT_0804d12c <= uVar2) {
      return;
    }
    if (DAT_0804d128 == '\x02') {
      puVar3 = &DAT_87c260c8 + uVar2 * 0x38;
    }
    else {
      puVar3 = &DAT_87c25448 + uVar2 * 0x20;
    }
    if (puVar3 == (undefined *)0x0) break;
    if (DAT_0804d128 == '\x02') {
      uVar4 = *(undefined4 *)(puVar3 + 0x18);
    }
    else {
      uVar4 = *(undefined4 *)(puVar3 + 0xc);
    }
    iVar1 = FUN_08015530(puVar3);
    if (iVar1 != 0) {
      FUN_08015200(puVar3,uVar4);
    }
    FUN_08018e7c(uVar2,&local_18);
    uVar2 = uVar2 + 1;
  }
  ((code*)DAT_0804cd60)("boot_elf_loader.c",0x205,0x3003);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08014fb0 */
void FUN_08014fb0()
{
  int iVar1;
  uint uVar2;
  undefined4 local_18;
  undefined4 local_14;
  
  uVar2 = 0;
  local_18 = 0;
  local_14 = DAT_0804d134;
  while( true ) {
    if (DAT_0804d12c <= uVar2) {
      return;
    }
    if (DAT_0804d128 == '\x02') {
      iVar1 = (&DAT_87c260cc)[uVar2 * 0xe];
    }
    else {
      iVar1 = (&DAT_87c25460)[uVar2 * 8];
    }
    if ((uint)(iVar1 << 5) >> 0x1d != 2) {
      FUN_080152d4();
    }
    FUN_08018e7c(uVar2,&local_14);
    iVar1 = FUN_08016484(&local_18);
    if (iVar1 != 0) break;
    uVar2 = uVar2 + 1;
  }
  ((code*)DAT_0804cd60)("boot_elf_loader.c",0x3e5,0x302e);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x0801503c */
void FUN_0801503c(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined *puVar9;
  
  uVar3 = 0;
  if ((param_1 == 0) || (param_2 == 0)) {
    ((code*)DAT_0804cd60)("boot_elf_loader.c",0x59a,0x3003,DAT_0804cd60,param_1);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_0801544c();
  iVar1 = FUN_08015744();
  if (iVar1 == 0) {
    ((code*)DAT_0804cd60)("boot_elf_loader.c",0x5a1,0x3039);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar4 = DAT_0804d154 * (uint)DAT_0804d12c & 0xffff;
  FUN_0801453c(DAT_0804d130 + 8,DAT_0804d14c,uVar4);
  iVar1 = FUN_08015e28(DAT_0804d130,DAT_0804d14c,0,uVar4);
  FUN_080147d4(DAT_0804d130 + 8,DAT_0804d14c,uVar4);
  if (iVar1 == 0) {
    ((code*)DAT_0804cd60)("boot_elf_loader.c",0x5b5,0x3038);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  while( true ) {
    if (DAT_0804d12c <= uVar3) {
      return;
    }
    if (DAT_0804d128 == '\x02') {
      puVar9 = &DAT_87c260c8 + uVar3 * 0x38;
      uVar4 = (&DAT_87c260f0)[uVar3 * 0xe];
      uVar5 = (&DAT_87c260f4)[uVar3 * 0xe];
      uVar6 = (&DAT_87c260e8)[uVar3 * 0xe];
      uVar7 = (&DAT_87c260ec)[uVar3 * 0xe];
      iVar1 = (&DAT_87c260cc)[uVar3 * 0xe];
      uVar8 = (&DAT_87c260d0)[uVar3 * 0xe];
    }
    else {
      uVar5 = 0;
      uVar7 = 0;
      puVar9 = &DAT_87c25448 + uVar3 * 0x20;
      uVar6 = (&DAT_87c25458)[uVar3 * 8];
      uVar4 = (&DAT_87c2545c)[uVar3 * 8];
      uVar8 = (&DAT_87c2544c)[uVar3 * 8];
      iVar1 = (&DAT_87c25460)[uVar3 * 8];
    }
    iVar2 = FUN_08015530(puVar9);
    if ((iVar2 != 0) && (uVar5 <= uVar7 && (uint)(uVar6 <= uVar4) <= uVar5 - uVar7)) {
      ((code*)DAT_0804cd60)("boot_elf_loader.c",0x5ce,0x3057);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if ((uint)(iVar1 << 5) >> 0x1d == 2) break;
    uVar3 = uVar3 + 1;
  }
  FUN_0801453c(DAT_0804d130 + 8,param_2,0x28);
  iVar1 = FUN_08015e28(DAT_0804d130,param_2,uVar8,0x28);
  FUN_080147d4(DAT_0804d130 + 8,param_2,0x28);
  if (iVar1 == 0) {
    ((code*)DAT_0804cd60)("boot_elf_loader.c",0x5e2,0x3038);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (-uVar5 < (uint)(uVar4 < 0xa001)) {
    DAT_0804d144 = FUN_08016164(-(uint)(uVar4 >= 0xa001) - uVar5,0xa000 - uVar4);
    FUN_0801453c(DAT_0804d130 + 8,DAT_0804d144,0xa000);
    FUN_08015200(puVar9,DAT_0804d144);
    FUN_080147d4(DAT_0804d130 + 8,DAT_0804d144,0xa000);
    if (DAT_0804d129 != '\x01') {
      DAT_0804d134 = DAT_0804d144 + 0x28;
      return;
    }
    DAT_0804d134 = DAT_0804d144 + 0x28;
    DAT_0804d138 = DAT_0804d144;
    DAT_0804d13c = uVar4;
    return;
  }
  ((code*)DAT_0804cd60)("boot_elf_loader.c",0x5e5,0x3038);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08015200 */
void FUN_08015200(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  
  if (param_1 == 0) {
    ((code*)DAT_0804cd60)("boot_elf_loader.c",0x13a,0x3003);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (DAT_0804d128 == '\x02') {
    uVar6 = *(undefined4 *)(param_1 + 8);
    uVar2 = *(undefined4 *)(param_1 + 0xc);
    uVar3 = *(uint *)(param_1 + 0x20);
    uVar5 = *(uint *)(param_1 + 0x24);
    uVar4 = *(uint *)(param_1 + 0x28);
    uVar7 = *(uint *)(param_1 + 0x2c);
  }
  else {
    uVar6 = *(undefined4 *)(param_1 + 4);
    uVar2 = 0;
    uVar3 = *(uint *)(param_1 + 0x10);
    uVar5 = 0;
    uVar4 = *(uint *)(param_1 + 0x14);
    uVar7 = 0;
  }
  iVar1 = FUN_08014694(DAT_0804d130 + 8,param_2,uVar4,uVar2);
  if (iVar1 == 0) {
    ((code*)DAT_0804cd60)("boot_elf_loader.c",0x145,0x303f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if ((uVar3 != 0 || uVar5 != 0) &&
     (iVar1 = FUN_08015e28(DAT_0804d130,param_2,uVar6,uVar3), iVar1 == 0)) {
    ((code*)DAT_0804cd60)("boot_elf_loader.c",0x154,0x3038);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (uVar5 <= uVar7 && (uint)(uVar4 <= uVar3) <= uVar5 - uVar7) {
    FUN_08007f08(param_2 + uVar3,0,uVar4 - uVar3);
  }
  FUN_080144b4(param_2,uVar4);
  return;
}




/* 0x080152d4 */
void FUN_080152d4(param_1, param_2, param_3)
int param_1; undefined4 param_2; undefined4 param_3;
{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  bool bVar11;
  uint uVar12;
  uint uVar13;
  undefined4 local_28;
  
  uVar6 = 0x100000;
  local_28 = 0;
  if (param_1 == 0) {
    ((code*)DAT_0804cd60)("boot_elf_loader.c",0x186,0x3003,DAT_0804cd60,param_2,param_3);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar2 = FUN_08016484(&local_28);
  if (iVar2 == 0) {
    if (DAT_0804d128 == '\x02') {
      uVar8 = *(uint *)(param_1 + 0x20);
      uVar12 = *(uint *)(param_1 + 0x24);
      iVar9 = *(int *)(param_1 + 0x18);
      iVar2 = *(int *)(param_1 + 8);
      uVar10 = *(uint *)(param_1 + 0x28);
      uVar3 = *(uint *)(param_1 + 0x2c);
    }
    else {
      iVar2 = *(int *)(param_1 + 4);
      uVar3 = 0;
      iVar9 = *(int *)(param_1 + 0xc);
      uVar8 = *(uint *)(param_1 + 0x10);
      uVar12 = 0;
      uVar10 = *(uint *)(param_1 + 0x14);
    }
    iVar4 = FUN_08014694(DAT_0804d130 + 8,iVar9,uVar10);
    if (iVar4 != 0) {
      iVar4 = FUN_08015530(param_1);
      if (iVar4 != 0) {
        uVar7 = uVar8;
        iVar4 = iVar9;
        uVar1 = DAT_0804d140;
        uVar13 = uVar12;
        if (uVar12 != 0 || uVar8 != 0) {
          while (DAT_0804d140 = uVar1, uVar7 != 0 || uVar12 != 0) {
            if (uVar12 == 0 && (uVar6 <= uVar7) <= uVar12) {
              uVar6 = uVar7;
            }
            iVar5 = FUN_08015e28(DAT_0804d130,iVar4,iVar2,uVar6);
            if (iVar5 == 0) {
              ((code*)DAT_0804cd60)("boot_elf_loader.c",0x1b6,0x3038);
              do {
                    /* WARNING: Do nothing block with infinite loop */
              } while( true );
            }
            iVar4 = iVar4 + uVar6;
            iVar2 = iVar2 + uVar6;
            bVar11 = uVar7 < uVar6;
            uVar7 = uVar7 - uVar6;
            uVar12 = uVar12 - bVar11;
            uVar1 = DAT_0804d140 + uVar6;
            if (DAT_0804d140 + uVar6 <= DAT_0804d140) {
              ((code*)DAT_0804cd60)("boot_elf_loader.c",0x1bd,0x302e);
              do {
                    /* WARNING: Do nothing block with infinite loop */
              } while( true );
            }
          }
        }
        iVar2 = uVar8 - uVar10;
        if (uVar13 <= uVar3 && (uint)(uVar10 <= uVar8) <= uVar13 - uVar3) {
          uVar6 = uVar10 - uVar8;
          FUN_08007f08(iVar9 + uVar8,0,uVar6);
          iVar2 = DAT_0804d140 - (uVar6 + DAT_0804d140);
          if (-(((uVar3 - uVar13) - (uint)(uVar10 < uVar8)) + (uint)CARRY4(uVar6,DAT_0804d140)) <
              (uint)(uVar6 + DAT_0804d140 <= DAT_0804d140)) {
            ((code*)DAT_0804cd60)("boot_elf_loader.c",0x1d5,0x302e);
            do {
                    /* WARNING: Do nothing block with infinite loop */
            } while( true );
          }
          DAT_0804d140 = uVar6 + DAT_0804d140;
        }
        FUN_080144b4(iVar9,uVar10,iVar2);
      }
      return;
    }
    ((code*)DAT_0804cd60)("boot_elf_loader.c",0x19b,0x303f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  ((code*)DAT_0804cd60)("boot_elf_loader.c",0x189,0x302e);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x0801544c */
void FUN_0801544c(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  int iVar1;
  
  FUN_080159d0(param_2);
  iVar1 = FUN_08015bc0();
  (**(code **)(*(int *)(iVar1 + 4) + 0x28))(param_1);
  if (DAT_0804d130 == 0) {
    iVar1 = FUN_08015bc0();
    DAT_0804d130 = ((code *)**(undefined4 **)(iVar1 + 4))(0x1b);
    if (DAT_0804d130 == 0) {
      ((code*)DAT_0804cd60)("boot_elf_loader.c",0x51d,0x300d);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
  }
  FUN_0801453c(DAT_0804d130 + 8,&DAT_87c276e0,0x40);
  iVar1 = FUN_08015e28(DAT_0804d130,&DAT_87c276e0,0,0x40);
  FUN_080147d4(DAT_0804d130 + 8,&DAT_87c276e0,0x40);
  if (iVar1 != 0) {
    DAT_0804d128 = 0;
    if (false) {
      DAT_0804d148 = &DAT_87c276e0;
      DAT_0804d150 = 0x40;
      DAT_0804d14c = &DAT_87c260c8;
    }
    else {
      DAT_0804d148 = &DAT_87c276a8;
      DAT_0804d150 = 0x34;
      FUN_08030b34(&DAT_87c276a8);
      FUN_08007f08(&DAT_87c276e0,0,0x40);
      DAT_0804d14c = &DAT_87c25448;
    }
    DAT_0804d154 = 0;
    DAT_0804d12c = 0;
    return;
  }
  ((code*)DAT_0804cd60)("boot_elf_loader.c",0x530,0x3038);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08015530 */
undefined4 FUN_08015530(param_1)
int * param_1;
{
  int iVar1;
  uint uVar2;
  
  if (param_1 == (int *)0x0) {
    ((code*)DAT_0804cd60)("boot_elf_loader.c",0xea,0x3003);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (DAT_0804d128 == '\x02') {
    iVar1 = param_1[1];
  }
  else {
    iVar1 = param_1[6];
  }
  if ((((*param_1 == 1) && (-1 < iVar1 << 0xb)) && (uVar2 = (uint)(iVar1 << 8) >> 0x1d, uVar2 != 3))
     && (((uint)(iVar1 << 5) >> 0x1d != 2 && (uVar2 != 4)))) {
    return 1;
  }
  return 0;
}




/* 0x08015598 */
void FUN_08015598()
{
  if (DAT_0804d129 == '\x01') {
    ((code*)DAT_0804cd60)("boot_elf_loader.c",0x4a3,0x3003);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return;
}




/* 0x080155d4 */
void FUN_080155d4(param_1, param_2)
undefined1 param_1; undefined1 param_2;
{
  DAT_0804d12a = param_1;
  DAT_0804d129 = param_2;
  return;
}




/* 0x080155e0 */
void FUN_080155e0()
{
  int iVar1;
  
  DAT_0804d12b = 0;
  if (DAT_0804d148 == 0) {
    ((code*)DAT_0804cd60)("boot_elf_loader.c",0x2fc,0x3036);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if ((DAT_0804d12c == 0) || (100 < DAT_0804d12c)) {
    ((code*)DAT_0804cd60)("boot_elf_loader.c",0x300,0x303a);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar1 = FUN_08015744();
  if (iVar1 != 1) {
    ((code*)DAT_0804cd60)("boot_elf_loader.c",0x304,0x3039);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar1 = FUN_080162dc(&DAT_87c25440,DAT_0804cdf4);
  if (iVar1 != 0) {
    ((code*)DAT_0804cd60)("boot_elf_loader.c",0x309,0x302e);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar1 = FUN_08014ed8();
  if (iVar1 != 0) {
    iVar1 = FUN_0801616c();
    if (iVar1 != 1) {
      ((code*)DAT_0804cd60)("boot_elf_loader.c",0x311,0x302e);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar1 = FUN_08016338(&DAT_87c25440,DAT_0804d148,DAT_0804d150);
    if (iVar1 != 0) {
      ((code*)DAT_0804cd60)("boot_elf_loader.c",0x315,0x302e);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar1 = FUN_08016338(&DAT_87c25440,DAT_0804d14c,DAT_0804d154 * (uint)DAT_0804d12c);
    if (iVar1 != 0) {
      ((code*)DAT_0804cd60)("boot_elf_loader.c",0x31c,0x302e);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar1 = FUN_0801622c(&DAT_87c25440,&DAT_87c27720,DAT_0804cdf8);
    if (iVar1 != 0) {
      ((code*)DAT_0804cd60)("boot_elf_loader.c",0x323,0x302e);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar1 = FUN_08013a24(&DAT_87c27720,DAT_0804d134,DAT_0804cdf8);
    if (iVar1 != 0) {
      ((code*)DAT_0804cd60)("boot_elf_loader.c",0x32b,0x303c);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    DAT_0804d12b = 1;
  }
  if (DAT_0804d128 == '\x02') {
    iVar1 = FUN_080158cc();
    if (iVar1 != 1) {
      ((code*)DAT_0804cd60)("boot_elf_loader.c",0x336,0x303a);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
  }
  else {
    iVar1 = FUN_0801596c();
    if (iVar1 != 1) {
      ((code*)DAT_0804cd60)("boot_elf_loader.c",0x33a,0x303a);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
  }
  return;
}




/* 0x08015744 */
undefined4 FUN_08015744()
{
  if (DAT_0804d128 == '\x01') {
    if (true) {
      return 0;
    }
    if (true) {
      return 0;
    }
    if (true) {
      return 0;
    }
    if (true) {
      return 0;
    }
    if (true) {
      return 0;
    }
    if (true) {
      return 0;
    }
    if (true) {
      return 0;
    }
    if (true) {
      return 0;
    }
  }
  else {
    if (DAT_0804d128 != '\x02') {
      return 0;
    }
    if (true) {
      return 0;
    }
    if (true) {
      return 0;
    }
    if (true) {
      return 0;
    }
    if (true) {
      return 0;
    }
    if (true) {
      return 0;
    }
    if (true) {
      return 0;
    }
    if (true) {
      return 0;
    }
    if (true) {
      return 0;
    }
  }
  if ((false) && (true)) {
    return 1;
  }
  return 0;
}




/* 0x080157d8 */
void FUN_080157d8(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  
  if (DAT_0804d128 == '\x02') {
    iVar6 = *(int *)(param_1 + 4);
    uVar4 = *(undefined4 *)(param_1 + 0x18);
    iVar3 = *(int *)(param_1 + 0x20);
    iVar5 = *(int *)(param_1 + 0x24);
  }
  else {
    iVar6 = *(int *)(param_1 + 0x18);
    iVar5 = 0;
    uVar4 = *(undefined4 *)(param_1 + 0xc);
    iVar3 = *(int *)(param_1 + 0x10);
  }
  iVar1 = FUN_0801616c();
  if (iVar1 != 1) {
    ((code*)DAT_0804cd60)("boot_elf_loader.c",0x23d,0x302e);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (DAT_0804d12b != '\x01') {
    ((code*)DAT_0804cd60)("boot_elf_loader.c",0x242,0x302e,DAT_0804cd60,param_4);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar2 = (uint)(iVar6 << 5) >> 0x1d;
  if ((((uVar2 != 7) && (uVar2 != 2)) && (iVar6 = FUN_08015530(param_1), iVar6 != 0)) &&
     (iVar3 != 0 || iVar5 != 0)) {
    iVar3 = FUN_080161f8(DAT_0804cdf4,uVar4,iVar3,&DAT_87c27720,DAT_0804cdf8);
    if (iVar3 != 0) {
      ((code*)DAT_0804cd60)("boot_elf_loader.c",0x253,0x302e);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar3 = FUN_08013a24(&DAT_87c27720,param_2,DAT_0804cdf8);
    if (iVar3 != 0) {
      ((code*)DAT_0804cd60)("boot_elf_loader.c",0x25c,0x303c);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
  }
  return;
}




/* 0x080158cc */
undefined4 FUN_080158cc()
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  iVar4 = 0;
  do {
    if (true) {
      return 0;
    }
    iVar1 = FUN_08015530(&DAT_87c260c8 + iVar4 * 0x38);
    if ((iVar1 != 0) && ((&DAT_87c260f0)[iVar4 * 0xe] != 0 || (&DAT_87c260f4)[iVar4 * 0xe] != 0)) {
      uVar2 = (&DAT_87c260e8)[iVar4 * 0xe];
      uVar3 = (&DAT_87c260ec)[iVar4 * 0xe];
      if (uVar2 != 0 || uVar3 != 0) {
        uVar6 = (&DAT_87c260e0)[iVar4 * 0xe];
        uVar5 = (&DAT_87c260e4)[iVar4 * 0xe];
        if (((uVar3 <= ~uVar5 && (uint)(~uVar6 <= uVar2) <= uVar3 - ~uVar5) &&
            (-uVar5 < (uint)(uVar6 == 0))) &&
           ((uint)(uVar6 + uVar2 == 0) <= -(uVar5 + uVar3 + (uint)CARRY4(uVar6,uVar2)))) {
          return 1;
        }
        uVar6 = (&DAT_87c260d8)[iVar4 * 0xe];
        uVar5 = (&DAT_87c260dc)[iVar4 * 0xe];
        if (((uVar3 <= ~uVar5 && (uint)(~uVar6 <= uVar2) <= uVar3 - ~uVar5) &&
            (-uVar5 < (uint)(uVar6 == 0))) &&
           ((uint)(uVar6 + uVar2 == 0) <= -(uVar5 + uVar3 + (uint)CARRY4(uVar6,uVar2)))) {
          return 1;
        }
      }
    }
    iVar4 = iVar4 + 1;
  } while( true );
}




/* 0x0801596c */
undefined4 FUN_0801596c()
{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = 0;
  while( true ) {
    if (true) {
      return 0;
    }
    iVar1 = FUN_08015530(&DAT_87c25448 + iVar3 * 0x20);
    if ((((iVar1 != 0) && ((&DAT_87c2545c)[iVar3 * 8] != 0)) &&
        (uVar2 = (&DAT_87c25458)[iVar3 * 8], uVar2 != 0)) &&
       ((((uVar2 < (uint)~(&DAT_87c25454)[iVar3 * 8] && ((&DAT_87c25454)[iVar3 * 8] == 0)) &&
         (uVar2 != 0)) ||
        (((uVar2 < (uint)~(&DAT_87c25450)[iVar3 * 8] && ((&DAT_87c25450)[iVar3 * 8] == 0)) &&
         (uVar2 != 0)))))) break;
    iVar3 = iVar3 + 1;
  }
  return 1;
}




/* 0x080159d0 */
void FUN_080159d0(param_1)
int param_1;
{
  undefined4 uVar1;
  
  FUN_08018fa4(0);
  DAT_0804d12b = 0;
  if (param_1 != 0) {
    FUN_08007f08(param_1,0,0x28);
  }
  FUN_08007f08(&DAT_87c276a8,0,0x34);
  FUN_08007f08(&DAT_87c276e0,0,0x40);
  FUN_08007f08(&DAT_87c25448,0,0xc80);
  FUN_08007f08(&DAT_87c260c8,0,0x15e0);
  uVar1 = FUN_08016164();
  FUN_08007f08(uVar1,0,0xa000);
  return;
}




/* 0x08015a3c */
undefined4 FUN_08015a3c(param_1)
undefined1 param_1;
{
  int iVar1;
  
  iVar1 = FUN_08016f26(param_1);
  if (iVar1 != 0) {
    return 0;
  }
  return 1;
}




/* 0x08016574 */
void FUN_08016574()
{
  if (DAT_0804d129 == '\x01') {
    DAT_0804d140 = 0;
    FUN_08015598();
    FUN_08014fb0();
  }
  else {
    FUN_08014f28();
  }
  if (DAT_0804d130 != 0) {
    FUN_08018fa4(0);
    DAT_0804d12b = 0;
    FUN_08015ba8(&DAT_0804d130);
    DAT_0804d130 = 0;
    return;
  }
  ((code*)DAT_0804cd60)("boot_elf_loader.c",0x42b,0x3003);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08018e7c */
void FUN_08018e7c(param_1, param_2)
int param_1; uint * param_2;
{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  
  if (DAT_0804d128 == '\x02') {
    puVar5 = &DAT_87c260c8 + param_1 * 0x38;
    iVar4 = (&DAT_87c260cc)[param_1 * 0xe];
    iVar3 = (&DAT_87c260e8)[param_1 * 0xe];
  }
  else {
    puVar5 = &DAT_87c25448 + param_1 * 0x20;
    iVar4 = (&DAT_87c25460)[param_1 * 8];
    iVar3 = (&DAT_87c25458)[param_1 * 8];
  }
  iVar1 = FUN_08014ed8();
  if (iVar1 != 0) {
    if (((DAT_0804d134 - DAT_0804cdf8) + 0xa000 < *param_2) || (*param_2 < DAT_0804d134)) {
      ((code*)DAT_0804cd60)("boot_elf_loader.c",0x396,0x3056);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    FUN_080157d8(puVar5);
    if (iVar4 << 0xb < 0) {
      uVar2 = ((iVar3 - 1U >> 0xc) + 1) * DAT_0804cdf8 + *param_2;
    }
    else {
      uVar2 = *param_2 + DAT_0804cdf8;
    }
    *param_2 = uVar2;
  }
  return;
}




