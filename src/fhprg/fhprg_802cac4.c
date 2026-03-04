/* Auto-generated: fhprg_802cac4.c */
/* Functions: 17 */
#include "globals.h"

/* 0x0802cac4 */
int FUN_0802cac4(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; int param_3;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uStack_10;
  int iStack_c;
  
  uVar2 = 0;
  if (param_3 != 0) {
    if (param_3 == 1) {
      uVar2 = 0x40;
    }
    else if (param_3 == 2) {
      uVar2 = 0x80;
    }
    else {
      if (param_3 != 3) {
        return 0x16;
      }
      uVar2 = 0xc0;
    }
  }
  uVar3 = param_1;
  uStack_10 = param_2;
  iStack_c = param_3;
  iVar1 = FUN_0802b248(param_1,0x7041,uVar2,1);
  if (iVar1 == 0) {
    iVar1 = FUN_0802b26a(param_1,0x7042,2,&uStack_10,1,uVar3);
  }
  return iVar1;
}




/* 0x0802cb12 */
void FUN_0802cb12(param_1)
undefined4 param_1;
{
  FUN_0802b248(param_1,0x7040,0,1);
  return;
}




/* 0x0802cb1e */
undefined4 FUN_0802cb1e(param_1)
undefined4 param_1;
{
  FUN_0802b248(param_1,0x7040,0x80,1);
  return 0;
}




/* 0x0802cb2c */
int FUN_0802cb2c()
{
  int iVar1;
  int iVar2;
  uint in_r3 = 0;
  uint uVar3;
  undefined4 local_20;
  uint local_1c;
  
  uVar3 = 0;
  local_20 = 0;
  local_1c = in_r3 & 0xffffff00;
  FUN_08006d14(&DAT_08058490,0x150);
  iVar1 = FUN_0802e86c(0x87);
  if (iVar1 == 0) {
LAB_0802cbae:
    iVar1 = 0x73;
  }
  else {
    do {
      iVar2 = FUN_0802b6b4(uVar3,0,&local_20);
      if (iVar2 != 0) break;
      iVar2 = FUN_0802b1e8(local_20,0x7004,&local_1c,0);
      if (iVar2 != 0) {
        return iVar2;
      }
      if ((char)local_1c != '\x16') {
        return 0x16;
      }
      DAT_0804dc0c = *(int *)(iVar1 + uVar3 * 4);
      if (DAT_0804dc0c == 0) goto LAB_0802cbae;
      if (*(char *)(DAT_0804dc0c + 2) == '\x01') {
        iVar2 = FUN_0802cbd4(local_20,&DAT_08058490 + uVar3 * 0x30);
      }
      else {
        iVar2 = FUN_0802cd8c();
      }
      if (iVar2 != 0) {
        FUN_0802cb12(local_20);
        return iVar2;
      }
      uVar3 = uVar3 + 1 & 0xff;
    } while (uVar3 < 7);
    iVar1 = 0;
    DAT_0804dc08 = 1;
  }
  return iVar1;
}




/* 0x0802cbd4 */
undefined4 FUN_0802cbd4(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 * param_2; undefined4 param_3; uint param_4;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  ushort uVar4;
  char cVar5;
  uint uVar6;
  uint local_2c;
  uint local_28;
  
  local_28 = param_4 & 0xffffff00;
  local_2c = 0;
  uVar6 = 0xc;
  *param_2 = 4;
  cVar5 = '\x03';
  uVar4 = 0;
  iVar1 = FUN_0802b1e8(param_1,((uint*)&DAT_0804dc0c)[4] + ((uint*)&DAT_0804dc0c)[2],&local_28,1,param_2);
  if (iVar1 == 0) {
    param_2[10] = local_28 & 0xff;
    local_28 = local_28 & 0xffffff00;
    iVar1 = FUN_0802b20e(param_1,((uint*)&DAT_0804dc0c)[5] + ((uint*)&DAT_0804dc0c)[2],4,&local_2c,1);
    if (iVar1 == 0) {
      param_2[6] = local_2c & 0xff;
      param_2[7] = (local_2c << 0x10) >> 0x18;
      param_2[8] = (local_2c << 8) >> 0x18;
      param_2[9] = local_2c >> 0x18;
      do {
        local_2c = 0;
        iVar1 = FUN_0802b20e(param_1,((uint*)&DAT_0804dc0c)[9] + ((uint*)&DAT_0804dc0c)[2] + uVar4,3,&local_2c,1);
        if (iVar1 != 0) {
          return 0;
        }
        local_2c = local_2c & 0xffffff;
        uVar6 = uVar6 - 1 & 0xff;
        uVar2 = uVar6 - 1 & 0xff;
        *(byte *)((int)param_2 + uVar6 + 4) = (byte)local_2c & 0x3f;
        uVar3 = uVar2 - 1 & 0xff;
        uVar4 = uVar4 + 3 & 0xff;
        *(byte *)((int)param_2 + uVar2 + 4) = (byte)((local_2c << 0x14) >> 0x1a);
        uVar6 = uVar3 - 1 & 0xff;
        *(byte *)((int)param_2 + uVar3 + 4) = (byte)((local_2c << 0xe) >> 0x1a);
        cVar5 = cVar5 + -1;
        *(byte *)((int)param_2 + uVar6 + 4) = (byte)(local_2c >> 0x10) >> 2;
        local_2c = 0;
      } while ((cVar5 != '\0') && (3 < uVar6));
      iVar1 = FUN_0802b1e8(param_1,((uint*)&DAT_0804dc0c)[10] + ((uint*)&DAT_0804dc0c)[2],&local_28,1);
      if (iVar1 == 0) {
        param_2[0xb] = param_2[0xb] & 0xffffff00 | local_28 >> 4 & 0xf |
                       ((local_28 << 0x1c) >> 0x1d) << 4 | (local_28 & 1) << 7;
        local_28 = local_28 & 0xffffff00;
        iVar1 = FUN_0802cb1e(param_1);
        if (((iVar1 == 0) && (iVar1 = FUN_0802cac4(param_1,*(uint*)DAT_0804dc0c * 4 + -4,2), iVar1 == 0))
           && (iVar1 = FUN_0802b20e(param_1,0x704c,4,&local_2c,1), iVar1 == 0)) {
          param_2[4] = local_2c & 0xffff;
          local_2c = 0;
          iVar1 = FUN_0802cac4(param_1,*(uint*)DAT_0804dc0c * 4 + 0x3fc,2);
          if ((iVar1 == 0) && (iVar1 = FUN_0802b20e(param_1,0x704c,4,&local_2c,1), iVar1 == 0)) {
            param_2[5] = local_2c & 0xffff;
            local_2c = 0;
            FUN_0802cb12(param_1);
          }
        }
      }
    }
  }
  return 0;
}




/* 0x0802cd8c */
undefined4 FUN_0802cd8c(param_1, param_2)
undefined4 param_1; undefined4 * param_2;
{
  int iVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  uint local_2c;
  
  uVar4 = 0xc;
  local_2c = 0;
  cVar3 = '\x04';
  *param_2 = 4;
  iVar1 = FUN_0802cb1e();
  if (((iVar1 == 0) && (iVar1 = FUN_0802cac4(param_1,*(uint*)DAT_0804dc0c * 4 + -0x1c,2), iVar1 == 0)) &&
     (iVar1 = FUN_0802b20e(param_1,0x704c,4,&local_2c,1), iVar1 == 0)) {
    param_2[10] = local_2c & 0xff;
    param_2[6] = (local_2c << 0x10) >> 0x18;
    local_2c = 0;
    iVar1 = FUN_0802b20e(param_1,0x704c,4,&local_2c,1);
    if (iVar1 == 0) {
      param_2[7] = local_2c & 0xff;
      param_2[8] = (local_2c << 0x10) >> 0x18;
      param_2[9] = (local_2c << 8) >> 0x18;
      do {
        local_2c = 0;
        iVar1 = FUN_0802b20e(param_1,0x704c,4,&local_2c,1);
        if (iVar1 != 0) {
          return 0;
        }
        uVar4 = uVar4 - 1 & 0xff;
        uVar2 = uVar4 - 1 & 0xff;
        *(char *)((int)param_2 + uVar4 + 4) = (char)local_2c;
        uVar4 = uVar2 - 1 & 0xff;
        *(char *)((int)param_2 + uVar2 + 4) = (char)(local_2c >> 8);
        *(char *)((int)param_2 + uVar4 + 4) = (char)(local_2c >> 0x10);
        cVar3 = cVar3 + -1;
        local_2c = 0;
      } while ((cVar3 != '\0') && (2 < uVar4));
      iVar1 = FUN_0802b20e(param_1,0x704c,4,&local_2c,1);
      if (iVar1 == 0) {
        param_2[4] = local_2c & 0xffff;
        local_2c = 0;
        iVar1 = FUN_0802cac4(param_1,*(uint*)DAT_0804dc0c * 4 + 0x3fc,2);
        if ((iVar1 == 0) && (iVar1 = FUN_0802b20e(param_1,0x704c,4,&local_2c,1), iVar1 == 0)) {
          param_2[5] = local_2c & 0xffff;
          local_2c = 0;
          FUN_0802cb12(param_1);
        }
      }
    }
  }
  return 0;
}




/* 0x0802cec0 */
undefined4 FUN_0802cec0()
{
  int iVar1;
  uint uVar2;
  int local_10;
  
  uVar2 = 0;
  local_10 = 0;
  if ((((DAT_0804dc08 != '\0') && (iVar1 = FUN_0800b424(), iVar1 == 0)) &&
      (iVar1 = FUN_0800b388("PM_PBS_INFO",0x170,0x10000,&local_10), iVar1 == 0)) && (local_10 != 0))
  {
    do {
      thunk_FUN_08027bf8(local_10 + uVar2 * 0x30 + 0x20,0x30,&DAT_08058490 + uVar2 * 0x30);
      uVar2 = uVar2 + 1 & 0xff;
    } while (uVar2 < 7);
    return 0;
  }
  return 0x16;
}




/* 0x0802cf28 */
int FUN_0802cf28(param_1, param_2, param_3)
undefined4 param_1; int param_2; uint param_3;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  while( true ) {
    iVar2 = 0;
    if (param_3 <= uVar3) {
      iVar1 = FUN_0800bb48();
      if ((iVar1 != 0xf) && (iVar1 = FUN_0800bb48(), iVar1 != 0x10)) {
        iVar2 = FUN_0802cf86(param_1,param_2,param_3);
      }
      return iVar2;
    }
    iVar2 = FUN_0802b26a(param_1,0x7048,4,param_2 + uVar3 * 4,1);
    if (iVar2 != 0) break;
    FUN_0802af1c(10);
    uVar3 = uVar3 + 1;
  }
  return iVar2;
}




/* 0x0802cf86 */
uint FUN_0802cf86(param_1, param_2, param_3, param_4)
undefined4 param_1; int param_2; uint param_3; int param_4;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int local_24;
  
  local_24 = param_4;
  uVar1 = FUN_0802cac4(param_1,0x400,2,param_4,param_3);
  if (uVar1 == 0) {
    for (uVar3 = 0; uVar3 < param_3; uVar3 = uVar3 + 1) {
      uVar2 = FUN_0802b20e(param_1,0x704c,4,&local_24,1);
      if ((uVar2 | uVar1) != 0) {
        return uVar2 | uVar1;
      }
      FUN_0802af1c(10);
      if (*(int *)(param_2 + uVar3 * 4) != local_24) {
        return 0x26;
      }
      uVar1 = 0;
    }
  }
  return uVar1;
}




/* 0x0802cfe0 */
uint FUN_0802cfe0()
{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  undefined1 auStack_44 [16];
  undefined4 local_34;
  char local_18 [8];
  
  bVar3 = 0;
  uVar1 = FUN_0802dbda(local_18,1);
  if (local_18[0] != '\0') {
    for (; bVar3 <= DAT_0804dc20; bVar3 = bVar3 + 1) {
      uVar2 = FUN_0802b5dc(bVar3,auStack_44);
      uVar1 = uVar1 | uVar2;
      snprintf_buf(&DAT_080585f8,0x3c,"PBS_GET:%d:0x%X",bVar3,local_34);
      boot_log_message(&DAT_080585f8);
    }
  }
  return uVar1;
}




/* 0x0802d044 */
undefined4 FUN_0802d044()
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  undefined4 uStack_c;
  
  uVar2 = 0;
  local_10 = 0x10800;
  uStack_c = 0x3040000;
  iVar1 = FUN_0800e614(1);
  if (((iVar1 != 0) || (iVar1 = FUN_0800e5f4(&local_10,1), iVar1 != 0)) ||
     (iVar1 = FUN_0800e51c(), iVar1 != 0)) {
    uVar2 = 9;
  }
  return uVar2;
}




/* 0x0802d074 */
int FUN_0802d074(param_1, param_2, param_3, param_4)
undefined4 param_1; int param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 local_14;
  
  local_14 = 0;
  if (param_2 == 0) {
    iVar1 = 0x73;
  }
  else {
    iVar1 = FUN_0802b6b4(param_1,0,&local_14,param_4,param_3);
    if (iVar1 != 0) {
      return 0xe;
    }
    if ((DAT_0804d288 != '\0') || (iVar1 = FUN_0802d0b8(), iVar1 == 0)) {
      iVar1 = FUN_0802b20e(local_14,0x808,8,param_2,0);
      return iVar1;
    }
  }
  return iVar1;
}




/* 0x0802d0b8 */
int FUN_0802d0b8()
{
  int iVar1;
  int iVar2;
  char local_24 [4];
  char local_20 [8];
  undefined4 local_18;
  int local_14;
  
  iVar1 = DAT_0804cd58;
  local_14 = DAT_0804cd58;
  local_24[0] = '\0';
  local_20[0] = '\0';
  local_18 = 0;
  iVar2 = FUN_0802b1e8(0,0x804,local_24,0);
  if (iVar2 == 0) {
    if (local_24[0] == '\x01') {
      iVar2 = FUN_0802b1e8(0,0x801,local_20);
      if (iVar2 == 0) {
        if (local_20[0] == '\0') {
          DAT_0804d2b4 = DAT_0804d2b2;
          DAT_0804d2c4 = DAT_0804d2c2;
          DAT_0804d2d4 = DAT_0804d2d2;
          DAT_0804d2e4 = DAT_0804d2e2;
          DAT_0804d2f4 = DAT_0804d2f2;
          DAT_0804d28c = DAT_0804d28a;
          DAT_0804d294 = DAT_0804d292;
        }
        iVar2 = FUN_0802b20e(0,0x80a,2,&local_18,0);
        if ((iVar2 == 0) &&
           ((((char)local_18 == '\0' && (_GHIDRA_FIELD(local_18, 1, byte) == '\0')) ||
            (iVar2 = FUN_0802b282(0,0x88d,1,1,0), iVar2 == 0)))) {
          DAT_0804d288 = 1;
        }
      }
    }
    else {
      iVar2 = 0x16;
    }
  }
  if (local_14 != iVar1) {
    FUN_08010960();
  }
  return iVar2;
}




/* 0x0802d180 */
uint FUN_0802d180(param_1, param_2)
undefined4 param_1; uint param_2;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 local_10;
  
  uVar4 = 1;
  local_10 = 0;
  iVar1 = FUN_0802b6b4(param_1,0,&local_10);
  if (iVar1 != 0) {
    return 0xe;
  }
  if (param_2 < 0xf) {
    if ((DAT_0804d288 != '\0') || (uVar2 = FUN_0802d0b8(), uVar2 == 0)) {
      if (false) {
switchD_0802d1b0_caseD_9:
        return 0x16;
      }
      switch(param_2) {
      case 0:
        break;
      case 1:
        uVar4 = 4;
        break;
      case 2:
        uVar4 = 5;
        break;
      case 3:
        uVar4 = 6;
        break;
      case 4:
        uVar4 = 7;
        break;
      case 5:
      case 6:
        uVar4 = 8;
        break;
      case 7:
        uVar4 = 9;
        break;
      case 8:
        uVar4 = 2;
        break;
      default:
        goto switchD_0802d1b0_caseD_9;
      case 0xe:
        uVar4 = 0xf;
      }
      uVar2 = FUN_0802b248(local_10,DAT_0804d28c,0);
      if (uVar2 == 0) {
        thunk_FUN_080199b4(300);
        uVar2 = FUN_0802b248(local_10,DAT_0804d28a,uVar4,0);
        uVar3 = FUN_0802b248(local_10,DAT_0804d28c,(char)DAT_0804d28e,0);
        return uVar3 | uVar2;
      }
    }
  }
  else {
    uVar2 = 0xf;
  }
  return uVar2;
}




/* 0x0802d228 */
int FUN_0802d228(param_1, param_2, param_3, param_4, param_5)
int param_1; int param_2; uint param_3; uint param_4; uint param_5;
{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined2 *puVar5;
  uint uVar6;
  uint local_2c;
  
  if (param_1 != 0) {
    return 0xe;
  }
  if (DAT_0804d338 < param_3) {
    return 0x10;
  }
  if (DAT_0804d358 < param_4) {
    return 0x11;
  }
  if (param_5 < 0xf) {
    uVar6 = param_3;
    local_2c = param_4;
    if ((DAT_0804d288 == '\0') && (iVar2 = FUN_0802d0b8(), iVar2 != 0)) {
      return iVar2;
    }
    uVar3 = FUN_0802eb04(param_3,&DAT_0804d2fc,0x10);
    uVar4 = FUN_0802eb04(param_4,&DAT_0804d33c,8);
    if (false) {
LAB_0802d23a:
      return 0xf;
    }
    switch(param_2) {
    case 0:
      puVar5 = (undefined2 *)0x804d2aa;
      break;
    case 1:
      puVar5 = (undefined2 *)0x804d2ba;
      break;
    case 2:
      puVar5 = (undefined2 *)0x804d2ca;
      break;
    default:
      goto LAB_0802d23a;
    case 4:
      puVar5 = (undefined2 *)0x804d2da;
      break;
    case 5:
      puVar5 = &DAT_0804d2ea;
    }
    iVar2 = FUN_0802b1e8(0,puVar5[5],&local_2c,0,uVar6);
    if (iVar2 != 0) {
      return iVar2;
    }
    uVar1 = puVar5[6] & (ushort)(byte)local_2c;
    local_2c = CONCAT31(_GHIDRA_FIELD(local_2c, 1, uint24_t),(char)uVar1);
    if (uVar1 != 0) {
      iVar2 = FUN_0802b282(0,puVar5[5],(char)puVar5[6],0,0);
      if (iVar2 != 0) {
        return iVar2;
      }
      thunk_FUN_080199b4(300);
    }
    if (param_2 == 0) {
      iVar2 = FUN_0802b282(0,DAT_0804d29a,(char)DAT_0804d29c,0,0);
      thunk_FUN_080199b4(0x96);
      if (iVar2 != 0) {
        return iVar2;
      }
    }
    iVar2 = FUN_0802b282(0,*puVar5,(char)puVar5[1],uVar3,0);
    if (iVar2 != 0) {
      return iVar2;
    }
    if ((param_2 == 0) &&
       (iVar2 = FUN_0802b282(0,DAT_0804d29a,(char)DAT_0804d29c,0xff,0), iVar2 != 0)) {
      return iVar2;
    }
    iVar2 = FUN_0802b282(0,puVar5[2],(char)puVar5[3],uVar4,0);
    if (iVar2 != 0) {
      return iVar2;
    }
    if (true) {
      switch(param_5) {
      case 0:
        uVar3 = 1;
        break;
      case 1:
        uVar3 = 4;
        break;
      case 2:
        uVar3 = 5;
        break;
      case 3:
        uVar3 = 6;
        break;
      case 4:
        uVar3 = 7;
        break;
      case 5:
        uVar3 = 8;
        break;
      default:
        goto switchD_0802d36c_caseD_6;
      case 7:
        uVar3 = 9;
        break;
      case 0xe:
        uVar3 = 0xf;
      }
      iVar2 = FUN_0802b282(0,puVar5[4],(char)puVar5[7],uVar3,0);
      if ((byte)local_2c == '\0') {
        return iVar2;
      }
      iVar2 = FUN_0802b282(0,puVar5[5],(char)puVar5[6],0xff,0);
      return iVar2;
    }
  }
switchD_0802d36c_caseD_6:
  return 0x12;
}




/* 0x0802d3d0 */
int FUN_0802d3d0(param_1, param_2, param_3)
int param_1; undefined4 param_2; int param_3;
{
  int iVar1;
  undefined2 *puVar2;
  undefined4 uVar3;
  
  if (param_1 == 0) {
    if ((DAT_0804d288 != '\0') || (iVar1 = FUN_0802d0b8(), iVar1 == 0)) {
      if (false) {
switchD_0802d3ee_caseD_3:
        return 0xf;
      }
      switch(param_2) {
      case 0:
        puVar2 = (undefined2 *)0x804d2aa;
        break;
      case 1:
        puVar2 = (undefined2 *)0x804d2ba;
        break;
      case 2:
        puVar2 = (undefined2 *)0x804d2ca;
        break;
      default:
        goto switchD_0802d3ee_caseD_3;
      case 4:
        puVar2 = (undefined2 *)0x804d2da;
        break;
      case 5:
        puVar2 = &DAT_0804d2ea;
      }
      if (param_3 == 1) {
        uVar3 = 0xff;
      }
      else {
        uVar3 = 0;
      }
      iVar1 = FUN_0802b282(0,puVar2[5],(char)puVar2[6],uVar3,0);
      return iVar1;
    }
  }
  else {
    iVar1 = 0xe;
  }
  return iVar1;
}




/* 0x0802d530 */
undefined4 FUN_0802d530(param_1, param_2, param_3)
int param_1; undefined1 * param_2; undefined4 * param_3;
{
  int iVar1;
  uint extraout_r3;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0802b68c((uint)(param_1 << 0x17) >> 0x18);
  if (((iVar1 == 0x7fffffff) || (iVar1 == 0)) || (6 < extraout_r3)) {
    *param_2 = 0;
    uVar2 = 0x17;
  }
  else {
    *param_2 = 1;
    *param_3 = (&DAT_08058688)[extraout_r3];
  }
  return uVar2;
}



/* WARNING: Type propagation algorithm not settling */

