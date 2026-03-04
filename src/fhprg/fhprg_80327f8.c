/* Auto-generated: fhprg_80327f8.c */
/* Functions: 127 */
#include "globals.h"

/* 0x080327f8 */
undefined4 FUN_080327f8()
{
  int iVar1;
  
  iVar1 = FUN_0801622c(0x87c7344c,0x87c734a4,DAT_0804cdf8);
  if (iVar1 != 0) {
    FUN_08032644();
    return 0;
  }
  return 0x87c734a4;
}




/* 0x08032840 */
undefined * FUN_08032840()
{
  return &DAT_0804cc40;
}




/* 0x08032874 */
bool FUN_08032874()
{
  int iVar1;
  
  iVar1 = FUN_080162dc(0x87c7344c,DAT_0804cdf4);
  if (iVar1 != 0) {
    FUN_08032644();
  }
  return iVar1 == 0;
}




/* 0x08032978 */
bool FUN_08032978(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  int iVar1;
  
  iVar1 = FUN_08016338(0x87c7344c,param_1,param_2);
  if (iVar1 != 0) {
    FUN_08032644();
  }
  return iVar1 == 0;
}




/* 0x080329c8 */
undefined4 FUN_080329c8()
{
  return 1;
}




/* 0x080329f8 */
void FUN_080329f8(param_1)
int param_1;
{
  if (param_1 << 0x1d < 0) {
    DataMemoryBarrier(0x1f);
  }
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08032a04 */
void FUN_08032a04(param_1, param_2, param_3)
int param_1; uint * param_2; int param_3;
{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  if (param_3 == 1) {
    if (*(int *)(&DAT_0804e2ac + param_1 * 4) == 2) {
      if (param_1 == 0) {
        _DAT_018004c8 = _DAT_018004c8 & 0xf000fff0;
        return;
      }
      if (param_1 == 1) {
        _DAT_01800508 = _DAT_01800508 & 0xf000fff0 | 1;
      }
    }
  }
  else {
    if (param_3 == 2) {
      puVar4 = (undefined4 *)(param_1 * 0x40 + 0x1842000);
      *puVar4 = 1;
      FUN_080199b4(500);
      *puVar4 = 0;
      return;
    }
    if (param_1 == 0) {
      uVar2 = 1;
    }
    else if (param_1 == 1) {
      uVar2 = 2;
    }
    else {
      uVar2 = 0;
    }
    if (param_2 != (uint *)0x0) {
      uVar3 = *param_2;
      if (uVar3 < 0x191) {
        uVar2 = 1;
      }
      else if (uVar3 < 0x6591) {
        uVar2 = 2;
      }
      else {
        if (52000 < uVar3) {
          if (uVar3 < 0x186a1) {
            uVar1 = 100000;
          }
          else if (param_1 == 0) {
            uVar1 = 0x2b368;
            uVar2 = 1;
          }
          else {
            uVar1 = 200000;
          }
          FUN_0800af38(uVar1,uVar2);
          return;
        }
        uVar2 = 3;
      }
      FUN_0800af10(uVar2);
      return;
    }
  }
  return;
}




/* 0x08032acc */
undefined4 FUN_08032acc()
{
  return 0x20;
}




/* 0x08032ad0 */
undefined4 FUN_08032ad0(param_1)
int param_1;
{
  if (param_1 != 0) {
    return 200000;
  }
  return 0x2b368;
}




/* 0x08032ae4 */
undefined4 FUN_08032ae4(param_1)
uint param_1;
{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 < 2) {
    uVar1 = *(undefined4 *)(&DAT_0804e2b8 + param_1 * 4);
  }
  return uVar1;
}




/* 0x08032af8 */
undefined4 FUN_08032af8(param_1)
uint param_1;
{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 < 2) {
    uVar1 = *(undefined4 *)(&DAT_0804e2ac + param_1 * 4);
  }
  return uVar1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08032b0c */
undefined4 FUN_08032b0c(param_1)
uint param_1;
{
  uint *puVar1;
  uint uVar2;
  
  if ((param_1 < 2) && (*(int *)(&DAT_0804e2ac + param_1 * 4) != 0)) {
    if (param_1 == 0) {
      _DAT_0110a000 = (_DAT_0110a000 & 0x6000) + 0x1fdb;
      puVar1 = (uint *)&DAT_01111000;
      uVar2 = _DAT_01111000 | 2;
    }
    else {
      if (param_1 != 1) {
        return 0;
      }
      puVar1 = (uint *)&DAT_01109000;
      uVar2 = (_DAT_01109000 & 0xe000) + 0x1edb;
    }
    *puVar1 = uVar2;
    return 0;
  }
  return 2;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08032b64 */
void FUN_08032b64()
{
  qtimer_init();
  _DAT_004a1000 = 1;
  return;
}




/* 0x08032b7c */
void FUN_08032b7c(param_1)
undefined4 * param_1;
{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  DAT_0804e2a8 = DAT_0804e2a8 + 1;
  return;
}




/* 0x08032b94 */
int sdcc_command(param_1, param_2)
int * param_1; int * param_2;
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  char cVar6;
  int iVar7;
  uint uVar8;
  bool bVar9;
  undefined4 local_30;
  undefined4 local_2c;
  int local_28;
  
  if ((param_1 == (int *)0x0) || (param_2 == (int *)0x0)) {
    return 0x14;
  }
  if ((char)param_1[0x23] != '\x01') {
    iVar7 = 0;
    FUN_08034edc();
    if (*param_2 == 0) {
      iVar7 = *param_1;
      uVar8 = 0;
      while ((uVar4 = uVar8 + 1, uVar8 < 800 && (uVar8 = FUN_0800bd8c(iVar7), (uVar8 & 0x80) == 0)))
      {
        thunk_FUN_080199b4(10);
        uVar8 = uVar4;
      }
      if (uVar4 < 800) {
        *(undefined4 *)((&DAT_0804e2c8)[iVar7] + 0x38) = 0x80;
        while (uVar4 < 800) {
          uVar8 = FUN_0800bd8c(iVar7);
          if ((uVar8 & 0x80) == 0) {
            return 0;
          }
          thunk_FUN_080199b4(10);
          uVar4 = uVar4 + 1;
        }
      }
      iVar7 = 6;
    }
    else {
      if ((char)param_2[2] != '\0') {
        iVar3 = FUN_08034b88(param_1,param_2);
        if (iVar3 != 0) {
          return iVar3;
        }
        if ((char)param_2[2] != '\0') {
          if ((char)param_2[2] == '\x04') {
            uVar8 = 4;
          }
          else {
            uVar8 = 1;
          }
          piVar5 = param_2 + 3;
          for (uVar4 = 0; uVar4 < uVar8; uVar4 = uVar4 + 1) {
            *piVar5 = *(int *)((&DAT_0804e2c8)[*param_1] + uVar4 * 4 + 0x14);
            piVar5 = piVar5 + 1;
          }
          if (((*param_2 == 0x34) || (*param_2 == 0x35)) && ((param_2[3] & 0xcf00U) != 0)) {
            iVar7 = 0xb;
          }
        }
      }
      if ((param_2[7] != 0) && (iVar7 == 0)) {
        iVar7 = FUN_08035134(param_1);
      }
      FUN_08006d14(&local_28,0x14);
      FUN_0800bd20(*param_1,&local_28);
    }
    return iVar7;
  }
  cVar6 = '\0';
  iVar7 = 0;
  local_28 = 0;
  uVar8 = 0;
  iVar3 = *param_1;
  local_30 = 0;
  local_2c = 0;
  do {
    uVar4 = FUN_0800be68(iVar3);
    if ((uVar4 & 3) == 0) goto LAB_08032cc4;
    thunk_FUN_080199b4(100);
    uVar8 = uVar8 + 100;
  } while (uVar8 < 10000);
  iVar7 = 3;
LAB_08032cc4:
  if (iVar7 == 0) {
    FUN_0800c11c(iVar3,0xf);
    FUN_0800c0c4(iVar3,param_2[1]);
    uVar2 = local_30;
    bVar9 = (param_2[9] & 3U) != 0;
    _GHIDRA_FIELD(local_30, 3, byte) = SUB41(uVar2,3);
    _GHIDRA_FIELD(local_30, 0, uint24_t) = CONCAT12(bVar9,(ushort)(byte)*param_2);
    cVar1 = (char)param_2[2];
    if (cVar1 == '\0') {
      cVar6 = '\0';
    }
    else if (cVar1 == '\x04') {
      cVar6 = '\x01';
    }
    else if (cVar1 == '\x01') {
      if (param_2[7] == 0) {
        cVar6 = '\x02';
      }
      else {
        cVar6 = '\x03';
      }
    }
    _GHIDRA_FIELD(local_2c, 0, ushort) = CONCAT11(cVar6,(undefined1)local_2c);
    FUN_0800c0d4(iVar3,&local_30);
    iVar7 = FUN_0803456c(iVar3,1,&local_28);
    if (iVar7 == 0) {
      FUN_0800bfac(iVar3,1);
      if (cVar6 != '\0') {
        param_2[3] = 0;
        param_2[4] = 0;
        param_2[5] = 0;
        param_2[6] = 0;
        FUN_0800be78(iVar3,param_2 + 3,(char)param_2[2] == '\x04');
      }
      if ((param_2[7] != 0) && (!bVar9)) {
        iVar7 = FUN_0803456c(iVar3,2,&local_28);
        if (iVar7 != 0) {
          param_2[8] = local_28;
          return 7;
        }
        FUN_0800bfac(iVar3,2);
      }
      iVar7 = 0;
    }
    else {
      param_2[8] = local_28;
    }
  }
  else {
    iVar7 = 3;
  }
  return iVar7;
}




/* 0x08032d8c */
undefined4 FUN_08032d8c(param_1, param_2, param_3)
undefined4 param_1; int param_2; int param_3;
{
  undefined4 uVar1;
  undefined4 local_30;
  undefined4 local_2c;
  undefined1 local_28;
  uint local_14;
  undefined4 local_c;
  
  uVar1 = 0;
  if (param_3 == 0) {
    if (param_2 == 1) {
      uVar1 = FUN_080350be(param_1);
    }
  }
  else {
    local_30 = 0xc;
    local_28 = 1;
    local_14 = (uint)(param_2 == 1);
    local_2c = 0;
    local_c = 0;
    uVar1 = sdcc_command(param_1,&local_30);
  }
  return uVar1;
}




/* 0x08032dcc */
void FUN_08032dcc(param_1, param_2, param_3, param_4)
undefined4 * param_1; undefined4 param_2; undefined4 param_3; uint param_4;
{
  char cVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint local_18;
  
  uVar4 = *param_1;
  cVar1 = *(char *)(param_1 + 2);
  local_18 = param_4;
  uVar2 = FUN_08032ad0(uVar4);
  uVar3 = 20000;
  if (false) goto switchD_08032de6_caseD_5;
  uVar3 = 20000;
  switch(param_2) {
  case 0:
    uVar3 = 400;
    *(undefined1 *)((int)param_1 + 0x5f) = 2;
    break;
  case 1:
  case 2:
  case 3:
switchD_08032de6_caseD_1:
    if ((cVar1 == '\x02') || (cVar1 == '\x06')) {
      if (*(char *)((int)param_1 + 0x5f) == '\x04') {
        uVar3 = 52000;
      }
      else if (*(char *)((int)param_1 + 0x5f) == '\x03') {
        uVar3 = 26000;
      }
      break;
    }
    goto LAB_08032e26;
  case 4:
    if ((cVar1 == '\x02') || (cVar1 == '\x06')) {
      *(undefined1 *)((int)param_1 + 0x5f) = 4;
      goto switchD_08032de6_caseD_1;
    }
    if ((cVar1 != '\x01') && (cVar1 != '\x05')) break;
    *(undefined1 *)((int)param_1 + 0x5f) = 1;
LAB_08032e26:
    if ((cVar1 == '\x01') || (cVar1 == '\x05')) {
      if (*(char *)((int)param_1 + 0x5f) == '\x01') {
        uVar3 = 50000;
      }
      else {
        uVar3 = 25000;
      }
    }
    break;
  case 6:
    if (((cVar1 == '\x02') || (cVar1 == '\x06')) && (*(char *)((int)param_1 + 0x5f) == '\x04')) {
      uVar3 = 100000;
    }
  }
switchD_08032de6_caseD_5:
  if (*(char *)(param_1 + 0x23) == '\x01') {
    local_18 = uVar2;
    if (uVar3 < uVar2) {
      local_18 = uVar3;
    }
    FUN_08034488(uVar4,local_18 * 1000);
  }
  else {
    local_18 = uVar3;
    if (uVar2 <= uVar3) {
      local_18 = uVar2;
    }
    FUN_08032a04(uVar4,&local_18,4);
  }
  param_1[0x21] = local_18;
  return;
}




/* 0x08032eac */
int FUN_08032eac(param_1)
int * param_1;
{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined1 local_48;
  undefined4 local_34;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  iVar3 = *param_1;
  iVar2 = FUN_08034e78(param_1,1);
  if (iVar2 != 0) {
    return iVar2;
  }
  *(undefined1 *)((int)param_1 + 9) = 2;
  param_1[0x16] = 1;
  local_48 = 1;
  local_34 = 0;
  local_50 = 0x10;
  uStack_4c = 0x200;
  local_2c = 0;
  iVar2 = sdcc_command(param_1,&local_50);
  if (iVar2 == 0) {
    param_1[9] = 0x200;
    *(uint *)((&DAT_0804e2c8)[*param_1] + 0x2c) =
         *(uint *)((&DAT_0804e2c8)[*param_1] + 0x2c) & 0xfffe000f | 0x2000;
    FUN_0800bda0();
  }
  cVar1 = (char)param_1[2];
  if ((cVar1 == '\x02') || (cVar1 == '\x06')) {
    if (*(byte *)((int)param_1 + 0x5d) < 4) {
      FUN_08032f98(iVar3,0);
    }
    else {
      iVar3 = FUN_08032fd0(param_1);
      iVar2 = 0;
      if (iVar3 != 0) {
        return iVar3;
      }
    }
  }
  else if ((cVar1 == '\x01') || (cVar1 == '\x05')) {
    param_1[0xd] = 1;
    local_28 = 0;
    local_24 = 0;
    iVar2 = FUN_08033be0(param_1,&local_28);
    if (iVar2 != 0) {
      return iVar2;
    }
    if ((char)local_24 == '\x05') {
      iVar2 = FUN_08034fde(param_1);
      if (iVar2 != 0) {
        return iVar2;
      }
    }
    else {
      FUN_0800bcec(iVar3,0);
    }
    iVar2 = FUN_08033c2c(param_1);
    if (iVar2 != 0) {
      return iVar2;
    }
    iVar2 = 0;
    if (_GHIDRA_FIELD(local_28, 1, byte) != '\0') {
      FUN_08034d68(param_1);
    }
  }
  iVar3 = FUN_08034f80(param_1);
  if (iVar3 != 4) {
    iVar2 = 9;
  }
  return iVar2;
}




/* 0x08032f98 */
undefined4 FUN_08032f98(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 uVar2;
  
  if (true) {
    switch(param_2) {
    case 0:
      uVar2 = 0;
      break;
    case 1:
    case 5:
      uVar2 = 1;
      break;
    case 2:
    case 6:
      iVar1 = FUN_0800bd9c();
      if (iVar1 != 1) {
        if (iVar1 != 0) {
          return 1;
        }
        return 0;
      }
      uVar2 = 2;
      break;
    default:
      goto switchD_08032fa0_caseD_3;
    }
    FUN_0800bcec(param_1,uVar2);
    return 1;
  }
switchD_08032fa0_caseD_3:
  return 0;
}




/* 0x08032fd0 */
int FUN_08032fd0(param_1)
int * param_1;
{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined1 auStack_80 [11];
  byte local_75;
  byte local_73;
  byte local_71;
  byte local_70;
  uint local_6c;
  undefined1 local_68;
  undefined1 local_66;
  byte local_5e;
  byte local_55;
  undefined1 local_47;
  int local_44 [7];
  byte local_28;
  
  iVar6 = *param_1;
  bVar1 = false;
  local_28 = 0;
  FUN_08006d14(auStack_80,0x58);
  iVar2 = FUN_08033b0a(param_1,&DAT_00223950);
  if (iVar2 != 0) {
    return iVar2;
  }
  FUN_080332aa(&DAT_00223950,auStack_80);
  if ((char)param_1[2] == '\x06') {
    if (local_6c == 0) {
      return 1;
    }
LAB_0803300c:
    if ((param_1[7] == 0) || (0x400000 < (uint)param_1[7])) {
      param_1[7] = local_6c & 0xfffffe00;
    }
  }
  else if (local_6c != 0) goto LAB_0803300c;
  if (local_71 != 0) {
    param_1[0xb] = (uint)local_71;
  }
  uVar3 = ((uint)local_55 << 0x1a) >> 0x1d;
  if ((uVar3 - 3 < 4) || (7 < uVar3)) {
    iVar2 = 0x14;
  }
  else {
    local_28 = (byte)(((uint)local_55 << 0x1a) >> 0x1d);
    iVar2 = 0;
  }
  if (iVar2 != 0) {
    return iVar2;
  }
  *(byte *)(param_1 + 0x1e) = local_28;
  if ((local_5e & 3) != 0) {
    iVar2 = mmc_switch_cmd6(param_1,0x3b90100);
    if (iVar2 != 0) {
      return iVar2;
    }
    if ((int)((uint)local_5e << 0x1e) < 0) {
      *(undefined1 *)((int)param_1 + 0x5f) = 4;
    }
    else {
      *(undefined1 *)((int)param_1 + 0x5f) = 3;
    }
  }
  FUN_08032dcc(param_1,1);
  if (((int)((uint)local_5e << 0x1d) < 0) &&
     (((char)param_1[0x23] != '\x01' || (*(char *)((int)param_1 + 0x8d) != '\0')))) {
    bVar1 = true;
  }
  iVar2 = FUN_08032af8(iVar6);
  if (iVar2 << 0x1a < 0) {
    local_66 = local_68;
    if (bVar1) {
      iVar2 = 6;
    }
    else {
      iVar2 = 2;
    }
  }
  else if (bVar1) {
    iVar2 = 5;
  }
  else {
    iVar2 = 1;
  }
  *(undefined1 *)(param_1 + 0x18) = local_66;
  iVar4 = mmc_switch_cmd6(param_1,iVar2 << 8 | 0x3b70000);
  if (iVar4 != 0) {
    return iVar4;
  }
  if ((char)param_1[0x23] == '\x01') {
    iVar2 = FUN_080342b8(iVar6,iVar2);
    if (iVar2 != 0) {
      return iVar2;
    }
    if (!bVar1) goto LAB_0803312a;
    FUN_08034300(iVar6);
    uVar5 = 1;
  }
  else {
    FUN_08032f98();
    if (!bVar1) goto LAB_0803312a;
    *(uint *)((&DAT_0804e2c8)[iVar6] + 4) = *(uint *)((&DAT_0804e2c8)[iVar6] + 4) | 0xc000;
    FUN_0800bda0();
    uVar5 = 6;
  }
  FUN_08032dcc(param_1,uVar5);
LAB_0803312a:
  if (*(char *)((int)param_1 + 0x5e) == '\x01') {
    if ((char)param_1[0x17] == '\0') {
      param_1[8] = 0;
      *(undefined1 *)((int)param_1 + 0x5e) = 0;
    }
    else if (((local_73 != 0) && (local_70 != 0)) &&
            (iVar2 = mmc_switch_cmd6(param_1,0x3af0100), iVar2 == 0)) {
      param_1[8] = (uint)local_70 * (uint)local_73 * 0x400;
    }
  }
  param_1[0x1f] = 1;
  if (local_75 == 0) {
    *(undefined1 *)((int)param_1 + 0x61) = 0;
    param_1[0xd] = 1;
  }
  else {
    *(undefined1 *)((int)param_1 + 0x61) = 1;
    param_1[0xd] = 3;
    param_1[0x19] = (uint)local_75 << 7;
    param_1[0x1f] = 7;
  }
  uVar3 = 0;
  do {
    if (local_44[uVar3] != 0) {
      param_1[0xd] = param_1[0xd] + 1;
      param_1[0x1f] = param_1[0x1f] | 0x10 << (uVar3 & 0xff);
      param_1[uVar3 + 0x1a] = param_1[8] * local_44[uVar3];
    }
    uVar3 = uVar3 + 1;
  } while ((int)uVar3 < 4);
  *(undefined1 *)(param_1 + 0x20) = local_47;
  return 0;
}




/* 0x080331e0 */
uint FUN_080331e0(param_1)
int param_1;
{
  uint uVar1;
  undefined4 local_30;
  undefined4 local_2c;
  undefined1 local_28;
  uint local_24;
  undefined4 local_14;
  undefined4 local_c;
  
  local_30 = 3;
  local_28 = 1;
  local_14 = 0;
  local_c = 0;
  if ((*(char *)(param_1 + 8) == '\x02') || (*(char *)(param_1 + 8) == '\x06')) {
    uVar1 = 2;
    local_2c = 0x20000;
    sdcc_command(param_1,&local_30);
  }
  else {
    local_2c = 0;
    sdcc_command(param_1,&local_30);
    uVar1 = local_24 >> 0x10;
  }
  return uVar1;
}




/* 0x0803321e */
void FUN_0803321e(param_1, param_2, param_3)
int param_1; uint * param_2; byte * param_3;
{
  uint uVar1;
  int iVar2;
  
  if (param_3 != (byte *)0x0) {
    uVar1 = *param_2;
    *param_3 = (byte)(uVar1 >> 0x1e);
    if ((*(char *)(param_1 + 8) == '\x01') || (*(char *)(param_1 + 8) == '\x05')) {
      if (uVar1 >> 0x1e != 1) {
        FUN_080334b4(param_1,param_2,param_3);
        return;
      }
      uVar1 = *param_2;
      param_3[2] = 0xe;
      param_3[3] = 0;
      param_3[4] = (byte)uVar1;
      uVar1 = param_2[1];
      param_3[8] = 9;
      *(uint *)(param_3 + 0x10) = (uVar1 << 0x1a) >> 10 | param_2[2] >> 0x10;
      return;
    }
    FUN_080334b4(param_1,param_2,param_3);
    *(byte *)(param_1 + 0x5d) = param_3[1];
    if ((param_3[0x1c] == 0) || (param_3[1] < 3)) {
      *(undefined1 *)(param_1 + 0x5e) = 0;
      return;
    }
    *(undefined1 *)(param_1 + 0x5e) = 1;
    iVar2 = (param_3[0x1a] + 1) * (param_3[0x19] + 1) * ((uint)param_3[0x1b] * 0x200 + 0x200);
    *(int *)(param_1 + 0x20) = (int)(iVar2 + ((uint)(iVar2 >> 0x1f) >> 0x17)) >> 9;
  }
  return;
}




/* 0x080332aa */
undefined4 FUN_080332aa(param_1, param_2)
int param_1; undefined1 * param_2;
{
  byte bVar1;
  ushort uVar2;
  uint3 uVar3;
  
  if (param_2 != (undefined1 *)0x0) {
    *(uint *)(param_2 + 0x3c) = (uint)*(uint3 *)(param_1 + 0x8f);
    *(uint *)(param_2 + 0x40) = (uint)*(uint3 *)(param_1 + 0x92);
    *(uint *)(param_2 + 0x44) = (uint)*(uint3 *)(param_1 + 0x95);
    *(uint *)(param_2 + 0x48) = (uint)*(uint3 *)(param_1 + 0x98);
    param_2[0x39] = *(undefined1 *)(param_1 + 0x9b);
    param_2[0x33] = *(undefined1 *)(param_1 + 0xa0);
    param_2[0x2e] = *(undefined1 *)(param_1 + 0xad);
    param_2[0x2f] = *(undefined1 *)(param_1 + 0xae);
    param_2[0x2d] = *(undefined1 *)(param_1 + 0xaf);
    param_2[0x2b] = *(undefined1 *)(param_1 + 0xb3);
    param_2[0x26] = *(undefined1 *)(param_1 + 0xbd);
    param_2[0x25] = *(undefined1 *)(param_1 + 0xbf);
    param_2[0x24] = *(undefined1 *)(param_1 + 0xc0);
    param_2[0x23] = *(undefined1 *)(param_1 + 0xc2);
    param_2[0x22] = *(undefined1 *)(param_1 + 0xc4);
    param_2[0x21] = *(undefined1 *)(param_1 + 200);
    param_2[0x20] = *(undefined1 *)(param_1 + 0xc9);
    param_2[0x1f] = *(undefined1 *)(param_1 + 0xca);
    param_2[0x1e] = *(undefined1 *)(param_1 + 0xcb);
    param_2[0x1d] = *(undefined1 *)(param_1 + 0xcd);
    param_2[0x1c] = *(undefined1 *)(param_1 + 0xce);
    param_2[0x1b] = *(undefined1 *)(param_1 + 0xcf);
    param_2[0x1a] = *(undefined1 *)(param_1 + 0xd0);
    param_2[0x19] = *(undefined1 *)(param_1 + 0xd1);
    param_2[0x18] = *(undefined1 *)(param_1 + 0xd2);
    bVar1 = *(byte *)(param_1 + 0xd4);
    *(uint *)(param_2 + 0x14) = (uint)bVar1;
    uVar2 = CONCAT11(*(undefined1 *)(param_1 + 0xd5),bVar1);
    *(uint *)(param_2 + 0x14) = (uint)uVar2;
    uVar3 = CONCAT12(*(undefined1 *)(param_1 + 0xd6),uVar2);
    *(uint *)(param_2 + 0x14) = (uint)uVar3;
    *(uint *)(param_2 + 0x14) = CONCAT13(*(undefined1 *)(param_1 + 0xd7),uVar3);
    param_2[0x10] = *(undefined1 *)(param_1 + 0xdd);
    param_2[0xf] = *(undefined1 *)(param_1 + 0xde);
    param_2[0xd] = *(undefined1 *)(param_1 + 0xe0);
    param_2[0xb] = *(undefined1 *)(param_1 + 0xe2);
    *param_2 = *(undefined1 *)(param_1 + 0x1f8);
    return 1;
  }
  return 0;
}




/* 0x080333ba */
undefined4 FUN_080333ba(param_1, param_2)
int * param_1; int param_2;
{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  if ((param_1 == (int *)0x0) || (param_2 == 0)) {
    uVar1 = 0;
  }
  else {
    *(ushort *)(param_2 + 0x3e) = (ushort)(byte)((uint)*param_1 >> 0x18);
    *(byte *)(param_2 + 0x5c) = (byte)((uint)(*param_1 << 0xe) >> 0x1e);
    *(ushort *)(param_2 + 0x40) = (ushort)(byte)((uint)*param_1 >> 8);
    *(char *)(param_2 + 0x42) = (char)*param_1;
    uVar3 = param_1[1];
    iVar2 = 4;
    do {
      iVar4 = param_2 + iVar2;
      iVar2 = iVar2 + -1;
      *(char *)(iVar4 + 0x42) = (char)uVar3;
      uVar3 = uVar3 >> 8;
    } while (0 < iVar2);
    *(char *)(param_2 + 0x47) = (char)((uint)param_1[2] >> 0x18);
    *(undefined1 *)(param_2 + 0x48) = 0;
    *(char *)(param_2 + 0x49) = (char)((uint)param_1[2] >> 0x10);
    *(uint *)(param_2 + 0x4c) = param_1[2] << 0x10 | (uint)param_1[3] >> 0x10;
    uVar1 = 1;
  }
  return uVar1;
}




/* 0x08033424 */
undefined4 FUN_08033424(param_1, param_2)
byte * param_1; byte * param_2;
{
  byte bVar1;
  
  if (param_2 != (byte *)0x0) {
    bVar1 = *param_1;
    *param_2 = bVar1 >> 4;
    param_2[1] = bVar1 & 0xf;
    bVar1 = param_1[1];
    param_2[2] = bVar1 >> 7;
    param_2[3] = (byte)(((uint)bVar1 << 0x19) >> 0x1d);
    param_2[4] = bVar1 & 0xf;
    return 1;
  }
  return 0;
}




/* 0x0803344c */
undefined4 FUN_0803344c(param_1, param_2)
undefined4 * param_1; int param_2;
{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  if ((param_1 != (undefined4 *)0x0) && (param_2 != 0)) {
    *(ushort *)(param_2 + 0x3e) = (ushort)(byte)((uint)*param_1 >> 0x18);
    *(short *)(param_2 + 0x40) = (short)((uint)*param_1 >> 8);
    *(char *)(param_2 + 0x42) = (char)*param_1;
    iVar1 = 4;
    uVar2 = param_1[1];
    do {
      iVar3 = param_2 + iVar1;
      iVar1 = iVar1 + -1;
      *(char *)(iVar3 + 0x42) = (char)uVar2;
      uVar2 = uVar2 >> 8;
    } while (0 < iVar1);
    *(undefined1 *)(param_2 + 0x47) = 0;
    *(char *)(param_2 + 0x49) = (char)((uint)param_1[2] >> 0x18);
    *(uint *)(param_2 + 0x4c) = param_1[2] << 8 | (uint)param_1[3] >> 0x18;
    return 1;
  }
  return 0;
}




/* 0x0803349a */
undefined4 FUN_0803349a(param_1, param_2)
byte * param_1; byte * param_2;
{
  if (param_2 != (byte *)0x0) {
    *param_2 = *param_1 >> 6;
    param_2[8] = param_1[8];
    param_2[10] = param_1[10] >> 4;
    return 1;
  }
  return 0;
}




/* 0x080334b4 */
void FUN_080334b4(param_1, param_2, param_3)
int param_1; int * param_2; int param_3;
{
  int iVar1;
  uint uVar2;
  
  if (param_3 != 0) {
    iVar1 = *param_2;
    if ((*(char *)(param_1 + 8) == '\x02') || (*(char *)(param_1 + 8) == '\x06')) {
      *(byte *)(param_3 + 1) = (byte)((uint)(iVar1 << 2) >> 0x1c);
    }
    *(char *)(param_3 + 2) = (char)((uint)iVar1 >> 0x10);
    *(char *)(param_3 + 3) = (char)((uint)iVar1 >> 8);
    *(char *)(param_3 + 4) = (char)iVar1;
    iVar1 = param_2[1];
    *(byte *)(param_3 + 8) = (byte)((uint)(iVar1 << 0xc) >> 0x1c);
    uVar2 = param_2[2];
    *(uint *)(param_3 + 0x10) = (uint)(iVar1 << 0x16) >> 0x14 | uVar2 >> 0x1e;
    *(byte *)(param_3 + 0x18) = (byte)((uVar2 << 0xe) >> 0x1d);
    if (((*(char *)(param_1 + 8) == '\x02') || (*(char *)(param_1 + 8) == '\x06')) &&
       (2 < *(byte *)(param_3 + 1))) {
      *(byte *)(param_3 + 0x19) = (byte)((uVar2 << 0x11) >> 0x1b);
      *(byte *)(param_3 + 0x1a) = (byte)((uVar2 << 0x16) >> 0x1b);
      *(byte *)(param_3 + 0x1b) = (byte)uVar2 & 0x1f;
    }
    *(byte *)(param_3 + 0x1c) = (byte)((uint)param_2[3] >> 0x1f);
  }
  return;
}




/* 0x0803351c */
undefined4 FUN_0803351c(param_1, param_2)
byte * param_1; short * param_2;
{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  if (param_2 != (short *)0x0) {
    bVar1 = *param_1;
    *param_2 = (ushort)bVar1 << 8;
    *param_2 = CONCAT11(bVar1,param_1[1]);
    uVar5 = 2;
    iVar4 = 5;
    do {
      bVar1 = param_1[uVar5];
      uVar5 = uVar5 + 1 & 0xff;
      param_2[iVar4 + 1] = (ushort)bVar1 << 8;
      iVar3 = (int)(char)((char)iVar4 + -1);
      param_2[iVar4 + 1] = CONCAT11(bVar1,param_1[uVar5]);
      uVar5 = uVar5 + 1 & 0xff;
      iVar4 = iVar3;
    } while (-1 < iVar3);
    uVar5 = 0xe;
    iVar4 = 5;
    do {
      bVar1 = param_1[uVar5];
      cVar2 = (char)iVar4;
      *(byte *)((int)param_2 + iVar4 + 0xe) = bVar1 >> 4;
      iVar4 = (int)(char)(cVar2 + -2);
      *(byte *)((int)param_2 + (char)(cVar2 + -1) + 0xe) = bVar1 & 0xf;
      uVar5 = uVar5 + 1 & 0xff;
    } while (0 < iVar4);
    uVar5 = 0x12;
    *(byte *)(param_2 + 10) = param_1[0x11];
    iVar4 = 5;
    do {
      bVar1 = param_1[uVar5];
      param_2[iVar4 + 0xb] = (ushort)bVar1 << 8;
      uVar5 = uVar5 + 1 & 0xff;
      param_2[iVar4 + 0xb] = CONCAT11(bVar1,param_1[uVar5]);
      iVar4 = (int)(char)((char)iVar4 + -1);
      uVar5 = uVar5 + 1 & 0xff;
    } while (-1 < iVar4);
    return 1;
  }
  return 0;
}




/* 0x080335b4 */
undefined4 FUN_080335b4(param_1)
int param_1;
{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)(param_1 + 0x90);
  iVar2 = *piVar1;
  if (*(char *)(param_1 + 9) != '\0') {
    if ((char)piVar1[1] != '\0') {
      *(uint *)(&DAT_0804e2c8)[iVar2] = *(uint *)(&DAT_0804e2c8)[iVar2] & 0xfffffffe;
      FUN_0800bda0();
      FUN_08032b0c(iVar2,0);
      *(undefined1 *)(piVar1 + 1) = 0;
    }
    *(undefined1 *)(param_1 + 8) = 0;
    *(undefined1 *)(param_1 + 9) = 0;
    *(undefined4 *)(param_1 + 0x84) = 0;
  }
  return 0;
}




/* 0x080335fc */
void FUN_080335fc(param_1)
undefined4 * param_1;
{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)*param_1;
  if (piVar1 != (int *)0x0) {
    if ((char)((int *)*piVar1)[2] == '\0') {
      iVar2 = *(int *)*piVar1;
      for (piVar1 = &DAT_08059efc; piVar1 < (int *)0x805a071; piVar1 = piVar1 + 3) {
        if (((int *)*piVar1 != (int *)0x0) && (*(int *)*piVar1 == iVar2)) {
          FUN_08032b7c(piVar1);
        }
        if (DAT_0804e2a8 == 0x20) break;
      }
    }
    else {
      FUN_08032b7c(piVar1);
    }
    *param_1 = 0;
  }
  return;
}




/* 0x08033654 */
void FUN_08033654()
{
  return;
}




/* 0x08033656 */
int mmc_write_dispatch(param_1, param_2, param_3, param_4)
undefined4 * param_1; int * param_2; undefined4 param_3; uint param_4;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined4 uVar9;
  uint3 local_60;
  undefined1 uStack_5d;
  uint local_5c;
  undefined1 local_58;
  uint local_44;
  undefined4 local_40;
  undefined4 local_3c;
  uint local_38;
  undefined4 *puStack_34;
  int *piStack_30;
  undefined4 local_2c;
  uint uStack_28;
  
  puStack_34 = param_1;
  piStack_30 = param_2;
  local_2c = param_3;
  uStack_28 = param_4;
  if (*(char *)(param_1 + 0x23) != '\x01') {
    uVar4 = param_2[9];
    iVar5 = param_1[0x24];
    iVar8 = 0;
    local_38 = (int)(uVar4 << 0x1e) >> 0x1f;
    iVar6 = 0;
    iVar1 = FUN_08035040(param_1,local_38 + 1,param_4);
    if (iVar1 == 0) {
      param_1[4] = 0x14;
      return 0x14;
    }
    if (param_1[0x16] != 0) {
      param_4 = param_1[9];
    }
    local_40 = param_4 & 0xffff;
    local_3c = 0x100;
    if (*(int *)(iVar5 + 0xa4) != 0) {
      _GHIDRA_FIELD(local_40, 0, uint24_t) = CONCAT12(1,(short)param_4);
      local_40 = (uint)(uint3)local_40;
    }
    if ((int)(uVar4 << 0x1e) < 0) {
      local_3c = 0x101;
      FUN_0800bbb4(*param_1,&local_40);
    }
    if ((int)(uVar4 << 0x1d) < 0) {
      iVar2 = FUN_08034eaa();
    }
    else {
      iVar2 = sdcc_command(param_1,param_2);
    }
    if (((uint)param_2[3] >> 0x1a & 1) != 0) {
      param_1[4] = 0x1d;
      return 0x1d;
    }
    if (iVar2 == 0) {
      if (*(int *)(iVar5 + 0xa4) != 0) {
        if ((int)(uVar4 << 0x1e) < 0) {
          uVar3 = 1;
        }
        else {
          uVar3 = 2;
        }
        iVar6 = (**(code **)(iVar5 + 0xac))(iVar5,local_2c,iVar1,uVar3);
        if (iVar6 == 0) {
          if ((uVar4 & 1) != 0) {
            FUN_0800bbb4(*param_1,&local_40);
          }
          iVar8 = FUN_080350ee(param_1);
        }
        if ((*(int *)(iVar5 + 0xa4) != 0) && (iVar6 == 0)) goto LAB_0803376e;
      }
      if ((int)(uVar4 << 0x1e) < 0) {
        iVar8 = FUN_08034c14(iVar5,local_2c,iVar1);
      }
      else {
        _GHIDRA_FIELD(local_40, 0, uint24_t) = (uint3)(ushort)local_40;
        FUN_0800bbb4(*param_1,&local_40);
        iVar8 = FUN_08035188(iVar5,local_2c,iVar1);
      }
      local_40 = 0;
      local_3c = 0;
      FUN_0800bbb4(*param_1,&local_40);
    }
LAB_0803376e:
    if (((int)(uVar4 << 0x1d) < 0) || ((*param_2 != 0x12 && (*param_2 != 0x19)))) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
    iVar1 = FUN_08032d8c(param_1,local_38 + 1,uVar3);
    if ((*(int *)(iVar5 + 0xa4) != 0) && (iVar6 == 0)) {
      if ((int)(uVar4 << 0x1e) < 0) {
        uVar3 = 1;
      }
      else {
        uVar3 = 2;
      }
      iVar8 = (**(code **)(iVar5 + 0xb0))(iVar5,uVar3);
    }
    if (iVar8 == 0) {
      iVar8 = iVar1;
    }
    param_1[4] = iVar8;
    return iVar8;
  }
  local_38 = 0;
  uVar3 = *param_1;
  if (param_1[0x16] == 0) {
    uVar7 = 1;
    uVar4 = param_4;
  }
  else {
    uVar4 = param_1[9];
    uVar7 = param_4;
  }
  iVar8 = uVar4 * uVar7;
  local_38 = FUN_0800be44(uVar3);
  if (((local_38 & 0x7ff003f) != 0) && (FUN_0800bfac(uVar3), (local_38 & 0x7ff0000) != 0)) {
    FUN_0800c154(uVar3,6);
  }
  if (*(char *)((int)param_1 + 0x8e) == '\x01') {
    FUN_080343c0(uVar3,local_2c,iVar8);
  }
  FUN_0800c018(uVar3,uVar4 & 0xffff);
  FUN_0800c008(uVar3,uVar7 & 0xffff);
  _local_60 = 0;
  if (param_2[9] << 0x1e < 0) {
    _local_60 = 0x100;
  }
  if (1 < (uVar7 & 0xffff)) {
    _local_60 = CONCAT31(stack0xffffffa1,1);
  }
  local_60 = (uint3)(ushort)local_60;
  _local_60 = CONCAT13(1,local_60);
  local_5c = (uint)*(byte *)((int)param_1 + 0x8e);
  FUN_0800c12c(*param_1,&local_60);
  if (param_2[9] << 0x1d < 0) {
    iVar1 = FUN_08034eaa();
  }
  else {
    iVar1 = sdcc_command(param_1,param_2);
  }
  if (iVar1 == 0) {
    uVar9 = 2;
    if (*(char *)((int)param_1 + 0x8e) == '\0') {
      iVar1 = FUN_08034314(param_1,param_2,local_2c,iVar8);
      if (iVar1 != 0) goto LAB_080338ba;
    }
    else {
      uVar9 = 0x2000002;
    }
    iVar1 = FUN_0803456c(uVar3,uVar9,&local_38);
    if (iVar1 == 0) {
      iVar1 = 0;
      if ((((int)(local_38 << 0x1e) < 0) && (FUN_0800bfac(uVar3,2), -1 < param_2[9] << 0x1d)) &&
         (1 < uVar7)) {
        _local_60 = 0xc;
        local_58 = 1;
        local_44 = param_2[9] & 1;
        local_5c = 0;
        local_3c = 0;
        iVar1 = sdcc_command(param_1,&local_60);
      }
      FUN_080329f8(4,0);
      if ((param_2[9] << 0x1e < 0) && (*(char *)((int)param_1 + 0x8e) == '\x01')) {
        FUN_080329f8(1,local_2c,iVar8);
        FUN_080329f8(4,0);
      }
      FUN_0800c154(uVar3,6);
      return iVar1;
    }
    param_2[8] = local_38;
  }
LAB_080338ba:
  FUN_0800be44(uVar3);
  return iVar1;
}




/* 0x08033aac */
int FUN_08033aac(param_1)
int param_1;
{
  int iVar1;
  int iVar2;
  undefined4 local_38;
  int local_34;
  undefined1 local_30;
  undefined1 auStack_2c [16];
  undefined4 local_1c;
  undefined4 local_14;
  
  local_38 = 10;
  local_34 = (uint)*(ushort *)(param_1 + 10) << 0x10;
  local_30 = 4;
  local_1c = 0;
  local_14 = 0;
  iVar1 = sdcc_command(param_1,&local_38);
  if ((iVar1 == 0) &&
     (((*(char *)(param_1 + 8) != '\x02' && (*(char *)(param_1 + 8) != '\x06')) ||
      (iVar2 = FUN_080333ba(auStack_2c,param_1), iVar2 == 0)))) {
    iVar1 = 0x14;
  }
  return iVar1;
}




/* 0x08033af2 */
undefined4 FUN_08033af2(param_1)
undefined2 * param_1;
{
  if (param_1 != (undefined2 *)0x0) {
    *param_1 = 3;
    param_1[1] = 0x200;
    *(undefined4 *)(param_1 + 2) = 0x80;
    return 0;
  }
  return 0x14;
}




/* 0x08033b0a */
undefined4 FUN_08033b0a(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  undefined4 local_30;
  undefined4 local_2c;
  undefined1 local_28;
  undefined4 local_14;
  undefined4 local_c;
  
  local_30 = 8;
  local_28 = 1;
  local_2c = 0;
  local_14 = 0;
  local_c = 2;
  mmc_write_dispatch(param_1,&local_30,param_2,1);
  return 0;
}




/* 0x08033b30 */
int FUN_08033b30(param_1)
int param_1;
{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined1 uVar4;
  char local_68 [4];
  char local_64;
  sbyte local_60;
  int local_58;
  undefined1 local_50;
  undefined4 local_40;
  int local_3c;
  undefined1 local_38;
  undefined1 auStack_34 [16];
  undefined4 local_24;
  undefined4 local_1c;
  
  iVar2 = FUN_08034f80();
  iVar3 = 9;
  if (iVar2 == 3) {
    local_40 = 9;
    local_38 = 4;
    uVar4 = 0;
    local_24 = 0;
    local_1c = 0;
    local_3c = (uint)*(ushort *)(param_1 + 10) << 0x10;
    iVar3 = sdcc_command(param_1,&local_40);
    if (iVar3 == 0) {
      FUN_08006d14(local_68,0x28);
      FUN_0803321e(param_1,auStack_34,local_68);
      cVar1 = *(char *)(param_1 + 8);
      if ((cVar1 == '\x01') || (cVar1 == '\x05')) {
        if (local_68[0] == '\x01') {
          *(int *)(param_1 + 0x24) = 1 << local_60;
          *(uint *)(param_1 + 0x1c) = (local_58 + 1) * ((uint)((1 << local_60) << 10) >> 9);
        }
        else {
          FUN_08033d0a(param_1,local_60,local_50,local_58);
        }
      }
      else {
        uVar4 = 3;
        if (cVar1 != '\x06') {
          FUN_08033d0a(param_1,local_60,local_50,local_58);
        }
        if (local_64 != '2') {
          *(undefined1 *)(param_1 + 0x5f) = 2;
          return 0;
        }
      }
      *(undefined1 *)(param_1 + 0x5f) = uVar4;
    }
  }
  return iVar3;
}




/* 0x08033be0 */
int FUN_08033be0(param_1, param_2)
int param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 local_40;
  undefined4 local_3c;
  undefined1 local_38;
  undefined4 local_24;
  undefined4 local_1c;
  
  FUN_08006cd0(&DAT_0805a368,8);
  local_40 = 0x33;
  local_3c = 0;
  local_38 = 1;
  local_1c = 6;
  local_24 = 0;
  *(undefined4 *)(param_1 + 0x58) = 0;
  iVar1 = mmc_write_dispatch(param_1,&local_40,&DAT_0805a368,8);
  *(undefined4 *)(param_1 + 0x58) = 1;
  if (iVar1 == 0) {
    FUN_08033424(&DAT_0805a368,param_2);
  }
  return iVar1;
}




/* 0x08033c2c */
undefined4 FUN_08033c2c(param_1)
int param_1;
{
  int iVar1;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  iVar1 = FUN_08033c54(param_1,&local_18);
  if (iVar1 == 0) {
    *(undefined1 *)(param_1 + 0x60) = (undefined1)local_10;
  }
  return 0;
}




/* 0x08033c54 */
int FUN_08033c54(param_1, param_2)
int param_1; undefined4 param_2;
{
  int iVar1;
  int extraout_r3;
  undefined4 local_38;
  undefined4 local_34;
  undefined1 local_30;
  undefined4 local_1c;
  undefined4 local_14;
  
  FUN_08006cd0(&DAT_0805a368,0x40);
  local_38 = 0xd;
  local_34 = 0;
  local_30 = 1;
  local_14 = 6;
  local_1c = 0;
  *(undefined4 *)(param_1 + 0x58) = 0;
  iVar1 = mmc_write_dispatch(param_1,&local_38,&DAT_0805a368,0x40);
  *(undefined4 *)(param_1 + 0x58) = 1;
  if (iVar1 == 0) {
    FUN_0803349a(&DAT_0805a368,param_2);
    iVar1 = extraout_r3;
  }
  return iVar1;
}




/* 0x08033ca0 */
int FUN_08033ca0(param_1)
uint param_1;
{
  if (2 < param_1) {
    return 0;
  }
  return param_1 * 0xbc + 0x8059cc8;
}




/* 0x08033cbc */
undefined4 FUN_08033cbc(param_1, param_2, param_3)
undefined4 param_1; undefined1 * param_2; undefined1 * param_3;
{
  uint uVar1;
  
  uVar1 = FUN_08032af8();
  if ((uVar1 & 1) == 0) {
    if ((int)(uVar1 << 0x1e) < 0) {
      *param_2 = 2;
    }
    else {
      *param_2 = 0;
    }
  }
  else {
    *param_2 = 1;
  }
  uVar1 = FUN_08032ae4(param_1);
  if ((uVar1 & 1) == 0) {
    if ((int)(uVar1 << 0x1e) < 0) {
      *param_3 = 2;
    }
    else {
      *param_3 = 0;
    }
  }
  else {
    *param_3 = 1;
  }
  return 0;
}




/* 0x08033d0a */
void FUN_08033d0a(param_1, param_2, param_3, param_4)
int param_1; uint param_2; int param_3; int param_4;
{
  uint uVar1;
  
  uVar1 = 1 << (param_2 & 0xff);
  *(uint *)(param_1 + 0x24) = uVar1;
  *(uint *)(param_1 + 0x1c) = (uVar1 >> 9) * (1 << (param_3 + 2U & 0xff)) * (param_4 + 1);
  return;
}




/* 0x08033d28 */
undefined4 FUN_08033d28(param_1)
int * param_1;
{
  int *local_10;
  
  if ((param_1 != (int *)0x0) && (*param_1 != 0)) {
    local_10 = param_1;
    FUN_080335fc(&local_10);
    return 0;
  }
  return 0x14;
}




/* 0x08033d44 */
int FUN_08033d44(param_1, param_2, param_3)
undefined4 * param_1; int param_2; int param_3;
{
  int iVar1;
  uint *puVar2;
  undefined4 local_40;
  int local_3c;
  undefined1 local_38;
  uint local_34;
  undefined4 local_24;
  undefined4 local_1c;
  
  if (((param_1 == (undefined4 *)0x0) || (puVar2 = (uint *)*param_1, puVar2 == (uint *)0x0)) ||
     (2 < *puVar2)) {
    iVar1 = 0x14;
  }
  else if (((char)puVar2[2] == '\x06') || ((char)puVar2[2] == '\x02')) {
    iVar1 = mmc_pre_write_check();
    if (iVar1 == 0) {
      local_38 = 1;
      local_40 = 0x23;
      local_24 = 0;
      local_1c = 0;
      local_3c = param_2;
      iVar1 = sdcc_command(puVar2,&local_40);
      if (iVar1 == 0) {
        if ((char)puVar2[2] == '\x06') {
          local_3c = param_2 + param_3 + -1;
        }
        else {
          local_3c = param_2 + param_3 * 0x200 + -0x200;
        }
        local_40 = 0x24;
        iVar1 = sdcc_command(puVar2,&local_40);
        if (iVar1 == 0) {
          local_40 = 0x26;
          local_3c = 0;
          local_24 = 1;
          local_1c = 0;
          iVar1 = sdcc_command(puVar2,&local_40);
          if (iVar1 == 0) {
            if ((local_34 & 0xfdff8000) == 0) {
              return 0;
            }
          }
          else {
            if (iVar1 != 7) {
              return iVar1;
            }
            if ((local_34 & 0xfdff8000) == 0) {
              do {
                iVar1 = FUN_08035134(puVar2);
              } while (iVar1 == 7);
              return iVar1;
            }
          }
          iVar1 = 0xf;
        }
      }
    }
  }
  else {
    iVar1 = 0x16;
  }
  return iVar1;
}




/* 0x08033dfc */
undefined4 FUN_08033dfc(param_1)
int * param_1;
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 local_50;
  undefined4 local_4c;
  uint local_48;
  int local_44;
  undefined1 local_40;
  uint local_3c;
  undefined4 local_34;
  undefined4 local_2c;
  undefined4 local_24;
  
  uVar2 = *(uint *)*param_1;
  if (2 < uVar2) {
    return 0;
  }
  *(uint *)(&DAT_0804e2c8)[uVar2] = *(uint *)(&DAT_0804e2c8)[uVar2] | 1;
  FUN_0800bda0();
  if (*(char *)(*param_1 + 0x8c) == '\0') {
    *(uint *)((&DAT_0804e2c8)[uVar2] + 4) = *(uint *)((&DAT_0804e2c8)[uVar2] + 4) | 0x100;
    FUN_0800bda0();
    FUN_0800bccc(uVar2,0);
    thunk_FUN_080199b4(1000);
    FUN_0800bccc(uVar2,1);
    thunk_FUN_080199b4(1000);
    *(uint *)((&DAT_0804e2c8)[uVar2] + 4) =
         *(uint *)((&DAT_0804e2c8)[uVar2] + 4) & 0xffff3fff | 0x8000;
    FUN_0800bda0();
  }
  else {
    FUN_0800bf88(uVar2,0);
    thunk_FUN_080199b4(1000);
    FUN_0800bf88(uVar2,1);
  }
  FUN_08032dcc(*param_1,0);
  uVar2 = FUN_08032af8(uVar2);
  if ((uVar2 & 1) != 0) {
    iVar4 = *param_1;
    local_40 = 0;
    local_48 = 0;
    local_44 = 0;
    local_2c = 0;
    local_24 = 0;
    sdcc_command(iVar4,&local_48);
    uVar2 = 0;
    while( true ) {
      local_40 = 1;
      local_2c = 0;
      local_48 = 1;
      local_44 = 0x40ff8000;
      local_24 = 0;
      iVar1 = sdcc_command(iVar4,&local_48);
      if (iVar1 != 0) {
        return 0;
      }
      if ((int)local_3c < 0) break;
      thunk_FUN_080199b4(50000);
      uVar2 = uVar2 + 1;
      if (0x13 < uVar2) {
        return 0;
      }
    }
    if (((local_3c >> 0x1e & 1) != 0) && ((local_3c >> 0x1d & 1) == 0)) {
      return 6;
    }
    return 2;
  }
  iVar4 = *param_1;
  uVar3 = 0xff8000;
  local_48 = local_48 & 0xffffff00;
  local_50 = 0;
  local_4c = 0;
  local_34 = 0;
  local_2c = 0;
  sdcc_command(iVar4,&local_50);
  uVar2 = 0;
  do {
    local_48 = CONCAT31(_GHIDRA_FIELD(local_48, 1, uint24_t),1);
    local_34 = 0;
    local_50 = 8;
    local_4c = 0x1aa;
    local_2c = 0;
    iVar1 = sdcc_command(iVar4,&local_50);
    if (iVar1 == 0) {
      if (local_44 != 0x1aa) {
        return 0;
      }
      uVar3 = 0x40ff8000;
      break;
    }
    thunk_FUN_080199b4(1000);
    uVar2 = uVar2 + 1;
  } while (uVar2 < 3);
  uVar2 = 0;
  do {
    _GHIDRA_FIELD(local_48, 0, byte) = 1;
    local_50 = 0x37;
    local_4c = 0;
    local_34 = 0;
    local_2c = 0;
    iVar1 = sdcc_command(iVar4,&local_50);
    if (iVar1 != 0) {
      return 0;
    }
    local_48 = CONCAT31(_GHIDRA_FIELD(local_48, 1, uint24_t),1);
    local_50 = 0x29;
    local_34 = 0;
    local_2c = 0;
    local_4c = uVar3;
    iVar1 = sdcc_command(iVar4,&local_50);
    if (iVar1 != 0) {
      return 0;
    }
    if (local_44 < 0) {
      if (local_44 << 1 < 0) {
        return 5;
      }
      return 1;
    }
    thunk_FUN_080199b4(50000);
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x14);
  return 0;
}




/* 0x08033eb4 */
undefined4 FUN_08033eb4(param_1)
undefined4 * param_1;
{
  int iVar1;
  uint *puVar2;
  
  if ((((param_1 != (undefined4 *)0x0) && (puVar2 = (uint *)*param_1, puVar2 != (uint *)0x0)) &&
      (*puVar2 < 3)) && ((*(char *)(puVar2[0x24] + 0xa0) == '\0' && ((char)puVar2[2] != '\0')))) {
    iVar1 = FUN_08034f80(puVar2);
    if (iVar1 != 9) {
      return 1;
    }
    *(undefined1 *)(puVar2 + 2) = 0;
  }
  return 0;
}




/* 0x08033ee8 */
undefined4 FUN_08033ee8(param_1, param_2)
undefined4 * param_1; char * param_2;
{
  char cVar1;
  uint uVar2;
  uint *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 local_28;
  undefined4 local_24;
  
  uVar4 = 0;
  local_28 = 0;
  local_24 = 0;
  if ((((param_1 == (undefined4 *)0x0) || (puVar3 = (uint *)*param_1, puVar3 == (uint *)0x0)) ||
      (2 < *puVar3)) || (param_2 == (char *)0x0)) {
    uVar4 = 0x14;
  }
  else {
    FUN_08006d14(param_2,0x40);
    iVar5 = param_1[1];
    if (iVar5 == -1) {
      iVar5 = 0;
    }
    if ((char)puVar3[2] == '\0') {
      uVar4 = 0x15;
    }
    else {
      *param_2 = (char)puVar3[2];
      *(uint *)(param_2 + 0xc) = puVar3[9];
      uVar2 = FUN_08032af8(*(undefined4 *)*param_1);
      if ((uVar2 & 1) == 0) {
        param_2[0x18] = '\0';
      }
      else {
        param_2[0x18] = '\x01';
      }
      if (((char)puVar3[2] == '\x02') || ((char)puVar3[2] == '\x06')) {
        uVar4 = FUN_080348e0(param_1,&local_28,&local_24);
        *(undefined4 *)(param_2 + 4) = local_28;
        param_2[0x10] = (char)puVar3[0x18];
        *(uint *)(param_2 + 0x14) = puVar3[0xb];
        cVar1 = FUN_08034966(param_1);
        param_2[0x24] = cVar1;
        *(uint *)(param_2 + 8) = puVar3[8];
      }
      else {
        if (iVar5 == 0) {
          *(uint *)(param_2 + 4) = puVar3[7];
        }
        else {
          uVar4 = 0x16;
          param_2[4] = '\0';
          param_2[5] = '\0';
          param_2[6] = '\0';
          param_2[7] = '\0';
        }
        param_2[0x10] = (char)puVar3[0x18];
        param_2[0x14] = '\0';
        param_2[0x15] = '\0';
        param_2[0x16] = '\0';
        param_2[0x17] = '\0';
        param_2[0x24] = '\0';
      }
      *(undefined4 *)(param_2 + 0x20) = local_24;
      *(uint *)(param_2 + 0x1c) = puVar3[0xd];
      *(undefined2 *)(param_2 + 0x26) = *(undefined2 *)((int)puVar3 + 0x3e);
      *(short *)(param_2 + 0x28) = (short)puVar3[0x10];
      FUN_08006a30(param_2 + 0x2a,(int)puVar3 + 0x42,7);
      param_2[0x31] = *(char *)((int)puVar3 + 0x49);
      *(uint *)(param_2 + 0x34) = puVar3[0x13];
      uVar2 = puVar3[0x15];
      *(uint *)(param_2 + 0x38) = puVar3[0x14];
      *(uint *)(param_2 + 0x3c) = uVar2;
    }
    FUN_08033654(param_1,param_2);
  }
  return uVar4;
}




/* 0x08033fe0 */
int FUN_08033fe0(param_1, param_2)
int param_1; undefined4 param_2;
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_20;
  
  local_20 = 0;
  if (param_1 < 3) {
    if ((false) && (iVar2 = FUN_080348b8(param_1), iVar2 == 1)) {
      iVar2 = FUN_080340e4(param_2);
      return iVar2;
    }
    if (true) {
      iVar2 = FUN_08034704(param_1);
    }
    else {
      iVar2 = FUN_0803460c();
    }
    if (iVar2 == 0) {
      return 0;
    }
    iVar2 = FUN_08033ca0(param_1);
    if (iVar2 != 0) {
      iVar4 = iVar2 + 0xc;
      local_20 = FUN_08034cb4(param_1,param_2);
      if (local_20 == 0) {
        iVar2 = FUN_08034888(iVar4);
        if (iVar2 != 0) {
          return local_20;
        }
        FUN_080335b4(iVar4);
        return local_20;
      }
      cVar1 = *(char *)(iVar2 + 0x14);
      if (cVar1 != '\x04') {
        if (cVar1 == '\x01') {
          return local_20;
        }
        if (cVar1 == '\x05') {
          return local_20;
        }
        if (cVar1 == '\x02') {
          return local_20;
        }
        if (cVar1 == '\x06') {
          return local_20;
        }
        cVar1 = FUN_08033dfc(local_20);
        *(char *)(iVar2 + 0x14) = cVar1;
        *(char *)(iVar2 + 0x24) = cVar1;
        if (cVar1 != '\0') {
          if (cVar1 == '\x04') goto LAB_08034086;
          iVar3 = FUN_080345b8(iVar4);
          if (iVar3 == 0) {
            if (*(char *)(iVar2 + 0x98) == '\0') {
              *(uint *)((&DAT_0804e2c8)[param_1] + 4) =
                   *(uint *)((&DAT_0804e2c8)[param_1] + 4) | 0x1000;
              FUN_0800bda0();
            }
            iVar3 = FUN_08033b30(iVar4);
            if (iVar3 == 0) {
              FUN_08032dcc(iVar4,1);
              iVar4 = FUN_08032eac(iVar4);
              if (iVar4 == 0) {
                *(undefined1 *)(iVar2 + 0x15) = 2;
                *(undefined1 *)(iVar2 + 0xa0) = 0;
                return local_20;
              }
              *(int *)(iVar2 + 0x1c) = iVar4;
              *(undefined1 *)(iVar2 + 0x14) = 0;
              goto LAB_080340c6;
            }
          }
          *(int *)(iVar2 + 0x1c) = iVar3;
        }
LAB_080340c6:
        FUN_08033d28(local_20);
        return 0;
      }
LAB_08034086:
      FUN_080335fc(&local_20);
      return local_20;
    }
  }
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x080340e4 */
int FUN_080340e4(param_1)
undefined4 param_1;
{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  uVar2 = DAT_0804d65c;
  iVar3 = FUN_08033ca0(DAT_0804d65c);
  if (iVar3 == 0) {
    return 0;
  }
  iVar5 = iVar3 + 0xc;
  if ((uVar2 < 3) && (iVar4 = FUN_08034b1c(uVar2), iVar4 != 0)) {
    iVar4 = FUN_08034cb4(uVar2,param_1);
    if (iVar4 == 0) {
      iVar3 = FUN_08034888(iVar5);
      if (iVar3 == 0) {
        FUN_080335b4(iVar5);
      }
    }
    else {
      cVar1 = *(char *)(iVar3 + 0x14);
      if (cVar1 == '\x01') {
        return iVar4;
      }
      if (cVar1 == '\x05') {
        return iVar4;
      }
      if (cVar1 == '\x02') {
        return iVar4;
      }
      if (cVar1 == '\x06') {
        return iVar4;
      }
      *(undefined1 *)(iVar3 + 0x14) = DAT_0804d660;
      *(undefined2 *)(iVar3 + 0x16) = DAT_0804d662;
      *(char *)(iVar3 + 0x24) = *(char *)(iVar3 + 0x14);
      if (*(char *)(iVar3 + 0x14) != '\0') {
        iVar5 = FUN_08034aa0(iVar5);
        if (iVar5 == 0) {
          *(undefined4 *)(iVar3 + 0x10) = 0xffffffff;
          return iVar4;
        }
        *(int *)(iVar3 + 0x1c) = iVar5;
      }
      FUN_08033d28(iVar4);
    }
  }
  _DAT_0804d660 = 0;
  DAT_0804d65c = 0;
  return 0;
}




/* 0x08034170 */
int FUN_08034170(param_1, param_2, param_3, param_4)
undefined4 * param_1; int param_2; undefined4 param_3; int param_4;
{
  char cVar1;
  int iVar2;
  uint *puVar3;
  undefined4 local_40;
  int local_3c;
  undefined1 local_38;
  undefined4 local_24;
  undefined4 local_1c;
  
  if (((param_1 == (undefined4 *)0x0) || (puVar3 = (uint *)*param_1, puVar3 == (uint *)0x0)) ||
     (2 < *puVar3)) {
    iVar2 = 0x14;
  }
  else if (*(char *)(puVar3[0x24] + 0xa0) == '\0') {
    cVar1 = (char)puVar3[2];
    if (cVar1 == '\0') {
      iVar2 = 0x15;
    }
    else if (((cVar1 == '\x01') || (cVar1 == '\x05')) || ((cVar1 == '\x02' || (cVar1 == '\x06')))) {
      iVar2 = mmc_pre_write_check();
      if (iVar2 == 0) {
        if (param_4 == 1) {
          local_40 = 0x11;
        }
        else {
          local_40 = 0x12;
        }
        local_38 = 1;
        local_24 = 0;
        local_3c = param_2;
        if (((char)puVar3[2] != '\x05') && ((char)puVar3[2] != '\x06')) {
          local_3c = param_2 * puVar3[9];
        }
        local_1c = 2;
        iVar2 = mmc_write_dispatch(puVar3,&local_40,param_3,param_4);
      }
    }
    else {
      iVar2 = 0x10;
    }
  }
  else {
    iVar2 = 0x1b;
  }
  return iVar2;
}




/* 0x08034202 */
int FUN_08034202(param_1)
int * param_1;
{
  int iVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  
  if (((param_1 == (int *)0x0) || (puVar2 = (uint *)*param_1, puVar2 == (uint *)0x0)) ||
     (2 < *puVar2)) {
    return 0x14;
  }
  if (((char)puVar2[2] != '\x02') && ((char)puVar2[2] != '\x06')) {
    return 0x16;
  }
  iVar3 = *param_1;
  uVar4 = param_1[1];
  if (uVar4 == 0xffffffff) {
    uVar4 = 0;
  }
  if (*(uint *)(iVar3 + 0x34) <= uVar4) {
    return 0x14;
  }
  iVar1 = FUN_08034966();
  if (iVar1 == 1) {
    iVar1 = 0;
  }
  else {
    if ((*(int *)(iVar3 + 4) != 0) &&
       (iVar1 = mmc_switch_cmd6(iVar3,(uint)*(byte *)(iVar3 + 0x78) << 0xb | 0x3b30000), iVar1 != 0)) {
      return iVar1;
    }
    if (uVar4 == 0) {
      uVar4 = 7;
    }
    iVar1 = mmc_switch_cmd6(iVar3,(*(uint *)(iVar3 + 4) | uVar4 << 3) << 8 | 0x3b30000);
    if (iVar1 == 0) {
      *(char *)(iVar3 + 0x78) = (char)uVar4;
      return 0;
    }
  }
  return iVar1;
}




/* 0x08034224 */
undefined4 FUN_08034224()
{
  return 0x16;
}




/* 0x08034228 */
int mmc_write_with_wp_check(param_1, param_2, param_3, param_4)
undefined4 * param_1; int param_2; undefined4 param_3; int param_4;
{
  char cVar1;
  int iVar2;
  uint *puVar3;
  undefined4 local_40;
  int local_3c;
  undefined1 local_38;
  undefined4 local_24;
  undefined4 local_1c;
  
  if (((param_1 == (undefined4 *)0x0) || (puVar3 = (uint *)*param_1, puVar3 == (uint *)0x0)) ||
     (2 < *puVar3)) {
    iVar2 = 0x14;
  }
  else if (*(char *)(puVar3[0x24] + 0xa0) == '\0') {
    cVar1 = (char)puVar3[2];
    if (cVar1 == '\0') {
      iVar2 = 0x15;
    }
    else if (((cVar1 == '\x01') || (cVar1 == '\x05')) || ((cVar1 == '\x02' || (cVar1 == '\x06')))) {
      iVar2 = mmc_pre_write_check();
      if (iVar2 == 0) {
        if (param_4 == 1) {
          local_40 = 0x18;
        }
        else {
          local_40 = 0x19;
        }
        local_38 = 1;
        local_24 = 0;
        local_3c = param_2;
        if (((char)puVar3[2] != '\x05') && ((char)puVar3[2] != '\x06')) {
          local_3c = param_2 * puVar3[9];
        }
        local_1c = 1;
        iVar2 = mmc_write_dispatch(puVar3,&local_40,param_3,param_4);
      }
    }
    else {
      iVar2 = 0x10;
    }
  }
  else {
    iVar2 = 0x1b;
  }
  return iVar2;
}




/* 0x080342b8 */
undefined4 FUN_080342b8(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  undefined4 uVar1;
  
  FUN_0800bf34(param_1,0x7ff003f,0);
  if (false) {
switchD_080342cc_caseD_3:
    return 0x14;
  }
  switch(param_2) {
  case 0:
    uVar1 = 0;
    break;
  case 1:
  case 5:
    uVar1 = 1;
    break;
  case 2:
  case 6:
    uVar1 = 2;
    break;
  default:
    goto switchD_080342cc_caseD_3;
  }
  FUN_0800c028(param_1,uVar1);
  FUN_0800bf34(param_1,0x7ff003f,1);
  return 0;
}




/* 0x08034300 */
undefined4 FUN_08034300(param_1)
undefined4 param_1;
{
  FUN_0800be10(param_1,0);
  FUN_0800bdf8(param_1);
  return 0;
}




/* 0x08034314 */
int FUN_08034314(param_1, param_2, param_3, param_4)
int * param_1; int param_2; undefined4 * param_3; uint param_4;
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 local_28;
  
  local_28 = 0;
  iVar4 = *param_1;
  if (param_1[0x16] == 1) {
    uVar6 = param_1[9];
    uVar5 = param_4 / uVar6;
  }
  else {
    uVar5 = 1;
    uVar6 = param_4;
  }
  uVar6 = uVar6 + 3 >> 2;
  if ((int)(*(uint *)(param_2 + 0x24) << 0x1e) < 0) {
    uVar7 = 0x20;
  }
  else {
    if ((*(uint *)(param_2 + 0x24) & 1) == 0) {
      return 1;
    }
    uVar7 = 0x10;
  }
  do {
    iVar1 = FUN_0803456c(iVar4,uVar7,&local_28);
    if (iVar1 != 0) {
      *(undefined4 *)(param_2 + 0x20) = local_28;
      return iVar1;
    }
    FUN_0800bfac(iVar4,uVar7);
    uVar2 = 0;
    if ((int)(*(uint *)(param_2 + 0x24) << 0x1e) < 0) {
      for (; uVar2 < uVar6; uVar2 = uVar2 + 1) {
        *param_3 = *(undefined4 *)((&DAT_0804e2d8)[iVar4] + 0x20);
        param_3 = param_3 + 1;
      }
    }
    else if ((*(uint *)(param_2 + 0x24) & 1) != 0) {
      for (; uVar2 < uVar6; uVar2 = uVar2 + 1) {
        uVar3 = *param_3;
        param_3 = param_3 + 1;
        *(undefined4 *)((&DAT_0804e2d8)[iVar4] + 0x20) = uVar3;
      }
    }
    uVar5 = uVar5 - 1;
  } while (uVar5 != 0);
  return 0;
}




/* 0x080343c0 */
undefined4 FUN_080343c0(param_1, param_2, param_3)
undefined4 param_1; int param_2; uint param_3;
{
  uint uVar1;
  byte *pbVar2;
  uint uVar3;
  
  FUN_080329f8(4,0);
  FUN_080329f8(2,param_2,param_3);
  FUN_080329f8(4,0);
  pbVar2 = &DAT_80201000;
  uVar1 = param_3 >> 0x10;
  if ((param_3 & 0xffff) != 0) {
    uVar1 = uVar1 + 1;
  }
  FUN_08006d14(&DAT_80201000,uVar1 << 3);
  if (param_3 != 0) {
    while( true ) {
      uVar3 = 0x10000;
      if (param_3 < 0x10000) {
        uVar3 = param_3;
      }
      FUN_08006e1a(param_2,pbVar2 + 4);
      pbVar2[2] = (byte)uVar3;
      pbVar2[3] = (byte)(uVar3 >> 8);
      param_3 = param_3 - uVar3;
      *pbVar2 = 1;
      pbVar2[1] = 0;
      if (uVar3 != 0) {
        *pbVar2 = 0x21;
        pbVar2[1] = 0;
      }
      param_2 = param_2 + uVar3;
      if (param_3 == 0) break;
      pbVar2 = pbVar2 + 8;
    }
    *pbVar2 = *pbVar2 | 2;
    pbVar2[1] = 0;
  }
  FUN_080329f8(4,0);
  FUN_080329f8(2,&DAT_80201000,uVar1 << 3);
  FUN_080329f8(4,0);
  FUN_0800bff8(param_1,0);
  FUN_0800bfe8(param_1,&DAT_80201000);
  return 0;
}




/* 0x08034488 */
undefined4 FUN_08034488(param_1, param_2)
undefined4 param_1; uint param_2;
{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  
  iVar1 = FUN_08033ca0();
  if (iVar1 == 0) {
    return 0x14;
  }
  uVar5 = (uint)(*(int *)(iVar1 + 0xb4) << 0x10) >> 0x18;
  FUN_0800bdd8(param_1);
  if (uVar5 == 0) {
    return 1;
  }
  uVar5 = uVar5 * 1000000;
  FUN_0800be10(param_1,0);
  uVar4 = uVar5 / (param_2 << 1);
  uVar2 = uVar5;
  if (uVar4 == 0) goto LAB_080344ca;
  while( true ) {
    uVar2 = uVar5 / (uVar4 << 1);
LAB_080344ca:
    if (uVar2 <= param_2) break;
    uVar4 = uVar4 + 1;
  }
  FUN_0800c0a8(param_1);
  iVar1 = 5000000;
  do {
    iVar3 = FUN_0800bf74(param_1);
    if (iVar3 == 1) {
      FUN_0800be10(param_1,1);
      return 0;
    }
    thunk_FUN_080199b4(1);
    bVar6 = iVar1 != 0;
    iVar1 = iVar1 + -1;
  } while (bVar6);
  return 3;
}




/* 0x08034508 */
undefined4 FUN_08034508(param_1, param_2)
undefined4 param_1; uint param_2;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 10;
  iVar1 = FUN_08033ca0();
  if (iVar1 == 0) {
    return 0x14;
  }
  iVar1 = *(int *)(iVar1 + 0xb4);
  if (iVar1 << 7 < 0) {
    uVar3 = 0xe;
  }
  else if (iVar1 << 6 < 0) {
    uVar3 = 0xc;
  }
  else if (-1 < iVar1 << 5) {
    return 1;
  }
  uVar2 = FUN_0800be54(param_1);
  if (((uVar3 | param_2) != uVar2) && (FUN_0800c104(param_1,0), param_2 == 1)) {
    FUN_0800c180(param_1,uVar3);
    FUN_0800c104(param_1,1);
    FUN_0800beb8(param_1);
  }
  return 0;
}




/* 0x0803456c */
undefined4 FUN_0803456c(param_1, param_2, param_3)
undefined4 param_1; uint param_2; uint * param_3;
{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  
  uVar3 = 0;
  if ((param_2 & 0x7ff003f) == 0) {
    uVar2 = 0x14;
  }
  else {
    do {
      uVar1 = FUN_0800be44(param_1);
      if (((param_2 | 0x8000) & uVar1) != 0) {
        *param_3 = uVar1;
        if ((uVar1 & 0x7ff0000) == 0) {
          return 0;
        }
        return 1;
      }
      thunk_FUN_080199b4(100);
      uVar3 = uVar3 + 100;
    } while (uVar3 < 5000000);
    uVar2 = 3;
  }
  return uVar2;
}




/* 0x080345b8 */
int FUN_080345b8(param_1)
int param_1;
{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  undefined4 local_38;
  undefined4 local_34;
  undefined1 local_30;
  undefined1 auStack_2c [16];
  undefined4 local_1c;
  undefined4 local_14;
  
  local_38 = 2;
  local_30 = 4;
  local_34 = 0;
  local_1c = 0;
  local_14 = 0;
  iVar2 = sdcc_command(param_1,&local_38);
  if (iVar2 == 0) {
    if ((*(char *)(param_1 + 8) == '\x02') || (*(char *)(param_1 + 8) == '\x06')) {
      iVar3 = FUN_080333ba(auStack_2c,param_1);
    }
    else {
      iVar3 = FUN_0803344c(auStack_2c,param_1);
    }
    if (iVar3 == 0) {
      iVar2 = 0x14;
    }
    else {
      uVar1 = FUN_080331e0(param_1);
      *(undefined2 *)(param_1 + 10) = uVar1;
    }
  }
  return iVar2;
}




/* 0x0803460c */
undefined4 FUN_0803460c(param_1)
int param_1;
{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  
  piVar1 = (int *)FUN_08033ca0();
  uVar2 = 0;
  if (piVar1 != (int *)0x0) {
    piVar1[0x27] = (int)piVar1;
    piVar4 = piVar1 + 3;
    if ((*(char *)((int)piVar1 + 0x15) != '\x01') && (*(char *)((int)piVar1 + 0x15) != '\x02')) {
      piVar1[0x29] = 0;
      if ((char)piVar1[1] == '\0') {
        FUN_08006d14(piVar4,0x94);
        *piVar4 = param_1;
        piVar1[0x27] = (int)piVar1;
        *piVar1 = param_1;
        *(undefined1 *)(piVar1 + 1) = 1;
        *(undefined1 *)(piVar1 + 0x26) = 0;
      }
      FUN_08032b0c(param_1,1);
      FUN_08032b64();
      FUN_08032dcc(piVar4,5);
      thunk_FUN_080199b4(1000);
      FUN_0800bc84();
      FUN_0800bc64(param_1,0);
      *(undefined4 *)((&DAT_0804e2c8)[param_1] + 0xc) = 0;
      FUN_0800bda0(param_1);
      *(undefined4 *)((&DAT_0804e2c8)[param_1] + 0x2c) = 0;
      FUN_0800bda0(param_1);
      *(undefined4 *)((&DAT_0804e2c8)[param_1] + 0x38) = 0x18007ff;
      *(uint *)((&DAT_0804e2c8)[param_1] + 4) = *(uint *)((&DAT_0804e2c8)[param_1] + 4) | 0x200000;
      *(uint *)((&DAT_0804e2c8)[param_1] + 4) = *(uint *)((&DAT_0804e2c8)[param_1] + 4) & 0xfffff3ff
      ;
      FUN_0800bda0(param_1);
      *(undefined4 *)((&DAT_0804e2c8)[param_1] + 0x38) = 0x400000;
      *(undefined4 *)((&DAT_0804e2c8)[param_1] + 0x3c) = 0;
      *piVar4 = param_1;
      *(undefined1 *)((int)piVar1 + 0x15) = 1;
      iVar3 = FUN_08032acc();
      piVar1[0x19] = 1;
      piVar1[0x25] = iVar3;
      FUN_08032a04(param_1,0,2);
    }
    uVar2 = 1;
  }
  return uVar2;
}




/* 0x08034704 */
undefined4 FUN_08034704(param_1)
int param_1;
{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  bool bVar5;
  undefined4 local_28;
  
  local_28 = 0;
  piVar1 = (int *)FUN_08033ca0();
  if (piVar1 == (int *)0x0) {
    uVar3 = 0;
  }
  else {
    piVar1[0x27] = (int)piVar1;
    piVar4 = piVar1 + 3;
    bVar5 = *(char *)((int)piVar1 + 0x15) == '\x01';
    do {
      if (bVar5) goto LAB_08034876;
      bVar5 = true;
    } while (*(char *)((int)piVar1 + 0x15) == '\x02');
    if ((char)piVar1[1] == '\0') {
      FUN_08006d14(piVar4,0x94);
      *piVar4 = param_1;
      piVar1[0x27] = (int)piVar1;
      *piVar1 = param_1;
      *(undefined1 *)(piVar1 + 1) = 1;
      *(undefined1 *)(piVar1 + 0x26) = 1;
    }
    FUN_08032b0c(param_1,1);
    FUN_08032b64();
    local_28 = FUN_08032ad0(param_1);
    FUN_08032a04(param_1,&local_28,4);
    FUN_08032dcc(piVar4,5);
    thunk_FUN_080199b4(1000);
    FUN_0800bc84();
    *(undefined4 *)((&DAT_0804e2c8)[param_1] + 0xc) = 0;
    FUN_0800bda0(param_1);
    *(undefined4 *)((&DAT_0804e2c8)[param_1] + 0x2c) = 0;
    FUN_0800bda0(param_1);
    *(undefined4 *)((&DAT_0804e2c8)[param_1] + 0x38) = 0x18007ff;
    *(uint *)((&DAT_0804e2c8)[param_1] + 4) = *(uint *)((&DAT_0804e2c8)[param_1] + 4) | 0x200000;
    *(uint *)((&DAT_0804e2c8)[param_1] + 4) = *(uint *)((&DAT_0804e2c8)[param_1] + 4) & 0xfffff3ff;
    FUN_0800bda0(param_1);
    *(undefined4 *)((&DAT_0804e2c8)[param_1] + 0x38) = 0x400000;
    *(undefined4 *)((&DAT_0804e2c8)[param_1] + 0x3c) = 0;
    *piVar4 = param_1;
    *(undefined1 *)((int)piVar1 + 0x15) = 1;
    iVar2 = FUN_08032acc();
    piVar1[0x19] = 1;
    piVar1[0x25] = iVar2;
    *(uint *)(&DAT_0804e2c8)[param_1] = *(uint *)(&DAT_0804e2c8)[param_1] | 1;
    FUN_0800bda0();
    FUN_0800bc64(param_1,1);
    FUN_0800c154(param_1,1);
    FUN_0800c058(param_1);
    FUN_0800be2c(param_1,piVar1 + 0x2d);
    FUN_08034508(param_1,1);
    FUN_0800bf18(param_1,0x7ff003f,0);
    FUN_0800bf34(param_1,0x7ff003f,1);
    FUN_0800bfac(param_1,0x7ff003f);
    *(byte *)((int)piVar1 + 0x99) = (byte)((uint)(piVar1[0x2e] << 0x1d) >> 0x1f);
    bVar5 = -1 < piVar1[0x2d] << 0xc;
    if (bVar5) {
      *(undefined1 *)((int)piVar1 + 0x9a) = 0;
    }
    else {
      *(undefined1 *)((int)piVar1 + 0x9a) = 1;
    }
    FUN_0800bdbc(param_1,!bVar5);
LAB_08034876:
    uVar3 = 1;
  }
  return uVar3;
}




/* 0x08034888 */
undefined4 FUN_08034888(param_1)
int param_1;
{
  int *piVar1;
  
  piVar1 = &DAT_08059efc;
  if (DAT_0804e2a8 != 0x20) {
    for (; piVar1 < (int *)0x805a071; piVar1 = piVar1 + 3) {
      if ((*piVar1 != 0) && (*piVar1 == param_1)) {
        return 1;
      }
    }
  }
  return 0;
}




/* 0x080348b8 */
undefined4 FUN_080348b8(param_1)
int param_1;
{
  if ((DAT_0804d65c == param_1) &&
     ((((DAT_0804d660 == '\x02' || (DAT_0804d660 == '\x06')) || (DAT_0804d660 == '\x01')) ||
      (DAT_0804d660 == '\x05')))) {
    return 1;
  }
  return 0;
}




/* 0x080348e0 */
undefined4 FUN_080348e0(param_1, param_2, param_3)
int * param_1; uint * param_2; undefined4 * param_3;
{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *param_1;
  uVar1 = param_1[1];
  if (uVar1 == 0xffffffff) {
    uVar1 = 0;
  }
  if ((uVar1 != 0) && (*(char *)(iVar3 + 0x61) == '\0')) {
    return 0x16;
  }
  if ((1 << (uVar1 & 0xff) & *(uint *)(iVar3 + 0x7c)) == 0) {
    return 0x14;
  }
  if (uVar1 == 0) {
    *param_2 = *(uint *)(iVar3 + 0x1c);
    uVar2 = 0;
  }
  else {
    if (uVar1 == 1) {
      *param_2 = (uint)(*(int *)(iVar3 + 100) << 10) >> 9;
      *param_3 = 1;
      return 0;
    }
    if (uVar1 == 2) {
      *param_2 = (uint)(*(int *)(iVar3 + 100) << 10) >> 9;
      uVar2 = 2;
    }
    else if (uVar1 == 4) {
      *param_2 = *(uint *)(iVar3 + 0x68);
      uVar2 = 4;
    }
    else if (uVar1 == 5) {
      *param_2 = *(uint *)(iVar3 + 0x6c);
      uVar2 = 5;
    }
    else if (uVar1 == 6) {
      *param_2 = *(uint *)(iVar3 + 0x70);
      uVar2 = 6;
    }
    else {
      if (uVar1 != 7) {
        return 0x14;
      }
      *param_2 = *(uint *)(iVar3 + 0x74);
      uVar2 = 7;
    }
  }
  *param_3 = uVar2;
  return 0;
}




/* 0x08034966 */
undefined4 FUN_08034966(param_1)
int * param_1;
{
  char cVar1;
  int iVar2;
  
  iVar2 = param_1[1];
  if (iVar2 == -1) {
    iVar2 = 0;
  }
  cVar1 = *(char *)(*param_1 + 0x78);
  if (cVar1 == '\x01') {
    if (iVar2 == 1) {
      return 1;
    }
  }
  else if (cVar1 == '\x02') {
    if (iVar2 == 2) {
      return 1;
    }
  }
  else if ((cVar1 == '\a') && (iVar2 == 0)) {
    return 1;
  }
  return 0;
}




/* 0x08034a40 */
int mmc_switch_cmd6(param_1, param_2)
int param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 local_60;
  int local_5c;
  undefined1 local_58;
  int local_54;
  undefined4 local_44;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined1 local_30;
  undefined4 local_1c;
  undefined4 local_14;
  
  local_38 = 6;
  local_30 = 1;
  local_1c = 1;
  local_14 = 0;
  uStack_34 = param_2;
  iVar1 = sdcc_command(param_1,&local_38);
  if (iVar1 == 0) {
    local_60 = 0xd;
    local_58 = 1;
    local_44 = 0;
    local_5c = (uint)*(ushort *)(param_1 + 10) << 0x10;
    local_3c = 0;
    iVar1 = sdcc_command(param_1,&local_60);
    if (iVar1 == 0) {
      if ((uint)(local_54 << 0x13) >> 0x1c == 4) {
        iVar1 = 0;
        if (local_54 << 0x18 < 0) {
          iVar1 = 0x13;
        }
      }
      else {
        iVar1 = 8;
      }
    }
  }
  return iVar1;
}




/* 0x08034aa0 */
undefined4 FUN_08034aa0(param_1)
undefined4 * param_1;
{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = *param_1;
  iVar2 = mmc_switch_cmd6(param_1,0x3b70000);
  if (iVar2 == 0) {
    FUN_08032f98((int)(short)uVar1,0);
    iVar2 = FUN_08034e78(param_1,0);
    if (((iVar2 == 0) && (iVar2 = FUN_08033b30(param_1), iVar2 == 0)) &&
       (iVar2 = FUN_08033aac(param_1), iVar2 == 0)) {
      *(uint *)((&DAT_0804e2c8)[(short)uVar1] + 4) =
           *(uint *)((&DAT_0804e2c8)[(short)uVar1] + 4) | 0x1000;
      FUN_0800bda0();
      FUN_08032dcc(param_1,1);
      iVar2 = FUN_08032eac(param_1);
      if (iVar2 == 0) {
        *(undefined1 *)((int)param_1 + 9) = 2;
        *(undefined1 *)(param_1[0x24] + 0xa0) = 0;
      }
    }
  }
  return 0;
}




/* 0x08034b1c */
undefined4 FUN_08034b1c(param_1)
uint param_1;
{
  uint *puVar1;
  uint *puVar2;
  
  if (param_1 < 3) {
    puVar1 = (uint *)FUN_08033ca0();
    if (puVar1 == (uint *)0x0) {
      return 0;
    }
    puVar2 = puVar1 + 3;
    if (puVar2 != (uint *)0x0) {
      if ((*(char *)((int)puVar1 + 0x15) != '\x01') && (*(char *)((int)puVar1 + 0x15) != '\x02')) {
        FUN_08006d14(puVar2,0x94);
        *puVar2 = param_1;
        puVar1[0x27] = (uint)puVar1;
        *puVar1 = param_1;
        *(undefined1 *)(puVar1 + 1) = 1;
        FUN_08032b64();
        FUN_08032a04(param_1,0,1);
        FUN_0800bc84();
        *puVar2 = param_1;
        *(undefined1 *)((int)puVar1 + 0x15) = 1;
        puVar1[0x19] = 1;
        *(undefined4 *)(puVar1[0x27] + 0xa4) = 0;
        FUN_08032b0c(param_1,1);
      }
      return 1;
    }
  }
  return 0;
}




/* 0x08034b88 */
undefined4 FUN_08034b88(param_1, param_2)
int * param_1; int * param_2;
{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  
  iVar4 = *param_1;
  uVar5 = 1;
  uVar1 = 0;
  uVar3 = 0;
  do {
    if (0x7ffff < uVar3) goto LAB_08034c08;
    uVar1 = FUN_0800bd8c(iVar4);
    if ((uVar1 & 0x40) != 0) {
      *(undefined4 *)((&DAT_0804e2c8)[iVar4] + 0x38) = 0x40;
      uVar5 = 0;
      if ((uVar1 & 0x800000) != 0) {
        *(undefined4 *)((&DAT_0804e2c8)[iVar4] + 0x38) = 0x800000;
        param_2[7] = 0;
      }
      goto LAB_08034c08;
    }
    if ((uVar1 & 4) != 0) {
      *(undefined4 *)((&DAT_0804e2c8)[iVar4] + 0x38) = 4;
      uVar5 = 2;
      goto LAB_08034c08;
    }
    uVar3 = uVar3 + 1;
  } while ((uVar1 & 1) == 0);
  iVar2 = *param_2;
  if (((iVar2 == 0x29) || (iVar2 == 1)) || (iVar2 == 5)) {
    uVar5 = 0;
  }
  else {
    uVar5 = 4;
  }
  *(undefined4 *)((&DAT_0804e2c8)[iVar4] + 0x38) = 1;
LAB_08034c08:
  param_2[8] = uVar1;
  return uVar5;
}




/* 0x08034c14 */
undefined4 FUN_08034c14(param_1, param_2, param_3)
int * param_1; uint * param_2; int param_3;
{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  undefined4 uVar5;
  bool bVar6;
  int local_20;
  
  iVar4 = *param_1;
  bVar6 = ((uint)param_2 & 3) != 0;
  uVar5 = 0;
  local_20 = 0;
  if (param_2 == (uint *)0x0) {
    uVar5 = 0xd;
  }
  else {
    while (0 < param_3) {
      uVar1 = FUN_0800bd8c(iVar4);
      if ((uVar1 & 0x2a) != 0) {
        uVar5 = 0xd;
        goto LAB_08034c9e;
      }
      if (param_3 == 0) break;
      if ((uVar1 & 0x200000) != 0) {
        if (((uVar1 & 0x8000) == 0) || (bVar6)) {
          uVar1 = *(uint *)((&DAT_0804e2c8)[iVar4] + 0x80);
          if (bVar6) {
            uVar2 = 0;
            puVar3 = param_2;
            do {
              param_2 = (uint *)((int)puVar3 + 1);
              *(char *)puVar3 = (char)uVar1;
              uVar1 = uVar1 >> 8;
              uVar2 = uVar2 + 1;
              puVar3 = param_2;
            } while (uVar2 < 4);
          }
          else {
            *param_2 = uVar1;
            param_2 = param_2 + 1;
          }
          param_3 = param_3 + -4;
        }
        else {
          local_20 = param_3;
          FUN_0800bbec(iVar4,param_2,&local_20);
          param_2 = (uint *)((int)param_2 + (param_3 - local_20));
          param_3 = local_20;
        }
      }
    }
    if (false) {
LAB_08034c9e:
      FUN_08034cfc(param_1);
    }
    FUN_0800bd78(iVar4);
  }
  return uVar5;
}




/* 0x08034cb4 */
int * FUN_08034cb4(param_1, param_2)
short param_1; int param_2;
{
  int iVar1;
  int *piVar2;
  
  if (DAT_0804e2a8 < 1) {
    return (int *)0x0;
  }
  for (piVar2 = &DAT_08059efc; piVar2 < (int *)0x805a071; piVar2 = piVar2 + 3) {
    if (*piVar2 == 0) goto LAB_08034cd8;
  }
  piVar2 = (int *)0x0;
LAB_08034cd8:
  if (piVar2 != (int *)0x0) {
    iVar1 = FUN_08033ca0((int)param_1);
    if (iVar1 == 0) {
      return (int *)0x0;
    }
    *piVar2 = iVar1 + 0xc;
    piVar2[1] = param_2;
    DAT_0804e2a8 = DAT_0804e2a8 + -1;
  }
  return piVar2;
}




/* 0x08034cfc */
undefined4 FUN_08034cfc(param_1)
int * param_1;
{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  iVar2 = *param_1;
  FUN_08032dcc(param_1 + 3,5);
  puVar1 = (undefined4 *)(&DAT_0804e2c8)[iVar2];
  uVar3 = puVar1[1];
  uVar4 = *puVar1;
  uVar5 = puVar1[0xf];
  FUN_08032a04(iVar2,0,2);
  *(undefined4 *)((&DAT_0804e2c8)[iVar2] + 4) = uVar3;
  FUN_0800bda0(iVar2);
  *(undefined4 *)(&DAT_0804e2c8)[iVar2] = uVar4;
  FUN_0800bda0(iVar2);
  *(undefined4 *)((&DAT_0804e2c8)[iVar2] + 0x3c) = uVar5;
  FUN_08032dcc(param_1 + 3,*(char *)((int)param_1 + 0x15) == '\x02');
  return 1;
}




/* 0x08034d68 */
int FUN_08034d68(param_1)
int * param_1;
{
  int iVar1;
  short local_68;
  short local_66;
  char local_5a;
  char local_54;
  short local_52;
  undefined4 local_44;
  undefined4 local_40;
  undefined1 local_3c;
  undefined4 local_28;
  undefined4 local_20;
  
  FUN_08006cd0(&DAT_0805a368,0x40);
  local_44 = 6;
  local_3c = 1;
  local_40 = 0xffff01;
  local_20 = 2;
  local_28 = 0;
  param_1[0x16] = 0;
  iVar1 = mmc_write_dispatch(param_1,&local_44,&DAT_0805a368,0x40);
  param_1[0x16] = 1;
  if (iVar1 != 0) {
    return iVar1;
  }
  FUN_0803351c(&DAT_0805a368,&local_68);
  if ((local_68 != 0) && ((local_54 != '\x01' || (local_52 != 2)))) {
    if (local_66 != -0x7ffd) {
      return 0;
    }
    if (local_5a != '\x01') {
      return 0;
    }
    FUN_08006cd0(&DAT_0805a368,0x40);
    FUN_08006d14(&local_68,0x24);
    local_20 = 2;
    local_40 = 0x80ffff01;
    param_1[0x16] = 0;
    iVar1 = mmc_write_dispatch(param_1,&local_44,&DAT_0805a368,0x40);
    param_1[0x16] = 1;
    if (iVar1 != 0) {
      return iVar1;
    }
    FUN_0803351c(&DAT_0805a368,&local_68);
    if (((local_68 != 0) && (local_5a == '\x01')) && ((local_54 != '\x01' || (local_52 != 2)))) {
      *(uint *)((&DAT_0804e2c8)[*param_1] + 4) =
           *(uint *)((&DAT_0804e2c8)[*param_1] + 4) & 0xffff3fff | 0x8000;
      FUN_0800bda0();
      thunk_FUN_080199b4(1000);
      *(undefined1 *)((int)param_1 + 0x5f) = 1;
      FUN_08032dcc(param_1,1);
      return 0;
    }
  }
  return 1;
}




/* 0x08034e78 */
undefined4 FUN_08034e78(param_1, param_2)
int param_1; int param_2;
{
  undefined4 uVar1;
  undefined4 local_30;
  int local_2c;
  undefined1 local_28;
  undefined4 local_14;
  undefined4 local_c;
  
  if (param_2 == 0) {
    local_2c = 0;
  }
  else {
    local_2c = (uint)*(ushort *)(param_1 + 10) << 0x10;
  }
  local_30 = 7;
  local_28 = 1;
  local_14 = 0;
  local_c = 0;
  uVar1 = sdcc_command(param_1,&local_30);
  if (param_2 == 0) {
    uVar1 = 0;
  }
  return uVar1;
}




/* 0x08034eaa */
undefined4 FUN_08034eaa(param_1, param_2)
int param_1; undefined4 param_2;
{
  undefined4 local_38;
  int local_34;
  undefined1 local_30;
  undefined4 local_1c;
  undefined4 local_14;
  
  local_38 = 0x37;
  local_34 = (uint)*(ushort *)(param_1 + 10) << 0x10;
  local_30 = 1;
  local_1c = 0;
  local_14 = 0;
  sdcc_command(param_1,&local_38);
  sdcc_command(param_1,param_2);
  return 0;
}




/* 0x08034edc */
void FUN_08034edc(param_1, param_2)
int * param_1; int * param_2;
{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined2 local_30;
  undefined2 local_2e;
  undefined2 local_2c;
  undefined2 local_28;
  undefined2 local_26;
  undefined2 local_24;
  int local_20;
  
  iVar4 = *param_1;
  uVar3 = 0;
  FUN_08006d14(&local_30,0x14);
  do {
    *(undefined4 *)((&DAT_0804e2c8)[iVar4] + 0x38) = 0x18007ff;
    uVar3 = uVar3 + 1;
    uVar1 = FUN_0800bd8c(iVar4);
    if ((uVar1 & 0x18007ff) == 0) goto LAB_08034f26;
  } while (uVar3 < 1000);
  *(uint *)((&DAT_0804e2c8)[iVar4] + 0x2c) = *(uint *)((&DAT_0804e2c8)[iVar4] + 0x2c) & 0xfffffffe;
  FUN_0800bda0();
LAB_08034f26:
  local_24 = (undefined2)*param_2;
  local_2c = 1;
  if (((char)param_2[2] != '\0') && (local_26 = 1, (char)param_2[2] == '\x04')) {
    local_28 = 1;
  }
  if (param_2[7] != 0) {
    local_2e = 1;
  }
  iVar2 = *param_2;
  if ((((iVar2 == 0x35) || (iVar2 == 0x11)) || (iVar2 == 0x12)) ||
     ((iVar2 == 0x18 || (iVar2 == 0x19)))) {
    local_30 = 1;
  }
  local_20 = param_2[1];
  FUN_0800bd20(iVar4,&local_30);
  return;
}




/* 0x08034f80 */
uint FUN_08034f80(param_1)
int param_1;
{
  int iVar1;
  uint uVar2;
  undefined4 local_30;
  int local_2c;
  undefined1 local_28;
  int local_24;
  undefined4 local_14;
  undefined4 local_c;
  
  uVar2 = 9;
  local_30 = 0xd;
  local_28 = 1;
  local_14 = 0;
  local_c = 0;
  local_2c = (uint)*(ushort *)(param_1 + 10) << 0x10;
  iVar1 = sdcc_command(param_1,&local_30);
  if (iVar1 == 0) {
    uVar2 = (uint)(local_24 << 0x13) >> 0x1c;
  }
  return uVar2;
}




/* 0x08034fb0 */
int mmc_pre_write_check(param_1)
int * param_1;
{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  if (param_1 == (int *)0x0) {
    return 0x14;
  }
  iVar3 = param_1[1];
  if (iVar3 == -1) {
    iVar3 = 0;
  }
  if (*(int *)(*param_1 + 4) == iVar3) {
    return 0;
  }
  cVar1 = *(char *)(*param_1 + 8);
  if ((cVar1 != '\x02') && (cVar1 != '\x06')) {
    return 0x16;
  }
  iVar3 = *param_1;
  uVar4 = param_1[1];
  if (uVar4 == 0xffffffff) {
    uVar4 = 0;
  }
  if ((uVar4 != 0) && (*(char *)(iVar3 + 0x61) == '\0')) {
    return 0x16;
  }
  if ((1 << (uVar4 & 0xff) & *(uint *)(iVar3 + 0x7c)) == 0) {
    return 0x14;
  }
  iVar2 = mmc_switch_cmd6(iVar3,(uVar4 | (uint)*(byte *)(iVar3 + 0x78) << 3) << 8 | 0x3b30000);
  if (iVar2 == 0) {
    *(uint *)(iVar3 + 4) = uVar4;
  }
  return iVar2;
}




/* 0x08034fde */
int FUN_08034fde(param_1)
undefined4 * param_1;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_38;
  int local_34;
  undefined1 local_30;
  undefined4 local_1c;
  undefined4 local_14;
  
  uVar2 = *param_1;
  local_30 = 1;
  local_1c = 0;
  local_38 = 0x37;
  local_14 = 0;
  local_34 = (uint)*(ushort *)((int)param_1 + 10) << 0x10;
  iVar1 = sdcc_command(param_1,&local_38);
  if (iVar1 == 0) {
    local_38 = 6;
    local_14 = 0;
    local_34 = 2;
    iVar1 = sdcc_command(param_1,&local_38);
    if (iVar1 == 0) {
      if (*(char *)(param_1 + 0x23) == '\x01') {
        iVar1 = FUN_080342b8(uVar2,1);
      }
      else {
        FUN_0800bcec();
      }
    }
  }
  return iVar1;
}




/* 0x08035040 */
int FUN_08035040(param_1, param_2, param_3)
undefined4 * param_1; int param_2; int param_3;
{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = *param_1;
  uVar3 = 1;
  iVar2 = 5000;
  if ((*(char *)(param_1 + 2) == '\x02') || (*(char *)(param_1 + 2) == '\x06')) {
    if (param_2 != 0) {
      iVar2 = 2000;
    }
  }
  else if (param_2 != 0) {
    iVar2 = 400;
  }
  if (param_1[0x21] == 0) {
    iVar2 = iVar2 * 50000;
  }
  else {
    iVar2 = param_1[0x21] * iVar2;
  }
  *(int *)((&DAT_0804e2c8)[(short)uVar1] + 0x24) = iVar2;
  if (param_1[0x16] == 1) {
    uVar3 = param_1[9] & 0xffff;
  }
  *(uint *)((&DAT_0804e2c8)[(short)uVar1] + 0x28) = uVar3 * param_3;
  return uVar3 * param_3;
}




/* 0x08035098 */
undefined4 FUN_08035098(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if (2 < param_1) {
    return 0;
  }
  uVar1 = FUN_08032af8();
  if (((uVar1 & 1) != 0) && (param_2 == 1)) {
    uVar2 = 1;
  }
  if ((int)(uVar1 << 0x1e) < 0) {
    uVar2 = 1;
  }
  return uVar2;
}




/* 0x080350be */
undefined4 FUN_080350be(param_1)
undefined4 param_1;
{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  while( true ) {
    if (0x7ffff < uVar2) {
      return 8;
    }
    iVar1 = FUN_08034f80(param_1);
    if (iVar1 == 4) break;
    thunk_FUN_080199b4(100);
    uVar2 = uVar2 + 1;
  }
  return 0;
}




/* 0x080350ee */
undefined4 FUN_080350ee(param_1)
undefined4 * param_1;
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar3 = *param_1;
  uVar2 = 0;
  do {
    if (0x7ffff < uVar2) {
      return 8;
    }
    uVar1 = FUN_0800bd8c(uVar3);
    if ((uVar1 & 0x1a) != 0) {
      return 0xe;
    }
    if ((uVar1 & 0x2a) != 0) {
      return 0xd;
    }
    uVar2 = uVar2 + 1;
  } while ((uVar1 & 0x100) == 0);
  FUN_0800bd78(uVar3);
  return 0;
}




/* 0x08035134 */
undefined4 FUN_08035134(param_1)
int * param_1;
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar4 = *param_1;
  uVar3 = 7;
  uVar2 = 0;
  do {
    if (0x7ffff < uVar2) {
      if ((true) && (iVar4 = FUN_08034f80(param_1), iVar4 == 4)) {
LAB_0803517c:
        uVar3 = 0;
      }
      return uVar3;
    }
    uVar1 = FUN_0800bd8c(iVar4);
    if ((uVar1 & 0x800000) != 0) {
      *(undefined4 *)((&DAT_0804e2c8)[iVar4] + 0x38) = 0x800000;
      goto LAB_0803517c;
    }
    thunk_FUN_080199b4(10);
    uVar2 = uVar2 + 1;
  } while( true );
}




/* 0x08035188 */
undefined4 FUN_08035188(param_1, param_2, param_3)
int * param_1; byte * param_2; int param_3;
{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  byte *pbVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  bool bVar9;
  int local_28;
  
  iVar7 = *param_1;
  uVar8 = 0;
  bVar9 = ((uint)param_2 & 3) != 0;
  uVar6 = 0;
  local_28 = 0;
  if (param_2 == (byte *)0x0) {
    return 0xe;
  }
  FUN_0800bd78(iVar7);
LAB_08035234:
  do {
    if (param_3 < 1) goto LAB_08035238;
    uVar6 = FUN_0800bd8c(iVar7);
    if ((uVar6 & 0x1a) != 0) break;
    if (param_3 == 0) goto LAB_08035238;
    if ((uVar6 & 0x10000) == 0) {
      if ((uVar6 & 0x4000) == 0) {
        if (!bVar9) goto LAB_0803520c;
LAB_08035218:
        uVar4 = 0;
        uVar3 = 0;
        pbVar5 = param_2;
        do {
          param_2 = pbVar5 + 1;
          uVar4 = uVar4 | (uint)*pbVar5 << (uVar3 & 0xff);
          uVar3 = uVar3 + 8;
          pbVar5 = param_2;
        } while (uVar3 < 0x20);
        *(uint *)((&DAT_0804e2c8)[iVar7] + 0x80) = uVar4;
      }
      else {
        if (bVar9) goto LAB_08035218;
        if (0x1f < param_3) {
          local_28 = param_3;
          FUN_0800bc20(iVar7,param_2,&local_28);
          iVar1 = local_28;
          param_2 = param_2 + (param_3 - local_28);
          uVar6 = FUN_0800bd8c(iVar7);
          param_3 = iVar1;
          goto LAB_08035234;
        }
LAB_0803520c:
        uVar2 = *(undefined4 *)param_2;
        param_2 = param_2 + 4;
        *(undefined4 *)((&DAT_0804e2c8)[iVar7] + 0x80) = uVar2;
      }
      param_3 = param_3 + -4;
    }
  } while( true );
LAB_080351ca:
  uVar8 = 0xe;
  goto LAB_08035254;
LAB_08035238:
  if (true) {
    while ((uVar6 & 0x100) == 0) {
      if ((uVar6 & 0x1a) != 0) goto LAB_080351ca;
      uVar6 = FUN_0800bd8c(iVar7);
    }
  }
LAB_08035254:
  FUN_0800bd78(iVar7);
  return uVar8;
}




/* 0x080354d0 */
int FUN_080354d0(param_1, param_2, param_3, param_4, param_5, param_6)
undefined4 param_1; int param_2; undefined4 param_3; int * param_4; undefined4 * param_5; undefined4 param_6;
{
  int iVar1;
  int iVar2;
  undefined1 auStack_298 [56];
  undefined1 auStack_260 [512];
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined1 auStack_58 [56];
  int local_20;
  
  FUN_08006d14(auStack_260,0x200);
  local_20 = 0;
  FUN_08006d14(&local_60,0x40);
  if ((((param_4 == (int *)0x0) || (param_5 == (undefined4 *)0x0)) ||
      ((code *)*param_5 == (code *)0x0)) ||
     (((*param_4 == 0 || (param_4[3] == 0)) || ((param_4[2] == 0 || (param_4[1] == 0)))))) {
    return 2;
  }
  iVar1 = ((code *)*param_5)(param_1,&local_20);
  if (iVar1 != 0) {
    return 7;
  }
  if ((local_20 != 1) &&
     (((local_20 != 0 || (param_2 == 0)) ||
      ((*(int *)(param_2 + 0x18) == 0 ||
       (((*(int *)(param_2 + 0x1c) == 0 || (*(int *)(param_2 + 0x10) == 0)) ||
        (*(int *)(param_2 + 0x14) == 0)))))))) {
    return 0;
  }
  iVar1 = ((code *)*param_4)(param_6,auStack_260);
  if (iVar1 != 0) {
    return iVar1;
  }
  if (local_20 == 0) {
    iVar1 = FUN_08035628(&local_60,param_2);
    if (iVar1 != 0) goto LAB_08035596;
    FUN_08006bdc(auStack_298,auStack_58,0x38);
    iVar1 = ((code *)param_4[3])(auStack_260,(code *)param_4[3],local_60,uStack_5c);
    if (iVar1 != 0) goto LAB_08035596;
  }
  iVar1 = ((code *)param_4[2])(auStack_260,param_1,param_2,param_3);
  if (((iVar1 != 0) && (local_20 == 0)) && (iVar1 == 0xb)) {
    iVar1 = 0;
  }
LAB_08035596:
  iVar2 = ((code *)param_4[1])(auStack_260);
  if (iVar1 == 0) {
    iVar1 = iVar2;
  }
  return iVar1;
}




/* 0x080355a4 */
undefined4 FUN_080355a4(param_1, param_2, param_3)
uint param_1; uint param_2; uint * param_3;
{
  int iVar1;
  uint uVar2;
  uint local_18;
  
  uVar2 = 0;
  if ((((param_1 != 0) && (param_3 != (uint *)0x0)) && (param_1 <= param_1 + param_2)) &&
     (param_2 < 0x11ffef)) {
    *param_3 = 0;
    local_18 = param_1;
    do {
      iVar1 = FUN_0802a10e(&local_18,param_1 + param_2,1);
      if (iVar1 != 0) {
        if (uVar2 == 0) {
          return 1;
        }
        *param_3 = uVar2;
        return 0;
      }
      uVar2 = uVar2 + 1 & 0xff;
    } while (uVar2 < 0x13);
  }
  return 1;
}




/* 0x080355fc */
undefined4 thunk_FUN_080355fc(param_1)
undefined4 * param_1;
{
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = &LAB_08035b7c;
    param_1[2] = &LAB_08035264;
    param_1[1] = &LAB_080355e8;
    param_1[3] = &LAB_08035c1c;
    return 0;
  }
  return 2;
}




/* 0x080355fc */
undefined4 FUN_080355fc(param_1)
undefined4 * param_1;
{
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = &LAB_08035b7c;
    param_1[2] = &LAB_08035264;
    param_1[1] = &LAB_080355e8;
    param_1[3] = &LAB_08035c1c;
    return 0;
  }
  return 2;
}




/* 0x08035628 */
undefined4 FUN_08035628(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  uint local_18;
  
  local_18 = 0;
  if (((param_2 != 0) && (*(int *)(param_2 + 0x10) != 0)) && (*(int *)(param_2 + 0x18) != 0)) {
    FUN_08006d14(param_1,0x20);
    *(undefined1 *)(param_1 + 0x30) = 0;
    *(undefined4 *)(param_1 + 0x28) = 0;
    *(undefined4 *)(param_1 + 0x2c) = 0;
    *(undefined4 *)(param_1 + 0x34) = 0;
    *(undefined4 *)(param_1 + 0x38) = 0;
    *(undefined4 *)(param_1 + 0x3c) = 0;
    iVar1 = FUN_080355a4(*(undefined4 *)(param_2 + 0x10),*(undefined4 *)(param_2 + 0x14),&local_18);
    if (iVar1 != 0) {
      return 1;
    }
    if (3 < local_18) {
      *(undefined4 *)(param_1 + 0x34) = 1;
      *(uint *)(param_1 + 0x3c) = local_18 - 2;
    }
    *(undefined4 *)(param_1 + 0x20) = 0;
    *(undefined4 *)(param_1 + 0x24) = 0;
    return 0;
  }
  return 2;
}




/* 0x08035680 */
undefined4 FUN_08035680(param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8)
undefined4 * param_1; undefined4 param_2; int param_3; int param_4; int param_5; undefined4 param_6; undefined4 param_7; undefined4 param_8;
{
  int iVar1;
  code *pcVar2;
  undefined4 uVar3;
  undefined1 auStack_120 [216];
  undefined1 **local_48;
  undefined1 *local_44;
  undefined4 uStack_40;
  undefined1 *local_3c;
  undefined1 auStack_38 [4];
  undefined1 auStack_34 [4];
  undefined1 auStack_30 [4];
  undefined1 auStack_2c [8];
  
  local_48 = (undefined1 **)0x0;
  if (((param_1 == (undefined4 *)0x0) || (param_3 == 0)) || (param_4 == 0)) {
    return 2;
  }
  iVar1 = ((code *)*param_1)();
  if (iVar1 != 0) {
    return 6;
  }
  pcVar2 = (code *)param_1[2];
  if (pcVar2 == (code *)0x8009981) {
    FUN_08006d14(auStack_120,0xd8);
    local_48 = &local_3c;
    local_3c = auStack_120;
  }
  iVar1 = (*pcVar2)(&local_48,param_2);
  if (iVar1 == 0) {
    FUN_08006e1a(param_3,auStack_38);
    FUN_08006e1a(param_4,auStack_34);
    local_44 = auStack_30;
    uStack_40 = 1;
    FUN_08006e1a(param_7,local_44);
    FUN_08006e1a(param_8,auStack_2c);
    if (param_5 == 0) {
      iVar1 = ((code *)param_1[6])(local_48,auStack_38,1,&local_44);
LAB_08035748:
      if ((iVar1 == 0) && (iVar1 = ((code *)param_1[3])(&local_48), iVar1 == 0)) {
        uVar3 = 0;
        goto LAB_08035758;
      }
    }
    else {
      iVar1 = ((code *)param_1[4])(local_48,auStack_38,1);
      if (iVar1 == 0) {
        FUN_08006e1a(param_5,auStack_38);
        FUN_08006e1a(param_6,auStack_34);
        iVar1 = ((code *)param_1[4])(local_48,auStack_38,1);
        if (iVar1 == 0) {
          iVar1 = ((code *)param_1[5])(local_48,&local_44);
          goto LAB_08035748;
        }
      }
    }
  }
  uVar3 = 6;
LAB_08035758:
  iVar1 = ((code *)param_1[1])();
  if (iVar1 != 0) {
    uVar3 = 6;
  }
  return uVar3;
}




/* 0x08035768 */
undefined4 FUN_08035768(param_1, param_2, param_3, param_4, param_5)
int param_1; uint param_2; int param_3; int param_4; int * param_5;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  uint local_38;
  int iStack_34;
  uint uStack_30;
  int local_2c;
  int iStack_28;
  
  uVar3 = 0;
  uVar4 = 0;
  local_38 = 0;
  iStack_34 = param_1;
  uStack_30 = param_2;
  local_2c = param_3;
  iStack_28 = param_4;
  while( true ) {
    if ((((param_1 == 0) || (param_2 == 0)) || (param_2 + local_2c < param_2)) || (param_4 == 0)) {
      FUN_08035c40(param_1,param_1,param_2,param_4,0x296);
      return 2;
    }
    if (*(int *)(param_4 + 0x378) - 1U == uVar3) {
      uVar5 = 2;
      if (*param_5 == 0) {
        iVar7 = *(int *)(param_4 + uVar3 * 0x128 + 0xe4);
        uVar2 = param_2;
      }
      else {
        local_38 = uVar4;
        iVar1 = FUN_0802a10e(&local_38,param_2 + local_2c,param_5[2] & 0xff);
        if (iVar1 != 0) {
          FUN_08035c40(param_1,param_1,iVar1,param_5[2],0x2b5);
          return 9;
        }
        iVar7 = local_38 - uVar4;
        uVar2 = uVar4;
      }
    }
    else {
      iVar1 = param_4 + uVar3 * 0x128;
      iVar7 = *(int *)(iVar1 + 0xfc);
      if (iVar7 == 2) {
        uVar5 = 1;
      }
      else {
        if (iVar7 != 3) {
          FUN_08035c40(param_1,iVar7,uVar3,*(undefined4 *)(param_4 + 0x378),0x2ca);
          return 4;
        }
        uVar5 = 2;
      }
      iVar7 = *(int *)(iVar1 + 0xe0);
      uVar2 = *(int *)(iVar1 + 0xdc) + param_2;
    }
    iVar6 = param_4 + uVar3 * 0x128;
    iVar1 = FUN_08035680(param_1 + 4,uVar5,uVar2,iVar7,0,0,iVar6 + 0x108,0x20);
    if (iVar1 != 0) break;
    param_2 = param_2 + *(int *)(iVar6 + 0xe4);
    if (*param_5 == 1) {
      uVar4 = param_2;
    }
    uVar3 = uVar3 + 1;
    if (*(uint *)(param_4 + 0x378) <= uVar3) {
      return 0;
    }
  }
  FUN_08035c40(param_1,iVar1,uVar3,uVar5,0x2dc);
  return 6;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x080358a4 */
int FUN_080358a4(param_1, param_2, param_3)
int param_1; int param_2; undefined4 * param_3;
{
  int iVar1;
  int local_18;
  
  iVar1 = 0;
  local_18 = 0;
  if (((param_3 == (undefined4 *)0x0) || (param_2 == 0)) || (param_1 == 0)) {
    iVar1 = 2;
  }
  else if (*(int *)(param_1 * 4 + 0x5e030) << 0x17 < 0) {
    iVar1 = FUN_08006898(param_2,&DAT_0803abdc,0x20);
    if (iVar1 != 0) {
      iVar1 = FUN_08035af6(param_1,&local_18);
      if (iVar1 != 0) {
        return iVar1;
      }
      if (local_18 != 0) {
        iVar1 = FUN_08035ae0(param_3);
        return iVar1;
      }
    }
    iVar1 = 0;
    *param_3 = _DAT_0005e080;
  }
  else {
    *param_3 = 0x10000;
  }
  return iVar1;
}




/* 0x08035908 */
undefined4 thunk_FUN_08035908(param_1)
undefined4 * param_1;
{
  if (param_1 != (undefined4 *)0x0) {
    param_1[2] = 0x8035963;
    param_1[1] = 0x8035a35;
    param_1[4] = 0x8035ae1;
    param_1[3] = 0x8035af7;
    *param_1 = &LAB_08035b14;
    param_1[5] = 0x80359a3;
    return 0;
  }
  return 2;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08035908 */
undefined4 FUN_08035908(param_1)
undefined4 * param_1;
{
  if (param_1 != (undefined4 *)0x0) {
    param_1[2] = 0x8035963;
    param_1[1] = 0x8035a35;
    param_1[4] = 0x8035ae1;
    param_1[3] = 0x8035af7;
    *param_1 = &LAB_08035b14;
    param_1[5] = 0x80359a3;
    return 0;
  }
  return 2;
}




/* 0x08035944 */
undefined4 FUN_08035944(param_1, param_2)
int param_1; uint * param_2;
{
  if ((param_2 != (uint *)0x0) && (param_1 != 0)) {
    *param_2 = (uint)(*(int *)(param_1 * 4 + 0x5e030) << 0x1b) >> 0x1f;
    return 0;
  }
  return 2;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08035962 */
int FUN_08035962(param_1, param_2, param_3)
int param_1; int param_2; uint * param_3;
{
  int iVar1;
  uint uVar2;
  uint local_10;
  
  local_10 = 0;
  if (((param_3 != (uint *)0x0) && (param_2 != 0)) && (param_1 != 0)) {
    uVar2 = _DAT_0005e07c & 0xfffffff;
    *param_3 = uVar2;
    param_3[1] = 0;
    *param_3 = 0;
    param_3[1] = uVar2;
    iVar1 = FUN_080358a4(param_1,param_2,&local_10);
    if (iVar1 == 0) {
      *param_3 = *param_3 | local_10;
      param_3[1] = param_3[1];
    }
    return iVar1;
  }
  return 2;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x080359a2 */
int FUN_080359a2(param_1, param_2, param_3, param_4)
int param_1; uint * param_2; undefined4 * param_3; uint * param_4;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int local_18;
  
  local_18 = 0;
  if ((((param_2 == (uint *)0x0) || (param_3 == (undefined4 *)0x0)) || (param_4 == (uint *)0x0)) ||
     (param_1 == 0)) {
    return 2;
  }
  iVar1 = FUN_08035944(param_1,&local_18);
  if (iVar1 != 0) {
    return iVar1;
  }
  if ((local_18 == 0) ||
     (uVar2 = ((uint)(_DAT_0005c030 << 10) >> 0x1c) + 1, *param_4 = uVar2, uVar2 == 1)) {
LAB_08035a08:
    *param_3 = 0;
    *param_2 = 0;
    *param_4 = 0;
    return 0;
  }
  iVar1 = FUN_08035b48(param_2);
  if (iVar1 != 0) {
    return iVar1;
  }
  if ((*param_2 & 0xff) == 0xf0) goto LAB_08035a08;
  *param_3 = 1;
  uVar3 = *param_2;
  uVar2 = 0;
  if (uVar3 != 0) {
    if ((~(uVar3 ^ uVar3 >> 4) & 0xf) != 0) goto LAB_080359fc;
    uVar2 = uVar3 & 0xf;
    *param_2 = uVar2;
  }
  if (uVar2 < *param_4) {
    return 0;
  }
LAB_080359fc:
  *param_2 = 0;
  *param_4 = 0;
  return 3;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08035a1e */
undefined4 FUN_08035a1e(param_1)
uint * param_1;
{
  if (param_1 != (uint *)0x0) {
    *param_1 = _DAT_0005c024 >> 0x18;
    return 0;
  }
  return 2;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08035a34 */
int FUN_08035a34(param_1, param_2, param_3, param_4)
int param_1; int param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  uint uVar5;
  int local_24;
  undefined4 local_20;
  uint local_1c;
  
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if ((param_2 == 0) || (param_1 == 0)) {
    iVar1 = 2;
  }
  else {
    iVar1 = FUN_08035944(param_1,&local_24,param_3,param_4,0);
    if (iVar1 == 0) {
      if (local_24 == 0) {
        uVar5 = *(uint *)(param_1 * 4 + 0x5e030) & 0xf;
        if (0xb < uVar5) {
          return 3;
        }
        uVar4 = 0x20;
        puVar3 = (undefined4 *)(&DAT_0803abdc + uVar5 * 0x20);
      }
      else {
        uVar5 = 0;
        do {
          local_20 = *(undefined4 *)(uVar5 * 8 + 0x5c0a8);
          local_1c = *(uint *)(uVar5 * 8 + 0x5c0ac) & 0x80ffffff;
          FUN_08006a30(uVar5 * 7 + param_2,&local_20,7);
          uVar5 = uVar5 + 1;
        } while (uVar5 < 4);
        uVar4 = 4;
        puVar3 = &local_20;
        local_20 = _DAT_0005c0c8;
        param_2 = param_2 + 0x1c;
      }
      FUN_08006a30(param_2,puVar3,uVar4);
      iVar2 = FUN_08019bfc();
      if (iVar2 == 1) {
        iVar1 = 4;
      }
    }
  }
  return iVar1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08035ae0 */
undefined4 FUN_08035ae0(param_1)
undefined4 * param_1;
{
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = _DAT_0005c008;
    return 0;
  }
  return 2;
}




/* 0x08035af6 */
undefined4 FUN_08035af6(param_1, param_2)
int param_1; uint * param_2;
{
  if ((param_2 != (uint *)0x0) && (param_1 != 0)) {
    *param_2 = (uint)(*(int *)(param_1 * 4 + 0x5e030) << 0x19) >> 0x1f;
    return 0;
  }
  return 2;
}




/* 0x08035b48 */
int FUN_08035b48(param_1)
int * param_1;
{
  int iVar1;
  
  if (param_1 == (int *)0x0) {
    return 2;
  }
  if (DAT_0804d614 == 0xffff) {
    iVar1 = FUN_08035a1e(param_1);
    if (iVar1 == 0) {
      DAT_0804d614 = *param_1;
    }
    return iVar1;
  }
  *param_1 = DAT_0804d614;
  return 0;
}




/* 0x08035c40 */
int FUN_08035c40(param_1, param_2, param_3, param_4, param_5)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4; undefined4 param_5;
{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x24) = param_5;
    *(undefined4 *)(param_1 + 0x28) = param_2;
    *(undefined4 *)(param_1 + 0x2c) = param_3;
    *(undefined4 *)(param_1 + 0x30) = param_4;
    param_1 = param_1 + 0x34;
  }
  return param_1;
}




/* 0x08035c52 */
undefined4 FUN_08035c52(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; int param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (param_3 == 0) {
    FUN_08035c40(param_1,0,0,0,0x55d);
    return 2;
  }
  FUN_08006d14(param_3,0x40,param_3,param_4,param_4);
  if (*(char *)(param_1 + 0x68) == '\0') {
    iVar1 = FUN_08035a34(param_2,param_3);
    if (iVar1 == 0) goto LAB_08035c7a;
    uVar2 = 0x56b;
  }
  else {
    FUN_08006bdc(param_3,param_1 + 0x38,0x20);
LAB_08035c7a:
    iVar1 = FUN_08035962(param_2,param_3,param_3 + 0x20);
    if (iVar1 == 0) {
      iVar1 = FUN_08035af6(param_2,param_3 + 0x28);
      if (iVar1 == 0) {
        iVar1 = FUN_08035ae0(param_3 + 0x2c);
        if (iVar1 == 0) {
          iVar1 = FUN_080359a2(param_2,param_3 + 0x38,param_3 + 0x34,param_3 + 0x3c);
          if (iVar1 == 0) {
            return 0;
          }
          uVar2 = 0x596;
          param_2 = *(undefined4 *)(param_3 + 0x34);
          iVar1 = *(int *)(param_3 + 0x38);
          uVar3 = *(undefined4 *)(param_3 + 0x3c);
          goto LAB_08035d02;
        }
        uVar2 = 0x58b;
      }
      else {
        uVar2 = 0x583;
      }
    }
    else {
      uVar2 = 0x57b;
    }
  }
  uVar3 = 0;
LAB_08035d02:
  FUN_08035c40(param_1,iVar1,param_2,uVar3,uVar2);
  return 7;
}




/* 0x08035d10 */
undefined4 FUN_08035d10(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 local_2c [2];
  undefined4 local_24;
  undefined4 local_20;
  
  uVar3 = 0;
  uVar2 = 0;
  if ((((param_1 == 0) || (param_2 == 0)) || (param_3 == 0)) ||
     ((uVar4 = *(uint *)(param_2 + 0x378), uVar4 < 2 || (3 < uVar4)))) {
    FUN_08035c40(param_1,param_1,param_2,param_3,0x319);
    uVar3 = 2;
  }
  else {
    uVar4 = uVar4 - 1;
    local_20 = 0;
    local_2c[0] = 0x100;
    local_24 = 0;
    iVar1 = FUN_080291c0(param_2,local_2c);
    if (iVar1 == 0) {
      if (((*(int *)(param_2 + 0x378) == 3) &&
          (iVar1 = FUN_08006898(param_2 + 0x358,&DAT_0803ab10,0x20), iVar1 == 0)) &&
         ((*(int *)(param_2 + 0x224) == 2 &&
          (iVar1 = FUN_08006898(param_2 + 0x230,&DAT_0803aafc,0x14), iVar1 == 0)))) {
        uVar4 = 1;
      }
      for (; uVar2 < uVar4; uVar2 = uVar2 + 1) {
        iVar1 = FUN_08035df8(param_1,param_2,uVar2 + 1,uVar2);
        if (iVar1 != 0) {
          return 10;
        }
      }
      if (true) {
        iVar1 = FUN_08006898(param_2 + *(int *)(param_2 + 0x378) * 0x128 + -0x20,param_3,0x20);
        if (iVar1 == 0) {
          uVar3 = 0;
        }
        else {
          uVar3 = 0xb;
        }
      }
    }
    else {
      FUN_08035c40(param_1,iVar1,0,0,0x32d);
      uVar3 = 9;
    }
  }
  return uVar3;
}




/* 0x08035df8 */
undefined4 FUN_08035df8(param_1, param_2, param_3, param_4)
undefined4 param_1; int param_2; uint param_3; uint param_4;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int aiStack_a34 [5];
  int local_a20;
  int local_a1c;
  int local_a18;
  int local_a14;
  int local_a10;
  int local_a0c;
  int local_a08;
  int local_a04;
  int aiStack_938 [66];
  undefined1 auStack_830 [516];
  undefined1 auStack_62c [516];
  undefined1 auStack_428 [516];
  undefined1 auStack_224 [516];
  
  uVar4 = 1;
  if (((param_2 == 0) || (2 < param_3)) || (2 < param_4)) {
    FUN_08035c40(param_1);
    uVar4 = 2;
  }
  else {
    iVar5 = param_2 + param_3 * 0x128;
    uVar6 = *(uint *)(iVar5 + 0xec) * 8;
    if (uVar6 - 0x800 < 0x801) {
      iVar1 = FUN_0803700e(auStack_830,*(undefined4 *)(iVar5 + 0xf0),
                           *(uint *)(iVar5 + 0xec) & 0x1fffffff);
      if (iVar1 == 0) {
        iVar1 = FUN_08036080(*(undefined4 *)(iVar5 + 0xf8),*(undefined4 *)(iVar5 + 0xf4));
        if (iVar1 != 0) {
          FUN_08035c40(param_1,iVar1,param_3,param_4,0x1ad);
          return 3;
        }
        iVar1 = FUN_0803700e(auStack_62c,*(undefined4 *)(iVar5 + 0xf8),*(undefined4 *)(iVar5 + 0xf4)
                            );
        if (iVar1 == 0) {
          param_2 = param_2 + param_4 * 0x128;
          iVar1 = FUN_0803700e(auStack_428,*(undefined4 *)(param_2 + 0x100),
                               *(undefined4 *)(param_2 + 0x104));
          if (iVar1 == 0) {
            iVar5 = *(int *)(param_2 + 0xfc);
            if (iVar5 == 2) {
              iVar5 = 1;
            }
            else {
              if (iVar5 != 3) {
                FUN_08035c40(param_1,iVar5,param_3,param_4,0x1d4);
                return 4;
              }
              iVar5 = 2;
            }
            if (iVar5 == 1) {
              uVar4 = 0x14;
            }
            else if (iVar5 == 2) {
              uVar4 = 0x20;
            }
            else {
              uVar4 = 0;
            }
            iVar1 = FUN_0803700e(auStack_224,param_2 + 0x108,uVar4);
            if (iVar1 == 0) {
              FUN_08006d14(aiStack_a34,0x200);
              iVar1 = FUN_08036fb0(aiStack_a34,auStack_428,auStack_62c,auStack_830);
              if (iVar1 == 0) {
                if (iVar5 == 1) {
                  uVar4 = 0x14;
                }
                else if (iVar5 == 2) {
                  uVar4 = 0x20;
                }
                else {
                  uVar4 = 0;
                }
                iVar1 = FUN_08006898(auStack_224,aiStack_a34,uVar4);
                if (iVar1 == 0) {
                  if (iVar5 == 1) {
                    iVar1 = 0x14;
                    iVar2 = 0x10;
                  }
                  else {
                    if (iVar5 == 2) {
                      iVar1 = 0x20;
                    }
                    else {
                      iVar1 = 0;
                    }
                    iVar2 = 0x14;
                  }
                  uVar3 = (uVar6 >> 5) - 1;
                  for (uVar6 = (uint)(iVar1 + iVar2) >> 2; uVar6 < uVar3; uVar6 = uVar6 + 1) {
                    if (aiStack_a34[uVar6] != -1) {
                      uVar4 = 0x215;
                      local_a14 = aiStack_a34[uVar6];
                      goto LAB_08035fb6;
                    }
                  }
                  if (false) {
                    return 0;
                  }
                  if (aiStack_a34[uVar3] == 0x1ffff) {
                    if (iVar5 == 1) {
                      if (((local_a20 == 0x5000414) && (local_a1c == 0xe03021a)) &&
                         ((local_a18 == 0x906052b && (local_a14 == 0x302130)))) {
                        return 0;
                      }
                      uVar4 = 0x239;
                      local_a14 = local_a20;
                    }
                    else if (iVar5 == 2) {
                      if (((local_a14 == 0x5000420) && (local_a10 == 0x3040201)) &&
                         ((local_a0c == -0x79b7fe9b &&
                          ((local_a08 == 0xd060960 && (local_a04 == 0x303130)))))) {
                        return 0;
                      }
                      uVar4 = 0x248;
                    }
                    else {
                      uVar4 = 0x24f;
                      local_a14 = iVar5;
                    }
                  }
                  else {
                    uVar4 = 0x224;
                    local_a14 = aiStack_a34[uVar3];
                  }
                }
                else {
                  uVar4 = 0x259;
                  local_a14 = 0;
                }
LAB_08035fb6:
                FUN_08035c40(param_1,local_a14,param_3,param_4,uVar4);
                return 9;
              }
              uVar4 = 0x1ed;
            }
            else {
              uVar4 = 0x1e0;
            }
          }
          else {
            uVar4 = 0x1c5;
          }
        }
        else {
          uVar4 = 0x1b8;
        }
      }
      else {
        uVar4 = 0x1a0;
      }
      FUN_08035c40(param_1,iVar1,param_3,param_4,uVar4);
      uVar4 = 5;
    }
    else {
      FUN_08035c40(param_1,uVar6,param_3,param_4,0x195);
    }
  }
  return uVar4;
}




/* 0x08036080 */
undefined4 FUN_08036080(param_1, param_2)
int param_1; uint param_2;
{
  uint uVar1;
  
  uVar1 = 0;
  if ((param_2 != 0) && (param_1 != 0)) {
    for (; (uVar1 < param_2 && (*(char *)(param_1 + uVar1) == '\0')); uVar1 = uVar1 + 1) {
    }
    if (((uVar1 + 1 == param_2) && (*(char *)(param_1 + uVar1) == '\x03')) ||
       ((uVar1 + 3 == param_2 &&
        (((*(char *)(param_1 + uVar1) == '\x01' && (*(char *)(param_1 + uVar1 + 1) == '\0')) &&
         (*(char *)(param_1 + uVar1 + 2) == '\x01')))))) {
      return 0;
    }
  }
  return 1;
}




/* 0x080360c0 */
undefined4 FUN_080360c0(param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8, param_9, param_10)
int param_1; int param_2; undefined4 * param_3; undefined4 param_4; undefined4 param_5; undefined4 param_6; undefined4 param_7; undefined4 param_8; int param_9; undefined4 * param_10;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined1 *puVar6;
  undefined4 uVar7;
  undefined1 *puVar8;
  uint uVar9;
  int iVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  int local_ac0 [8];
  int local_aa0;
  undefined1 auStack_8bc [516];
  undefined1 auStack_6b8 [516];
  undefined1 auStack_4b4 [516];
  undefined1 auStack_2b0 [516];
  int local_ac;
  int local_a8;
  undefined1 auStack_a4 [32];
  undefined1 auStack_84 [32];
  undefined1 auStack_64 [32];
  byte local_44 [8];
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  
  local_ac = DAT_0804cd58;
  local_2c = DAT_0804cd58;
  FUN_08006d14(auStack_a4,0x20);
  FUN_08006d14(auStack_64,0x20);
  FUN_08006d14(auStack_84,0x20);
  local_30 = 0;
  iVar10 = 1;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_a8 = 0;
  if ((((param_1 == 0) || (param_2 == 0)) || (param_3 == (undefined4 *)0x0)) ||
     (param_10 == (undefined4 *)0x0)) {
    uVar11 = 0x3a0;
  }
  else {
    puVar4 = (undefined4 *)param_3[7];
    if ((((uint)puVar4 & 3) == 0) && (puVar4 == *(undefined4 **)(param_2 + 0xec))) {
      if (param_9 == 2) {
        iVar10 = 2;
      }
      iVar1 = FUN_08035680(param_1 + 4,iVar10,*param_3,param_3[1],param_3[2],param_3[3],auStack_a4,
                           0x20);
      if (iVar1 == 0) {
        *param_10 = param_3[2];
        param_10[1] = param_3[3];
        if (iVar10 == 1) {
          puVar4 = (undefined4 *)0x14;
        }
        else if (iVar10 == 2) {
          puVar4 = (undefined4 *)0x20;
        }
        else {
          puVar4 = (undefined4 *)0x0;
        }
        param_10[2] = puVar4;
        if ((undefined4 *)0x20 < puVar4) {
          param_3 = (undefined4 *)0x20;
          uVar11 = 0x3d3;
          param_2 = 2;
          param_10 = puVar4;
          goto LAB_08036156;
        }
        FUN_08006bdc(param_10 + 3,auStack_a4);
        local_44[0] = 0;
        local_44[1] = 0;
        local_44[2] = 0;
        local_44[3] = 0;
        local_44[4] = 0;
        local_44[5] = 0;
        local_44[6] = 0;
        local_44[7] = 0;
        local_34 = param_5;
        local_30 = param_6;
        uVar2 = 0;
        local_3c = param_7;
        local_38 = param_8;
        do {
          local_44[uVar2] = *(byte *)((int)&local_38 + (3 - uVar2)) ^ 0x36;
          uVar2 = uVar2 + 1;
        } while (uVar2 < 8);
        if (iVar10 == 1) {
          uVar11 = 0x14;
        }
        else if (iVar10 == 2) {
          uVar11 = 0x20;
        }
        else {
          uVar11 = 0;
        }
        iVar1 = FUN_08035680(param_1 + 4,iVar10,local_44,8,auStack_a4,uVar11,auStack_64,0x20);
        if (iVar1 == 0) {
          uVar2 = 0;
          local_44[0] = 0;
          local_44[1] = 0;
          local_44[2] = 0;
          local_44[3] = 0;
          local_44[4] = 0;
          local_44[5] = 0;
          local_44[6] = 0;
          local_44[7] = 0;
          do {
            local_44[uVar2] = *(byte *)((int)&local_30 + (3 - uVar2)) ^ 0x5c;
            uVar2 = uVar2 + 1;
          } while (uVar2 < 8);
          if (iVar10 == 1) {
            uVar11 = 0x14;
          }
          else if (iVar10 == 2) {
            uVar11 = 0x20;
          }
          else {
            uVar11 = 0;
          }
          iVar1 = FUN_08035680(param_1 + 4,iVar10,local_44,8,auStack_64,uVar11,auStack_84,0x20);
          if (iVar1 == 0) {
            uVar2 = *(uint *)(param_2 + 0xf0);
            if (((uVar2 == 0) || (uVar2 + *(uint *)(param_2 + 0xec) <= uVar2)) ||
               ((0x200 < *(uint *)(param_2 + 0xec) ||
                (((uVar2 = *(uint *)(param_2 + 0xf8), uVar2 == 0 ||
                  (uVar2 + *(uint *)(param_2 + 0xf4) <= uVar2)) || (4 < *(uint *)(param_2 + 0xf4))))
                ))) {
              uVar7 = 0;
              uVar11 = 3;
              uVar5 = 0;
              uVar12 = 0x421;
LAB_08036314:
              FUN_08035c40(param_1,uVar11,uVar5,uVar7,uVar12);
              uVar11 = 3;
            }
            else {
              iVar1 = FUN_0803700e(auStack_8bc);
              if (iVar1 == 0) {
                iVar1 = FUN_08036080(*(undefined4 *)(param_2 + 0xf8),*(undefined4 *)(param_2 + 0xf4)
                                    );
                if (iVar1 != 0) {
                  uVar12 = 0x439;
                  uVar7 = *(undefined4 *)(param_2 + 0xf4);
                  uVar5 = *(undefined4 *)(param_2 + 0xf8);
                  uVar11 = 0;
                  goto LAB_08036314;
                }
                iVar1 = FUN_0803700e(auStack_6b8,*(undefined4 *)(param_2 + 0xf8),
                                     *(undefined4 *)(param_2 + 0xf4));
                if (iVar1 == 0) {
                  iVar1 = FUN_0803700e(auStack_4b4,param_3[6],param_3[7]);
                  if (iVar1 == 0) {
                    if (iVar10 == 1) {
                      uVar11 = 0x14;
                    }
                    else if (iVar10 == 2) {
                      uVar11 = 0x20;
                    }
                    else {
                      uVar11 = 0;
                    }
                    iVar1 = FUN_0803700e(auStack_2b0,auStack_84,uVar11);
                    if (iVar1 == 0) {
                      FUN_08006d14(local_ac0,0x200);
                      iVar1 = FUN_08036fb0(local_ac0,auStack_4b4,auStack_6b8,auStack_8bc);
                      if (iVar1 == 0) {
                        if (iVar10 == 1) {
                          iVar1 = 0x14;
                        }
                        else if (iVar10 == 2) {
                          iVar1 = 0x20;
                        }
                        else {
                          iVar1 = 0;
                        }
                        if (*(int *)((int)local_ac0 + iVar1) == -0x100) {
                          if (iVar10 == 1) {
                            uVar2 = 0x14;
                          }
                          else if (iVar10 == 2) {
                            uVar2 = 0x20;
                          }
                          else {
                            uVar2 = 0;
                          }
                          uVar3 = (*(uint *)(param_2 + 0xec) >> 2) - 1;
                          uVar9 = (uVar2 >> 2) + 1;
                          for (uVar2 = uVar9; uVar2 < uVar3; uVar2 = uVar2 + 1) {
                            if (local_ac0[uVar2] != -1) goto LAB_08036422;
                          }
                          if (local_a8 == 0) {
                            local_aa0 = local_ac0[uVar3];
                            if (local_aa0 == 0x1ffff) {
                              if (iVar10 == 1) {
                                uVar11 = 0x14;
                              }
                              else if (iVar10 == 2) {
                                uVar11 = 0x20;
                              }
                              else {
                                uVar11 = 0;
                              }
                              iVar10 = FUN_08006898(auStack_2b0,local_ac0,uVar11);
                              if (iVar10 == 0) {
                                uVar11 = 0;
                                goto LAB_0803647a;
                              }
                              uVar9 = 0;
                              local_aa0 = 0xc;
                              uVar2 = 0;
                              uVar11 = 0x4a0;
                            }
                            else {
                              uVar11 = 0x491;
                              uVar2 = uVar3;
                            }
                          }
                          else {
LAB_08036422:
                            uVar11 = 0x489;
                            local_aa0 = local_ac0[uVar2];
                            uVar9 = uVar3;
                          }
                        }
                        else {
                          uVar11 = 0x476;
                          uVar2 = 0;
                          uVar9 = 0;
                        }
                        FUN_08035c40(param_1,local_aa0,uVar2,uVar9,uVar11);
                        uVar11 = 0xc;
                        goto LAB_0803647a;
                      }
                      puVar6 = (undefined1 *)0x0;
                      uVar11 = 0x467;
                      puVar8 = puVar6;
                    }
                    else {
                      puVar6 = auStack_84;
                      uVar11 = 0x45c;
                      puVar8 = (undefined1 *)0x20;
                    }
                  }
                  else {
                    uVar11 = 0x450;
                    puVar6 = (undefined1 *)param_3[6];
                    puVar8 = (undefined1 *)param_3[7];
                  }
                }
                else {
                  uVar11 = 0x445;
                  puVar6 = *(undefined1 **)(param_2 + 0xf8);
                  puVar8 = *(undefined1 **)(param_2 + 0xf4);
                }
              }
              else {
                uVar11 = 0x42c;
                puVar6 = *(undefined1 **)(param_2 + 0xf0);
                puVar8 = *(undefined1 **)(param_2 + 0xec);
              }
              FUN_08035c40(param_1,iVar1,puVar6,puVar8,uVar11);
              uVar11 = 5;
            }
            goto LAB_0803647a;
          }
          uVar11 = 0x40a;
        }
        else {
          uVar11 = 0x3f2;
        }
      }
      else {
        uVar11 = 0x3c5;
      }
      FUN_08035c40(param_1,iVar1,*param_3,param_3[2],uVar11);
      uVar11 = 6;
      goto LAB_0803647a;
    }
    uVar11 = 0x3b0;
    param_2 = *(int *)(param_2 + 0xec);
    param_3 = puVar4;
    param_10 = (undefined4 *)0x0;
  }
LAB_08036156:
  FUN_08035c40(param_1,param_2,param_3,param_10,uVar11);
  uVar11 = 2;
LAB_0803647a:
  if (local_2c != local_ac) {
    FUN_08010960();
  }
  return uVar11;
}




/* 0x0803649c */
void FUN_0803649c(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; int param_4;
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  FUN_0803650c();
  if (param_4 != 0) {
    iVar1 = 0;
    do {
      iVar2 = param_1 + iVar1 * 4;
      *(char *)(param_4 + iVar1 * 4) = (char)((uint)*(undefined4 *)(iVar2 + 8) >> 0x18);
      iVar3 = param_4 + iVar1 * 4;
      iVar1 = iVar1 + 1;
      *(char *)(iVar3 + 1) = (char)((uint)*(undefined4 *)(iVar2 + 8) >> 0x10);
      *(char *)(iVar3 + 2) = (char)((uint)*(undefined4 *)(iVar2 + 8) >> 8);
      *(char *)(iVar3 + 3) = (char)*(undefined4 *)(iVar2 + 8);
    } while (iVar1 < 8);
    FUN_080365b8(param_1 + 8,param_2);
    return;
  }
  return;
}




/* 0x080364e4 */
void FUN_080364e4(param_1)
undefined4 * param_1;
{
  if (param_1 != (undefined4 *)0x0) {
    FUN_080287e2(param_1,0,0x8c);
    FUN_08027bf8(param_1 + 2,0x20,&DAT_0803cad4);
    *param_1 = 0;
    param_1[1] = 0;
  }
  return;
}




/* 0x0803650c */
void FUN_0803650c(param_1, param_2, param_3, param_4)
int * param_1; undefined1 * param_2; undefined4 param_3; undefined4 param_4;
{
  uint uVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined4 local_20;
  undefined4 uStack_1c;
  
  local_20 = param_3;
  uStack_1c = param_4;
  FUN_08027bf8(&local_20,8,param_1);
  uVar1 = (uint)(*param_1 << 0x17) >> 0x1a;
  if (uVar1 == 0) {
    FUN_080287e2(param_2,0,0x38);
    *param_2 = 0x80;
  }
  else {
    param_2[uVar1] = 0x80;
    uVar1 = uVar1 + 1;
    if (uVar1 < 0x39) {
      iVar3 = 0x38 - uVar1;
      puVar2 = param_2 + uVar1;
    }
    else {
      if (uVar1 < 0x40) {
        FUN_080287e2(param_2 + uVar1,0,0x40 - uVar1);
      }
      FUN_080365b8(param_1 + 2,param_2);
      iVar3 = 0x38;
      puVar2 = param_2;
    }
    FUN_080287e2(puVar2,0,iVar3);
  }
  param_2[0x38] = (char)((uint)uStack_1c >> 0x18);
  param_2[0x39] = (char)((uint)uStack_1c >> 0x10);
  param_2[0x3a] = (char)((uint)uStack_1c >> 8);
  param_2[0x3b] = (char)uStack_1c;
  param_2[0x3c] = (char)((uint)local_20 >> 0x18);
  param_2[0x3d] = (char)((uint)local_20 >> 0x10);
  param_2[0x3e] = (char)((uint)local_20 >> 8);
  param_2[0x3f] = (char)local_20;
  FUN_080365b8(param_1 + 2,param_2);
  FUN_08027bf8(param_1,8,&local_20);
  return;
}




/* 0x080365b8 */
void FUN_080365b8(param_1, param_2)
uint * param_1; byte * param_2;
{
  ushort *puVar1;
  byte *pbVar2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint local_a4 [16];
  uint local_64;
  uint local_60;
  uint local_5c;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint *local_2c;
  byte *pbStack_28;
  
  pbStack_28 = param_2;
  local_2c = param_1;
  uVar15 = 0;
  local_54 = *param_1;
  local_48 = local_54;
  uVar5 = param_1[1];
  local_44 = uVar5;
  uVar6 = param_1[2];
  local_40 = uVar6;
  uVar7 = param_1[3];
  local_3c = uVar7;
  uVar14 = param_1[4];
  local_38 = uVar14;
  local_60 = param_1[5];
  local_4c = local_60;
  uVar13 = param_1[6];
  local_34 = uVar13;
  uVar17 = param_1[7];
  local_30 = uVar17;
  do {
    uVar10 = (*(ushort *)(param_2 + 2) & 0xff) << 8 | (uint)(*(ushort *)(param_2 + 2) >> 8) |
             (uint)param_2[1] << 0x10 | (uint)*param_2 << 0x18;
    local_a4[uVar15] = uVar10;
    iVar9 = (&DAT_0803c9d4)[uVar15] + uVar17 +
            ((uVar14 >> 6 | uVar14 << 0x1a) ^ (uVar14 >> 0xb | uVar14 << 0x15) ^
            (uVar14 >> 0x19 | uVar14 << 7)) + (uVar14 & local_60 ^ uVar13 & ~uVar14) + uVar10;
    local_58 = uVar7 + iVar9;
    uVar17 = ((local_54 >> 2 | local_54 << 0x1e) ^ (local_54 >> 0xd | local_54 << 0x13) ^
             (local_54 >> 0x16 | local_54 << 10)) + iVar9 +
             ((uVar5 ^ uVar6) & local_54 ^ uVar5 & uVar6);
    uVar7 = (*(ushort *)(param_2 + 6) & 0xff) << 8 | (uint)(*(ushort *)(param_2 + 6) >> 8) |
            (uint)param_2[5] << 0x10 | (uint)param_2[4] << 0x18;
    local_a4[uVar15 + 1] = uVar7;
    iVar9 = (&DAT_0803c9d4)[uVar15 + 1] + uVar13 +
            ((local_58 >> 6 | local_58 * 0x4000000) ^ (local_58 >> 0xb | local_58 * 0x200000) ^
            (local_58 >> 0x19 | local_58 * 0x80)) + (local_58 & uVar14 ^ local_60 & ~local_58) +
            uVar7;
    local_5c = uVar6 + iVar9;
    uVar13 = iVar9 + ((uVar17 >> 2 | uVar17 * 0x40000000) ^ (uVar17 >> 0xd | uVar17 * 0x80000) ^
                     (uVar17 >> 0x16 | uVar17 * 0x400)) +
             ((local_54 ^ uVar5) & uVar17 ^ local_54 & uVar5);
    uVar7 = (*(ushort *)(param_2 + 10) & 0xff) << 8 | (uint)(*(ushort *)(param_2 + 10) >> 8) |
            (uint)param_2[9] << 0x10 | (uint)param_2[8] << 0x18;
    local_a4[uVar15 + 2] = uVar7;
    iVar9 = uVar7 + (&DAT_0803c9d4)[uVar15 + 2] + local_60 +
                    ((local_5c >> 6 | local_5c * 0x4000000) ^
                     (local_5c >> 0xb | local_5c * 0x200000) ^ (local_5c >> 0x19 | local_5c * 0x80))
                    + (local_58 & local_5c ^ uVar14 & ~local_5c);
    local_60 = uVar5 + iVar9;
    uVar10 = ((uVar17 ^ local_54) & uVar13 ^ uVar17 & local_54) +
             ((uVar13 >> 2 | uVar13 * 0x40000000) ^ (uVar13 >> 0xd | uVar13 * 0x80000) ^
             (uVar13 >> 0x16 | uVar13 * 0x400)) + iVar9;
    uVar7 = (*(ushort *)(param_2 + 0xe) & 0xff) << 8 | (uint)(*(ushort *)(param_2 + 0xe) >> 8) |
            (uint)param_2[0xd] << 0x10 | (uint)param_2[0xc] << 0x18;
    local_a4[uVar15 + 3] = uVar7;
    iVar9 = (&DAT_0803c9d4)[uVar15 + 3] + uVar14 +
            ((local_60 >> 6 | local_60 << 0x1a) ^ (local_60 >> 0xb | local_60 << 0x15) ^
            (local_60 >> 0x19 | local_60 << 7)) + (local_60 & local_5c ^ local_58 & ~local_60) +
            uVar7;
    local_54 = local_54 + iVar9;
    uVar14 = ((uVar10 >> 2 | uVar10 * 0x40000000) ^ (uVar10 >> 0xd | uVar10 * 0x80000) ^
             (uVar10 >> 0x16 | uVar10 * 0x400)) + iVar9 +
             ((uVar13 ^ uVar17) & uVar10 ^ uVar13 & uVar17);
    uVar7 = (*(ushort *)(param_2 + 0x12) & 0xff) << 8 | (uint)(*(ushort *)(param_2 + 0x12) >> 8) |
            (uint)param_2[0x11] << 0x10 | (uint)param_2[0x10] << 0x18;
    local_a4[uVar15 + 4] = uVar7;
    iVar9 = (&DAT_0803c9d4)[uVar15 + 4] + local_58 +
            ((local_54 >> 6 | local_54 * 0x4000000) ^ (local_54 >> 0xb | local_54 * 0x200000) ^
            (local_54 >> 0x19 | local_54 * 0x80)) + (local_54 & local_60 ^ local_5c & ~local_54) +
            uVar7;
    uVar17 = uVar17 + iVar9;
    uVar7 = iVar9 + ((uVar14 >> 2 | uVar14 * 0x40000000) ^ (uVar14 >> 0xd | uVar14 * 0x80000) ^
                    (uVar14 >> 0x16 | uVar14 * 0x400)) +
            ((uVar10 ^ uVar13) & uVar14 ^ uVar10 & uVar13);
    uVar5 = (*(ushort *)(param_2 + 0x16) & 0xff) << 8 | (uint)(*(ushort *)(param_2 + 0x16) >> 8) |
            (uint)param_2[0x15] << 0x10 | (uint)param_2[0x14] << 0x18;
    local_a4[uVar15 + 5] = uVar5;
    iVar11 = uVar15 + 6;
    iVar9 = ((uVar17 >> 6 | uVar17 * 0x4000000) ^ (uVar17 >> 0xb | uVar17 * 0x200000) ^
            (uVar17 >> 0x19 | uVar17 * 0x80)) + (uVar17 & local_54 ^ local_60 & ~uVar17) +
            (&DAT_0803c9d4)[uVar15 + 5] + local_5c + uVar5;
    uVar13 = uVar13 + iVar9;
    uVar6 = iVar9 + ((uVar7 >> 2 | uVar7 * 0x40000000) ^ (uVar7 >> 0xd | uVar7 * 0x80000) ^
                    (uVar7 >> 0x16 | uVar7 * 0x400)) + ((uVar14 ^ uVar10) & uVar7 ^ uVar14 & uVar10)
    ;
    uVar5 = (*(ushort *)(param_2 + 0x1a) & 0xff) << 8 | (uint)(*(ushort *)(param_2 + 0x1a) >> 8) |
            (uint)param_2[0x19] << 0x10 | (uint)param_2[0x18] << 0x18;
    local_a4[iVar11] = uVar5;
    iVar12 = uVar15 + 7;
    uVar15 = uVar15 + 8;
    iVar9 = uVar5 + ((uVar13 >> 6 | uVar13 * 0x4000000) ^ (uVar13 >> 0xb | uVar13 * 0x200000) ^
                    (uVar13 >> 0x19 | uVar13 * 0x80)) + (uVar13 & uVar17 ^ local_54 & ~uVar13) +
                    (&DAT_0803c9d4)[iVar11] + local_60;
    local_60 = uVar10 + iVar9;
    puVar1 = (ushort *)(param_2 + 0x1e);
    uVar5 = ((uVar6 >> 2 | uVar6 * 0x40000000) ^ (uVar6 >> 0xd | uVar6 * 0x80000) ^
            (uVar6 >> 0x16 | uVar6 * 0x400)) + iVar9 + ((uVar7 ^ uVar14) & uVar6 ^ uVar7 & uVar14);
    pbVar2 = param_2 + 0x1d;
    pbVar3 = param_2 + 0x1c;
    param_2 = param_2 + 0x20;
    uVar10 = (*puVar1 & 0xff) << 8 | (uint)(*puVar1 >> 8) | (uint)*pbVar2 << 0x10 |
             (uint)*pbVar3 << 0x18;
    local_a4[iVar12] = uVar10;
    iVar9 = uVar10 + local_54 + (&DAT_0803c9d4)[iVar12] +
                     ((local_60 >> 6 | local_60 << 0x1a) ^ (local_60 >> 0xb | local_60 << 0x15) ^
                     (local_60 >> 0x19 | local_60 << 7)) + (local_60 & uVar13 ^ uVar17 & ~local_60);
    uVar14 = uVar14 + iVar9;
    local_54 = ((uVar6 ^ uVar7) & uVar5 ^ uVar6 & uVar7) +
               ((uVar5 >> 2 | uVar5 * 0x40000000) ^ (uVar5 >> 0xd | uVar5 * 0x80000) ^
               (uVar5 >> 0x16 | uVar5 * 0x400)) + iVar9;
  } while ((int)uVar15 < 0x10);
  do {
    uVar10 = local_a4[uVar15 + 1 & 0xf];
    uVar4 = local_a4[uVar15 - 2 & 0xf];
    uVar16 = uVar15 + 1;
    uVar10 = local_a4[uVar15 - 7 & 0xf] + local_a4[uVar15 & 0xf] +
             ((uVar4 >> 0x11 | uVar4 << 0xf) ^ (uVar4 >> 0x13 | uVar4 << 0xd) ^ uVar4 >> 10) +
             ((uVar10 >> 7 | uVar10 << 0x19) ^ (uVar10 >> 0x12 | uVar10 << 0xe) ^ uVar10 >> 3);
    iVar9 = ((uVar14 >> 6 | uVar14 << 0x1a) ^ (uVar14 >> 0xb | uVar14 << 0x15) ^
            (uVar14 >> 0x19 | uVar14 << 7)) + (uVar14 & local_60 ^ uVar13 & ~uVar14) +
            (&DAT_0803c9d4)[uVar15] + uVar17 + uVar10;
    local_a4[uVar15 & 0xf] = uVar10;
    uVar7 = uVar7 + iVar9;
    local_58 = uVar7;
    local_64 = uVar16;
    uVar17 = ((local_54 >> 2 | local_54 << 0x1e) ^ (local_54 >> 0xd | local_54 << 0x13) ^
             (local_54 >> 0x16 | local_54 << 10)) + iVar9 +
             ((uVar5 ^ uVar6) & local_54 ^ uVar5 & uVar6);
    uVar10 = local_a4[uVar15 + 2 & 0xf];
    uVar4 = local_a4[uVar15 - 1 & 0xf];
    uVar8 = local_60 & ~uVar7;
    iVar9 = (&DAT_0803c9d4)[uVar16];
    uVar10 = local_a4[uVar15 - 6 & 0xf] + local_a4[uVar16 & 0xf] +
             ((uVar4 >> 0x11 | uVar4 << 0xf) ^ (uVar4 >> 0x13 | uVar4 << 0xd) ^ uVar4 >> 10) +
             ((uVar10 >> 7 | uVar10 << 0x19) ^ (uVar10 >> 0x12 | uVar10 << 0xe) ^ uVar10 >> 3);
    local_a4[uVar16 & 0xf] = uVar10;
    uVar15 = local_64;
    iVar9 = uVar10 + ((uVar7 >> 6 | uVar7 * 0x4000000) ^ (uVar7 >> 0xb | uVar7 * 0x200000) ^
                     (uVar7 >> 0x19 | uVar7 * 0x80)) + (uVar7 & uVar14 ^ uVar8) + iVar9 + uVar13;
    uVar6 = uVar6 + iVar9;
    local_5c = uVar6;
    uVar13 = ((uVar17 >> 2 | uVar17 * 0x40000000) ^ (uVar17 >> 0xd | uVar17 * 0x80000) ^
             (uVar17 >> 0x16 | uVar17 * 0x400)) + iVar9 +
             ((local_54 ^ uVar5) & uVar17 ^ local_54 & uVar5);
    uVar7 = local_64 + 2;
    local_64 = local_64 + 1;
    uVar7 = local_a4[uVar7 & 0xf];
    uVar10 = local_a4[uVar15 - 1 & 0xf];
    uVar4 = local_58 & uVar6;
    iVar9 = (&DAT_0803c9d4)[local_64];
    uVar15 = local_a4[uVar15 - 6 & 0xf] + local_a4[local_64 & 0xf] +
             ((uVar10 >> 0x11 | uVar10 << 0xf) ^ (uVar10 >> 0x13 | uVar10 << 0xd) ^ uVar10 >> 10) +
             ((uVar7 >> 7 | uVar7 << 0x19) ^ (uVar7 >> 0x12 | uVar7 << 0xe) ^ uVar7 >> 3);
    local_a4[local_64 & 0xf] = uVar15;
    uVar7 = local_64;
    iVar9 = uVar15 + ((uVar6 >> 6 | uVar6 * 0x4000000) ^ (uVar6 >> 0xb | uVar6 * 0x200000) ^
                     (uVar6 >> 0x19 | uVar6 * 0x80)) + (uVar4 ^ uVar14 & ~uVar6) + iVar9 + local_60;
    uVar5 = uVar5 + iVar9;
    local_60 = uVar5;
    uVar8 = iVar9 + ((uVar13 >> 2 | uVar13 * 0x40000000) ^ (uVar13 >> 0xd | uVar13 * 0x80000) ^
                    (uVar13 >> 0x16 | uVar13 * 0x400)) +
            ((uVar17 ^ local_54) & uVar13 ^ uVar17 & local_54);
    uVar6 = local_64 + 2;
    local_64 = local_64 + 1;
    uVar6 = local_a4[uVar6 & 0xf];
    uVar15 = local_a4[uVar7 - 1 & 0xf];
    uVar4 = uVar5 & local_5c;
    uVar10 = local_58 & ~uVar5;
    iVar9 = (&DAT_0803c9d4)[local_64];
    uVar7 = local_a4[uVar7 - 6 & 0xf] + local_a4[local_64 & 0xf] +
            ((uVar15 >> 0x11 | uVar15 << 0xf) ^ (uVar15 >> 0x13 | uVar15 << 0xd) ^ uVar15 >> 10) +
            ((uVar6 >> 7 | uVar6 << 0x19) ^ (uVar6 >> 0x12 | uVar6 << 0xe) ^ uVar6 >> 3);
    local_a4[local_64 & 0xf] = uVar7;
    uVar6 = local_64;
    iVar9 = uVar7 + (uVar4 ^ uVar10) +
                    ((uVar5 >> 6 | uVar5 * 0x4000000) ^ (uVar5 >> 0xb | uVar5 * 0x200000) ^
                    (uVar5 >> 0x19 | uVar5 * 0x80)) + iVar9 + uVar14;
    uVar10 = local_54 + iVar9;
    local_54 = uVar10;
    local_50 = ((uVar8 >> 2 | uVar8 * 0x40000000) ^ (uVar8 >> 0xd | uVar8 * 0x80000) ^
               (uVar8 >> 0x16 | uVar8 * 0x400)) + iVar9 +
               ((uVar13 ^ uVar17) & uVar8 ^ uVar13 & uVar17);
    uVar7 = local_a4[local_64 + 2 & 0xf];
    uVar5 = local_a4[local_64 - 1 & 0xf];
    uVar4 = uVar10 & local_60;
    uVar15 = local_5c & ~uVar10;
    iVar9 = (&DAT_0803c9d4)[local_64 + 1];
    uVar14 = local_64 + 1 & 0xf;
    uVar16 = local_64 + 2;
    uVar7 = ((uVar5 >> 0x11 | uVar5 << 0xf) ^ (uVar5 >> 0x13 | uVar5 << 0xd) ^ uVar5 >> 10) +
            ((uVar7 >> 7 | uVar7 << 0x19) ^ (uVar7 >> 0x12 | uVar7 << 0xe) ^ uVar7 >> 3) +
            local_a4[local_64 - 6 & 0xf] + local_a4[uVar14];
    local_a4[uVar14] = uVar7;
    iVar9 = uVar7 + local_58 + iVar9 +
                    ((uVar10 >> 6 | uVar10 * 0x4000000) ^ (uVar10 >> 0xb | uVar10 * 0x200000) ^
                    (uVar10 >> 0x19 | uVar10 * 0x80)) + (uVar4 ^ uVar15);
    uVar17 = uVar17 + iVar9;
    local_64 = uVar16;
    uVar7 = iVar9 + ((local_50 >> 2 | local_50 << 0x1e) ^ (local_50 >> 0xd | local_50 << 0x13) ^
                    (local_50 >> 0x16 | local_50 << 10)) +
            ((uVar8 ^ uVar13) & local_50 ^ uVar8 & uVar13);
    uVar5 = local_a4[uVar6 + 3 & 0xf];
    uVar10 = uVar17 & local_54;
    uVar14 = local_a4[uVar6 & 0xf];
    uVar15 = local_60 & ~uVar17;
    iVar9 = (&DAT_0803c9d4)[uVar16];
    uVar6 = ((uVar14 >> 0x11 | uVar14 << 0xf) ^ (uVar14 >> 0x13 | uVar14 << 0xd) ^ uVar14 >> 10) +
            ((uVar5 >> 7 | uVar5 << 0x19) ^ (uVar5 >> 0x12 | uVar5 << 0xe) ^ uVar5 >> 3) +
            local_a4[uVar6 - 5 & 0xf] + local_a4[uVar16 & 0xf];
    local_a4[uVar16 & 0xf] = uVar6;
    uVar5 = local_64;
    iVar9 = uVar6 + ((uVar17 >> 6 | uVar17 * 0x4000000) ^ (uVar17 >> 0xb | uVar17 * 0x200000) ^
                    (uVar17 >> 0x19 | uVar17 * 0x80)) + (uVar10 ^ uVar15) + local_5c + iVar9;
    uVar13 = uVar13 + iVar9;
    local_64 = local_64 + 1;
    uVar6 = ((uVar7 >> 2 | uVar7 * 0x40000000) ^ (uVar7 >> 0xd | uVar7 * 0x80000) ^
            (uVar7 >> 0x16 | uVar7 * 0x400)) + iVar9 +
            ((local_50 ^ uVar8) & uVar7 ^ local_50 & uVar8);
    uVar14 = local_a4[uVar5 + 2 & 0xf];
    uVar15 = local_a4[uVar5 - 1 & 0xf];
    iVar9 = (&DAT_0803c9d4)[local_64];
    uVar10 = local_54 & ~uVar13;
    uVar5 = ((uVar15 >> 0x11 | uVar15 << 0xf) ^ (uVar15 >> 0x13 | uVar15 << 0xd) ^ uVar15 >> 10) +
            ((uVar14 >> 7 | uVar14 << 0x19) ^ (uVar14 >> 0x12 | uVar14 << 0xe) ^ uVar14 >> 3) +
            local_a4[uVar5 - 6 & 0xf] + local_a4[local_64 & 0xf];
    local_a4[local_64 & 0xf] = uVar5;
    uVar14 = local_64;
    iVar9 = uVar5 + local_60 + iVar9 +
                    ((uVar13 >> 6 | uVar13 * 0x4000000) ^ (uVar13 >> 0xb | uVar13 * 0x200000) ^
                    (uVar13 >> 0x19 | uVar13 * 0x80)) + (uVar13 & uVar17 ^ uVar10);
    uVar8 = uVar8 + iVar9;
    local_60 = uVar8;
    local_64 = local_64 + 1;
    uVar5 = ((uVar6 >> 2 | uVar6 * 0x40000000) ^ (uVar6 >> 0xd | uVar6 * 0x80000) ^
            (uVar6 >> 0x16 | uVar6 * 0x400)) + iVar9 +
            ((uVar7 ^ local_50) & uVar6 ^ local_50 & uVar7);
    uVar15 = local_a4[uVar14 + 2 & 0xf];
    uVar10 = local_a4[uVar14 - 1 & 0xf];
    iVar9 = (&DAT_0803c9d4)[local_64];
    uVar14 = ((uVar10 >> 0x11 | uVar10 << 0xf) ^ (uVar10 >> 0x13 | uVar10 << 0xd) ^ uVar10 >> 10) +
             ((uVar15 >> 7 | uVar15 << 0x19) ^ (uVar15 >> 0x12 | uVar15 << 0xe) ^ uVar15 >> 3) +
             local_a4[uVar14 - 6 & 0xf] + local_a4[local_64 & 0xf];
    local_a4[local_64 & 0xf] = uVar14;
    iVar9 = uVar14 + local_54 + iVar9 +
                     (uVar8 & uVar13 ^ uVar17 & ~uVar8) +
                     ((uVar8 >> 6 | uVar8 * 0x4000000) ^ (uVar8 >> 0xb | uVar8 * 0x200000) ^
                     (uVar8 >> 0x19 | uVar8 * 0x80));
    uVar14 = local_50 + iVar9;
    uVar15 = local_64 + 1;
    local_54 = ((uVar6 ^ uVar7) & uVar5 ^ uVar6 & uVar7) +
               ((uVar5 >> 2 | uVar5 * 0x40000000) ^ (uVar5 >> 0xd | uVar5 * 0x80000) ^
               (uVar5 >> 0x16 | uVar5 * 0x400)) + iVar9;
  } while ((int)uVar15 < 0x40);
  *local_2c = local_48 + local_54;
  local_2c[1] = local_44 + uVar5;
  local_2c[2] = local_40 + uVar6;
  local_2c[3] = local_3c + uVar7;
  local_2c[4] = local_38 + uVar14;
  local_2c[5] = local_60 + local_4c;
  local_2c[6] = local_34 + uVar13;
  local_2c[7] = local_30 + uVar17;
  return;
}




/* 0x08036ee8 */
void FUN_08036ee8(param_1, param_2, param_3, param_4, param_5)
int param_1; int param_2; uint param_3; int param_4; uint param_5;
{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  uint local_28;
  int iStack_24;
  
  if (param_5 == 0) {
    return;
  }
  local_28 = param_3;
  iStack_24 = param_4;
  FUN_08027bf8(&local_28,8,param_1);
  uVar1 = (local_28 << 0x17) >> 0x1a;
  if (uVar1 != 0) {
    uVar2 = 0x40 - uVar1;
    if (param_5 < uVar2) {
      FUN_08027bf8(uVar1 + param_2,uVar2,param_4,param_5);
      bVar3 = CARRY4(param_5 * 8,local_28);
      local_28 = param_5 * 8 + local_28;
      iStack_24 = iStack_24 + (uint)bVar3;
      goto LAB_08036fa4;
    }
    FUN_08027bf8(uVar1 + param_2,uVar2,param_4,uVar2);
    bVar3 = CARRY4(uVar2 * 8,local_28);
    local_28 = uVar2 * 8 + local_28;
    iStack_24 = iStack_24 + (uint)bVar3;
    param_5 = param_5 - uVar2;
    param_4 = param_4 + uVar2;
    FUN_080365b8(param_1 + 8,param_2);
  }
  for (; 0x3f < param_5; param_5 = param_5 - 0x40) {
    FUN_080365b8(param_1 + 8,param_4);
    bVar3 = 0xfffffdff < local_28;
    local_28 = local_28 + 0x200;
    iStack_24 = iStack_24 + (uint)bVar3;
    param_4 = param_4 + 0x40;
  }
  if (param_5 != 0) {
    FUN_08027bf8(param_2,0x40,param_4,param_5);
    bVar3 = CARRY4(param_5 * 8,local_28);
    local_28 = param_5 * 8 + local_28;
    iStack_24 = iStack_24 + (uint)bVar3;
  }
LAB_08036fa4:
  FUN_08027bf8(param_1,8,&local_28,8);
  return;
}




/* 0x08036fb0 */
bool FUN_08036fb0(param_1, param_2, param_3, param_4)
int param_1; int param_2; undefined4 param_3; int param_4;
{
  int iVar1;
  undefined1 auStack_824 [512];
  undefined1 auStack_624 [512];
  undefined1 auStack_424 [512];
  undefined1 auStack_224 [512];
  undefined1 *local_24;
  undefined1 *local_20;
  undefined1 *local_1c;
  undefined1 *local_18;
  
  local_24 = auStack_824;
  local_20 = auStack_624;
  local_1c = auStack_424;
  local_18 = auStack_224;
  for (iVar1 = *(int *)(param_2 + 0x200); iVar1 < *(int *)(param_4 + 0x200); iVar1 = iVar1 + 1) {
    *(undefined4 *)(param_2 + iVar1 * 4) = 0;
  }
  *(int *)(param_1 + 0x200) = *(int *)(param_4 + 0x200);
  iVar1 = FUN_08027d0c();
  return iVar1 != 0;
}




/* 0x0803700e */
undefined4 FUN_0803700e(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar5 = 0;
  if (((param_1 == 0) || (param_2 == 0)) || (param_3 == 0)) {
    uVar2 = 6;
  }
  else if (param_3 < 0x201) {
    FUN_08006d14();
    uVar1 = param_3;
    while (uVar1 = uVar1 - 1, -1 < (int)uVar1) {
      uVar3 = uVar5 << 0x1e;
      uVar4 = uVar5 & 0xfffffffc;
      uVar5 = uVar5 + 1;
      *(uint *)(param_1 + uVar4) =
           (uint)*(byte *)(param_2 + uVar1) << (uVar3 >> 0x1b) | *(uint *)(param_1 + uVar4);
    }
    uVar5 = param_3 + 3 >> 2;
    while ((*(uint *)(param_1 + 0x200) = uVar5, 1 < (int)uVar5 &&
           (*(int *)(param_1 + uVar5 * 4 + -4) == 0))) {
      uVar5 = uVar5 - 1;
    }
    uVar2 = 0;
  }
  else {
    uVar2 = 4;
  }
  return uVar2;
}




/* 0x0803707c */
undefined4 handle_response(param_1)
undefined4 param_1;
{
  FUN_08037084(param_1,0);
  return 0;
}




/* 0x08037084 */
undefined4 FUN_08037084(param_1, param_2, param_3, param_4)
int param_1; int param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined *puVar4;
  uint *puVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined1 auStack_130 [256];
  int local_30;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  iVar1 = DAT_0804cd58;
  local_30 = DAT_0804cd58;
  uStack_8 = param_3;
  uStack_4 = param_4;
  FUN_08006d14(auStack_130,0x100);
  uVar2 = FUN_08006906("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>");
  FUN_080391f0(&DAT_08055f18,"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>",uVar2,0);
  FUN_08039100(&DAT_08055f18,&DAT_08037180);
  FUN_080390f4(&DAT_08055f18,"response");
  if (param_1 == 1) {
    puVar4 = &DAT_080371a0;
  }
  else {
    puVar4 = &DAT_08037194;
  }
  FUN_08039174(&DAT_08055f18,"value",puVar4);
  iVar7 = 0;
  puVar6 = &uStack_8;
  do {
    if (param_2 <= iVar7) {
      FUN_080390d8(&DAT_08055f18);
      FUN_080390e4(&DAT_08055f18,&DAT_08037180);
      FUN_080371b8();
      uVar2 = 0;
LAB_0803715c:
      if (local_30 != iVar1) {
        FUN_08010960();
      }
      return uVar2;
    }
    puVar5 = puVar6 + 2;
    uVar2 = *puVar6;
    uVar3 = puVar6[1] & 0xff;
    if (uVar3 != 99) {
      if (uVar3 == 100) {
        uVar3 = *puVar5;
        puVar4 = &DAT_080371a8;
        goto LAB_080370fe;
      }
      if (uVar3 == 0x73) {
        uVar3 = *puVar5;
        puVar4 = &DAT_080371a4;
        goto LAB_080370fe;
      }
      if (uVar3 == 0x74) {
        puVar6 = (undefined4 *)(((int)puVar6 + 0xfU & 0xfffffff8) + 8);
        uVar3 = snprintf_buf(auStack_130,0x100,&DAT_080371ac);
        goto LAB_08037120;
      }
LAB_08037124:
      uVar2 = 1;
      goto LAB_0803715c;
    }
    puVar4 = &DAT_080371b4;
    uVar3 = *puVar5 & 0xff;
LAB_080370fe:
    puVar6 = puVar6 + 3;
    uVar3 = snprintf_buf(auStack_130,0x100,puVar4,uVar3);
LAB_08037120:
    if (0xff < uVar3) goto LAB_08037124;
    FUN_0803918c(&DAT_08055f18,uVar2,auStack_130);
    iVar7 = iVar7 + 1;
  } while( true );
}




/* 0x080371b8 */
undefined4 FUN_080371b8(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  undefined4 uVar1;
  
  uVar1 = FUN_08038c24(DAT_08055f18,param_2,DAT_08055f28,DAT_08055f2c);
  FUN_08039234(&DAT_08055f18);
  return uVar1;
}




/* 0x080371d8 */
void FUN_080371d8(param_1, param_2, param_3)
int param_1; uint param_2; code * param_3;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined1 auStack_38 [8];
  int iStack_30;
  uint local_2c;
  code *pcStack_28;
  
  uVar6 = 0;
  iStack_30 = param_1;
  local_2c = param_2;
  pcStack_28 = param_3;
  do {
    uVar5 = (uint)(byte)(&DAT_080396d0)[uVar6];
    for (uVar4 = uVar5; uVar4 < local_2c; uVar4 = uVar4 + 1) {
      FUN_08006a30(auStack_38,param_1 + uVar4 * 6,6);
      uVar3 = uVar4;
      while (uVar5 <= uVar3) {
        iVar1 = param_1 + (uVar3 - uVar5) * 6;
        iVar2 = (*param_3)(iVar1,auStack_38);
        if (iVar2 == 0) break;
        FUN_08006a30(param_1 + uVar3 * 6,iVar1,6);
        uVar3 = uVar3 - uVar5;
      }
      FUN_08006a30(param_1 + uVar3 * 6,auStack_38,6);
    }
    uVar6 = uVar6 + 1;
    if (4 < uVar6) {
      return;
    }
  } while( true );
}




/* 0x0803725c */
undefined4 FUN_0803725c(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  if (((param_1 != 0) && (param_2 != 0)) && (param_3 != 0)) {
    iVar1 = FUN_08006906();
    uVar2 = FUN_08006906(param_2);
    uVar3 = FUN_08006906(param_3);
    if (uVar3 <= uVar2) {
      iVar4 = param_1 + iVar1;
      while (param_1 = FUN_08006874(param_1,param_2), param_1 != 0) {
        FUN_08027bf8(param_1,iVar1,param_3,uVar3);
        param_1 = param_1 + uVar3;
        FUN_08027c12(param_1,iVar1,(uVar2 - uVar3) + param_1,iVar4 - param_1);
      }
      return 1;
    }
  }
  return 0;
}




/* 0x080372d0 */
undefined1 FUN_080372d0(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  undefined1 uVar1;
  int iVar2;
  undefined4 **local_58;
  undefined4 uStack_54;
  uint local_50;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined4 *local_48;
  undefined4 uStack_44;
  uint local_40;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined4 *local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  undefined1 *local_28;
  undefined4 local_24;
  undefined1 auStack_20 [12];
  undefined4 uStack_14;
  undefined4 uStack_10;
  
  local_38 = &uStack_14;
  local_28 = (undefined1 *)&local_58;
  uVar1 = 0;
  if (DAT_080508f0 != '\0') {
    local_34 = 1;
    local_58 = &local_38;
    local_2c = 1;
    uStack_54 = 1;
    local_50 = (uint)*(byte *)*(uint*)DAT_080508f8;
    local_48 = &uStack_30;
    local_4c = 1;
    uStack_44 = 1;
    local_4b = 1;
    local_40 = (uint)*(byte *)*(uint*)DAT_080508f8;
    local_3c = 0;
    local_3b = 3;
    local_24 = 2;
    uStack_30 = param_2;
    uStack_14 = param_1;
    uStack_10 = param_2;
    iVar2 = FUN_0800cd1c(DAT_080508f4,&local_28,&DAT_080508fc,auStack_20);
    uVar1 = 0;
    if (iVar2 != 0) {
      uVar1 = 5;
    }
  }
  return uVar1;
}




/* 0x0803733c */
undefined1 FUN_0803733c(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  undefined1 uVar1;
  int iVar2;
  undefined4 **local_38;
  undefined4 local_34;
  uint local_30;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined4 *local_28;
  undefined4 local_24;
  undefined4 *puStack_20;
  undefined4 local_1c;
  undefined1 auStack_18 [4];
  undefined4 uStack_14;
  undefined4 uStack_10;
  
  local_28 = &uStack_14;
  uVar1 = 0;
  if (DAT_080508f0 != '\0') {
    puStack_20 = &uStack_10;
    local_24 = 1;
    local_38 = &local_28;
    local_1c = 1;
    local_34 = 2;
    local_30 = (uint)*(byte *)*(uint*)DAT_080508f8;
    local_2c = 1;
    local_2b = 0;
    uStack_14 = param_1;
    uStack_10 = param_2;
    iVar2 = FUN_0800cf90(DAT_080508f4,&local_38,&DAT_080508fc,auStack_18);
    uVar1 = 0;
    if (iVar2 != 0) {
      uVar1 = 5;
    }
  }
  return uVar1;
}




/* 0x08037390 */
undefined4 FUN_08037390(param_1, param_2, param_3, param_4)
undefined4 param_1; byte param_2; byte param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_18;
  
  local_18 = param_4;
  iVar1 = FUN_080372d0(param_1,&local_18);
  if (iVar1 != 0) {
    return 5;
  }
  local_18 = CONCAT31(_GHIDRA_FIELD(local_18, 1, uint24_t),(byte)local_18 & ~param_3 | param_2);
  uVar2 = FUN_0803733c(param_1);
  return uVar2;
}




