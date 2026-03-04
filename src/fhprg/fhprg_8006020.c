/* Auto-generated: fhprg_8006020.c */
/* Functions: 47 */
#include "globals.h"

/* 0x08006020 */
undefined4 FUN_08006020(param_1, param_2, param_3)
uint * param_1; uint param_2; uint * param_3;
{
  uint uVar1;
  char cVar2;
  undefined1 uVar3;
  char extraout_r1;
  char extraout_r1_00;
  int iVar4;
  undefined4 *puVar5;
  uint *puVar6;
  char extraout_r2;
  int *piVar7;
  int iVar8;
  undefined *puVar9;
  undefined4 uVar10;
  uint uVar11;
  uint uVar12;
  char *pcVar13;
  uint unaff_r5 = 0;
  int unaff_r6 = 0;
  char *pcVar14;
  int unaff_r9 = 0;
  int unaff_r10 = 0;
  uint unaff_r11 = 0;
  bool bVar15;
  longlong lVar16;
  undefined1 local_64 [32];
  int local_44;
  undefined4 local_40;
  int local_3c;
  int local_38;
  uint uStack_34;
  int local_30;
  char local_27 [3];
  
  if (param_2 == 0x6e) {
    param_3 = (uint *)*param_3;
    uVar12 = *param_1;
    uVar11 = param_1[8];
    if ((int)(uVar12 << 0x15) < 0) {
      *(char *)param_3 = (char)uVar11;
    }
    else if ((int)(uVar12 << 0x17) < 0) {
      *(short *)param_3 = (short)uVar11;
    }
    else if ((int)(uVar12 << 0x18) < 0) {
      *param_3 = uVar11;
      param_3[1] = (int)uVar11 >> 0x1f;
    }
    else {
      *param_3 = uVar11;
    }
    return 1;
  }
  if (param_2 == 0x70) {
    uVar11 = *param_3;
    *param_1 = *param_1 | 0x20;
    param_1[7] = 8;
    uVar12 = 0;
    goto LAB_08006614;
  }
  if (((param_2 != 0x66) && (param_2 != 0x65)) && (param_2 != 0x67)) {
    uVar11 = *param_1 >> 8;
    if ((*param_1 >> 7 & 1) != 0) {
      param_2 = param_2 | 0x80;
    }
    if (((param_2 == 0x69) || (param_2 == 100)) || (param_2 == 0x75)) {
      uVar10 = 0;
      puVar9 = &UNK_0800658c;
      if (param_2 == 0x75) {
        iVar4 = FUN_08006f4a(*param_3,param_1,param_3,uVar11);
      }
      else {
        iVar4 = FUN_08006f38();
        if (iVar4 < 0) {
          iVar4 = -iVar4;
          puVar9 = &DAT_08006590;
        }
        else if ((int)(*param_1 << 0x1e) < 0) {
          puVar9 = &UNK_08006594;
        }
        else {
          if (-1 < (int)(*param_1 << 0x1d)) goto LAB_08006564;
          puVar9 = &UNK_08006598;
        }
        uVar10 = 1;
      }
LAB_08006564:
      iVar8 = 0;
      while (iVar4 != 0) {
        iVar4 = FUN_08007418();
        *(char *)((int)param_1 + iVar8 + 0x24) = extraout_r1 + '0';
        iVar8 = iVar8 + 1;
      }
      uVar10 = FUN_08006f5c(param_1,iVar8,puVar9,uVar10);
      return uVar10;
    }
    if (param_2 == 0x6f) {
      uVar11 = FUN_08006f4a(*param_3,param_1,param_3,uVar11);
      uVar12 = 0;
LAB_08007174:
      iVar4 = 0;
      for (; uVar11 != 0 || uVar12 != 0; uVar11 = uVar11 >> 3 | uVar1) {
        uVar1 = uVar12 << 0x1d;
        *(byte *)((int)param_1 + iVar4 + 0x24) = ((byte)uVar11 & 7) + 0x30;
        iVar4 = iVar4 + 1;
        uVar12 = uVar12 >> 3;
      }
      uVar10 = 0;
      puVar9 = &DAT_080071e4;
      if (((int)(*param_1 << 0x1c) < 0) && ((*param_1 & 0x20) != 0 || iVar4 != 0)) {
        uVar10 = 1;
        puVar9 = &DAT_080071e8;
        param_1[7] = param_1[7] - 1;
      }
      uVar10 = FUN_08006f5c(param_1,iVar4,puVar9,uVar10);
      return uVar10;
    }
    if (param_2 == 0x78) {
      uVar11 = FUN_08006f4a(*param_3,param_1,param_3,uVar11);
      uVar12 = 0;
    }
    else {
      if (((param_2 == 0xe9) || (param_2 == 0xe4)) || (param_2 == 0xf5)) {
        piVar7 = (int *)((int)param_3 + 7U & 0xfffffff8);
        uVar10 = 0;
        iVar4 = *piVar7;
        iVar8 = piVar7[1];
        puVar9 = &UNK_08006604;
        if (param_2 != 0xf5) {
          if (iVar8 < 0) {
            bVar15 = iVar4 != 0;
            iVar4 = -iVar4;
            iVar8 = -(uint)bVar15 - iVar8;
            puVar9 = &DAT_08006608;
          }
          else if ((int)(*param_1 << 0x1e) < 0) {
            puVar9 = &UNK_0800660c;
          }
          else {
            if (-1 < (int)(*param_1 << 0x1d)) goto LAB_080065da;
            puVar9 = &UNK_08006610;
          }
          uVar10 = 1;
        }
LAB_080065da:
        lVar16 = CONCAT44(iVar8,iVar4);
        iVar4 = 0;
        while (lVar16 != 0) {
          lVar16 = FUN_08006ea0();
          *(char *)((int)param_1 + iVar4 + 0x24) = extraout_r2 + '0';
          iVar4 = iVar4 + 1;
        }
        uVar10 = FUN_08006f5c(param_1,iVar4,puVar9,uVar10);
        return uVar10;
      }
      if (param_2 == 0xef) {
        puVar6 = (uint *)((int)param_3 + 7U & 0xfffffff8);
        uVar11 = *puVar6;
        uVar12 = puVar6[1];
        goto LAB_08007174;
      }
      if (param_2 != 0xf8) {
        if ((*param_1 >> 6 & 1) != 0) {
          param_2 = param_2 | 0x80;
        }
        if (param_2 == 99) {
          puVar6 = param_1 + 9;
          *(char *)puVar6 = (char)*param_3;
          *(undefined1 *)((int)param_1 + 0x25) = 0;
          uVar10 = 1;
        }
        else {
          if (param_2 != 0x73) {
            if (param_2 == 0xe3) {
              puVar6 = param_1 + 9;
              *(short *)(param_1 + 9) = (short)*param_3;
              *(undefined2 *)((int)param_1 + 0x26) = 0;
              uVar10 = 1;
            }
            else {
              if (param_2 != 0xf3) {
                return 0;
              }
              puVar6 = (uint *)*param_3;
              uVar10 = 0xffffffff;
            }
            if (param_1[5] == 0) {
              FUN_080070b8(param_1,puVar6,uVar10);
            }
            return 1;
          }
          puVar6 = (uint *)*param_3;
          uVar10 = 0xffffffff;
        }
        if (param_1[5] == 0) {
          FUN_080064d6(param_1,puVar6,uVar10);
        }
        return 1;
      }
      puVar6 = (uint *)((int)param_3 + 7U & 0xfffffff8);
      uVar11 = *puVar6;
      uVar12 = puVar6[1];
    }
LAB_08006614:
    if ((int)(*param_1 << 0x14) < 0) {
      pcVar13 = "0123456789ABCDEF@0X";
    }
    else {
      pcVar13 = "0123456789abcdef@0x";
    }
    iVar4 = 0;
    for (; uVar11 != 0 || uVar12 != 0; uVar11 = uVar11 >> 4 | uVar1) {
      uVar1 = uVar12 << 0x1c;
      uVar12 = uVar12 >> 4;
      *(char *)((int)param_1 + iVar4 + 0x24) = pcVar13[uVar11 & 0xf];
      iVar4 = iVar4 + 1;
    }
    uVar10 = 0;
    if ((int)(*param_1 << 0x1c) < 0) {
      if (param_2 == 0x70) {
        pcVar13 = pcVar13 + 0x10;
        uVar10 = 1;
      }
      else if (iVar4 != 0) {
        pcVar13 = pcVar13 + 0x11;
        uVar10 = 2;
      }
    }
    uVar10 = FUN_08006f5c(param_1,iVar4,pcVar13,uVar10);
    return uVar10;
  }
  puVar5 = (undefined4 *)((int)param_3 + 7U & 0xfffffff8);
  local_40 = *puVar5;
  local_3c = puVar5[1];
  iVar4 = FUN_080108fe();
  if (local_3c < 0) {
    local_44 = 0x2d;
  }
  else if ((int)(*param_1 << 0x1e) < 0) {
    local_44 = 0x2b;
  }
  else {
    local_44 = (*param_1 & 4) << 3;
  }
  if ((iVar4 == 3) || (6 < iVar4)) {
    FUN_0800799c(param_1,param_2,iVar4,local_44);
    return 2;
  }
  if ((int)(*param_1 << 0x1a) < 0) {
    uVar11 = param_1[7];
  }
  else {
    uVar11 = 6;
  }
  if (param_2 == 0x65) {
    if ((int)uVar11 < 0x11) {
      iVar4 = uVar11 + 1;
    }
    else {
      iVar4 = 0x11;
    }
    FUN_0800745a(&local_38,local_64,&local_40,iVar4,0);
    unaff_r5 = uVar11 + 1;
  }
  else {
    if (param_2 == 0x66) {
      unaff_r9 = -0x80000000;
      FUN_0800745a(&local_38,local_64,&local_40,uVar11,1);
      unaff_r6 = 0;
      unaff_r5 = uStack_34;
      if (local_30 == 0) {
        unaff_r5 = local_38 + uVar11 + 1;
      }
      iVar4 = uVar11 - unaff_r5;
      if (-1 < iVar4) {
        unaff_r5 = uVar11 + 1;
        unaff_r6 = -1 - iVar4;
      }
      unaff_r10 = unaff_r5 - uVar11;
      unaff_r11 = uStack_34;
      goto LAB_08007748;
    }
    if (param_2 != 0x67) goto LAB_08007748;
    if ((int)uVar11 < 1) {
      uVar11 = 1;
    }
    uVar12 = uVar11;
    if (0x11 < (int)uVar11) {
      uVar12 = 0x11;
    }
    FUN_0800745a(&local_38,local_64,&local_40,uVar12,0);
    unaff_r6 = 0;
    unaff_r5 = uVar11;
    if (-1 < (int)(*param_1 << 0x1c)) {
      if ((int)uStack_34 < (int)uVar11) {
        unaff_r5 = uStack_34;
      }
      for (; (1 < (int)unaff_r5 && (local_64[unaff_r5 - 1] == '0')); unaff_r5 = unaff_r5 - 1) {
      }
    }
    if ((local_38 < (int)uVar11) && (-5 < local_38)) {
      if (local_38 < 1) {
        unaff_r5 = unaff_r5 - local_38;
        unaff_r6 = local_38;
      }
      else if ((int)unaff_r5 < (int)(local_38 + 1U)) {
        unaff_r5 = local_38 + 1U;
      }
      unaff_r10 = (local_38 - unaff_r6) + 1;
      unaff_r9 = -0x80000000;
      unaff_r11 = uStack_34;
      goto LAB_08007748;
    }
  }
  unaff_r6 = 0;
  unaff_r10 = 1;
  unaff_r9 = local_38;
  unaff_r11 = uStack_34;
LAB_08007748:
  if ((-1 < (int)(*param_1 << 0x1c)) && ((int)unaff_r5 <= unaff_r10)) {
    unaff_r10 = -1;
  }
  pcVar13 = local_27 + 2;
  local_27[2] = 0;
  if (unaff_r9 != -0x80000000) {
    uVar10 = 0x2b;
    iVar4 = 2;
    if (unaff_r9 < 0) {
      unaff_r9 = -unaff_r9;
      uVar10 = 0x2d;
    }
    while ((0 < iVar4 || (unaff_r9 != 0))) {
      unaff_r9 = FUN_08007418(unaff_r9);
      pcVar13 = pcVar13 + -1;
      *pcVar13 = extraout_r1_00 + '0';
      iVar4 = iVar4 + -1;
    }
    pcVar13[-1] = (char)uVar10;
    if ((int)(*param_1 << 0x14) < 0) {
      cVar2 = 'E';
    }
    else {
      cVar2 = 'e';
    }
    pcVar13 = pcVar13 + -2;
    *pcVar13 = cVar2;
  }
  pcVar14 = local_27 + (2 - (int)pcVar13);
  param_1[6] = (param_1[6] - (int)(pcVar14 + (local_44 != 0) + unaff_r5 + (unaff_r10 >> 0x1f))) - 1;
  if (-1 < (int)(*param_1 << 0x1b)) {
    FUN_08006484(param_1);
  }
  if (local_44 != 0) {
    ((code *)param_1[1])(local_44,param_1[2]);
    param_1[8] = param_1[8] + 1;
  }
  if ((int)(*param_1 << 0x1b) < 0) {
    FUN_08006484(param_1);
  }
  while (uVar11 = unaff_r5 - 1, 0 < (int)unaff_r5) {
    if ((unaff_r6 < 0) || ((int)unaff_r11 <= unaff_r6)) {
      uVar3 = 0x30;
    }
    else {
      uVar3 = local_64[unaff_r6];
    }
    ((code *)param_1[1])(uVar3,param_1[2]);
    unaff_r6 = unaff_r6 + 1;
    unaff_r10 = unaff_r10 + -1;
    param_1[8] = param_1[8] + 1;
    unaff_r5 = uVar11;
    if (unaff_r10 == 0) {
      iVar4 = FUN_08006e98();
      ((code *)param_1[1])
                (*(undefined1 *)((int)*(int **)(iVar4 + 0xc) + **(int **)(iVar4 + 0xc)),param_1[2]);
      param_1[8] = param_1[8] + 1;
    }
  }
  while (0 < (int)pcVar14) {
    ((code *)param_1[1])(*pcVar13,param_1[2]);
    param_1[8] = param_1[8] + 1;
    pcVar13 = pcVar13 + 1;
    pcVar14 = pcVar14 + -1;
  }
  FUN_080064b2(param_1);
  return 2;
}




/* 0x080060b0 */
int FUN_080060b0()
{
  int iVar1;
  
  iVar1 = FUN_08006e98();
  return iVar1 + 4;
}




/* 0x080060c0 */
ulonglong FUN_080060c0(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; uint param_3; uint param_4;
{
  longlong lVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  bool bVar12;
  ulonglong uVar13;
  
  bVar11 = param_4 == 0;
  uVar9 = param_4;
  if (bVar11) {
    uVar9 = param_3;
  }
  uVar10 = LZCOUNT(uVar9);
  uVar9 = uVar9 << uVar10 + 1;
  uVar5 = 0;
  if (!bVar11) {
    uVar10 = 0x3f - uVar10;
    bVar11 = uVar10 == 0;
    uVar5 = uVar10;
  }
  if (bVar11) {
    uVar10 = 0x1f - uVar10;
    uVar5 = uVar10;
  }
  if ((int)uVar5 < 0) {
    uVar13 = thunk_FUN_08007446(0,0,param_1,param_2,param_1,param_2);
    return uVar13;
  }
  if (param_2 == 0) {
    iVar4 = LZCOUNT(param_1);
    bVar11 = true;
  }
  else {
    iVar4 = 0x3f - LZCOUNT(param_2);
    bVar11 = iVar4 == 0;
  }
  if (bVar11) {
    iVar4 = 0x1f - iVar4;
  }
  uVar5 = iVar4 - uVar10;
  if ((int)uVar5 < 0) {
    return 0;
  }
  if (-1 < (int)(4 - uVar5)) {
    uVar6 = 0;
    uVar10 = param_3 << (uVar5 & 0xff);
    uVar9 = param_4 << (uVar5 & 0xff) | param_3 >> (0x20 - uVar5 & 0xff);
    while( true ) {
      bVar12 = uVar10 <= param_1;
      bVar11 = param_2 - uVar9 < (uint)bVar12;
      uVar6 = uVar6 * 2 + (uint)(uVar9 < param_2 || bVar11);
      if (uVar9 < param_2 || bVar11) {
        param_1 = param_1 - uVar10;
        param_2 = param_2 - (uVar9 + !bVar12);
      }
      bVar11 = uVar5 == 0;
      uVar5 = uVar5 - 1;
      if (bVar11) break;
      bVar2 = (byte)uVar9;
      uVar9 = uVar9 >> 1;
      uVar10 = (uint)(bVar2 & 1) << 0x1f | uVar10 >> 1;
    }
    return (ulonglong)uVar6;
  }
  if ((int)(uVar10 - 0x20) < 5) {
    uVar9 = uVar9 | param_3 >> (uVar10 - 0x20 & 0xff);
  }
  uVar5 = *(uint *)(&DAT_080063b0 + (uVar9 >> 0x1c) * 4);
  uVar9 = uVar10;
  if (0x1f < uVar10) {
    uVar9 = uVar10 - 0x20;
  }
  uVar6 = 0x20 - uVar9;
  if (0x1f < uVar10) {
    lVar1 = (ulonglong)param_4 * (ulonglong)uVar5 + ((ulonglong)param_3 * (ulonglong)uVar5 >> 0x20);
    uVar3 = (uint)lVar1;
    uVar10 = -((int)((ulonglong)lVar1 >> 0x20) << (uVar6 & 0xff) | uVar3 >> (uVar9 & 0xff));
    if (uVar3 << (0x20 - uVar9 & 0xff) != 0) {
      uVar10 = uVar10 - 1;
    }
    uVar5 = uVar5 + (int)((ulonglong)uVar10 * (ulonglong)uVar5 >> 0x20);
    lVar1 = (ulonglong)param_4 * (ulonglong)uVar5 + ((ulonglong)param_3 * (ulonglong)uVar5 >> 0x20);
    uVar6 = (uint)lVar1;
    uVar10 = -((int)((ulonglong)lVar1 >> 0x20) << (0x20 - uVar9 & 0xff) | uVar6 >> (uVar9 & 0xff));
    if (uVar6 << (0x20 - uVar9 & 0xff) != 0) {
      uVar10 = uVar10 - 1;
    }
    uVar3 = (uVar5 + (int)((ulonglong)uVar10 * (ulonglong)uVar5 >> 0x20)) - 1;
    uVar5 = (uint)((ulonglong)param_2 * (ulonglong)uVar3 +
                   ((ulonglong)param_1 * (ulonglong)uVar3 >> 0x20) >> 0x20) >> (uVar9 & 0xff);
    uVar6 = (uint)((ulonglong)param_3 * (ulonglong)uVar5);
    uVar10 = param_1 - uVar6;
    param_2 = param_2 - (uVar5 * param_4 + (int)((ulonglong)param_3 * (ulonglong)uVar5 >> 0x20) +
                        (uint)(param_1 < uVar6));
    bVar11 = param_4 <= param_2;
    if (param_2 == param_4) {
      bVar11 = param_3 <= uVar10;
    }
    if (bVar11) {
      uVar9 = (uint)((ulonglong)param_2 * (ulonglong)uVar3 +
                     ((ulonglong)uVar10 * (ulonglong)uVar3 >> 0x20) >> 0x20) >> (uVar9 & 0xff);
      uVar6 = (uint)((ulonglong)param_3 * (ulonglong)uVar9);
      param_2 = param_2 - (uVar9 * param_4 + (int)((ulonglong)param_3 * (ulonglong)uVar9 >> 0x20) +
                          (uint)(uVar10 < uVar6));
      bVar11 = param_4 <= param_2;
      if (param_2 == param_4) {
        bVar11 = param_3 <= uVar10 - uVar6;
      }
      if (bVar11) {
        return (ulonglong)(uVar5 + uVar9 + 1);
      }
      return (ulonglong)(uVar5 + uVar9);
    }
    return (ulonglong)uVar5;
  }
  uVar3 = (uint)((ulonglong)param_3 * (ulonglong)uVar5);
  uVar10 = -((int)((ulonglong)param_3 * (ulonglong)uVar5 >> 0x20) << (uVar6 & 0xff) |
            uVar3 >> (uVar9 & 0xff));
  if (uVar3 << (uVar6 & 0xff) != 0) {
    uVar10 = uVar10 - 1;
  }
  uVar5 = uVar5 + (int)((ulonglong)uVar10 * (ulonglong)uVar5 >> 0x20);
  uVar3 = (uint)((ulonglong)param_3 * (ulonglong)uVar5);
  uVar10 = -((int)((ulonglong)param_3 * (ulonglong)uVar5 >> 0x20) << (uVar6 & 0xff) |
            uVar3 >> (uVar9 & 0xff));
  if (uVar3 << (uVar6 & 0xff) != 0) {
    uVar10 = uVar10 - 1;
  }
  uVar5 = uVar5 + (int)((ulonglong)uVar10 * (ulonglong)uVar5 >> 0x20);
  if (param_2 != 0) {
    uVar3 = (uint)((ulonglong)param_3 * (ulonglong)uVar5);
    uVar10 = -((int)((ulonglong)param_3 * (ulonglong)uVar5 >> 0x20) << (uVar6 & 0xff) |
              uVar3 >> (uVar9 & 0xff));
    if (uVar3 << (uVar6 & 0xff) != 0) {
      uVar10 = uVar10 - 1;
    }
    uVar5 = uVar5 + (int)((ulonglong)uVar10 * (ulonglong)uVar5 >> 0x20);
  }
  lVar1 = (ulonglong)param_2 * (ulonglong)uVar5 + ((ulonglong)param_1 * (ulonglong)uVar5 >> 0x20);
  uVar10 = (uint)((ulonglong)lVar1 >> 0x20);
  uVar3 = (uint)lVar1 >> (uVar9 & 0xff) | uVar10 << (uVar6 & 0xff);
  uVar10 = uVar10 >> (uVar9 & 0xff);
  uVar7 = (uint)((ulonglong)param_3 * (ulonglong)uVar3);
  uVar6 = param_1 - uVar7;
  param_2 = param_2 - (uVar10 * param_3 + (int)((ulonglong)param_3 * (ulonglong)uVar3 >> 0x20) +
                      (uint)(param_1 < uVar7));
  if (param_2 != 0 || param_3 <= uVar6) {
    lVar1 = (ulonglong)param_2 * (ulonglong)uVar5 + ((ulonglong)uVar6 * (ulonglong)uVar5 >> 0x20);
    uVar7 = (uint)((ulonglong)lVar1 >> 0x20);
    uVar8 = (uint)lVar1 >> (uVar9 & 0xff) | uVar7 << (0x20 - uVar9 & 0xff);
    uVar5 = uVar3 + uVar8;
    iVar4 = uVar10 + (uVar7 >> (uVar9 & 0xff)) + (uint)CARRY4(uVar3,uVar8);
    uVar6 = uVar6 - param_3 * uVar8;
    if (param_3 <= uVar6) {
      uVar6 = uVar6 - param_3;
      bVar11 = param_3 <= uVar6;
      if (bVar11) {
        uVar6 = uVar6 - param_3;
      }
      uVar9 = uVar5 + 1 + (uint)bVar11;
      return CONCAT44(iVar4 + (uint)(0xfffffffe < uVar5) + (uint)CARRY4(uVar5 + 1,(uint)bVar11) +
                      (uint)CARRY4(uVar9,(uint)(param_3 <= uVar6)),uVar9 + (param_3 <= uVar6));
    }
    return CONCAT44(iVar4,uVar5);
  }
  return CONCAT44(uVar10,uVar3);
}




/* 0x080063f0 */
longlong FUN_080063f0(param_1, param_2, param_3)
uint param_1; int param_2; uint param_3;
{
  if ((int)(param_3 - 0x20) < 0) {
    return CONCAT44(param_2 << (param_3 & 0xff) | param_1 >> (0x20 - param_3 & 0xff),
                    param_1 << (param_3 & 0xff));
  }
  return (ulonglong)(param_1 << (param_3 - 0x20 & 0xff)) << 0x20;
}




/* 0x08006418 */
undefined4 FUN_08006418(param_1, param_2, param_3, param_4)
int param_1; int param_2; undefined4 param_3; undefined4 param_4;
{
  undefined4 uVar1;
  int local_18;
  int local_14;
  
  local_14 = param_1;
  if (param_2 != 0) {
    local_14 = param_1 + param_2 + -1;
  }
  local_18 = param_1;
  uVar1 = FUN_0800704a(param_3,&local_18,param_4,&LAB_0800707a);
  if (param_2 != 0) {
    FUN_08007070(0,&local_18);
  }
  return uVar1;
}




/* 0x0800644c */
undefined4 snprintf_buf(param_1, param_2, param_3, param_4)
int param_1; int param_2; undefined4 param_3; undefined4 param_4;
{
  undefined4 uVar1;
  int local_28;
  int local_24;
  undefined4 uStack_4;
  
  local_24 = param_1;
  if (param_2 != 0) {
    local_24 = param_1 + param_2 + -1;
  }
  local_28 = param_1;
  uStack_4 = param_4;
  uVar1 = FUN_0800704a(param_3,&local_28,&uStack_4,&LAB_0800707a);
  if (param_2 != 0) {
    FUN_08007070(0,&local_28);
  }
  return uVar1;
}




/* 0x08006484 */
void FUN_08006484(param_1)
uint * param_1;
{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = param_1[6];
  if ((int)(*param_1 << 0x1b) < 0) {
    uVar2 = 0x30;
  }
  else {
    uVar2 = 0x20;
  }
  if ((*param_1 & 1) != 0) {
    return;
  }
  while (uVar1 = uVar1 - 1, -1 < (int)uVar1) {
    ((code *)param_1[1])(uVar2,param_1[2]);
    param_1[8] = param_1[8] + 1;
  }
  return;
}




/* 0x080064b2 */
void FUN_080064b2(param_1)
uint * param_1;
{
  uint uVar1;
  
  uVar1 = param_1[6];
  if ((*param_1 & 1) == 0) {
    return;
  }
  while (uVar1 = uVar1 - 1, -1 < (int)uVar1) {
    ((code *)param_1[1])(0x20,param_1[2]);
    param_1[8] = param_1[8] + 1;
  }
  return;
}




/* 0x080064d6 */
void FUN_080064d6(param_1, param_2, param_3)
int * param_1; undefined1 * param_2; uint param_3;
{
  uint uVar1;
  undefined1 *puVar2;
  
  if (param_3 == 1) {
    uVar1 = 1;
  }
  else {
    if (*param_1 << 0x1a < 0) {
      param_3 = param_1[7];
    }
    for (uVar1 = 0; (uVar1 < param_3 && (param_2[uVar1] != '\0')); uVar1 = uVar1 + 1) {
    }
  }
  puVar2 = param_2 + uVar1;
  param_1[6] = param_1[6] - uVar1;
  param_1[8] = param_1[8] + uVar1;
  FUN_08006484(param_1);
  for (; param_2 < puVar2; param_2 = param_2 + 1) {
    ((code *)param_1[1])(*param_2,param_1[2]);
  }
  FUN_080064b2(param_1);
  return;
}




/* 0x080066b0 */
uint FUN_080066b0(param_1, param_2)
uint * param_1; uint * param_2;
{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint *puVar6;
  
  param_1[8] = 0;
  while (uVar1 = ((code *)param_1[3])(param_1), uVar1 != 0) {
    if (uVar1 == 0x25) {
      uVar4 = 0;
      while (((uVar1 = ((code *)param_1[3])(param_1), 0x1f < (int)uVar1 && (uVar1 < 0x31)) &&
             ((byte)"0123456789ABCDEF@0X"[uVar1 + 8] != 0))) {
        uVar4 = uVar4 | (byte)"0123456789ABCDEF@0X"[uVar1 + 8];
      }
      if ((int)(uVar4 << 0x1e) < 0) {
        uVar4 = uVar4 & 0xfffffffb;
      }
      param_1[7] = 0;
      iVar5 = 0;
      param_1[6] = 0;
      puVar6 = param_2;
      do {
        if (uVar1 == 0x2a) {
          param_2 = puVar6 + 1;
          param_1[iVar5 + 6] = *puVar6;
          uVar1 = ((code *)param_1[3])(param_1);
          if (iVar5 == 1) {
            if ((int)param_1[7] < 0) {
              uVar4 = uVar4 & 0xffffffdf;
            }
            break;
          }
        }
        else {
          iVar2 = FUN_08013520(uVar1);
          if (iVar2 != 0) {
            param_1[iVar5 + 6] = uVar1 - 0x30;
            while( true ) {
              uVar1 = ((code *)param_1[3])(param_1);
              iVar2 = FUN_08013520();
              if (iVar2 == 0) break;
              param_1[iVar5 + 6] = (uVar1 + param_1[iVar5 + 6] * 10) - 0x30;
            }
          }
          param_2 = puVar6;
          if (iVar5 == 1) break;
        }
        if (uVar1 != 0x2e) break;
        uVar1 = ((code *)param_1[3])(param_1);
        iVar5 = iVar5 + 1;
        uVar4 = uVar4 | 0x20;
        puVar6 = param_2;
      } while (iVar5 < 2);
      if ((int)param_1[6] < 0) {
        uVar4 = uVar4 | 1;
        param_1[6] = -param_1[6];
      }
      if ((uVar4 & 1) != 0) {
        uVar4 = uVar4 & 0xffffffef;
      }
      if ((uVar1 == 0x6c) || (uVar1 == 0x68)) {
        uVar3 = ((code *)param_1[3])(param_1);
        if (uVar3 == uVar1) {
          if (uVar1 == 0x6c) goto LAB_0800681e;
          uVar1 = 0x400;
          goto LAB_080067d4;
        }
        if (uVar1 == 0x6c) {
          uVar1 = 0x40;
        }
        else {
          uVar1 = 0x100;
        }
        uVar4 = uVar4 | uVar1;
        uVar1 = uVar3;
      }
      else {
        if (uVar1 != 0x4c) {
          if (uVar1 == 0x6a) {
LAB_0800681e:
            uVar1 = 0x80;
            goto LAB_080067d4;
          }
          if ((uVar1 != 0x74) && (uVar1 != 0x7a)) goto LAB_080067ea;
        }
        uVar1 = 0;
LAB_080067d4:
        uVar4 = uVar4 | uVar1;
        uVar1 = ((code *)param_1[3])(param_1);
      }
LAB_080067ea:
      if (uVar1 == 0) break;
      if (uVar1 - 0x41 < 0x1a) {
        uVar1 = uVar1 + 0x20;
        uVar4 = uVar4 | 0x800;
      }
      *param_1 = uVar4;
      iVar5 = FUN_08006020(param_1,uVar1,param_2);
      if (iVar5 == 0) goto LAB_080066d4;
      if (iVar5 == 1) {
        param_2 = param_2 + 1;
      }
      else {
        param_2 = (uint *)(((int)param_2 + 7U & 0xfffffff8) + 8);
      }
    }
    else {
LAB_080066d4:
      ((code *)param_1[1])(uVar1,param_1[2]);
      param_1[8] = param_1[8] + 1;
    }
  }
  return param_1[8];
}




/* 0x08006840 */
void FUN_08006840(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  FUN_08007302(&DAT_0805a86c,param_1,param_2);
  return;
}




/* 0x08006850 */
char * FUN_08006850()
{
  int iVar1;
  char *pcVar2;
  char extraout_r1;
  
  FUN_08007410(0);
  iVar1 = FUN_08006e88(1);
  pcVar2 = (char *)(iVar1 + -1);
  do {
    pcVar2 = pcVar2 + 1;
    if (extraout_r1 == *pcVar2) {
      return pcVar2;
    }
  } while (*pcVar2 != '\0');
  return (char *)0x0;
}




/* 0x08006860 */
char * FUN_08006860(param_1, param_2)
int param_1; char param_2;
{
  char *pcVar1;
  
  pcVar1 = (char *)(param_1 + -1);
  do {
    pcVar1 = pcVar1 + 1;
    if (param_2 == *pcVar1) {
      return pcVar1;
    }
  } while (*pcVar1 != '\0');
  return (char *)0x0;
}




/* 0x08006874 */
char * FUN_08006874(param_1, param_2)
char * param_1; char * param_2;
{
  char cVar1;
  char cVar2;
  char *pcVar3;
  char *pcVar4;
  
  pcVar3 = param_2;
  pcVar4 = param_1;
LAB_0800687c:
  cVar1 = *pcVar3;
  cVar2 = *param_1;
  if (cVar2 != '\0') goto code_r0x08006886;
  goto LAB_0800688a;
code_r0x08006886:
  param_1 = param_1 + 1;
  pcVar3 = pcVar3 + 1;
  if (cVar2 != cVar1) {
LAB_0800688a:
    pcVar3 = pcVar4;
    if ((cVar1 == '\0') || (pcVar3 = (char *)0x0, cVar2 == '\0')) {
      return pcVar3;
    }
    param_1 = pcVar4 + 1;
    pcVar3 = param_2;
    pcVar4 = param_1;
  }
  goto LAB_0800687c;
}




/* 0x08006898 */
int FUN_08006898(param_1, param_2, param_3)
uint * param_1; uint * param_2; uint param_3;
{
  uint *puVar1;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  if ((((uint)param_1 | (uint)param_2) & 3) == 0) {
    while (3 < param_3) {
      uVar5 = *param_1;
      param_1 = param_1 + 1;
      uVar3 = *param_2;
      param_2 = param_2 + 1;
      param_3 = param_3 - 4;
      if (uVar5 != uVar3) {
        if ((uVar5 << 0x18 | (uVar5 >> 8 & 0xff) << 0x10 | (uVar5 >> 0x10 & 0xff) << 8 |
            uVar5 >> 0x18) <=
            (uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
            uVar3 >> 0x18)) {
          return -1;
        }
        return 1;
      }
    }
  }
  if (param_3 != 0) {
    if ((param_3 & 1) == 0) goto LAB_080068d0;
    param_3 = param_3 + 1;
    puVar1 = param_1;
    puVar2 = param_2;
    while( true ) {
      param_1 = (uint *)((int)puVar1 + 1);
      param_2 = (uint *)((int)puVar2 + 1);
      iVar4 = (uint)(byte)*puVar1 - (uint)(byte)*puVar2;
      if (iVar4 != 0) {
        return iVar4;
      }
      param_3 = param_3 - 2;
      if (param_3 == 0) break;
LAB_080068d0:
      puVar1 = (uint *)((int)param_1 + 1);
      puVar2 = (uint *)((int)param_2 + 1);
      iVar4 = (uint)(byte)*param_1 - (uint)(byte)*param_2;
      if (iVar4 != 0) {
        return iVar4;
      }
    }
    return 0;
  }
  return 0;
}




/* 0x080068f0 */
char * FUN_080068f0(param_1, param_2)
char * param_1; char param_2;
{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = (char *)0x0;
  do {
    cVar1 = *param_1;
    if (cVar1 == param_2) {
      pcVar2 = param_1;
    }
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  return pcVar2;
}




/* 0x08006906 */
int FUN_08006906(param_1)
uint * param_1;
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  short sVar5;
  int3 iVar6;
  uint *puVar7;
  uint *puVar8;
  int iVar9;
  uint uVar10;
  
  puVar8 = param_1;
  while (((uint)puVar8 & 3) != 0) {
    puVar7 = (uint *)((int)puVar8 + 1);
    uVar10 = *puVar8;
    puVar8 = puVar7;
    if ((char)uVar10 == '\0') {
      return (int)puVar7 - ((int)param_1 + 1);
    }
  }
  do {
    uVar10 = *puVar8;
    puVar8 = puVar8 + 1;
    uVar1 = UnsignedSaturate(1 - (uVar10 & 0xff),8);
    uVar2 = UnsignedSaturate(1 - (uVar10 >> 8 & 0xff),8);
    uVar3 = UnsignedSaturate(1 - (uVar10 >> 0x10 & 0xff),8);
    uVar4 = UnsignedSaturate(1 - (uVar10 >> 0x18),8);
    sVar5 = CONCAT11((char)uVar2,(char)uVar1);
    iVar6 = CONCAT12((char)uVar3,sVar5);
  } while (CONCAT13((char)uVar4,iVar6) == 0);
  iVar9 = (int)puVar8 - (int)((int)param_1 + 1);
  if ((char)uVar1 == '\0') {
    if (sVar5 == 0) {
      if (iVar6 != 0) {
        return iVar9 + -1;
      }
    }
    else {
      iVar9 = iVar9 + -2;
    }
    return iVar9;
  }
  return iVar9 + -3;
}




/* 0x08006940 */
uint FUN_08006940(param_1, param_2, param_3)
uint * param_1; uint * param_2; uint param_3;
{
  char cVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  bool bVar5;
  bool bVar6;
  uint uVar7;
  byte *pbVar8;
  byte *pbVar9;
  uint uVar10;
  uint uVar11;
  
  if ((((uint)param_1 | (uint)param_2) & 3) == 0) {
    while (3 < param_3) {
      uVar10 = *param_1;
      uVar11 = *param_2;
      param_3 = param_3 - 4;
      cVar1 = UnsignedSaturate('\x01' - (char)uVar10,0x10);
      uVar2 = UnsignedSaturate('\x01' - (char)(uVar10 >> 8),0x10);
      uVar3 = UnsignedSaturate('\x01' - (char)(uVar10 >> 0x10),0x10);
      uVar4 = UnsignedSaturate('\x01' - (char)(uVar10 >> 0x18),0x10);
      if ((((uVar4 & 0xff) != 0 || uVar3 != 0) || uVar2 != 0) || cVar1 != '\0') {
        uVar7 = (uVar10 & 0xff) - (uVar11 & 0xff);
        if (uVar7 != 0 || cVar1 != '\0') {
          return uVar7;
        }
        uVar7 = (uVar10 & 0xffff) - (uVar11 & 0xffff);
        if (uVar7 != 0 || ((uVar2 & 0xff) != 0 || cVar1 != '\0')) {
          return uVar7;
        }
        uVar7 = (uVar10 & 0xffffff) - (uVar11 & 0xffffff);
        bVar5 = uVar7 == 0;
        bVar6 = (uVar3 & 0xff) == 0;
        if (bVar5 && ((bVar6 && uVar2 == 0) && cVar1 == '\0')) {
          uVar7 = uVar10 >> 0x18;
        }
        if (bVar5 && ((bVar6 && uVar2 == 0) && cVar1 == '\0')) {
          uVar7 = uVar7 - (uVar11 >> 0x18);
        }
        return uVar7;
      }
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
      if (uVar10 != uVar11) {
        if ((uVar11 << 0x18 | (uVar11 >> 8 & 0xff) << 0x10 | (uVar11 >> 0x10 & 0xff) << 8 |
            uVar11 >> 0x18) <
            (uVar10 << 0x18 | (uVar10 >> 8 & 0xff) << 0x10 | (uVar10 >> 0x10 & 0xff) << 8 |
            uVar10 >> 0x18)) {
          uVar10 = 1;
        }
        else {
          uVar10 = 0xffffffff;
        }
        return uVar10;
      }
    }
  }
  if (param_3 == 0) {
    return 0;
  }
  while( true ) {
    pbVar8 = (byte *)((int)param_1 + 1);
    uVar10 = (uint)(byte)*param_1;
    pbVar9 = (byte *)((int)param_2 + 1);
    uVar11 = (uint)(byte)*param_2;
    if (((uVar10 == 0) || (uVar10 != uVar11)) || (param_3 == 1)) break;
    param_1 = (uint *)((int)param_1 + 2);
    uVar10 = (uint)*pbVar8;
    param_2 = (uint *)((int)param_2 + 2);
    uVar11 = (uint)*pbVar9;
    if (((uVar10 == 0) || (uVar10 != uVar11)) || (param_3 = param_3 - 2, param_3 == 0)) break;
  }
  return uVar10 - uVar11;
}




/* 0x08006a30 */
undefined8 FUN_08006a30(param_1, param_2, param_3, param_4)
uint * param_1; uint * param_2; uint param_3; uint param_4;
{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  byte *pbVar4;
  uint *puVar5;
  byte bVar6;
  undefined2 uVar7;
  byte bVar8;
  uint in_r12 = 0;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  bool bVar13;
  bool bVar14;
  
  if (3 < param_3) {
    uVar9 = (uint)param_1 & 3;
    in_r12 = uVar9;
    if (uVar9 != 0) {
      bVar6 = (byte)*param_2;
      puVar3 = (uint *)((int)param_2 + 1);
      if (uVar9 < 3) {
        puVar3 = (uint *)((int)param_2 + 2);
        in_r12 = (uint)*(byte *)((int)param_2 + 1);
      }
      *(byte *)param_1 = bVar6;
      param_2 = puVar3;
      if (uVar9 < 2) {
        param_2 = (uint *)((int)puVar3 + 1);
        bVar6 = (byte)*puVar3;
      }
      puVar3 = (uint *)((int)param_1 + 1);
      if (uVar9 < 3) {
        puVar3 = (uint *)((int)param_1 + 2);
        *(byte *)((int)param_1 + 1) = (byte)in_r12;
      }
      param_3 = (param_3 + uVar9) - 4;
      param_1 = puVar3;
      if (uVar9 < 2) {
        param_1 = (uint *)((int)puVar3 + 1);
        *(byte *)puVar3 = bVar6;
      }
    }
    param_4 = (uint)param_2 & 3;
    if (param_4 == 0) {
      uVar9 = 0;
      while (uVar1 = param_3 - 0x20, 0x1f < param_3) {
        uVar9 = param_2[1];
        uVar10 = param_2[2];
        uVar11 = param_2[3];
        *param_1 = *param_2;
        param_1[1] = uVar9;
        param_1[2] = uVar10;
        param_1[3] = uVar11;
        uVar9 = param_2[4];
        uVar10 = param_2[5];
        uVar11 = param_2[6];
        uVar12 = param_2[7];
        param_2 = param_2 + 8;
        param_1[4] = uVar9;
        param_1[5] = uVar10;
        param_1[6] = uVar11;
        param_1[7] = uVar12;
        param_1 = param_1 + 8;
        param_3 = uVar1;
      }
      if ((bool)((byte)(uVar1 >> 4) & 1)) {
        uVar9 = *param_2;
        uVar10 = param_2[1];
        uVar11 = param_2[2];
        uVar12 = param_2[3];
        param_2 = param_2 + 4;
        *param_1 = uVar9;
        param_1[1] = uVar10;
        param_1[2] = uVar11;
        param_1[3] = uVar12;
        param_1 = param_1 + 4;
      }
      if ((int)(param_3 << 0x1c) < 0) {
        uVar9 = *param_2;
        uVar10 = param_2[1];
        param_2 = param_2 + 2;
        *param_1 = uVar9;
        param_1[1] = uVar10;
        param_1 = param_1 + 2;
      }
      puVar2 = param_1;
      puVar3 = param_2;
      if ((bool)((byte)(uVar1 >> 2) & 1)) {
        puVar3 = param_2 + 1;
        uVar9 = *param_2;
        puVar2 = param_1 + 1;
        *param_1 = uVar9;
      }
      uVar7 = (undefined2)uVar9;
      if ((uVar1 & 3) == 0) {
        return CONCAT44(puVar3,puVar2);
      }
      bVar14 = (bool)((byte)(uVar1 >> 1) & 1);
      param_3 = param_3 << 0x1f;
      bVar13 = (int)param_3 < 0;
      puVar5 = puVar3;
      if (bVar14) {
        puVar5 = (uint *)((int)puVar3 + 2);
        uVar7 = (undefined2)*puVar3;
      }
      puVar3 = puVar5;
      if (bVar13) {
        puVar3 = (uint *)((int)puVar5 + 1);
        param_3 = (uint)(byte)*puVar5;
      }
      puVar5 = puVar2;
      if (bVar14) {
        puVar5 = (uint *)((int)puVar2 + 2);
        *(undefined2 *)puVar2 = uVar7;
      }
      puVar2 = puVar5;
      if (bVar13) {
        puVar2 = (uint *)((int)puVar5 + 1);
        *(byte *)puVar5 = (byte)param_3;
      }
      return CONCAT44(puVar3,puVar2);
    }
    bVar13 = 3 < param_3;
    param_3 = param_3 - 4;
    if (bVar13) {
      param_2 = (uint *)((int)param_2 - param_4);
      in_r12 = *param_2;
      puVar3 = param_1;
      if (param_4 == 2) {
        do {
          puVar2 = param_2;
          param_4 = in_r12 >> 0x10;
          param_2 = puVar2 + 1;
          in_r12 = *param_2;
          bVar13 = 3 < param_3;
          param_3 = param_3 - 4;
          param_4 = param_4 | in_r12 << 0x10;
          param_1 = puVar3 + 1;
          *puVar3 = param_4;
          puVar3 = param_1;
        } while (bVar13);
        param_2 = (uint *)((int)puVar2 + 6);
      }
      else if (param_4 < 3) {
        do {
          puVar2 = param_2;
          param_4 = in_r12 >> 8;
          param_2 = puVar2 + 1;
          in_r12 = *param_2;
          bVar13 = 3 < param_3;
          param_3 = param_3 - 4;
          param_4 = param_4 | in_r12 << 0x18;
          param_1 = puVar3 + 1;
          *puVar3 = param_4;
          puVar3 = param_1;
        } while (bVar13);
        param_2 = (uint *)((int)puVar2 + 5);
      }
      else {
        do {
          puVar2 = param_2;
          param_4 = in_r12 >> 0x18;
          param_2 = puVar2 + 1;
          in_r12 = *param_2;
          bVar13 = 3 < param_3;
          param_3 = param_3 - 4;
          param_4 = param_4 | in_r12 << 8;
          param_1 = puVar3 + 1;
          *puVar3 = param_4;
          puVar3 = param_1;
        } while (bVar13);
        param_2 = (uint *)((int)puVar2 + 7);
      }
    }
  }
  bVar8 = (byte)in_r12;
  bVar6 = (byte)param_4;
  bVar14 = (bool)((byte)(param_3 >> 1) & 1);
  param_3 = param_3 << 0x1f;
  bVar13 = (int)param_3 < 0;
  if (bVar14) {
    pbVar4 = (byte *)((int)param_2 + 1);
    bVar6 = (byte)*param_2;
    param_2 = (uint *)((int)param_2 + 2);
    bVar8 = *pbVar4;
  }
  puVar3 = param_2;
  if (bVar13) {
    puVar3 = (uint *)((int)param_2 + 1);
    param_3 = (uint)(byte)*param_2;
  }
  if (bVar14) {
    pbVar4 = (byte *)((int)param_1 + 1);
    *(byte *)param_1 = bVar6;
    param_1 = (uint *)((int)param_1 + 2);
    *pbVar4 = bVar8;
  }
  puVar2 = param_1;
  if (bVar13) {
    puVar2 = (uint *)((int)param_1 + 1);
    *(byte *)param_1 = (byte)param_3;
  }
  return CONCAT44(puVar3,puVar2);
}




/* 0x08006b04 */
void thunk_FUN_08006b04()
{
  FUN_08006b04();
  return;
}




/* 0x08006b04 */
undefined8 FUN_08006b04(param_1, param_2, param_3)
uint * param_1; uint * param_2; uint param_3;
{
  uint *puVar1;
  uint *puVar2;
  byte *pbVar3;
  uint *puVar4;
  byte bVar5;
  undefined2 uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  byte bVar10;
  uint in_r12 = 0;
  uint uVar11;
  uint uVar12;
  bool bVar13;
  bool bVar14;
  
  uVar7 = (int)param_1 - (int)param_2;
  bVar13 = uVar7 == 0;
  if (param_2 <= param_1) {
    bVar13 = param_3 == uVar7;
  }
  if ((param_2 > param_1 || param_3 < uVar7) || bVar13) {
    if (3 < param_3) {
      uVar7 = (uint)param_1 & 3;
      in_r12 = uVar7;
      if (uVar7 != 0) {
        bVar5 = (byte)*param_2;
        puVar2 = (uint *)((int)param_2 + 1);
        if (uVar7 < 3) {
          puVar2 = (uint *)((int)param_2 + 2);
          in_r12 = (uint)*(byte *)((int)param_2 + 1);
        }
        *(byte *)param_1 = bVar5;
        param_2 = puVar2;
        if (uVar7 < 2) {
          param_2 = (uint *)((int)puVar2 + 1);
          bVar5 = (byte)*puVar2;
        }
        puVar2 = (uint *)((int)param_1 + 1);
        if (uVar7 < 3) {
          puVar2 = (uint *)((int)param_1 + 2);
          *(byte *)((int)param_1 + 1) = (byte)in_r12;
        }
        param_3 = (param_3 + uVar7) - 4;
        param_1 = puVar2;
        if (uVar7 < 2) {
          param_1 = (uint *)((int)puVar2 + 1);
          *(byte *)puVar2 = bVar5;
        }
      }
      uVar7 = (uint)param_2 & 3;
      if (uVar7 == 0) {
        uVar7 = 0;
        while (uVar8 = param_3 - 0x20, 0x1f < param_3) {
          uVar7 = param_2[1];
          uVar9 = param_2[2];
          uVar11 = param_2[3];
          *param_1 = *param_2;
          param_1[1] = uVar7;
          param_1[2] = uVar9;
          param_1[3] = uVar11;
          uVar7 = param_2[4];
          uVar9 = param_2[5];
          uVar11 = param_2[6];
          uVar12 = param_2[7];
          param_2 = param_2 + 8;
          param_1[4] = uVar7;
          param_1[5] = uVar9;
          param_1[6] = uVar11;
          param_1[7] = uVar12;
          param_1 = param_1 + 8;
          param_3 = uVar8;
        }
        if ((bool)((byte)(uVar8 >> 4) & 1)) {
          uVar7 = *param_2;
          uVar9 = param_2[1];
          uVar11 = param_2[2];
          uVar12 = param_2[3];
          param_2 = param_2 + 4;
          *param_1 = uVar7;
          param_1[1] = uVar9;
          param_1[2] = uVar11;
          param_1[3] = uVar12;
          param_1 = param_1 + 4;
        }
        if ((int)(param_3 << 0x1c) < 0) {
          uVar7 = *param_2;
          uVar9 = param_2[1];
          param_2 = param_2 + 2;
          *param_1 = uVar7;
          param_1[1] = uVar9;
          param_1 = param_1 + 2;
        }
        puVar1 = param_1;
        puVar2 = param_2;
        if ((bool)((byte)(uVar8 >> 2) & 1)) {
          puVar2 = param_2 + 1;
          uVar7 = *param_2;
          puVar1 = param_1 + 1;
          *param_1 = uVar7;
        }
        uVar6 = (undefined2)uVar7;
        if ((uVar8 & 3) != 0) {
          bVar14 = (bool)((byte)(uVar8 >> 1) & 1);
          param_3 = param_3 << 0x1f;
          bVar13 = (int)param_3 < 0;
          puVar4 = puVar2;
          if (bVar14) {
            puVar4 = (uint *)((int)puVar2 + 2);
            uVar6 = (undefined2)*puVar2;
          }
          puVar2 = puVar4;
          if (bVar13) {
            puVar2 = (uint *)((int)puVar4 + 1);
            param_3 = (uint)(byte)*puVar4;
          }
          puVar4 = puVar1;
          if (bVar14) {
            puVar4 = (uint *)((int)puVar1 + 2);
            *(undefined2 *)puVar1 = uVar6;
          }
          puVar1 = puVar4;
          if (bVar13) {
            puVar1 = (uint *)((int)puVar4 + 1);
            *(byte *)puVar4 = (byte)param_3;
          }
          return CONCAT44(puVar2,puVar1);
        }
        return CONCAT44(puVar2,puVar1);
      }
      bVar13 = 3 < param_3;
      param_3 = param_3 - 4;
      if (bVar13) {
        param_2 = (uint *)((int)param_2 - uVar7);
        in_r12 = *param_2;
        puVar2 = param_1;
        if (uVar7 == 2) {
          do {
            puVar1 = param_2;
            uVar7 = in_r12 >> 0x10;
            param_2 = puVar1 + 1;
            in_r12 = *param_2;
            bVar13 = 3 < param_3;
            param_3 = param_3 - 4;
            uVar7 = uVar7 | in_r12 << 0x10;
            param_1 = puVar2 + 1;
            *puVar2 = uVar7;
            puVar2 = param_1;
          } while (bVar13);
          param_2 = (uint *)((int)puVar1 + 6);
        }
        else if (uVar7 < 3) {
          do {
            puVar1 = param_2;
            uVar7 = in_r12 >> 8;
            param_2 = puVar1 + 1;
            in_r12 = *param_2;
            bVar13 = 3 < param_3;
            param_3 = param_3 - 4;
            uVar7 = uVar7 | in_r12 << 0x18;
            param_1 = puVar2 + 1;
            *puVar2 = uVar7;
            puVar2 = param_1;
          } while (bVar13);
          param_2 = (uint *)((int)puVar1 + 5);
        }
        else {
          do {
            puVar1 = param_2;
            uVar7 = in_r12 >> 0x18;
            param_2 = puVar1 + 1;
            in_r12 = *param_2;
            bVar13 = 3 < param_3;
            param_3 = param_3 - 4;
            uVar7 = uVar7 | in_r12 << 8;
            param_1 = puVar2 + 1;
            *puVar2 = uVar7;
            puVar2 = param_1;
          } while (bVar13);
          param_2 = (uint *)((int)puVar1 + 7);
        }
      }
    }
    bVar10 = (byte)in_r12;
    bVar5 = (byte)uVar7;
    bVar14 = (bool)((byte)(param_3 >> 1) & 1);
    param_3 = param_3 << 0x1f;
    bVar13 = (int)param_3 < 0;
    if (bVar14) {
      pbVar3 = (byte *)((int)param_2 + 1);
      bVar5 = (byte)*param_2;
      param_2 = (uint *)((int)param_2 + 2);
      bVar10 = *pbVar3;
    }
    puVar2 = param_2;
    if (bVar13) {
      puVar2 = (uint *)((int)param_2 + 1);
      param_3 = (uint)(byte)*param_2;
    }
    if (bVar14) {
      pbVar3 = (byte *)((int)param_1 + 1);
      *(byte *)param_1 = bVar5;
      param_1 = (uint *)((int)param_1 + 2);
      *pbVar3 = bVar10;
    }
    puVar1 = param_1;
    if (bVar13) {
      puVar1 = (uint *)((int)param_1 + 1);
      *(byte *)param_1 = (byte)param_3;
    }
    return CONCAT44(puVar2,puVar1);
  }
  param_1 = (uint *)((int)param_1 + param_3);
  param_2 = (uint *)((int)param_2 + param_3);
  if (3 < param_3) {
    bVar13 = ((uint)param_1 & 3) == 0;
    do {
      if (!bVar13) {
        param_2 = (uint *)((int)param_2 + -1);
        param_3 = param_3 - 1;
        param_1 = (uint *)((int)param_1 + -1);
        *(byte *)param_1 = *(byte *)param_2;
      }
      bVar13 = ((uint)param_1 & 3) == 0;
    } while (!bVar13);
    uVar7 = (uint)param_2 & 3;
    if (uVar7 == 0) {
      while (uVar7 = param_3 - 0x10, 0xf < param_3) {
        puVar2 = param_2 + -1;
        uVar11 = param_2[-2];
        uVar9 = param_2[-3];
        param_2 = param_2 + -4;
        uVar8 = *param_2;
        param_1[-1] = *puVar2;
        param_1[-2] = uVar11;
        param_1[-3] = uVar9;
        param_1 = param_1 + -4;
        *param_1 = uVar8;
        param_3 = uVar7;
      }
      uVar8 = param_3 << 0x1d;
      bVar13 = (int)uVar8 < 0;
      if ((bool)((byte)(uVar7 >> 3) & 1)) {
        puVar2 = param_2 + -1;
        param_2 = param_2 + -2;
        uVar8 = *param_2;
        param_1[-1] = *puVar2;
        param_1 = param_1 + -2;
        *param_1 = uVar8;
      }
      if (bVar13) {
        param_2 = param_2 + -1;
        uVar8 = *param_2;
        param_1 = param_1 + -1;
        *param_1 = uVar8;
      }
      uVar6 = (undefined2)uVar8;
      if ((uVar7 & 3) != 0) {
        bVar14 = (bool)((byte)(uVar7 >> 1) & 1);
        param_3 = param_3 << 0x1f;
        bVar13 = (int)param_3 < 0;
        if (bVar14) {
          param_2 = (uint *)((int)param_2 + -2);
          uVar6 = *(undefined2 *)param_2;
        }
        if (bVar13) {
          param_3 = (uint)*(byte *)((int)param_2 + -1);
        }
        if (bVar14) {
          param_1 = (uint *)((int)param_1 + -2);
          *(undefined2 *)param_1 = uVar6;
        }
        if (bVar13) {
          *(byte *)((int)param_1 + -1) = (byte)param_3;
        }
        return CONCAT44(param_2,param_1);
      }
      return CONCAT44(param_2,param_1);
    }
    bVar13 = 3 < param_3;
    param_3 = param_3 - 4;
    if (bVar13) {
      param_2 = (uint *)((int)param_2 - uVar7);
      in_r12 = *param_2;
      if (uVar7 < 2) {
        do {
          puVar2 = param_2;
          uVar7 = in_r12 << 0x18;
          param_2 = puVar2 + -1;
          in_r12 = *param_2;
          bVar13 = 3 < param_3;
          param_3 = param_3 - 4;
          uVar7 = uVar7 | in_r12 >> 8;
          param_1 = param_1 + -1;
          *param_1 = uVar7;
        } while (bVar13);
        param_2 = (uint *)((int)puVar2 + -3);
      }
      else if (uVar7 < 3) {
        do {
          puVar2 = param_2;
          uVar7 = in_r12 << 0x10;
          param_2 = puVar2 + -1;
          in_r12 = *param_2;
          bVar13 = 3 < param_3;
          param_3 = param_3 - 4;
          uVar7 = uVar7 | in_r12 >> 0x10;
          param_1 = param_1 + -1;
          *param_1 = uVar7;
        } while (bVar13);
        param_2 = (uint *)((int)puVar2 + -2);
      }
      else {
        do {
          puVar2 = param_2;
          uVar7 = in_r12 << 8;
          param_2 = puVar2 + -1;
          in_r12 = *param_2;
          bVar13 = 3 < param_3;
          param_3 = param_3 - 4;
          uVar7 = uVar7 | in_r12 >> 0x18;
          param_1 = param_1 + -1;
          *param_1 = uVar7;
        } while (bVar13);
        param_2 = (uint *)((int)puVar2 + -1);
      }
    }
  }
  bVar10 = (byte)in_r12;
  bVar5 = (byte)uVar7;
  bVar14 = (bool)((byte)(param_3 >> 1) & 1);
  param_3 = param_3 << 0x1f;
  bVar13 = (int)param_3 < 0;
  if (bVar14) {
    bVar5 = *(byte *)((int)param_2 + -1);
    param_2 = (uint *)((int)param_2 + -2);
    bVar10 = *(byte *)param_2;
  }
  if (bVar13) {
    param_3 = (uint)*(byte *)((int)param_2 + -1);
  }
  if (bVar14) {
    *(byte *)((int)param_1 + -1) = bVar5;
    param_1 = (uint *)((int)param_1 + -2);
    *(byte *)param_1 = bVar10;
  }
  if (bVar13) {
    *(byte *)((int)param_1 + -1) = (byte)param_3;
  }
  return CONCAT44(param_2,param_1);
}




/* 0x08006bdc */
void thunk_FUN_08006bdc()
{
  FUN_08006bdc();
  return;
}




/* 0x08006bdc */
undefined8 FUN_08006bdc(param_1, param_2, param_3, param_4)
undefined4 * param_1; byte * param_2; uint param_3; undefined4 param_4;
{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  byte *pbVar4;
  byte *pbVar5;
  undefined2 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  bool bVar10;
  bool bVar11;
  
  while (uVar1 = param_3 - 0x20, 0x1f < param_3) {
    uVar7 = *(undefined4 *)(param_2 + 4);
    uVar8 = *(undefined4 *)(param_2 + 8);
    uVar9 = *(undefined4 *)(param_2 + 0xc);
    *param_1 = *(undefined4 *)param_2;
    param_1[1] = uVar7;
    param_1[2] = uVar8;
    param_1[3] = uVar9;
    param_4 = *(undefined4 *)(param_2 + 0x10);
    uVar7 = *(undefined4 *)(param_2 + 0x14);
    uVar8 = *(undefined4 *)(param_2 + 0x18);
    uVar9 = *(undefined4 *)(param_2 + 0x1c);
    param_2 = param_2 + 0x20;
    param_1[4] = param_4;
    param_1[5] = uVar7;
    param_1[6] = uVar8;
    param_1[7] = uVar9;
    param_1 = param_1 + 8;
    param_3 = uVar1;
  }
  if ((bool)((byte)(uVar1 >> 4) & 1)) {
    param_4 = *(undefined4 *)param_2;
    uVar7 = *(undefined4 *)(param_2 + 4);
    uVar8 = *(undefined4 *)(param_2 + 8);
    uVar9 = *(undefined4 *)(param_2 + 0xc);
    param_2 = param_2 + 0x10;
    *param_1 = param_4;
    param_1[1] = uVar7;
    param_1[2] = uVar8;
    param_1[3] = uVar9;
    param_1 = param_1 + 4;
  }
  if ((int)(param_3 << 0x1c) < 0) {
    param_4 = *(undefined4 *)param_2;
    uVar7 = *(undefined4 *)(param_2 + 4);
    param_2 = param_2 + 8;
    *param_1 = param_4;
    param_1[1] = uVar7;
    param_1 = param_1 + 2;
  }
  puVar3 = param_1;
  pbVar4 = param_2;
  if ((bool)((byte)(uVar1 >> 2) & 1)) {
    pbVar4 = param_2 + 4;
    param_4 = *(undefined4 *)param_2;
    puVar3 = param_1 + 1;
    *param_1 = param_4;
  }
  uVar6 = (undefined2)param_4;
  if ((uVar1 & 3) == 0) {
    return CONCAT44(pbVar4,puVar3);
  }
  bVar11 = (bool)((byte)(uVar1 >> 1) & 1);
  param_3 = param_3 << 0x1f;
  bVar10 = (int)param_3 < 0;
  pbVar5 = pbVar4;
  if (bVar11) {
    pbVar5 = pbVar4 + 2;
    uVar6 = *(undefined2 *)pbVar4;
  }
  pbVar4 = pbVar5;
  if (bVar10) {
    pbVar4 = pbVar5 + 1;
    param_3 = (uint)*pbVar5;
  }
  puVar2 = puVar3;
  if (bVar11) {
    puVar2 = (undefined4 *)((int)puVar3 + 2);
    *(undefined2 *)puVar3 = uVar6;
  }
  puVar3 = puVar2;
  if (bVar10) {
    puVar3 = (undefined4 *)((int)puVar2 + 1);
    *(char *)puVar2 = (char)param_3;
  }
  return CONCAT44(pbVar4,puVar3);
}




/* 0x08006c40 */
void thunk_FUN_08006c40()
{
  FUN_08006c40();
  return;
}




/* 0x08006c40 */
undefined8 FUN_08006c40(param_1, param_2, param_3)
uint * param_1; uint * param_2; uint param_3;
{
  uint uVar1;
  uint *puVar2;
  byte *pbVar3;
  uint *puVar4;
  uint *puVar5;
  byte *pbVar6;
  undefined2 uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  bool bVar15;
  bool bVar16;
  byte *pbVar17;
  
  uVar8 = (int)param_1 - (int)param_2;
  bVar15 = uVar8 == 0;
  if (param_2 <= param_1) {
    bVar15 = param_3 == uVar8;
  }
  if ((param_2 > param_1 || param_3 < uVar8) || bVar15) {
    while (uVar1 = param_3 - 0x20, 0x1f < param_3) {
      uVar8 = param_2[1];
      uVar11 = param_2[2];
      uVar13 = param_2[3];
      *param_1 = *param_2;
      param_1[1] = uVar8;
      param_1[2] = uVar11;
      param_1[3] = uVar13;
      uVar8 = param_2[4];
      uVar11 = param_2[5];
      uVar13 = param_2[6];
      uVar14 = param_2[7];
      param_2 = param_2 + 8;
      param_1[4] = uVar8;
      param_1[5] = uVar11;
      param_1[6] = uVar13;
      param_1[7] = uVar14;
      param_1 = param_1 + 8;
      param_3 = uVar1;
    }
    if ((bool)((byte)(uVar1 >> 4) & 1)) {
      uVar8 = *param_2;
      uVar11 = param_2[1];
      uVar13 = param_2[2];
      uVar14 = param_2[3];
      param_2 = param_2 + 4;
      *param_1 = uVar8;
      param_1[1] = uVar11;
      param_1[2] = uVar13;
      param_1[3] = uVar14;
      param_1 = param_1 + 4;
    }
    if ((int)(param_3 << 0x1c) < 0) {
      uVar8 = *param_2;
      uVar11 = param_2[1];
      param_2 = param_2 + 2;
      *param_1 = uVar8;
      param_1[1] = uVar11;
      param_1 = param_1 + 2;
    }
    puVar2 = param_1;
    puVar5 = param_2;
    if ((bool)((byte)(uVar1 >> 2) & 1)) {
      puVar5 = param_2 + 1;
      uVar8 = *param_2;
      puVar2 = param_1 + 1;
      *param_1 = uVar8;
    }
    uVar7 = (undefined2)uVar8;
    if ((uVar1 & 3) != 0) {
      bVar16 = (bool)((byte)(uVar1 >> 1) & 1);
      param_3 = param_3 << 0x1f;
      bVar15 = (int)param_3 < 0;
      puVar4 = puVar5;
      if (bVar16) {
        puVar4 = (uint *)((int)puVar5 + 2);
        uVar7 = (undefined2)*puVar5;
      }
      puVar5 = puVar4;
      if (bVar15) {
        puVar5 = (uint *)((int)puVar4 + 1);
        param_3 = (uint)(byte)*puVar4;
      }
      puVar4 = puVar2;
      if (bVar16) {
        puVar4 = (uint *)((int)puVar2 + 2);
        *(undefined2 *)puVar2 = uVar7;
      }
      puVar2 = puVar4;
      if (bVar15) {
        puVar2 = (uint *)((int)puVar4 + 1);
        *(byte *)puVar4 = (byte)param_3;
      }
      return CONCAT44(puVar5,puVar2);
    }
    return CONCAT44(puVar5,puVar2);
  }
  pbVar3 = (byte *)((int)param_1 + param_3);
  bVar15 = ((uint)pbVar3 & 3) == 0;
  pbVar6 = (byte *)((int)param_2 + param_3);
  do {
    if (!bVar15) {
      param_3 = param_3 - 1;
      pbVar6 = pbVar6 + -1;
      pbVar3 = pbVar3 + -1;
      *pbVar3 = *pbVar6;
    }
    bVar15 = ((uint)pbVar3 & 3) == 0;
  } while (!bVar15);
  while (uVar8 = param_3 - 0x10, 0xf < param_3) {
    pbVar17 = pbVar6 + -4;
    iVar12 = *(int *)(pbVar6 + -8);
    iVar10 = *(int *)(pbVar6 + -0xc);
    pbVar6 = pbVar6 + -0x10;
    iVar9 = *(int *)pbVar6;
    *(int *)(pbVar3 + -4) = *(int *)pbVar17;
    *(int *)(pbVar3 + -8) = iVar12;
    *(int *)(pbVar3 + -0xc) = iVar10;
    pbVar3 = pbVar3 + -0x10;
    *(int *)pbVar3 = iVar9;
    param_3 = uVar8;
  }
  iVar9 = param_3 << 0x1d;
  bVar15 = iVar9 < 0;
  if ((bool)((byte)(uVar8 >> 3) & 1)) {
    pbVar17 = pbVar6 + -4;
    pbVar6 = pbVar6 + -8;
    iVar9 = *(int *)pbVar6;
    *(int *)(pbVar3 + -4) = *(int *)pbVar17;
    pbVar3 = pbVar3 + -8;
    *(int *)pbVar3 = iVar9;
  }
  if (bVar15) {
    pbVar6 = pbVar6 + -4;
    iVar9 = *(int *)pbVar6;
    pbVar3 = pbVar3 + -4;
    *(int *)pbVar3 = iVar9;
  }
  uVar7 = (undefined2)iVar9;
  if ((uVar8 & 3) != 0) {
    bVar16 = (bool)((byte)(uVar8 >> 1) & 1);
    param_3 = param_3 << 0x1f;
    bVar15 = (int)param_3 < 0;
    if (bVar16) {
      pbVar6 = pbVar6 + -2;
      uVar7 = *(undefined2 *)pbVar6;
    }
    if (bVar15) {
      param_3 = (uint)pbVar6[-1];
    }
    if (bVar16) {
      pbVar3 = pbVar3 + -2;
      *(undefined2 *)pbVar3 = uVar7;
    }
    if (bVar15) {
      pbVar3[-1] = (byte)param_3;
    }
    return CONCAT44(pbVar6,pbVar3);
  }
  return CONCAT44(pbVar6,pbVar3);
}




/* 0x08006cc0 */
undefined4 * FUN_08006cc0(param_1, param_2, param_3)
undefined4 * param_1; uint param_2; undefined1 param_3;
{
  undefined2 uVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  bool bVar8;
  
  uVar1 = CONCAT11(param_3,param_3);
  uVar6 = CONCAT22(uVar1,uVar1);
  if (param_2 < 4) {
    if ((param_2 & 2) != 0) {
      puVar3 = (undefined1 *)((int)param_1 + 1);
      *(undefined1 *)param_1 = param_3;
      param_1 = (undefined4 *)((int)param_1 + 2);
      *puVar3 = param_3;
    }
    puVar2 = param_1;
    if ((int)(param_2 << 0x1f) < 0) {
      puVar2 = (undefined4 *)((int)param_1 + 1);
      *(undefined1 *)param_1 = param_3;
    }
    return puVar2;
  }
  if (((uint)param_1 & 3) != 0) {
    iVar7 = 4 - ((uint)param_1 & 3);
    puVar2 = param_1;
    if (iVar7 != 2) {
      puVar2 = (undefined4 *)((int)param_1 + 1);
      *(undefined1 *)param_1 = param_3;
    }
    param_1 = puVar2;
    if (1 < iVar7) {
      param_1 = (undefined4 *)((int)puVar2 + 2);
      *(undefined2 *)puVar2 = uVar1;
    }
    param_2 = param_2 - iVar7;
  }
  bVar8 = 0x1f < param_2;
  param_2 = param_2 - 0x20;
  do {
    if (bVar8) {
      *param_1 = uVar6;
      param_1[1] = uVar6;
      param_1[2] = uVar6;
      param_1[3] = uVar6;
      param_1[4] = uVar6;
      param_1[5] = uVar6;
      param_1[6] = uVar6;
      param_1[7] = uVar6;
      param_1 = param_1 + 8;
      bVar8 = 0x1f < param_2;
      param_2 = param_2 - 0x20;
    }
  } while (bVar8);
  if ((param_2 & 0x10) != 0) {
    *param_1 = uVar6;
    param_1[1] = uVar6;
    param_1[2] = uVar6;
    param_1[3] = uVar6;
    param_1 = param_1 + 4;
  }
  if ((int)(param_2 << 0x1c) < 0) {
    *param_1 = uVar6;
    param_1[1] = uVar6;
    param_1 = param_1 + 2;
  }
  uVar5 = param_2 << 0x1e;
  puVar2 = param_1;
  if ((param_2 << 0x1c & 0x40000000) != 0) {
    puVar2 = param_1 + 1;
    *param_1 = uVar6;
  }
  if (uVar5 != 0) {
    puVar4 = puVar2;
    if ((int)uVar5 < 0) {
      puVar4 = (undefined4 *)((int)puVar2 + 2);
      *(undefined2 *)puVar2 = uVar1;
    }
    puVar2 = puVar4;
    if ((uVar5 & 0x40000000) != 0) {
      puVar2 = (undefined4 *)((int)puVar4 + 1);
      *(undefined1 *)puVar4 = param_3;
    }
    return puVar2;
  }
  return puVar2;
}




/* 0x08006cd0 */
undefined4 * FUN_08006cd0(param_1, param_2)
undefined4 * param_1; uint param_2;
{
  undefined4 *puVar1;
  undefined1 *puVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  
  if (param_2 < 4) {
    if ((param_2 & 2) != 0) {
      puVar2 = (undefined1 *)((int)param_1 + 1);
      *(undefined1 *)param_1 = 0;
      param_1 = (undefined4 *)((int)param_1 + 2);
      *puVar2 = 0;
    }
    puVar1 = param_1;
    if ((int)(param_2 << 0x1f) < 0) {
      puVar1 = (undefined4 *)((int)param_1 + 1);
      *(undefined1 *)param_1 = 0;
    }
    return puVar1;
  }
  if (((uint)param_1 & 3) != 0) {
    iVar5 = 4 - ((uint)param_1 & 3);
    puVar1 = param_1;
    if (iVar5 != 2) {
      puVar1 = (undefined4 *)((int)param_1 + 1);
      *(undefined1 *)param_1 = 0;
    }
    param_1 = puVar1;
    if (1 < iVar5) {
      param_1 = (undefined4 *)((int)puVar1 + 2);
      *(undefined2 *)puVar1 = 0;
    }
    param_2 = param_2 - iVar5;
  }
  bVar6 = 0x1f < param_2;
  param_2 = param_2 - 0x20;
  do {
    if (bVar6) {
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = 0;
      param_1[3] = 0;
      param_1[4] = 0;
      param_1[5] = 0;
      param_1[6] = 0;
      param_1[7] = 0;
      param_1 = param_1 + 8;
      bVar6 = 0x1f < param_2;
      param_2 = param_2 - 0x20;
    }
  } while (bVar6);
  if ((param_2 & 0x10) != 0) {
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1 = param_1 + 4;
  }
  if ((int)(param_2 << 0x1c) < 0) {
    *param_1 = 0;
    param_1[1] = 0;
    param_1 = param_1 + 2;
  }
  uVar4 = param_2 << 0x1e;
  puVar1 = param_1;
  if ((param_2 << 0x1c & 0x40000000) != 0) {
    puVar1 = param_1 + 1;
    *param_1 = 0;
  }
  if (uVar4 != 0) {
    puVar3 = puVar1;
    if ((int)uVar4 < 0) {
      puVar3 = (undefined4 *)((int)puVar1 + 2);
      *(undefined2 *)puVar1 = 0;
    }
    puVar1 = puVar3;
    if ((uVar4 & 0x40000000) != 0) {
      puVar1 = (undefined4 *)((int)puVar3 + 1);
      *(undefined1 *)puVar3 = 0;
    }
    return puVar1;
  }
  return puVar1;
}




/* 0x08006d14 */
void thunk_FUN_08006d14()
{
  FUN_08006d14();
  return;
}




/* 0x08006d14 */
undefined4 * FUN_08006d14(param_1, param_2)
undefined4 * param_1; uint param_2;
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  bool bVar4;
  
  bVar4 = 0x1f < param_2;
  param_2 = param_2 - 0x20;
  do {
    if (bVar4) {
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = 0;
      param_1[3] = 0;
      param_1[4] = 0;
      param_1[5] = 0;
      param_1[6] = 0;
      param_1[7] = 0;
      param_1 = param_1 + 8;
      bVar4 = 0x1f < param_2;
      param_2 = param_2 - 0x20;
    }
  } while (bVar4);
  if ((param_2 & 0x10) != 0) {
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1 = param_1 + 4;
  }
  if ((int)(param_2 << 0x1c) < 0) {
    *param_1 = 0;
    param_1[1] = 0;
    param_1 = param_1 + 2;
  }
  uVar3 = param_2 << 0x1e;
  puVar2 = param_1;
  if ((param_2 << 0x1c & 0x40000000) != 0) {
    puVar2 = param_1 + 1;
    *param_1 = 0;
  }
  if (uVar3 != 0) {
    puVar1 = puVar2;
    if ((int)uVar3 < 0) {
      puVar1 = (undefined4 *)((int)puVar2 + 2);
      *(undefined2 *)puVar2 = 0;
    }
    puVar2 = puVar1;
    if ((uVar3 & 0x40000000) != 0) {
      puVar2 = (undefined4 *)((int)puVar1 + 1);
      *(undefined1 *)puVar1 = 0;
    }
    return puVar2;
  }
  return puVar2;
}




/* 0x08006d64 */
uint FUN_08006d64(param_1, param_2)
uint * param_1; uint * param_2;
{
  uint uVar1;
  byte *pbVar2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  bool bVar10;
  
  if (((uint)param_1 & 3) == 0 && ((uint)param_2 & 3) == 0) {
    do {
      uVar4 = *param_1;
      uVar5 = *param_2;
      uVar6 = uVar4 + 0xfefefeff & ~uVar4;
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
    } while ((uVar6 & 0x80808080) == 0 && uVar4 == uVar5);
    uVar1 = uVar5 * 0x1000000 + uVar4 * -0x1000000;
    bVar7 = uVar1 == 0;
    bVar10 = !bVar7 && uVar4 * 0x1000000 <= uVar5 * 0x1000000;
    bVar8 = (uVar6 & 0x80) == 0;
    bVar9 = bVar7 && bVar8;
    if (bVar7 && bVar8) {
      uVar1 = uVar5 * 0x10000 + uVar4 * -0x10000;
      bVar7 = uVar1 == 0;
      bVar10 = !bVar7 && uVar4 * 0x10000 <= uVar5 * 0x10000;
      bVar8 = (uVar6 & 0x8000) == 0;
      bVar9 = bVar7 && bVar8;
      if (bVar7 && bVar8) {
        uVar1 = uVar5 * 0x100 + uVar4 * -0x100;
        bVar7 = uVar1 == 0;
        bVar10 = !bVar7 && uVar4 * 0x100 <= uVar5 * 0x100;
        bVar8 = (uVar6 & 0x800000) == 0;
        bVar9 = bVar7 && bVar8;
        if (bVar7 && bVar8) {
          bVar10 = uVar4 <= uVar5;
          uVar1 = uVar5 - uVar4;
          bVar9 = uVar1 == 0;
        }
      }
    }
    if (!bVar9) {
      uVar1 = (uint)bVar10 << 0x1f | uVar1 >> 1;
    }
    return uVar1;
  }
  do {
    pbVar2 = (byte *)((int)param_1 + 1);
    uVar4 = (uint)(byte)*param_1;
    pbVar3 = (byte *)((int)param_2 + 1);
    uVar5 = (uint)(byte)*param_2;
    bVar9 = uVar4 == 1;
    if (uVar4 != 0) {
      bVar9 = uVar4 == uVar5;
    }
    if (!bVar9) break;
    param_1 = (uint *)((int)param_1 + 2);
    uVar4 = (uint)*pbVar2;
    param_2 = (uint *)((int)param_2 + 2);
    uVar5 = (uint)*pbVar3;
    bVar9 = uVar4 == 1;
    if (uVar4 != 0) {
      bVar9 = uVar4 == uVar5;
    }
  } while (bVar9);
  return uVar4 - uVar5;
}




/* 0x08006e04 */
undefined4 FUN_08006e04(param_1)
undefined4 * param_1;
{
  return *param_1;
}




/* 0x08006e1a */
undefined4 FUN_08006e1a(param_1, param_2)
undefined4 param_1; undefined1 * param_2;
{
  *param_2 = (char)param_1;
  param_2[1] = (char)((uint)param_1 >> 8);
  param_2[2] = (char)((uint)param_1 >> 0x10);
  param_2[3] = (char)((uint)param_1 >> 0x18);
  return 0;
}




/* 0x08006e30 */
undefined8 FUN_08006e30(param_1)
undefined8 * param_1;
{
  return *param_1;
}




/* 0x08006e5e */
void FUN_08006e5e(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined1 * param_3;
{
  *param_3 = (char)param_1;
  param_3[1] = (char)((uint)param_1 >> 8);
  param_3[2] = (char)((uint)param_1 >> 0x10);
  param_3[3] = (char)((uint)param_1 >> 0x18);
  param_3[4] = (char)param_2;
  param_3[5] = (char)((uint)param_2 >> 8);
  param_3[6] = (char)((uint)param_2 >> 0x10);
  param_3[7] = (char)((uint)param_2 >> 0x18);
  return;
}




/* 0x08006e88 */
undefined4 FUN_08006e88()
{
  software_interrupt(0xab);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08006e98 */
undefined * FUN_08006e98()
{
  return &DAT_0805a898;
}




/* 0x08006ea0 */
undefined8 FUN_08006ea0(param_1, param_2)
uint param_1; uint param_2;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = param_1 >> 2 | param_2 << 0x1e;
  uVar1 = param_1 - uVar3;
  uVar2 = param_2 - ((param_2 >> 2) + (uint)(param_1 < uVar3));
  uVar4 = uVar1 >> 4 | uVar2 * 0x10000000;
  uVar3 = uVar1 + uVar4;
  uVar2 = uVar2 + (uVar2 >> 4) + (uint)CARRY4(uVar1,uVar4);
  uVar4 = uVar3 >> 8 | uVar2 * 0x1000000;
  uVar1 = uVar3 + uVar4;
  uVar3 = uVar2 + (uVar2 >> 8) + (uint)CARRY4(uVar3,uVar4);
  uVar4 = uVar1 >> 0x10 | uVar3 * 0x10000;
  uVar2 = uVar1 + uVar4;
  uVar4 = uVar3 + (uVar3 >> 0x10) + (uint)CARRY4(uVar1,uVar4);
  uVar3 = uVar4 + CARRY4(uVar2,uVar4);
  uVar1 = uVar3 * 0x20000000;
  uVar2 = uVar2 + uVar4 >> 3 | uVar1;
  uVar3 = uVar3 >> 3;
  if (-1 < (int)((param_2 - (param_1 < 10)) -
                (((uVar3 << 2 | uVar1 >> 0x1e) + uVar3 + (uint)CARRY4(uVar2,uVar2 * 4)) * 2 +
                 (uint)CARRY4(uVar2 * 5,uVar2 * 5) + (uint)(param_1 - 10 < uVar2 * 10)))) {
    return CONCAT44(uVar3 + (0xfffffffe < uVar2),uVar2 + 1);
  }
  return CONCAT44(uVar3,uVar2);
}




/* 0x08006f38 */
int FUN_08006f38(param_1, param_2)
int param_1; int * param_2;
{
  if (*param_2 << 0x15 < 0) {
    param_1 = (int)(char)param_1;
  }
  else if (*param_2 << 0x17 < 0) {
    return (int)(short)param_1;
  }
  return param_1;
}




/* 0x08006f4a */
uint FUN_08006f4a(param_1, param_2)
uint param_1; int * param_2;
{
  if (*param_2 << 0x15 < 0) {
    param_1 = param_1 & 0xff;
  }
  else if (*param_2 << 0x17 < 0) {
    return param_1 & 0xffff;
  }
  return param_1;
}




/* 0x08006f5c */
undefined4 FUN_08006f5c(param_1, param_2, param_3, param_4)
uint * param_1; int param_2; int param_3; int param_4;
{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  if ((int)(*param_1 << 0x1a) < 0) {
    uVar1 = param_1[7];
    *param_1 = *param_1 & 0xffffffef;
  }
  else {
    uVar1 = 1;
  }
  if (param_2 < (int)uVar1) {
    iVar4 = uVar1 - param_2;
  }
  else {
    iVar4 = 0;
  }
  param_1[6] = param_1[6] - (iVar4 + param_2 + param_4);
  if (-1 < (int)(*param_1 << 0x1b)) {
    FUN_08006484(param_1);
  }
  for (iVar3 = 0; iVar3 < param_4; iVar3 = iVar3 + 1) {
    ((code *)param_1[1])(*(undefined1 *)(param_3 + iVar3),param_1[2]);
    param_1[8] = param_1[8] + 1;
  }
  if ((int)(*param_1 << 0x1b) < 0) {
    FUN_08006484(param_1);
  }
  while (0 < iVar4) {
    ((code *)param_1[1])(0x30,param_1[2]);
    param_1[8] = param_1[8] + 1;
    iVar4 = iVar4 + -1;
  }
  while (0 < param_2) {
    ((code *)param_1[1])(*(undefined1 *)((int)param_1 + param_2 + 0x23),param_1[2]);
    param_1[8] = param_1[8] + 1;
    param_2 = param_2 + -1;
  }
  FUN_080064b2(param_1);
  if ((int)(*param_1 << 0x18) < 0) {
    uVar2 = 2;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}




/* 0x0800704a */
undefined4 FUN_0800704a(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  undefined1 auStack_40 [4];
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined1 *local_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  
  local_2c = 0;
  local_34 = &LAB_08007040;
  local_3c = param_4;
  uStack_38 = param_2;
  uStack_30 = param_1;
  FUN_080066b0(auStack_40,param_3);
  return 0;
}




/* 0x08007070 */
void FUN_08007070(param_1, param_2)
undefined1 param_1; undefined4 * param_2;
{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)*param_2;
  *puVar1 = param_1;
  *param_2 = puVar1 + 1;
  return;
}




/* 0x080070b8 */
undefined8 FUN_080070b8(param_1, param_2, param_3, param_4)
int * param_1; int param_2; int param_3; undefined4 param_4;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 local_38;
  undefined4 uStack_34;
  int local_30;
  undefined4 uStack_2c;
  
  iVar5 = 0;
  iVar4 = 0;
  local_38 = 0;
  uStack_34 = 0;
  local_30 = param_3;
  uStack_2c = param_4;
  do {
    if (((*param_1 << 0x1a < 0) && (param_1[7] <= iVar5)) ||
       ((param_3 <= iVar4 && (*(short *)(param_2 + iVar4 * 2) == 0)))) goto LAB_08007112;
    iVar1 = FUN_0800795c(&local_30,*(undefined2 *)(param_2 + iVar4 * 2),&local_38);
    if (iVar1 != -1) {
      if ((*param_1 << 0x1a < 0) && ((uint)param_1[7] < (uint)(iVar5 + iVar1))) {
LAB_08007112:
        param_1[6] = param_1[6] - iVar5;
        FUN_08006484(param_1);
        local_38 = 0;
        uStack_34 = 0;
        for (iVar1 = 0; iVar1 < iVar4; iVar1 = iVar1 + 1) {
          uVar2 = FUN_0800795c(&local_30,*(undefined2 *)(param_2 + iVar1 * 2),&local_38);
          if (uVar2 != 0xffffffff) {
            for (uVar3 = 0; uVar3 < uVar2; uVar3 = uVar3 + 1) {
              ((code *)param_1[1])(*(undefined1 *)((int)&local_30 + uVar3),param_1[2]);
            }
          }
        }
        param_1[8] = param_1[8] + iVar5;
        FUN_080064b2(param_1);
        return CONCAT44(uStack_34,local_38);
      }
      iVar5 = iVar5 + iVar1;
    }
    iVar4 = iVar4 + 1;
  } while( true );
}




/* 0x080071ec */
int thunk_FUN_080071ec(param_1, param_2, param_3)
byte * param_1; undefined4 * param_2; undefined4 param_3;
{
  int *piVar1;
  int *piVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  byte *pbVar5;
  
  iVar8 = 0;
  piVar1 = (int *)FUN_08007450();
  iVar9 = *piVar1;
  pbVar4 = param_1;
  do {
    pbVar5 = pbVar4;
    pbVar4 = pbVar5 + 1;
    uVar7 = (uint)*pbVar5;
    if (uVar7 == 0) break;
    piVar2 = (int *)FUN_080060b0();
  } while ((*(byte *)(*piVar2 + uVar7) & 1) != 0);
  pbVar6 = pbVar4;
  if ((uVar7 != 0x2b) && (pbVar6 = pbVar5, uVar7 == 0x2d)) {
    iVar8 = 0x400;
    pbVar6 = pbVar4;
  }
  *piVar1 = 0;
  iVar3 = FUN_0800789c(pbVar6,param_2,param_3);
  if ((param_2 != (undefined4 *)0x0) && ((byte *)*param_2 == pbVar6)) {
    *param_2 = param_1;
  }
  if ((*piVar1 != 2) && (*piVar1 = iVar9, iVar8 << 0x15 < 0)) {
    iVar3 = -iVar3;
  }
  return iVar3;
}




/* 0x080071ec */
int FUN_080071ec(param_1, param_2, param_3)
byte * param_1; undefined4 * param_2; undefined4 param_3;
{
  int *piVar1;
  int *piVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  byte *pbVar5;
  
  iVar8 = 0;
  piVar1 = (int *)FUN_08007450();
  iVar9 = *piVar1;
  pbVar4 = param_1;
  do {
    pbVar5 = pbVar4;
    pbVar4 = pbVar5 + 1;
    uVar7 = (uint)*pbVar5;
    if (uVar7 == 0) break;
    piVar2 = (int *)FUN_080060b0();
  } while ((*(byte *)(*piVar2 + uVar7) & 1) != 0);
  pbVar6 = pbVar4;
  if ((uVar7 != 0x2b) && (pbVar6 = pbVar5, uVar7 == 0x2d)) {
    iVar8 = 0x400;
    pbVar6 = pbVar4;
  }
  *piVar1 = 0;
  iVar3 = FUN_0800789c(pbVar6,param_2,param_3);
  if ((param_2 != (undefined4 *)0x0) && ((byte *)*param_2 == pbVar6)) {
    *param_2 = param_1;
  }
  if ((*piVar1 != 2) && (*piVar1 = iVar9, iVar8 << 0x15 < 0)) {
    iVar3 = -iVar3;
  }
  return iVar3;
}




/* 0x08007268 */
undefined1 * FUN_08007268(param_1, param_2)
undefined1 * param_1; uint param_2;
{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  char cVar6;
  char *pcVar7;
  char *pcVar8;
  int iVar9;
  
  if ((param_2 & ~-param_2) != 0) {
    pcVar7 = param_1 + 1;
    iVar9 = 0;
    *param_1 = 0x2a;
    iVar2 = FUN_08006e98();
    do {
      iVar3 = 0;
      uVar5 = *(uint *)(iVar2 + iVar9 * 4);
      pcVar8 = pcVar7;
      do {
        bVar1 = (byte)(uVar5 >> 0x18);
        if (uVar5 >> 0x1c < 10) {
          cVar6 = (bVar1 >> 4) + 0x30;
        }
        else {
          cVar6 = (bVar1 >> 4) + 0x57;
        }
        iVar3 = iVar3 + 1;
        pcVar7 = pcVar8 + 1;
        *pcVar8 = cVar6;
        uVar5 = uVar5 << 4;
        pcVar8 = pcVar7;
      } while (iVar3 < 8);
      iVar9 = iVar9 + 1;
    } while (iVar9 < 5);
    *pcVar7 = '\0';
    return param_1;
  }
  if (param_2 == 4) {
    iVar2 = FUN_08006e98();
    uVar5 = *(uint *)(iVar2 + 8);
  }
  else if ((int)param_2 < 5) {
    if (param_2 == 1) {
      puVar4 = (uint *)FUN_08006e98();
      uVar5 = *puVar4;
    }
    else {
      if (param_2 != 2) {
        return (undefined1 *)0x0;
      }
      iVar2 = FUN_08006e98();
      uVar5 = *(uint *)(iVar2 + 4);
    }
  }
  else if (param_2 == 8) {
    iVar2 = FUN_08006e98();
    uVar5 = *(uint *)(iVar2 + 0xc);
  }
  else {
    if (param_2 != 0x10) {
      return (undefined1 *)0x0;
    }
    iVar2 = FUN_08006e98();
    uVar5 = *(uint *)(iVar2 + 0x10);
  }
  if (uVar5 == 0) {
    return &DAT_08007408;
  }
  return (undefined1 *)((uVar5 & 0xfffffffc) + *(int *)((uVar5 & 0xfffffffc) - 4));
}




/* 0x08007302 */
undefined * FUN_08007302(param_1, param_2, param_3)
undefined4 param_1; uint param_2; char * param_3;
{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined *puVar4;
  uint uVar5;
  byte *pbVar6;
  byte *pbVar7;
  uint uVar8;
  
  if ((param_2 != 0) && (param_2 >> 5 == 0)) {
    if (param_3 != (char *)0x0) {
      if (*param_3 != '*') {
        if ((int)(param_2 << 0x1e) < 0) {
          iVar1 = FUN_08039248(&DAT_0803e420,param_3);
          if (iVar1 == 0) {
            return (undefined *)0x0;
          }
          iVar2 = FUN_08006e98();
          *(int *)(iVar2 + 4) = iVar1 + 1;
        }
        if ((param_2 & 1) != 0) {
          if (false) {
            return &DAT_0803e420;
          }
          puVar3 = (undefined4 *)FUN_08006e98(&DAT_0803e420,param_3);
          *puVar3 = &DAT_0803e420;
        }
        if ((int)(param_2 << 0x1d) < 0) {
          if (false) {
            return &DAT_0803e420;
          }
          iVar1 = FUN_08006e98(&DAT_0803e420,param_3);
          *(undefined **)(iVar1 + 8) = &DAT_0803e420;
        }
        if ((int)(param_2 << 0x1c) < 0) {
          iVar1 = FUN_08039274(&DAT_0803e420,param_3);
          if (iVar1 == 0) {
            return (undefined *)0x0;
          }
          iVar2 = FUN_08006e98();
          *(int *)(iVar2 + 0xc) = iVar1;
        }
        if ((int)(param_2 << 0x1b) < 0) {
          if (false) {
            return &DAT_0803e420;
          }
          iVar1 = FUN_08006e98(&DAT_0803e420,param_3);
          *(undefined **)(iVar1 + 0x10) = &DAT_0803e420;
        }
        puVar4 = (undefined *)FUN_08007268(param_1,param_2);
        return puVar4;
      }
      pbVar6 = (byte *)(param_3 + 1);
      uVar5 = 0;
      do {
        uVar8 = 0;
        iVar1 = 0;
        pbVar7 = pbVar6;
        do {
          pbVar6 = pbVar7 + 1;
          if (*pbVar7 < 0x3a) {
            iVar2 = -0x30;
          }
          else {
            iVar2 = -0x57;
          }
          iVar1 = iVar1 + 1;
          uVar8 = (uint)*pbVar7 + iVar2 | uVar8 << 4;
          pbVar7 = pbVar6;
        } while (iVar1 < 8);
        if ((1 << (uVar5 & 0xff) & param_2) != 0) {
          iVar1 = FUN_08006e98();
          *(uint *)(iVar1 + uVar5 * 4) = uVar8;
        }
        uVar5 = uVar5 + 1;
      } while ((int)uVar5 < 5);
    }
    puVar4 = (undefined *)FUN_08007268(param_1,param_2);
    return puVar4;
  }
  return (undefined *)0x0;
}




