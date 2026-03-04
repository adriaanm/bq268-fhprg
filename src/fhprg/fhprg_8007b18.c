/* Auto-generated: fhprg_8007b18.c */
/* Functions: 514 */
#include "globals.h"

/* 0x08007b18 */
void FUN_08007b18(UNRECOVERED_JUMPTABLE)
code * UNRECOVERED_JUMPTABLE;
{
                    /* WARNING: Could not recover jumptable at 0x08007b18. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}




/* 0x08007b30 */
undefined4 FUN_08007b30()
{
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  coproc_moveto_Invalidate_unified_TLB_unlocked(0);
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  return 0;
}




/* 0x08007bec */
void FUN_08007bec()
{
  DataSynchronizationBarrier(0xf);
  return;
}




/* 0x08007c00 */
void FUN_08007c00()
{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 in_cr0 = 0;
  undefined4 in_cr7 = 0;
  undefined4 in_cr14 = 0;
  
  DataSynchronizationBarrier(0xf);
  uVar2 = coprocessor_movefromRt(0xf,1,1,in_cr0,in_cr0);
  if ((uVar2 & 0x7000000) != 0) {
    uVar7 = 0;
    do {
      if (1 < (uVar2 >> (uVar7 + (uVar7 >> 1) & 0xff) & 7)) {
        coprocessor_moveto(0xf,2,0,uVar7,in_cr0,in_cr0);
        InstructionSynchronizationBarrier(0xf);
        uVar3 = coprocessor_movefromRt(0xf,1,0,in_cr0,in_cr0);
        uVar4 = uVar3 >> 3 & 0x3ff;
        uVar6 = uVar4;
        uVar5 = uVar3 >> 0xd & 0x7fff;
        do {
          do {
            coprocessor_moveto(0xf,0,2,uVar7 | uVar6 << LZCOUNT(uVar4) | uVar5 << (uVar3 & 7) + 4,
                               in_cr7,in_cr14);
            bVar1 = 0 < (int)uVar6;
            uVar6 = uVar6 - 1;
          } while (bVar1);
          bVar1 = 0 < (int)uVar5;
          uVar6 = uVar4;
          uVar5 = uVar5 - 1;
        } while (bVar1);
      }
      uVar7 = uVar7 + 2;
    } while ((int)uVar7 < (int)((uVar2 & 0x7000000) >> 0x17));
  }
  coprocessor_moveto(0xf,2,0,0,in_cr0,in_cr0);
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  return;
}




/* 0x08007de0 */
undefined8 FUN_08007de0(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  FUN_08007c00();
  coproc_moveto_Invalidate_Entire_Instruction(0);
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  return CONCAT44(param_2,param_1);
}




/* 0x08007e9c */
undefined8 FUN_08007e9c(param_1, param_2)
uint param_1; undefined4 param_2;
{
  uint uVar1;
  
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  uVar1 = coproc_movefrom_Translation_table_base_0();
  uVar1 = uVar1 & 0x7f | param_1;
  coproc_moveto_Translation_table_base_0(uVar1);
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  coproc_moveto_Invalidate_unified_TLB_unlocked(uVar1);
  coproc_moveto_Instruction_cache(uVar1,6);
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  return CONCAT44(param_2,param_1);
}




/* 0x08007edc */
undefined4 thunk_FUN_08007edc()
{
  FUN_08007edc();
  return 0;
}




/* 0x08007edc */
uint FUN_08007edc()
{
  uint uVar1;
  
  uVar1 = coproc_movefrom_Translation_table_base_0();
  return uVar1 & 0xffffc000;
}




/* 0x08007ef0 */
void FUN_08007ef0(param_1)
undefined4 param_1;
{
  coproc_moveto_Domain_Access_Control(param_1);
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  return;
}




/* 0x08007f08 */
void FUN_08007f08(param_1, param_2, param_3)
uint * param_1; uint param_2; uint param_3;
{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  
  uVar3 = param_2 & 0xff | (param_2 & 0xff) << 8;
  uVar3 = uVar3 | uVar3 << 0x10;
  uVar4 = (uint)param_1 & 3;
  if (uVar4 == 0) {
    if (param_3 < 4) goto LAB_08007f98;
  }
  else {
    puVar1 = (uint *)((int)param_1 - uVar4);
    iVar2 = param_3 + uVar4;
    param_3 = iVar2 - 4;
    uVar4 = -1 << (uVar4 << 3);
    if ((int)param_3 < 0) {
      uVar4 = (uVar4 << (param_3 * -8 & 0xff)) >> (param_3 * -8 & 0xff);
    }
    param_1 = puVar1 + 1;
    *puVar1 = *puVar1 & ~uVar4 | uVar3 & uVar4;
    if (param_3 == 0 || iVar2 < 4) {
      return;
    }
  }
  bVar5 = 0x1f < param_3;
  param_3 = param_3 - 0x20;
  do {
    if (bVar5) {
      *param_1 = uVar3;
      param_1[1] = uVar3;
      param_1[2] = uVar3;
      param_1[3] = uVar3;
      param_1[4] = uVar3;
      param_1[5] = uVar3;
      param_1[6] = uVar3;
      param_1[7] = uVar3;
      param_1 = param_1 + 8;
      bVar5 = 0x1f < param_3;
      param_3 = param_3 - 0x20;
    }
    if (bVar5) {
      *param_1 = uVar3;
      param_1[1] = uVar3;
      param_1[2] = uVar3;
      param_1[3] = uVar3;
      param_1[4] = uVar3;
      param_1[5] = uVar3;
      param_1[6] = uVar3;
      param_1[7] = uVar3;
      param_1 = param_1 + 8;
      bVar5 = 0x1f < param_3;
      param_3 = param_3 - 0x20;
    }
  } while (bVar5);
  if ((bool)((byte)(param_3 >> 4) & 1)) {
    *param_1 = uVar3;
    param_1[1] = uVar3;
    param_1[2] = uVar3;
    param_1[3] = uVar3;
    param_1 = param_1 + 4;
  }
  if ((int)(param_3 << 0x1c) < 0) {
    *param_1 = uVar3;
    param_1[1] = uVar3;
    param_1 = param_1 + 2;
  }
  if ((bool)((byte)((param_3 << 0x1c) >> 0x1e) & 1)) {
    *param_1 = uVar3;
    param_1 = param_1 + 1;
  }
  if ((param_3 & 3) == 0) {
    return;
  }
  param_3 = param_3 & 3;
LAB_08007f98:
  uVar4 = -1 << ((param_3 & 0x1f) << 3);
  *param_1 = *param_1 & uVar4 | uVar3 & ~uVar4;
  return;
}




/* 0x08008004 */
undefined8 FUN_08008004(param_1, param_2)
uint param_1; uint param_2;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  uVar4 = param_1 << 1;
  uVar3 = param_2 << 0xb;
  uVar2 = param_1 << 0xb | param_2 >> 0x15;
  uVar1 = uVar4 >> 0x14;
  if (uVar4 != 0 || param_2 != 0) {
    uVar1 = uVar1 + 0x7800;
  }
  uVar1 = (uint)((param_1 & 0x80000000) != 0) << 0x1f | uVar1 >> 1;
  if (uVar4 != 0 || param_2 != 0) {
    uVar2 = uVar2 | 0x80000000;
  }
  if ((int)uVar4 >> 0x15 != 0) {
    if ((int)uVar4 >> 0x15 == -1) {
      uVar1 = uVar1 | 0x40000000;
    }
    return CONCAT44(uVar2,uVar1);
  }
  if ((uVar2 & 0x80000000) == 0) {
    return CONCAT44(uVar2,uVar1);
  }
  uVar2 = uVar2 & 0x7fffffff;
  if (uVar2 == 0) {
    if (uVar3 >> 0x10 == 0) {
      uVar3 = param_2 << 0x1b;
      iVar5 = 0x10;
    }
    else {
      iVar5 = 0;
    }
    if (uVar3 >> 0x18 == 0) {
      uVar3 = uVar3 << 8;
      iVar5 = iVar5 + 8;
    }
    if (uVar3 >> 0x1c == 0) {
      uVar3 = uVar3 << 4;
      iVar5 = iVar5 + 4;
    }
    if (uVar3 >> 0x1e == 0) {
      uVar3 = uVar3 << 2;
      iVar5 = iVar5 + 2;
    }
    if (-1 < (int)uVar3) {
      uVar3 = uVar3 << 1;
      iVar5 = iVar5 + 1;
    }
    return CONCAT44(uVar3,(uVar1 - 0x1f) - iVar5);
  }
  if (uVar2 >> 0x10 == 0) {
    uVar2 = uVar2 << 0x10;
    iVar5 = 0x10;
  }
  else {
    iVar5 = 0;
  }
  if (uVar2 >> 0x18 == 0) {
    uVar2 = uVar2 << 8;
    iVar5 = iVar5 + 8;
  }
  if (uVar2 >> 0x1c == 0) {
    uVar2 = uVar2 << 4;
    iVar5 = iVar5 + 4;
  }
  if (uVar2 >> 0x1e == 0) {
    uVar2 = uVar2 << 2;
    iVar5 = iVar5 + 2;
  }
  if (-1 < (int)uVar2) {
    uVar2 = uVar2 << 1;
    iVar5 = iVar5 + 1;
  }
  return CONCAT44(uVar2 | uVar3 >> (0x20U - iVar5 & 0xff),(uVar1 - iVar5) + 1);
}




/* 0x080080e8 */
ulonglong FUN_080080e8(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; uint param_3; uint param_4;
{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint unaff_r4 = 0;
  uint unaff_r5 = 0;
  uint uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  bool bVar23;
  bool bVar24;
  bool bVar25;
  bool bVar26;
  bool bVar27;
  
  param_1 = param_1 ^ param_4;
  uVar2 = param_1 & 0x80000000;
  uVar17 = unaff_r5 >> 0x10;
  uVar8 = unaff_r4 >> 0x10;
  uVar22 = unaff_r5 & ~(uVar17 << 0x10);
  uVar16 = unaff_r4 & ~(uVar8 << 0x10);
  uVar10 = (uint)*(byte *)((unaff_r4 >> 0x18) + 0x8008320);
  uVar3 = (uint)((param_2 & 1) != 0) << 0x1f | param_3 >> 1;
  iVar11 = ((0x800000 - (uVar8 * uVar10 + uVar10)) * uVar10 >> 0x13) + 2;
  uVar18 = 0x20000000 - ((unaff_r4 >> 0xd) * iVar11 + iVar11);
  uVar10 = uVar18 >> 0x10;
  uVar10 = uVar10 * iVar11 + ((uVar18 & ~(uVar10 << 0x10)) * iVar11 >> 0x10) >> 6;
  if ((param_3 & 1) == 0) {
    uVar2 = 0;
  }
  if ((param_3 & 1) != 0) {
    uVar2 = 0x80000000;
  }
  uVar19 = uVar10 * (param_2 >> 0x10) >> 0x10;
  uVar4 = uVar3 - uVar19 * uVar17;
  uVar18 = uVar19 * uVar22;
  bVar23 = uVar18 * 0x10000 <= uVar2;
  uVar2 = uVar2 + uVar18 * -0x10000;
  uVar18 = uVar18 >> 0x10;
  bVar1 = uVar4 - uVar18 < (uint)bVar23;
  bVar24 = uVar18 < uVar4 || bVar1;
  uVar5 = (uVar4 - uVar18) - (uint)!bVar23;
  uVar12 = uVar19 * uVar16;
  if (uVar18 < uVar4 || bVar1) {
    bVar24 = uVar12 * 0x10000 <= uVar5;
  }
  uVar5 = uVar5 + uVar12 * -0x10000;
  uVar18 = ((((param_2 >> 1) - uVar8 * uVar19) - (uint)(uVar3 < uVar19 * uVar17)) - (uVar12 >> 0x10)
           ) - (uint)!bVar24;
  uVar20 = uVar10 * (uVar18 >> 2) >> 0x10;
  uVar3 = uVar20 * uVar17;
  bVar23 = uVar3 * 0x80000 <= uVar2;
  uVar2 = uVar2 + uVar3 * -0x80000;
  uVar3 = uVar3 >> 0xd;
  bVar1 = uVar5 - uVar3 < (uint)bVar23;
  bVar24 = uVar3 < uVar5 || bVar1;
  uVar4 = (uVar5 - uVar3) - (uint)!bVar23;
  uVar12 = uVar8 * uVar20;
  if (uVar3 < uVar5 || bVar1) {
    bVar24 = uVar12 * 0x80000 <= uVar4;
  }
  uVar4 = uVar4 + uVar12 * -0x80000;
  uVar5 = uVar20 * uVar22;
  bVar25 = uVar5 * 8 <= uVar2;
  uVar3 = uVar5 >> 0x1d;
  bVar1 = uVar4 - uVar3 < (uint)bVar25;
  bVar23 = uVar3 < uVar4 || bVar1;
  uVar6 = (uVar4 - uVar3) - (uint)!bVar25;
  uVar13 = uVar20 * uVar16;
  if (uVar3 < uVar4 || bVar1) {
    bVar23 = uVar13 * 8 <= uVar6;
  }
  uVar6 = uVar6 + uVar13 * -8;
  uVar3 = ((((uVar18 - (uVar12 >> 0xd)) - (uint)!bVar24) - (uVar13 >> 0x1d)) - (uint)!bVar23) *
          0x4000000 | uVar6 >> 6;
  uVar13 = uVar10 * (uVar3 >> 0xf);
  uVar18 = uVar6 * 0x4000000 | uVar2 + uVar5 * -8 >> 6;
  uVar5 = uVar5 * -0x20000000;
  uVar21 = uVar13 >> 0x10;
  uVar4 = uVar18 - uVar21 * uVar17;
  uVar2 = uVar21 * uVar22;
  bVar23 = uVar2 * 0x10000 <= uVar5;
  uVar5 = uVar5 + uVar2 * -0x10000;
  uVar2 = uVar2 >> 0x10;
  bVar1 = uVar4 - uVar2 < (uint)bVar23;
  bVar24 = uVar2 < uVar4 || bVar1;
  uVar12 = (uVar4 - uVar2) - (uint)!bVar23;
  uVar6 = uVar21 * uVar16;
  if (uVar2 < uVar4 || bVar1) {
    bVar24 = uVar6 * 0x10000 <= uVar12;
  }
  uVar12 = uVar12 + uVar6 * -0x10000;
  uVar3 = (((uVar3 - uVar8 * uVar21) - (uint)(uVar18 < uVar21 * uVar17)) - (uVar6 >> 0x10)) -
          (uint)!bVar24;
  uVar6 = uVar10 * (uVar3 >> 2) >> 0x10;
  uVar2 = uVar6 * uVar17;
  bVar23 = uVar2 * 0x80000 <= uVar5;
  uVar5 = uVar5 + uVar2 * -0x80000;
  uVar2 = uVar2 >> 0xd;
  bVar1 = uVar12 - uVar2 < (uint)bVar23;
  bVar24 = uVar2 < uVar12 || bVar1;
  uVar18 = (uVar12 - uVar2) - (uint)!bVar23;
  uVar4 = uVar8 * uVar6;
  if (uVar2 < uVar12 || bVar1) {
    bVar24 = uVar4 * 0x80000 <= uVar18;
  }
  uVar18 = uVar18 + uVar4 * -0x80000;
  uVar12 = uVar6 * uVar22;
  bVar25 = uVar12 * 8 <= uVar5;
  uVar2 = uVar12 >> 0x1d;
  bVar1 = uVar18 - uVar2 < (uint)bVar25;
  bVar23 = uVar2 < uVar18 || bVar1;
  uVar7 = (uVar18 - uVar2) - (uint)!bVar25;
  uVar14 = uVar6 * uVar16;
  if (uVar2 < uVar18 || bVar1) {
    bVar23 = uVar14 * 8 <= uVar7;
  }
  uVar7 = uVar7 + uVar14 * -8;
  uVar9 = uVar21 * 0x400000 + uVar6 * 0x200;
  uVar18 = ((((uVar3 - (uVar4 >> 0xd)) - (uint)!bVar24) - (uVar14 >> 0x1d)) - (uint)!bVar23) *
           0x4000000 | uVar7 >> 6;
  uVar4 = uVar7 * 0x4000000 | uVar5 + uVar12 * -8 >> 6;
  uVar10 = uVar10 * (uVar18 >> 0xf);
  uVar12 = uVar12 * -0x20000000;
  uVar14 = uVar10 >> 0x10;
  uVar5 = uVar4 - uVar14 * uVar17;
  uVar3 = uVar14 * uVar22;
  bVar23 = uVar3 * 0x10000 <= uVar12;
  uVar2 = uVar3 >> 0x10;
  bVar1 = uVar5 - uVar2 < (uint)bVar23;
  bVar24 = uVar2 < uVar5 || bVar1;
  uVar7 = (uVar5 - uVar2) - (uint)!bVar23;
  uVar15 = uVar14 * uVar16;
  if (uVar2 < uVar5 || bVar1) {
    bVar24 = uVar15 * 0x10000 <= uVar7;
  }
  uVar7 = uVar7 + uVar15 * -0x10000;
  uVar10 = uVar10 >> 0x14;
  uVar5 = uVar9 + uVar10;
  uVar4 = ((((uVar18 - uVar8 * uVar14) - (uint)(uVar4 < uVar14 * uVar17)) - (uVar15 >> 0x10)) -
          (uint)!bVar24) * 0x4000 | uVar7 >> 0x12;
  uVar2 = uVar7 * 0x4000 | uVar12 + uVar3 * -0x10000 >> 0x12;
  uVar18 = uVar3 * -0x40000000;
  uVar14 = uVar14 << 0x1c;
  uVar16 = uVar16 | uVar8 << 0x10;
  uVar22 = uVar22 | uVar17 << 0x10;
  bVar1 = uVar4 - uVar16 < (uint)(uVar22 <= uVar2);
  uVar8 = uVar4;
  if (uVar16 < uVar4 || bVar1) {
    uVar8 = (uVar4 - uVar16) - (uint)(uVar22 > uVar2);
    uVar2 = uVar2 - uVar22;
  }
  uVar3 = uVar3 * -0x80000000;
  bVar23 = CARRY4(uVar2,uVar2) || CARRY4(uVar2 * 2,(uint)CARRY4(uVar18,uVar18));
  uVar2 = uVar2 * 2 + (uint)CARRY4(uVar18,uVar18);
  bVar24 = CARRY4(uVar8 * 2,(uint)bVar23);
  bVar25 = CARRY4(uVar8,uVar8) || bVar24;
  uVar17 = uVar8 * 2 + (uint)bVar23;
  bVar23 = bVar25 < (uVar16 < uVar17 || uVar17 - uVar16 < (uint)(uVar22 <= uVar2));
  if ((CARRY4(uVar8,uVar8) || bVar24) || bVar23) {
    uVar17 = (uVar17 - uVar16) - (uint)(uVar22 > uVar2);
    uVar2 = uVar2 - uVar22;
  }
  bVar26 = CARRY4(uVar2,uVar2) || CARRY4(uVar2 * 2,(uint)CARRY4(uVar3,uVar3));
  uVar2 = uVar2 * 2 + (uint)CARRY4(uVar3,uVar3);
  bVar24 = CARRY4(uVar17 * 2,(uint)bVar26);
  bVar27 = CARRY4(uVar17,uVar17) || bVar24;
  uVar3 = uVar17 * 2 + (uint)bVar26;
  bVar26 = bVar27 < (uVar16 < uVar3 || uVar3 - uVar16 < (uint)(uVar22 <= uVar2));
  if ((CARRY4(uVar17,uVar17) || bVar24) || bVar26) {
    uVar3 = (uVar3 - uVar16) - (uint)(uVar22 > uVar2);
    uVar2 = uVar2 - uVar22;
  }
  if (uVar3 != 0 || uVar2 != 0) {
    uVar14 = uVar14 | 1;
  }
  uVar2 = (((uint)(uVar16 < uVar4 || bVar1) * 2 + (uint)(bVar25 || bVar23)) * 2 +
          (uint)(bVar27 || bVar26)) * 0x10000000;
  uVar3 = uVar5 + CARRY4(uVar14,uVar2);
  iVar11 = uVar19 * 0x10000 + uVar20 * 8 + (uVar13 >> 0x1a) +
           (uint)CARRY4(uVar21 * 0x400000,uVar6 * 0x200) + (uint)CARRY4(uVar9,uVar10) +
           (uint)CARRY4(uVar5,(uint)CARRY4(uVar14,uVar2));
  if (-1 < iVar11) {
    return CONCAT44(iVar11 * 2 +
                    (uint)(CARRY4(uVar3,uVar3) ||
                          CARRY4(uVar3 * 2,(uint)CARRY4(uVar14 + uVar2,uVar14 + uVar2))),param_1) &
           0xffffffff80000000;
  }
  return CONCAT44(iVar11,param_1) & 0xffffffff80000000;
}




/* 0x08008420 */
undefined8 FUN_08008420(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; uint param_3; uint param_4;
{
  uint uVar1;
  uint uVar2;
  uint unaff_r6 = 0;
  int unaff_r11 = 0;
  bool bVar3;
  
  if ((int)param_4 < 0) {
    unaff_r6 = (unaff_r6 | unaff_r6 << 0x10) >> 0x10;
    if ((int)param_4 < -0x3f) {
      unaff_r6 = (unaff_r6 | param_3 | (unaff_r6 | param_3) << 0x10) >> 0x10 | param_2;
      if ((int)param_4 < -0x40) {
        unaff_r6 = (unaff_r6 | unaff_r6 << 0x10) >> 0x10;
      }
      param_4 = 0;
      param_3 = 0;
      param_2 = 0;
    }
    else {
      uVar2 = param_4;
      if ((int)param_4 < -0x1f) {
        unaff_r6 = unaff_r6 | param_3;
        uVar2 = param_4 + 0x20;
        param_2 = 0;
        param_3 = param_2;
      }
      uVar1 = -uVar2;
      param_4 = 0;
      if (uVar1 != 0) {
        unaff_r6 = (unaff_r6 | unaff_r6 << 0x10) >> 0x10 | param_3 << (uVar2 + 0x20 & 0xff);
        uVar2 = param_2 << (uVar2 + 0x20 & 0xff);
        param_2 = param_2 >> (uVar1 & 0xff);
        param_4 = 0;
        param_3 = param_3 >> (uVar1 & 0xff) | uVar2;
      }
    }
  }
  if (((unaff_r6 & 0x7fffffff) != 0) || ((unaff_r6 & 0x80000000) != 0)) {
    bVar3 = unaff_r11 != -1 && 0xfffffffe < param_3;
    if (unaff_r11 != -1 && 0xfffffffe < param_3) {
      bVar3 = 0xfffffffe < param_2;
      param_2 = param_2 + 1;
    }
    if (bVar3 != false) {
      param_2 = 0x80000000;
    }
    param_4 = param_4 + bVar3;
  }
  return CONCAT44(param_2,param_4 | param_1 & 0x80000000);
}




/* 0x080084e6 */
undefined4 FUN_080084e6(param_1, param_2)
int * param_1; int * param_2;
{
  if ((param_1[1] & ~(*param_1 << 1)) < 0 && (param_2[1] & ~(*param_2 << 1)) < 0) {
    FUN_080080e8(*param_1,param_1[1],param_1[2]);
    FUN_08008420();
  }
  return 0;
}




/* 0x0800850e */
undefined4 FUN_0800850e(param_1, param_2)
uint * param_1; uint * param_2;
{
  if ((*param_1 & 0x40000000) == 0 && (*param_2 & 0x40000000) == 0) {
    FUN_08008536(*param_1,param_1[1],param_1[2]);
    FUN_08008420();
  }
  return 0;
}




/* 0x08008536 */
ulonglong FUN_08008536(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; uint param_3; uint param_4;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint unaff_r4 = 0;
  uint unaff_r5 = 0;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  bool bVar18;
  bool bVar19;
  
  param_1 = param_1 ^ param_4;
  if (param_3 == 0) {
    if (unaff_r5 == 0) {
      uVar5 = unaff_r4 >> 0x10;
      uVar6 = param_2 >> 0x10;
      uVar14 = unaff_r4 & ~(uVar5 << 0x10);
      param_2 = param_2 & ~(uVar6 << 0x10);
      uVar7 = uVar14 * uVar6;
      uVar14 = param_2 * uVar14;
      param_2 = uVar5 * param_2;
      uVar3 = uVar7 * 0x10000;
      uVar1 = uVar14 + uVar3;
      uVar2 = param_2 * 0x10000;
      uVar4 = uVar1 + uVar2;
      iVar8 = uVar5 * uVar6 + (uVar7 >> 0x10) + (uint)CARRY4(uVar14,uVar3) +
              (param_2 >> 0x10) + (uint)CARRY4(uVar1,uVar2);
      if (-1 < iVar8) {
        return CONCAT44(iVar8 * 2 + (uint)CARRY4(uVar4,uVar4),param_1) & 0xffffffff80000000;
      }
      return CONCAT44(iVar8,param_1) & 0xffffffff80000000;
    }
    uVar4 = param_2 >> 0x10;
    uVar12 = unaff_r4 >> 0x10;
    param_2 = param_2 & ~(uVar4 << 0x10);
    uVar15 = unaff_r4 & ~(uVar12 << 0x10);
    uVar5 = uVar15 * param_2;
    uVar15 = uVar4 * uVar15;
    uVar3 = param_2 * uVar12 * 0x10000;
    uVar6 = uVar5 + uVar3;
    uVar13 = unaff_r5 >> 0x10;
    uVar2 = uVar15 * 0x10000;
    uVar7 = uVar6 + uVar2;
    uVar16 = unaff_r5 & ~(uVar13 << 0x10);
    uVar9 = uVar16 * param_2;
    uVar16 = uVar4 * uVar16;
    uVar14 = param_2 * uVar13 * 0x10000;
    uVar10 = uVar9 + uVar14;
    uVar1 = uVar16 * 0x10000;
    uVar11 = uVar10 + uVar1;
    uVar14 = uVar4 * uVar13 + (param_2 * uVar13 >> 0x10) + (uint)CARRY4(uVar9,uVar14) +
             (uVar16 >> 0x10) + (uint)CARRY4(uVar10,uVar1);
    uVar1 = uVar14 + uVar7;
    iVar8 = uVar4 * uVar12 + (param_2 * uVar12 >> 0x10) + (uint)CARRY4(uVar5,uVar3) +
            (uVar15 >> 0x10) + (uint)CARRY4(uVar6,uVar2) + (uint)CARRY4(uVar14,uVar7);
    if (-1 < iVar8) {
      return CONCAT44(iVar8 * 2 +
                      (uint)(CARRY4(uVar1,uVar1) || CARRY4(uVar1 * 2,(uint)CARRY4(uVar11,uVar11))),
                      param_1) & 0xffffffff80000000;
    }
    return CONCAT44(iVar8,param_1) & 0xffffffff80000000;
  }
  if (unaff_r5 == 0) {
    uVar7 = unaff_r4 >> 0x10;
    uVar13 = param_2 >> 0x10;
    uVar9 = unaff_r4 & ~(uVar7 << 0x10);
    param_2 = param_2 & ~(uVar13 << 0x10);
    uVar4 = param_2 * uVar9;
    param_2 = uVar7 * param_2;
    uVar3 = uVar9 * uVar13 * 0x10000;
    uVar5 = uVar4 + uVar3;
    uVar15 = param_3 >> 0x10;
    uVar2 = param_2 * 0x10000;
    uVar6 = uVar5 + uVar2;
    param_3 = param_3 & ~(uVar15 << 0x10);
    uVar10 = param_3 * uVar9;
    param_3 = uVar7 * param_3;
    uVar14 = uVar9 * uVar15 * 0x10000;
    uVar11 = uVar10 + uVar14;
    uVar1 = param_3 * 0x10000;
    uVar12 = uVar11 + uVar1;
    uVar1 = uVar7 * uVar15 + (uVar9 * uVar15 >> 0x10) + (uint)CARRY4(uVar10,uVar14) +
            (param_3 >> 0x10) + (uint)CARRY4(uVar11,uVar1);
    uVar14 = uVar1 + uVar6;
    iVar8 = uVar7 * uVar13 + (uVar9 * uVar13 >> 0x10) + (uint)CARRY4(uVar4,uVar3) +
            (param_2 >> 0x10) + (uint)CARRY4(uVar5,uVar2) + (uint)CARRY4(uVar1,uVar6);
    if (-1 < iVar8) {
      return CONCAT44(iVar8 * 2 +
                      (uint)(CARRY4(uVar14,uVar14) || CARRY4(uVar14 * 2,(uint)CARRY4(uVar12,uVar12))
                            ),param_1) & 0xffffffff80000000;
    }
    return CONCAT44(iVar8,param_1) & 0xffffffff80000000;
  }
  uVar1 = param_2 >> 0x10;
  uVar4 = unaff_r4 >> 0x10;
  uVar11 = param_2 & ~(uVar1 << 0x10);
  uVar9 = unaff_r4 & ~(uVar4 << 0x10);
  uVar5 = uVar11 * uVar4;
  uVar11 = uVar9 * uVar11;
  uVar9 = uVar1 * uVar9;
  uVar3 = uVar5 * 0x10000;
  uVar12 = uVar11 + uVar3;
  uVar15 = param_3 >> 0x10;
  uVar2 = uVar9 * 0x10000;
  uVar13 = uVar12 + uVar2;
  uVar6 = unaff_r5 >> 0x10;
  uVar16 = param_3 & ~(uVar15 << 0x10);
  uVar10 = unaff_r5 & ~(uVar6 << 0x10);
  uVar7 = uVar16 * uVar6;
  uVar16 = uVar10 * uVar16;
  uVar10 = uVar15 * uVar10;
  uVar14 = uVar7 * 0x10000;
  uVar17 = uVar16 + uVar14;
  uVar7 = uVar15 * uVar6 + (uVar7 >> 0x10) + (uint)CARRY4(uVar16,uVar14);
  iVar8 = 0;
  uVar14 = uVar10 * 0x10000;
  uVar15 = uVar17 + uVar14;
  uVar6 = uVar7 + (uVar10 >> 0x10) + (uint)CARRY4(uVar17,uVar14);
  uVar14 = uVar13 + uVar6;
  uVar2 = uVar1 * uVar4 + (uVar5 >> 0x10) + (uint)CARRY4(uVar11,uVar3) +
          (uVar9 >> 0x10) + (uint)CARRY4(uVar12,uVar2) + (uint)CARRY4(uVar13,uVar6);
  uVar4 = uVar14 + uVar15;
  uVar1 = uVar14 + uVar2 + CARRY4(uVar14,uVar15);
  bVar19 = param_3 <= param_2;
  param_2 = param_2 - param_3;
  bVar18 = param_2 == 0;
  uVar3 = 0;
  if (!bVar19) {
    uVar3 = 0xffffffff;
    iVar8 = unaff_r4 - unaff_r5;
  }
  if (!bVar18) {
    bVar19 = unaff_r4 <= unaff_r5;
    uVar7 = unaff_r5 - unaff_r4;
    bVar18 = uVar7 == 0;
  }
  if (bVar18) {
    uVar3 = 0;
  }
  if (!bVar19) {
    uVar3 = ~uVar3;
    iVar8 = iVar8 - param_2;
  }
  uVar9 = param_2 >> 0x10;
  param_2 = param_2 & ~(uVar9 << 0x10);
  uVar12 = uVar7 >> 0x10;
  uVar7 = uVar7 & ~(uVar12 << 0x10);
  uVar13 = param_2 * uVar12;
  param_2 = uVar7 * param_2;
  uVar7 = uVar9 * uVar7;
  uVar5 = uVar13 * 0x10000;
  uVar10 = param_2 + uVar5;
  uVar6 = uVar7 * 0x10000;
  uVar11 = uVar10 + uVar6;
  uVar5 = uVar9 * uVar12 + iVar8 + (uVar13 >> 0x10) + (uint)CARRY4(param_2,uVar5) +
          (uVar7 >> 0x10) + (uint)CARRY4(uVar10,uVar6);
  uVar6 = uVar1 + uVar5 + CARRY4(uVar4,uVar11);
  iVar8 = uVar3 + uVar2 + (CARRY4(uVar14,uVar2) ||
                          CARRY4(uVar14 + uVar2,(uint)CARRY4(uVar14,uVar15))) +
          (uint)(CARRY4(uVar1,uVar5) || CARRY4(uVar1 + uVar5,(uint)CARRY4(uVar4,uVar11)));
  uVar3 = uVar4 + uVar11 | (uVar15 | uVar15 * 4) >> 2;
  if (-1 < iVar8) {
    return CONCAT44(iVar8 * 2 +
                    (uint)(CARRY4(uVar6,uVar6) || CARRY4(uVar6 * 2,(uint)CARRY4(uVar3,uVar3))),
                    param_1) & 0xffffffff80000000;
  }
  return CONCAT44(iVar8,param_1) & 0xffffffff80000000;
}



void processEntry_entry(undefined4 param_1)

{
  undefined8 *puVar1;
  undefined4 extraout_r2;
  undefined4 extraout_r3;
  undefined4 in_r4 = 0;
  undefined4 in_r6 = 0;
  undefined4 in_r8 = 0;
  undefined4 in_r9 = 0;
  undefined4 in_r10 = 0;
  undefined4 in_r11 = 0;
  undefined4 extraout_r12;
  char in_NG = 0;
  char in_ZR = 0;
  char in_CY = 0;
  char in_OV = 0;
  byte in_Q = 0;
  undefined4 uVar2;
  undefined4 in_cr0 = 0;
  undefined4 in_cr12 = 0;
  undefined8 uVar3;
  
  uVar2 = 0;
  coprocessor_moveto(0xf,0,0,0x8006000,in_cr12,in_cr0);
  FUN_08031f88(param_1);
  uVar3 = FUN_0800897c();
  puVar1 = DAT_0804c084;
  DAT_0804bff8 = param_1;
  DAT_0804bffc = in_r6;
  *(uint*)DAT_0804c084 = uVar3;
  *(undefined4 *)(puVar1 + 1) = extraout_r2;
  *(undefined4 *)((int)puVar1 + 0xc) = extraout_r3;
  *(undefined4 *)(puVar1 + 2) = in_r4;
  *(undefined4 *)((int)puVar1 + 0x14) = 0x8031f89;
  *(undefined4 *)(puVar1 + 4) = in_r8;
  *(undefined4 *)((int)puVar1 + 0x24) = in_r9;
  *(undefined4 *)(puVar1 + 5) = in_r10;
  *(undefined4 *)((int)puVar1 + 0x2c) = in_r11;
  *(undefined4 *)(puVar1 + 6) = extraout_r12;
  *(code **)(puVar1 + 7) = FUN_080087d4;
  *(undefined4 **)((int)puVar1 + 0x34) = &DAT_0804bff8;
  *(undefined4 *)((int)puVar1 + 0x3c) = uVar2;
  *(code **)(puVar1 + 8) = FUN_080087d4;
  *(undefined4 **)(puVar1 + 9) = &DAT_0804bff8;
  *(code **)((int)puVar1 + 0x4c) = FUN_080087d4;
  *(undefined4 **)(puVar1 + 10) = &DAT_0804bff8;
  *(code **)((int)puVar1 + 0x54) = FUN_080087d4;
  *(undefined4 *)(puVar1 + 0xb) = uVar2;
  *(undefined4 **)((int)puVar1 + 0x5c) = &DAT_0804bff8;
  *(code **)(puVar1 + 0xc) = FUN_080087d4;
  *(undefined4 *)((int)puVar1 + 100) = uVar2;
  *(undefined4 **)(puVar1 + 0xd) = &DAT_0804bff8;
  *(code **)((int)puVar1 + 0x6c) = FUN_080087d4;
  *(undefined4 *)(puVar1 + 0xe) = uVar2;
  *(undefined4 *)((int)puVar1 + 0x74) = in_r8;
  *(undefined4 *)(puVar1 + 0xf) = in_r9;
  *(undefined4 *)((int)puVar1 + 0x7c) = in_r10;
  *(undefined4 *)(puVar1 + 0x10) = in_r11;
  *(undefined4 *)((int)puVar1 + 0x84) = extraout_r12;
  *(undefined4 **)(puVar1 + 0x11) = &DAT_0804bff8;
  *(code **)((int)puVar1 + 0x8c) = FUN_080087d4;
  *(undefined4 *)(puVar1 + 0x12) = uVar2;
  *(uint *)((int)puVar1 + 0x44) =
       (uint)(byte)(in_NG << 4 | in_ZR << 3 | in_CY << 2 | in_OV << 1 | in_Q) << 0x1b;
  *(undefined4 *)((int)puVar1 + 0x1c) = DAT_0804bff8;
  *(undefined4 *)(puVar1 + 3) = DAT_0804bffc;
  return;
}




/* 0x080087d4 */
void FUN_080087d4(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  undefined4 *puVar1;
  undefined4 unaff_r4 = 0;
  undefined4 unaff_r5 = 0;
  undefined4 unaff_r6 = 0;
  undefined4 unaff_r7 = 0;
  undefined4 unaff_r8 = 0;
  undefined4 unaff_r9 = 0;
  undefined4 unaff_r10 = 0;
  undefined4 unaff_r11 = 0;
  undefined4 in_r12 = 0;
  undefined4 unaff_lr = 0;
  char in_NG = 0;
  char in_ZR = 0;
  char in_CY = 0;
  char in_OV = 0;
  byte in_Q = 0;
  
  puVar1 = DAT_0804c084;
  *(uint*)DAT_0804c084 = param_1;
  puVar1[1] = param_2;
  puVar1[2] = param_3;
  puVar1[3] = param_4;
  puVar1[4] = unaff_r4;
  puVar1[5] = unaff_r5;
  puVar1[8] = unaff_r8;
  puVar1[9] = unaff_r9;
  puVar1[10] = unaff_r10;
  puVar1[0xb] = unaff_r11;
  puVar1[0xc] = in_r12;
  puVar1[0xe] = unaff_lr;
  puVar1[0xd] = &stack0xfffffff8;
  puVar1[0xf] = 0;
  puVar1[0x10] = FUN_080087d4;
  puVar1[0x12] = &stack0xfffffff8;
  puVar1[0x13] = unaff_lr;
  puVar1[0x14] = &stack0xfffffff8;
  puVar1[0x15] = unaff_lr;
  puVar1[0x16] = 0;
  puVar1[0x17] = &stack0xfffffff8;
  puVar1[0x18] = unaff_lr;
  puVar1[0x19] = 0;
  puVar1[0x1a] = &stack0xfffffff8;
  puVar1[0x1b] = unaff_lr;
  puVar1[0x1c] = 0;
  puVar1[0x1d] = unaff_r8;
  puVar1[0x1e] = unaff_r9;
  puVar1[0x1f] = unaff_r10;
  puVar1[0x20] = unaff_r11;
  puVar1[0x21] = in_r12;
  puVar1[0x22] = &stack0xfffffff8;
  puVar1[0x23] = unaff_lr;
  puVar1[0x24] = 0;
  puVar1[0x11] = (uint)(byte)(in_NG << 4 | in_ZR << 3 | in_CY << 2 | in_OV << 1 | in_Q) << 0x1b;
  puVar1[7] = unaff_r7;
  puVar1[6] = unaff_r6;
  return;
}




/* 0x080088c4 */
void FUN_080088c4(param_1, param_2, param_3)
undefined8 * param_1; undefined8 * param_2; int param_3;
{
  undefined4 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  
  if (param_3 < 0x80) {
LAB_080088cc:
    if (0x1f < param_3) goto LAB_08008900;
LAB_080088d4:
    if (3 < param_3) goto LAB_08008918;
  }
  else {
    do {
      uVar2 = *param_2;
      uVar3 = param_2[1];
      uVar4 = param_2[2];
      uVar5 = param_2[3];
      uVar6 = param_2[4];
      uVar7 = param_2[5];
      uVar8 = param_2[6];
      uVar9 = param_2[7];
      uVar10 = param_2[8];
      uVar11 = param_2[9];
      uVar12 = param_2[10];
      uVar13 = param_2[0xb];
      uVar14 = param_2[0xc];
      uVar15 = param_2[0xd];
      uVar16 = param_2[0xe];
      uVar17 = param_2[0xf];
      param_2 = param_2 + 0x10;
      *param_1 = uVar2;
      param_1[1] = uVar3;
      param_1[2] = uVar4;
      param_1[3] = uVar5;
      param_1[4] = uVar6;
      param_1[5] = uVar7;
      param_1[6] = uVar8;
      param_1[7] = uVar9;
      param_1[8] = uVar10;
      param_1[9] = uVar11;
      param_1[10] = uVar12;
      param_1[0xb] = uVar13;
      param_1[0xc] = uVar14;
      param_1[0xd] = uVar15;
      param_1[0xe] = uVar16;
      param_1[0xf] = uVar17;
      param_1 = param_1 + 0x10;
      param_3 = param_3 + -0x80;
    } while (0x7f < param_3);
    if (param_3 < 0x80) goto LAB_080088cc;
LAB_08008900:
    do {
      uVar2 = *param_2;
      uVar3 = param_2[1];
      uVar4 = param_2[2];
      uVar5 = param_2[3];
      param_2 = param_2 + 4;
      *param_1 = uVar2;
      param_1[1] = uVar3;
      param_1[2] = uVar4;
      param_1[3] = uVar5;
      param_1 = param_1 + 4;
      param_3 = param_3 + -0x20;
    } while (0x1f < param_3);
    if (param_3 < 0x20) goto LAB_080088d4;
LAB_08008918:
    do {
      uVar1 = *(undefined4 *)param_2;
      param_2 = (undefined8 *)((int)param_2 + 4);
      *(undefined4 *)param_1 = uVar1;
      param_1 = (undefined8 *)((int)param_1 + 4);
      param_3 = param_3 + -4;
    } while (3 < param_3);
    if (3 < param_3) goto LAB_08008930;
  }
  if (param_3 < 1) {
    return;
  }
LAB_08008930:
  do {
    *(undefined1 *)param_1 = *(undefined1 *)param_2;
    param_3 = param_3 + -1;
    param_1 = (undefined8 *)((int)param_1 + 1);
    param_2 = (undefined8 *)((int)param_2 + 1);
  } while (0 < param_3);
  if (param_3 < 1) {
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x0800897c */
undefined4 FUN_0800897c()
{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x080089e0 */
void FUN_080089e0()
{
  return;
}




/* 0x08008a20 */
void FUN_08008a20(param_1, param_2)
undefined8 * param_1; int param_2;
{
  if (param_2 < 0x80) {
LAB_08008a50:
    if (0x1f < param_2) goto LAB_08008a78;
  }
  else {
    do {
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = 0;
      param_1[3] = 0;
      param_1[4] = 0;
      param_1[5] = 0;
      param_1[6] = 0;
      param_1[7] = 0;
      param_1[8] = 0;
      param_1[9] = 0;
      param_1[10] = 0;
      param_1[0xb] = 0;
      param_1[0xc] = 0;
      param_1[0xd] = 0;
      param_1[0xe] = 0;
      param_1[0xf] = 0;
      param_1 = param_1 + 0x10;
      param_2 = param_2 + -0x80;
    } while (0x7f < param_2);
    if (param_2 < 0x80) goto LAB_08008a50;
LAB_08008a78:
    do {
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = 0;
      param_1[3] = 0;
      param_1 = param_1 + 4;
      param_2 = param_2 + -0x20;
    } while (0x1f < param_2);
    if (0x1f < param_2) goto LAB_08008a8c;
  }
  if (param_2 < 1) {
    return;
  }
LAB_08008a8c:
  do {
    *(undefined1 *)param_1 = 0;
    param_2 = param_2 + -1;
    param_1 = (undefined8 *)((int)param_1 + 1);
  } while (0 < param_2);
  if (param_2 < 1) {
    return;
  }
  ((code *)0x0)();
  return;
}




/* 0x08008ba4 */
undefined4 FUN_08008ba4(param_1, param_2, param_3, param_4)
undefined4 * param_1; undefined4 * param_2; uint * param_3; uint param_4;
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  do {
    uVar1 = param_2[1];
    uVar2 = param_2[2];
    uVar3 = param_2[3];
    uVar4 = param_2[4];
    uVar5 = param_2[5];
    uVar6 = param_2[6];
    uVar7 = param_2[7];
    *param_1 = *param_2;
    param_1[1] = uVar1;
    param_1[2] = uVar2;
    param_1[3] = uVar3;
    param_1[4] = uVar4;
    param_1[5] = uVar5;
    param_1[6] = uVar6;
    param_1[7] = uVar7;
    param_1 = param_1 + 8;
  } while ((param_4 & *param_3) != 0);
  return 0;
}




/* 0x08008bc4 */
undefined4 * FUN_08008bc4(param_1, param_2, param_3)
undefined4 * param_1; undefined4 * param_2; undefined4 * param_3;
{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  int iVar10;
  uint *puVar11;
  
  iVar10 = param_3[2];
  uVar1 = param_3[1];
  puVar11 = (uint *)*param_3;
  while( true ) {
    uVar2 = *param_2;
    uVar3 = param_2[1];
    uVar4 = param_2[2];
    uVar5 = param_2[3];
    uVar6 = param_2[4];
    uVar7 = param_2[5];
    uVar8 = param_2[6];
    uVar9 = param_2[7];
    param_2 = param_2 + 8;
    *param_1 = uVar2;
    param_1[1] = uVar3;
    param_1[2] = uVar4;
    param_1[3] = uVar5;
    param_1[4] = uVar6;
    param_1[5] = uVar7;
    param_1[6] = uVar8;
    param_1[7] = uVar9;
    iVar10 = iVar10 + -0x20;
    if (iVar10 < 0x20) break;
    do {
      if ((*puVar11 & param_3[3]) != 0) goto LAB_08008c04;
    } while ((*puVar11 & uVar1) == 0);
  }
LAB_08008c04:
  param_3[2] = iVar10;
  return param_2;
}




/* 0x08008c14 */
undefined4 FUN_08008c14(param_1, param_2, param_3, param_4)
int param_1; uint * param_2; undefined4 param_3; uint param_4;
{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint local_20;
  
  if ((param_1 == 0) || (param_2 == (uint *)0x0)) {
    uVar2 = 0xffffffff;
  }
  else {
    local_20 = param_4;
    for (uVar3 = 0; uVar3 < DAT_08052c94; uVar3 = uVar3 + 1) {
      iVar1 = (**(code **)(*(int *)((&DAT_08052c80)[uVar3 * 2] + 4) + 0x24))
                        ((&DAT_08052c80)[uVar3 * 2],param_1,&local_20);
      if (iVar1 == 0) {
        *param_2 = uVar3;
        goto LAB_08008c56;
      }
    }
    local_20 = 0xffffffff;
    *param_2 = 0xffffffff;
LAB_08008c56:
    param_2[1] = local_20;
    uVar2 = 0;
  }
  return uVar2;
}




/* 0x08008c60 */
int FUN_08008c60()
{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  uint uVar4;
  undefined1 auStack_40 [8];
  int local_38;
  undefined1 auStack_30 [8];
  int *local_28;
  undefined1 auStack_24 [8];
  int local_1c;
  int local_18;
  
  pcVar3 = "ADC_BOOT_BSP";
  if (DAT_0804ceb4 != 1) {
    FUN_0800b604(0);
    if ((DAT_0804ceb8 == 0) && (iVar1 = FUN_0800b7ea(0,0x200006f,0x10000,&DAT_0804ceb8), iVar1 != 0)
       ) {
      local_18 = 0;
    }
    else if ((DAT_0804ceb8 & 1) == 0) {
      (**(code **)(*(int *)(DAT_0804ceb8 + 4) + 0x38))(DAT_0804ceb8,0);
    }
    else {
      (**(code **)(*(int *)((DAT_0804ceb8 & 0xfffffffe) + 4) + 0x2c))
                (0xe,DAT_0804ceb8 & 0xfffffffe,0,&local_18);
    }
    if (local_18 == 0x2e) {
      iVar1 = FUN_0800b7ea(0,0x2000139,0x10000,&local_1c);
      if (iVar1 != 0) {
        return iVar1;
      }
      iVar1 = (**(code **)(*(int *)(local_1c + 4) + 0x28))(local_1c,auStack_40);
      if (iVar1 != 0) {
        return iVar1;
      }
      if (local_38 == 1) {
        pcVar3 = "ADC_BOOT_BSP_8974PRO_PMA8084_PM8941";
      }
    }
    iVar1 = dal_device_attach(&DAT_08008d8c,auStack_24);
    if (iVar1 != 0) {
      return iVar1;
    }
    iVar1 = thunk_FUN_080106aa(auStack_24,pcVar3,0,auStack_30);
    if (iVar1 != 0) {
      return iVar1;
    }
    DAT_08052c78 = local_28;
    DAT_08052c94 = local_28[1];
    if (3 < DAT_08052c94) {
      DAT_08052c94 = 3;
    }
    for (uVar4 = 0; uVar4 < DAT_08052c94; uVar4 = uVar4 + 1) {
      uVar2 = *(undefined4 *)(*(uint*)DAT_08052c78 + uVar4 * 8);
      (&DAT_08052c7c)[uVar4 * 2] = uVar2;
      iVar1 = FUN_0800b8a4(0,uVar2,0x20000,&DAT_08052c80 + uVar4 * 2);
      if (iVar1 != 0) {
        FUN_0800b54e();
        return -1;
      }
    }
    DAT_0804ceb4 = 1;
  }
  return 0;
}




/* 0x08008d98 */
undefined4 FUN_08008d98(param_1, param_2)
uint * param_1; undefined1 * param_2;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  int local_38 [2];
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  uVar4 = 0xffffffff;
  if ((((param_1 != (uint *)0x0) && (param_2 != (undefined1 *)0x0)) &&
      (uVar2 = *param_1, uVar2 < DAT_08052c94)) && (uVar2 < 3)) {
    uVar3 = param_1[1];
    uVar2 = (&DAT_08052c80)[uVar2 * 2];
    local_38[0] = 1;
    local_30 = 0;
    local_2c = 0;
    local_28 = 0;
    local_24 = 0;
    iVar1 = FUN_0800bb0c(uVar2,0);
    if (((iVar1 == 0) &&
        (iVar1 = (**(code **)(*(int *)(uVar2 + 4) + 0x40))(uVar2,uVar3,local_38), iVar1 == 0)) &&
       ((**(code **)(*(int *)((uVar2 & 0xfffffffe) + 4) + 0x14))(), local_38[0] != 2)) {
      if (local_38[0] == 0) {
        *param_2 = 1;
      }
      else {
        *param_2 = 0;
      }
      *(undefined4 *)(param_2 + 4) = local_30;
      *(undefined4 *)(param_2 + 8) = local_2c;
      *(undefined4 *)(param_2 + 0xc) = local_28;
      *(undefined4 *)(param_2 + 0x10) = local_24;
      uVar4 = 0;
    }
  }
  return uVar4;
}




/* 0x08008e24 */
undefined4 FUN_08008e24(param_1, param_2, param_3, param_4)
int * param_1; uint param_2; int param_3; int * param_4;
{
  bool bVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  bVar1 = true;
  if ((param_1 == (int *)0x0) || (param_4 == (int *)0x0)) {
    return 1;
  }
  if ((1 < param_2) && (*param_1 < param_1[2])) {
    bVar1 = false;
  }
  for (; uVar3 < param_2; uVar3 = uVar3 + 1) {
    if (bVar1) {
      if (param_1[uVar3 * 2] < param_3) break;
    }
    else if ((true) && (param_3 < param_1[uVar3 * 2])) break;
  }
  if (uVar3 == 0) {
    iVar2 = param_1[1];
  }
  else if (uVar3 == param_2) {
    iVar2 = param_1[param_2 * 2 + -1];
  }
  else {
    iVar2 = ((param_1[uVar3 * 2 + 1] - param_1[uVar3 * 2 + -1]) *
            (param_3 - param_1[uVar3 * 2 + -2])) / (param_1[uVar3 * 2] - param_1[uVar3 * 2 + -2]) +
            param_1[uVar3 * 2 + -1];
  }
  *param_4 = iVar2;
  return 0;
}




/* 0x08008eb0 */
undefined4 AuthenticateImage()
{
  int iVar1;
  char *pcVar2;
  int iVar3;
  undefined1 auStack_210 [516];
  
  iVar3 = *(int *)(DAT_0804d260 + 0x30);
  if ((iVar3 == -0x60) || ((undefined4 *)(iVar3 + 0x50) == (undefined4 *)0x0)) {
    pcVar2 = 
    "AuthenticateImage() Returning FALSE, pbl_secboot_hw_ftbl_ptr == NULL || pbl_secboot_ftbl_ptr == NULL."
    ;
  }
  else {
    iVar1 = FUN_080273cc();
    if (iVar1 == 0) {
      firehose_log("AuthenticateImage() Authentication is NOT enabled, returning TRUE");
      return 1;
    }
    FUN_08006d14(&DAT_0805a0c0,0x50);
    iVar1 = (**(code **)(iVar3 + 0x50))(0,auStack_210);
    if (iVar1 == 0) {
      firehose_log("Calling pbl_secboot_ftbl_ptr->secboot_authenticate with image_info.signature_len = 0x%X"
                   ,DAT_0805a09c);
      firehose_log("Calling pbl_secboot_ftbl_ptr->secboot_authenticate with image_info.sw_type = 0x%X"
                   ,DAT_0805a0a0);
      firehose_log("Calling pbl_secboot_ftbl_ptr->secboot_authenticate with image_info.sw_version = 0x%X"
                   ,DAT_0805a0a4);
      iVar1 = (**(code **)(iVar3 + 0x58))(auStack_210,1,&DAT_0805a080);
      if (iVar1 != 0) {
        firehose_log("AuthenticateImage() Returning FALSE, secboot_authenticate() returned 0x%X (not E_SECBOOT_SUCCESS=0x%X)"
                     ,iVar1,0);
        (**(code **)(iVar3 + 0x54))(auStack_210);
        return 0;
      }
      (**(code **)(iVar3 + 0x54))(auStack_210);
      return 1;
    }
    pcVar2 = 
    "AuthenticateImage() Returning FALSE, pbl_secboot_ftbl_ptr->secboot_init(NULL, &secboot_handle) FAILED"
    ;
  }
  firehose_log(pcVar2);
  return 0;
}




/* 0x08008f5c */
undefined4 boot_temp_check_init()
{
  int iVar1;
  undefined1 auStack_20 [8];
  int *local_18;
  undefined1 auStack_14 [8];
  int local_c;
  
  if (DAT_0804d198 == 0) {
    iVar1 = dal_device_attach("QBootTempCheck",auStack_14);
    if (iVar1 != 0) {
      return 5;
    }
    iVar1 = thunk_FUN_080106aa(auStack_14,"BOOT_TEMP_CHECK_BSP",0,auStack_20);
    if (iVar1 != 0) {
      return 5;
    }
    DAT_0804d194 = local_18;
    DAT_0804d198 = 1;
  }
  iVar1 = FUN_0800f134(((uint*)&DAT_0804d194)[2],&local_c);
  if (iVar1 != 0) {
    if (iVar1 == 1) {
      return 2;
    }
    if (iVar1 != 2) {
      return 5;
    }
    return 1;
  }
  if (*(uint*)DAT_0804d194 < local_c) {
    return 4;
  }
  if (((uint*)&DAT_0804d194)[1] <= local_c) {
    return 0;
  }
  return 3;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08008f5c */
undefined4 thunk_boot_temp_check_init()
{
  int iVar1;
  undefined1 auStack_20 [8];
  int *piStack_18;
  undefined1 auStack_14 [8];
  int iStack_c;
  
  if (DAT_0804d198 == 0) {
    iVar1 = dal_device_attach("QBootTempCheck",auStack_14);
    if (iVar1 != 0) {
      return 5;
    }
    iVar1 = thunk_FUN_080106aa(auStack_14,"BOOT_TEMP_CHECK_BSP",0,auStack_20);
    if (iVar1 != 0) {
      return 5;
    }
    DAT_0804d194 = piStack_18;
    DAT_0804d198 = 1;
  }
  iVar1 = FUN_0800f134(((uint*)&DAT_0804d194)[2],&iStack_c);
  if (iVar1 != 0) {
    if (iVar1 == 1) {
      return 2;
    }
    if (iVar1 != 2) {
      return 5;
    }
    return 1;
  }
  if (*(uint*)DAT_0804d194 < iStack_c) {
    return 4;
  }
  if (((uint*)&DAT_0804d194)[1] <= iStack_c) {
    return 0;
  }
  return 3;
}




/* 0x08008fec */
undefined1 FUN_08008fec(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined1 uVar7;
  undefined4 local_28;
  
  uVar6 = 0;
  local_28 = param_4;
  puVar2 = (undefined4 *)FUN_08006e04();
  puVar3 = (undefined4 *)FUN_08006e04(param_1 + 8);
  local_28 = 0;
  if (((puVar2 == (undefined4 *)0x0) || (uVar4 = FUN_08006e04(param_1 + 4), uVar4 == 0)) ||
     (puVar3 == (undefined4 *)0x0)) {
    uVar7 = 2;
  }
  else {
    uVar1 = (uint)puVar2 & 3;
    for (; uVar6 < uVar4 >> 4; uVar6 = uVar6 + 1) {
      uVar5 = 0;
      do {
        do {
        } while (-1 < (int)(_DAT_0073a100 << 0x1d));
        if (uVar1 == 0) {
          _DAT_0073a010 = *puVar2;
        }
        else {
          FUN_08009600(&local_28,puVar2,4);
          _DAT_0073a010 = local_28;
        }
        FUN_0800960a();
        puVar2 = puVar2 + 1;
        uVar5 = uVar5 + 1;
      } while (uVar5 < 4);
      uVar5 = 0;
      do {
        do {
        } while (-1 < (int)(_DAT_0073a100 << 0x1c));
        *puVar3 = *(undefined4 *)(uVar5 * 4 + 0x73a020);
        FUN_0800960a();
        puVar3 = puVar3 + 1;
        uVar5 = uVar5 + 1;
      } while (uVar5 < 4);
    }
    uVar7 = (_DAT_0073a100 & 1) != 0;
    FUN_0800960a();
  }
  return uVar7;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x080090a0 */
undefined4 FUN_080090a0(param_1)
int param_1;
{
  if (param_1 != 0) {
    FUN_08006e1a(_DAT_0073a20c,param_1 + 0x45);
    FUN_08006e1a(_DAT_0073a210,param_1 + 0x49);
    FUN_08006e1a(_DAT_0073a214,param_1 + 0x4d);
    FUN_08006e1a(_DAT_0073a218,param_1 + 0x51);
    FUN_0800960a();
    return 0;
  }
  return 2;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x080090e4 */
undefined4 FUN_080090e4(param_1)
int param_1;
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  if ((param_1 == 0) ||
     ((*(char *)(param_1 + 0x78) != '\x01' && (*(char *)(param_1 + 0x78) != '\x02')))) {
    uVar3 = 2;
  }
  else {
    do {
      iVar1 = _DAT_0073a100;
      FUN_0800960a();
    } while (-1 < iVar1 << 0x1e);
    FUN_08006e1a(_DAT_0073a390,param_1 + 0x60);
    FUN_08006e1a(_DAT_0073a394,param_1 + 100);
    FUN_0800960a();
    uVar2 = 0;
    do {
      FUN_08006e1a(*(undefined4 *)(uVar2 * 4 + 0x73a310),param_1 + uVar2 * 4 + 0x40);
      uVar2 = uVar2 + 1;
    } while (uVar2 < 8);
    FUN_0800960a();
  }
  return uVar3;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08009154 */
undefined1 FUN_08009154(param_1)
int param_1;
{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined1 uVar8;
  undefined4 local_40;
  undefined1 local_3c [16];
  int local_2c;
  
  iVar1 = DAT_0804cd58;
  local_2c = DAT_0804cd58;
  local_40 = 0;
  if ((param_1 == 0) || (puVar2 = (undefined4 *)FUN_08006e04(param_1), puVar2 == (undefined4 *)0x0))
  {
    uVar8 = 2;
  }
  else {
    uVar3 = FUN_08006e04(param_1 + 4);
    uVar7 = uVar3 & 0xf;
    if (uVar7 != 0) {
      for (uVar5 = 0; uVar5 < uVar7; uVar5 = uVar5 + 1 & 0xff) {
        iVar4 = FUN_08006e04(param_1);
        local_3c[uVar5] = *(undefined1 *)(iVar4 + uVar5 + (uVar3 >> 4) * 0x10);
      }
    }
    uVar5 = (uint)puVar2 & 3;
    for (uVar6 = 0; uVar6 < (uVar3 >> 4) << 2; uVar6 = uVar6 + 1) {
      do {
      } while (-1 < (int)(_DAT_0073a100 << 0x1d));
      if (uVar5 == 0) {
        _DAT_0073a010 = *puVar2;
      }
      else {
        FUN_08009600(&local_40,puVar2,4);
        _DAT_0073a010 = local_40;
      }
      FUN_0800960a();
      puVar2 = puVar2 + 1;
    }
    if (uVar7 != 0) {
      uVar3 = 0;
      do {
        do {
        } while (-1 < (int)(_DAT_0073a100 << 0x1d));
        FUN_08009600(&local_40,local_3c + uVar3 * 4,4);
        _DAT_0073a010 = local_40;
        FUN_0800960a();
        uVar3 = uVar3 + 1;
      } while (uVar3 < 4);
    }
    do {
      uVar3 = _DAT_0073a100;
      FUN_0800960a();
    } while (-1 < (int)(uVar3 << 0x1e));
    uVar8 = (_DAT_0073a100 & 1) != 0;
    FUN_0800960a();
  }
  if (local_2c != iVar1) {
    FUN_08010960();
  }
  return uVar8;
}




/* 0x0800947c */
undefined4 FUN_0800947c()
{
  return 0;
}




/* 0x0800947c */
undefined4 thunk_FUN_0800947c()
{
  return 0;
}




/* 0x08009480 */
undefined4 FUN_08009480()
{
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08009480 */
undefined4 thunk_FUN_08009480()
{
  return 0;
}




/* 0x08009484 */
undefined4 FUN_08009484(param_1, param_2, param_3, param_4, param_5, param_6)
int param_1; char * param_2; uint param_3; undefined1 * param_4; uint param_5; undefined4 * param_6;
{
  undefined4 uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  
  uVar1 = 0;
  if (param_1 == 1) {
    if ((param_4 == (undefined1 *)0x0) || (param_5 == 0)) {
      return 1;
    }
    uVar3 = 1;
    *param_4 = 1;
LAB_080094ce:
    *param_6 = uVar3;
    return uVar1;
  }
  if (param_1 != 2) {
    if (param_1 == 3) {
      if (param_4 == (undefined1 *)0x0) {
        return 1;
      }
      if (param_5 < 0x90) {
        return 1;
      }
      uVar1 = FUN_080090a0(param_4);
      uVar3 = 0x90;
    }
    else {
      if (param_1 != 4) {
        return 1;
      }
      if (param_2 == (char *)0x0) {
        return 1;
      }
      if (param_3 < 0xc) {
        return 1;
      }
      uVar1 = FUN_08008fec(param_2);
      uVar3 = 0xc;
    }
    goto LAB_080094ce;
  }
  if (param_2 == (char *)0x0) {
    return 1;
  }
  if (param_3 != 0x90) {
    return 1;
  }
  if (param_2 == (char *)0x0) {
    return 2;
  }
  _DAT_0073a200 = 0;
  FUN_0800960a();
  _DAT_0073a300 = 0;
  FUN_0800960a();
  uVar2 = (uint)(byte)param_2[0x8a] << 6;
  uVar4 = uVar2 | 2;
  if (param_2[0x89] == '\0') {
    uVar4 = uVar2 | 0x402;
  }
  if ((byte)param_2[0x8a] == 2) {
    uVar4 = uVar4 | 0x400;
  }
  if ((*param_2 != '\0') && (*param_2 == '\x01')) {
    uVar4 = uVar4 | 0x10;
  }
  if (param_2[0x8b] != '\0') {
    uVar4 = uVar4 | 0x4000;
  }
  _DAT_0073a200 = uVar4;
  _DAT_0073a204 = FUN_08006e04(param_2 + 0x8c);
  FUN_0800960a();
  _DAT_0073a208 = 0;
  FUN_0800960a();
  _DAT_0073a110 = FUN_08006e04(param_2 + 0x8c);
  if (_DAT_0073a110 % 0x10 != 0) {
    _DAT_0073a110 = _DAT_0073a110 + (0x10 - _DAT_0073a110 % 0x10);
  }
  FUN_0800960a();
  if ((int)(uVar4 << 0x1e) < 0) {
    _DAT_0073a20c = FUN_08006e04(param_2 + 0x45);
    _DAT_0073a210 = FUN_08006e04(param_2 + 0x49);
    _DAT_0073a214 = FUN_08006e04(param_2 + 0x4d);
    _DAT_0073a218 = FUN_08006e04(param_2 + 0x51);
    _DAT_0073a21c = 0xffffffff;
    FUN_0800960a();
    if (param_2[0x8b] == '\0') {
      uVar2 = 0;
      do {
        uVar1 = FUN_08006e04(param_2 + uVar2 * 4 + 1);
        *(undefined4 *)(uVar2 * 4 + 0x73d000) = uVar1;
        uVar2 = uVar2 + 1;
      } while (uVar2 < 8);
      FUN_0800960a();
      goto LAB_08009352;
    }
  }
  else {
LAB_08009352:
    if (param_2[0x8b] == '\0') {
      _DAT_0073a120 = 1;
      goto LAB_08009362;
    }
  }
  _DAT_0073c000 = 1;
LAB_08009362:
  FUN_0800960a();
  do {
    uVar2 = _DAT_0073a100 << 0x12;
    FUN_0800960a();
  } while (uVar2 >> 0x1c == 0);
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x080094e6 */
undefined4 FUN_080094e6(param_1, param_2, param_3, param_4, param_5, param_6)
int param_1; int param_2; uint param_3; undefined1 * param_4; uint param_5; undefined4 * param_6;
{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar1 = 0;
  if (param_1 == 1) {
    if ((param_4 == (undefined1 *)0x0) || (param_5 == 0)) {
      return 1;
    }
    uVar2 = 1;
    *param_4 = 1;
LAB_08009530:
    *param_6 = uVar2;
    return uVar1;
  }
  if (param_1 != 2) {
    if (param_1 == 3) {
      if (param_4 == (undefined1 *)0x0) {
        return 1;
      }
      if (param_5 < 0x7a) {
        return 1;
      }
      uVar1 = FUN_080090e4(param_4);
      uVar2 = 0x7a;
    }
    else {
      if (param_1 != 4) {
        return 1;
      }
      if (param_2 == 0) {
        return 1;
      }
      if (param_3 < 8) {
        return 1;
      }
      uVar1 = FUN_08009154(param_2);
      uVar2 = 8;
    }
    goto LAB_08009530;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_3 != 0x7a) {
    return 1;
  }
  uVar3 = 0;
  uVar1 = 0;
  if (param_2 == 0) {
LAB_080093c0:
    uVar1 = 2;
  }
  else {
    _DAT_0073a200 = 0;
    FUN_0800960a();
    _DAT_0073a300 = 0;
    FUN_0800960a();
    if (*(char *)(param_2 + 0x78) == '\x01') {
      uVar4 = 1;
      uVar5 = 5;
    }
    else {
      if (*(char *)(param_2 + 0x78) != '\x02') goto LAB_080093c0;
      uVar5 = 8;
      uVar4 = 0x201;
    }
    if (*(char *)(param_2 + 0x69) != '\0') {
      uVar4 = uVar4 | 0x10000;
    }
    for (; uVar3 < uVar5; uVar3 = uVar3 + 1) {
      uVar2 = FUN_08006e04(param_2 + uVar3 * 4 + 0x40);
      *(undefined4 *)(uVar3 * 4 + 0x73a310) = uVar2;
    }
    FUN_0800960a();
    _DAT_0073a300 = uVar4;
    FUN_0800960a();
    _DAT_0073a390 = FUN_08006e04(param_2 + 0x60);
    _DAT_0073a394 = FUN_08006e04(param_2 + 100);
    FUN_0800960a();
    _DAT_0073a304 = FUN_08006e04(param_2 + 0x6a);
    FUN_0800960a();
    _DAT_0073a308 = 0;
    FUN_0800960a();
    _DAT_0073a110 = FUN_08006e04(param_2 + 0x6a);
    if (_DAT_0073a110 % 0x10 != 0) {
      _DAT_0073a110 = _DAT_0073a110 + (0x10 - _DAT_0073a110 % 0x10);
    }
    FUN_0800960a();
    _DAT_0073a120 = 1;
    FUN_0800960a();
    do {
      uVar3 = _DAT_0073a100 << 0x12;
      FUN_0800960a();
    } while (uVar3 >> 0x1c == 0);
  }
  return uVar1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08009548 */
undefined4 FUN_08009548(param_1)
int param_1;
{
  if (param_1 == 0) {
    _DAT_0073a400 = 0x21e;
  }
  else {
    if (param_1 != 1) {
      return 1;
    }
    _DAT_0073a400 = 0xe022e;
  }
  FUN_0800960a();
  return 0;
}




/* 0x080095a4 */
undefined4 FUN_080095a4(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  undefined4 local_10;
  undefined4 local_c;
  undefined4 uStack_8;
  
  local_10 = 8;
  local_c = param_1;
  uStack_8 = param_2;
  FUN_080094e6(4,&local_c,8,0,0,&local_10);
  return 0;
}




/* 0x080095d2 */
undefined4 FUN_080095d2(param_1)
undefined1 * param_1;
{
  *param_1 = 0;
  return 0;
}




/* 0x080095dc */
undefined4 FUN_080095dc(param_1, param_2)
int param_1; undefined4 * param_2;
{
  undefined1 *puVar1;
  
  if (param_1 == 0) {
    puVar1 = (undefined1 *)0x8009625;
  }
  else {
    if (param_1 != 1) {
      return 1;
    }
    puVar1 = &LAB_080095c6;
  }
  *param_2 = puVar1;
  return 0;
}




/* 0x080095fc */
undefined4 FUN_080095fc()
{
  return 0;
}




/* 0x08009600 */
undefined4 FUN_08009600()
{
  FUN_08006a30();
  return 0;
}




/* 0x0800960a */
undefined4 FUN_0800960a()
{
  FUN_08007bec();
  return 0;
}




/* 0x08009614 */
undefined4 FUN_08009614(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  FUN_08006cc0(param_1,param_3,param_2);
  return 0;
}




/* 0x08009624 */
undefined4 FUN_08009624(param_1, param_2, param_3, param_4, param_5)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4; int param_5;
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  
  if (param_5 == 1) {
    iVar5 = FUN_08006e04(param_2);
    uVar1 = FUN_08006e04(iVar5 + 4);
    uVar2 = FUN_08006e04(iVar5);
    iVar5 = FUN_08006e04(param_1);
    uVar3 = FUN_08006e04(iVar5 + 4);
    uVar4 = FUN_08006e04(iVar5);
    uVar1 = FUN_080095a4(uVar4,uVar3,uVar2,uVar1);
    return uVar1;
  }
  if (param_5 != 2) {
    return 1;
  }
  FUN_08006e04(param_2);
  FUN_08006e04();
  iVar5 = FUN_08006e04(param_1);
  FUN_08006e04(iVar5 + 4);
  FUN_08006e04(iVar5);
  uVar1 = FUN_08009484(4,&stack0xffffffec,0xc,0,0,&stack0xffffffe8);
  return uVar1;
}




/* 0x080096a4 */
undefined4 FUN_080096a4()
{
  FUN_080096b0();
  return 0;
}




/* 0x080096b0 */
undefined4 FUN_080096b0(param_1)
undefined4 * param_1;
{
  uint uVar1;
  
  uVar1 = 0;
  do {
    if (&DAT_87c198b8 + uVar1 * 4 == param_1) {
      (&DAT_87c198c7)[uVar1 * 0x10] = 0;
      return 0;
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 < 6);
  return 0;
}




/* 0x080096d4 */
undefined4 FUN_080096d4()
{
  FUN_080096e0();
  return 0;
}




/* 0x080096e0 */
undefined4 FUN_080096e0(param_1, param_2)
undefined4 * param_1; uint param_2;
{
  undefined *puVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (param_2 < 5) {
    puVar1 = &DAT_08050d00;
  }
  else {
    if (param_2 - 5 < 10) {
      do {
        if ((&DAT_87c198c7)[uVar2 * 0x10] != '\x01') {
          *param_1 = &DAT_87c198b8 + uVar2 * 4;
          (&DAT_87c198c7)[uVar2 * 0x10] = 1;
          break;
        }
        uVar2 = uVar2 + 1;
      } while (uVar2 < 6);
      if (uVar2 < 5) {
        return 0;
      }
      return 1;
    }
    if (0x130 < param_2 - 0xf) {
      return 1;
    }
    puVar1 = &DAT_87c19918;
  }
  *param_1 = puVar1;
  return 0;
}




/* 0x08009734 */
int FUN_08009734(param_1, param_2, param_3, param_4)
int param_1; int param_2; int param_3; int param_4;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  
  if ((((param_1 != 0) && (iVar1 = FUN_08006e04(), iVar1 != 0)) && (param_4 != 0)) &&
     (((iVar2 = FUN_08006e04(param_4 + 4), iVar2 == 1 && (iVar2 = FUN_08006e04(param_4), iVar2 != 0)
       ) && ((param_3 == 1 && (param_2 != 0)))))) {
    if (*(char *)(iVar1 + 0x78) == '\x01') {
      uVar6 = 0x14;
    }
    else {
      if (*(char *)(iVar1 + 0x78) != '\x02') {
        return 2;
      }
      uVar6 = 0x20;
    }
    uVar3 = FUN_08006e04(iVar2 + 4);
    if (uVar6 <= uVar3) {
      iVar2 = FUN_08006e04(param_2);
      uVar3 = FUN_08006e04(param_2 + 4);
      do {
        if (uVar3 <= DAT_0804d610) {
          FUN_08009e14(iVar1,iVar2,uVar3,1);
          break;
        }
        iVar4 = FUN_08009e14(iVar1,iVar2,DAT_0804d610,0);
        if (iVar4 != 0) break;
        uVar3 = uVar3 - DAT_0804d610;
        iVar2 = iVar2 + DAT_0804d610;
      } while (uVar3 != 0);
      FUN_08006e04(param_4);
      uVar5 = FUN_08006e04();
      iVar1 = FUN_08009600(uVar5,iVar1 + 0x40,uVar6);
      if (iVar1 == 0) {
        FUN_08006e1a(1,param_4 + 4);
        iVar1 = FUN_08006e04(param_4);
        FUN_08006e1a(uVar6,iVar1 + 4);
        return 0;
      }
      return iVar1;
    }
  }
  return 2;
}




/* 0x08009804 */
undefined4 FUN_08009804(param_1)
int * param_1;
{
  if ((param_1 != (int *)0x0) && (*param_1 != 0)) {
    FUN_08006e04();
    FUN_080096a4();
    FUN_08006e1a(0,*param_1);
    FUN_080096a4(*param_1);
    *param_1 = 0;
    return 0;
  }
  return 2;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08009804 */
undefined4 thunk_FUN_08009804(param_1)
int * param_1;
{
  if ((param_1 != (int *)0x0) && (*param_1 != 0)) {
    FUN_08006e04();
    FUN_080096a4();
    FUN_08006e1a(0,*param_1);
    FUN_080096a4(*param_1);
    *param_1 = 0;
    return 0;
  }
  return 2;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08009830 */
int FUN_08009830(param_1, param_2, param_3, param_4)
int param_1; int param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  
  if ((((param_1 != 0) &&
       (uStack_30 = param_3, uStack_2c = param_4, iVar1 = FUN_08006e04(), iVar1 != 0)) &&
      (param_2 != 0)) &&
     ((iVar2 = FUN_08006e04(param_2 + 4), iVar2 == 1 && (iVar2 = FUN_08006e04(param_2), iVar2 != 0))
     )) {
    if (*(char *)(iVar1 + 0x78) == '\x01') {
      uVar5 = 0x14;
    }
    else {
      if (*(char *)(iVar1 + 0x78) != '\x02') {
        return 2;
      }
      uVar5 = 0x20;
    }
    uVar3 = FUN_08006e04(iVar2 + 4);
    if (uVar5 <= uVar3) {
      if (*(char *)(iVar1 + 0x76) == '\x01') {
        do {
          iVar2 = _DAT_0073a100;
          FUN_0800960a();
        } while (-1 < iVar2 << 0x1e);
        for (uVar3 = 0; uVar3 < DAT_87c00a24; uVar3 = uVar3 + 1) {
          *(undefined1 *)(iVar1 + 0x76) = 0;
          *(undefined1 *)(iVar1 + 0x77) = 1;
          FUN_08006e1a(*(undefined4 *)(&DAT_87c00a00 + DAT_87c00a20 * 4),&uStack_30);
          FUN_08006e1a(*(undefined4 *)(&DAT_87c00a10 + DAT_87c00a20 * 4),&uStack_2c);
          iVar2 = FUN_08009af4(param_1,&uStack_30,1);
          if (iVar2 != 0) {
            return 1;
          }
          DAT_87c00a20 = DAT_87c00a20 + 1 & 3;
        }
        DAT_87c00a24 = 0;
        *(undefined1 *)(iVar1 + 0x76) = 0;
        *(undefined1 *)(iVar1 + 0x77) = 1;
      }
      uVar3 = FUN_08006e04(iVar1 + 0xba);
      if (uVar3 != 0) {
        if (0x40 < uVar3) {
          return 1;
        }
        if ((uVar3 < 0x40) &&
           (iVar2 = FUN_08009614(uVar3 + iVar1 + 0x7a,0,0x40 - uVar3), iVar2 != 0)) {
          return iVar2;
        }
        uVar4 = FUN_08006e04(iVar1 + 0xba);
        iVar2 = FUN_08009e14(iVar1,iVar1 + 0x7a,uVar4,1);
        if (iVar2 != 0) {
          return iVar2;
        }
      }
      FUN_08006e04(param_2);
      uVar4 = FUN_08006e04();
      iVar1 = FUN_08009600(uVar4,iVar1 + 0x40,uVar5);
      if (iVar1 == 0) {
        FUN_08006e1a(1,param_2 + 4);
        iVar1 = FUN_08006e04(param_2);
        FUN_08006e1a(uVar5,iVar1 + 4);
        return 0;
      }
      return iVar1;
    }
  }
  return 2;
}




/* 0x08009830 */
int thunk_FUN_08009830(param_1, param_2, param_3, param_4)
int param_1; int param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  
  if ((((param_1 != 0) &&
       (uStack_30 = param_3, uStack_2c = param_4, iVar1 = FUN_08006e04(), iVar1 != 0)) &&
      (param_2 != 0)) &&
     ((iVar2 = FUN_08006e04(param_2 + 4), iVar2 == 1 && (iVar2 = FUN_08006e04(param_2), iVar2 != 0))
     )) {
    if (*(char *)(iVar1 + 0x78) == '\x01') {
      uVar5 = 0x14;
    }
    else {
      if (*(char *)(iVar1 + 0x78) != '\x02') {
        return 2;
      }
      uVar5 = 0x20;
    }
    uVar3 = FUN_08006e04(iVar2 + 4);
    if (uVar5 <= uVar3) {
      if (*(char *)(iVar1 + 0x76) == '\x01') {
        do {
          iVar2 = _DAT_0073a100;
          FUN_0800960a();
        } while (-1 < iVar2 << 0x1e);
        for (uVar3 = 0; uVar3 < DAT_87c00a24; uVar3 = uVar3 + 1) {
          *(undefined1 *)(iVar1 + 0x76) = 0;
          *(undefined1 *)(iVar1 + 0x77) = 1;
          FUN_08006e1a(*(undefined4 *)(&DAT_87c00a00 + DAT_87c00a20 * 4),&uStack_30);
          FUN_08006e1a(*(undefined4 *)(&DAT_87c00a10 + DAT_87c00a20 * 4),&uStack_2c);
          iVar2 = FUN_08009af4(param_1,&uStack_30,1);
          if (iVar2 != 0) {
            return 1;
          }
          DAT_87c00a20 = DAT_87c00a20 + 1 & 3;
        }
        DAT_87c00a24 = 0;
        *(undefined1 *)(iVar1 + 0x76) = 0;
        *(undefined1 *)(iVar1 + 0x77) = 1;
      }
      uVar3 = FUN_08006e04(iVar1 + 0xba);
      if (uVar3 != 0) {
        if (0x40 < uVar3) {
          return 1;
        }
        if ((uVar3 < 0x40) &&
           (iVar2 = FUN_08009614(uVar3 + iVar1 + 0x7a,0,0x40 - uVar3), iVar2 != 0)) {
          return iVar2;
        }
        uVar4 = FUN_08006e04(iVar1 + 0xba);
        iVar2 = FUN_08009e14(iVar1,iVar1 + 0x7a,uVar4,1);
        if (iVar2 != 0) {
          return iVar2;
        }
      }
      FUN_08006e04(param_2);
      uVar4 = FUN_08006e04();
      iVar1 = FUN_08009600(uVar4,iVar1 + 0x40,uVar5);
      if (iVar1 == 0) {
        FUN_08006e1a(1,param_2 + 4);
        iVar1 = FUN_08006e04(param_2);
        FUN_08006e1a(uVar5,iVar1 + 4);
        return 0;
      }
      return iVar1;
    }
  }
  return 2;
}




/* 0x08009980 */
undefined4 FUN_08009980(param_1, param_2)
int * param_1; int param_2;
{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  if ((param_2 == 1) || (param_2 == 2)) {
    *param_1 = 0;
    FUN_080096d4(param_1,4);
    if (*param_1 != 0) {
      FUN_08006e1a(0);
      FUN_080096d4(*param_1,0xbe);
      iVar3 = *param_1;
      iVar1 = FUN_08006e04(iVar3);
      if (iVar1 == 0) {
        FUN_080096a4(iVar3);
      }
      else {
        FUN_08009614(iVar1,0,0xbe);
        if ((param_2 == 1) || (param_2 == 2)) {
          iVar1 = FUN_08006e04(*param_1);
          FUN_08006e1a(0,iVar1 + 0x60);
          FUN_08006e1a(0,iVar1 + 100);
          FUN_08006e1a(0,iVar1 + 0xba);
          FUN_08009614(iVar1,0,0xbe);
          *(undefined1 *)(iVar1 + 0x76) = 0;
          *(undefined1 *)(iVar1 + 0x77) = 0;
          DAT_87c00a28 = 0;
          *(undefined1 *)(iVar1 + 0x68) = 1;
          FUN_08009614(&DAT_87c00a00,0,0x2c);
          if (param_2 == 1) {
            *(undefined1 *)(iVar1 + 0x78) = 1;
            FUN_08006e1a(0x1234567,iVar1 + 0x40);
            FUN_08006e1a(0x89abcdef,iVar1 + 0x44);
            FUN_08006e1a(0xfedcba98,iVar1 + 0x48);
            FUN_08006e1a(0x76543210,iVar1 + 0x4c);
            uVar2 = 0xf0e1d2c3;
            iVar1 = iVar1 + 0x50;
          }
          else {
            if (param_2 != 2) {
              return 0;
            }
            *(undefined1 *)(iVar1 + 0x78) = 2;
            FUN_08006e1a(0x67e6096a,iVar1 + 0x40);
            FUN_08006e1a(0x85ae67bb,iVar1 + 0x44);
            FUN_08006e1a(0x72f36e3c,iVar1 + 0x48);
            FUN_08006e1a(0x3af54fa5,iVar1 + 0x4c);
            FUN_08006e1a(0x7f520e51,iVar1 + 0x50);
            FUN_08006e1a(0x8c68059b,iVar1 + 0x54);
            FUN_08006e1a(0xabd9831f,iVar1 + 0x58);
            uVar2 = 0x19cde05b;
            iVar1 = iVar1 + 0x5c;
          }
          FUN_08006e1a(uVar2,iVar1);
          return 0;
        }
      }
    }
  }
  return 2;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08009980 */
undefined4 thunk_FUN_08009980(param_1, param_2)
int * param_1; int param_2;
{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  if ((param_2 == 1) || (param_2 == 2)) {
    *param_1 = 0;
    FUN_080096d4(param_1,4);
    if (*param_1 != 0) {
      FUN_08006e1a(0);
      FUN_080096d4(*param_1,0xbe);
      iVar3 = *param_1;
      iVar1 = FUN_08006e04(iVar3);
      if (iVar1 == 0) {
        FUN_080096a4(iVar3);
      }
      else {
        FUN_08009614(iVar1,0,0xbe);
        if ((param_2 == 1) || (param_2 == 2)) {
          iVar1 = FUN_08006e04(*param_1);
          FUN_08006e1a(0,iVar1 + 0x60);
          FUN_08006e1a(0,iVar1 + 100);
          FUN_08006e1a(0,iVar1 + 0xba);
          FUN_08009614(iVar1,0,0xbe);
          *(undefined1 *)(iVar1 + 0x76) = 0;
          *(undefined1 *)(iVar1 + 0x77) = 0;
          DAT_87c00a28 = 0;
          *(undefined1 *)(iVar1 + 0x68) = 1;
          FUN_08009614(&DAT_87c00a00,0,0x2c);
          if (param_2 == 1) {
            *(undefined1 *)(iVar1 + 0x78) = 1;
            FUN_08006e1a(0x1234567,iVar1 + 0x40);
            FUN_08006e1a(0x89abcdef,iVar1 + 0x44);
            FUN_08006e1a(0xfedcba98,iVar1 + 0x48);
            FUN_08006e1a(0x76543210,iVar1 + 0x4c);
            uVar2 = 0xf0e1d2c3;
            iVar1 = iVar1 + 0x50;
          }
          else {
            if (param_2 != 2) {
              return 0;
            }
            *(undefined1 *)(iVar1 + 0x78) = 2;
            FUN_08006e1a(0x67e6096a,iVar1 + 0x40);
            FUN_08006e1a(0x85ae67bb,iVar1 + 0x44);
            FUN_08006e1a(0x72f36e3c,iVar1 + 0x48);
            FUN_08006e1a(0x3af54fa5,iVar1 + 0x4c);
            FUN_08006e1a(0x7f520e51,iVar1 + 0x50);
            FUN_08006e1a(0x8c68059b,iVar1 + 0x54);
            FUN_08006e1a(0xabd9831f,iVar1 + 0x58);
            uVar2 = 0x19cde05b;
            iVar1 = iVar1 + 0x5c;
          }
          FUN_08006e1a(uVar2,iVar1);
          return 0;
        }
      }
    }
  }
  return 2;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08009af4 */
int FUN_08009af4(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  
  uVar7 = 0;
  iVar6 = 0;
  iVar8 = 0;
  uVar10 = 0;
  if ((((param_1 == 0) || (iVar1 = FUN_08006e04(), iVar1 == 0)) || (param_3 != 1)) || (param_2 == 0)
     ) {
    return 2;
  }
  iVar2 = FUN_08006e04(param_2);
  uVar3 = FUN_08006e04(param_2 + 4);
  if (*(char *)(iVar1 + 0x76) == '\x01') {
    *(undefined1 *)(iVar1 + 0x77) = 1;
    if (DAT_87c00a24 < 4) {
      if (DAT_87c00a24 == 0) {
        DAT_87c00a20 = 0;
      }
      else {
        iVar8 = *(int *)(&DAT_87c00a00 + DAT_87c00a20 * 4);
        uVar10 = *(uint *)(&DAT_87c00a10 + DAT_87c00a20 * 4);
      }
      uVar9 = DAT_87c00a24 + DAT_87c00a20 & 3;
      *(int *)(&DAT_87c00a00 + uVar9 * 4) = iVar2;
      *(uint *)(&DAT_87c00a10 + uVar9 * 4) = uVar3;
      if (DAT_87c00a24 != 0) {
        uVar3 = uVar10;
        iVar2 = iVar8;
      }
      DAT_87c00a24 = DAT_87c00a24 + 1;
    }
    else {
      do {
        iVar8 = _DAT_0073a100;
        FUN_0800960a();
      } while (-1 < iVar8 << 0x1e);
      *(undefined1 *)(iVar1 + 0x76) = 0;
      uVar10 = DAT_87c00a20;
      iVar2 = *(int *)(&DAT_87c00a00 + DAT_87c00a20 * 4);
      uVar3 = *(uint *)(&DAT_87c00a10 + DAT_87c00a20 * 4);
      uVar5 = FUN_08006e04(param_2);
      *(undefined4 *)(&DAT_87c00a00 + uVar10 * 4) = uVar5;
      uVar5 = FUN_08006e04(param_2 + 4);
      *(undefined4 *)(&DAT_87c00a10 + DAT_87c00a20 * 4) = uVar5;
      DAT_87c00a20 = DAT_87c00a20 + 1 & 3;
    }
  }
  iVar4 = iVar1 + 0xba;
  uVar10 = FUN_08006e04();
  iVar8 = _DAT_0073a100;
  if (uVar10 + uVar3 < uVar3) {
LAB_08009cc2:
    iVar6 = 1;
    goto LAB_08009db2;
  }
  if (uVar10 + uVar3 < 0x41) {
    if (DAT_87c00a28 == 0) {
      iVar6 = FUN_08009600(uVar10 + iVar1 + 0x7a,iVar2,uVar3);
      bVar11 = iVar6 == 0;
      do {
        if (!bVar11) goto LAB_08009db2;
        iVar8 = FUN_08006e04(iVar4);
        FUN_08006e1a(iVar8 + uVar3,iVar4);
        bVar11 = *(char *)(iVar1 + 0x76) == '\x01';
      } while (!bVar11);
      DAT_87c00a20 = DAT_87c00a20 + 1 & 3;
      DAT_87c00a24 = DAT_87c00a24 - 1;
      goto LAB_08009db2;
    }
LAB_08009c30:
    uVar9 = 0;
    uVar7 = uVar3;
LAB_08009d12:
    iVar8 = _DAT_0073a100;
    if ((*(char *)(iVar1 + 0x76) == '\x01') && (FUN_0800960a(), -1 < iVar8 << 0x1e)) {
      return 0;
    }
  }
  else {
    if (DAT_87c00a28 != 0) goto LAB_08009c30;
    uVar9 = 0x40 - uVar10;
    if ((0x40 < uVar10) || (0x40 < uVar9)) goto LAB_08009cc2;
    if ((*(char *)(iVar1 + 0x76) == '\x01') &&
       ((FUN_0800960a(), -1 < iVar8 << 0x1e && (*(char *)(iVar1 + 0x68) == '\0')))) {
      return 0;
    }
    uVar10 = FUN_08006e04(iVar4);
    if ((uVar10 < 0x40) && (iVar6 = FUN_08009600(uVar10 + iVar1 + 0x7a,iVar2,uVar9), iVar6 != 0))
    goto LAB_08009db2;
    uVar5 = FUN_08006e1a(0x40,iVar4);
    iVar6 = FUN_08009e14(iVar1,iVar1 + 0x7a,uVar5,0);
    if (iVar6 != 0) goto LAB_08009db2;
    if (*(char *)(iVar1 + 0x76) == '\x01') {
      *(uint *)(&DAT_87c00a00 + DAT_87c00a20 * 4) = iVar2 + uVar9;
      *(uint *)(&DAT_87c00a10 + DAT_87c00a20 * 4) = uVar3 - uVar9;
    }
    if (uVar3 < uVar9) goto LAB_08009cc2;
    if (DAT_87c00a28 != 0) goto LAB_08009d12;
    uVar7 = uVar3 - uVar9 & 0xffffffc0;
    uVar10 = uVar3 - uVar9 & 0x3f;
    if (uVar10 == 0) {
      uVar7 = uVar7 - 0x40;
      uVar10 = 0x40;
    }
    iVar6 = FUN_08009600(iVar1 + 0x7a,(uVar3 - uVar10) + iVar2,uVar10);
    if (iVar6 != 0) goto LAB_08009db2;
    FUN_08006e1a(uVar10,iVar4);
    if (*(char *)(iVar1 + 0x76) == '\x01') {
      DAT_87c00a28 = 1;
      *(uint *)(&DAT_87c00a10 + DAT_87c00a20 * 4) = uVar7;
      goto LAB_08009d12;
    }
  }
  if (uVar7 != 0) {
    iVar2 = uVar9 + iVar2;
    do {
      if (uVar7 <= DAT_0804d610) {
        iVar6 = FUN_08009e14(iVar1,iVar2,uVar7,0);
        break;
      }
      iVar6 = FUN_08009e14(iVar1,iVar2,DAT_0804d610,0);
      if (iVar6 != 0) break;
      uVar7 = uVar7 - DAT_0804d610;
      iVar2 = iVar2 + DAT_0804d610;
      if (*(char *)(iVar1 + 0x76) == '\x01') {
        *(int *)(&DAT_87c00a00 + DAT_87c00a20 * 4) = iVar2;
        *(uint *)(&DAT_87c00a10 + DAT_87c00a20 * 4) = uVar7;
        iVar8 = _DAT_0073a100;
        FUN_0800960a();
        if (-1 < iVar8 << 0x1e) {
          return 0;
        }
      }
    } while (uVar7 != 0);
  }
  if (*(char *)(iVar1 + 0x76) == '\x01') {
    DAT_87c00a24 = DAT_87c00a24 - 1;
    DAT_87c00a20 = DAT_87c00a20 + 1 & 3;
  }
LAB_08009db2:
  DAT_87c00a28 = 0;
  if (*(char *)(iVar1 + 0x77) == '\x01') {
    *(undefined1 *)(iVar1 + 0x77) = 0;
    *(undefined1 *)(iVar1 + 0x76) = 1;
  }
  return iVar6;
}




/* 0x08009af4 */
int thunk_FUN_08009af4(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  
  uVar7 = 0;
  iVar6 = 0;
  iVar8 = 0;
  uVar10 = 0;
  if ((((param_1 == 0) || (iVar1 = FUN_08006e04(), iVar1 == 0)) || (param_3 != 1)) || (param_2 == 0)
     ) {
    return 2;
  }
  iVar2 = FUN_08006e04(param_2);
  uVar3 = FUN_08006e04(param_2 + 4);
  if (*(char *)(iVar1 + 0x76) == '\x01') {
    *(undefined1 *)(iVar1 + 0x77) = 1;
    if (DAT_87c00a24 < 4) {
      if (DAT_87c00a24 == 0) {
        DAT_87c00a20 = 0;
      }
      else {
        iVar8 = *(int *)(&DAT_87c00a00 + DAT_87c00a20 * 4);
        uVar10 = *(uint *)(&DAT_87c00a10 + DAT_87c00a20 * 4);
      }
      uVar9 = DAT_87c00a24 + DAT_87c00a20 & 3;
      *(int *)(&DAT_87c00a00 + uVar9 * 4) = iVar2;
      *(uint *)(&DAT_87c00a10 + uVar9 * 4) = uVar3;
      if (DAT_87c00a24 != 0) {
        uVar3 = uVar10;
        iVar2 = iVar8;
      }
      DAT_87c00a24 = DAT_87c00a24 + 1;
    }
    else {
      do {
        iVar8 = _DAT_0073a100;
        FUN_0800960a();
      } while (-1 < iVar8 << 0x1e);
      *(undefined1 *)(iVar1 + 0x76) = 0;
      uVar10 = DAT_87c00a20;
      iVar2 = *(int *)(&DAT_87c00a00 + DAT_87c00a20 * 4);
      uVar3 = *(uint *)(&DAT_87c00a10 + DAT_87c00a20 * 4);
      uVar5 = FUN_08006e04(param_2);
      *(undefined4 *)(&DAT_87c00a00 + uVar10 * 4) = uVar5;
      uVar5 = FUN_08006e04(param_2 + 4);
      *(undefined4 *)(&DAT_87c00a10 + DAT_87c00a20 * 4) = uVar5;
      DAT_87c00a20 = DAT_87c00a20 + 1 & 3;
    }
  }
  iVar4 = iVar1 + 0xba;
  uVar10 = FUN_08006e04();
  iVar8 = _DAT_0073a100;
  if (uVar10 + uVar3 < uVar3) {
LAB_08009cc2:
    iVar6 = 1;
    goto LAB_08009db2;
  }
  if (uVar10 + uVar3 < 0x41) {
    if (DAT_87c00a28 == 0) {
      iVar6 = FUN_08009600(uVar10 + iVar1 + 0x7a,iVar2,uVar3);
      bVar11 = iVar6 == 0;
      do {
        if (!bVar11) goto LAB_08009db2;
        iVar8 = FUN_08006e04(iVar4);
        FUN_08006e1a(iVar8 + uVar3,iVar4);
        bVar11 = *(char *)(iVar1 + 0x76) == '\x01';
      } while (!bVar11);
      DAT_87c00a20 = DAT_87c00a20 + 1 & 3;
      DAT_87c00a24 = DAT_87c00a24 - 1;
      goto LAB_08009db2;
    }
LAB_08009c30:
    uVar9 = 0;
    uVar7 = uVar3;
LAB_08009d12:
    iVar8 = _DAT_0073a100;
    if ((*(char *)(iVar1 + 0x76) == '\x01') && (FUN_0800960a(), -1 < iVar8 << 0x1e)) {
      return 0;
    }
  }
  else {
    if (DAT_87c00a28 != 0) goto LAB_08009c30;
    uVar9 = 0x40 - uVar10;
    if ((0x40 < uVar10) || (0x40 < uVar9)) goto LAB_08009cc2;
    if ((*(char *)(iVar1 + 0x76) == '\x01') &&
       ((FUN_0800960a(), -1 < iVar8 << 0x1e && (*(char *)(iVar1 + 0x68) == '\0')))) {
      return 0;
    }
    uVar10 = FUN_08006e04(iVar4);
    if ((uVar10 < 0x40) && (iVar6 = FUN_08009600(uVar10 + iVar1 + 0x7a,iVar2,uVar9), iVar6 != 0))
    goto LAB_08009db2;
    uVar5 = FUN_08006e1a(0x40,iVar4);
    iVar6 = FUN_08009e14(iVar1,iVar1 + 0x7a,uVar5,0);
    if (iVar6 != 0) goto LAB_08009db2;
    if (*(char *)(iVar1 + 0x76) == '\x01') {
      *(uint *)(&DAT_87c00a00 + DAT_87c00a20 * 4) = iVar2 + uVar9;
      *(uint *)(&DAT_87c00a10 + DAT_87c00a20 * 4) = uVar3 - uVar9;
    }
    if (uVar3 < uVar9) goto LAB_08009cc2;
    if (DAT_87c00a28 != 0) goto LAB_08009d12;
    uVar7 = uVar3 - uVar9 & 0xffffffc0;
    uVar10 = uVar3 - uVar9 & 0x3f;
    if (uVar10 == 0) {
      uVar7 = uVar7 - 0x40;
      uVar10 = 0x40;
    }
    iVar6 = FUN_08009600(iVar1 + 0x7a,(uVar3 - uVar10) + iVar2,uVar10);
    if (iVar6 != 0) goto LAB_08009db2;
    FUN_08006e1a(uVar10,iVar4);
    if (*(char *)(iVar1 + 0x76) == '\x01') {
      DAT_87c00a28 = 1;
      *(uint *)(&DAT_87c00a10 + DAT_87c00a20 * 4) = uVar7;
      goto LAB_08009d12;
    }
  }
  if (uVar7 != 0) {
    iVar2 = uVar9 + iVar2;
    do {
      if (uVar7 <= DAT_0804d610) {
        iVar6 = FUN_08009e14(iVar1,iVar2,uVar7,0);
        break;
      }
      iVar6 = FUN_08009e14(iVar1,iVar2,DAT_0804d610,0);
      if (iVar6 != 0) break;
      uVar7 = uVar7 - DAT_0804d610;
      iVar2 = iVar2 + DAT_0804d610;
      if (*(char *)(iVar1 + 0x76) == '\x01') {
        *(int *)(&DAT_87c00a00 + DAT_87c00a20 * 4) = iVar2;
        *(uint *)(&DAT_87c00a10 + DAT_87c00a20 * 4) = uVar7;
        iVar8 = _DAT_0073a100;
        FUN_0800960a();
        if (-1 < iVar8 << 0x1e) {
          return 0;
        }
      }
    } while (uVar7 != 0);
  }
  if (*(char *)(iVar1 + 0x76) == '\x01') {
    DAT_87c00a24 = DAT_87c00a24 - 1;
    DAT_87c00a20 = DAT_87c00a20 + 1 & 3;
  }
LAB_08009db2:
  DAT_87c00a28 = 0;
  if (*(char *)(iVar1 + 0x77) == '\x01') {
    *(undefined1 *)(iVar1 + 0x77) = 0;
    *(undefined1 *)(iVar1 + 0x76) = 1;
  }
  return iVar6;
}




/* 0x08009de0 */
void FUN_08009de0()
{
  int iVar1;
  uint in_r3 = 0;
  uint local_8;
  
  local_8 = in_r3;
  iVar1 = thunk_FUN_08009480();
  if (iVar1 == 0) {
    if (DAT_0804d60c == '\0') {
      DAT_0804d60c = '\x01';
      iVar1 = FUN_080095fc();
      if (iVar1 != 0) {
        return;
      }
    }
    iVar1 = FUN_080095d2(&local_8);
    if (iVar1 == 0) {
      FUN_08009548(local_8 & 0xff);
    }
  }
  return;
}




/* 0x08009de0 */
undefined4 thunk_FUN_08009de0()
{
  int iVar1;
  uint in_r3 = 0;
  uint uStack_8;
  
  uStack_8 = in_r3;
  iVar1 = thunk_FUN_08009480();
  if (iVar1 == 0) {
    if (DAT_0804d60c == '\0') {
      DAT_0804d60c = '\x01';
      iVar1 = FUN_080095fc();
      if (iVar1 != 0) {
        return 0;
      }
    }
    iVar1 = FUN_080095d2(&uStack_8);
    if (iVar1 == 0) {
      FUN_08009548(uStack_8 & 0xff);
    }
  }
  return 0;
}




/* 0x08009e14 */
int FUN_08009e14(param_1, param_2, param_3, param_4)
int param_1; int param_2; uint param_3; int param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined1 *local_50;
  undefined4 uStack_4c;
  undefined1 *local_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined1 local_3c [4];
  code *local_38;
  undefined1 auStack_34 [4];
  undefined1 auStack_30 [4];
  undefined1 auStack_2c [12];
  
  local_40 = 0;
  if ((param_1 == 0) || (param_2 == 0)) {
    return 2;
  }
  if (param_4 == 1) {
    *(undefined1 *)(param_1 + 0x69) = 1;
  }
  else {
    *(undefined1 *)(param_1 + 0x69) = 0;
  }
  FUN_08006e1a(param_3,param_1 + 0x6a);
  iVar1 = FUN_080094e6(2,param_1,0x7a,0,0,&local_40);
  if (iVar1 != 0) {
    return iVar1;
  }
  if ((param_3 & 0xf) != 0) {
    param_3 = param_3 + (0x10 - (param_3 & 0xf));
  }
  local_48 = auStack_34;
  uStack_44 = 1;
  FUN_08006e1a(param_2,local_48);
  FUN_08006e1a(param_3,auStack_30);
  local_50 = auStack_2c;
  uStack_4c = 1;
  FUN_08006e1a(param_1 + 0x40);
  if (*(char *)(param_1 + 0x78) == '\x01') {
    uVar2 = 0x14;
  }
  else {
    if (*(char *)(param_1 + 0x78) != '\x02') goto LAB_08009ebe;
    uVar2 = 0x20;
  }
  FUN_08006e1a(uVar2,local_50 + 4);
LAB_08009ebe:
  iVar1 = FUN_080095d2(local_3c);
  if ((((iVar1 == 0) && (iVar1 = FUN_080095dc(local_3c[0],&local_38), iVar1 == 0)) &&
      (iVar1 = (*local_38)(&local_48,&local_50,param_4,param_1,1), iVar1 == 0)) &&
     ((local_40 = 0x7a, *(char *)(param_1 + 0x76) == '\0' || (*(char *)(param_1 + 0x69) == '\x01')))
     ) {
    iVar1 = FUN_080094e6(3,0,0,param_1,0x7a,&local_40);
  }
  return iVar1;
}




/* 0x08009f10 */
int FUN_08009f10(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 * param_3;
{
  int iVar1;
  
  *param_3 = 0;
  iVar1 = FUN_0800b1b6(param_2,&DAT_08050ee0,&DAT_0805a3a8);
  if (iVar1 == 0) {
    DAT_0805a3b8 = 0xda1fda1f;
    DAT_0805a3bc = &PTR_FUN_08009f10_1_0803d454;
    DAT_0805a3c0 = &DAT_0805a3a8;
    FUN_0800b19a();
    *param_3 = &DAT_0805a3b8;
  }
  return iVar1;
}




/* 0x08009fa4 */
undefined4 FUN_08009fa4(param_1)
int param_1;
{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 8) + 0xc);
  thunk_FUN_08010668(*(undefined4 *)(iVar1 + 4),iVar1 + 0x10);
  return 0;
}




/* 0x08009fda */
undefined4 FUN_08009fda(param_1)
int param_1;
{
  if (*(uint *)(param_1 + 0xa0) != 0) {
    (**(code **)(*(int *)((*(uint *)(param_1 + 0xa0) & 0xfffffffe) + 4) + 0x14))();
  }
  return 0;
}




/* 0x08009ff0 */
undefined4 FUN_08009ff0(param_1)
int param_1;
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  undefined4 *local_3c [2];
  undefined4 *local_34 [2];
  undefined4 *local_2c;
  undefined1 auStack_28 [8];
  undefined4 *local_20;
  
  iVar6 = param_1 + 0xa4;
  iVar7 = 0;
  local_2c = (undefined4 *)0x0;
  local_34[0] = (undefined4 *)0x0;
  local_3c[0] = (undefined4 *)0x0;
  thunk_FUN_08010668(0x200006f);
  thunk_FUN_080106aa(iVar6,"HWREVNUM_PHYS_ADDR",0,auStack_28);
  puVar9 = local_20;
  thunk_FUN_080106aa(iVar6,"SOC_HW_VERSION_PHYS_ADDR",0,auStack_28);
  puVar2 = local_20;
  thunk_FUN_080106aa(iVar6,"FOUNDRY_PHYS_ADDR",0,auStack_28);
  puVar3 = local_20;
  iVar4 = FUN_0800b7b4(0x2000070,param_1 + 0xa0);
  if (iVar4 == 0) {
    puVar1 = (undefined4 *)(param_1 + 0xa0);
    FUN_0800bb16(*puVar1,puVar9,&local_2c);
    FUN_0800bb16(*puVar1,puVar2,local_34);
    FUN_0800bb16(*puVar1,puVar3,local_3c);
  }
  else {
    local_3c[0] = puVar3;
    local_34[0] = puVar2;
    local_2c = puVar9;
  }
  thunk_FUN_080106aa(iVar6,"HWREVNUM_OFFSET",0,auStack_28);
  local_2c = (undefined4 *)((int)local_2c + (int)local_20);
  thunk_FUN_080106aa(iVar6,"SOC_HW_VERSION_OFFSET",0,auStack_28);
  local_34[0] = (undefined4 *)((int)local_20 + (int)local_34[0]);
  thunk_FUN_080106aa(iVar6,"SERIALNUM_OFFSET",0,auStack_28);
  puVar9 = (undefined4 *)((int)local_20 + (int)local_3c[0]);
  thunk_FUN_080106aa(iVar6,"FOUNDRY_OFFSET",0,auStack_28);
  local_3c[0] = (undefined4 *)((int)local_20 + (int)local_3c[0]);
  uVar8 = *local_3c[0];
  uVar10 = *local_2c;
  FUN_0800a474(param_1,param_1 + 0x7c,*local_34[0]);
  FUN_0800a378(param_1,param_1 + 0x70,uVar10);
  FUN_0800a418(param_1,param_1 + 0x80,uVar10);
  FUN_0800a3cc(param_1,param_1 + 0x84,uVar10);
  FUN_0800a270(param_1,param_1 + 0x78,uVar10);
  FUN_0800a304(param_1,param_1 + 0x74,uVar8);
  *(undefined4 *)(param_1 + 0x88) = *puVar9;
  if ((*(int *)(param_1 + 0x70) == 0) &&
     (iVar4 = thunk_FUN_080106aa(iVar6,"ChipIdOverride",0,auStack_28), iVar4 == 0)) {
    *(undefined4 **)(param_1 + 0x70) = local_20;
    FUN_0800a2bc(local_20,param_1 + 0x78);
    *(undefined4 *)(param_1 + 0x7c) = 0x10000;
  }
  uVar5 = 0;
  do {
    if (*(int *)(param_1 + 0x70) == (&DAT_0805133c)[uVar5 * 2]) {
      iVar7 = (&DAT_08051340)[uVar5 * 2];
      break;
    }
    uVar5 = uVar5 + 1;
  } while (uVar5 < 0x1e);
  if (uVar5 == 0x1e) {
    iVar7 = 0;
  }
  *(undefined4 *)(param_1 + 0x8c) = (&DAT_0803db24)[iVar7 * 3];
  FUN_080382c2(param_1 + 0x90,(&DAT_0803db1c)[iVar7 * 3],0x10);
  return 0;
}




/* 0x0800a250 */
undefined4 FUN_0800a250(param_1, param_2)
int param_1; undefined4 param_2;
{
  FUN_080382c2(param_2,*(int *)(*(int *)(param_1 + 0xc) + 0xc) + 0x90);
  return 0;
}




/* 0x0800a270 */
void FUN_0800a270(param_1, param_2, param_3, param_4)
undefined4 param_1; uint * param_2; undefined4 param_3; uint param_4;
{
  uint uVar1;
  int iVar2;
  uint local_10;
  
  iVar2 = 0;
  local_10 = param_4;
  FUN_0800a378(param_1,&local_10);
  uVar1 = 0;
  if (local_10 < 0x117) {
    do {
      if ((&DAT_0805133c)[uVar1 * 2] == local_10) {
        iVar2 = (&DAT_08051340)[uVar1 * 2];
        break;
      }
      uVar1 = uVar1 + 1;
    } while (uVar1 < 0x1e);
    if (uVar1 == 0x1e) {
      iVar2 = 0;
    }
    uVar1 = (&DAT_0803db20)[iVar2 * 3];
  }
  *param_2 = uVar1;
  return;
}




/* 0x0800a2bc */
void FUN_0800a2bc(param_1, param_2)
uint param_1; undefined4 * param_2;
{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = 0;
  if (param_1 < 0x117) {
    uVar2 = 0;
    do {
      if ((&DAT_0805133c)[uVar2 * 2] == param_1) {
        iVar3 = (&DAT_08051340)[uVar2 * 2];
        break;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < 0x1e);
    if (uVar2 == 0x1e) {
      iVar3 = 0;
    }
    uVar1 = (&DAT_0803db20)[iVar3 * 3];
  }
  else {
    uVar1 = 0;
  }
  *param_2 = uVar1;
  return;
}




/* 0x0800a304 */
void FUN_0800a304(param_1, param_2, param_3, param_4)
int param_1; int * param_2; uint param_3; uint param_4;
{
  uint uVar1;
  int *piStack_20;
  uint uStack_1c;
  uint local_18;
  
  piStack_20 = param_2;
  uStack_1c = param_3;
  local_18 = param_4;
  thunk_FUN_080106aa(param_1 + 0xa4,"FOUNDRY_BMSK",0,&piStack_20);
  uVar1 = local_18;
  thunk_FUN_080106aa(param_1 + 0xa4,"FOUNDRY_SHFT",0,&piStack_20);
  uVar1 = (param_3 & uVar1) >> (local_18 & 0xff);
  if (4 < uVar1) {
    *param_2 = 0;
    return;
  }
  *param_2 = uVar1 + 1;
  return;
}




/* 0x0800a378 */
void FUN_0800a378(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 * param_2; undefined4 param_3; int param_4;
{
  uint uVar1;
  int local_10;
  
  local_10 = param_4;
  FUN_0800a3cc(param_1,&local_10);
  uVar1 = 0;
  do {
    if ((&DAT_08051254)[uVar1 * 2] == local_10) {
      *param_2 = (&DAT_08051258)[uVar1 * 2];
      break;
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 < 0x1d);
  if (uVar1 == 0x1d) {
    *param_2 = 0;
  }
  return;
}




/* 0x0800a3cc */
void FUN_0800a3cc(param_1, param_2, param_3, param_4)
int param_1; uint * param_2; uint param_3; uint param_4;
{
  uint uVar1;
  uint *puStack_20;
  uint uStack_1c;
  uint local_18;
  
  puStack_20 = param_2;
  uStack_1c = param_3;
  local_18 = param_4;
  thunk_FUN_080106aa(param_1 + 0xa4,"PARTNUM_BMSK",0,&puStack_20);
  uVar1 = local_18;
  thunk_FUN_080106aa(param_1 + 0xa4,"PARTNUM_SHFT",0,&puStack_20);
  *param_2 = (param_3 & uVar1) >> (local_18 & 0xff);
  return;
}




/* 0x0800a418 */
void FUN_0800a418(param_1, param_2, param_3, param_4)
int param_1; uint * param_2; uint param_3; uint param_4;
{
  uint uVar1;
  uint *puStack_20;
  uint uStack_1c;
  uint local_18;
  
  puStack_20 = param_2;
  uStack_1c = param_3;
  local_18 = param_4;
  thunk_FUN_080106aa(param_1 + 0xa4,"VERSION_ID_BMSK",0,&puStack_20);
  uVar1 = local_18;
  thunk_FUN_080106aa(param_1 + 0xa4,"VERSION_ID_SHFT",0,&puStack_20);
  *param_2 = (param_3 & uVar1) >> (local_18 & 0xff);
  return;
}




/* 0x0800a474 */
void FUN_0800a474(param_1, param_2, param_3, param_4)
int param_1; uint * param_2; uint param_3; uint param_4;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint *puStack_28;
  uint uStack_24;
  uint local_20;
  
  param_1 = param_1 + 0xa4;
  puStack_28 = param_2;
  uStack_24 = param_3;
  local_20 = param_4;
  thunk_FUN_080106aa(param_1,"MAJOR_VERSION_BMSK",0,&puStack_28);
  uVar3 = local_20;
  thunk_FUN_080106aa(param_1,"MAJOR_VERSION_SHFT",0,&puStack_28);
  uVar1 = local_20;
  thunk_FUN_080106aa(param_1,"MINOR_VERSION_BMSK",0,&puStack_28);
  uVar2 = local_20;
  thunk_FUN_080106aa(param_1,"MINOR_VERSION_SHFT",0,&puStack_28);
  uVar3 = (param_3 & uVar3) >> (uVar1 & 0xff);
  if (uVar3 == 0) {
    uVar3 = 1;
  }
  *param_2 = (param_3 & uVar2) >> (local_20 & 0xff) | uVar3 << 0x10;
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800a52c */
void FUN_0800a52c()
{
  _DAT_01831018 = _DAT_01831018 & 0x3f0e00;
  FUN_0800b140(0x181f004,1);
  return;
}




/* 0x0800a54c */
undefined4 FUN_0800a54c(param_1)
undefined4 * param_1;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  uint local_18;
  
  local_18 = 0;
  iVar1 = FUN_0800b124(param_1,&local_18);
  if (iVar1 != 0) {
    puVar4 = (uint *)*param_1;
    uVar2 = param_1[2];
    if (uVar2 != 0) {
      uVar2 = uVar2 - 1;
    }
    uVar2 = uVar2 & 0x1f | (local_18 & 7) << 8 | puVar4[1] & 0xffffc8e0;
    uVar3 = param_1[3];
    if ((uVar3 != 0) && (uVar3 < (uint)param_1[4])) {
      puVar4[2] = uVar3;
      puVar4[3] = ~(param_1[4] - param_1[3]);
      puVar4[4] = ~param_1[5];
      uVar2 = uVar2 | 0x2000;
    }
    puVar4[1] = uVar2;
    *puVar4 = *puVar4 | 1;
    uVar2 = 0;
    while( true ) {
      if ((*puVar4 & 1) == 0) {
        return 1;
      }
      if (999 < uVar2) break;
      FUN_080199b4(1);
      uVar2 = uVar2 + 1;
    }
  }
  return 0;
}




/* 0x0800a5d0 */
undefined4 FUN_0800a5d0(param_1)
int * param_1;
{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  
  puVar2 = (uint *)*param_1;
  uVar4 = *puVar2;
  if (((~uVar4 & 7) == 0) ||
     ((((int)(uVar4 << 0xb) < 0 && ((uint *)param_1[1] != (uint *)0x0)) &&
      ((*(uint *)param_1[1] & param_1[2]) != 0)))) {
    return 0;
  }
  iVar1 = param_1[0xc];
  puVar2[1] = param_1[6];
  if ((char)iVar1 == '\x02') {
    puVar2[2] = param_1[10];
    puVar2[3] = param_1[0xb];
    uVar3 = puVar2[4] & 0xfecf8cff | param_1[3] << 0x14;
    if (param_1[4] - 1U < 8) {
      uVar3 = uVar3 | param_1[4] * 0x1000 - 0x1000U;
    }
    if (param_1[5] == 2) {
      uVar3 = uVar3 | 0x100;
    }
    else if (param_1[5] == 4) {
      uVar3 = uVar3 | 0x300;
    }
    if (param_1[10] == 0 && param_1[0xb] == 0) goto LAB_0800a684;
  }
  else {
    puVar2[2] = param_1[7];
    puVar2[3] = param_1[8];
    uVar3 = puVar2[4] & 0xfecf8cff | param_1[3] << 0x14;
    if (param_1[4] - 1U < 8) {
      uVar3 = uVar3 | param_1[4] * 0x1000 - 0x1000U;
    }
    if (param_1[5] == 2) {
      uVar3 = uVar3 | 0x100;
    }
    else if (param_1[5] == 4) {
      uVar3 = uVar3 | 0x300;
    }
    if ((param_1[7] == 0) || ((uint)param_1[8] <= (uint)param_1[7])) goto LAB_0800a684;
  }
  uVar3 = uVar3 | 0x1000000;
LAB_0800a684:
  puVar2[4] = uVar3 | 1;
  uVar3 = uVar4 & 0xfff000ff | 0x4000;
  if (param_1[1] != 0) {
    uVar3 = uVar4 & 0xfff000ff | 0x104000;
  }
  *puVar2 = uVar3;
  if ((char)param_1[0xc] == '\x02') {
    puVar2[6] = param_1[9];
  }
  else {
    puVar2[5] = param_1[9];
  }
  return 1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800a6bc */
undefined4 FUN_0800a6bc(param_1)
int param_1;
{
  undefined4 uVar1;
  undefined1 *puVar2;
  uint uVar3;
  
  if (param_1 == 3) {
    if (1 < (uint)(_DAT_0194d000 << 0x10) >> 0x18) {
      _DAT_01825020 = _DAT_01825020 & 0xff3fffff | 0x400000;
    }
    FUN_0800a5d0(&DAT_0804d6d8);
    _DAT_01825010 = _DAT_01825010 | 2;
LAB_0800a742:
    if (1 < (uint)(_DAT_0194d000 << 0x10) >> 0x18) {
      _DAT_01823020 = _DAT_01823020 & 0xff3fffff | 0x400000;
    }
    uVar1 = FUN_0800a5d0(&DAT_0804d710);
    _DAT_01823010 = _DAT_01823010 | 8;
    return uVar1;
  }
  if (param_1 < 4) {
    if (param_1 == 0) {
      return 1;
    }
    if (param_1 == 1) {
      uVar1 = FUN_0800a5d0(&DAT_0804d668);
      puVar2 = &DAT_01821000;
      uVar3 = _DAT_01821010 | 2;
      goto LAB_0800a700;
    }
    if (param_1 != 2) {
      return 0;
    }
    uVar1 = FUN_0800a5d0(&DAT_0804d6a0);
    puVar2 = (undefined1 *)0x1820000;
    _DAT_01820010 = _DAT_01820010 | 2;
  }
  else {
    if (param_1 == 7) goto LAB_0800a742;
    if (param_1 != 0x18) {
      return 0;
    }
    uVar1 = FUN_0800a5d0(&DAT_0804d748);
    puVar2 = &DAT_0b016000;
  }
  uVar3 = *(uint *)(puVar2 + 0x10) | 8;
LAB_0800a700:
  *(uint *)(puVar2 + 0x10) = uVar3;
  return uVar1;
}




/* 0x0800a784 */
undefined4 FUN_0800a784()
{
  return DAT_0804d270;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800a784 */
undefined4 thunk_FUN_0800a784()
{
  return DAT_0804d270;
}




/* 0x0800a790 */
undefined4 FUN_0800a790()
{
  _DAT_01830038 = 1;
  _DAT_01845004 = _DAT_01845004 & 0x3f7ff | 0x100;
  _DAT_01836004 = _DAT_01836004 & 0x3f7ff | 0x40;
  return 1;
}




/* 0x0800a790 */
undefined4 thunk_FUN_0800a790()
{
  _DAT_01830038 = 1;
  _DAT_01845004 = _DAT_01845004 & 0x3f7ff | 0x100;
  _DAT_01836004 = _DAT_01836004 & 0x3f7ff | 0x40;
  return 1;
}




/* 0x0800a7c4 */
undefined4 FUN_0800a7c4(param_1)
uint param_1;
{
  if (6 < param_1) {
    return 0;
  }
  FUN_0800b140(*(undefined4 *)(&DAT_0803986c + param_1 * 8),0);
  return 1;
}




/* 0x0800a7e4 */
undefined4 FUN_0800a7e4(param_1)
int param_1;
{
  undefined4 uVar1;
  
  if (param_1 == 1) {
    uVar1 = 0x180203c;
  }
  else {
    if (param_1 != 2) {
      return 0;
    }
    uVar1 = 0x180302c;
  }
  FUN_0800b140(uVar1,0);
  return 1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800a7e4 */
undefined4 thunk_FUN_0800a7e4(param_1)
int param_1;
{
  undefined4 uVar1;
  
  if (param_1 == 1) {
    uVar1 = 0x180203c;
  }
  else {
    if (param_1 != 2) {
      return 0;
    }
    uVar1 = 0x180302c;
  }
  FUN_0800b140(uVar1,0);
  return 1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800a80c */
undefined4 FUN_0800a80c()
{
  int iVar1;
  undefined1 auStack_20 [28];
  
  FUN_08006bdc(auStack_20,&DAT_08039948,0x18);
  if (-1 < _DAT_01841004) {
    iVar1 = FUN_0800a54c(auStack_20);
    if (iVar1 == 0) {
      return 0;
    }
    FUN_0800b140(&DAT_01841004,0);
    FUN_0800b140(0x1841008,0);
    FUN_0800b140(0x1841030,0);
  }
  return 1;
}




/* 0x0800a80c */
undefined4 thunk_FUN_0800a80c()
{
  int iVar1;
  undefined1 auStack_20 [28];
  
  FUN_08006bdc(auStack_20,&DAT_08039948,0x18);
  if (-1 < _DAT_01841004) {
    iVar1 = FUN_0800a54c(auStack_20);
    if (iVar1 == 0) {
      return 0;
    }
    FUN_0800b140(&DAT_01841004,0);
    FUN_0800b140(0x1841008,0);
    FUN_0800b140(0x1841030,0);
  }
  return 1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800a85c */
undefined4 FUN_0800a85c(param_1)
undefined4 * param_1;
{
  int iVar1;
  uint *puVar2;
  undefined4 uVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  puVar6 = (uint *)*param_1;
  uVar4 = 0;
  if (*(char *)(param_1 + 0xc) == '\x02') {
    uVar7 = 0x40000000;
    uVar9 = 0x80000000;
    puVar5 = puVar6;
  }
  else {
    uVar7 = 0x20000;
    uVar9 = 0x10000;
    puVar5 = puVar6 + 7;
  }
  uVar8 = *puVar6;
  if (((~uVar8 & 7) == 0) || ((int)(uVar8 << 0xb) < 0)) {
    puVar6 = (uint *)param_1[1];
    if (puVar6 != (uint *)0x0) {
      *puVar6 = *puVar6 | param_1[2];
      while ((*puVar5 & uVar7) == 0) {
        if (199 < uVar4) {
          return 0;
        }
        FUN_080199b4(1);
        uVar4 = uVar4 + 1;
      }
    }
  }
  else {
    iVar1 = FUN_0800a5d0(param_1);
    if (iVar1 == 0) {
      return 0;
    }
    puVar2 = (uint *)param_1[1];
    if (puVar2 == (uint *)0x0) {
      *puVar6 = uVar8 | 2;
      FUN_080199b4(5);
      *puVar6 = uVar8 | 6;
      uVar3 = 0x32;
      while (FUN_080199b4(uVar3), (*puVar5 & uVar9) == 0) {
        if (199 < uVar4) {
          return 0;
        }
        uVar3 = 1;
        uVar4 = uVar4 + 1;
      }
      *puVar6 = uVar8 | 7;
    }
    else {
      *puVar2 = *puVar2 | param_1[2];
      while ((*puVar5 & uVar7) == 0) {
        if (199 < uVar4) {
          return 0;
        }
        FUN_080199b4(1);
        uVar4 = uVar4 + 1;
      }
    }
  }
  return 1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800a92c */
undefined4 FUN_0800a92c(param_1)
int param_1;
{
  undefined4 uVar1;
  undefined *puVar2;
  
  uVar1 = 0;
  if (param_1 == 3) {
    if (1 < (uint)(_DAT_0194d000 << 0x10) >> 0x18) {
      _DAT_01825020 = _DAT_01825020 & 0xff3fffff | 0x400000;
    }
    puVar2 = &DAT_0804d6d8;
  }
  else {
    if (3 < param_1) {
      if (param_1 != 7) {
        if (param_1 == 0x18) {
          uVar1 = FUN_0800a85c(&DAT_0804d748);
          _DAT_0b016010 = _DAT_0b016010 | 8;
        }
        return uVar1;
      }
      if (1 < (uint)(_DAT_0194d000 << 0x10) >> 0x18) {
        _DAT_01823020 = _DAT_01823020 & 0xff3fffff | 0x400000;
      }
      uVar1 = FUN_0800a85c(&DAT_0804d710);
      _DAT_01823010 = _DAT_01823010 | 8;
      return uVar1;
    }
    if (param_1 == 0) {
      return 1;
    }
    if (param_1 == 1) {
      puVar2 = &DAT_0804d668;
    }
    else {
      if (param_1 != 2) {
        return 0;
      }
      puVar2 = &DAT_0804d6a0;
    }
  }
  uVar1 = FUN_0800a85c(puVar2);
  return uVar1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800a9d0 */
bool FUN_0800a9d0()
{
  int iVar1;
  
  iVar1 = FUN_0800aa18();
  if (iVar1 != 0) {
    _DAT_01845004 = _DAT_01845004 & 0x3f2f8;
  }
  return iVar1 != 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800a9d0 */
bool thunk_FUN_0800a9d0()
{
  int iVar1;
  
  iVar1 = FUN_0800aa18();
  if (iVar1 != 0) {
    _DAT_01845004 = _DAT_01845004 & 0x3f2f8;
  }
  return iVar1 != 0;
}




/* 0x0800aa18 */
undefined4 FUN_0800aa18()
{
  int iVar1;
  int local_10;
  
  local_10 = 0;
  iVar1 = FUN_0800b7b4(0x2000020,&local_10);
  if (iVar1 == 0) {
    _DAT_0110e000 = _DAT_0110e000 | 1;
    iVar1 = (**(code **)(*(int *)(local_10 + 4) + 0x24))(local_10,0x2061c5d0,0);
    FUN_0800b874(local_10);
    if (iVar1 == 0) {
      return 1;
    }
  }
  return 0;
}




/* 0x0800aa5c */
undefined4 FUN_0800aa5c()
{
  return 1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800aa5c */
undefined4 thunk_FUN_0800aa5c()
{
  return 1;
}




/* 0x0800aa60 */
undefined4 FUN_0800aa60(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; int param_4;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int local_18;
  
  local_18 = param_4;
  iVar1 = FUN_0800ae0c();
  iVar2 = FUN_0800ae14(param_2);
  uVar3 = 0;
  if (iVar2 != 0) {
    iVar2 = FUN_0800b008(param_1);
    uVar3 = 0;
    if (iVar2 != 0) {
      iVar2 = FUN_0800ab3c();
      uVar3 = 0;
      if (iVar2 != 0) {
        FUN_0800a6bc(1);
        FUN_0800a6bc(2);
        FUN_0800a6bc(3);
        if ((DAT_0804d274 == 0) &&
           (iVar2 = FUN_0800b7ea(0,0x200006f,0x10000,&DAT_0804d274), iVar2 != 0)) {
          DAT_0804d278 = 0;
        }
        else if ((DAT_0804d274 & 1) == 0) {
          (**(code **)(*(int *)(DAT_0804d274 + 4) + 0x2c))(DAT_0804d274,0);
          DAT_0804d278 = local_18;
        }
        else {
          (**(code **)(*(int *)((DAT_0804d274 & 0xfffffffe) + 4) + 0x2c))
                    (0xb,DAT_0804d274 & 0xfffffffe,0,&local_18);
          DAT_0804d278 = local_18;
        }
        if (DAT_0804d278 != 0x103) {
          FUN_0800a6bc(7);
        }
        FUN_0800a6bc(0x18);
        FUN_0800add0();
        FUN_0800b140(0x184102c,1);
        if ((_DAT_0182d014 & 0x700) == 0) {
          iVar2 = FUN_0800a92c(*(undefined1 *)(iVar1 + 0x4a5));
          if (iVar2 == 0) {
            return 0;
          }
          iVar1 = FUN_0800a54c(iVar1 + 0x4a0);
          if (iVar1 == 0) {
            return 0;
          }
        }
        iVar1 = FUN_0800adb4();
        uVar3 = 0;
        if (iVar1 != 0) {
          uVar3 = 1;
        }
      }
    }
  }
  return uVar3;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800ab3c */
undefined4 FUN_0800ab3c()
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_0800ae0c();
  iVar2 = FUN_0800a92c(*(undefined1 *)(iVar1 + 0x3fd));
  uVar3 = 0;
  if ((iVar2 != 0) && (iVar1 = FUN_0800a54c(iVar1 + 0x3f8), uVar3 = 0, iVar1 != 0)) {
    _DAT_01845004 = _DAT_01845004 & 0x3f7ff | 7;
    uVar3 = 1;
  }
  return uVar3;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800abf4 */
undefined4 FUN_0800abf4()
{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0800ae0c();
  if ((_DAT_01841004 & 1) == 0) {
    iVar2 = FUN_0800a92c(*(undefined1 *)(iVar1 + 0x415));
    if (iVar2 == 0) {
      return 0;
    }
    iVar1 = FUN_0800a54c(iVar1 + 0x410);
    if (iVar1 == 0) {
      return 0;
    }
    FUN_0800b140(&DAT_01841004,1);
    FUN_0800b140(0x1841008,1);
    FUN_0800b140(0x1841030,1);
  }
  return 1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800abf4 */
undefined4 thunk_FUN_0800abf4()
{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0800ae0c();
  if ((_DAT_01841004 & 1) == 0) {
    iVar2 = FUN_0800a92c(*(undefined1 *)(iVar1 + 0x415));
    if (iVar2 == 0) {
      return 0;
    }
    iVar1 = FUN_0800a54c(iVar1 + 0x410);
    if (iVar1 == 0) {
      return 0;
    }
    FUN_0800b140(&DAT_01841004,1);
    FUN_0800b140(0x1841008,1);
    FUN_0800b140(0x1841030,1);
  }
  return 1;
}




/* 0x0800ac40 */
void FUN_0800ac40()
{
  _DAT_01836000 = (uint)(_DAT_01821000 << 0xb < 0);
  _DAT_01845000 = _DAT_01836000;
  _DAT_01813010 = 0;
  _DAT_0181b000 = 0;
  _DAT_01870000 = 0;
  _DAT_01800000 = 0;
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800ac84 */
undefined4 FUN_0800ac84()
{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_50 [5];
  undefined1 uStack_4b;
  undefined1 auStack_38 [5];
  undefined1 uStack_33;
  undefined1 auStack_20 [28];
  
  FUN_0800ae0c();
  FUN_08006bdc(auStack_20,&DAT_080398a0,0x18);
  FUN_08006bdc(auStack_50,&DAT_080398b8,0x18);
  FUN_08006bdc(auStack_38,&DAT_080398d0,0x18);
  DAT_0804d270 = 0x82208;
  FUN_0800ac40();
  _DAT_01836004 = _DAT_01836004 & 0x3f7ff | 0x20040;
  _DAT_01845004 = _DAT_01845004 & 0x217ff | 0x1e000;
  FUN_0800b140(&DAT_01832024,1);
  FUN_0800b140(0x183201c,1);
  FUN_0800b140(0x1832020,1);
  FUN_0800b140(0x1831008,1);
  FUN_0800b140(0x183100c,1);
  FUN_0800b140(0x1831010,1);
  FUN_0800b140(0x1831014,1);
  FUN_0800b140(0x183101c,1);
  iVar1 = FUN_0800a92c(uStack_4b);
  uVar2 = 0;
  if (iVar1 != 0) {
    _DAT_01831018 = _DAT_01831018 & 0x3f0f00 | 0x500;
    iVar1 = FUN_0800a54c(auStack_50);
    uVar2 = 0;
    if ((((iVar1 != 0) && (iVar1 = FUN_0800b166(&DAT_01831018,0x200), uVar2 = 0, iVar1 != 0)) &&
        (iVar1 = FUN_0800a92c(uStack_33), uVar2 = 0, iVar1 != 0)) &&
       (iVar1 = FUN_0800a54c(auStack_38), uVar2 = 0, iVar1 != 0)) {
      uVar2 = 1;
    }
  }
  return uVar2;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800ac84 */
undefined4 thunk_FUN_0800ac84()
{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_50 [5];
  undefined1 uStack_4b;
  undefined1 auStack_38 [5];
  undefined1 uStack_33;
  undefined1 auStack_20 [28];
  
  FUN_0800ae0c();
  FUN_08006bdc(auStack_20,&DAT_080398a0,0x18);
  FUN_08006bdc(auStack_50,&DAT_080398b8,0x18);
  FUN_08006bdc(auStack_38,&DAT_080398d0,0x18);
  DAT_0804d270 = 0x82208;
  FUN_0800ac40();
  _DAT_01836004 = _DAT_01836004 & 0x3f7ff | 0x20040;
  _DAT_01845004 = _DAT_01845004 & 0x217ff | 0x1e000;
  FUN_0800b140(&DAT_01832024,1);
  FUN_0800b140(0x183201c,1);
  FUN_0800b140(0x1832020,1);
  FUN_0800b140(0x1831008,1);
  FUN_0800b140(0x183100c,1);
  FUN_0800b140(0x1831010,1);
  FUN_0800b140(0x1831014,1);
  FUN_0800b140(0x183101c,1);
  iVar1 = FUN_0800a92c(uStack_4b);
  uVar2 = 0;
  if (iVar1 != 0) {
    _DAT_01831018 = _DAT_01831018 & 0x3f0f00 | 0x500;
    iVar1 = FUN_0800a54c(auStack_50);
    uVar2 = 0;
    if ((((iVar1 != 0) && (iVar1 = FUN_0800b166(&DAT_01831018,0x200), uVar2 = 0, iVar1 != 0)) &&
        (iVar1 = FUN_0800a92c(uStack_33), uVar2 = 0, iVar1 != 0)) &&
       (iVar1 = FUN_0800a54c(auStack_38), uVar2 = 0, iVar1 != 0)) {
      uVar2 = 1;
    }
  }
  return uVar2;
}




/* 0x0800ac88 */
undefined4 FUN_0800ac88()
{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_50 [5];
  undefined1 local_4b;
  undefined1 auStack_38 [5];
  undefined1 local_33;
  undefined1 auStack_20 [28];
  
  FUN_0800ae0c();
  FUN_08006bdc(auStack_20,&DAT_080398a0,0x18);
  FUN_08006bdc(auStack_50,&DAT_080398b8,0x18);
  FUN_08006bdc(auStack_38,&DAT_080398d0,0x18);
  DAT_0804d270 = 0x82208;
  FUN_0800ac40();
  _DAT_01836004 = _DAT_01836004 & 0x3f7ff | 0x20040;
  _DAT_01845004 = _DAT_01845004 & 0x217ff | 0x1e000;
  FUN_0800b140(&DAT_01832024,1);
  FUN_0800b140(0x183201c,1);
  FUN_0800b140(0x1832020,1);
  FUN_0800b140(0x1831008,1);
  FUN_0800b140(0x183100c,1);
  FUN_0800b140(0x1831010,1);
  FUN_0800b140(0x1831014,1);
  FUN_0800b140(0x183101c,1);
  iVar1 = FUN_0800a92c(local_4b);
  uVar2 = 0;
  if (iVar1 != 0) {
    _DAT_01831018 = _DAT_01831018 & 0x3f0f00 | 0x500;
    iVar1 = FUN_0800a54c(auStack_50);
    uVar2 = 0;
    if ((((iVar1 != 0) && (iVar1 = FUN_0800b166(&DAT_01831018,0x200), uVar2 = 0, iVar1 != 0)) &&
        (iVar1 = FUN_0800a92c(local_33), uVar2 = 0, iVar1 != 0)) &&
       (iVar1 = FUN_0800a54c(auStack_38), uVar2 = 0, iVar1 != 0)) {
      uVar2 = 1;
    }
  }
  return uVar2;
}




/* 0x0800adb4 */
undefined4 FUN_0800adb4()
{
  undefined1 auStack_20 [28];
  
  FUN_08006bdc(auStack_20,&DAT_080398e8,0x18);
  FUN_0800a54c(auStack_20);
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800add0 */
void FUN_0800add0()
{
  FUN_0800b140(0x182602c,1);
  FUN_0800b140(0x182701c,1);
  FUN_0800b140(0x1841008,1);
  FUN_0800b140(0x1826020,1);
  _DAT_01840000 = 0;
  return;
}




/* 0x0800ae0c */
undefined * FUN_0800ae0c()
{
  return &DAT_0804d668;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800ae14 */
undefined4 FUN_0800ae14(param_1)
uint param_1;
{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = FUN_0800ae0c();
  if (param_1 < 5) {
    iVar4 = iVar1 + param_1 * 0x1c;
    if ((*(char *)(iVar4 + 0x121) == '\x18') && ((_DAT_0b016000 & 1) != 0)) {
      iVar3 = FUN_0800a92c(*(undefined1 *)(iVar1 + 0x13d));
      if (iVar3 == 0) {
        return 0;
      }
      iVar1 = FUN_0800a54c(iVar1 + 0x138);
      if (iVar1 == 0) {
        return 0;
      }
      _DAT_0b016000 = _DAT_0b016000 & 0xe;
    }
    iVar1 = FUN_0800a92c(*(undefined1 *)(iVar4 + 0x121));
    uVar2 = 0;
    if (iVar1 != 0) {
      iVar1 = FUN_0800a54c(iVar4 + 0x11c);
      uVar2 = 0;
      if (iVar1 != 0) {
        DAT_0804d27c = *(undefined4 *)(iVar4 + 0x118);
        uVar2 = 1;
      }
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800ae14 */
undefined4 thunk_FUN_0800ae14(param_1)
uint param_1;
{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = FUN_0800ae0c();
  if (param_1 < 5) {
    iVar4 = iVar1 + param_1 * 0x1c;
    if ((*(char *)(iVar4 + 0x121) == '\x18') && ((_DAT_0b016000 & 1) != 0)) {
      iVar3 = FUN_0800a92c(*(undefined1 *)(iVar1 + 0x13d));
      if (iVar3 == 0) {
        return 0;
      }
      iVar1 = FUN_0800a54c(iVar1 + 0x138);
      if (iVar1 == 0) {
        return 0;
      }
      _DAT_0b016000 = _DAT_0b016000 & 0xe;
    }
    iVar1 = FUN_0800a92c(*(undefined1 *)(iVar4 + 0x121));
    uVar2 = 0;
    if (iVar1 != 0) {
      iVar1 = FUN_0800a54c(iVar4 + 0x11c);
      uVar2 = 0;
      if (iVar1 != 0) {
        DAT_0804d27c = *(undefined4 *)(iVar4 + 0x118);
        uVar2 = 1;
      }
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}




/* 0x0800ae8c */
undefined4 FUN_0800ae8c(param_1, param_2)
uint param_1; uint param_2;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_28;
  undefined1 local_23;
  
  FUN_08006d14(&local_28,0x18);
  iVar1 = FUN_0800ae0c();
  if ((param_1 < 5) && (param_2 < 7)) {
    FUN_08006bdc(&local_28,iVar1 + param_1 * 0x18 + 0x4b8,0x18);
    iVar1 = FUN_0800a92c(local_23);
    uVar2 = 0;
    if (iVar1 != 0) {
      local_28 = *(undefined4 *)(&DAT_08039868 + param_2 * 8);
      iVar1 = FUN_0800a54c(&local_28);
      uVar2 = 0;
      if (iVar1 != 0) {
        FUN_0800b140(*(undefined4 *)(&DAT_0803986c + param_2 * 8),1);
        _DAT_01845004 = _DAT_01845004 & 0x3f7ff | 0x400;
        uVar2 = 1;
      }
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}




/* 0x0800af0c */
undefined4 FUN_0800af0c()
{
  return 0;
}




/* 0x0800af0c */
undefined4 thunk_FUN_0800af0c()
{
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800af10 */
undefined4 FUN_0800af10(param_1, param_2)
uint param_1; undefined4 param_2;
{
  int iVar1;
  
  iVar1 = FUN_0800ae0c();
  if ((param_1 < 5) &&
     (iVar1 = FUN_0800af38(*(undefined4 *)(iVar1 + param_1 * 4 + 0x294),param_2), iVar1 != 0)) {
    return 1;
  }
  return 0;
}




/* 0x0800af38 */
undefined4 FUN_0800af38(param_1, param_2)
uint param_1; uint param_2;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int local_38;
  undefined1 local_33;
  
  FUN_08006d14(&local_38,0x18);
  iVar1 = FUN_0800ae0c();
  if ((param_2 < 6) && (iVar4 = *(int *)(&DAT_08039900 + param_2 * 0xc), iVar4 != 0)) {
    if (param_2 == 1) {
      iVar1 = iVar1 + 0x2a8;
    }
    else {
      iVar1 = iVar1 + 0x350;
    }
    for (iVar2 = 0; uVar3 = *(uint *)(iVar1 + iVar2 * 0x1c), uVar3 != 0; iVar2 = iVar2 + 1) {
      if (param_1 <= uVar3) {
        if (*(int *)(iVar1 + iVar2 * 0x1c) == 0) {
          return 0;
        }
        FUN_08006bdc(&local_38,iVar1 + iVar2 * 0x1c + 4,0x18);
        local_38 = iVar4;
        FUN_0800b140(0x182602c,1);
        FUN_0800b140(0x182701c,1);
        iVar4 = FUN_0800a92c(local_33);
        if (iVar4 == 0) {
          return 0;
        }
        iVar4 = FUN_0800a54c(&local_38);
        if (iVar4 == 0) {
          return 0;
        }
        iVar4 = FUN_0800b140(*(undefined4 *)(&DAT_08039904 + param_2 * 0xc),1);
        if (iVar4 != 0) {
          iVar4 = FUN_0800b140(*(undefined4 *)(&DAT_08039908 + param_2 * 0xc),1);
          if (iVar4 != 0) {
            return *(undefined4 *)(iVar1 + iVar2 * 0x1c);
          }
          return 0;
        }
        return 0;
      }
    }
  }
  return 0;
}




/* 0x0800b008 */
undefined4 FUN_0800b008(param_1)
uint param_1;
{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0800ae0c();
  if (param_1 < 5) {
    iVar1 = iVar1 + param_1 * 0x18;
    iVar2 = FUN_0800a92c(*(undefined1 *)(iVar1 + 0x1a9));
    if ((iVar2 != 0) && (iVar2 = FUN_0800a54c(iVar1 + 0x1a4), iVar2 != 0)) {
      FUN_0800a52c();
      iVar2 = FUN_0800a92c(*(undefined1 *)(iVar1 + 0x221));
      if ((iVar2 != 0) && (iVar1 = FUN_0800a54c(iVar1 + 0x21c), iVar1 != 0)) {
        return 1;
      }
    }
  }
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800b058 */
undefined4 FUN_0800b058(param_1, param_2)
uint param_1; int param_2;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_28;
  undefined1 local_23;
  
  FUN_08006d14(&local_28,0x18);
  iVar1 = FUN_0800ae0c();
  if (param_1 < 5) {
    FUN_08006bdc(&local_28,iVar1 + param_1 * 0x18 + 0x428,0x18);
    iVar1 = FUN_0800a92c(local_23);
    if (iVar1 == 0) {
      return 0;
    }
    if (param_2 == 1) {
      local_28 = 0x1802044;
      iVar1 = FUN_0800a54c(&local_28);
      if (iVar1 == 0) {
        return 0;
      }
      uVar2 = 0x180203c;
    }
    else {
      if (param_2 != 2) goto LAB_0800b098;
      local_28 = 0x1803034;
      iVar1 = FUN_0800a54c(&local_28);
      if (iVar1 == 0) {
        return 0;
      }
      uVar2 = 0x180302c;
    }
    FUN_0800b140(uVar2,1);
    _DAT_01845004 = _DAT_01845004 & 0x3f7ff | 0x400;
    uVar2 = 1;
  }
  else {
LAB_0800b098:
    uVar2 = 0;
  }
  return uVar2;
}




/* 0x0800b058 */
undefined4 thunk_FUN_0800b058(param_1, param_2)
uint param_1; int param_2;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uStack_28;
  undefined1 uStack_23;
  
  FUN_08006d14(&uStack_28,0x18);
  iVar1 = FUN_0800ae0c();
  if (param_1 < 5) {
    FUN_08006bdc(&uStack_28,iVar1 + param_1 * 0x18 + 0x428,0x18);
    iVar1 = FUN_0800a92c(uStack_23);
    if (iVar1 == 0) {
      return 0;
    }
    if (param_2 == 1) {
      uStack_28 = 0x1802044;
      iVar1 = FUN_0800a54c(&uStack_28);
      if (iVar1 == 0) {
        return 0;
      }
      uVar2 = 0x180203c;
    }
    else {
      if (param_2 != 2) goto LAB_0800b098;
      uStack_28 = 0x1803034;
      iVar1 = FUN_0800a54c(&uStack_28);
      if (iVar1 == 0) {
        return 0;
      }
      uVar2 = 0x180302c;
    }
    FUN_0800b140(uVar2,1);
    _DAT_01845004 = _DAT_01845004 & 0x3f7ff | 0x400;
    uVar2 = 1;
  }
  else {
LAB_0800b098:
    uVar2 = 0;
  }
  return uVar2;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800b124 */
undefined4 FUN_0800b124(param_1, param_2)
int param_1; uint * param_2;
{
  uint uVar1;
  uint uVar2;
  
  if (((param_1 != 0) && (param_2 != (uint *)0x0)) && (*(byte *)(param_1 + 4) < 5)) {
    uVar2 = (uint)*(byte *)(param_1 + 5);
                    /* WARNING (jumptable): Sanity check requires truncation of jumptable */
                    /* WARNING: Could not find normalized switch variable to match jumptable */
    switch(*(byte *)(param_1 + 4)) {
    case 1:
      uVar1 = 0;
      if (uVar2 != 0) {
        if (uVar2 == 1) {
          uVar1 = 4;
        }
        else {
          if (uVar2 != 0x18) {
            return 0;
          }
          uVar1 = 5;
        }
      }
      *param_2 = uVar1;
      return 1;
    }
    if ((uVar2 != 0) && (uVar2 != 1)) {
      if (uVar2 != 7) {
        return 0;
      }
      uVar2 = 2;
    }
    *param_2 = uVar2;
    return 1;
  }
  return 0;
}




/* 0x0800b140 */
undefined4 FUN_0800b140(param_1, param_2)
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




/* 0x0800b166 */
undefined4 FUN_0800b166(param_1, param_2)
uint * param_1; uint param_2;
{
  uint uVar1;
  
  *param_1 = *param_1 | param_2;
  uVar1 = 0;
  while( true ) {
    if ((*param_1 & param_2) == 0) {
      return 1;
    }
    if (999 < uVar1) break;
    FUN_080199b4(1);
    uVar1 = uVar1 + 1;
  }
  return 0;
}




/* 0x0800b19a */
int FUN_0800b19a(param_1)
int * param_1;
{
  int iVar1;
  
  *(int *)param_1[3] = *(int *)param_1[3] + 1;
  *(int *)(*(int *)(param_1[3] + 0xc) + 0x14) = *(int *)(*(int *)(param_1[3] + 0xc) + 0x14) + 1;
  iVar1 = *param_1;
  *param_1 = iVar1 + 1;
  return iVar1 + 1;
}




/* 0x0800b1b6 */
undefined4 FUN_0800b1b6(param_1, param_2, param_3)
int param_1; int param_2; undefined4 param_3;
{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  
  uVar5 = 0;
  uVar4 = 0;
  iVar7 = 2;
  FUN_0800b2f6(param_2);
  iVar6 = param_2 + 0x18;
  uVar1 = *(uint *)(param_2 + 8);
  do {
    uVar1 = uVar1 - 1;
    if (*(uint *)(param_2 + 8) <= uVar4) {
LAB_0800b1fc:
      if (iVar7 == 0) {
        uVar3 = 0;
      }
      else {
        if (iVar7 != 1) {
          return 0xffffffff;
        }
        FUN_0800b2e8(*(int *)(param_2 + 0xc) * uVar5 + iVar6,param_2,uVar5,param_1);
        uVar3 = 1;
      }
      FUN_0800b2da(param_3,*(int *)(param_2 + 0xc) * uVar5 + iVar6,uVar3);
      return 0;
    }
    iVar2 = *(int *)(*(int *)(param_2 + 0xc) * uVar1 + iVar6 + 4);
    if (iVar2 == param_1) {
      iVar7 = 0;
      uVar5 = uVar1;
      goto LAB_0800b1fc;
    }
    if (iVar2 == 0) {
      iVar7 = 1;
      uVar5 = uVar1;
    }
    uVar4 = uVar4 + 1;
  } while( true );
}




/* 0x0800b236 */
undefined8 FUN_0800b236(param_1, param_2, param_3)
undefined4 param_1; int param_2; int param_3;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  bool bVar8;
  int iVar9;
  
  uVar4 = 0;
  uVar5 = *(uint *)(param_2 + 8);
  iVar9 = param_2;
  FUN_0800b2f6(param_2);
  do {
    iVar7 = 0;
    if (*(uint *)(param_2 + 8) <= uVar4) {
LAB_0800b28c:
      bVar8 = *(uint *)(param_2 + 8) != uVar5;
      if (bVar8) {
        iVar7 = *(int *)(param_2 + 0xc) * uVar5 + param_2 + 0x18;
        FUN_0800b2e8(iVar7,param_2,uVar5,0,param_1,iVar9);
        *(undefined4 *)(iVar7 + 0x2c) = param_1;
      }
      if (*(int *)(param_3 + 0xc) == 0) {
        FUN_0800b2da(param_3,iVar7,bVar8);
      }
      if (iVar7 == 0) {
        uVar3 = 0xffffffff;
      }
      else {
        uVar3 = 0;
      }
      return CONCAT44(param_1,uVar3);
    }
    iVar7 = *(int *)(param_2 + 0xc) * uVar4 + param_2 + 0x18;
    uVar6 = uVar4;
    if (*(int *)(iVar7 + 0x2c) != 0) {
      iVar1 = FUN_08006906(param_1);
      iVar2 = FUN_08006906(*(undefined4 *)(iVar7 + 0x2c));
      uVar6 = uVar5;
      if (iVar1 == iVar2) {
        uVar3 = FUN_08006906(param_1);
        iVar1 = FUN_08006940(param_1,*(undefined4 *)(iVar7 + 0x2c),uVar3);
        if (iVar1 == 0) {
          uVar5 = *(uint *)(param_2 + 8);
          goto LAB_0800b28c;
        }
      }
    }
    uVar4 = uVar4 + 1;
    uVar5 = uVar6;
  } while( true );
}




/* 0x0800b2da */
void FUN_0800b2da(param_1, param_2)
undefined4 * param_1; undefined4 param_2;
{
  if (param_1[3] == 0) {
    *param_1 = 0;
    param_1[1] = 0;
    param_1[3] = param_2;
  }
  return;
}




/* 0x0800b2e8 */
void FUN_0800b2e8(param_1, param_2, param_3, param_4)
undefined4 * param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  param_1[2] = param_3;
  param_1[3] = param_2;
  *param_1 = 0;
  param_1[1] = param_4;
  return;
}




/* 0x0800b2f6 */
void FUN_0800b2f6(param_1)
undefined4 * param_1;
{
  uint uVar1;
  
  if (param_1[4] == 0) {
    param_1[4] = 1;
    param_1[5] = 0;
    for (uVar1 = 0; uVar1 < (uint)param_1[2]; uVar1 = uVar1 + 1) {
      *(undefined4 *)((int)param_1 + param_1[3] * uVar1 + 0x1c) = 0;
    }
    if ((code *)*param_1 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0800b324. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      ((code *)*param_1)();
      return;
    }
  }
  return;
}




/* 0x0800b33e */
int FUN_0800b33e(param_1)
int * param_1;
{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1[3] + 0xc);
  if (*param_1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar2 = *(int *)(iVar1 + 0x14) + -1;
    *(int *)(iVar1 + 0x14) = iVar2;
    if ((iVar2 == 0) && (*(int *)(iVar1 + 0x10) != 0)) {
      *(undefined4 *)(iVar1 + 0x10) = 0;
      if (*(code **)(iVar1 + 4) != (code *)0x0) {
        (**(code **)(iVar1 + 4))();
      }
    }
    iVar1 = *(int *)param_1[3] + -1;
    *(int *)param_1[3] = iVar1;
    if (iVar1 == 0) {
      iVar1 = param_1[3];
      *(undefined4 *)(iVar1 + 4) = 0;
      *(undefined4 *)(iVar1 + 0xc) = 0;
      *(undefined4 *)(iVar1 + 8) = 0;
      *(undefined4 *)(iVar1 + 0x2c) = 0;
    }
    iVar1 = *param_1 + -1;
    *param_1 = iVar1;
    if (iVar1 == 0) {
      param_1[3] = 0;
      return 0;
    }
  }
  return iVar1;
}




/* 0x0800b388 */
undefined4 FUN_0800b388(param_1, param_2, param_3, param_4)
undefined4 param_1; uint param_2; undefined4 param_3; int * param_4;
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0xffffffff;
  if ((DAT_0804e274 == 0) && (iVar1 = FUN_0800b424(), iVar1 != 0)) {
    return 0xffffffff;
  }
  if ((param_2 & 0xf) != 0) {
    param_2 = param_2 + 0x10 & 0xfffffff0;
  }
  iVar1 = FUN_0800bb7c();
  if (iVar1 != 0) {
    FUN_0800b614(0,2,"Cannot lock in DALGLBCTXT_AllocCtxt: lock:0x%x",
                 *(undefined4 *)(DAT_0804e268 + 0x10));
    return 0xffffffff;
  }
  iVar1 = FUN_08010790(param_1,0);
  if (iVar1 == 0) {
    iVar1 = FUN_08010790(0,param_2);
    if (iVar1 == 0) goto LAB_0800b3ea;
    FUN_080107e8(iVar1,param_2,param_1);
  }
  if (param_4 != (int *)0x0) {
    *param_4 = iVar1;
  }
  uVar2 = 0;
LAB_0800b3ea:
  FUN_0800bb9c();
  return uVar2;
}




/* 0x0800b424 */
undefined4 FUN_0800b424()
{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = 0xffffffff;
  FUN_0800b634(0x10,&DAT_0804e270,0);
  FUN_0800b648(DAT_0804e270);
  if (DAT_0804e274 == 0) {
    piVar1 = (int *)FUN_080373b8(0x194,0x2000);
    if (piVar1 == (int *)0x0) goto LAB_0800b494;
    if (DAT_0804e26c == 0) {
      FUN_0800b554(0x40,&DAT_0804e26c,0);
    }
    if (((uint)piVar1 & 0xfff) != 0) {
      *piVar1 = ((uint)(piVar1 + 0x400) & 0xfffff000) - (int)piVar1;
    }
    if (DAT_0804e268 == 0) {
      DAT_0804e268 = *piVar1 + (int)piVar1;
    }
    iVar2 = FUN_0800d534();
    if (iVar2 != 0) {
      FUN_0800b614(0,2,"Cannot lock in DALGLBCTXT_Init: lock:0x%x",
                   *(undefined4 *)(DAT_0804e268 + 0x10));
      goto LAB_0800b494;
    }
    iVar2 = FUN_08006898(DAT_0804e268 + 4,"dalspinlock",0xb);
    if (iVar2 != 0) {
      FUN_08006d14(DAT_0804e268,0x1000);
      FUN_080107e8(DAT_0804e268,0x20,"dalspinlock");
    }
    FUN_0800d57c();
    DAT_0804e274 = 1;
  }
  uVar3 = 0;
LAB_0800b494:
  FUN_0800b64a(DAT_0804e270);
  return uVar3;
}




/* 0x0800b54e */
void FUN_0800b54e()
{
  return;
}




/* 0x0800b550 */
undefined4 FUN_0800b550()
{
  return 0;
}




/* 0x0800b554 */
undefined4 FUN_0800b554(param_1, param_2, param_3)
int param_1; undefined4 * param_2; undefined4 * param_3;
{
  if (((param_3 != (undefined4 *)0x0) && (param_2 != (undefined4 *)0x0)) && (param_1 << 0x1a < 0)) {
    *param_3 = 0x21;
    *param_2 = param_3;
    return 0;
  }
  return 0xffffffff;
}




/* 0x0800b56e */
undefined4 FUN_0800b56e()
{
  return 0xffffffff;
}




/* 0x0800b574 */
undefined4 FUN_0800b574()
{
  DAT_0804d16c = DAT_0804d16c + 1;
  FUN_08020680();
  return 0;
}




/* 0x0800b590 */
int dal_device_attach(param_1, param_2)
undefined4 param_1; undefined4 * param_2;
{
  int iVar1;
  int local_18;
  undefined4 local_14;
  
  local_18 = 0;
  local_14 = 0;
  iVar1 = FUN_0800b944(param_1,&local_18,&DAT_0803aaec);
  if (iVar1 != 0) {
    *param_2 = 0;
    param_2[1] = 0;
    return iVar1;
  }
  FUN_0800b5c4(&local_14);
  *param_2 = local_14;
  param_2[1] = *(undefined4 *)(local_18 + 8);
  return 0;
}




/* 0x0800b5c4 */
void FUN_0800b5c4(param_1)
undefined4 * param_1;
{
  *param_1 = &DAT_08039978;
  return;
}



undefined ** FUN_0800b5d0()
{
  return &DAT_0804d450;
}




/* 0x0800b5e0 */
void FUN_0800b5e0(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  
  uVar1 = param_1 + 0x1fU & 0xffffffe0;
  uVar2 = param_2 + uVar1 & 0xffffffe0;
  if (param_3 == 0) {
    puVar3 = &DAT_0804d178;
    DAT_0804d174 = uVar1;
  }
  else {
    puVar3 = &DAT_0804d188;
    DAT_0804d184 = uVar1;
  }
  *puVar3 = uVar1;
  puVar3[1] = uVar2;
  puVar3[2] = uVar2 - uVar1;
  return;
}




/* 0x0800b5e0 */
void thunk_FUN_0800b5e0(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  
  uVar1 = param_1 + 0x1fU & 0xffffffe0;
  uVar2 = param_2 + uVar1 & 0xffffffe0;
  if (param_3 == 0) {
    puVar3 = &DAT_0804d178;
    DAT_0804d174 = uVar1;
  }
  else {
    puVar3 = &DAT_0804d188;
    DAT_0804d184 = uVar1;
  }
  *puVar3 = uVar1;
  puVar3[1] = uVar2;
  puVar3[2] = uVar2 - uVar1;
  return;
}




/* 0x0800b604 */
void FUN_0800b604()
{
  DAT_0804d170 = &DAT_0804d5c4;
  return;
}




/* 0x0800b604 */
void thunk_FUN_0800b604()
{
  DAT_0804d170 = &DAT_0804d5c4;
  return;
}




/* 0x0800b614 */
void FUN_0800b614(param_1, param_2)
undefined4 param_1; int param_2;
{
  if (param_2 == 1) {
    FUN_08006850();
  }
  return;
}




/* 0x0800b61e */
undefined4 FUN_0800b61e(param_1, param_2)
int param_1; int * param_2;
{
  int iVar1;
  int *extraout_r1;
  int extraout_r2;
  
  if (param_1 != 0) {
    iVar1 = FUN_08027760();
    *param_2 = iVar1;
    if (iVar1 != 0) {
      return 0;
    }
  }
  FUN_08006850();
  if (extraout_r2 == 0) {
    *extraout_r1 = (int)&DAT_08054270;
  }
  else {
    *extraout_r1 = extraout_r2;
  }
  return 0;
}




/* 0x0800b634 */
undefined4 FUN_0800b634(param_1, param_2, param_3)
undefined4 param_1; int * param_2; int param_3;
{
  if (param_3 == 0) {
    *param_2 = (int)&DAT_08054270;
  }
  else {
    *param_2 = param_3;
  }
  return 0;
}




/* 0x0800b648 */
void FUN_0800b648()
{
  return;
}




/* 0x0800b64a */
void FUN_0800b64a()
{
  return;
}




/* 0x0800b64c */
void FUN_0800b64c(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; int param_4;
{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int local_20;
  
  iVar6 = 0;
  if (DAT_08051508 == 0) {
    return;
  }
  local_20 = param_4;
  if ((DAT_08051504 != 0) || (iVar1 = FUN_0800b7ea(0,0x200006f,0x10000,&DAT_08051504), iVar1 == 0))
  {
    if ((DAT_08051504 & 1) == 0) {
      (**(code **)(*(int *)(DAT_08051504 + 4) + 0x38))(DAT_08051504,0);
    }
    else {
      (**(code **)(*(int *)((DAT_08051504 & 0xfffffffe) + 4) + 0x2c))
                (0xe,DAT_08051504 & 0xfffffffe,0,&local_20);
    }
    if (local_20 == 0x31) {
      iVar1 = *(int *)(param_1 + 0xc);
      pcVar3 = "tlmm_sleep8926";
      goto LAB_0800b6a4;
    }
  }
  iVar1 = *(int *)(param_1 + 0xc);
  pcVar3 = "tlmm_sleep";
LAB_0800b6a4:
  iVar1 = thunk_FUN_080106aa(iVar1 + 0x10,pcVar3,0,&DAT_0805a854);
  if (iVar1 == 0) {
    DAT_08051434 = DAT_0805a85c;
    for (uVar5 = 0; uVar5 < DAT_0805143c; uVar5 = uVar5 + 1) {
      iVar4 = DAT_08051508 + uVar5 * 8;
      *(undefined1 *)(iVar4 + 0x28) = 0;
      *(undefined1 *)(iVar4 + 0x2b) = 0;
      iVar1 = *(int *)(DAT_0805a85c + iVar6 * 4);
      iVar6 = iVar6 + 1;
      *(byte *)(iVar4 + 0x29) = (byte)((uint)(iVar1 << 0x11) >> 0x1f);
      *(byte *)(iVar4 + 0x2a) = (byte)((uint)(iVar1 << 0xf) >> 0x1e);
      *(byte *)(iVar4 + 0x2e) = (byte)((uint)(iVar1 << 10) >> 0x1f);
      if (iVar1 << 3 < 0) {
        FUN_0800b786(uVar5,(undefined1 *)(iVar4 + 0x28));
        FUN_0800c198();
        iVar1 = DAT_08051508 + uVar5 * 8;
        if (*(char *)(iVar1 + 0x2e) != '\0') {
          uVar2 = FUN_0800b786(uVar5,iVar1 + 0x28);
          FUN_0800c238(uVar2,*(undefined1 *)(DAT_08051508 + uVar5 * 8 + 0x2e));
        }
      }
    }
    *(undefined4 *)(DAT_08051508 + 0x20) = 1;
  }
  return;
}




/* 0x0800b76c */
void FUN_0800b76c(param_1, param_2)
int param_1; byte * param_2;
{
  *param_2 = (byte)param_1 & 0xf;
  param_2[1] = (byte)((uint)(param_1 << 0x11) >> 0x1f);
  param_2[2] = (byte)((uint)(param_1 << 0xf) >> 0x1e);
  param_2[3] = (byte)((uint)(param_1 << 0xb) >> 0x1c);
  return;
}




/* 0x0800b786 */
uint FUN_0800b786(param_1, param_2)
uint param_1; byte * param_2;
{
  return *param_2 & 0xf | (param_1 & 0x3ff) << 4 | (param_2[1] & 1) << 0xe | (param_2[2] & 3) << 0xf
         | (param_2[3] & 0xf) << 0x11 | 0x20000000;
}




/* 0x0800b7b4 */
int FUN_0800b7b4(param_1, param_2)
undefined4 param_1; uint * param_2;
{
  int iVar1;
  
  iVar1 = FUN_08010618(param_1,0,param_2);
  if ((((iVar1 == 0) && ((*param_2 & 1) == 0)) && (**(int **)(*(int *)(*param_2 + 8) + 0xc) == 1))
     && (iVar1 = FUN_0800bb02(), iVar1 != 0)) {
    FUN_0800b874(*param_2);
    *param_2 = 0;
  }
  return iVar1;
}




/* 0x0800b7ea */
int FUN_0800b7ea(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; uint param_3; undefined4 * param_4;
{
  int iVar1;
  int iVar2;
  undefined1 auStack_40 [4];
  uint local_3c;
  
  iVar1 = FUN_0800b830(param_1,param_2,param_4);
  if (iVar1 == 0) {
    iVar2 = FUN_0800baf8(*param_4,auStack_40,0x28);
    iVar1 = -1;
    if (iVar2 == 0) {
      if (param_3 >> 0x10 == local_3c >> 0x10) {
        iVar1 = 0;
      }
      else {
        FUN_0800b874(*param_4);
        *param_4 = 0;
      }
    }
  }
  else {
    *param_4 = 0;
  }
  return iVar1;
}




/* 0x0800b7ea */
int thunk_FUN_0800b7ea(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; uint param_3; undefined4 * param_4;
{
  int iVar1;
  int iVar2;
  undefined1 auStack_40 [4];
  uint uStack_3c;
  
  iVar1 = FUN_0800b830(param_1,param_2,param_4);
  if (iVar1 == 0) {
    iVar2 = FUN_0800baf8(*param_4,auStack_40,0x28);
    iVar1 = -1;
    if (iVar2 == 0) {
      if (param_3 >> 0x10 == uStack_3c >> 0x10) {
        iVar1 = 0;
      }
      else {
        FUN_0800b874(*param_4);
        *param_4 = 0;
      }
    }
  }
  else {
    *param_4 = 0;
  }
  return iVar1;
}




/* 0x0800b830 */
undefined * FUN_0800b830(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; uint * param_3;
{
  int iVar1;
  undefined *puVar2;
  
  *param_3 = 0;
  iVar1 = FUN_08010618(param_2,param_1);
  if (iVar1 != 0) {
    return &DAT_80000006;
  }
  if ((((*param_3 & 1) == 0) && (**(int **)(*(int *)(*param_3 + 8) + 0xc) == 1)) &&
     (puVar2 = (undefined *)FUN_0800bb02(), puVar2 != (undefined *)0x0)) {
    FUN_0800b874(*param_3);
    *param_3 = 0;
    return puVar2;
  }
  return (undefined *)0x0;
}




/* 0x0800b874 */
undefined4 FUN_0800b874(param_1)
uint param_1;
{
  uint uVar1;
  
  if (param_1 != 0) {
    uVar1 = param_1 & 0xfffffffe;
    if (((param_1 & 1) == 0) && (**(int **)(*(int *)(param_1 + 8) + 0xc) == 1)) {
      (**(code **)(*(int *)(uVar1 + 4) + 0xc))(uVar1);
    }
    (**(code **)(*(int *)(uVar1 + 4) + 4))(uVar1);
    return 0;
  }
  return 0xffffffff;
}




/* 0x0800b874 */
undefined4 thunk_FUN_0800b874(param_1)
uint param_1;
{
  uint uVar1;
  
  if (param_1 != 0) {
    uVar1 = param_1 & 0xfffffffe;
    if (((param_1 & 1) == 0) && (**(int **)(*(int *)(param_1 + 8) + 0xc) == 1)) {
      (**(code **)(*(int *)(uVar1 + 4) + 0xc))(uVar1);
    }
    (**(code **)(*(int *)(uVar1 + 4) + 4))(uVar1);
    return 0;
  }
  return 0xffffffff;
}




/* 0x0800b8a4 */
int FUN_0800b8a4(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; uint param_3; undefined4 * param_4;
{
  int iVar1;
  int iVar2;
  undefined1 auStack_40 [4];
  uint local_3c;
  
  iVar1 = FUN_0800b8e8(param_1,param_2,param_4);
  if (iVar1 == 0) {
    iVar2 = FUN_0800baf8(*param_4,auStack_40,0x28);
    iVar1 = -1;
    if (iVar2 == 0) {
      if (param_3 >> 0x10 == local_3c >> 0x10) {
        iVar1 = 0;
      }
      else {
        FUN_0800b874(*param_4);
        *param_4 = 0;
      }
    }
  }
  else {
    *param_4 = 0;
  }
  return iVar1;
}




/* 0x0800b8e8 */
undefined * FUN_0800b8e8(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; uint * param_3;
{
  int iVar1;
  undefined *puVar2;
  int local_18;
  
  *param_3 = 0;
  local_18 = 0;
  iVar1 = FUN_0800b944(param_2,&local_18,&DAT_0804d5e4);
  if ((iVar1 != 0) ||
     (iVar1 = ((code *)**(undefined4 **)(local_18 + 0xc))(param_2,0,param_3), iVar1 != 0)) {
    return &DAT_80000006;
  }
  if (((*param_3 & 1) == 0) &&
     ((**(int **)(*(int *)(*param_3 + 8) + 0xc) == 1 &&
      (puVar2 = (undefined *)FUN_0800bb02(), puVar2 != (undefined *)0x0)))) {
    FUN_0800b874(*param_3);
    *param_3 = 0;
    return puVar2;
  }
  return (undefined *)0x0;
}




/* 0x0800b944 */
undefined4 FUN_0800b944(param_1, param_2, param_3)
byte * param_1; int * param_2; int param_3;
{
  byte *pbVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  
  if ((((param_3 != 0) && (iVar6 = *(int *)(param_3 + 0xc), iVar6 != 0)) && (param_1 != (byte *)0x0)
      ) && ((uVar7 = *(uint *)(param_3 + 8), uVar7 != 0 && (param_2 != (int *)0x0)))) {
    iVar8 = 0x1505;
    for (pbVar1 = param_1; *pbVar1 != 0; pbVar1 = pbVar1 + 1) {
      iVar8 = (uint)*pbVar1 + iVar8 * 0x21;
    }
    uVar2 = 0;
    while ((uVar2 < uVar7 && (*(int *)(iVar6 + uVar2 * 0x18 + 4) != iVar8))) {
      uVar2 = uVar2 + 1;
    }
    if (uVar7 != uVar2) {
      iVar8 = *(int *)(iVar6 + uVar2 * 0x18 + 0x10);
      if (iVar8 == 0) {
LAB_0800b9ba:
        *param_2 = iVar6 + uVar2 * 0x18;
        return 0;
      }
      iVar9 = *(int *)(iVar6 + uVar2 * 0x18 + 0x14);
      for (iVar6 = 0; iVar6 < iVar8; iVar6 = iVar6 + 1) {
        iVar3 = FUN_08006906(param_1);
        iVar4 = FUN_08006906(*(undefined4 *)
                              (*(int *)(param_3 + 0xc) + *(int *)(iVar9 + iVar6 * 4) * 0x18));
        if (iVar3 == iVar4) {
          uVar5 = FUN_08006906(param_1);
          iVar3 = FUN_08006940(param_1,*(undefined4 *)
                                        (*(int *)(param_3 + 0xc) +
                                        *(int *)(iVar9 + iVar6 * 4) * 0x18),uVar5);
          if (iVar3 == 0) {
            uVar2 = *(uint *)(iVar9 + iVar6 * 4);
            iVar6 = *(int *)(param_3 + 0xc);
            goto LAB_0800b9ba;
          }
        }
      }
    }
  }
  return 0xffffffff;
}




/* 0x0800ba1c */
undefined4 FUN_0800ba1c()
{
  int iVar1;
  undefined4 in_r3 = 0;
  undefined4 local_10;
  
  local_10 = in_r3;
  if ((DAT_08050f94 == 0) && (iVar1 = FUN_0800b7ea(0,0x200006f,0x10000,&DAT_08050f94), iVar1 != 0))
  {
    return 0;
  }
  if ((DAT_08050f94 & 1) == 0) {
    (**(code **)(*(int *)(DAT_08050f94 + 4) + 0x38))(DAT_08050f94,0);
  }
  else {
    (**(code **)(*(int *)((DAT_08050f94 & 0xfffffffe) + 4) + 0x2c))
              (0xe,DAT_08050f94 & 0xfffffffe,0,&local_10);
  }
  return local_10;
}




/* 0x0800ba6c */
undefined4 FUN_0800ba6c()
{
  int iVar1;
  undefined4 in_r3 = 0;
  undefined4 local_10;
  
  local_10 = in_r3;
  if ((DAT_08051438 == 0) && (iVar1 = FUN_0800b7ea(0,0x200006f,0x10000,&DAT_08051438), iVar1 != 0))
  {
    return 0;
  }
  if ((DAT_08051438 & 1) == 0) {
    (**(code **)(*(int *)(DAT_08051438 + 4) + 0x38))(DAT_08051438,0);
  }
  else {
    (**(code **)(*(int *)((DAT_08051438 & 0xfffffffe) + 4) + 0x2c))
              (0xe,DAT_08051438 & 0xfffffffe,0,&local_10);
  }
  return local_10;
}




/* 0x0800babc */
void FUN_0800babc(param_1, param_2)
uint param_1; undefined4 param_2;
{
  if ((param_1 & 1) != 0) {
                    /* WARNING: Could not recover jumptable at 0x0800bad2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(int *)((param_1 & 0xfffffffe) + 4) + 0x2c))(9,param_1 & 0xfffffffe,0,param_2);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0800bada. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(param_1 + 4) + 0x24))(param_1,0);
  return;
}




/* 0x0800badc */
void FUN_0800badc(param_1)
int param_1;
{
                    /* WARNING: Could not recover jumptable at 0x0800bae0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(param_1 + 4) + 0x24))();
  return;
}




/* 0x0800bae2 */
uint FUN_0800bae2(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; uint param_4;
{
  uint local_8;
  
  local_8 = param_4 & 0xffffff00;
  (**(code **)(*(int *)(param_1 + 4) + 0x44))(param_1,param_2,&local_8);
  return local_8 & 0xff;
}




/* 0x0800baf8 */
undefined4 FUN_0800baf8(param_1)
uint param_1;
{
                    /* WARNING: Could not recover jumptable at 0x0800bb00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)((param_1 & 0xfffffffe) + 4) + 0x18))();
  return 0;
}




/* 0x0800bb02 */
undefined4 FUN_0800bb02(param_1)
uint param_1;
{
                    /* WARNING: Could not recover jumptable at 0x0800bb0a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)((param_1 & 0xfffffffe) + 4) + 8))();
  return 0;
}




/* 0x0800bb0c */
undefined4 FUN_0800bb0c(param_1)
uint param_1;
{
                    /* WARNING: Could not recover jumptable at 0x0800bb14. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)((param_1 & 0xfffffffe) + 4) + 0x10))();
  return 0;
}




/* 0x0800bb16 */
void FUN_0800bb16(param_1)
int param_1;
{
                    /* WARNING: Could not recover jumptable at 0x0800bb1a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(param_1 + 4) + 0x2c))();
  return;
}




/* 0x0800bb1c */
undefined4 FUN_0800bb1c()
{
  int iVar1;
  undefined4 in_r3 = 0;
  undefined4 local_10;
  
  local_10 = in_r3;
  if ((DAT_0804d3a0 == 0) && (iVar1 = FUN_0800b7b4(0x2000139,&DAT_0804d3a0), iVar1 != 0)) {
    return 0;
  }
  (**(code **)(*(int *)(DAT_0804d3a0 + 4) + 0x24))(DAT_0804d3a0,&local_10);
  return local_10;
}




/* 0x0800bb48 */
undefined4 FUN_0800bb48()
{
  int iVar1;
  undefined4 in_r3 = 0;
  undefined4 local_10;
  
  local_10 = in_r3;
  if ((DAT_08050858 == 0) && (iVar1 = FUN_0800b7b4(0x2000139,&DAT_08050858), iVar1 != 0)) {
    return 0;
  }
  (**(code **)(*(int *)(DAT_08050858 + 4) + 0x24))(DAT_08050858,&local_10);
  return local_10;
}




/* 0x0800bb74 */
undefined4 FUN_0800bb74(param_1)
int param_1;
{
                    /* WARNING: Could not recover jumptable at 0x0800bb78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(param_1 + 4) + 0x24))();
  return 0;
}




/* 0x0800bb7c */
int FUN_0800bb7c()
{
  int iVar1;
  
  FUN_0800b648(DAT_0804e270);
  iVar1 = FUN_0800d534();
  if (iVar1 != 0) {
    FUN_0800b64a(DAT_0804e270);
  }
  return iVar1;
}




/* 0x0800bb9c */
void FUN_0800bb9c()
{
  FUN_0800d57c();
  FUN_0800b64a(DAT_0804e270);
  return;
}




/* 0x0800bbb4 */
void FUN_0800bbb4(param_1, param_2)
int param_1; ushort * param_2;
{
  uint uVar1;
  
  uVar1 = (uint)*param_2 << 4;
  if ((char)param_2[1] != '\0') {
    uVar1 = uVar1 | 8;
  }
  if ((char)param_2[2] == '\x01') {
    uVar1 = uVar1 | 2;
  }
  if (*(char *)((int)param_2 + 3) != '\0') {
    uVar1 = uVar1 | 4;
  }
  if (*(char *)((int)param_2 + 5) != '\0') {
    uVar1 = uVar1 | 1;
  }
  *(uint *)((&DAT_0804e2c8)[param_1] + 0x2c) = uVar1;
  FUN_0800bda0();
  return;
}




/* 0x0800bbec */
void FUN_0800bbec(param_1, param_2, param_3)
int param_1; int param_2; int * param_3;
{
  int iVar1;
  
  iVar1 = FUN_08008ba4(param_2,(&DAT_0804e2d0)[param_1] + 0x80,(&DAT_0804e2c8)[param_1] + 0x34,
                       0x8000);
  *param_3 = *param_3 - (iVar1 - param_2);
  return;
}




/* 0x0800bc20 */
undefined8 FUN_0800bc20(param_1, param_2, param_3)
int param_1; int param_2; int * param_3;
{
  int iVar1;
  int local_20;
  undefined4 local_1c;
  int local_18;
  undefined4 local_14;
  
  local_20 = (&DAT_0804e2c8)[param_1] + 0x34;
  local_1c = 0x4000;
  local_18 = *param_3;
  local_14 = 0x1a;
  iVar1 = FUN_08008bc4((&DAT_0804e2d0)[param_1] + 0x80,param_2,&local_20);
  *param_3 = *param_3 - (iVar1 - param_2);
  return CONCAT44(local_1c,local_20);
}




/* 0x0800bc64 */
void FUN_0800bc64(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  
  uVar1 = *(uint *)((&DAT_0804e2c8)[param_1] + 0x78);
  if (param_2 == 1) {
    uVar1 = uVar1 | 1;
  }
  else {
    uVar1 = uVar1 & 0xfffffffe;
  }
  *(uint *)((&DAT_0804e2c8)[param_1] + 0x78) = uVar1;
  return;
}




/* 0x0800bc84 */
void FUN_0800bc84()
{
  if (DAT_0804e2c4 != '\x01') {
    DAT_0804e2c8 = 0x7824000;
    DAT_0804e2d0 = 0x7824000;
    DAT_0804e2cc = 0x7864000;
    DAT_0804e2d4 = 0x7864000;
    DAT_0804e2d8 = 0x7824900;
    DAT_0804e2e0 = 0x7824900;
    DAT_0804e2dc = 0x7864900;
    DAT_0804e2e4 = 0x7864900;
    DAT_0804e2c4 = '\x01';
  }
  return;
}




/* 0x0800bccc */
void FUN_0800bccc(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  
  uVar1 = *(uint *)((&DAT_0804e2c8)[param_1] + 4);
  if (param_2 == 0) {
    uVar1 = uVar1 & 0xfffffdff;
  }
  else {
    uVar1 = uVar1 | 0x200;
  }
  *(uint *)((&DAT_0804e2c8)[param_1] + 4) = uVar1;
  FUN_0800bda0();
  return;
}




/* 0x0800bcec */
void FUN_0800bcec(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  
  uVar1 = 0;
  if (param_2 != 0) {
    if (param_2 == 1) {
      uVar1 = 0x800;
    }
    else {
      if (param_2 != 2) {
        return;
      }
      uVar1 = 0xc00;
    }
  }
  *(uint *)((&DAT_0804e2c8)[param_1] + 4) =
       *(uint *)((&DAT_0804e2c8)[param_1] + 4) & 0xfffff3ff | uVar1;
  FUN_0800bda0();
  return;
}




/* 0x0800bd20 */
void FUN_0800bd20(param_1, param_2)
int param_1; short * param_2;
{
  uint uVar1;
  
  if (param_2 != (short *)0x0) {
    uVar1 = (uint)(ushort)param_2[6];
    if (param_2[2] == 1) {
      uVar1 = uVar1 | 0x400;
    }
    if (param_2[5] == 1) {
      uVar1 = uVar1 | 0x40;
    }
    if (param_2[4] == 1) {
      uVar1 = uVar1 | 0x80;
    }
    if (param_2[1] == 1) {
      uVar1 = uVar1 | 0x800;
    }
    if (*param_2 == 1) {
      uVar1 = uVar1 | 0x1000;
    }
    *(undefined4 *)((&DAT_0804e2c8)[param_1] + 8) = *(undefined4 *)(param_2 + 8);
    *(uint *)((&DAT_0804e2c8)[param_1] + 0xc) = uVar1;
    FUN_0800bda0();
    return;
  }
  return;
}




/* 0x0800bd78 */
void FUN_0800bd78(param_1)
int param_1;
{
  *(undefined4 *)((&DAT_0804e2c8)[param_1] + 0x38) = 0x18007ff;
  return;
}




/* 0x0800bd8c */
undefined4 FUN_0800bd8c(param_1)
int param_1;
{
  return *(undefined4 *)((&DAT_0804e2c8)[param_1] + 0x34);
}




/* 0x0800bd9c */
undefined4 FUN_0800bd9c()
{
  return 1;
}




/* 0x0800bda0 */
void FUN_0800bda0(param_1)
int param_1;
{
  int iVar1;
  bool bVar2;
  
  iVar1 = 1000;
  do {
    bVar2 = iVar1 == 0;
    iVar1 = iVar1 + -1;
    if (bVar2) {
      return;
    }
  } while ((*(uint *)((&DAT_0804e2c8)[param_1] + 0x6c) & 1) != 0);
  return;
}




/* 0x0800bdbc */
void FUN_0800bdbc(param_1, param_2)
int param_1; int param_2;
{
  byte bVar1;
  
  bVar1 = 0;
  if (param_2 != 0) {
    bVar1 = 0x10;
  }
  *(byte *)((&DAT_0804e2d8)[param_1] + 0x28) =
       *(byte *)((&DAT_0804e2d8)[param_1] + 0x28) & 0xe7 | bVar1;
  return;
}




/* 0x0800bdd8 */
void FUN_0800bdd8(param_1)
int param_1;
{
  uint *puVar1;
  uint uVar2;
  
  puVar1 = (uint *)((&DAT_0804e2d8)[param_1] + 0x100);
  uVar2 = *puVar1;
  *puVar1 = uVar2 | 0x20000000;
  *puVar1 = uVar2 | 0x60000000;
  return;
}




/* 0x0800bdf8 */
void FUN_0800bdf8(param_1)
int param_1;
{
  *(ushort *)((&DAT_0804e2d8)[param_1] + 0x3e) =
       (*(ushort *)((&DAT_0804e2d8)[param_1] + 0x3e) & 0xfff8) + 4;
  return;
}




/* 0x0800be10 */
void FUN_0800be10(param_1, param_2)
int param_1; char param_2;
{
  *(byte *)((&DAT_0804e2d8)[param_1] + 0x2c) =
       *(byte *)((&DAT_0804e2d8)[param_1] + 0x2c) & 0xfb | param_2 << 2;
  return;
}




/* 0x0800be2c */
void FUN_0800be2c(param_1, param_2)
int param_1; undefined4 * param_2;
{
  *param_2 = *(undefined4 *)((&DAT_0804e2d8)[param_1] + 0x40);
  param_2[1] = *(undefined4 *)((&DAT_0804e2d8)[param_1] + 0x44);
  return;
}




/* 0x0800be44 */
undefined4 FUN_0800be44(param_1)
int param_1;
{
  return *(undefined4 *)((&DAT_0804e2d8)[param_1] + 0x30);
}




/* 0x0800be54 */
byte FUN_0800be54(param_1)
int param_1;
{
  return *(byte *)((&DAT_0804e2d8)[param_1] + 0x29) & 0xf;
}




/* 0x0800be68 */
undefined4 FUN_0800be68(param_1)
int param_1;
{
  return *(undefined4 *)((&DAT_0804e2d8)[param_1] + 0x24);
}




/* 0x0800be78 */
void FUN_0800be78(param_1, param_2, param_3)
int param_1; uint * param_2; int param_3;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = (&DAT_0804e2d8)[param_1];
  uVar3 = *(uint *)(iVar1 + 0x10);
  *param_2 = uVar3;
  if (param_3 != 0) {
    uVar2 = *(uint *)(iVar1 + 0x14);
    param_2[1] = uVar2;
    uVar4 = *(uint *)(iVar1 + 0x18);
    param_2[2] = uVar4;
    *param_2 = *(int *)(iVar1 + 0x1c) << 8 | uVar4 >> 0x18;
    param_2[1] = uVar4 << 8 | uVar2 >> 0x18;
    param_2[2] = uVar2 << 8 | uVar3 >> 0x18;
    param_2[3] = uVar3 << 8;
  }
  return;
}




/* 0x0800beb8 */
void FUN_0800beb8(param_1)
int param_1;
{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  
  iVar3 = 100000;
  do {
    uVar2 = *(uint *)((&DAT_0804e2c8)[param_1] + 0xdc);
    if (uVar2 != 0) break;
    thunk_FUN_080199b4(1);
    bVar4 = iVar3 != 0;
    iVar3 = iVar3 + -1;
  } while (bVar4);
  *(uint *)((&DAT_0804e2c8)[param_1] + 0xe4) = uVar2;
  if ((uVar2 & 3) == 0) {
    uVar1 = 4;
  }
  else {
    uVar1 = 1;
  }
  *(undefined4 *)((&DAT_0804e2c8)[param_1] + 0xe8) = uVar1;
  iVar3 = 100000;
  do {
    if (*(int *)((&DAT_0804e2c8)[param_1] + 0xdc) == 0) {
      return;
    }
    thunk_FUN_080199b4(1);
    bVar4 = iVar3 != 0;
    iVar3 = iVar3 + -1;
  } while (bVar4);
  return;
}




/* 0x0800bf18 */
void FUN_0800bf18(param_1, param_2, param_3)
int param_1; uint param_2; int param_3;
{
  uint uVar1;
  
  uVar1 = *(uint *)((&DAT_0804e2d8)[param_1] + 0x38) & ~param_2;
  if (param_3 == 1) {
    uVar1 = uVar1 | param_2;
  }
  *(uint *)((&DAT_0804e2d8)[param_1] + 0x38) = uVar1;
  return;
}




/* 0x0800bf34 */
void FUN_0800bf34(param_1, param_2, param_3)
int param_1; uint param_2; int param_3;
{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  
  iVar3 = 100000;
  puVar1 = (uint *)((&DAT_0804e2d8)[param_1] + 0x34);
  uVar2 = *puVar1;
  if (param_3 == 0) {
    *puVar1 = uVar2 & ~param_2;
  }
  else {
    do {
      *puVar1 = uVar2 & ~param_2 | param_2;
      uVar2 = *puVar1;
      if ((param_2 & ~uVar2) == 0) {
        return;
      }
      thunk_FUN_080199b4(1);
      bVar4 = iVar3 != 0;
      iVar3 = iVar3 + -1;
    } while (bVar4);
  }
  return;
}




/* 0x0800bf74 */
uint FUN_0800bf74(param_1)
int param_1;
{
  return ((uint)*(byte *)((&DAT_0804e2d8)[param_1] + 0x2c) << 0x1e) >> 0x1f;
}




/* 0x0800bf88 */
void FUN_0800bf88(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  
  uVar1 = *(uint *)((&DAT_0804e2d8)[param_1] + 0x10c);
  if (param_2 == 1) {
    uVar1 = uVar1 | 2;
  }
  else {
    uVar1 = uVar1 & 0xfffffffd;
  }
  *(uint *)((&DAT_0804e2d8)[param_1] + 0x10c) = uVar1;
  return;
}




/* 0x0800bfac */
void FUN_0800bfac(param_1, param_2)
int param_1; uint param_2;
{
  uint uVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = 100000;
  do {
    *(uint *)((&DAT_0804e2d8)[param_1] + 0x30) = param_2 & 0x7ff003f;
    uVar1 = FUN_0800be44(param_1);
    if ((param_2 & 0x7ff003f & uVar1) == 0) {
      return;
    }
    thunk_FUN_080199b4(1);
    bVar3 = iVar2 != 0;
    iVar2 = iVar2 + -1;
  } while (bVar3);
  return;
}




/* 0x0800bfe8 */
void FUN_0800bfe8(param_1, param_2)
int param_1; undefined4 param_2;
{
  *(undefined4 *)((&DAT_0804e2d8)[param_1] + 0x58) = param_2;
  return;
}




/* 0x0800bff8 */
void FUN_0800bff8(param_1, param_2)
int param_1; undefined4 param_2;
{
  *(undefined4 *)((&DAT_0804e2d8)[param_1] + 0x5c) = param_2;
  return;
}




/* 0x0800c008 */
void FUN_0800c008(param_1, param_2)
int param_1; undefined2 param_2;
{
  *(undefined2 *)((&DAT_0804e2d8)[param_1] + 6) = param_2;
  return;
}




/* 0x0800c018 */
void FUN_0800c018(param_1, param_2)
int param_1; undefined2 param_2;
{
  *(undefined2 *)((&DAT_0804e2d8)[param_1] + 4) = param_2;
  return;
}




/* 0x0800c028 */
void FUN_0800c028(param_1, param_2)
int param_1; int param_2;
{
  byte bVar1;
  
  bVar1 = *(byte *)((&DAT_0804e2d8)[param_1] + 0x28);
  if (param_2 == 0) {
    bVar1 = bVar1 & 0xdd;
  }
  else if (param_2 == 1) {
    bVar1 = (bVar1 & 0xdd) + 2;
  }
  else {
    if (param_2 != 2) {
      return;
    }
    bVar1 = bVar1 | 0x20;
  }
  *(byte *)((&DAT_0804e2d8)[param_1] + 0x28) = bVar1;
  return;
}




/* 0x0800c058 */
void FUN_0800c058(param_1)
int param_1;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  uVar1 = FUN_08032af8();
  iVar4 = (&DAT_0804e2d8)[param_1];
  uVar2 = *(uint *)(iVar4 + 0x40);
  uVar3 = *(uint *)(iVar4 + 0x44);
  if ((uVar1 & 3) != 0) {
    uVar2 = uVar2 | 0x280000;
    uVar3 = uVar3 | 7;
  }
  if ((uVar1 & 1) == 0) {
    if ((int)(uVar1 << 0x1e) < 0) {
      uVar2 = uVar2 & 0x3bffffff | 0x3000000;
    }
  }
  else {
    uVar2 = uVar2 & 0x38ffffff | 0x44040000;
  }
  *(uint *)(iVar4 + 0x11c) = uVar2;
  *(uint *)((&DAT_0804e2d8)[param_1] + 0x120) = uVar3;
  return;
}




/* 0x0800c0a8 */
void FUN_0800c0a8(param_1, param_2)
int param_1; uint param_2;
{
  *(ushort *)((&DAT_0804e2d8)[param_1] + 0x2c) =
       (ushort)(param_2 << 8) | (ushort)((param_2 & 0x300) >> 2) | 1;
  return;
}




/* 0x0800c0c4 */
void FUN_0800c0c4(param_1, param_2)
int param_1; undefined4 param_2;
{
  *(undefined4 *)((&DAT_0804e2d8)[param_1] + 8) = param_2;
  return;
}




/* 0x0800c0d4 */
void FUN_0800c0d4(param_1, param_2)
int param_1; byte * param_2;
{
  *(ushort *)((&DAT_0804e2d8)[param_1] + 0xe) =
       (ushort)*param_2 << 8 | (ushort)param_2[1] << 6 | (ushort)param_2[2] << 5 |
       (ushort)param_2[3] << 4 | (ushort)param_2[4] << 3 | (ushort)param_2[5];
  return;
}




/* 0x0800c104 */
void FUN_0800c104(param_1, param_2)
int param_1; byte param_2;
{
  *(byte *)((&DAT_0804e2d8)[param_1] + 0x29) =
       *(byte *)((&DAT_0804e2d8)[param_1] + 0x29) & 0xfe | param_2;
  return;
}




/* 0x0800c11c */
void FUN_0800c11c(param_1, param_2)
int param_1; undefined1 param_2;
{
  *(undefined1 *)((&DAT_0804e2d8)[param_1] + 0x2e) = param_2;
  return;
}




/* 0x0800c12c */
void FUN_0800c12c(param_1, param_2)
int param_1; byte * param_2;
{
  *(ushort *)((&DAT_0804e2d8)[param_1] + 0xc) =
       (ushort)*param_2 << 5 | (ushort)param_2[1] << 4 | (ushort)param_2[2] << 2 |
       (ushort)param_2[3] << 1 | (ushort)param_2[4];
  return;
}




/* 0x0800c154 */
void FUN_0800c154(param_1, param_2)
int param_1; byte param_2;
{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  iVar1 = 100000;
  iVar2 = (&DAT_0804e2d8)[param_1];
  *(byte *)(iVar2 + 0x2f) = param_2;
  while ((bVar3 = iVar1 != 0, iVar1 = iVar1 + -1, bVar3 &&
         ((*(byte *)(iVar2 + 0x2f) & param_2) != 0))) {
    thunk_FUN_080199b4(1);
  }
  return;
}




/* 0x0800c180 */
void FUN_0800c180(param_1, param_2)
int param_1; byte param_2;
{
  *(byte *)((&DAT_0804e2d8)[param_1] + 0x29) =
       *(byte *)((&DAT_0804e2d8)[param_1] + 0x29) & 0xf1 | param_2;
  return;
}




/* 0x0800c198 */
void FUN_0800c198(param_1)
uint param_1;
{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  
  uVar3 = (param_1 << 0x12) >> 0x16;
  if (DAT_0805150c <= uVar3) {
    return;
  }
  uVar1 = (param_1 << 7) >> 0x1c;
  if (uVar1 == 2) {
    uVar2 = 0;
  }
  else {
    if (uVar1 != 3) goto LAB_0800c1c2;
    uVar2 = 1;
  }
  FUN_0800c238(param_1,uVar2);
LAB_0800c1c2:
  if (uVar3 < DAT_0805150c) {
    *(uint *)(DAT_08051510 + uVar3 * 0x1000) =
         (param_1 << 0xf) >> 0x1e | (param_1 & 0xf) << 2 | (param_1 & 0x1e0000) >> 0xb |
         (param_1 & 0x4000) >> 5;
  }
  return;
}




/* 0x0800c1f0 */
void FUN_0800c1f0(param_1)
undefined4 * param_1;
{
  if (param_1 != (undefined4 *)0x0) {
    DAT_0805150c = *param_1;
    DAT_08051510 = param_1[1];
  }
  return;
}




/* 0x0800c204 */
void FUN_0800c204(param_1, param_2, param_3)
int param_1; uint param_2; uint param_3;
{
  *(uint *)(DAT_08051510 + param_1) =
       param_2 & param_3 | *(uint *)(DAT_08051510 + param_1) & ~param_2;
  return;
}




/* 0x0800c238 */
void FUN_0800c238(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  int iVar2;
  
  if ((uint)(param_1 << 0x12) >> 0x16 < DAT_0805150c) {
    iVar2 = ((uint)(param_1 << 0x12) >> 0x16) * 0x1000 + 4;
    uVar1 = *(uint *)(DAT_08051510 + iVar2);
    if (param_2 == 1) {
      uVar1 = uVar1 & 3 | 2;
    }
    else {
      uVar1 = uVar1 & 1;
    }
    *(uint *)(DAT_08051510 + iVar2) = uVar1;
  }
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800c270 */
uint FUN_0800c270()
{
  return (uint)(_DAT_0005c0dc << 0xd) >> 0x1d;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800c280 */
void FUN_0800c280(param_1, param_2)
int param_1; uint param_2;
{
  if (param_1 != 0) {
    *(uint *)(param_1 * 4 + 0x4a803c) = param_2 & 0x1fff;
    return;
  }
  _DAT_004a8038 = param_2 & 0x3ff;
  return;
}




/* 0x0800c2a0 */
void FUN_0800c2a0(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  uint uVar2;
  
  iVar1 = param_2 * 4;
  if (param_1 == 0) {
    uVar2 = *(uint *)(iVar1 + 0x4a8008) & 0x3fffff | 0x100000;
LAB_0800c2c6:
    *(uint *)(iVar1 + 0x4a8008) = uVar2;
    return;
  }
  param_2 = param_2 * 4;
  if (param_1 == 1) {
    uVar2 = *(uint *)(param_2 + 0x4a9004) & 0x3fffff | 0x100000;
  }
  else {
    if (param_1 != 2) {
      if (param_1 != 3) {
        return;
      }
      uVar2 = *(uint *)(iVar1 + 0x4a8008) & 0x3fffff | 0x200000;
      goto LAB_0800c2c6;
    }
    uVar2 = *(uint *)(param_2 + 0x4a9004) & 0x3fffff | 0x200000;
  }
  *(uint *)(param_2 + 0x4a9004) = uVar2;
  return;
}




/* 0x0800c2f4 */
void FUN_0800c2f4(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  uint uVar2;
  
  iVar1 = param_2 * 4;
  if (param_1 == 0) {
    uVar2 = *(uint *)(iVar1 + 0x4a8008) & 0x2fffff;
LAB_0800c31a:
    *(uint *)(iVar1 + 0x4a8008) = uVar2;
    return;
  }
  param_2 = param_2 * 4;
  if (param_1 == 1) {
    uVar2 = *(uint *)(param_2 + 0x4a9004) & 0x2fffff;
  }
  else {
    if (param_1 != 2) {
      if (param_1 != 3) {
        return;
      }
      uVar2 = *(uint *)(iVar1 + 0x4a8008) & 0x1fffff;
      goto LAB_0800c31a;
    }
    uVar2 = *(uint *)(param_2 + 0x4a9004) & 0x1fffff;
  }
  *(uint *)(param_2 + 0x4a9004) = uVar2;
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800c33c */
uint FUN_0800c33c()
{
  return (uint)(_DAT_0005c0dc << 0x18) >> 0x16;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800c350 */
uint FUN_0800c350()
{
  return (_DAT_0005c0dc & 0xff00) >> 6;
}




/* 0x0800c364 */
undefined4 FUN_0800c364()
{
  return 0x3ff;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800c36a */
uint FUN_0800c36a(param_1, param_2)
int param_1; undefined4 param_2;
{
  if (param_1 == 0) {
    switch(param_2) {
    case 0:
      return (_DAT_0005c0a0 << 0x1a) >> 0x18;
    case 1:
      return (_DAT_0005c0a0 & 0x3f000) >> 10;
    case 2:
      return (_DAT_0005c0a0 & 0x3f000000) >> 0x16;
    case 3:
      return (_DAT_0005c0a4 & 0x3f0) >> 2;
    case 4:
      return (_DAT_0005c0a4 & 0x3f0000) >> 0xe;
    }
  }
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800c3bc */
uint FUN_0800c3bc(param_1, param_2)
int param_1; undefined4 param_2;
{
  if (param_1 == 0) {
    switch(param_2) {
    case 0:
      return (_DAT_0005c0a0 & 0xfc0) >> 4;
    case 1:
      return (_DAT_0005c0a0 & 0xfc0000) >> 0x10;
    case 2:
      return ((_DAT_0005c0a4 << 0x1c) >> 0x1a | _DAT_0005c0a0 >> 0x1e) << 2;
    case 3:
      return (_DAT_0005c0a4 & 0xfc00) >> 8;
    case 4:
      return (_DAT_0005c0a4 & 0xfc00000) >> 0x14;
    }
  }
  return 0;
}




/* 0x0800c420 */
undefined4 FUN_0800c420(param_1, param_2)
int param_1; uint * param_2;
{
  *param_2 = *(uint *)(param_1 * 4 + 0x4a9030) & 0x3ff;
  return 1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800c438 */
void FUN_0800c438(param_1)
uint param_1;
{
  _DAT_004a8034 = param_1 & 0x1fffffff;
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800c448 */
void FUN_0800c448()
{
  _DAT_004a8000 = _DAT_004a8000 & 0xffc3ffd;
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800c468 */
void FUN_0800c468(param_1)
int param_1;
{
  if (param_1 == 0) {
    _DAT_004a8000 = _DAT_004a8000 & 0xffc3ffb;
  }
  else if (param_1 == 1) {
    _DAT_004a8000 = _DAT_004a8000 & 0xffc3fff | 4;
  }
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800c490 */
void FUN_0800c490(param_1)
byte param_1;
{
  _DAT_004a8000 = _DAT_004a8000 & 0xc003fff | (uint)param_1 << 0x12;
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800c4a8 */
void FUN_0800c4a8(param_1)
uint param_1;
{
  _DAT_004a8000 = (param_1 & 0x7ff) << 3 | _DAT_004a8000 & 0xffc0007;
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800c4c8 */
void FUN_0800c4c8(param_1)
int param_1;
{
  if (param_1 == 0) {
    _DAT_004a8000 = _DAT_004a8000 & 0xffc3ffe;
  }
  else if (param_1 == 1) {
    _DAT_004a8000 = _DAT_004a8000 & 0xffc3fff | 1;
  }
  return;
}




/* 0x0800c4f0 */
void FUN_0800c4f0(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  int iVar1;
  uint uVar2;
  
  iVar1 = param_2 * 4;
  if (param_1 == 0) {
    uVar2 = *(uint *)(iVar1 + 0x4a8008) & 0x3ffc00 | param_3 & 0x3ff;
LAB_0800c522:
    *(uint *)(iVar1 + 0x4a8008) = uVar2;
    return;
  }
  param_2 = param_2 * 4;
  if (param_1 == 1) {
    uVar2 = *(uint *)(param_2 + 0x4a9004) & 0x3ffc00 | param_3 & 0x3ff;
  }
  else {
    uVar2 = (param_3 & 0x3ff) << 10;
    if (param_1 != 2) {
      if (param_1 != 3) {
        return;
      }
      uVar2 = *(uint *)(iVar1 + 0x4a8008) & 0x3003ff | uVar2;
      goto LAB_0800c522;
    }
    uVar2 = *(uint *)(param_2 + 0x4a9004) & 0x3003ff | uVar2;
  }
  *(uint *)(param_2 + 0x4a9004) = uVar2;
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800c554 */
bool FUN_0800c554()
{
  return (_DAT_004a905c & 1) != 0;
}




/* 0x0800c568 */
undefined4 FUN_0800c568()
{
  return 0;
}




/* 0x0800c56c */
void FUN_0800c56c(param_1, param_2)
int param_1; uint param_2;
{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + 0xb0) & 0x1ffff;
  if ((uVar1 & param_2) != 0) {
    *(uint *)(param_1 + 0xb0) = uVar1 & ~param_2;
  }
  return;
}




/* 0x0800c580 */
int FUN_0800c580(param_1)
int param_1;
{
  return 1 << (*(uint *)(param_1 + 0xdc) & 0xf);
}




/* 0x0800c58e */
uint FUN_0800c58e(param_1)
int param_1;
{
  return *(uint *)(param_1 + 0xb4) & 0x1ffff;
}




/* 0x0800c598 */
uint FUN_0800c598(param_1)
int param_1;
{
  return *(uint *)(param_1 + 0xa4) & 0xfff;
}




/* 0x0800c5a2 */
uint FUN_0800c5a2(param_1)
int param_1;
{
  return *(uint *)(param_1 + 0x44) & 0xfffffffc;
}




/* 0x0800c5aa */
void FUN_0800c5aa(param_1)
int param_1;
{
  *(undefined4 *)(param_1 + 0xa8) = 0x30;
  return;
}




/* 0x0800c5b2 */
void FUN_0800c5b2(param_1)
int param_1;
{
  *(undefined4 *)(param_1 + 0xa8) = 0x10;
  return;
}




/* 0x0800c5ba */
void FUN_0800c5ba(param_1)
int param_1;
{
  *(undefined4 *)(param_1 + 0xa8) = 0x20;
  return;
}




/* 0x0800c5c2 */
void FUN_0800c5c2(param_1, param_2)
uint * param_1; int param_2;
{
  uint uVar1;
  
  if (param_2 == 0) {
    uVar1 = *param_1 & 0xffffff7f;
  }
  else {
    uVar1 = *param_1 | 0x80;
  }
  *param_1 = uVar1;
  return;
}




/* 0x0800c5d4 */
void FUN_0800c5d4(param_1, param_2, param_3, param_4)
int param_1; int param_2; int param_3; uint param_4;
{
  *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & 0x7c0 | param_2 << 4 | param_3 << 2 | param_4;
  return;
}




/* 0x0800c5ea */
void FUN_0800c5ea(param_1, param_2)
int param_1; int param_2;
{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0x200;
  }
  else {
    uVar1 = 0x100;
  }
  *(undefined4 *)(param_1 + 0xa8) = uVar1;
  return;
}




/* 0x0800c5fc */
void FUN_0800c5fc(param_1, param_2)
int param_1; undefined4 param_2;
{
  *(undefined4 *)(param_1 + 0xa0) = param_2;
  return;
}




/* 0x0800c602 */
void FUN_0800c602(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  
  if (param_2 == 0) {
    uVar1 = *(uint *)(param_1 + 0x3c) & 0x30;
  }
  else {
    uVar1 = *(uint *)(param_1 + 0x3c) & 0x3c | 0xc;
  }
  *(uint *)(param_1 + 0x3c) = uVar1;
  return;
}




/* 0x0800c618 */
void FUN_0800c618(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  
  if (param_2 == 0) {
    uVar1 = *(uint *)(param_1 + 0xb8) & 0x1e;
  }
  else {
    uVar1 = *(uint *)(param_1 + 0xb8) & 0x1f | 1;
  }
  *(uint *)(param_1 + 0xb8) = uVar1;
  return;
}




/* 0x0800c632 */
void FUN_0800c632(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  
  if (param_2 == 0) {
    uVar1 = *(uint *)(param_1 + 4) & 0x77f;
  }
  else {
    uVar1 = *(uint *)(param_1 + 4) & 0x7ff | 0x80;
  }
  *(uint *)(param_1 + 4) = uVar1;
  return;
}




/* 0x0800c648 */
void FUN_0800c648(param_1, param_2)
uint * param_1; int param_2;
{
  uint uVar1;
  
  if (param_2 == 0) {
    uVar1 = *param_1 & 0xffffffbf;
  }
  else {
    uVar1 = *param_1 | 0x40;
  }
  *param_1 = uVar1;
  return;
}




/* 0x0800c65a */
void FUN_0800c65a(param_1, param_2)
int param_1; int param_2;
{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 2;
  }
  else {
    uVar1 = 1;
  }
  *(undefined4 *)(param_1 + 0xa8) = uVar1;
  return;
}




/* 0x0800c668 */
void FUN_0800c668(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  
  if (param_2 == 0) {
    uVar1 = *(uint *)(param_1 + 0x3c) & 0x1c;
  }
  else {
    uVar1 = *(uint *)(param_1 + 0x3c) & 0x3c | 0x20;
  }
  *(uint *)(param_1 + 0x3c) = uVar1;
  return;
}




/* 0x0800c67e */
void FUN_0800c67e(param_1, param_2)
int param_1; uint param_2;
{
  if (-1 < (int)((*(uint *)(param_1 + 0x3c) & 0x3c) << 0x1a)) {
    param_2 = param_2 >> 2;
  }
  *(uint *)(param_1 + 0x20) = param_2 - 1;
  return;
}




/* 0x0800c698 */
void FUN_0800c698(param_1, param_2)
int param_1; int param_2;
{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0x600;
  }
  else {
    uVar1 = 0x500;
  }
  *(undefined4 *)(param_1 + 0xa8) = uVar1;
  return;
}




/* 0x0800c6aa */
void FUN_0800c6aa(param_1, param_2)
int param_1; uint param_2;
{
  *(uint *)(param_1 + 0x18) =
       (param_2 & 0x3fffffe0) << 2 | param_2 & 0x1f | *(uint *)(param_1 + 0x18) & 0x40;
  return;
}




/* 0x0800c6c4 */
void FUN_0800c6c4(param_1, param_2)
int param_1; int param_2;
{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 8;
  }
  else {
    uVar1 = 4;
  }
  *(undefined4 *)(param_1 + 0xa8) = uVar1;
  return;
}




/* 0x0800c6d2 */
void FUN_0800c6d2(param_1, param_2)
int param_1; uint param_2;
{
  *(uint *)(param_1 + 0x44) = param_2 & 0xfffffffc;
  return;
}




/* 0x0800c6da */
void FUN_0800c6da(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  
  if (param_2 == 0) {
    uVar1 = *(uint *)(param_1 + 0x3c) & 0x2c;
  }
  else {
    uVar1 = *(uint *)(param_1 + 0x3c) & 0x3c | 0x10;
  }
  *(uint *)(param_1 + 0x3c) = uVar1;
  return;
}




/* 0x0800c6f0 */
void FUN_0800c6f0(param_1, param_2)
int param_1; uint param_2;
{
  if (-1 < (int)((*(uint *)(param_1 + 0x3c) & 0x3c) << 0x1b)) {
    param_2 = param_2 >> 2;
  }
  *(uint *)(param_1 + 0x1c) = param_2;
  return;
}




/* 0x0800c700 */
void FUN_0800c700(param_1, param_2)
int param_1; undefined4 param_2;
{
  *(undefined4 *)(param_1 + 0x34) = param_2;
  return;
}




/* 0x0800c704 */
undefined4 FUN_0800c704(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  byte *pbVar1;
  uint uVar2;
  int iVar3;
  undefined4 extraout_r3;
  uint uVar4;
  bool bVar5;
  
  iVar3 = 0;
  uVar4 = *(uint *)(param_1 + 0x44) & 0xfffffffc;
  uVar2 = uVar4 - (*(uint *)(param_1 + 0x4c) & 0x7f | *(uint *)(param_1 + 0x4c) >> 0xe);
  if (param_3 <= uVar2) {
    uVar2 = param_3;
  }
  param_3 = param_3 - uVar2;
  while (bVar5 = uVar2 != 0, uVar2 = uVar2 - 1, bVar5) {
    pbVar1 = (byte *)(param_2 + iVar3);
    iVar3 = iVar3 + 1;
    *(uint *)(param_1 + 0x100) = (uint)*pbVar1;
  }
  if ((param_3 == 0) || (uVar4 < param_3)) {
    iVar3 = 0;
  }
  else {
    iVar3 = uVar4 - param_3;
  }
  FUN_0800c6f0(param_1,iVar3);
  return extraout_r3;
}




/* 0x0800c74a */
void FUN_0800c74a(param_1, param_2, param_3)
int param_1; int * param_2; int * param_3;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = *(uint *)(param_1 + 4);
  uVar2 = uVar3 / 0xff;
  if (uVar3 != uVar2 * 0xff) {
    uVar2 = uVar2 + 1;
  }
  if (*(char *)(param_1 + 0xc) == '\0') {
    *param_3 = uVar2 * 2 + 2;
    iVar1 = uVar3 + uVar2 * 2;
  }
  else {
    *param_3 = uVar3 + uVar2 * 2 + 2;
    iVar1 = 0;
  }
  *param_2 = iVar1;
  return;
}




/* 0x0800c77e */
void FUN_0800c77e(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; uint param_3; uint param_4;
{
  bool bVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint local_2c;
  uint local_28;
  
  if (*(int *)(param_1 + 0xc0) == 0) {
    *(undefined4 *)(param_1 + 200) = *(undefined4 *)(param_1 + 0x88);
    *(undefined4 *)(param_1 + 0xc4) = *(undefined4 *)(param_1 + 0x50);
  }
  else {
    uVar4 = *(uint *)(param_1 + 0x27c);
    uVar3 = *(uint *)(param_1 + 0x278);
    *(undefined4 *)(param_1 + 200) = 0;
    bVar1 = false;
    *(undefined4 *)(param_1 + 0xc4) = 0;
    bVar2 = false;
    if (uVar3 == 0) {
LAB_0800c834:
      if (*(char *)(*(int *)(param_1 + 0x44) + 0xc) == '\0') {
        uVar3 = uVar4 >> 8;
        if ((uVar4 & 0xff) != 0) {
          uVar3 = uVar3 + 1;
        }
        *(uint *)(param_1 + 0x88) = (uVar4 - uVar3) + *(int *)(param_1 + 0x88);
      }
      else if (4 < uVar3) {
        uVar3 = uVar3 - 2;
        uVar4 = uVar3 / 0x101;
        if (uVar3 != uVar4 * 0x101) {
          uVar4 = uVar4 + 1;
        }
        *(uint *)(param_1 + 0x50) = uVar3 + uVar4 * -2 + *(int *)(param_1 + 0x50);
      }
    }
    else {
      uVar5 = 0;
      local_2c = param_3;
      local_28 = param_4;
      do {
        iVar6 = *(int *)(param_1 + 0x34) + uVar5 * 0x10;
        FUN_0800c74a(iVar6,&local_2c,&local_28);
        if (uVar3 < local_28) {
LAB_0800c82a:
          if ((bVar2) && (bVar1)) {
            return;
          }
          goto LAB_0800c834;
        }
        uVar3 = uVar3 - local_28;
        if (uVar3 == 0) {
          bVar2 = true;
        }
        if (uVar4 < local_2c) goto LAB_0800c82a;
        uVar4 = uVar4 - local_2c;
        if (uVar4 == 0) {
          bVar1 = true;
        }
        if (*(char *)(iVar6 + 0xc) == '\0') {
          *(int *)(param_1 + 0x88) = *(int *)(param_1 + 0x88) + *(int *)(iVar6 + 4);
        }
        else {
          *(int *)(param_1 + 0x50) = *(int *)(param_1 + 0x50) + *(int *)(iVar6 + 4);
        }
        uVar5 = uVar5 + 1;
        if (*(uint *)(param_1 + 0x38) <= uVar5) goto LAB_0800c82a;
      } while ((!bVar2) || (!bVar1));
    }
  }
  return;
}




/* 0x0800c878 */
int FUN_0800c878(param_1)
int param_1;
{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  
  iVar3 = *(int *)(param_1 + 0xcc);
  puVar4 = *(uint **)(param_1 + 0xd0);
  iVar1 = FUN_0800cbd0(param_1,0);
  if ((iVar1 == 0) && (iVar1 = FUN_0800cade(param_1), iVar1 == 0)) {
    iVar1 = *(int *)(param_1 + 0xd0);
    if (*(int *)(iVar1 + 4) << 0x17 < 0) {
      *(undefined4 *)(iVar1 + 0xc) = 1;
      thunk_FUN_080199b4(*(undefined4 *)(param_1 + 0x298));
      if (*(int *)(iVar1 + 4) << 0x17 < 0) {
        return 0x30000106;
      }
    }
    *(int *)(param_1 + 600) = param_1 + 0xd8;
    *(int *)(param_1 + 0x25c) = param_1 + 0xd8;
    *(undefined4 *)(param_1 + 0xd4) = 0;
    *(undefined4 *)(param_1 + 0x260) = 0;
    *(undefined4 *)(param_1 + 0x264) = 0;
    *(undefined4 *)(param_1 + 0x268) = 0;
    *(undefined4 *)(param_1 + 0x26c) = 0;
    *(undefined4 *)(param_1 + 0x280) = 0;
    *(undefined4 *)(param_1 + 0x270) = 0;
    *(undefined4 *)(param_1 + 0x274) = 0;
    uVar2 = *(int *)(param_1 + 0x48) + 3;
    if (uVar2 < 0x40000) {
      if (*(uint *)(param_1 + 0x14) < uVar2 >> 2) {
        *(undefined4 *)(param_1 + 0x284) = 1;
      }
      else {
        *(undefined4 *)(param_1 + 0x284) = 0;
      }
      uVar2 = *(int *)(param_1 + 0x84) + 3;
      if (uVar2 < 0x40000) {
        *(uint *)(param_1 + 0x288) = (uint)(*(uint *)(param_1 + 0x10) < uVar2 >> 2);
        *(uint *)(iVar3 + 8) =
             *(int *)(param_1 + 0x284) << 10 | 0xc000U | *(int *)(param_1 + 0x288) << 0xc;
        if (*(int *)(param_1 + 0x284) == 0) {
          *(undefined4 *)(param_1 + 0x264) = *(undefined4 *)(param_1 + 0x14);
          *(undefined4 *)(iVar3 + 0x150) = *(undefined4 *)(param_1 + 0x48);
        }
        else {
          *(undefined4 *)(iVar3 + 0x100) = *(undefined4 *)(param_1 + 0x48);
        }
        if (*(int *)(param_1 + 0x288) == 0) {
          *(undefined4 *)(iVar3 + 0x208) = *(undefined4 *)(param_1 + 0x84);
        }
        else {
          *(undefined4 *)(iVar3 + 0x200) = *(undefined4 *)(param_1 + 0x84);
        }
        if (*(int *)(param_1 + 0x294) == 0) {
          iVar1 = 0x30000118;
        }
        else {
          uVar2 = *(uint *)(param_1 + 8) / (uint)(*(int *)(param_1 + 0x294) << 1) - 3;
          if (uVar2 < 3) {
            iVar1 = 0x30000119;
          }
          else {
            *puVar4 = uVar2 | 0x5000000;
            iVar1 = FUN_0800cbd0(param_1,1);
            if (iVar1 != 0) {
              FUN_0800cade(param_1);
              FUN_0800cbd0(param_1,0);
            }
          }
        }
      }
      else {
        iVar1 = 0x30000117;
      }
    }
    else {
      iVar1 = 0x30000116;
    }
  }
  return iVar1;
}




/* 0x0800c9d8 */
void FUN_0800c9d8(param_1, param_2, param_3, param_4)
int param_1; int * param_2; int param_3; int param_4;
{
  int iVar1;
  undefined1 *puVar2;
  uint uVar3;
  int iVar4;
  int local_28;
  int local_24;
  
  puVar2 = (undefined1 *)(param_1 + 0x7c);
  *(int *)(param_1 + 0x34) = *param_2;
  *(int *)(param_1 + 0x38) = param_2[1];
  *(undefined4 *)(param_1 + 0xc4) = 0;
  *(undefined4 *)(param_1 + 200) = 0;
  *(undefined4 *)(param_1 + 0xc0) = 0;
  *(undefined1 *)(param_1 + 0xbc) = 0;
  *(undefined1 *)(param_1 + 0xbd) = 1;
  local_28 = param_3;
  local_24 = param_4;
  FUN_0800cac8(param_1 + 0x40);
  *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x34);
  *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(param_1 + 0x38);
  FUN_0800e18e(param_1 + 0x40);
  FUN_0800cab2(puVar2);
  for (uVar3 = 0; uVar3 < *(uint *)(param_1 + 0x38); uVar3 = uVar3 + 1) {
    iVar4 = *param_2 + uVar3 * 0x10;
    if (*(char *)(iVar4 + 0xc) == '\0') {
      iVar1 = *(int *)(param_1 + 0x90) + 1;
      *(int *)(param_1 + 0x90) = iVar1;
      if (iVar1 == 1) {
        *(int *)(param_1 + 0x80) = iVar4;
        *puVar2 = 3;
        *(uint *)(param_1 + 0x94) = uVar3;
        FUN_0800e150(puVar2);
      }
      *(uint *)(param_1 + 0x98) = uVar3;
      *(int *)(param_1 + 0x88) = *(int *)(param_1 + 0x88) + *(int *)(iVar4 + 4);
    }
    else {
      *(int *)(param_1 + 0x50) = *(int *)(param_1 + 0x50) + *(int *)(iVar4 + 4);
    }
    FUN_0800c74a(iVar4,&local_28,&local_24);
    *(int *)(param_1 + 0x84) = *(int *)(param_1 + 0x84) + local_28;
    *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + local_24;
  }
  *(int *)(param_1 + 0x3c) =
       *(int *)(param_1 + 0x298) * (*(int *)(param_1 + 0x84) + *(int *)(param_1 + 0x48));
  return;
}




/* 0x0800cab2 */
void FUN_0800cab2(param_1)
undefined1 * param_1;
{
  *(undefined4 *)(param_1 + 0x20) = 0;
  *param_1 = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  return;
}




/* 0x0800cac8 */
void FUN_0800cac8(param_1)
undefined1 * param_1;
{
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *param_1 = 2;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  return;
}




/* 0x0800cade */
int FUN_0800cade(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uStack_18;
  
  iVar3 = *(int *)(param_1 + 0xd0);
  puVar2 = *(undefined4 **)(param_1 + 0xcc);
  puVar2[3] = 1;
  uStack_18 = param_4;
  iVar1 = FUN_0800cce8(param_1,&uStack_18);
  if (iVar1 == 0) {
    *puVar2 = 0x207;
    *(undefined4 *)(iVar3 + 8) = 1;
    iVar1 = 0;
  }
  return iVar1;
}




/* 0x0800cb02 */
void FUN_0800cb02(param_1)
int param_1;
{
  int iVar1;
  
  while (*(int *)(param_1 + 600) != *(int *)(param_1 + 0x25c)) {
    FUN_0800cb42(param_1,*(undefined4 *)(param_1 + 0x25c));
    iVar1 = *(int *)(param_1 + 0x25c) + 0x18;
    if (iVar1 == param_1 + 600) {
      iVar1 = param_1 + 0xd8;
    }
    *(int *)(param_1 + 0x25c) = iVar1;
  }
  return;
}




/* 0x0800cb42 */
void FUN_0800cb42(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  
  *(undefined4 *)(param_1 + 0x268) = *(undefined4 *)(param_2 + 4);
  *(undefined4 *)(param_1 + 0x26c) = *(undefined4 *)(param_2 + 8);
  *(undefined4 *)(param_1 + 0x280) = *(undefined4 *)(param_2 + 0x14);
  *(undefined4 *)(param_1 + 0x278) = *(undefined4 *)(param_2 + 0xc);
  *(undefined4 *)(param_1 + 0x27c) = *(undefined4 *)(param_2 + 0x10);
  if (*(int *)(param_2 + 8) << 0x17 < 0) {
    if ((*(int *)(param_1 + 0x284) == 1) && (*(int *)(param_2 + 8) << 0x13 < 0)) {
      *(int *)(param_1 + 0x264) = *(int *)(param_1 + 0x264) + *(int *)(param_1 + 0x18);
    }
    if (*(int *)(param_1 + 0x284) == 0) {
      *(undefined1 *)(param_1 + 0x40) = 4;
    }
  }
  if (*(int *)(param_2 + 8) << 0x15 < 0) {
    *(undefined1 *)(param_1 + 0x40) = 4;
  }
  if (*(int *)(param_2 + 8) << 0x16 < 0) {
    if (*(int *)(param_1 + 0x288) == 1) {
      iVar1 = *(int *)(param_1 + 0x20) + *(int *)(param_1 + 0x260);
    }
    else {
      iVar1 = *(int *)(param_1 + 0x260) + (*(uint *)(*(int *)(param_1 + 0xcc) + 0x214) & 0x1ff);
    }
    *(int *)(param_1 + 0x260) = iVar1;
  }
  return;
}




/* 0x0800cbd0 */
undefined4 FUN_0800cbd0(param_1, param_2, param_3, param_4)
int param_1; uint param_2; undefined4 param_3; uint param_4;
{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint local_18;
  
  iVar3 = *(int *)(param_1 + 0xcc);
  iVar4 = 100;
  local_18 = param_4;
  iVar1 = FUN_0800cce8(param_1,&local_18);
  if (iVar1 != 0) {
    return 0x30000102;
  }
  if (param_2 != (local_18 & 3)) {
    uVar2 = local_18 & 0xfffffffc;
    if (param_2 == 0) {
      uVar2 = uVar2 | 2;
      if ((local_18 & 3) == 3) {
        *(uint *)(iVar3 + 4) = uVar2;
      }
    }
    else if (param_2 == 1) {
      uVar2 = uVar2 | 1;
    }
    else {
      if (param_2 != 3) {
        return 0x30000115;
      }
      uVar2 = uVar2 | 3;
    }
    *(uint *)(iVar3 + 4) = uVar2;
    local_18 = *(uint *)(iVar3 + 4);
    do {
      if (param_2 == (local_18 & 3)) {
        if (iVar4 == 0) {
          return 0x30000103;
        }
        return 0;
      }
      thunk_FUN_080199b4(5);
      local_18 = *(uint *)(iVar3 + 4);
      iVar4 = iVar4 + -5;
    } while (iVar4 != 0);
    return 0x30000103;
  }
  return 0;
}




/* 0x0800cc4c */
int FUN_0800cc4c(param_1)
int param_1;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = *(int *)(param_1 + 0xcc);
  iVar1 = FUN_0800cade();
  if (iVar1 == 0) {
    uVar2 = *(uint *)(iVar5 + 8);
    iVar4 = 1 << (uVar2 & 3) + (0xeU >> (uVar2 & 3) & 1);
    iVar1 = 1 << ((uVar2 << 0x1b) >> 0x1d) + 1;
    *(int *)(param_1 + 0x18) = iVar4;
    *(int *)(param_1 + 0x1c) = iVar1;
    *(int *)(param_1 + 0x14) = iVar4 * iVar1;
    uVar3 = (uVar2 << 0x19) >> 0x1e;
    iVar1 = 1 << (0xeU >> uVar3 & 1) + uVar3;
    iVar4 = 1 << ((uVar2 << 0x16) >> 0x1d) + 1;
    *(int *)(param_1 + 0x20) = iVar1;
    *(int *)(param_1 + 0x24) = iVar4;
    *(int *)(param_1 + 0x10) = iVar1 * iVar4;
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(iVar5 + 0x30);
    if (*(char *)(param_1 + 0xc) == '\0') {
      uVar2 = *(uint *)(param_1 + 0x30);
    }
    else {
      iVar1 = FUN_0800d31c(*(undefined4 *)(param_1 + 0x290),&LAB_0800ca9e,param_1,&LAB_0800caa8,
                           param_1);
      if (iVar1 != 0) {
        return iVar1;
      }
      uVar2 = *(uint *)(param_1 + 0x30) | 0x40;
      *(uint *)(param_1 + 0x30) = uVar2;
    }
    *(uint *)(param_1 + 0x30) = uVar2 | 8;
    iVar1 = 0;
  }
  return iVar1;
}




/* 0x0800cce8 */
undefined4 FUN_0800cce8(param_1, param_2)
int param_1; int * param_2;
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0xcc);
  iVar2 = 100;
  while (iVar1 = *(int *)(iVar3 + 4), -1 < iVar1 << 0x1d) {
    if (iVar2 == 0) {
      return 0x30000102;
    }
    thunk_FUN_080199b4(5);
    iVar2 = iVar2 + -5;
  }
  if (iVar2 == 0) {
    return 0x30000102;
  }
  *param_2 = iVar1;
  return 0;
}




/* 0x0800cd1c */
int FUN_0800cd1c(param_1, param_2, param_3, param_4)
int param_1; int param_2; undefined4 * param_3; int * param_4;
{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  if (param_1 == 0) {
    iVar1 = 0x30000109;
  }
  else if (param_2 == 0) {
    iVar1 = 0x3000010c;
  }
  else if (param_4 == (int *)0x0) {
    iVar1 = 0x3000010e;
  }
  else {
    iVar1 = 0;
  }
  if (iVar1 == 0) {
    do {
      if (*(char *)(param_1 + 0x2a0) != '\x02') {
        iVar1 = 0x30000105;
LAB_0800cd94:
        *(int *)(param_1 + 0xc0) = iVar1;
        return iVar1;
      }
      if (((-1 < *(int *)(param_1 + 0x30) << 0x1c) && (iVar1 = FUN_0800cc4c(param_1), iVar1 != 0))
         || ((*(char *)(param_1 + 0xc) != '\0' &&
             (iVar1 = FUN_0800d23c(*(undefined4 *)(param_1 + 0x28c)), iVar1 != 0))))
      goto LAB_0800cd94;
      if (param_3 != (undefined4 *)0x0) {
        *(undefined4 **)(param_1 + 0x29c) = param_3;
        uVar2 = param_3[1];
        *(undefined4 *)(param_1 + 0x294) = *param_3;
        *(undefined4 *)(param_1 + 0x298) = uVar2;
      }
      FUN_0800c9d8(param_1,param_2);
      iVar1 = FUN_0800c878(param_1);
      if (iVar1 != 0) goto LAB_0800cd94;
      FUN_0800e1a8(param_1);
      FUN_0800e430(param_1);
      iVar1 = *(int *)(param_1 + 0xc4);
      iVar3 = *(int *)(param_1 + 200);
      *param_4 = *(int *)(param_1 + 0xc0);
      param_4[1] = iVar1;
      param_4[2] = iVar3;
    } while (false);
    iVar1 = *(int *)(param_1 + 0xc0);
  }
  return iVar1;
}




/* 0x0800cdc8 */
int FUN_0800cdc8(param_1)
int param_1;
{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar3 = 0;
  if (param_1 == 0) {
    return 0;
  }
  if (*(int *)(param_1 + 0x30) << 0x1d < 0) {
    puVar2 = &DAT_0805091c;
    for (iVar1 = DAT_0805091c; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x2a8)) {
      if (iVar1 == param_1) {
        *puVar2 = *(undefined4 *)(iVar1 + 0x2a8);
        break;
      }
      puVar2 = (undefined4 *)(iVar1 + 0x2a8);
    }
  }
  if (((*(int *)(param_1 + 0x30) << 0x1a < 0) &&
      (iVar1 = FUN_0800d240(*(undefined4 *)(param_1 + 0x2a4)), iVar1 != 0)) && (true)) {
    iVar3 = iVar1;
  }
  if (((*(int *)(param_1 + 0x30) << 0x1e < 0) &&
      (iVar1 = FUN_0800d240(*(undefined4 *)(param_1 + 0x28c)), iVar1 != 0)) && (iVar3 == 0)) {
    iVar3 = iVar1;
  }
  if (((*(int *)(param_1 + 0x30) << 0x19 < 0) &&
      (iVar1 = FUN_0800d324(*(undefined4 *)(param_1 + 0x290)), iVar1 != 0)) && (iVar3 == 0)) {
    iVar3 = iVar1;
  }
  if ((((*(uint *)(param_1 + 0x30) & 1) != 0) &&
      (iVar1 = FUN_0800cfe0(*(undefined4 *)(param_1 + 0x290)), iVar1 != 0)) && (iVar3 == 0)) {
    iVar3 = iVar1;
  }
  iVar1 = FUN_0800d2cc(param_1);
  if ((iVar1 != 0) && (iVar3 == 0)) {
    iVar3 = iVar1;
  }
  return iVar3;
}




/* 0x0800ce64 */
int FUN_0800ce64(param_1, param_2)
int param_1; undefined4 * param_2;
{
  int iVar1;
  int *local_20;
  
  for (local_20 = DAT_0805091c; local_20 != (int *)0x0; local_20 = (int *)local_20[0xaa]) {
    if (*local_20 == param_1) goto LAB_0800ce8e;
  }
  local_20 = (int *)0x0;
LAB_0800ce8e:
  if (local_20 == (int *)0x0) {
    iVar1 = FUN_0800d2ec(&local_20,0x2ac);
    if (iVar1 == 0) {
      iVar1 = FUN_0800d30c(local_20,0,0x2ac);
      if (iVar1 == 0) {
        *local_20 = param_1;
        local_20[0xc] = 0;
        do {
          iVar1 = FUN_0800d0d4(param_1,local_20 + 0xa4);
          if (iVar1 != 0) {
LAB_0800cf22:
            FUN_0800cdc8(local_20);
            return iVar1;
          }
          local_20[0xc] = local_20[0xc] | 1;
          iVar1 = FUN_0800d1e8(local_20[0xa4],local_20 + 1);
          if (iVar1 != 0) goto LAB_0800cf22;
          local_20[0x1e] = (int)(local_20 + 0xd);
          local_20[0x2e] = (int)(local_20 + 0xd);
          if ((char)local_20[3] != '\0') {
            iVar1 = FUN_0800d294(local_20 + 0xa3);
            if (iVar1 != 0) goto LAB_0800cf22;
            local_20[0xc] = local_20[0xc] | 2;
          }
          iVar1 = FUN_0800d258(local_20 + 0xa9);
          if (iVar1 != 0) goto LAB_0800cf22;
          local_20[0xa5] = 100;
          local_20[0xa6] = 200;
          local_20[0xc] = local_20[0xc] | 0x24;
          *(undefined1 *)(local_20 + 0xa8) = 0;
          local_20[0x33] = local_20[1];
          local_20[0x34] = local_20[1] + 0x400;
          local_20[0xaa] = (int)DAT_0805091c;
          DAT_0805091c = local_20;
          *param_2 = local_20;
          iVar1 = 0;
        } while (false);
      }
      else {
        FUN_0800d2cc();
      }
    }
  }
  else {
    *param_2 = local_20;
    iVar1 = 0;
  }
  return iVar1;
}




/* 0x0800cf6c */
int FUN_0800cf6c(param_1, param_2)
int param_1; undefined1 param_2;
{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = FUN_0800d1f8(*(undefined4 *)(param_1 + 0x290));
    if (iVar1 == 0) {
      *(undefined1 *)(param_1 + 0x2a0) = param_2;
    }
    return iVar1;
  }
  return 0x30000109;
}




/* 0x0800cf90 */
int FUN_0800cf90(param_1, param_2, param_3, param_4)
int param_1; int param_2; undefined4 param_3; undefined4 * param_4;
{
  int iVar1;
  int local_20 [2];
  undefined1 auStack_18 [4];
  undefined4 local_14;
  
  if (param_1 == 0) {
    iVar1 = 0x30000109;
  }
  else if (param_2 == 0) {
    iVar1 = 0x3000010a;
  }
  else if (param_4 == (undefined4 *)0x0) {
    iVar1 = 0x3000010e;
  }
  else {
    iVar1 = 0;
  }
  if (iVar1 == 0) {
    if (*(char *)(param_2 + 0xc) == '\x01') {
      local_20[1] = 1;
      local_20[0] = param_2;
      iVar1 = FUN_0800cd1c(param_1,local_20,param_3,auStack_18);
      *param_4 = local_14;
    }
    else {
      iVar1 = 0x30000112;
    }
  }
  return iVar1;
}




/* 0x0800cfe0 */
int FUN_0800cfe0(param_1)
int param_1;
{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = 0;
  if (*(int *)(param_1 + 0x1c) != 0) {
    if ((int)((uint)*(byte *)(param_1 + 0x28) << 0x1b) < 0) {
      for (uVar2 = 0; uVar2 < *(uint *)(param_1 + 0x1c); uVar2 = uVar2 + 1) {
        iVar1 = FUN_0800bb74(*(undefined4 *)(param_1 + 0x24),
                             *(undefined4 *)(*(int *)(param_1 + 0x18) + uVar2 * 4),0);
        if (iVar1 != 0) {
          iVar3 = -0x1ffffff7;
          goto LAB_0800d03a;
        }
      }
      iVar1 = (**(code **)(*(int *)((*(uint *)(param_1 + 0x24) & 0xfffffffe) + 4) + 0x14))();
      if (iVar1 != 0) {
        iVar3 = -0x1ffffff8;
        goto LAB_0800d03a;
      }
    }
    if (((int)((uint)*(byte *)(param_1 + 0x28) << 0x1c) < 0) &&
       (iVar1 = FUN_0800b874(*(undefined4 *)(param_1 + 0x24)), iVar1 != 0)) {
      iVar3 = -0x1ffffffa;
    }
  }
LAB_0800d03a:
  iVar1 = FUN_0800d2cc(param_1);
  if (iVar3 != 0) {
    iVar1 = iVar3;
  }
  return iVar1;
}




/* 0x0800d050 */
undefined4 FUN_0800d050(param_1)
int param_1;
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  if (*(int *)(param_1 + 0x1c) != 0) {
    if ((*(int *)(param_1 + 0x24) == 0) &&
       ((iVar1 = FUN_0800b7ea(0,0x2000020,0x10001,param_1 + 0x24), iVar1 != 0 ||
        (*(int *)(param_1 + 0x24) == 0)))) {
      return 0xe0000005;
    }
    *(byte *)(param_1 + 0x28) = *(byte *)(param_1 + 0x28) | 8;
    uVar2 = *(uint *)(param_1 + 0x24) & 0xfffffffe;
    iVar1 = (**(code **)(*(int *)(uVar2 + 4) + 0x10))(uVar2,1);
    if (iVar1 == 0) {
      uVar2 = 0;
      *(byte *)(param_1 + 0x28) = *(byte *)(param_1 + 0x28) | 0x10;
      while( true ) {
        if (*(uint *)(param_1 + 0x1c) <= uVar2) {
          return 0;
        }
        iVar1 = FUN_0800bb74(*(undefined4 *)(param_1 + 0x24),
                             *(undefined4 *)(*(int *)(param_1 + 0x18) + uVar2 * 4),1);
        if (iVar1 != 0) break;
        uVar2 = uVar2 + 1;
      }
      return 0xe0000009;
    }
    uVar3 = 0xe0000007;
  }
  return uVar3;
}




/* 0x0800d0d4 */
int FUN_0800d0d4(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 * param_2; undefined4 param_3; undefined4 * param_4;
{
  int iVar1;
  undefined4 *local_18;
  
  local_18 = param_4;
  iVar1 = FUN_0800d2ec(&local_18,0x2c);
  if (iVar1 == 0) {
    iVar1 = FUN_0800d30c(local_18,0,0x2c);
    if (((iVar1 == 0) && (iVar1 = FUN_0800d11c(param_1,local_18), iVar1 == 0)) &&
       (iVar1 = FUN_0800d050(local_18), iVar1 == 0)) {
      *local_18 = param_1;
      *param_2 = local_18;
    }
    else {
      FUN_0800cfe0(local_18);
    }
  }
  return iVar1;
}




/* 0x0800d11c */
undefined4 FUN_0800d11c(param_1, param_2)
undefined4 param_1; int param_2;
{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_20 [4];
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 auStack_14 [8];
  
  iVar1 = thunk_FUN_08010668(param_1,auStack_14);
  if (iVar1 == 0) {
    uVar2 = 0xe0000003;
    iVar1 = thunk_FUN_080106aa(auStack_14,"CHIP_CLK_INDEX",0,auStack_20);
    if (iVar1 == 0) {
      *(char *)(param_2 + 4) = (char)local_18;
      iVar1 = thunk_FUN_080106aa(auStack_14,"CHIP_QUP_BASE_ADDR",0,auStack_20);
      if (iVar1 == 0) {
        *(undefined4 *)(param_2 + 0xc) = local_18;
        iVar1 = thunk_FUN_080106aa(auStack_14,"CHIP_GPIO_CONFIG_ARR",0,auStack_20);
        if (iVar1 == 0) {
          *(undefined4 *)(param_2 + 0x18) = local_18;
        }
        else {
          local_1c = 0;
        }
        *(undefined4 *)(param_2 + 0x1c) = local_1c;
        iVar1 = thunk_FUN_080106aa(auStack_14,"CHIP_APPS_CLK_FREQ_KHZ",0,auStack_20);
        if (iVar1 == 0) {
          uVar2 = 0;
          *(undefined4 *)(param_2 + 0x10) = local_18;
        }
      }
    }
  }
  else {
    uVar2 = 0xe0000002;
  }
  return uVar2;
}




/* 0x0800d1e8 */
undefined4 FUN_0800d1e8(param_1, param_2)
int param_1; undefined4 * param_2;
{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 0x10);
  uVar1 = *(undefined4 *)(param_1 + 0x14);
  *param_2 = *(undefined4 *)(param_1 + 0xc);
  param_2[1] = uVar2;
  param_2[2] = uVar1;
  return 0;
}




/* 0x0800d1f8 */
int FUN_0800d1f8(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  if ((param_2 == 0) || (param_2 == 1)) {
    iVar1 = FUN_0800a7c4(*(undefined1 *)(param_1 + 4));
    if (iVar1 == 0) {
      iVar2 = -0x1ffffff5;
    }
  }
  else {
    if (param_2 != 2) {
      return -0x1ffffffc;
    }
    iVar1 = FUN_0800ae8c(1,*(undefined1 *)(param_1 + 4));
    if (iVar1 == 0) {
      iVar2 = -0x1ffffff6;
    }
  }
  if (iVar2 != 0) {
    return iVar2;
  }
  *(int *)(param_1 + 8) = param_2;
  return 0;
}




/* 0x0800d23c */
undefined4 FUN_0800d23c()
{
  return 0;
}




/* 0x0800d240 */
undefined4 FUN_0800d240(param_1)
char * param_1;
{
  undefined4 uVar1;
  
  if (*param_1 == '\0') {
    return 0;
  }
  if (*param_1 != '\x01') {
    return 0xf000000f;
  }
  uVar1 = FUN_0800d298();
  return uVar1;
}




/* 0x0800d258 */
int FUN_0800d258(param_1, param_2, param_3, param_4)
undefined4 * param_1; undefined4 param_2; undefined4 param_3; undefined1 * param_4;
{
  int iVar1;
  int iVar2;
  undefined1 *local_10;
  
  local_10 = param_4;
  iVar1 = FUN_0800d2ec(&local_10,0x30);
  if (iVar1 == 0) {
    iVar2 = FUN_0800b634(0x10,local_10 + 4,local_10 + 8);
    if (iVar2 == 0) {
      *local_10 = 1;
      *param_1 = local_10;
    }
    else {
      FUN_0800d2cc(local_10);
      iVar1 = -0xffffff3;
    }
  }
  return iVar1;
}




/* 0x0800d294 */
undefined4 FUN_0800d294()
{
  return 0;
}




/* 0x0800d298 */
undefined4 FUN_0800d298(param_1)
int param_1;
{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0800b550(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = FUN_0800d2cc(param_1);
  }
  else {
    uVar2 = 0xf000000e;
    FUN_0800d2cc(param_1);
  }
  return uVar2;
}




/* 0x0800d2c0 */
undefined4 FUN_0800d2c0(param_1)
int param_1;
{
  FUN_0800b648(*(undefined4 *)(param_1 + 4));
  return 0;
}




/* 0x0800d2cc */
undefined4 FUN_0800d2cc()
{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0800b574();
  uVar2 = 0;
  if (iVar1 != 0) {
    uVar2 = 0xf0000004;
  }
  return uVar2;
}




/* 0x0800d2ec */
undefined4 FUN_0800d2ec(param_1, param_2, param_3, param_4)
int * param_1; undefined4 param_2; undefined4 param_3; int param_4;
{
  int iVar1;
  int local_10;
  
  local_10 = param_4;
  iVar1 = FUN_0800b61e(param_2,&local_10);
  if ((iVar1 == 0) && (local_10 != 0)) {
    *param_1 = local_10;
    return 0;
  }
  return 0xf0000005;
}




/* 0x0800d30c */
undefined4 FUN_0800d30c(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  FUN_08006cc0(param_1,param_3,param_2);
  return 0;
}




/* 0x0800d31c */
undefined4 FUN_0800d31c()
{
  return 0;
}




/* 0x0800d320 */
undefined4 FUN_0800d320()
{
  return 0;
}




/* 0x0800d324 */
undefined4 FUN_0800d324()
{
  return 0;
}




/* 0x0800d328 */
undefined4 FUN_0800d328()
{
  return 0;
}




/* 0x0800d330 */
undefined4 FUN_0800d330(param_1)
undefined4 param_1;
{
  int iVar1;
  char *pcVar2;
  undefined4 local_20;
  int local_1c;
  int local_18;
  undefined1 auStack_14 [8];
  int local_c;
  
  iVar1 = dal_device_attach(param_1,auStack_14);
  if (iVar1 != 0) {
    return 2;
  }
  iVar1 = thunk_FUN_080106aa(auStack_14,"TargetId",0,&local_20);
  if (iVar1 == 0) {
    if ((DAT_0804d160 == 0) && (iVar1 = FUN_0800b7ea(0,0x200006f,0x10000,&DAT_0804d160), iVar1 != 0)
       ) {
      local_c = 0;
    }
    else if ((DAT_0804d160 & 1) == 0) {
      (**(code **)(*(int *)(DAT_0804d160 + 4) + 0x38))(DAT_0804d160,0);
    }
    else {
      (**(code **)(*(int *)((DAT_0804d160 & 0xfffffffe) + 4) + 0x2c))
                (0xe,DAT_0804d160 & 0xfffffffe,0,&local_c);
    }
    if (local_c == local_18) {
      pcVar2 = "icb_config_data_ext";
      goto LAB_0800d3ba;
    }
  }
  pcVar2 = "icb_config_data";
LAB_0800d3ba:
  iVar1 = thunk_FUN_080106aa(auStack_14,pcVar2,0,&local_20);
  if (((iVar1 == 0) && (local_1c != 0)) &&
     (iVar1 = FUN_0800d400(local_20,local_1c,local_18), iVar1 == 0)) {
    return 0;
  }
  return 2;
}




/* 0x0800d330 */
undefined4 thunk_FUN_0800d330(param_1)
undefined4 param_1;
{
  int iVar1;
  char *pcVar2;
  undefined4 uStack_20;
  int iStack_1c;
  int iStack_18;
  undefined1 auStack_14 [8];
  int iStack_c;
  
  iVar1 = dal_device_attach(param_1,auStack_14);
  if (iVar1 != 0) {
    return 2;
  }
  iVar1 = thunk_FUN_080106aa(auStack_14,"TargetId",0,&uStack_20);
  if (iVar1 == 0) {
    if ((DAT_0804d160 == 0) && (iVar1 = FUN_0800b7ea(0,0x200006f,0x10000,&DAT_0804d160), iVar1 != 0)
       ) {
      iStack_c = 0;
    }
    else if ((DAT_0804d160 & 1) == 0) {
      (**(code **)(*(int *)(DAT_0804d160 + 4) + 0x38))(DAT_0804d160,0);
    }
    else {
      (**(code **)(*(int *)((DAT_0804d160 & 0xfffffffe) + 4) + 0x2c))
                (0xe,DAT_0804d160 & 0xfffffffe,0,&iStack_c);
    }
    if (iStack_c == iStack_18) {
      pcVar2 = "icb_config_data_ext";
      goto LAB_0800d3ba;
    }
  }
  pcVar2 = "icb_config_data";
LAB_0800d3ba:
  iVar1 = thunk_FUN_080106aa(auStack_14,pcVar2,0,&uStack_20);
  if (((iVar1 == 0) && (iStack_1c != 0)) &&
     (iVar1 = FUN_0800d400(uStack_20,iStack_1c,iStack_18), iVar1 == 0)) {
    return 0;
  }
  return 2;
}




/* 0x0800d400 */
undefined4 FUN_0800d400(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; uint * param_3;
{
  undefined4 uVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  byte bVar8;
  ushort uVar9;
  
  uVar1 = 0;
  uVar7 = param_3[1];
  uVar4 = 0;
  while( true ) {
    if (*param_3 <= uVar4) {
      return uVar1;
    }
    iVar2 = uVar7 + uVar4 * 0x14;
    puVar3 = *(uint **)(iVar2 + 4);
    if ((puVar3 == (uint *)0x0) && (*(int *)(uVar7 + uVar4 * 0x14) != 1)) break;
    iVar5 = *(int *)(uVar7 + uVar4 * 0x14);
    if (iVar5 == 1) {
      return 0;
    }
    if (iVar5 == 2) {
      uVar6 = *(uint *)(iVar2 + 8);
      if (uVar6 == *(uint *)(iVar2 + 0xc)) {
        uVar6 = *(uint *)(iVar2 + 0x10) & uVar6;
      }
      else {
        uVar6 = *puVar3 & *(uint *)(iVar2 + 0xc) & ~uVar6 | *(uint *)(iVar2 + 0x10) & uVar6;
      }
      *puVar3 = uVar6;
    }
    else if (iVar5 == 3) {
      uVar9 = (ushort)*(int *)(iVar2 + 8);
      if (*(int *)(iVar2 + 8) == *(int *)(iVar2 + 0xc)) {
        uVar9 = (ushort)*(undefined4 *)(iVar2 + 0x10) & uVar9;
      }
      else {
        uVar9 = (ushort)*puVar3 & (ushort)*(int *)(iVar2 + 0xc) & ~uVar9 |
                (ushort)*(undefined4 *)(iVar2 + 0x10) & uVar9;
      }
      *(ushort *)puVar3 = uVar9;
    }
    else if (iVar5 == 4) {
      bVar8 = (byte)*(int *)(iVar2 + 8);
      if (*(int *)(iVar2 + 8) == *(int *)(iVar2 + 0xc)) {
        bVar8 = (byte)*(undefined4 *)(iVar2 + 0x10) & bVar8;
      }
      else {
        bVar8 = (byte)*puVar3 & (byte)*(int *)(iVar2 + 0xc) & ~bVar8 |
                (byte)*(undefined4 *)(iVar2 + 0x10) & bVar8;
      }
      *(byte *)puVar3 = bVar8;
    }
    else {
      uVar1 = 1;
    }
    uVar4 = uVar4 + 1;
  }
  return 1;
}




/* 0x0800d4ba */
undefined4 FUN_0800d4ba(param_1, param_2, param_3, param_4)
int param_1; int param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  
  uVar2 = 0xffffffff;
  if ((param_1 == 0) || (param_2 == 0)) {
    uVar2 = 1;
  }
  else {
    local_10 = param_4;
    iVar1 = FUN_08021d54(param_1,&local_10);
    if (iVar1 != 0) {
      FUN_080221f8(local_10,0,param_2);
      FUN_08019dbe(local_10,1,param_2);
      uVar2 = 0;
    }
  }
  return uVar2;
}




/* 0x0800d4ec */
undefined4 FUN_0800d4ec(param_1, param_2)
undefined4 param_1; int param_2;
{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_100 [240];
  undefined4 *local_10;
  
  uVar2 = 2;
  if (param_2 == 0) {
    uVar2 = 1;
  }
  else {
    iVar1 = FUN_08021d54(param_1,&local_10);
    if (iVar1 != 0) {
      FUN_0801a2bc(param_2,*local_10,auStack_100);
      FUN_08019dbe(local_10,1,auStack_100);
      thunk_FUN_00221cf2(local_10[4]);
      FUN_080277a4(local_10,auStack_100);
      uVar2 = 0;
    }
  }
  return uVar2;
}




/* 0x0800d4ec */
undefined4 thunk_FUN_0800d4ec(param_1, param_2)
undefined4 param_1; int param_2;
{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_100 [240];
  undefined4 *puStack_10;
  
  uVar2 = 2;
  if (param_2 == 0) {
    uVar2 = 1;
  }
  else {
    iVar1 = FUN_08021d54(param_1,&puStack_10);
    if (iVar1 != 0) {
      FUN_0801a2bc(param_2,*puStack_10,auStack_100);
      FUN_08019dbe(puStack_10,1,auStack_100);
      thunk_FUN_00221cf2(puStack_10[4]);
      FUN_080277a4(puStack_10,auStack_100);
      uVar2 = 0;
    }
  }
  return uVar2;
}




/* 0x0800d534 */
undefined4 FUN_0800d534()
{
  int iVar1;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar1 = 0;
  while( true ) {
    if (*(int *)(DAT_0804e268 + 0x10) == 0) {
      *(undefined4 *)(DAT_0804e268 + 0x10) = 1;
      return 0;
    }
    if (500 < iVar1) break;
    local_1c = 0;
    iVar1 = iVar1 + 1;
    local_20 = DAT_0804e26c;
    FUN_0800b56e(&local_20,1,1000,&local_1c);
  }
  return 0xffffffff;
}




/* 0x0800d57c */
void FUN_0800d57c()
{
  *(undefined4 *)(DAT_0804e268 + 0x10) = 0;
  return;
}




/* 0x0800d58c */
bool FUN_0800d58c()
{
  return DAT_0804d184 != -1;
}




/* 0x0800d59c */
void FUN_0800d59c(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  undefined4 local_38;
  undefined1 *local_34;
  undefined4 uStack_30;
  undefined1 auStack_2c [4];
  undefined1 auStack_28 [4];
  undefined1 auStack_24 [4];
  undefined1 auStack_20 [8];
  
  local_38 = 0;
  FUN_08006e1a(param_2,auStack_28);
  FUN_08006e1a(param_1,auStack_2c);
  uStack_30 = 1;
  local_34 = auStack_24;
  FUN_08006e1a(0x20,auStack_20);
  FUN_08006e1a(param_3,auStack_24);
  FUN_08009de0();
  FUN_08009980(&local_38,2);
  FUN_08009af4(local_38,auStack_2c,1);
  FUN_08009830(local_38,&local_34);
  FUN_08009804(&local_38);
  thunk_FUN_0800947c();
  return;
}




/* 0x0800d604 */
undefined4 FUN_0800d604(param_1)
int * param_1;
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = FUN_0800d694();
  if (iVar1 == 0) {
    FUN_0800b424();
    iVar1 = param_1[5];
    iVar2 = FUN_0800b388("DAL_PLATFORM_INFO",iVar1 * 8 + 0x34,0x10000,param_1);
    if (iVar2 == 0) {
      iVar2 = *param_1;
      iVar5 = param_1[4];
      iVar3 = param_1[2];
      iVar4 = param_1[3];
      *(int *)(iVar2 + 0x20) = param_1[1];
      *(int *)(iVar2 + 0x24) = iVar3;
      *(int *)(iVar2 + 0x28) = iVar4;
      *(int *)(iVar2 + 0x2c) = iVar5;
      *(int *)(*param_1 + 0x30) = param_1[5];
      FUN_08027bf8(*param_1 + 0x34,iVar1 * 8,param_1[6]);
    }
    iVar1 = FUN_0800d880(param_1);
    if (iVar1 == 0) {
      return 0;
    }
  }
  return 0xffffffff;
}




/* 0x0800d694 */
undefined4 FUN_0800d694(param_1, param_2, param_3, param_4)
int param_1; byte * param_2; undefined4 param_3; undefined4 param_4;
{
  uint uVar1;
  int iVar2;
  undefined4 local_20;
  
  if (DAT_08050f8c == '\x01') {
    return 0;
  }
  if (param_2 == (byte *)0x0) {
    return 0xffffffff;
  }
  *(uint *)(param_1 + 4) = (uint)param_2[1];
  *(uint *)(param_1 + 8) = (uint)param_2[3] | (uint)param_2[2] << 0x10;
  if (1 < *param_2) {
    *(uint *)(param_1 + 0xc) = (uint)param_2[4];
  }
  if (2 < *param_2) {
    uVar1 = (uint)param_2[5];
    *(uint *)(param_1 + 0x14) = uVar1;
    local_20 = param_4;
    if (uVar1 != 0) {
      iVar2 = FUN_0800b61e(uVar1 << 3,param_1 + 0x18);
      if (iVar2 != 0) {
        return 0xffffffff;
      }
      for (uVar1 = 0; uVar1 < *(uint *)(param_1 + 0x14); uVar1 = uVar1 + 1) {
        *(uint *)(*(int *)(param_1 + 0x18) + uVar1 * 8) = (uint)param_2[uVar1 * 2 + 6];
        *(uint *)(*(int *)(param_1 + 0x18) + uVar1 * 8 + 4) = (uint)param_2[uVar1 * 2 + 7];
      }
    }
    iVar2 = FUN_0800d7c0(param_1,4,&local_20);
    if (iVar2 == 0) {
      *(char *)(param_1 + 0x10) = (char)local_20;
    }
    else {
      iVar2 = FUN_0800ba1c();
      if (iVar2 == 0x20) {
        if (*(int *)(param_1 + 4) != 1) {
          DAT_08050f8c = 1;
          return 0;
        }
      }
      else {
        if (iVar2 != 0x23) {
          DAT_08050f8c = 1;
          return 0;
        }
        if ((*(int *)(param_1 + 4) != 1) && (*(int *)(param_1 + 4) != 8)) {
          DAT_08050f8c = 1;
          return 0;
        }
      }
      if (*(int *)(param_1 + 0xc) == 1) {
        *(undefined1 *)(param_1 + 0x10) = 1;
      }
    }
  }
  DAT_08050f8c = 1;
  return 0;
}




/* 0x0800d750 */
int FUN_0800d750(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 * param_3;
{
  int iVar1;
  
  *param_3 = 0;
  iVar1 = FUN_0800b1b6(param_2,&DAT_0804e2f0,&DAT_0805a110);
  if (iVar1 == 0) {
    DAT_0805a120 = 0xda1fda1f;
    DAT_0805a124 = &PTR_FUN_0800d750_1_0803ce34;
    DAT_0805a128 = &DAT_0805a110;
    FUN_0800b19a();
    *param_3 = &DAT_0805a120;
  }
  return iVar1;
}




/* 0x0800d7c0 */
undefined4 FUN_0800d7c0(param_1, param_2, param_3)
int param_1; int param_2; undefined4 * param_3;
{
  uint uVar1;
  
  if (param_3 != (undefined4 *)0x0) {
    for (uVar1 = 0; uVar1 < *(uint *)(param_1 + 0x14); uVar1 = uVar1 + 1) {
      if (*(int *)(*(int *)(param_1 + 0x18) + uVar1 * 8) == param_2) {
        *param_3 = *(undefined4 *)(*(int *)(param_1 + 0x18) + uVar1 * 8 + 4);
        return 0;
      }
    }
  }
  return 0xffffffff;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800d820 */
undefined4 FUN_0800d820(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; uint param_4;
{
  int iVar1;
  uint local_10;
  
  local_10 = param_4;
  iVar1 = FUN_0800ba1c();
  if ((iVar1 != 0x20) ||
     (((DAT_08050f90 != 0 || (iVar1 = FUN_0800b7ea(0,0x200006f,0x10000,&DAT_08050f90), iVar1 == 0))
      && (FUN_0800babc(DAT_08050f90,&local_10), 0x1ffff < local_10)))) {
    _DAT_00060b00 = *(undefined4 *)(param_1 + 4);
    _DAT_00060b04 = *(undefined4 *)(param_1 + 8);
    _DAT_00060b08 = *(undefined4 *)(param_1 + 0xc);
    _DAT_00060b0c = *(undefined4 *)(param_1 + 0x10);
    _DAT_00060b10 = *(int *)(param_1 + 0x14);
    if (_DAT_00060b10 != 0) {
      FUN_08027bf8(0x60b14,_DAT_00060b10 << 3,*(undefined4 *)(param_1 + 0x18),_DAT_00060b10 << 3);
    }
  }
  return 0;
}




/* 0x0800d880 */
undefined4 FUN_0800d880(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; int param_3; uint param_4;
{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint local_28;
  uint local_24;
  int local_20;
  uint uStack_1c;
  
  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  uStack_1c = param_4;
  puVar1 = (undefined4 *)FUN_080373b8(0x89,100);
  if (puVar1 == (undefined4 *)0x0) {
    uVar3 = 0xffffffff;
  }
  else {
    FUN_08006d14(puVar1,100);
    *puVar1 = 10;
    FUN_080382c2(puVar1 + 3,"8909A-DAADANAZA-10139",0x20);
    iVar2 = FUN_0800b7b4(0x200006f,&local_28);
    if (iVar2 == 0) {
      if ((local_28 & 1) == 0) {
        (**(code **)(*(int *)(local_28 + 4) + 0x2c))(local_28,0);
      }
      else {
        (**(code **)(*(int *)((local_28 & 0xfffffffe) + 4) + 0x2c))
                  (0xb,local_28 & 0xfffffffe,0,puVar1 + 1);
      }
      FUN_0800babc(local_28,puVar1 + 2);
      if ((local_28 & 1) == 0) {
        (**(code **)(*(int *)(local_28 + 4) + 0x30))(local_28,0);
      }
      else {
        (**(code **)(*(int *)((local_28 & 0xfffffffe) + 4) + 0x2c))
                  (0xc,local_28 & 0xfffffffe,0,puVar1 + 0xb);
      }
      if ((local_28 & 1) == 0) {
        (**(code **)(*(int *)(local_28 + 4) + 0x28))(local_28,0);
      }
      else {
        (**(code **)(*(int *)((local_28 & 0xfffffffe) + 4) + 0x2c))
                  (10,local_28 & 0xfffffffe,0,puVar1 + 0xc);
      }
      if ((local_28 & 1) == 0) {
        (**(code **)(*(int *)(local_28 + 4) + 0x40))(local_28,0);
      }
      else {
        (**(code **)(*(int *)((local_28 & 0xfffffffe) + 4) + 0x2c))
                  (0x10,local_28 & 0xfffffffe,0,puVar1 + 0x17);
      }
      if ((local_28 & 1) == 0) {
        (**(code **)(*(int *)(local_28 + 4) + 0x44))(local_28,0);
      }
      else {
        (**(code **)(*(int *)((local_28 & 0xfffffffe) + 4) + 0x2c))
                  (0x11,local_28 & 0xfffffffe,0,puVar1 + 0x18);
      }
    }
    uVar4 = 0;
    do {
      iVar2 = FUN_0802b658(uVar4,&local_24);
      if (iVar2 == 0) {
        puVar1[uVar4 * 2 + 0x11] = local_24 | 0x10000;
        puVar1[uVar4 * 2 + 0x12] = uStack_1c | local_20 << 0x10;
      }
      else {
        puVar1[uVar4 * 2 + 0x11] = 0x7fffffff;
        puVar1[uVar4 * 2 + 0x12] = 0;
      }
      uVar4 = uVar4 + 1 & 0xff;
    } while (uVar4 < 3);
    puVar1[0xd] = *(undefined4 *)(param_1 + 4);
    puVar1[0xe] = *(undefined4 *)(param_1 + 8);
    puVar1[0x10] = *(undefined4 *)(param_1 + 0xc);
    puVar1[0xf] = (uint)*(byte *)(param_1 + 0x10);
    uVar3 = 0;
  }
  return uVar3;
}




/* 0x0800d9d0 */
undefined4 FUN_0800d9d0(param_1, param_2, param_3)
uint param_1; char param_2; int param_3;
{
  uint uVar1;
  uint uVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  char *pcVar7;
  short sVar8;
  uint uVar9;
  int iVar10;
  bool bVar11;
  
  if (param_1 < 0x80) {
    iVar4 = param_1 * 5;
    pcVar7 = &DAT_08054834 + iVar4;
    bVar11 = (&DAT_08054634)[param_3] == -0x8000;
    if (bVar11) {
      (&DAT_08054634)[param_3] = (short)param_1;
    }
    uVar9 = (uint)(short)(&DAT_08054634)[param_3];
    iVar10 = uVar9 * 5;
    uVar2 = uVar9;
    if (!bVar11) {
      do {
        uVar9 = uVar2;
        iVar10 = uVar9 * 5;
        uVar1 = (int)((uint)(byte)(&DAT_08054838)[iVar10] << 0x18) >> 0x10;
        if (uVar9 == param_1) {
          *pcVar7 = param_2;
          goto LAB_0800dab8;
        }
        uVar2 = (byte)(&DAT_08054837)[iVar10] | uVar1;
      } while (uVar1 >> 0xf == 0);
    }
    sVar8 = (short)uVar9;
    if (*pcVar7 != -1) {
      uVar2 = (int)((uint)(byte)(&DAT_08054838)[iVar4] << 0x18) >> 0x10;
      if (uVar2 >> 0xf == 0) {
        uVar3 = (&DAT_08054836)[iVar4];
        iVar5 = ((byte)(&DAT_08054837)[iVar4] | uVar2) * 5;
        (&DAT_08054835)[iVar5] = (&DAT_08054835)[iVar4];
        (&DAT_08054836)[iVar5] = uVar3;
      }
      uVar2 = (int)((uint)(byte)(&DAT_08054836)[iVar4] << 0x18) >> 0x10;
      if (uVar2 >> 0xf == 0) {
        uVar3 = (&DAT_08054838)[iVar4];
        iVar5 = ((byte)(&DAT_08054835)[iVar4] | uVar2) * 5;
        (&DAT_08054837)[iVar5] = (&DAT_08054837)[iVar4];
        (&DAT_08054838)[iVar5] = uVar3;
      }
      else {
        (&DAT_08054634)[(uint)(byte)(&DAT_08054835)[iVar4] | uVar2 & 0x7fff] =
             (ushort)(byte)(&DAT_08054837)[iVar4] |
             (ushort)(((uint)(byte)(&DAT_08054838)[iVar4] << 0x18) >> 0x10);
      }
    }
    (&DAT_08054837)[iVar10] = (char)param_1;
    (&DAT_08054838)[iVar10] = (char)(param_1 >> 8);
    *pcVar7 = param_2;
    if (bVar11) {
      sVar8 = (short)param_3 + -0x8000;
    }
    (&DAT_08054835)[iVar4] = (char)sVar8;
    (&DAT_08054836)[iVar4] = (char)((ushort)sVar8 >> 8);
    (&DAT_08054837)[iVar4] = 0;
    (&DAT_08054838)[iVar4] = 0x80;
LAB_0800dab8:
    uVar6 = 0;
  }
  else {
    uVar6 = 0x18;
  }
  return uVar6;
}




/* 0x0800dae4 */
undefined4 FUN_0800dae4()
{
  return 0;
}




/* 0x0800dae8 */
int FUN_0800dae8(param_1, param_2, param_3, param_4, param_5, param_6, param_7)
int param_1; int param_2; uint param_3; uint param_4; int param_5; uint param_6; int * param_7;
{
  undefined1 *puVar1;
  bool bVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  byte local_40 [4];
  undefined4 local_3c;
  int local_38;
  int local_34;
  int iStack_30;
  uint uStack_2c;
  uint uStack_28;
  
  iVar8 = 0;
  bVar2 = false;
  if (param_3 < 0x10) {
    if ((param_5 == 0) || (param_6 == 0)) {
      iVar8 = 0xf;
    }
    else {
      if (param_7 == (int *)0x0) {
        param_7 = &local_38;
      }
      local_34 = param_1;
      iStack_30 = param_2;
      uStack_2c = param_3;
      uStack_28 = param_4;
      *param_7 = 0;
      iVar3 = FUN_0800dc88(param_3,param_4 >> 8,local_40);
      if (iVar3 == 0) {
        if (local_34 == 0) {
          bVar2 = true;
        }
        else {
          if (local_34 != 1) {
            return 3;
          }
          iVar8 = 1;
        }
        do {
          iVar3 = DAT_0804d44c + (uint)DAT_0805462c * 0x1000 + (uint)local_40[0] * 0x8000;
          if (iVar8 == 0) {
            iVar3 = iVar3 + 0x400000;
          }
          else {
            iVar3 = iVar3 + 0xc00000;
          }
          if ((*(uint *)(iVar3 + 8) & 1) == 0) {
            return 1;
          }
          uVar7 = param_6;
          if (8 < param_6) {
            uVar7 = 8;
          }
          if (bVar2) {
            FUN_08038c54((uint)local_40[0],*param_7 + param_5,uVar7);
          }
          uVar6 = *param_7 + (param_4 & 0xff) & 0xff;
          if (iVar8 == 0) {
            uVar6 = local_34 << 0x1b | iStack_30 << 0x1a | uVar6 << 4;
            puVar4 = (uint *)(DAT_0804d44c + (uint)DAT_0805462c * 0x1000 +
                              (uint)local_40[0] * 0x8000 + 0x400000);
          }
          else {
            uVar6 = local_34 << 0x1b | uVar6 << 4;
            puVar4 = (uint *)(DAT_0804d44c + (uint)DAT_0805462c * 0x1000 +
                              (uint)local_40[0] * 0x8000 + 0xc00000);
          }
          *puVar4 = uVar6 | uVar7 - 1;
          iVar3 = FUN_08038ba4(iVar8,local_40[0]);
          if (iVar3 != 0) {
            return iVar3;
          }
          if (iVar8 != 0) {
            iVar3 = *param_7;
            local_3c = *(undefined4 *)
                        (DAT_0804d44c + (uint)DAT_0805462c * 0x1000 + (uint)local_40[0] * 0x8000 +
                        0xc00018);
            uVar5 = 0;
            uVar6 = uVar7;
            do {
              if (uVar6 == 0) goto LAB_0800dc6e;
              uVar6 = uVar6 - 1;
              *(undefined1 *)(iVar3 + param_5 + uVar5) = *(undefined1 *)((int)&local_3c + uVar5);
              uVar5 = uVar5 + 1;
            } while (uVar5 < 4);
            if (uVar6 != 0) {
              local_3c = *(undefined4 *)
                          (DAT_0804d44c + (uint)DAT_0805462c * 0x1000 + (uint)local_40[0] * 0x8000 +
                          0xc0001c);
              uVar5 = 0;
              do {
                iVar9 = iVar3 + param_5 + uVar5;
                uVar6 = uVar6 - 1;
                puVar1 = (undefined1 *)((int)&local_3c + uVar5);
                uVar5 = uVar5 + 1;
                *(undefined1 *)(iVar9 + 4) = *puVar1;
                if (3 < uVar5) break;
              } while (uVar6 != 0);
            }
          }
LAB_0800dc6e:
          param_6 = param_6 - uVar7;
          *param_7 = *param_7 + uVar7;
        } while (param_6 != 0);
        iVar8 = 0;
      }
      else {
        iVar8 = 0x19;
      }
    }
  }
  else {
    iVar8 = 0x13;
  }
  return iVar8;
}




/* 0x0800dc88 */
undefined4 FUN_0800dc88(param_1, param_2, param_3)
int param_1; int param_2; undefined1 * param_3;
{
  int iVar1;
  uint uVar2;
  
  uVar2 = (uint)(short)(&DAT_08054634)[param_2];
  while( true ) {
    if (uVar2 == 0xffff8000) {
      return 0x19;
    }
    iVar1 = uVar2 * 5;
    if ((char)(&DAT_08054834)[iVar1] == param_1) break;
    uVar2 = (uint)(byte)(&DAT_08054837)[iVar1] |
            (int)((uint)(byte)(&DAT_08054838)[iVar1] << 0x18) >> 0x10;
  }
  *param_3 = (char)uVar2;
  return 0;
}




/* 0x0800dcf0 */
undefined4 FUN_0800dcf0()
{
  return 0x80;
}




/* 0x0800dcf4 */
undefined1 FUN_0800dcf4()
{
  return DAT_0805462d;
}




/* 0x0800dd00 */
int FUN_0800dd00(param_1)
undefined4 param_1;
{
  int iVar1;
  
  DAT_08054630 = param_1;
  iVar1 = FUN_0800e64c();
  if ((iVar1 == 0) && (iVar1 = FUN_0800ea40(&DAT_0805462c), iVar1 == 0)) {
    iVar1 = FUN_0800eb5e(&LAB_0802eeb4,0);
    DAT_0805462d = iVar1 == 0;
    FUN_0800dd84();
    iVar1 = 0;
  }
  return iVar1;
}




/* 0x0800dd3c */
undefined4 FUN_0800dd3c()
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  do {
    uVar2 = uVar3 + 1;
    (&DAT_08054634)[uVar3] = 0x8000;
    uVar3 = uVar2;
  } while (uVar2 < 0x100);
  uVar3 = 0;
  do {
    iVar1 = uVar3 * 5;
    uVar3 = uVar3 + 1;
    (&DAT_08054834)[iVar1] = 0xff;
    (&DAT_08054837)[iVar1] = 0;
    (&DAT_08054838)[iVar1] = 0x80;
    (&DAT_08054835)[iVar1] = 0;
    (&DAT_08054836)[iVar1] = 0x80;
  } while (uVar3 < 0x80);
  return 0;
}




/* 0x0800dd84 */
undefined4 FUN_0800dd84()
{
  int iVar1;
  uint uVar2;
  
  FUN_0800dd3c();
  uVar2 = 0;
  do {
    iVar1 = *(int *)(DAT_0804d44c + uVar2 * 4 + 0xf800);
    FUN_0800d9d0(uVar2,(uint)(iVar1 << 0xc) >> 0x1c,(uint)(iVar1 << 0x10) >> 0x18);
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x80);
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800ddb8 */
undefined4 FUN_0800ddb8(param_1, param_2)
int param_1; uint param_2;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  int local_28;
  
  uVar4 = 0;
  if ((param_1 == 0) || (param_2 == 0)) {
    uVar4 = 3;
  }
  else {
    uVar3 = param_2;
    if ((param_2 & 3) != 0) {
      uVar3 = (4 - (param_2 & 3)) + param_2;
    }
    for (uVar2 = 0; uVar2 < uVar3 >> 2; uVar2 = uVar2 + 1) {
      do {
      } while ((_DAT_00022004 & 1) == 0);
      do {
        local_28 = _DAT_00022000;
      } while (_DAT_00022000 == 0);
      if (uVar2 < (uVar3 >> 2) - 1) {
        FUN_08006a30(param_1,&local_28,4);
        param_1 = param_1 + 4;
      }
      else {
        if ((param_2 & 3) == 0) {
          uVar1 = 4;
        }
        else {
          uVar1 = param_2 & 3;
        }
        FUN_08006a30(param_1,&local_28,uVar1);
      }
    }
  }
  return uVar4;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0800de34 */
undefined4 FUN_0800de34()
{
  FUN_0800de50();
  _DAT_00022104 = 2;
  _DAT_00022100 = 0xdddd;
  return 0;
}




/* 0x0800de50 */
undefined4 FUN_0800de50()
{
  return 0;
}




/* 0x0800de54 */
int FUN_0800de54(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  
  if ((param_1 == 0) || (param_2 == 0)) {
    iVar1 = 3;
  }
  else {
    iVar1 = FUN_0800de34();
    if (iVar1 == 0) {
      FUN_0800ddb8(param_1,param_2);
      return 0;
    }
  }
  return iVar1;
}




/* 0x0800de54 */
int thunk_FUN_0800de54(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  
  if ((param_1 == 0) || (param_2 == 0)) {
    iVar1 = 3;
  }
  else {
    iVar1 = FUN_0800de34();
    if (iVar1 == 0) {
      FUN_0800ddb8(param_1,param_2);
      return 0;
    }
  }
  return iVar1;
}




/* 0x0800de7c */
void FUN_0800de7c(param_1)
int param_1;
{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0xd0);
  uVar2 = *(uint *)(param_1 + 0x298);
  if (*(int *)(iVar3 + 4) << 0x17 < 0) {
    do {
      thunk_FUN_080199b4(5);
      if (uVar2 < 6) {
        uVar2 = 0;
      }
      else {
        uVar2 = uVar2 - 5;
      }
      iVar1 = *(int *)(iVar3 + 4) << 0x17;
    } while ((uVar2 != 0) && (iVar1 < 0));
    if ((iVar1 < 0) && (*(int *)(param_1 + 0xc0) == 0)) {
      *(undefined4 *)(param_1 + 0xc0) = 0x30000107;
    }
  }
  if (((*(uint *)(param_1 + 0x268) & 0x30000000) == 0) && (-1 < *(int *)(param_1 + 0xc0) << 3)) {
    FUN_0800e0c8(param_1,param_1 + 0x278);
  }
  FUN_0800c77e(param_1);
  iVar3 = FUN_0800cbd0(param_1,0);
  if ((iVar3 != 0) && (FUN_0800cade(param_1), *(int *)(param_1 + 0xc0) == 0)) {
    *(int *)(param_1 + 0xc0) = iVar3;
  }
  return;
}




/* 0x0800df14 */
uint FUN_0800df14(param_1)
char * param_1;
{
  char cVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint local_28;
  
  uVar7 = 0;
  uVar6 = 0;
  do {
    if (*param_1 == '\x03') {
      return uVar7;
    }
    if (false) {
LAB_0800e0c0:
      return 0;
    }
    switch(*(undefined4 *)(param_1 + 0x24)) {
    case 4:
      if ((*(char *)(*(int *)(param_1 + 4) + 0xc) == '\x01') &&
         (*(int *)(*(int *)(param_1 + 4) + 4) == 0)) {
        bVar2 = 0x8a;
      }
      else {
        bVar2 = 0x81;
      }
      local_28 = (uint)bVar2;
      param_1[0x24] = '\x05';
      param_1[0x25] = '\0';
      param_1[0x26] = '\0';
      param_1[0x27] = '\0';
      *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
      break;
    case 5:
      iVar3 = *(int *)(param_1 + 4);
      local_28 = (uint)(*(int *)(iVar3 + 8) << 0x19) >> 0x18;
      if (*(char *)(iVar3 + 0xc) == '\0') {
        local_28 = local_28 | 1;
LAB_0800e036:
        param_1[0x24] = '\x06';
        param_1[0x25] = '\0';
        param_1[0x26] = '\0';
        param_1[0x27] = '\0';
      }
      else {
        if (*(int *)(iVar3 + 4) == 0) goto LAB_0800e02e;
        param_1[0x24] = '\a';
        param_1[0x25] = '\0';
        param_1[0x26] = '\0';
        param_1[0x27] = '\0';
      }
      goto LAB_0800df76;
    case 6:
      iVar3 = *(int *)(param_1 + 0x2c);
      iVar5 = *(int *)(*(int *)(param_1 + 4) + 4);
      if ((uint)(iVar5 - iVar3) < 0x100) {
        *(int *)(param_1 + 0x2c) = iVar5;
        bVar2 = 0x87;
      }
      else {
        *(int *)(param_1 + 0x2c) = iVar3 + 0xff;
        bVar2 = 0x85;
        if (*(int *)(*(int *)(param_1 + 4) + 4) - (iVar3 + 0xff) == 2) {
          *(int *)(param_1 + 0x2c) = iVar3 + 0xfe;
        }
      }
      param_1[0x24] = '\b';
      param_1[0x25] = '\0';
      param_1[0x26] = '\0';
      param_1[0x27] = '\0';
      *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
      local_28 = (uint)bVar2;
      break;
    case 7:
      iVar3 = *(int *)(*(int *)(param_1 + 4) + 4);
      if ((uint)(iVar3 - *(int *)(param_1 + 0x2c)) < 0x100) {
        *(int *)(param_1 + 0x2c) = iVar3;
        cVar1 = *(char *)(*(int *)(param_1 + 4) + 0xd);
        if ((cVar1 == '\x01') || (cVar1 == '\x02')) goto LAB_0800dff0;
        bVar2 = 0x83;
      }
      else {
        *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x2c) + 0xff;
LAB_0800dff0:
        bVar2 = 0x82;
      }
      param_1[0x24] = '\b';
      param_1[0x25] = '\0';
      param_1[0x26] = '\0';
      param_1[0x27] = '\0';
      *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
      local_28 = (uint)bVar2;
      break;
    case 8:
      local_28 = *(int *)(param_1 + 0x2c) - *(int *)(param_1 + 0x28) & 0xff;
      if (local_28 == 0) {
LAB_0800e02e:
        FUN_0800e164(param_1);
      }
      else {
        if (*(char *)(*(int *)(param_1 + 4) + 0xc) == '\0') {
          iVar3 = *(int *)(param_1 + 0x28) + local_28;
          *(int *)(param_1 + 0x28) = iVar3;
          if (iVar3 != *(int *)(*(int *)(param_1 + 4) + 4)) goto LAB_0800e036;
          if ((*(char *)(*(int *)(param_1 + 0x38) + 0x88) == '\0') ||
             (*(int *)(*(int *)(param_1 + 0x38) + 100) != *(int *)(param_1 + 0x18)))
          goto LAB_0800e02e;
          uVar4 = 9;
        }
        else {
          uVar4 = 10;
        }
        *(undefined4 *)(param_1 + 0x24) = uVar4;
      }
LAB_0800df76:
      *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
      break;
    default:
      goto LAB_0800e0c0;
    case 10:
      if (*(int *)(param_1 + 0x34) == *(int *)(*(int *)(param_1 + 0x30) + 4)) {
        *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + 8;
        param_1[0x34] = '\0';
        param_1[0x35] = '\0';
        param_1[0x36] = '\0';
        param_1[0x37] = '\0';
      }
      iVar5 = **(int **)(param_1 + 0x30);
      iVar3 = *(int *)(param_1 + 0x34);
      *(int *)(param_1 + 0x34) = iVar3 + 1;
      bVar2 = *(byte *)(iVar5 + iVar3);
      *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
      *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
      local_28 = (uint)bVar2;
      if (*(int *)(param_1 + 0x28) == *(int *)(*(int *)(param_1 + 4) + 4)) {
        FUN_0800e164();
      }
      else if (*(int *)(param_1 + 0x28) == *(int *)(param_1 + 0x2c)) {
        param_1[0x24] = '\a';
        param_1[0x25] = '\0';
        param_1[0x26] = '\0';
        param_1[0x27] = '\0';
      }
      break;
    case 0xb:
      iVar3 = *(int *)(param_1 + 0xc);
      *(uint *)(param_1 + 0xc) = iVar3 + 1U;
      local_28 = 0x96;
      if ((*(char *)(*(int *)(param_1 + 0x38) + 0x88) == '\0') || ((~(iVar3 + 1U) & 3) != 0)) {
        *param_1 = '\x03';
      }
    }
    uVar7 = uVar7 | local_28 << ((uVar6 & 0x1f) << 3);
    uVar6 = uVar6 + 1;
    if (3 < uVar6) {
      return uVar7;
    }
  } while( true );
}




/* 0x0800e0c8 */
void FUN_0800e0c8(param_1, param_2, param_3)
int param_1; int * param_2; int * param_3;
{
  int iVar1;
  int iVar2;
  ushort uVar3;
  
  iVar2 = *(int *)(param_1 + 0xcc);
  if (*(int *)(param_1 + 0x284) == 0) {
    iVar1 = *(int *)(param_1 + 0x48);
    uVar3 = (ushort)*(undefined4 *)(iVar2 + 0x154);
  }
  else {
    if (*(int *)(param_1 + 0x284) != 1) goto LAB_0800e100;
    iVar1 = *(int *)(param_1 + 0x48);
    uVar3 = (ushort)*(undefined4 *)(iVar2 + 0x104);
  }
  *param_2 = iVar1 - (uint)uVar3;
LAB_0800e100:
  if (*(int *)(param_1 + 0x288) == 0) {
    iVar1 = *(int *)(param_1 + 0x84);
    uVar3 = (ushort)*(undefined4 *)(iVar2 + 0x20c);
  }
  else {
    if (*(int *)(param_1 + 0x288) != 1) {
      return;
    }
    iVar1 = *(int *)(param_1 + 0x84);
    uVar3 = (ushort)*(undefined4 *)(iVar2 + 0x204);
  }
  *param_3 = iVar1 - (uint)uVar3;
  return;
}




/* 0x0800e124 */
void FUN_0800e124(param_1)
int param_1;
{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x14) + -1;
  *(int *)(param_1 + 0x14) = iVar1;
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 0x24) = 0xd;
    return;
  }
  do {
    iVar1 = *(int *)(param_1 + 0x18) + 1;
    *(int *)(param_1 + 0x18) = iVar1;
    iVar2 = **(int **)(param_1 + 0x3c) + iVar1 * 0x10;
    *(int *)(param_1 + 4) = iVar2;
    if (*(char *)(iVar2 + 0xc) == '\0') break;
  } while (iVar1 != *(int *)(param_1 + 0x1c));
  FUN_0800e150();
  return;
}




/* 0x0800e150 */
void FUN_0800e150(param_1)
int param_1;
{
  *(undefined4 *)(param_1 + 0x24) = 6;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = **(undefined4 **)(param_1 + 4);
  *(undefined4 *)(param_1 + 0x38) = 0;
  return;
}




/* 0x0800e164 */
void FUN_0800e164(param_1)
undefined1 * param_1;
{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x18);
  *(int *)(param_1 + 0x18) = iVar1 + 1;
  if (iVar1 + 1 != *(int *)(*(int *)(param_1 + 0x38) + 4)) {
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 0x10;
    *(undefined4 *)(param_1 + 0x2c) = 0;
    *(undefined4 *)(param_1 + 0x24) = 4;
    *(undefined4 *)(param_1 + 0x28) = 0;
    if (*(char *)(*(undefined4 **)(param_1 + 4) + 3) == '\x01') {
      *(undefined4 *)(param_1 + 0x30) = **(undefined4 **)(param_1 + 4);
      *(undefined4 *)(param_1 + 0x34) = 0;
    }
    return;
  }
  if (*(char *)(*(int *)(param_1 + 0x38) + 0x88) != '\0') {
    *(undefined4 *)(param_1 + 0x24) = 0xb;
    return;
  }
  *param_1 = 3;
  return;
}




/* 0x0800e18e */
void FUN_0800e18e(param_1)
int param_1;
{
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x24) = 4;
  *(undefined4 *)(param_1 + 0x28) = 0;
  if (*(char *)(*(undefined4 **)(param_1 + 4) + 3) == '\x01') {
    *(undefined4 *)(param_1 + 0x30) = **(undefined4 **)(param_1 + 4);
    *(undefined4 *)(param_1 + 0x34) = 0;
  }
  return;
}




/* 0x0800e1a8 */
undefined4 FUN_0800e1a8(param_1)
int param_1;
{
  undefined4 uVar1;
  undefined4 unaff_r4 = 0;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  undefined4 unaff_lr = 0;
  
  pcVar2 = (char *)(param_1 + 0x7c);
  pcVar4 = (char *)(param_1 + 0x40);
  FUN_0800d2c0(*(undefined4 *)(param_1 + 0x2a4));
  do {
    FUN_0800cb02(param_1);
    if (*(char *)(param_1 + 0xbd) != '\x01') break;
    if ((*(uint *)(param_1 + 0x268) & 0xbc) != 0) {
      *(uint *)(param_1 + 0xc0) = *(uint *)(param_1 + 0x268) & 0xbc | 0x30000000;
      FUN_0800cade(param_1);
      goto LAB_0800e2b4;
    }
    if (*pcVar2 == '\x03') {
      iVar3 = *(int *)(param_1 + 0xcc);
      while ((*pcVar2 == '\x03' && (*(uint *)(param_1 + 0x270) < *(uint *)(param_1 + 0x260)))) {
        FUN_0800e2dc(pcVar2,*(undefined4 *)(iVar3 + 0x218));
        *(int *)(param_1 + 0x270) = *(int *)(param_1 + 0x270) + 1;
      }
    }
    if ((*(uint *)(param_1 + 0x280) & 0x38000fc) != 0) {
      *(undefined4 *)(param_1 + 0xc0) = 0x10000000;
      *(uint *)(param_1 + 0xc0) = *(uint *)(param_1 + 0x280) & 0xffffffc | 0x10000000;
      goto LAB_0800e2b4;
    }
    if (*pcVar4 == '\x02') {
      iVar3 = *(int *)(param_1 + 0xcc);
      while ((*pcVar4 == '\x02' && (*(uint *)(param_1 + 0x274) < *(uint *)(param_1 + 0x264)))) {
        uVar1 = FUN_0800df14(pcVar4);
        *(undefined4 *)(iVar3 + 0x110) = uVar1;
        *(int *)(param_1 + 0x274) = *(int *)(param_1 + 0x274) + 1;
      }
    }
    if (((*pcVar4 == '\x04') && (*(int *)(param_1 + 0x84) == 0)) ||
       ((*pcVar2 == '\a' && (*pcVar4 == '\x04')))) goto LAB_0800e2b4;
  } while (false);
  if (false) {
LAB_0800e2b4:
    *(undefined1 *)(param_1 + 0xbd) = 2;
    FUN_0800de7c(param_1);
    FUN_0800d320(*(undefined4 *)(param_1 + 0x28c));
  }
  FUN_0800b64a(*(undefined4 *)(*(int *)(param_1 + 0x2a4) + 4),0,0,pcVar2,unaff_r4,unaff_lr);
  return 0;
}




/* 0x0800e2dc */
void FUN_0800e2dc(param_1, param_2)
undefined1 * param_1; uint param_2;
{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  
  uVar5 = 0;
  do {
    iVar2 = *(int *)(param_1 + 0x24);
    if (iVar2 == 0xd) break;
    uVar1 = uVar5 & 0x1f;
    uVar5 = uVar5 + 1;
    if (iVar2 == 6) {
      iVar2 = *(int *)(param_1 + 0x2c);
      iVar4 = *(int *)(*(int *)(param_1 + 4) + 4);
      if ((uint)(iVar4 - iVar2) < 0x100) {
        *(int *)(param_1 + 0x2c) = iVar4;
      }
      else {
        *(int *)(param_1 + 0x2c) = iVar2 + 0xff;
        if (*(int *)(*(int *)(param_1 + 4) + 4) - (iVar2 + 0xff) == 2) {
          *(int *)(param_1 + 0x2c) = iVar2 + 0xfe;
        }
      }
      *(undefined4 *)(param_1 + 0x24) = 8;
    }
    else if (iVar2 == 8) {
      if ((*(int *)(param_1 + 0x2c) - *(int *)(param_1 + 0x28) & 0xffU) == 0) goto LAB_0800e330;
      uVar3 = 10;
LAB_0800e378:
      *(undefined4 *)(param_1 + 0x24) = uVar3;
    }
    else {
      if (iVar2 != 10) {
        return;
      }
      if (*(int *)(param_1 + 0x38) == *(int *)(*(int *)(param_1 + 0x30) + 4)) {
        *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + 8;
        *(undefined4 *)(param_1 + 0x38) = 0;
      }
      iVar4 = **(int **)(param_1 + 0x30);
      iVar2 = *(int *)(param_1 + 0x38);
      *(int *)(param_1 + 0x38) = iVar2 + 1;
      *(char *)(iVar4 + iVar2) = (char)(param_2 >> (uVar1 << 3));
      iVar2 = *(int *)(param_1 + 0x28) + 1;
      *(int *)(param_1 + 0x28) = iVar2;
      if (iVar2 == *(int *)(*(int *)(param_1 + 4) + 4)) {
LAB_0800e330:
        FUN_0800e124();
      }
      else if (iVar2 == *(int *)(param_1 + 0x2c)) {
        uVar3 = 6;
        goto LAB_0800e378;
      }
    }
  } while (uVar5 < 4);
  if ((*(int *)(param_1 + 0x20) == *(int *)(param_1 + 8)) || (*(int *)(param_1 + 0x14) == 0)) {
    *param_1 = 7;
  }
  return;
}




/* 0x0800e39c */
void FUN_0800e39c(param_1)
int param_1;
{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  
  iVar7 = *(int *)(param_1 + 0xd0);
  iVar4 = *(int *)(param_1 + 0xcc);
  puVar1 = *(undefined4 **)(param_1 + 600);
  uVar2 = *(uint *)(iVar4 + 0x18);
  uVar3 = *(uint *)(iVar4 + 0x1c) & 0xbc;
  uVar8 = *(uint *)(iVar7 + 4);
  uVar5 = uVar2 & 0x300;
  uVar6 = uVar8 & 0x38000fc;
  if ((uVar3 != 0 || uVar6 != 0) || uVar5 != 0) {
    *(int *)(param_1 + 0xd4) = *(int *)(param_1 + 0xd4) + 1;
    *puVar1 = *(undefined4 *)(param_1 + 0xd4);
    puVar1[1] = uVar3;
    puVar1[2] = uVar2;
    puVar1[5] = uVar8;
    FUN_0800e0c8(param_1,puVar1 + 3,puVar1 + 4);
    if (uVar3 != 0) {
      *(uint *)(iVar4 + 0x1c) = uVar3;
    }
    if (uVar6 != 0) {
      *(uint *)(iVar7 + 4) = uVar6;
    }
    if (uVar5 != 0) {
      *(uint *)(iVar4 + 0x18) = uVar5;
    }
    iVar4 = *(int *)(param_1 + 600) + 0x18;
    if (iVar4 == param_1 + 600) {
      iVar4 = param_1 + 0xd8;
    }
    if (*(int *)(param_1 + 0x25c) != iVar4) {
      iVar4 = *(int *)(param_1 + 600) + 0x18;
      if (iVar4 == param_1 + 600) {
        iVar4 = param_1 + 0xd8;
      }
      *(int *)(param_1 + 600) = iVar4;
    }
  }
  return;
}




/* 0x0800e430 */
void FUN_0800e430(param_1)
int param_1;
{
  bool bVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  
  bVar1 = false;
  uVar4 = *(uint *)(param_1 + 0x3c);
  if (*(char *)(param_1 + 0xc) == '\0') {
    while( true ) {
      if ((*(int *)(param_1 + 0xc0) == 0) &&
         ((*(char *)(param_1 + 0x40) != '\x04' ||
          ((*(int *)(param_1 + 0x84) != 0 && (*(char *)(param_1 + 0x7c) != '\a')))))) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      if (bVar2 || bVar1) break;
      FUN_0800e39c(param_1);
      FUN_0800e1a8(param_1);
      if (*(int *)(param_1 + 0xc0) != 0) break;
      thunk_FUN_080199b4(5);
      if (uVar4 < 6) {
        bVar1 = true;
      }
      else {
        uVar4 = uVar4 - 5;
      }
    }
    if (!bVar1) {
      return;
    }
  }
  else {
    iVar3 = FUN_0800d328(*(undefined4 *)(param_1 + 0x28c),uVar4 / 1000);
    if (iVar3 != -0xfffffff) {
      if (iVar3 == 0) {
        return;
      }
      goto LAB_0800e460;
    }
  }
  FUN_0800cbd0(param_1,3);
  FUN_0800e0c8(param_1,param_1 + 0x278);
  FUN_0800c77e(param_1);
  FUN_0800cbd0(param_1,0);
  iVar3 = 0x20000000;
LAB_0800e460:
  *(int *)(param_1 + 0xc0) = iVar3;
  return;
}




/* 0x0800e4dc */
undefined4 FUN_0800e4dc()
{
  int iVar1;
  uint uVar2;
  
  if (DAT_08053fc4 != 0) {
    for (uVar2 = 0; uVar2 < DAT_08053fc0; uVar2 = uVar2 + 1) {
      iVar1 = *(int *)(DAT_08053fc4 + uVar2 * 4);
      while (iVar1 != 0) {
        iVar1 = *(int *)(iVar1 + 0x10);
        FUN_0800ea14();
      }
    }
    FUN_0800ea14();
    DAT_08053fc4 = 0;
  }
  DAT_08053fb8 = 0;
  return 0;
}




/* 0x0800e51c */
int FUN_0800e51c()
{
  int iVar1;
  int iVar2;
  
  if (DAT_08053fb8 != '\0') {
    iVar1 = FUN_0800dd84();
    return iVar1;
  }
  iVar1 = FUN_0800dd00(&LAB_080281b4);
  if (iVar1 == 0) {
    DAT_08053fc0 = FUN_0800dcf0();
    iVar2 = FUN_0800dcf4();
    if ((iVar2 == 0) || (iVar1 = FUN_0800eb5a(DAT_08053fc0 << 2,&DAT_08053fc4), iVar1 == 0)) {
      DAT_08053fb8 = '\x01';
    }
  }
  return iVar1;
}




/* 0x0800e564 */
undefined4 FUN_0800e564(param_1, param_2, param_3, param_4, param_5, param_6)
undefined1 param_1; undefined4 param_2; undefined2 param_3; undefined4 param_4; undefined4 param_5; undefined4 param_6;
{
  FUN_0801b5b0(1,param_2,param_1,param_3,param_4,param_5,param_6);
  return 0;
}




/* 0x0800e57a */
undefined4 FUN_0800e57a(param_1, param_2, param_3, param_4, param_5)
undefined1 param_1; undefined4 param_2; undefined2 param_3; undefined4 param_4; undefined4 param_5;
{
  FUN_0801b5b0(0,param_2,param_1,param_3,param_4,param_5,0);
  return 0;
}




/* 0x0800e594 */
int FUN_0800e594(param_1)
ushort * param_1;
{
  int iVar1;
  int iVar2;
  
  iVar2 = FUN_080138ec();
  iVar1 = DAT_0804d44c;
  if (iVar2 == 0) {
    *(uint *)(DAT_0804d44c + (uint)param_1[1] * 4 + 0xf800) =
         ((byte)*param_1 & 0xf) << 0x10 | (uint)*(byte *)((int)param_1 + 1) << 8;
    if (DAT_0804d165 == '\0') {
      *(uint *)(iVar1 + (uint)param_1[1] * 4 + 0xa700) =
           (byte)param_1[2] & 7 | ((*param_1 & 0xf) << 8 | (uint)(*param_1 >> 8)) << 0x10;
    }
    iVar2 = 0;
  }
  return iVar2;
}




/* 0x0800e5f4 */
undefined4 FUN_0800e5f4(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  FUN_08019ff0(param_1,param_2,0,0,0,1,1);
  return 0;
}




/* 0x0800e608 */
undefined1 FUN_0800e608()
{
  return DAT_0804d165;
}




/* 0x0800e614 */
int FUN_0800e614(param_1)
int param_1;
{
  int iVar1;
  
  if (DAT_0804d164 == '\0') {
    iVar1 = FUN_0800e64c();
    if (iVar1 != 0) {
      return iVar1;
    }
    DAT_0804d164 = '\x01';
  }
  if ((param_1 == 0) ||
     ((iVar1 = FUN_0800e660(0,1), iVar1 == 0 && (iVar1 = FUN_0800dae4(1), iVar1 == 0)))) {
    iVar1 = 0;
  }
  return iVar1;
}




/* 0x0800e64c */
int FUN_0800e64c(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; int param_4;
{
  int iVar1;
  undefined4 *local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  int local_c;
  
  if (DAT_0804d44c != 0) {
    return 0;
  }
  local_18 = &DAT_0804d44c;
  uStack_14 = param_2;
  uStack_10 = param_3;
  local_c = param_4;
  iVar1 = FUN_0800b7ea(0,0x2000070,0x10000,&local_18);
  if ((iVar1 == 0) && (local_18 != (undefined4 *)0x0)) {
    iVar1 = (**(code **)(*(int *)(((uint)local_18 & 0xfffffffe) + 4) + 0x10))
                      ((uint)local_18 & 0xfffffffe,1);
    if (((iVar1 == 0) &&
        (iVar1 = (**(code **)(local_18[1] + 0x24))(local_18,"PMIC_ARB",&DAT_0804d44c), iVar1 == 0))
       && (iVar1 = (**(code **)(*(int *)(((uint)local_18 & 0xfffffffe) + 4) + 0x14))(), iVar1 == 0))
    {
      iVar1 = 0;
    }
    else {
      iVar1 = 0xd;
    }
  }
  else {
    iVar1 = spmi_init("pmic_arb_base_addr",&uStack_14);
    if (iVar1 == 0) {
      DAT_0804d44c = local_c;
    }
  }
  return iVar1;
}




/* 0x0800e660 */
int FUN_0800e660(param_1, param_2)
uint param_1; int param_2;
{
  int iVar1;
  int iVar2;
  
  if (3 < param_1) {
    return 0x12;
  }
  FUN_08019cd8();
  if (param_2 != 1) {
    if (param_2 != 2) {
      snprintf_buf(&DAT_08054ab4,0x80,"SPMI Fatal: Invalid config type for SPMI Master: %d",param_2)
      ;
      boot_log_message(&DAT_08054ab4);
      return 0xd;
    }
    iVar1 = FUN_0802754c(param_1);
    return iVar1;
  }
  if ((*(uint *)(DAT_0804d44c + 0xa02c) & 1) == 0) {
    iVar2 = FUN_0802754c(param_1);
    iVar1 = DAT_0804d44c;
    if (iVar2 == 0) {
      *(uint *)(DAT_0804d44c + 0xaf04) = *(uint *)(DAT_0804d44c + 0xaf04) | 0x100;
      *(uint *)(iVar1 + 0xa048) = *(uint *)(iVar1 + 0xa048) & 0xfffffffe;
      *(uint *)(iVar1 + 0xa018) = *(uint *)(iVar1 + 0xa018) & 0xfffffdff;
      *(uint *)(iVar1 + 0xa018) = *(uint *)(iVar1 + 0xa018) | 0x17f;
      return 0;
    }
  }
  else {
    iVar2 = 1;
  }
  return iVar2;
}




/* 0x0800e6dc */
uint FUN_0800e6dc(param_1, param_2, param_3, param_4, param_5)
int param_1; uint param_2; int param_3; uint param_4; undefined4 param_5;
{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar2 = 0;
  uVar4 = param_4 - 1 & 0xff;
  while ((uVar2 < param_2 &&
         (uVar1 = *(ushort *)(param_1 + uVar2 * 6),
         (((uVar1 & 0xff) << 8 | (uint)(uVar1 >> 8)) & 1 << (param_4 & 0xff) & 0xffffU) != 0))) {
    uVar2 = uVar2 + 1 & 0xff;
  }
  if ((uVar2 == param_2) || (uVar2 == 0)) {
    uVar3 = FUN_0800e6dc(param_1,param_2,param_3,uVar4,param_5,param_4);
  }
  else {
    if (uVar2 == 1) {
      FUN_0800e944(param_3,param_4,1,1,(char)*(undefined2 *)(param_1 + 2),param_5);
      uVar3 = param_3 + 1U & 0xff;
    }
    else {
      uVar3 = param_3 + 1U & 0xff;
      FUN_0800e944(param_3,param_4,1,0,uVar3,param_5);
      uVar3 = FUN_0800e6dc(param_1,uVar2,uVar3,uVar4,param_5);
    }
    if (uVar2 == param_2 - 1) {
      FUN_0800e944(param_3,param_4,0,1,(char)*(undefined2 *)(param_1 + param_2 * 6 + -4),param_5);
    }
    else {
      FUN_0800e944(param_3,param_4,0,0,uVar3,param_5);
      uVar3 = FUN_0800e6dc(param_1 + uVar2 * 6,param_2 - uVar2,uVar3,uVar4,param_5);
    }
  }
  return uVar3;
}




/* 0x0800e7c2 */
uint FUN_0800e7c2(param_1, param_2, param_3, param_4, param_5)
uint param_1; uint param_2; byte param_3; uint param_4; uint param_5;
{
  return (param_1 & 0xf) << 0x12 | (param_2 & 1) << 0x11 | (uint)param_3 << 9 | (param_4 & 1) << 8 |
         param_5 & 0xff;
}




/* 0x0800e7f0 */
void FUN_0800e7f0()
{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_0804d44c;
  *(undefined4 *)(DAT_0804d44c + 0xa100) = 0x202187f;
  *(undefined4 *)(iVar1 + 0xa104) = 0x27f7b;
  *(undefined4 *)(iVar1 + 0xa108) = 0x76bf;
  *(undefined4 *)(iVar1 + 0xa10c) = 0x7f8fe;
  *(undefined4 *)(iVar1 + 0xa110) = 0xffefe;
  *(undefined4 *)(iVar1 + 0xa114) = 0x208802ab;
  *(undefined4 *)(iVar1 + 0xa118) = 0x5512;
  *(undefined4 *)(iVar1 + 0xa11c) = 0x3880001;
  *(undefined4 *)(iVar1 + 0xa120) = 0x21f;
  *(undefined4 *)(iVar1 + 0xa124) = 0x7f8fe;
  *(undefined4 *)(iVar1 + 0xa128) = 0xffefe;
  *(undefined4 *)(iVar1 + 0xa12c) = 0x41000;
  uVar2 = 0;
  *(undefined4 *)(iVar1 + 0xa130) = 0;
  *(undefined4 *)(iVar1 + 0xa134) = 0;
  *(undefined4 *)(iVar1 + 0xa138) = 0;
  *(undefined4 *)(iVar1 + 0xa13c) = 0x2dc896;
  *(undefined4 *)(iVar1 + 0xa140) = 9;
  *(undefined4 *)(iVar1 + 0xa144) = 0x1fc3fd;
  *(undefined4 *)(iVar1 + 0xa148) = 0x80102;
  *(undefined4 *)(iVar1 + 0xa14c) = 0x100000;
  *(undefined4 *)(iVar1 + 0xa150) = 8;
  *(undefined4 *)(iVar1 + 0xa154) = 0x208800;
  *(undefined4 *)(iVar1 + 0xa158) = 0x68b800;
  *(undefined4 *)(iVar1 + 0xa15c) = 0x800;
  *(undefined4 *)(iVar1 + 0xa160) = 0x483000;
  *(undefined4 *)(iVar1 + 0xa164) = 0x555555;
  *(undefined4 *)(iVar1 + 0xa168) = 0x397a41;
  *(undefined4 *)(iVar1 + 0xa16c) = 0;
  *(undefined4 *)(iVar1 + 0xa170) = 0;
  *(undefined4 *)(iVar1 + 0xa174) = 0;
  *(undefined4 *)(iVar1 + 0xa178) = 0;
  do {
    *(undefined4 *)(iVar1 + uVar2 * 4 + 0xa200) = (&DAT_0803b5b8)[uVar2];
    uVar2 = uVar2 + 1;
    if (100 < uVar2) {
      return;
    }
  } while (uVar2 < 0x100);
  return;
}




/* 0x0800e8d8 */
void FUN_0800e8d8(param_1, param_2)
int param_1; uint param_2;
{
  int iVar1;
  uint uVar2;
  undefined4 local_410 [256];
  
  FUN_08006d14(local_410,0x3fc);
  if (param_2 == 1) {
    FUN_0800e944(0,0,*(byte *)(param_1 + 1) & 1,1,(char)*(undefined2 *)(param_1 + 2),local_410);
  }
  else if (1 < param_2) {
    FUN_0800e6dc(param_1,param_2,0,0xb,local_410);
  }
  iVar1 = DAT_0804d44c;
  uVar2 = 0;
  do {
    *(undefined4 *)(iVar1 + uVar2 * 4 + 0xab00) = local_410[uVar2];
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0xff);
  return;
}




/* 0x0800e944 */
void FUN_0800e944(param_1, param_2, param_3, param_4, param_5, param_6)
int param_1; undefined4 param_2; int param_3; int param_4; uint param_5; int param_6;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar1 = (uint)(param_4 != 1);
  uVar4 = *(uint *)(param_6 + param_1 * 4);
  if (param_3 == 1) {
    uVar3 = 0;
    uVar2 = uVar3;
  }
  else {
    uVar3 = uVar1;
    uVar2 = param_5;
    uVar1 = 0;
    param_5 = 0;
  }
  uVar1 = FUN_0800e7c2(param_2,uVar3,uVar2,uVar1,param_5);
  *(uint *)(param_6 + param_1 * 4) = uVar1 | uVar4;
  return;
}




/* 0x0800e980 */
undefined4 spmi_init(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  int iVar1;
  
  if (DAT_0804e220 == '\0') {
    iVar1 = dal_device_attach("DALDEVICEID_SPMI_DEVICE",&DAT_0804e224);
    if (iVar1 != 0) {
      snprintf_buf(&DAT_08054ab4,0x80,"SPMI Error: Unable to get SPMI property handle");
      boot_log_message(&DAT_08054ab4);
      return 0xd;
    }
    DAT_0804e220 = '\x01';
  }
  iVar1 = thunk_FUN_080106aa(&DAT_0804e224,param_1,0,param_2);
  if (iVar1 == 0) {
    return 0;
  }
  return 0xb;
}




/* 0x0800ea14 */
undefined4 FUN_0800ea14()
{
  return 0xb;
}




/* 0x0800ea18 */
bool FUN_0800ea18()
{
  int iVar1;
  
  if (DAT_0804d43c == '\0') {
    FUN_08027208();
  }
  if (DAT_0804d440 != 0) {
    iVar1 = FUN_0800bae2(DAT_0804d440,DAT_0804d444);
    return iVar1 != 0;
  }
  return (bool)2;
}




/* 0x0800ea40 */
undefined4 FUN_0800ea40(param_1, param_2, param_3, param_4)
undefined1 * param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 local_10;
  
  uStack_18 = param_2;
  uStack_14 = param_3;
  local_10 = param_4;
  iVar1 = spmi_init("owner",&uStack_18);
  if (iVar1 == 0) {
    *param_1 = (char)local_10;
  }
  return 0;
}




/* 0x0800eae4 */
bool FUN_0800eae4()
{
  int iVar1;
  
  if (DAT_0804d43c == '\0') {
    FUN_08027208();
  }
  if (DAT_0804d440 != 0) {
    iVar1 = FUN_0800bae2(DAT_0804d440,DAT_0804d448);
    return iVar1 != 0;
  }
  return (bool)2;
}




/* 0x0800eb0c */
undefined4 FUN_0800eb0c()
{
  return 0;
}




/* 0x0800eb12 */
undefined4 FUN_0800eb12(param_1, param_2, param_3, param_4)
char * param_1; undefined4 param_2; undefined4 param_3; uint param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_20;
  uint uStack_1c;
  
  uVar2 = 0;
  local_20 = param_3;
  uStack_1c = param_4;
  iVar1 = FUN_0800e608();
  if ((iVar1 != 0) && (*param_1 == '\x19')) {
    _GHIDRA_FIELD(local_20, 0, ushort) = CONCAT11((char)(param_4 >> 8),(char)param_3);
    iVar1 = FUN_0800e594(&local_20,1);
    if ((iVar1 == 0) && (iVar1 = FUN_0800d9d0(_GHIDRA_FIELD(local_20, 2, ushort),param_3,param_4 >> 8), iVar1 == 0)) {
      uVar2 = 1;
    }
    else {
      *param_1 = (char)iVar1;
    }
  }
  return uVar2;
}




/* 0x0800eb5a */
undefined4 FUN_0800eb5a()
{
  return 0xb;
}




/* 0x0800eb5e */
undefined4 FUN_0800eb5e()
{
  return 0xb;
}




/* 0x0800eb80 */
undefined4 FUN_0800eb80(param_1, param_2, param_3, param_4)
int param_1; int param_2; int param_3; uint param_4;
{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = 0xffffffff;
  FUN_0800b648(*(undefined4 *)(*(int *)(param_1 + 0xc) + 0x80));
  if (param_2 == 0) {
    for (uVar2 = 0; uVar2 < param_4; uVar2 = uVar2 + 1) {
      uVar3 = (uint)(*(int *)(param_3 + uVar2 * 4) << 0x12) >> 0x16;
      if ((uVar3 < DAT_0805143c) && (DAT_08051508 != 0)) {
        uVar1 = FUN_0800b786(uVar3,DAT_08051508 + uVar3 * 8 + 0x28);
        FUN_0800eee8(param_1,*(undefined4 *)(param_3 + uVar2 * 4),
                     *(undefined1 *)(DAT_08051508 + uVar3 * 8 + 0x2e));
        FUN_0800c198(uVar1);
        *(undefined1 *)(DAT_08051508 + uVar3 * 8 + 0x2c) = 0;
      }
    }
  }
  else {
    if (param_2 != 1) goto LAB_0800ebda;
    for (uVar2 = 0; uVar2 < param_4; uVar2 = uVar2 + 1) {
      uVar3 = (uint)(*(int *)(param_3 + uVar2 * 4) << 0x12) >> 0x16;
      if ((uVar3 < DAT_0805143c) && (FUN_0800c198(), DAT_08051508 != 0)) {
        *(undefined1 *)(DAT_08051508 + uVar3 * 8 + 0x2c) = 1;
      }
    }
  }
  uVar1 = 0;
LAB_0800ebda:
  FUN_0800b64a(*(undefined4 *)(*(int *)(param_1 + 0xc) + 0x80));
  return uVar1;
}




/* 0x0800ec50 */
int FUN_0800ec50(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 * param_3;
{
  int iVar1;
  
  *param_3 = 0;
  iVar1 = FUN_0800b1b6(0x2000020,&DAT_08050f98,&DAT_0805a3fc);
  if (iVar1 == 0) {
    DAT_0805a40c = 0xda1fda1f;
    DAT_0805a410 = &PTR_FUN_0800ec50_1_0803d4ac;
    DAT_0805a414 = &DAT_0805a3fc;
    FUN_0800b19a();
    *param_3 = &DAT_0805a40c;
  }
  return iVar1;
}




/* 0x0800ecc4 */
void FUN_0800ecc4(param_1)
int param_1;
{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 8) + 0xc);
  thunk_FUN_08010668(*(undefined4 *)(iVar1 + 4),iVar1 + 0x10);
  FUN_0800ed1c(*(undefined4 *)(param_1 + 8));
  return;
}




/* 0x0800ed04 */
undefined4 FUN_0800ed04(param_1)
int param_1;
{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0800b550(*(undefined4 *)(*(int *)(param_1 + 0xc) + 0x80));
  uVar2 = 0;
  if (iVar1 != 0) {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}




/* 0x0800ed1c */
undefined4 FUN_0800ed1c(param_1)
int param_1;
{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  int iVar6;
  undefined1 auStack_30 [8];
  uint local_28;
  uint local_24;
  uint local_20;
  
  iVar6 = 0;
  uVar1 = 0;
  local_24 = (uint)DAT_0805142c;
  if (local_24 == 0) {
    do {
      uVar2 = uVar1 + 1;
      (&DAT_0805a69c)[uVar1 * 5] = 0x16;
      uVar1 = uVar2;
    } while (uVar2 < 0x16);
    local_20 = local_24;
    iVar3 = FUN_0800b634(0x10,*(int *)(param_1 + 0xc) + 0x80,*(int *)(param_1 + 0xc) + 0x58);
    if (iVar3 == 0) {
      FUN_0800b648(*(undefined4 *)(*(int *)(param_1 + 0xc) + 0x80));
      iVar3 = thunk_FUN_08010668(*(undefined4 *)(*(int *)(param_1 + 0xc) + 4),
                                 *(int *)(param_1 + 0xc) + 0x10);
      if (iVar3 == 0) {
        iVar3 = FUN_0800ba6c();
        if (iVar3 == 0x31) {
          pcVar5 = "tlmm_total_gpio8926";
        }
        else {
          pcVar5 = "tlmm_total_gpio";
        }
        iVar3 = thunk_FUN_080106aa(*(int *)(param_1 + 0xc) + 0x10,pcVar5,0,auStack_30);
        if (iVar3 == 0) {
          DAT_0805143c = local_28;
          local_24 = local_28;
          iVar3 = thunk_FUN_080106aa(*(int *)(param_1 + 0xc) + 0x10,"tlmm_base",0,auStack_30);
          if (iVar3 == 0) {
            local_20 = local_28;
            iVar3 = thunk_FUN_080106aa(*(int *)(param_1 + 0xc) + 0x10,"tlmm_offset",0,auStack_30);
            if (iVar3 != 0) {
              FUN_0800b614(*(undefined4 *)(*(int *)(param_1 + 0xc) + 4),1,
                           "TLMM_DeviceInit: Failed to retrieve the register base offset.");
            }
            local_20 = local_20 + local_28;
            iVar3 = thunk_FUN_080106aa(*(int *)(param_1 + 0xc) + 0x10,"tlmm_ports",0,auStack_30);
            if (iVar3 == 0) {
              for (; iVar3 = *(int *)(local_28 + iVar6 * 4), iVar3 != -1; iVar6 = iVar6 + 5) {
                (&DAT_0805a69c)[iVar3 * 5] = iVar3;
                iVar3 = iVar3 * 0x14;
                *(undefined4 *)(&DAT_0805a6a0 + iVar3) = *(undefined4 *)(local_28 + (iVar6 + 1) * 4)
                ;
                *(undefined4 *)(&DAT_0805a6a4 + iVar3) = *(undefined4 *)(local_28 + (iVar6 + 2) * 4)
                ;
                *(undefined4 *)(&DAT_0805a6a8 + iVar3) = *(undefined4 *)(local_28 + (iVar6 + 3) * 4)
                ;
                *(undefined4 *)(&DAT_0805a6ac + iVar3) = *(undefined4 *)(local_28 + (iVar6 + 4) * 4)
                ;
                DAT_08051430 = DAT_08051430 + 1;
              }
            }
            FUN_0800c1f0(&local_24);
            DAT_0805142c = 1;
            FUN_0800b64a(*(undefined4 *)(*(int *)(param_1 + 0xc) + 0x80));
            goto LAB_0800ee4a;
          }
        }
      }
    }
    uVar4 = 0xffffffff;
  }
  else {
LAB_0800ee4a:
    uVar4 = 0;
  }
  return uVar4;
}




/* 0x0800eee8 */
undefined4 FUN_0800eee8(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined1 param_3;
{
  FUN_0800c238(param_2,param_3);
  return 0;
}




/* 0x0800ef00 */
undefined4 FUN_0800ef00(param_1)
undefined4 param_1;
{
  int iVar1;
  
  iVar1 = FUN_0800b424();
  if (((iVar1 == 0) &&
      (iVar1 = FUN_0800b388("DALTLMM",DAT_0805143c * 8 + 0x30,0x10000,&DAT_08051508), iVar1 == 0))
     && (DAT_08051508 != 0)) {
    if (*(int *)(DAT_08051508 + 0x20) == 0) {
      FUN_0800b64c(param_1);
    }
    *(undefined4 *)(DAT_08051508 + 0x24) = 1;
    return 0;
  }
  return 0xffffffff;
}




/* 0x0800ef58 */
undefined4 FUN_0800ef58(param_1, param_2, param_3)
undefined4 param_1; uint param_2; int param_3;
{
  if ((param_2 < DAT_0805143c) && (DAT_08051508 != 0)) {
    FUN_0800b76c(param_3,DAT_08051508 + param_2 * 8 + 0x28);
    *(byte *)(DAT_08051508 + param_2 * 8 + 0x2e) = (byte)((uint)(param_3 << 10) >> 0x1f);
    return 0;
  }
  return 0xffffffff;
}




/* 0x0800ef98 */
undefined4 FUN_0800ef98(param_1, param_2, param_3)
int param_1; uint param_2; int param_3;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar4 = 0xffffffff;
  if ((param_2 < 0x16) && ((&DAT_0805a69c)[param_2 * 5] != 0x16)) {
    FUN_0800b648(*(undefined4 *)(*(int *)(param_1 + 0xc) + 0x80));
    iVar1 = param_2 * 0x14;
    if (param_3 == 0) {
      uVar3 = *(undefined4 *)(&DAT_0805a6ac + iVar1);
      uVar4 = *(undefined4 *)(&DAT_0805a6a0 + iVar1);
      uVar2 = *(undefined4 *)(&DAT_0805a6a4 + iVar1);
    }
    else {
      uVar4 = *(undefined4 *)(&DAT_0805a6a0 + iVar1);
      uVar2 = *(undefined4 *)(&DAT_0805a6a4 + iVar1);
      uVar3 = *(undefined4 *)(&DAT_0805a6a8 + iVar1);
    }
    FUN_0800c204(uVar4,uVar2,uVar3);
    uVar4 = 0;
    FUN_0800b64a(*(undefined4 *)(*(int *)(param_1 + 0xc) + 0x80));
  }
  return uVar4;
}




/* 0x0800eff4 */
undefined4 FUN_0800eff4(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  undefined4 uVar4;
  uint uVar5;
  
  uVar4 = 0xffffffff;
  if ((param_2 != 0) && ((DAT_0805142d != '\0' || (iVar1 = FUN_0800f0ac(), iVar1 != 0)))) {
    if (param_1 == 0) {
      if (DAT_08051434 == 0) {
        iVar1 = FUN_0800ba6c();
        if (iVar1 == 0x31) {
          pcVar3 = "tlmm_sleep8926";
        }
        else {
          pcVar3 = "tlmm_sleep";
        }
        iVar1 = thunk_FUN_080106aa(&DAT_08051440,pcVar3,0,&DAT_0805a690);
        if (iVar1 == -1) {
          return 0xffffffff;
        }
        DAT_08051434 = DAT_0805a698;
      }
      for (uVar5 = 0; uVar5 < param_3; uVar5 = uVar5 + 1) {
        uVar2 = (uint)(*(int *)(param_2 + uVar5 * 4) << 0x12) >> 0x16;
        FUN_0800c198(*(uint *)(DAT_08051434 + uVar2 * 4) | uVar2 << 4);
      }
    }
    else {
      if (param_1 != 1) {
        return 0xffffffff;
      }
      for (uVar5 = 0; uVar5 < param_3; uVar5 = uVar5 + 1) {
        FUN_0800c198(*(undefined4 *)(param_2 + uVar5 * 4));
      }
    }
    uVar4 = 0;
  }
  return uVar4;
}




/* 0x0800f0ac */
undefined4 FUN_0800f0ac()
{
  int iVar1;
  undefined1 auStack_18 [8];
  int local_10;
  undefined4 local_c;
  int local_8;
  
  local_c = 200;
  thunk_FUN_08010668(0x2000020,&DAT_08051440);
  iVar1 = thunk_FUN_080106aa(&DAT_08051440,"tlmm_base",0,auStack_18);
  if (iVar1 == 0) {
    local_8 = local_10;
    iVar1 = thunk_FUN_080106aa(&DAT_08051440,"tlmm_offset",0,auStack_18);
    if (iVar1 == 0) {
      local_8 = local_8 + local_10;
      FUN_0800c1f0(&local_c);
      thunk_FUN_080106aa(&DAT_08051440,"tlmm_sleep",0,auStack_18);
      DAT_0805142d = 1;
      return 1;
    }
  }
  return 0;
}




/* 0x0800f134 */
undefined8 FUN_0800f134(param_1, param_2, param_3, param_4)
uint param_1; undefined4 * param_2; undefined4 * param_3; undefined4 * param_4;
{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 *local_28;
  undefined4 *local_24;
  undefined4 *local_20;
  
  local_28 = param_2;
  if (param_2 != (undefined4 *)0x0) {
    if (DAT_0804d19c != '\x01') {
      iVar1 = 3;
      goto LAB_0800f14c;
    }
    uVar2 = *(uint *)(DAT_0804d1a8 + 4);
    if (param_1 < uVar2) {
      local_24 = param_3;
      local_20 = param_4;
      if (DAT_0804d19d == '\0') {
        iVar1 = *(int *)(DAT_0804d1a8 + 0xc);
        for (uVar5 = 0; uVar5 < *(uint *)(DAT_0804d1a8 + 0x10); uVar5 = uVar5 + 1) {
          iVar3 = FUN_0800c554();
          if (iVar3 == 1) goto LAB_0800f190;
          thunk_FUN_080199b4(iVar1 * uVar2);
        }
        if ((true) && (iVar1 = FUN_0800c554(), iVar1 == 0)) {
          iVar1 = 2;
          goto LAB_0800f14c;
        }
LAB_0800f190:
        DAT_0804d19d = '\x01';
      }
      iVar1 = FUN_0800c420(param_1,&local_24);
      puVar4 = local_24;
      if ((((iVar1 != 1) && (iVar1 = FUN_0800c420(param_1,&local_20), puVar4 = local_20, iVar1 != 1)
           ) && (iVar1 = FUN_0800c420(param_1,&local_28), puVar4 = local_28, iVar1 != 1)) &&
         ((puVar4 = local_24, local_24 != local_20 && (local_20 == local_28)))) {
        puVar4 = local_20;
      }
      iVar1 = FUN_0800f56c(param_1,puVar4,param_2);
      if (iVar1 == 0) {
        DAT_0804d1a0 = *param_2;
        DAT_0804d1a4 = param_1;
      }
      goto LAB_0800f14c;
    }
  }
  iVar1 = 4;
LAB_0800f14c:
  return CONCAT44(local_28,iVar1);
}




/* 0x0800f1f0 */
int tsens_init()
{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined4 local_38;
  undefined1 auStack_34 [8];
  int *local_2c;
  undefined1 auStack_28 [12];
  
  if (DAT_0804d19c != '\x01') {
    iVar1 = dal_device_attach("QTsens",auStack_28);
    if ((iVar1 != 0) ||
       (iVar1 = thunk_FUN_080106aa(auStack_28,"TSENS_BOOT_BSP",0,auStack_34), iVar1 != 0)) {
      return 4;
    }
    uVar4 = 0;
    DAT_0804d1a8 = local_2c;
    for (uVar2 = 0; uVar2 < (uint)local_2c[1]; uVar2 = uVar2 + 1) {
      uVar4 = uVar4 | 1 << (uVar2 & 0xff);
    }
    FUN_0800f378(*local_2c,local_2c[1],local_2c[6],local_2c[7]);
    FUN_0800c4c8(0);
    FUN_0800c448();
    FUN_0800c438(((uint*)&DAT_0804d1a8)[5]);
    for (uVar2 = 0; uVar2 < (uint)((uint*)&DAT_0804d1a8)[1]; uVar2 = uVar2 + 1) {
      puVar3 = (undefined4 *)(*(uint*)DAT_0804d1a8 + uVar2 * 0x18);
      FUN_0800c280(uVar2,*puVar3);
      if (puVar3[4] == 0x7fffffff) {
        FUN_0800c2a0(0,uVar2);
      }
      else {
        iVar1 = FUN_0800f510(uVar2,puVar3[4],&local_38);
        if (iVar1 != 0) {
          return iVar1;
        }
        FUN_0800c4f0(0,uVar2,local_38);
        FUN_0800c2f4(0,uVar2);
      }
      if (puVar3[5] == 0x7fffffff) {
        FUN_0800c2a0(3,uVar2);
      }
      else {
        iVar1 = FUN_0800f510(uVar2,puVar3[5],&local_38);
        if (iVar1 != 0) {
          return iVar1;
        }
        FUN_0800c4f0(3,uVar2,local_38);
        FUN_0800c2f4(3,uVar2);
      }
    }
    FUN_0800c490(((uint*)&DAT_0804d1a8)[2]);
    FUN_0800c468(0);
    FUN_0800c4a8(uVar4);
    FUN_0800c4c8(1);
    DAT_0804d19c = '\x01';
    DAT_0804d19d = 0;
  }
  return 0;
}




/* 0x0800f1f0 */
int thunk_tsens_init()
{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined4 uStack_38;
  undefined1 auStack_34 [8];
  int *piStack_2c;
  undefined1 auStack_28 [12];
  
  if (DAT_0804d19c != '\x01') {
    iVar1 = dal_device_attach("QTsens",auStack_28);
    if ((iVar1 != 0) ||
       (iVar1 = thunk_FUN_080106aa(auStack_28,"TSENS_BOOT_BSP",0,auStack_34), iVar1 != 0)) {
      return 4;
    }
    uVar4 = 0;
    DAT_0804d1a8 = piStack_2c;
    for (uVar2 = 0; uVar2 < (uint)piStack_2c[1]; uVar2 = uVar2 + 1) {
      uVar4 = uVar4 | 1 << (uVar2 & 0xff);
    }
    FUN_0800f378(*piStack_2c,piStack_2c[1],piStack_2c[6],piStack_2c[7]);
    FUN_0800c4c8(0);
    FUN_0800c448();
    FUN_0800c438(((uint*)&DAT_0804d1a8)[5]);
    for (uVar2 = 0; uVar2 < (uint)((uint*)&DAT_0804d1a8)[1]; uVar2 = uVar2 + 1) {
      puVar3 = (undefined4 *)(*(uint*)DAT_0804d1a8 + uVar2 * 0x18);
      FUN_0800c280(uVar2,*puVar3);
      if (puVar3[4] == 0x7fffffff) {
        FUN_0800c2a0(0,uVar2);
      }
      else {
        iVar1 = FUN_0800f510(uVar2,puVar3[4],&uStack_38);
        if (iVar1 != 0) {
          return iVar1;
        }
        FUN_0800c4f0(0,uVar2,uStack_38);
        FUN_0800c2f4(0,uVar2);
      }
      if (puVar3[5] == 0x7fffffff) {
        FUN_0800c2a0(3,uVar2);
      }
      else {
        iVar1 = FUN_0800f510(uVar2,puVar3[5],&uStack_38);
        if (iVar1 != 0) {
          return iVar1;
        }
        FUN_0800c4f0(3,uVar2,uStack_38);
        FUN_0800c2f4(3,uVar2);
      }
    }
    FUN_0800c490(((uint*)&DAT_0804d1a8)[2]);
    FUN_0800c468(0);
    FUN_0800c4a8(uVar4);
    FUN_0800c4c8(1);
    DAT_0804d19c = '\x01';
    DAT_0804d19d = 0;
  }
  return 0;
}




/* 0x0800f324 */
void FUN_0800f324(param_1, param_2)
int param_1; int * param_2;
{
  int iVar1;
  
  if (param_1 == 1) {
    iVar1 = *param_2 + -10;
  }
  else if (param_1 == 3) {
    iVar1 = *param_2 + -9;
  }
  else {
    if (param_1 != 4) {
      return;
    }
    iVar1 = *param_2 + -8;
  }
  *param_2 = iVar1;
  return;
}




/* 0x0800f344 */
void FUN_0800f344(param_1, param_2, param_3)
int param_1; int * param_2; int * param_3;
{
  int iVar1;
  
  if (param_1 == 1) {
    *param_2 = *param_2 + -10;
    iVar1 = *param_3 + -6;
  }
  else if (param_1 == 3) {
    *param_2 = *param_2 + -9;
    iVar1 = *param_3 + -9;
  }
  else {
    if (param_1 != 4) {
      return;
    }
    *param_2 = *param_2 + -8;
    iVar1 = *param_3 + -10;
  }
  *param_3 = iVar1;
  return;
}




/* 0x0800f378 */
void FUN_0800f378(param_1, param_2, param_3, param_4)
int param_1; uint param_2; int param_3; int param_4;
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int extraout_r3;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  iVar6 = 0;
  iVar8 = 0;
  iVar9 = 0;
  DAT_0804d5f8 = param_2;
  DAT_0804d604 = FUN_0800c364();
  DAT_0804d5fc = param_3;
  DAT_0804d600 = param_4;
  uVar1 = FUN_0800c568();
  uVar2 = FUN_0800c270();
  switch(uVar2) {
  case 2:
  case 4:
    iVar6 = FUN_0800c33c(uVar1);
    break;
  case 3:
  case 6:
    iVar6 = FUN_0800c33c(uVar1);
    iVar8 = FUN_0800c350(uVar1);
    break;
  case 5:
    iVar6 = FUN_0800c33c(uVar1);
    iVar8 = FUN_0800c350(uVar1);
    iVar9 = ((param_4 - param_3) * 0x8000) / (iVar8 - iVar6);
  }
  uVar5 = 0;
  do {
    if (DAT_0804d5f8 <= uVar5) {
      return;
    }
    iVar7 = param_1 + uVar5 * 0x18;
    uVar3 = uVar2;
    if (*(char *)(iVar7 + 4) != '\0') {
      if (*(char *)(iVar7 + 4) != '\x01') {
        return;
      }
      uVar3 = 0;
    }
    switch(uVar3) {
    case 2:
      iVar4 = FUN_0800c36a(uVar1,uVar5);
      (&DAT_08054bb4)[uVar5] = iVar6 + iVar4;
      FUN_0800f324(uVar5,&DAT_08054bb4 + uVar5);
      goto LAB_0800f49a;
    case 3:
      iVar7 = FUN_0800c36a(uVar1,uVar5);
      (&DAT_08054bb4)[uVar5] = iVar7 + iVar6;
      iVar7 = FUN_0800c3bc(uVar1,uVar5);
      (&DAT_08054bf4)[uVar5] = iVar7 + iVar8;
      FUN_0800f344(uVar5,&DAT_08054bb4 + uVar5,&DAT_08054bf4 + uVar5);
      iVar7 = *(int *)(extraout_r3 + uVar5 * 4);
      break;
    case 4:
      iVar4 = FUN_0800c36a(uVar1,uVar5);
      iVar4 = iVar6 + iVar4;
      goto LAB_0800f496;
    case 5:
      iVar7 = FUN_0800c36a(uVar1,uVar5);
      (&DAT_08054bb4)[uVar5] = iVar6 + iVar7;
      (&DAT_08054c34)[uVar5] = iVar9;
      goto LAB_0800f472;
    case 6:
      iVar7 = FUN_0800c36a(uVar1,uVar5);
      (&DAT_08054bb4)[uVar5] = iVar7 + iVar6;
      iVar7 = FUN_0800c3bc(uVar1,uVar5);
      iVar7 = iVar8 + iVar7;
      (&DAT_08054bf4)[uVar5] = iVar7;
      break;
    default:
      iVar4 = *(int *)(iVar7 + 8);
LAB_0800f496:
      (&DAT_08054bb4)[uVar5] = iVar4;
LAB_0800f49a:
      (&DAT_08054c34)[uVar5] = *(undefined4 *)(iVar7 + 0xc);
      goto LAB_0800f472;
    }
    uVar3 = FUN_0800f5b8(0x8000,(&DAT_08054bb4)[uVar5],DAT_0804d5fc,iVar7,DAT_0804d600);
    (&DAT_08054c34)[uVar5] = uVar3;
LAB_0800f472:
    (&DAT_08054c74)[uVar5] = 1;
    uVar5 = uVar5 + 1;
  } while( true );
}




/* 0x0800f510 */
undefined4 FUN_0800f510(param_1, param_2, param_3)
int param_1; int param_2; uint * param_3;
{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = (param_2 - DAT_0804d5fc) * 0x8000;
  iVar1 = (int)(&DAT_08054c34)[param_1] >> 1;
  if (iVar3 < 0) {
    iVar1 = -iVar1;
  }
  uVar2 = (iVar1 + iVar3) / (int)(&DAT_08054c34)[param_1] + (&DAT_08054bb4)[param_1];
  if ((int)uVar2 < 0) {
    uVar2 = 0;
  }
  else if (DAT_0804d604 < uVar2) {
    *param_3 = DAT_0804d604;
    goto LAB_0800f54e;
  }
  *param_3 = uVar2;
LAB_0800f54e:
  if ((&DAT_08054c74)[param_1] != 1) {
    return 1;
  }
  return 0;
}




/* 0x0800f56c */
undefined4 FUN_0800f56c(param_1, param_2, param_3)
int param_1; int param_2; int * param_3;
{
  int iVar1;
  int iVar2;
  
  iVar1 = (&DAT_08054c34)[param_1] * (param_2 - (&DAT_08054bb4)[param_1]);
  iVar2 = 0x4000;
  if (iVar1 < 0) {
    iVar2 = -0x4000;
  }
  *param_3 = (iVar1 + iVar2) / 0x8000 + DAT_0804d5fc;
  if ((&DAT_08054c74)[param_1] != 1) {
    return 1;
  }
  return 0;
}




/* 0x0800f5b8 */
int FUN_0800f5b8(param_1, param_2, param_3, param_4, param_5)
int param_1; int param_2; int param_3; int param_4; int param_5;
{
  return (param_1 * (param_5 - param_3)) / (param_4 - param_2);
}




/* 0x0800f5cc */
undefined4 FUN_0800f5cc(param_1)
int param_1;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (*(int *)(param_1 + 0x24) == 0) {
    uVar3 = 1;
    uVar2 = 0xb2;
  }
  else {
    iVar1 = thunk_FUN_0800a7e4((&DAT_0803d390)[*(int *)(param_1 + 0x24)]);
    if (iVar1 != 0) {
      return 0;
    }
    uVar2 = 0xba;
    uVar3 = 0;
  }
  FUN_08038460(0x14,uVar2,uVar3,0,0,0);
  return 1;
}




/* 0x0800f608 */
undefined4 FUN_0800f608(param_1, param_2, param_3, param_4)
int param_1; int param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int *piVar4;
  
  piVar4 = &DAT_0803d380;
  do {
    iVar1 = *piVar4;
    if (iVar1 == 0) {
LAB_0800f63c:
      iVar1 = 0;
      uVar2 = 0xd6;
LAB_0800f664:
      FUN_08038460(0x14,uVar2,1,iVar1,0,0);
      return 1;
    }
    if (iVar1 == param_2) {
      if (iVar1 != 0) {
        uVar3 = *(uint *)(param_1 + 0x24);
        if ((uVar3 == 0) || (0xc < uVar3)) {
          FUN_08038460(0x14,0xdd,1,uVar3,0,0);
          *(undefined4 *)(param_1 + 0x24) = 0;
          return 1;
        }
        iVar1 = thunk_FUN_0800b058(piVar4[1],(&DAT_0803d390)[uVar3],param_3,uVar3,param_3,param_4);
        if (iVar1 != 0) {
          return 0;
        }
        uVar2 = 0xe5;
        iVar1 = *piVar4;
        goto LAB_0800f664;
      }
      goto LAB_0800f63c;
    }
    piVar4 = piVar4 + 2;
  } while( true );
}




/* 0x0800f674 */
bool FUN_0800f674(param_1)
int param_1;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  
  if (param_1 == 0) {
    uVar6 = 0x175;
  }
  else {
    if (*(char *)(param_1 + 4) != '\0') {
      uVar6 = *(undefined4 *)(param_1 + 8);
      iVar1 = 1000000 / *(uint *)(param_1 + 0xc) + 1;
      iVar2 = FUN_0800c5a2(uVar6);
      uVar4 = iVar1 * 10 * iVar2 * 2;
      uVar5 = iVar1 * 100;
      do {
        iVar1 = FUN_0800c598(uVar6);
        if (iVar1 << 0x1c < 0) goto LAB_0800f6f4;
        thunk_FUN_080199b4(uVar5);
        uVar3 = uVar4;
        if (uVar5 < uVar4) {
          uVar3 = uVar5;
        }
        uVar4 = uVar4 - uVar3;
      } while (uVar4 != 0);
      FUN_08038460(10,0xbe,0,0,0,0);
LAB_0800f6f4:
      *(undefined1 *)(param_1 + 4) = 0;
      iVar1 = FUN_0800f5cc(param_1);
      if (iVar1 != 0) {
        FUN_08038460(10,0x186,0,0,0,0);
      }
      iVar2 = FUN_0800f988(param_1);
      if (iVar2 != 0) {
        FUN_08038460(10,0x18b,0,0,0,0);
      }
      return iVar2 != 0 || iVar1 != 0;
    }
    uVar6 = 0x17c;
  }
  FUN_08038460(10,uVar6,0,0,0,0);
  return true;
}




/* 0x0800f750 */
undefined4 uart_init()
{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_20 [8];
  undefined1 auStack_18 [8];
  undefined4 local_10;
  
  iVar1 = dal_device_attach("/core/buses/uart",auStack_20);
  if (iVar1 == 0) {
    iVar1 = thunk_FUN_080106aa(auStack_20,"UartMainPortPhy",0,auStack_18);
    if (iVar1 == 0) {
      DAT_0804e22c = local_10;
    }
    else {
      DAT_0804e22c = 0;
    }
    uVar2 = 0;
  }
  else {
    FUN_08038460(0x14,0xfc,0,0,0,0);
    uVar2 = 1;
  }
  return uVar2;
}




/* 0x0800f7bc */
bool FUN_0800f7bc(param_1, param_2, param_3, param_4)
undefined4 * param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  uStack_10 = param_3;
  uStack_c = param_4;
  iVar1 = dal_device_attach(*param_1,&uStack_10,param_3,param_4,param_1,param_2);
  if (iVar1 == 0) {
    FUN_08021e7c(&uStack_10,"IsLoopback",param_1 + 4,0);
    FUN_08021e7c(&uStack_10,"BitRate",param_1 + 3,0);
    FUN_08021e7c(&uStack_10,"UartBase",param_1 + 2,0);
    FUN_08021e7c(&uStack_10,"GpioTxData",param_1 + 5,0);
    FUN_08021e7c(&uStack_10,"GpioRxData",param_1 + 6,0);
    FUN_08021e7c(&uStack_10,"GpioRfrN",param_1 + 8,0);
    FUN_08021e7c(&uStack_10,"GpioCtsN",param_1 + 7,0);
    FUN_08021e7c(&uStack_10,"ClockIdIndex",param_1 + 9,0);
  }
  else {
    FUN_08038460(0x14,0x115,0,0,0,0);
  }
  return iVar1 != 0;
}




/* 0x0800f988 */
bool FUN_0800f988(param_1)
int param_1;
{
  int iVar1;
  uint uVar2;
  int local_18 [5];
  
  iVar1 = *(int *)(param_1 + 0x20);
  if (iVar1 != 0) {
    local_18[0] = iVar1;
  }
  uVar2 = (uint)(iVar1 != 0);
  if (*(int *)(param_1 + 0x1c) != 0) {
    local_18[uVar2] = *(int *)(param_1 + 0x1c);
    uVar2 = uVar2 + 1;
  }
  if (*(int *)(param_1 + 0x14) != 0) {
    local_18[uVar2] = *(int *)(param_1 + 0x14);
    uVar2 = uVar2 + 1;
  }
  if (*(int *)(param_1 + 0x18) != 0) {
    local_18[uVar2] = *(int *)(param_1 + 0x18);
    uVar2 = uVar2 + 1;
  }
  iVar1 = FUN_0800eff4(0,local_18,uVar2);
  if (iVar1 != 0) {
    FUN_08038460(0x14,0x13e,0,0,0,0);
  }
  return iVar1 != 0;
}




/* 0x0800f9dc */
undefined4 FUN_0800f9dc(param_1)
int param_1;
{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int local_18 [4];
  
  iVar1 = *(int *)(param_1 + 0x20);
  if (iVar1 != 0) {
    local_18[0] = iVar1;
  }
  uVar3 = (uint)(iVar1 != 0);
  if (*(int *)(param_1 + 0x1c) != 0) {
    local_18[uVar3] = *(int *)(param_1 + 0x1c);
    uVar3 = uVar3 + 1;
  }
  if (*(int *)(param_1 + 0x14) != 0) {
    local_18[uVar3] = *(int *)(param_1 + 0x14);
    uVar3 = uVar3 + 1;
  }
  if (*(int *)(param_1 + 0x18) != 0) {
    local_18[uVar3] = *(int *)(param_1 + 0x18);
    uVar3 = uVar3 + 1;
  }
  iVar1 = *(int *)(param_1 + 0x14);
  if ((iVar1 == 0) || (*(int *)(param_1 + 0x18) == 0)) {
    uVar5 = *(undefined4 *)(param_1 + 0x18);
    uVar4 = 2;
    uVar2 = 0x15d;
  }
  else {
    iVar1 = FUN_0800eff4(1,local_18,uVar3);
    if (iVar1 == 0) {
      return 0;
    }
    iVar1 = 0;
    uVar2 = 0x166;
    uVar4 = 0;
    uVar5 = 0;
  }
  FUN_08038460(0x14,uVar2,uVar4,iVar1,uVar5,0);
  return 1;
}




/* 0x0800fa46 */
int FUN_0800fa46(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  
  if (param_1 == 0) {
    uVar1 = 0x236;
  }
  else if (param_2 == 0) {
    uVar1 = 0x23c;
  }
  else {
    if (param_3 == 0) {
      return 0;
    }
    if (*(char *)(param_1 + 4) != '\0') {
      uVar1 = *(undefined4 *)(param_1 + 8);
      iVar7 = 0;
      uVar2 = FUN_0800c5a2();
      iVar8 = (1000000 / *(uint *)(param_1 + 0xc) + 1) * 10;
      uVar5 = param_3 * iVar8 * 2;
      uVar6 = param_3;
      do {
        if (uVar6 == 0) {
          return iVar7;
        }
        iVar3 = FUN_0800c704(uVar1,param_2 + iVar7,uVar6);
        iVar7 = iVar7 + iVar3;
        uVar6 = param_3 - iVar7;
        if (uVar6 == 0) {
          return iVar7;
        }
        if (uVar5 == 0) {
          FUN_08038460(10,0xf1,1,uVar6,0,0);
          return iVar7;
        }
        do {
          uVar4 = FUN_0800c58e(uVar1);
          if ((uVar4 & 1) != 0) break;
          uVar4 = uVar6;
          if (uVar2 < uVar6) {
            uVar4 = uVar2;
          }
          uVar4 = uVar4 * iVar8;
          thunk_FUN_080199b4(uVar4);
          if (uVar5 <= uVar4) {
            uVar4 = uVar5;
          }
          uVar5 = uVar5 - uVar4;
        } while (uVar5 != 0);
      } while( true );
    }
    uVar1 = 0x246;
  }
  FUN_08038460(10,uVar1,0,0,0,0);
  return 0;
}




/* 0x0800fa46 */
int thunk_FUN_0800fa46(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  
  if (param_1 == 0) {
    uVar1 = 0x236;
  }
  else if (param_2 == 0) {
    uVar1 = 0x23c;
  }
  else {
    if (param_3 == 0) {
      return 0;
    }
    if (*(char *)(param_1 + 4) != '\0') {
      uVar1 = *(undefined4 *)(param_1 + 8);
      iVar7 = 0;
      uVar2 = FUN_0800c5a2();
      iVar8 = (1000000 / *(uint *)(param_1 + 0xc) + 1) * 10;
      uVar5 = param_3 * iVar8 * 2;
      uVar6 = param_3;
      do {
        if (uVar6 == 0) {
          return iVar7;
        }
        iVar3 = FUN_0800c704(uVar1,param_2 + iVar7,uVar6);
        iVar7 = iVar7 + iVar3;
        uVar6 = param_3 - iVar7;
        if (uVar6 == 0) {
          return iVar7;
        }
        if (uVar5 == 0) {
          FUN_08038460(10,0xf1,1,uVar6,0,0);
          return iVar7;
        }
        do {
          uVar4 = FUN_0800c58e(uVar1);
          if ((uVar4 & 1) != 0) break;
          uVar4 = uVar6;
          if (uVar2 < uVar6) {
            uVar4 = uVar2;
          }
          uVar4 = uVar4 * iVar8;
          thunk_FUN_080199b4(uVar4);
          if (uVar5 <= uVar4) {
            uVar4 = uVar5;
          }
          uVar5 = uVar5 - uVar4;
        } while (uVar5 != 0);
      } while( true );
    }
    uVar1 = 0x246;
  }
  FUN_08038460(10,uVar1,0,0,0,0);
  return 0;
}




/* 0x0800fa90 */
int FUN_0800fa90(param_1, param_2, param_3)
undefined4 * param_1; uint * param_2; uint param_3;
{
  int iVar1;
  int iVar2;
  uint *local_1c;
  uint local_18;
  int local_14;
  
  iVar1 = DAT_0804cd58;
  local_14 = DAT_0804cd58;
  local_1c = param_2;
  local_18 = param_3;
  iVar2 = ((code *)param_1[2])(*param_1,0x60,&local_18,2,&local_1c);
  if (iVar2 == 0) {
    if (local_1c == (uint *)0x2) {
      iVar2 = 0;
      *param_2 = local_18 & 0xffff;
    }
    else {
      iVar2 = 1;
    }
  }
  if (local_14 != iVar1) {
    FUN_08010960();
  }
  return iVar2;
}




/* 0x0800fad8 */
int FUN_0800fad8(param_1, param_2)
undefined4 * param_1; undefined1 * param_2;
{
  int iVar1;
  int iVar2;
  int local_24;
  undefined1 local_20;
  undefined1 local_1f;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  int local_18;
  
  iVar1 = DAT_0804cd58;
  local_18 = DAT_0804cd58;
  iVar2 = ((code *)param_1[2])(*param_1,0,&local_20,6,&local_24);
  if (iVar2 == 0) {
    if (local_24 == 6) {
      param_2[1] = local_20;
      *param_2 = local_1f;
      param_2[3] = local_1e;
      param_2[2] = local_1d;
      param_2[4] = local_1c;
      param_2[5] = local_1b;
    }
    else {
      iVar2 = 1;
    }
  }
  if (local_18 != iVar1) {
    FUN_08010960();
  }
  return iVar2;
}




/* 0x0800fb40 */
int FUN_0800fb40(param_1, param_2, param_3)
undefined4 * param_1; byte * param_2; uint param_3;
{
  int iVar1;
  int iVar2;
  byte *local_1c;
  undefined4 local_18;
  int local_14;
  
  iVar1 = DAT_0804cd58;
  local_14 = DAT_0804cd58;
  local_1c = param_2;
  local_18 = param_3;
  iVar2 = ((code *)param_1[2])(*param_1,8,&local_18,2,&local_1c);
  if (iVar2 == 0) {
    if (local_1c == (byte *)0x2) {
      *param_2 = (byte)((local_18 << 0x1b) >> 0x1e);
      param_2[1] = (byte)((local_18 << 0x1d) >> 0x1f);
      param_2[2] = (byte)local_18 & 3;
      param_2[3] = _GHIDRA_FIELD(local_18, 1, byte) >> 3;
      if ((int)((uint)_GHIDRA_FIELD(local_18, 1, byte) << 0x1e) < 0) {
        param_2[4] = 1;
      }
      else {
        param_2[4] = 0;
      }
      if ((local_18 & 0x100) == 0) {
        param_2[5] = 0;
      }
      else {
        param_2[5] = 1;
      }
      iVar2 = 0;
    }
    else {
      iVar2 = 1;
    }
  }
  if (local_14 != iVar1) {
    FUN_08010960();
  }
  return iVar2;
}




/* 0x0800fbd0 */
undefined4 FUN_0800fbd0(param_1, param_2, param_3)
undefined4 * param_1; undefined4 param_2; undefined4 param_3;
{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_18;
  undefined3 uStack_17;
  int local_14;
  
  iVar1 = DAT_0804cd58;
  local_14 = DAT_0804cd58;
  _local_18 = CONCAT31((int3)((uint)param_3 >> 8),0x80);
  uVar2 = ((code *)param_1[1])(*param_1,0x52,&local_18,1);
  if (local_14 != iVar1) {
    FUN_08010960();
  }
  return uVar2;
}




/* 0x0800fc00 */
int FUN_0800fc00(param_1, param_2, param_3)
undefined4 * param_1; undefined4 * param_2; undefined4 param_3;
{
  int iVar1;
  int iVar2;
  undefined4 local_20;
  int local_1c;
  
  iVar1 = DAT_0804cd58;
  local_1c = DAT_0804cd58;
  local_20 = CONCAT31((int3)((uint)param_3 >> 8),(char)*param_2);
  iVar2 = ((code *)param_1[1])(*param_1,0x48,&local_20,1);
  if (iVar2 == 0) {
    local_20 = CONCAT22(_GHIDRA_FIELD(local_20, 2, ushort),
                        CONCAT11(*(undefined1 *)((int)param_2 + 6),
                                 (*(byte *)(param_2 + 1) & 3) << 2 | *(byte *)((int)param_2 + 5) & 3
                                )) & 0xffff0fff;
    iVar2 = ((code *)param_1[1])(*param_1,0x50,&local_20,2);
    if (iVar2 == 0) {
      _GHIDRA_FIELD(local_20, 0, ushort) = 0;
      if (*(ushort *)(param_2 + 2) != 0xffff) {
        _GHIDRA_FIELD(local_20, 0, ushort) = CONCAT11(0x80,(byte)(((uint)*(ushort *)(param_2 + 2) << 0x1c) >> 0x1c));
      }
      iVar2 = ((code *)param_1[1])(*param_1,0x5a,&local_20,2);
    }
  }
  if (local_1c != iVar1) {
    FUN_08010960();
  }
  return iVar2;
}




/* 0x0800fc9c */
undefined4 FUN_0800fc9c(param_1, param_2, param_3)
undefined4 * param_1; char param_2; undefined4 param_3;
{
  int iVar1;
  undefined4 uVar2;
  char local_18;
  undefined3 uStack_17;
  int local_14;
  
  iVar1 = DAT_0804cd58;
  local_14 = DAT_0804cd58;
  _local_18 = CONCAT31((int3)((uint)param_3 >> 8),param_2 << 7);
  uVar2 = ((code *)param_1[1])(*param_1,0x46,&local_18,1);
  if (local_14 != iVar1) {
    FUN_08010960();
  }
  return uVar2;
}




/* 0x0800fcd0 */
undefined4 FUN_0800fcd0(param_1, param_2, param_3)
undefined4 * param_1; byte param_2; undefined4 param_3;
{
  int iVar1;
  undefined4 uVar2;
  uint local_18;
  int local_14;
  
  iVar1 = DAT_0804cd58;
  local_14 = DAT_0804cd58;
  _GHIDRA_FIELD(local_18, 1, uint24_t) = (undefined3)((uint)param_3 >> 8);
  local_18 = CONCAT31(_GHIDRA_FIELD(local_18, 1, uint24_t),(param_2 & 3) << 3) | 3;
  uVar2 = ((code *)param_1[1])(*param_1,0x40,&local_18,1);
  if (local_14 != iVar1) {
    FUN_08010960();
  }
  return uVar2;
}




/* 0x0800fd04 */
undefined4 FUN_0800fd04(param_1, param_2, param_3)
undefined4 * param_1; char * param_2; undefined4 param_3;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_18;
  int local_14;
  
  iVar1 = DAT_0804cd58;
  local_14 = DAT_0804cd58;
  _GHIDRA_FIELD(local_18, 0, ushort) = CONCAT11(param_2[2] << 7 | param_2[3] & 3U,*param_2 << 4 | param_2[1] & 0xfU);
  local_18 = CONCAT22((short)((uint)param_3 >> 0x10),(undefined2)local_18);
  uVar2 = ((code *)param_1[1])(*param_1,0x54,&local_18,2);
  if (local_14 != iVar1) {
    FUN_08010960();
  }
  return uVar2;
}




/* 0x0800fd64 */
int FUN_0800fd64(param_1, param_2)
undefined4 * param_1; undefined4 param_2;
{
  int iVar1;
  int iVar2;
  undefined4 *local_28;
  undefined1 local_24;
  undefined3 uStack_23;
  int local_20;
  int local_1c;
  
  iVar1 = DAT_0804cd58;
  local_20 = DAT_0804cd58;
  local_1c = DAT_0804cd58;
  _local_24 = CONCAT31((int3)((uint)param_2 >> 8),0xa5);
  local_28 = param_1;
  iVar2 = ((code *)param_1[1])(*param_1,0xd0,&local_24,1);
  if (local_1c != iVar1) {
    FUN_08010960();
  }
  if (iVar2 == 0) {
    local_28 = (undefined4 *)CONCAT31(_GHIDRA_FIELD(local_28, 1, uint24_t),(char)param_2);
    iVar2 = ((code *)param_1[1])(*param_1,0xe1,&local_28,1);
  }
  if (local_20 != iVar1) {
    FUN_08010960();
  }
  return iVar2;
}




/* 0x0800fdbc */
undefined4 FUN_0800fdbc(param_1)
int param_1;
{
  *(uint *)(param_1 + 8) = (*(uint *)(param_1 + 0x10) >> 1) - 0x42b08;
  return 0;
}




/* 0x0800fdd0 */
undefined4 FUN_0800fdd0(param_1, param_2, param_3)
int param_1; undefined4 param_2; undefined4 param_3;
{
  uint uVar1;
  
  uVar1 = 0xffff - *(int *)(param_1 + 0xc);
  if ((uVar1 == 0) ||
     (uVar1 = ((uVar1 >> 1) + *(int *)(param_1 + 0xc) * 0x4000) / uVar1, 0x7fffffff < uVar1)) {
    uVar1 = 0x7fffffff;
  }
  FUN_08008e24(param_2,param_3,uVar1,param_1 + 8);
  return 0;
}




/* 0x0800fe0a */
int FUN_0800fe0a(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 local_24;
  
  uVar5 = *(uint *)(*(int *)(param_1 + 0x5c) + 0x4c);
  iVar1 = *(int *)(param_1 + 0xa8);
  uVar4 = 0;
  uStack_2c = param_2;
  uStack_28 = param_3;
  local_24 = param_4;
  do {
    if (uVar5 <= uVar4) {
      *(undefined4 *)(param_1 + 0xa8) = 1;
      return 0;
    }
    puVar3 = (undefined4 *)(*(int *)(param_1 + 0xac) + uVar4 * 0x18);
    iVar2 = FUN_080102b0(param_1,*(undefined4 *)(*(int *)(param_1 + 0x5c) + 0x60),uVar4,&uStack_2c,
                         &local_24);
    if (iVar2 != 0) {
      return iVar2;
    }
    *puVar3 = local_24;
    iVar2 = FUN_080102b0(param_1,*(int *)(*(int *)(param_1 + 0x5c) + 0x60) + 0x30,uVar4,&uStack_2c,
                         &local_24);
    if (iVar2 != 0) {
      return iVar2;
    }
    puVar3[1] = local_24;
    if (iVar1 == 0) {
      iVar2 = FUN_080102b0(param_1,*(int *)(*(int *)(param_1 + 0x5c) + 0x60) + 0x60,uVar4,&uStack_2c
                           ,&local_24);
      if (iVar2 != 0) {
        return iVar2;
      }
      puVar3[2] = local_24;
      iVar2 = FUN_080102b0(param_1,*(int *)(*(int *)(param_1 + 0x5c) + 0x60) + 0x90,uVar4,&uStack_2c
                           ,&local_24);
      if (iVar2 != 0) {
        return iVar2;
      }
      puVar3[3] = local_24;
    }
    iVar2 = FUN_080104d2(puVar3[2],puVar3[1],*puVar3,puVar3 + 4);
    if ((iVar2 != 0) || (iVar2 = FUN_080104d2(puVar3[3],puVar3[1],*puVar3,puVar3 + 5), iVar2 != 0))
    {
      return -1;
    }
    uVar4 = uVar4 + 1;
  } while( true );
}




/* 0x0800fee6 */
undefined4 FUN_0800fee6(param_1)
int param_1;
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if (*(int *)(*(int *)(param_1 + 0xc) + 0x60) != 0) {
    iVar1 = FUN_0800fc9c(*(int *)(param_1 + 0xc) + 0x68,0);
    if (iVar1 != 0) {
      uVar2 = 0xffffffff;
    }
    return uVar2;
  }
  return 0;
}




/* 0x0800ff04 */
int FUN_0800ff04(param_1, param_2, param_3)
undefined4 param_1; int param_2; int * param_3;
{
  int iVar1;
  int local_18;
  
  local_18 = 0;
  *param_3 = 0;
  iVar1 = FUN_0800b61e(0x1c,&local_18);
  if (iVar1 != 0) {
    return -1;
  }
  if (local_18 == 0) {
    return -1;
  }
  FUN_08006d14(local_18,0x1c);
  if (param_2 == 0) {
    iVar1 = FUN_0800b236(param_1,&DAT_08050b28,local_18);
    if (iVar1 != 0) goto LAB_0800ff68;
    iVar1 = dal_device_attach(param_1,*(int *)(local_18 + 0xc) + 0x10);
  }
  else {
    iVar1 = FUN_0800b1b6(param_2);
    if (iVar1 != 0) goto LAB_0800ff68;
    iVar1 = thunk_FUN_08010668(param_2,*(int *)(local_18 + 0xc) + 0x10);
  }
  if (iVar1 == 0) {
    *(undefined4 *)(local_18 + 0x10) = 0xda1fda1f;
    *(undefined ***)(local_18 + 0x14) = &PTR_FUN_0800ff04_1_0803d3a0;
    *(int *)(local_18 + 0x18) = local_18;
    FUN_0800b19a(*(undefined4 *)(local_18 + 0x18));
    *param_3 = local_18 + 0x10;
    return 0;
  }
LAB_0800ff68:
  FUN_0800b574(local_18);
  return iVar1;
}




/* 0x0800fffe */
undefined4 FUN_0800fffe(param_1)
int param_1;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = *(int *)(param_1 + 0xc);
  uVar3 = 0;
  FUN_0800e4dc();
  if (*(int *)(iVar2 + 0xac) != 0) {
    iVar1 = FUN_0800b574();
    if (iVar1 != 0) {
      uVar3 = 0xffffffff;
    }
    *(undefined4 *)(iVar2 + 0xac) = 0;
  }
  return uVar3;
}




/* 0x08010020 */
int FUN_08010020(param_1)
int param_1;
{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined1 auStack_48 [20];
  undefined4 local_34;
  undefined1 auStack_1c [8];
  undefined4 local_14;
  
  iVar3 = *(int *)(param_1 + 0xc);
  *(undefined4 *)(iVar3 + 0x60) = 1;
  iVar1 = thunk_FUN_080106aa(iVar3 + 0x10,"VADC_BSP",0,auStack_1c);
  if (iVar1 != 0) {
    return iVar1;
  }
  *(undefined4 *)(iVar3 + 0x5c) = local_14;
  iVar1 = FUN_0800e51c();
  if (iVar1 != 0) {
    return -1;
  }
  *(int *)(iVar3 + 100) = iVar3;
  *(int *)(iVar3 + 0x68) = iVar3 + 100;
  *(undefined4 *)(iVar3 + 0x6c) = 0x80105ed;
  *(undefined4 *)(iVar3 + 0xa8) = 0;
  *(undefined4 *)(iVar3 + 0x70) = 0x80103bb;
  iVar1 = FUN_0800b61e(*(int *)(*(int *)(iVar3 + 0x5c) + 0x4c) * 0x18,iVar3 + 0xac);
  if (iVar1 != 0) {
    return iVar1;
  }
  iVar1 = FUN_0802b5dc(*(uint *)(*(int *)(iVar3 + 0x5c) + 8) & 0xff,auStack_48);
  if (iVar1 == 0) {
    *(undefined4 *)(iVar3 + 0xd8) = local_34;
    iVar1 = FUN_0800fd64(iVar3 + 0x68,local_34);
    if (iVar1 == 0) {
      iVar1 = 0;
      goto LAB_0801009e;
    }
  }
  iVar1 = -1;
LAB_0801009e:
  if (iVar1 != 0) {
    return iVar1;
  }
  iVar1 = FUN_0800fad8(iVar3 + 0x68,iVar3 + 0xa0);
  if (iVar1 != 0) {
    return -1;
  }
  iVar1 = *(int *)(iVar3 + 0x5c);
  if (*(uint *)(iVar1 + 0x28) != (uint)*(byte *)(iVar3 + 0xa4)) {
    *(undefined4 *)(iVar3 + 0x60) = 0;
  }
  if (*(uint *)(iVar1 + 0x2c) != (uint)*(byte *)(iVar3 + 0xa5)) {
    *(undefined4 *)(iVar3 + 0x60) = 0;
  }
  if (((uint)*(byte *)(iVar3 + 0xa0) < *(uint *)(iVar1 + 0x1c)) ||
     (((uint)*(byte *)(iVar3 + 0xa0) == *(uint *)(iVar1 + 0x1c) &&
      ((uint)*(byte *)(iVar3 + 0xa1) < *(uint *)(iVar1 + 0x18))))) {
    *(undefined4 *)(iVar3 + 0x60) = 0;
  }
  if (((uint)*(byte *)(iVar3 + 0xa2) < *(uint *)(iVar1 + 0x24)) ||
     (((uint)*(byte *)(iVar3 + 0xa2) == *(uint *)(iVar1 + 0x24) &&
      ((uint)*(byte *)(iVar3 + 0xa3) < *(uint *)(iVar1 + 0x20))))) {
    *(undefined4 *)(iVar3 + 0x60) = 0;
  }
  else if (*(int *)(iVar3 + 0x60) != 0) {
    for (uVar4 = 0; iVar1 = *(int *)(iVar3 + 0x5c), uVar4 < *(uint *)(iVar1 + 0x54);
        uVar4 = uVar4 + 1) {
      iVar2 = *(int *)(iVar1 + 0x58) + uVar4 * 0x30;
      if (*(char *)(iVar2 + 0x2d) == '\x01') {
        if (*(char *)(iVar2 + 0x2e) == '\x10') {
          return -1;
        }
        if (*(char *)(iVar2 + 0x2f) == '\b') {
          return -1;
        }
        iVar1 = FUN_0802c736(*(undefined4 *)(iVar1 + 8),*(char *)(iVar2 + 0x2e));
        if (iVar1 != 0) {
          return -1;
        }
      }
    }
  }
  return 0;
}




/* 0x08010168 */
undefined4 FUN_08010168(param_1, param_2, param_3)
int param_1; undefined4 param_2; uint * param_3;
{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = *(int *)(param_1 + 0xc);
  if (*(int *)(iVar3 + 0x60) != 0) {
    uVar4 = *(uint *)(*(int *)(iVar3 + 0x5c) + 0x54);
    for (uVar2 = 0; uVar2 < uVar4; uVar2 = uVar2 + 1) {
      iVar1 = FUN_08006d64(param_2,*(undefined4 *)
                                    (*(int *)(*(int *)(iVar3 + 0x5c) + 0x58) + uVar2 * 0x30));
      if (iVar1 == 0) {
        *param_3 = uVar2;
        return 0;
      }
    }
  }
  return 0xffffffff;
}




/* 0x080101c2 */
undefined4 FUN_080101c2(param_1)
int param_1;
{
  int iVar1;
  undefined4 uVar2;
  
  if (*(int *)(*(int *)(param_1 + 0xc) + 0x60) != 0) {
    iVar1 = FUN_0800fc9c(*(int *)(param_1 + 0xc) + 0x68,1);
    uVar2 = 0;
    if (iVar1 != 0) {
      uVar2 = 0xffffffff;
    }
    return uVar2;
  }
  return 0;
}




/* 0x080101e4 */
void FUN_080101e4(param_1, param_2, param_3, param_4, param_5, param_6)
int param_1; undefined4 param_2; int param_3; undefined4 * param_4; undefined4 param_5; undefined4 * param_6;
{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  int local_20;
  
  local_20 = 0;
  param_6[5] = param_5;
  uVar2 = FUN_080104d2(param_5,param_4[1],*param_4,&local_20,param_2,param_3);
  *param_6 = uVar2;
  param_6[1] = param_2;
  param_6[3] = local_20;
  if (*(char *)(param_3 + 0x2c) == '\0') {
    param_6[4] = (local_20 * ((uint)(*(int *)(*(int *)(param_1 + 0x5c) + 0x30) * 100000) / 0xffff))
                 / 100;
  }
  else if (*(char *)(param_3 + 0x2c) == '\x01') {
    uVar2 = FUN_0801052c(local_20,param_4[4],param_4[5],
                         *(undefined4 *)(*(int *)(param_1 + 0x5c) + 0x38),
                         *(undefined4 *)(*(int *)(param_1 + 0x5c) + 0x3c),param_6 + 4);
    *param_6 = uVar2;
  }
  if (*(int *)(param_3 + 0x18) == 0) {
    *param_6 = 1;
    uVar3 = param_6[4];
  }
  else {
    uVar3 = *(int *)(param_3 + 0x1c) * param_6[4];
    param_6[4] = uVar3;
    uVar3 = uVar3 / *(uint *)(param_3 + 0x18);
    param_6[4] = uVar3;
  }
  param_6[2] = uVar3 / 1000;
  cVar1 = *(char *)(param_3 + 0x20);
  if (cVar1 != '\0') {
    if (cVar1 == '\x01') {
      uVar2 = FUN_0800fdbc(param_6);
    }
    else if (cVar1 == '\x02') {
      uVar2 = FUN_0800fdd0(param_6,*(undefined4 *)(param_3 + 0x24),*(undefined4 *)(param_3 + 0x28));
    }
    else {
      if (cVar1 != '\x03') {
        return;
      }
      uVar2 = FUN_08008e24(*(undefined4 *)(param_3 + 0x24),*(undefined4 *)(param_3 + 0x28),
                           uVar3 / 1000,param_6 + 2);
    }
    *param_6 = uVar2;
  }
  return;
}




/* 0x080102b0 */
int FUN_080102b0(param_1, param_2, param_3, param_4, param_5)
int param_1; undefined4 param_2; int param_3; int param_4; int * param_5;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int local_28;
  
  iVar2 = *(int *)(*(int *)(param_1 + 0x5c) + 0x50) + param_3 * 8;
  local_28 = param_4;
  iVar1 = FUN_08010572(param_1,iVar2,param_2);
  if (iVar1 == 0) {
    uVar4 = *(uint *)(iVar2 + 4);
    uVar3 = 0;
    iVar1 = *(int *)(*(int *)(param_1 + 0x5c) + 0x40);
    do {
      thunk_FUN_080199b4(0x32);
      uVar3 = uVar3 + 0x32;
      if (uVar4 <= uVar3) {
        iVar2 = FUN_0800fb40(param_1 + 0x68,param_4);
        if (iVar2 != 0) break;
        if (*(char *)(param_4 + 2) == '\x01') {
          iVar1 = 0;
          goto LAB_0801030a;
        }
      }
    } while (uVar3 < iVar1 * uVar4);
    iVar1 = -1;
LAB_0801030a:
    if (iVar1 == 0) {
      iVar1 = FUN_0800fa90(param_1 + 0x68,&local_28);
      if (iVar1 == 0) {
        *param_5 = local_28;
        iVar1 = 0;
      }
      else {
        iVar1 = -1;
      }
    }
  }
  return iVar1;
}




/* 0x0801032e */
undefined4 FUN_0801032e(param_1, param_2, param_3)
int param_1; int param_2; int * param_3;
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 auStack_28 [4];
  char local_24;
  char local_23;
  undefined4 local_20 [2];
  
  iVar4 = *(int *)(*(int *)(param_1 + 0x5c) + 0x58) + param_2 * 0x30;
  iVar3 = *(int *)(param_1 + 0xac);
  iVar1 = *(int *)(iVar4 + 8);
  *(int *)(param_1 + 0xb4) = param_2;
  if (((*(int *)(param_1 + 0xa8) == 0) && (iVar2 = FUN_0800fe0a(param_1), iVar2 != 0)) ||
     (iVar2 = FUN_080102b0(param_1,iVar4,*(undefined4 *)(iVar4 + 8),auStack_28,local_20), iVar2 != 0
     )) {
    iVar1 = 1;
  }
  else {
    FUN_080101e4(param_1,param_2,iVar4,iVar3 + iVar1 * 0x18,local_20[0],param_3);
    if (*(int *)(iVar4 + 0x10) != 1) {
      return 0;
    }
    if (*param_3 != 0) {
      return 0;
    }
    if (local_23 == '\x01') {
      iVar1 = 3;
    }
    else {
      if (local_24 != '\x01') {
        return 0;
      }
      iVar1 = 4;
    }
  }
  *param_3 = iVar1;
  return 0;
}




/* 0x080103ba */
undefined4 FUN_080103ba(param_1, param_2, param_3, param_4, param_5)
int * param_1; byte param_2; undefined4 param_3; undefined4 param_4; undefined4 param_5;
{
  undefined1 *puVar1;
  int iVar2;
  
  if (param_1 != (int *)0x0) {
    puVar1 = *(undefined1 **)(*param_1 + 0x5c);
    iVar2 = FUN_0800e564(*(undefined4 *)(puVar1 + 4),*puVar1,
                         (*(uint *)(puVar1 + 0xc) & 0xff) << 8 | (uint)param_2,param_3,param_4,
                         param_5);
    if (iVar2 == 0) {
      return 0;
    }
  }
  return 1;
}




/* 0x080103ea */
int FUN_080103ea(param_1, param_2, param_3)
int param_1; uint param_2; undefined4 * param_3;
{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xc);
  if (*(int *)(iVar2 + 0x60) == 0) {
    return -1;
  }
  if (param_2 < *(uint *)(*(int *)(iVar2 + 0x5c) + 0x54)) {
    *(uint *)(iVar2 + 0xb4) = param_2;
    *(undefined4 *)(iVar2 + 0xcc) = 1;
    *(undefined1 *)(iVar2 + 0xb0) = 2;
    iVar1 = FUN_0801032e(iVar2);
    *(undefined1 *)(iVar2 + 0xb0) = 0;
    *(undefined4 *)(iVar2 + 0xcc) = 0;
    if (iVar1 != 0) {
      return iVar1;
    }
  }
  else {
    *param_3 = 2;
  }
  return 0;
}




/* 0x08010430 */
int FUN_08010430(param_1, param_2, param_3)
int param_1; uint param_2; undefined4 * param_3;
{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined1 *puVar7;
  
  iVar6 = *(int *)(param_1 + 0xc);
  if (*(int *)(iVar6 + 0x60) == 0) {
    return -1;
  }
  if (param_2 < *(uint *)(*(int *)(iVar6 + 0x5c) + 0x54)) {
    puVar7 = (undefined1 *)(iVar6 + 0xb0);
    *(uint *)(iVar6 + 0xb4) = param_2;
    *(undefined4 *)(iVar6 + 0xcc) = 2;
    *puVar7 = 3;
    iVar1 = FUN_0800fe0a(iVar6);
    if (iVar1 != 0) {
      *puVar7 = 0;
      *(undefined4 *)(iVar6 + 0xcc) = 0;
      return iVar1;
    }
    *puVar7 = 0;
    *(undefined4 *)(iVar6 + 0xcc) = 0;
    iVar1 = *(int *)(*(int *)(*(int *)(iVar6 + 0x5c) + 0x58) + param_2 * 0x30 + 8);
    iVar5 = *(int *)(iVar6 + 0xac);
    *param_3 = 0;
    param_3[1] = param_2;
    iVar4 = *(int *)(iVar6 + 0x5c);
    puVar2 = (undefined4 *)(iVar5 + iVar1 * 0x18);
    if (*(char *)(*(int *)(iVar4 + 0x58) + param_2 * 0x30 + 0x2c) == '\x01') {
      param_3[2] = *(undefined4 *)(iVar4 + 0x38);
      param_3[3] = *(undefined4 *)(*(int *)(iVar6 + 0x5c) + 0x3c);
      param_3[4] = puVar2[2];
      uVar3 = puVar2[3];
    }
    else {
      param_3[2] = *(undefined4 *)(iVar4 + 0x34);
      param_3[3] = *(undefined4 *)(*(int *)(iVar6 + 0x5c) + 0x30);
      param_3[4] = puVar2[1];
      uVar3 = *puVar2;
    }
    param_3[5] = uVar3;
  }
  else {
    *param_3 = 2;
  }
  return 0;
}




/* 0x080104d2 */
undefined4 FUN_080104d2(param_1, param_2, param_3, param_4)
ushort param_1; ushort param_2; ushort param_3; uint * param_4;
{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = (uint)param_1;
  uVar2 = (uint)param_2;
  uVar3 = (uint)param_3;
  uVar1 = 0;
  if (((uVar2 < uVar3) && ((uVar3 < uVar4 || (uVar4 < uVar2)))) ||
     ((uVar3 < uVar2 && ((uVar3 < uVar4 && (uVar4 < uVar2)))))) {
    if ((uVar2 - uVar4 & 0xffff) < (uVar2 - uVar3 & 0xffff) >> 1) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0xffff;
    }
  }
  else {
    uVar3 = uVar3 - uVar2 & 0xffff;
    if (uVar3 == 0) {
      uVar2 = 0;
      uVar1 = 1;
    }
    else {
      uVar2 = ((uVar4 - uVar2) * 0xffff) / uVar3 & 0xffff;
    }
  }
  *param_4 = uVar2;
  return uVar1;
}




/* 0x0801052c */
undefined4 FUN_0801052c(param_1, param_2, param_3, param_4, param_5, param_6)
int param_1; uint param_2; uint param_3; int param_4; int param_5; int * param_6;
{
  int iVar1;
  uint uVar2;
  
  if (param_3 <= param_2) {
    return 1;
  }
  uVar2 = (uint)(param_4 * 100000) / (param_3 - param_2);
  iVar1 = (int)(uVar2 * param_1 + (param_5 * 100000 - uVar2 * param_3)) / 100;
  if (iVar1 < 0) {
    iVar1 = 0;
  }
  *param_6 = iVar1;
  return 0;
}




/* 0x08010572 */
undefined4 FUN_08010572(param_1, param_2, param_3, param_4)
int param_1; undefined1 * param_2; int param_3; undefined4 param_4;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_28;
  undefined1 local_24;
  undefined1 local_23 [3];
  undefined2 local_20;
  undefined2 uStack_1e;
  undefined4 uStack_1c;
  
  local_28 = *(undefined4 *)(param_3 + 4);
  local_23[2] = (undefined1)((uint)param_2 >> 0x18);
  _local_24 = CONCAT31(CONCAT21(CONCAT11(local_23[2],*(undefined1 *)(param_3 + 0xc)),param_2[1]),
                       *param_2);
  _local_20 = CONCAT22((short)((uint)param_3 >> 0x10),*(undefined2 *)(param_3 + 0xe));
  iVar1 = param_1 + 0x68;
  uStack_1c = param_4;
  iVar2 = FUN_0800fc00(iVar1,&local_28);
  if (iVar2 == 0) {
    if (*(int *)(param_3 + 0x10) == 1) {
      FUN_08006a30(&uStack_1c,
                   *(int *)(*(int *)(param_1 + 0x5c) + 0x48) + *(int *)(param_3 + 0x14) * 4,4);
      iVar2 = FUN_0800fd04(iVar1,&uStack_1c);
      if (iVar2 != 0) {
        return 0xffffffff;
      }
      uVar3 = 1;
    }
    else {
      uVar3 = 0;
    }
    iVar2 = FUN_0800fcd0(iVar1,uVar3);
    if ((iVar2 == 0) && (iVar1 = FUN_0800fbd0(iVar1), iVar1 == 0)) {
      return 0;
    }
  }
  return 0xffffffff;
}




/* 0x080105ec */
undefined4 FUN_080105ec(param_1, param_2, param_3, param_4)
int * param_1; byte param_2; undefined4 param_3; undefined4 param_4;
{
  undefined1 *puVar1;
  int iVar2;
  
  if (param_1 != (int *)0x0) {
    puVar1 = *(undefined1 **)(*param_1 + 0x5c);
    iVar2 = FUN_0800e57a(*(undefined4 *)(puVar1 + 4),*puVar1,
                         (*(uint *)(puVar1 + 0xc) & 0xff) << 8 | (uint)param_2,param_3,param_4);
    if (iVar2 == 0) {
      return 0;
    }
  }
  return 1;
}




/* 0x08010618 */
undefined4 FUN_08010618(param_1, param_2, param_3)
int param_1; undefined4 param_2; undefined4 * param_3;
{
  uint *puVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 *puVar5;
  
  puVar1 = DAT_0804d170;
  uVar4 = 0;
  *param_3 = 0;
  do {
    if (*puVar1 <= uVar4) {
      return 0xffffffff;
    }
    puVar5 = *(undefined4 **)(puVar1[1] + uVar4 * 4);
    for (uVar2 = 0; uVar2 < (uint)puVar5[1]; uVar2 = uVar2 + 1) {
      if (*(int *)(puVar5[2] + uVar2 * 4) == param_1) {
                    /* WARNING: Could not recover jumptable at 0x0801064e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar3 = ((code *)*puVar5)(param_2,param_1);
        return uVar3;
      }
    }
    uVar4 = uVar4 + 1;
  } while( true );
}




/* 0x08010668 */
undefined4 thunk_FUN_08010668(param_1, param_2)
int param_1; int * param_2;
{
  uint uVar1;
  int iStack_18;
  
  uVar1 = 0;
  iStack_18 = 0;
  FUN_0800b5c4(&iStack_18);
  if (iStack_18 != 0) {
    for (; uVar1 < *(uint *)(iStack_18 + 0x14); uVar1 = uVar1 + 1) {
      if (*(int *)(iStack_18 + uVar1 * 8 + 0x18) == param_1) {
        *param_2 = iStack_18;
        param_2[1] = *(int *)(iStack_18 + uVar1 * 8 + 0x1c);
        return 0;
      }
    }
  }
  *param_2 = 0;
  param_2[1] = 0;
  return 0xffffffff;
}




/* 0x08010668 */
undefined4 FUN_08010668(param_1, param_2)
int param_1; int * param_2;
{
  uint uVar1;
  int local_18;
  
  uVar1 = 0;
  local_18 = 0;
  FUN_0800b5c4(&local_18);
  if (local_18 != 0) {
    for (; uVar1 < *(uint *)(local_18 + 0x14); uVar1 = uVar1 + 1) {
      if (*(int *)(local_18 + uVar1 * 8 + 0x18) == param_1) {
        *param_2 = local_18;
        param_2[1] = *(int *)(local_18 + uVar1 * 8 + 0x1c);
        return 0;
      }
    }
  }
  *param_2 = 0;
  param_2[1] = 0;
  return 0xffffffff;
}




/* 0x080106aa */
undefined8 thunk_FUN_080106aa(param_1, param_2, param_3, param_4)
int * param_1; int param_2; int param_3; uint * param_4;
{
  bool bVar1;
  bool bVar2;
  byte bVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  int iVar9;
  int iStack_30;
  int iStack_2c;
  uint *puStack_28;
  
  bVar1 = false;
  iStack_30 = 0;
  iVar9 = *param_1;
  pcVar7 = (char *)(iVar9 + param_1[1]);
  if ((iVar9 == 0) || (pcVar7 == (char *)0x0)) {
LAB_08010768:
    uVar5 = 0xffffffff;
  }
  else {
    iStack_2c = param_3;
    puStack_28 = param_4;
    iVar4 = FUN_08010668(0,&iStack_2c);
    if (iVar4 != 0) {
      bVar1 = true;
    }
LAB_080106d2:
    do {
      while( true ) {
        FUN_08027bf8(param_4,4,pcVar7);
        if (*param_4 != 0xff00ff00) break;
        if (bVar1) goto LAB_08010768;
        bVar1 = true;
        pcVar7 = (char *)(*param_1 + *(int *)(iVar9 + 0x1c));
      }
      FUN_08027bf8(&iStack_30,4,pcVar7 + 4);
      pcVar8 = pcVar7 + 8;
      bVar2 = false;
      if (param_2 == 0) {
        if (iStack_30 == param_3) goto LAB_08010724;
      }
      else {
        iVar4 = FUN_08006d64(iStack_30 + iVar9 + *(int *)(iVar9 + 4));
        if (iVar4 == 0) {
LAB_08010724:
          bVar2 = true;
        }
      }
      if (!bVar2) {
        uVar6 = *param_4 & 0x3fffff;
        if (uVar6 == 0x12) goto LAB_0801076e;
        if (uVar6 < 0x13) {
          if (uVar6 == 2) {
LAB_0801076e:
            pcVar8 = pcVar7 + 0xc;
          }
          else {
            if (uVar6 != 8) {
              if (uVar6 != 0x11) goto LAB_08010760;
              goto LAB_0801076e;
            }
            bVar3 = *pcVar8 + 2;
            pcVar8 = pcVar8 + bVar3;
            if ((bVar3 & 3) != 0) {
              pcVar8 = pcVar8 + (4 - (bVar3 & 3));
            }
          }
          iVar4 = 0;
        }
        else {
          if ((uVar6 == 0x14) || (uVar6 == 0x18)) goto LAB_0801076e;
LAB_08010760:
          iVar4 = -1;
        }
        pcVar7 = pcVar8;
        if (iVar4 == -1) goto LAB_08010768;
        goto LAB_080106d2;
      }
      pcVar7 = pcVar8;
    } while (false);
    uVar5 = FUN_08010808(param_4,iVar9,pcVar8);
  }
  return CONCAT44(iStack_30,uVar5);
}




/* 0x080106aa */
undefined8 FUN_080106aa(param_1, param_2, param_3, param_4)
int * param_1; int param_2; int param_3; uint * param_4;
{
  bool bVar1;
  bool bVar2;
  byte bVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  int iVar9;
  int local_30;
  int iStack_2c;
  uint *puStack_28;
  
  bVar1 = false;
  local_30 = 0;
  iVar9 = *param_1;
  pcVar7 = (char *)(iVar9 + param_1[1]);
  if ((iVar9 == 0) || (pcVar7 == (char *)0x0)) {
LAB_08010768:
    uVar5 = 0xffffffff;
  }
  else {
    iStack_2c = param_3;
    puStack_28 = param_4;
    iVar4 = FUN_08010668(0,&iStack_2c);
    if (iVar4 != 0) {
      bVar1 = true;
    }
LAB_080106d2:
    do {
      while( true ) {
        FUN_08027bf8(param_4,4,pcVar7);
        if (*param_4 != 0xff00ff00) break;
        if (bVar1) goto LAB_08010768;
        bVar1 = true;
        pcVar7 = (char *)(*param_1 + *(int *)(iVar9 + 0x1c));
      }
      FUN_08027bf8(&local_30,4,pcVar7 + 4);
      pcVar8 = pcVar7 + 8;
      bVar2 = false;
      if (param_2 == 0) {
        if (local_30 == param_3) goto LAB_08010724;
      }
      else {
        iVar4 = FUN_08006d64(local_30 + iVar9 + *(int *)(iVar9 + 4));
        if (iVar4 == 0) {
LAB_08010724:
          bVar2 = true;
        }
      }
      if (!bVar2) {
        uVar6 = *param_4 & 0x3fffff;
        if (uVar6 == 0x12) goto LAB_0801076e;
        if (uVar6 < 0x13) {
          if (uVar6 == 2) {
LAB_0801076e:
            pcVar8 = pcVar7 + 0xc;
          }
          else {
            if (uVar6 != 8) {
              if (uVar6 != 0x11) goto LAB_08010760;
              goto LAB_0801076e;
            }
            bVar3 = *pcVar8 + 2;
            pcVar8 = pcVar8 + bVar3;
            if ((bVar3 & 3) != 0) {
              pcVar8 = pcVar8 + (4 - (bVar3 & 3));
            }
          }
          iVar4 = 0;
        }
        else {
          if ((uVar6 == 0x14) || (uVar6 == 0x18)) goto LAB_0801076e;
LAB_08010760:
          iVar4 = -1;
        }
        pcVar7 = pcVar8;
        if (iVar4 == -1) goto LAB_08010768;
        goto LAB_080106d2;
      }
      pcVar7 = pcVar8;
    } while (false);
    uVar5 = FUN_08010808(param_4,iVar9,pcVar8);
  }
  return CONCAT44(local_30,uVar5);
}




/* 0x08010790 */
int * FUN_08010790(param_1, param_2)
int param_1; uint param_2;
{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  
  uVar5 = 0x1000;
  piVar4 = DAT_0804e268;
  if (DAT_0804e268 != (int *)0x0) {
    while ((*piVar4 != 0 && (uVar5 != 0))) {
      if (param_1 != 0) {
        uVar1 = FUN_08006906(param_1);
        if (uVar1 < 0xc) {
          uVar2 = FUN_08006906(param_1);
        }
        else {
          uVar2 = 0xb;
        }
        iVar3 = FUN_08006898(piVar4 + 1,param_1,uVar2);
        if (iVar3 == 0) {
          return piVar4;
        }
      }
      uVar5 = uVar5 - *piVar4;
      piVar4 = (int *)((int)piVar4 + *piVar4);
    }
    if ((param_1 == 0) && (param_2 <= uVar5)) {
      return piVar4;
    }
  }
  return (int *)0x0;
}




/* 0x080107e8 */
void FUN_080107e8(param_1, param_2, param_3)
undefined4 * param_1; undefined4 param_2; undefined4 param_3;
{
  *param_1 = param_2;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  FUN_080382c2(param_1 + 1,param_3,0xc);
  param_1[4] = 0;
  param_1[7] = 0;
  return;
}




/* 0x08010808 */
undefined4 FUN_08010808(param_1, param_2, param_3, param_4)
uint * param_1; int param_2; byte * param_3; int param_4;
{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int local_20;
  
  uVar2 = *param_1 & 0x3fffff;
  local_20 = param_4;
  if (uVar2 == 0x12) {
    iVar3 = FUN_0800b5d0();
    local_20 = 0;
    if (iVar3 != 0) {
      FUN_08027bf8(&local_20,4,param_3);
      uVar2 = *(uint *)(iVar3 + local_20 * 4);
      *param_1 = 0x12;
      param_1[1] = 4;
      param_1[2] = uVar2;
    }
  }
  else if (uVar2 < 0x13) {
    if (uVar2 == 2) {
      FUN_08027bf8(param_1 + 2,4);
      *param_1 = 2;
      param_1[1] = 4;
    }
    else if (uVar2 == 8) {
      bVar1 = *param_3;
      *param_1 = 0x11;
      param_1[1] = bVar1 + 1;
      param_1[2] = (uint)(param_3 + 1);
    }
    else {
      if (uVar2 != 0x11) {
        return 0xffffffff;
      }
      local_20 = 0;
      FUN_08027bf8(&local_20,4);
      param_1[2] = *(int *)(param_2 + 8) + local_20 + param_2;
      uVar2 = FUN_08006906();
      param_1[1] = uVar2;
      *param_1 = 0x10;
    }
  }
  else if (uVar2 == 0x14) {
    local_20 = 0;
    FUN_08027bf8(&local_20,4);
    uVar2 = local_20 + 4 + *(int *)(param_2 + 0x10) + param_2;
    param_1[2] = uVar2;
    iVar3 = *(int *)(uVar2 - 4);
    *param_1 = 0x12;
    param_1[1] = iVar3 + 1;
  }
  else {
    if (uVar2 != 0x18) {
      return 0xffffffff;
    }
    local_20 = 0;
    FUN_08027bf8(&local_20,4);
    uVar2 = local_20 + 1 + *(int *)(param_2 + 0xc) + param_2;
    param_1[2] = uVar2;
    bVar1 = *(byte *)(uVar2 - 1);
    *param_1 = 0x11;
    param_1[1] = bVar1 + 1;
  }
  return 0;
}




/* 0x080108fe */
uint FUN_080108fe(param_1, param_2)
int param_1; uint param_2;
{
  uint uVar1;
  
  uVar1 = 0;
  if (param_1 != 0 || (param_2 & 0xfffff) != 0) {
    uVar1 = 4;
  }
  if ((param_2 << 1) >> 0x15 != 0) {
    uVar1 = uVar1 | 1;
  }
  if ((param_2 << 1) >> 0x15 == 0x7ff) {
    uVar1 = uVar1 | 2;
  }
  if (uVar1 == 1) {
    uVar1 = 5;
  }
  return uVar1;
}




/* 0x08010960 */
undefined4 FUN_08010960()
{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08010962 */
void FUN_08010962(param_1, param_2, param_3, param_4, param_5)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4; undefined4 param_5;
{
  *(undefined1 *)(param_1 + 0x438) = 1;
  FUN_08006a30(param_1 + 0x400,param_4,0x20);
  thunk_FUN_08038cc0(param_1,param_2,0x100);
  thunk_FUN_08038cc0(param_1 + 0x200,param_3,0x100);
  FUN_08006bdc(param_1 + 0x420,param_5,0x18);
  return;
}




/* 0x080109ac */
int FUN_080109ac(param_1, param_2)
undefined4 param_1; int param_2;
{
  int iVar1;
  
  *(byte *)(param_2 + 8) = *(byte *)(param_2 + 8) | 0x40;
  iVar1 = FUN_08011896(param_1);
  if ((iVar1 == 0) && (*(int *)(param_2 + 0xe2c) != 0)) {
    iVar1 = FUN_080130f8(param_1,param_2,0);
  }
  else {
    FUN_080130f8(param_1,param_2,1);
  }
  return iVar1;
}




/* 0x080109e8 */
undefined4 FUN_080109e8(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = FUN_08025618(0);
  uVar2 = FUN_08010a18(param_1,param_2,param_3,param_4,uVar1);
  FUN_08025760(uVar1);
  return uVar2;
}




/* 0x08010a18 */
int FUN_08010a18(param_1, param_2, param_3, param_4, param_5)
int param_1; undefined4 * param_2; int * param_3; int * param_4; int param_5;
{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 extraout_r2;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  bool bVar10;
  char local_74 [8];
  char local_6c [4];
  undefined1 local_68;
  undefined1 auStack_66 [2];
  undefined1 auStack_64 [2];
  undefined1 auStack_62 [14];
  int local_54;
  undefined4 *local_50;
  undefined4 local_4c;
  int local_48;
  char local_44 [8];
  char local_3c [4];
  int local_38;
  int iStack_34;
  undefined4 *local_30;
  int *local_2c;
  int *local_28;
  
  local_48 = DAT_0804cd58;
  local_38 = DAT_0804cd58;
  iVar7 = 0;
  local_4c = 0;
  iVar8 = -1;
  uVar5 = 0;
  iStack_34 = param_1;
  local_30 = param_2;
  local_2c = param_3;
  local_28 = param_4;
  if (*(short *)(param_2 + 0x81) != 0) {
    local_50 = param_2 + 0x81;
    iVar2 = FUN_080274a0();
    if ((iVar2 == 0) && (iVar2 = FUN_080274ba(local_50), iVar2 == 0)) {
      uVar3 = FUN_080115ac(local_50,param_5,local_44,local_3c,extraout_r2);
      iVar2 = 2;
      if ((*(char *)(param_5 + 0x20c) != '\x03') &&
         ((DAT_0804e29c != '\0' || (*(char *)(param_5 + 0x20c) != '\0')))) {
        iVar9 = *(byte *)(param_5 + 0x20a) + 1;
        if ((*local_2c == 0) && (*(int *)(param_1 + 0x882c) == 3)) {
          local_4c = 1;
        }
        local_54 = FUN_080127a0(param_1,*local_30);
        if (local_54 != 0) {
LAB_08010ab0:
          do {
            iVar6 = FUN_080129f0(param_1,local_74,local_54);
            if (iVar6 == 9) {
LAB_08010b74:
              if (iVar9 <= (int)uVar5) goto LAB_08010bce;
              iVar6 = FUN_08010f40(param_1,local_54,local_74,local_4c);
              if (iVar6 != 0) goto LAB_08010b88;
              iVar6 = FUN_08012bdc(param_1,local_54,iVar7,0);
              bVar10 = iVar6 == 0;
              while( true ) {
                if (!bVar10) goto LAB_08010ac2;
                FUN_080129f0(param_1,local_74,local_54);
                if (iVar8 < 0) {
                  iVar8 = iVar7;
                }
LAB_08010bce:
                iVar6 = FUN_08012bdc(param_1,local_54,iVar8,0);
                bVar10 = iVar6 == 0;
                if (!bVar10) break;
                if (*(char *)(param_5 + 0x20c) == '\0') {
                  uVar1 = FUN_080221c8(local_44,local_3c);
                  *(undefined1 *)(param_5 + 0x20b) = uVar1;
                  for (uVar5 = (uint)*(byte *)(param_5 + 0x20a); 0 < (int)uVar5; uVar5 = uVar5 - 1)
                  {
                    FUN_0801d964(local_74,uVar5,param_5,local_30);
                    iVar6 = FUN_0801317a(param_1,local_74,local_54);
                    bVar10 = iVar6 == 0;
                    if (!bVar10) goto LAB_08010b4c;
                  }
                }
                FUN_08012630(local_74,local_44,local_3c);
                local_68 = (undefined1)uVar3;
                if ((*(int *)(param_1 + 0x882c) == 3) && (*(char *)(param_5 + 0x20c) == '\x01')) {
                  uVar5 = FUN_080219a8();
                  uVar4 = FUN_08021380();
                  FUN_08012d3c(auStack_64,uVar4);
                  uVar4 = FUN_080213c0(uVar5);
                  FUN_08012d3c(auStack_66,uVar4);
                  uVar4 = FUN_08021380(uVar5);
                  FUN_08012d3c(auStack_62,uVar4);
                }
                iVar6 = FUN_0801317a(param_1,local_74,local_54);
                bVar10 = false;
                if (iVar6 == 0) {
                  if (local_28 != (int *)0x0) {
                    iVar8 = FUN_08011218(local_54);
                    if ((iVar8 == 0) || (*(uint *)(iVar8 + 0x14) < 0x20)) {
                      iVar6 = 8;
                      goto LAB_08010ac2;
                    }
                    *(undefined4 *)(param_1 + 0x8820) = *(undefined4 *)(iVar8 + 0xe3c);
                    FUN_08006a30(param_1 + 0x8620,
                                 param_1 + (*(int *)(iVar8 + 0xe3c) - *(int *)(param_1 + 0x81dc)) *
                                           0x200 + 0x41dc,0x200);
                    *local_28 = param_1 + 0x8600 + *(int *)(iVar8 + 0x14);
                    *local_2c = *(int *)(iVar8 + 0xe30);
                    local_2c[5] = (*(uint *)(iVar8 + 0x14) >> 5) - 1;
                    local_2c[3] = *(int *)(iVar8 + 0xe3c);
                    local_2c[4] = *(int *)(iVar8 + 0xe40);
                  }
                  iVar6 = 0;
                  goto LAB_08010ac2;
                }
              }
LAB_08010b4c:
              if (!bVar10) goto LAB_08010ac2;
              iVar7 = 0;
              goto LAB_08010ab0;
            }
            if (iVar6 != 0) goto LAB_08010ac2;
            if (local_74[0] == '\0') {
              if ((int)uVar5 < iVar9) {
                uVar5 = 1;
                while ((iVar8 = iVar7, (int)uVar5 < iVar9 &&
                       (iVar6 = FUN_080129f0(param_1,local_74,local_54), iVar6 != 9))) {
                  uVar5 = uVar5 + 1;
                }
              }
              goto LAB_08010b74;
            }
            if (local_74[0] == -0x1b) {
              if ((int)uVar5 < iVar9) {
                if (iVar8 == -1) {
                  uVar5 = 0;
                  iVar8 = iVar7;
                }
                uVar5 = uVar5 + 1;
              }
              iVar7 = iVar7 + 1;
            }
            else {
              if ((int)uVar5 < iVar9) {
                uVar5 = 0;
                iVar8 = -1;
              }
              iVar7 = iVar7 + 1;
              if (local_6c[3] != '\x0f') {
                iVar6 = 0;
                do {
                  if (local_6c[iVar6] != local_3c[iVar6]) goto LAB_08010ab0;
                  iVar6 = iVar6 + 1;
                } while (iVar6 < 3);
                if (true) {
                  iVar6 = 0;
                  do {
                    if (local_74[iVar6] != local_44[iVar6]) goto LAB_08010ab0;
                    iVar6 = iVar6 + 1;
                  } while (iVar6 < 8);
                  if (true) {
                    uVar3 = FUN_080115ac(local_50,param_5,local_44,local_3c,iVar2);
                    iVar2 = iVar2 + 1;
                    iVar6 = FUN_08012bdc(param_1,local_54,0,0,uVar3);
                    bVar10 = iVar6 == 0;
                    goto LAB_08010b4c;
                  }
                }
              }
            }
          } while( true );
        }
        iVar6 = 3;
        goto LAB_08010b88;
      }
    }
  }
  iVar6 = 4;
  goto LAB_08010b88;
LAB_08010ac2:
  iVar6 = FUN_08011458(param_1,local_54,iVar6);
LAB_08010b88:
  if (local_38 != local_48) {
    FUN_08010960();
  }
  return iVar6;
}




/* 0x08010d00 */
void FUN_08010d00(param_1, param_2, param_3)
byte * param_1; int param_2; undefined4 param_3;
{
  byte *pbVar1;
  char cVar2;
  uint uVar3;
  ushort *puVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  byte bVar8;
  
  cVar2 = DAT_0804e29c;
  bVar8 = 0;
  if ((*param_1 == 0) || (*param_1 == 0xe5)) {
    *(undefined1 *)(param_2 + 0x20c) = 3;
    return;
  }
  if (DAT_0804e29c == '\0') {
    if (param_1[0xb] == 0xf) goto LAB_08010e30;
  }
  else if (param_1[0xb] == 0xf) {
    iVar6 = FUN_08011f68(param_1 + 0x1a);
    if (iVar6 == 0) {
      bVar8 = *param_1;
      uVar3 = (uint)bVar8;
      uVar5 = (uVar3 & 0x3f) - 1;
      if (uVar5 < 0x14) {
        iVar6 = uVar5 * 0xd;
        if ((int)(uVar3 << 0x19) < 0) {
          *(byte *)(param_2 + 0x20a) = bVar8;
          *(undefined1 *)(param_2 + 0x20c) = 2;
          *(undefined2 *)(param_2 + uVar5 * 0x1a + 0x1a) = 0;
          *(byte *)(param_2 + 0x20b) = param_1[0xd];
          *(undefined4 *)(param_2 + 0x210) = param_3;
          *(undefined4 *)(param_2 + 0x214) = param_3;
        }
        else {
          if (((*(byte *)(param_2 + 0x20b) != param_1[0xd]) ||
              (*(char *)(param_2 + 0x20c) != '\x02')) ||
             (uVar3 != (*(byte *)(param_2 + 0x20a) & 0x3f) - 1)) goto LAB_08010e30;
          *(byte *)(param_2 + 0x20a) = bVar8;
        }
        *(ushort *)(param_2 + uVar5 * 0x1a) = (ushort)param_1[2] << 8;
        puVar4 = (ushort *)(param_2 + uVar5 * 0x1a);
        *puVar4 = *puVar4 | (ushort)param_1[1];
        *(ushort *)(param_2 + (iVar6 + 1) * 2) = (ushort)param_1[4] << 8;
        puVar4 = (ushort *)(param_2 + (iVar6 + 1) * 2);
        *puVar4 = *puVar4 | (ushort)param_1[3];
        *(ushort *)(param_2 + (iVar6 + 2) * 2) = (ushort)param_1[6] << 8;
        puVar4 = (ushort *)(param_2 + (iVar6 + 2) * 2);
        *puVar4 = *puVar4 | (ushort)param_1[5];
        *(ushort *)(param_2 + (iVar6 + 3) * 2) = (ushort)param_1[8] << 8;
        puVar4 = (ushort *)(param_2 + (iVar6 + 3) * 2);
        *puVar4 = *puVar4 | (ushort)param_1[7];
        *(ushort *)(param_2 + (iVar6 + 4) * 2) = (ushort)param_1[10] << 8;
        puVar4 = (ushort *)(param_2 + (iVar6 + 4) * 2);
        *puVar4 = *puVar4 | (ushort)param_1[9];
        *(ushort *)(param_2 + (iVar6 + 5) * 2) = (ushort)param_1[0xf] << 8;
        puVar4 = (ushort *)(param_2 + (iVar6 + 5) * 2);
        *puVar4 = *puVar4 | (ushort)param_1[0xe];
        *(ushort *)(param_2 + (iVar6 + 6) * 2) = (ushort)param_1[0x11] << 8;
        puVar4 = (ushort *)(param_2 + (iVar6 + 6) * 2);
        *puVar4 = *puVar4 | (ushort)param_1[0x10];
        *(ushort *)(param_2 + (iVar6 + 7) * 2) = (ushort)param_1[0x13] << 8;
        puVar4 = (ushort *)(param_2 + (iVar6 + 7) * 2);
        *puVar4 = *puVar4 | (ushort)param_1[0x12];
        *(ushort *)(param_2 + (iVar6 + 8) * 2) = (ushort)param_1[0x15] << 8;
        puVar4 = (ushort *)(param_2 + (iVar6 + 8) * 2);
        *puVar4 = *puVar4 | (ushort)param_1[0x14];
        *(ushort *)(param_2 + (iVar6 + 9) * 2) = (ushort)param_1[0x17] << 8;
        puVar4 = (ushort *)(param_2 + (iVar6 + 9) * 2);
        *puVar4 = *puVar4 | (ushort)param_1[0x16];
        *(ushort *)(param_2 + (iVar6 + 10) * 2) = (ushort)param_1[0x19] << 8;
        puVar4 = (ushort *)(param_2 + (iVar6 + 10) * 2);
        *puVar4 = *puVar4 | (ushort)param_1[0x18];
        *(ushort *)(param_2 + (iVar6 + 0xb) * 2) = (ushort)param_1[0x1d] << 8;
        puVar4 = (ushort *)(param_2 + (iVar6 + 0xb) * 2);
        *puVar4 = *puVar4 | (ushort)param_1[0x1c];
        *(ushort *)(param_2 + (iVar6 + 0xc) * 2) = (ushort)param_1[0x1f] << 8;
        puVar4 = (ushort *)(param_2 + (iVar6 + 0xc) * 2);
        *puVar4 = *puVar4 | (ushort)param_1[0x1e];
        return;
      }
    }
LAB_08010e30:
    *(undefined1 *)(param_2 + 0x20c) = 3;
    return;
  }
  if ((*(char *)(param_2 + 0x20c) == '\x02') && ((*(byte *)(param_2 + 0x20a) & 0x3f) == 1)) {
    uVar3 = 0;
    iVar6 = 0;
    do {
      pbVar1 = param_1 + iVar6;
      iVar6 = iVar6 + 1;
      uVar3 = (uVar3 << 7 | uVar3 >> 1) + (uint)*pbVar1 & 0xff;
    } while (iVar6 < 8);
    iVar6 = 0;
    do {
      iVar7 = iVar6 + 1;
      uVar3 = (uVar3 << 7 | uVar3 >> 1) + (uint)param_1[iVar6 + 8] & 0xff;
      iVar6 = iVar7;
    } while (iVar7 < 3);
    if (*(byte *)(param_2 + 0x20b) == uVar3) {
      *(undefined1 *)(param_2 + 0x20c) = 0;
      *(undefined4 *)(param_2 + 0x214) = param_3;
      return;
    }
  }
  *(undefined4 *)(param_2 + 0x214) = param_3;
  *(undefined4 *)(param_2 + 0x210) = param_3;
  if (cVar2 != '\0') {
    bVar8 = param_1[0xc];
  }
  FUN_0801242c(param_2,param_1,param_1 + 8,bVar8);
  *(undefined1 *)(param_2 + 0x20c) = 1;
  return;
}




/* 0x08010f40 */
undefined4 FUN_08010f40(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; uint param_4;
{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  bool bVar4;
  uint local_20;
  
  local_20 = param_4;
  iVar1 = FUN_08011218(param_2);
  if (((iVar1 != 0) && (*(uint *)(iVar1 + 0xe30) != 0)) && (*(uint *)(iVar1 + 0xe30) < 0xffffff0)) {
    iVar3 = FUN_08010fe0(param_1,&local_20);
    if (iVar3 != 0) goto LAB_08010faa;
    if (local_20 < 0xffffff0) {
      if (param_4 == 0) {
        uVar2 = 0xffffff8;
      }
      else {
        uVar2 = 0xfffffff;
      }
      iVar3 = FUN_08012d54(param_1,local_20,uVar2);
      if (((iVar3 == 0) &&
          (iVar3 = FUN_08012d54(param_1,*(undefined4 *)(iVar1 + 0xe30),local_20), iVar3 == 0)) &&
         (iVar3 = FUN_08013228(param_1), iVar3 == 0)) {
        FUN_08006cd0(param_3,0x20);
        iVar1 = (uint)*(byte *)(param_1 + 0x5a) << 4;
        do {
          bVar4 = iVar1 == 0;
          iVar1 = iVar1 + -1;
          if (bVar4) {
            return 0;
          }
          iVar3 = FUN_0801317a(param_1,param_3,param_2);
        } while (iVar3 == 0);
      }
      goto LAB_08010faa;
    }
  }
  iVar3 = 7;
LAB_08010faa:
  uVar2 = FUN_08011458(param_1,param_2,iVar3);
  return uVar2;
}




/* 0x08010fe0 */
int FUN_08010fe0(param_1, param_2)
int param_1; uint * param_2;
{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  int extraout_r3;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int local_34 [2];
  int iStack_2c;
  uint *local_28;
  
  iStack_2c = param_1;
  local_28 = param_2;
  uVar1 = FUN_08012500();
  puVar2 = (uint *)(param_1 + 0x8824);
  uVar5 = *puVar2;
  if (*(int *)(param_1 + 0x882c) == 3) {
    uVar6 = *(uint *)(param_1 + 0xb4);
    uVar7 = uVar5 >> 7;
    uVar5 = uVar5 + uVar7 * -0x80;
    for (uVar8 = 0; uVar8 < uVar6; uVar8 = uVar8 + 1) {
      if (uVar6 <= uVar7) {
        uVar7 = 0;
      }
      iVar4 = FUN_08012350(param_1,uVar7);
      if (iVar4 != 0) {
        return iVar4;
      }
      iVar4 = *(int *)(param_1 + 0x41d0) + uVar5 * 4;
      for (; uVar5 < 0x80; uVar5 = uVar5 + 1) {
        iVar4 = FUN_08011f72(iVar4);
        if ((iVar4 == 0) && (uVar3 = uVar5 + uVar7 * 0x80, uVar3 < uVar1 + 2)) {
          *puVar2 = uVar3 + 1;
          if (local_28 != (uint *)0x0) {
            *local_28 = uVar3;
          }
          goto LAB_08011070;
        }
        iVar4 = extraout_r3 + 4;
      }
      uVar5 = 0;
      uVar7 = uVar7 + 1;
    }
  }
  else {
    for (uVar6 = 0; uVar6 < uVar1; uVar6 = uVar6 + 1) {
      if (uVar1 + 2 <= uVar5) {
        uVar5 = 2;
      }
      iVar4 = FUN_08012088(param_1,uVar5,local_34);
      if (iVar4 != 0) {
        return iVar4;
      }
      if (local_34[0] == 0) {
        *puVar2 = uVar5 + 1;
        if (local_28 != (uint *)0x0) {
          *local_28 = uVar5;
        }
LAB_08011070:
        if (*(char *)(param_1 + 0x883c) != '\0') {
          *(int *)(param_1 + 0x8830) = *(int *)(param_1 + 0x8830) + -1;
          *(int *)(param_1 + 0x8834) = *(int *)(param_1 + 0x8834) + 1;
        }
        return 0;
      }
      uVar5 = uVar5 + 1;
    }
  }
  return 7;
}




/* 0x080110dc */
int FUN_080110dc(param_1, param_2, param_3, param_4)
undefined4 param_1; int param_2; uint param_3; uint param_4;
{
  int iVar1;
  uint uVar2;
  uint local_20;
  uint local_1c;
  
  if (*(uint *)(param_2 + 0xe40) <= *(uint *)(param_2 + 0xe3c)) {
    local_20 = param_3;
    local_1c = param_4;
    if (*(int *)(param_2 + 0xe2c) == 0) {
      iVar1 = FUN_08010fe0(param_1,(undefined4 *)(param_2 + 0xe2c));
      if (iVar1 != 0) {
        return iVar1;
      }
      FUN_080114a4(param_1,*(undefined4 *)(param_2 + 0xe2c),param_2 + 0xe30);
      iVar1 = FUN_08012d54(param_1,*(undefined4 *)(param_2 + 0xe2c),0xffffff8);
      if (iVar1 != 0) {
        return iVar1;
      }
    }
    else {
      iVar1 = FUN_08012088(param_1,*(undefined4 *)(param_2 + 0xe30),&local_1c);
      if (iVar1 != 0) {
        return iVar1;
      }
      uVar2 = local_1c;
      if (0xfffffef < local_1c) {
        iVar1 = FUN_08010fe0(param_1,&local_20);
        if (iVar1 != 0) {
          return iVar1;
        }
        iVar1 = FUN_08012d54(param_1,local_20,0xffffff8);
        if (iVar1 != 0) {
          return iVar1;
        }
        iVar1 = FUN_08012d54(param_1,*(undefined4 *)(param_2 + 0xe30),local_20);
        uVar2 = local_20;
        if (iVar1 != 0) {
          return iVar1;
        }
      }
      FUN_080114a4(param_1,uVar2,param_2 + 0xe30);
    }
  }
  return 0;
}




/* 0x08011180 */
void FUN_08011180(param_1)
int param_1;
{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  *(undefined4 *)(param_1 + 0x882c) = 0;
  *(uint *)(param_1 + 0xb0) = (uint)*(ushort *)(param_1 + 0x5c);
  iVar1 = (uint)*(ushort *)(param_1 + 0x5c) + *(int *)(param_1 + 0x6c);
  *(int *)(param_1 + 0xb0) = iVar1;
  uVar3 = (uint)*(ushort *)(param_1 + 0x66);
  if (uVar3 == 0) {
    *(int *)(param_1 + 0xb4) = *(int *)(param_1 + 0x74);
    *(int *)(param_1 + 0xc0) = iVar1;
    *(uint *)(param_1 + 0xc0) = *(int *)(param_1 + 0x74) * (uint)*(byte *)(param_1 + 0x5e) + iVar1;
    *(undefined4 *)(param_1 + 0xc4) = 0;
    uVar2 = FUN_08013510(param_1,*(undefined4 *)(param_1 + 0x7c));
    *(undefined4 *)(param_1 + 0xb8) = uVar2;
    *(uint *)(param_1 + 0xbc) = (uint)*(byte *)(param_1 + 0x5a);
  }
  else {
    *(uint *)(param_1 + 0xb4) = uVar3;
    *(int *)(param_1 + 0xb8) = iVar1;
    iVar1 = uVar3 * *(byte *)(param_1 + 0x5e) + iVar1;
    *(int *)(param_1 + 0xb8) = iVar1;
    uVar3 = ((uint)*(ushort *)(param_1 + 0x60) << 5) >> 9;
    *(uint *)(param_1 + 0xbc) = uVar3;
    *(uint *)(param_1 + 0xc0) = iVar1 + uVar3;
    *(undefined4 *)(param_1 + 0xc4) = 0;
  }
  uVar3 = FUN_08012500(param_1);
  if (uVar3 < 0xff0) {
    uVar2 = 1;
  }
  else {
    uVar3 = FUN_08012500(param_1);
    if (uVar3 < 0xfff0) {
      uVar2 = 2;
    }
    else {
      uVar2 = 3;
    }
  }
  *(undefined4 *)(param_1 + 0x882c) = uVar2;
  return;
}




/* 0x08011218 */
uint * FUN_08011218(param_1)
uint param_1;
{
  uint *puVar1;
  
  if ((7 < (param_1 & 0xf)) ||
     (puVar1 = (uint *)(&DAT_87c11f08 + (param_1 & 0xf) * 0xeb0), *puVar1 != param_1)) {
    puVar1 = (uint *)0x0;
  }
  return puVar1;
}




/* 0x08011244 */
undefined4 FUN_08011244(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (((((&DAT_87c11f10)[iVar1 * 0xeb0] != '\0') && ((&DAT_87c11f14)[iVar1 * 0x3ac] == param_1))
        && ((&DAT_87c12d64)[iVar1 * 0x3ac] == *(int *)(param_2 + 0x14))) &&
       ((&DAT_87c12d5c)[iVar1 * 0x3ac] == *(int *)(param_2 + 0xc))) {
      if ((&DAT_87c11f10)[iVar1 * 0xeb0] != '\x01') {
        return 0xc;
      }
      *(uint *)(param_3 + 0xe60) = *(uint *)(param_3 + 0xe60) | 1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 8);
  return 0;
}




/* 0x080112a8 */
undefined4 FUN_080112a8(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  
  iVar1 = 0;
  while (((((&DAT_87c11f10)[iVar1 * 0xeb0] == '\0' || ((&DAT_87c11f14)[iVar1 * 0x3ac] != param_1))
          || ((&DAT_87c12d64)[iVar1 * 0x3ac] != *(int *)(param_2 + 0x14))) ||
         ((&DAT_87c12d5c)[iVar1 * 0x3ac] != *(int *)(param_2 + 0xc)))) {
    iVar1 = iVar1 + 1;
    if (7 < iVar1) {
      return 0;
    }
  }
  return 0xc;
}




/* 0x080112f0 */
undefined4 FUN_080112f0(param_1, param_2)
ushort * param_1; int param_2;
{
  uint uVar1;
  
  if ((param_1 != (ushort *)0x0) && (*param_1 != 0xe5)) {
    do {
      uVar1 = (uint)*param_1;
      if (uVar1 == 0) {
        return 0;
      }
    } while (((0x1e < uVar1 - 1) && ((param_2 == 0 || ((uVar1 != 0x3f && (uVar1 != 0x2a)))))) &&
            ((uVar1 != 0x7c &&
             ((((uVar1 != 0x3c && (uVar1 != 0x3e)) && (uVar1 != 0x2f)) &&
              (((uVar1 != 0x5c && (uVar1 != 0x3a)) && (param_1 = param_1 + 1, uVar1 != 0x22))))))));
  }
  return 1;
}




/* 0x08011334 */
undefined4 FUN_08011334(param_1, param_2, param_3, param_4)
undefined4 param_1; int param_2; int param_3; undefined4 * param_4;
{
  int iVar1;
  char cVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  
  iVar5 = 0;
  *param_4 = 0;
  do {
    iVar1 = iVar5 * 0xeb0;
    puVar4 = &DAT_87c11f08 + iVar1;
    cVar2 = (&DAT_87c11f10)[iVar1];
    if ((((cVar2 != '\0') && ((&DAT_87c11f14)[iVar5 * 0x3ac] == param_2)) &&
        ((&DAT_87c12d64)[iVar5 * 0x3ac] == *(int *)(param_3 + 0x14))) &&
       (((&DAT_87c12d5c)[iVar5 * 0x3ac] == *(int *)(param_3 + 0xc) && (cVar2 != '\x01')))) {
      if ((cVar2 != '\x03') && (cVar2 != '\x06')) {
        return 0xc;
      }
      if (((&DAT_87c12d68)[iVar5 * 0x3ac] & 1) == 0) {
        (&DAT_87c12d68)[iVar5 * 0x3ac] = (&DAT_87c12d68)[iVar5 * 0x3ac] | 1;
        iVar3 = FUN_080117ea(param_1,puVar4,0);
        if (iVar3 != 0) {
          FUN_080130f8(param_1,puVar4,1);
          (&DAT_87c11f10)[iVar1] = (&DAT_87c11f10)[iVar1] | 0x40;
          return 0;
        }
      }
      *param_4 = puVar4;
    }
    iVar5 = iVar5 + 1;
    if (7 < iVar5) {
      return 0;
    }
  } while( true );
}




/* 0x080113d0 */
undefined4 FUN_080113d0(param_1, param_2)
int param_1; uint * param_2;
{
  int iVar1;
  uint uVar2;
  code *pcVar3;
  
  if (param_2 != (uint *)0x0) {
    *param_2 = 0;
  }
  iVar1 = *(int *)(param_1 + 0x885c);
  if ((iVar1 != 0) && (pcVar3 = *(code **)(iVar1 + 0x2c), pcVar3 != (code *)0x0)) {
    uVar2 = (*pcVar3)();
    if (param_2 != (uint *)0x0) {
      *param_2 = uVar2;
    }
    if ((uVar2 & 3) != 0) {
      iVar1 = 0;
      do {
        if (((&DAT_87c00a48)[iVar1 * 0x2298] != 0) &&
           (*(int *)(param_1 + 0x885c) == (&DAT_87c092a4)[iVar1 * 0x2298])) {
          (&DAT_87c00a48)[iVar1 * 0x2298] = 1;
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 < 2);
      return 0x10;
    }
  }
  return 0;
}




/* 0x08011428 */
void FUN_08011428(param_1)
int param_1;
{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (((&DAT_87c11f14)[iVar1 * 0x3ac] == param_1) && ((&DAT_87c11f10)[iVar1 * 0xeb0] != '\0')) {
      (&DAT_87c11f10)[iVar1 * 0xeb0] = 0;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 8);
  return;
}




/* 0x08011458 */
int FUN_08011458(param_1, param_2, param_3)
int param_1; undefined4 param_2; int param_3;
{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_08011218(param_2);
  if (iVar1 == 0) {
    if (param_3 == 0) {
      return 8;
    }
  }
  else {
    *(undefined1 *)(iVar1 + 8) = 0;
    if (*(int *)(iVar1 + 4) != 0) {
      iVar2 = FUN_08013284(param_1,param_1 + (*(int *)(iVar1 + 0xe3c) - *(int *)(param_1 + 0x81dc))
                                             * 0x200 + 0x41dc,*(int *)(iVar1 + 0xe3c),1);
      if (iVar2 == 0) {
        *(undefined4 *)(iVar1 + 4) = 0;
      }
      else if (param_3 == 0) {
        return iVar2;
      }
    }
  }
  return param_3;
}




/* 0x080114a4 */
void FUN_080114a4(param_1, param_2, param_3)
int param_1; uint param_2; uint * param_3;
{
  uint uVar1;
  int iVar2;
  
  uVar1 = *param_3;
  *param_3 = param_2;
  param_3[1] = uVar1;
  if (param_2 == 0) {
    uVar1 = *(uint *)(param_1 + 0xb8);
    iVar2 = *(int *)(param_1 + 0xbc);
    param_3[3] = uVar1;
    param_3[4] = uVar1 + iVar2;
  }
  else {
    uVar1 = FUN_08013510(param_1,param_2);
    param_3[3] = uVar1;
    param_3[4] = uVar1 + *(byte *)(param_1 + 0x5a);
    if (0xfffffef < param_2) {
      param_3[4] = 0;
    }
  }
  param_3[5] = 0;
  param_3[2] = param_3[3];
  return;
}




/* 0x080114f4 */
undefined4 FUN_080114f4(param_1, param_2)
ushort * param_1; ushort * param_2;
{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  
LAB_080114f6:
  do {
    while( true ) {
      uVar1 = *param_2;
      if (uVar1 - 0x61 < 0x1a) {
        uVar1 = uVar1 - 0x20;
      }
      uVar2 = *param_1;
      if (uVar2 - 0x61 < 0x1a) {
        uVar2 = uVar2 - 0x20;
      }
      if (uVar1 == 0 && uVar2 == 0) {
        return 1;
      }
      if ((uVar2 != 0) || (uVar1 != 0x2e)) break;
LAB_08011566:
      param_2 = param_2 + 1;
    }
    if (uVar2 == uVar1) {
LAB_08011522:
      param_2 = param_2 + 1;
LAB_08011534:
      param_1 = param_1 + 1;
      goto LAB_080114f6;
    }
    if (uVar2 == 0x3f) {
      if (uVar1 != 0) goto LAB_08011522;
      goto LAB_08011534;
    }
    if (uVar2 != 0x2a) {
      return 0;
    }
    uVar3 = (uint)param_1[1];
    if (uVar3 - 0x61 < 0x1a) {
      uVar3 = uVar3 - 0x20;
    }
    param_1 = param_1 + 2;
    uVar3 = uVar3 & 0xffff;
    if (uVar3 == 0) {
      return 1;
    }
    while( true ) {
      uVar1 = *param_2;
      if (uVar1 - 0x61 < 0x1a) {
        uVar1 = uVar1 - 0x20;
      }
      if (uVar1 == uVar3) goto LAB_08011566;
      if (uVar1 == 0) break;
      param_2 = param_2 + 1;
    }
    if (uVar3 != 0x2e) {
      return 0;
    }
  } while( true );
}




/* 0x08011578 */
void FUN_08011578(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; uint param_3; int param_4;
{
  uint uVar1;
  uint uVar2;
  
  uVar1 = FUN_080382c2();
  if (param_3 < uVar1) {
    uVar1 = param_3;
  }
  if (param_4 != 0) {
    for (uVar2 = 0; uVar2 < uVar1; uVar2 = uVar2 + 1) {
      if (*(byte *)(param_1 + uVar2) - 0x41 < 0x1a) {
        *(byte *)(param_1 + uVar2) = *(byte *)(param_1 + uVar2) + 0x20;
      }
    }
  }
  return;
}




/* 0x080115ac */
undefined8 FUN_080115ac(param_1, param_2, param_3, param_4, param_5)
undefined4 param_1; int param_2; undefined4 param_3; undefined4 param_4; undefined4 param_5;
{
  int iVar1;
  int iVar2;
  int local_30;
  undefined4 local_2c;
  undefined4 uStack_28;
  
  *(undefined1 *)(param_2 + 0x20c) = 1;
  *(undefined1 *)(param_2 + 0x20a) = 0;
  local_2c = param_3;
  uStack_28 = param_4;
  iVar1 = (**(code **)(DAT_08050d08 + 8))(param_5,param_1,&local_2c);
  *(int *)(param_2 + 0x214) = iVar1;
  local_30 = param_2;
  if ((0xc < iVar1) ||
     (iVar2 = FUN_08022048(param_1,param_2,param_3,param_4), local_30 = iVar1, iVar2 == 0xff)) {
    iVar2 = 0;
    *(undefined1 *)(param_2 + 0x20c) = 0;
    *(char *)(param_2 + 0x20a) = (char)((iVar1 + 0xc) / 0xd);
  }
  return CONCAT44(local_30,iVar2);
}




/* 0x08011618 */
int FUN_08011618(param_1, param_2)
int * param_1; int param_2;
{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 auStack_60 [12];
  uint local_54;
  uint uStack_50;
  undefined1 auStack_48 [12];
  int local_3c;
  undefined4 local_30;
  undefined4 auStack_2c [2];
  
  iVar1 = *(int *)(param_2 + 0xe3c);
  iVar3 = *(int *)(param_2 + 0xe40);
  local_30 = 0xffffff7;
  iVar2 = FUN_08012088(param_1,*(undefined4 *)(param_2 + 0xe30),auStack_2c);
  if ((iVar2 == 0) &&
     (iVar2 = FUN_08012d54(param_1,*(undefined4 *)(param_2 + 0xe30),0xffffff7), iVar2 == 0)) {
LAB_08011664:
    do {
      if ((char)param_1[0x220f] != '\0') {
        param_1[0x220d] = param_1[0x220d] + -1;
        param_1[0x220e] = param_1[0x220e] + 1;
      }
      iVar2 = FUN_08010fe0(param_1,&local_30);
      if (iVar2 != 0) {
        return iVar2;
      }
      iVar2 = FUN_08012d54(param_1,local_30,auStack_2c[0]);
      if (iVar2 != 0) {
        return iVar2;
      }
      FUN_080114a4(param_1,local_30,auStack_60);
      FUN_080114a4(param_1,*(undefined4 *)(param_2 + 0xe30),auStack_48);
      for (; local_54 < uStack_50; local_54 = local_54 + 1) {
        iVar2 = FUN_08012a3c(param_1,param_1 + 0x2218,local_3c,1);
        if (iVar2 != 0) {
          return iVar2;
        }
        iVar2 = FUN_08013284(param_1,param_1 + 0x2218,local_54,1);
        if (iVar2 != 0) {
          if (*param_1 != 2) {
            return iVar2;
          }
          iVar2 = FUN_08012d54(param_1,local_30,0xffffff7);
          if (iVar2 != 0) {
            return iVar2;
          }
          goto LAB_08011664;
        }
        local_3c = local_3c + 1;
      }
    } while (false);
    uVar4 = *(undefined4 *)(param_2 + 0xe34);
    FUN_080114a4(param_1,local_30,param_2 + 0xe30);
    *(undefined4 *)(param_2 + 0xe34) = uVar4;
    *(int *)(param_2 + 0xe3c) = *(int *)(param_2 + 0xe40) - (iVar3 - iVar1);
    iVar2 = 0;
  }
  return iVar2;
}




/* 0x0801172c */
uint FUN_0801172c(param_1)
uint param_1;
{
  uint uVar1;
  
  if ((0x19 < param_1) || (uVar1 = (uint)(char)(&DAT_87c19488)[param_1], 1 < uVar1)) {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}




/* 0x08011744 */
undefined4 FUN_08011744(param_1, param_2)
int param_1; undefined4 * param_2;
{
  int iVar1;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x28) != 0)) {
    *param_2 = 0;
    param_2[1] = 0;
    param_2[2] = 0;
    param_2[3] = 0;
    iVar1 = (**(code **)(param_1 + 0x28))(param_1,param_2);
    if (iVar1 != 0) {
      return 0x15;
    }
    if (*(char *)(param_2 + 3) == '\0') {
      *(undefined1 *)(param_2 + 3) = 0xf8;
    }
    return 0;
  }
  return 0xf;
}




/* 0x08011774 */
undefined4 FUN_08011774(param_1, param_2, param_3)
int param_1; undefined4 param_2; undefined4 param_3;
{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = 3;
  while( true ) {
    bVar3 = iVar2 == 0;
    iVar2 = iVar2 + -1;
    if (bVar3) {
      return 0x11;
    }
    iVar1 = (**(code **)(param_1 + 0x20))(param_1,param_2,param_3);
    if (iVar1 == 0) break;
    if (iVar1 == -1) {
      return 0x10;
    }
  }
  return 0;
}




/* 0x080117a2 */
undefined4 FUN_080117a2(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; int param_4;
{
  int iVar1;
  undefined4 uVar2;
  code *pcVar3;
  int iVar4;
  bool bVar5;
  
  iVar4 = 3;
  iVar1 = 0;
  if ((param_1 == 0) || (*(int *)(param_1 + 0x10) == 0)) {
    uVar2 = 0xf;
  }
  else {
    do {
      bVar5 = iVar4 == 0;
      iVar4 = iVar4 + -1;
      if (bVar5) {
        if (iVar1 != 0) {
          if (iVar1 != -1) {
            return 0x11;
          }
          return 0x10;
        }
        break;
      }
      if (param_4 == 0) {
        pcVar3 = *(code **)(param_1 + 0x10);
      }
      else {
        pcVar3 = *(code **)(param_1 + 0x14);
      }
      iVar1 = (*pcVar3)(param_1,param_2,param_3);
    } while (iVar1 != 0);
    uVar2 = 0;
  }
  return uVar2;
}




/* 0x080117ea */
undefined4 FUN_080117ea(param_1, param_2, param_3)
int * param_1; int param_2; int param_3;
{
  int iVar1;
  
  if ((*(int *)(param_2 + 4) != 0) && (iVar1 = FUN_080110dc(param_1), iVar1 == 0)) {
    if (param_3 == 0) {
      do {
        while( true ) {
          if ((*(int *)(param_2 + 0x21c) != 0) ||
             (iVar1 = FUN_08013344(param_1,param_2 + 0x1c,*(undefined4 *)(param_2 + 0xe3c),1),
             iVar1 == 0)) goto LAB_08011884;
          if (*param_1 != 2) {
            return 0;
          }
          iVar1 = FUN_08011618(param_1,param_2);
          if (iVar1 != 0) {
            return 0;
          }
          if (*(int *)(param_2 + 0xe34) != 0) break;
          *(undefined4 *)(param_2 + 0xe2c) = *(undefined4 *)(param_2 + 0xe30);
        }
        iVar1 = FUN_08012d54(param_1,*(int *)(param_2 + 0xe34),*(undefined4 *)(param_2 + 0xe30));
      } while (iVar1 == 0);
    }
    else if ((*(int *)(param_2 + 0x220) != 0x80) ||
            (iVar1 = FUN_08011896(param_1,param_2), iVar1 == 0)) {
      iVar1 = *(int *)(param_2 + 0x220);
      if (iVar1 == 0) {
        *(int *)(param_2 + 0x224) = param_3;
      }
      *(int *)(param_2 + 0x220) = iVar1 + 1;
      FUN_08006bdc(*(int *)(param_2 + 0x228) + iVar1 * 0x18,param_2 + 0xe30,0x18);
LAB_08011884:
      *(undefined4 *)(param_2 + 4) = 0;
    }
  }
  return 0;
}




/* 0x08011896 */
undefined4 FUN_08011896(param_1, param_2)
int * param_1; int param_2;
{
  bool bVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  undefined4 local_28;
  
  iVar6 = 0;
  do {
    iVar5 = iVar6;
    if (*(int *)(param_2 + 0x220) <= iVar5) goto LAB_08011a12;
    iVar2 = *(int *)(param_2 + 0x228);
    iVar6 = iVar5;
    do {
      iVar6 = iVar6 + 1;
      if ((*(int *)(param_2 + 0x220) <= iVar6) ||
         (*(int *)(iVar2 + iVar6 * 0x18 + -0xc) + 1 != *(int *)(iVar2 + iVar6 * 0x18 + 0xc))) break;
    } while ((uint)(iVar6 - iVar5) < 0x100);
    iVar2 = FUN_08013344(param_1,*(int *)(param_2 + 0x224) + iVar5 * 0x200,
                         *(undefined4 *)(iVar2 + iVar5 * 0x18 + 0xc),iVar6 - iVar5);
  } while (iVar2 == 0);
  iVar6 = param_2 + 0xe30;
  FUN_08006bdc(&local_38,iVar6,0x18);
  for (; iVar5 < *(int *)(param_2 + 0x220); iVar5 = iVar5 + 1) {
    bVar1 = false;
    FUN_08006bdc(iVar6,*(int *)(param_2 + 0x228) + iVar5 * 0x18,0x18);
    while (iVar2 = FUN_08013344(param_1,*(int *)(param_2 + 0x224) + iVar5 * 0x200,
                                *(undefined4 *)(param_2 + 0xe3c),1), iVar2 != 0) {
      if (*param_1 != 2) {
        return 0;
      }
      iVar2 = FUN_08011618(param_1,param_2);
      if (iVar2 != 0) {
        return 0;
      }
      if (*(int *)(param_2 + 0xe34) == 0) {
        *(undefined4 *)(param_2 + 0xe2c) = *(undefined4 *)(param_2 + 0xe30);
      }
      else {
        iVar2 = FUN_08012d54(param_1,*(int *)(param_2 + 0xe34),*(undefined4 *)(param_2 + 0xe30));
        if (iVar2 != 0) {
          return 0;
        }
      }
      bVar1 = true;
    }
    if (bVar1) {
      piVar4 = (int *)(*(int *)(param_2 + 0x228) + iVar5 * 0x18);
      if (local_38 == *piVar4) {
        local_38 = *(int *)(param_2 + 0xe30);
        local_2c = (local_2c - local_30) + *(int *)(param_2 + 0xe38);
        local_30 = *(int *)(param_2 + 0xe38);
        local_28 = *(undefined4 *)(param_2 + 0xe40);
      }
      if (local_34 == *piVar4) {
        local_34 = *(int *)(param_2 + 0xe30);
      }
      iVar2 = *(int *)(param_2 + 0x220);
      while (iVar2 = iVar2 + -1, iVar5 < iVar2) {
        piVar3 = (int *)(*(int *)(param_2 + 0x228) + iVar2 * 0x18);
        if (*piVar3 == *piVar4) {
          *piVar3 = *(int *)(param_2 + 0xe30);
          piVar3[3] = (piVar3[3] - piVar3[2]) + *(int *)(param_2 + 0xe38);
          piVar3[2] = *(int *)(param_2 + 0xe38);
          piVar3[4] = *(int *)(param_2 + 0xe40);
        }
        if (piVar3[1] == *piVar4) {
          piVar3[1] = *(int *)(param_2 + 0xe30);
        }
      }
    }
  }
  FUN_08006bdc(iVar6,&local_38,0x18);
LAB_08011a12:
  *(undefined4 *)(param_2 + 0x220) = 0;
  return 0;
}




/* 0x08011a1e */
undefined4 FUN_08011a1e(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if (*(int *)(param_1 + 200) != 0) {
    iVar5 = 0;
    iVar6 = param_1;
    do {
      iVar3 = *(int *)(param_1 + 200);
      iVar4 = iVar5;
      while ((iVar4 < iVar3 && (*(int *)(*(int *)(param_1 + 0xcc) + iVar4 * 8 + 4) == 0))) {
        iVar4 = iVar4 + 1;
      }
      if (iVar4 < iVar3) {
        iVar1 = *(int *)(param_1 + 0xcc);
        iVar5 = iVar4;
        do {
          iVar5 = iVar5 + 1;
          if ((iVar3 <= iVar5) || (*(int *)(iVar1 + iVar5 * 8 + 4) == 0)) break;
        } while (*(int *)(iVar1 + iVar5 * 8 + -8) + 1 == *(int *)(iVar1 + iVar5 * 8));
        iVar1 = *(int *)(iVar1 + iVar4 * 8);
        for (iVar3 = 0; iVar2 = iVar4, iVar3 < (int)(uint)*(byte *)(param_1 + 0x5e);
            iVar3 = iVar3 + 1) {
          iVar2 = FUN_08013284(param_1,param_1 + iVar4 * 0x200 + 0x1d0,iVar1,iVar5 - iVar4,iVar6);
          if (iVar2 != 0) {
            return 0;
          }
          iVar1 = iVar1 + *(int *)(param_1 + 0xb4);
        }
        for (; iVar2 < iVar5; iVar2 = iVar2 + 1) {
          *(undefined4 *)(*(int *)(param_1 + 0xcc) + iVar2 * 8 + 4) = 0;
        }
      }
    } while (iVar4 < *(int *)(param_1 + 200));
    if (param_2 != 0) {
      *(undefined4 *)(param_1 + 200) = 0;
      *(undefined4 *)(param_1 + 0x41d4) = 0xffffffff;
    }
  }
  *(undefined4 *)(param_1 + 0x41d8) = 0;
  return 0;
}




/* 0x08011af0 */
undefined4 FUN_08011af0(param_1, param_2, param_3, param_4, param_5, param_6)
int param_1; undefined4 param_2; uint * param_3; int * param_4; int param_5; undefined4 param_6;
{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *local_28;
  
  iVar4 = 0;
  *(undefined1 *)(param_5 + 0x20c) = 3;
  *(undefined4 *)(param_5 + 0x210) = 0xffffffff;
  *(undefined4 *)(param_5 + 0x214) = 0xffffffff;
  local_28 = param_4;
  while( true ) {
    if (0xfffffef < *param_3) {
      return 0;
    }
    while (param_3[3] < param_3[4]) {
      iVar3 = param_1 + param_3[5] * 0x20 + 0x8620;
      iVar2 = FUN_08012326(param_1);
      if (iVar2 != 0) {
        return 0;
      }
      uVar1 = param_3[5];
      while (uVar1 < 0x10) {
        FUN_08010d00(iVar3,param_5,iVar4);
        iVar4 = iVar4 + 1;
        iVar2 = FUN_0801a360(param_2,iVar3,param_5,param_6);
        if (iVar2 == 0) {
          if (param_4 != (int *)0x0) {
            *param_4 = iVar3;
          }
          return 1;
        }
        if (iVar2 == 1) {
          return 0;
        }
        iVar3 = iVar3 + 0x20;
        uVar1 = param_3[5] + 1;
        param_3[5] = uVar1;
      }
      param_3[5] = 0;
      param_3[3] = param_3[3] + 1;
    }
    uVar1 = *param_3;
    if (uVar1 == 0) {
      if (*(int *)(param_1 + 0x882c) != 3) {
        return 0;
      }
      uVar1 = *(uint *)(param_1 + 0x7c);
      *param_3 = uVar1;
    }
    iVar2 = FUN_08012088(param_1,uVar1,&local_28);
    if (iVar2 != 0) break;
    if (0xfffffed < (int)local_28 - 2U) {
      return 0;
    }
    FUN_080114a4(param_1,local_28,param_3);
  }
  return 0;
}




/* 0x08011bc4 */
undefined4 FUN_08011bc4(param_1, param_2, param_3)
undefined4 * param_1; int param_2; int param_3;
{
  char cVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    cVar1 = (&DAT_87c11f10)[iVar2 * 0xeb0];
    if (((((cVar1 != '\0') && ((&DAT_87c11f14)[iVar2 * 0x3ac] == param_2)) &&
         ((&DAT_87c12d64)[iVar2 * 0x3ac] == *(int *)(param_3 + 0x14))) &&
        ((&DAT_87c12d5c)[iVar2 * 0x3ac] == *(int *)(param_3 + 0xc))) &&
       (((cVar1 == '\x02' || (cVar1 == '\x05')) ||
        ((cVar1 == '\x03' || ((cVar1 == '\x06' || (cVar1 == '\x04')))))))) break;
    iVar2 = iVar2 + 1;
    if (7 < iVar2) {
      return 0;
    }
  }
  *param_1 = (&DAT_87c11f20)[iVar2 * 0x3ac];
  return 1;
}




/* 0x08011c30 */
undefined4 FUN_08011c30(param_1, param_2, param_3)
int param_1; int param_2; int * param_3;
{
  short sVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  short *psVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  short *psVar8;
  undefined2 *local_38;
  int local_34;
  short *local_30;
  undefined4 local_2c;
  int local_28;
  
  iVar7 = 0;
  psVar8 = (short *)(param_2 + 4);
  FUN_080114a4(param_1,0);
  local_28 = FUN_080133a4(param_1 + 0x81e4,psVar8,0,param_3);
  if (local_28 == 0) {
    local_2c = FUN_080256a0(&local_30);
    uVar2 = FUN_080256a0(&local_38);
    uVar3 = FUN_08025618(&local_34);
    *local_38 = 0;
LAB_08011d7a:
    if (*psVar8 != 0) {
      iVar6 = 0;
      psVar4 = local_30;
      while (((sVar1 = *psVar8, sVar1 != 0 && (psVar8 = psVar8 + 1, sVar1 != 0x2f)) &&
             (sVar1 != 0x5c))) {
        iVar6 = iVar6 + 1;
        *psVar4 = sVar1;
        psVar4 = psVar4 + 1;
      }
      *psVar4 = 0;
      FUN_08031632(local_30,iVar6);
      if (((*param_3 == 0) && (*local_30 == 0x2e)) && (local_30[1] == 0)) {
        FUN_080114a4(param_1,0,param_3);
      }
      else {
        iVar6 = FUN_08011af0(param_1,local_30,param_3,&local_28,local_34,0);
        if ((iVar6 == 0) || (-1 < (int)((uint)*(byte *)(local_28 + 0xb) << 0x1b))) {
LAB_08011d3a:
          FUN_08025790(local_2c);
          FUN_08025790(uVar2);
          FUN_08025760(uVar3);
          return 0;
        }
        uVar5 = FUN_080122f8(param_1);
        FUN_080114a4(param_1,uVar5,param_3);
        iVar6 = FUN_080274a0(local_34);
        if (iVar6 == 0) {
          iVar6 = FUN_080274ba(local_34);
          if (iVar6 != 0) goto LAB_08011d3a;
          if (iVar7 != 0) {
            local_38[iVar7] = 0x2f;
            iVar7 = iVar7 + 1;
          }
          iVar6 = 0;
          while( true ) {
            sVar1 = *(short *)(local_34 + iVar6 * 2);
            iVar6 = iVar6 + 1;
            if (sVar1 == 0) break;
            local_38[iVar7] = sVar1;
            iVar7 = iVar7 + 1;
          }
        }
        else if ((*(short *)(local_34 + 2) != 0) && (*(short *)(local_34 + 2) == 0x2e)) {
          if ((*(short *)(local_34 + 4) != 0) || (iVar7 == 0)) goto LAB_08011d3a;
          do {
            iVar7 = iVar7 + -1;
            if (local_38[iVar7] == 0x2f) break;
          } while (iVar7 != 0);
        }
      }
      goto LAB_08011d7a;
    }
    local_38[iVar7] = 0;
    FUN_08006a30(param_2 + 4,local_38,0x200);
    FUN_08025790(local_2c);
    FUN_08025790(uVar2);
    FUN_08025760(uVar3);
  }
  else {
    uVar2 = FUN_080122f8(param_1,local_28);
    FUN_080114a4(param_1,uVar2,param_3);
  }
  return 1;
}




/* 0x08011da8 */
int FUN_08011da8(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; int param_3; uint param_4;
{
  char cVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  uint *puVar9;
  uint local_28;
  
  uVar5 = *(uint *)(param_3 + 0x18);
  if (uVar5 < param_4) {
    cVar1 = *(char *)(param_3 + 8);
    if ((((cVar1 != '\x04') && (cVar1 != '\x02')) && (cVar1 != '\x05')) &&
       ((cVar1 != '\x03' && (cVar1 != '\x06')))) {
      return 8;
    }
    *(uint *)(param_3 + 0xe64) = param_4 - uVar5;
  }
  else {
    *(undefined4 *)(param_3 + 0xe64) = 0;
    uVar5 = param_4;
  }
  uVar3 = *(uint *)(param_3 + 0x10);
  if (((uVar3 <= uVar5) && (uVar5 < uVar3 + 0x200)) && (*(int *)(param_3 + 0xe64) == 0)) {
    *(uint *)(param_3 + 0x14) = uVar5 - uVar3;
    return 0;
  }
  local_28 = param_4;
  if (*(int *)(param_3 + 4) != 0) {
    iVar4 = FUN_080117ea(param_1,param_3,0);
    if ((iVar4 != 0) || (iVar4 = FUN_08013228(param_1), iVar4 != 0)) goto LAB_08011ec0;
    FUN_080134a8(param_3);
  }
  if (*(int *)(param_3 + 0x18) == 0) {
    return 0;
  }
  bVar2 = *(byte *)(param_1 + 0x5a);
  puVar9 = (uint *)(param_3 + 0xe30);
  uVar8 = (uint)bVar2 * 0x200;
  uVar3 = *(uint *)(param_3 + 0x10) / uVar8;
  if (uVar5 / uVar8 < uVar3) {
    *(undefined4 *)(param_3 + 0x10) = 0;
    *(undefined4 *)(param_3 + 0x14) = 0;
    *(undefined4 *)(param_3 + 0xe34) = 0;
    *(undefined4 *)(param_3 + 0xe30) = *(undefined4 *)(param_3 + 0xe2c);
    iVar4 = (uVar5 >> (*(uint *)(param_3 + 0xea8) & 0xff)) - 1;
    if (iVar4 < 8) goto LAB_08011e7c;
    iVar4 = 7;
    do {
      if (*(int *)(param_3 + iVar4 * 4 + 0xe68) != -1) {
        iVar6 = param_3 + iVar4 * 4;
        *(undefined4 *)(param_3 + 0xe30) = *(undefined4 *)(iVar6 + 0xe68);
        iVar4 = iVar4 + 1 << (*(uint *)(param_3 + 0xea8) & 0xff);
        uVar5 = uVar5 - iVar4;
        *(undefined4 *)(param_3 + 0xe34) = *(undefined4 *)(iVar6 + 0xe88);
        *(int *)(param_3 + 0x10) = iVar4;
        break;
      }
      iVar4 = iVar4 + -1;
LAB_08011e7c:
    } while (-1 < iVar4);
  }
  else {
    uVar5 = uVar5 - uVar3 * uVar8;
    *(uint *)(param_3 + 0x10) = uVar8 * uVar3;
    *(undefined4 *)(param_3 + 0x14) = 0;
  }
  while( true ) {
    if (uVar5 < uVar8) {
      uVar7 = *(undefined4 *)(param_3 + 0xe34);
      FUN_080114a4(param_1,*(undefined4 *)(param_3 + 0xe30),puVar9);
      *(undefined4 *)(param_3 + 0xe34) = uVar7;
      for (; 0x1ff < uVar5; uVar5 = uVar5 - 0x200) {
        *(int *)(param_3 + 0xe3c) = *(int *)(param_3 + 0xe3c) + 1;
        *(int *)(param_3 + 0x10) = *(int *)(param_3 + 0x10) + 0x200;
      }
      *(uint *)(param_3 + 0x14) = uVar5;
      iVar4 = FUN_08012190(param_1,param_3,0);
      if (iVar4 == 0) {
        FUN_080134a8(param_3);
        return 0;
      }
      return iVar4;
    }
    iVar4 = FUN_08012088(param_1,*(undefined4 *)(param_3 + 0xe30),&local_28);
    if (iVar4 != 0) break;
    uVar5 = uVar5 + (uint)bVar2 * -0x200;
    *(uint *)(param_3 + 0x10) = *(int *)(param_3 + 0x10) + uVar8;
    if (0xfffffef < local_28) {
      if (uVar5 == 0) {
        uVar7 = *(undefined4 *)(param_3 + 0xe34);
        FUN_080114a4(param_1,*(undefined4 *)(param_3 + 0xe30),puVar9);
        *(undefined4 *)(param_3 + 0xe34) = uVar7;
        *(undefined4 *)(param_3 + 0xe3c) = *(undefined4 *)(param_3 + 0xe40);
        return 0;
      }
      *(byte *)(param_3 + 8) = *(byte *)(param_3 + 8) | 0x40;
      return 0x12;
    }
    *(undefined4 *)(param_3 + 0xe34) = *(undefined4 *)(param_3 + 0xe30);
    *puVar9 = local_28;
    FUN_080134a8(param_3);
  }
LAB_08011ec0:
  *(byte *)(param_3 + 8) = *(byte *)(param_3 + 8) | 0x40;
  return iVar4;
}




/* 0x08011f68 */
undefined2 FUN_08011f68(param_1)
undefined2 * param_1;
{
  return *param_1;
}




/* 0x08011f72 */
undefined4 FUN_08011f72(param_1)
undefined4 * param_1;
{
  return *param_1;
}




/* 0x08011f88 */
int FUN_08011f88(param_1, param_2)
int param_1; int param_2;
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int extraout_r3;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int local_38;
  
  iVar6 = 0;
  iVar9 = 0;
  iVar5 = *(int *)(param_1 + 0x8840);
  piVar7 = (int *)(param_1 + 0x8844);
  local_38 = 0;
  *piVar7 = 0;
  if (*(int *)(param_1 + 0x885c) == 0) {
    iVar2 = 1;
  }
  else {
    iVar2 = FUN_08011744(*(int *)(param_1 + 0x885c),param_1 + 0x884c);
    if (iVar2 == 0) {
      iVar2 = *(int *)(param_1 + 0x8854);
      *(int *)(param_1 + 0x8848) = iVar2;
LAB_08012062:
      if (iVar2 != 0) {
LAB_08011fe2:
        iVar3 = local_38 + 1;
        if (local_38 < 0x65) {
          iVar2 = FUN_08012a3c(param_1,param_2,*piVar7,1);
          if (iVar2 != 0) {
            return iVar2;
          }
          if ((*(char *)(param_2 + 0x1fe) == 'U') && (*(char *)(param_2 + 0x1ff) == -0x56)) {
            if ((*(char *)(param_2 + 0xb) != '\0') || (*(char *)(param_2 + 0xc) != '\x02')) {
              iVar2 = 0;
              iVar4 = 0;
              do {
                iVar8 = param_2 + iVar4;
                cVar1 = *(char *)(iVar8 + 0x1c2);
                local_38 = iVar3;
                if (cVar1 != '\0') {
                  iVar4 = FUN_08011f72(iVar8 + 0x1c6);
                  *piVar7 = iVar4 + iVar9 + iVar6;
                  iVar2 = FUN_08011f72(iVar8 + 0x1ca);
                  *(int *)(param_1 + 0x8848) = iVar2;
                  iVar2 = 1;
                  if ((cVar1 == '\x0f') || (cVar1 == '\x05')) {
                    *piVar7 = iVar4 + iVar6;
                    iVar9 = iVar4;
                    if (iVar6 == 0) {
                      iVar6 = iVar4;
                      iVar9 = 0;
                    }
                    goto LAB_08011fe2;
                  }
                  if (iVar5 == 0) goto LAB_08011fe2;
                  iVar5 = iVar5 + -1;
                  iVar4 = extraout_r3;
                }
                iVar4 = iVar4 + 0x10;
                if (0x30 < iVar4) goto LAB_08012062;
              } while( true );
            }
            if (iVar5 == 0) {
              return 0;
            }
          }
          else if (iVar5 == 0) {
            return 2;
          }
        }
      }
      iVar2 = 0x15;
    }
  }
  return iVar2;
}




/* 0x08012088 */
int FUN_08012088(param_1, param_2, param_3)
int param_1; uint param_2; uint * param_3;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 local_30;
  int local_2c;
  
  iVar1 = DAT_0804cd58;
  local_2c = DAT_0804cd58;
  iVar2 = *(int *)(param_1 + 0x882c);
  local_30 = param_3;
  if (iVar2 == 2) {
    iVar2 = FUN_08012350(param_1);
    if (iVar2 != 0) goto LAB_080120b8;
    uVar3 = FUN_08011f68(*(int *)(param_1 + 0x41d0) + (param_2 + (param_2 >> 8) * -0x100) * 2);
    if (0xffef < uVar3) {
LAB_08012156:
      uVar3 = uVar3 | 0xffff000;
    }
LAB_080120ec:
    if (param_3 != (uint *)0x0) {
LAB_080120ee:
      *param_3 = uVar3;
    }
  }
  else {
    if (iVar2 == 1) {
      uVar3 = param_2 + (param_2 >> 1);
      uVar5 = uVar3 >> 9;
      uVar3 = uVar3 & 0x1ff;
      iVar2 = FUN_08012350(param_1,uVar5);
      if (iVar2 != 0) goto LAB_080120b8;
      uVar4 = uVar3 + 1;
      local_30 = (uint *)CONCAT31(_GHIDRA_FIELD(local_30, 1, uint24_t),*(undefined1 *)(*(int *)(param_1 + 0x41d0) + uVar3)
                                 );
      if (0x1ff < uVar4) {
        iVar2 = FUN_08012350(param_1,uVar5 + 1);
        if (iVar2 != 0) goto LAB_080120b8;
        uVar4 = 0;
      }
      _GHIDRA_FIELD(local_30, 0, ushort) =
           CONCAT11(*(undefined1 *)(*(int *)(param_1 + 0x41d0) + uVar4),(undefined1)local_30);
      uVar3 = FUN_08011f68(&local_30);
      if ((param_2 & 1) == 0) {
        uVar3 = uVar3 & 0xfff;
      }
      else {
        uVar3 = uVar3 >> 4;
      }
      if (0xfef < uVar3) goto LAB_08012156;
      goto LAB_080120ec;
    }
    if (iVar2 != 3) {
      iVar2 = 0x15;
      goto LAB_080120b8;
    }
    iVar2 = FUN_08012350(param_1);
    if (iVar2 != 0) goto LAB_080120b8;
    if (param_3 != (uint *)0x0) {
      uVar3 = FUN_08011f72(*(int *)(param_1 + 0x41d0) + (param_2 + (param_2 >> 7) * -0x80) * 4);
      uVar3 = uVar3 & 0xfffffff;
      goto LAB_080120ee;
    }
  }
  iVar2 = 0;
LAB_080120b8:
  if (local_2c != iVar1) {
    FUN_08010960();
  }
  return iVar2;
}




/* 0x08012190 */
int FUN_08012190(param_1, param_2, param_3, param_4)
int param_1; int param_2; int param_3; uint * param_4;
{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  undefined1 auStack_58 [12];
  int local_4c;
  int local_48;
  int local_40;
  uint local_3c;
  int local_34;
  int iStack_30;
  int iStack_2c;
  uint *puStack_28;
  
  iVar7 = param_2 + 0xe30;
  piVar6 = (int *)(param_2 + 0xe3c);
  local_34 = param_1;
  iStack_30 = param_2;
  iStack_2c = param_3;
  puStack_28 = param_4;
  while( true ) {
    if (0xfffffed < *(int *)(param_2 + 0xe30) - 2U) {
      return 9;
    }
    local_3c = *(uint *)(param_2 + 0xe3c);
    if (local_3c < *(uint *)(param_2 + 0xe40)) break;
    iVar4 = FUN_08012088(local_34,*(int *)(param_2 + 0xe30),&local_40);
    if (iVar4 != 0) {
      return iVar4;
    }
    if (0xfffffed < local_40 - 2U) {
      return 9;
    }
    FUN_080114a4(local_34,local_40,iVar7);
  }
  if (param_3 == 0) {
    uVar5 = 1;
    param_3 = param_2 + 0x1c;
  }
  else {
    if (0x100 < *param_4) {
      *param_4 = 0x100;
    }
    iVar4 = *(int *)(param_2 + 0xe40);
    uVar5 = iVar4 - *(int *)(param_2 + 0xe3c);
    if ((int)uVar5 < (int)*param_4) {
      bVar1 = *(byte *)(local_34 + 0x5a);
      *piVar6 = iVar4 + -1;
      FUN_08006bdc(auStack_58,iVar7,0x18);
      FUN_080134a8(param_2);
      *(uint *)(param_2 + 0x10) = uVar5 * 0x200 + -0x200 + *(int *)(param_2 + 0x10);
      while( true ) {
        iVar2 = FUN_08012088(local_34,*(undefined4 *)(param_2 + 0xe30),&local_40);
        if (iVar2 != 0) {
          return iVar2;
        }
        if (0xfffffed < local_40 - 2U) break;
        FUN_080114a4(local_34,local_40,auStack_58);
        FUN_080134a8(param_2);
        if (local_4c != iVar4) goto LAB_08012284;
        FUN_08006bdc(iVar7,auStack_58,0x18);
        uVar3 = uVar5 + bVar1;
        if (*param_4 <= uVar3) {
          *piVar6 = *(int *)(param_2 + 0xe3c) + (*param_4 - uVar5) + -1;
          *(uint *)(param_2 + 0x10) = *(int *)(param_2 + 0x10) + (*param_4 - uVar5) * 0x200;
          uVar5 = *param_4;
          goto LAB_08012284;
        }
        *(uint *)(param_2 + 0x10) = *(int *)(param_2 + 0x10) + (uint)bVar1 * 0x200;
        *(int *)(param_2 + 0xe3c) = local_48 + -1;
        uVar5 = uVar3;
        iVar4 = local_48;
      }
      *(int *)(param_2 + 0xe3c) = iVar4 + -1;
LAB_08012284:
      *param_4 = uVar5;
    }
    else {
      FUN_080134a8(param_2);
      uVar5 = *param_4;
      *piVar6 = *(int *)(param_2 + 0xe3c) + (uVar5 - 1);
      *(uint *)(param_2 + 0x10) = uVar5 * 0x200 + -0x200 + *(int *)(param_2 + 0x10);
    }
  }
  iVar7 = FUN_08012a3c(local_34,param_3,local_3c,uVar5);
  return iVar7;
}




/* 0x080122f8 */
uint FUN_080122f8(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  undefined4 extraout_r2;
  uint extraout_r3;
  
  if (*(int *)(param_1 + 0x882c) != 3) {
    uVar1 = FUN_08011f68(param_2 + 0x1a);
    return uVar1;
  }
  FUN_08011f68(param_2 + 0x14);
  uVar1 = FUN_08011f68(extraout_r2);
  return uVar1 | extraout_r3;
}




/* 0x08012326 */
undefined4 FUN_08012326(param_1, param_2)
int param_1; undefined4 param_2;
{
  int iVar1;
  
  iVar1 = FUN_08012a3c(param_1,param_1 + 0x8620,param_2,1);
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + 0x8820) = 0xffffffff;
    return 0;
  }
  *(undefined4 *)(param_1 + 0x8820) = param_2;
  return 0;
}




/* 0x08012350 */
int FUN_08012350(param_1, param_2)
int param_1; uint param_2;
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (*(uint *)(param_1 + 0x41d4) != param_2) {
    if ((*(int *)(param_1 + 0x41d8) != 0) && (iVar1 = FUN_08013228(param_1), iVar1 != 0)) {
      return iVar1;
    }
    if (*(uint *)(param_1 + 0xb4) <= param_2) {
      return 0x12;
    }
    iVar3 = *(int *)(param_1 + 0xb0) + param_2;
    for (iVar1 = 0;
        (iVar1 < *(int *)(param_1 + 200) &&
        (*(int *)(*(int *)(param_1 + 0xcc) + iVar1 * 8) != iVar3)); iVar1 = iVar1 + 1) {
    }
    if (*(int *)(param_1 + 200) == iVar1) {
      if (iVar1 == 0x20) {
        iVar1 = FUN_08011a1e(param_1,1);
        if (iVar1 != 0) {
          return iVar1;
        }
        iVar1 = *(int *)(param_1 + 200);
      }
      *(uint *)(param_1 + 0x41d4) = param_2;
      iVar4 = 0;
      iVar5 = param_1 + iVar1 * 0x200 + 0x1d0;
      while( true ) {
        if ((int)(uint)*(byte *)(param_1 + 0x5e) <= iVar4) {
          *(undefined4 *)(param_1 + 0x41d4) = 0xffffffff;
          return 0x13;
        }
        iVar2 = FUN_08012a3c(param_1,iVar5,iVar3,8);
        if (iVar2 == 0) break;
        iVar4 = iVar4 + 1;
        iVar3 = iVar3 + *(int *)(param_1 + 0xb4);
      }
      iVar4 = 0;
      *(int *)(param_1 + 0x41d0) = iVar5;
      do {
        iVar5 = iVar3 + iVar4;
        iVar2 = iVar1 + iVar4;
        iVar4 = iVar4 + 1;
        *(int *)(*(int *)(param_1 + 0xcc) + iVar2 * 8) = iVar5;
      } while (iVar4 < 8);
      *(int *)(param_1 + 200) = *(int *)(param_1 + 200) + 8;
    }
    else {
      *(int *)(param_1 + 0x41d0) = param_1 + iVar1 * 0x200 + 0x1d0;
      *(uint *)(param_1 + 0x41d4) = param_2;
    }
  }
  return 0;
}




/* 0x0801242c */
void FUN_0801242c(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; uint param_4;
{
  int iVar1;
  undefined1 *local_30;
  undefined1 *local_2c;
  undefined1 auStack_28 [12];
  undefined1 auStack_1c [4];
  int local_18;
  
  iVar1 = DAT_0804cd58;
  local_18 = DAT_0804cd58;
  FUN_08011578(auStack_28,param_2,9,param_4 & 8);
  FUN_08011578(auStack_1c,param_3,4,param_4 & 0x10);
  local_30 = auStack_28;
  local_2c = auStack_1c;
  (**(code **)(DAT_08050d08 + 0xc))(&local_30,param_1);
  if (local_18 != iVar1) {
    FUN_08010960();
    return;
  }
  return;
}




/* 0x08012488 */
int * FUN_08012488()
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = FUN_0801d932(&DAT_0804e298);
  if (iVar3 == 0) {
    iVar3 = 0;
    do {
      if ((&DAT_87c11f10)[iVar3 * 0xeb0] == '\0') {
        iVar1 = iVar3 * 0xeb0;
        *(undefined4 *)(&DAT_87c11f1c + iVar1) = 0;
        (&DAT_87c11f18)[iVar3 * 0x3ac] = 0;
        (&DAT_87c11f20)[iVar3 * 0x3ac] = 0;
        (&DAT_87c12d34)[iVar3 * 0x3ac] = 0;
        *(undefined4 *)(&DAT_87c12d3c + iVar1) = 0;
        *(undefined4 *)(&DAT_87c11f0c + iVar1) = 0;
        iVar2 = DAT_0804e28c;
        *(undefined4 *)(&DAT_87c12128 + iVar1) = 0;
        *(undefined4 *)(&DAT_87c1212c + iVar1) = 0;
        *(int *)(&DAT_87c11f08 + iVar1) = iVar3 + iVar2 * 0x10;
        FUN_0801d942(&DAT_0804e298);
        return (int *)(&DAT_87c11f08 + iVar1);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 8);
    FUN_0801d942(&DAT_0804e298);
  }
  return (int *)0x0;
}




/* 0x08012500 */
uint FUN_08012500(param_1)
int param_1;
{
  uint uVar1;
  uint uVar2;
  
  uVar1 = (uint)*(ushort *)(param_1 + 0x62);
  if ((uVar1 != 0) || (uVar1 = *(uint *)(param_1 + 0x70), uVar2 = 0, uVar1 != 0)) {
    uVar2 = ((uVar1 + *(int *)(param_1 + 0x6c)) - *(int *)(param_1 + 0xc0)) /
            (uint)*(byte *)(param_1 + 0x5a);
  }
  return uVar2;
}




/* 0x08012524 */
int FUN_08012524(param_1, param_2, param_3)
int param_1; undefined4 param_2; undefined4 * param_3;
{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined2 *puVar5;
  int extraout_r3;
  int *piVar6;
  
  cVar2 = FUN_0801172c(param_2);
  if (cVar2 < '\0') {
    *(undefined4 *)(param_1 + 0x410) = 1;
    return 1;
  }
  iVar4 = (int)(short)cVar2;
  iVar1 = iVar4 * 0x8a60;
  piVar6 = &DAT_87c00a48 + iVar4 * 0x2298;
  iVar3 = FUN_0801267c(param_1,piVar6);
  if (iVar3 != 0) {
    return iVar3;
  }
  *(int *)(&DAT_87c09270 + iVar1) = param_1 + extraout_r3 * 0x200 + 8;
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = piVar6;
  }
  iVar3 = *piVar6;
  if (iVar3 == 0) {
    FUN_08011428(param_2);
  }
  else {
    if (iVar3 != 1) {
      if (iVar3 != 2) {
        return 1;
      }
      iVar3 = FUN_080113d0(piVar6,0);
      if (iVar3 == 0) {
        return 0;
      }
    }
    if ((&DAT_87c092a4)[iVar4 * 0x2298] != 0) {
      *(undefined4 *)(&DAT_87c00b10 + iVar1) = 0;
      iVar4 = 0;
      do {
        iVar3 = iVar4 * 8;
        iVar4 = iVar4 + 1;
        *(undefined4 *)(*(int *)(&DAT_87c00b14 + iVar1) + iVar3 + 4) = 0;
      } while (iVar4 < 0x20);
      *(undefined4 *)(&DAT_87c08c24 + iVar1) = 0xffffffff;
      *(undefined4 *)(&DAT_87c04c1c + iVar1) = 0xffffffff;
      *(undefined4 *)(&DAT_87c04c20 + iVar1) = 0;
      *(undefined4 *)(&DAT_87c09268 + iVar1) = 0xffffffff;
      *(undefined4 *)(&DAT_87c0926c + iVar1) = 0;
      (&DAT_87c09284)[iVar1] = 0;
      FUN_08011428(param_2);
      puVar5 = *(undefined2 **)(&DAT_87c09270 + iVar1);
      if (puVar5 != (undefined2 *)0x0) {
        *puVar5 = 0;
      }
      *(undefined4 *)(&DAT_87c09274 + iVar1) = 0;
      iVar4 = FUN_080113d0(piVar6,0);
      if (iVar4 == 0) {
        iVar4 = FUN_0801281c(piVar6);
        if (iVar4 == 0) {
          FUN_08011180(piVar6);
          DAT_0804e28c = DAT_0804e28c + 1;
          if ((DAT_0804e28c & 0xfffffff) == 0) {
            DAT_0804e28c = 1;
          }
          *piVar6 = 2;
          return 0;
        }
        *(undefined4 *)(&DAT_87c09274 + iVar1) = 0;
        return 2;
      }
      return iVar4;
    }
  }
  return 1;
}




/* 0x08012630 */
void FUN_08012630(param_1, param_2, param_3)
int param_1; undefined4 param_2; undefined4 param_3;
{
  undefined4 uVar1;
  undefined4 uVar2;
  
  FUN_08006cd0(param_1,0x20);
  FUN_08006a30(param_1,param_2,8);
  FUN_08006a30(param_1 + 8,param_3,3);
  uVar1 = FUN_080219a8();
  uVar2 = FUN_08021380();
  FUN_08012d3c(param_1 + 0x18,uVar2);
  uVar1 = FUN_080213c0(uVar1);
  FUN_08012d3c(param_1 + 0x16,uVar1);
  return;
}




/* 0x0801267c */
undefined4 FUN_0801267c(param_1, param_2)
undefined4 param_1; int param_2;
{
  if (*(int *)(param_2 + 0x885c) != 0) {
    return 0;
  }
  return 1;
}




/* 0x0801268c */
void FUN_0801268c()
{
  return;
}




/* 0x08012690 */
int FUN_08012690(param_1, param_2, param_3, param_4)
int param_1; int param_2; undefined4 param_3; int param_4;
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  int local_20;
  
  if (*(int *)(param_2 + 0x14) == 0x200) {
    local_20 = param_4;
    if (*(int *)(param_2 + 4) != 0) {
      iVar1 = FUN_08013284(param_1,param_1 + (*(int *)(param_2 + 0xe3c) - *(int *)(param_1 + 0x81dc)
                                             ) * 0x200 + 0x41dc,*(int *)(param_2 + 0xe3c),1);
      if (iVar1 != 0) {
        return iVar1;
      }
      *(undefined4 *)(param_2 + 4) = 0;
    }
    iVar1 = *(int *)(param_2 + 0xe3c) + 1;
    if (iVar1 == *(int *)(param_2 + 0xe40)) {
      uVar2 = *(uint *)(param_2 + 0xe30);
      if (0xfffffef < uVar2) {
        return 9;
      }
      if (uVar2 == 0) {
        if (*(int *)(param_1 + 0x882c) != 3) {
          return 9;
        }
        uVar2 = *(uint *)(param_1 + 0x7c);
        *(uint *)(param_2 + 0xe30) = uVar2;
      }
      iVar1 = FUN_08012088(param_1,uVar2,&local_20);
      if (iVar1 != 0) {
        return 9;
      }
      if (0xfffffed < local_20 - 2U) {
        return 9;
      }
      FUN_080114a4(param_1,local_20,param_2 + 0xe30);
    }
    else {
      *(int *)(param_2 + 0xe3c) = iVar1;
    }
    iVar1 = *(int *)(param_2 + 0xe38);
    uVar2 = *(int *)(param_2 + 0xe40) - iVar1;
    if (0x20 < uVar2) {
      uVar2 = 0x20;
    }
    uVar4 = *(uint *)(param_2 + 0xe3c);
    if (uVar2 <= uVar4 - *(int *)(param_1 + 0x81dc)) {
      if (uVar4 < iVar1 + uVar2) {
        iVar1 = FUN_08012a3c(param_1,param_1 + 0x41dc,iVar1,uVar2);
        if (iVar1 != 0) {
LAB_08012778:
          *(undefined4 *)(param_1 + 0x81dc) = 0xffffffff;
          return iVar1;
        }
        uVar3 = *(undefined4 *)(param_2 + 0xe38);
      }
      else {
        iVar1 = FUN_08012a3c(param_1,param_1 + 0x41dc,uVar4,uVar2);
        if (iVar1 != 0) goto LAB_08012778;
        uVar3 = *(undefined4 *)(param_2 + 0xe3c);
      }
      *(undefined4 *)(param_1 + 0x81dc) = uVar3;
      *(uint *)(param_1 + 0x81e0) = uVar2;
    }
    *(undefined4 *)(param_2 + 0x14) = 0;
    *(int *)(param_2 + 0x10) = *(int *)(param_2 + 0x10) + 0x200;
  }
  return 0;
}




/* 0x080127a0 */
undefined4 FUN_080127a0(param_1, param_2, param_3)
int param_1; undefined4 param_2; undefined4 param_3;
{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  puVar1 = (undefined4 *)FUN_08012488();
  uVar3 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[0x38b] = param_3;
    puVar1[3] = param_2;
    FUN_080114a4(param_1,puVar1[0x38b],puVar1 + 0x38c);
    uVar4 = puVar1[0x390] - puVar1[0x38e];
    if (0x20 < uVar4) {
      uVar4 = 0x20;
    }
    if ((*(int *)(param_1 + 0x81dc) == -1) ||
       (uVar4 <= (uint)(puVar1[0x38f] - *(int *)(param_1 + 0x81dc)))) {
      iVar2 = FUN_08012a3c(param_1,param_1 + 0x41dc,puVar1[0x38e],uVar4);
      if (iVar2 != 0) {
        *(undefined4 *)(param_1 + 0x81dc) = 0xffffffff;
        return 0;
      }
      *(undefined4 *)(param_1 + 0x81dc) = puVar1[0x38e];
      *(uint *)(param_1 + 0x81e0) = uVar4;
    }
    *(undefined1 *)(puVar1 + 2) = 1;
    uVar3 = *puVar1;
  }
  return uVar3;
}




/* 0x0801281c */
int FUN_0801281c(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  
  FUN_08006d14(param_1 + 0x4c,100,param_3,param_4,param_3,param_4);
  iVar1 = FUN_08011f88(param_1,param_1 + 0x8860);
  if (iVar1 != 0) {
    return iVar1;
  }
  uVar2 = FUN_080134f8(param_1 + 0x4c,3,param_1 + 0x8860);
  uVar2 = FUN_080134f8(param_1 + 0x4f,8,uVar2);
  puVar3 = (undefined1 *)FUN_080134d4(param_1 + 0x58,uVar2);
  piVar5 = (int *)(param_1 + 0x882c);
  if (*(short *)(param_1 + 0x58) != 0x200) {
    *piVar5 = 0;
    return 0x1b;
  }
  *(undefined1 *)(param_1 + 0x5a) = *puVar3;
  puVar3 = (undefined1 *)FUN_080134d4(param_1 + 0x5c,puVar3 + 1);
  *(undefined1 *)(param_1 + 0x5e) = *puVar3;
  uVar2 = FUN_080134d4(param_1 + 0x60,puVar3 + 1);
  puVar3 = (undefined1 *)FUN_080134d4(param_1 + 0x62,uVar2);
  *(undefined1 *)(param_1 + 100) = *puVar3;
  uVar2 = FUN_080134d4(param_1 + 0x66,puVar3 + 1);
  uVar2 = FUN_080134d4(param_1 + 0x68,uVar2);
  uVar2 = FUN_080134d4(param_1 + 0x6a,uVar2);
  uVar2 = FUN_080134e6(param_1 + 0x6c,uVar2);
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(param_1 + 0x8844);
  uVar2 = FUN_080134e6(param_1 + 0x70,uVar2);
  iVar1 = param_1 + 0x94;
  iVar6 = param_1 + 0x98;
  if (*(short *)(param_1 + 0x66) == 0) {
    if (*(int *)(param_1 + 0x70) == 0) {
      *piVar5 = 0;
      return 0x15;
    }
    *piVar5 = 3;
  }
  else {
    FUN_08011180(param_1);
    if (*piVar5 != 3) {
      puVar3 = (undefined1 *)FUN_080134d4(param_1 + 0x90,uVar2);
      *(undefined1 *)(param_1 + 0x92) = *puVar3;
      uVar2 = FUN_080134e6(iVar1,puVar3 + 1);
      uVar2 = FUN_080134f8(iVar6,0xb,uVar2);
      uVar2 = FUN_080134f8(param_1 + 0xa3,8,uVar2);
      uVar4 = 0x1c0;
      goto LAB_08012940;
    }
  }
  uVar2 = FUN_080134e6(param_1 + 0x74,uVar2);
  uVar2 = FUN_080134d4(param_1 + 0x78,uVar2);
  uVar2 = FUN_080134d4(param_1 + 0x7a,uVar2);
  uVar2 = FUN_080134e6(param_1 + 0x7c,uVar2);
  uVar2 = FUN_080134d4(param_1 + 0x80,uVar2);
  uVar2 = FUN_080134d4(param_1 + 0x82,uVar2);
  uVar2 = FUN_080134f8(param_1 + 0x84,0xc,uVar2);
  puVar3 = (undefined1 *)FUN_080134d4(param_1 + 0x90,uVar2);
  *(undefined1 *)(param_1 + 0x92) = *puVar3;
  uVar2 = FUN_080134e6(iVar1,puVar3 + 1);
  uVar2 = FUN_080134f8(iVar6,0xb,uVar2);
  uVar2 = FUN_080134f8(param_1 + 0xa3,8,uVar2);
  uVar4 = 0x1a4;
LAB_08012940:
  uVar2 = FUN_080134f8(0,uVar4,uVar2);
  FUN_080134f8(param_1 + 0xab,2,uVar2);
  if ((*(char *)(param_1 + 100) == -8) || (*(char *)(param_1 + 100) == -0x10)) {
    iVar1 = 0;
  }
  else {
    iVar1 = 2;
  }
  return iVar1;
}




/* 0x080129f0 */
int FUN_080129f0(param_1, param_2, param_3)
int param_1; undefined4 param_2; undefined4 param_3;
{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_08011218(param_3);
  if (iVar1 != 0) {
    iVar2 = FUN_08012690(param_1,iVar1);
    if (iVar2 == 0) {
      FUN_08006a30(param_2,*(int *)(iVar1 + 0x14) + param_1 +
                           (*(int *)(iVar1 + 0xe3c) - *(int *)(param_1 + 0x81dc)) * 0x200 + 0x41dc,
                   0x20);
      *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + 0x20;
      iVar2 = 0;
    }
    return iVar2;
  }
  return 8;
}




/* 0x08012a3c */
int FUN_08012a3c(param_1, param_2, param_3, param_4)
undefined4 * param_1; int param_2; int param_3; int param_4;
{
  int iVar1;
  int iVar2;
  int *piVar3;
  bool bVar4;
  
  if (param_1 != (undefined4 *)0x0) {
    piVar3 = param_1 + 0x2217;
    if (*piVar3 != 0) {
      if (*(int *)(*piVar3 + 0x20) == 0) {
        return 0xd;
      }
      iVar1 = FUN_080113d0(param_1,0);
      if (iVar1 != 0) {
        return iVar1;
      }
      if ((param_4 != 1) && (*(int *)(*piVar3 + 0x24) != 0)) {
        iVar1 = 3;
        while( true ) {
          bVar4 = iVar1 == 0;
          iVar1 = iVar1 + -1;
          if (bVar4) {
            return 0x11;
          }
          iVar2 = (**(code **)(*piVar3 + 0x24))(*piVar3,param_2,param_3,param_4);
          if (iVar2 == 0) break;
          if (iVar2 == -1) {
            *param_1 = 1;
            return 0x10;
          }
        }
        return 0;
      }
      iVar1 = 0;
      while( true ) {
        if (param_4 <= iVar1) {
          return 0;
        }
        iVar2 = FUN_08011774(*piVar3,param_2 + iVar1 * 0x200,param_3 + iVar1);
        if (iVar2 != 0) break;
        iVar1 = iVar1 + 1;
      }
      if (iVar2 != 0x10) {
        return iVar2;
      }
      *param_1 = 1;
      return 0x10;
    }
  }
  return 1;
}




/* 0x08012ad0 */
undefined4 FUN_08012ad0(param_1, param_2, param_3, param_4)
int param_1; uint param_2; undefined4 param_3; uint param_4;
{
  int iVar1;
  uint local_20;
  
  if (param_2 < *(uint *)(param_1 + 0x8824)) {
    *(uint *)(param_1 + 0x8824) = param_2;
  }
  local_20 = param_4;
  while( true ) {
    if (0xfffffed < param_2 - 2) {
      FUN_08013228(param_1);
      return 0;
    }
    iVar1 = FUN_08012088(param_1,param_2,&local_20);
    if ((iVar1 != 0) || (iVar1 = FUN_08012d54(param_1,param_2,0), iVar1 != 0)) break;
    param_2 = local_20;
    if (*(char *)(param_1 + 0x883c) != '\0') {
      *(int *)(param_1 + 0x8834) = *(int *)(param_1 + 0x8834) + -1;
      *(int *)(param_1 + 0x8830) = *(int *)(param_1 + 0x8830) + 1;
    }
  }
  return 0;
}




/* 0x08012b48 */
undefined4 FUN_08012b48(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; int param_4;
{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined1 local_40 [36];
  
  if ((*(char *)(param_4 + 0x20c) == '\0') || (*(char *)(param_4 + 0x20c) == '\x01')) {
    iVar2 = FUN_080127a0(param_1);
    if (iVar2 == 0) {
      uVar1 = 3;
    }
    else {
      iVar3 = FUN_08012bdc(param_1,iVar2,*(undefined4 *)(param_4 + 0x210),0);
      if (iVar3 == 0) {
        for (uVar4 = *(uint *)(param_4 + 0x210); uVar4 <= *(uint *)(param_4 + 0x214);
            uVar4 = uVar4 + 1) {
          iVar3 = FUN_080129f0(param_1,local_40,iVar2);
          if ((iVar3 != 0) || (iVar3 = FUN_08012bdc(param_1,iVar2,0xffffffff,1), iVar3 != 0))
          goto LAB_08012bc2;
          local_40[0] = 0xe5;
          iVar3 = FUN_0801317a(param_1,local_40,iVar2);
          if (iVar3 != 0) goto LAB_08012bc2;
        }
        iVar3 = 0;
      }
LAB_08012bc2:
      uVar1 = FUN_08011458(param_1,iVar2,iVar3);
    }
  }
  else {
    uVar1 = 4;
  }
  return uVar1;
}




/* 0x08012bdc */
int FUN_08012bdc(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; int param_3; int param_4;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  int local_28;
  
  local_28 = param_4;
  iVar1 = FUN_08011218(param_2);
  if (iVar1 == 0) {
    return 8;
  }
  if (((param_3 == -1) && (param_4 == 1)) && (*(int *)(iVar1 + 0x14) != 0)) {
    *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + -0x20;
  }
  else {
    param_3 = param_3 * 0x20;
    if (param_4 != 0) {
      if (param_4 != 1) {
        return 0xb;
      }
      param_3 = param_3 + *(int *)(iVar1 + 0x10) + *(int *)(iVar1 + 0x14);
    }
    if (*(int *)(iVar1 + 4) != 0) {
      iVar2 = FUN_08013284(param_1,param_1 + (*(int *)(iVar1 + 0xe3c) - *(int *)(param_1 + 0x81dc))
                                             * 0x200 + 0x41dc,*(int *)(iVar1 + 0xe3c),1);
      if (iVar2 != 0) {
        return iVar2;
      }
      *(undefined4 *)(iVar1 + 4) = 0;
    }
    *(undefined4 *)(iVar1 + 0x14) = 0;
    *(undefined4 *)(iVar1 + 0x10) = 0;
    FUN_080114a4(param_1,*(undefined4 *)(iVar1 + 0xe2c),iVar1 + 0xe30);
    while (0x1ff < param_3) {
      param_3 = param_3 + -0x200;
      *(int *)(iVar1 + 0x10) = *(int *)(iVar1 + 0x10) + 0x200;
      iVar2 = *(int *)(iVar1 + 0xe3c) + 1;
      if (iVar2 == *(int *)(iVar1 + 0xe40)) {
        uVar5 = *(uint *)(iVar1 + 0xe30);
        if (0xfffffef < uVar5) {
          return 9;
        }
        if (uVar5 == 0) {
          if (*(int *)(param_1 + 0x882c) != 3) {
            return 9;
          }
          uVar5 = *(uint *)(param_1 + 0x7c);
          *(uint *)(iVar1 + 0xe30) = uVar5;
        }
        iVar2 = FUN_08012088(param_1,uVar5,&local_28);
        if (iVar2 != 0) {
          return 9;
        }
        if (0xfffffed < local_28 - 2U) {
          return 9;
        }
        FUN_080114a4(param_1,local_28,iVar1 + 0xe30);
      }
      else {
        *(int *)(iVar1 + 0xe3c) = iVar2;
      }
    }
    *(int *)(iVar1 + 0x14) = param_3;
    iVar2 = *(int *)(iVar1 + 0xe38);
    uVar5 = *(int *)(iVar1 + 0xe40) - iVar2;
    if (0x20 < uVar5) {
      uVar5 = 0x20;
    }
    uVar4 = *(uint *)(iVar1 + 0xe3c);
    if (uVar5 <= uVar4 - *(int *)(param_1 + 0x81dc)) {
      if (uVar4 < iVar2 + uVar5) {
        iVar2 = FUN_08012a3c(param_1,param_1 + 0x41dc,iVar2,uVar5);
        if (iVar2 != 0) {
LAB_08012cc0:
          *(undefined4 *)(param_1 + 0x81dc) = 0xffffffff;
          return iVar2;
        }
        uVar3 = *(undefined4 *)(iVar1 + 0xe38);
      }
      else {
        iVar2 = FUN_08012a3c(param_1,param_1 + 0x41dc,uVar4,uVar5);
        if (iVar2 != 0) goto LAB_08012cc0;
        uVar3 = *(undefined4 *)(iVar1 + 0xe3c);
      }
      *(undefined4 *)(param_1 + 0x81dc) = uVar3;
      *(uint *)(param_1 + 0x81e0) = uVar5;
    }
  }
  return 0;
}




/* 0x08012d3c */
void FUN_08012d3c(param_1, param_2)
undefined1 * param_1; undefined4 param_2;
{
  *param_1 = (char)param_2;
  param_1[1] = (char)((uint)param_2 >> 8);
  return;
}




/* 0x08012d44 */
void FUN_08012d44(param_1, param_2)
undefined1 * param_1; undefined4 param_2;
{
  *param_1 = (char)param_2;
  param_1[1] = (char)((uint)param_2 >> 8);
  param_1[2] = (char)((uint)param_2 >> 0x10);
  param_1[3] = (char)((uint)param_2 >> 0x18);
  return;
}




/* 0x08012d54 */
int FUN_08012d54(param_1, param_2, param_3)
int param_1; uint param_2; uint param_3;
{
  int iVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  uint extraout_r2;
  int iVar5;
  uint uVar6;
  undefined4 local_28;
  int local_24;
  
  iVar1 = DAT_0804cd58;
  local_24 = DAT_0804cd58;
  iVar3 = *(int *)(param_1 + 0x882c);
  local_28 = param_3;
  if (iVar3 == 2) {
    iVar5 = param_2 + (param_2 >> 8) * -0x100;
    iVar3 = FUN_08012350(param_1);
    if (iVar3 != 0) goto LAB_08012d84;
    uVar4 = FUN_08011f68(*(int *)(param_1 + 0x41d0) + iVar5 * 2);
    if (uVar4 != (param_3 & 0xffff)) {
      FUN_08012d3c(*(int *)(param_1 + 0x41d0) + iVar5 * 2,param_3 & 0xffff);
LAB_08012ea0:
      *(undefined4 *)(param_1 + 0x41d8) = 1;
    }
  }
  else if (iVar3 == 1) {
    param_3 = param_3 & 0xfff;
    if ((param_2 & 1) != 0) {
      param_3 = (param_3 << 0x14) >> 0x10;
    }
    FUN_08012d3c(&local_28,param_3,param_2);
    uVar4 = extraout_r2 + (extraout_r2 >> 1);
    uVar6 = uVar4 >> 9;
    uVar4 = uVar4 & 0x1ff;
    iVar3 = FUN_08012350(param_1,uVar6);
    if (iVar3 != 0) goto LAB_08012d84;
    if ((param_2 & 1) != 0) {
      local_28 = CONCAT31(_GHIDRA_FIELD(local_28, 1, uint24_t),
                          (byte)local_28 | *(byte *)(*(int *)(param_1 + 0x41d0) + uVar4) & 0xf);
    }
    if ((uint)*(byte *)(*(int *)(param_1 + 0x41d0) + uVar4) != (local_28 & 0xff)) {
      *(byte *)(*(int *)(param_1 + 0x41d0) + uVar4) = (byte)local_28;
      *(undefined4 *)(param_1 + 0x41d8) = 1;
    }
    uVar4 = uVar4 + 1;
    if (0x1ff < uVar4) {
      iVar3 = FUN_08012350(param_1,uVar6 + 1);
      if (iVar3 != 0) goto LAB_08012d84;
      uVar4 = 0;
    }
    if ((param_2 & 1) == 0) {
      bVar2 = _GHIDRA_FIELD(local_28, 1, byte) | *(byte *)(*(int *)(param_1 + 0x41d0) + uVar4) & 0xf0;
      _GHIDRA_FIELD(local_28, 0, ushort) = CONCAT11(bVar2,(byte)local_28);
    }
    if (*(char *)(*(int *)(param_1 + 0x41d0) + uVar4) != _GHIDRA_FIELD(local_28, 1, byte)) {
      *(byte *)(*(int *)(param_1 + 0x41d0) + uVar4) = _GHIDRA_FIELD(local_28, 1, byte);
      goto LAB_08012ea0;
    }
  }
  else {
    if (iVar3 != 3) {
      iVar3 = 0x15;
      goto LAB_08012d84;
    }
    iVar5 = param_2 + (param_2 >> 7) * -0x80;
    iVar3 = FUN_08012350(param_1);
    if (iVar3 != 0) goto LAB_08012d84;
    uVar4 = FUN_08011f72(*(int *)(param_1 + 0x41d0) + iVar5 * 4);
    if ((uVar4 & 0xf0000000 | param_3 & 0xfffffff) != uVar4) {
      FUN_08012d44(*(int *)(param_1 + 0x41d0) + iVar5 * 4);
      goto LAB_08012ea0;
    }
  }
  iVar3 = 0;
LAB_08012d84:
  if (local_24 != iVar1) {
    FUN_08010960();
  }
  return iVar3;
}




/* 0x08012eac */
void FUN_08012eac(param_1, param_2, param_3)
int param_1; int param_2; undefined2 param_3;
{
  uint uVar1;
  uint extraout_r2;
  int extraout_r3;
  
  FUN_08012d3c(param_2 + 0x1a,param_3);
  if (*(int *)(param_1 + 0x882c) == 3) {
    uVar1 = extraout_r2 >> 0x10;
  }
  else {
    uVar1 = 0;
  }
  FUN_08012d3c(extraout_r3 + 0x14,uVar1);
  return;
}




/* 0x08012ed8 */
undefined4 FUN_08012ed8(param_1, param_2, param_3)
undefined4 param_1; ushort * param_2; uint * param_3;
{
  int iVar1;
  short sVar2;
  ushort uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar6 = 0;
  uVar4 = (uint)*param_2;
  iVar7 = 0;
  if (uVar4 != 0) {
    if (param_2[1] == 0x3a) {
      if (uVar4 - 0x61 < 0x1a) {
        uVar4 = uVar4 - 0x20;
      }
      if (0x19 < uVar4 - 0x41) {
        return 1;
      }
      param_2 = param_2 + 2;
      *param_3 = uVar4 - 0x41;
    }
    else {
      uVar4 = FUN_0801e7da(param_1);
      *param_3 = uVar4;
      if (uVar4 == 0xffffffff) {
        return 1;
      }
    }
    if ((*param_2 != 0x2f) && (*param_2 != 0x5c)) {
      iVar5 = FUN_0801f280(param_1,*param_3,param_3 + 1,0x100);
      if (iVar5 != 0) {
        return 1;
      }
      while (*(short *)((int)param_3 + iVar6 * 2 + 4) != 0) {
        *(undefined2 *)((int)param_3 + iVar6 * 2 + 4) =
             *(undefined2 *)((int)param_3 + iVar6 * 2 + 6);
        iVar6 = iVar6 + 1;
      }
      iVar6 = iVar6 + -1;
      if (iVar6 < 0) {
        iVar6 = 0;
      }
    }
    while( true ) {
      uVar3 = *param_2;
      if (uVar3 == 0) {
        *(undefined2 *)((int)param_3 + iVar7 * 2 + 0x204) = 0;
        *(undefined2 *)((int)param_3 + iVar6 * 2 + 4) = 0;
        iVar6 = FUN_08031632(param_3 + 0x81,iVar7);
        if (iVar6 == 0) {
          return 2;
        }
        return 0;
      }
      if (uVar3 == 0x3a) break;
      if ((uVar3 == 0x2f) || (uVar3 == 0x5c)) {
        if (0 < iVar6) {
          sVar2 = *(short *)((int)param_3 + iVar6 * 2 + 2);
          if (sVar2 == 0x2f) {
            return 1;
          }
          if (sVar2 == 0x5c) {
            return 1;
          }
          if (0xfd < iVar6) {
            return 1;
          }
          *(undefined2 *)((int)param_3 + iVar6 * 2 + 4) = 0x2f;
          iVar6 = iVar6 + 1;
        }
        iVar7 = FUN_08031632(param_3 + 0x81,iVar7);
        for (iVar5 = 0; iVar5 < iVar7; iVar5 = iVar5 + 1) {
          if (0xfd < iVar6) {
            return 1;
          }
          iVar1 = iVar6 * 2;
          iVar6 = iVar6 + 1;
          *(undefined2 *)((int)param_3 + iVar1 + 4) =
               *(undefined2 *)((int)param_3 + iVar5 * 2 + 0x204);
        }
        iVar7 = 0;
        param_2 = param_2 + 1;
      }
      else {
        if (0xfd < iVar7) {
          return 1;
        }
        iVar5 = iVar7 * 2;
        iVar7 = iVar7 + 1;
        *(ushort *)((int)param_3 + iVar5 + 0x204) = uVar3;
        param_2 = param_2 + 1;
      }
    }
  }
  return 1;
}




/* 0x08012fe0 */
void FUN_08012fe0(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined * param_3;
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if ((param_3[8] == '\x06') || (param_3[8] == '\x03')) {
    iVar3 = 0;
    do {
      iVar1 = iVar3 * 0xeb0;
      if (((((&DAT_87c11f08 + iVar1 != param_3) && ((&DAT_87c11f10)[iVar1] != '\0')) &&
           (*(int *)(param_3 + 0xc) == (&DAT_87c11f14)[iVar3 * 0x3ac])) &&
          ((*(int *)(param_3 + 0xe5c) == (&DAT_87c12d64)[iVar3 * 0x3ac] &&
           ((&DAT_87c12d5c)[iVar3 * 0x3ac] == *(int *)(param_3 + 0xe54))))) &&
         (((&DAT_87c11f10)[iVar1] == '\x01' &&
          (((&DAT_87c11f20)[iVar3 * 0x3ac] = *(undefined4 *)(param_3 + 0x18),
           (&DAT_87c12d34)[iVar3 * 0x3ac] == 0 && (iVar2 = *(int *)(param_3 + 0xe2c), iVar2 != 0))))
         )) {
        (&DAT_87c12d34)[iVar3 * 0x3ac] = iVar2;
        FUN_080114a4(param_1,iVar2,&DAT_87c12d38 + iVar1);
        (&DAT_87c11f18)[iVar3 * 0x3ac] = 0xfffffe00;
        FUN_08011da8(param_1,param_2,&DAT_87c11f08 + iVar1,0);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 8);
  }
  return;
}




/* 0x08013078 */
void FUN_08013078(param_1, param_2, param_3, param_4)
undefined * param_1; int param_2; int param_3; undefined4 param_4;
{
  int iVar1;
  
  if ((param_1[8] == '\x06') || (param_1[8] == '\x03')) {
    iVar1 = 0;
    do {
      if ((((&DAT_87c11f08 + iVar1 * 0xeb0 != param_1) && ((&DAT_87c11f10)[iVar1 * 0xeb0] != '\0'))
          && (*(int *)(param_1 + 0xc) == (&DAT_87c11f14)[iVar1 * 0x3ac])) &&
         (((*(int *)(param_1 + 0xe5c) == (&DAT_87c12d64)[iVar1 * 0x3ac] &&
           ((&DAT_87c12d5c)[iVar1 * 0x3ac] == *(int *)(param_1 + 0xe54))) &&
          (((&DAT_87c11f10)[iVar1 * 0xeb0] == '\x01' &&
           ((&DAT_87c11f18)[iVar1 * 0x3ac] == *(int *)(param_1 + 0x10))))))) {
        FUN_08006a30(&DAT_87c11f08 + iVar1 * 0xeb0 + param_3 + 0x1c,param_2 + param_3,param_4);
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < 8);
  }
  return;
}




/* 0x080130f8 */
undefined4 FUN_080130f8(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (param_3 != 0) {
    *(byte *)(param_2 + 8) = *(byte *)(param_2 + 8) | 0x40;
  }
  iVar1 = param_1 + *(int *)(param_2 + 0xe5c) * 0x20;
  iVar2 = FUN_08012326(param_1,*(undefined4 *)(param_2 + 0xe54));
  if (iVar2 == 0) {
    FUN_08012eac(param_1,iVar1 + 0x8620,*(undefined4 *)(param_2 + 0xe2c));
    FUN_08012d44(iVar1 + 0x863c,*(undefined4 *)(param_2 + 0x18));
    uVar3 = FUN_080219a8();
    uVar4 = FUN_08021380();
    FUN_08012d3c(iVar1 + 0x8638,uVar4);
    uVar4 = FUN_080213c0(uVar3);
    FUN_08012d3c(iVar1 + 0x8636,uVar4);
    uVar3 = FUN_08021380(uVar3);
    FUN_08012d3c(iVar1 + 0x8632,uVar3);
    FUN_080131ca(param_1);
    return 0;
  }
  return 0;
}




/* 0x0801317a */
int FUN_0801317a(param_1, param_2, param_3)
int param_1; undefined4 param_2; undefined4 param_3;
{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_08011218(param_3);
  if (iVar1 != 0) {
    iVar2 = FUN_08012690(param_1,iVar1);
    if (iVar2 == 0) {
      FUN_08006a30((*(int *)(iVar1 + 0xe3c) - *(int *)(param_1 + 0x81dc)) * 0x200 + 0x41dc +
                   *(int *)(iVar1 + 0x14) + param_1,param_2,0x20);
      *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + 0x20;
      *(undefined4 *)(iVar1 + 4) = 1;
      iVar2 = 0;
    }
    return iVar2;
  }
  return 8;
}




/* 0x080131ca */
undefined4 FUN_080131ca(param_1)
int param_1;
{
  uint uVar1;
  undefined4 uVar2;
  int *piVar3;
  
  piVar3 = (int *)(param_1 + 0x8820);
  if (*piVar3 != -1) {
    *(undefined1 *)(param_1 + 0x861c) = 0;
    uVar1 = *piVar3 - *(int *)(param_1 + 0x81dc);
    if (uVar1 < *(uint *)(param_1 + 0x81e0)) {
      FUN_08006a30(param_1 + uVar1 * 0x200 + 0x41dc,param_1 + 0x8620,0x200);
    }
    uVar2 = FUN_08013284(param_1,param_1 + 0x8620,*piVar3,1);
    return uVar2;
  }
  return 0x12;
}




/* 0x08013228 */
undefined4 FUN_08013228(param_1)
int param_1;
{
  int iVar1;
  
  if (*(int *)(param_1 + 0x41d8) != 0) {
    if (*(uint *)(param_1 + 0xb4) <= *(uint *)(param_1 + 0x41d4)) {
      return 0x12;
    }
    for (iVar1 = 0;
        (iVar1 < *(int *)(param_1 + 200) &&
        (*(int *)(*(int *)(param_1 + 0xcc) + iVar1 * 8) !=
         *(int *)(param_1 + 0xb0) + *(uint *)(param_1 + 0x41d4))); iVar1 = iVar1 + 1) {
    }
    if (*(int *)(param_1 + 200) == iVar1) {
      return 5;
    }
    *(undefined4 *)(*(int *)(param_1 + 0xcc) + iVar1 * 8 + 4) = 1;
    *(undefined4 *)(param_1 + 0x41d8) = 0;
  }
  return 0;
}




/* 0x08013284 */
undefined4 FUN_08013284()
{
  FUN_08013290();
  return 0;
}




/* 0x08013290 */
int FUN_08013290(param_1, param_2, param_3, param_4, param_5)
undefined4 * param_1; int param_2; int param_3; int param_4; int param_5;
{
  int iVar1;
  int iVar2;
  int *piVar3;
  code *pcVar4;
  bool bVar5;
  int local_28;
  
  if (param_1 != (undefined4 *)0x0) {
    piVar3 = param_1 + 0x2217;
    if (*piVar3 != 0) {
      if (*(int *)(*piVar3 + 0x10) == 0) {
        *param_1 = 1;
        return 0xd;
      }
      local_28 = param_4;
      iVar1 = FUN_080113d0(param_1,&local_28);
      if (iVar1 != 0) {
        return iVar1;
      }
      if (local_28 << 0x1d < 0) {
        return 0x17;
      }
      if ((param_4 != 1) && (*(int *)(*piVar3 + 0x18) != 0)) {
        iVar1 = 3;
        while( true ) {
          bVar5 = iVar1 == 0;
          iVar1 = iVar1 + -1;
          if (bVar5) {
            return 0x11;
          }
          iVar2 = *piVar3;
          if (param_5 == 0) {
            pcVar4 = *(code **)(iVar2 + 0x18);
          }
          else {
            pcVar4 = *(code **)(iVar2 + 0x1c);
          }
          iVar2 = (*pcVar4)(iVar2,param_2,param_3,param_4);
          if (iVar2 == 0) break;
          if (iVar2 == -1) {
            *param_1 = 1;
            return 0x10;
          }
        }
        return 0;
      }
      iVar1 = 0;
      while( true ) {
        if (param_4 <= iVar1) {
          return 0;
        }
        iVar2 = FUN_080117a2(*piVar3,param_2 + iVar1 * 0x200,param_3 + iVar1,param_5);
        if (iVar2 == 0x10) break;
        if (iVar2 != 0) {
          return iVar2;
        }
        iVar1 = iVar1 + 1;
      }
      *param_1 = 1;
      return 0x10;
    }
  }
  return 1;
}




/* 0x08013344 */
undefined4 FUN_08013344()
{
  FUN_08013290();
  return 0;
}




/* 0x08013350 */
undefined4 FUN_08013350(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 * param_3; uint param_4;
{
  uint uVar1;
  uint uVar2;
  
  FUN_08006d14(param_1 + 0x8860,0x200,0x8860,param_4,param_4);
  while( true ) {
    if (param_4 == 0) {
      return 0;
    }
    uVar2 = param_4;
    if (0x200 < param_4) {
      uVar2 = 0x200;
    }
    uVar1 = FUN_0802000e(param_2,param_1 + 0x8860,1,uVar2,*param_3);
    if (uVar1 != uVar2) break;
    param_4 = param_4 - uVar2;
  }
  *(byte *)(param_3 + 2) = *(byte *)(param_3 + 2) | 0x40;
  return 0x14;
}




/* 0x080133a4 */
int FUN_080133a4(param_1, param_2, param_3, param_4)
int param_1; int param_2; int param_3; undefined4 param_4;
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x438) != '\0') {
    iVar3 = param_1 + 0x200;
    if (param_3 == 0) {
      iVar2 = FUN_08038b92(param_1);
      if (iVar2 != 0) {
        iVar1 = FUN_08038b44(param_2,param_1,iVar2);
        if (iVar1 != 0) {
          return 0;
        }
        if (*(short *)(param_2 + iVar2 * 2) != 0x2f) {
          return 0;
        }
        iVar2 = iVar2 + 1;
      }
      param_2 = param_2 + iVar2 * 2;
      iVar2 = FUN_08038b92(iVar3);
      iVar2 = iVar2 + 1;
    }
    else {
      iVar3 = FUN_08038b44(param_3,iVar3,0x100);
      if (iVar3 != 0) {
        return 0;
      }
      iVar2 = 0x100;
      iVar3 = param_1;
    }
    iVar3 = FUN_08038b44(param_2,iVar3,iVar2);
    if (iVar3 == 0) {
      FUN_08006bdc(param_4,param_1 + 0x420,0x18);
      return param_1 + 0x400;
    }
  }
  return 0;
}




/* 0x08013426 */
void FUN_08013426(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  uVar1 = (uint)*(byte *)(param_2 + 0x5a) * 0x200;
  uVar4 = ((*(uint *)(param_1 + 0x18) >> 3) + ((int)uVar1 >> 1)) / uVar1;
  if (uVar4 == 0) {
    uVar4 = 1;
  }
  *(undefined4 *)(param_1 + 0xea8) = 9;
  iVar3 = 0;
  iVar2 = 0x200;
  do {
    if ((int)(uVar1 * uVar4) <= iVar2) break;
    iVar2 = iVar2 << 1;
    iVar3 = iVar3 + 1;
    *(int *)(param_1 + 0xea8) = *(int *)(param_1 + 0xea8) + 1;
  } while (iVar3 < 0x1f);
  iVar2 = 0;
  do {
    iVar3 = iVar2 * 4;
    iVar2 = iVar2 + 1;
    *(undefined4 *)(param_1 + iVar3 + 0xe68) = 0xffffffff;
  } while (iVar2 < 8);
  return;
}




/* 0x0801347a */
void FUN_0801347a(param_1)
int param_1;
{
  int iVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(param_1 + 0x18) >> (*(uint *)(param_1 + 0xea8) & 0xff);
  if (uVar2 << (*(uint *)(param_1 + 0xea8) & 0xff) == *(uint *)(param_1 + 0x18)) {
    uVar2 = uVar2 - 1;
  }
  if (-1 < (int)uVar2) goto LAB_080134a2;
  uVar2 = 0;
  do {
    iVar1 = uVar2 * 4;
    uVar2 = uVar2 + 1;
    *(undefined4 *)(param_1 + iVar1 + 0xe68) = 0xffffffff;
LAB_080134a2:
  } while ((int)uVar2 < 8);
  return;
}




/* 0x080134a8 */
void FUN_080134a8(param_1)
int param_1;
{
  uint uVar1;
  int iVar2;
  
  uVar1 = (*(uint *)(param_1 + 0x10) >> (*(uint *)(param_1 + 0xea8) & 0xff)) - 1;
  if ((uVar1 < 8) && (iVar2 = param_1 + uVar1 * 4, *(int *)(iVar2 + 0xe68) == -1)) {
    *(undefined4 *)(iVar2 + 0xe68) = *(undefined4 *)(param_1 + 0xe30);
    *(undefined4 *)(iVar2 + 0xe88) = *(undefined4 *)(param_1 + 0xe34);
  }
  return;
}




/* 0x080134d4 */
int FUN_080134d4(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  undefined2 uVar1;
  undefined2 *extraout_r2;
  int extraout_r3;
  
  uVar1 = FUN_08011f68(param_2,param_2,param_1,param_2);
  *extraout_r2 = uVar1;
  return extraout_r3 + 2;
}




/* 0x080134e6 */
int FUN_080134e6(param_1, param_2, param_3)
undefined4 param_1; int param_2; undefined4 param_3;
{
  undefined4 uVar1;
  undefined4 *extraout_r3;
  
  uVar1 = FUN_08011f72(param_2,param_2,param_3,param_1);
  *extraout_r3 = uVar1;
  return param_2 + 4;
}




/* 0x080134f8 */
undefined1 * FUN_080134f8(param_1, param_2, param_3)
undefined1 * param_1; int param_2; undefined1 * param_3;
{
  bool bVar1;
  
  if (param_1 == (undefined1 *)0x0) {
    return param_3 + param_2;
  }
  while (bVar1 = param_2 != 0, param_2 = param_2 + -1, bVar1) {
    *param_1 = *param_3;
    param_3 = param_3 + 1;
    param_1 = param_1 + 1;
  }
  return param_3;
}




/* 0x08013510 */
int FUN_08013510(param_1, param_2)
int param_1; int param_2;
{
  return *(int *)(param_1 + 0xc0) + (param_2 + -2) * (uint)*(byte *)(param_1 + 0x5a);
}




/* 0x08013520 */
undefined4 FUN_08013520(param_1)
int param_1;
{
  if (param_1 - 0x30U < 10) {
    return 1;
  }
  return 0;
}




/* 0x0801352e */
uint FUN_0801352e(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar5 = 0;
  for (uVar1 = 0; uVar1 < param_3; uVar1 = uVar1 + 1) {
    uVar3 = *(uint *)(param_1 + uVar1 * 4);
    uVar4 = uVar3 + uVar5;
    uVar2 = *(uint *)(param_2 + uVar1 * 4);
    *(uint *)(param_1 + uVar1 * 4) = uVar2 + uVar4;
    uVar5 = (uint)CARRY4(uVar3,uVar5) + (uint)CARRY4(uVar2,uVar4);
  }
  return uVar5;
}




/* 0x0801355c */
undefined4 FUN_0801355c(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 local_14;
  
  local_14 = param_4;
  iVar1 = FUN_080135fc();
  if (iVar1 == 0) {
    iVar1 = FUN_080135cc(param_1,0x200000,0x20000,1,4,0,1);
    if (iVar1 == 0) {
      iVar1 = FUN_080135cc(param_1,&DAT_08600000,0x4000,1,5,0,1);
      if (iVar1 == 0) {
        local_14 = 0xffffffff;
        FUN_0802212c(param_1,&DAT_87c00000,&local_14);
        FUN_080135cc(param_1,&DAT_87c00000,0xe0000,1,local_14,0,2);
      }
    }
  }
  return 0;
}




/* 0x080135cc */
undefined4 FUN_080135cc(param_1, param_2, param_3, param_4, param_5, param_6, param_7)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4; undefined4 param_5; undefined4 param_6; undefined4 param_7;
{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = 4;
  if (*(uint *)(param_1 + 0x10) < 0x20) {
    iVar2 = param_1 + *(uint *)(param_1 + 0x10) * 0x40;
    *(undefined4 *)(iVar2 + 0x28) = param_2;
    *(undefined4 *)(iVar2 + 0x2c) = 0;
    *(undefined4 *)(iVar2 + 0x30) = param_3;
    *(undefined4 *)(iVar2 + 0x34) = 0;
    *(undefined4 *)(iVar2 + 0x38) = param_4;
    *(undefined4 *)(iVar2 + 0x3c) = param_5;
    *(undefined4 *)(iVar2 + 0x40) = param_6;
    *(undefined4 *)(iVar2 + 0x44) = param_7;
    uVar1 = 0;
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
  }
  return uVar1;
}




