/* Auto-generated: fs_extfs.c */
/* Functions: 16 */
#include "globals.h"

/* 0x080136ac */
int FUN_080136ac(param_1)
int param_1;
{
  int iVar1;
  
  if (param_1 == 0) {
    ((code*)DAT_0804cd60)("fs_extfs.c",0x16a,0x302f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_08020d4c();
  iVar1 = 0;
  do {
    if ((&DAT_0804d624)[iVar1] == 0) {
      (&DAT_0804d624)[iVar1] = param_1;
      FUN_08020d64();
      return iVar1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 2);
  FUN_08020d64();
  return -1;
}




/* 0x08013704 */
void boot_canary_check()
{
  int iVar1;
  int iVar2;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 local_20;
  int local_1c;
  
  iVar1 = DAT_0804cd58;
  puVar5 = &local_20;
  local_1c = DAT_0804cd58;
  iVar4 = 0;
  local_20 = 0;
  do {
    iVar2 = FUN_08006898(puVar5,&DAT_0804cd58,4);
    if (iVar2 == 0) goto LAB_08013732;
    iVar4 = iVar4 + 1;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
  } while (iVar4 < 0x3c);
  if (true) {
    boot_log_message("Canary NOT found");
    uVar3 = extraout_r1_00;
  }
  else {
LAB_08013732:
    boot_log_message("Canary found");
    *(undefined1 *)puVar5 = 0;
    uVar3 = extraout_r1;
  }
  if (local_1c != iVar1) {
    FUN_08010960(local_1c,uVar3,local_20,local_1c);
    return;
  }
  return;
}




/* 0x08013780 */
undefined4 FUN_08013780(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  int iVar1;
  undefined4 *puVar2;
  char *pcVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  int local_1c;
  
  iVar1 = DAT_0804cd58;
  puVar2 = &local_28;
  local_1c = DAT_0804cd58;
  local_28 = param_1;
  uStack_24 = param_2;
  uStack_20 = param_3;
  if (DAT_0804cebd == '\0') {
    if (DAT_0804cebe != '\0') {
      FUN_08006a30(&DAT_0804cec3,&LAB_08007b1c,8);
      puVar2 = (undefined4 *)&DAT_0804cec3;
      goto LAB_080137b2;
    }
    if (DAT_0804cebf == '\0') {
      if (DAT_0804cec0 == '\0') {
        if (DAT_0804cec1 == '\0') {
          if (DAT_0804cec2 == '\0') goto LAB_08013810;
          boot_canary_check();
          pcVar3 = "TEST FAILURE. Canary overwritten";
        }
        else {
          pcVar3 = (char *)&DAT_0804cd58;
        }
      }
      else {
        iVar6 = 0;
        local_28 = 0;
        do {
          iVar4 = FUN_08006898(puVar2,&DAT_0804cd58,4);
          if (iVar4 == 0) goto LAB_080137f0;
          iVar6 = iVar6 + 1;
          puVar2 = (undefined4 *)((int)puVar2 + 1);
        } while (iVar6 < 0x3c);
        if (true) {
          pcVar3 = "TEST FAILURE. Canary not found";
        }
        else {
LAB_080137f0:
          pcVar3 = "Canary found";
        }
      }
    }
    else {
      FUN_08006a30(&LAB_080274d4,&LAB_08007b1c,8);
      pcVar3 = "TEST FAILURE. Code overwritten";
    }
  }
  else {
    FUN_08006a30(&uStack_24,&LAB_08007b1c,8);
    puVar2 = &uStack_24;
LAB_080137b2:
    FUN_08007b18(puVar2);
    pcVar3 = "TEST FAILURE. DEP did not prevent execution.";
  }
  boot_log_message(pcVar3);
LAB_08013810:
  if (local_1c != iVar1) {
    uVar5 = FUN_08010960(local_28,uStack_24,uStack_20,local_1c);
    return uVar5;
  }
  return local_28;
}




/* 0x080138ec */
undefined4 FUN_080138ec(param_1, param_2)
int param_1; int param_2;
{
  if (param_2 != 0) {
    *(short *)(param_1 + 2) = DAT_0804d166;
  }
  if (0x7f < *(ushort *)(param_1 + 2)) {
    if ((param_2 == 0) || (DAT_0804d165 == '\0')) {
      return 0x18;
    }
    *(undefined2 *)(param_1 + 2) = 0;
  }
  DAT_0804d166 = *(short *)(param_1 + 2) + 1;
  return 0;
}




/* 0x08013918 */
int FUN_08013918(param_1, param_2, param_3, param_4, param_5, param_6)
int param_1; undefined4 param_2; uint param_3; uint param_4; int * param_5; undefined4 * param_6;
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if ((param_4 == 0 && (0x4f < param_3) <= param_4) || (param_5 == (int *)0x0)) {
    firehose_log("ERROR: length < sizeof(eighty_byte_header_type) || hash_position_address == NULL")
    ;
    iVar1 = 0;
  }
  else {
    FUN_08006d14(&DAT_0805a080,0x28);
    DAT_0805a0a0 = 0x1a;
    if (*(int *)(param_1 + 4) == 0x73d71034) {
      DAT_0805a084 = 0x50;
      iVar1 = *(int *)(param_1 + 0x14);
      DAT_0805a08c = *(undefined4 *)(param_1 + 0x20);
      iVar2 = *(int *)(param_1 + 0x14) + *(int *)(param_1 + 0x2c);
      DAT_0805a094 = *(undefined4 *)(param_1 + 0x30);
      iVar3 = *(int *)(param_1 + 0x14) + *(int *)(param_1 + 0x24);
      DAT_0805a09c = *(undefined4 *)(param_1 + 0x28);
    }
    else {
      DAT_0805a084 = 0x28;
      iVar1 = *(int *)(param_1 + 8);
      DAT_0805a08c = *(undefined4 *)(param_1 + 0x14);
      iVar2 = *(int *)(param_1 + 8) + *(int *)(param_1 + 0x20);
      DAT_0805a094 = *(undefined4 *)(param_1 + 0x24);
      iVar3 = *(int *)(param_1 + 8) + *(int *)(param_1 + 0x18);
      DAT_0805a09c = *(undefined4 *)(param_1 + 0x1c);
    }
    DAT_0805a098 = iVar3 + param_1;
    DAT_0805a090 = iVar2 + param_1;
    DAT_0805a088 = iVar1 + param_1;
    DAT_0805a080 = param_1;
    firehose_log("Calling AuthenticateImage");
    iVar1 = AuthenticateImage(param_1);
    firehose_log("Back from AuthenticateImage, retval=0x%X",iVar1);
    if (iVar1 == 1) {
      *param_5 = DAT_0805a088;
      *param_6 = DAT_0805a08c;
      param_6[1] = 0;
    }
  }
  return iVar1;
}




/* 0x08013a24 */
int FUN_08013a24(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  int iVar1;
  int extraout_r2;
  int iVar2;
  int extraout_r3;
  
  iVar2 = 0;
  while( true ) {
    if (param_3 <= iVar2) {
      return 0;
    }
    iVar2 = FUN_08013a52(param_1);
    iVar1 = FUN_08013a52(param_2);
    if (iVar2 != iVar1) break;
    iVar2 = extraout_r3 + 1;
    param_3 = extraout_r2;
    param_2 = param_2 + 1;
    param_1 = param_1 + 1;
  }
  return extraout_r3 + 1;
}




/* 0x08013a52 */
uint FUN_08013a52(param_1)
uint param_1;
{
  return *(uint *)(param_1 & 0xfffffffc) >> ((param_1 << 0x1e) >> 0x1b) & 0xff;
}




/* 0x08013a62 */
void FUN_08013a62(param_1, param_2)
uint param_1; int param_2;
{
  uint uVar1;
  
  uVar1 = (param_1 << 0x1e) >> 0x1b;
  *(uint *)(param_1 & 0xfffffffc) =
       *(uint *)(param_1 & 0xfffffffc) & ~(0xff << uVar1) | param_2 << uVar1;
  return;
}




/* 0x08013a7c */
undefined4 FUN_08013a7c(param_1)
int param_1;
{
  undefined4 uVar1;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x14) == 0xd00cafe)) {
                    /* WARNING: Could not recover jumptable at 0x08013a90. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*(int *)(param_1 + 4) + 4))();
    return uVar1;
  }
  return 0xffffffff;
}



undefined ** FUN_08013ab0()
{
  return &PTR_LAB_08013b42_1_08051460;
}




/* 0x0801d708 */
int FUN_0801d708(param_1, param_2)
int * param_1; int param_2;
{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  if (param_2 != 1) {
    if (param_2 != 2) {
      ((code*)DAT_0804cd60)("fs_extfs.c",0x2d5,0x302f);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (param_1[0x56] == 1) {
      (**(code **)(*(int *)(iVar2 + 0x10) + 0x28))(param_1[0x55]);
      param_1[0x56] = 0;
      goto LAB_0801d74a;
    }
  }
  if (param_1[0x56] != 0) {
    return 0;
  }
LAB_0801d74a:
  uVar1 = 0;
  if (param_2 == 2) {
    uVar1 = 2;
  }
  iVar2 = (**(code **)(*(int *)(iVar2 + 0x10) + 0x14))(param_1 + 9,uVar1);
  if (-1 < iVar2) {
    param_1[0x55] = iVar2;
    param_1[0x56] = param_2;
    return 0;
  }
  return iVar2;
}




/* 0x08020684 */
int FUN_08020684(param_1)
int param_1;
{
  int iVar1;
  
  FUN_08020d4c();
  iVar1 = (&DAT_0804d624)[param_1];
  if (iVar1 != 0) {
    (&DAT_0804d624)[param_1] = 0;
    FUN_08020d64();
    return iVar1;
  }
  ((code*)DAT_0804cd60)("fs_extfs.c",0x195,0x302f);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x080206c8 */
undefined4 FUN_080206c8(param_1, param_2, param_3, param_4, param_5)
undefined4 * param_1; ushort * param_2; undefined4 * param_3; byte * param_4; int param_5;
{
  ushort uVar1;
  byte bVar2;
  undefined4 uVar3;
  uint uVar4;
  ushort *puVar5;
  ushort *puVar6;
  byte *pbVar7;
  int iVar8;
  
  pbVar7 = (byte *)*param_3;
  uVar3 = 0;
  puVar6 = (ushort *)*param_1;
  do {
    if (param_2 <= puVar6) {
LAB_080207b6:
      *param_1 = puVar6;
      *param_3 = pbVar7;
      return uVar3;
    }
    puVar5 = puVar6 + 1;
    uVar4 = (uint)*puVar6;
    if (uVar4 - 0xd800 < 0x400) {
      if (param_2 <= puVar5) {
        uVar3 = 1;
        goto LAB_080207b6;
      }
      uVar1 = *puVar5;
      if (uVar1 - 0xdc00 < 0x400) {
        puVar5 = puVar6 + 2;
        uVar4 = uVar4 * 0x400 + (uint)uVar1 + 0xfca02400;
      }
      else if (param_5 == 0) goto LAB_08020712;
    }
    else if ((param_5 == 0) && (uVar4 - 0xdc00 < 0x400)) {
LAB_08020712:
      uVar3 = 3;
      goto LAB_080207b6;
    }
    if (uVar4 < 0x80) {
      iVar8 = 1;
    }
    else if (uVar4 < 0x800) {
      iVar8 = 2;
    }
    else if (uVar4 < 0x10000) {
      iVar8 = 3;
    }
    else if (uVar4 < 0x110000) {
      iVar8 = 4;
    }
    else {
      iVar8 = 3;
      uVar4 = 0xfffd;
    }
    pbVar7 = pbVar7 + iVar8;
    if (param_4 < pbVar7) {
      pbVar7 = pbVar7 + -iVar8;
      uVar3 = 2;
      goto LAB_080207b6;
    }
    if (iVar8 == 1) {
LAB_080207a0:
      pbVar7 = pbVar7 + -1;
      *pbVar7 = (&UNK_0803dc84)[iVar8] | (byte)uVar4;
    }
    else {
      if (iVar8 == 2) {
LAB_08020792:
        bVar2 = (byte)uVar4;
        uVar4 = uVar4 >> 6;
        pbVar7 = pbVar7 + -1;
        *pbVar7 = bVar2 & 0xbf | 0x80;
        goto LAB_080207a0;
      }
      if (iVar8 == 3) {
LAB_08020784:
        bVar2 = (byte)uVar4;
        uVar4 = uVar4 >> 6;
        pbVar7 = pbVar7 + -1;
        *pbVar7 = bVar2 & 0xbf | 0x80;
        goto LAB_08020792;
      }
      if (iVar8 == 4) {
        bVar2 = (byte)uVar4;
        uVar4 = uVar4 >> 6;
        pbVar7 = pbVar7 + -1;
        *pbVar7 = bVar2 & 0xbf | 0x80;
        goto LAB_08020784;
      }
    }
    pbVar7 = pbVar7 + iVar8;
    puVar6 = puVar5;
  } while( true );
}




/* 0x080207c4 */
undefined4 FUN_080207c4(param_1, param_2, param_3, param_4, param_5)
undefined4 * param_1; byte * param_2; undefined4 * param_3; short * param_4; int param_5;
{
  int iVar1;
  uint uVar2;
  byte *pbVar3;
  byte *pbVar4;
  short *psVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  
  uVar8 = 0;
  pbVar3 = (byte *)*param_1;
  psVar5 = (short *)*param_3;
  do {
    if (param_2 <= pbVar3) {
LAB_080208b4:
      *param_1 = pbVar3;
      *param_3 = psVar5;
      return uVar8;
    }
    iVar6 = 0;
    uVar7 = (uint)(byte)(&DAT_0803dc8b)[*pbVar3];
    if (param_2 <= pbVar3 + uVar7) {
      uVar8 = 1;
      goto LAB_080208b4;
    }
    iVar1 = FUN_08020dde(pbVar3,uVar7 + 1);
    if (iVar1 == 0) {
LAB_0802080a:
      uVar8 = 3;
      goto LAB_080208b4;
    }
    pbVar4 = pbVar3;
    switch(uVar7) {
    case 5:
      pbVar4 = pbVar3 + 1;
      iVar6 = (uint)*pbVar3 << 6;
    case 4:
      pbVar3 = pbVar4 + 1;
      iVar6 = ((uint)*pbVar4 + iVar6) * 0x40;
    case 3:
      pbVar4 = pbVar3 + 1;
      iVar6 = ((uint)*pbVar3 + iVar6) * 0x40;
    case 2:
      pbVar3 = pbVar4 + 1;
      iVar6 = ((uint)*pbVar4 + iVar6) * 0x40;
    case 1:
      pbVar4 = pbVar3 + 1;
      iVar6 = ((uint)*pbVar3 + iVar6) * 0x40;
    case 0:
      pbVar3 = pbVar4 + 1;
      iVar6 = iVar6 + (uint)*pbVar4;
    }
    uVar2 = iVar6 - *(int *)(&DAT_0803dd8c + uVar7 * 4);
    if (param_4 <= psVar5) {
LAB_08020848:
      uVar8 = 2;
      pbVar3 = pbVar3 + (-1 - uVar7);
      goto LAB_080208b4;
    }
    if (uVar2 < 0x10000) {
      if (uVar2 - 0xd800 < 0x800) {
        if (param_5 == 0) {
          pbVar3 = pbVar3 + (-1 - uVar7);
          goto LAB_0802080a;
        }
LAB_08020880:
        uVar2 = 0xfffd;
      }
      *psVar5 = (short)uVar2;
      psVar5 = psVar5 + 1;
    }
    else {
      if (0x10ffff < uVar2) {
        if (param_5 != 0) goto LAB_08020880;
        uVar8 = 3;
        pbVar3 = pbVar3 + (-1 - uVar7);
        goto LAB_080208b4;
      }
      if (param_4 <= psVar5 + 1) goto LAB_08020848;
      *psVar5 = (short)(uVar2 - 0x10000 >> 10) + -0x2800;
      psVar5[1] = (ushort)(uVar2 * 0x400000 >> 0x16) + 0xdc00;
      psVar5 = psVar5 + 2;
    }
  } while( true );
}




/* 0x080208cc */
int FUN_080208cc(param_1)
ushort * param_1;
{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  
  uVar1 = *param_1;
  iVar3 = uVar1 - 0x7bc;
  iVar3 = ((int)(iVar3 + ((uint)(iVar3 >> 0x1f) >> 0x1e)) >> 2) * 0x5b5;
  if ((uVar1 & 3) == 0) {
    iVar3 = (uint)*(ushort *)(&DAT_0803c94a + (uint)param_1[1] * 2) + iVar3;
  }
  else {
    iVar3 = (uint)(ushort)(&DAT_0803c928)[uVar1 & 3] + iVar3 +
            (uint)*(ushort *)(&DAT_0803c930 + (uint)param_1[1] * 2);
  }
  uVar2 = (uint)param_1[5] +
          ((uint)param_1[4] + ((uint)param_1[3] + (iVar3 + -1 + (uint)param_1[2]) * 0x18) * 0x3c) *
          0x3c;
  if (0xe205797f < uVar2) {
    uVar2 = uVar2 - 0x15180;
  }
  if (uVar2 < 0xed3159ff) {
    return uVar2 + 0x12cea600;
  }
  return -1;
}




/* 0x08020964 */
undefined4 FUN_08020964(param_1, param_2)
int param_1; uint param_2;
{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = 0xffffffff;
  if (((param_1 != 0) && (param_2 != 0)) && (0xf < param_2)) {
    iVar3 = 0;
    do {
      iVar2 = iVar3;
      if ((&DAT_87c00a2c)[iVar2 * 7] == 0) {
        (&DAT_87c00a2c)[iVar2 * 7] = 1;
        iVar3 = iVar2;
        break;
      }
      iVar3 = iVar2 + 1;
    } while (iVar3 == 0);
    if (iVar3 == 0) {
      (&DAT_87c00a30)[iVar2 * 7] = param_1;
      (&DAT_87c00a38)[iVar2 * 7] = param_2 + param_1;
      iVar3 = FUN_08020ad0();
      if (iVar3 == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = 0xffffffff;
      }
    }
  }
  return uVar1;
}




/* 0x080209bc */
void FUN_080209bc()
{
  FUN_08006d14(&DAT_87c00a2c,0x1c);
  return;
}




