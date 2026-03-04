/* Auto-generated: fhprg_802efa4.c */
/* Functions: 84 */
#include "globals.h"

/* 0x0802efa4 */
longlong FUN_0802efa4(param_1, param_2, param_3)
uint param_1; uint param_2; int param_3;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  uVar3 = *(uint *)(param_3 + 0x20);
  uVar2 = *(uint *)(param_3 + 0x24);
  if (uVar2 < param_2 || param_2 - uVar2 < (uint)(uVar3 <= param_1)) {
    uVar1 = param_1 - uVar3;
    uVar2 = (param_2 - uVar2) - (uint)(param_1 < uVar3);
    bVar4 = *(uint *)(param_3 + 0x18) <= uVar1;
    param_2 = uVar2 - !bVar4;
    if (uVar2 == 0 && bVar4 <= uVar2) {
      return CONCAT44(*(int *)(param_3 + 0x10),
                      *(ushort *)(param_3 + 8) * uVar1 + *(int *)(param_3 + 0x10));
    }
  }
  return (ulonglong)param_2 << 0x20;
}




/* 0x0802efd6 */
undefined4 FUN_0802efd6(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  
  iVar1 = FUN_0802efa4(param_1,param_2,param_4);
  if ((iVar1 == 0) && (iVar1 = FUN_0802ef24(param_1,param_2,param_4,param_3), iVar1 != 0)) {
    FUN_0802efa4(param_1,param_2,param_4);
    return 0;
  }
  return 0;
}




/* 0x0802f02c */
void FUN_0802f02c(param_1, param_2, param_3, param_4, param_5, param_6)
int param_1; int param_2; int param_3; uint param_4; int param_5; int param_6;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  
  iVar1 = -1;
  if (DAT_0804ded3 != '\0') {
    iVar1 = 0;
    DAT_0804ded3 = '\0';
  }
  uVar3 = param_4;
  do {
    iVar2 = iVar1;
    iVar1 = iVar2 + 1;
    uVar4 = 0x4000;
    if (uVar3 < 0x4000) {
      uVar4 = uVar3;
    }
    puVar5 = (undefined4 *)(param_1 * 0x1040 + -0x7838b700 + param_2 * 0x820 + iVar1 * 0x20);
    FUN_08006d14(puVar5,0x20);
    puVar5[1] = uVar4 * 0x10000 + 0x80;
    if (0 < iVar1) {
      puVar5[-8] = puVar5;
    }
    puVar5[2] = param_3;
    puVar5[3] = puVar5[2] & 0xfffff000;
    puVar5[3] = puVar5[3] + 0x1000;
    puVar5[4] = puVar5[3] + 0x1000;
    puVar5[5] = puVar5[4] + 0x1000;
    puVar5[6] = puVar5[5] + 0x1000;
    uVar3 = uVar3 - uVar4;
    param_3 = param_3 + uVar4;
  } while ((uVar3 != 0) && (iVar1 < 0x3f));
  if (param_6 == 0) {
    if ((((param_5 != 0) && (param_2 == 1)) && (param_4 == DAT_0804dedc * (param_4 / DAT_0804dedc)))
       && ((param_4 != 0 && (iVar2 != -2)))) {
      puVar5 = (undefined4 *)(param_1 * 0x1040 + -0x7838aee0 + (iVar2 + 2) * 0x20);
      FUN_08006d14(puVar5,0x20);
      puVar5[1] = 0x80;
      if (0 < iVar2 + 2) {
        puVar5[-8] = puVar5;
      }
      puVar5[2] = &DAT_0804dee0;
      puVar5[3] = &DAT_0804dee0;
      puVar5[4] = &DAT_0804dee0;
      puVar5[5] = &DAT_0804dee0;
      puVar5[6] = &DAT_0804dee0;
    }
    *puVar5 = 1;
    puVar5[1] = puVar5[1] | 0x8000;
  }
  else {
    DAT_0804ded3 = '\x01';
  }
  return;
}




/* 0x0802f130 */
undefined4 firehose_dispatch()
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 auStack_218 [512];
  int local_18;
  
  iVar1 = DAT_0804cd58;
  local_18 = DAT_0804cd58;
  iVar2 = FUN_08038db4();
  FUN_08006d14(auStack_218,0x200);
  if (iVar2 == 0) {
LAB_0802f176:
    uVar3 = 1;
  }
  else {
    if (iVar2 == 4) {
      xml_get_tag_name(&DAT_08055ea0,auStack_218,0x200,0);
      iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f2e8);
      if (iVar2 != 0) goto LAB_0802f176;
    }
    else if (iVar2 == 1) {
      iVar2 = xml_tag_match(&DAT_08055ea0,"configure");
      if (iVar2 != 0) {
        uVar3 = handle_configure();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,"program");
      if (iVar2 != 0) {
        uVar3 = handle_program();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,"firmwarewrite");
      if (iVar2 != 0) {
        uVar3 = handle_firmwarewrite();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,"patch");
      if (iVar2 != 0) {
        uVar3 = handle_patch();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,"setbootablestoragedrive");
      if (iVar2 != 0) {
        uVar3 = handle_setbootable();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f334);
      if ((iVar2 != 0) || (iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f338), iVar2 != 0)) {
        uVar3 = handle_storagextras();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,"power");
      if (iVar2 != 0) {
        uVar3 = handle_power();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,"benchmark");
      if (iVar2 != 0) {
        uVar3 = handle_benchmark();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f354);
      if (iVar2 != 0) {
        uVar3 = handle_read();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,"getstorageinfo");
      if (iVar2 != 0) {
        uVar3 = handle_getstorageinfo();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,"getcrc16digest");
      if (iVar2 == 0) {
        iVar2 = xml_tag_match(&DAT_08055ea0,"getsha256digest");
        if (iVar2 == 0) {
          iVar2 = xml_tag_match(&DAT_08055ea0,"erase");
          if (iVar2 != 0) {
            uVar3 = handle_erase();
            goto LAB_0802f2a6;
          }
          iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f394);
          if (iVar2 != 0) {
            uVar3 = handle_peek();
            goto LAB_0802f2a6;
          }
          iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f39c);
          if (iVar2 != 0) {
            uVar3 = handle_poke();
            goto LAB_0802f2a6;
          }
          iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f3a4);
          if (iVar2 != 0) {
            uVar3 = handle_nop();
            goto LAB_0802f2a6;
          }
          iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f3a8);
          if (((iVar2 == 0) && (iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f2e8), iVar2 == 0)) &&
             (iVar2 = xml_tag_match(&DAT_08055ea0,"patches"), iVar2 == 0)) {
            iVar2 = xml_get_tag_name(&DAT_08055ea0,auStack_218,0x200,0);
            if (iVar2 == 0) {
              firehose_log("WARNING: Ignoring unrecognized tag too long to display. Continuing.");
            }
            else {
              firehose_log("WARNING: Ignoring unrecognized tag \'%s\'. Continuing.",auStack_218);
            }
            uVar3 = handle_response(1);
            goto LAB_0802f2a6;
          }
          goto LAB_0802f2a4;
        }
        uVar3 = 0;
      }
      else {
        uVar3 = 1;
      }
      uVar3 = FUN_080233ec(uVar3);
      goto LAB_0802f2a6;
    }
LAB_0802f2a4:
    uVar3 = 0;
  }
LAB_0802f2a6:
  if (local_18 != iVar1) {
    FUN_08010960();
  }
  return uVar3;
}




/* 0x0802f494 */
undefined4 FUN_0802f494()
{
  undefined4 uVar1;
  
  uVar1 = 0;
  FUN_08030ac4(0x12,0,DAT_0804d3a4);
  if ((DAT_0804d3a4 == '\0') || ((DAT_0804d3a4 != '\x01' && (DAT_0804d3a4 == '\x02')))) {
    DAT_0804d3a6 = 1;
    uVar1 = FUN_0802f694();
  }
  return uVar1;
}




/* 0x0802f4c4 */
void thunk_FUN_0802f4c4(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  
  DAT_0804d3b0 = 0;
  DAT_0804d3a7 = '\0';
  DAT_0804d3c0 = 0;
  DAT_0804d3c4 = 0;
  FUN_08030ac4(0x1b,0,param_2,param_4,param_4);
  FUN_08030944(param_1);
  thunk_FUN_0801ac9c(1);
  FUN_08030aa8(param_2);
  uVar2 = 0;
  DAT_0804d3b4 = FUN_08030704(0x802f6d1,&DAT_0804d3c8,&LAB_0802f96c,&LAB_0802fb48);
  if (param_1 == 0) {
    FUN_0802f84c(0xffffff);
    FUN_0802f8c0();
  }
  while (DAT_0804d3a7 == '\0') {
    iVar1 = FUN_0802f988();
    if ((iVar1 == 1) && (param_1 == 0)) {
      FUN_0802f87c();
      uVar2 = 0;
      DAT_0804d3b4 = FUN_08030704(0x802f6d1,&DAT_0804d3c8,&LAB_0802f96c,&LAB_0802fb48);
      FUN_0802f84c(0xffffff);
      FUN_0802f8c0();
    }
    FUN_0802f57c();
  }
  if (param_1 == 0) {
    FUN_0802f8e8();
  }
  thunk_FUN_0801ac9c(0);
  FUN_08030ac4(0x1c,0,param_2,uVar2);
  return;
}




/* 0x0802f4c4 */
void FUN_0802f4c4(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  
  DAT_0804d3b0 = 0;
  DAT_0804d3a7 = '\0';
  DAT_0804d3c0 = 0;
  DAT_0804d3c4 = 0;
  FUN_08030ac4(0x1b,0,param_2,param_4,param_4);
  FUN_08030944(param_1);
  thunk_FUN_0801ac9c(1);
  FUN_08030aa8(param_2);
  uVar2 = 0;
  DAT_0804d3b4 = FUN_08030704(0x802f6d1,&DAT_0804d3c8,&LAB_0802f96c,&LAB_0802fb48);
  if (param_1 == 0) {
    FUN_0802f84c(0xffffff);
    FUN_0802f8c0();
  }
  while (DAT_0804d3a7 == '\0') {
    iVar1 = FUN_0802f988();
    if ((iVar1 == 1) && (param_1 == 0)) {
      FUN_0802f87c();
      uVar2 = 0;
      DAT_0804d3b4 = FUN_08030704(0x802f6d1,&DAT_0804d3c8,&LAB_0802f96c,&LAB_0802fb48);
      FUN_0802f84c(0xffffff);
      FUN_0802f8c0();
    }
    FUN_0802f57c();
  }
  if (param_1 == 0) {
    FUN_0802f8e8();
  }
  thunk_FUN_0801ac9c(0);
  FUN_08030ac4(0x1c,0,param_2,uVar2);
  return;
}




/* 0x0802f57c */
void FUN_0802f57c()
{
  int iVar1;
  
  FUN_0802fc0c(DAT_0804d3b4);
  if ((DAT_0804d3a5 != '\0') && (iVar1 = FUN_0802f988(), iVar1 != 0)) {
    if (DAT_0804d3a4 == '\0') {
      DAT_0804d3a4 = 1;
      DAT_0804d3a5 = 0;
      DAT_0804d3a6 = 0;
      FUN_0802fde8(*(undefined4 *)(DAT_0804d3b4 + 0xc),1,0);
      return;
    }
    if ((DAT_0804d3a4 != '\x01') && (DAT_0804d3a4 == '\x02')) {
      FUN_08030ac4(0xf,0);
      FUN_08030af4();
      return;
    }
  }
  return;
}




/* 0x0802f5d4 */
undefined4 FUN_0802f5d4(param_1, param_2, param_3, param_4)
int param_1; uint param_2; code * param_3; int * param_4;
{
  uint uVar1;
  code *pcVar2;
  int iVar3;
  
  FUN_08030ac4(0x20,0,param_2);
  pcVar2 = DAT_0804d3b8;
  if ((param_4 != (int *)0x0) && (param_2 != 0)) {
    if (DAT_0804d3a6 != '\0') {
      DAT_0804d3a6 = '\0';
      if (param_2 < DAT_0804d3a8) {
        DAT_0804d3a8 = param_2;
      }
      FUN_08030ac4(0x17,0,DAT_0804d3a8);
      FUN_08027bf8(param_1,param_2,0x87c74000,DAT_0804d3a8);
      uVar1 = DAT_0804d3a8;
      if (DAT_0804d3a8 < 0x200) {
        if (param_3 != (code *)0x0) {
          FUN_08030ac4(0x16,0);
          (*param_3)(DAT_0804d3a8,0);
        }
        DAT_0804d3a8 = 0;
        DAT_0804d3b8 = (code *)0x0;
        return 0;
      }
      param_2 = param_2 - DAT_0804d3a8;
      DAT_0804d3a8 = 0;
      param_1 = param_1 + uVar1;
    }
    if (0x100000 < param_2) {
      param_2 = 0x100000;
    }
    FUN_08030ac4(0x20,0,param_2);
    iVar3 = FUN_080308f4(param_1,param_2);
    *param_4 = iVar3;
    pcVar2 = DAT_0804d3b8;
    if ((iVar3 == 0) && (pcVar2 = param_3, param_3 == (code *)0x0)) {
      DAT_0804d3c4 = '\x01';
      do {
        FUN_0802f57c();
      } while (DAT_0804d3c4 != '\0');
      return DAT_0804d3c0;
    }
  }
  DAT_0804d3b8 = pcVar2;
  return 0;
}




/* 0x0802f694 */
int FUN_0802f694()
{
  int iVar1;
  
  FUN_08030ac4(0x10,0);
  iVar1 = FUN_080308f4(0x87c74000,0x200);
  if ((iVar1 == 0) && (DAT_0804d3a4 == '\0')) {
    DAT_0804d3a5 = 1;
    FUN_0802f84c(50000);
    FUN_0802f8c0();
  }
  return iVar1;
}




/* 0x0802f6d0 */
void FUN_0802f6d0(param_1)
int param_1;
{
  bool bVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  bVar1 = false;
  FUN_08030ac4(0x13,0,0);
  if (*(int *)(param_1 + 4) == 2) {
    if (*(int *)(param_1 + 0x1c) == 0) {
      FUN_08030ac4(0x11,0);
      DAT_0804d3a6 = '\0';
      bVar1 = true;
      if (DAT_0804d3a5 != '\0') {
        DAT_0804d3a4 = '\x02';
        DAT_0804d3a5 = '\0';
      }
    }
    if (*(uint *)(param_1 + 0x1c) != (*(uint *)(param_1 + 0x1c) / 0x200) * 0x200) {
      bVar1 = true;
      FUN_08030ac4(0x24,0,DAT_0804d3bc);
    }
    DAT_0804d3bc = *(int *)(param_1 + 0x1c) + DAT_0804d3bc;
    FUN_08030ac4(4,0);
  }
  else if ((*(int *)(param_1 + 4) == 3) && (FUN_08030ac4(10,0), DAT_0804d3a5 != '\0')) {
    bVar1 = true;
    DAT_0804d3a5 = '\0';
  }
  iVar4 = DAT_0804d3bc;
  uVar2 = *(uint *)(param_1 + 0x18);
  uVar6 = *(uint *)(param_1 + 0x1c);
  if ((uVar2 == uVar6) || (bVar1)) {
    if ((DAT_0804d3a6 != '\0') && (uVar6 != 0)) {
      FUN_08030ac4(0x25,0);
      ((code*)DAT_0804d3b8)(DAT_0804d3bc - *(int *)(param_1 + 0x1c),0);
      DAT_0804d3a8 = *(undefined4 *)(param_1 + 0x1c);
      DAT_0804d3ac = DAT_0804d3ac + 1;
      DAT_0804d3b8 = (code *)0x0;
      DAT_0804d3bc = *(undefined4 *)(param_1 + 0x1c);
      return;
    }
    if ((uVar2 == uVar6) && (uVar2 == (uVar2 / 0x200) * 0x200)) {
      if (DAT_0804d3a4 != '\x01') {
        iVar4 = FUN_0802f494();
        if (iVar4 == 0) {
          return;
        }
        if (DAT_0804d3b8 == (code *)0x0) {
          DAT_0804d3c4 = 0;
          DAT_0804d3c0 = DAT_0804d3bc;
          DAT_0804d3bc = 0;
          return;
        }
        uVar3 = 9;
        goto LAB_0802f822;
      }
      if (DAT_0804d3b8 == (code *)0x0) {
        DAT_0804d3bc = 0;
        DAT_0804d3c0 = iVar4;
        DAT_0804d3c4 = 0;
        return;
      }
      uVar3 = 0x14;
    }
    else {
      if (DAT_0804d3b8 == (code *)0x0) {
        DAT_0804d3bc = 0;
        DAT_0804d3c0 = iVar4;
        DAT_0804d3c4 = 0;
        return;
      }
      uVar3 = 0x15;
    }
    FUN_08030ac4(uVar3,0,DAT_0804d3bc);
    uVar3 = 0;
  }
  else {
    if (uVar2 < uVar6) {
      FUN_08030ac4(10,0,DAT_0804d3bc);
      FUN_08030af4();
      return;
    }
    uVar2 = uVar2 - uVar6;
    iVar4 = *(int *)(param_1 + 0x14);
    FUN_08030ac4(0x18,0,uVar2);
    if (0x100000 < uVar2) {
      uVar2 = 0x100000;
    }
    iVar5 = FUN_080308f4(*(int *)(param_1 + 0x1c) + iVar4,uVar2);
    iVar4 = DAT_0804d3bc;
    if (iVar5 == 0) {
      return;
    }
    if (DAT_0804d3b8 == (code *)0x0) {
      DAT_0804d3bc = 0;
      DAT_0804d3c0 = iVar4;
      DAT_0804d3c4 = 0;
      return;
    }
    uVar3 = 0;
  }
LAB_0802f822:
  ((code*)DAT_0804d3b8)(DAT_0804d3bc,uVar3);
  DAT_0804d3b8 = (code *)0x0;
  DAT_0804d3bc = 0;
  return;
}




/* 0x0802f838 */
void FUN_0802f838(param_1)
int param_1;
{
  if (param_1 == 0) {
    DAT_0804d3a4 = 1;
  }
  else {
    DAT_0804d3a4 = 2;
  }
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0802f84c */
void FUN_0802f84c(param_1)
int param_1;
{
  _DAT_078d9148 = _DAT_078d9148 | 0x1000000;
  FUN_08030ac4(0xb,0,param_1);
  if (param_1 == 0) {
    param_1 = 1;
  }
  _DAT_078d9080 = param_1 - 1U & 0xffffff;
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0802f87c */
void thunk_FUN_0802f87c()
{
  FUN_08030ac4(0x1f,0);
  if (*(int *)(DAT_0804d3b4 + 0xc) == 0) {
    FUN_0803056c(0,4,8,0x18);
    _DAT_078d9140 = _DAT_078d9140 & 0xfffffffe;
    FUN_080300bc(10);
  }
  FUN_08030ac4(0x4a,0);
  FUN_0802fdac(&DAT_0804dde4);
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0802f87c */
void FUN_0802f87c()
{
  FUN_08030ac4(0x1f,0);
  if (*(int *)(DAT_0804d3b4 + 0xc) == 0) {
    FUN_0803056c(0,4,8,0x18);
    _DAT_078d9140 = _DAT_078d9140 & 0xfffffffe;
    FUN_080300bc(10);
  }
  FUN_08030ac4(0x4a,0);
  FUN_0802fdac(&DAT_0804dde4);
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0802f8c0 */
void FUN_0802f8c0()
{
  _DAT_078d9144 = 0x1000000;
  FUN_08030ac4(0xc,0);
  _DAT_078d9084 = 0xc0000000;
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0802f8e8 */
void FUN_0802f8e8()
{
  FUN_08030ac4(0xd,0);
  _DAT_078d9084 = 0;
  return;
}




/* 0x0802f900 */
undefined4 FUN_0802f900(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; code * param_3; undefined4 * param_4;
{
  undefined4 uVar1;
  
  *param_4 = 0;
  FUN_08030ac4(0x21,0,0);
  FUN_08030ac4(3,0,param_2);
  FUN_0803098c(param_1,param_2);
  while (DAT_0804d3b0 == 0) {
    FUN_0802f57c();
  }
  uVar1 = *(undefined4 *)(DAT_0804d3b0 + 0x1c);
  if (*(int *)(DAT_0804d3b0 + 4) == 2) {
    DAT_0804d3b0 = 0;
  }
  else {
    FUN_08030ac4(0x26,0);
    DAT_0804d3b0 = 0;
    *param_4 = 10;
  }
  if (param_3 != (code *)0x0) {
    (*param_3)(uVar1,*param_4);
  }
  return uVar1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0802f988 */
undefined4 FUN_0802f988()
{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((_DAT_078d9144 << 7 < 0) || (_DAT_078d9084 == -0x80000000)) {
    _DAT_078d9144 = 0x1000000;
    FUN_0802f8e8();
    uVar1 = 1;
    FUN_08030ac4(0xf,0,1);
  }
  return uVar1;
}




/* 0x0802f9c0 */
void FUN_0802f9c0()
{
  FUN_08030ac4(0xb0,0);
  FUN_0802fdac(&DAT_0805104c);
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0802f9d4 */
void FUN_0802f9d4()
{
  FUN_08030ac4(0xb1,0);
  DAT_0804def8 = 0;
  _DAT_078d9140 = _DAT_078d9140 & 0xfffffffe;
  return;
}




/* 0x0802f9ea */
undefined4 FUN_0802f9ea()
{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar4 = 0;
  bVar1 = false;
  FUN_08030ac4(0x9b,0,0);
  do {
    iVar2 = FUN_0802facc();
    uVar4 = uVar4 + 1;
    if (iVar2 == 5) break;
    iVar2 = FUN_0802fab0();
    if (iVar2 == 0) {
      bVar1 = true;
      break;
    }
    FUN_080300bc(3);
  } while (uVar4 < 10000);
  uVar5 = 0;
  do {
    if (bVar1) break;
    iVar2 = FUN_0802fab0();
    if (iVar2 == 0) {
      bVar1 = true;
      break;
    }
    FUN_0802facc();
    uVar5 = uVar5 + 1;
    FUN_080300bc(3);
  } while (uVar5 < 1000);
  if ((uVar4 < 10000) || (bVar1)) {
    if (bVar1) {
      uVar3 = 2;
    }
    else {
      FUN_08030ac4(0x9c,0);
      uVar3 = 0;
    }
  }
  else {
    FUN_08030ac4(0x9d,0);
    uVar3 = 1;
  }
  return uVar3;
}




/* 0x0802fa6e */
undefined4 FUN_0802fa6e()
{
  undefined4 uVar1;
  
  uVar1 = FUN_08030688();
  FUN_08030ac4(uVar1,0xa9,0);
  return uVar1;
}




/* 0x0802fa84 */
undefined4 FUN_0802fa84()
{
  DAT_0805090c = FUN_080306a4();
  if (DAT_0805090c != 0) {
    FUN_08030ac4(0xaf,0,1);
    return 1;
  }
  FUN_08030ac4(0xaf,0);
  return 0;
}




/* 0x0802fab0 */
bool FUN_0802fab0()
{
  uint in_r3 = 0;
  uint local_8;
  
  local_8 = in_r3 & 0xffffff00;
  FUN_0802a960(&local_8);
  return (local_8 & 0xff) == 1;
}




/* 0x0802facc */
int FUN_0802facc()
{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  FUN_0802fc0c(DAT_0805090c);
  iVar1 = *(int *)(DAT_0805090c + 0x18);
  uVar2 = (uint)(*(char *)(DAT_0805090c + 0x29) != '\0');
  iVar3 = *(int *)(DAT_0805090c + 0x24);
  if ((iVar1 != DAT_08050910 || DAT_08050914 != uVar2) || DAT_08050918 != iVar3) {
    if (iVar1 == 0) {
      iVar4 = 2;
    }
    else if (iVar3 == 0) {
      if (uVar2 == 0) {
        if (DAT_08050910 == 0) {
          iVar4 = 1;
        }
        else {
          iVar4 = 4;
        }
      }
      else if (*(int *)(DAT_0805090c + 0x20) < 500) {
        iVar4 = 7;
      }
      else {
        iVar4 = 5;
      }
    }
    else {
      iVar4 = 6;
    }
    DAT_08050910 = iVar1;
    DAT_08050914 = uVar2;
    DAT_08050918 = iVar3;
    if (iVar4 != 0) {
      FUN_08030ac4(iVar4,0x9e,0);
    }
  }
  return iVar4;
}




/* 0x0802fb44 */
undefined4 FUN_0802fb44()
{
  return 1;
}




/* 0x0802fb64 */
undefined4 FUN_0802fb64(param_1)
int param_1;
{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    if (*(int *)(param_1 + 0x88) != 0x61945374) {
      return 0;
    }
    uVar1 = 1;
  }
  return uVar1;
}




/* 0x0802fbac */
undefined4 FUN_0802fbac(param_1)
int param_1;
{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined1 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined1 *)(param_1 + 0x29) = 0;
  FUN_0801a6fa(param_1,0);
  *(int *)(param_1 + 0x3c) = param_1;
  *(undefined1 *)(param_1 + 0x44) = 0x80;
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(int *)(param_1 + 0x74) = param_1;
  *(undefined4 *)(param_1 + 0x38) = 3;
  *(undefined1 *)(param_1 + 0x7c) = 0;
  *(undefined4 *)(param_1 + 0x90) = 0;
  *(undefined4 *)(param_1 + 0x70) = 3;
  *(undefined4 *)(param_1 + 0x30) = 0x87c74734;
  *(undefined1 *)(param_1 + 0xa4) = 0;
  *(undefined4 *)(param_1 + 0xa8) = 0;
  FUN_0803016c(*(undefined4 *)(param_1 + 0xc),param_1,&PTR_FUN_0801a5f0_1_0804dec4);
  if ((true) && (*(int *)(param_1 + 0xc) == 0)) {
    if (DAT_0804ded4 != '\0') {
      return 6;
    }
    uVar2 = 0xc0000000;
    if (true) {
      uVar2 = 0xc1000000;
    }
    if (true) {
      puVar1 = (undefined4 *)&DAT_078d9080;
    }
    else {
      puVar1 = (undefined4 *)&DAT_078d9088;
    }
    *puVar1 = 0xffffff;
    puVar1[1] = uVar2;
    DAT_0804ded4 = 1;
    return 0;
  }
  return 3;
}




/* 0x0802fc0c */
void FUN_0802fc0c(param_1)
int param_1;
{
  if (param_1 != 0) {
    FUN_08030254(*(undefined4 *)(param_1 + 0xc));
    return;
  }
  return;
}




/* 0x0802fc18 */
void FUN_0802fc18(param_1)
int param_1;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_08030220(*(undefined4 *)(param_1 + 0xc));
  if (*(int *)(param_1 + 0x18) == iVar1) goto LAB_0802fc66;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  if (iVar1 == 0) {
    uVar3 = 0;
LAB_0802fc46:
    FUN_0801a6fa(param_1,uVar3);
  }
  else {
    *(undefined4 *)(param_1 + 0x24) = 0;
    FUN_0801a6fa(param_1,100);
    iVar2 = FUN_08030250(*(undefined4 *)(param_1 + 0xc));
    if (iVar2 != 0) {
      uVar3 = 0x5dc;
      goto LAB_0802fc46;
    }
    FUN_0801a6fa(param_1,0);
    FUN_0803009c(*(undefined4 *)(param_1 + 0xc));
  }
  *(int *)(param_1 + 0x18) = iVar1;
  FUN_0801a69e(param_1,0);
LAB_0802fc66:
  iVar1 = FUN_0803015c(*(undefined4 *)(param_1 + 0xc));
  if (iVar1 == 0) {
    iVar2 = 0xc;
  }
  else {
    iVar2 = 1;
    if (iVar1 != 1) {
      if (iVar1 == 2) {
        iVar2 = 0x1e0;
      }
      else {
        iVar2 = 0;
      }
    }
  }
  if (*(int *)(param_1 + 0x1c) != iVar2) {
    *(undefined4 *)(param_1 + 0x24) = 0;
    *(int *)(param_1 + 0x1c) = iVar2;
    FUN_0801a69e(param_1,1);
  }
  iVar1 = FUN_0803023c(*(undefined4 *)(param_1 + 0xc));
  if (*(int *)(param_1 + 0x24) != iVar1) {
    if ((iVar1 == 0) && (*(int *)(param_1 + 0x2c) != 0)) {
      iVar2 = (uint)*(byte *)(*(int *)(*(int *)(param_1 + 0x2c) + 4) + 8) << 1;
    }
    else {
      iVar2 = 0;
    }
    FUN_0801a6fa(param_1,iVar2);
    *(int *)(param_1 + 0x24) = iVar1;
    FUN_0801a69e(param_1,5);
    return;
  }
  return;
}




/* 0x0802fcd0 */
undefined4 FUN_0802fcd0(param_1, param_2)
int param_1; uint param_2;
{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  byte bVar4;
  undefined4 *puVar5;
  
  uVar1 = (uint)*(byte *)(param_1 + 0x29);
  uVar3 = 0;
  if (((uVar1 == 0) || (param_2 == 0)) || (uVar1 == param_2)) {
    if (uVar1 != param_2) {
      if (param_2 == 0) {
        *(undefined1 *)(param_1 + 0x29) = 0;
        *(undefined4 *)(param_1 + 0x2c) = 0;
        FUN_0801a6fa(param_1,0);
        bVar4 = 1;
        do {
          FUN_0802fde8(*(undefined4 *)(param_1 + 0xc),bVar4,0);
          FUN_080305c8(*(undefined4 *)(param_1 + 0xc),bVar4,0);
          FUN_0802fde8(*(undefined4 *)(param_1 + 0xc),bVar4,1);
          FUN_080305c8(*(undefined4 *)(param_1 + 0xc),bVar4,1);
          bVar4 = bVar4 + 1;
        } while (bVar4 < 2);
      }
      else {
        puVar5 = *(undefined4 **)(param_1 + 4);
        while ((puVar5 != (undefined4 *)0x0 && (*(byte *)(puVar5[1] + 5) != param_2))) {
          puVar5 = (undefined4 *)*puVar5;
        }
        if ((puVar5 == (undefined4 *)0x0) ||
           (iVar2 = FUN_0801a6a8(puVar5,*(undefined1 *)(*(int *)(puVar5[3] + 4) + 2),0), iVar2 < 0))
        goto LAB_0802fd20;
        *(char *)(param_1 + 0x29) = (char)param_2;
        *(undefined4 *)(param_1 + 0x24) = 0;
        *(undefined4 **)(param_1 + 0x2c) = puVar5;
        FUN_0801a6fa(param_1,(uint)*(byte *)(puVar5[1] + 8) << 1);
      }
      FUN_0801a69e(param_1,3);
    }
    iVar2 = FUN_0803015c(*(undefined4 *)(param_1 + 0xc));
    if (iVar2 == 0) {
      uVar3 = 0x40;
    }
    else if (iVar2 == 1) {
      uVar3 = 8;
    }
    else if (iVar2 == 2) {
      uVar3 = 0x200;
    }
    FUN_08030348(uVar3);
    uVar3 = 0;
  }
  else {
LAB_0802fd20:
    uVar3 = 0xffffffff;
  }
  return uVar3;
}




/* 0x0802fdac */
void FUN_0802fdac(param_1)
int param_1;
{
  uint uVar1;
  
  for (uVar1 = 0; (*(int *)(param_1 + 0x38) == 1 && (uVar1 < DAT_0804dec0)); uVar1 = uVar1 + 1) {
    FUN_0802fc0c(param_1);
  }
  FUN_0802fcd0(param_1,0);
  FUN_08030364(*(undefined4 *)(param_1 + 0xc));
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined1 *)(param_1 + 0x28) = 0;
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0802fde8 */
undefined4 FUN_0802fde8(param_1, param_2, param_3)
int param_1; uint param_2; uint param_3;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  if (param_1 != 0) {
    FUN_08030ac4(0xb7,0,0x657);
    do {
    } while (DAT_0804deec != 0);
  }
  if ((param_2 < 2) && (param_3 < 2)) {
    uVar1 = 1 << (param_2 + param_3 * 0x10 & 0xff);
    uVar3 = _DAT_078d91b8 & uVar1;
    if (uVar3 != 0) {
      thunk_FUN_080300ba(&DAT_87c74800 + param_3 * 0x40 + param_2 * 0x80,0x40);
      uVar2 = 0;
      iVar4 = param_2 * 0x1040 + -0x7838b700 + param_3 * 0x820;
      do {
        thunk_FUN_080300ba(iVar4 + uVar2 * 0x20,0x20);
        uVar2 = uVar2 + 1;
      } while (uVar2 < 0x41);
      iVar4 = *(int *)(iVar4 + 0x1c);
      while (uVar3 != 0) {
        do {
        } while (uVar1 != 0);
        _DAT_078d91b4 = 0;
        uVar3 = 0;
      }
      if (iVar4 != 0) {
        *(undefined4 *)(iVar4 + 4) = 3;
        if (*(code **)(iVar4 + 0x24) != (code *)0x0) {
          (**(code **)(iVar4 + 0x24))();
        }
      }
    }
  }
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0802fe98 */
undefined4 FUN_0802fe98(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  uint uVar1;
  
  if (param_1 != 0) {
    FUN_08030ac4(0xb7,0,0x695);
    do {
    } while (DAT_0804deec != 0);
  }
  uVar1 = 1 << (param_2 + param_3 * 0x10 & 0xffU);
  while ((_DAT_078d91b8 & uVar1) != 0) {
    do {
      _DAT_078d91b4 = uVar1;
    } while (uVar1 != 0);
  }
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0802fee8 */
undefined4 thunk_FUN_0802fee8(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uStack_18;
  
  iVar3 = 0;
  uStack_18 = param_4;
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
  thunk_FUN_080199b4(10);
  uVar4 = -((int)(_DAT_0006c05c << 0x18) >> 0x1f);
  if (uVar4 == (_DAT_0006c05c & 1)) {
    FUN_08030ac4(0xb8,0,uVar4);
  }
  if (uVar4 == 0) {
    uStack_18 = CONCAT31(_GHIDRA_FIELD(uStack_18, 1, uint24_t),1);
    FUN_0802a960(&uStack_18);
    if ((char)uStack_18 == '\0') {
      iVar2 = 0;
      uVar1 = 0xb5;
    }
    else {
      FUN_0801a948(param_1);
      FUN_0803056c(param_1,10,0,2);
      FUN_0803056c(param_1,4,0x45,0xff);
      do {
        thunk_FUN_080199b4(5);
        iVar2 = FUN_08030528(param_1,0x15);
        if (iVar2 != 0) break;
        iVar3 = iVar3 + 1;
      } while (iVar3 < 0x19);
      FUN_0803056c(param_1,4,0x41,0xff);
      FUN_0803056c(param_1,10,7,0xff);
      if (iVar2 == 0) {
        FUN_08030ac4(0xb3,0,0);
        return 1;
      }
      uVar1 = 0xb2;
    }
  }
  else {
    iVar2 = 0;
    uVar1 = 0xb4;
  }
  FUN_08030ac4(uVar1,0,iVar2);
  return 0;
}




/* 0x0802fee8 */
undefined4 FUN_0802fee8(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 local_18;
  
  iVar3 = 0;
  local_18 = param_4;
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
  thunk_FUN_080199b4(10);
  uVar4 = -((int)(_DAT_0006c05c << 0x18) >> 0x1f);
  if (uVar4 == (_DAT_0006c05c & 1)) {
    FUN_08030ac4(0xb8,0,uVar4);
  }
  if (uVar4 == 0) {
    local_18 = CONCAT31(_GHIDRA_FIELD(local_18, 1, uint24_t),1);
    FUN_0802a960(&local_18);
    if ((char)local_18 == '\0') {
      iVar2 = 0;
      uVar1 = 0xb5;
    }
    else {
      FUN_0801a948(param_1);
      FUN_0803056c(param_1,10,0,2);
      FUN_0803056c(param_1,4,0x45,0xff);
      do {
        thunk_FUN_080199b4(5);
        iVar2 = FUN_08030528(param_1,0x15);
        if (iVar2 != 0) break;
        iVar3 = iVar3 + 1;
      } while (iVar3 < 0x19);
      FUN_0803056c(param_1,4,0x41,0xff);
      FUN_0803056c(param_1,10,7,0xff);
      if (iVar2 == 0) {
        FUN_08030ac4(0xb3,0,0);
        return 1;
      }
      uVar1 = 0xb2;
    }
  }
  else {
    iVar2 = 0;
    uVar1 = 0xb4;
  }
  FUN_08030ac4(uVar1,0,iVar2);
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0802ffec */
undefined4 FUN_0802ffec()
{
  FUN_0800abf4();
  return 1;
}




/* 0x0802fff8 */
undefined4 FUN_0802fff8(param_1, param_2, param_3, param_4, param_5, param_6)
int param_1; uint param_2; uint param_3; int param_4; int param_5; int param_6;
{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  
  uVar6 = 0;
  if (param_2 == 0) {
    uVar6 = 0;
  }
  else if (((param_2 < 2) && (param_3 < 2)) && (param_1 == 0)) {
    if (param_3 == 1) {
      iVar1 = FUN_0801acc0();
      if (iVar1 == 0) {
        iVar1 = 0x400000;
      }
      else {
        iVar1 = 0;
      }
      uVar3 = 0xffff0000;
      uVar4 = iVar1 + param_4 * 0x40000 + 0x800000;
    }
    else {
      iVar1 = FUN_0801acc0();
      if (iVar1 == 0) {
        iVar1 = 0x40;
      }
      else {
        iVar1 = 0;
      }
      uVar3 = 0xffff;
      uVar4 = iVar1 + param_4 * 4 + 0x80;
    }
    puVar2 = (uint *)(&DAT_87c74800 + param_3 * 0x40 + param_2 * 0x80);
    *puVar2 = param_5 << 0x10;
    if (param_6 == 1) {
      uVar5 = *puVar2 & 0xdfffffff;
    }
    else {
      uVar5 = *puVar2 | 0x20000000;
    }
    *puVar2 = uVar5;
    *(uint *)(param_2 * 4 + 0x78d91c0) = *(uint *)(param_2 * 4 + 0x78d91c0) & ~uVar3 | uVar4 & uVar3
    ;
  }
  else {
    uVar6 = 3;
  }
  return uVar6;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0803009c */
void FUN_0803009c()
{
  DAT_0804def8 = 1;
  _DAT_078d9140 = _DAT_078d9140 | 1;
  return;
}




/* 0x080300b8 */
void thunk_FUN_080300b8()
{
  return;
}




/* 0x080300b8 */
void FUN_080300b8()
{
  return;
}




/* 0x080300ba */
void thunk_FUN_080300ba()
{
  return;
}




/* 0x080300ba */
void FUN_080300ba()
{
  return;
}




/* 0x080300bc */
void FUN_080300bc(param_1)
uint param_1;
{
  uint uVar1;
  
  for (uVar1 = 0; uVar1 < param_1; uVar1 = uVar1 + 1) {
    FUN_080199b4(1000);
  }
  return;
}




/* 0x080300da */
undefined1 FUN_080300da()
{
  undefined1 uVar1;
  
  uVar1 = FUN_0801a754();
  return uVar1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08030100 */
void FUN_08030100(param_1)
int param_1;
{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + 0xa8);
  switch(uVar1) {
  case 0:
    _DAT_078d9184 = _DAT_078d9184 & 0xfff0ffff | (uVar1 & 0xf) << 0x10;
    *(undefined1 *)(param_1 + 0xa4) = 0;
    break;
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
    _DAT_078d9184 = _DAT_078d9184 & 0xfff0ffff | (uVar1 & 0xf) << 0x10;
    break;
  default:
    FUN_08030ac4(0x82,0);
    return;
  }
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0803014c */
uint FUN_0803014c()
{
  return (uint)(_DAT_078d9184 << 0x14) >> 0x1e;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0803015c */
uint FUN_0803015c()
{
  return (uint)(_DAT_078d9184 << 4) >> 0x1e;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0803016c */
undefined4 FUN_0803016c(param_1, param_2, param_3)
int param_1; undefined4 param_2; undefined4 param_3;
{
  int iVar1;
  
  if (param_1 != 0) {
    FUN_08030ac4(0xb7,0,0xf3);
    do {
    } while (DAT_0804deec != 0);
  }
  DAT_0804ded8 = param_3;
  *(undefined4 *)(param_1 * 0xc + -0x78389678) = param_2;
  iVar1 = FUN_0802ffec();
  if ((iVar1 == 0) || (iVar1 = FUN_0801acc0(param_1), iVar1 == 0)) {
    FUN_0801aba0(param_1);
  }
  _DAT_078d91a8 = (_DAT_078d91a8 & 0xfffffffc) + 2;
  FUN_0801ab18(param_1);
  _DAT_078d9158 = &DAT_87c74800;
  _DAT_078d9148 = 0;
  iVar1 = FUN_0801ac40();
  if (iVar1 != 0) {
    _DAT_078d91a8 = _DAT_078d91a8 | 0x10;
  }
  _DAT_078d91a8 = _DAT_078d91a8 | 8;
  _DAT_078d91ac = 0;
  _DAT_078d9098 = 8;
  if (DAT_0804ded2 == '\x01') {
    _DAT_078d9140 = _DAT_078d9140 | 1;
  }
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08030220 */
undefined4 FUN_08030220()
{
  DAT_0804def9 = (undefined1)(_DAT_078d9184 & 1);
  if ((_DAT_078d9184 & 1) != 0) {
    DAT_0804def9 = 1;
  }
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0803023c */
bool FUN_0803023c()
{
  return (_DAT_078d9184 & 0x80) != 0;
}




/* 0x08030250 */
undefined4 FUN_08030250()
{
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08030254 */
void FUN_08030254(param_1)
int param_1;
{
  uint uVar1;
  uint uVar2;
  undefined4 unaff_r4 = 0;
  undefined4 unaff_r5 = 0;
  undefined4 unaff_r6 = 0;
  undefined4 uVar3;
  undefined4 unaff_lr = 0;
  
  uVar2 = _DAT_078d91ac;
  uVar1 = _DAT_078d9144;
  if ((int)(_DAT_078d9144 << 0x19) < 0) {
    FUN_08030ac4(0x94,0);
    uVar3 = *(undefined4 *)(param_1 * 0xc + -0x78389678);
    FUN_08030ac4(0x7e,0);
    ((code *)*(uint*)DAT_0804ded8)(uVar3);
  }
  if ((int)(uVar1 << 0x17) < 0) {
    FUN_08030ac4(0x95,0);
    FUN_0801a9a0(param_1);
  }
  if ((int)(uVar1 << 0x1d) < 0) {
    FUN_08030ac4(0x96,0);
    FUN_0801a9a0(param_1);
  }
  if ((int)(uVar1 << 0x1b) < 0) {
    FUN_08030ac4(0x97,0);
    do {
    } while (DAT_0804deec != 0);
  }
  if ((int)(uVar1 << 0x1e) < 0) {
    FUN_08030ac4(0x98,0);
    do {
    } while (DAT_0804deec != 0);
  }
  if ((uVar1 & 1) != 0) {
    FUN_0801aa38(param_1);
  }
  if ((uVar2 & 1) == 0) {
    return;
  }
  _DAT_078d91ac = 1;
  do {
  } while (true);
  do {
    _DAT_078d9140 = _DAT_078d9140 | 0x2000;
    thunk_FUN_080300ba(0x87c74828,8);
    FUN_08027bf8(0x804def0,8,0x87c74828,8,unaff_r4,unaff_r5,unaff_r6,unaff_lr);
  } while ((_DAT_078d9140 & 0x2000) == 0);
  _DAT_078d9140 = _DAT_078d9140 & 0xffffdfff;
                    /* WARNING: Could not recover jumptable at 0x0801aa24. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code *)((uint*)&DAT_0804ded8)[1])(*(undefined4 *)(param_1 * 0xc + -0x78389678),0x804def0);
  return;
}




/* 0x0803030c */
void FUN_0803030c(param_1, param_2, param_3)
undefined4 param_1; int param_2; undefined4 * param_3;
{
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = *(undefined4 *)(param_2 * 4 + 0x78d9040);
  }
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08030320 */
void FUN_08030320(param_1, param_2)
undefined4 param_1; int param_2;
{
  _DAT_078d9154 = param_2 << 0x19 | 0x1000000;
  DAT_0804ded1 = (char)param_2;
  return;
}




/* 0x0803033c */
void FUN_0803033c(param_1)
undefined1 param_1;
{
  DAT_0804ded2 = param_1;
  return;
}




/* 0x08030348 */
void FUN_08030348(param_1)
undefined4 param_1;
{
  DAT_0804dedc = param_1;
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08030354 */
void FUN_08030354()
{
  _DAT_078d9140 = _DAT_078d9140 | 1;
  return;
}




/* 0x08030364 */
undefined4 FUN_08030364(param_1)
int param_1;
{
  byte bVar1;
  byte bVar2;
  
  if (param_1 != 0) {
    FUN_08030ac4(0xb7,0,0x6cf);
    do {
    } while (DAT_0804deec != 0);
  }
  bVar2 = 0;
  do {
    bVar1 = 0;
    do {
      FUN_0802fde8(param_1,bVar2,bVar1);
      bVar1 = bVar1 + 1;
    } while (bVar1 < 2);
    bVar2 = bVar2 + 1;
  } while (bVar2 < 2);
  bVar2 = 0;
  do {
    bVar1 = 0;
    do {
      FUN_080305c8(param_1,bVar2,bVar1);
      bVar1 = bVar1 + 1;
    } while (bVar1 < 2);
    bVar2 = bVar2 + 1;
  } while (bVar2 < 2);
  return 0;
}




/* 0x080303c4 */
undefined4 FUN_080303c4(param_1, param_2, param_3)
int param_1; uint param_2; uint param_3;
{
  uint uVar1;
  
  if (param_1 != 0) {
    FUN_08030ac4(0xb7,0,0x3a9);
    do {
    } while (DAT_0804deec != 0);
  }
  if ((param_2 < 2) && (param_3 < 2)) {
    if (param_2 == 0) {
      uVar1 = 0x10001;
    }
    else if (param_3 == 0) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0x10000;
    }
    *(uint *)(param_2 * 4 + 0x78d91c0) = *(uint *)(param_2 * 4 + 0x78d91c0) & ~uVar1 | uVar1;
  }
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08030528 */
uint FUN_08030528(param_1, param_2)
undefined4 param_1; int param_2;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  _DAT_078d9170 = param_2 * 0x10000 + 0x40000000;
  uVar2 = 0;
  uVar3 = 0;
  do {
    uVar1 = _DAT_078d9170;
    if (499 < uVar2) break;
    uVar4 = _DAT_078d9170 & 0x40000000;
    FUN_080300bc(1);
    uVar2 = uVar2 + 1;
    uVar3 = uVar1;
  } while (uVar4 == 0x40000000);
  return (uVar3 << 0x10) >> 0x18;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0803056c */
void FUN_0803056c(param_1, param_2, param_3, param_4)
undefined4 param_1; int param_2; uint param_3; uint param_4;
{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  
  if (param_4 != 0xff) {
    bVar1 = FUN_08030528();
    param_3 = param_4 & param_3 | (uint)bVar1 & ~param_4;
  }
  _DAT_078d9170 = param_3 + param_2 * 0x10000 + 0x60000000;
  uVar2 = 0;
  do {
    if (499 < uVar2) {
      return;
    }
    uVar3 = _DAT_078d9170 & 0x40000000;
    FUN_080300bc(1);
    uVar2 = uVar2 + 1;
  } while (uVar3 == 0x40000000);
  return;
}




/* 0x080305c8 */
undefined4 FUN_080305c8(param_1, param_2, param_3)
int param_1; uint param_2; uint param_3;
{
  undefined4 uVar1;
  uint uVar2;
  
  uVar1 = 0;
  if (((param_2 < 2) && (param_3 < 2)) && (param_1 == 0)) {
    *(undefined4 *)(&DAT_87c74800 + param_3 * 0x40 + param_2 * 0x80) = 0;
    if (param_2 != 0) {
      if (param_3 == 1) {
        uVar2 = 0x800000;
      }
      else {
        uVar2 = 0x80;
      }
      *(uint *)(param_2 * 4 + 0x78d91c0) = *(uint *)(param_2 * 4 + 0x78d91c0) & ~uVar2;
      return 0;
    }
  }
  else {
    uVar1 = 3;
  }
  return uVar1;
}




/* 0x08030614 */
undefined4 FUN_08030614(param_1, param_2, param_3)
int param_1; uint param_2; uint param_3;
{
  uint uVar1;
  uint uVar2;
  
  if (param_1 != 0) {
    FUN_08030ac4(0xb7,0,0x3f7);
    do {
    } while (DAT_0804deec != 0);
  }
  if ((param_2 < 2) && (param_3 < 2)) {
    if (param_2 == 0) {
      uVar2 = 0;
      uVar1 = 0x10001;
    }
    else if (param_3 == 0) {
      uVar1 = 0x41;
      uVar2 = 0x40;
    }
    else {
      uVar1 = 0x410000;
      uVar2 = 0x400000;
    }
    *(uint *)(param_2 * 4 + 0x78d91c0) = *(uint *)(param_2 * 4 + 0x78d91c0) & ~uVar1 | uVar2 & uVar1
    ;
  }
  return 0;
}




/* 0x08030678 */
void FUN_08030678(param_1, param_2, param_3)
undefined4 param_1; int param_2; undefined4 param_3;
{
  *(undefined4 *)(param_2 * 4 + 0x78d9040) = param_3;
  return;
}




/* 0x08030688 */
undefined4 FUN_08030688()
{
  FUN_08030ac4(0x40,0);
  FUN_080300da(DAT_08051058);
  return 0;
}




/* 0x080306a4 */
undefined * FUN_080306a4()
{
  int iVar1;
  
  FUN_08030ac4(0x3e,0);
  thunk_FUN_0800abf4();
  iVar1 = FUN_0801acc0(DAT_08051058);
  FUN_0803033c(0);
  FUN_0802fbac(&DAT_0805104c);
  if (iVar1 != 0) {
    FUN_08030ac4(0x43,0);
    FUN_0802fc18(&DAT_0805104c);
    DAT_08051074 = 1;
    FUN_0802fcd0(&DAT_0805104c,1);
  }
  return &DAT_0805104c;
}




/* 0x08030704 */
undefined4 * FUN_08030704(param_1, param_2, param_3, param_4, param_5)
int param_1; int param_2; int param_3; int param_4; int param_5;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  DAT_0804dc34 = (undefined1)param_5;
  FUN_08030ac4(0x49,0);
  FUN_08030a40();
  if (param_2 != 0) {
    *(int *)(DAT_0804ddec + 0x1c) = param_2;
  }
  if (DAT_0804dc35 == '\0') {
    DAT_0804dd98 = &DAT_0804dc68;
    DAT_0804ddac = &DAT_0804dc6f;
    DAT_0804ddc0 = &DAT_0804dc5f;
    DAT_0804ddd8 = &DAT_0804dc56;
  }
  else if ((DAT_0804dc35 == '\x01') || (DAT_0804dc35 == '\x02')) {
    DAT_0804ddbc = 0;
    DAT_0804ddac = &DAT_0804dc8f;
    DAT_0804dd98 = &DAT_0804dc88;
    DAT_0804ddc0 = &DAT_0804dc7f;
    DAT_0804ddd8 = &DAT_0804dc76;
    if (DAT_0804dc4e == -0x6ffa) {
      DAT_0804dc4e = -0x6ff2;
      DAT_0804dc54 = 3;
    }
  }
  DAT_0804dde4 = &DAT_0804dc44;
  DAT_0804dde0 = &DAT_0804ddbc;
  FUN_0803033c(1);
  FUN_0802fbac(&DAT_0804dde4);
  DAT_0804dc3c = param_1;
  if (param_1 == 0) {
    DAT_0804dc3c = 0;
  }
  DAT_0804dc38 = param_3;
  if (param_3 == 0) {
    DAT_0804dc38 = 0;
  }
  if (param_4 != 0) {
    DAT_0804dc40 = param_4;
  }
  iVar2 = FUN_0801acc0(DAT_0804ddf0);
  _DAT_87c74494 = &DAT_0804dde4;
  DAT_87c7449c = ((uint*)&DAT_0804dd98)[2];
  _DAT_87c744a0 = 0x87c7428c;
  _DAT_87c744a4 = 0;
  _DAT_87c74490 = 0;
  DAT_87c744ac = 1;
  _DAT_87c744b0 = &LAB_080255e4;
  DAT_87c744c0 = 0;
  if (param_5 == 0) {
    iVar4 = -0x7838bb3c;
    _DAT_87c744cc = &DAT_0804dde4;
    DAT_87c744d4 = ((uint*)&DAT_0804ddac)[2];
    _DAT_87c744d8 = 0;
    _DAT_87c744dc = 0;
    _DAT_87c744c8 = 0;
    DAT_87c744e4 = 0;
    _DAT_87c744e0 = 0;
    _DAT_87c744e8 = &LAB_08025588;
    DAT_87c744f8 = 0;
  }
  else {
    uVar3 = 0;
    do {
      iVar1 = uVar3 * 0x38;
      iVar4 = iVar1 + -0x7838bb04;
      *(undefined ***)(iVar1 + -0x7838bafc) = &DAT_0804dde4;
      *(undefined *)(iVar1 + -0x7838baf4) = ((uint*)&DAT_0804ddac)[2];
      *(uint *)(iVar1 + -0x7838baf0) = uVar3 * 0x200 + -0x7838bacc;
      *(undefined4 *)(iVar1 + -0x7838baec) = 0x200;
      *(undefined1 *)(iVar1 + -0x7838bae4) = 0;
      *(undefined4 *)(&DAT_87c74500 + iVar1) = 0;
      uVar3 = uVar3 + 1 & 0xff;
      *(undefined1 **)(iVar1 + -0x7838bae0) = &LAB_080255c0;
      *(undefined4 *)(iVar1 + -0x7838bae8) = 0;
      *(undefined1 *)(iVar1 + -0x7838bad0) = 0;
    } while (uVar3 < 2);
  }
  if (iVar2 != 0) {
    FUN_0802fc18(&DAT_0804dde4);
    DAT_0804de0c = 1;
    FUN_0802fe98(DAT_0804ddf0,1,0);
    FUN_0802fe98(DAT_0804ddf0,1);
    FUN_0802fe98(DAT_0804ddf0,2,0);
    FUN_0802fe98(DAT_0804ddf0,2,1);
    FUN_0802fcd0(&DAT_0804dde4,1);
    if (param_5 == 1) {
      FUN_080254d4(*(undefined4 *)(iVar4 + 8));
    }
  }
  return &DAT_0804dde4;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x080308f4 */
undefined4 FUN_080308f4(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  
  FUN_08030ac4(0x4e,0,param_2);
  while (_DAT_87c744c8 == 1) {
    FUN_0802fc0c(&DAT_0804dde4);
  }
  iVar1 = param_1;
  if ((param_1 == 0) && (iVar1 = param_1, param_2 != 0)) {
    FUN_08030af4();
    iVar1 = _DAT_87c744d8;
  }
  _DAT_87c744d8 = iVar1;
  _DAT_87c744dc = param_2;
  FUN_08030ac4(5,0,param_2);
  FUN_08030b04(0x87c744c4);
  return 0;
}




/* 0x08030944 */
void FUN_08030944(param_1)
int param_1;
{
  FUN_08030ac4(0x48,0,param_1);
  if (0 < param_1) {
    FUN_08030ac4(0xb7,0,0x3bb);
    FUN_08030af4();
  }
  DAT_0804ddf0 = param_1;
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0803098c */
void FUN_0803098c(param_1, param_2)
int param_1; uint param_2;
{
  int iVar1;
  uint uVar2;
  
  FUN_08030ac4(0x4c,0,param_2);
  while (_DAT_87c74490 == 1) {
    FUN_0802fc0c(&DAT_0804dde4);
  }
  iVar1 = param_1;
  uVar2 = param_2;
  if ((param_1 == 0) && (iVar1 = param_1, uVar2 = param_2, param_2 != 0)) {
    if (param_2 < 0x201) {
      FUN_08030ac4(0x55,0,param_2);
      FUN_08027bf8(0x87c7428c,0x200,0,param_2);
      iVar1 = _DAT_87c744a0;
      uVar2 = param_2;
    }
    else {
      FUN_08030ac4(0x55,0,param_2);
      FUN_08027bf8(0x87c7428c,0x200,0);
      DAT_87c744c0 = 1;
      _DAT_87c744a4 = 0x200;
      FUN_08030b04(0x87c7448c);
      _DAT_87c744a0 = 0x200;
      iVar1 = _DAT_87c744a0;
      uVar2 = param_2 - 0x200;
    }
  }
  _DAT_87c744a4 = uVar2;
  _DAT_87c744a0 = iVar1;
  DAT_87c744c0 = 0;
  FUN_08030ac4(3,0,_DAT_87c744a4);
  FUN_08030b04(0x87c7448c);
  while (_DAT_87c74490 == 1) {
    FUN_0802fc0c(&DAT_0804dde4);
  }
  _DAT_87c744a0 = 0x87c7428c;
  return;
}




/* 0x08030a40 */
void FUN_08030a40()
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar3 = 2;
  iVar2 = 0;
  iVar1 = thunk_FUN_08030abc();
  if (iVar1 != 0) {
    do {
      *(undefined4 *)(iVar2 * 4 + -0x7838be00) = *(undefined4 *)(iVar1 + iVar2 * 4);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x23);
    iVar1 = FUN_0802fb64(0x87c74200);
    DAT_0804dc54 = 3;
    if (iVar1 != 0) {
      for (; ((*(char *)(iVar4 + -0x7838bdfc) != '\0' && (iVar4 < 0x80)) && (iVar3 < 0xfe));
          iVar3 = iVar3 + 2) {
        (&DAT_0804dc96)[iVar3] = *(char *)(iVar4 + -0x7838bdfc);
        *(undefined1 *)(iVar3 + 0x804dc97) = 0;
        iVar4 = iVar4 + 1;
      }
      DAT_0804dc96 = (undefined1)iVar3;
      *(undefined1 **)(DAT_0804ddec + 0x28) = &DAT_0804dc96;
    }
  }
  return;
}




/* 0x08030aa8 */
void FUN_08030aa8(param_1)
int param_1;
{
  if (((param_1 == 0) || (param_1 == 1)) || (param_1 == 2)) {
    DAT_0804dc35 = (undefined1)param_1;
  }
  return;
}




/* 0x08030abc */
undefined4 thunk_FUN_08030abc()
{
  return 0x86000c8;
}




/* 0x08030abc */
undefined4 FUN_08030abc()
{
  return 0x86000c8;
}




/* 0x08030ac4 */
void FUN_08030ac4(param_1, param_2, param_3)
char param_1; char param_2; undefined4 param_3;
{
  DAT_0804df00 = DAT_0804df00 + 1;
  *(int *)(DAT_0804defc * 0xc + -0x78389674) = DAT_0804df00;
  *(char *)(DAT_0804defc * 0xc + -0x78389670) = param_2 + param_1;
  *(undefined4 *)(DAT_0804defc * 0xc + -0x7838966c) = param_3;
  DAT_0804defc = DAT_0804defc + 1 & 0xff;
  return;
}




/* 0x08030af4 */
undefined4 FUN_08030af4()
{
  do {
  } while (DAT_0804deec != 0);
  return 0;
}




/* 0x08030b04 */
undefined8 FUN_08030b04(param_1, param_2, param_3, param_4)
undefined4 * param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  
  *param_1 = 0x42525551;
  param_1[1] = 0;
  param_1[7] = 0;
  iVar4 = param_1[2];
  if (iVar4 != 0) {
    uVar6 = *(undefined4 *)(iVar4 + 0xc);
    param_1[3] = uVar6;
    uVar5 = (uint)*(byte *)(iVar4 + 0x29);
    if ((uVar5 != 0) || (uVar5 = 0, (*(byte *)(param_1 + 4) & 0xf) == 0)) {
      iVar4 = param_1[3];
      if (iVar4 != 0) {
        FUN_08030ac4(0xb7,0,0x5ff,param_4,uVar5,uVar6,param_4);
        do {
        } while (DAT_0804deec != 0);
      }
      uVar3 = param_1[6];
      uVar7 = *(byte *)(param_1 + 4) & 0xf;
      cVar1 = *(char *)(param_1 + 0xd);
      uVar8 = (uint)(*(byte *)(param_1 + 4) >> 7);
      if (cVar1 != '\0') {
        DAT_0804dee4 = uVar3;
      }
      if (uVar7 < 2) {
        if (uVar8 == 1) {
          uVar2 = 0x800000;
        }
        else {
          uVar2 = 0x80;
        }
        if ((*(uint *)(uVar7 * 4 + 0x78d91c0) & uVar2) == 0) {
          iVar4 = 7;
        }
        else {
          iVar4 = FUN_0803836c(iVar4,uVar7,uVar8,param_1[5],uVar3,*(undefined1 *)(param_1 + 8),cVar1
                              );
          uVar5 = uVar3;
          if (iVar4 == 0) {
            param_1[7] = 0;
            param_1[1] = 1;
            if ((cVar1 == '\0') && (DAT_0804dee4 != 0)) {
              param_1[6] = DAT_0804dee4 + param_1[6];
              DAT_0804dee4 = 0;
            }
            *(undefined4 **)(uVar7 * 0x1040 + uVar8 * 0x820 + -0x7838b6e4) = param_1;
          }
          else {
            param_1[1] = 3;
          }
        }
      }
      else {
        iVar4 = 3;
      }
      return CONCAT44(uVar5,iVar4);
    }
  }
  param_1[1] = 3;
  return 0x3ffffffff;
}




/* 0x08030b34 */
void FUN_08030b34(param_1, param_2, param_3)
undefined4 * param_1; undefined4 * param_2; uint param_3;
{
  undefined4 uVar1;
  uint uVar2;
  
  if ((param_3 != 0) && (param_1 != param_2)) {
    if (param_1 < param_2) {
      if ((((uint)param_2 | (uint)param_1) & 3) != 0) {
        uVar2 = param_3;
        if (((((uint)param_2 ^ (uint)param_1) & 3) == 0) && (3 < param_3)) {
          uVar2 = 4 - ((uint)param_2 & 3);
        }
        param_3 = param_3 - uVar2;
        for (; uVar2 != 0; uVar2 = uVar2 - 1) {
          uVar1 = FUN_08013a52(param_2);
          FUN_08013a62(param_1,uVar1);
          param_1 = (undefined4 *)((int)param_1 + 1);
          param_2 = (undefined4 *)((int)param_2 + 1);
        }
      }
      for (uVar2 = param_3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        uVar1 = *param_2;
        param_2 = param_2 + 1;
        *param_1 = uVar1;
        param_1 = param_1 + 1;
      }
      for (param_3 = param_3 & 3; param_3 != 0; param_3 = param_3 - 1) {
        uVar1 = FUN_08013a52(param_2);
        FUN_08013a62(param_1,uVar1);
        param_1 = (undefined4 *)((int)param_1 + 1);
        param_2 = (undefined4 *)((int)param_2 + 1);
      }
    }
    else {
      param_2 = (undefined4 *)((int)param_2 + param_3);
      param_1 = (undefined4 *)((int)param_1 + param_3);
      if ((((uint)param_2 | (uint)param_1) & 3) != 0) {
        uVar2 = param_3;
        if (((((uint)param_2 ^ (uint)param_1) & 3) == 0) && (4 < param_3)) {
          uVar2 = (uint)param_2 & 3;
        }
        param_3 = param_3 - uVar2;
        for (; uVar2 != 0; uVar2 = uVar2 - 1) {
          param_2 = (undefined4 *)((int)param_2 + -1);
          uVar1 = FUN_08013a52(param_2);
          param_1 = (undefined4 *)((int)param_1 + -1);
          FUN_08013a62(param_1,uVar1);
        }
      }
      for (uVar2 = param_3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        param_2 = param_2 + -1;
        param_1 = param_1 + -1;
        *param_1 = *param_2;
      }
      param_3 = param_3 & 3;
      if (param_3 != 0) {
        do {
          param_2 = (undefined4 *)((int)param_2 + -1);
          uVar1 = FUN_08013a52(param_2);
          param_1 = (undefined4 *)((int)param_1 + -1);
          FUN_08013a62(param_1,uVar1);
          param_3 = param_3 - 1;
        } while (param_3 != 0);
        return;
      }
    }
  }
  return;
}




/* 0x08030c10 */
undefined4 thunk_FUN_08030c10(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; int param_4;
{
  undefined4 uVar1;
  int iStack_10;
  
  uVar1 = 0;
  iStack_10 = param_4;
  FUN_08016484(&iStack_10);
  if ((iStack_10 == 0) || (*(int *)(param_1 + 0x18) == 3)) {
    uVar1 = 1;
  }
  return uVar1;
}




/* 0x08030c10 */
undefined4 FUN_08030c10(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; int param_4;
{
  undefined4 uVar1;
  int local_10;
  
  uVar1 = 0;
  local_10 = param_4;
  FUN_08016484(&local_10);
  if ((local_10 == 0) || (*(int *)(param_1 + 0x18) == 3)) {
    uVar1 = 1;
  }
  return uVar1;
}




/* 0x08030c2c */
undefined4 thunk_FUN_08030c2c(param_1)
int param_1;
{
  if (((*(uint *)(param_1 + 0x48) & 1) != 0) && (*(int *)(param_1 + 0x18) != 3)) {
    return 1;
  }
  return 0;
}




/* 0x08030c2c */
undefined4 FUN_08030c2c(param_1)
int param_1;
{
  if (((*(uint *)(param_1 + 0x48) & 1) != 0) && (*(int *)(param_1 + 0x18) != 3)) {
    return 1;
  }
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

