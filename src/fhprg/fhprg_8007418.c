/* Auto-generated: fhprg_8007418.c */
/* Functions: 10 */
#include "globals.h"

/* 0x08007418 */
undefined8 FUN_08007418(param_1)
uint param_1;
{
  uint uVar1;
  int iVar2;
  
  uVar1 = param_1 - (param_1 >> 2);
  uVar1 = uVar1 + (uVar1 >> 4);
  uVar1 = uVar1 + (uVar1 >> 8);
  uVar1 = uVar1 + (uVar1 >> 0x10) >> 3;
  iVar2 = (param_1 - 10) + uVar1 * -10;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 10;
  }
  else {
    uVar1 = uVar1 + 1;
  }
  return CONCAT44(iVar2,uVar1);
}




/* 0x08007446 */
undefined8 thunk_FUN_08007446(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  FUN_08007b10(2);
  return CONCAT44(param_2,param_1);
}




/* 0x08007446 */
undefined8 FUN_08007446(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  FUN_08007b10(2);
  return CONCAT44(param_2,param_1);
}




/* 0x08007450 */
undefined * FUN_08007450()
{
  return &DAT_0805a8ac;
}




/* 0x0800745a */
void FUN_0800745a(param_1, param_2, param_3, param_4, param_5)
uint * param_1; char * param_2; int * param_3; uint param_4; uint param_5;
{
  char cVar1;
  bool bVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  char extraout_r2;
  char extraout_r2_00;
  int iVar7;
  undefined4 extraout_r2_01;
  undefined4 extraout_r2_02;
  uint uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  uint unaff_r11 = 0;
  undefined8 uVar12;
  ulonglong uVar13;
  longlong lVar14;
  undefined8 local_60;
  int local_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  int local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  uint local_3c;
  int local_38;
  uint *local_34;
  char *pcStack_30;
  int *piStack_2c;
  uint uStack_28;
  
  uVar13 = CONCAT44(_GHIDRA_FIELD(local_60, 4, uint),(int)local_60);
  local_38 = *param_3;
  uVar4 = param_3[1];
  uVar8 = (uVar4 << 1) >> 0x15;
  if (uVar8 == 0) {
    uVar8 = 0xffffffff;
  }
  iVar11 = 0;
  if (false) {
    iVar11 = -1;
  }
  if (local_38 == 0 && (uVar4 & 0x7fffffff) == 0) {
    uVar4 = 0;
    if (param_5 == 1) {
      uVar8 = ~param_4;
      param_4 = uVar4;
    }
    else {
      for (; (int)uVar4 < (int)param_4; uVar4 = uVar4 + 1) {
        param_2[uVar4] = '0';
      }
      uVar8 = 0;
    }
    param_2[param_4] = '\0';
    param_1[2] = param_5;
    *param_1 = uVar8;
    param_1[1] = param_4;
    return;
  }
  uVar8 = (int)((uVar8 - 0x3ff) * 0x4d10) >> 0x10;
  local_34 = param_1;
  pcStack_30 = param_2;
  piStack_2c = param_3;
  uStack_28 = param_4;
LAB_080074ba:
  do {
    if (param_5 == 0) {
      iVar9 = (uVar8 - param_4) + 1;
    }
    else {
      iVar9 = -param_4;
    }
    iVar7 = iVar11;
    if (0 < iVar9) {
      iVar7 = -iVar11;
    }
    iVar5 = iVar9;
    if (iVar9 < 0) {
      iVar5 = -iVar9;
    }
    local_60 = uVar13;
    FUN_08007a38(&local_48,iVar5,iVar7);
    local_54 = local_48;
    uStack_50 = uStack_44;
    uStack_4c = uStack_40;
    uVar12 = FUN_08008004(uVar4,local_38,uStack_40,&local_48);
    _GHIDRA_FIELD(local_60, 4, uint) = (undefined4)((ulonglong)uVar12 >> 0x20);
    _GHIDRA_FIELD(local_60, 0, uint) = (int)uVar12 + -0x201f;
    if (iVar9 < 1) {
      local_54 = local_54 + -0x201f;
      uVar13 = FUN_0800850e(&local_60,&local_54,iVar11);
      uVar3 = extraout_r2_02;
    }
    else {
      local_54 = local_54 + 0x201f;
      uVar13 = FUN_080084e6(&local_60,&local_54,iVar11);
      uVar3 = extraout_r2_01;
    }
    _GHIDRA_FIELD(local_60, 4, uint) = (undefined4)(uVar13 >> 0x20);
    uVar6 = _GHIDRA_FIELD(local_60, 4, uint);
    if ((uVar13 & 0xffff) != 0) {
      uVar3 = 0xffffffff;
      uVar6 = 0x7fffffff;
    }
    lVar14 = CONCAT44(uVar6,uVar3);
    uVar10 = param_4;
    if (param_5 != 0) {
      _GHIDRA_FIELD(local_60, 0, uint) = 0;
      for (uVar10 = 0;
          (uVar13 = CONCAT44(_GHIDRA_FIELD(local_60, 4, uint),(int)local_60), lVar14 != 0 && ((int)uVar10 < 0x11));
          uVar10 = uVar10 + 1) {
        lVar14 = FUN_08006ea0();
        param_2[uVar10] = extraout_r2_00 + '0';
      }
      if (lVar14 != 0) {
        param_4 = unaff_r11;
        if ((int)local_60 != 0) goto LAB_080075ea;
        param_4 = 0x11;
        param_5 = 0;
        goto LAB_080074ba;
      }
      uVar4 = uVar10;
      for (iVar11 = 0; uVar4 = uVar4 - 1, iVar11 < (int)uVar4; iVar11 = iVar11 + 1) {
        cVar1 = param_2[iVar11];
        param_2[iVar11] = param_2[uVar4];
        param_2[uVar4] = cVar1;
      }
      iVar11 = uVar10 - param_4;
      param_4 = uVar10;
      local_3c = iVar11 - 1;
LAB_080075ea:
      param_2[param_4] = '\0';
      local_34[2] = param_5;
      *local_34 = local_3c;
      local_34[1] = param_4;
      return;
    }
    while (uVar10 = uVar10 - 1, -1 < (int)uVar10) {
      local_60 = uVar13;
      lVar14 = FUN_08006ea0();
      param_2[uVar10] = extraout_r2 + '0';
      uVar13 = local_60;
    }
    bVar2 = true;
    if (lVar14 == 0) {
      if (*param_2 == '0') {
        bVar2 = false;
        uVar8 = uVar8 - 1;
      }
    }
    else {
      bVar2 = false;
      uVar8 = uVar8 + 1;
    }
    unaff_r11 = param_4;
    local_3c = uVar8;
    if (bVar2) goto LAB_080075ea;
  } while( true );
}




/* 0x0800789c */
undefined8 FUN_0800789c(param_1, param_2, param_3, param_4)
char * param_1; undefined4 * param_2; uint param_3; uint param_4;
{
  bool bVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  
  bVar1 = false;
  bVar2 = false;
  pcVar8 = param_1 + 1;
  cVar3 = *param_1;
  uVar7 = param_3;
  if (cVar3 == '0') {
    pcVar9 = param_1 + 2;
    cVar3 = *pcVar8;
    bVar1 = true;
    pcVar8 = pcVar9;
    if ((cVar3 == 'x') || (cVar3 == 'X')) {
      if ((param_3 == 0) || (param_3 == 0x10)) {
        bVar1 = false;
        cVar3 = *pcVar9;
        pcVar8 = param_1 + 3;
        uVar7 = 0x10;
      }
    }
    else if (param_3 == 0) {
      uVar7 = 8;
    }
  }
  else if (param_3 == 0) {
    uVar7 = 10;
  }
  uVar11 = 0;
  uVar10 = 0;
  uVar12 = 0;
  pcVar9 = param_1;
  uVar13 = param_3;
  while (iVar4 = FUN_08007a1c(cVar3,uVar7,param_3,param_4,pcVar9,param_2,uVar13), -1 < iVar4) {
    param_4 = uVar7 * uVar12 + iVar4;
    bVar1 = true;
    uVar6 = (uint)((ulonglong)uVar7 * (ulonglong)uVar11);
    param_3 = (uint)((ulonglong)uVar7 * (ulonglong)uVar11 >> 0x20);
    uVar12 = param_4 & 0xffff;
    iVar4 = ((int)uVar7 >> 0x1f) * uVar11;
    uVar11 = uVar6 + (param_4 >> 0x10);
    uVar10 = uVar7 * uVar10 + iVar4 + param_3 + (uint)CARRY4(uVar6,param_4 >> 0x10);
    if (0xffff < uVar10) {
      bVar2 = true;
    }
    cVar3 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  }
  if (param_2 != (undefined4 *)0x0) {
    if (bVar1) {
      param_1 = pcVar8 + -1;
    }
    *param_2 = param_1;
  }
  if (bVar2) {
    puVar5 = (undefined4 *)FUN_08007450();
    *puVar5 = 2;
    uVar12 = 0xffffffff;
    uVar7 = uVar12;
  }
  else {
    uVar7 = uVar10 << 0x10 | uVar11 >> 0x10;
    uVar12 = uVar12 | uVar11 << 0x10;
  }
  return CONCAT44(uVar7,uVar12);
}




/* 0x0800795c */
undefined4 FUN_0800795c(param_1, param_2, param_3)
undefined1 * param_1; uint param_2; undefined4 param_3;
{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  
  piVar1 = (int *)FUN_080060b0();
  iVar3 = *piVar1;
  if (*(char *)(iVar3 + 0x101) == '\x01') {
                    /* WARNING: Could not recover jumptable at 0x08007994. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = ((code *)(iVar3 + *(int *)(iVar3 + 0x107) + 0x107))(param_1,param_2,param_3);
    return uVar2;
  }
  if ((param_2 < 0x100) && (*(char *)(iVar3 + param_2) != '\0')) {
    *param_1 = (char)param_2;
    return 1;
  }
  return 0xffffffff;
}




/* 0x0800799c */
void FUN_0800799c(param_1, param_2, param_3, param_4)
uint * param_1; undefined4 param_2; int param_3; int param_4;
{
  uint uVar1;
  undefined1 *puVar2;
  int iVar3;
  bool bVar4;
  
  iVar3 = 3;
  uVar1 = *param_1 & 0x800;
  if (param_3 < 7) {
    if (uVar1 == 0) {
      puVar2 = &UNK_08007a18;
    }
    else {
      puVar2 = &UNK_08007a14;
    }
  }
  else if (uVar1 == 0) {
    puVar2 = &UNK_08007a10;
  }
  else {
    puVar2 = &DAT_08007a0c;
  }
  *param_1 = *param_1 & 0xffffffef;
  uVar1 = param_1[6];
  param_1[6] = uVar1 - 3;
  if (param_4 != 0) {
    param_1[6] = uVar1 - 4;
  }
  FUN_08006484(param_1);
  if (param_4 == 0) {
    uVar1 = param_1[8];
  }
  else {
    ((code *)param_1[1])(param_4,param_1[2]);
    uVar1 = param_1[8] + 1;
    param_1[8] = uVar1;
  }
  param_1[8] = uVar1 + 3;
  while (bVar4 = iVar3 != 0, iVar3 = iVar3 + -1, bVar4) {
    ((code *)param_1[1])(*puVar2,param_1[2]);
    puVar2 = puVar2 + 1;
  }
  FUN_080064b2(param_1);
  return;
}




/* 0x08007a1c */
uint FUN_08007a1c(param_1, param_2)
uint param_1; uint param_2;
{
  if (param_1 < 0x3a) {
    param_1 = param_1 - 0x30;
  }
  if (0x40 < (param_1 & 0xffffffdf)) {
    param_1 = (param_1 & 0xffffffdf) - 0x37;
  }
  if (param_2 <= param_1) {
    param_1 = 0xffffffff;
  }
  return param_1;
}




/* 0x08007a38 */
void FUN_08007a38(param_1, param_2, param_3)
undefined8 * param_1; int param_2; int param_3;
{
  int iVar1;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 extraout_r2_01;
  undefined4 extraout_r2_02;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 local_48;
  undefined4 uStack_40;
  undefined8 local_3c;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  int local_28;
  
  _GHIDRA_FIELD(local_48, 0, uint) = 0x3fff;
  _GHIDRA_FIELD(local_48, 4, uint) = 0x80000000;
  uStack_40 = 0;
  _GHIDRA_FIELD(local_3c, 0, uint) = 0x3fff;
  _GHIDRA_FIELD(local_3c, 4, uint) = 0x80000000;
  uStack_34 = 0;
  uVar7 = FUN_080392a4(param_2 + 0x1b9b,0x37);
  uVar8 = CONCAT44(_GHIDRA_FIELD(local_48, 4, uint),(undefined4)local_48);
  uVar3 = (int)((ulonglong)uVar7 >> 0x20) - 0x1b;
  bVar6 = -1 < (int)uVar3;
  uVar4 = (int)uVar7 - 0x80;
  if (!bVar6) {
    uVar3 = -uVar3;
  }
  iVar5 = 0;
  for (; uVar7 = CONCAT44(_GHIDRA_FIELD(local_3c, 4, uint),(undefined4)local_3c), uVar3 != 0; uVar3 = (int)uVar3 >> 1)
  {
    if ((uVar3 & 1) != 0) {
      local_48 = uVar8;
      uVar8 = FUN_0800850e(&local_48,&DAT_0803dde8 + iVar5 * 0xc,param_3);
      uStack_40 = extraout_r2;
    }
    iVar5 = iVar5 + 1;
  }
  iVar5 = 0;
  for (; local_48 = uVar8, local_3c = uVar7, uVar4 != 0; uVar4 = (int)uVar4 >> 1) {
    if ((uVar4 & 1) != 0) {
      iVar1 = iVar5 * 0x10;
      local_30 = *(undefined4 *)(&DAT_0803de24 + iVar1);
      uStack_2c = *(undefined4 *)(&DAT_0803de28 + iVar1);
      local_28 = *(int *)(&DAT_0803de2c + iVar1);
      if (*(int *)(&DAT_0803de30 + iVar1) + param_3 == 0) {
        local_28 = local_28 + param_3;
      }
      uVar7 = FUN_0800850e(&local_3c,&local_30,param_3);
      uStack_34 = extraout_r2_00;
      uVar8 = local_48;
    }
    iVar5 = iVar5 + 1;
  }
  if (bVar6) {
    uVar8 = FUN_0800850e(&local_3c,&local_48,param_3);
    uVar2 = extraout_r2_02;
  }
  else {
    uVar8 = FUN_080084e6();
    uVar2 = extraout_r2_01;
  }
  *param_1 = uVar8;
  *(undefined4 *)(param_1 + 1) = uVar2;
  return;
}




