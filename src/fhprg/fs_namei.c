/* Auto-generated: fs_namei.c */
/* Functions: 8 */
#include "globals.h"

/* 0x08021058 */
int FUN_08021058(param_1, param_2, param_3)
int * param_1; int param_2; int param_3;
{
  uint uVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  int iVar7;
  char *pcVar8;
  
  iVar7 = 0;
  if (param_2 == 0) {
    ((code*)DAT_0804cd60)("fs_namei.c",0x48,0x302f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar1 = FUN_08006906(param_2);
  if (uVar1 == 0) {
    ((code*)DAT_0804cd60)("fs_namei.c",0x4c,0x302f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (uVar1 < 0x12d) {
    FUN_080382c2(param_1 + 5,param_2,0x12d);
    *param_1 = (int)(param_1 + 5);
    param_1[4] = 0;
    while ((0 < (int)(uVar1 - 1) && (*(char *)((int)param_1 + uVar1 + 0x13) == '/'))) {
      *(undefined1 *)((int)param_1 + uVar1 + 0x13) = 0;
      uVar1 = uVar1 - 1;
    }
    pcVar8 = (char *)((int)param_1 + uVar1 + 0x14);
    param_1[3] = DAT_0804d640;
    FUN_08021c60();
    for (pcVar4 = (char *)*param_1; pcVar5 = pcVar4, *pcVar4 == '/'; pcVar4 = pcVar4 + 1) {
    }
LAB_080210f0:
    for (; (*pcVar4 != '\0' && (*pcVar4 != '/')); pcVar4 = pcVar4 + 1) {
    }
    if (0x88 < (int)pcVar4 - (int)pcVar5) {
LAB_08021182:
      iVar2 = -0x40c;
      goto LAB_0802123a;
    }
    param_1[1] = (int)pcVar5;
    param_1[2] = (int)pcVar4 - (int)pcVar5;
    iVar2 = ((code *)**(undefined4 **)(param_1[3] + 0x14))(param_1);
    pcVar6 = pcVar5 + param_1[2];
    if (iVar2 == 0) {
      iVar2 = param_1[4];
      if ((*(ushort *)(iVar2 + 0xc) >> 0xc == 10) && ((*pcVar6 != '\0' || (-1 < param_3 << 0xe)))) {
        iVar7 = iVar7 + 1;
        if (8 < iVar7) {
          iVar2 = -0x410;
          goto LAB_0802123a;
        }
        iVar2 = (**(code **)(*(int *)(iVar2 + 0x14) + 0x40))(iVar2,&DAT_87c28384,300);
        if (iVar2 < 0) goto LAB_0802123a;
        pcVar4 = pcVar5;
        if (false) {
          FUN_08021c68(param_1[3]);
          param_1[3] = DAT_0804d640;
          FUN_08021c60();
          pcVar4 = (char *)*param_1;
        }
        iVar3 = *param_1;
        if ((char *)0x12c < pcVar4 + (int)(pcVar8 + ((iVar2 - iVar3) - (int)pcVar6)))
        goto LAB_08021182;
        FUN_08020edc(pcVar4 + iVar2,pcVar8 + (1 - (int)pcVar6),pcVar6,pcVar8 + (1 - (int)pcVar6));
        pcVar8 = (char *)((int)param_1 +
                         (int)(pcVar4 + (int)(pcVar8 + ((iVar2 - iVar3) - (int)pcVar6)) + 0x14));
        FUN_08020e68(pcVar4,iVar2,&DAT_87c28384);
        for (; *pcVar4 == '/'; pcVar4 = pcVar4 + 1) {
        }
        FUN_08021c68(param_1[4]);
        param_1[4] = 0;
        pcVar5 = pcVar4;
      }
      else {
        iVar3 = 0;
        do {
          if (((&DAT_87c282bc)[iVar3 * 10] == *(short *)(iVar2 + 4)) &&
             ((&DAT_87c282c0)[iVar3 * 5] == *(int *)(iVar2 + 8))) {
            if (iVar3 < 10) {
              FUN_08021c68();
              param_1[4] = (&DAT_87c282c4)[iVar3 * 5];
              FUN_08021c60();
            }
            break;
          }
          iVar3 = iVar3 + 1;
        } while (iVar3 < 10);
        if (*pcVar6 == '\0') goto LAB_08021218;
        FUN_08021c68(param_1[3]);
        param_1[3] = param_1[4];
        param_1[4] = 0;
        for (pcVar4 = pcVar6; pcVar5 = pcVar4, *pcVar4 == '/'; pcVar4 = pcVar4 + 1) {
        }
      }
      goto LAB_080210f0;
    }
    if (*pcVar6 != '\0') goto LAB_0802123a;
LAB_08021218:
    if ((param_3 << 0x18 < 0) && (param_1[4] != 0)) {
      iVar2 = -0x3ee;
    }
    else {
      if ((param_3 << 0x19 < 0) || (param_1[4] != 0)) {
        return 0;
      }
      iVar2 = -0x3ea;
    }
LAB_0802123a:
    if (param_1[3] != 0) {
      FUN_08021c68();
      param_1[3] = 0;
    }
    if (param_1[4] != 0) {
      FUN_08021c68();
      param_1[4] = 0;
    }
  }
  else {
    iVar2 = -0x40c;
  }
  return iVar2;
}




/* 0x08021278 */
void FUN_08021278()
{
  uint uVar1;
  
  uVar1 = 0;
  do {
    (&DAT_87c284b0)[uVar1 * 4] = &PTR_FUN_080282ac_1_0803b0cc;
    FUN_08021000("nodev");
    uVar1 = uVar1 + 1;
  } while (uVar1 < 5);
  return;
}




/* 0x080212a4 */
undefined * FUN_080212a4()
{
  return &DAT_0804d618;
}




/* 0x080212ac */
void FUN_080212ac(param_1, param_2)
uint param_1; short * param_2;
{
  ushort uVar1;
  short sVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined2 *puVar8;
  
  FUN_08006cd0(param_2,0xe);
  if (0x12cea5ff < param_1) {
    uVar4 = param_1 + 0xed315a00;
    if (0xe205797f < uVar4) {
      uVar4 = param_1 + 0xed32ab80;
    }
    sVar2 = (short)(uVar4 / 0x3c);
    param_2[5] = (short)uVar4 + sVar2 * -0x3c;
    uVar4 = (uVar4 / 0x3c) / 0x3c;
    sVar3 = (short)uVar4;
    param_2[4] = sVar2 + sVar3 * -0x3c;
    uVar4 = uVar4 / 0x18;
    param_2[3] = sVar3 + (short)uVar4 * -0x18;
    sVar2 = (short)(uVar4 / 0x5b5) * 4 + 0x7bc;
    *param_2 = sVar2;
    for (iVar5 = 0; (uint)(ushort)(&DAT_0803c92a)[iVar5] <= uVar4 % 0x5b5; iVar5 = iVar5 + 1) {
    }
    uVar1 = (&DAT_0803c928)[iVar5];
    *param_2 = sVar2 + (short)iVar5;
    uVar6 = uVar4 % 0x5b5 - (uint)uVar1;
    uVar7 = uVar6 & 0xffff;
    uVar4 = (uVar4 / 0x5b5) * 5 + uVar7 + (uint)(ushort)(&DAT_0803c920)[iVar5];
    param_2[6] = (short)uVar4 + (short)(uVar4 / 7) * -7;
    if (iVar5 == 0) {
      puVar8 = &DAT_0803c94c;
    }
    else {
      puVar8 = (undefined2 *)&UNK_0803c932;
    }
    iVar5 = 0;
    while ((ushort)puVar8[iVar5 + 1] <= uVar7) {
      iVar5 = iVar5 + 1;
    }
    param_2[2] = ((short)uVar6 - puVar8[iVar5]) + 1;
    param_2[1] = (short)iVar5 + 1;
  }
  return;
}




/* 0x08021380 */
ushort FUN_08021380(param_1, param_2, param_3, param_4)
uint param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  ushort uVar1;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  if (param_1 < 0x12cea600) {
    uVar1 = 0x21;
  }
  else {
    local_18 = param_1;
    local_14 = param_2;
    uStack_10 = param_3;
    uStack_c = param_4;
    FUN_080212ac(param_1,&local_18);
    uVar1 = (short)local_18 * 0x200 + 0x8800U | (_GHIDRA_FIELD(local_18, 2, ushort) & 0xf) << 5 |
            (ushort)local_14 & 0x1f;
  }
  return uVar1;
}




/* 0x080213c0 */
uint FUN_080213c0(param_1)
uint param_1;
{
  if (param_1 < 0x12cea600) {
    return 0;
  }
  return (((param_1 / 0x3c) / 0x3c) % 0x18) * 0x800 | ((param_1 / 0x3c) % 0x3c) * 0x20 |
         (param_1 % 0x3c << 0x1a) >> 0x1b;
}




/* 0x0802141c */
int FUN_0802141c(param_1, param_2, param_3)
int param_1; undefined4 param_2; int param_3;
{
  int iVar1;
  
  if ((*(uint *)(param_1 + 0xc) & 1) == 1) {
    return -0x3f1;
  }
  if (param_3 != 0) {
    iVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 0x14) + 0x14) + 0x14))
                      (*(int *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0x10),param_2,param_3);
    if (0 < iVar1) {
      *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + iVar1;
    }
    return iVar1;
  }
  return 0;
}




/* 0x08021454 */
int FUN_08021454(param_1, param_2, param_3)
int param_1; undefined4 param_2; int param_3;
{
  int iVar1;
  int iVar2;
  int local_40 [3];
  int local_34;
  int local_14;
  
  local_40[0] = *(int *)(param_1 + 0xc);
  if (local_40[0] * 0x40000000 + 0x40000000 < 0) {
    if (param_3 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 0x14) + 0x14) + 0x10))
                        (*(int *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0x10),param_2,param_3);
      if (0 < iVar1) {
        if (*(int *)(param_1 + 0xc) << 0x15 < 0) {
          iVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x14) + 0x14) + 0x34))
                            (*(int *)(param_1 + 0x14),&local_14);
          if ((iVar2 != 0) &&
             (iVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x14) + 0x14) + 0x30))
                                (*(int *)(param_1 + 0x14),local_40), local_14 = local_34, iVar2 != 0
             )) {
            return iVar1;
          }
        }
        else {
          local_14 = *(int *)(param_1 + 0x10) + iVar1;
        }
        *(int *)(param_1 + 0x10) = local_14;
      }
    }
  }
  else {
    iVar1 = -0x3f1;
  }
  return iVar1;
}




