/* Auto-generated: fhprg_801ce50.c */
/* Functions: 17 */
#include "globals.h"

/* 0x0801ce50 */
uint thunk_FUN_0801ce50(param_1, param_2, param_3)
undefined4 param_1; int param_2; undefined4 param_3;
{
  uint uVar1;
  undefined4 extraout_r1;
  int iVar2;
  uint uVar3;
  longlong lVar4;
  
  FUN_08020d4c();
  lVar4 = FUN_0801ce8c(param_1,extraout_r1,param_2,param_2 >> 0x1f,param_3,0);
  iVar2 = (int)((ulonglong)lVar4 >> 0x20);
  uVar1 = (uint)lVar4;
  uVar3 = 0xffffffff;
  if ((-1 < lVar4) &&
     ((int)(-(uint)(0x7fffffff < uVar1) - iVar2) < 0 ==
      (SBORROW4(0,iVar2) != SBORROW4(-iVar2,(uint)(0x7fffffff < uVar1))))) {
    uVar3 = uVar1;
  }
  FUN_08020d64();
  return uVar3;
}




/* 0x0801ce50 */
uint FUN_0801ce50(param_1, param_2, param_3)
undefined4 param_1; int param_2; undefined4 param_3;
{
  uint uVar1;
  undefined4 extraout_r1;
  int iVar2;
  uint uVar3;
  longlong lVar4;
  
  FUN_08020d4c();
  lVar4 = FUN_0801ce8c(param_1,extraout_r1,param_2,param_2 >> 0x1f,param_3,0);
  iVar2 = (int)((ulonglong)lVar4 >> 0x20);
  uVar1 = (uint)lVar4;
  uVar3 = 0xffffffff;
  if ((-1 < lVar4) &&
     ((int)(-(uint)(0x7fffffff < uVar1) - iVar2) < 0 ==
      (SBORROW4(0,iVar2) != SBORROW4(-iVar2,(uint)(0x7fffffff < uVar1))))) {
    uVar3 = uVar1;
  }
  FUN_08020d64();
  return uVar3;
}




/* 0x0801ce8c */
undefined8 FUN_0801ce8c(param_1, param_2, param_3, param_4, param_5, param_6)
undefined4 param_1; undefined4 param_2; uint param_3; uint param_4; int param_5; int param_6;
{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint local_28;
  
  uVar5 = 0xffffffff;
  local_28 = param_4;
  if (((int)param_4 < 1) && (-2 < (int)param_4)) {
    iVar2 = FUN_08020c90(param_1,-1 - param_3);
    if (iVar2 == 0) {
      piVar3 = (int *)FUN_0801cd9a();
      iVar6 = 0x3f1;
    }
    else {
      if (*(int *)(iVar2 + 4) == 1) {
        uVar7 = 0;
        if (param_5 != 0) {
          if (param_5 == 1) {
            uVar7 = *(uint *)(iVar2 + 0x10);
          }
          else {
            if (param_5 != 2) goto LAB_0801ceb4;
            iVar6 = (**(code **)(*(int *)(*(int *)(iVar2 + 0x14) + 0x14) + 0x34))
                              (*(int *)(iVar2 + 0x14),&local_28);
            uVar7 = local_28;
            if (iVar6 != 0) {
              iVar6 = (**(code **)(*(int *)(*(int *)(iVar2 + 0x14) + 0x14) + 0x30))
                                (*(int *)(iVar2 + 0x14),&DAT_87c27740);
              if (iVar6 != 0) {
                piVar3 = (int *)FUN_0801cd9a();
                iVar6 = -iVar6;
                goto LAB_0801ced6;
              }
              uVar7 = 0;
            }
          }
        }
        uVar4 = uVar7 + param_3;
        param_4 = param_4 + CARRY4(uVar7,param_3);
        if ((((param_6 != 0) ||
             ((int)(-(uint)(0x7fffffff < uVar4) - param_4) < 0 ==
              (SBORROW4(0,param_4) != SBORROW4(-param_4,(uint)(0x7fffffff < uVar4))))) &&
            (-1 < (int)param_4)) && ((int)param_4 < 1)) {
          *(uint *)(iVar2 + 0x10) = uVar4;
          uVar5 = uVar4;
          goto LAB_0801cedc;
        }
        goto LAB_0801ceb4;
      }
      piVar3 = (int *)FUN_0801cd9a();
      iVar6 = 0x405;
    }
LAB_0801ced6:
    *piVar3 = iVar6;
    param_4 = uVar5;
  }
  else {
LAB_0801ceb4:
    puVar1 = (undefined4 *)FUN_0801cd9a();
    *puVar1 = 5;
    param_4 = uVar5;
  }
LAB_0801cedc:
  return CONCAT44(param_4,uVar5);
}




/* 0x0801cf5c */
undefined4 thunk_FUN_0801cf5c(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  
  iVar1 = FUN_08020e54();
  if (iVar1 == 0) {
    FUN_08020d4c();
    iVar1 = FUN_08021058(&DAT_87c2776c,param_1,0xc0);
    if (-1 < iVar1) {
      iVar1 = (**(code **)(*(int *)(DAT_87c27778 + 0x14) + 0x1c))(&DAT_87c2776c,param_2);
      if (DAT_87c27778 != 0) {
        FUN_08021c68();
      }
      if (DAT_87c2777c != 0) {
        FUN_08021c68();
      }
    }
    FUN_08020d64();
    if (iVar1 == 0) {
      return 0;
    }
    piVar3 = (int *)FUN_0801cd9a();
    *piVar3 = -iVar1;
  }
  else {
    puVar2 = (undefined4 *)FUN_0801cd9a();
    *puVar2 = 5;
  }
  return 0xffffffff;
}




/* 0x0801cf5c */
undefined4 FUN_0801cf5c(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  
  iVar1 = FUN_08020e54();
  if (iVar1 == 0) {
    FUN_08020d4c();
    iVar1 = FUN_08021058(&DAT_87c2776c,param_1,0xc0);
    if (-1 < iVar1) {
      iVar1 = (**(code **)(*(int *)(DAT_87c27778 + 0x14) + 0x1c))(&DAT_87c2776c,param_2);
      if (DAT_87c27778 != 0) {
        FUN_08021c68();
      }
      if (DAT_87c2777c != 0) {
        FUN_08021c68();
      }
    }
    FUN_08020d64();
    if (iVar1 == 0) {
      return 0;
    }
    piVar3 = (int *)FUN_0801cd9a();
    *piVar3 = -iVar1;
  }
  else {
    puVar2 = (undefined4 *)FUN_0801cd9a();
    *puVar2 = 5;
  }
  return 0xffffffff;
}




/* 0x0801cfc8 */
undefined4 FUN_0801cfc8(param_1, param_2, param_3, param_4, param_5)
undefined4 param_1; undefined4 param_2; int param_3; undefined4 param_4; undefined4 param_5;
{
  int iVar1;
  int *piVar2;
  
  iVar1 = FUN_08020e54(param_2);
  if ((iVar1 == 0) && (param_3 != 0)) {
    FUN_08020d4c();
    iVar1 = FUN_08021058(&DAT_87c2776c,param_2,0);
    if (iVar1 == 0) {
      if ((*(ushort *)(DAT_87c2777c + 0xc) >> 0xc == 4) || (DAT_0804d258 != 0)) {
        iVar1 = FUN_08020fe0(DAT_87c2777c,param_3,param_5);
      }
      else {
        iVar1 = -0x3fc;
      }
    }
    if (DAT_87c27778 != 0) {
      FUN_08021c68();
    }
    if (DAT_87c2777c != 0) {
      FUN_08021c68();
    }
    FUN_08020d64();
    if (-1 < iVar1) {
      return 0;
    }
    piVar2 = (int *)FUN_0801cd9a();
    iVar1 = -iVar1;
  }
  else {
    piVar2 = (int *)FUN_0801cd9a();
    iVar1 = 5;
  }
  *piVar2 = iVar1;
  return 0xffffffff;
}




/* 0x0801d058 */
undefined4 FUN_0801d058(param_1, param_2, param_3)
undefined4 param_1; uint param_2; undefined2 param_3;
{
  ushort uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  int *piVar6;
  undefined4 uVar7;
  undefined2 uVar8;
  
  iVar2 = FUN_08020e54();
  if (iVar2 != 0) {
    puVar3 = (undefined4 *)FUN_0801cd9a();
    *puVar3 = 5;
    return 0xffffffff;
  }
  uVar8 = 0;
  if ((int)(param_2 << 0x19) < 0) {
    uVar8 = param_3;
  }
  FUN_08020d4c();
  puVar3 = (undefined4 *)FUN_08020c28();
  if (puVar3 == (undefined4 *)0x0) {
    piVar6 = (int *)FUN_0801cd9a();
    iVar2 = 0x400;
  }
  else {
    iVar2 = FUN_08021058(&DAT_87c2776c,param_1,param_2);
    if (iVar2 == 0) {
      if (DAT_87c2777c == 0) {
        iVar2 = (**(code **)(*(int *)(DAT_87c27778 + 0x14) + 4))(&DAT_87c2776c,uVar8);
        iVar5 = DAT_87c27778;
        if (-1 < iVar2) {
LAB_0801d138:
          FUN_08021c68(DAT_87c27778);
          DAT_87c27778 = 0;
          if (((int)(param_2 << 0x16) < 0) && ((int)(param_2 * 0x40000000 + 0x40000000) < 0)) {
            (**(code **)(*(int *)(DAT_87c2777c + 0x14) + 0x18))(DAT_87c2777c,0);
          }
          puVar3[1] = 1;
          puVar3[5] = DAT_87c2777c;
          DAT_87c2777c = 0;
          puVar3[3] = param_2;
          puVar3[4] = 0;
          puVar3[6] = &PTR_LAB_08021408_1_0803982c;
          uVar7 = *puVar3;
          FUN_08020d64();
          return uVar7;
        }
      }
      else {
        uVar1 = *(ushort *)(DAT_87c2777c + 0xc);
        if ((((uVar1 >> 0xc == 2) || (uVar1 >> 0xc == 6)) || (uVar1 >> 0xc == 1)) ||
           (uVar1 >> 0xc == 0xc)) {
          puVar4 = (undefined4 *)FUN_0801cd9a();
          uVar7 = 0x3ee;
        }
        else {
          if ((uVar1 >> 0xc != 4) || ((param_2 & 3) == 0)) goto LAB_0801d138;
          puVar4 = (undefined4 *)FUN_0801cd9a();
          uVar7 = 0x3fd;
        }
        *puVar4 = uVar7;
        FUN_08021c68(DAT_87c27778);
        iVar5 = DAT_87c2777c;
      }
      FUN_08021c68(iVar5);
    }
    FUN_08020c7c(puVar3);
    if (-1 < iVar2) goto LAB_0801d114;
    piVar6 = (int *)FUN_0801cd9a();
    iVar2 = -iVar2;
  }
  *piVar6 = iVar2;
LAB_0801d114:
  FUN_08020d64();
  return 0xffffffff;
}




/* 0x0801d184 */
undefined4 thunk_FUN_0801d184(param_1)
undefined4 param_1;
{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_08020e54();
  if (iVar1 != 0) {
    puVar2 = (undefined4 *)FUN_0801cd9a();
    *puVar2 = 5;
    return 0;
  }
  FUN_08020d4c();
  uVar3 = FUN_0801d1b4(param_1);
  FUN_0801cd9a();
  FUN_08020d64();
  return uVar3;
}




/* 0x0801d184 */
undefined4 FUN_0801d184(param_1)
undefined4 param_1;
{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_08020e54();
  if (iVar1 != 0) {
    puVar2 = (undefined4 *)FUN_0801cd9a();
    *puVar2 = 5;
    return 0;
  }
  FUN_08020d4c();
  uVar3 = FUN_0801d1b4(param_1);
  FUN_0801cd9a();
  FUN_08020d64();
  return uVar3;
}




/* 0x0801d1b4 */
undefined4 * FUN_0801d1b4(param_1)
undefined4 param_1;
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  iVar2 = 0;
  do {
    if ((&DAT_87c279f4)[iVar2 * 0x32] == 0) break;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 2);
  if (iVar2 == 2) {
    piVar5 = (int *)FUN_0801cd9a(2,param_1);
    iVar3 = 0x400;
  }
  else {
    iVar1 = iVar2 * 200;
    iVar3 = FUN_08021058(&DAT_87c2776c,param_1,0);
    if (iVar3 == 0) {
      iVar4 = (**(code **)(*(int *)(DAT_87c2777c + 0x14) + 0x24))();
      *(int *)(&UNK_87c279f8 + iVar1) = iVar4;
      if (iVar4 == 0) {
        FUN_08021c68(DAT_87c2777c);
        iVar3 = -0x3fc;
      }
      else {
        (&DAT_87c279f4)[iVar2 * 0x32] = 1;
        *(int *)(&UNK_87c27ab8 + iVar1) = DAT_87c2777c;
      }
    }
    else {
      *(undefined4 *)(&UNK_87c279f8 + iVar1) = 0;
    }
    if (DAT_87c27778 != 0) {
      FUN_08021c68();
    }
    if (-1 < iVar3) {
      return &DAT_87c279f4 + iVar2 * 0x32;
    }
    piVar5 = (int *)FUN_0801cd9a();
    iVar3 = -iVar3;
  }
  *piVar5 = iVar3;
  return (undefined4 *)0x0;
}




/* 0x0801d244 */
undefined4 thunk_FUN_0801d244(param_1)
undefined4 param_1;
{
  ushort uVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = FUN_08020e54();
  if (iVar2 != 0) {
    piVar3 = (int *)FUN_0801cd9a();
    iVar2 = 5;
    goto LAB_0801d2f0;
  }
  FUN_08020d4c();
  iVar2 = FUN_08021058(&DAT_87c2776c,param_1,0x20000);
  if (iVar2 == 0) {
    uVar1 = *(ushort *)(DAT_87c2777c + 0xc);
    if (((((uVar1 >> 0xc == 8) || (uVar1 >> 0xc == 10)) || (uVar1 >> 0xc == 2)) ||
        ((uVar1 >> 0xc == 6 || (uVar1 >> 0xc == 1)))) ||
       ((uVar1 >> 0xc == 0xc || (uVar1 >> 0xc == 0xe)))) {
      if ((uVar1 >> 0xc != 8) || (iVar2 = FUN_080219fc(DAT_87c2777c), iVar2 < 2)) {
        iVar2 = (**(code **)(*(int *)(DAT_87c27778 + 0x14) + 0xc))(&DAT_87c2776c);
        goto LAB_0801d2da;
      }
      iVar2 = -0x402;
    }
    else {
      iVar2 = -0x3e9;
    }
    FUN_08021c68(DAT_87c2777c);
  }
LAB_0801d2da:
  if (DAT_87c27778 != 0) {
    FUN_08021c68();
  }
  FUN_08020d64();
  if (-1 < iVar2) {
    return 0;
  }
  piVar3 = (int *)FUN_0801cd9a();
  iVar2 = -iVar2;
LAB_0801d2f0:
  *piVar3 = iVar2;
  return 0xffffffff;
}




/* 0x0801d244 */
undefined4 FUN_0801d244(param_1)
undefined4 param_1;
{
  ushort uVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = FUN_08020e54();
  if (iVar2 != 0) {
    piVar3 = (int *)FUN_0801cd9a();
    iVar2 = 5;
    goto LAB_0801d2f0;
  }
  FUN_08020d4c();
  iVar2 = FUN_08021058(&DAT_87c2776c,param_1,0x20000);
  if (iVar2 == 0) {
    uVar1 = *(ushort *)(DAT_87c2777c + 0xc);
    if (((((uVar1 >> 0xc == 8) || (uVar1 >> 0xc == 10)) || (uVar1 >> 0xc == 2)) ||
        ((uVar1 >> 0xc == 6 || (uVar1 >> 0xc == 1)))) ||
       ((uVar1 >> 0xc == 0xc || (uVar1 >> 0xc == 0xe)))) {
      if ((uVar1 >> 0xc != 8) || (iVar2 = FUN_080219fc(DAT_87c2777c), iVar2 < 2)) {
        iVar2 = (**(code **)(*(int *)(DAT_87c27778 + 0x14) + 0xc))(&DAT_87c2776c);
        goto LAB_0801d2da;
      }
      iVar2 = -0x402;
    }
    else {
      iVar2 = -0x3e9;
    }
    FUN_08021c68(DAT_87c2777c);
  }
LAB_0801d2da:
  if (DAT_87c27778 != 0) {
    FUN_08021c68();
  }
  FUN_08020d64();
  if (-1 < iVar2) {
    return 0;
  }
  piVar3 = (int *)FUN_0801cd9a();
  iVar2 = -iVar2;
LAB_0801d2f0:
  *piVar3 = iVar2;
  return 0xffffffff;
}




/* 0x0801d304 */
int thunk_FUN_0801d304(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; int param_3;
{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  if (param_3 == 0) {
    return 0;
  }
  FUN_08020d4c();
  iVar1 = FUN_08020c90(param_1);
  if (iVar1 == 0) {
    piVar3 = (int *)FUN_0801cd9a();
    iVar1 = 0x3f1;
  }
  else {
    iVar2 = (**(code **)(*(int *)(iVar1 + 0x18) + 4))(iVar1,param_2,param_3);
    if (0 < iVar2) goto LAB_0801d33a;
    if (iVar2 == 0) {
      iVar2 = -0x404;
    }
    piVar3 = (int *)FUN_0801cd9a();
    iVar1 = -iVar2;
  }
  iVar2 = -1;
  *piVar3 = iVar1;
LAB_0801d33a:
  if (iVar2 < 0) {
    FUN_0801cd9a();
  }
  FUN_08020d64();
  return iVar2;
}




/* 0x0801d304 */
int FUN_0801d304(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; int param_3;
{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  if (param_3 == 0) {
    return 0;
  }
  FUN_08020d4c();
  iVar1 = FUN_08020c90(param_1);
  if (iVar1 == 0) {
    piVar3 = (int *)FUN_0801cd9a();
    iVar1 = 0x3f1;
  }
  else {
    iVar2 = (**(code **)(*(int *)(iVar1 + 0x18) + 4))(iVar1,param_2,param_3);
    if (0 < iVar2) goto LAB_0801d33a;
    if (iVar2 == 0) {
      iVar2 = -0x404;
    }
    piVar3 = (int *)FUN_0801cd9a();
    iVar1 = -iVar2;
  }
  iVar2 = -1;
  *piVar3 = iVar1;
LAB_0801d33a:
  if (iVar2 < 0) {
    FUN_0801cd9a();
  }
  FUN_08020d64();
  return iVar2;
}




/* 0x0801d5a2 */
void FUN_0801d5a2(param_1, param_2, param_3, param_4)
int * param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *param_1;
  iVar1 = FUN_0801d708(param_1,1);
  if (-1 < iVar1) {
    iVar3 = param_1[0x55];
    iVar1 = (**(code **)(*(int *)(iVar2 + 0x10) + 0x18))(iVar3,param_2,0);
    if (-1 < iVar1) {
                    /* WARNING: Could not recover jumptable at 0x0801d5dc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*(int *)(iVar2 + 0x10) + 0x1c))(iVar3,param_3,param_4);
      return;
    }
  }
  return;
}




/* 0x0801d5e2 */
undefined4 FUN_0801d5e2()
{
  FUN_08015a50();
  return 0xfffffffb;
}




/* 0x0801d5f0 */
int FUN_0801d5f0(param_1, param_2, param_3, param_4, param_5)
int param_1; int param_2; undefined4 param_3; undefined4 param_4; int param_5;
{
  int iVar1;
  undefined **ppuVar2;
  
  *(int *)(param_2 + 0x20) = param_5;
  FUN_08020e68(param_2 + 0x24,0x12d,param_4,param_5);
  *(undefined1 *)(param_2 + param_5 + 0x24) = 0;
  iVar1 = (**(code **)(*(int *)(param_1 + 0x10) + 8))(param_2 + 0x24,param_2 + 0xc);
  if (-1 < iVar1) {
    *(undefined4 *)(param_2 + 0x154) = 0xffffffff;
    *(undefined4 *)(param_2 + 0x158) = 0;
    if (*(ushort *)(param_2 + 0xc) >> 0xc == 8) {
      ppuVar2 = &PTR_LAB_08021a98_1_0803af64;
    }
    else if (*(ushort *)(param_2 + 0xc) >> 0xc == 4) {
      ppuVar2 = &PTR_LAB_08021a98_1_0803aeb0;
    }
    else {
      ppuVar2 = &PTR_LAB_08021a98_1_0803b018;
    }
    *(undefined ***)(param_2 + 0x14) = ppuVar2;
    iVar1 = 0;
  }
  return iVar1;
}




