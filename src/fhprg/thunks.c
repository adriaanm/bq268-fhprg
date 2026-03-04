/* Auto-generated: thunks.c */
/* Functions: 104 */
#include "globals.h"

/* 0x00220178 */
undefined4 FUN_00220178(param_1, param_2)
uint * param_1; uint param_2;
{
  if (param_2 < 2) {
    if (param_2 == 1) {
      *param_1 = *param_1 | 1;
      do {
      } while ((int)*param_1 < 0);
    }
    else {
      *param_1 = *param_1 & 0xfffffffe;
    }
    return 1;
  }
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x002201a0 */
void FUN_002201a0()
{
  _DAT_01829004 = (_DAT_01829004 & 0x80000000) + 1;
  _DAT_01829008 = _DAT_01829008 & 0xf0008001 | 1;
  _DAT_01829084 = (_DAT_01829084 & 0x80000000) + 1;
  _DAT_01832024 = 0x8000;
  FUN_00220178(&DAT_01832024,1);
  FUN_00220178(0x183201c,1);
  FUN_00220178(0x1832020,1);
  FUN_00220178(0x1831008,1);
  FUN_00220178(0x183100c,1);
  FUN_00220178(0x1831010,1);
  FUN_00220178(0x1831014,1);
  FUN_00220178(0x183101c,1);
  _DAT_01831018 = 0x10100;
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0022024c */
void FUN_0022024c(param_1)
int param_1;
{
  FUN_002201a0();
  _DAT_0086dfb0 = 0xc5acce55;
  _DAT_0086d000 = 1;
  _DAT_0086d004 = 1;
  _DAT_0086d008 = 0;
  *(undefined4 *)(param_1 + 0xf8) = _DAT_0086d0b0;
  *(undefined4 *)(param_1 + 0xfc) = 0;
  *(undefined4 *)(param_1 + 0x118) = _DAT_0086d0c0;
  *(undefined4 *)(param_1 + 0x11c) = 0;
  thunk_FUN_00222684(&SUB_00004b00);
  if (DAT_00223b90 != 2) {
                    /* WARNING: Could not recover jumptable at 0x0022029a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((code*)DAT_00223b88)(param_1);
    return;
  }
  FUN_00220388(DAT_00223b88,param_1);
  return;
}




/* 0x002202b8 */
uint FUN_002202b8()
{
  uint uVar1;
  undefined4 in_cr0 = 0;
  undefined4 in_cr12 = 0;
  
  uVar1 = coprocessor_movefromRt(0xf,0,2,in_cr12,in_cr0);
  DataSynchronizationBarrier(0xf);
  coprocessor_moveto(0xf,0,2,uVar1 | 1,in_cr12,in_cr0);
  InstructionSynchronizationBarrier(0xf);
  DataSynchronizationBarrier(0xf);
  return uVar1 | 1;
}




/* 0x00220358 */
void FUN_00220358(param_1)
int param_1;
{
  thunk_FUN_0802ee94(param_1 != 1);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x00220358 */
void thunk_FUN_00220358()
{
  FUN_00220358();
  return;
}




/* 0x00220388 */
void FUN_00220388(param_1)
uint param_1;
{
  uint uVar1;
  undefined4 in_cr0 = 0;
  undefined4 in_cr12 = 0;
  
  if ((param_1 & 0xf4fefffb) == 0) {
    _DAT_0b010004 = param_1 | 1;
    FUN_002202b8();
    uVar1 = coprocessor_movefromRt(0xf,0,2,in_cr12,in_cr0);
    DataSynchronizationBarrier(0xf);
    coprocessor_moveto(0xf,0,2,uVar1 | 2,in_cr12,in_cr0);
    InstructionSynchronizationBarrier(0xf);
    DataSynchronizationBarrier(0xf);
    InstructionSynchronizationBarrier(0xf);
    WaitForInterrupt();
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  ((code*)DAT_0804cd60)("boot_a53.c",0x76,0x3062);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x00220388 */
void thunk_FUN_00220388()
{
  FUN_00220388();
  return;
}




/* 0x00220428 */
void FUN_00220428()
{
  return;
}




/* 0x0022042a */
void FUN_0022042a()
{
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x00220430 */
void FUN_00220430(param_1, param_2, param_3, param_4)
int param_1; uint param_2; uint param_3; uint param_4;
{
  _DAT_0049f008 = (uint)((param_2 & 0xff) != 0);
  if ((param_2 << 0x10) >> 0x18 != 0) {
    _DAT_0049f008 = _DAT_0049f008 | 2;
  }
  if ((param_2 << 8) >> 0x18 != 0) {
    _DAT_0049f008 = _DAT_0049f008 | 4;
  }
  if (param_2 >> 0x18 != 0) {
    _DAT_0049f008 = _DAT_0049f008 | 8;
  }
  if ((param_3 & 0xff) != 0) {
    _DAT_0049f008 = _DAT_0049f008 | 0x10;
  }
  if ((param_3 << 0x10) >> 0x18 != 0) {
    _DAT_0049f008 = _DAT_0049f008 | 0x20;
  }
  if ((param_3 << 8) >> 0x18 != 0) {
    _DAT_0049f008 = _DAT_0049f008 | 0x40;
  }
  if (param_3 >> 0x18 != 0) {
    _DAT_0049f008 = _DAT_0049f008 | 0x80;
  }
  if ((param_4 & 0xff) != 0) {
    _DAT_0049f008 = _DAT_0049f008 | 0x100;
  }
  if ((param_4 << 0x10) >> 0x18 != 0) {
    _DAT_0049f008 = _DAT_0049f008 | 0x200;
  }
  if (param_1 == 1) {
    _DAT_0049f008 = _DAT_0049f008 << 10;
  }
  return;
}




/* 0x002204ac */
uint FUN_002204ac(param_1)
int param_1;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  if (param_1 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = -1;
  }
  iVar1 = FUN_00222380();
  uVar3 = 0;
  if (*(int *)(iVar2 + 0x44d004) << 7 < 0) {
    FUN_0022141c(0,param_1,1,0x20);
    if ((*(uint *)(iVar2 + 0x44d070) & 1) == 0) {
      uVar3 = 1;
    }
    else {
      *(uint *)(iVar2 + 0x44d004) = *(uint *)(iVar2 + 0x44d004) & 0xeeffffff;
      *(uint *)(iVar2 + 0x44d020) = *(uint *)(iVar2 + 0x44d020) & 0xcf7fffff | 0x10800000;
      do {
      } while (*(int *)(iVar2 + 0x44d020) << 8 < 0);
      *(undefined4 *)(iVar1 + 0x48) = 0;
      *(undefined4 *)(iVar1 + 0x4c) = 0;
      *(undefined4 *)(iVar1 + 0x50) = 0;
    }
  }
  if (*(int *)(iVar2 + 0x44d004) << 6 < 0) {
    FUN_0022141c(0,param_1,2,0x20);
    if ((*(uint *)(iVar2 + 0x44d070) & 1) == 0) {
      uVar3 = uVar3 | 2;
    }
    else {
      *(uint *)(iVar2 + 0x44d004) = *(uint *)(iVar2 + 0x44d004) & 0xddffffff;
      *(uint *)(iVar2 + 0x44d020) = *(uint *)(iVar2 + 0x44d020) & 0xcf7fffff | 0x20800000;
      do {
      } while (*(int *)(iVar2 + 0x44d020) << 8 < 0);
      *(undefined4 *)(iVar1 + 0x54) = 0;
      *(undefined4 *)(iVar1 + 0x58) = 0;
      *(undefined4 *)(iVar1 + 0x5c) = 0;
    }
  }
  return uVar3;
}




/* 0x00220550 */
void FUN_00220550(param_1, param_2, param_3)
int param_1; undefined1 * param_2; code * param_3;
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  
  if (*(int *)(param_1 + 0x400028) << 3 < 0) {
    if (param_2 == &SUB_00004b00) {
      uVar1 = 0xcb73;
      goto LAB_002205a2;
    }
    uVar3 = 1000000000;
    uVar2 = (*param_3)(1000000000,param_2);
    uVar1 = 0x1ffff;
    if (0x1fffe < uVar2) goto LAB_002205a2;
  }
  else {
    if (param_2 == &SUB_00004b00) {
      uVar1 = 0x208;
      goto LAB_002205a2;
    }
    uVar3 = 10000000;
    uVar1 = (*param_3)(10000000,param_2);
    if (0xfe < uVar1) {
      uVar1 = 0xff;
      goto LAB_002205a2;
    }
  }
  uVar1 = (*param_3)(uVar3,param_2);
LAB_002205a2:
  *(uint *)(param_1 + 0x400028) = *(uint *)(param_1 + 0x400028) & 0xfffe0000 | uVar1 & 0x1ffff;
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x002205bc */
void FUN_002205bc(param_1)
uint param_1;
{
  if (DAT_00223048 != '\0') {
    do {
    } while ((uint)((int)((ulonglong)param_1 * 0x14) == 0) <=
             (uint)-(int)((ulonglong)param_1 * 0x14 >> 0x20));
    return;
  }
  FUN_080199b4();
  return;
}




/* 0x002205d0 */
void FUN_002205d0(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  
  iVar1 = 0;
  if (param_2 != 0) {
    iVar1 = -1;
  }
  *(uint *)(param_1 + iVar1 + 0x44c068) = *(uint *)(param_1 + iVar1 + 0x44c068) & 0xfeefffff;
  return;
}




/* 0x002205ec */
void FUN_002205ec(param_1, param_2, param_3, param_4)
int param_1; int param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_2 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = -1;
  }
  if ((*(uint *)(iVar1 + param_1 + 0x44c010) & 0x30000) == 0) {
    uVar3 = 2;
  }
  else {
    uVar3 = 5;
  }
  iVar1 = FUN_00221230(uVar3,param_4,param_3,param_4,param_4);
  iVar2 = FUN_00221c20(uVar3,param_4);
  if (iVar1 == 3) {
    if (iVar2 == 1) goto LAB_00220692;
  }
  else if (iVar1 == 4) {
    if (iVar2 == 2) goto LAB_00220692;
  }
  else if (iVar1 == 5) {
    if (iVar2 == 2) {
      iVar2 = 3;
      goto LAB_00220692;
    }
  }
  else if (iVar1 == 6) {
    if (iVar2 == 3) {
      iVar2 = 4;
      goto LAB_00220692;
    }
  }
  else if (iVar1 == 7) {
    if (iVar2 == 4) {
      iVar2 = 5;
      goto LAB_00220692;
    }
  }
  else if (iVar1 == 8) {
    if (iVar2 == 4) {
      iVar2 = 6;
      goto LAB_00220692;
    }
  }
  else if (iVar1 == 9) {
    if (iVar2 == 5) {
      iVar2 = 7;
      goto LAB_00220692;
    }
  }
  else if (iVar1 == 10) {
    if (iVar2 == 6) {
      iVar2 = 8;
      goto LAB_00220692;
    }
  }
  else if ((iVar1 == 0xb) && (iVar2 == 6)) {
    iVar2 = 9;
    goto LAB_00220692;
  }
  iVar2 = 10;
LAB_00220692:
  FUN_00221c78(param_1,param_2,param_3,2,iVar2);
  return;
}




/* 0x002206ac */
void FUN_002206ac(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  if (param_2 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = -1;
  }
  iVar3 = iVar3 + param_1;
  iVar1 = FUN_00222380();
  uVar2 = *(uint *)(iVar1 + 0x60) & 0xffff;
  if (uVar2 == 8) {
    iVar4 = 0;
  }
  else if (uVar2 == 0x10) {
    iVar4 = 1;
  }
  else {
    iVar4 = 2;
  }
  *(uint *)(iVar3 + 0x44c010) = *(uint *)(iVar3 + 0x44c010) & 0xfffffcff | iVar4 << 8;
  uVar2 = *(uint *)(iVar1 + 0x60) >> 0x10;
  if (uVar2 == 8) {
    iVar4 = 0;
  }
  else if (uVar2 == 0x10) {
    iVar4 = 1;
  }
  else {
    iVar4 = 2;
  }
  *(uint *)(iVar3 + 0x44c010) = *(uint *)(iVar3 + 0x44c010) & 0xfffff3ff | iVar4 << 10;
  *(uint *)(iVar3 + 0x44c014) =
       (*(uint *)(iVar1 + 0x50) | *(int *)(iVar1 + 0x5c) << 8) & 0x1f1f |
       *(uint *)(iVar3 + 0x44c014) & 0xffffe0e0;
  *(uint *)(iVar3 + 0x44c018) =
       *(uint *)(iVar3 + 0x44c018) & 0xfe0fffff | (*(uint *)(iVar1 + 100) & 0x1f) << 0x14;
  *(uint *)(iVar3 + 0x44c068) = *(uint *)(iVar3 + 0x44c068) | 0x100000;
  *(uint *)(iVar3 + 0x44c020) = *(uint *)(iVar3 + 0x44c020) | 1;
  return;
}




/* 0x002207d4 */
void FUN_002207d4(param_1, param_2, param_3)
int param_1; int param_2; undefined4 param_3;
{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint local_b0 [18];
  uint local_68 [19];
  
  uVar2 = 0;
  do {
    local_b0[uVar2] = 0;
    local_68[uVar2] = 0;
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x12);
  if (param_2 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = -1;
  }
  param_1 = param_1 + iVar3;
  iVar3 = FUN_00222380();
  iVar1 = *(int *)(iVar3 + 8);
  if ((iVar1 == 2) || (iVar1 == 5)) {
    local_b0[0] = *(uint *)(iVar3 + 0x10);
    local_68[0] = 0x3ff;
    local_b0[1] = *(uint *)(iVar3 + 0x40) | *(int *)(iVar3 + 0x38) << 0x10;
    local_68[1] = 0xff01ff;
    local_b0[2] = *(uint *)(iVar3 + 0x34) | *(int *)(iVar3 + 0x2c) << 0x10;
    local_68[2] = 0x7f00ff;
    local_b0[3] = *(int *)(iVar3 + 0xc) << 0x10;
    local_68[3] = 0xfff0000;
    local_b0[4] = *(undefined4 *)(iVar3 + 0x74);
    local_68[4] = 0x7f;
    local_b0[5] = *(uint *)(iVar3 + 0x6c) | *(int *)(iVar3 + 0x30) << 0x10;
    local_68[5] = 0x1ff01ff;
    local_b0[6] = *(uint *)(iVar3 + 0x3c) | *(int *)(iVar3 + 0x70) << 0x10;
    local_68[6] = 0x3ff00ff;
    local_b0[7] = *(undefined4 *)(iVar3 + 0x94);
    local_68[7] = 0x7ff;
    local_b0[9] = *(undefined4 *)(iVar3 + 0xa0);
    local_68[9] = 0xff;
    local_b0[10] = *(uint *)(iVar3 + 0x24) | *(uint *)(iVar3 + 0x24) << 0x10;
    local_68[10] = 0xfff0fff;
    local_68[0xb] = 0xff01ff;
    local_68[0xc] = 0xff01ff;
    local_b0[0xb] = *(uint *)(iVar3 + 0x28) | *(uint *)(iVar3 + 0x28) << 0x10;
    local_b0[0xc] = local_b0[0xb];
    uVar2 = FUN_00221c20(iVar1,param_3);
    iVar1 = FUN_00221230(*(undefined4 *)(iVar3 + 8),param_3);
    local_b0[0x10] = uVar2 | iVar1 << 8;
    local_68[0x10] = 0x3f3f;
    local_b0[0x11] = *(undefined4 *)(iVar3 + 0x90);
    local_68[0x11] = 0xfff;
  }
  uVar2 = 0;
  do {
    iVar3 = param_1 + uVar2 * 4;
    *(uint *)(iVar3 + 0x44c144) =
         *(uint *)(iVar3 + 0x44c144) & ~local_68[uVar2] | local_b0[uVar2] & local_68[uVar2];
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x12);
  *(uint *)(param_1 + 0x44c020) = *(uint *)(param_1 + 0x44c020) | 0x10;
  do {
  } while ((*(uint *)(param_1 + 0x44c0a0) & 1) != 0);
  *(uint *)(param_1 + 0x44c020) = *(uint *)(param_1 + 0x44c020) | 1;
  return;
}




/* 0x00220928 */
void FUN_00220928(param_1, param_2, param_3)
int param_1; int param_2; undefined4 param_3;
{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  
  iVar2 = 0;
  if (param_2 != 0) {
    iVar2 = -1;
  }
  param_1 = param_1 + iVar2;
  if ((*(uint *)(param_1 + 0x44c010) & 0x30000) == 0) {
    uVar4 = 2;
  }
  else {
    uVar4 = 5;
  }
  iVar2 = FUN_00221230(uVar4,param_3);
  uVar1 = FUN_00221c20(uVar4,param_3);
  if (iVar2 == 3) {
    if (uVar1 == 1) {
      uVar3 = 1;
      goto LAB_002209c6;
    }
  }
  else if (iVar2 == 4) {
    if (uVar1 == 2) {
      uVar3 = 2;
      goto LAB_002209c6;
    }
  }
  else if (iVar2 == 5) {
    if (uVar1 == 2) {
      uVar3 = 3;
      goto LAB_002209c6;
    }
  }
  else if (iVar2 == 6) {
    if (uVar1 == 3) {
      uVar3 = 4;
      goto LAB_002209c6;
    }
  }
  else if (iVar2 == 7) {
    if (uVar1 == 4) {
      uVar3 = 5;
      goto LAB_002209c6;
    }
  }
  else if (iVar2 == 8) {
    if (uVar1 == 4) {
      uVar3 = 6;
      goto LAB_002209c6;
    }
  }
  else if (iVar2 == 9) {
    if (uVar1 == 5) {
      uVar3 = 7;
      goto LAB_002209c6;
    }
  }
  else if (iVar2 == 10) {
    if (uVar1 == 6) {
      uVar3 = 8;
      goto LAB_002209c6;
    }
  }
  else if ((iVar2 == 0xb) && (uVar1 == 6)) {
    uVar3 = 9;
    goto LAB_002209c6;
  }
  uVar3 = 10;
LAB_002209c6:
  *(uint *)(param_1 + 0x44c124) = *(uint *)(param_1 + 0x44c124) & 0xf00f0000 | uVar3 | 0x200000;
  *(uint *)(param_1 + 0x44c134) = *(uint *)(param_1 + 0x44c134) | 1;
  *(uint *)(param_1 + 0x44c184) =
       *(uint *)(param_1 + 0x44c184) & 0xffffc0c0 | (uVar1 | iVar2 << 8) & 0x3f3f;
  return;
}




/* 0x00220a14 */
void FUN_00220a14(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  int iVar1;
  
  FUN_00221674();
  if (param_2 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = -1;
  }
  iVar1 = iVar1 + param_1;
  FUN_00222380(param_2);
  FUN_00221a80(param_1,param_2,param_3);
  FUN_00221a30(param_1,param_2,param_3);
  *(uint *)(iVar1 + 0x44d020) = *(uint *)(iVar1 + 0x44d020) | 0x200000;
  do {
  } while (*(int *)(iVar1 + 0x44d020) << 10 < 0);
  if ((param_3 & 1) != 0) {
    do {
    } while (-1 < *(int *)(iVar1 + 0x44c08c) << 0xb);
  }
  if ((int)(param_3 << 0x1e) < 0) {
    do {
    } while (-1 < *(int *)(iVar1 + 0x44c08c) << 10);
  }
  *(uint *)(iVar1 + 0x44d020) = *(uint *)(iVar1 + 0x44d020) & 0xcfffffff | (param_3 & 3) << 0x1c;
  *(uint *)(iVar1 + 0x44d020) = *(uint *)(iVar1 + 0x44d020) | 0x800000;
  do {
  } while (*(int *)(iVar1 + 0x44d020) << 8 < 0);
  if ((param_3 & 1) != 0) {
    *(uint *)(iVar1 + 0x44d004) = *(uint *)(iVar1 + 0x44d004) & 0xeeffffff;
  }
  if ((int)(param_3 << 0x1e) < 0) {
    *(uint *)(iVar1 + 0x44d004) = *(uint *)(iVar1 + 0x44d004) & 0xddffffff;
  }
  return;
}




/* 0x00220a2e */
void FUN_00220a2e(param_1, param_2, param_3, param_4)
int param_1; int param_2; uint param_3; undefined4 param_4;
{
  int iVar1;
  
  FUN_00221674();
  FUN_00221a30(param_1,param_2,param_3);
  FUN_00220d20(param_1,param_2,param_4);
  iVar1 = 0;
  if (param_2 != 0) {
    iVar1 = -1;
  }
  param_1 = param_1 + iVar1;
  *(uint *)(param_1 + 0x44d020) =
       *(uint *)(param_1 + 0x44d020) & 0xcfff7fff | (param_3 & 3) << 0x1c | 0x8000;
  do {
  } while (*(int *)(param_1 + 0x44d020) << 0x10 < 0);
  do {
  } while (-1 < *(int *)(param_1 + 0x44d074) << 0x1e);
  return;
}




/* 0x00220a60 */
void FUN_00220a60(param_1, param_2, param_3, param_4)
int param_1; int param_2; uint param_3; undefined4 param_4;
{
  int iVar1;
  
  FUN_002216cc();
  if (param_2 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = -1;
  }
  iVar1 = iVar1 + param_1;
  FUN_002205d0(param_1);
  *(uint *)(iVar1 + 0x44d020) = *(uint *)(iVar1 + 0x44d020) & 0xcfffffff | (param_3 & 3) << 0x1c;
  *(uint *)(iVar1 + 0x44d020) = *(uint *)(iVar1 + 0x44d020) | 0x100000;
  FUN_002217e4(param_1,param_2,param_3,param_4);
  return;
}




/* 0x00220a80 */
void FUN_00220a80(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  FUN_002216cc();
  FUN_00221070(param_1,param_2,param_4);
  FUN_00221b80(param_1,param_2,param_3);
  FUN_00220e34(param_1,param_2);
  FUN_00221ad0(param_1,param_2,param_3);
  return;
}




/* 0x00220aba */
int FUN_00220aba(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = FUN_0022254c();
  iVar2 = FUN_00222380(0);
  iVar3 = *(int *)(iVar2 + 0x50) << (*(int *)(iVar2 + 0x48) + *(int *)(iVar2 + 0x4c) + 2U & 0xff);
  iVar4 = *(int *)(iVar2 + 0x5c) << (*(int *)(iVar2 + 0x54) + *(int *)(iVar2 + 0x58) + 2U & 0xff);
  iVar2 = FUN_00222380(1);
  if (param_2 == 1) {
    if (param_1 == 0) {
      return -0x80000000;
    }
    if ((uVar1 & 1) != 0) {
      return -0x80000000;
    }
    iVar3 = iVar3 + iVar4;
  }
  else {
    if ((int)(uVar1 << 0x1e) < 0) {
      return iVar3 * 2 + -0x80000000;
    }
    if (param_1 == 0) {
      return iVar3 + -0x80000000;
    }
    iVar3 = iVar3 + iVar4 +
            (*(int *)(iVar2 + 0x50) << (*(int *)(iVar2 + 0x4c) + *(int *)(iVar2 + 0x48) + 2U & 0xff)
            );
  }
  return iVar3 + -0x80000000;
}




/* 0x00220b2c */
void FUN_00220b2c(param_1, param_2, param_3)
int param_1; uint param_2; undefined4 param_3;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_1 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = -1;
  }
  iVar1 = FUN_00222380();
  if ((*(int *)(iVar1 + 8) == 2) || (*(int *)(iVar1 + 8) == 5)) {
    uVar3 = *(undefined4 *)(iVar2 + 0x44d004);
    FUN_00222748(iVar2,DAT_00223600,DAT_00223610);
    FUN_002219fc(0,param_1,3);
    FUN_00221a30(0,param_1,3);
    FUN_00221a80(0,param_1,3);
    FUN_00221a64(0,param_1,3);
    *(uint *)(iVar2 + 0x44d004) = *(uint *)(iVar2 + 0x44d004) & 0xccffffff;
    if ((param_2 & 1) != 0) {
      *(uint *)(iVar2 + 0x44d004) = *(uint *)(iVar2 + 0x44d004) | 0x10000000;
    }
    if ((int)(param_2 << 0x1e) < 0) {
      *(uint *)(iVar2 + 0x44d004) = *(uint *)(iVar2 + 0x44d004) | 0x20000000;
    }
    FUN_00220550(0,param_3,0x222079);
    FUN_002207d4(0,param_1,param_3);
    FUN_00220ee8(0,param_1,param_3);
    if (*(int *)(iVar2 + 0x44d074) << 0x1d < 0) {
      *(undefined4 *)(iVar2 + 0x44d004) = uVar3;
      *(uint *)(iVar2 + 0x44d024) = *(uint *)(iVar2 + 0x44d024) & 0xffff0000;
      *(uint *)(iVar2 + 0x44c020) = *(uint *)(iVar2 + 0x44c020) | 0x10;
      do {
      } while ((*(uint *)(iVar2 + 0x44c0a0) & 1) != 0);
      *(uint *)(iVar2 + 0x44c020) = *(uint *)(iVar2 + 0x44c020) | 1;
      *(uint *)(iVar2 + 0x44d004) = param_2 & 0xfcffffff;
      *(uint *)(iVar2 + 0x44d004) = *(uint *)(iVar2 + 0x44d004) & 0xfcffffff;
      FUN_002205bc(1,0);
      *(undefined4 *)(iVar2 + 0x44d004) = uVar3;
    }
    else {
      FUN_002217e4(0,param_1,param_2,param_3);
      param_2 = FUN_002204ac(param_1);
      FUN_002212c0(param_1);
      FUN_00222558(param_1);
      FUN_002207d4(0,param_1,param_3);
    }
    FUN_002206ac(0,param_1);
    FUN_00221bc4(0,param_1);
    FUN_00221474(0,param_1);
    if (param_2 != 0) {
      FUN_00221a9c(0,param_1,param_2);
      FUN_00221ad0(0,param_1,param_2);
      FUN_00221b20(0,param_1,param_2);
      FUN_00221b04(0,param_1,param_2);
      FUN_00220e34(0,param_1);
      return;
    }
  }
  return;
}




/* 0x00220ca8 */
void FUN_00220ca8(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  
  iVar2 = 0;
  if (param_2 != 0) {
    iVar2 = -1;
  }
  iVar2 = iVar2 + param_1;
  uVar1 = 0;
  do {
    iVar3 = iVar2 + uVar1 * 0x800;
    puVar4 = (uint *)(iVar3 + 0x480838);
    *puVar4 = *puVar4 & 0xfffeffff;
    puVar4 = (uint *)(iVar3 + 0x480830);
    *puVar4 = *puVar4 & 0xfffdffff;
    uVar1 = uVar1 + 1;
  } while (uVar1 < 4);
  uVar1 = 0;
  do {
    iVar3 = iVar2 + uVar1 * 0x800;
    do {
    } while (-1 < *(int *)(iVar3 + 0x4808d0) << 0x1d);
    do {
    } while (-1 < *(int *)(iVar3 + 0x480870) << 0x1d);
    uVar1 = uVar1 + 1;
  } while (uVar1 < 4);
  *(uint *)(iVar2 + 0x480038) = *(uint *)(iVar2 + 0x480038) & 0xfffeffff;
  *(uint *)(iVar2 + 0x480030) = *(uint *)(iVar2 + 0x480030) & 0xfffdffff;
  do {
  } while (-1 < *(int *)(iVar2 + 0x480070) << 0x1d);
  return;
}




/* 0x00220d20 */
void FUN_00220d20(param_1, param_2, param_3)
int param_1; int param_2; code * param_3;
{
  int iVar1;
  
  iVar1 = 0;
  if (param_2 != 0) {
    iVar1 = -1;
  }
  iVar1 = iVar1 + param_1;
  *(uint *)(iVar1 + 0x4800e0) = *(uint *)(iVar1 + 0x4800e0) & 0xbfffffff;
  (*param_3)(0x41,0);
  do {
  } while (-1 < *(int *)(iVar1 + 0x4800f4) << 0xd);
  return;
}




/* 0x00220d4c */
void FUN_00220d4c(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  
  if (param_2 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = -1;
  }
  iVar1 = iVar1 + param_1;
  if (*(int *)(iVar1 + 0x48083c) << 0x13 < 0) {
    uVar2 = 0;
    do {
      iVar4 = iVar1 + uVar2 * 0x800;
      *(uint *)(iVar4 + 0x48083c) = *(uint *)(iVar4 + 0x48083c) & 0xffffefff;
      *(uint *)(iVar4 + 0x480830) = *(uint *)(iVar4 + 0x480830) & 0xfffdffff;
      *(uint *)(iVar4 + 0x480840) = (*(uint *)(iVar4 + 0x480840) & 0xffffc0c0) + 0x2020;
      uVar2 = uVar2 + 1;
    } while (uVar2 < 4);
    *(uint *)(iVar1 + 0x48003c) = *(uint *)(iVar1 + 0x48003c) & 0xffffefff;
    *(uint *)(iVar1 + 0x480030) = *(uint *)(iVar1 + 0x480030) & 0xfffdffff;
    *(uint *)(iVar1 + 0x480040) = (*(uint *)(iVar1 + 0x480040) & 0xffffc0c0) + 0x2020;
    iVar1 = 0;
    if (param_2 != 0) {
      iVar1 = -1;
    }
    iVar1 = iVar1 + param_1;
    uVar2 = 0;
    do {
      iVar4 = iVar1 + uVar2 * 0x800;
      puVar3 = (uint *)(iVar4 + 0x480830);
      *puVar3 = *puVar3 | 0x20000;
      puVar3 = (uint *)(iVar4 + 0x480838);
      *puVar3 = *puVar3 | 0x10000;
      uVar2 = uVar2 + 1;
    } while (uVar2 < 4);
    *(uint *)(iVar1 + 0x480030) = *(uint *)(iVar1 + 0x480030) | 0x20000;
    *(uint *)(iVar1 + 0x480038) = *(uint *)(iVar1 + 0x480038) | 0x10000;
    return;
  }
  return;
}




/* 0x00220e34 */
void FUN_00220e34(param_1, param_2)
int param_1; int param_2;
{
  uint *puVar1;
  int iVar2;
  
  iVar2 = 0;
  if (param_2 != 0) {
    iVar2 = -1;
  }
  puVar1 = (uint *)(param_1 + iVar2 + 0x4800e0);
  *puVar1 = *puVar1 | 0x40000100;
  return;
}




/* 0x00220ee8 */
void FUN_00220ee8(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  
  if (param_2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = -1;
  }
  FUN_00220430(param_2,0x1010100,1,0);
  FUN_00222748(0,DAT_00223604,DAT_00223614);
  FUN_00222748(iVar2 + param_1,DAT_00223608,DAT_00223618);
  FUN_00222748(0x1f000,DAT_0022360c,DAT_0022361c);
  puVar4 = (uint *)(iVar2 + param_1 + 0x4800e0);
  *puVar4 = (*puVar4 & 0x3ffff8fc) + 0x603;
  FUN_002210d8(param_1,param_2,DAT_0022304c);
  FUN_002205bc(10,0);
  FUN_00221070(param_1,param_2,0x2205bd);
  FUN_00220fb4(param_1,param_2);
  iVar2 = 0;
  if (param_2 != 0) {
    iVar2 = -1;
  }
  iVar2 = iVar2 + param_1;
  uVar1 = 0;
  do {
    iVar3 = iVar2 + uVar1 * 0x800;
    puVar4 = (uint *)(iVar3 + 0x480830);
    *puVar4 = *puVar4 | 0x20000;
    puVar4 = (uint *)(iVar3 + 0x480838);
    *puVar4 = *puVar4 | 0x10000;
    uVar1 = uVar1 + 1;
  } while (uVar1 < 4);
  *(uint *)(iVar2 + 0x480030) = *(uint *)(iVar2 + 0x480030) | 0x20000;
  *(uint *)(iVar2 + 0x480038) = *(uint *)(iVar2 + 0x480038) | 0x10000;
  return;
}




/* 0x00220fb4 */
void FUN_00220fb4(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  if (param_2 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = -1;
  }
  iVar1 = iVar1 + param_1;
  uVar5 = *(uint *)(iVar1 + 0x480830) & 0x20000;
  uVar6 = *(uint *)(iVar1 + 0x480838) & 0x10000;
  if ((uVar5 != 0) && (uVar6 != 0)) {
    FUN_00220ca8(param_1);
  }
  uVar2 = 0;
  do {
    puVar3 = (uint *)(iVar1 + uVar2 * 0x800 + 0x480830);
    *puVar3 = *puVar3 | 0x10000;
    *puVar3 = *puVar3 & 0xfffeffff;
    uVar2 = uVar2 + 1;
  } while (uVar2 < 4);
  uVar2 = 0;
  do {
    iVar4 = iVar1 + uVar2 * 0x800;
    do {
    } while ((*(uint *)(iVar4 + 0x4808d0) & 1) == 0);
    do {
    } while ((*(uint *)(iVar4 + 0x480870) & 1) == 0);
    uVar2 = uVar2 + 1;
  } while (uVar2 < 4);
  *(uint *)(iVar1 + 0x480030) = *(uint *)(iVar1 + 0x480030) | 0x10000;
  *(uint *)(iVar1 + 0x480030) = *(uint *)(iVar1 + 0x480030) & 0xfffeffff;
  do {
  } while ((*(uint *)(iVar1 + 0x480070) & 1) == 0);
  if ((uVar5 != 0) && (uVar6 != 0)) {
    iVar1 = 0;
    if (param_2 != 0) {
      iVar1 = -1;
    }
    iVar1 = iVar1 + param_1;
    uVar5 = 0;
    do {
      iVar4 = iVar1 + uVar5 * 0x800;
      puVar3 = (uint *)(iVar4 + 0x480830);
      *puVar3 = *puVar3 | 0x20000;
      puVar3 = (uint *)(iVar4 + 0x480838);
      *puVar3 = *puVar3 | 0x10000;
      uVar5 = uVar5 + 1;
    } while (uVar5 < 4);
    *(uint *)(iVar1 + 0x480030) = *(uint *)(iVar1 + 0x480030) | 0x20000;
    *(uint *)(iVar1 + 0x480038) = *(uint *)(iVar1 + 0x480038) | 0x10000;
    return;
  }
  return;
}




/* 0x00221070 */
void FUN_00221070(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  uint uVar2;
  
  if (param_2 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = -1;
  }
  iVar1 = iVar1 + param_1;
  if ((*(uint *)(iVar1 + 0x4800e0) & 3) == 3) {
    uVar2 = *(uint *)(iVar1 + 0x4800e0) & 0x40000000;
    if (uVar2 != 0) {
      FUN_00220d20(param_1);
    }
    *(uint *)(iVar1 + 0x4800e0) = *(uint *)(iVar1 + 0x4800e0) | 0x80000000;
    do {
    } while (-1 < *(int *)(iVar1 + 0x4800f4) << 0xd);
    *(uint *)(iVar1 + 0x4800e0) = *(uint *)(iVar1 + 0x4800e0) & 0x7fffffff;
    if (uVar2 != 0) {
      FUN_00220e34(param_1,param_2);
      return;
    }
  }
  return;
}




/* 0x002210d8 */
void FUN_002210d8(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  
  iVar2 = 0;
  if (param_2 != 0) {
    iVar2 = -1;
  }
  iVar2 = iVar2 + param_1;
  uVar1 = 0;
  do {
    iVar3 = iVar2 + uVar1 * 0x800;
    puVar4 = (uint *)(iVar3 + 0x480850);
    *puVar4 = *puVar4 & 0xfffff000 | param_3 & 0xfff;
    puVar4 = (uint *)(iVar3 + 0x4808b0);
    *puVar4 = *puVar4 & 0xfffff000 | param_3 & 0xfff;
    uVar1 = uVar1 + 1;
  } while (uVar1 < 4);
  *(uint *)(iVar2 + 0x480050) = *(uint *)(iVar2 + 0x480050) & 0xfffff000 | param_3 & 0xfff;
  return;
}




/* 0x00221120 */
void FUN_00221120(param_1, param_2, param_3, param_4, param_5)
int param_1; int param_2; int param_3; uint param_4; uint param_5;
{
  uint uVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  uint uVar5;
  
  iVar2 = 0;
  if (param_2 != 0) {
    iVar2 = -1;
  }
  iVar2 = iVar2 + param_1;
  uVar1 = 0;
  if (param_3 == 0) {
    do {
      iVar4 = iVar2 + uVar1 * 0x800;
      if (((uVar1 == 1) || (uVar1 == 2)) && (0x12b128 < param_5)) {
        puVar3 = (uint *)(iVar4 + 0x4808b0);
        uVar5 = *puVar3 & 0xfffff000 | 300;
      }
      else if (param_5 - 0x100591 < 0x2ab98) {
        *(uint *)(iVar4 + 0x4808b0) = *(uint *)(iVar4 + 0x4808b0) & 0xfffff000 | 400;
        puVar3 = (uint *)(iVar4 + 0x480850);
        uVar5 = (*puVar3 & 0xfffff000) + 0x271;
      }
      else {
        puVar3 = (uint *)(iVar4 + 0x4808b0);
        uVar5 = *puVar3 & 0xfffff000 | param_4 & 0xfff;
      }
      *puVar3 = uVar5;
      uVar1 = uVar1 + 1;
    } while (uVar1 < 4);
  }
  else {
    do {
      puVar3 = (uint *)(iVar2 + uVar1 * 0x800 + 0x480850);
      *puVar3 = *puVar3 & 0xfffff000 | param_4 & 0xfff;
      uVar1 = uVar1 + 1;
    } while (uVar1 < 4);
  }
  if (param_5 < 0x12b129) {
    if (0x2ab97 < param_5 - 0x100591) {
      return;
    }
    uVar1 = *(uint *)(iVar2 + 0x480050) & 0xfffff000 | 400;
  }
  else {
    uVar1 = *(uint *)(iVar2 + 0x480050) & 0xfffff000 | 0x15e;
  }
  *(uint *)(iVar2 + 0x480050) = uVar1;
  return;
}




/* 0x00221230 */
undefined4 FUN_00221230(param_1, param_2)
int param_1; uint param_2;
{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 == 2) {
    if (param_2 < 0x412f9) {
      return 4;
    }
    if (param_2 < 0x518b1) {
      return 5;
    }
    if (400000 < param_2) {
      if (param_2 < 0x71e45) {
        uVar1 = 7;
      }
      else if (param_2 < 0x825f1) {
        return 8;
      }
      return uVar1;
    }
  }
  else {
    if (param_1 != 5) {
      return 0;
    }
    if (400000 < param_2) {
      if (param_2 < 0x82209) {
        return 8;
      }
      if (param_2 < 0x927c1) {
        return 9;
      }
      if (param_2 < 0xa2d79) {
        return 10;
      }
      if (0xb2f48 < param_2) {
        return 0xc;
      }
      return 0xb;
    }
  }
  return 6;
}




/* 0x002212c0 */
undefined4 FUN_002212c0(param_1)
int param_1;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  
  if (param_1 == 0) {
    iVar8 = 0;
  }
  else {
    iVar8 = -1;
  }
  iVar1 = FUN_00222380();
  iVar2 = FUN_00222380(param_1);
  if (*(int *)(iVar8 + 0x44d004) << 7 < 0) {
    uVar3 = FUN_0022141c(0,param_1,1,5);
    *(undefined4 *)(iVar1 + 4) = uVar3;
    uVar4 = FUN_0022141c(0,param_1,1,8);
    uVar6 = (uVar4 << 0x18) >> 0x1e;
    if (((uVar4 & 3) != 0) && ((uVar4 & 3) != 3)) {
      return 0;
    }
    uVar5 = (uint)(*(int *)(iVar2 + 0xac) << 0xc) >> 0x1c;
    if (uVar5 == 1) {
switchD_00221330_caseD_4:
      uVar3 = 0xd;
LAB_00221340:
      iVar2 = 9;
    }
    else {
      if (uVar5 == 2) {
switchD_00221330_caseD_5:
        uVar3 = 0xe;
        goto LAB_00221340;
      }
      if (uVar5 == 3) {
switchD_00221330_caseD_6:
        uVar3 = 0xe;
LAB_00221350:
        iVar2 = 10;
      }
      else {
        if (false) {
          return 0;
        }
        switch((uVar4 << 0x1a) >> 0x1c) {
        case 4:
          goto switchD_00221330_caseD_4;
        case 5:
          goto switchD_00221330_caseD_5;
        case 6:
          goto switchD_00221330_caseD_6;
        case 7:
        case 0xe:
          uVar3 = 0xf;
          goto LAB_00221350;
        case 8:
          uVar3 = 0xf;
          iVar2 = 0xb;
          break;
        default:
          goto LAB_002213d2;
        }
      }
    }
    if (uVar6 == 0) {
      uVar7 = 0x20;
    }
    else {
      if (uVar6 != 1) {
        return 0;
      }
      uVar7 = 0x10;
      iVar2 = iVar2 + 1;
    }
    *(undefined4 *)(iVar1 + 0x50) = 8;
    *(undefined4 *)(iVar1 + 0x60) = uVar7;
    *(undefined4 *)(iVar1 + 0x48) = uVar3;
    *(int *)(iVar1 + 0x4c) = iVar2;
  }
  if (-1 < *(int *)(iVar8 + 0x44d004) << 6) goto LAB_002213fc;
  uVar3 = FUN_0022141c(0,param_1,2,5);
  *(undefined4 *)(iVar1 + 4) = uVar3;
  uVar4 = FUN_0022141c(0,param_1,2,8);
  uVar6 = (uVar4 << 0x18) >> 0x1e;
  if (((uVar4 & 3) != 0) && ((uVar4 & 3) != 3)) {
    return 0;
  }
  if (false) {
    return 0;
  }
  switch((uVar4 << 0x1a) >> 0x1c) {
  case 4:
    uVar3 = 0xd;
    break;
  case 5:
    uVar3 = 0xe;
    break;
  case 6:
    uVar3 = 0xe;
    goto LAB_002213dc;
  case 7:
  case 0xe:
    uVar3 = 0xf;
LAB_002213dc:
    iVar8 = 10;
    goto LAB_002213c8;
  case 8:
    uVar3 = 0xf;
    iVar8 = 0xb;
    goto LAB_002213c8;
  default:
    goto LAB_002213d2;
  }
  iVar8 = 9;
LAB_002213c8:
  if (uVar6 == 0) {
    iVar2 = 0x20;
  }
  else {
    if (uVar6 != 1) {
LAB_002213d2:
      return 0;
    }
    iVar2 = 0x10;
    iVar8 = iVar8 + 1;
  }
  *(undefined4 *)(iVar1 + 0x5c) = 8;
  *(undefined4 *)(iVar1 + 0x54) = uVar3;
  *(int *)(iVar1 + 0x58) = iVar8;
  *(uint *)(iVar1 + 0x60) = *(uint *)(iVar1 + 0x60) | iVar2 << 0x10;
LAB_002213fc:
  if ((0xe < *(uint *)(iVar1 + 0x48)) || (0xe < *(uint *)(iVar1 + 0x54))) {
    *(undefined4 *)(iVar1 + 0xc) = 0x834;
    *(undefined4 *)(iVar1 + 0x24) = 0x898;
  }
  return 1;
}




/* 0x0022141c */
undefined4 FUN_0022141c(param_1, param_2, param_3, param_4)
int param_1; int param_2; uint param_3; uint param_4;
{
  int iVar1;
  
  iVar1 = 0;
  if (param_2 != 0) {
    iVar1 = -1;
  }
  param_1 = param_1 + iVar1;
  if (param_3 == 3) {
    param_3 = 1;
  }
  *(uint *)(param_1 + 0x44d030) =
       *(uint *)(param_1 + 0x44d030) & 0xf00fffff | (param_4 & 0xff) << 0x14;
  *(uint *)(param_1 + 0x44d020) =
       *(uint *)(param_1 + 0x44d020) & 0xcfffefff | (param_3 & 3) << 0x1c | 0x1000;
  do {
  } while (*(int *)(param_1 + 0x44d020) << 0x13 < 0);
  if (param_3 != 1) {
    return *(undefined4 *)(param_1 + 0x44d054);
  }
  return *(undefined4 *)(param_1 + 0x44d064);
}




/* 0x00221474 */
void FUN_00221474(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int extraout_r3;
  uint *puVar6;
  uint uVar7;
  uint *puVar8;
  uint *puVar9;
  uint *puVar10;
  uint *puVar11;
  uint *puVar12;
  uint *puVar13;
  int iVar14;
  
  iVar14 = param_1;
  iVar1 = FUN_00222380(param_2);
  iVar2 = 0;
  if (param_2 != 0) {
    iVar2 = -1;
  }
  iVar2 = iVar2 + param_1;
  puVar6 = (uint *)(iVar2 + 0x448400);
  *puVar6 = 0;
  puVar8 = (uint *)(iVar2 + 0x448410);
  *puVar8 = 0;
  puVar9 = (uint *)(iVar2 + 0x448414);
  *puVar9 = 0;
  puVar13 = (uint *)(iVar2 + 0x448420);
  *puVar13 = 0;
  puVar12 = (uint *)(iVar2 + 0x448424);
  *puVar12 = 0;
  puVar10 = (uint *)(iVar2 + 0x448430);
  *puVar10 = 0;
  puVar11 = (uint *)(iVar2 + 0x448434);
  *puVar11 = 0;
  uVar3 = FUN_0022254c();
  if ((uVar3 & 1) != 0) {
    *puVar6 = *puVar6 | 1;
  }
  iVar2 = FUN_0022254c();
  if (iVar2 << 0x1e < 0) {
    *puVar6 = *puVar6 | 0x10;
  }
  uVar3 = (uint)((1 << ((*(int *)(iVar1 + 0x48) + *(int *)(iVar1 + 0x4c)) - 0x14U & 0xff)) *
                 *(int *)(iVar1 + 0x50) * 0x20) >> 3;
  iVar2 = *(int *)(iVar1 + 0x5c) *
          (1 << ((*(int *)(iVar1 + 0x54) + *(int *)(iVar1 + 0x58)) - 0x14U & 0xff));
  uVar7 = (uint)(iVar2 * 0x20) >> 3;
  if (uVar3 == 0) {
    uVar3 = *puVar8 | 0x3fc;
  }
  else {
    if (uVar3 == 0x200) {
      iVar2 = 0x38;
    }
    else if (uVar3 < 0x201) {
      if (uVar3 == 0x40) {
        iVar2 = 0x3f;
      }
      else if (uVar3 == 0x80) {
        iVar2 = 0x3e;
      }
      else {
        if (uVar3 != 0x100) goto LAB_00221546;
        iVar2 = 0x3c;
      }
    }
    else if (uVar3 == 0x400) {
      iVar2 = 0x30;
    }
    else if (uVar3 == 0x800) {
      iVar2 = 0x20;
    }
    else {
LAB_00221546:
      iVar2 = 0;
    }
    *puVar10 = *puVar10 & 0xfffffc03 | iVar2 << 2;
    uVar5 = *puVar13;
    uVar3 = (*(int *)(iVar1 + 0x4c) - 8U | *(int *)(iVar1 + 0x48) * 0x10 - 0xd0U) & 0x9133 |
            (uint)(*(int *)(iVar1 + 0x50) != 4) << 8 | 0x8000 | uVar5 & 0xffff6ecc;
    *puVar13 = uVar3;
    uVar3 = FUN_00220aba(param_2,1,uVar3,uVar5 & 0xffff6ecc,iVar14);
    uVar3 = uVar3 >> 0x18 & 0x3fc | *puVar8 & 0xfffffc03;
    iVar2 = extraout_r3;
  }
  *puVar8 = uVar3;
  if (uVar7 == 0) {
    uVar3 = *puVar9 | 0x3fc;
    goto LAB_00221660;
  }
  if (uVar7 == 0x200) {
    iVar4 = 0x38;
  }
  else if (uVar7 < 0x201) {
    if (uVar7 == 0x40) {
      iVar4 = 0x3f;
    }
    else if (uVar7 == 0x80) {
      iVar4 = 0x3e;
    }
    else {
      if (uVar7 != 0x100) goto LAB_002215ea;
      iVar4 = 0x3c;
    }
  }
  else if (uVar7 == 0x400) {
    iVar4 = 0x30;
  }
  else if (uVar7 == 0x800) {
    iVar4 = 0x20;
  }
  else {
LAB_002215ea:
    iVar4 = 0;
  }
  *puVar11 = *puVar11 & 0xfffffc03 | iVar4 << 2;
  uVar3 = *puVar12;
  *puVar12 = (*(int *)(iVar1 + 0x58) - 8U | *(int *)(iVar1 + 0x54) * 0x10 - 0xd0U) & 0x9133 |
             (uint)(*(int *)(iVar1 + 0x5c) != 4) << 8 | 0x8000 | uVar3 & 0xffff6ecc;
  uVar3 = FUN_00220aba(param_2,2,uVar3 & 0xffff6ecc,iVar2,iVar14);
  uVar3 = uVar3 >> 0x18 & 0x3fc | *puVar9 & 0xfffffc03;
LAB_00221660:
  *puVar9 = uVar3;
  return;
}




/* 0x00221674 */
void FUN_00221674(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  int iVar1;
  uint *puVar2;
  
  iVar1 = 0;
  if (param_2 != 0) {
    iVar1 = -1;
  }
  param_1 = param_1 + iVar1;
  if ((param_3 & 1) != 0) {
    *(uint *)(param_1 + 0x448420) = *(uint *)(param_1 + 0x448420) & 0xffff7fff;
  }
  if ((int)(param_3 << 0x1e) < 0) {
    *(uint *)(param_1 + 0x448424) = *(uint *)(param_1 + 0x448424) & 0xffff7fff;
  }
  puVar2 = (uint *)(param_1 + 0x4485c4);
  *puVar2 = (*puVar2 & 0xfffffffc) + 1;
  do {
  } while ((*puVar2 & 3) != 0);
  do {
  } while ((*(uint *)(param_1 + 0x448450) & 0x30) == 0);
  return;
}




/* 0x002216cc */
void FUN_002216cc(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  int iVar1;
  uint *puVar2;
  
  iVar1 = 0;
  if (param_2 != 0) {
    iVar1 = -1;
  }
  if ((param_3 & 1) != 0) {
    puVar2 = (uint *)(param_1 + iVar1 + 0x448420);
    *puVar2 = *puVar2 | 0x8000;
  }
  if ((int)(param_3 << 0x1e) < 0) {
    puVar2 = (uint *)(param_1 + iVar1 + 0x448424);
    *puVar2 = *puVar2 | 0x8000;
  }
  return;
}




/* 0x002217e4 */
void FUN_002217e4(param_1, param_2, param_3, param_4)
int param_1; int param_2; uint param_3; undefined4 param_4;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  
  if (param_2 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = -1;
  }
  iVar1 = iVar1 + param_1;
  iVar2 = FUN_00222380(param_2);
  *(uint *)(iVar1 + 0x44d024) = (*(uint *)(iVar1 + 0x44d024) & 0xfffe0000) + 0x10005;
  *(uint *)(iVar1 + 0x44d020) =
       *(uint *)(iVar1 + 0x44d020) & 0xc7ffffff | (param_3 & 3) << 0x1c | 0x8000000;
  do {
  } while (*(int *)(iVar1 + 0x44d020) << 4 < 0);
  *(uint *)(iVar1 + 0x44d024) = (*(uint *)(iVar1 + 0x44d024) & 0xfffe0000) + 7;
  *(uint *)(iVar1 + 0x44d020) =
       *(uint *)(iVar1 + 0x44d020) & 0xcbffffff | (param_3 & 3) << 0x1c | 0x4000000;
  do {
  } while (*(int *)(iVar1 + 0x44d020) << 5 < 0);
  *(uint *)(iVar1 + 0x44d024) = (*(uint *)(iVar1 + 0x44d024) & 0xfffe0000) + 2;
  if (*(int *)(iVar2 + 8) == 2) {
    FUN_00221c78(param_1,param_2,param_3,0x3f,0);
  }
  else if (*(int *)(iVar2 + 8) == 5) {
    FUN_00221c78(param_1,param_2,param_3,0x3f,0xfc);
    *(uint *)(iVar1 + 0x44d024) = *(uint *)(iVar1 + 0x44d024) & 0xffff0000;
  }
  *(uint *)(iVar1 + 0x44d024) = (*(uint *)(iVar1 + 0x44d024) & 0xfffe0000) + 0x10014;
  if ((param_3 & 1) != 0) {
    *(uint *)(iVar1 + 0x44d020) = *(uint *)(iVar1 + 0x44d020) & 0xdfffffff | 0x10040000;
    do {
    } while (*(int *)(iVar1 + 0x44d020) << 0xd < 0);
  }
  if ((int)(param_3 << 0x1e) < 0) {
    *(uint *)(iVar1 + 0x44d020) = *(uint *)(iVar1 + 0x44d020) & 0xefffffff | 0x20040000;
    do {
    } while (*(int *)(iVar1 + 0x44d020) << 0xd < 0);
  }
  *(uint *)(iVar1 + 0x44d024) = (*(uint *)(iVar1 + 0x44d024) & 0xfffe0000) + 0x10005;
  iVar5 = *(int *)(iVar2 + 100);
  uVar3 = 0xc0;
  if (iVar5 == 4) {
    uVar3 = 0xc2;
  }
  else if (iVar5 == 8) {
    uVar3 = 0xc3;
  }
  else if (iVar5 == 0x10) {
    uVar3 = 0xc4;
  }
  FUN_00221c78(param_1,param_2,param_3,1,uVar3);
  uVar4 = (uint)(*(int *)(iVar2 + 0x68) << 0xc) >> 0x1c;
  if (uVar4 == 0) {
    uVar4 = 1;
  }
  FUN_00221c78(param_1,param_2,param_3,3,uVar4);
  *(uint *)(iVar1 + 0x44d024) = (*(uint *)(iVar1 + 0x44d024) & 0xfffe0000) + 0x10005;
  iVar5 = FUN_00221230(*(undefined4 *)(iVar2 + 8),param_4);
  iVar2 = FUN_00221c20(*(undefined4 *)(iVar2 + 8),param_4);
  if (iVar5 == 3) {
    if (iVar2 == 1) goto LAB_002219ba;
  }
  else if (iVar5 == 4) {
    if (iVar2 == 2) goto LAB_002219ba;
  }
  else if (iVar5 == 5) {
    if (iVar2 == 2) {
      iVar2 = 3;
      goto LAB_002219ba;
    }
  }
  else if (iVar5 == 6) {
    if (iVar2 == 3) {
      iVar2 = 4;
      goto LAB_002219ba;
    }
  }
  else if (iVar5 == 7) {
    if (iVar2 == 4) {
      iVar2 = 5;
      goto LAB_002219ba;
    }
  }
  else if (iVar5 == 8) {
    if (iVar2 == 4) {
      iVar2 = 6;
      goto LAB_002219ba;
    }
  }
  else if (iVar5 == 9) {
    if (iVar2 == 5) {
      iVar2 = 7;
      goto LAB_002219ba;
    }
  }
  else if (iVar5 == 10) {
    if (iVar2 == 6) {
      iVar2 = 8;
      goto LAB_002219ba;
    }
  }
  else if ((iVar5 == 0xb) && (iVar2 == 6)) {
    iVar2 = 9;
    goto LAB_002219ba;
  }
  iVar2 = 10;
LAB_002219ba:
  FUN_00221c78(param_1,param_2,param_3,2,iVar2);
  if ((param_3 & 1) != 0) {
    *(uint *)(iVar1 + 0x44d004) = *(uint *)(iVar1 + 0x44d004) | 0x1000000;
  }
  if ((int)(param_3 << 0x1e) < 0) {
    *(uint *)(iVar1 + 0x44d004) = *(uint *)(iVar1 + 0x44d004) | 0x2000000;
  }
  *(uint *)(iVar1 + 0x44d024) = *(uint *)(iVar1 + 0x44d024) & 0xffff0000;
  return;
}




/* 0x002219fc */
void FUN_002219fc(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  uint *puVar1;
  int iVar2;
  
  iVar2 = 0;
  if (param_2 != 0) {
    iVar2 = -1;
  }
  if ((param_3 & 1) != 0) {
    puVar1 = (uint *)(param_1 + iVar2 + 0x44d0f0);
    *puVar1 = *puVar1 & 0xefffffff;
  }
  if ((int)(param_3 << 0x1e) < 0) {
    puVar1 = (uint *)(param_1 + iVar2 + 0x44d0f0);
    *puVar1 = *puVar1 & 0xdfffffff;
  }
  return;
}




/* 0x00221a30 */
void FUN_00221a30(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  uint *puVar1;
  int iVar2;
  
  iVar2 = 0;
  if (param_2 != 0) {
    iVar2 = -1;
  }
  if ((param_3 & 1) != 0) {
    puVar1 = (uint *)(param_1 + iVar2 + 0x44d0f4);
    *puVar1 = *puVar1 & 0xefffffff;
  }
  if ((int)(param_3 << 0x1e) < 0) {
    puVar1 = (uint *)(param_1 + iVar2 + 0x44d0f4);
    *puVar1 = *puVar1 & 0xdfffffff;
  }
  return;
}




/* 0x00221a64 */
void FUN_00221a64(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  uint *puVar1;
  int iVar2;
  
  iVar2 = 0;
  if (param_2 != 0) {
    iVar2 = -1;
  }
  puVar1 = (uint *)(param_1 + iVar2 + 0x44d0a0);
  *puVar1 = *puVar1 & ~(param_3 << 0x10);
  return;
}




/* 0x00221a80 */
void FUN_00221a80(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  uint *puVar1;
  int iVar2;
  
  iVar2 = 0;
  if (param_2 != 0) {
    iVar2 = -1;
  }
  puVar1 = (uint *)(param_1 + iVar2 + 0x44d0d0);
  *puVar1 = *puVar1 & ~(param_3 << 0x1c);
  return;
}




/* 0x00221a9c */
void FUN_00221a9c(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  uint *puVar1;
  int iVar2;
  
  iVar2 = 0;
  if (param_2 != 0) {
    iVar2 = -1;
  }
  if ((param_3 & 1) != 0) {
    puVar1 = (uint *)(param_1 + iVar2 + 0x44d0f0);
    *puVar1 = *puVar1 | 0x10000000;
  }
  if ((int)(param_3 << 0x1e) < 0) {
    puVar1 = (uint *)(param_1 + iVar2 + 0x44d0f0);
    *puVar1 = *puVar1 | 0x20000000;
  }
  return;
}




/* 0x00221ad0 */
void FUN_00221ad0(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  uint *puVar1;
  int iVar2;
  
  iVar2 = 0;
  if (param_2 != 0) {
    iVar2 = -1;
  }
  if ((param_3 & 1) != 0) {
    puVar1 = (uint *)(param_1 + iVar2 + 0x44d0f4);
    *puVar1 = *puVar1 | 0x10000000;
  }
  if ((int)(param_3 << 0x1e) < 0) {
    puVar1 = (uint *)(param_1 + iVar2 + 0x44d0f4);
    *puVar1 = *puVar1 | 0x20000000;
  }
  return;
}




/* 0x00221b04 */
void FUN_00221b04(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  uint *puVar1;
  int iVar2;
  
  iVar2 = 0;
  if (param_2 != 0) {
    iVar2 = -1;
  }
  puVar1 = (uint *)(param_1 + iVar2 + 0x44d0a0);
  *puVar1 = *puVar1 | param_3 << 0x10;
  return;
}




/* 0x00221b20 */
void FUN_00221b20(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  uint *puVar1;
  int iVar2;
  
  iVar2 = 0;
  if (param_2 != 0) {
    iVar2 = -1;
  }
  puVar1 = (uint *)(param_1 + iVar2 + 0x44d0d0);
  *puVar1 = *puVar1 | param_3 << 0x1c;
  return;
}




/* 0x00221b80 */
void FUN_00221b80(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  int iVar1;
  
  iVar1 = 0;
  if (param_2 != 0) {
    iVar1 = -1;
  }
  param_1 = param_1 + iVar1;
  *(uint *)(param_1 + 0x44d020) =
       *(uint *)(param_1 + 0x44d020) & 0xcfffdfff | (param_3 & 3) << 0x1c | 0x2000;
  do {
  } while (*(int *)(param_1 + 0x44d020) << 0x12 < 0);
  do {
  } while (*(int *)(param_1 + 0x44d074) << 0x1e < 0);
  return;
}




/* 0x00221bc4 */
void FUN_00221bc4(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  if (param_2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = -1;
  }
  iVar2 = iVar2 + param_1;
  iVar1 = FUN_00222380();
  uVar3 = *(uint *)(iVar2 + 0x44d004) & 0xffcfffff;
  if (*(int *)(iVar1 + 0x50) == 8) {
    uVar3 = uVar3 | 0x100000;
  }
  *(uint *)(iVar2 + 0x44d004) = uVar3;
  iVar1 = FUN_00222078(*(undefined4 *)(iVar1 + 0x20),1000);
  iVar1 = FUN_00222078(iVar1 * 0x4b00,10000);
  *(uint *)(iVar2 + 0x44d0f0) = *(uint *)(iVar2 + 0x44d0f0) & 0xfffffc00 | iVar1 - 1U & 0x3ff;
  return;
}




/* 0x00221c20 */
undefined4 FUN_00221c20(param_1, param_2)
int param_1; uint param_2;
{
  if (param_1 == 2) {
    if (param_2 < 0x518b1) {
      return 2;
    }
    if (400000 < param_2) {
      if (0x825f0 < param_2) {
        return 0;
      }
      return 4;
    }
  }
  else {
    if (param_1 != 5) {
      return 0;
    }
    if (400000 < param_2) {
      if (param_2 < 0x82209) {
        return 4;
      }
      if (600000 < param_2) {
        return 6;
      }
      return 5;
    }
  }
  return 3;
}




/* 0x00221c78 */
void FUN_00221c78(param_1, param_2, param_3, param_4, param_5)
int param_1; int param_2; uint param_3; int param_4; uint param_5;
{
  int iVar1;
  
  iVar1 = 0;
  if (param_2 != 0) {
    iVar1 = -1;
  }
  param_1 = param_1 + iVar1;
  *(uint *)(param_1 + 0x44d030) =
       *(uint *)(param_1 + 0x44d030) & 0xf00f0000 | (param_5 | param_4 << 0x14) & 0xff0ffff;
  *(uint *)(param_1 + 0x44d020) = *(uint *)(param_1 + 0x44d020) & 0xcfffffff | (param_3 & 3) << 0x1c
  ;
  if (((param_4 != 0x29) && (param_4 != 0x2a)) && (param_4 != 0x30)) {
    *(uint *)(param_1 + 0x44d020) = *(uint *)(param_1 + 0x44d020) | 0x800;
    do {
    } while (*(int *)(param_1 + 0x44d020) << 0x14 < 0);
    return;
  }
  *(uint *)(param_1 + 0x44d020) = *(uint *)(param_1 + 0x44d020) | 0x40;
  do {
  } while (*(int *)(param_1 + 0x44d020) << 0x19 < 0);
  return;
}




/* 0x00221cd8 */
void FUN_00221cd8(param_1, param_2, param_3, param_4)
int param_1; uint param_2; undefined4 param_3; int param_4;
{
  if (((param_1 != 0) && (param_2 < *(uint *)(param_1 + 0x18))) && (param_4 != 0)) {
    FUN_00221d18();
    return;
  }
  return;
}




/* 0x00221cd8 */
void thunk_FUN_00221cd8()
{
  FUN_00221cd8();
  return;
}




/* 0x00221cf2 */
void FUN_00221cf2(param_1)
int param_1;
{
  if (param_1 != 0) {
    FUN_00221e30();
    return;
  }
  return;
}




/* 0x00221cf2 */
void thunk_FUN_00221cf2()
{
  FUN_00221cf2();
  return;
}




/* 0x00221cfc */
void FUN_00221cfc(param_1, param_2, param_3, param_4)
int param_1; uint param_2; undefined4 param_3; int param_4;
{
  if (((param_1 != 0) && (param_2 < *(uint *)(param_1 + 0x18))) && (param_4 != 0)) {
    FUN_00221e5c();
    return;
  }
  return;
}




/* 0x00221cfc */
void thunk_FUN_00221cfc()
{
  FUN_00221cfc();
  return;
}




/* 0x00221d18 */
void FUN_00221d18(param_1, param_2, param_3, param_4)
int * param_1; int param_2; uint param_3; undefined1 * param_4;
{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  
  if (param_3 < 3) {
    iVar4 = param_3 * 0x10 + 0x2200;
    iVar3 = *param_1 + param_2 * 0x80;
    if ((*(uint *)(iVar3 + iVar4) & 1) == 0) {
      uVar2 = 0;
      *param_4 = 0;
      *(undefined4 *)(param_4 + 8) = 0;
      *(undefined4 *)(param_4 + 0xc) = 0;
      *(undefined4 *)(param_4 + 0x10) = 0;
      *(undefined4 *)(param_4 + 0x14) = 0;
      *(undefined4 *)(param_4 + 0x18) = 0;
    }
    else {
      uVar1 = *(uint *)(iVar3 + iVar4);
      uVar6 = 0;
      uVar5 = *(uint *)(iVar3 + param_3 * 0x10 + 0x2208);
      uVar9 = 0;
      uVar8 = uVar5 & 0x400;
      uVar7 = 0;
      uVar10 = 0;
      if (0x20 < *(uint *)(*param_1 + 0x1020) >> 0x18) {
        uVar6 = *(uint *)(iVar3 + param_3 * 0x10 + 0x2204) & 0xf;
        uVar9 = 0xf;
        uVar10 = *(uint *)(iVar3 + param_3 * 0x10 + 0x220c) & 0xf;
        uVar7 = 0xf;
      }
      *param_4 = 1;
      *(uint *)(param_4 + 8) = uVar1 & 0xfff00000;
      *(uint *)(param_4 + 0xc) = uVar6 & uVar9;
      uVar5 = ~(uVar5 & 0xfff00000);
      *(uint *)(param_4 + 0x10) = uVar5 + 1;
      *(uint *)(param_4 + 0x14) = (uVar7 & ~uVar10) + (uint)(0xfffffffe < uVar5);
      *(uint *)(param_4 + 0x18) = (uVar1 & 2) >> 1;
      if ((uVar1 & 0x400 & uVar8) != 0) {
        *(undefined4 *)(param_4 + 0x1c) = 1;
        return;
      }
      if (uVar8 == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = 2;
      }
    }
    *(undefined4 *)(param_4 + 0x1c) = uVar2;
  }
  return;
}




/* 0x00221e30 */
void FUN_00221e30(param_1)
undefined4 * param_1;
{
  uint uVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)*param_1;
  uVar1 = puVar2[0x408];
  param_1[2] = (uVar1 << 8) >> 0x18;
  param_1[5] = uVar1 & 0xff;
  param_1[6] = (uVar1 << 0x10) >> 0x18;
  param_1[3] = uVar1 >> 0x18;
  param_1[4] = (uint)puVar2[0x40c] >> 0x10;
  param_1[7] = *puVar2;
  return;
}




/* 0x00221e5c */
void FUN_00221e5c(param_1, param_2, param_3, param_4)
int * param_1; int param_2; uint param_3; char * param_4;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  if (param_3 < 3) {
    if (*param_4 == '\0') {
      uVar4 = 0;
      uVar2 = 0;
      uVar5 = 0;
      uVar6 = 0;
    }
    else {
      uVar3 = *(uint *)(param_4 + 8) & 0xfff00000;
      uVar5 = ~(*(int *)(param_4 + 0x10) - 1U) & 0xfff00000;
      uVar2 = *(uint *)(param_4 + 0xc) & 0xf;
      uVar4 = uVar3 | 1;
      uVar6 = ~(*(int *)(param_4 + 0x14) + -1 + (uint)(*(int *)(param_4 + 0x10) != 0)) & 0xf;
      if (*(int *)(param_4 + 0x18) == 0) {
        iVar1 = *(int *)(param_4 + 0x1c);
        if (iVar1 != 0) {
          if (iVar1 == 1) {
            uVar4 = uVar3 | 0x401;
          }
          else if (iVar1 != 2) {
            return;
          }
          uVar5 = uVar5 | 0x400;
        }
      }
      else {
        if (*(int *)(param_4 + 0x18) != 1) {
          return;
        }
        uVar4 = uVar3 | 3;
      }
    }
    if (0x20 < *(uint *)(*param_1 + 0x1020) >> 0x18) {
      *(uint *)(*param_1 + param_2 * 0x80 + param_3 * 0x10 + 0x220c) = uVar6;
      *(uint *)(*param_1 + param_2 * 0x80 + param_3 * 0x10 + 0x2204) = uVar2;
    }
    *(uint *)(*param_1 + param_2 * 0x80 + param_3 * 0x10 + 0x2208) = uVar5;
    *(uint *)(*param_1 + param_2 * 0x80 + param_3 * 0x10 + 0x2200) = uVar4;
  }
  return;
}




/* 0x00221f58 */
void FUN_00221f58(param_1)
int param_1;
{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  int local_60;
  int iStack_5c;
  int local_58;
  int iStack_54;
  uint local_50;
  uint local_4c;
  uint uStack_48;
  uint local_44;
  undefined4 local_30;
  undefined4 local_2c;
  uint local_28;
  
  if (DAT_00223004 == 0) {
    return;
  }
  if (DAT_00223000 == '\0') {
    thunk_FUN_08006bdc(&local_30,&DAT_002228f4,0x20);
    FUN_00222448(&local_60);
    if (local_4c <= local_44 && (uint)(uStack_48 <= local_50) <= local_4c - local_44) {
      uStack_48 = local_50;
    }
    local_2c = 0x87ce0000;
    local_30 = 0x87ce0000;
    local_28 = (local_60 + iStack_5c + local_58 + iStack_54) * 0x100000 - (-0x78320000 - uStack_48)
               >> 10;
    uVar1 = thunk_FUN_08007edc();
    iVar2 = thunk_FUN_08016dd4(uVar1,&local_30);
    if (iVar2 == 0) {
      ((code*)DAT_0804cd60)("boot_extern_ddr_interface.c",400,0x3056);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
  }
  if (DAT_00223001 == '\0') {
    do {
      iVar2 = DAT_00223014 + -1;
      bVar3 = DAT_00223014 == 0;
      DAT_00223014 = iVar2;
      if (bVar3) break;
      local_60 = param_1;
      iVar2 = thunk_FUN_0801ad44(DAT_00223004,DAT_00223008,DAT_0022300c,DAT_00223010);
    } while (iVar2 != 0);
  }
  else {
    do {
      iVar2 = DAT_00223014 + -1;
      bVar3 = DAT_00223014 == 0;
      DAT_00223014 = iVar2;
      if (bVar3) break;
      iVar2 = thunk_FUN_0801afc4(DAT_00223004,DAT_00223008,param_1);
    } while (iVar2 != 0);
  }
  ((code *)0x801b1e0)();
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x00221f58 */
void thunk_FUN_00221f58()
{
  FUN_00221f58();
  return;
}




/* 0x00222058 */
undefined4 FUN_00222058()
{
  _DAT_004a1000 = (_DAT_004a1000 & 0x102) + 1;
  _DAT_004a4040 = 0x3f;
  return 1;
}




/* 0x00222078 */
int FUN_00222078(param_1, param_2)
uint param_1; uint param_2;
{
  int iVar1;
  
  iVar1 = 0;
  for (; param_2 <= param_1; param_1 = param_1 - param_2) {
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}




/* 0x00222088 */
void thunk_FUN_00222088()
{
  thunk_FUN_00222088();
  return;
}




/* 0x00222088 */
void FUN_00222088()
{
  return;
}




/* 0x0022208c */
void FUN_0022208c(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  
  uVar1 = 0;
  FUN_0022042a();
  if (param_1 == 0) {
    if ((param_2 << 0x1f != 0) && (DAT_00223934 == 1)) {
      uVar1 = 1;
      DAT_00223934 = 4;
    }
    if ((param_2 << 0x1e < 0) && (DAT_00223938 == 1)) {
      uVar1 = uVar1 | 2;
      DAT_00223938 = 4;
    }
  }
  else {
    if ((param_2 << 0x1f != 0) && (DAT_0022393c == 1)) {
      uVar1 = 1;
      DAT_0022393c = 4;
    }
    if ((param_2 << 0x1e < 0) && (DAT_00223940 == 1)) {
      uVar1 = uVar1 | 2;
      DAT_00223940 = 4;
    }
  }
  if (uVar1 != 0) {
    FUN_00220a14(0,param_1,uVar1);
  }
  return;
}




/* 0x0022208c */
void thunk_FUN_0022208c()
{
  FUN_0022208c();
  return;
}




/* 0x002220f8 */
void FUN_002220f8(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  
  uVar1 = 0;
  FUN_0022042a();
  if (param_1 == 0) {
    if ((param_2 << 0x1f != 0) && (DAT_00223934 == 1)) {
      uVar1 = 1;
      DAT_00223934 = 2;
    }
    if ((param_2 << 0x1e < 0) && (DAT_00223938 == 1)) {
      uVar1 = uVar1 | 2;
      DAT_00223938 = 2;
    }
  }
  else {
    if ((param_2 << 0x1f != 0) && (DAT_0022393c == 1)) {
      uVar1 = 1;
      DAT_0022393c = 2;
    }
    if ((param_2 << 0x1e < 0) && (DAT_00223940 == 1)) {
      uVar1 = uVar1 | 2;
      DAT_00223940 = 2;
    }
  }
  if (uVar1 != 0) {
    FUN_00220a2e(0,param_1,uVar1,0x2205bd);
  }
  return;
}




/* 0x002220f8 */
void thunk_FUN_002220f8()
{
  FUN_002220f8();
  return;
}




/* 0x00222168 */
void FUN_00222168(param_1, param_2, param_3)
int param_1; int param_2; undefined4 param_3;
{
  uint uVar1;
  
  uVar1 = 0;
  FUN_0022042a();
  if (param_1 == 0) {
    if ((param_2 << 0x1f != 0) && (DAT_00223934 == 4)) {
      uVar1 = 1;
      DAT_00223934 = 1;
    }
    if ((param_2 << 0x1e < 0) && (DAT_00223938 == 4)) {
      uVar1 = uVar1 | 2;
      DAT_00223938 = 1;
    }
  }
  else {
    if ((param_2 << 0x1f != 0) && (DAT_0022393c == 4)) {
      uVar1 = 1;
      DAT_0022393c = 1;
    }
    if ((param_2 << 0x1e < 0) && (DAT_00223940 == 4)) {
      uVar1 = uVar1 | 2;
      DAT_00223940 = 1;
    }
  }
  if (uVar1 != 0) {
    FUN_00220a60(0,param_1,uVar1,param_3);
  }
  return;
}




/* 0x00222168 */
void thunk_FUN_00222168()
{
  FUN_00222168();
  return;
}




/* 0x002221d8 */
void FUN_002221d8(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  
  uVar1 = 0;
  FUN_0022042a();
  if (param_1 == 0) {
    if ((param_2 << 0x1f != 0) && (DAT_00223934 == 2)) {
      uVar1 = 1;
      DAT_00223934 = 1;
    }
    if ((param_2 << 0x1e < 0) && (DAT_00223938 == 2)) {
      uVar1 = uVar1 | 2;
      DAT_00223938 = 1;
    }
  }
  else {
    if ((param_2 << 0x1f != 0) && (DAT_0022393c == 2)) {
      uVar1 = 1;
      DAT_0022393c = 1;
    }
    if ((param_2 << 0x1e < 0) && (DAT_00223940 == 2)) {
      uVar1 = uVar1 | 2;
      DAT_00223940 = 1;
    }
  }
  if (uVar1 != 0) {
    FUN_00220a80(0,param_1,uVar1,0x2205bd);
  }
  return;
}




/* 0x002221d8 */
void thunk_FUN_002221d8()
{
  FUN_002221d8();
  return;
}




/* 0x00222248 */
void thunk_FUN_00222248()
{
  thunk_FUN_00222248();
  return;
}




/* 0x00222248 */
void FUN_00222248(param_1)
undefined4 param_1;
{
  int iVar1;
  int iVar2;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  thunk_FUN_08006d14(&local_48,0x38);
  iVar1 = FUN_00222380(0);
  iVar2 = FUN_00222380(1);
  local_48 = ((uint)(*(int *)(iVar1 + 0x50) << 5) >> 3) *
             (1 << ((*(int *)(iVar1 + 0x4c) + *(int *)(iVar1 + 0x48)) - 0x14U & 0xff));
  local_44 = ((uint)(*(int *)(iVar1 + 0x5c) << 5) >> 3) *
             (1 << ((*(int *)(iVar1 + 0x54) + *(int *)(iVar1 + 0x58)) - 0x14U & 0xff));
  local_40 = ((uint)(*(int *)(iVar2 + 0x50) << 5) >> 3) *
             (1 << ((*(int *)(iVar2 + 0x48) + *(int *)(iVar2 + 0x4c)) - 0x14U & 0xff));
  local_3c = ((uint)(*(int *)(iVar2 + 0x5c) << 5) >> 3) *
             (1 << ((*(int *)(iVar2 + 0x54) + *(int *)(iVar2 + 0x58)) - 0x14U & 0xff));
  if ((*(int *)(iVar1 + 8) == 5) && (DAT_00223018 != '\0')) {
    if ((local_48 != 0) && (iVar2 = FUN_0022141c(0,0,1,8), iVar2 == 0x3b)) {
      local_48 = 0x300;
    }
    if ((local_44 != 0) && (iVar2 = FUN_0022141c(0,0,2,8), iVar2 == 0x3b)) {
      local_44 = 0x300;
    }
    if ((local_40 != 0) && (iVar2 = FUN_0022141c(0,1,1,8), iVar2 == 0x3b)) {
      local_40 = 0x300;
    }
    if ((local_3c != 0) && (iVar2 = FUN_0022141c(0,0,2,8), iVar2 == 0x3b)) {
      local_3c = 0x300;
    }
  }
  local_38 = FUN_00220aba(0,1);
  uStack_34 = 0;
  local_30 = FUN_00220aba(0,2);
  uStack_2c = 0;
  local_28 = FUN_00220aba(1);
  uStack_24 = 0;
  local_20 = FUN_00220aba(1,2);
  uStack_1c = 0;
  local_18 = FUN_0022254c();
  local_14 = *(undefined4 *)(iVar1 + 8);
  thunk_FUN_08006bdc(param_1,&local_48,0x38);
  return;
}




/* 0x00222380 */
undefined4 FUN_00222380(param_1)
int param_1;
{
  int iVar1;
  
  iVar1 = DAT_00223038;
  if (param_1 != 0) {
    iVar1 = DAT_0022303c;
  }
  if (iVar1 != 0) {
    return 0;
  }
  if (param_1 == 0) {
    DAT_00223038 = DAT_00223024;
    return 0;
  }
  iVar1 = *(int *)(DAT_00223024 + 8);
  if (iVar1 != 2) {
    if (iVar1 == 4) {
      iVar1 = 0xa8;
      goto LAB_002223a0;
    }
    if (iVar1 != 5) {
      iVar1 = 0;
      goto LAB_002223a0;
    }
  }
  iVar1 = 0xb8;
LAB_002223a0:
  DAT_0022303c = DAT_00223024 + iVar1;
  return 0;
}




/* 0x002223bc */
void thunk_FUN_002223bc()
{
  thunk_FUN_002223bc();
  return;
}




/* 0x002223bc */
void FUN_002223bc(param_1)
undefined4 param_1;
{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  
  thunk_FUN_08006d14(&local_38,0x20);
  bVar1 = FUN_0022254c();
  iVar2 = FUN_00222380(0);
  iVar3 = FUN_00222380(1);
  if (*(int *)(iVar2 + 0x48) != 0) {
    uStack_34 = FUN_00220aba(0,1);
    local_38 = 8;
  }
  if (*(int *)(iVar2 + 0x54) != 0) {
    uStack_2c = FUN_00220aba(0,2);
    local_30 = 8;
  }
  if (((bVar1 & 1) == 0) && (*(int *)(iVar3 + 0x48) != 0)) {
    uStack_24 = FUN_00220aba(1);
    local_28 = 8;
  }
  if ((-1 < (int)((uint)bVar1 << 0x1e)) && (*(int *)(iVar3 + 0x54) != 0)) {
    uStack_1c = FUN_00220aba(1,2);
    local_20 = 8;
  }
  thunk_FUN_08006bdc(param_1,&local_38,0x20);
  return;
}




/* 0x0022243c */
undefined4 FUN_0022243c()
{
  return DAT_00223028;
}




/* 0x00222448 */
void thunk_FUN_00222448()
{
  thunk_FUN_00222448();
  return;
}




/* 0x00222448 */
void FUN_00222448(param_1)
undefined4 param_1;
{
  int local_40;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  uint local_10;
  
  FUN_00222248(&local_40);
  if ((local_10 & 1) != 0) {
    local_38 = 0;
    local_40 = local_40 << 1;
  }
  if ((int)(local_10 << 0x1e) < 0) {
    local_34 = 0;
    local_3c = local_3c << 1;
  }
  thunk_FUN_08006bdc(param_1,&local_40,0x30);
  return;
}




/* 0x00222484 */
void FUN_00222484()
{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  FUN_00220428();
  iVar1 = FUN_00222380(0);
  iVar2 = FUN_00222380(1);
  DAT_00223934 = (uint)(*(int *)(iVar1 + 0x48) != 0);
  DAT_00223938 = (uint)(*(int *)(iVar1 + 0x54) != 0);
  DAT_0022393c = (uint)(*(int *)(iVar2 + 0x48) != 0);
  DAT_00223940 = (uint)(*(int *)(iVar2 + 0x54) != 0);
  iVar1 = FUN_00222380(0);
  if (*(int *)(iVar1 + 8) == 5) {
    DAT_00223610 = &DAT_00223548;
    DAT_00223614 = &DAT_002235e0;
    DAT_00223618 = &DAT_002235e8;
    DAT_0022361c = &DAT_002235f8;
  }
  DAT_0022304c = 0x271;
  DAT_00223b50 = 0x20a2f;
  DAT_00223b54 = 0x20a81;
  DAT_00223b58 = 0x21231;
  DAT_00223b5c = 0x21c21;
  DAT_00223b60 = 0x20551;
  DAT_00223b64 = 0x20771;
  DAT_00223b68 = 0x20739;
  DAT_00223b6c = 0x21071;
  DAT_00223b70 = 0x210d9;
  DAT_00223b74 = 0x20fb5;
  DAT_00223b80 = 0x211f1;
  DAT_00223b84 = 0x21121;
  DAT_00223b78 = 0x20e55;
  DAT_00223b7c = 0x20d4d;
  puVar3 = (undefined4 *)FUN_0022243c();
  *puVar3 = 0;
  puVar3[1] = 0x23b50;
  puVar3[2] = 0x38;
  return;
}




/* 0x002224cc */
void thunk_FUN_002224cc()
{
  thunk_FUN_002224cc();
  return;
}




/* 0x002224cc */
void FUN_002224cc(param_1)
undefined4 param_1;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (DAT_00223018 == '\0') {
    FUN_00222484();
    DAT_00223944 = param_1;
    if (DAT_00223934 != 0) {
      if (DAT_00223938 == 0) {
        uVar3 = 1;
      }
      else {
        uVar3 = 3;
      }
      FUN_00220b2c(0,uVar3,param_1);
    }
    if (DAT_0022393c != 0) {
      if (DAT_00223940 == 0) {
        uVar3 = 1;
      }
      else {
        uVar3 = 3;
      }
      FUN_00220b2c(1,uVar3,param_1);
    }
    iVar1 = FUN_00222380(0);
    iVar2 = FUN_00222380(1);
    DAT_00223934 = (uint)(*(int *)(iVar1 + 0x48) != 0);
    DAT_00223938 = (uint)(*(int *)(iVar1 + 0x54) != 0);
    DAT_0022393c = (uint)(*(int *)(iVar2 + 0x48) != 0);
    DAT_00223940 = (uint)(*(int *)(iVar2 + 0x54) != 0);
    FUN_002225f8();
    DAT_00223018 = '\x01';
  }
  return;
}




/* 0x0022254c */
undefined4 FUN_0022254c()
{
  return DAT_00223040;
}




/* 0x00222558 */
bool FUN_00222558(param_1)
int param_1;
{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  iVar1 = FUN_00222380();
  uVar4 = 2;
  iVar3 = DAT_00223034 << 1;
  do {
    iVar2 = DAT_00223038;
    if (DAT_00223030 <= uVar4) {
LAB_002225d0:
      DAT_00223038 = iVar2;
      return uVar4 < DAT_00223030;
    }
    iVar2 = DAT_00223024 + iVar3;
    if (((((*(int *)(iVar2 + 4) == *(int *)(iVar1 + 4)) &&
          (*(int *)(iVar2 + 0x48) == *(int *)(iVar1 + 0x48))) &&
         (*(int *)(iVar2 + 0x4c) == *(int *)(iVar1 + 0x4c))) &&
        ((*(int *)(iVar2 + 0x50) == *(int *)(iVar1 + 0x50) &&
         (*(int *)(iVar2 + 0x54) == *(int *)(iVar1 + 0x54))))) &&
       ((*(int *)(iVar2 + 0x58) == *(int *)(iVar1 + 0x58) &&
        ((*(int *)(iVar2 + 0x5c) == *(int *)(iVar1 + 0x5c) &&
         (*(int *)(iVar2 + 0x60) == *(int *)(iVar1 + 0x60))))))) {
      iVar2 = DAT_00223024 + iVar3;
      if (param_1 != 0) {
        iVar2 = DAT_00223038;
        DAT_0022303c = DAT_00223024 + iVar3;
      }
      goto LAB_002225d0;
    }
    uVar4 = uVar4 + 1;
    iVar3 = iVar3 + DAT_00223034;
  } while( true );
}




/* 0x002225e4 */
void thunk_FUN_002225e4()
{
  thunk_FUN_002225e4();
  return;
}




/* 0x002225e4 */
undefined4 FUN_002225e4(param_1)
undefined4 * param_1;
{
  *param_1 = 0x2fc;
  return DAT_00223044;
}




/* 0x002225f4 */
undefined4 thunk_FUN_002225f4()
{
  thunk_FUN_002225f4();
  return 0;
}




/* 0x002225f4 */
undefined4 FUN_002225f4()
{
  return 0;
}




/* 0x002225f8 */
void FUN_002225f8()
{
  undefined4 uVar1;
  
  uVar1 = FUN_00222380(0);
  thunk_FUN_08006c40(DAT_0022302c,uVar1,DAT_00223034);
  uVar1 = FUN_00222380(1);
  thunk_FUN_08006b04(DAT_0022302c + DAT_00223034,uVar1);
  DAT_00223038 = DAT_0022302c;
  DAT_0022303c = DAT_0022302c + DAT_00223034;
  if (DAT_00223044 != 0) {
    thunk_FUN_08006b04(DAT_00223034 * 2 + 0x8600190,DAT_00223044,0x2fc);
    DAT_00223044 = DAT_00223034 * 2 + 0x8600190;
  }
  return;
}




/* 0x00222650 */
undefined4 thunk_FUN_00222650()
{
  thunk_FUN_00222650();
  return 0;
}




/* 0x00222650 */
undefined4 FUN_00222650(param_1, param_2)
int * param_1; int param_2;
{
  if ((param_1 != (int *)0x0) && (param_2 == 0x2fc)) {
    DAT_00223044 = param_1;
    if (*param_1 != 0x44445200) {
      thunk_FUN_08006d14(param_1,0x2fc);
    }
    return 1;
  }
  return 0;
}




/* 0x00222680 */
void thunk_FUN_00222680()
{
  thunk_FUN_00222680();
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x00222680 */
undefined4 FUN_00222680()
{
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x00222684 */
void thunk_FUN_00222684(param_1)
undefined4 param_1;
{
  int iVar1;
  int iVar2;
  byte bVar3;
  byte bVar4;
  
  iVar1 = FUN_00222380(0);
  iVar2 = FUN_00222380(1);
  bVar3 = *(int *)(iVar1 + 0x50) != 0;
  if (*(int *)(iVar1 + 0x5c) != 0) {
    bVar3 = bVar3 | 2;
  }
  bVar4 = *(int *)(iVar2 + 0x50) != 0;
  if (*(int *)(iVar2 + 0x5c) != 0) {
    bVar4 = bVar4 | 2;
  }
  DAT_00223048 = 1;
  FUN_00222058();
  _DAT_004ab004 = 0;
  FUN_00222720();
  if (bVar3 != 0) {
    FUN_00220b2c(0,bVar3,param_1);
    FUN_00220a80(0,0,bVar3,0x2205bd);
    FUN_002205ec(0,0,bVar3,param_1);
  }
  if (bVar4 != 0) {
    FUN_00220b2c(0,bVar4,param_1);
    FUN_00220a80(0,0,bVar4,0x2205bd);
    return;
  }
  return;
}




/* 0x00222684 */
void FUN_00222684(param_1)
undefined4 param_1;
{
  int iVar1;
  int iVar2;
  byte bVar3;
  byte bVar4;
  
  iVar1 = FUN_00222380(0);
  iVar2 = FUN_00222380(1);
  bVar3 = *(int *)(iVar1 + 0x50) != 0;
  if (*(int *)(iVar1 + 0x5c) != 0) {
    bVar3 = bVar3 | 2;
  }
  bVar4 = *(int *)(iVar2 + 0x50) != 0;
  if (*(int *)(iVar2 + 0x5c) != 0) {
    bVar4 = bVar4 | 2;
  }
  DAT_00223048 = 1;
  FUN_00222058();
  _DAT_004ab004 = 0;
  FUN_00222720();
  if (bVar3 != 0) {
    FUN_00220b2c(0,bVar3,param_1);
    FUN_00220a80(0,0,bVar3,0x2205bd);
    FUN_002205ec(0,0,bVar3,param_1);
  }
  if (bVar4 != 0) {
    FUN_00220b2c(0,bVar4,param_1);
    FUN_00220a80(0,0,bVar4,0x2205bd);
    return;
  }
  return;
}




/* 0x00222720 */
void FUN_00222720()
{
  int iVar1;
  
  DAT_00223038 = DAT_0022302c;
  iVar1 = *(int *)(DAT_0022302c + 8);
  if (iVar1 != 2) {
    if (iVar1 == 4) {
      iVar1 = 0xa8;
      goto LAB_00222736;
    }
    if (iVar1 != 5) {
      iVar1 = 0;
      goto LAB_00222736;
    }
  }
  iVar1 = 0xb8;
LAB_00222736:
  DAT_0022303c = DAT_0022302c + iVar1;
  return;
}




/* 0x00222748 */
void FUN_00222748(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  int iVar1;
  int iVar2;
  
  if (param_2 != 0) {
    for (iVar1 = 0; iVar2 = *(int *)(param_2 + iVar1 * 8), iVar2 != 0; iVar1 = iVar1 + 1) {
      *(undefined4 *)(iVar2 + param_1) = *(undefined4 *)(param_2 + iVar1 * 8 + 4);
    }
  }
  if (param_3 != 0) {
    for (iVar1 = 0; iVar2 = *(int *)(param_3 + iVar1 * 8), iVar2 != 0; iVar1 = iVar1 + 1) {
      *(undefined4 *)(iVar2 + param_1) = *(undefined4 *)(param_3 + iVar1 * 8 + 4);
    }
  }
  return;
}




/* 0x00222780 */
undefined4 thunk_FUN_00222780()
{
  thunk_FUN_00222780();
  return 0;
}




/* 0x00222780 */
bool FUN_00222780(param_1, param_2)
int * param_1; int param_2;
{
  int iVar1;
  
  if (param_1 == (int *)0x0) {
    return false;
  }
  if (param_2 == 0) {
    return false;
  }
  if (*param_1 != 1) {
    return false;
  }
  if (param_1[1] != 0x44445200) {
    return false;
  }
  iVar1 = param_1[8];
  if (iVar1 != 2) {
    if (iVar1 == 4) {
      DAT_00223034 = 0xa8;
      goto LAB_002227c0;
    }
    if (iVar1 != 5) {
      DAT_00223024 = param_1 + 6;
      DAT_00223030 = param_1[3];
      DAT_00223034 = 0;
      return false;
    }
  }
  DAT_00223034 = 0xb8;
LAB_002227c0:
  if (param_1[4] == DAT_00223034) {
    DAT_00223040 = param_1[5];
  }
  DAT_00223024 = param_1 + 6;
  DAT_00223030 = param_1[3];
  return param_1[4] == DAT_00223034;
}




