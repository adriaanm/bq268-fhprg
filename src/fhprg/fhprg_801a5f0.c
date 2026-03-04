/* Auto-generated: fhprg_801a5f0.c */
/* Functions: 39 */
#include "globals.h"

/* 0x0801a5f0 */
void FUN_0801a5f0(param_1)
int param_1;
{
  FUN_0802fc18();
  FUN_0802fcd0(param_1,0);
  *(undefined1 *)(param_1 + 0x28) = 0;
  FUN_08030320(*(undefined4 *)(param_1 + 0xc));
  *(undefined4 *)(param_1 + 0x70) = 3;
  *(undefined4 *)(param_1 + 0x38) = 3;
  return;
}




/* 0x0801a614 */
int FUN_0801a614(param_1, param_2)
int param_1; byte * param_2;
{
  bool bVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  
  if ((param_1 == 0) || (param_2 == (byte *)0x0)) {
    FUN_08030ac4(0xb9,0,0x2e7);
    iVar3 = FUN_08030af4();
    return iVar3;
  }
  bVar2 = *param_2 & 0x1f;
  if ((*param_2 & 0x1f) == 0) {
    iVar3 = FUN_080252f0(param_1);
  }
  else if (bVar2 == 1) {
    iVar3 = FUN_0802544c(param_1);
  }
  else {
    if (bVar2 != 2) goto LAB_0801a682;
    iVar3 = FUN_080253ba(param_1);
  }
  if (iVar3 < 1) {
    if (iVar3 != 0) {
      if (-1 < iVar3) {
        return iVar3;
      }
LAB_0801a682:
      iVar3 = FUN_080303c4(*(undefined4 *)(param_1 + 0xc),0);
      return iVar3;
    }
    uVar4 = *(undefined4 *)(param_1 + 0x30);
    iVar3 = 0;
    bVar1 = true;
  }
  else {
    uVar4 = *(undefined4 *)(param_1 + 0x30);
    iVar3 = 10;
    bVar1 = false;
  }
  iVar5 = -1;
  if (bVar1) {
    param_1 = param_1 + 0x34;
  }
  else {
    param_1 = param_1 + 0x6c;
  }
  if (*(int *)(param_1 + 4) != 1) {
    *(undefined4 *)(param_1 + 0x14) = uVar4;
    *(int *)(param_1 + 0x18) = iVar3;
    iVar5 = FUN_08030b04();
    if (-1 < iVar5) {
      return iVar3;
    }
  }
  return iVar5;
}




/* 0x0801a69e */
void FUN_0801a69e(param_1)
int param_1;
{
  if (*(code **)(param_1 + 0x10) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0801a6a4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(param_1 + 0x10))();
    return;
  }
  return;
}




/* 0x0801a6a8 */
undefined4 FUN_0801a6a8(param_1, param_2, param_3)
int param_1; uint param_2; uint param_3;
{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar2 = *(int *)(*(int *)(param_1 + 0xc) + 4);
  if ((*(byte *)(iVar2 + 2) == param_2) && (*(byte *)(iVar2 + 3) == param_3)) {
    for (puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xc) + 0xc); puVar3 != (undefined4 *)0x0;
        puVar3 = (undefined4 *)*puVar3) {
      iVar2 = puVar3[1];
      FUN_0802fff8(*(undefined4 *)(*(int *)(param_1 + 8) + 0xc),*(byte *)(iVar2 + 2) & 0xf,
                   *(byte *)(iVar2 + 2) >> 7,*(byte *)(iVar2 + 3) & 3,*(undefined2 *)(iVar2 + 4),0);
    }
    uVar1 = 0;
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}




/* 0x0801a6fa */
void FUN_0801a6fa(param_1, param_2)
int param_1; undefined4 param_2;
{
  *(undefined4 *)(param_1 + 0x20) = param_2;
  FUN_0801a69e(param_1,4);
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0801a704 */
int FUN_0801a704(param_1)
int param_1;
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = _DAT_0184103c;
  iVar2 = _DAT_01841034;
  iVar1 = _DAT_01841000;
  if (param_1 == 0) {
    _DAT_01841000 = 1;
    return iVar1;
  }
  if (param_1 != 1) {
    if (param_1 == 2) {
      _DAT_01841034 = 1;
      param_1 = iVar2;
    }
    return param_1;
  }
  _DAT_0184103c = 1;
  return iVar3;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0801a728 */
int FUN_0801a728(param_1)
int param_1;
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = _DAT_0184103c;
  iVar2 = _DAT_01841034;
  iVar1 = _DAT_01841000;
  if (param_1 == 0) {
    _DAT_01841000 = 0;
    return iVar1;
  }
  if (param_1 != 1) {
    if (param_1 == 2) {
      _DAT_01841034 = 0;
      param_1 = iVar2;
    }
    return param_1;
  }
  _DAT_0184103c = 0;
  return iVar3;
}




/* 0x0801a754 */
int FUN_0801a754(param_1)
undefined4 param_1;
{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  bool bVar6;
  
  uVar3 = 1;
  iVar4 = 5;
  uVar5 = 0;
LAB_0801a854:
  bVar6 = 99 < uVar5;
  uVar5 = uVar5 + 1;
  if (bVar6) goto LAB_0801a85e;
  FUN_08030ac4(uVar3,0x83,0);
  if (uVar3 == 7) {
    iVar4 = 2;
  }
  else {
    if (uVar3 < 8) {
      if (uVar3 == 1) {
        FUN_0801aca8(param_1,1);
        FUN_0801ac76(param_1);
        FUN_0801ac52(param_1);
        FUN_0803056c(param_1,10,0,2);
        FUN_0803056c(param_1,10,0,4);
        FUN_0803056c(param_1,0x84,0x10);
        FUN_0803056c(param_1,0x84,0x20);
        FUN_080300bc(10);
        FUN_0803056c(param_1,10,4);
        uVar3 = 2;
        goto LAB_0801a854;
      }
      if (uVar3 != 2) {
        if (uVar3 == 5) {
          FUN_0801a970(param_1);
          cVar1 = FUN_0801ac44(param_1);
          FUN_0801a918(param_1);
          iVar2 = FUN_0803014c(param_1);
          if (iVar2 == 0) {
            if (cVar1 == '\0') {
              uVar3 = 9;
            }
            else if (cVar1 == '\x01') {
LAB_0801a8c8:
              uVar3 = 7;
            }
            else {
              uVar3 = 0x10;
            }
            goto LAB_0801a854;
          }
        }
        else {
          if (uVar3 != 6) goto LAB_0801a796;
          FUN_0801a970(param_1);
          cVar1 = FUN_0801ac44(param_1);
          FUN_0801a918(param_1);
          iVar2 = FUN_0803014c(param_1);
          if ((cVar1 != '\0') && (iVar2 == 0)) goto LAB_0801a8c8;
        }
        iVar4 = 3;
        goto LAB_0801a8b6;
      }
      cVar1 = '\0';
      do {
        iVar2 = FUN_08030528(param_1,0x87);
        if (iVar2 << 0x1e < 0) {
          FUN_080300bc(10);
          uVar3 = 5;
          goto LAB_0801a826;
        }
        FUN_080300bc(0x96);
        cVar1 = cVar1 + '\x01';
      } while (cVar1 != '\x0e');
      if (true) {
        uVar3 = 6;
      }
LAB_0801a826:
      FUN_0803056c(param_1,0x84,0,0x10);
      FUN_0803056c(param_1,0x84,0,0x20);
      FUN_0803056c(param_1,10,0,4);
      FUN_080300bc(10);
LAB_0801a850:
      if (uVar3 == 0x12) {
LAB_0801a85e:
        if ((99 < uVar5) && (uVar3 != 0x12)) {
          iVar4 = 4;
          FUN_0801ac76(param_1);
          FUN_0801ac52(param_1);
          FUN_0801aca8(param_1,0);
        }
        FUN_08030ac4(0x93,0,iVar4);
        return iVar4;
      }
      goto LAB_0801a854;
    }
    if (uVar3 == 9) {
      iVar4 = 0;
      goto LAB_0801a8b6;
    }
    if (uVar3 != 0x10) {
      if (uVar3 == 0x11) {
        FUN_0801ac76(param_1);
        FUN_0801ac52(param_1);
        FUN_0801aca8(param_1,0);
        if (iVar4 == 0) {
          FUN_08030354(param_1);
        }
        uVar3 = 0x12;
        goto LAB_0801a85e;
      }
      if (uVar3 == 0x12) goto LAB_0801a850;
    }
LAB_0801a796:
    iVar4 = 4;
  }
LAB_0801a8b6:
  uVar3 = 0x11;
  goto LAB_0801a854;
}




/* 0x0801a918 */
void FUN_0801a918(param_1)
undefined4 param_1;
{
  FUN_0801ac76();
  FUN_0801ac52(param_1);
  FUN_0803056c(param_1,0x84,0,2);
  FUN_0803056c(param_1,0x84,0,1);
  FUN_080300bc(0x32);
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0801a948 */
void FUN_0801a948(param_1)
undefined4 param_1;
{
  FUN_0803056c(param_1,0x96,3,0xff);
  _DAT_078d90a0 = _DAT_078d90a0 | 0x80;
  _DAT_078d9140 = _DAT_078d9140 | 0x2000000;
  return;
}




/* 0x0801a970 */
void FUN_0801a970(param_1)
undefined4 param_1;
{
  FUN_0801ac76();
  FUN_0801ac52(param_1);
  FUN_0803056c(param_1,0x84,2);
  FUN_0803056c(param_1,0x84,1);
  FUN_080300bc(0x32);
  return;
}




/* 0x0801a9a0 */
void FUN_0801a9a0(param_1)
int param_1;
{
                    /* WARNING: Could not recover jumptable at 0x0801a9b2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0804ded8 + 8))(*(undefined4 *)(param_1 * 0xc + -0x78389678));
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0801aa38 */
void FUN_0801aa38(param_1)
int param_1;
{
  uint uVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  
  uVar1 = _DAT_078d91bc;
  uVar7 = 0;
  do {
    uVar5 = 0;
    do {
      if ((uVar1 & 1 << (uVar7 + uVar5 * 0x10 & 0xff)) != 0) {
        thunk_FUN_080300ba(&DAT_87c74800 + uVar5 * 0x40 + uVar7 * 0x80,0x40);
        uVar6 = 0;
        iVar8 = 0;
        piVar2 = (int *)(uVar7 * 0x1040 + -0x7838b700 + uVar5 * 0x820);
        piVar3 = piVar2;
        do {
          thunk_FUN_080300ba(piVar3,0x20);
          iVar8 = iVar8 + ((uint)piVar3[1] >> 0x10);
          if (uVar6 == 0) {
            uVar6 = piVar3[1] & 0xff;
          }
        } while ((*piVar3 != 1) && (piVar3 = (int *)*piVar3, piVar3 != (int *)0x0));
        iVar4 = piVar2[7];
        *(int *)(iVar4 + 0x1c) = *(int *)(iVar4 + 0x18) - iVar8;
        thunk_FUN_080300ba(*(undefined4 *)(iVar4 + 0x14));
        if (uVar6 == 0) {
          *(undefined4 *)(iVar4 + 4) = 2;
          if (*(code **)(iVar4 + 0x24) != (code *)0x0) {
            (**(code **)(iVar4 + 0x24))(iVar4);
          }
          if (*(char *)(*(int *)(param_1 * 0xc + -0x78389678) + 0xa4) == '\x01') {
            FUN_08030100();
          }
        }
        else if (uVar6 == 0x80) {
          *(undefined4 *)(iVar4 + 4) = 1;
        }
        else {
          *(undefined4 *)(iVar4 + 4) = 3;
          if (*(code **)(iVar4 + 0x24) != (code *)0x0) {
            (**(code **)(iVar4 + 0x24))(iVar4);
          }
        }
      }
      uVar5 = uVar5 + 1 & 0xff;
    } while (uVar5 < 2);
    uVar7 = uVar7 + 1 & 0xff;
  } while (uVar7 < 2);
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0801ab18 */
void FUN_0801ab18()
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  FUN_08006d14(&DAT_87c74800,0x100);
  FUN_08006d14(0x87c74900,0x2080);
  iVar3 = 0;
  do {
    iVar2 = 0;
    do {
      iVar4 = iVar3 * 0x1040 + -0x7838b700 + iVar2 * 0x820;
      *(int *)(iVar3 * 0x80 + iVar2 * 0x40 + -0x7838b7f8) = iVar4;
      iVar1 = 0;
      do {
        *(undefined4 *)(iVar4 + iVar1 * 0x20) = 1;
        iVar1 = iVar1 + 1;
      } while (iVar1 < 0x40);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 2);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 2);
  _DAT_87c74840 = 0x400000;
  _DAT_87c74800 = 0x408000;
  thunk_FUN_080300b8(&DAT_87c74800,0x100);
  thunk_FUN_080300b8(0x87c74900,0x2080);
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0801aba0 */
void FUN_0801aba0(param_1)
undefined4 param_1;
{
  DAT_87c76984 = 2;
  thunk_FUN_0800a80c();
  FUN_0801a704(0);
  FUN_0801a704(1);
  thunk_FUN_080199b4(10);
  FUN_0801a728(1);
  thunk_FUN_080199b4(0x4b);
  FUN_0801a728(0);
  thunk_FUN_080199b4(10);
  thunk_FUN_0800abf4();
  _DAT_078d9184 = 0x80000000;
  FUN_0801a704(2);
  FUN_0803056c(param_1,0x80,0x33,0xff);
  FUN_0803056c(param_1,0x81,0x33,0xff);
  FUN_0803056c(param_1,0x82,7,0xff);
  FUN_0803056c(param_1,0x83,0x13,0xff);
  thunk_FUN_080199b4(10);
  FUN_0801a728(2);
  thunk_FUN_080199b4(0x4b);
  FUN_0801a948(param_1);
  return;
}




/* 0x0801ac40 */
undefined4 FUN_0801ac40()
{
  return 0;
}




/* 0x0801ac44 */
uint FUN_0801ac44(param_1)
undefined4 param_1;
{
  uint uVar1;
  
  uVar1 = FUN_08030528(param_1,0x87);
  return uVar1 & 1;
}




/* 0x0801ac52 */
void FUN_0801ac52(param_1)
undefined4 param_1;
{
  FUN_0803056c(param_1,0x91,0,0xff);
  FUN_0803056c(param_1,0x93,0,0xff);
  thunk_FUN_080199b4(100);
  return;
}




/* 0x0801ac76 */
void FUN_0801ac76(param_1)
undefined4 param_1;
{
  FUN_0803056c(param_1,0x84,0,0xff);
  FUN_0803056c(param_1,0x87,0,0xff);
  thunk_FUN_080199b4(100);
  return;
}




/* 0x0801ac9c */
void FUN_0801ac9c(param_1)
undefined1 param_1;
{
  DAT_0804ded0 = param_1;
  return;
}




/* 0x0801ac9c */
void thunk_FUN_0801ac9c(param_1)
undefined1 param_1;
{
  DAT_0804ded0 = param_1;
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0801aca8 */
void FUN_0801aca8(param_1, param_2)
undefined4 param_1; int param_2;
{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    if (param_2 != 1) {
      return;
    }
    uVar1 = 8;
  }
  FUN_0803056c(param_1,4,uVar1,0x18);
  return;
}




/* 0x0801acc0 */
undefined4 FUN_0801acc0(param_1)
undefined4 param_1;
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 extraout_r3;
  
  if (DAT_0804dee8 == -1) {
    FUN_0803030c(param_1,0,&DAT_0804dee8,param_1);
    FUN_08030678(extraout_r3,0,0);
  }
  if (DAT_0804dee8 == 0xabcdef) {
    FUN_08030ac4(0x7d,0,1);
    uVar1 = 0x7f;
LAB_0801ad18:
    FUN_08030ac4(uVar1,0);
    return 1;
  }
  if (DAT_0804dee8 == 0x123456) {
    FUN_08030ac4(0x7d,0,1);
    if (DAT_0804ded0 != '\x01') {
      uVar1 = 0x80;
      goto LAB_0801ad18;
    }
    uVar2 = 1;
    uVar1 = 0x81;
  }
  else {
    uVar2 = 0;
    uVar1 = 0x7d;
  }
  FUN_08030ac4(uVar1,0,uVar2);
  return 0;
}




/* 0x0801ad44 */
undefined4 thunk_FUN_0801ad44()
{
  FUN_0801ad44();
  return 0;
}




/* 0x0801ad44 */
undefined4 FUN_0801ad44(param_1, param_2, param_3, param_4, param_5)
int param_1; int param_2; int param_3; int param_4; undefined4 param_5;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  uint local_48;
  uint uStack_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint uStack_34;
  uint local_30;
  uint local_2c;
  
  uVar5 = 0;
  iVar7 = 0;
  thunk_FUN_00222448(&local_58);
  iVar1 = 0;
  if (param_3 == 0) {
    uVar6 = local_48;
    iVar2 = local_58;
    if (((param_4 == 1) || (uVar6 = local_40, iVar2 = local_54, param_4 == 2)) ||
       (uVar6 = uVar5, iVar2 = iVar7, param_4 != 3)) goto LAB_0801adca;
    if (uStack_44 <= local_3c && (uint)(local_40 <= local_48) <= uStack_44 - local_3c) {
      local_40 = local_48;
    }
  }
  else {
    uVar6 = uVar5;
    iVar2 = iVar7;
    if (((param_3 != 1) || (uVar6 = local_38, iVar2 = local_50, param_4 == 1)) ||
       ((uVar6 = local_30, iVar2 = local_4c, param_4 == 2 ||
        (uVar6 = uVar5, iVar2 = iVar7, param_4 != 3)))) goto LAB_0801adca;
    local_58 = local_50;
    local_54 = local_4c;
    local_40 = local_30;
    if (uStack_34 <= local_2c && (uint)(local_30 <= local_38) <= uStack_34 - local_2c) {
      local_40 = local_38;
    }
  }
  uVar6 = local_40;
  iVar2 = local_58 + local_54;
LAB_0801adca:
  uVar5 = iVar2 * 0x100000;
  if (uVar5 == 0) {
    iVar1 = 1;
  }
  else {
    uVar4 = uVar5 - 1;
    DAT_08052c98 = "Testing Memory Map.";
    if ((((uVar5 & uVar4) == 0) && (2 < uVar4)) && ((uVar6 & uVar4) == 0)) {
      if (DAT_0804cecc < uVar6 + uVar5) {
        if (uVar6 < DAT_0804cecc) {
          uVar5 = uVar5 - (DAT_0804cecc - uVar6);
          uVar6 = DAT_0804cecc;
        }
        if (param_1 != 0) {
          if (param_1 == 1) {
            iVar7 = uVar5 - 1;
            iVar1 = 0;
            DAT_08052c98 = "Testing DDR Read/Write.";
            if (param_2 == 0) {
              iVar2 = FUN_0801b010(uVar6,iVar7);
              if (iVar2 == 0) {
                iVar1 = 3;
              }
              else {
                iVar7 = FUN_0801aee4(uVar6,iVar7);
                if (iVar7 == 0) {
                  iVar1 = 4;
                }
              }
            }
            else if (param_2 == 1) {
              iVar7 = FUN_0801b1e4(uVar6,iVar7);
              if (iVar7 == 0) {
                iVar1 = 5;
              }
            }
            else {
              iVar7 = FUN_0801b460();
              if (iVar7 == 0) {
                iVar1 = 6;
              }
            }
          }
          else if (param_1 == 2) {
            iVar1 = FUN_0801b2c8(param_2,param_3,param_4,uVar6,uVar5 - 1,param_5);
          }
          else if (param_1 == 3) {
            iVar1 = FUN_0801b0ac(param_2,param_3,param_4,uVar6,uVar5 - 1,param_5);
          }
        }
      }
    }
    else {
      iVar1 = 2;
    }
  }
  DAT_08052c9c = iVar1;
  if ((iVar1 == 0) || (iVar1 == 1)) {
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}




/* 0x0801aee4 */
undefined4 FUN_0801aee4(param_1, param_2)
undefined4 * param_1; uint param_2;
{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_98 [33];
  
  FUN_08006d14(local_98,0x80);
  DAT_08052c98 = "Testing DDR Read/Write: Entering Address lines.";
  iVar3 = 1;
  for (uVar1 = 1; uVar1 <= param_2 >> 2; uVar1 = uVar1 << 1) {
    local_98[iVar3] = param_1[uVar1];
    param_1[uVar1] = ~uVar1;
    iVar3 = iVar3 + 1;
  }
  uVar2 = *param_1;
  *param_1 = 0xffffffff;
  uVar1 = 1;
  iVar3 = 1;
  while( true ) {
    if (param_2 >> 2 < uVar1) {
      DAT_08052c98 = "Testing DDR Read/Write: Exiting Address lines.";
      *param_1 = uVar2;
      return 1;
    }
    if (param_1[uVar1] != ~uVar1) break;
    param_1[uVar1] = local_98[iVar3];
    uVar1 = uVar1 << 1;
    iVar3 = iVar3 + 1;
  }
  DAT_08052ca0 = param_1 + uVar1;
  DAT_08052ca4 = ~uVar1;
  return 0;
}




/* 0x0801afc4 */
undefined4 thunk_FUN_0801afc4()
{
  FUN_0801afc4();
  return 0;
}




/* 0x0801afc4 */
undefined4 FUN_0801afc4(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  int iVar1;
  
  iVar1 = FUN_0801ad44(param_1,param_2,0,1,param_3);
  if (iVar1 != 0) {
    iVar1 = FUN_0801ad44(param_1,param_2,0,2,param_3);
    if (iVar1 != 0) {
      iVar1 = FUN_0801ad44(param_1,param_2,1,1,param_3);
      if (iVar1 != 0) {
        iVar1 = FUN_0801ad44(param_1,param_2,1,2,param_3);
        if (iVar1 != 0) {
          return 1;
        }
      }
    }
  }
  return 0;
}




/* 0x0801b010 */
undefined4 FUN_0801b010(param_1, param_2)
uint * param_1; uint param_2;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  DAT_08052c98 = "Testing DDR Read/Write: Entering Data lines.";
  param_2 = param_2 >> 2;
  uVar2 = *param_1;
  uVar3 = param_1[param_2];
  uVar1 = 1;
  do {
    *param_1 = uVar1;
    param_1[param_2] = ~uVar1;
    if (*param_1 != uVar1) {
      DAT_08052ca0 = param_1;
      DAT_08052ca4 = uVar1;
      return 0;
    }
    uVar1 = uVar1 << 1;
  } while (uVar1 != 0);
  DAT_08052c98 = "Testing DDR Read/Write: Exiting Data lines.";
  *param_1 = uVar2;
  param_1[param_2] = uVar3;
  return 1;
}




/* 0x0801b0ac */
undefined4 FUN_0801b0ac(param_1, param_2, param_3, param_4, param_5, param_6)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4; undefined4 param_5; undefined4 param_6;
{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  DAT_08052c98 = "Testing DDR Deep Power Down.";
  while (param_1 != 0) {
    param_1 = param_1 + -1;
    DAT_08052c98 = "Testing DDR Deep Power Down: Entering deep power down.";
    thunk_FUN_0022208c(param_2,param_3);
    uVar1 = 0;
    do {
      uVar4 = 0;
      do {
        uVar1 = uVar1 + 1;
        uVar4 = uVar4 + 1;
      } while (uVar4 < 100000000);
      uVar1 = (uVar1 - uVar4) + 1;
    } while (uVar1 < 10);
    DAT_08052c98 = "Testing DDR Deep Power Down: Exiting deep power down.";
    thunk_FUN_00222168(param_2,param_3,param_6);
  }
  iVar2 = FUN_0801b1e4(param_4,param_5);
  if (iVar2 == 0) {
    uVar3 = 8;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}




/* 0x0801b1e4 */
undefined4 FUN_0801b1e4(param_1, param_2)
int param_1; uint param_2;
{
  uint uVar1;
  uint uVar2;
  
  DAT_08052c98 = "Testing DDR Read/Write: Entering Own-address algorithm.";
  param_2 = param_2 >> 2;
  for (uVar2 = 0; uVar2 <= param_2; uVar2 = uVar2 + 1) {
    *(uint *)(param_1 + uVar2 * 4) = uVar2;
  }
  for (uVar2 = 0; uVar2 <= param_2; uVar2 = uVar2 + 1) {
    uVar1 = uVar2;
    if (*(uint *)(param_1 + uVar2 * 4) != uVar2) goto LAB_0801b240;
  }
  for (uVar2 = 0; uVar2 <= param_2; uVar2 = uVar2 + 1) {
    *(uint *)(param_1 + uVar2 * 4) = ~uVar2;
  }
  uVar2 = 0;
  while( true ) {
    if (param_2 < uVar2) {
      DAT_08052c98 = "Testing DDR Read/Write: Exiting Own-address algorithm.";
      return 1;
    }
    if (*(uint *)(param_1 + uVar2 * 4) != ~uVar2) break;
    uVar2 = uVar2 + 1;
  }
  uVar1 = ~uVar2;
LAB_0801b240:
  DAT_08052ca4 = uVar1;
  DAT_08052ca0 = param_1 + uVar2 * 4;
  return 0;
}




/* 0x0801b2c8 */
undefined4 FUN_0801b2c8(param_1, param_2, param_3, param_4, param_5, param_6)
int param_1; undefined4 param_2; undefined4 param_3; int param_4; uint param_5; undefined4 param_6;
{
  uint uVar1;
  uint uVar2;
  
  for (uVar1 = 0; uVar1 <= param_5 >> 2; uVar1 = uVar1 + 1) {
    *(uint *)(param_4 + uVar1 * 4) = uVar1;
  }
  while (param_1 != 0) {
    param_1 = param_1 + -1;
    DAT_08052c98 = "Testing DDR Self Refresh: Entering self refresh.";
    thunk_FUN_002220f8(param_2,param_3,param_6);
    uVar1 = 0;
    do {
      uVar2 = 0;
      do {
        uVar1 = uVar1 + 1;
        uVar2 = uVar2 + 1;
      } while (uVar2 < 100000000);
      uVar1 = (uVar1 - uVar2) + 1;
    } while (uVar1 < 10);
    DAT_08052c98 = "Testing DDR Self Refresh: Exiting self refresh.";
    thunk_FUN_002221d8(param_2,param_3,param_6);
  }
  DAT_08052c98 = "Testing DDR Self Refresh: Read pass.";
  uVar1 = 0;
  while( true ) {
    if (param_5 >> 2 < uVar1) {
      return 0;
    }
    if (*(uint *)(param_4 + uVar1 * 4) != uVar1) break;
    uVar1 = uVar1 + 1;
  }
  DAT_08052ca0 = param_4 + uVar1 * 4;
  DAT_08052ca4 = uVar1;
  return 7;
}




/* 0x0801b460 */
undefined4 FUN_0801b460(param_1, param_2)
int param_1; uint param_2;
{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = 1;
  do {
    iVar1 = iVar3;
    for (uVar2 = 0; uVar2 <= param_2 >> 2; uVar2 = uVar2 + 1) {
      *(int *)(param_1 + uVar2 * 4) = iVar1;
      iVar1 = iVar1 << 1;
      if (iVar1 == 0) {
        iVar1 = 1;
      }
    }
    DAT_08052c98 = "Testing DDR Read/Write: Walking-ones algorithm : Read Pass.";
    iVar1 = iVar3;
    for (uVar2 = 0; uVar2 <= param_2 >> 2; uVar2 = uVar2 + 1) {
      if (*(int *)(param_1 + uVar2 * 4) != iVar1) {
        DAT_08052ca0 = param_1 + uVar2 * 4;
        DAT_08052ca4 = iVar1;
        return 0;
      }
      iVar1 = iVar1 << 1;
      if (iVar1 == 0) {
        iVar1 = 1;
      }
    }
    iVar3 = iVar3 << 1;
  } while (iVar3 != 0);
  DAT_08052c98 = "Testing DDR Read/Write: Exiting Walking-ones algorithm.";
  return 1;
}




/* 0x0801b5b0 */
uint FUN_0801b5b0(param_1, param_2, param_3, param_4, param_5, param_6, param_7)
undefined4 param_1; undefined4 param_2; undefined4 param_3; uint param_4; undefined4 param_5; undefined4 param_6; undefined4 param_7;
{
  undefined1 uVar1;
  int iVar2;
  char *pcVar3;
  char cVar4;
  uint local_2c;
  
  cVar4 = '\0';
  if (DAT_08053fb8 == '\0') {
    return 0xe;
  }
  local_2c = param_4;
  FUN_0801b7d0(param_1,param_3,param_4,param_6,param_1,param_2,param_3);
  do {
    cVar4 = cVar4 + '\x01';
    iVar2 = FUN_0800dae8(param_1,param_2,param_3,param_4,param_5,param_6,param_7);
    local_2c = CONCAT31(_GHIDRA_FIELD(local_2c, 1, uint24_t),(char)iVar2);
    if (iVar2 == 0) break;
    iVar2 = FUN_0800ea18();
    if (iVar2 == 0) {
      uVar1 = 10;
LAB_0801b60a:
      local_2c = CONCAT31(_GHIDRA_FIELD(local_2c, 1, uint24_t),uVar1);
    }
    else {
      iVar2 = FUN_0800eae4();
      if (iVar2 == 0) {
        uVar1 = 9;
        goto LAB_0801b60a;
      }
    }
    iVar2 = FUN_0800eb12(&local_2c,param_1,param_3,param_4,cVar4);
  } while (iVar2 != 0);
  FUN_0801b6f8(param_1,param_3,param_4,param_6,param_5,cVar4,local_2c & 0xff);
  if ((local_2c & 0xff) == 8) {
    pcVar3 = "SPMI Fatal: Timeout while executing SPMI transaction";
  }
  else {
    if ((local_2c & 0xff) != 1) goto LAB_0801b658;
    pcVar3 = "SPMI Fatal: SPMI bus busy";
  }
  snprintf_buf(&DAT_08054ab4,0x80,pcVar3);
  boot_log_message(&DAT_08054ab4);
LAB_0801b658:
  return local_2c & 0xff;
}




/* 0x0801b6bc */
void FUN_0801b6bc(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uStack_c = param_2;
  uStack_8 = param_3;
  uStack_4 = param_4;
  FUN_08006418(&DAT_08058028 + DAT_08058428 * 0x20,0x20,param_1,&uStack_c);
  DAT_08058428 = DAT_08058428 + 1 & 0x1f;
  DAT_0805842c = 0;
  return;
}




/* 0x0801b6f8 */
void FUN_0801b6f8(param_1, param_2, param_3, param_4, param_5, param_6, param_7)
uint param_1; uint param_2; uint param_3; uint param_4; undefined1 * param_5; undefined1 param_6; uint param_7;
{
  int iVar1;
  uint uVar2;
  
  iVar1 = (uint)DAT_08053fc8 * 0x18;
  if (((((byte)(&DAT_08053fd6)[iVar1] == param_1) && ((byte)(&DAT_08053fd0)[iVar1] == param_2)) &&
      (*(ushort *)(&DAT_08053fd2 + iVar1) == param_3)) && ((byte)(&DAT_08053fd7)[iVar1] == param_4))
  {
    (&DAT_08053fe5)[iVar1] = 2;
    (&DAT_08053fd5)[(uint)DAT_08053fc8 * 0x18] = (char)param_7;
    (&DAT_08053fe4)[(uint)DAT_08053fc8 * 0x18] = param_6;
    iVar1 = FUN_0800eb0c();
    *(int *)(&DAT_08053fe0 + (uint)DAT_08053fc8 * 0x18) =
         iVar1 - *(int *)(&DAT_08053fd8 + (uint)DAT_08053fc8 * 0x18);
    if (param_5 != (undefined1 *)0x0) {
      (&DAT_08053fd4)[(uint)DAT_08053fc8 * 0x18] = *param_5;
    }
    if (param_7 < 0x1c) {
      *(short *)(&DAT_08054228 + param_7 * 2) = *(short *)(&DAT_08054228 + param_7 * 2) + 1;
    }
  }
  else {
    DAT_0805426c = 1;
  }
  if (param_7 != 0) {
    uVar2 = (DAT_08053fc9 + 1) % 5;
    DAT_08053fc9 = (byte)uVar2;
    FUN_08006bdc(uVar2 * 0x18 + 0x80540c0,&DAT_08053fd0 + (uint)DAT_08053fc8 * 0x18,0x18);
    if (true) {
      DAT_08054260 = *(undefined4 *)(DAT_0804d44c + 0xb000);
      DAT_08054264 = *(undefined4 *)(DAT_0804d44c + 0xa02c);
      DAT_08054268 = *(undefined4 *)(DAT_0804d44c + 41000);
    }
    return;
  }
  return;
}




/* 0x0801b7d0 */
void FUN_0801b7d0(param_1, param_2, param_3, param_4)
undefined1 param_1; undefined1 param_2; undefined2 param_3; undefined1 param_4;
{
  uint uVar1;
  undefined8 uVar2;
  
  uVar1 = (DAT_08053fc8 + 1) % 10;
  DAT_08053fc8 = (byte)uVar1;
  (&DAT_08053fe5)[uVar1 * 0x18] = 1;
  (&DAT_08053fd6)[(uint)DAT_08053fc8 * 0x18] = param_1;
  (&DAT_08053fd0)[(uint)DAT_08053fc8 * 0x18] = param_2;
  *(undefined2 *)(&DAT_08053fd2 + (uint)DAT_08053fc8 * 0x18) = param_3;
  (&DAT_08053fd7)[(uint)DAT_08053fc8 * 0x18] = param_4;
  (&DAT_08053fe4)[(uint)DAT_08053fc8 * 0x18] = 0;
  uVar2 = FUN_0800eb0c();
  *(undefined8 *)(&DAT_08053fd8 + (uint)DAT_08053fc8 * 0x18) = uVar2;
  return;
}




/* 0x0801b850 */
void FUN_0801b850(param_1)
int param_1;
{
  FUN_080199b4(param_1 * 1000);
  return;
}




/* 0x0801b85c */
void FUN_0801b85c()
{
  int iVar1;
  int extraout_r3;
  
  FUN_08022440();
  do {
    iVar1 = FUN_08022440();
  } while (iVar1 < extraout_r3);
  return;
}




