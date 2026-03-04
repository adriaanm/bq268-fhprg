/* Auto-generated: smem.c */
/* Functions: 10 */
#include "globals.h"

/* 0x080373b8 */
int thunk_FUN_080373b8(param_1, param_2)
uint param_1; int param_2;
{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int *piVar8;
  
  if (DAT_0804d1d0 == '\x01') {
    return 0;
  }
  if (8 < param_1) {
    if (8 < param_1) {
      if (DAT_0804d1d0 == '\0') {
        FUN_08037868();
      }
      if (0x1dd < param_1) {
        FUN_08015a50();
      }
      uVar7 = param_2 + 7U & 0xfffffff8;
      FUN_08037be8(3);
      iVar3 = DAT_08054298;
      iVar4 = DAT_0804d1b8;
      iVar2 = DAT_0804d1b4;
      piVar8 = (int *)(DAT_0804d1b8 + param_1 * 0x10);
      if (*piVar8 == 1) {
        if (*(uint *)(DAT_0804d1b8 + param_1 * 0x10 + 8) == uVar7) {
          iVar2 = DAT_0804d1c0;
          if (*(uint *)(DAT_0804d1b8 + param_1 * 0x10 + 0xc) >> 2 != 0) {
            iVar2 = DAT_08054294;
          }
          iVar2 = *(int *)(DAT_0804d1b8 + param_1 * 0x10 + 4) + iVar2;
        }
        else {
          iVar2 = 0;
          FUN_08037bec(3);
          FUN_08015a50();
        }
      }
      else {
        uVar6 = DAT_0805429c;
        if (true) {
          uVar6 = *(uint *)(DAT_0804d1b4 + 8);
        }
        if (uVar6 < uVar7) {
          iVar2 = 0;
          FUN_08037bec(3);
          FUN_08015a50();
        }
        else {
          if (true) {
            iVar3 = *(int *)(DAT_0804d1b4 + 4);
            *(uint *)(DAT_0804d1b4 + 4) = iVar3 + uVar7;
            *(uint *)(iVar2 + 8) = uVar6 - uVar7;
          }
          else {
            DAT_0805429c = uVar6 - uVar7;
            DAT_08054298 = DAT_08054298 + uVar7;
            iVar2 = param_1 * 0x10 + 0xc;
            *(uint *)(DAT_0804d1b8 + iVar2) = *(uint *)(DAT_0804d1b8 + iVar2) | DAT_08054290;
          }
          iVar5 = param_1 * 0x10 + 4;
          *(int *)(iVar4 + iVar5) = iVar3;
          *(uint *)(iVar4 + param_1 * 0x10 + 8) = uVar7;
          *piVar8 = 1;
          iVar2 = DAT_0804d1c0;
          if (false) {
            iVar2 = *(int *)(iVar4 + iVar5);
            iVar3 = DAT_08054294;
          }
          iVar2 = iVar2 + iVar3;
        }
        FUN_08007bec();
      }
      FUN_08037bec(3);
      return iVar2;
    }
    ((code*)DAT_0804cd60)("smem.c",0x15f,0x302f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_080379bc();
  FUN_08037a34();
  if (param_1 == 4) {
    if (param_2 == 8) {
      iVar4 = 0x20d0;
      iVar2 = DAT_0804d1c0;
      goto LAB_08037562;
    }
  }
  else {
    iVar2 = 0;
    while( true ) {
      uVar1 = *(ushort *)(DAT_0804d1bc + iVar2 * 8);
      if ((uVar1 == 0x1de) || (uVar1 == param_1)) break;
      iVar2 = iVar2 + 1;
    }
    if ((uVar1 == param_1) && (*(int *)(DAT_0804d1bc + iVar2 * 8 + 4) == param_2)) {
      iVar2 = FUN_08037758(param_1);
      iVar4 = DAT_0804d1c0;
LAB_08037562:
      return iVar2 + iVar4;
    }
  }
  return 0;
}




/* 0x080373b8 */
int FUN_080373b8(param_1, param_2)
uint param_1; int param_2;
{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int *piVar8;
  
  if (DAT_0804d1d0 == '\x01') {
    return 0;
  }
  if (8 < param_1) {
    if (8 < param_1) {
      if (DAT_0804d1d0 == '\0') {
        FUN_08037868();
      }
      if (0x1dd < param_1) {
        FUN_08015a50();
      }
      uVar7 = param_2 + 7U & 0xfffffff8;
      FUN_08037be8(3);
      iVar3 = DAT_08054298;
      iVar4 = DAT_0804d1b8;
      iVar2 = DAT_0804d1b4;
      piVar8 = (int *)(DAT_0804d1b8 + param_1 * 0x10);
      if (*piVar8 == 1) {
        if (*(uint *)(DAT_0804d1b8 + param_1 * 0x10 + 8) == uVar7) {
          iVar2 = DAT_0804d1c0;
          if (*(uint *)(DAT_0804d1b8 + param_1 * 0x10 + 0xc) >> 2 != 0) {
            iVar2 = DAT_08054294;
          }
          iVar2 = *(int *)(DAT_0804d1b8 + param_1 * 0x10 + 4) + iVar2;
        }
        else {
          iVar2 = 0;
          FUN_08037bec(3);
          FUN_08015a50();
        }
      }
      else {
        uVar6 = DAT_0805429c;
        if (true) {
          uVar6 = *(uint *)(DAT_0804d1b4 + 8);
        }
        if (uVar6 < uVar7) {
          iVar2 = 0;
          FUN_08037bec(3);
          FUN_08015a50();
        }
        else {
          if (true) {
            iVar3 = *(int *)(DAT_0804d1b4 + 4);
            *(uint *)(DAT_0804d1b4 + 4) = iVar3 + uVar7;
            *(uint *)(iVar2 + 8) = uVar6 - uVar7;
          }
          else {
            DAT_0805429c = uVar6 - uVar7;
            DAT_08054298 = DAT_08054298 + uVar7;
            iVar2 = param_1 * 0x10 + 0xc;
            *(uint *)(DAT_0804d1b8 + iVar2) = *(uint *)(DAT_0804d1b8 + iVar2) | DAT_08054290;
          }
          iVar5 = param_1 * 0x10 + 4;
          *(int *)(iVar4 + iVar5) = iVar3;
          *(uint *)(iVar4 + param_1 * 0x10 + 8) = uVar7;
          *piVar8 = 1;
          iVar2 = DAT_0804d1c0;
          if (false) {
            iVar2 = *(int *)(iVar4 + iVar5);
            iVar3 = DAT_08054294;
          }
          iVar2 = iVar2 + iVar3;
        }
        FUN_08007bec();
      }
      FUN_08037bec(3);
      return iVar2;
    }
    ((code*)DAT_0804cd60)("smem.c",0x15f,0x302f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_080379bc();
  FUN_08037a34();
  if (param_1 == 4) {
    if (param_2 == 8) {
      iVar4 = 0x20d0;
      iVar2 = DAT_0804d1c0;
      goto LAB_08037562;
    }
  }
  else {
    iVar2 = 0;
    while( true ) {
      uVar1 = *(ushort *)(DAT_0804d1bc + iVar2 * 8);
      if ((uVar1 == 0x1de) || (uVar1 == param_1)) break;
      iVar2 = iVar2 + 1;
    }
    if ((uVar1 == param_1) && (*(int *)(DAT_0804d1bc + iVar2 * 8 + 4) == param_2)) {
      iVar2 = FUN_08037758(param_1);
      iVar4 = DAT_0804d1c0;
LAB_08037562:
      return iVar2 + iVar4;
    }
  }
  return 0;
}




/* 0x0803758c */
void thunk_FUN_0803758c()
{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  
  FUN_080379bc();
  uVar1 = thunk_FUN_08037940();
  FUN_08006cd0(DAT_0804d1c0,uVar1);
  iVar2 = FUN_08037758(2);
  iVar4 = DAT_0804d1bc;
  iVar8 = 0;
  iVar2 = iVar2 + DAT_0804d1c0;
  iVar3 = 0;
  DAT_0804d1b8 = iVar2;
  while (uVar7 = (uint)*(ushort *)(iVar4 + iVar3 * 8), uVar7 != 0x1de) {
    *(int *)(iVar2 + uVar7 * 0x10 + 4) = iVar8;
    iVar9 = iVar3 * 8 + 4;
    *(undefined4 *)(iVar2 + uVar7 * 0x10 + 8) = *(undefined4 *)(iVar4 + iVar9);
    *(undefined4 *)(iVar2 + uVar7 * 0x10) = 1;
    iVar3 = iVar3 + 1;
    iVar8 = iVar8 + *(int *)(iVar4 + iVar9);
  }
  iVar4 = FUN_08037758(8);
  DAT_0804d1cc = iVar4 + DAT_0804d1c0;
  FUN_08007bec();
  FUN_08037820();
  smem_init();
  FUN_08037964();
  DAT_0804d1d0 = 2;
  iVar4 = FUN_08037bee(3,0xb2002,0xffff0000);
  if (iVar4 == 0) {
    FUN_08015a50();
  }
  puVar5 = (undefined4 *)FUN_080373b8(0x1a3,0x10);
  if (puVar5 == (undefined4 *)0x0) {
    FUN_08015a50();
  }
  *puVar5 = 5;
  puVar5[1] = 8;
  iVar4 = FUN_080373b8(0x1a4,0x294);
  if (iVar4 == 0) {
    FUN_08015a50();
  }
  uVar7 = 0;
  do {
    uVar6 = uVar7 + 1;
    *(undefined4 *)(iVar4 + uVar7 * 0x2c + 0x1c) = 0xffffffff;
    uVar7 = uVar6;
  } while (uVar6 < 0xf);
  FUN_08007bec();
  return;
}




/* 0x0803758c */
void FUN_0803758c()
{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  
  FUN_080379bc();
  uVar1 = thunk_FUN_08037940();
  FUN_08006cd0(DAT_0804d1c0,uVar1);
  iVar2 = FUN_08037758(2);
  iVar4 = DAT_0804d1bc;
  iVar8 = 0;
  iVar2 = iVar2 + DAT_0804d1c0;
  iVar3 = 0;
  DAT_0804d1b8 = iVar2;
  while (uVar7 = (uint)*(ushort *)(iVar4 + iVar3 * 8), uVar7 != 0x1de) {
    *(int *)(iVar2 + uVar7 * 0x10 + 4) = iVar8;
    iVar9 = iVar3 * 8 + 4;
    *(undefined4 *)(iVar2 + uVar7 * 0x10 + 8) = *(undefined4 *)(iVar4 + iVar9);
    *(undefined4 *)(iVar2 + uVar7 * 0x10) = 1;
    iVar3 = iVar3 + 1;
    iVar8 = iVar8 + *(int *)(iVar4 + iVar9);
  }
  iVar4 = FUN_08037758(8);
  DAT_0804d1cc = iVar4 + DAT_0804d1c0;
  FUN_08007bec();
  FUN_08037820();
  smem_init();
  FUN_08037964();
  DAT_0804d1d0 = 2;
  iVar4 = FUN_08037bee(3,0xb2002,0xffff0000);
  if (iVar4 == 0) {
    FUN_08015a50();
  }
  puVar5 = (undefined4 *)FUN_080373b8(0x1a3,0x10);
  if (puVar5 == (undefined4 *)0x0) {
    FUN_08015a50();
  }
  *puVar5 = 5;
  puVar5[1] = 8;
  iVar4 = FUN_080373b8(0x1a4,0x294);
  if (iVar4 == 0) {
    FUN_08015a50();
  }
  uVar7 = 0;
  do {
    uVar6 = uVar7 + 1;
    *(undefined4 *)(iVar4 + uVar7 * 0x2c + 0x1c) = 0xffffffff;
    uVar7 = uVar6;
  } while (uVar6 < 0xf);
  FUN_08007bec();
  return;
}




/* 0x08037688 */
uint FUN_08037688(param_1, param_2)
uint param_1; int * param_2;
{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  if (8 < param_1) {
    if (DAT_0804d1d0 == '\0') {
      FUN_08037868();
    }
    if (0x1dd < param_1) {
      FUN_08015a50();
    }
    FUN_08037be8(3);
    if (*(int *)(DAT_0804d1b8 + param_1 * 0x10) == 1) {
      *param_2 = *(int *)(DAT_0804d1b8 + param_1 * 0x10 + 8);
      uVar3 = DAT_0804d1c0;
      if (*(uint *)(DAT_0804d1b8 + param_1 * 0x10 + 0xc) >> 2 != 0) {
        uVar3 = DAT_08054294;
      }
      uVar3 = *(int *)(DAT_0804d1b8 + param_1 * 0x10 + 4) + uVar3;
    }
    else {
      uVar3 = 0;
      *param_2 = 0;
    }
    FUN_08037bec(3);
    if ((uVar3 != 0) && (*(int *)(DAT_0804d1b8 + param_1 * 0x10 + 0xc) == 0)) {
      iVar4 = thunk_FUN_08037940();
      if ((uVar3 < DAT_0804d1c0) ||
         ((iVar4 + DAT_0804d1c0 <= uVar3 || (iVar4 + DAT_0804d1c0 <= *param_2 + uVar3)))) {
        uVar3 = 0;
        *param_2 = 0;
      }
    }
    return uVar3;
  }
  iVar4 = FUN_080377d0();
  *param_2 = iVar4;
  FUN_080379bc();
  FUN_08037a34();
  if (param_1 == 4) {
    if (iVar4 == 8) {
      uVar5 = 0x20d0;
      uVar3 = DAT_0804d1c0;
      goto LAB_08037562;
    }
  }
  else {
    iVar2 = 0;
    while( true ) {
      uVar1 = *(ushort *)(DAT_0804d1bc + iVar2 * 8);
      if ((uVar1 == 0x1de) || (uVar1 == param_1)) break;
      iVar2 = iVar2 + 1;
    }
    if ((uVar1 == param_1) && (*(int *)(DAT_0804d1bc + iVar2 * 8 + 4) == iVar4)) {
      uVar3 = FUN_08037758(param_1);
      uVar5 = DAT_0804d1c0;
LAB_08037562:
      return uVar3 + uVar5;
    }
  }
  return 0;
}




/* 0x08037748 */
undefined4 FUN_08037748()
{
  FUN_080379bc();
  return DAT_0804d1c0;
}




/* 0x08037758 */
int FUN_08037758(param_1)
uint param_1;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar2 = 0;
  while ((uVar3 = (uint)*(ushort *)(DAT_0804d1bc + iVar2 * 8), uVar3 != 0x1de && (uVar3 != param_1))
        ) {
    iVar1 = iVar2 * 8;
    iVar2 = iVar2 + 1;
    iVar4 = iVar4 + *(int *)(DAT_0804d1bc + iVar1 + 4);
  }
  if ((ushort)(&DAT_080396e4)[iVar2 * 4] != param_1) {
    FUN_08015a50();
  }
  return iVar4;
}




/* 0x0803779c */
int FUN_0803779c()
{
  if (DAT_0804d1c4 != -1) {
    return DAT_0804d1c4;
  }
  DAT_0804d1c4 = thunk_FUN_0803791c();
  return DAT_0804d1c4;
}




/* 0x080377b8 */
undefined4 FUN_080377b8()
{
  if (DAT_0804d1c8 == 0) {
    DAT_0804d1c8 = thunk_FUN_08037940();
  }
  return 0;
}




/* 0x080377d0 */
undefined4 FUN_080377d0(param_1)
uint param_1;
{
  uint uVar1;
  
  uVar1 = 0;
  do {
    if (*(ushort *)(DAT_0804d1bc + uVar1 * 8) == param_1) break;
    uVar1 = uVar1 + 1;
  } while (uVar1 < 9);
  if (*(short *)(DAT_0804d1bc + uVar1 * 8) != 0x1de) {
    return *(undefined4 *)(DAT_0804d1bc + uVar1 * 8 + 4);
  }
  ((code*)DAT_0804cd60)("smem.c",0x238,0x302f);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




