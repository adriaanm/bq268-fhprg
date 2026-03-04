/* Auto-generated: fhprg_8030dac.c */
/* Functions: 11 */
#include "globals.h"

/* 0x08030dac */
void thunk_FUN_08030dac()
{
  int iVar1;
  int iVar2;
  uint *puVar3;
  undefined *puVar4;
  uint uVar5;
  uint uStack_4c;
  undefined1 auStack_48 [32];
  int iStack_28;
  
  iVar1 = DAT_0804cd58;
  iStack_28 = DAT_0804cd58;
  iVar2 = FUN_0800d4ba("/dev/icbcfg/boot",&DAT_080542a8);
  if (iVar2 == 0) {
    iVar2 = FUN_080161f8(2,0x87fcc000,0x60,auStack_48,0x20);
    if (((iVar2 == 0) && (iVar2 = FUN_08013a24(auStack_48,0x87fcc060,0x20), iVar2 == 0)) &&
       (iVar2 = FUN_08013a24(auStack_48,0x8600784,0x20), iVar2 == 0)) {
      iVar2 = 0;
      do {
        if (*(int *)(iVar2 * 8 + -0x78033ffc) != 0) {
          FUN_08008a20(*(uint *)(iVar2 * 8 + -0x78034000) & 0xfffff000);
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < 0xc);
    }
    else {
      uVar5 = 0;
      do {
        uStack_4c = (&DAT_080542a8)[((int)uVar5 >> 1) * 0x1e + (uVar5 & 1) * 6];
        puVar4 = (undefined *)(&DAT_080542a8)[((int)uVar5 >> 1) * 0x1e + (uVar5 & 1) * 6 + 2];
        if (puVar4 != (undefined *)0x0) {
          if ((uStack_4c < 0x87c00000) && ((undefined *)0x87ce0000 < puVar4 + uStack_4c)) {
            FUN_08008a20(&uStack_4c,&DAT_87c00000);
            puVar4 = puVar4 + uStack_4c + 0x78320000;
            puVar3 = (uint *)0x87ce0000;
          }
          else {
            if ((uStack_4c < 0x87c00000) && (puVar4 + uStack_4c < (undefined *)0x87ce0000)) {
              puVar4 = &DAT_87c00000;
            }
            else {
              puVar3 = (uint *)0x87ce0000;
              if (uStack_4c < 0x87ce0000) {
                puVar4 = puVar4 + uStack_4c + 0x78320000;
                goto LAB_08030e80;
              }
            }
            puVar3 = &uStack_4c;
          }
LAB_08030e80:
          FUN_08008a20(puVar3,puVar4);
        }
        uVar5 = uVar5 + 1;
      } while ((int)uVar5 < 2);
    }
  }
  if (iStack_28 == iVar1) {
    return;
  }
  FUN_08010960();
  return;
}




/* 0x08030dac */
void FUN_08030dac()
{
  int iVar1;
  int iVar2;
  uint *puVar3;
  undefined *puVar4;
  uint uVar5;
  uint local_4c;
  undefined1 auStack_48 [32];
  int local_28;
  
  iVar1 = DAT_0804cd58;
  local_28 = DAT_0804cd58;
  iVar2 = FUN_0800d4ba("/dev/icbcfg/boot",&DAT_080542a8);
  if (iVar2 == 0) {
    iVar2 = FUN_080161f8(2,0x87fcc000,0x60,auStack_48,0x20);
    if (((iVar2 == 0) && (iVar2 = FUN_08013a24(auStack_48,0x87fcc060,0x20), iVar2 == 0)) &&
       (iVar2 = FUN_08013a24(auStack_48,0x8600784,0x20), iVar2 == 0)) {
      iVar2 = 0;
      do {
        if (*(int *)(iVar2 * 8 + -0x78033ffc) != 0) {
          FUN_08008a20(*(uint *)(iVar2 * 8 + -0x78034000) & 0xfffff000);
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < 0xc);
    }
    else {
      uVar5 = 0;
      do {
        local_4c = (&DAT_080542a8)[((int)uVar5 >> 1) * 0x1e + (uVar5 & 1) * 6];
        puVar4 = (undefined *)(&DAT_080542a8)[((int)uVar5 >> 1) * 0x1e + (uVar5 & 1) * 6 + 2];
        if (puVar4 != (undefined *)0x0) {
          if ((local_4c < 0x87c00000) && ((undefined *)0x87ce0000 < puVar4 + local_4c)) {
            FUN_08008a20(&local_4c,&DAT_87c00000);
            puVar4 = puVar4 + local_4c + 0x78320000;
            puVar3 = (uint *)0x87ce0000;
          }
          else {
            if ((local_4c < 0x87c00000) && (puVar4 + local_4c < (undefined *)0x87ce0000)) {
              puVar4 = &DAT_87c00000;
            }
            else {
              puVar3 = (uint *)0x87ce0000;
              if (local_4c < 0x87ce0000) {
                puVar4 = puVar4 + local_4c + 0x78320000;
                goto LAB_08030e80;
              }
            }
            puVar3 = &local_4c;
          }
LAB_08030e80:
          FUN_08008a20(puVar3,puVar4);
        }
        uVar5 = uVar5 + 1;
      } while ((int)uVar5 < 2);
    }
  }
  if (local_28 == iVar1) {
    return;
  }
  FUN_08010960();
  return;
}




/* 0x08030ecc */
void FUN_08030ecc(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  FUN_08031170(0,param_2,param_1,param_2,0,1);
  return;
}




/* 0x08030ef0 */
undefined4 FUN_08030ef0(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  *(undefined ***)(param_2 + 0x14) = &PTR_LAB_08021a98_1_0803b1c0;
  FUN_08020da0(param_2 + 0x20,0x8124,0);
  *(undefined4 *)(param_2 + 0x28) = *(undefined4 *)(*(int *)(param_1 + 0xc) + param_3 * 0xc + -0x70)
  ;
  *(undefined2 *)(param_2 + 0x22) = 1;
  *(undefined4 *)(param_2 + 0x34) = 0;
  *(undefined4 *)(param_2 + 0x38) = 0;
  *(undefined4 *)(param_2 + 0x3c) = 0;
  *(undefined2 *)(param_2 + 0xc) = *(undefined2 *)(param_2 + 0x20);
  *(undefined4 *)(param_2 + 0x60) = *(undefined4 *)(*(int *)(param_1 + 0xc) + param_3 * 0xc + -0x74)
  ;
  return 0;
}




/* 0x08030fa8 */
void FUN_08030fa8()
{
  int iVar1;
  uint uVar2;
  undefined8 uVar3;
  uint local_18;
  int local_14;
  undefined4 local_10;
  
  iVar1 = 0;
  local_18 = 0;
  local_14 = 0;
  while (local_18 == 0 && local_14 == 0) {
    uVar2 = DAT_08055fb8;
    iVar1 = DAT_08055fbc;
    if ((uint)(DAT_08055fb8 < 0x1001) <= (uint)-DAT_08055fbc) {
      iVar1 = 0;
      uVar2 = 0x1000;
    }
    iVar1 = FUN_08021ca4(&local_10,0x1000 - DAT_08055fb8,uVar2,iVar1,&local_18);
  }
  if (iVar1 == 0) {
    FUN_08039030(&DAT_08055ea0,local_10,local_18,local_14);
    uVar3 = FUN_08038948();
    if ((int)uVar3 == 1) {
      firehose_log("XML (%d bytes) not validated",(int)((ulonglong)uVar3 >> 0x20),local_18,local_14)
      ;
      handle_response(0);
    }
    else {
      if ((uint)-local_14 < (uint)(local_18 < 0x1001)) {
        FUN_08027bf8(&DAT_08054e98,0x1000,local_10);
        FUN_08039030(&DAT_08055ea0,&DAT_08054e98,local_18,local_14);
        do {
          iVar1 = firehose_dispatch();
        } while (iVar1 != 1);
        return;
      }
      firehose_log("XML file cannot fit in buffer",local_14,0x1000 - local_18);
    }
    FUN_08039030(&DAT_08055ea0,0,0,0);
  }
  return;
}




/* 0x080310a0 */
undefined4 FUN_080310a0(param_1, param_2, param_3, param_4, param_5, param_6)
undefined4 * param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4; uint * param_5; int param_6;
{
  uint uVar1;
  
  if (DAT_08055fd0 == '\0') {
    FUN_0801b6bc("queue %d");
    FUN_0802f5d4((&DAT_08054e90)[DAT_08055fd4],param_3,0x8028811,&DAT_08055f88);
    if (DAT_08055f88 != 0) {
      return 2;
    }
    DAT_08055f98 = '\0';
    DAT_08055f90 = 0;
    DAT_08055f94 = 0;
    DAT_08055fd0 = '\x01';
  }
  if (param_6 != 1) {
    while (uVar1 = DAT_08055f94, DAT_08055f98 == '\0') {
      FUN_0802f57c();
    }
    if (DAT_08055f94 < DAT_08055fbc ||
        DAT_08055fbc - DAT_08055f94 < (uint)(DAT_08055f90 <= DAT_08055fb8)) {
      *param_5 = DAT_08055f90;
      param_5[1] = uVar1;
      *param_1 = (&DAT_08054e90)[DAT_08055fd4];
      DAT_08055fd0 = '\0';
      DAT_08055fd4 = 1 - DAT_08055fd4;
      if (DAT_08055f88 == 0) {
        DAT_08055fd0 = 0;
        return 0;
      }
    }
    else {
      FUN_0801b6bc("read %i bufsize %i");
    }
    return 2;
  }
  return 0;
}




/* 0x08031170 */
int FUN_08031170(param_1, param_2, param_3, param_4, param_5, param_6)
undefined4 * param_1; undefined4 param_2; int param_3; uint param_4; uint * param_5; int param_6;
{
  int iVar1;
  int iVar2;
  char *pcVar3;
  undefined *puVar4;
  undefined4 extraout_r1;
  uint uVar5;
  undefined *extraout_r1_00;
  uint uVar6;
  bool bVar7;
  undefined *puVar8;
  uint local_48;
  uint uStack_44;
  undefined4 local_40 [2];
  undefined4 *puStack_38;
  undefined4 uStack_34;
  int local_30;
  uint uStack_2c;
  
  puVar4 = &DAT_08058008;
  puVar8 = &DAT_08058008;
  puStack_38 = param_1;
  uStack_34 = param_2;
  local_30 = param_3;
  uStack_2c = param_4;
  if (DAT_08055fd8 == '\x01') {
    do {
      iVar1 = 0;
      if (DAT_08055fd9 == '\0') {
        iVar2 = FUN_080310a0(param_1,puVar4,0x2000,0,param_5,param_6);
        if (iVar2 != 0) {
LAB_08031280:
          FUN_0801daf0();
          return iVar2;
        }
        if (param_6 == 1) {
          return 0;
        }
        firehose_log("Validation is enabled.");
        iVar2 = FUN_08013918(*param_1,extraout_r1,*param_5,param_5[1],local_40,&local_48);
        if (iVar2 == 0) {
          firehose_log("ERROR: Failed to authenticate Digital Signature");
          pcVar3 = "Resetting validation state";
          goto LAB_0803131c;
        }
        DAT_08055fd9 = '\x01';
        DAT_08055fc8 = 0;
        DAT_08055fcc = 0;
        DAT_08057fe0 = local_48 >> 5 | uStack_44 << 0x1b;
        DAT_08057fe4 = uStack_44 >> 5;
        FUN_08027bf8(&DAT_08055fda + (DAT_08057ff0 - DAT_08057fe0) * 0x20,0x2000,local_40[0]);
        DAT_08057fe8 = DAT_08057ff0 - DAT_08057fe0;
        DAT_08057fec = (DAT_08057ff4 - DAT_08057fe4) - (uint)(DAT_08057ff0 < DAT_08057fe0);
      }
      else {
        iVar2 = local_30;
        uVar5 = uStack_2c;
        if (DAT_08057fe8 == DAT_08057ff0 - 1 &&
            DAT_08057fec == DAT_08057ff4 + -1 + (uint)(DAT_08057ff0 != 0)) {
          iVar2 = DAT_08057ff8 << 5;
          uVar5 = DAT_08057ffc << 5 | DAT_08057ff8 >> 0x1b;
        }
        iVar2 = FUN_080310a0(param_1,DAT_08057ff0 - 1,iVar2,uVar5,param_5,param_6);
        if (iVar2 != 0) goto LAB_08031280;
        if (param_6 == 1) {
          return 0;
        }
        if (DAT_08057fe0 == 0 && DAT_08057fe4 == 0) {
          pcVar3 = "No more hashes to validate against";
LAB_0803131c:
          firehose_log(pcVar3);
          handle_response(0);
          FUN_0801daf0();
          return 4;
        }
        FUN_0800d59c(*param_1,*param_5,puVar8);
        iVar2 = FUN_08006898(puVar8,&DAT_08055fda + DAT_08057fe8 * 0x20,0x20);
        if (iVar2 != 0) {
          firehose_log("ERROR: Hash value mismatch. Rejecting this packet.");
          FUN_080275c4("Expected:      ",&DAT_08055fda + DAT_08057fe8 * 0x20,0x20,0);
          FUN_080275c4("Found instead: ",puVar8,0x20,0);
          firehose_log("(P%04d) (H%04d) Table %d",DAT_08057fec,DAT_08055fc8 + -1,
                       DAT_08055fcc + -1 + (uint)(DAT_08055fc8 != 0),DAT_08057fe8,DAT_08057fec,
                       DAT_08058000,DAT_08058004);
          pcVar3 = "Resetting validation state.";
          goto LAB_0803131c;
        }
        bVar7 = DAT_08057fe0 != 0;
        DAT_08057fe0 = DAT_08057fe0 - 1;
        DAT_08057fe4 = (DAT_08057fe4 - 1) + (uint)bVar7;
        if (DAT_08057fe8 != DAT_08057ff0 - 1 ||
            DAT_08057fec != DAT_08057ff4 + -1 + (uint)(DAT_08057ff0 != 0)) {
          bVar7 = 0xfffffffe < DAT_08057fe8;
          DAT_08057fe8 = DAT_08057fe8 + 1;
          DAT_08057fec = DAT_08057fec + (uint)bVar7;
          return 0;
        }
        uVar5 = *param_5;
        uVar6 = param_5[1];
        if ((uint)(uVar5 < 0x2001) <= -uVar6) {
          uVar6 = 0;
          uVar5 = 0x2000;
        }
        FUN_08027bf8(&DAT_08055fda,0x2000,*param_1,uVar5);
        DAT_08057fe4 = uVar6 >> 5;
        DAT_08057fe8 = 0;
        DAT_08057fec = 0;
        DAT_08057fe0 = uVar5 >> 5 | uVar6 << 0x1b;
        if (DAT_08057ff0 != DAT_08057ff8 || DAT_08057ff4 != DAT_08057ffc) {
          DAT_08057ff0 = DAT_08057ff8;
          DAT_08057ff4 = DAT_08057ffc;
        }
        if (DAT_08057fe4 == 0 && (1 < DAT_08057fe0) <= DAT_08057fe4) {
          FUN_0801b6bc("read hashes %d");
        }
        bVar7 = 0xfffffffe < DAT_08058000;
        DAT_08058000 = DAT_08058000 + 1;
        DAT_08058004 = DAT_08058004 + (uint)bVar7;
      }
      handle_response(1);
      puVar4 = extraout_r1_00;
    } while (iVar1 == 0);
  }
  else {
    iVar1 = FUN_080310a0(param_1,&DAT_08058008,param_3,param_4,param_5,param_6);
    if (iVar1 != 0) {
      return iVar1;
    }
    if ((param_6 != 1) && (DAT_08058481 == '\x01')) {
      FUN_0800d59c(*param_1,*param_5,puVar8);
    }
  }
  return 0;
}




/* 0x08031548 */
uint FUN_08031548(param_1, param_2)
uint param_1; uint param_2;
{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  for (uVar2 = 0; uVar2 < param_2; uVar2 = uVar2 + 1) {
    if ((param_1 & 1) != 0) {
      uVar1 = uVar1 | 1 << ((param_2 - uVar2) - 1 & 0xff);
    }
    param_1 = (int)param_1 >> 1;
  }
  return uVar1;
}




/* 0x0803156c */
void FUN_0803156c(param_1)
int param_1;
{
  uint uVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 8);
  uVar1 = FUN_0800c580(uVar2);
  FUN_0800c5d4(uVar2,3,1,0);
  FUN_0800c5ea(uVar2,1);
  FUN_0800c6d2(uVar2,(uint)(0.0 < (double)uVar1 * 0.5) * (int)(longlong)((double)uVar1 * 0.5));
  FUN_0800c602(uVar2,0);
  FUN_0800c6da(uVar2,1);
  FUN_0800c668(uVar2,0);
  FUN_0800c5c2(uVar2,0);
  FUN_0800c648(uVar2,0);
  FUN_0800c632(uVar2,*(undefined4 *)(param_1 + 0x10));
  FUN_0800c56c(uVar2,0xffffffff);
  FUN_0800c6aa(uVar2,0xf);
  FUN_0800c618(uVar2,0);
  FUN_0800c6f0(uVar2,0);
  FUN_0800c67e(uVar2,0x10);
  FUN_0800c5b2(uVar2);
  FUN_0800c5ba(uVar2);
  FUN_0800c5aa(uVar2);
  FUN_0800c65a(uVar2,1);
  FUN_0800c6c4(uVar2,1);
  uVar2 = *(undefined4 *)(param_1 + 8);
  FUN_0800c700(uVar2,0x1000);
  FUN_0800c698(uVar2,1);
  *(undefined4 *)(param_1 + 0x34) = 0x1000;
  return;
}




/* 0x08031632 */
int FUN_08031632(param_1, param_2)
int param_1; int param_2;
{
  short sVar1;
  int iVar2;
  int iVar3;
  int extraout_r3;
  
  while ((iVar3 = param_2 + -1, 0 < iVar3 &&
         ((sVar1 = *(short *)(param_1 + iVar3 * 2), sVar1 == 0x20 ||
          ((sVar1 == 0x2e &&
           (iVar2 = FUN_0802740c(param_1,param_2), iVar3 = extraout_r3, iVar2 == 0))))))) {
    *(undefined2 *)(param_1 + iVar3 * 2) = 0;
    param_2 = iVar3;
  }
  return iVar3 + 1;
}




/* 0x08031660 */
void FUN_08031660(param_1)
undefined4 * param_1;
{
  *param_1 = 0;
  param_1[0x1d3] = 1;
  return;
}




