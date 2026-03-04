/* Auto-generated: fhprg_802d61a.c */
/* Functions: 10 */
#include "globals.h"

/* 0x0802d61a */
void FUN_0802d61a(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 local_28;
  undefined4 local_24;
  
  uVar6 = 0;
  local_28 = param_3;
  local_24 = param_4;
  uVar1 = FUN_0802b5d8();
  local_28 = 0;
  local_24 = 0;
  do {
    iVar2 = FUN_0802b68c();
    if (iVar2 != 0) {
      for (uVar5 = 0; uVar5 < uVar1; uVar5 = uVar5 + 1) {
        uVar3 = FUN_0802b170(uVar6,uVar5);
        uVar4 = 0;
        do {
          local_28 = CONCAT22(_GHIDRA_FIELD(local_28, 2, ushort),(short)(uVar4 << 8));
          iVar2 = FUN_0802e9f0(uVar3,&local_28);
          if (iVar2 == 0) {
            FUN_0802d56c(uVar3,&local_28,uVar6 & 0xff);
          }
          uVar4 = uVar4 + 1;
        } while (uVar4 < 0x100);
      }
    }
    uVar6 = uVar6 + 1;
  } while (uVar6 < 7);
  return;
}




/* 0x0802d714 */
uint FUN_0802d714(param_1, param_2, param_3, param_4, param_5)
undefined4 param_1; uint param_2; uint param_3; uint param_4; int param_5;
{
  ushort uVar1;
  undefined4 *puVar2;
  uint uVar3;
  ushort *puVar4;
  uint uVar5;
  uint local_1c;
  
  local_1c = param_4;
  puVar2 = (undefined4 *)FUN_0802d7bc();
  if (puVar2 == (undefined4 *)0x0) {
    uVar3 = 0x16;
  }
  else if (param_2 < *(byte *)(puVar2 + 2)) {
    puVar4 = (ushort *)puVar2[1];
    if (param_5 == 0) {
      uVar1 = puVar4[3];
    }
    else {
      uVar1 = puVar4[4];
    }
    uVar3 = (uint)uVar1 + puVar4[1] * param_2 + (uint)*puVar4 & 0xffff;
    uVar5 = FUN_0802b22c(*(undefined4 *)*puVar2,uVar3,0xff,&local_1c,0);
    if ((param_3 & 1) != 0) {
      local_1c = CONCAT31(_GHIDRA_FIELD(local_1c, 1, uint24_t),(byte)local_1c & 0x7f | (byte)(param_4 << 7));
    }
    if ((int)(param_3 << 0x1e) < 0) {
      local_1c = CONCAT31(_GHIDRA_FIELD(local_1c, 1, uint24_t),(byte)local_1c & 0xbf | (byte)(param_4 << 6));
    }
    if ((int)(param_3 << 0x1d) < 0) {
      local_1c = CONCAT31(_GHIDRA_FIELD(local_1c, 1, uint24_t),(byte)local_1c & 0xdf | (byte)(param_4 << 5));
    }
    uVar3 = FUN_0802b248(*(undefined4 *)*puVar2,uVar3,local_1c & 0xff,0);
    uVar3 = uVar3 | uVar5;
  }
  else {
    uVar3 = 0x78;
  }
  return uVar3;
}




/* 0x0802d7bc */
undefined4 FUN_0802d7bc(param_1)
uint param_1;
{
  if (param_1 < 7) {
    return *(undefined4 *)(&DAT_0805a280 + param_1 * 4);
  }
  return 0;
}




/* 0x0802d7d0 */
undefined8 FUN_0802d7d0(param_1, param_2, param_3, param_4, param_5, param_6)
undefined4 param_1; int param_2; uint param_3; uint param_4; uint param_5; int param_6;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = param_2;
  if (((param_2 == 1) || (param_2 == 2)) || (param_2 == 4)) {
    if (param_3 < 9) {
      if (param_4 < 4) {
        if (param_5 < 0x200) {
          uVar3 = param_3;
          iVar1 = FUN_0802d8a0(param_1,0);
          if (iVar1 == 0) {
            if (param_6 != 0) {
              iVar2 = 0;
              param_4 = 0;
              iVar1 = FUN_0802c454(param_1,param_3,0,0,0,0,0);
              if (((iVar1 != 0) || (iVar1 = FUN_0802c4b0(param_1,param_3,3), iVar1 != 0)) ||
                 (iVar1 = FUN_0802c532(param_1,param_3,2,7), iVar1 != 0)) goto LAB_0802d7ee;
              iVar2 = 0;
              uVar3 = 0;
              iVar1 = FUN_0802c348(param_1,param_3,0,0,0,0);
              if (((iVar1 != 0) ||
                  (iVar1 = FUN_0802c576(param_1,param_3,param_5 & 0xffff), iVar1 != 0)) ||
                 ((iVar1 = FUN_0802c5e4(param_1,param_3,1), iVar1 != 0 ||
                  (iVar1 = FUN_0802c4ee(param_1,param_3,1), iVar1 != 0)))) goto LAB_0802d7ee;
            }
            iVar2 = 0;
            iVar1 = FUN_0802d714(param_1,0,param_2,param_6,0,uVar3,param_4);
          }
        }
        else {
          iVar1 = 0x12;
        }
      }
      else {
        iVar1 = 0x11;
      }
    }
    else {
      iVar1 = 0x10;
    }
  }
  else {
    iVar1 = 0xf;
  }
LAB_0802d7ee:
  return CONCAT44(iVar2,iVar1);
}




/* 0x0802d8a0 */
undefined4 FUN_0802d8a0(param_1, param_2, param_3)
undefined4 param_1; uint param_2; int param_3;
{
  undefined4 *puVar1;
  undefined4 uVar2;
  ushort *puVar3;
  
  puVar1 = (undefined4 *)FUN_0802d7bc();
  if (puVar1 == (undefined4 *)0x0) {
    return 0x16;
  }
  if (*(byte *)(puVar1 + 2) <= param_2) {
    return 0x78;
  }
  puVar3 = (ushort *)puVar1[1];
  if ((((param_3 != 0) && (param_3 != 1)) && (param_3 != 2)) && (param_3 != 3)) {
    return 0x10;
  }
  uVar2 = FUN_0802b282(*(undefined4 *)*puVar1,
                       (uint)puVar3[2] + puVar3[1] * param_2 + (uint)*puVar3 & 0xffff,3,param_3,0);
  return uVar2;
}




/* 0x0802d920 */
uint FUN_0802d920(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; uint param_3; undefined4 param_4;
{
  char cVar1;
  short sVar2;
  ushort uVar3;
  undefined1 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  uint uVar8;
  uint local_28;
  undefined4 local_24;
  
  uVar8 = 0;
  local_28 = param_3 & 0xffffff00;
  local_24 = param_4;
  puVar4 = (undefined1 *)FUN_0802e86c(0x24);
  if (puVar4 == (undefined1 *)0x0) {
LAB_0802d9ee:
    uVar8 = 0x73;
  }
  else {
    for (; puVar4[6] != '\x04'; puVar4 = puVar4 + 0xc) {
      if (uVar8 == 0) {
        DAT_0804dc28 = DAT_0804dc28 + 1;
      }
      else {
        DAT_0804dc2c = (uint)*(ushort *)(puVar4 + 2);
      }
      if (puVar4[6] == '\x01') {
LAB_0802d95a:
        iVar5 = FUN_0802db9c(*(undefined4 *)(puVar4 + 8),local_24,puVar4[6],puVar4[7]);
        if (iVar5 == 1) {
          cVar1 = puVar4[6];
          if (cVar1 == '\0') {
            sVar2 = *(short *)(puVar4 + 2);
            *(short *)(puVar4 + 2) = sVar2 + *(short *)(puVar4 + 4);
            uVar7 = FUN_0802b248(*puVar4,sVar2 + *(short *)(puVar4 + 4),puVar4[1],1);
LAB_0802d9ea:
            uVar8 = uVar8 | uVar7;
          }
          else if (cVar1 == '\x01') {
            FUN_0802af1c(*(undefined2 *)(puVar4 + 4));
          }
          else {
            if (cVar1 == '\x02') {
              puVar6 = (undefined4 *)FUN_0802e86c(0x87);
              if (puVar6 != (undefined4 *)0x0) {
                DAT_0804dc22 = 0;
                DAT_0804dc24 = *(undefined2 *)*puVar6;
                uVar3 = (&DAT_0804dc22)[(byte)puVar4[1]];
                iVar5 = FUN_0802e86c(0x25);
                uVar7 = FUN_0802cf28(*puVar4,iVar5 + (uint)uVar3 * 4,(&DAT_0804dc24)[uVar3]);
                goto LAB_0802d9ea;
              }
              goto LAB_0802d9ee;
            }
            if (cVar1 != '\x03') {
              uVar8 = uVar8 | 0x7a;
            }
          }
        }
      }
      else {
        FUN_0802d530(*puVar4,&local_28,&local_24);
        if ((char)local_28 != '\0') goto LAB_0802d95a;
      }
    }
  }
  return uVar8;
}




/* 0x0802d9f8 */
uint pm_set_val()
{
  ushort uVar1;
  uint uVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  byte *pbVar7;
  uint uVar8;
  byte *pbVar9;
  byte bVar10;
  char local_24 [4];
  undefined4 local_20;
  byte local_1c [4];
  char local_18 [4];
  
  pbVar9 = (byte *)0x0;
  local_24[0] = '\0';
  uVar2 = FUN_0802dbda(local_18,0);
  if (local_18[0] == '\0') {
    pcVar6 = "PM_SET_VAL:Skip";
  }
  else {
    pbVar3 = (byte *)FUN_0802e86c(0x24);
    iVar4 = FUN_0802e86c(0x25);
    boot_log_message("PM_SET_VAL:Start");
    for (; pbVar3[6] != 4; pbVar3 = pbVar3 + 0xc) {
      if (((pbVar3[6] == 1) || (FUN_0802d530(*pbVar3,local_24,&local_20), local_24[0] != '\0')) &&
         (iVar5 = FUN_0802db9c(*(undefined4 *)(pbVar3 + 8),local_20,pbVar3[6],pbVar3[7]), iVar5 == 1
         )) {
        bVar10 = pbVar3[6];
        pbVar7 = pbVar3;
        if (bVar10 == 0) {
          for (; pbVar7[6] != 4; pbVar7 = pbVar7 + 0xc) {
            if (((*pbVar7 == *pbVar3) && (*(short *)(pbVar7 + 2) == *(short *)(pbVar3 + 2))) &&
               (*(short *)(pbVar7 + 4) == *(short *)(pbVar3 + 4))) {
              pbVar9 = pbVar7;
            }
          }
          if ((*(short *)(pbVar3 + 4) != 0xd0) && (*(short *)(pbVar3 + 4) != 0x15)) {
            uVar8 = FUN_0802b1e8(*pbVar3,*(undefined2 *)(pbVar3 + 2),local_1c,1);
            uVar2 = uVar2 | uVar8;
            uVar1 = *(ushort *)(pbVar3 + 2);
            bVar10 = pbVar3[1];
            uVar8 = (uint)*pbVar3;
            if (pbVar9[1] == local_1c[0]) {
              pcVar6 = "PASS:%d,0x%X,set:0x%X,get:0x%X";
            }
            else {
              pcVar6 = "VIOLATION:%d,0x%X,set:0x%X,get:0x%X";
            }
            goto LAB_0802dad0;
          }
        }
        else if (bVar10 == 2) {
          pcVar6 = "PBS:%d:0x%X,0x%X";
          DAT_0804dc20 = pbVar3[1];
          uVar8 = (uint)DAT_0804dc20;
          iVar5 = iVar4 + uVar8 * 4 + (uint)(ushort)(&DAT_0804dc24)[uVar8] * 4;
          bVar10 = *(byte *)(iVar5 + -4);
          uVar1 = (ushort)*(byte *)(iVar5 + -3);
LAB_0802dad0:
          snprintf_buf(&DAT_080585f8,0x3c,pcVar6,uVar8,uVar1,bVar10);
          boot_log_message(&DAT_080585f8);
        }
        else if (bVar10 != 3) {
          uVar2 = uVar2 | 0x7a;
        }
      }
    }
    pcVar6 = "PM_SET_VAL:End";
  }
  boot_log_message(pcVar6);
  return uVar2;
}




/* 0x0802db9c */
undefined4 FUN_0802db9c(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; undefined4 param_3; undefined4 param_4;
{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 != 0xffffffff) {
    switch(param_4) {
    case 0:
      if (param_2 != param_1) {
        return 0;
      }
      break;
    case 1:
      if (param_2 <= param_1) {
        return 0;
      }
      break;
    case 2:
      if (param_2 < param_1) {
        return 0;
      }
      break;
    case 3:
      if (param_1 <= param_2) {
        return 0;
      }
      break;
    case 4:
      if (param_1 < param_2) {
        return 0;
      }
      break;
    default:
      goto switchD_0802dbac_default;
    }
  }
  uVar1 = 1;
switchD_0802dbac_default:
  return uVar1;
}




/* 0x0802dbda */
uint FUN_0802dbda(param_1, param_2)
undefined1 * param_1; int param_2;
{
  undefined2 *puVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  *param_1 = 0;
  puVar1 = (undefined2 *)FUN_0802e824(0x3b);
  if (puVar1 != (undefined2 *)0x0) {
    uVar3 = FUN_0802b22c(0,*puVar1,1,param_1,1);
  }
  if (param_2 != 0) {
    uVar2 = FUN_0802b282(0,*puVar1,1,0,1);
    uVar3 = uVar3 | uVar2;
  }
  return uVar3;
}




/* 0x0802dc20 */
undefined1 FUN_0802dc20()
{
  undefined1 uVar1;
  int iVar2;
  
  uVar1 = 0;
  if (DAT_080508f0 != '\0') {
    iVar2 = FUN_0800cf6c(DAT_080508f4,0);
    FUN_0800cdc8(DAT_080508f4);
    if (iVar2 == 0) {
      return 0;
    }
    uVar1 = 5;
  }
  return uVar1;
}




