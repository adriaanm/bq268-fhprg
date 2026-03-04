/* Auto-generated: fhprg_8019930.c */
/* Functions: 26 */
#include "globals.h"

/* 0x08019930 */
void FUN_08019930(param_1)
undefined4 param_1;
{
  thunk_FUN_0801ce50(param_1,0);
  FUN_08014ea0(param_1,0x87c734c4,0x38);
  FUN_08014ea0(param_1,0x87c734fc,DAT_0804cd74 << 6);
  return;
}




/* 0x08019964 */
undefined4 FUN_08019964()
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_08016e54();
  if ((((iVar1 == 2) || (iVar1 == 4)) || (iVar1 == 5)) || (iVar1 == 8)) {
    uVar2 = 1;
  }
  return uVar2;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08019984 */
void FUN_08019984()
{
  FUN_0802d180(0,2);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0801999c */
void FUN_0801999c()
{
  FUN_0802d180(0);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x080199b4 */
void thunk_FUN_080199b4(param_1)
uint param_1;
{
  int *piVar1;
  int iVar2;
  undefined8 uVar3;
  
  piVar1 = DAT_0804d264;
  if (DAT_0804d264 != (int *)0x0) {
    iVar2 = *(uint*)DAT_0804d264;
    uVar3 = FUN_080060c0((int)((ulonglong)param_1 * 0x4b00),
                         (int)((ulonglong)param_1 * 0x4b00 >> 0x20),1000,0);
    do {
    } while ((uint)((uint)uVar3 <= (uint)(*piVar1 - iVar2)) <=
             (uint)-(int)((ulonglong)uVar3 >> 0x20));
  }
  return;
}




/* 0x080199b4 */
void FUN_080199b4(param_1)
uint param_1;
{
  int *piVar1;
  int iVar2;
  undefined8 uVar3;
  
  piVar1 = DAT_0804d264;
  if (DAT_0804d264 != (int *)0x0) {
    iVar2 = *(uint*)DAT_0804d264;
    uVar3 = FUN_080060c0((int)((ulonglong)param_1 * 0x4b00),
                         (int)((ulonglong)param_1 * 0x4b00 >> 0x20),1000,0);
    do {
    } while ((uint)((uint)uVar3 <= (uint)(*piVar1 - iVar2)) <=
             (uint)-(int)((ulonglong)uVar3 >> 0x20));
  }
  return;
}




/* 0x080199e4 */
undefined4 thunk_qtimer_init()
{
  int iVar1;
  
  iVar1 = dal_device_attach("QTimer",&DAT_0804d268);
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  thunk_FUN_080106aa(&DAT_0804d268,"QTIMER_BASE",0,&DAT_08054398);
  DAT_0804d264 = DAT_080543a0;
  thunk_FUN_080106aa(&DAT_0804d268,"QTIMER_FRAME",0,&DAT_08054398);
  iVar1 = DAT_080543a0;
  thunk_FUN_080106aa(&DAT_0804d268,"QTIMER_AC_BASE",0,&DAT_08054398);
  *(undefined4 *)(DAT_080543a0 + iVar1 * 4 + 0x40) = 0x3f;
  return 0;
}




/* 0x080199e4 */
undefined4 qtimer_init()
{
  int iVar1;
  
  iVar1 = dal_device_attach("QTimer",&DAT_0804d268);
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  thunk_FUN_080106aa(&DAT_0804d268,"QTIMER_BASE",0,&DAT_08054398);
  DAT_0804d264 = DAT_080543a0;
  thunk_FUN_080106aa(&DAT_0804d268,"QTIMER_FRAME",0,&DAT_08054398);
  iVar1 = DAT_080543a0;
  thunk_FUN_080106aa(&DAT_0804d268,"QTIMER_AC_BASE",0,&DAT_08054398);
  *(undefined4 *)(DAT_080543a0 + iVar1 * 4 + 0x40) = 0x3f;
  return 0;
}




/* 0x08019a70 */
undefined4 FUN_08019a70(param_1, param_2, param_3, param_4, param_5)
int param_1; undefined4 param_2; uint param_3; int param_4; undefined4 param_5;
{
  uint uVar1;
  int iVar2;
  
  for (; param_3 != 0 || param_4 != 0; param_3 = param_3 - uVar1) {
    uVar1 = param_3;
    iVar2 = param_4;
    if ((uint)(param_3 < 0x10000) <= (uint)-param_4) {
      uVar1 = 0xffff;
      iVar2 = 0;
    }
    param_5 = FUN_0801a524(param_5,param_1,uVar1 & 0xffff);
    param_1 = param_1 + uVar1;
    param_4 = (param_4 - iVar2) - (uint)(param_3 < uVar1);
  }
  return param_5;
}




/* 0x08019abc */
uint FUN_08019abc(param_1, param_2)
int param_1; uint param_2;
{
  int iVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  uVar5 = 0xffffffff;
  if ((param_1 == 0) || (param_2 == 0)) {
    uVar5 = 0;
  }
  else {
    for (uVar6 = 0; uVar6 < param_2; uVar6 = uVar6 + 1) {
      bVar2 = FUN_08031548(*(undefined1 *)(param_1 + uVar6),8);
      uVar3 = (uint)bVar2;
      for (uVar4 = 0; uVar4 < 8; uVar4 = uVar4 + 1) {
        iVar1 = (int)uVar5 >> 0x1f;
        uVar5 = uVar5 << 1;
        if (-iVar1 != uVar3 >> 7) {
          uVar5 = uVar5 ^ 0x4c11db7;
        }
        uVar3 = (uVar3 << 0x19) >> 0x18;
      }
    }
    uVar5 = FUN_08031548(uVar5,0x20);
    uVar5 = ~uVar5;
  }
  return uVar5;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08019b80 */
undefined4 FUN_08019b80()
{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((_DAT_0860065c != 0) && ((~_DAT_0860065c & 0x77665506) == 0)) {
    _DAT_01024000 = 3;
    FUN_080199b4(200000);
    if ((_DAT_01024004 & 3) == 0) {
      uVar1 = 1;
    }
  }
  return uVar1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08019bfc */
undefined4 FUN_08019bfc()
{
  if ((_DAT_0005a090 & 1) != 0) {
    _DAT_0005a090 = _DAT_0005a090 & 0xffe;
    return 1;
  }
  return 0;
}




/* 0x08019c1c */
undefined4 FUN_08019c1c(param_1)
int param_1;
{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint local_30 [4];
  
  uVar6 = 0;
  local_30[0] = 0;
  local_30[1] = 0;
  local_30[2] = 0;
  local_30[3] = 0;
  uVar9 = *(uint *)(param_1 + 0xc);
  iVar2 = FUN_0802efd6(0,0,1,param_1);
  if (((iVar2 == 0) || (*(char *)(iVar2 + 0x1fe) != 'U')) || (*(char *)(iVar2 + 0x1ff) != -0x56)) {
LAB_08019cb0:
    uVar5 = 0xffffffff;
  }
  else {
    if ((*(char *)(iVar2 + 0xb) == '\0') && (*(char *)(iVar2 + 0xc) == '\x02')) {
      uVar7 = 0;
      do {
        iVar8 = iVar2 + uVar7 * 0x10;
        if ((*(char *)(iVar8 + 0x1c2) != '\0') && (iVar3 = FUN_08006e04(iVar8 + 0x1ca), iVar3 != 0))
        {
          uVar4 = FUN_08006e04(iVar8 + 0x1c6);
          if ((uVar4 == 0) || (uVar9 < uVar4)) goto LAB_08019cb0;
          local_30[uVar6] = uVar4;
          uVar6 = uVar6 + 1 & 0xff;
        }
        uVar7 = uVar7 + 1 & 0xff;
      } while (uVar7 < 4);
      if (uVar6 == 0) goto LAB_08019cb0;
      uVar9 = 0;
      while ((int)uVar9 < (int)(uVar6 - 1)) {
        bVar1 = (char)uVar9 + 1;
        for (uVar7 = (uint)bVar1; uVar7 < uVar6; uVar7 = uVar7 + 1 & 0xff) {
          if (local_30[uVar9] == local_30[uVar7]) goto LAB_08019cb0;
        }
        uVar9 = (uint)bVar1;
      }
    }
    uVar5 = 0;
  }
  return uVar5;
}




/* 0x08019cd8 */
void FUN_08019cd8()
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = DAT_0804d44c;
  uVar2 = 0;
  do {
    *(undefined4 *)(iVar1 + uVar2 * 0x1000 + 0x1800008) = 0xff;
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x80);
  uVar2 = 0;
  do {
    *(undefined4 *)(iVar1 + uVar2 * 0x1000 + 0x1800000) = 0;
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x80);
  uVar2 = 0;
  do {
    *(undefined4 *)(iVar1 + uVar2 * 4 + 0xa700) = 0;
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x100);
  uVar2 = 0;
  do {
    uVar3 = 0;
    do {
      uVar3 = uVar3 + 1;
    } while (uVar3 < 4);
    uVar2 = uVar2 + 1;
  } while (uVar2 < 6);
  return;
}




/* 0x08019d3c */
undefined4 FUN_08019d3c(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = *(int *)(param_1 + 0xc);
  piVar1 = &DAT_0803b74c;
  do {
    iVar2 = *piVar1;
    if (iVar2 == 0) {
LAB_08019d7e:
      uVar3 = 0x91;
      iVar2 = iVar4;
LAB_08019d72:
      FUN_08038460(10,uVar3,1,iVar2,0,0);
      return 1;
    }
    if (iVar2 == iVar4) {
      if (iVar2 != 0) {
        iVar2 = piVar1[1];
        iVar5 = piVar1[2];
        iVar4 = FUN_0800f608(param_1,iVar2,param_3,iVar4,param_3,param_4);
        if (iVar4 == 0) {
          FUN_0800c5fc(*(undefined4 *)(param_1 + 8),iVar5);
          return 0;
        }
        uVar3 = 0x9b;
        goto LAB_08019d72;
      }
      goto LAB_08019d7e;
    }
    piVar1 = piVar1 + 3;
  } while( true );
}




/* 0x08019d98 */
undefined4 FUN_08019d98(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  
  while( true ) {
    bVar3 = param_3 == 0;
    param_3 = param_3 + -1;
    if (bVar3) {
      return 0;
    }
    uVar1 = *(uint *)(param_1 + param_3 * 4);
    uVar2 = *(uint *)(param_2 + param_3 * 4);
    if (uVar1 < uVar2) break;
    if (uVar1 != uVar2) {
      return 1;
    }
  }
  return 0xffffffff;
}




/* 0x08019dbe */
void FUN_08019dbe(param_1, param_2, param_3)
uint * param_1; int param_2; int param_3;
{
  uint *puVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint *puVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint local_58;
  uint local_54;
  uint local_50;
  uint uStack_4c;
  
  local_50 = 0;
  uStack_4c = 0;
  local_58 = 0;
  local_54 = 0;
  for (uVar10 = 0; uVar10 < *param_1; uVar10 = uVar10 + 1) {
    uVar4 = 0;
    iVar3 = param_3 + uVar10 * 0x78;
    uVar12 = 0;
    do {
      puVar2 = (undefined4 *)(iVar3 + uVar12 * 0x18);
      if (puVar2[3] == 0 && puVar2[2] == 0) {
        *puVar2 = 0;
        puVar2[1] = 0;
        *(undefined1 *)(puVar2 + 4) = 0;
      }
      else {
        if (uVar12 != uVar4) {
          FUN_08006bdc(iVar3 + uVar4 * 0x18,puVar2,0x18);
          *puVar2 = 0;
          puVar2[1] = 0;
          puVar2[2] = 0;
          puVar2[3] = 0;
          *(undefined1 *)(puVar2 + 4) = 0;
        }
        uVar4 = uVar4 + 1;
      }
      uVar12 = uVar12 + 1;
    } while (uVar12 < 5);
  }
  uVar10 = 0;
  do {
    if (*param_1 <= uVar10) {
      return;
    }
    iVar3 = param_3 + uVar10 * 0x78;
    uVar4 = 0;
    uVar12 = 0;
    do {
      puVar1 = (uint *)(iVar3 + uVar12 * 0x18);
      uVar6 = puVar1[2];
      uVar7 = puVar1[3];
      if (uVar6 != 0 || uVar7 != 0) {
        if (uVar12 != 0 || uVar4 != 0) {
          puVar9 = (uint *)(iVar3 + uVar4 * 0x18);
          if ((char)puVar1[4] == (char)puVar9[4]) {
            uVar5 = *puVar9;
            uVar8 = puVar9[1];
            uVar11 = puVar9[2];
            uVar13 = *puVar1;
            if ((uVar13 == uVar5 + uVar11 &&
                 puVar1[1] == uVar8 + puVar9[3] + (uint)CARRY4(uVar5,uVar11)) ||
               (uVar5 == uVar13 + uVar6 && puVar1[1] + uVar7 + CARRY4(uVar13,uVar6) == uVar8)) {
              puVar9[2] = uVar11 + uVar6;
              puVar9[3] = puVar9[3] + uVar7 + CARRY4(uVar11,uVar6);
              uVar6 = puVar1[1];
              if (uVar6 <= uVar8 && (uint)(uVar5 <= *puVar1) <= uVar6 - uVar8) {
                *puVar9 = *puVar1;
                puVar9[1] = uVar6;
              }
              goto LAB_08019ef4;
            }
          }
          uVar4 = uVar4 + 1;
          puVar9 = (uint *)(iVar3 + uVar4 * 0x18);
          *(char *)(puVar9 + 4) = (char)puVar1[4];
          uVar6 = puVar1[1];
          *puVar9 = *puVar1;
          puVar9[1] = uVar6;
          uVar6 = puVar1[3];
          puVar9[2] = puVar1[2];
          puVar9[3] = uVar6;
        }
LAB_08019ef4:
        if (param_2 != 0) {
          puVar1 = (uint *)(iVar3 + uVar4 * 0x18);
          for (uVar6 = 0; uVar6 < param_1[2]; uVar6 = uVar6 + 1) {
            uVar8 = param_1[3];
            puVar9 = (uint *)(uVar8 + uVar6 * 0x10);
            uVar5 = puVar9[1];
            uVar7 = puVar1[1];
            if ((uVar5 < uVar7 || uVar7 - uVar5 < (uint)(*puVar9 <= *puVar1)) &&
               (puVar9 = (uint *)(uVar8 + uVar6 * 0x10 + 8), uVar5 = puVar9[1],
               uVar7 <= uVar5 && (uint)(*puVar9 <= *puVar1) <= uVar7 - uVar5)) {
              puVar9 = (uint *)(uVar8 + uVar6 * 0x10);
              local_50 = *puVar9;
              uStack_4c = puVar9[1];
              puVar9 = (uint *)(uVar6 * 0x10 + 8 + uVar8);
              local_58 = *puVar9;
              local_54 = puVar9[1];
              break;
            }
          }
          if (param_1[2] != uVar6) {
            if (puVar1[1] <= uStack_4c && (uint)(local_50 <= *puVar1) <= puVar1[1] - uStack_4c) {
              *puVar1 = local_50;
              puVar1[1] = uStack_4c;
            }
            uVar6 = *puVar1;
            uVar7 = puVar1[1] + puVar1[3] + (uint)CARRY4(uVar6,puVar1[2]);
            if (local_54 <= uVar7 && (uint)(uVar6 + puVar1[2] <= local_58) <= local_54 - uVar7) {
              puVar1[2] = local_58 - uVar6;
              puVar1[3] = (local_54 - puVar1[1]) - (uint)(local_58 < uVar6);
            }
          }
        }
      }
      uVar12 = uVar12 + 1;
    } while (uVar12 < 5);
    if (param_1[1] < uVar4) {
      *(undefined1 *)(param_1 + 7) = 1;
      return;
    }
    while (uVar4 = uVar4 + 1, uVar4 < 5) {
      puVar2 = (undefined4 *)(iVar3 + uVar4 * 0x18);
      *(undefined1 *)(puVar2 + 4) = 0;
      *puVar2 = 0;
      puVar2[1] = 0;
      puVar2[2] = 0;
      puVar2[3] = 0;
    }
    uVar10 = uVar10 + 1;
  } while( true );
}




/* 0x08019ff0 */
int FUN_08019ff0(param_1, param_2, param_3, param_4, param_5, param_6, param_7)
int param_1; uint param_2; int param_3; int * param_4; int param_5; int param_6; int param_7;
{
  ushort uVar1;
  uint *puVar2;
  uint uVar3;
  byte *pbVar4;
  int iVar5;
  uint unaff_r7 = 0;
  uint unaff_r8 = 0;
  uint unaff_r9 = 0;
  uint unaff_r10 = 0;
  int iVar6;
  uint local_40;
  uint local_3c;
  
  iVar6 = DAT_0804d44c;
  iVar5 = 0;
  pbVar4 = (byte *)0x0;
  if (DAT_0804d164 == '\0') {
    return 0xe;
  }
  if (((param_1 == 0) || (param_2 == 0)) || ((param_3 != 0 && (param_4 == (int *)0x0)))) {
    return 0xc;
  }
  if (0x80 < param_2) {
    return 0x10;
  }
  if (param_5 != 0) {
    DAT_0804d166 = 0;
  }
  if (param_6 != 0) {
    uVar3 = 0;
    do {
      *(undefined4 *)(iVar6 + uVar3 * 4 + 0xf800) = 0;
      uVar3 = uVar3 + 1;
    } while (uVar3 < 0x80);
  }
  if (param_3 != 0) {
    FUN_080371d8(param_1,param_2,&LAB_080287f2);
    unaff_r10 = unaff_r10 & 0xffffff00;
    local_40 = DAT_0804d44c + 0x400000;
    unaff_r9 = DAT_0804d44c + 0x1800000;
    unaff_r7 = unaff_r7 & 0xffffff00 | (uint)*(byte *)(param_1 + 5);
    unaff_r8 = unaff_r8 & 0xffffff00 | (uint)*(byte *)(param_1 + 4);
    local_3c = local_3c & 0xffffff00;
  }
  for (uVar3 = 0; uVar3 < param_2; uVar3 = uVar3 + 1) {
    pbVar4 = (byte *)(param_1 + uVar3 * 6);
    if (0xf < *pbVar4) {
      return 0x13;
    }
    if ((5 < pbVar4[4]) || (((param_3 != 0 && (5 < pbVar4[5])) && (pbVar4[5] != 0xff)))) {
      return 0x17;
    }
    if (param_6 == 0) {
      iVar6 = FUN_080138ec(pbVar4,param_5);
    }
    else {
      iVar6 = FUN_0800e594();
    }
    if (iVar6 != 0) {
      return iVar6;
    }
    if (param_3 != 0) {
      if ((uint)pbVar4[5] != (unaff_r7 & 0xff)) {
        if (*param_4 == iVar5) goto LAB_0801a1e6;
        iVar6 = DAT_0804d44c + (uint)*(ushort *)(pbVar4 + 2) * 0x8000;
        puVar2 = (uint *)(param_3 + iVar5 * 0x10);
        iVar5 = iVar5 + 1;
        puVar2[3] = unaff_r10 & 0xffff00ff | (*(ushort *)(pbVar4 + 2) - 1 & 0xff) << 8;
        *puVar2 = unaff_r7;
        puVar2[1] = local_40;
        puVar2[2] = (iVar6 - local_40) + 0x400000;
        unaff_r7 = unaff_r7 & 0xffffff00 | (uint)pbVar4[5];
        unaff_r10 = unaff_r10 & 0xffff0000 | *(ushort *)(pbVar4 + 2) & 0xff;
        local_40 = DAT_0804d44c + (uint)*(ushort *)(pbVar4 + 2) * 0x8000 + 0x400000;
      }
      if ((uint)pbVar4[4] != (unaff_r8 & 0xff)) {
        if (*param_4 == iVar5) goto LAB_0801a1e6;
        uVar1 = *(ushort *)(pbVar4 + 2);
        puVar2 = (uint *)(param_3 + iVar5 * 0x10);
        iVar5 = iVar5 + 1;
        puVar2[2] = ((DAT_0804d44c + (uint)uVar1 * 0x1000) - unaff_r9) + 0x1800000;
        puVar2[3] = local_3c & 0xffff00ff | (uVar1 - 1 & 0xff) << 8;
        *puVar2 = unaff_r8;
        puVar2[1] = unaff_r9;
        unaff_r8 = unaff_r8 & 0xffffff00 | (uint)pbVar4[4];
        local_3c = local_3c & 0xffff0000 | *(ushort *)(pbVar4 + 2) & 0xff;
        unaff_r9 = DAT_0804d44c + (uint)*(ushort *)(pbVar4 + 2) * 0x1000 + 0x1800000;
      }
    }
  }
  if (param_3 == 0) {
LAB_0801a20e:
    if (param_4 != (int *)0x0) {
      *param_4 = iVar5;
    }
    if ((param_6 != 0) && (DAT_0804d165 == '\0')) {
      if (param_7 == 0) {
        FUN_080371d8(param_1,param_2,&LAB_0802f00e);
      }
      FUN_0800e8d8(param_1,param_2);
      iVar6 = DAT_0804d44c;
      *(uint *)(DAT_0804d44c + 0xaf54) = *(uint *)(DAT_0804d44c + 0xaf54) | 1;
      puVar2 = (uint *)(iVar6 + 0xaf08);
      *puVar2 = *puVar2 & 0xfffffffe;
      puVar2 = (uint *)(iVar6 + 0xaf14);
      *puVar2 = *puVar2 | 1;
    }
    iVar6 = 0;
  }
  else {
    uVar1 = *(ushort *)(pbVar4 + 2);
    iVar6 = DAT_0804d44c + (uint)uVar1 * 0x8000;
    if ((unaff_r7 & 0xff) == 0xff) {
LAB_0801a1da:
      if (*param_4 != iVar5) {
        uVar1 = *(ushort *)(pbVar4 + 2);
        puVar2 = (uint *)(param_3 + iVar5 * 0x10);
        puVar2[2] = ((DAT_0804d44c + (uint)uVar1 * 0x1000) - unaff_r9) + 0x1801000;
        puVar2[3] = local_3c & 0xffff00ff | (uVar1 & 0xff) << 8;
        iVar5 = iVar5 + 1;
        *puVar2 = unaff_r8;
        puVar2[1] = unaff_r9;
        goto LAB_0801a20e;
      }
    }
    else if (*param_4 != iVar5) {
      puVar2 = (uint *)(param_3 + iVar5 * 0x10);
      iVar5 = iVar5 + 1;
      *puVar2 = unaff_r7;
      puVar2[1] = local_40;
      puVar2[2] = (iVar6 - local_40) + 0x408000;
      puVar2[3] = unaff_r10 & 0xffff00ff | (uVar1 & 0xff) << 8;
      goto LAB_0801a1da;
    }
LAB_0801a1e6:
    iVar6 = 0x11;
  }
  return iVar6;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0801a27c */
void FUN_0801a27c()
{
  _DAT_01000000 = 0;
  _DAT_01001000 = 0;
  _DAT_01002000 = 0;
  return;
}




/* 0x0801a298 */
void FUN_0801a298()
{
  undefined4 *puVar1;
  
  if (DAT_0804cd50 == 0 && DAT_0804cd4c == 0) {
    puVar1 = (undefined4 *)&DAT_0105c000;
  }
  else {
    puVar1 = (undefined4 *)&DAT_01051000;
  }
  *puVar1 = 0;
  return;
}




/* 0x0801a2bc */
void FUN_0801a2bc(param_1, param_2, param_3)
int param_1; uint param_2; int param_3;
{
  longlong lVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  undefined4 *puVar11;
  
  FUN_08006d14(param_3,0xf0);
  for (uVar3 = 0; uVar3 < param_2; uVar3 = uVar3 + 1) {
    uVar2 = 0;
    iVar5 = 0;
    do {
      uVar4 = *(uint *)(param_1 + uVar3 * 8 + uVar2 * 4);
      iVar9 = iVar5;
      if (uVar4 != 0) {
        uVar10 = *(uint *)(param_1 + 0x30) & 1 << (uVar2 & 0xff);
        uVar8 = uVar4 >> 0xc;
        if (uVar10 == 0) {
          iVar7 = uVar4 << 0x14;
        }
        else {
          lVar1 = (ulonglong)(uVar4 * 0x100000) * (ulonglong)param_2;
          iVar7 = (int)lVar1;
          uVar8 = uVar8 * param_2 + (int)((ulonglong)lVar1 >> 0x20);
        }
        iVar9 = iVar5 + 1;
        puVar11 = (undefined4 *)(param_3 + uVar3 * 0x78 + iVar5 * 0x18);
        *(bool *)(puVar11 + 4) = uVar10 != 0;
        iVar5 = param_1 + uVar3 * 0x10 + uVar2 * 8;
        uVar6 = *(undefined4 *)(iVar5 + 0x14);
        *puVar11 = *(undefined4 *)(iVar5 + 0x10);
        puVar11[1] = uVar6;
        puVar11[2] = iVar7;
        puVar11[3] = uVar8;
      }
      uVar2 = uVar2 + 1;
      iVar5 = iVar9;
    } while (uVar2 < 2);
  }
  return;
}




/* 0x0801a360 */
undefined4 FUN_0801a360(param_1, param_2, param_3, param_4)
int param_1; char * param_2; int param_3; int param_4;
{
  int iVar1;
  int iVar2;
  ushort uVar3;
  uint uVar4;
  undefined4 uVar5;
  char cVar6;
  ushort local_40 [14];
  int local_24;
  
  iVar1 = DAT_0804cd58;
  local_24 = DAT_0804cd58;
  cVar6 = '\0';
  if (*param_2 == '\0') {
    uVar5 = 1;
  }
  else if ((*param_2 == -0x1b) || ((int)((uint)(byte)param_2[0xb] << 0x1c) < 0)) {
LAB_0801a43e:
    uVar5 = 2;
  }
  else {
    if ((param_4 == 0) || (iVar2 = FUN_080114f4(param_1,param_3), iVar2 == 0)) {
      iVar2 = 0;
LAB_0801a39e:
      uVar3 = *(ushort *)(param_3 + iVar2 * 2);
      if (uVar3 - 0x61 < 0x1a) {
        uVar3 = uVar3 - 0x20;
      }
      uVar4 = (uint)*(ushort *)(param_1 + iVar2 * 2);
      if (uVar4 - 0x61 < 0x1a) {
        uVar4 = uVar4 - 0x20;
      }
      if (uVar4 != uVar3) {
        if (DAT_0804e29c != '\0') {
          cVar6 = param_2[0xc];
        }
        FUN_0801242c(local_40,param_2,param_2 + 8,cVar6);
        if (param_4 != 0) {
          if (param_2[8] == ' ') {
            for (iVar2 = 0; local_40[iVar2] != 0; iVar2 = iVar2 + 1) {
            }
            local_40[iVar2] = 0x2e;
            local_40[iVar2 + 1] = 0;
          }
          iVar2 = FUN_080114f4(param_1,local_40);
          if (iVar2 != 0) goto LAB_0801a448;
        }
        iVar2 = 0;
        while( true ) {
          uVar3 = local_40[iVar2];
          if (uVar3 - 0x61 < 0x1a) {
            uVar3 = uVar3 - 0x20;
          }
          uVar4 = (uint)*(ushort *)(param_1 + iVar2 * 2);
          if (uVar4 - 0x61 < 0x1a) {
            uVar4 = uVar4 - 0x20;
          }
          if (uVar4 != uVar3) break;
          if (uVar3 == 0) goto LAB_0801a448;
          iVar2 = iVar2 + 1;
        }
        goto LAB_0801a43e;
      }
      if (uVar3 != 0) goto code_r0x0801a3ec;
    }
LAB_0801a448:
    uVar5 = 0;
  }
  if (local_24 != iVar1) {
    FUN_08010960();
  }
  return uVar5;
code_r0x0801a3ec:
  iVar2 = iVar2 + 1;
  goto LAB_0801a39e;
}




/* 0x0801a464 */
void FUN_0801a464(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  int iVar1;
  
  iVar1 = FUN_08025f4e(param_1,0,param_2,1);
  if ((iVar1 == 0) && (iVar1 = FUN_08025f4e(param_1,1,param_2,1), iVar1 == 0)) {
    return;
  }
  FUN_08015a50();
  return;
}




/* 0x0801a490 */
int FUN_0801a490(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  int iVar1;
  
  iVar1 = LZCOUNT(param_2);
  if (iVar1 == 0x20) {
    iVar1 = LZCOUNT(param_1) + 0x20;
  }
  return iVar1;
}




/* 0x0801a4a2 */
undefined4 FUN_0801a4a2(param_1, param_2)
uint param_1; uint param_2;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 extraout_r2;
  uint uVar5;
  
  uVar1 = param_1 >> 1 & 0x55555555;
  uVar2 = (param_1 & 0x55555555) + uVar1;
  uVar3 = (param_2 & 0x55555555) + (param_2 >> 1 & 0x55555555) +
          (uint)CARRY4(param_1 & 0x55555555,uVar1);
  uVar5 = uVar2 & 0x33333333;
  uVar1 = uVar2 >> 2 & 0x33333333;
  uVar4 = uVar5 + uVar1;
  uVar2 = (uVar3 & 0x33333333) + (uVar3 >> 2 & 0x33333333) + (uint)CARRY4(uVar5,uVar1);
  uVar3 = uVar4 & 0xf0f0f0f;
  uVar1 = uVar4 >> 4 & 0xf0f0f0f;
  FUN_080060c0(uVar3 + uVar1,
               (uVar2 & 0xf0f0f0f) + (uVar2 >> 4 & 0xf0f0f0f) + (uint)CARRY4(uVar3,uVar1),0xff,0);
  return extraout_r2;
}




/* 0x0801a502 */
int FUN_0801a502(param_1, param_2)
uint param_1; uint param_2;
{
  int iVar1;
  uint uVar2;
  int extraout_r3;
  
  uVar2 = -(uint)(param_1 != 0) - param_2;
  iVar1 = FUN_0801a490(param_1 & -param_1,param_2 & uVar2,uVar2,param_1);
  if (extraout_r3 != 0 || param_2 != 0) {
    iVar1 = 0x3f - iVar1;
  }
  return iVar1;
}




