/* Auto-generated: fhprg_801daf0.c */
/* Functions: 90 */
#include "globals.h"

/* 0x0801daf0 */
void FUN_0801daf0()
{
  FUN_0801db04();
  firehose_log("Reset validation state. Expecting Digital signature");
  return;
}




/* 0x0801db04 */
void FUN_0801db04()
{
  DAT_08055fc8 = 0;
  DAT_08055fcc = 0;
  DAT_08057fe0 = 0;
  DAT_08057fe4 = 0;
  DAT_08057ff0 = 0x100;
  DAT_08057ff4 = 0;
  DAT_08057ff8 = 0x100;
  DAT_08057ffc = 0;
  DAT_08057fe8 = 0;
  DAT_08057fec = 0;
  DAT_08058000 = 0;
  DAT_08058004 = 0;
  DAT_08055fd9 = 0;
  return;
}




/* 0x0801db38 */
undefined4 FUN_0801db38(param_1)
int param_1;
{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0xc);
  iVar1 = (**(code **)(*(int *)(iVar3 + 0xbc) + 8))();
  if ((iVar1 != 0) || (iVar1 = FUN_0800b550(*(undefined4 *)(iVar3 + 0x40)), uVar2 = 0, iVar1 != 0))
  {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}




/* 0x0801dbc8 */
void FUN_0801dbc8(param_1)
int param_1;
{
  FUN_0800b19a(*(undefined4 *)(param_1 + 8));
  return;
}




/* 0x0801dc4c */
undefined4 FUN_0801dc4c(param_1)
int param_1;
{
  undefined4 uVar1;
  code *pcVar2;
  
  uVar1 = 0xffffffff;
  pcVar2 = *(code **)(*(int *)(*(int *)(*(int *)(param_1 + 8) + 0xc) + 0xbc) + 0x1c);
  if (pcVar2 != (code *)0x0) {
    uVar1 = (*pcVar2)();
  }
  return uVar1;
}




/* 0x0801dc66 */
undefined4 FUN_0801dc66(param_1)
int param_1;
{
  undefined4 uVar1;
  code *pcVar2;
  
  uVar1 = 0xffffffff;
  pcVar2 = *(code **)(*(int *)(*(int *)(*(int *)(param_1 + 8) + 0xc) + 0xbc) + 0x2c);
  if (pcVar2 != (code *)0x0) {
    uVar1 = (*pcVar2)();
  }
  return uVar1;
}




/* 0x0801dc80 */
undefined4 FUN_0801dc80(param_1)
int param_1;
{
  undefined4 uVar1;
  code *pcVar2;
  
  uVar1 = 0xffffffff;
  pcVar2 = *(code **)(*(int *)(*(int *)(*(int *)(param_1 + 8) + 0xc) + 0xbc) + 0x28);
  if (pcVar2 != (code *)0x0) {
    uVar1 = (*pcVar2)();
  }
  return uVar1;
}




/* 0x0801dcb4 */
undefined4 FUN_0801dcb4(param_1)
int param_1;
{
  undefined4 uVar1;
  code *pcVar2;
  
  uVar1 = 0xffffffff;
  pcVar2 = *(code **)(*(int *)(*(int *)(*(int *)(param_1 + 8) + 0xc) + 0xbc) + 0x44);
  if (pcVar2 != (code *)0x0) {
    uVar1 = (*pcVar2)();
  }
  return uVar1;
}




/* 0x0801dcd4 */
int FUN_0801dcd4(param_1)
int param_1;
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_0800b33e(*(undefined4 *)(param_1 + 8));
  if (DAT_08050d10 != 0) {
    iVar3 = DAT_08050d10;
    if (*(int *)(param_1 + 8) == DAT_08050d10) {
      DAT_08050d10 = *(int *)(DAT_08050d10 + 0x94);
    }
    else {
      do {
        iVar2 = iVar3;
        iVar3 = *(int *)(iVar2 + 0x94);
      } while (iVar3 != *(int *)(param_1 + 8));
      *(undefined4 *)(iVar2 + 0x94) = *(undefined4 *)(iVar3 + 0x94);
    }
  }
  if (iVar1 == 0) {
    FUN_0800b574(*(undefined4 *)(param_1 + 8));
  }
  return iVar1;
}




/* 0x0801dd18 */
undefined4 FUN_0801dd18(param_1)
int param_1;
{
  undefined4 uVar1;
  code *pcVar2;
  
  uVar1 = 0xffffffff;
  pcVar2 = *(code **)(*(int *)(*(int *)(*(int *)(param_1 + 8) + 0xc) + 0xbc) + 0x18);
  if (pcVar2 != (code *)0x0) {
    uVar1 = (*pcVar2)();
  }
  return uVar1;
}




/* 0x0801dd32 */
undefined4 FUN_0801dd32(param_1)
int param_1;
{
  undefined4 uVar1;
  code *pcVar2;
  
  uVar1 = 0xffffffff;
  pcVar2 = *(code **)(*(int *)(*(int *)(*(int *)(param_1 + 8) + 0xc) + 0xbc) + 0x4c);
  if (pcVar2 != (code *)0x0) {
    uVar1 = (*pcVar2)();
  }
  return uVar1;
}




/* 0x0801dd8a */
undefined4 FUN_0801dd8a(param_1)
int param_1;
{
  undefined4 uVar1;
  code *pcVar2;
  
  uVar1 = 0xffffffff;
  pcVar2 = *(code **)(*(int *)(*(int *)(*(int *)(param_1 + 8) + 0xc) + 0xbc) + 0x10);
  if (pcVar2 != (code *)0x0) {
    uVar1 = (*pcVar2)();
  }
  return uVar1;
}




/* 0x0801ddbe */
undefined4 FUN_0801ddbe(param_1)
int param_1;
{
  undefined4 uVar1;
  code *pcVar2;
  
  uVar1 = 0xffffffff;
  pcVar2 = *(code **)(*(int *)(*(int *)(*(int *)(param_1 + 8) + 0xc) + 0xbc) + 0x48);
  if (pcVar2 != (code *)0x0) {
    uVar1 = (*pcVar2)();
  }
  return uVar1;
}




/* 0x0801ddd8 */
undefined4 FUN_0801ddd8(param_1)
int param_1;
{
  undefined4 uVar1;
  code *pcVar2;
  
  uVar1 = 0xffffffff;
  pcVar2 = (code *)**(undefined4 **)(*(int *)(*(int *)(param_1 + 8) + 0xc) + 0xbc);
  if (pcVar2 != (code *)0x0) {
    uVar1 = (*pcVar2)();
  }
  return uVar1;
}




/* 0x0801ddf8 */
undefined4 FUN_0801ddf8(param_1)
int param_1;
{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 extraout_r3;
  int *piVar4;
  undefined4 unaff_r4 = 0;
  int iVar5;
  int iVar6;
  
  iVar3 = *(int *)(*(int *)(param_1 + 8) + 0xc);
  thunk_FUN_08010668(*(undefined4 *)(iVar3 + 4),iVar3 + 0x10);
  iVar2 = *(int *)(param_1 + 8);
  iVar6 = *(int *)(iVar2 + 0xc);
  iVar5 = -1;
  piVar4 = (int *)0xffffffff;
  iVar3 = FUN_0800b634(0x10,iVar6 + 0x40,iVar6 + 0x18,extraout_r3,unaff_r4);
  if (iVar3 == 0) {
    iVar3 = *(int *)(iVar6 + 4);
    if (iVar3 == 0x2000050) {
      uVar1 = 5;
    }
    else {
      if ((iVar3 != 0x200013f) && (iVar3 != 0x2000140)) goto LAB_0801db98;
      uVar1 = 6;
    }
    piVar4 = (int *)FUN_0801deb8(uVar1);
  }
LAB_0801db98:
  if ((piVar4 != (int *)0xffffffff) && (*piVar4 != 0)) {
    for (; (piVar4 != (int *)0x0 && ((code *)*piVar4 != (code *)0x0)); piVar4 = piVar4 + 1) {
      iVar5 = ((code *)*piVar4)(iVar2);
      if (iVar5 == 0) {
        return 0;
      }
    }
    if (iVar5 == 0) {
      return 0;
    }
  }
  return 0xffffffff;
}




/* 0x0801de16 */
undefined4 FUN_0801de16(param_1)
int param_1;
{
  undefined4 uVar1;
  code *pcVar2;
  
  uVar1 = 0xffffffff;
  pcVar2 = *(code **)(*(int *)(*(int *)(*(int *)(param_1 + 8) + 0xc) + 0xbc) + 0xc);
  if (pcVar2 != (code *)0x0) {
    uVar1 = (*pcVar2)();
  }
  return uVar1;
}




/* 0x0801de30 */
undefined4 FUN_0801de30(param_1)
int param_1;
{
  undefined4 uVar1;
  code *pcVar2;
  
  uVar1 = 0xffffffff;
  pcVar2 = *(code **)(*(int *)(*(int *)(*(int *)(param_1 + 8) + 0xc) + 0xbc) + 0x3c);
  if (pcVar2 != (code *)0x0) {
    uVar1 = (*pcVar2)();
  }
  return uVar1;
}




/* 0x0801de4a */
undefined4 FUN_0801de4a(param_1)
int param_1;
{
  undefined4 uVar1;
  code *pcVar2;
  
  uVar1 = 0xffffffff;
  pcVar2 = *(code **)(*(int *)(*(int *)(*(int *)(param_1 + 8) + 0xc) + 0xbc) + 0x40);
  if (pcVar2 != (code *)0x0) {
    uVar1 = (*pcVar2)();
  }
  return uVar1;
}




/* 0x0801de64 */
undefined4 FUN_0801de64(param_1)
int param_1;
{
  undefined4 uVar1;
  code *pcVar2;
  
  uVar1 = 0xffffffff;
  pcVar2 = *(code **)(*(int *)(*(int *)(*(int *)(param_1 + 8) + 0xc) + 0xbc) + 0x50);
  if (pcVar2 != (code *)0x0) {
    uVar1 = (*pcVar2)();
  }
  return uVar1;
}




/* 0x0801de84 */
undefined4 FUN_0801de84(param_1)
int param_1;
{
  undefined4 uVar1;
  code *pcVar2;
  
  uVar1 = 0xffffffff;
  pcVar2 = *(code **)(*(int *)(*(int *)(*(int *)(param_1 + 8) + 0xc) + 0xbc) + 0x30);
  if (pcVar2 != (code *)0x0) {
    uVar1 = (*pcVar2)();
  }
  return uVar1;
}




/* 0x0801de9e */
undefined4 FUN_0801de9e(param_1)
int param_1;
{
  undefined4 uVar1;
  code *pcVar2;
  
  uVar1 = 0xffffffff;
  pcVar2 = *(code **)(*(int *)(*(int *)(*(int *)(param_1 + 8) + 0xc) + 0xbc) + 0x34);
  if (pcVar2 != (code *)0x0) {
    uVar1 = (*pcVar2)();
  }
  return uVar1;
}




/* 0x0801deb8 */
undefined * FUN_0801deb8(param_1)
undefined4 param_1;
{
  undefined *local_8;
  
  if (true) {
    switch(param_1) {
    case 0:
    case 1:
    case 2:
    case 0xc:
      return (undefined *)0x0;
    case 3:
    case 10:
      return (undefined *)0x1;
    case 4:
      return &DAT_08051448;
    case 5:
      return &DAT_08051450;
    case 6:
      return &DAT_08051458;
    case 9:
      local_8 = (undefined *)0x0;
      FUN_0801e170(&local_8);
      return local_8;
    case 0x13:
      return &DAT_0805144c;
    case 0x14:
      return (undefined *)0x40;
    }
  }
  return (undefined *)0xffffffff;
}




/* 0x0801e170 */
void FUN_0801e170(param_1)
undefined4 * param_1;
{
  *param_1 = &DAT_08051a00;
  return;
}




/* 0x0801e17c */
void FUN_0801e17c(param_1, param_2, param_3)
int param_1; undefined4 param_2; int param_3;
{
  thunk_FUN_08027bf8(param_1,param_3,param_2);
  *(undefined1 *)(param_1 + param_3 + -1) = 0;
  return;
}




/* 0x0801e196 */
undefined4 FUN_0801e196(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  
  local_10 = param_4;
  iVar1 = FUN_0801e554(&local_10);
  if (iVar1 != 0) {
    return 0x16;
  }
  uVar2 = FUN_0801e5f0(local_10,param_1);
  FUN_0801268c(local_10);
  return uVar2;
}




/* 0x0801e1ba */
undefined4 FUN_0801e1ba(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  
  local_10 = param_4;
  iVar1 = FUN_0801e554(&local_10);
  if (iVar1 != 0) {
    return 0x16;
  }
  uVar2 = FUN_0801e708(local_10,param_1);
  FUN_0801268c(local_10);
  return uVar2;
}




/* 0x0801e1e2 */
undefined4 FUN_0801e1e2(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  
  local_10 = param_4;
  iVar1 = FUN_0801e554(&local_10);
  if (iVar1 != 0) {
    return 0x16;
  }
  uVar2 = FUN_0801e79c(local_10,param_1,param_2);
  FUN_0801268c(local_10);
  return uVar2;
}




/* 0x0801e20a */
undefined4 FUN_0801e20a(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  
  local_10 = param_4;
  iVar1 = FUN_0801e554(&local_10);
  if (iVar1 != 0) {
    return 0x16;
  }
  uVar2 = FUN_0801e7e4(local_10,param_1,param_2);
  FUN_0801268c(local_10);
  return uVar2;
}




/* 0x0801e232 */
undefined4 FUN_0801e232(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_18;
  
  local_18 = param_4;
  iVar1 = FUN_0801e554(&local_18);
  if (iVar1 != 0) {
    return 0x16;
  }
  uVar2 = FUN_0801e954(local_18,param_1,param_2,param_3);
  FUN_0801268c(local_18);
  return uVar2;
}




/* 0x0801e25e */
undefined4 FUN_0801e25e(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_18;
  
  local_18 = param_4;
  iVar1 = FUN_0801e554(&local_18);
  if (iVar1 != 0) {
    return 0x16;
  }
  uVar2 = FUN_0801ea98(local_18,param_1,param_2,param_3);
  FUN_0801268c(local_18);
  return uVar2;
}




/* 0x0801e28a */
undefined4 FUN_0801e28a(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_1c;
  
  local_1c = param_4;
  iVar1 = FUN_0801e554(&local_1c);
  if (iVar1 == 0) {
    uVar2 = FUN_0801eb7c(local_1c,param_1,param_2,param_3,param_4);
    FUN_0801268c(local_1c);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}




/* 0x0801e2be */
undefined4 FUN_0801e2be(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_18;
  
  local_18 = param_4;
  iVar1 = FUN_0801e554(&local_18);
  if (iVar1 != 0) {
    return 0x16;
  }
  uVar2 = FUN_0801ed88(local_18,param_1,param_2,param_3);
  FUN_0801268c(local_18);
  return uVar2;
}




/* 0x0801e2ea */
undefined4 FUN_0801e2ea(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  
  local_10 = param_4;
  iVar1 = FUN_0801e554(&local_10);
  if (iVar1 != 0) {
    return 0x16;
  }
  uVar2 = FUN_0801eea0(local_10,param_1,param_2);
  FUN_0801268c(local_10);
  return uVar2;
}




/* 0x0801e312 */
undefined4 FUN_0801e312(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  
  local_10 = param_4;
  iVar1 = FUN_0801e554(&local_10);
  if (iVar1 != 0) {
    return 0x16;
  }
  uVar2 = FUN_0801f004(local_10,param_1);
  FUN_0801268c(local_10);
  return uVar2;
}




/* 0x0801e336 */
undefined4 FUN_0801e336(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  
  local_10 = param_4;
  iVar1 = FUN_0801e554(&local_10);
  if (iVar1 != 0) {
    return 0x16;
  }
  uVar2 = FUN_0801f11a(local_10,param_1,param_2);
  FUN_0801268c(local_10);
  return uVar2;
}




/* 0x0801e382 */
undefined4 FUN_0801e382(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  
  local_10 = param_4;
  iVar1 = FUN_0801e554(&local_10);
  if (iVar1 != 0) {
    return 0x16;
  }
  uVar2 = FUN_0801f30c(local_10,param_1);
  FUN_0801268c(local_10);
  return uVar2;
}




/* 0x0801e3a6 */
undefined4 FUN_0801e3a6(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  
  local_10 = param_4;
  iVar1 = FUN_0801e554(&local_10);
  if (iVar1 != 0) {
    return 0;
  }
  uVar2 = FUN_0801f91c(local_10,param_1,param_2);
  FUN_0801268c(local_10);
  return uVar2;
}




/* 0x0801e3ce */
undefined4 FUN_0801e3ce(param_1, param_2, param_3, param_4)
int param_1; int param_2; undefined4 param_3; undefined4 param_4;
{
  short sVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 local_18;
  
  local_18 = param_4;
  iVar2 = FUN_0801e554(&local_18);
  if (iVar2 != 0) {
    return 0x16;
  }
  uVar3 = 0;
  for (uVar5 = 0; *(short *)(param_1 + uVar5 * 2) != 0; uVar5 = uVar5 + 1) {
  }
  while (1 < uVar5) {
    uVar5 = uVar5 - 1;
    sVar1 = *(short *)(param_1 + uVar5 * 2);
    if ((sVar1 == 0x2f) || (sVar1 == 0x5c)) break;
  }
  for (; *(short *)(param_2 + uVar3 * 2) != 0; uVar3 = uVar3 + 1) {
  }
  while (1 < uVar3) {
    uVar3 = uVar3 - 1;
    sVar1 = *(short *)(param_2 + uVar3 * 2);
    if ((sVar1 == 0x2f) || (sVar1 == 0x5c)) break;
  }
  if (uVar3 == uVar5) {
    for (; 1 < uVar3; uVar3 = uVar3 - 1) {
      uVar5 = (uint)*(ushort *)(param_1 + uVar3 * 2);
      if (uVar5 - 0x61 < 0x1a) {
        uVar5 = uVar5 - 0x20;
      }
      uVar6 = (uint)*(ushort *)(param_2 + uVar3 * 2);
      if (uVar6 - 0x61 < 0x1a) {
        uVar6 = uVar6 - 0x20;
      }
      if (uVar5 != uVar6) goto LAB_0801e454;
    }
    if (true) {
      uVar4 = FUN_0801fdc8(local_18,param_1,param_2);
      goto LAB_0801e46a;
    }
  }
LAB_0801e454:
  uVar4 = FUN_0801f540(local_18,param_1,param_2);
LAB_0801e46a:
  FUN_0801268c(local_18);
  return uVar4;
}




/* 0x0801e476 */
undefined4 FUN_0801e476(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_1c;
  
  local_1c = param_4;
  iVar1 = FUN_0801e554(&local_1c);
  if (iVar1 == 0) {
    uVar2 = FUN_0802000e(local_1c,param_1,param_2,param_3,param_4);
    FUN_0801268c(local_1c);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}




/* 0x0801e4aa */
undefined4 FUN_0801e4aa(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  
  local_10 = param_4;
  iVar1 = FUN_0801e554(&local_10);
  if (iVar1 != 0) {
    return 0x16;
  }
  uVar2 = FUN_0802023c(local_10,param_1);
  FUN_0801268c(local_10);
  return uVar2;
}




/* 0x0801e4ce */
undefined4 FUN_0801e4ce(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_1c;
  
  local_1c = param_4;
  iVar1 = FUN_0801e554(&local_1c);
  if (iVar1 == 0) {
    uVar2 = FUN_080203a2(local_1c,param_1,param_2,param_3,param_4);
    FUN_0801268c(local_1c);
  }
  else {
    uVar2 = 0x16;
  }
  return uVar2;
}




/* 0x0801e502 */
undefined4 FUN_0801e502(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  
  local_10 = param_4;
  iVar1 = FUN_0801e554(&local_10);
  if (iVar1 != 0) {
    return 0x16;
  }
  uVar2 = FUN_0802047e(local_10,param_1,param_2);
  FUN_0801268c(local_10);
  return uVar2;
}




/* 0x0801e52a */
undefined4 FUN_0801e52a(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  
  local_10 = param_4;
  iVar1 = FUN_0801e554(&local_10);
  if (iVar1 != 0) {
    return 0x16;
  }
  uVar2 = FUN_08020552(local_10,param_1,param_2);
  FUN_0801268c(local_10);
  return uVar2;
}




/* 0x0801e554 */
undefined4 FUN_0801e554(param_1)
undefined4 * param_1;
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_0801ea4a();
  if (DAT_0804e290 == 0) {
    DAT_0804e290 = 1;
    iVar2 = 0;
    do {
      if ((&DAT_87c194a4)[iVar2 * 0x105] == iVar1) {
        *param_1 = &DAT_87c194a4 + iVar2 * 0x105;
        (&DAT_87c198ac)[iVar2 * 0x105] = 0;
        return 0;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 1);
    iVar2 = 0;
    while ((&DAT_87c194a4)[iVar2 * 0x105] != 0) {
      iVar2 = iVar2 + 1;
      if (0 < iVar2) {
        FUN_08015a50();
        return 1;
      }
    }
    (&DAT_87c194a4)[iVar2 * 0x105] = iVar1;
    *(undefined4 *)(&UNK_87c194a8 + iVar2 * 0x414) = 0xffffffff;
    iVar1 = 0;
    do {
      iVar3 = iVar1 + 1;
      *(undefined2 *)(&DAT_87c194a4 + iVar2 * 0x105 + iVar1 * 0x80 + 2) = 0;
      iVar1 = iVar3;
    } while (iVar3 < 2);
    *param_1 = &DAT_87c194a4 + iVar2 * 0x105;
    (&DAT_87c198ac)[iVar2 * 0x105] = 0;
  }
  else {
    *param_1 = &DAT_87c194a4;
  }
  return 0;
}




/* 0x0801e5f0 */
undefined4 FUN_0801e5f0(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  int iVar2;
  undefined4 local_18;
  
  local_18 = param_4;
  iVar1 = FUN_08011218(param_2);
  iVar2 = 8;
  if ((iVar1 == 0) ||
     (iVar2 = FUN_08012524(param_1,*(undefined4 *)(iVar1 + 0xc),&local_18), iVar2 != 0))
  goto switchD_0801e642_default;
  iVar2 = 0;
  do {
    if (*(int *)(&DAT_87c12db4 + iVar2 * 0xeb0) == iVar1) {
      *(undefined4 *)(&DAT_87c12db4 + iVar2 * 0xeb0) = 0;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 8);
  if ((int)((uint)*(byte *)(iVar1 + 8) << 0x19) < 0) {
switchD_0801e642_caseD_1:
    iVar2 = 0;
    *(undefined1 *)(iVar1 + 8) = 0;
  }
  else {
    iVar2 = 8;
    switch((uint)*(byte *)(iVar1 + 8)) {
    case 0:
      iVar2 = 8;
      break;
    case 1:
      goto switchD_0801e642_caseD_1;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      iVar2 = FUN_080117ea(local_18,iVar1,0);
      if ((iVar2 == 0) && (iVar2 = FUN_08013228(local_18), iVar2 == 0)) {
        iVar2 = FUN_08011a1e(local_18,0);
        if (iVar2 == 0) {
          FUN_08012fe0(local_18,param_1,iVar1);
          *(undefined1 *)(iVar1 + 8) = 0;
          iVar2 = FUN_080130f8(local_18,iVar1,0);
          break;
        }
      }
      else {
        FUN_080130f8(local_18,iVar1,1);
      }
      iVar2 = 0x14;
      *(undefined1 *)(iVar1 + 8) = 0;
    }
  }
switchD_0801e642_default:
  *(int *)(param_1 + 0x410) = iVar2;
  return 0;
}




/* 0x0801e6b0 */
undefined4 FUN_0801e6b0(param_1, param_2, param_3, param_4, param_5)
int param_1; int * param_2; code * param_3; undefined4 param_4; undefined4 param_5;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_3 != (code *)0x0) {
    iVar1 = (*param_3)(param_4,param_5);
    *param_2 = iVar1;
    if (iVar1 != 0) {
      iVar2 = 0;
      do {
        if ((&DAT_87c092a4)[iVar2 * 0x2298] == iVar1) {
          uVar3 = 6;
          goto LAB_0801e6fc;
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < 2);
      iVar1 = FUN_0801d922(iVar1);
      if (iVar1 == 0) {
        *(undefined4 *)(*param_2 + 4) = 1;
        uVar3 = 0;
        goto LAB_0801e6fc;
      }
    }
  }
  uVar3 = 0xf;
LAB_0801e6fc:
  *(undefined4 *)(param_1 + 0x410) = uVar3;
  return 0;
}




/* 0x0801e708 */
undefined4 FUN_0801e708(param_1, param_2)
int param_1; int param_2;
{
  char cVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  cVar1 = FUN_0801172c(param_2);
  if (cVar1 < '\0') {
    iVar2 = 1;
  }
  else {
    piVar4 = &DAT_87c00a48 + (short)cVar1 * 0x2298;
    iVar2 = FUN_0801267c(param_1,piVar4);
    if ((iVar2 == 0) && (*piVar4 != 0)) {
      FUN_08011428(param_2);
      iVar2 = FUN_08011a1e(piVar4,0);
      if (iVar2 == 0x10) {
        iVar2 = 0;
      }
      else if (iVar2 != 0) goto LAB_0801e77c;
      *piVar4 = 0;
      (&DAT_87c19488)[param_2] = 0xff;
      iVar3 = (&DAT_87c092a4)[(short)cVar1 * 0x2298];
      if (((iVar3 != 0) && ((&DAT_87c092a4)[(short)cVar1 * 0x2298] = 0, *(int *)(iVar3 + 4) == 0))
         && (iVar3 = FUN_0801ed28(param_1), iVar3 != 0)) {
        iVar2 = 0xf;
      }
    }
  }
LAB_0801e77c:
  *(int *)(param_1 + 0x410) = iVar2;
  return 0;
}




/* 0x0801e790 */
void thunk_FUN_0801e790(param_1)
undefined1 param_1;
{
  DAT_0804e29c = param_1;
  return;
}




/* 0x0801e790 */
void FUN_0801e790(param_1)
undefined1 param_1;
{
  DAT_0804e29c = param_1;
  return;
}




/* 0x0801e79c */
undefined4 FUN_0801e79c(param_1, param_2, param_3)
int param_1; undefined4 param_2; uint param_3;
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 extraout_r2;
  undefined4 extraout_r3;
  undefined4 local_18;
  undefined4 local_14;
  
  iVar2 = FUN_08011218(param_2);
  if (iVar2 == 0) {
    uVar3 = 8;
  }
  else {
    if (param_3 <= *(uint *)(iVar2 + 0x18)) {
      iVar2 = FUN_0801ed88(param_1,param_2,param_3,0);
      if (iVar2 != 0) {
        return 0;
      }
      local_18 = extraout_r2;
      local_14 = extraout_r3;
      iVar2 = FUN_08011218(param_2);
      if ((iVar2 == 0) ||
         (((cVar1 = *(char *)(iVar2 + 8), cVar1 != '\x02' && (cVar1 != '\x04')) && (cVar1 != '\x05')
          ))) {
        iVar4 = 8;
      }
      else {
        iVar4 = FUN_08012524(param_1,*(undefined4 *)(iVar2 + 0xc),&local_14);
        if (iVar4 == 0) {
          if (*(int *)(iVar2 + 0xe2c) == 0) {
            iVar4 = *(int *)(iVar2 + 0x18);
          }
          else {
            iVar4 = FUN_08012088(local_14,*(undefined4 *)(iVar2 + 0xe30),&local_18);
            if (((iVar4 != 0) || (iVar4 = FUN_08012ad0(local_14,local_18), iVar4 != 0)) ||
               (iVar4 = FUN_08012d54(local_14,*(undefined4 *)(iVar2 + 0xe30),0xffffff8), iVar4 != 0)
               ) goto LAB_0801ee7a;
            iVar4 = *(int *)(iVar2 + 0x10) + *(int *)(iVar2 + 0x14);
            *(int *)(iVar2 + 0x18) = iVar4;
          }
          if (iVar4 == 0) {
            if ((*(int *)(iVar2 + 0xe2c) - 2U < 0xfffffee) &&
               (iVar4 = FUN_08012ad0(local_14), iVar4 != 0)) goto LAB_0801ee7a;
            *(undefined4 *)(iVar2 + 0xe2c) = 0;
            *(undefined4 *)(iVar2 + 0xe3c) = 0;
            *(undefined4 *)(iVar2 + 0xe40) = 0;
            *(undefined4 *)(iVar2 + 4) = 0;
          }
          FUN_0801347a(iVar2);
          iVar4 = 0;
        }
      }
LAB_0801ee7a:
      *(int *)(param_1 + 0x410) = iVar4;
      return 0;
    }
    uVar3 = 9;
  }
  *(undefined4 *)(param_1 + 0x410) = uVar3;
  return 0;
}




/* 0x0801e7da */
undefined4 FUN_0801e7da(param_1)
int param_1;
{
  *(undefined4 *)(param_1 + 0x410) = 0;
  return *(undefined4 *)(param_1 + 4);
}




/* 0x0801e7e4 */
undefined4 FUN_0801e7e4(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; uint * param_3; int param_4;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int extraout_r3;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint *local_30;
  int local_2c;
  
  local_30 = param_3;
  local_2c = param_4;
  iVar1 = FUN_08012524(param_1,param_2,&local_30);
  if (iVar1 == 0) {
    uVar2 = FUN_08012500(local_30);
    *param_3 = uVar2;
    param_3[1] = 0;
    param_3[2] = 0;
    param_3[3] = 0;
    if ((char)local_30[0x220f] == '\0') {
      if (local_30[0x220b] == 3) {
        iVar7 = 0;
        uVar9 = local_30[0x2d];
        uVar4 = 0;
        uVar3 = 0;
        while ((uVar4 < uVar9 && (uVar3 < uVar2))) {
          iVar1 = FUN_08012350(local_30,iVar7);
          if (iVar1 != 0) goto LAB_0801e8c6;
          uVar8 = local_30[0x1074];
          if (uVar4 == 0) {
            uVar5 = 2;
          }
          else {
            uVar5 = 0;
          }
          do {
            uVar6 = uVar3 + 1;
            if (uVar2 <= uVar3) break;
            uVar3 = FUN_08011f72(uVar8 + uVar5 * 4);
            if ((uVar3 & 0xfffffff) == 0) {
              param_3[1] = param_3[1] + 1;
            }
            else if ((uVar3 & 0xfffffff) == 0xffffff7) {
              param_3[3] = param_3[3] + 1;
            }
            else {
              param_3[2] = param_3[2] + 1;
            }
            uVar5 = extraout_r3 + 1;
            uVar3 = uVar6;
          } while (uVar5 < 0x80);
          uVar4 = uVar4 + 1;
          iVar7 = iVar7 + 1;
          uVar3 = uVar6;
        }
      }
      else {
        for (uVar3 = 0; uVar3 < uVar2; uVar3 = uVar3 + 1) {
          iVar1 = FUN_08012088(local_30,uVar3 + 2,&local_2c);
          if (iVar1 != 0) goto LAB_0801e8c6;
          if (local_2c == 0) {
            param_3[1] = param_3[1] + 1;
          }
          else if (local_2c == 0xffffff7) {
            param_3[3] = param_3[3] + 1;
          }
          else {
            param_3[2] = param_3[2] + 1;
          }
        }
      }
      local_30[0x220c] = param_3[1];
      local_30[0x220d] = param_3[2];
      local_30[0x220e] = param_3[3];
      *(undefined1 *)(local_30 + 0x220f) = 1;
    }
    else {
      param_3[1] = local_30[0x220c];
      param_3[2] = local_30[0x220d];
      param_3[3] = local_30[0x220e];
    }
    uVar2 = 0;
    for (uVar3 = (uint)*(byte *)((int)local_30 + 0x5a) << 9; (uVar3 & 1) == 0; uVar3 = uVar3 >> 1) {
      uVar2 = uVar2 + 1;
    }
    uVar3 = 0x20 - uVar2;
    param_3[4] = *param_3 >> (uVar3 & 0xff);
    *param_3 = *param_3 << (uVar2 & 0xff);
    param_3[5] = param_3[1] >> (uVar3 & 0xff);
    param_3[1] = param_3[1] << (uVar2 & 0xff);
    param_3[6] = param_3[2] >> (uVar3 & 0xff);
    param_3[2] = param_3[2] << (uVar2 & 0xff);
    uVar4 = param_3[3];
    param_3[3] = uVar4 << (uVar2 & 0xff);
    iVar1 = 0;
    param_3[7] = uVar4 >> (uVar3 & 0xff);
  }
LAB_0801e8c6:
  *(int *)(param_1 + 0x410) = iVar1;
  return 0;
}




/* 0x0801e954 */
undefined4 FUN_0801e954(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; int param_3; int param_4;
{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint local_50;
  undefined4 uStack_4c;
  undefined1 auStack_48 [3];
  char local_45;
  int local_30;
  uint local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  int local_20;
  
  iVar1 = DAT_0804cd58;
  local_20 = DAT_0804cd58;
  if (param_4 != 0) {
    iVar2 = FUN_08012524(param_1,param_2,&local_30);
    if (iVar2 != 0) goto LAB_0801e9e6;
    local_2c = *(uint *)(local_30 + 0x98);
    uStack_28 = *(undefined4 *)(local_30 + 0x9c);
    uStack_24 = *(undefined4 *)(local_30 + 0xa0);
    iVar2 = FUN_080127a0(local_30,param_2,0);
    if (iVar2 == 0) {
      iVar2 = 0x13;
      goto LAB_0801e9e6;
    }
    do {
      iVar3 = FUN_080129f0(local_30,&local_50,iVar2);
      if (((iVar3 == 9) || (iVar3 != 0)) || ((local_50 & 0xff) == 0)) goto LAB_0801e9d8;
    } while (((local_50 & 0xff) == 0xe5) || (local_45 != '\b'));
    local_2c = local_50;
    uStack_28 = uStack_4c;
    FUN_08006bdc(&uStack_24,auStack_48,3);
LAB_0801e9d8:
    iVar2 = FUN_08011458(local_30,iVar2,0);
    if (iVar2 != 0) goto LAB_0801e9e6;
    iVar2 = 0;
    do {
      if (param_4 + -1 <= iVar2) break;
      *(undefined1 *)(param_3 + iVar2) = *(undefined1 *)((int)&local_2c + iVar2);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0xb);
    *(undefined1 *)(param_3 + iVar2) = 0;
    if (-1 < iVar2) {
      do {
        *(undefined1 *)(param_3 + iVar2) = 0;
        iVar2 = iVar2 + -1;
        if (iVar2 < 0) break;
      } while (*(byte *)(param_3 + iVar2) < 0x21);
    }
  }
  iVar2 = 0;
LAB_0801e9e6:
  uVar4 = FUN_0801eff4(param_1,iVar2);
  if (local_20 != iVar1) {
    FUN_08010960();
  }
  return uVar4;
}




/* 0x0801ea34 */
undefined4 FUN_0801ea34()
{
  int iVar1;
  undefined4 *extraout_r3;
  
  iVar1 = FUN_08011218();
  if (iVar1 != 0) {
    *extraout_r3 = *(undefined4 *)(iVar1 + 0x18);
    return 0;
  }
  return 8;
}




/* 0x0801ea4a */
undefined4 FUN_0801ea4a()
{
  return 1;
}




/* 0x0801ea50 */
undefined4 FUN_0801ea50()
{
  int iVar1;
  undefined4 uVar2;
  
  FUN_08006d14(&DAT_87c00a48,0x18a40);
  FUN_08006cc0(&DAT_87c19488,0x1a,0xffffffff);
  FUN_08006d14(&DAT_87c194a4,0x414);
  thunk_FUN_0801e790(1);
  iVar1 = FUN_0801d922(&DAT_0804e298);
  uVar2 = 0;
  if (iVar1 != 0) {
    uVar2 = 0xf;
  }
  return uVar2;
}




/* 0x0801ea50 */
undefined4 thunk_FUN_0801ea50()
{
  int iVar1;
  undefined4 uVar2;
  
  FUN_08006d14(&DAT_87c00a48,0x18a40);
  FUN_08006cc0(&DAT_87c19488,0x1a,0xffffffff);
  FUN_08006d14(&DAT_87c194a4,0x414);
  thunk_FUN_0801e790(1);
  iVar1 = FUN_0801d922(&DAT_0804e298);
  uVar2 = 0;
  if (iVar1 != 0) {
    uVar2 = 0xf;
  }
  return uVar2;
}




/* 0x0801ea98 */
undefined4 FUN_0801ea98(param_1, param_2, param_3, param_4)
int param_1; uint param_2; undefined4 param_3; int param_4;
{
  undefined4 uVar1;
  int iVar2;
  int local_1c;
  
  if (param_2 < 0x1a) {
    if ((byte)(&DAT_87c19488)[param_2] < 2) {
      uVar1 = 0x1d;
    }
    else {
      iVar2 = 0;
      do {
        if ((&DAT_87c00a48)[(short)iVar2 * 0x2298] == 0) {
          if (iVar2 < 2) {
            (&DAT_87c19488)[param_2] = (char)iVar2;
            local_1c = param_4;
            iVar2 = FUN_0801e6b0(param_1,&local_1c,param_3,param_2,param_4);
            if (iVar2 == 0) {
              if (local_1c == 0) goto LAB_0801eaa6;
              *(undefined4 *)(local_1c + 4) = 0;
              uVar1 = FUN_0801eb14(param_1,param_2,local_1c,0);
              goto LAB_0801eb02;
            }
          }
          break;
        }
        iVar2 = (int)(char)((char)iVar2 + '\x01');
      } while (iVar2 < 2);
      uVar1 = 0xf;
    }
  }
  else {
LAB_0801eaa6:
    uVar1 = 1;
  }
LAB_0801eb02:
  *(undefined4 *)(param_1 + 0x410) = uVar1;
  return 0;
}




/* 0x0801eb14 */
undefined4 FUN_0801eb14(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  int iVar2;
  char cVar3;
  undefined4 uVar4;
  int *piVar5;
  
  cVar3 = FUN_0801172c(param_2);
  if (cVar3 < '\0') {
    uVar4 = 1;
  }
  else {
    iVar2 = (int)(short)cVar3;
    iVar1 = iVar2 * 0x8a60;
    piVar5 = &DAT_87c00a48 + iVar2 * 0x2298;
    if (*piVar5 == 0) {
      *(undefined **)(&DAT_87c00b14 + iVar1) = &UNK_87c00b18 + iVar1;
      FUN_080257ee(piVar5);
      *(undefined4 *)(&DAT_87c09288 + iVar1) = param_4;
      (&DAT_87c092a4)[iVar2 * 0x2298] = param_3;
      *piVar5 = 1;
      uVar4 = FUN_08012524(param_1,param_2,0);
    }
    else {
      uVar4 = 0x1d;
    }
  }
  *(undefined4 *)(param_1 + 0x410) = uVar4;
  return 0;
}




/* 0x0801eb7c */
undefined8 FUN_0801eb7c(param_1, param_2, param_3, param_4, param_5)
int param_1; int param_2; int param_3; int param_4; undefined4 param_5;
{
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int local_2c;
  int local_28;
  
  local_2c = param_3;
  local_28 = param_4;
  iVar3 = FUN_08011218(param_5);
  iVar10 = 0;
  bVar2 = false;
  local_2c = 0;
  if ((iVar3 == 0) ||
     ((((cVar1 = *(char *)(iVar3 + 8), cVar1 != '\x01' && (cVar1 != '\x04')) && (cVar1 != '\x05'))
      && (cVar1 != '\x06')))) {
    iVar4 = 8;
  }
  else {
    if (*(int *)(iVar3 + 0xe64) == 0) {
      iVar4 = FUN_08012524(param_1,*(undefined4 *)(iVar3 + 0xc),&local_28);
      if (iVar4 != 0) goto LAB_0801ebc8;
      uVar7 = param_4 * param_3;
      if (0 < (int)uVar7) {
        if ((*(int *)(iVar3 + 0x14) + *(int *)(iVar3 + 0x10) + uVar7 < *(uint *)(iVar3 + 0x18)) ||
           (uVar7 = (*(uint *)(iVar3 + 0x18) - *(int *)(iVar3 + 0x14)) - *(int *)(iVar3 + 0x10),
           0 < (int)uVar7)) {
          do {
            uVar8 = uVar7;
            if (*(int *)(iVar3 + 0x14) == 0x200) {
              if (*(int *)(iVar3 + 4) != 0) {
                iVar4 = FUN_080117ea(local_28,iVar3,0);
                if ((iVar4 != 0) || (iVar4 = FUN_08013228(local_28), iVar4 != 0)) {
                  *(byte *)(iVar3 + 8) = *(byte *)(iVar3 + 8) | 0x40;
                  goto LAB_0801ecc4;
                }
                FUN_080134a8(iVar3);
              }
              *(int *)(iVar3 + 0x10) = *(int *)(iVar3 + 0x10) + *(int *)(iVar3 + 0x14);
              *(undefined4 *)(iVar3 + 0x14) = 0;
              *(int *)(iVar3 + 0xe3c) = *(int *)(iVar3 + 0xe3c) + 1;
              if ((int)uVar7 < 0x201) {
                bVar2 = false;
                iVar4 = FUN_08012190(local_28,iVar3,0,0);
              }
              else {
                bVar2 = true;
                local_2c = (int)(uVar7 + ((uint)((int)uVar7 >> 0x1f) >> 0x17)) >> 9;
                iVar4 = FUN_08012190(local_28,iVar3,param_2,&local_2c);
                if (uVar7 == local_2c * 0x200) {
                  FUN_08006a30(iVar3 + 0x1c,param_2 + local_2c * 0x200 + -0x200,0x200);
                }
                iVar5 = local_2c + -1;
                local_2c = iVar5 * 0x200;
                param_2 = param_2 + local_2c;
                iVar10 = iVar10 + local_2c;
                uVar8 = uVar7 + iVar5 * -0x200;
              }
              FUN_080134a8(iVar3);
              if (iVar4 == 9) {
                if (uVar8 == 0) break;
              }
              else if (iVar4 == 0) goto LAB_0801ecca;
              *(byte *)(iVar3 + 8) = *(byte *)(iVar3 + 8) | 0x40;
              *(int *)(param_1 + 0x410) = iVar4;
              goto LAB_0801ecb8;
            }
LAB_0801ecca:
            uVar6 = 0x200 - *(int *)(iVar3 + 0x14);
            uVar9 = uVar7;
            if (uVar6 <= uVar7) {
              uVar9 = uVar6;
            }
            if (!bVar2) {
              iVar4 = *(int *)(iVar3 + 0xeac);
              iVar5 = iVar3 + 0x1c;
              if (iVar4 != 0) {
                if ((*(char *)(iVar4 + 8) == '\x06') || (*(char *)(iVar4 + 8) == '\x03')) {
                  if (*(int *)(iVar3 + 0x10) == *(int *)(iVar4 + 0x10)) {
                    iVar5 = iVar4 + 0x1c;
                  }
                }
                else {
                  *(undefined4 *)(iVar3 + 0xeac) = 0;
                }
              }
              FUN_08006a30(param_2,*(int *)(iVar3 + 0x14) + iVar5,uVar9);
            }
            uVar7 = uVar8 - uVar9;
            param_2 = param_2 + uVar9;
            *(uint *)(iVar3 + 0x14) = *(int *)(iVar3 + 0x14) + uVar9;
            iVar10 = iVar10 + uVar9;
          } while (uVar7 != 0);
          iVar4 = 0;
LAB_0801ecc4:
          *(int *)(param_1 + 0x410) = iVar4;
LAB_0801ecb8:
          iVar10 = iVar10 / param_3;
          goto LAB_0801ebce;
        }
      }
    }
    iVar4 = 0;
  }
LAB_0801ebc8:
  *(int *)(param_1 + 0x410) = iVar4;
  iVar10 = 0;
LAB_0801ebce:
  return CONCAT44(param_3,iVar10);
}




/* 0x0801ed28 */
undefined4 FUN_0801ed28(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  int iVar2;
  
  if (param_2 != 0) {
    iVar2 = 0;
    do {
      if ((&DAT_87c092a4)[iVar2 * 0x2298] == param_2) {
        iVar1 = FUN_0801e708(param_1,iVar2);
        if (iVar1 != 0) goto LAB_0801ed5c;
        (&DAT_87c092a4)[iVar2 * 0x2298] = 0;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 2);
    FUN_0801d92a(param_2);
    *(undefined4 *)(param_1 + 0x408) = 0;
    if (*(code **)(param_2 + 0x30) != (code *)0x0) {
      (**(code **)(param_2 + 0x30))(param_2);
    }
  }
  iVar1 = 0;
LAB_0801ed5c:
  *(int *)(param_1 + 0x410) = iVar1;
  return 0;
}




/* 0x0801ed88 */
undefined4 FUN_0801ed88(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; uint param_3; int param_4;
{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  int local_18;
  
  local_18 = param_4;
  iVar2 = FUN_08011218(param_2);
  if ((iVar2 == 0) ||
     ((((cVar1 = *(char *)(iVar2 + 8), cVar1 != '\x01' && (cVar1 != '\x02')) && (cVar1 != '\x03'))
      && (((cVar1 != '\x04' && (cVar1 != '\x05')) && (cVar1 != '\x06')))))) {
    iVar3 = 8;
  }
  else {
    iVar3 = FUN_08012524(param_1,*(undefined4 *)(iVar2 + 0xc),&local_18);
    if (iVar3 == 0) {
      if (param_4 != 0) {
        if (param_4 == 1) {
          uVar4 = *(int *)(iVar2 + 0x10) + *(int *)(iVar2 + 0x14);
        }
        else {
          if (param_4 != 2) {
            iVar3 = 0xb;
            goto LAB_0801ede8;
          }
          uVar4 = *(uint *)(iVar2 + 0x18);
        }
        bVar5 = CARRY4(uVar4,param_3);
        param_3 = uVar4 + param_3;
        if (bVar5) {
          iVar3 = 0x22;
          goto LAB_0801ede8;
        }
      }
      iVar3 = FUN_08011da8(local_18,param_1,iVar2,param_3);
    }
  }
LAB_0801ede8:
  *(int *)(param_1 + 0x410) = iVar3;
  return 0;
}




/* 0x0801eea0 */
undefined4 FUN_0801eea0(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = FUN_08025660(0);
  uVar2 = FUN_0801eecc(param_1,param_2,param_3,uVar1);
  FUN_08025778(uVar1);
  return uVar2;
}




/* 0x0801eecc */
undefined4 FUN_0801eecc(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; int param_3; undefined4 * param_4;
{
  int iVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  uint local_70;
  undefined4 uStack_6c;
  undefined1 auStack_68 [3];
  char local_65;
  undefined4 local_50;
  undefined1 auStack_4c [24];
  int local_34;
  uint local_30;
  undefined4 uStack_2c;
  undefined1 auStack_28 [4];
  int local_24;
  
  iVar1 = DAT_0804cd58;
  local_24 = DAT_0804cd58;
  iVar3 = FUN_08012524(param_1,param_2,&local_50);
  if (iVar3 == 0) {
    iVar3 = 0;
    iVar6 = 0;
    do {
      uVar4 = (uint)*(byte *)(param_3 + iVar6);
      if (uVar4 - 0x61 < 0x1a) {
        uVar4 = uVar4 - 0x20 & 0xff;
      }
      uVar2 = (undefined1)uVar4;
      if (uVar4 < 0x20) {
        uVar2 = 0x20;
      }
      else {
        iVar6 = iVar6 + 1;
      }
      *(undefined1 *)((int)&local_30 + iVar3) = uVar2;
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0xb);
    iVar3 = FUN_080127a0(local_50,param_2,0);
    if (iVar3 == 0) {
      iVar3 = 0x13;
    }
    else {
      do {
        iVar6 = FUN_080129f0(local_50,&local_70,iVar3);
        if (iVar6 == 9) {
LAB_0801ef82:
          iVar3 = FUN_08011458(local_50,iVar3,0);
          if (iVar3 == 0) {
            FUN_080114a4(local_50,0,auStack_4c);
            *param_4 = param_2;
            *(undefined2 *)(param_4 + 1) = 0;
            *(undefined2 *)(param_4 + 0x81) = 0x58;
            *(undefined2 *)((int)param_4 + 0x206) = 0;
            iVar3 = FUN_080109e8(local_50,param_4,auStack_4c,&local_34);
            if (iVar3 == 0) {
              FUN_08012630(local_34,&local_30,auStack_28);
              *(undefined1 *)(local_34 + 0xb) = 8;
              iVar3 = FUN_080131ca(local_50);
            }
            else {
              iVar3 = 7;
            }
          }
          goto LAB_0801efd4;
        }
        if (iVar6 != 0) goto LAB_0801ef32;
        if ((local_70 & 0xff) == 0) goto LAB_0801ef82;
      } while (((local_70 & 0xff) == 0xe5) || (local_65 != '\b'));
      local_70 = local_30;
      uStack_6c = uStack_2c;
      FUN_08006bdc(auStack_68,auStack_28,3);
      iVar6 = FUN_08012bdc(local_50,iVar3,0xffffffff);
      if (iVar6 == 0) {
        iVar6 = FUN_0801317a(local_50,&local_70,iVar3);
      }
LAB_0801ef32:
      iVar3 = FUN_08011458(local_50,iVar3,iVar6);
    }
  }
LAB_0801efd4:
  uVar5 = FUN_0801eff4(param_1,iVar3);
  if (local_24 != iVar1) {
    FUN_08010960();
  }
  return uVar5;
}




/* 0x0801eff4 */
undefined4 FUN_0801eff4(param_1, param_2)
int param_1; undefined4 param_2;
{
  *(undefined4 *)(param_1 + 0x410) = param_2;
  return param_2;
}




/* 0x0801effe */
void FUN_0801effe(param_1, param_2)
int param_1; undefined4 param_2;
{
  *(undefined4 *)(param_1 + 0x410) = param_2;
  return;
}




/* 0x0801f004 */
undefined4 FUN_0801f004(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = FUN_08025618(0);
  uVar2 = FUN_08025660(0);
  uVar3 = FUN_0801f03c(param_1,param_2,uVar2,uVar1);
  FUN_08025778(uVar2);
  FUN_08025760(uVar1);
  return uVar3;
}




/* 0x0801f03c */
undefined4 FUN_0801f03c(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 * param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 auStack_50 [24];
  undefined4 local_38 [6];
  int local_20;
  int local_1c;
  
  iVar1 = FUN_08012ed8();
  if (iVar1 == 0) {
    puVar2 = param_3 + 0x81;
    iVar1 = FUN_080112f0(puVar2,1);
    if (iVar1 == 0) {
      iVar1 = FUN_08012524(param_1,*param_3,&local_20);
      if (iVar1 != 0) goto LAB_0801f102;
      iVar1 = FUN_08011c30(local_20,param_3,local_38);
      if (iVar1 != 0) {
        FUN_08006bdc(auStack_50,local_38,0x18);
        iVar1 = FUN_080274a0(puVar2);
        if ((iVar1 != 0) || (iVar1 = FUN_080274ba(puVar2), iVar1 != 0)) goto LAB_0801f04e;
        iVar1 = FUN_08011af0(local_20,puVar2,auStack_50,&local_1c,param_4,0);
        if (iVar1 == 0) {
          iVar1 = 5;
          goto LAB_0801f102;
        }
        if (-1 < (int)((uint)*(byte *)(local_1c + 0xb) << 0x1b)) {
          if ((*(byte *)(local_1c + 0xb) & 1) == 0) {
            iVar1 = FUN_080112a8(*param_3,auStack_50);
            if (iVar1 == 0) {
              *(undefined1 *)(local_20 + 0x861c) = 0;
              iVar1 = FUN_08012b48(local_20,*param_3,local_38[0],param_4);
              if (iVar1 == 0) {
                uVar3 = FUN_080122f8(local_20,local_1c);
                iVar1 = FUN_08012ad0(local_20,uVar3);
                if (iVar1 == 0) {
                  iVar1 = FUN_08011a1e(local_20,0);
                }
              }
            }
            else {
              iVar1 = 0xc;
            }
          }
          else {
            iVar1 = 0xd;
          }
          goto LAB_0801f102;
        }
      }
      iVar1 = 3;
      goto LAB_0801f102;
    }
  }
LAB_0801f04e:
  iVar1 = 4;
LAB_0801f102:
  FUN_0801eff4(param_1,iVar1);
  return 0;
}




/* 0x0801f11a */
undefined4 FUN_0801f11a(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; int param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 local_18;
  
  local_18 = param_4;
  iVar1 = FUN_08012ed8();
  if ((iVar1 == 0) && (iVar1 = FUN_080112f0(param_3 + 0x41c,0), iVar1 == 0)) {
    iVar1 = FUN_08012524(param_1,*(undefined4 *)(param_3 + 0x218),&local_18);
    if (iVar1 == 0) {
      iVar1 = FUN_08011c30(local_18,param_3 + 0x218,param_3 + 0x61c);
      if (iVar1 == 0) {
        iVar1 = 3;
      }
      else {
        iVar1 = FUN_0801f172(param_1,param_3);
      }
    }
  }
  else {
    iVar1 = 4;
  }
  FUN_0801eff4(param_1,iVar1);
  return 0;
}




/* 0x0801f172 */
undefined4 FUN_0801f172(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = FUN_08025618(0);
  uVar2 = FUN_0801f196(param_1,param_2,uVar1);
  FUN_08025760(uVar1);
  return uVar2;
}




/* 0x0801f196 */
undefined4 FUN_0801f196(param_1, param_2, param_3)
undefined4 param_1; int param_2; undefined4 param_3;
{
  undefined1 *puVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int local_20;
  int local_1c;
  undefined4 local_18;
  
  iVar3 = FUN_08012524(param_1,*(undefined4 *)(param_2 + 0x218),&local_1c);
  if (iVar3 == 0) {
    iVar5 = param_2 + 0x61c;
    iVar3 = FUN_08011af0(local_1c,param_2 + 0x41c,iVar5,&local_20,param_3,1);
    if (iVar3 == 0) {
      iVar3 = 9;
    }
    else {
      iVar3 = 0;
      do {
        iVar6 = param_2 + iVar3;
        puVar1 = (undefined1 *)(local_20 + iVar3);
        iVar3 = iVar3 + 1;
        *(undefined1 *)(iVar6 + 0x200) = *puVar1;
      } while (iVar3 < 8);
      iVar3 = 0;
      do {
        iVar6 = local_20 + iVar3;
        iVar7 = param_2 + iVar3;
        iVar3 = iVar3 + 1;
        *(undefined1 *)(iVar7 + 0x208) = *(undefined1 *)(iVar6 + 8);
      } while (iVar3 < 3);
      FUN_08006bdc(param_2,param_3,0x200);
      iVar3 = FUN_080274a0(param_3);
      if (iVar3 == 0) {
        FUN_08010962(local_1c + 0x81e4,param_2 + 0x21c,param_3,local_20,iVar5);
      }
      *(undefined1 *)(param_2 + 0x20b) = *(undefined1 *)(local_20 + 0xb);
      uVar2 = FUN_08011f68(local_20 + 0x18);
      *(undefined2 *)(param_2 + 0x20e) = uVar2;
      uVar2 = FUN_08011f68(local_20 + 0x16);
      *(undefined2 *)(param_2 + 0x20c) = uVar2;
      uVar4 = FUN_08011f72(local_20 + 0x1c);
      *(undefined4 *)(param_2 + 0x210) = uVar4;
      uVar4 = FUN_080122f8(local_1c,local_20);
      *(undefined4 *)(param_2 + 0x214) = uVar4;
      iVar3 = FUN_08011bc4(&local_18,*(undefined4 *)(param_2 + 0x218),iVar5);
      if (iVar3 != 0) {
        *(undefined4 *)(param_2 + 0x210) = local_18;
      }
      *(int *)(param_2 + 0x630) = *(int *)(param_2 + 0x630) + 1;
      iVar3 = 0;
    }
  }
  FUN_0801eff4(param_1,iVar3);
  return 0;
}




/* 0x0801f280 */
undefined4 FUN_0801f280(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined2 * param_3; int param_4;
{
  short sVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined2 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  
  cVar2 = FUN_0801172c(param_2);
  if (cVar2 < 0) {
    iVar4 = 1;
  }
  else {
    iVar7 = param_1 + cVar2 * 0x200;
    puVar6 = &DAT_87c00a48 + (short)cVar2 * 0x2298;
    iVar4 = FUN_0801267c(param_1,puVar6);
    if (iVar4 == 0) {
      iVar4 = FUN_080113d0(puVar6,0);
      if (iVar4 != 0) {
        *(undefined2 *)(iVar7 + 8) = 0;
        *puVar6 = 1;
      }
      if (param_4 != 0) {
        iVar4 = 0;
        puVar5 = param_3;
        if (param_4 != 1) {
          puVar5 = param_3 + 1;
          *param_3 = 0x2f;
          iVar4 = param_4 + -2;
        }
        for (iVar3 = 0;
            (iVar3 < iVar4 &&
            (sVar1 = *(short *)(iVar7 + 8 + iVar3 * 2), puVar5[iVar3] = sVar1, sVar1 != 0));
            iVar3 = iVar3 + 1) {
        }
        puVar5[iVar3] = 0;
      }
      iVar4 = 0;
    }
  }
  FUN_0801eff4(param_1,iVar4);
  return 0;
}




/* 0x0801f30c */
undefined4 FUN_0801f30c(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = FUN_08025618(0);
  uVar2 = FUN_08025660(0);
  uVar3 = FUN_0801f344(param_1,param_2,uVar2,uVar1);
  FUN_08025778(uVar2);
  FUN_08025760(uVar1);
  return uVar3;
}




/* 0x0801f344 */
undefined4 FUN_0801f344(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 * param_3; undefined4 param_4;
{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 local_58;
  int local_54;
  int *local_50 [2];
  undefined4 local_48 [3];
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30 [3];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar2 = FUN_08012ed8();
  if (iVar2 == 0) {
    puVar3 = param_3 + 0x81;
    iVar2 = FUN_080112f0(puVar3,1);
    if (iVar2 == 0) {
      iVar2 = FUN_08012524(param_1,*param_3,local_50);
      if (iVar2 != 0) goto LAB_0801f50a;
      iVar2 = FUN_08011c30(local_50[0],param_3,local_30);
      if (iVar2 == 0) {
        iVar2 = 3;
        goto LAB_0801f50a;
      }
      local_48[0] = local_30[0];
      local_3c = local_24;
      local_38 = local_20;
      local_34 = local_1c;
      iVar2 = FUN_080274a0(puVar3);
      if ((iVar2 == 0) && (iVar2 = FUN_080274ba(puVar3), iVar2 == 0)) {
        iVar2 = FUN_08011af0(local_50[0],puVar3,local_48,&local_54,param_4,0);
        if (iVar2 == 0) {
          local_48[0] = local_30[0];
          local_3c = local_24;
          local_38 = local_20;
          local_34 = local_1c;
          iVar2 = FUN_08010fe0(local_50[0],&local_58);
          if ((iVar2 == 0) &&
             (iVar2 = FUN_080109e8(local_50[0],param_3,local_48,&local_54), iVar2 == 0)) {
            *(byte *)(local_54 + 0xb) = *(byte *)(local_54 + 0xb) | 0x10;
            iVar4 = FUN_08012488();
            if (iVar4 == 0) {
              iVar2 = 7;
            }
            else {
              FUN_080114a4(local_50[0],local_58,iVar4 + 0xe30);
              FUN_08012eac(local_50[0],local_54,local_58);
              iVar6 = iVar4 + 0x1c;
              local_54 = iVar6;
              FUN_08012630(iVar6,".       ",&DAT_0801f520);
              *(undefined1 *)(local_54 + 0xb) = 0x10;
              FUN_08012eac(local_50[0],local_54,local_58);
              local_54 = local_54 + 0x20;
              FUN_08012630(local_54,"..      ",&DAT_0801f520);
              *(undefined1 *)(local_54 + 0xb) = 0x10;
              FUN_08012eac(local_50[0],local_54,local_30[0]);
              local_54 = local_54 + 0x20;
              uVar5 = 2;
              do {
                FUN_08006cd0(local_54,0x20);
                uVar5 = uVar5 + 1;
                local_54 = local_54 + 0x20;
              } while (uVar5 < 0x10);
              iVar2 = FUN_08013284(local_50[0],iVar6,*(undefined4 *)(iVar4 + 0xe3c),1);
              if (iVar2 == 0) {
                *(int *)(iVar4 + 0xe3c) = *(int *)(iVar4 + 0xe3c) + 1;
                uVar5 = 0;
                local_54 = iVar6;
                do {
                  FUN_08006cd0(local_54,0x20);
                  uVar5 = uVar5 + 1;
                  local_54 = local_54 + 0x20;
                } while (uVar5 < 2);
                while (iVar1 = iVar6, *(uint *)(iVar4 + 0xe3c) < *(uint *)(iVar4 + 0xe40)) {
                  while (local_54 = iVar1,
                        iVar2 = FUN_08013284(local_50[0],iVar6,*(undefined4 *)(iVar4 + 0xe3c),1),
                        iVar2 != 0) {
                    if ((*local_50[0] != 2) ||
                       (iVar2 = FUN_08011618(local_50[0],iVar4), iVar1 = local_54, iVar2 != 0))
                    goto LAB_0801f50a;
                  }
                  *(int *)(iVar4 + 0xe3c) = *(int *)(iVar4 + 0xe3c) + 1;
                }
                iVar2 = FUN_08012d54(local_50[0],*(undefined4 *)(iVar4 + 0xe30),0xffffff8);
                if (((iVar2 == 0) && (iVar2 = FUN_08013228(local_50[0]), iVar2 == 0)) &&
                   (iVar2 = FUN_08011a1e(local_50[0]), iVar2 == 0)) {
                  iVar2 = FUN_080131ca(local_50[0]);
                }
              }
            }
          }
        }
        else {
          iVar2 = 6;
        }
        goto LAB_0801f50a;
      }
    }
  }
  iVar2 = 4;
LAB_0801f50a:
  FUN_0801eff4(param_1,iVar2);
  return 0;
}




/* 0x0801f540 */
undefined8 FUN_0801f540(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  uVar1 = FUN_08025618(0);
  uVar2 = FUN_08025618(0);
  uVar3 = FUN_08025660(0);
  uVar4 = FUN_08025660(0);
  uVar6 = uVar4;
  uVar5 = FUN_0801f59a(param_1,param_2,param_3,uVar3,uVar4,uVar1,uVar2);
  FUN_08025778(uVar3);
  FUN_08025778(uVar4);
  FUN_08025760(uVar1);
  FUN_08025760(uVar2);
  return CONCAT44(uVar6,uVar5);
}




/* 0x0801f59a */
undefined4 FUN_0801f59a(param_1, param_2, param_3, param_4, param_5, param_6, param_7)
undefined4 param_1; undefined4 param_2; undefined4 param_3; int * param_4; int * param_5; undefined4 param_6; undefined4 param_7;
{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int *piVar6;
  char *pcVar7;
  int *piVar8;
  bool bVar9;
  char local_e0;
  char local_df;
  undefined1 auStack_d8 [4];
  undefined1 local_d4;
  int local_c0;
  undefined4 local_bc [3];
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  int local_a4 [3];
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c [3];
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  int local_74 [3];
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  int *local_5c;
  int local_58;
  undefined1 auStack_54 [12];
  undefined4 local_48;
  int local_3c [2];
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  int *piStack_28;
  
  local_34 = param_1;
  uStack_30 = param_2;
  local_2c = param_3;
  piStack_28 = param_4;
  iVar3 = FUN_08012ed8(param_1,param_2,param_4);
  if (iVar3 == 0) {
    local_5c = param_4 + 0x81;
    iVar3 = FUN_080112f0(local_5c,1);
    if (iVar3 == 0) {
      iVar3 = FUN_08012524(local_34,*param_4,&local_c0);
      if (iVar3 != 0) goto LAB_0801f910;
      iVar3 = FUN_08011c30(local_c0,param_4,local_8c);
      if (iVar3 == 0) goto LAB_0801f628;
      local_bc[0] = local_8c[0];
      local_b0 = local_80;
      local_ac = local_7c;
      local_a8 = local_78;
      iVar3 = FUN_080274a0(local_5c);
      if ((iVar3 != 0) || (iVar3 = FUN_080274ba(local_5c), iVar3 != 0)) goto LAB_0801f5b2;
      iVar3 = FUN_08011af0(local_c0,local_5c,local_bc,local_3c,param_6,0);
      if (iVar3 != 0) {
        bVar1 = *(byte *)(local_3c[0] + 0xb);
        if ((bVar1 & 1) != 0) {
          iVar3 = 0xd;
          goto LAB_0801f910;
        }
        FUN_08006a30(&local_e0,local_3c[0],0x20);
        piVar8 = param_5 + 0x81;
        if ((int)((uint)bVar1 << 0x1b) < 0) {
          iVar4 = FUN_080122f8(local_c0,&local_e0);
          iVar3 = FUN_08012ed8(local_34,local_2c,param_5);
          if ((iVar3 != 0) || (iVar3 = FUN_080112f0(piVar8,1), iVar3 != 0)) goto LAB_0801f5b2;
          if (*param_5 != *param_4) {
LAB_0801f672:
            iVar3 = 1;
            goto LAB_0801f910;
          }
          iVar3 = FUN_08011c30(local_c0,param_5,local_a4);
          if (iVar3 == 0) {
LAB_0801f628:
            iVar3 = 3;
            goto LAB_0801f910;
          }
          local_74[0] = local_a4[0];
          local_68 = local_98;
          local_64 = local_94;
          local_60 = local_90;
          iVar3 = FUN_080274a0(piVar8);
          if ((iVar3 == 0) && (iVar3 = FUN_080274ba(piVar8), iVar3 == 0)) {
            iVar3 = FUN_08011af0(local_c0,piVar8,local_74,&local_58,param_7,0);
            iVar2 = local_c0;
            if (iVar3 != 0) {
              if (*(char *)(local_58 + 0xb) == '\x10') {
                iVar3 = 0xe;
                goto LAB_0801f910;
              }
              goto LAB_0801f628;
            }
            pcVar7 = (char *)(local_c0 + 0x8640);
            iVar3 = local_74[0];
            while (iVar3 != iVar4) {
              FUN_080114a4(local_c0,iVar3,auStack_54);
              iVar3 = FUN_08012326(local_c0,local_48);
              if (iVar3 != 0) goto LAB_0801f910;
              if (((*pcVar7 != '.') || (*(char *)(iVar2 + 0x8641) != '.')) ||
                 (*(char *)(iVar2 + 0x8642) != ' ')) {
                iVar3 = FUN_080109e8(local_c0,param_5,local_a4,&local_58);
                if (iVar3 != 0) goto LAB_0801f910;
                *(undefined1 *)(local_c0 + 0x861c) = 0;
                FUN_08006a30(&local_e0,local_58,8);
                FUN_08006a30(auStack_d8,local_58 + 8,3);
                local_d4 = *(undefined1 *)(local_58 + 0xc);
                FUN_08006a30(local_58,&local_e0,0x20);
                iVar3 = FUN_080131ca(local_c0);
                if (iVar3 != 0) goto LAB_0801f910;
                local_bc[0] = local_8c[0];
                local_b0 = local_80;
                local_ac = local_7c;
                local_a8 = local_78;
                iVar3 = FUN_08011af0(local_c0,local_5c,local_bc,local_3c,param_6,0);
                if (iVar3 == 0) goto LAB_0801f62c;
                iVar3 = FUN_08012b48(local_c0,*param_4,local_8c[0],param_6);
                if (iVar3 != 0) goto LAB_0801f910;
                uVar5 = FUN_080122f8(local_c0,&local_e0);
                piVar6 = (int *)FUN_080127a0(local_c0,*param_4,uVar5);
                bVar9 = piVar6 == (int *)0x0;
                param_4 = piVar6;
                goto LAB_0801f7a8;
              }
              iVar3 = FUN_080122f8(local_c0,pcVar7);
            }
          }
          goto LAB_0801f5b2;
        }
        iVar3 = FUN_080112a8(*param_4,local_bc);
        if (iVar3 != 0) {
          iVar3 = 0xc;
          goto LAB_0801f910;
        }
        iVar3 = FUN_08012ed8(local_34,local_2c,param_5);
        bVar9 = iVar3 == 0;
        do {
          do {
            do {
              if (!bVar9) goto LAB_0801f5b2;
              iVar3 = FUN_080112f0(piVar8,1);
              bVar9 = iVar3 == 0;
            } while (!bVar9);
            if (*param_5 != *param_4) goto LAB_0801f672;
            iVar3 = FUN_08011c30(local_c0,param_5,local_a4);
            bVar9 = true;
            piVar6 = (int *)0x0;
            if (iVar3 == 0) goto LAB_0801f7a8;
            local_74[0] = local_a4[0];
            local_68 = local_98;
            local_64 = local_94;
            local_60 = local_90;
            iVar3 = FUN_080274a0(local_5c);
            bVar9 = iVar3 == 0;
          } while (!bVar9);
          iVar3 = FUN_080274ba(local_5c);
          bVar9 = iVar3 == 0;
        } while (!bVar9);
        iVar3 = FUN_08011af0(local_c0,piVar8,local_74,&local_58,param_7,0);
        if (iVar3 != 0) {
          if (*(char *)(local_58 + 0xb) == '\x10') {
            iVar3 = 0x25;
          }
          else {
            iVar3 = 6;
          }
          goto LAB_0801f910;
        }
        iVar3 = FUN_080109e8(local_c0,param_5,local_a4,&local_58);
        if (iVar3 != 0) goto LAB_0801f910;
        FUN_08006a30(&local_e0,local_58,8);
        FUN_08006a30(auStack_d8,local_58 + 8,3);
        local_d4 = *(undefined1 *)(local_58 + 0xc);
        FUN_08006a30(local_58,&local_e0,0x20);
        iVar3 = FUN_080131ca(local_c0);
        if (iVar3 != 0) goto LAB_0801f910;
        local_bc[0] = local_8c[0];
        local_b0 = local_80;
        local_ac = local_7c;
        local_a8 = local_78;
        iVar3 = FUN_08011af0(local_c0,local_5c,local_bc,local_3c,param_6,0);
        if (iVar3 != 0) {
          iVar3 = FUN_08012b48(local_c0,*param_4,local_8c[0],param_6);
          goto LAB_0801f910;
        }
      }
LAB_0801f62c:
      iVar3 = 5;
      goto LAB_0801f910;
    }
  }
LAB_0801f5b2:
  iVar3 = 4;
LAB_0801f910:
  FUN_0801eff4(local_34,iVar3);
  return 0;
LAB_0801f7a8:
  if (!bVar9) {
    iVar3 = FUN_08012bdc(local_c0,piVar6,1,0);
    if (((iVar3 == 0) && (iVar3 = FUN_080129f0(local_c0,&local_e0,param_4), iVar3 == 0)) &&
       (iVar3 = FUN_08012bdc(local_c0,param_4,0xffffffff,1), iVar3 == 0)) {
      if ((local_e0 == '.') && (local_df == '.')) {
        FUN_08012eac(local_c0,&local_e0,local_a4[0]);
        iVar3 = FUN_0801317a(local_c0,&local_e0,param_4);
      }
      else {
        iVar3 = 3;
      }
    }
    iVar3 = FUN_08011458(local_c0,param_4,iVar3);
    goto LAB_0801f910;
  }
  goto LAB_0801f628;
}




/* 0x0801f91c */
undefined4 FUN_0801f91c(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = FUN_08025618(0);
  uVar2 = FUN_08025660(0);
  uVar3 = FUN_0801f958(param_1,param_2,param_3,uVar2,uVar1);
  FUN_08025778(uVar2);
  FUN_08025760(uVar1);
  return uVar3;
}




/* 0x0801f958 */
undefined4 FUN_0801f958(param_1, param_2, param_3, param_4, param_5)
undefined4 param_1; undefined4 param_2; short * param_3; undefined4 * param_4; undefined4 param_5;
{
  short sVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  char cVar9;
  int iStack_30;
  int iStack_2c;
  int local_28;
  
  cVar9 = '\0';
  local_28 = 0;
  sVar1 = *param_3;
  if (sVar1 == 0x72) {
    if (param_3[1] == 0) {
      cVar9 = '\x01';
    }
    else if ((param_3[1] == 0x2b) && (param_3[2] == 0)) {
      cVar9 = '\x04';
    }
  }
  else if (sVar1 == 0x77) {
    if (param_3[1] == 0) {
      cVar9 = '\x02';
    }
    else if ((param_3[1] == 0x2b) && (param_3[2] == 0)) {
      cVar9 = '\x05';
    }
  }
  else if (sVar1 == 0x61) {
    if (param_3[1] == 0) {
      cVar9 = '\x03';
    }
    else if ((param_3[1] == 0x2b) && (param_3[2] == 0)) {
      cVar9 = '\x06';
    }
  }
  iVar2 = FUN_08012ed8(param_1,param_2,param_4);
  if (iVar2 == 0) {
    puVar3 = param_4 + 0x81;
    iVar2 = FUN_080112f0(puVar3,1);
    if (iVar2 == 0) {
      iVar2 = FUN_08012524(param_1,*param_4,&iStack_2c);
      if (iVar2 != 0) {
        iVar2 = 1;
        goto LAB_0801fdae;
      }
      puVar4 = (undefined4 *)FUN_08012488();
      if (puVar4 == (undefined4 *)0x0) {
        iVar2 = 7;
        goto LAB_0801fdae;
      }
      puVar4[3] = *param_4;
      puVar4[0x398] = 0;
      puVar4[0x3ab] = 0;
      iVar2 = FUN_080274a0(puVar3);
      if ((iVar2 != 0) || (iVar2 = FUN_080274ba(puVar3), iVar2 != 0)) goto LAB_0801f9c6;
      if (true) {
        switch(cVar9) {
        default:
          goto LAB_0801fdbe;
        case '\x01':
        case '\x04':
          puVar8 = puVar4 + 0x392;
          iStack_30 = FUN_080133a4(iStack_2c + 0x81e4,param_4 + 1,puVar3);
          if (iStack_30 == 0) {
            iVar2 = FUN_08011c30(iStack_2c,param_4,puVar8);
            if (iVar2 != 0) {
              iVar2 = FUN_08011af0(iStack_2c,puVar3,puVar8,&iStack_30,param_5,0);
              if (iVar2 == 0) {
                iVar2 = 5;
                break;
              }
              goto LAB_0801fa62;
            }
          }
          else {
LAB_0801fa62:
            *(undefined1 *)(iStack_2c + 0x861c) = 0;
            if (-1 < (int)((uint)*(byte *)(iStack_30 + 0xb) << 0x1b)) {
              if (cVar9 == '\x04') {
                if ((*(byte *)(iStack_30 + 0xb) & 1) != 0) goto LAB_0801fa94;
                iVar2 = FUN_080112a8(*param_4,puVar8);
              }
              else {
                iVar2 = FUN_08011334(iStack_2c,*param_4,puVar8,&local_28);
              }
              if (iVar2 == 0) {
                if (local_28 == 0) {
                  iVar2 = FUN_080122f8(iStack_2c,iStack_30);
                  puVar4[0x38b] = iVar2;
                  if (iVar2 == 0) goto LAB_0801fb26;
                  FUN_080114a4(iStack_2c,iVar2,puVar4 + 0x38c);
                  uVar5 = FUN_08011f72(iStack_30 + 0x1c);
                  puVar4[6] = uVar5;
                  FUN_08013426(puVar4,iStack_2c);
                }
                else {
                  puVar4[0x38f] = 0;
                  puVar4[0x390] = 0;
                  uVar5 = *(undefined4 *)(local_28 + 0x18);
                  puVar4[0x38b] = 0;
                  puVar4[6] = uVar5;
                  puVar4[0x3ab] = local_28;
                  FUN_08013426(puVar4,iStack_2c);
                  iVar2 = *(int *)(local_28 + 0xe2c);
                  if (iVar2 == 0) goto LAB_0801fc24;
                  puVar4[0x38b] = iVar2;
                  FUN_080114a4(iStack_2c,iVar2,puVar4 + 0x38c);
                }
                puVar4[4] = 0xfffffe00;
                iVar2 = FUN_08011da8(iStack_2c,param_1,puVar4,0);
                if (iVar2 == 0) goto LAB_0801fc24;
                break;
              }
              goto LAB_0801faa2;
            }
          }
LAB_0801fa78:
          iVar2 = 3;
          break;
        case '\x02':
        case '\x05':
          iStack_30 = FUN_080133a4(iStack_2c + 0x81e4,param_4 + 1,puVar3);
          if (iStack_30 == 0) {
            iVar2 = FUN_08011c30(iStack_2c,param_4,puVar4 + 0x392);
            if (iVar2 == 0) goto LAB_0801fa78;
            FUN_080114a4(iStack_2c,puVar4[0x392],puVar4 + 0x38c);
            iVar2 = FUN_08011af0(iStack_2c,puVar3,puVar4 + 0x38c,&iStack_30,param_5,0);
            if (iVar2 == 0) {
              iStack_30 = 0;
            }
          }
          *(undefined1 *)(iStack_2c + 0x861c) = 0;
          if (iStack_30 != 0) {
            uVar5 = FUN_080219a8();
            uVar6 = FUN_080122f8(iStack_2c,iStack_30);
            if ((int)((uint)*(byte *)(iStack_30 + 0xb) << 0x1b) < 0) goto LAB_0801fa78;
            if ((*(byte *)(iStack_30 + 0xb) & 1) == 0) {
              puVar4[0x392] = puVar4[0x38c];
              puVar4[0x397] = puVar4[0x391];
              puVar4[0x395] = puVar4[0x38f];
              puVar4[0x396] = puVar4[0x390];
              iVar2 = FUN_080112a8(*param_4,puVar4 + 0x392);
              if (iVar2 != 0) goto LAB_0801faa2;
              *(undefined1 *)(iStack_30 + 0x1c) = 0;
              *(undefined1 *)(iStack_30 + 0x1d) = 0;
              *(undefined1 *)(iStack_30 + 0x1e) = 0;
              *(undefined1 *)(iStack_30 + 0x1f) = 0;
              *(byte *)(iStack_30 + 0xb) = *(byte *)(iStack_30 + 0xb) | 0x20;
              *(undefined1 *)(iStack_30 + 0x1a) = 0;
              *(undefined1 *)(iStack_30 + 0x1b) = 0;
              *(undefined1 *)(iStack_30 + 0x14) = 0;
              *(undefined1 *)(iStack_30 + 0x15) = 0;
              uVar7 = FUN_08021380(uVar5);
              FUN_08012d3c(iStack_30 + 0x10,uVar7);
              uVar7 = FUN_080213c0(uVar5);
              FUN_08012d3c(iStack_30 + 0xe,uVar7);
              uVar5 = FUN_08021380(uVar5);
              FUN_08012d3c(iStack_30 + 0x12,uVar5);
              iVar2 = FUN_080131ca(iStack_2c);
              if (iVar2 != 0) break;
              iVar2 = FUN_08012ad0(iStack_2c,uVar6);
              goto LAB_0801fd76;
            }
LAB_0801fa94:
            iVar2 = 0xd;
            break;
          }
LAB_0801fd84:
          iVar2 = FUN_080109e8(iStack_2c,param_4,puVar4 + 0x392,&iStack_30);
          if (iVar2 != 0) break;
          puVar4[5] = 0;
          puVar4[4] = 0;
          puVar4[6] = 0;
          puVar4[0x38b] = 0;
          puVar4[0x38d] = 0;
          puVar4[1] = 0;
          *(byte *)(iStack_30 + 0xb) = *(byte *)(iStack_30 + 0xb) | 0x20;
          iVar2 = FUN_080131ca(iStack_2c);
LAB_0801fd76:
          if (iVar2 != 0) break;
          puVar4[0x38b] = 0;
LAB_0801fb26:
          puVar4[0x38f] = 0;
          puVar4[0x390] = 0;
          FUN_08013426(puVar4,iStack_2c);
LAB_0801fc24:
          puVar4[0x8a] = puVar4 + 0x8b;
          *(char *)(puVar4 + 2) = cVar9;
          FUN_0801effe(param_1,0);
          return *puVar4;
        case '\x03':
        case '\x06':
          puVar8 = puVar4 + 0x38c;
          iStack_30 = FUN_080133a4(iStack_2c + 0x81e4,param_4 + 1,puVar3);
          if (iStack_30 == 0) {
            iVar2 = FUN_08011c30(iStack_2c,param_4,puVar4 + 0x392);
            if (iVar2 == 0) goto LAB_0801fa78;
            puVar4[0x38c] = puVar4[0x392];
            puVar4[0x391] = puVar4[0x397];
            puVar4[0x38f] = puVar4[0x395];
            puVar4[0x390] = puVar4[0x396];
            iVar2 = FUN_08011af0(iStack_2c,puVar3,puVar8,&iStack_30,param_5,0);
            if (iVar2 == 0) {
              iStack_30 = 0;
            }
          }
          *(undefined1 *)(iStack_2c + 0x861c) = 0;
          if (iStack_30 == 0) {
            puVar4[0x392] = puVar4[0x38c];
            puVar4[0x397] = puVar4[0x391];
            puVar4[0x395] = puVar4[0x38f];
            puVar4[0x396] = puVar4[0x390];
            FUN_080114a4(iStack_2c,puVar4[0x38c],puVar8);
            goto LAB_0801fd84;
          }
          if ((int)((uint)*(byte *)(iStack_30 + 0xb) << 0x1b) < 0) goto LAB_0801fa78;
          if ((*(byte *)(iStack_30 + 0xb) & 1) != 0) goto LAB_0801fa94;
          iVar2 = FUN_08011244(*param_4,puVar4 + 0x392,puVar4);
          if (iVar2 == 0) {
            uVar5 = FUN_080122f8(iStack_2c,iStack_30);
            puVar4[0x38b] = uVar5;
            uVar5 = FUN_08011f72(iStack_30 + 0x1c);
            puVar4[6] = uVar5;
            FUN_08013426(puVar4,iStack_2c);
            if (puVar4[0x38b] == 0) {
              puVar4[0x38f] = 0;
              puVar4[0x390] = 0;
              puVar4[5] = 0;
              puVar4[4] = 0;
              puVar4[6] = 0;
              puVar4[0x38d] = 0;
              puVar4[1] = 0;
              goto LAB_0801fc24;
            }
            FUN_080114a4(iStack_2c,puVar4[0x38b],puVar8);
            puVar4[4] = 0xfffffe00;
            iVar2 = FUN_08011da8(iStack_2c,param_1,puVar4,puVar4[6]);
            if (iVar2 == 0) goto LAB_0801fc24;
            *(undefined1 *)(puVar4 + 2) = 0;
            break;
          }
LAB_0801faa2:
          iVar2 = 0xc;
        }
      }
      else {
LAB_0801fdbe:
        iVar2 = 0xb;
      }
      goto LAB_0801fdae;
    }
  }
LAB_0801f9c6:
  iVar2 = 4;
LAB_0801fdae:
  FUN_0801effe(param_1,iVar2);
  return 0;
}




/* 0x0801fdc8 */
undefined4 FUN_0801fdc8(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar1 = FUN_08025618(0);
  uVar2 = FUN_08025660(0);
  uVar3 = FUN_08025660(0);
  uVar4 = FUN_0801fe14(param_1,param_2,param_3,uVar2,uVar3,uVar1);
  FUN_08025778(uVar2);
  FUN_08025778(uVar3);
  FUN_08025760(uVar1);
  return uVar4;
}




/* 0x0801fe14 */
undefined4 FUN_0801fe14(param_1, param_2, param_3, param_4, param_5, param_6)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 * param_4; undefined4 * param_5; undefined4 param_6;
{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 local_80 [3];
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68 [3];
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined1 auStack_50 [8];
  undefined1 auStack_48 [4];
  undefined1 local_44;
  int local_30;
  int local_2c;
  int local_28;
  
  iVar1 = FUN_08012ed8(param_1,param_2,param_4);
  if (iVar1 == 0) {
    puVar2 = param_4 + 0x81;
    iVar1 = FUN_080112f0(puVar2,1);
    if (iVar1 == 0) {
      iVar1 = FUN_08012524(param_1,*param_4,&local_30);
      if (iVar1 != 0) goto LAB_08020002;
      iVar1 = FUN_08011c30(local_30,param_4,local_68);
      if (iVar1 == 0) {
        iVar1 = 3;
        goto LAB_08020002;
      }
      local_80[0] = local_68[0];
      local_74 = local_5c;
      local_70 = local_58;
      local_6c = local_54;
      iVar1 = FUN_080274a0(puVar2);
      if ((iVar1 == 0) && (iVar1 = FUN_080274ba(puVar2), iVar1 == 0)) {
        iVar1 = FUN_08011af0(local_30,puVar2,local_80,&local_2c,param_6,0);
        if (iVar1 == 0) {
LAB_0801fea2:
          iVar1 = 5;
          goto LAB_08020002;
        }
        if ((*(byte *)(local_2c + 0xb) & 1) != 0) {
          iVar1 = 0xd;
          goto LAB_08020002;
        }
        iVar1 = FUN_080112a8(*param_4,local_80);
        if (iVar1 != 0) {
          iVar1 = 0xc;
          goto LAB_08020002;
        }
        FUN_08006a30(auStack_50,local_2c,0x20);
        iVar1 = FUN_08012ed8(param_1,param_3,param_5);
        if (iVar1 == 0) {
          puVar3 = param_5 + 0x81;
          iVar1 = FUN_080112f0(puVar3,1);
          if (((iVar1 == 0) && (iVar1 = FUN_080274a0(puVar3), iVar1 == 0)) &&
             (iVar1 = FUN_080274ba(puVar3), iVar1 == 0)) {
            FUN_08006bdc(param_5 + 1,param_4 + 1,0x200);
            *param_5 = *param_4;
            local_80[0] = local_68[0];
            local_74 = local_5c;
            local_70 = local_58;
            local_6c = local_54;
            iVar1 = 0;
            while( true ) {
              uVar4 = (uint)*(ushort *)((int)param_4 + iVar1 * 2 + 0x204);
              uVar6 = uVar4;
              if (uVar4 - 0x61 < 0x1a) {
                uVar6 = uVar4 - 0x20;
              }
              uVar5 = (uint)*(ushort *)((int)param_5 + iVar1 * 2 + 0x204);
              uVar7 = uVar5;
              if (uVar5 - 0x61 < 0x1a) {
                uVar7 = uVar5 - 0x20;
              }
              if (uVar6 != uVar7) break;
              if ((uVar4 == 0) || (uVar5 == 0)) goto LAB_0801ff6e;
              iVar1 = iVar1 + 1;
            }
            iVar1 = FUN_08011af0(local_30,puVar3,local_80,&local_28,param_6,0);
            if (iVar1 != 0) {
              if (*(char *)(local_28 + 0xb) == '\x10') {
                iVar1 = 0x25;
              }
              else {
                iVar1 = 6;
              }
              goto LAB_08020002;
            }
LAB_0801ff6e:
            local_80[0] = local_68[0];
            local_74 = local_5c;
            local_70 = local_58;
            local_6c = local_54;
            iVar1 = FUN_080109e8(local_30,param_5,local_80,&local_2c);
            if (iVar1 != 0) goto LAB_08020002;
            *(undefined1 *)(local_30 + 0x861c) = 0;
            FUN_08006a30(auStack_50,local_2c,8);
            FUN_08006a30(auStack_48,local_2c + 8,3);
            local_44 = *(undefined1 *)(local_2c + 0xc);
            FUN_08006a30(local_2c,auStack_50,0x20);
            iVar1 = FUN_080131ca(local_30);
            if (iVar1 != 0) goto LAB_08020002;
            local_80[0] = local_68[0];
            local_74 = local_5c;
            local_70 = local_58;
            local_6c = local_54;
            iVar1 = FUN_08011af0(local_30,puVar2,local_80,&local_2c,param_6,0);
            if (iVar1 != 0) {
              iVar1 = FUN_08012b48(local_30,*param_4,local_68[0],param_6);
              goto LAB_08020002;
            }
            goto LAB_0801fea2;
          }
        }
      }
    }
  }
  iVar1 = 4;
LAB_08020002:
  FUN_0801eff4(param_1,iVar1);
  return 0;
}




/* 0x0802000e */
int FUN_0802000e(param_1, param_2, param_3, param_4, param_5)
int param_1; int param_2; int param_3; int param_4; undefined4 param_5;
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int local_38;
  int local_34;
  int local_30;
  uint local_2c;
  
  local_38 = param_1;
  local_34 = param_2;
  local_30 = param_3;
  local_2c = param_4;
  iVar2 = FUN_08011218(param_5);
  local_30 = 0;
  local_34 = 0;
  if ((iVar2 == 0) ||
     ((((cVar1 = *(char *)(iVar2 + 8), cVar1 != '\x02' && (cVar1 != '\x03')) && (cVar1 != '\x04'))
      && ((cVar1 != '\x05' && (cVar1 != '\x06')))))) {
    iVar3 = 8;
  }
  else {
    iVar3 = FUN_08012524(param_1,*(undefined4 *)(iVar2 + 0xc),&local_38);
    if (iVar3 == 0) {
      if (*(int *)(iVar2 + 0xe64) != 0) {
        *(undefined4 *)(iVar2 + 0xe64) = 0;
        FUN_08013350(local_38,param_1,iVar2);
      }
      uVar8 = param_4 * param_3;
      if ((int)uVar8 < 1) {
        iVar3 = 0x1c;
      }
      else {
        local_2c = *(uint *)(iVar2 + 0x18);
        if ((local_2c < local_2c + uVar8) && (local_2c + uVar8 != 0)) {
          *(undefined4 *)(iVar2 + 0x21c) = 0;
          iVar3 = 0;
          do {
            iVar6 = iVar3;
            if (*(int *)(iVar2 + 0x14) == 0x200) {
              iVar3 = FUN_080117ea(local_38,iVar2,local_34);
              if (iVar3 != 0) {
                *(uint *)(iVar2 + 0x18) = local_2c;
                iVar2 = FUN_080109ac(local_38,iVar2);
                if (iVar2 == 0) {
                  *(int *)(param_1 + 0x410) = iVar3;
                  return local_30 / param_3;
                }
                goto LAB_080200d4;
              }
              FUN_080134a8(iVar2);
              *(int *)(iVar2 + 0x10) = *(int *)(iVar2 + 0x10) + *(int *)(iVar2 + 0x14);
              *(undefined4 *)(iVar2 + 0x14) = 0;
              *(int *)(iVar2 + 0xe3c) = *(int *)(iVar2 + 0xe3c) + 1;
              if (((0x1ff < uVar8) || (iVar3 = FUN_08012190(local_38,iVar2,0), iVar3 == 0)) ||
                 (iVar3 == 9)) goto LAB_0802011e;
LAB_08020168:
              iVar2 = FUN_080109ac(local_38,iVar2);
              if (iVar2 != 0) {
LAB_080200d4:
                *(int *)(param_1 + 0x410) = iVar3;
                return 0;
              }
              *(int *)(param_1 + 0x410) = iVar3;
              iVar3 = iVar6;
              goto LAB_08020236;
            }
LAB_0802011e:
            uVar7 = 0x200 - *(int *)(iVar2 + 0x14);
            uVar5 = uVar8;
            if (uVar7 <= uVar8) {
              uVar5 = uVar7;
            }
            *(undefined4 *)(iVar2 + 4) = 1;
            if (uVar5 == 0x200) {
              local_34 = param_2;
              if ((*(uint *)(iVar2 + 0xe60) & 1) != 0) {
                FUN_08013078(iVar2,param_2,0,0x200);
              }
              if (uVar8 == 0x200) {
                FUN_08006a30(iVar2 + 0x1c,param_2);
                *(undefined4 *)(iVar2 + 0x21c) = 1;
                iVar3 = FUN_080117ea(local_38,iVar2,local_34);
                goto LAB_08020162;
              }
            }
            else {
              FUN_08006a30(*(int *)(iVar2 + 0x14) + iVar2 + 0x1c,param_2,uVar5);
              if ((*(uint *)(iVar2 + 0xe60) & 1) != 0) {
                FUN_08013078(iVar2,iVar2 + 0x1c,*(undefined4 *)(iVar2 + 0x14),uVar5);
              }
              iVar3 = FUN_080110dc(local_38,iVar2);
LAB_08020162:
              if (iVar3 != 0) goto LAB_08020168;
            }
            uVar8 = uVar8 - uVar5;
            param_2 = param_2 + uVar5;
            iVar3 = iVar6 + uVar5;
            iVar4 = *(int *)(iVar2 + 0x14) + uVar5;
            *(int *)(iVar2 + 0x14) = iVar4;
            local_2c = *(uint *)(iVar2 + 0x18);
            uVar5 = iVar4 + *(int *)(iVar2 + 0x10);
            if (local_2c < uVar5) {
              *(uint *)(iVar2 + 0x18) = uVar5;
            }
            local_30 = iVar6;
          } while (uVar8 != 0);
          iVar6 = FUN_08011896(local_38,iVar2);
          if (iVar6 != 0) {
            *(byte *)(iVar2 + 8) = *(byte *)(iVar2 + 8) | 0x40;
            FUN_08012ad0(local_38,*(undefined4 *)(iVar2 + 0xe2c));
LAB_0802021e:
            *(int *)(param_1 + 0x410) = iVar6;
            return 0;
          }
          if ((*(uint *)(iVar2 + 0xe60) & 1) != 0) {
            iVar6 = FUN_080117ea(local_38,iVar2,0);
            if (iVar6 != 0) {
              FUN_080130f8(local_38,iVar2,1);
              *(byte *)(iVar2 + 8) = *(byte *)(iVar2 + 8) | 0x40;
              goto LAB_0802021e;
            }
            FUN_08012fe0(local_38,param_1,iVar2);
          }
          *(undefined4 *)(param_1 + 0x410) = 0;
LAB_08020236:
          return iVar3 / param_3;
        }
        iVar3 = 9;
      }
    }
  }
  *(int *)(param_1 + 0x410) = iVar3;
  return 0;
}




/* 0x0802023c */
undefined4 FUN_0802023c(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = FUN_08025618(0);
  uVar2 = FUN_08025660(0);
  uVar3 = FUN_08020274(param_1,param_2,uVar2,uVar1);
  FUN_08025778(uVar2);
  FUN_08025760(uVar1);
  return uVar3;
}




/* 0x08020274 */
undefined4 FUN_08020274(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 * param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int local_78;
  undefined4 local_74 [6];
  char local_5c;
  char local_5b;
  char local_5a;
  undefined1 auStack_3c [24];
  int local_24 [2];
  
  iVar1 = FUN_08012ed8();
  if (iVar1 == 0) {
    puVar2 = param_3 + 0x81;
    iVar1 = FUN_080112f0(puVar2,1);
    if (iVar1 == 0) {
      iVar1 = FUN_08012524(param_1,*param_3,&local_78);
      if (iVar1 != 0) goto LAB_0802038a;
      iVar1 = FUN_08011c30(local_78,param_3,local_74);
      if (iVar1 != 0) {
        FUN_08006bdc(auStack_3c,local_74,0x18);
        iVar1 = FUN_080274a0(puVar2);
        if ((iVar1 != 0) || (iVar1 = FUN_080274ba(puVar2), iVar1 != 0)) goto LAB_08020286;
        iVar1 = FUN_08011af0(local_78,puVar2,auStack_3c,local_24,param_4,0);
        if (iVar1 == 0) {
          iVar1 = 5;
          goto LAB_0802038a;
        }
        if ((int)((uint)*(byte *)(local_24[0] + 0xb) << 0x1b) < 0) {
          if ((*(byte *)(local_24[0] + 0xb) & 1) != 0) {
            iVar1 = 0xd;
            goto LAB_0802038a;
          }
          uVar3 = FUN_080122f8(local_78);
          iVar1 = FUN_080127a0(local_78,*param_3,uVar3);
          if (iVar1 != 0) {
            do {
              iVar4 = FUN_080129f0(local_78,&local_5c,iVar1);
              if (iVar4 == 9) {
LAB_08020356:
                iVar1 = FUN_08011458(local_78,iVar1,0);
                if (iVar1 == 0) {
                  *(undefined1 *)(local_78 + 0x861c) = 0;
                  iVar1 = FUN_08012b48(local_78,*param_3,local_74[0],param_4);
                  if ((iVar1 == 0) && (iVar1 = FUN_08012ad0(local_78,uVar3), iVar1 == 0)) {
                    iVar1 = FUN_08011a1e(local_78,0);
                  }
                }
                goto LAB_0802038a;
              }
              if (iVar4 != 0) goto LAB_08020326;
              if (local_5c == '\0') goto LAB_08020356;
            } while ((local_5c == -0x1b) ||
                    ((local_5c == '.' &&
                     ((local_5b == ' ' || ((local_5b == '.' && (local_5a == ' '))))))));
            iVar4 = 0xe;
LAB_08020326:
            iVar1 = FUN_08011458(local_78,iVar1,iVar4);
            goto LAB_0802038a;
          }
        }
      }
      iVar1 = 3;
      goto LAB_0802038a;
    }
  }
LAB_08020286:
  iVar1 = 4;
LAB_0802038a:
  FUN_0801eff4(param_1,iVar1);
  return 0;
}




/* 0x080203a2 */
undefined8 FUN_080203a2(param_1, param_2, param_3, param_4, param_5)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4; undefined4 param_5;
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = FUN_08025618(0);
  uVar2 = FUN_08025660(0);
  uVar3 = FUN_080203e6(param_1,param_2,param_3,param_4,param_5,uVar2,uVar1);
  FUN_08025778(uVar2);
  FUN_08025760(uVar1);
  return CONCAT44(param_5,uVar3);
}




/* 0x080203e6 */
undefined4 FUN_080203e6(param_1, param_2, param_3, param_4, param_5, param_6, param_7)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4; undefined4 param_5; undefined4 * param_6; undefined4 param_7;
{
  int iVar1;
  undefined1 auStack_40 [24];
  int local_28;
  undefined4 local_24;
  
  iVar1 = FUN_08012ed8(param_1,param_2,param_6);
  if (iVar1 == 0) {
    iVar1 = FUN_080112f0(param_6 + 0x81,1);
    if (iVar1 == 0) {
      iVar1 = FUN_08012524(param_1,*param_6,&local_24);
      if (iVar1 == 0) {
        iVar1 = FUN_08011c30(local_24,param_6,auStack_40);
        if (iVar1 == 0) {
          iVar1 = 3;
        }
        else {
          iVar1 = FUN_08011af0(local_24,param_6 + 0x81,auStack_40,&local_28,param_7,0);
          if (iVar1 == 0) {
            iVar1 = 5;
          }
          else {
            FUN_08012d3c(local_28 + 0x16,param_3);
            FUN_08012d3c(local_28 + 0x18,param_4);
            FUN_08012d3c(local_28 + 0x12,param_5);
            iVar1 = FUN_080131ca(local_24);
          }
        }
      }
      goto LAB_0802046a;
    }
  }
  iVar1 = 4;
LAB_0802046a:
  FUN_0801eff4(param_1,iVar1);
  return 0;
}




/* 0x0802047e */
undefined4 FUN_0802047e(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = FUN_08025618(0);
  uVar2 = FUN_08025660(0);
  uVar3 = FUN_080204ba(param_1,param_2,param_3,uVar2,uVar1);
  FUN_08025778(uVar2);
  FUN_08025760(uVar1);
  return uVar3;
}




/* 0x080204ba */
undefined4 FUN_080204ba(param_1, param_2, param_3, param_4, param_5)
undefined4 param_1; undefined4 param_2; byte param_3; undefined4 * param_4; undefined4 param_5;
{
  byte bVar1;
  int iVar2;
  undefined1 auStack_38 [24];
  int local_20;
  int local_1c;
  
  iVar2 = FUN_08012ed8(param_1,param_2,param_4);
  if (iVar2 == 0) {
    iVar2 = FUN_080112f0(param_4 + 0x81,1);
    if (iVar2 == 0) {
      iVar2 = FUN_08012524(param_1,*param_4,&local_20);
      if (iVar2 == 0) {
        iVar2 = FUN_08011c30(local_20,param_4,auStack_38);
        if (iVar2 == 0) {
          iVar2 = 3;
        }
        else {
          iVar2 = FUN_08011af0(local_20,param_4 + 0x81,auStack_38,&local_1c,param_5,0);
          if (iVar2 == 0) {
            iVar2 = 5;
          }
          else {
            *(undefined1 *)(local_20 + 0x861c) = 0;
            bVar1 = *(byte *)(local_1c + 0xb) & 0x18 | param_3 & 0x27;
            if (*(byte *)(local_1c + 0xb) == bVar1) {
              iVar2 = 0;
            }
            else {
              *(byte *)(local_1c + 0xb) = bVar1;
              iVar2 = FUN_080131ca(local_20);
            }
          }
        }
      }
      goto LAB_08020546;
    }
  }
  iVar2 = 4;
LAB_08020546:
  FUN_0801eff4(param_1,iVar2);
  return 0;
}




/* 0x08020552 */
undefined4 FUN_08020552(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = FUN_08025618(0);
  uVar2 = FUN_08025660(0);
  uVar3 = FUN_0802058e(param_1,param_2,param_3,uVar2,uVar1);
  FUN_08025778(uVar2);
  FUN_08025760(uVar1);
  return uVar3;
}




/* 0x0802058e */
undefined4 FUN_0802058e(param_1, param_2, param_3, param_4, param_5)
undefined4 param_1; undefined4 param_2; undefined4 * param_3; undefined4 * param_4; undefined4 param_5;
{
  undefined2 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined1 auStack_40 [24];
  int local_28;
  int local_24;
  undefined4 local_20;
  
  iVar2 = FUN_08012ed8(param_1,param_2,param_4);
  if (iVar2 == 0) {
    puVar3 = param_4 + 0x81;
    iVar2 = FUN_080112f0(puVar3,1);
    if (iVar2 == 0) {
      iVar2 = FUN_08012524(param_1,*param_4,&local_24);
      if (iVar2 != 0) goto LAB_0802066c;
      local_28 = FUN_080133a4(local_24 + 0x81e4,param_4 + 1,puVar3,auStack_40);
      if (local_28 == 0) {
        iVar2 = FUN_08011c30(local_24,param_4,auStack_40);
        if (iVar2 == 0) {
          iVar2 = 3;
          goto LAB_0802066c;
        }
        iVar2 = FUN_08011af0(local_24,puVar3,auStack_40,&local_28,param_5,0);
        if (iVar2 == 0) {
          iVar2 = 5;
          goto LAB_0802066c;
        }
        FUN_08010962(local_24 + 0x81e4,param_4 + 1,puVar3,local_28,auStack_40);
      }
      uVar4 = FUN_08011f72(local_28 + 0x1c);
      *param_3 = uVar4;
      uVar1 = FUN_08011f68(local_28 + 0x10);
      *(undefined2 *)(param_3 + 1) = uVar1;
      uVar1 = FUN_08011f68(local_28 + 0xe);
      *(undefined2 *)((int)param_3 + 6) = uVar1;
      uVar1 = FUN_08011f68(local_28 + 0x18);
      *(undefined2 *)(param_3 + 2) = uVar1;
      uVar1 = FUN_08011f68(local_28 + 0x16);
      *(undefined2 *)((int)param_3 + 10) = uVar1;
      uVar1 = FUN_08011f68(local_28 + 0x12);
      *(undefined2 *)(param_3 + 3) = uVar1;
      *(undefined1 *)((int)param_3 + 0xe) = *(undefined1 *)(local_28 + 0xb);
      param_3[4] = *param_4;
      iVar2 = FUN_08011bc4(&local_20,*param_4,auStack_40);
      if (iVar2 != 0) {
        *param_3 = local_20;
      }
      iVar2 = 0;
      goto LAB_0802066c;
    }
  }
  iVar2 = 4;
LAB_0802066c:
  FUN_0801eff4(param_1,iVar2);
  return 0;
}




/* 0x08020680 */
void FUN_08020680()
{
  return;
}




