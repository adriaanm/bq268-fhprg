/* Auto-generated: fhprg_8026f54.c */
/* Functions: 114 */
#include "globals.h"

/* 0x08026f54 */
void FUN_08026f54(param_1, param_2)
uint param_1; uint param_2;
{
  uint uVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  
  if (param_2 < 0x65) {
    dVar4 = 0.0047;
    dVar3 = (double)param_1;
  }
  else if (param_2 < 0x191) {
    dVar4 = 0.0013;
    dVar3 = (double)param_1;
  }
  else {
    if (1000 < param_2) {
      uVar1 = 7;
      iVar2 = 7;
      goto LAB_08026faa;
    }
    dVar4 = 0.0005;
    dVar3 = (double)param_1;
  }
  dVar3 = dVar3 * dVar4 - 2.0;
  uVar1 = (uint)(0.0 < dVar3) * (int)(longlong)dVar3;
  iVar2 = (param_1 / param_2 - uVar1) + -6;
LAB_08026faa:
  *(uint*)DAT_08051a9c = uVar1 | ((uint)(iVar2 * DAT_08051a4c) / 100 & 0xff) << 0x10;
  return;
}




/* 0x08026fe4 */
undefined4 FUN_08026fe4(param_1)
undefined4 param_1;
{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_080270ac();
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  *(uint*)DAT_08051a70 = param_1;
  uVar2 = FUN_080270ac();
  return uVar2;
}




/* 0x08027008 */
void FUN_08027008()
{
  *(uint*)DAT_08051aa4 = DAT_08051a54;
  *(uint*)DAT_08051aa0 = DAT_08051a50;
  return;
}




/* 0x08027020 */
void FUN_08027020(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; undefined4 param_3; undefined4 param_4;
{
  uint *puVar1;
  
  puVar1 = DAT_08051a64;
  *(uint*)DAT_08051a64 = *(uint*)DAT_08051a64 & 0xffffcfff;
  *puVar1 = *puVar1 | param_1;
  *puVar1 = *puVar1 & 0xfffff3ff;
  *puVar1 = *puVar1 | param_2;
  *(uint*)DAT_08051a80 = param_3;
  *(uint*)DAT_08051a88 = param_3;
  *(uint*)DAT_08051a7c = param_4;
  *(uint*)DAT_08051a84 = param_4;
  FUN_08026fe4(0);
  return;
}




/* 0x08027070 */
undefined4 FUN_08027070()
{
  int iVar1;
  
  *(uint*)DAT_08051a68 = 0;
  iVar1 = FUN_08026fe4();
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  *(uint*)DAT_08051a60 = 0x20f;
  *(uint*)DAT_08051a64 = 0xc000;
  FUN_08026f54(&SUB_00004b00,DAT_08051a4a);
  return 0;
}




/* 0x080270ac */
int FUN_080270ac()
{
  int iVar1;
  int iVar2;
  
  iVar2 = 1000;
  do {
    iVar1 = iVar2;
    if (*(uint*)DAT_08051a70 << 0x1d < 0) {
      return 0;
    }
    iVar2 = iVar1 + -1;
  } while (iVar2 != 0);
  return iVar1 + -2;
}




/* 0x080270cc */
int FUN_080270cc()
{
  int iVar1;
  int iVar2;
  
  iVar2 = 500000;
  do {
    iVar1 = iVar2;
    if (*(uint*)DAT_08051a6c << 0x15 < 0) {
      return 0;
    }
    iVar2 = iVar1 + -1;
  } while (iVar2 != 0);
  return iVar1 + -2;
}




/* 0x080270ec */
void thunk_FUN_080270ec()
{
  FUN_08006cd0(&DAT_08054b34,0x80);
  FUN_080382c2(&DAT_08054b34,
               "OEM_IMAGE_UUID_STRING=Q_SENTINEL_{FB715645-0901-433D-A22C-C30D464634AC}_20160824_1109"
               ,0x80);
  return;
}




/* 0x080270ec */
void FUN_080270ec()
{
  FUN_08006cd0(&DAT_08054b34,0x80);
  FUN_080382c2(&DAT_08054b34,
               "OEM_IMAGE_UUID_STRING=Q_SENTINEL_{FB715645-0901-433D-A22C-C30D464634AC}_20160824_1109"
               ,0x80);
  return;
}




/* 0x0802710c */
undefined4 thunk_FUN_0802710c()
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 2;
  iVar1 = FUN_080373b8(0x1d5,0x1000);
  if (iVar1 != 0) {
    FUN_08006d14(iVar1,0x1000);
    uVar2 = 0;
  }
  return uVar2;
}




/* 0x0802710c */
undefined4 FUN_0802710c()
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 2;
  iVar1 = FUN_080373b8(0x1d5,0x1000);
  if (iVar1 != 0) {
    FUN_08006d14(iVar1,0x1000);
    uVar2 = 0;
  }
  return uVar2;
}




/* 0x0802712c */
undefined4 thunk_FUN_0802712c(param_1)
uint param_1;
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  char cStack_90;
  char cStack_8f;
  undefined1 uStack_8e;
  undefined1 auStack_8d [72];
  undefined1 auStack_45 [20];
  undefined1 uStack_31;
  undefined1 auStack_30 [32];
  int iStack_10;
  
  DAT_0804d5f4 = FUN_08037688(0x1d5,&iStack_10);
  if (DAT_0804d5f4 == 0) {
    uVar2 = 3;
  }
  else if (iStack_10 == 0x1000) {
    if (param_1 < 0x20) {
      FUN_08006d14(&cStack_90,0x80);
      iVar3 = FUN_08006860("QC_IMAGE_VERSION_STRING=BOOT.BF.3.1.2-00023",0x3d);
      if (iVar3 == 0) {
        pcVar4 = "QC_IMAGE_VERSION_STRING=BOOT.BF.3.1.2-00023";
      }
      else {
        pcVar4 = (char *)(iVar3 + 1);
      }
      FUN_080382c2(auStack_8d,pcVar4,0x48);
      iVar3 = FUN_08006860("IMAGE_VARIANT_STRING=DAADANAZA",0x3d);
      if (iVar3 == 0) {
        pcVar4 = "IMAGE_VARIANT_STRING=DAADANAZA";
      }
      else {
        pcVar4 = (char *)(iVar3 + 1);
      }
      FUN_080382c2(auStack_45,pcVar4,0x14);
      iVar3 = FUN_08006860("OEM_IMAGE_VERSION_STRING=vBuild1PFW2",0x3d);
      if (iVar3 == 0) {
        pcVar4 = "OEM_IMAGE_VERSION_STRING=vBuild1PFW2";
      }
      else {
        pcVar4 = (char *)(iVar3 + 1);
      }
      FUN_080382c2(auStack_30,pcVar4,0x20);
      cVar1 = (char)(param_1 / 10);
      cStack_8f = (char)param_1 + cVar1 * -10 + '0';
      cStack_90 = cVar1 + (char)((param_1 / 10) / 10) * -10 + '0';
      uStack_8e = 0x3a;
      uStack_31 = 0x3a;
      FUN_08006a30(DAT_0804d5f4 + param_1 * 0x80,&cStack_90,0x80);
      uVar2 = 0;
    }
    else {
      uVar2 = 5;
    }
  }
  else {
    uVar2 = 4;
  }
  return uVar2;
}




/* 0x0802712c */
undefined4 FUN_0802712c(param_1)
uint param_1;
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  char local_90;
  char local_8f;
  undefined1 local_8e;
  undefined1 auStack_8d [72];
  undefined1 auStack_45 [20];
  undefined1 local_31;
  undefined1 auStack_30 [32];
  int local_10;
  
  DAT_0804d5f4 = FUN_08037688(0x1d5,&local_10);
  if (DAT_0804d5f4 == 0) {
    uVar2 = 3;
  }
  else if (local_10 == 0x1000) {
    if (param_1 < 0x20) {
      FUN_08006d14(&local_90,0x80);
      iVar3 = FUN_08006860("QC_IMAGE_VERSION_STRING=BOOT.BF.3.1.2-00023",0x3d);
      if (iVar3 == 0) {
        pcVar4 = "QC_IMAGE_VERSION_STRING=BOOT.BF.3.1.2-00023";
      }
      else {
        pcVar4 = (char *)(iVar3 + 1);
      }
      FUN_080382c2(auStack_8d,pcVar4,0x48);
      iVar3 = FUN_08006860("IMAGE_VARIANT_STRING=DAADANAZA",0x3d);
      if (iVar3 == 0) {
        pcVar4 = "IMAGE_VARIANT_STRING=DAADANAZA";
      }
      else {
        pcVar4 = (char *)(iVar3 + 1);
      }
      FUN_080382c2(auStack_45,pcVar4,0x14);
      iVar3 = FUN_08006860("OEM_IMAGE_VERSION_STRING=vBuild1PFW2",0x3d);
      if (iVar3 == 0) {
        pcVar4 = "OEM_IMAGE_VERSION_STRING=vBuild1PFW2";
      }
      else {
        pcVar4 = (char *)(iVar3 + 1);
      }
      FUN_080382c2(auStack_30,pcVar4,0x20);
      cVar1 = (char)(param_1 / 10);
      local_8f = (char)param_1 + cVar1 * -10 + '0';
      local_90 = cVar1 + (char)((param_1 / 10) / 10) * -10 + '0';
      local_8e = 0x3a;
      local_31 = 0x3a;
      FUN_08006a30(DAT_0804d5f4 + param_1 * 0x80,&local_90,0x80);
      uVar2 = 0;
    }
    else {
      uVar2 = 5;
    }
  }
  else {
    uVar2 = 4;
  }
  return uVar2;
}




/* 0x08027208 */
void FUN_08027208()
{
  int iVar1;
  
  iVar1 = FUN_0800b7ea(0,0x2000145,0x10000,&DAT_0804d440);
  if (iVar1 == 0) {
    FUN_0800badc(DAT_0804d440,"gcc_spmi_ser_clk",&DAT_0804d448);
    FUN_0800badc(DAT_0804d440,"gcc_spmi_ahb_clk",&DAT_0804d444);
  }
  else {
    DAT_0804d440 = 0;
  }
  DAT_0804d43c = 1;
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08027274 */
void FUN_08027274()
{
  DAT_08055fd8 = 0;
  DAT_08055e98 = &DAT_80200000;
  DAT_08054e90 = 0x80000000;
  _DAT_08054e94 = &DAT_80100000;
  DAT_08055f88 = 0;
  DAT_08055f90 = 0;
  DAT_08055f94 = 0;
  DAT_08055f98 = 0;
  DAT_08055fb0 = 0;
  DAT_08055fb4 = 0;
  DAT_08055f99 = 0;
  DAT_08055fa0 = 0;
  DAT_08055fa4 = 0;
  DAT_08055fa8 = 0;
  DAT_08055fac = 0;
  DAT_08055fb8 = 0x100000;
  DAT_08055fbc = 0;
  DAT_08055fc0 = 0;
  DAT_08055fc4 = 0;
  DAT_08055fd0 = 0;
  DAT_08055fd4 = 0;
  DAT_08058428 = 0;
  DAT_0805842c = 0;
  FUN_08039030(&DAT_08055ea0,0,0,0);
  FUN_08039044(&DAT_08055f18,DAT_08055e98,0x1000,0);
  FUN_08027386(&DAT_08058430);
  DAT_08058480 = 0;
  DAT_08058481 = 0;
  DAT_08058482 = 0;
  DAT_08058484 = 0;
  FUN_0801db04();
  return;
}




/* 0x08027314 */
undefined4 FUN_08027314()
{
  FUN_08027328(&DAT_08058430);
  return 0;
}




/* 0x08027320 */
void FUN_08027320()
{
  FUN_0802f4c4(0,1);
  return;
}




/* 0x08027328 */
undefined4 FUN_08027328(param_1)
int param_1;
{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined1 auStack_50 [4];
  int local_4c;
  undefined4 local_44;
  
  iVar3 = 0;
  do {
    uVar1 = FUN_08033fe0((int)*(short *)(param_1 + 0x24),iVar3);
    *(undefined4 *)(param_1 + iVar3 * 4 + 4) = uVar1;
    if (iVar3 == 0) {
      iVar2 = *(int *)(param_1 + 4);
      if (iVar2 == 0) {
        iVar2 = FUN_08033fe0((int)*(short *)(param_1 + 0x24),0);
        *(int *)(param_1 + 4) = iVar2;
        if (iVar2 == 0) {
          return 0;
        }
      }
      iVar2 = FUN_08033ee8(iVar2,auStack_50);
      if (iVar2 != 0) {
        return 0;
      }
      if (local_4c != 0) {
        *(undefined4 *)(param_1 + 0x28) = local_44;
        *(undefined4 *)(param_1 + 0x2c) = 0;
      }
    }
    do {
      iVar3 = iVar3 + 1;
      if (7 < iVar3) {
        FUN_08034202(*(undefined4 *)(param_1 + 4));
        return 1;
      }
    } while (iVar3 == 3);
  } while( true );
}




/* 0x08027386 */
void FUN_08027386(param_1)
undefined1 * param_1;
{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    iVar1 = iVar2 * 4;
    iVar2 = iVar2 + 1;
    *(undefined4 *)(param_1 + iVar1 + 4) = 0;
  } while (iVar2 < 8);
  *param_1 = 0;
  *(undefined2 *)(param_1 + 0x24) = 0;
  param_1[0x26] = 8;
  *(undefined4 *)(param_1 + 0x28) = 0x200;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  return;
}




/* 0x080273aa */
int FUN_080273aa(param_1)
uint param_1;
{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  uVar1 = 2;
  iVar4 = 1;
  iVar2 = 1;
  uVar3 = param_1;
  do {
    uVar3 = uVar3 * 2;
    if ((param_1 & uVar1) != 0) {
      iVar4 = iVar4 + uVar1;
      param_1 = param_1 + uVar3;
    }
    uVar1 = uVar1 << 1;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x20);
  return iVar4;
}




/* 0x080273cc */
undefined4 FUN_080273cc()
{
  undefined4 *puVar1;
  int iVar2;
  int local_8;
  
  local_8 = 1;
  puVar1 = (undefined4 *)(*(int *)(DAT_0804d260 + 0x30) + 0x60);
  if ((puVar1 == (undefined4 *)0x0) || (*(int *)(DAT_0804d260 + 0x30) == -0x50)) {
    firehose_log("Returning FALSE, pbl_secboot_hw_ftbl_ptr == NULL || pbl_secboot_ftbl_ptr == NULL."
                );
  }
  else {
    iVar2 = ((code *)*puVar1)(1,&local_8);
    if ((iVar2 == 0) && (local_8 != 0)) {
      return 1;
    }
  }
  return 0;
}




/* 0x0802740c */
undefined4 FUN_0802740c(param_1, param_2)
int param_1; int param_2;
{
  short sVar1;
  
  param_2 = param_2 + -1;
  if (*(short *)(param_1 + param_2 * 2) != 0x2e) {
    return 0;
  }
  if (param_2 != 0) {
    param_1 = param_1 + param_2 * 2;
    sVar1 = *(short *)(param_1 + -2);
    if ((sVar1 != 0x2f) && (sVar1 != 0x5c)) {
      if (sVar1 != 0x2e) {
        return 0;
      }
      if (((param_2 != 1) && (sVar1 = *(short *)(param_1 + -4), sVar1 != 0x2f)) && (sVar1 != 0x5c))
      {
        return 0;
      }
    }
  }
  return 1;
}




/* 0x08027444 */
undefined4 FUN_08027444(param_1)
uint param_1;
{
  if (0x7f < param_1) {
    return 0;
  }
  if ((((0x19 < param_1 - 0x41) && (0x19 < param_1 - 0x61)) && (9 < param_1 - 0x30)) &&
     (param_1 != 0x2d)) {
    if ((int)param_1 < 0x2e) {
      if (false) {
        return 0;
      }
      switch(param_1) {
      case 0x21:
      case 0x23:
      case 0x24:
      case 0x25:
      case 0x26:
      case 0x27:
      case 0x28:
      case 0x29:
        goto switchD_0802746a_caseD_21;
      default:
        return 0;
      }
    }
    if (param_1 != 0x60) {
      if ((int)param_1 < 0x61) {
        if (((param_1 != 0x40) && (param_1 != 0x5e)) && (param_1 != 0x5f)) {
          return 0;
        }
      }
      else if (((param_1 != 0x7b) && (param_1 != 0x7d)) && (param_1 != 0x7e)) {
        return 0;
      }
    }
  }
switchD_0802746a_caseD_21:
  return 1;
}




/* 0x080274a0 */
undefined4 FUN_080274a0(param_1)
short * param_1;
{
  if ((*param_1 == 0x2e) && ((param_1[1] == 0 || ((param_1[1] == 0x2e && (param_1[2] == 0)))))) {
    return 1;
  }
  return 0;
}




/* 0x080274ba */
undefined4 FUN_080274ba(param_1)
short * param_1;
{
  short sVar1;
  short *psVar2;
  
  do {
    psVar2 = param_1 + 1;
    sVar1 = *param_1;
    if (sVar1 == 0) {
      return 1;
    }
    param_1 = psVar2;
  } while ((sVar1 == 0x20) || (sVar1 == 0x2e));
  return 0;
}




/* 0x0802754c */
undefined4 FUN_0802754c(param_1)
uint param_1;
{
  int iVar1;
  uint *puVar2;
  
  *(uint *)(DAT_0804d44c + 0xa000) = *(uint *)(DAT_0804d44c + 0xa000) & 0xfffffffe;
  FUN_0800e7f0();
  iVar1 = DAT_0804d44c;
  puVar2 = (uint *)(DAT_0804d44c + 0xa000);
  *(uint *)(DAT_0804d44c + 0xa010) = *(uint *)(DAT_0804d44c + 0xa010) | 1;
  *puVar2 = *puVar2 | 1;
  *(uint *)(iVar1 + 0xaf08) = *(uint *)(iVar1 + 0xaf08) | 1;
  *(uint *)(iVar1 + 0xa014) = *(uint *)(iVar1 + 0xa014) | 3;
  *(uint *)(iVar1 + 0xaf00) = *(uint *)(iVar1 + 0xaf00) & 0xfffffffc | param_1 & 3;
  puVar2 = (uint *)(iVar1 + 0xaf04);
  *puVar2 = *puVar2 | 8;
  *puVar2 = *puVar2 | 1;
  *puVar2 = *puVar2 & 0xfffffffd;
  return 0;
}




/* 0x080275c4 */
void FUN_080275c4(param_1, param_2, param_3, param_4)
undefined4 param_1; int param_2; uint param_3; uint param_4;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int extraout_r1;
  int iVar5;
  uint uVar6;
  bool bVar7;
  undefined8 uVar8;
  undefined1 auStack_228 [512];
  int local_28;
  
  iVar1 = DAT_0804cd58;
  local_28 = DAT_0804cd58;
  uVar6 = 0;
  FUN_08006d14(auStack_228,0x200);
  uVar2 = FUN_08006906(param_1);
  uVar3 = uVar2 + param_3 * 2;
  iVar5 = param_4 * 2 + (uint)CARRY4(param_3,param_3) + (uint)CARRY4(uVar2,param_3 * 2) +
          (uint)(0xfffffffe < uVar3);
  bVar7 = uVar3 + 1 < 0x201;
  iVar4 = -(uint)!bVar7 - iVar5;
  if ((uint)-iVar5 < (uint)bVar7) {
    uVar8 = snprintf_buf(auStack_228,0x200,&DAT_08027668,param_1);
    for (; (iVar4 = (int)((ulonglong)uVar8 >> 0x20), uVar2 = (uint)uVar8, uVar2 < 0x200 &&
           (iVar4 = uVar6 - param_3,
           (uint)((int)uVar6 >> 0x1f) <= param_4 &&
           (uint)(param_3 <= uVar6) <= ((int)uVar6 >> 0x1f) - param_4)); uVar6 = uVar6 + 1) {
      uVar8 = snprintf_buf(auStack_228 + uVar2,0x200 - uVar2,&DAT_0802766c,
                           *(undefined1 *)(param_2 + uVar6));
      uVar8 = CONCAT44((int)((ulonglong)uVar8 >> 0x20),uVar2 + (int)uVar8);
    }
    firehose_log(auStack_228,iVar4);
    iVar4 = extraout_r1;
  }
  if (local_28 != iVar1) {
    FUN_08010960(local_28,iVar4);
    return;
  }
  return;
}




/* 0x08027674 */
void firehose_log(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_128 [256];
  int local_28;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  iVar1 = DAT_0804cd58;
  local_28 = DAT_0804cd58;
  uStack_c = param_2;
  uStack_8 = param_3;
  uStack_4 = param_4;
  FUN_08006d14(auStack_128,0x100);
  FUN_08006418(auStack_128,0x100,param_1,&uStack_c);
  uVar2 = FUN_08006906("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>");
  FUN_080391f0(&DAT_08055f18,"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>",uVar2,0);
  FUN_08039100(&DAT_08055f18,&DAT_08027710);
  FUN_080390f4(&DAT_08055f18,&DAT_08027718);
  FUN_0803918c(&DAT_08055f18,"value",auStack_128);
  FUN_080390d8(&DAT_08055f18);
  FUN_080390e4(&DAT_08055f18,&DAT_08027710);
  FUN_080371b8();
  if (local_28 != iVar1) {
    FUN_08010960();
  }
  return;
}




/* 0x08027724 */
undefined4 FUN_08027724()
{
  bool bVar1;
  
  bVar1 = false;
  do {
    do {
      FUN_08030fa8();
    } while (bVar1);
    bVar1 = true;
    firehose_log("logbuf@0x%08X fh@0x%08X",&DAT_08058028,&DAT_08054e90);
  } while( true );
}




/* 0x08027760 */
int FUN_08027760(param_1, param_2, param_3)
int param_1; undefined4 param_2; undefined4 param_3;
{
  int iVar1;
  int iVar2;
  int iVar3;
  int extraout_r3;
  undefined8 uVar4;
  
  uVar4 = FUN_0800d58c(param_1 + 0x1fU,param_1 + 0x1fU & 0xffffffe0,param_3,0);
  iVar2 = DAT_0804d188;
  iVar1 = DAT_0804d178;
  iVar3 = (int)((ulonglong)uVar4 >> 0x20);
  if ((int)uVar4 == 0) {
    if (DAT_0804d178 + iVar3 <= DAT_0804d17c) {
      DAT_0804d178 = DAT_0804d178 + iVar3;
      DAT_0804d180 = DAT_0804d180 - iVar3;
      return iVar1;
    }
  }
  else if (DAT_0804d188 + iVar3 <= DAT_0804d18c) {
    DAT_0804d188 = DAT_0804d188 + iVar3;
    DAT_0804d190 = DAT_0804d190 - iVar3;
    return iVar2;
  }
  return extraout_r3;
}




/* 0x080277a4 */
void FUN_080277a4(param_1, param_2)
uint * param_1; int param_2;
{
  bool bVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint *puVar9;
  uint uVar10;
  uint *puVar11;
  uint uVar12;
  uint uVar13;
  uint *puVar14;
  undefined8 uVar15;
  longlong lVar16;
  longlong lVar17;
  uint local_198 [22];
  undefined1 auStack_140 [32];
  undefined1 local_120 [8];
  uint local_118 [38];
  undefined1 local_80 [8];
  uint local_78;
  uint uStack_74;
  undefined8 local_70;
  int local_68;
  undefined4 local_64;
  uint *local_60;
  uint local_5c;
  uint *local_58;
  int local_54;
  uint *local_50;
  uint local_4c;
  uint local_48;
  uint *local_44;
  uint uStack_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint *puStack_2c;
  int local_28;
  
  local_4c = 0;
  puStack_2c = param_1;
  local_28 = param_2;
  do {
    if (*param_1 <= local_4c) {
      return;
    }
    uVar13 = 0;
    uVar10 = 0;
    uVar12 = 0;
    local_48 = 0;
    local_60 = (uint *)(local_28 + local_4c * 0x78);
    FUN_08006d14(local_120,0xa0);
    FUN_08006d14(local_198,0x78);
    for (uVar8 = 0; uVar8 < param_1[1]; uVar8 = uVar8 + 1) {
      if (local_60[uVar8 * 6 + 2] != 0 || local_60[uVar8 * 6 + 3] != 0) {
        iVar4 = FUN_0801a4a2(local_60[uVar8 * 6 + 2]);
        uVar10 = uVar10 + 1;
        local_48 = iVar4 + local_48;
      }
    }
    lVar16 = local_70;
    if ((param_1[1] < local_48) && (1 < uVar10)) {
      local_54 = 0;
      uVar8 = uVar12;
      for (local_5c = 1; local_5c < param_1[1]; local_5c = local_5c + 1) {
        puVar9 = local_60 + local_5c * 6;
        uVar12 = puVar9[2];
        local_34 = puVar9[3];
        if (uVar12 != 0 || local_34 != 0) {
          local_50 = local_60 + local_54 * 6;
          uVar7 = *local_50;
          puVar2 = (uint *)local_50[1];
          local_58 = puVar2;
          local_38 = local_50[2];
          local_3c = local_50[3];
          uStack_40 = local_38 + uVar7;
          local_44 = (uint *)((int)puVar2 + local_3c + CARRY4(local_38,uVar7));
          uVar10 = *puVar9;
          puVar11 = (uint *)puVar9[1];
          uVar6 = uVar12 + uVar10;
          puVar14 = (uint *)((int)puVar11 + local_34 + CARRY4(uVar12,uVar10));
          if ((((puVar2 <= puVar11 && (uint)(uVar10 <= uVar7) <= (uint)((int)puVar2 - (int)puVar11))
               && (uVar7 != 0 || puVar2 != (uint *)0x0)) &&
              (puVar3 = (uint *)((int)puVar2 + (-(uint)(uVar7 < uVar6) - (int)puVar14)),
              puVar2 <= puVar3 &&
              (uint)(uVar7 - uVar6 <= uVar7) <= (uint)((int)puVar2 - (int)puVar3))) ||
             (((puVar11 <= puVar2 && (uint)(uVar7 <= uVar10) <= (uint)((int)puVar11 - (int)puVar2)
               && (uVar10 != 0 || puVar11 != (uint *)0x0)) &&
              (puVar3 = (uint *)((int)puVar11 + (-(uint)(uVar10 < uStack_40) - (int)local_44)),
              puVar11 <= puVar3 &&
              (uint)(uVar10 - uStack_40 <= uVar10) <= (uint)((int)puVar11 - (int)puVar3)))))
          goto LAB_08027970;
          if (uStack_40 == uVar10 && local_44 == puVar11) {
            local_50[2] = local_38 + uVar12;
            local_50[3] = local_3c + local_34 + CARRY4(local_38,uVar12);
          }
          else {
            if (uVar6 != uVar7 || puVar14 != puVar2) {
              if (puVar11 < puVar2 || (uint)((int)puVar2 - (int)puVar11) < (uint)(uVar10 <= uVar7))
              {
                local_58 = (uint *)(uVar7 - uVar6);
                local_44 = (uint *)((int)puVar2 + (-(uint)(uVar7 < uVar6) - (int)puVar14));
                uVar15 = FUN_08022018(uVar6,puVar14);
                puVar2 = (uint *)((ulonglong)uVar15 >> 0x20);
                if (puVar2 <= local_44 &&
                    (uint)(local_58 <= (uint *)uVar15) <= (uint)((int)puVar2 - (int)local_44))
                goto LAB_08027970;
                local_198[uVar8 * 6] = uVar6;
                local_198[uVar8 * 6 + 1] = (uint)puVar14;
                puVar14 = local_44;
                puVar2 = local_58;
                local_198[uVar8 * 6 + 2] = (uint)local_58;
                local_198[uVar8 * 6 + 3] = (uint)puVar14;
                *local_50 = uVar10;
                local_50[1] = (uint)puVar11;
                uVar12 = puVar9[2] + (int)puVar2;
                iVar4 = (int)puVar14 + puVar9[3] + (uint)CARRY4(puVar9[2],(uint)puVar2);
              }
              else {
                uVar6 = uVar10 - uStack_40;
                uVar10 = (int)puVar11 + (-(uint)(uVar10 < uStack_40) - (int)local_44);
                uVar15 = FUN_08022018(uStack_40,local_44);
                puVar2 = local_44;
                uVar12 = (uint)((ulonglong)uVar15 >> 0x20);
                if (uVar12 <= uVar10 && (uint)(uVar6 <= (uint)uVar15) <= uVar12 - uVar10) {
LAB_08027970:
                  local_54 = local_54 + 1;
                  goto LAB_080279c2;
                }
                local_198[uVar8 * 6] = uStack_40;
                local_198[uVar8 * 6 + 1] = (uint)puVar2;
                local_198[uVar8 * 6 + 2] = uVar6;
                local_198[uVar8 * 6 + 3] = uVar10;
                uVar12 = puVar9[2] + uVar6;
                iVar4 = puVar9[3] + uVar10 + (uint)CARRY4(puVar9[2],uVar6);
              }
              uVar8 = uVar8 + 1;
              uVar10 = local_50[2];
              local_50[2] = uVar12 + uVar10;
              local_50[3] = iVar4 + local_50[3] + (uint)CARRY4(uVar12,uVar10);
              *puVar9 = 0;
              puVar9[1] = 0;
              puVar9[2] = 0;
              puVar9[3] = 0;
              goto LAB_080279c2;
            }
            *local_50 = uVar10;
            local_50[1] = (uint)puVar11;
            uVar12 = puVar9[2];
            uVar10 = puVar9[3];
            local_50[2] = local_38 + uVar12;
            local_50[3] = local_3c + uVar10 + CARRY4(local_38,uVar12);
          }
          *puVar9 = 0;
          puVar9[1] = 0;
          puVar9[2] = 0;
          puVar9[3] = 0;
        }
LAB_080279c2:
      }
      uVar12 = uVar8;
      lVar16 = local_70;
      if (local_54 == 0) {
        local_48 = FUN_0801a4a2(local_60[2],local_60[3]);
        lVar16 = local_70;
        if (param_1[1] - uVar8 < local_48) {
          uVar7 = *local_60;
          uVar6 = local_60[1];
          uVar12 = local_60[2];
          uVar10 = local_60[3];
          local_198[uVar8 * 6] = uVar7 + uVar12;
          local_198[uVar8 * 6 + 1] = uVar6 + uVar10 + (uint)CARRY4(uVar7,uVar12);
          iVar4 = FUN_0801a490();
          lVar16 = FUN_080063f0(1,0,0x40 - iVar4);
          uVar12 = uVar8 + 1;
          *(longlong *)(local_60 + 2) = lVar16;
          lVar16 = (lVar16 + *(longlong *)local_60) -
                   CONCAT44(local_198[uVar8 * 6 + 1],local_198[uVar8 * 6]);
          local_198[uVar8 * 6 + 2] = (uint)lVar16;
          local_198[uVar8 * 6 + 3] = (uint)((ulonglong)lVar16 >> 0x20);
          lVar16 = local_70;
        }
      }
    }
    for (local_5c = 0; local_70 = lVar16, local_5c < param_1[1]; local_5c = local_5c + 1) {
      local_58 = local_60 + local_5c * 6;
      uVar8 = local_58[2];
      uVar10 = local_58[3];
      lVar17 = *(longlong *)(local_58 + 2);
      if (uVar8 != 0 || uVar10 != 0) {
        uVar6 = *local_58;
        uVar7 = local_58[1];
        local_80[0] = 1;
        local_68 = 0;
        if ((char)local_58[4] == '\0') {
          local_64 = 0;
        }
        else if ((local_4c & 1) == 0) {
          local_64 = 2;
        }
        else {
          local_64 = 1;
        }
        uVar5 = FUN_0801a4a2(uVar8,uVar10);
        if ((uVar5 < 2) || (local_48 <= param_1[1] - uVar12)) {
          bVar1 = false;
        }
        else {
          bVar1 = true;
        }
        lVar16 = local_70;
        if (bVar1) {
          iVar4 = FUN_0801a490(uVar8,uVar10);
          lVar17 = FUN_080063f0(1,0,0x40 - iVar4);
          lVar16 = local_70;
        }
        while( true ) {
          iVar4 = (int)((ulonglong)lVar17 >> 0x20);
          uVar8 = (uint)lVar17;
          if ((lVar17 == 0) || (param_1[1] <= uVar13)) break;
          local_78 = uVar6;
          uStack_74 = uVar7;
          local_70 = lVar17;
          if (!bVar1) {
            local_70 = lVar16;
            lVar16 = FUN_08022018(uVar6,uVar7,uVar8,iVar4);
            local_70 = lVar16;
          }
          FUN_08006bdc(local_120 + uVar13 * 0x20,local_80,0x20);
          if (bVar1) {
            if (local_68 == 0) {
              uVar8 = local_58[2];
              iVar4 = local_58[3] + (uint)CARRY4(uVar6,uVar8);
              lVar17 = local_70 - *(longlong *)(local_58 + 2);
            }
            else {
              iVar4 = iVar4 + (uint)CARRY4(uVar6,uVar8);
              lVar17 = lVar17 - local_70;
            }
            local_68 = 1;
            local_64 = 0;
          }
          else {
            iVar4 = _GHIDRA_FIELD(local_70, 4, uint) + (uint)CARRY4(uVar6,(uint)local_70);
            lVar17 = lVar17 - local_70;
            uVar8 = (uint)local_70;
          }
          uVar7 = uVar7 + iVar4;
          uVar6 = uVar6 + uVar8;
          uVar13 = uVar13 + 1;
          lVar16 = local_70;
          if ((lVar17 != 0) && (param_1[1] == uVar13)) {
            *(undefined1 *)(param_1 + 7) = 1;
          }
        }
      }
    }
    uVar8 = 0;
    for (; (uVar8 < uVar12 && (uVar13 < param_1[1])); uVar13 = uVar13 + 1) {
      local_120[uVar13 * 0x20] = 1;
      uVar10 = local_198[uVar8 * 6 + 1];
      local_118[uVar13 * 8] = local_198[uVar8 * 6];
      local_118[uVar13 * 8 + 1] = uVar10;
      uVar10 = local_198[uVar8 * 6 + 3];
      local_118[uVar13 * 8 + 2] = local_198[uVar8 * 6 + 2];
      uVar8 = uVar8 + 1;
      local_118[uVar13 * 8 + 3] = uVar10;
      local_118[uVar13 * 8 + 4] = 1;
      local_118[uVar13 * 8 + 5] = 0;
    }
    for (uVar12 = param_1[1]; uVar12 != 0; uVar12 = uVar12 - 1) {
      thunk_FUN_00221cfc(param_1[4],*(undefined4 *)(param_1[5] + local_4c * 4),uVar12 - 1,param_1[6]
                        );
    }
    for (uVar12 = param_1[1]; uVar12 != 0; uVar12 = uVar12 - 1) {
      thunk_FUN_00221cfc(param_1[4],*(undefined4 *)(param_1[5] + local_4c * 4),uVar12 - 1,
                         auStack_140 + uVar12 * 0x20);
    }
    local_4c = local_4c + 1;
  } while( true );
}




/* 0x08027bf8 */
uint thunk_FUN_08027bf8(param_1, param_2, param_3, param_4)
undefined4 param_1; uint param_2; undefined4 param_3; uint param_4;
{
  if (param_2 <= param_4) {
    param_4 = param_2;
  }
  FUN_08006a30(param_1,param_3,param_4);
  return param_4;
}




/* 0x08027bf8 */
uint FUN_08027bf8(param_1, param_2, param_3, param_4)
undefined4 param_1; uint param_2; undefined4 param_3; uint param_4;
{
  if (param_2 <= param_4) {
    param_4 = param_2;
  }
  FUN_08006a30(param_1,param_3,param_4);
  return param_4;
}




/* 0x08027c12 */
uint FUN_08027c12(param_1, param_2, param_3, param_4)
undefined4 param_1; uint param_2; undefined4 param_3; uint param_4;
{
  if (param_2 <= param_4) {
    param_4 = param_2;
  }
  FUN_08006b04(param_1,param_3,param_4);
  return param_4;
}




/* 0x08027c2c */
void FUN_08027c2c(param_1, param_2)
int param_1; uint * param_2;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar1 = param_2[1] >> 0x14;
  uVar4 = uVar1 + (param_2[2] + 0x3ff >> 10);
  uVar2 = *param_2 & 0xfff00000;
  for (; uVar1 < uVar4; uVar1 = uVar1 + 1) {
    uVar3 = param_2[4] | param_2[5] | param_2[7] | uVar2 | param_2[6];
    *(uint *)(param_1 + uVar1 * 4) = uVar3 | 2;
    if (param_2[3] == 1) {
      *(uint *)(param_1 + uVar1 * 4) = uVar3 | 0x80002;
    }
    uVar2 = uVar2 + 0x100000;
  }
  return;
}




/* 0x08027c78 */
void FUN_08027c78(param_1, param_2)
int param_1; uint * param_2;
{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  bVar1 = true;
  uVar3 = param_2[1] >> 0x14;
  uVar5 = *(uint *)(param_1 + uVar3 * 4);
  if ((uVar5 & 1) == 0) {
    if (DAT_0804cd24 == 0) {
      return;
    }
    uVar5 = param_2[7] | DAT_0804cd20 & 0xfffffc00 | 1;
    *(uint *)(param_1 + uVar3 * 4) = uVar5;
    if (param_2[3] == 3) {
      *(uint *)(param_1 + uVar3 * 4) = uVar5 | 8;
    }
    bVar1 = false;
    DAT_0804cd24 = DAT_0804cd24 + -1;
    uVar3 = DAT_0804cd20;
    DAT_0804cd20 = DAT_0804cd20 + 0x400;
  }
  else {
    uVar3 = uVar5 & 0xfffffc00;
  }
  uVar4 = *param_2 & 0xfff00000;
  uVar6 = (param_2[1] << 0xc) >> 0x18;
  uVar5 = param_2[2];
  uVar2 = 0;
  do {
    if ((uVar2 < uVar6) || (uVar6 + (uVar5 + 3 >> 2) <= uVar2)) {
      if (!bVar1) {
        uVar7 = uVar4 | 0x37;
        goto LAB_08027cf8;
      }
    }
    else {
      uVar7 = param_2[4] | param_2[5] | param_2[6] | uVar4 | 2;
LAB_08027cf8:
      *(uint *)(uVar3 + uVar2 * 4) = uVar7;
    }
    uVar2 = uVar2 + 1;
    uVar4 = uVar4 + 0x1000;
    if (0xff < uVar2) {
      return;
    }
  } while( true );
}




/* 0x08027d0c */
uint FUN_08027d0c(param_1, param_2, param_3, param_4, param_5, param_6, param_7)
undefined4 * param_1; undefined4 param_2; int param_3; int * param_4; uint param_5; uint param_6; int * param_7;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int local_48;
  undefined4 *local_44;
  int local_40;
  int local_3c;
  int local_38;
  undefined4 *local_34;
  undefined4 uStack_30;
  int local_2c;
  int *local_28;
  
  if ((((param_5 < 2) ||
       (local_34 = param_1, uStack_30 = param_2, local_2c = param_3, local_28 = param_4,
       iVar1 = FUN_08019d98(param_2,param_4,param_5), -1 < iVar1)) ||
      ((uint)local_28[param_5 - 1] >> 0x1e == 0)) ||
     (uVar2 = FUN_0801d9e0(local_2c,param_6), uVar2 == 0xfffffffe)) {
LAB_08027d88:
    uVar2 = 0xffffffff;
  }
  else {
    local_38 = param_5 << 2;
    if (uVar2 == 0xffffffff) {
      FUN_08006d14(local_34,local_38);
      *local_34 = 1;
    }
    else {
      if (uVar2 != 0) {
        local_48 = 0;
        uVar9 = uVar2 & 0xfffffffe;
        local_44 = local_34;
        local_40 = param_7[2];
        local_3c = 0;
        iVar1 = FUN_080273aa(*local_28);
        iVar1 = -iVar1;
        if (*local_28 * iVar1 == -1) {
          uVar3 = FUN_08028046(local_44,param_2,local_28,param_5);
          uVar4 = FUN_08027f7c(local_40,local_44,local_44,local_28,param_5,iVar1);
          uVar4 = uVar4 | uVar3;
          uVar3 = 0;
          do {
            if (param_6 <= uVar3) {
LAB_08027e00:
              uVar2 = *(uint *)(local_2c +
                               ((int)(uVar9 + ((uint)((int)uVar2 >> 0x1f) >> 0x1b)) >> 5) * 4) >>
                      (uVar2 & 0x1e) & 3;
              if (uVar2 == 1) {
                iVar8 = 1;
                iVar7 = local_40;
              }
              else {
                iVar8 = 2;
                iVar7 = (&local_48)[uVar2];
              }
              while (uVar9 = uVar9 - 2, -1 < (int)uVar9) {
                uVar2 = *(uint *)(local_2c +
                                 ((int)(uVar9 + ((uint)((int)uVar9 >> 0x1f) >> 0x1b)) >> 5) * 4) >>
                        (uVar9 & 0x1f) & 3;
                for (; 0 < iVar8; iVar8 = iVar8 + -1) {
                  iVar5 = *param_7;
                  if (iVar5 == iVar7) {
                    iVar5 = param_7[1];
                  }
                  uVar3 = FUN_08027f7c(iVar5,iVar7,iVar7,local_28,param_5,iVar1);
                  uVar4 = uVar4 | uVar3;
                  iVar7 = iVar5;
                }
                iVar5 = iVar7;
                if (uVar2 != 0) {
                  iVar5 = *param_7;
                  if (iVar5 == iVar7) {
                    iVar5 = param_7[1];
                  }
                  uVar2 = FUN_08027f7c(iVar5,(&local_48)[uVar2],iVar7,local_28,param_5,iVar1);
                  uVar4 = uVar4 | uVar2;
                }
                iVar8 = 2;
                iVar7 = iVar5;
              }
              uVar2 = FUN_08027efa(local_34,iVar7,local_28,param_5,iVar1);
              if ((uVar2 | uVar4) == 0) {
                return 0;
              }
              FUN_08006d14(local_34,local_38);
              return uVar2 | uVar4;
            }
            uVar6 = *(uint *)(local_2c + uVar3 * 4);
            if ((uVar6 & (uVar6 & 0x55555555) << 1) != 0) {
              local_3c = param_7[3];
              uVar3 = FUN_08027f7c(local_3c,local_40,local_44,local_28,param_5,iVar1);
              uVar4 = uVar4 | uVar3;
              goto LAB_08027e00;
            }
            uVar3 = uVar3 + 1;
          } while( true );
        }
        goto LAB_08027d88;
      }
      FUN_08006bdc(local_34,param_2);
    }
    uVar2 = 0;
  }
  return uVar2;
}




/* 0x08027ec2 */
void FUN_08027ec2(param_1, param_2)
ushort * param_1; uint param_2;
{
  *param_1 = 0x124;
  if ((param_2 & 1) == 0) {
    *param_1 = 0x1b6;
  }
  if ((int)(param_2 << 0x1b) < 0) {
    *param_1 = *param_1 | 0x4000;
  }
  if ((param_2 & 0x18) == 0) {
    *param_1 = *param_1 | 0x8000;
  }
  if ((int)(param_2 << 0x1e) < 0) {
    *param_1 = *param_1 | 0x200;
  }
  return;
}




/* 0x08027efa */
undefined4 FUN_08027efa(param_1, param_2, param_3, param_4, param_5)
uint * param_1; undefined4 param_2; uint * param_3; uint param_4; int param_5;
{
  longlong lVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  
  FUN_08006bdc(param_1,param_2,param_4 << 2);
  for (uVar7 = 0; uVar7 < param_4; uVar7 = uVar7 + 1) {
    uVar6 = *param_1 * param_5;
    uVar4 = (uint)((ulonglong)uVar6 * (ulonglong)*param_3 + (ulonglong)*param_1 >> 0x20);
    for (uVar2 = 1; uVar2 < param_4; uVar2 = uVar2 + 1) {
      lVar1 = (ulonglong)uVar6 * (ulonglong)param_3[uVar2] +
              (ulonglong)CONCAT14(CARRY4(param_1[uVar2],uVar4),param_1[uVar2] + uVar4);
      uVar4 = (uint)((ulonglong)lVar1 >> 0x20);
      param_1[uVar2 - 1] = (uint)lVar1;
    }
    param_1[uVar2 - 1] = uVar4;
  }
  uVar5 = 0;
  iVar3 = FUN_08019d98(param_1,param_3,param_4);
  if (-1 < iVar3) {
    uVar5 = FUN_08038338(param_1,param_3,param_4);
  }
  return uVar5;
}




/* 0x08027f7c */
undefined4 FUN_08027f7c(param_1, param_2, param_3, param_4, param_5, param_6)
uint * param_1; int param_2; uint * param_3; uint * param_4; uint param_5; int param_6;
{
  ulonglong uVar1;
  longlong lVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint local_38;
  
  FUN_08006d14(param_1,param_5 << 2);
  local_38 = 0;
  for (uVar5 = 0; uVar5 < param_5; uVar5 = uVar5 + 1) {
    uVar10 = *(uint *)(param_2 + uVar5 * 4);
    uVar1 = (ulonglong)uVar10 * (ulonglong)*param_3 + (ulonglong)*param_1;
    uVar7 = (uint)(uVar1 >> 0x20);
    uVar9 = (int)uVar1 * param_6;
    uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)*param_4 + (uVar1 & 0xffffffff) >> 0x20);
    for (uVar6 = 1; uVar6 < param_5; uVar6 = uVar6 + 1) {
      lVar2 = (ulonglong)uVar10 * (ulonglong)param_3[uVar6] +
              (ulonglong)CONCAT14(CARRY4(param_1[uVar6],uVar7),param_1[uVar6] + uVar7);
      uVar11 = (uint)lVar2;
      uVar7 = (uint)((ulonglong)lVar2 >> 0x20);
      lVar2 = (ulonglong)uVar9 * (ulonglong)param_4[uVar6] +
              (ulonglong)CONCAT14(CARRY4(uVar8,uVar11),uVar8 + uVar11);
      uVar8 = (uint)((ulonglong)lVar2 >> 0x20);
      param_1[uVar6 - 1] = (uint)lVar2;
    }
    uVar9 = uVar7 + uVar8 + local_38;
    local_38 = (uint)CARRY4(uVar7,uVar8) + (uint)CARRY4(uVar7 + uVar8,local_38);
    param_1[uVar6 - 1] = uVar9;
  }
  uVar4 = 0;
  if (local_38 != 0) {
    iVar3 = FUN_08038338(param_1,param_4);
    uVar4 = 0;
    if (iVar3 + local_38 != 0) {
      uVar4 = 0xffffffff;
    }
  }
  return uVar4;
}




/* 0x08028046 */
uint FUN_08028046(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; int param_3; uint param_4;
{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  uint local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_30;
  uint local_2c [2];
  
  FUN_08006bdc(param_1,param_2,param_4 << 2);
  iVar7 = param_3 + param_4 * 4;
  uVar6 = 0xffffffff;
  piVar8 = (int *)(iVar7 + -8);
  uVar4 = *(uint *)(iVar7 + -4);
  if (0x3fffffff < uVar4) {
    if ((uVar4 == 0x40000000) && (*piVar8 == 0)) {
      local_2c[0] = 0xffffffff;
      local_30 = 0xffffffff;
      uVar6 = 0;
    }
    else {
      local_38 = 0;
      uStack_34 = 0x40000000;
      local_40 = 0;
      local_3c = 0;
      uVar4 = FUN_0801be1c(&local_30,&local_3c,piVar8);
      uVar6 = FUN_0801be1c(local_2c,&local_40,piVar8);
      uVar6 = uVar6 | uVar4;
    }
  }
  uVar4 = local_2c[0];
  uVar1 = local_30;
  for (uVar5 = 0; uVar5 < param_4; uVar5 = uVar5 + 1) {
    local_40 = uVar4;
    local_3c = uVar1;
    uVar2 = FUN_08022178(param_1,param_3,param_4);
    local_40 = param_4;
    uVar3 = FUN_080280e2(param_1,param_3,param_1,uVar2);
    uVar6 = uVar6 | uVar3;
  }
  return uVar6;
}




/* 0x080280e2 */
undefined4 FUN_080280e2(param_1, param_2, param_3, param_4, param_5)
int param_1; uint * param_2; int param_3; uint param_4; uint param_5;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  iVar2 = (int)((ulonglong)param_4 * (ulonglong)*param_2);
  uVar4 = (uint)((ulonglong)param_4 * (ulonglong)*param_2 >> 0x20);
  iVar1 = -iVar2;
  uVar3 = -(uint)(iVar2 != 0);
  uVar5 = uVar3 - uVar4;
  iVar2 = ((int)uVar3 >> 0x1f) - (uint)(uVar3 < uVar4);
  for (uVar3 = 1; uVar3 < param_5; uVar3 = uVar3 + 1) {
    uVar6 = *(uint *)(param_3 + uVar3 * 4 + -4);
    uVar7 = (uint)((ulonglong)param_4 * (ulonglong)param_2[uVar3]);
    uVar8 = (uint)((ulonglong)param_4 * (ulonglong)param_2[uVar3] >> 0x20);
    uVar4 = uVar6 + uVar5;
    *(int *)(param_1 + uVar3 * 4 + -4) = iVar1;
    iVar1 = uVar4 - uVar7;
    uVar4 = (iVar2 + (uint)CARRY4(uVar6,uVar5)) - (uint)(uVar4 < uVar7);
    uVar5 = uVar4 - uVar8;
    iVar2 = ((int)uVar4 >> 0x1f) - (uint)(uVar4 < uVar8);
  }
  iVar2 = *(int *)(param_3 + uVar3 * 4 + -4) + uVar5;
  *(int *)(param_1 + uVar3 * 4 + -4) = iVar1;
  if (iVar2 != 0) {
    uVar3 = 0;
    if (iVar2 < 1) {
      do {
        iVar1 = FUN_0801352e(param_1,param_2,param_5);
        uVar3 = uVar3 + 1;
        iVar2 = iVar2 + iVar1;
        if (0xf < uVar3) {
          return 0xffffffff;
        }
      } while (iVar2 != 0);
    }
    else {
      do {
        iVar1 = FUN_08038338(param_1,param_2,param_5);
        uVar3 = uVar3 + 1;
        iVar2 = iVar2 + iVar1;
        if (0xf < uVar3) {
          return 0xffffffff;
        }
      } while (iVar2 != 0);
    }
    if (0xf < uVar3) {
      return 0xffffffff;
    }
  }
  while (iVar1 = FUN_08019d98(param_1,param_2,param_5), -1 < iVar1) {
    FUN_08038338(param_1,param_2,param_5);
  }
  return 0;
}




/* 0x080282ac */
undefined4 FUN_080282ac(param_1)
int param_1;
{
  int *piVar1;
  
  piVar1 = (int *)FUN_080219d8();
  if (piVar1 != (int *)0x0) {
    *piVar1 = param_1;
    piVar1[5] = (int)&PTR_LAB_08038a78_1_0803b274;
    *(undefined2 *)(piVar1 + 3) = 0x41ed;
    *(undefined2 *)(piVar1 + 1) = *(undefined2 *)(param_1 + 4);
    *(int **)(param_1 + 0xc) = piVar1;
    return 0;
  }
  return 0xfffffbfc;
}




/* 0x08028314 */
int FUN_08028314(param_1)
int param_1;
{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0xc);
  iVar2 = -2;
  piVar1 = (int *)FUN_0801deb8(9);
  *(undefined ***)(iVar3 + 0xbc) = &PTR_LAB_080283aa_1_08051514;
  if ((piVar1 != (int *)0xffffffff) && (*piVar1 != 0)) {
    while ((piVar1 != (int *)0x0 &&
           (((code *)*piVar1 != (code *)0x0 && (iVar2 = ((code *)*piVar1)(param_1), iVar2 != 0)))))
    {
      piVar1 = piVar1 + 1;
    }
  }
  return iVar2;
}




/* 0x0802838e */
undefined4 FUN_0802838e(param_1)
int param_1;
{
  undefined4 uVar1;
  int iVar2;
  code *pcVar3;
  
  uVar1 = 0xffffffff;
  iVar2 = *(int *)(*(int *)(param_1 + 0xc) + 0xc0);
  *(int *)(param_1 + 0x90) = iVar2;
  pcVar3 = *(code **)(iVar2 + 0xc);
  if (pcVar3 != (code *)0x0) {
    uVar1 = (*pcVar3)();
  }
  return uVar1;
}




/* 0x08028408 */
undefined4 FUN_08028408(param_1, param_2)
int param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0xc);
  if ((*(int *)(iVar3 + 0x58) == 0) && (iVar1 = FUN_0800b61e(4,iVar3 + 0x58), iVar1 != 0)) {
    return 0xffffffff;
  }
  DAT_08051aac = &LAB_08028404;
  DAT_08051ab0 = &LAB_080284f8;
  DAT_08051ab4 = &DAT_0802861f;
  *(undefined **)(iVar3 + 0xc0) = &DAT_08051aa8;
  **(undefined4 **)(*(int *)(param_1 + 0xc) + 0x58) = param_2;
  uVar2 = FUN_08028460(param_1,param_2);
  **(undefined4 **)(*(int *)(param_1 + 0xc) + 0x58) = param_2;
  return uVar2;
}




/* 0x08028460 */
undefined4 FUN_08028460(param_1, param_2)
int param_1; undefined4 * param_2;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = *(int *)(param_1 + 0xc);
  *(undefined **)(iVar1 + 0xc0) = &DAT_08051aa8;
  *(undefined4 **)(iVar1 + 0x44) = param_2 + 5;
  *(undefined4 *)(iVar1 + 0x48) = param_2[1];
  *(undefined4 *)(iVar1 + 0x4c) = param_2[2];
  *(undefined4 *)(iVar1 + 0x50) = param_2[3];
  *(undefined4 *)(iVar1 + 0x54) = param_2[4];
  FUN_0801e17c(iVar1 + 0x60,param_2 + 5,0x20);
  *(undefined4 *)(iVar1 + 0x80) = param_2[0xd];
  *(undefined4 *)(iVar1 + 0x84) = param_2[0xe];
  *(undefined4 *)(iVar1 + 0x88) = param_2[0xf];
  *(undefined4 *)(iVar1 + 0x8c) = param_2[0x10];
  *(undefined4 *)(iVar1 + 0x90) = param_2[0x11];
  *(undefined4 *)(iVar1 + 0x5c) = *param_2;
  *(undefined4 *)(iVar1 + 0x94) = param_2[0x12];
  *(undefined4 *)(iVar1 + 0x98) = param_2[0x13];
  *(undefined4 *)(iVar1 + 0x9c) = param_2[0x14];
  *(undefined4 *)(iVar1 + 0xa0) = param_2[0x15];
  *(undefined4 *)(iVar1 + 0xa4) = param_2[0x16];
  *(undefined4 *)(iVar1 + 0xa8) = param_2[0x17];
  *(undefined4 *)(iVar1 + 0xac) = param_2[0x18];
  *(undefined4 *)(iVar1 + 0xb0) = param_2[0x19];
  for (uVar2 = *(uint *)(iVar1 + 0x9c); (uVar2 & 1) == 0; uVar2 = uVar2 >> 1) {
    *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x44) + 1;
  }
  for (uVar2 = *(uint *)(iVar1 + 0x98); (uVar2 & 1) == 0; uVar2 = uVar2 >> 1) {
    *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + 1;
  }
  iVar1 = *(int *)(param_1 + 0xc);
  uVar2 = *(uint *)(iVar1 + 0x98);
  uVar3 = *(uint *)(iVar1 + 0x9c);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(iVar1 + 0x94);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(iVar1 + 0x98);
  *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(iVar1 + 0x9c);
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(iVar1 + 0x9c);
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(iVar1 + 0xb0);
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(iVar1 + 0x94);
  *(undefined4 *)(param_1 + 0x74) = 0;
  *(undefined4 *)(param_1 + 0x78) = 0;
  *(undefined4 *)(param_1 + 0x7c) = *(undefined4 *)(iVar1 + 0x94);
  *(undefined4 *)(param_1 + 0x80) = *(undefined4 *)(iVar1 + 0x94);
  *(int *)(param_1 + 0x84) = *(int *)(iVar1 + 0x98) * *(int *)(iVar1 + 0x9c);
  for (; (uVar2 & 1) == 0; uVar2 = uVar2 >> 1) {
    *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + 1;
  }
  *(undefined4 *)(param_1 + 0x44) = 0;
  for (; (uVar3 & 1) == 0; uVar3 = uVar3 >> 1) {
    *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x44) + 1;
  }
  *(undefined **)(iVar1 + 0xc0) = &DAT_08051aa8;
  *(undefined **)(param_1 + 0x90) = &DAT_08051aa8;
  return 0;
}




/* 0x08028502 */
undefined4 FUN_08028502(param_1, param_2, param_3)
int * param_1; int param_2; undefined4 * param_3;
{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (*param_1 == 0) {
    uVar1 = 0xffffffff;
  }
  else if (param_2 == 0) {
    FUN_0801e17c(param_3 + 4,*(undefined4 *)(param_1[3] + 0x44),0x20);
    *param_3 = *(undefined4 *)(param_1[3] + 0x48);
    param_3[1] = *(undefined4 *)(param_1[3] + 0x4c);
    param_3[2] = *(undefined4 *)(param_1[3] + 0x50);
    param_3[0xf] = *(undefined4 *)(param_1[3] + 0x94);
    param_3[3] = *(undefined4 *)(param_1[3] + 0x54);
    param_3[0xc] = *(undefined4 *)(param_1[3] + 0x84);
    param_3[0xd] = *(undefined4 *)(param_1[3] + 0x88);
    param_3[0xe] = *(undefined4 *)(param_1[3] + 0x8c);
    param_3[0x11] = param_1[9];
    param_3[0x12] = param_1[10];
    param_3[0x13] = param_1[0xb];
    param_3[0x14] = param_1[0xc];
    param_3[0x16] = param_1[0x1e];
  }
  else if (param_2 == 2) {
    *param_3 = 1;
    param_3[1] = *(undefined4 *)(param_1[3] + 0x94);
    param_3[2] = param_1[0xb] * param_1[10];
  }
  return uVar1;
}




/* 0x08028608 */
void FUN_08028608(param_1)
int param_1;
{
  if (*(int *)(*(int *)(param_1 + 0xc) + 0x58) != 0) {
    FUN_0800b574();
  }
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x58) = 0;
  return;
}




/* 0x080287e2 */
void FUN_080287e2(param_1, param_2, param_3)
undefined1 * param_1; undefined1 param_2; uint param_3;
{
  uint uVar1;
  
  for (uVar1 = 0; uVar1 < param_3; uVar1 = uVar1 + 1) {
    *param_1 = param_2;
    param_1 = param_1 + 1;
  }
  return;
}




/* 0x08028810 */
void FUN_08028810(param_1, param_2)
uint param_1; int param_2;
{
  bool bVar1;
  
  FUN_0801b6bc("cback %d err %d",param_1,param_2);
  DAT_08055f88 = param_2;
  if (param_2 == 0) {
    bVar1 = 0xfffffffe < DAT_08055fc8;
    DAT_08055fc8 = DAT_08055fc8 + 1;
    DAT_08055fcc = DAT_08055fcc + (uint)bVar1;
    DAT_08055f90 = param_1;
  }
  else {
    DAT_08055f90 = 0;
    bVar1 = 0xfffffffe < DAT_08055fc0;
    DAT_08055fc0 = DAT_08055fc0 + 1;
    DAT_08055fc4 = DAT_08055fc4 + (uint)bVar1;
  }
  DAT_08055f94 = 0;
  bVar1 = CARRY4(DAT_08055fb0,param_1);
  DAT_08055fb0 = DAT_08055fb0 + param_1;
  DAT_08055fb4 = DAT_08055fb4 + (uint)bVar1;
  DAT_08055f98 = 1;
  return;
}




/* 0x080288b0 */
undefined4 FUN_080288b0(param_1, param_2)
int param_1; uint * param_2;
{
  byte bVar1;
  longlong lVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  bool bVar19;
  undefined8 uVar20;
  uint auStack_258 [80];
  uint local_118 [16];
  undefined4 auStack_d8 [16];
  int local_98;
  int local_94;
  uint local_90;
  int local_8c;
  int local_88;
  int local_84;
  uint local_80;
  int local_7c;
  int local_78;
  char local_74 [4];
  undefined4 local_70;
  byte local_6c [16];
  byte local_5c [16];
  undefined1 auStack_4c [16];
  undefined4 local_3c;
  undefined4 uStack_38;
  int local_34;
  int local_30;
  int local_2c;
  uint *local_28;
  
  local_28 = param_2;
  local_2c = param_1;
  local_7c = DAT_0804cd58;
  local_34 = DAT_0804cd58;
  uVar15 = 0;
  uVar17 = 0;
  iVar13 = 0;
  local_94 = 0;
  local_90 = 0;
  local_84 = 0;
  local_80 = 0;
  local_88 = 0;
  local_98 = 0;
  local_8c = 0;
  uVar7 = 0;
  do {
    bVar1 = *(byte *)(local_2c + local_90);
    uVar11 = (uint)bVar1;
    if (local_8c == 0) {
      piVar3 = (int *)FUN_080060b0();
      if (*(char *)(*piVar3 + uVar11) == ' ') {
        local_84 = local_94;
        local_80 = local_90;
        local_8c = 1;
        goto LAB_08028a5c;
      }
      if (uVar11 != 0x28) {
        if (uVar11 == 0x29) {
          while (uVar7 != 0 || iVar13 != 0) {
            uVar9 = uVar7 - 1;
            iVar13 = iVar13 + -1 + (uint)(uVar7 != 0);
            uVar11 = (uint)local_6c[uVar7 - 1];
            if (uVar11 == 0x28) goto LAB_08028a5e;
            uVar17 = uVar17 + (0xfffffffe < uVar15);
            local_5c[uVar15] = local_6c[uVar7 - 1];
            uVar7 = uVar9;
            uVar15 = uVar15 + 1;
          }
        }
        else {
          uVar9 = uVar7;
          if ((((uVar11 == 0x2b) || (uVar11 == 0x2d)) || (uVar11 == 0x2a)) || (uVar11 == 0x2f)) {
            while (uVar9 != 0 || iVar13 != 0) {
              local_70 = iVar13 + -1 + (uint)(uVar9 != 0);
              local_78 = DAT_0804cd58;
              local_30 = DAT_0804cd58;
              local_3c = 0x2f2a2b2d;
              uStack_38 = 0;
              uVar7 = FUN_08006860(&local_3c,local_6c[uVar9 - 1]);
              uVar4 = FUN_08006860(&local_3c,uVar11);
              if (((uVar7 == 0) || (uVar4 == 0)) || (uVar7 <= uVar4)) {
                bVar19 = false;
              }
              else {
                bVar19 = true;
              }
              if (local_30 != local_78) {
                FUN_08010960();
              }
              if (!bVar19) break;
              uVar17 = uVar17 + (0xfffffffe < uVar15);
              local_5c[uVar15] = local_6c[uVar9 - 1];
              uVar9 = uVar9 - 1;
              iVar13 = local_70;
              uVar15 = uVar15 + 1;
            }
            uVar7 = uVar9 + 1;
            iVar13 = iVar13 + (uint)(0xfffffffe < uVar9);
            local_6c[uVar9] = bVar1;
          }
        }
        goto LAB_08028a5c;
      }
      uVar9 = uVar7 + 1;
      iVar13 = iVar13 + (uint)(0xfffffffe < uVar7);
      local_6c[uVar7] = bVar1;
    }
    else {
      if ((local_8c == 1) && (piVar3 = (int *)FUN_080060b0(), *(char *)(*piVar3 + uVar11) != ' ')) {
        uVar9 = local_90 - 1;
        local_8c = 0;
        iVar5 = local_94 + -1 + (uint)(local_90 != 0);
        bVar19 = local_90 < local_80;
        uVar4 = local_90 - local_80;
        iVar14 = local_94 - local_84;
        local_94 = iVar5;
        local_90 = uVar9;
        if ((uint)(uVar4 < 0x10) <= -(iVar14 - (uint)bVar19)) goto LAB_08028b06;
        FUN_08027bf8(auStack_4c,0x10,local_2c + local_80,uVar4);
        auStack_4c[uVar4] = 0;
        uVar20 = FUN_0803823e(auStack_4c,local_74);
        iVar14 = local_88;
        if (local_74[0] == '\0') goto LAB_08028b06;
        uVar17 = uVar17 + (0xfffffffe < uVar15);
        local_5c[uVar15] = (char)local_88 + 0x30;
        local_88 = local_88 + 1;
        auStack_d8[iVar14 * 2] = (int)uVar20;
        auStack_d8[iVar14 * 2 + 1] = (int)((ulonglong)uVar20 >> 0x20);
        uVar15 = uVar15 + 1;
      }
LAB_08028a5c:
      uVar9 = uVar7;
      if (uVar11 == 0) break;
    }
LAB_08028a5e:
    local_94 = local_94 + (uint)(0xfffffffe < local_90);
    local_90 = local_90 + 1;
    uVar7 = uVar9;
  } while( true );
  for (; uVar7 != 0 || iVar13 != 0; uVar7 = uVar7 - 1) {
    iVar13 = iVar13 + -1 + (uint)(uVar7 != 0);
    uVar17 = uVar17 + (0xfffffffe < uVar15);
    local_5c[uVar15] = local_6c[uVar7 - 1];
    uVar15 = uVar15 + 1;
  }
  uVar7 = 0;
  uVar11 = 0;
  uVar9 = 0;
  do {
    if (uVar17 < uVar11 || uVar11 - uVar17 < (uint)(uVar15 <= uVar7)) {
      if ((local_28 == (uint *)0x0) || (uVar9 == 0 && local_98 == 0)) {
LAB_08028b06:
        uVar8 = 0;
      }
      else {
        uVar8 = 1;
        uVar7 = local_118[(uVar9 - 1) * 2 + 1];
        *local_28 = local_118[(uVar9 - 1) * 2];
        local_28[1] = uVar7;
      }
      if (local_34 != local_7c) {
        FUN_08010960();
      }
      return uVar8;
    }
    uVar4 = (uint)local_5c[uVar7];
    if (uVar4 == 0x2a) {
      uVar16 = uVar9 - 1;
      uVar18 = uVar9 - 2;
      uVar4 = local_118[uVar16 * 2];
      uVar10 = local_118[uVar16 * 2 + 1];
      uVar6 = local_118[uVar18 * 2];
      uVar12 = local_118[uVar18 * 2 + 1];
      lVar2 = (ulonglong)uVar6 * (ulonglong)uVar4;
      local_98 = local_98 + (uint)(uVar9 != 0) + -2 + (uint)(uVar16 != 0) +
                 (uint)(0xfffffffe < uVar18);
      local_118[uVar18 * 2] = (uint)lVar2;
      local_118[uVar18 * 2 + 1] = uVar6 * uVar10 + uVar12 * uVar4 + (int)((ulonglong)lVar2 >> 0x20);
    }
    else {
      if (uVar4 == 0x2b) {
        iVar13 = uVar9 - 1;
        iVar14 = local_98 + (uint)(uVar9 != 0) + -2 + (uint)(iVar13 != 0);
        uVar6 = local_118[(uVar9 - 2) * 2] + local_118[iVar13 * 2];
        uVar4 = local_118[(uVar9 - 2) * 2 + 1] + local_118[iVar13 * 2 + 1] +
                (uint)CARRY4(local_118[(uVar9 - 2) * 2],local_118[iVar13 * 2]);
      }
      else {
        if (uVar4 != 0x2d) {
          if (uVar4 == 0x2f) {
            uVar16 = uVar9 - 1;
            iVar13 = local_98 + (uint)(uVar9 != 0);
            uVar9 = uVar9 - 2;
            uVar20 = FUN_080060c0(local_118[uVar9 * 2],local_118[uVar9 * 2 + 1],
                                  local_118[uVar16 * 2],local_118[uVar16 * 2 + 1]);
            local_98 = iVar13 + -2 + (uint)(uVar16 != 0) + (uint)(0xfffffffe < uVar9);
            local_118[uVar9 * 2] = (uint)uVar20;
            local_118[uVar9 * 2 + 1] = (uint)((ulonglong)uVar20 >> 0x20);
          }
          else {
            uVar6 = auStack_258[uVar4 * 2 + 1];
            uVar16 = uVar9 + 1;
            local_98 = local_98 + (uint)(0xfffffffe < uVar9);
            local_118[uVar9 * 2] = auStack_258[uVar4 * 2];
            local_118[uVar9 * 2 + 1] = uVar6;
          }
          goto LAB_08028ace;
        }
        iVar13 = uVar9 - 1;
        iVar14 = local_98 + (uint)(uVar9 != 0) + -2 + (uint)(iVar13 != 0);
        uVar6 = local_118[(uVar9 - 2) * 2] - local_118[iVar13 * 2];
        uVar4 = (local_118[(uVar9 - 2) * 2 + 1] - local_118[iVar13 * 2 + 1]) -
                (uint)(local_118[(uVar9 - 2) * 2] < local_118[iVar13 * 2]);
      }
      uVar10 = uVar9 - 2;
      uVar16 = uVar9 - 1;
      local_98 = iVar14 + (uint)(0xfffffffe < uVar10);
      local_118[uVar10 * 2] = uVar6;
      local_118[uVar10 * 2 + 1] = uVar4;
    }
LAB_08028ace:
    bVar19 = 0xfffffffe < uVar7;
    uVar7 = uVar7 + 1;
    uVar11 = uVar11 + bVar19;
    uVar9 = uVar16;
  } while( true );
}




/* 0x08028c10 */
undefined4 FUN_08028c10(param_1)
undefined4 param_1;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  bool bVar6;
  undefined8 uVar7;
  uint *in_stack_00000000;
  undefined1 auStack_220 [512];
  int local_20;
  
  iVar1 = DAT_0804cd58;
  local_20 = DAT_0804cd58;
  FUN_08006d14(auStack_220,0x200);
  FUN_0803725c(param_1,&DAT_08028ca4,&DAT_08028ca0);
  iVar2 = FUN_08006874(param_1,"NUM_DISK_SECTORS");
  if (iVar2 != 0) {
    FUN_08037f64(&DAT_08058430);
    snprintf_buf(auStack_220,0x200,&DAT_08028cc0);
    FUN_0803725c(param_1,"NUM_DISK_SECTORS",auStack_220);
  }
  iVar2 = FUN_080288b0(param_1,in_stack_00000000);
  if (iVar2 != 0) {
    uVar7 = FUN_08037f64(&DAT_08058430);
    uVar3 = (uint)((ulonglong)uVar7 >> 0x20);
    uVar4 = in_stack_00000000[1];
    bVar6 = *in_stack_00000000 <= (uint)uVar7;
    if (uVar4 < uVar3 || uVar3 - uVar4 < (uint)bVar6) {
      uVar5 = 1;
      goto LAB_08028c88;
    }
    firehose_log("Parsed value exceeds size of partition in sectors",(uVar3 - uVar4) - (uint)!bVar6)
    ;
  }
  uVar5 = 0;
LAB_08028c88:
  if (local_20 != iVar1) {
    FUN_08010960();
  }
  return uVar5;
}




/* 0x08028cfc */
int FUN_08028cfc(param_1)
uint * param_1;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  if (((((((((param_1 != (uint *)0x0) && (uVar4 = *param_1, 0x7bb < uVar4)) && (uVar4 < 0x834)) &&
          ((uVar2 = param_1[1], uVar2 != 0 && (uVar2 < 0xd)))) &&
         ((uVar3 = param_1[2], uVar3 != 0 && ((uVar3 < 0x20 && (param_1[3] < 0x18)))))) &&
        (param_1[4] < 0x3c)) &&
       ((param_1[5] < 0x3c && (((uVar4 != 0x7bc || (uVar2 != 1)) || (5 < uVar3)))))) &&
      ((uVar3 < 0x1f || (((uVar2 != 4 && (uVar2 != 6)) && ((uVar2 != 9 && (uVar2 != 0xb)))))))) &&
     (((uVar1 = (uint)((uVar4 & 3) == 0), uVar2 != 2 || (uVar3 <= uVar1 + 0x1c)) &&
      (iVar5 = (uVar4 - 0x7bc) * 0x16d +
               ((int)((uVar4 - 0x7b9) + ((uint)((int)(uVar4 - 0x7b9) >> 0x1f) >> 0x1e)) >> 2), true)
      ))) {
    switch(uVar2) {
    default:
      goto switchD_08028d92_caseD_0;
    case 1:
      break;
    case 2:
      iVar5 = iVar5 + 0x1f;
      break;
    case 3:
      iVar5 = iVar5 + 0x3b;
      break;
    case 4:
      iVar5 = iVar5 + 0x5a;
      break;
    case 5:
      iVar5 = iVar5 + 0x78;
      break;
    case 6:
      iVar5 = iVar5 + 0x97;
      break;
    case 7:
      iVar5 = iVar5 + 0xb5;
      break;
    case 8:
      iVar5 = iVar5 + 0xd4;
      break;
    case 9:
      iVar5 = iVar5 + 0xf3;
      break;
    case 10:
      iVar5 = iVar5 + 0x111;
      break;
    case 0xb:
      iVar5 = iVar5 + 0x130;
      break;
    case 0xc:
      iVar5 = iVar5 + 0x14e;
    }
    if ((uVar1 != 0) && (2 < uVar2)) {
      iVar5 = iVar5 + 1;
    }
    return param_1[5] + (param_1[4] + (param_1[3] + (uVar3 + iVar5 + -6) * 0x18) * 0x3c) * 0x3c;
  }
switchD_08028d92_caseD_0:
  return 0;
}




/* 0x08028e00 */
undefined4 FUN_08028e00(param_1, param_2)
int * param_1; int * param_2;
{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((param_2 == (int *)0x0) || (param_1 == (int *)0x0)) {
    uVar1 = 4;
  }
  else if ((param_2[2] != 0) || (*param_2 != *param_1)) {
    return 3;
  }
  return uVar1;
}




/* 0x08028e1e */
undefined4 FUN_08028e1e(param_1, param_2)
int * param_1; int * param_2;
{
  undefined4 uVar1;
  byte *pbVar2;
  uint uVar3;
  int iVar4;
  
  uVar1 = 0;
  if ((param_1 == (int *)0x0) || (param_2 == (int *)0x0)) {
    uVar1 = 4;
  }
  else {
    iVar4 = param_1[2];
    if ((((iVar4 == 0) || (pbVar2 = (byte *)*param_1, pbVar2 == (byte *)0x0)) ||
        (pbVar2 + iVar4 < pbVar2)) ||
       ((((byte *)param_1[1] < pbVar2 + iVar4 || (uVar3 = (uint)*pbVar2, 7 < uVar3)) ||
        ((iVar4 == 1 && (uVar3 != 0)))))) {
      uVar1 = 3;
    }
    else {
      param_2[2] = uVar3;
      *param_2 = *param_1 + 1;
      param_2[1] = param_1[2] + -1;
    }
  }
  return uVar1;
}




/* 0x08028e62 */
undefined4 FUN_08028e62(param_1, param_2)
undefined4 * param_1; int param_2;
{
  char *pcVar1;
  
  if ((param_1 == (undefined4 *)0x0) || (param_2 == 0)) {
    return 4;
  }
  if ((((param_1[2] == 1) && (pcVar1 = (char *)*param_1, pcVar1 != (char *)0x0)) &&
      (pcVar1 <= pcVar1 + 1)) && (pcVar1 + 1 <= (char *)param_1[1])) {
    *(bool *)param_2 = *pcVar1 != '\0';
    return 0;
  }
  return 3;
}




/* 0x08028e98 */
undefined4 FUN_08028e98(param_1, param_2, param_3)
int * param_1; byte * param_2; uint * param_3;
{
  byte *pbVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = 0;
  if (((param_1 == (int *)0x0) || (*param_1 == 0)) || (param_3 == (uint *)0x0)) {
    return 4;
  }
  *param_3 = 0;
  pbVar1 = (byte *)*param_1;
  if ((pbVar1 <= pbVar1 + 1) && (pbVar1 + 1 <= param_2)) {
    uVar3 = (uint)*pbVar1;
    if ((int)(uVar3 << 0x18) < 0) {
      uVar3 = uVar3 & 0x7f;
      if (uVar3 == 0x7f) {
        return 3;
      }
      pbVar2 = pbVar1 + 1;
      if ((*pbVar1 & 0x7f) == 0) {
        return 3;
      }
      do {
        if (pbVar2 + 1 < pbVar2) {
          return 3;
        }
        if (param_2 < pbVar2 + 1) {
          return 3;
        }
        uVar4 = (uint)*pbVar2 + uVar4 * 0x100;
        if (0xffff < uVar4) {
          return 3;
        }
        pbVar2 = pbVar2 + 1;
        uVar3 = uVar3 - 1;
      } while (uVar3 != 0);
      if (false) {
        return 0;
      }
    }
    else {
      pbVar2 = pbVar1 + 1;
      uVar4 = uVar3;
    }
    if ((pbVar2 <= pbVar2 + uVar4) && (pbVar2 + uVar4 <= param_2)) {
      *param_1 = (int)pbVar2;
      *param_3 = uVar4;
      return 0;
    }
  }
  return 3;
}




/* 0x08028f10 */
undefined4 FUN_08028f10(param_1, param_2, param_3)
undefined4 * param_1; byte * param_2; uint * param_3;
{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  
  if ((((param_1 == (undefined4 *)0x0) || (pbVar3 = (byte *)*param_1, pbVar3 == (byte *)0x0)) ||
      (param_3 == (uint *)0x0)) || ((pbVar3 + 1 < pbVar3 || (param_2 < pbVar3 + 1)))) {
    return 3;
  }
  bVar1 = *pbVar3;
  uVar2 = (uint)bVar1;
  *param_3 = 0;
  if ((~uVar2 & 0x1f) == 0) {
    return 3;
  }
  if ((bVar1 & 0xc0) == 0) {
    uVar2 = uVar2 & 0x1f;
  }
  else if ((uVar2 & 0xc0) != 0x80) goto LAB_08028f50;
  *param_3 = uVar2;
LAB_08028f50:
  *param_1 = pbVar3 + 1;
  return 0;
}




/* 0x08028f54 */
undefined4 FUN_08028f54(param_1, param_2, param_3)
undefined4 * param_1; undefined4 * param_2; int param_3;
{
  undefined4 uVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  if ((param_1 == (undefined4 *)0x0) || (param_2 == (undefined4 *)0x0)) {
    return 4;
  }
  pbVar3 = (byte *)*param_1;
  iVar2 = param_1[2];
  if ((pbVar3 <= pbVar3 + iVar2) && (pbVar3 + iVar2 <= (byte *)param_1[1])) {
    if (param_3 == 0) {
      if (iVar2 != 0xf) {
        return 3;
      }
      pbVar4 = pbVar3 + 4;
      local_28 = (uint)pbVar3[2] * 10 + (uint)pbVar3[1] * 100 + (short)(*pbVar3 - 0x30) * 1000 +
                 (uint)pbVar3[3] + -0x14d0;
    }
    else {
      if (iVar2 != 0xd) {
        return 3;
      }
      pbVar4 = pbVar3 + 2;
      local_28 = (*pbVar3 - 0x30) * 10 + (uint)pbVar3[1];
      if (local_28 - 0x30U < 0x32) {
        local_28 = local_28 + 0x7a0;
      }
      else {
        local_28 = local_28 + 0x73c;
      }
    }
    local_24 = (*pbVar4 - 0x30) * 10 + (uint)pbVar4[1] + -0x30;
    local_20 = (pbVar4[2] - 0x30) * 10 + (uint)pbVar4[3] + -0x30;
    local_1c = (pbVar4[4] - 0x30) * 10 + (uint)pbVar4[5] + -0x30;
    local_18 = (pbVar4[6] - 0x30) * 10 + (uint)pbVar4[7] + -0x30;
    local_14 = (pbVar4[8] - 0x30) * 10 + (uint)pbVar4[9] + -0x30;
    if (pbVar4[10] == 0x5a) {
      uVar1 = FUN_08028cfc(&local_28);
      *param_2 = uVar1;
      return 0;
    }
  }
  return 3;
}




/* 0x08029074 */
undefined4 FUN_08029074(param_1)
uint * param_1;
{
  if (param_1 == (uint *)0x0) {
    return 4;
  }
  if ((param_1[2] == 0) && (*param_1 <= param_1[1])) {
    return 0;
  }
  return 3;
}




/* 0x08029092 */
int FUN_08029092(param_1, param_2, param_3, param_4)
uint * param_1; uint * param_2; int param_3; int param_4;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int local_24;
  
  if (((param_2 != (uint *)0x0) && (param_1 != (uint *)0x0)) &&
     (uVar4 = param_1[2], uVar4 < 0x10000)) {
    uVar3 = *param_1;
    if ((uVar3 <= uVar3 + uVar4) && (uVar2 = param_1[1], uVar3 + uVar4 <= uVar2)) {
      if (uVar4 == 0) {
        return 2;
      }
      local_24 = param_4;
      iVar1 = FUN_08028f10(param_1,uVar2,&local_24);
      if (iVar1 == 0) {
        if ((param_3 != 0) && (param_3 != local_24)) {
          param_1[2] = uVar4;
          *param_1 = uVar3;
          param_1[1] = uVar2;
          return 1;
        }
        iVar1 = FUN_08028e98(param_1,param_1[1],param_2 + 2);
        if (iVar1 == 0) {
          *param_2 = *param_1;
          uVar4 = param_2[2] + *param_1;
          if ((*param_1 <= uVar4) && (uVar4 <= param_1[1])) {
            *param_1 = uVar4;
            param_1[2] = param_1[2] - (uVar4 - uVar3);
            uVar4 = *param_2 + param_2[2];
            if (uVar4 <= uVar2) {
              uVar2 = uVar4;
            }
            param_2[1] = uVar2;
            if (((((param_1[2] < 0x10000) && (uVar3 = param_1[2] + *param_1, *param_1 <= uVar3)) &&
                 (uVar3 <= param_1[1])) && ((param_2[2] < 0x10000 && (*param_2 <= uVar4)))) &&
               (uVar4 <= uVar2)) {
              return 0;
            }
          }
          return 3;
        }
      }
      param_1[2] = uVar4;
      *param_1 = uVar3;
      param_1[1] = uVar2;
      return iVar1;
    }
  }
  return 4;
}




/* 0x08029160 */
int FUN_08029160(param_1, param_2, param_3)
uint param_1; uint param_2; uint * param_3;
{
  int iVar1;
  uint uVar2;
  int local_1c;
  uint local_18;
  uint uStack_14;
  uint *puStack_10;
  
  iVar1 = 4;
  if ((((param_1 != 0) && (param_3 != (uint *)0x0)) && (param_1 <= param_2)) &&
     (local_18 = param_1, uStack_14 = param_2, puStack_10 = param_3,
     iVar1 = FUN_08028f10(&local_18,param_2,&local_1c), iVar1 == 0)) {
    if (local_1c == 0x10) {
      iVar1 = FUN_08028e98(&local_18,param_2,param_3 + 2);
      if (iVar1 == 0) {
        if (param_3[2] < 0x10000) {
          *param_3 = local_18;
          param_3[1] = param_2;
          uVar2 = param_3[2] + local_18;
          if ((local_18 <= uVar2) && (uVar2 <= param_2)) {
            return 0;
          }
        }
        iVar1 = 3;
      }
    }
    else {
      iVar1 = 1;
    }
  }
  return iVar1;
}




/* 0x080291c0 */
undefined4 FUN_080291c0(param_1, param_2)
int param_1; int * param_2;
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  if (((param_1 == 0) || (param_2 == (int *)0x0)) || (*(int *)(param_1 + 0x378) == 0)) {
    uVar3 = 3;
  }
  else {
    for (uVar2 = 0; uVar2 < *(uint *)(param_1 + 0x378); uVar2 = uVar2 + 1) {
      if (((*param_2 != 0) &&
          (((param_2[2] == uVar2 &&
            (iVar1 = FUN_080292de(param_1 + uVar2 * 0x128,*param_2,uVar2), iVar1 == 0)) ||
           ((uVar2 != 0 &&
            ((iVar1 = *(int *)(param_1 + uVar2 * 0x128 + 0xd4), iVar1 != -1 &&
             (iVar1 + 1 < (int)uVar2)))))))) ||
         ((uVar2 + 1 < *(uint *)(param_1 + 0x378) &&
          (iVar1 = FUN_0802924e(param_1 + uVar2 * 0x128 + 0x128), iVar1 != 0)))) {
        return 3;
      }
    }
  }
  return uVar3;
}




/* 0x0802924e */
int FUN_0802924e(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  
  if ((param_1 == 0) || (param_2 == 0)) {
LAB_0802929e:
    iVar1 = 1;
  }
  else {
    iVar1 = FUN_08029348(param_1 + 0x5c,param_2 + 0x2c);
    if (iVar1 != 0) {
      return iVar1;
    }
    if (*(char *)(param_2 + 0x88) == '\0') goto LAB_080292c6;
    if ((*(int *)(param_2 + 0x94) != 0) && (*(char *)(param_1 + 0xb4) != '\0')) {
      if (*(int *)(param_2 + 0x94) != *(int *)(param_1 + 0xc0)) goto LAB_0802929e;
      iVar1 = FUN_08006898(*(undefined4 *)(param_2 + 0x8c),*(undefined4 *)(param_1 + 0xb8));
      if (iVar1 != 0) {
        return iVar1;
      }
    }
    if (*(int *)(param_2 + 0xb0) != 0) {
      if (*(int *)(param_2 + 0xb0) != *(int *)(param_1 + 0x18)) goto LAB_0802929e;
      iVar1 = FUN_08006898(*(undefined4 *)(param_2 + 0xa8),*(undefined4 *)(param_1 + 0x10));
      if (iVar1 != 0) {
        return iVar1;
      }
    }
    if ((*(int *)(param_2 + 0x98) == 0) ||
       (iVar1 = FUN_08029348(param_1 + 0x2c,param_2 + 0x98), iVar1 == 0)) {
LAB_080292c6:
      if ((*(char *)(param_1 + 200) != '\0') && (-1 < *(int *)(param_1 + 0xc4) << 0x1c)) {
        return -1;
      }
      return 0;
    }
  }
  return iVar1;
}




/* 0x080292de */
bool FUN_080292de(param_1, param_2)
int param_1; uint param_2;
{
  bool bVar1;
  
  bVar1 = false;
  if (param_1 != 0) {
    if ((param_2 == 0xffffffff) || (*(char *)(param_1 + 0x84) == '\0')) {
      return true;
    }
    bVar1 = (*(uint *)(param_1 + 0xc4) & param_2) != 0;
  }
  return bVar1;
}




/* 0x08029300 */
undefined8 FUN_08029300(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; uint * param_3; int param_4;
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint local_20;
  uint *puStack_1c;
  int local_18;
  
  uVar3 = 0;
  if (((param_3 == (uint *)0x0) || (param_1 == 0)) || (param_2 < param_1)) {
    return CONCAT44(param_2,8);
  }
  local_20 = param_2;
  puStack_1c = param_3;
  local_18 = param_4;
  iVar1 = FUN_08029160(param_1,param_2,&local_20);
  if (((iVar1 == 0) && (uVar2 = local_20 - param_1, uVar2 < 0x10000)) && (uVar2 != 0)) {
    uVar2 = uVar2 + local_18;
    *param_3 = uVar2;
    if (((uVar2 < 0x10000) && (param_1 <= uVar2 + param_1)) && (uVar2 + param_1 <= param_2))
    goto LAB_08029344;
  }
  uVar3 = 3;
LAB_08029344:
  return CONCAT44(local_20,uVar3);
}




/* 0x08029348 */
int FUN_08029348(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  
  if ((param_1 != 0) && (param_2 != 0)) {
    if (*(int *)(param_2 + 0xc) != *(int *)(param_1 + 0xc)) {
      return *(int *)(param_2 + 0xc) - *(int *)(param_1 + 0xc);
    }
    iVar1 = FUN_08006898(*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_1 + 4));
    return iVar1;
  }
  return 1;
}




/* 0x08029366 */
undefined4 FUN_08029366(param_1, param_2, param_3)
undefined4 param_1; undefined1 * param_2; int param_3;
{
  int iVar1;
  uint uVar2;
  undefined1 auStack_28 [12];
  undefined1 auStack_1c [12];
  
  if ((param_3 == 0) && (param_2 != (undefined1 *)0x0)) {
    *param_2 = 1;
    iVar1 = FUN_08029092(param_1,auStack_28,0x10);
    if ((iVar1 == 0) && (uVar2 = FUN_08029092(auStack_28,param_2 + 4,0x80), uVar2 < 3)) {
      uVar2 = FUN_08029092(auStack_28,auStack_1c,0xa1);
      if (uVar2 == 0) {
        iVar1 = FUN_08029cf8(auStack_1c,param_2 + 0x10);
        if (iVar1 != 0) {
          return 3;
        }
      }
      else if (2 < uVar2) {
        return 3;
      }
      uVar2 = FUN_08029092(auStack_28,param_2 + 0x20,0x82);
      if ((uVar2 < 3) && (iVar1 = FUN_08028e00(param_1,auStack_28), iVar1 == 0)) {
        return 0;
      }
    }
  }
  return 3;
}




/* 0x080293d4 */
undefined4 FUN_080293d4(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  undefined1 auStack_38 [8];
  int local_30;
  byte *local_2c [2];
  int local_24;
  undefined1 local_20 [4];
  
  if ((param_1 == 0) || (param_2 == 0)) {
    return 8;
  }
  iVar1 = FUN_08029092(param_1,auStack_38,0x10);
  if (iVar1 != 0) {
    return 3;
  }
  if (local_30 == 0) {
    *(undefined1 *)(param_2 + 0x54) = 1;
    *(undefined1 *)(param_2 + 0x55) = 0;
    *(undefined4 *)(param_2 + 0x50) = 0xffffffff;
  }
  else {
    iVar1 = FUN_08029092(auStack_38,local_2c,1);
    if (iVar1 == 0) {
      iVar1 = FUN_08028e62(local_2c,local_20);
      if (iVar1 != 0) {
        return 3;
      }
    }
    else {
      if (iVar1 != 1) {
        return 3;
      }
      local_20[0] = 0;
    }
    *(undefined1 *)(param_2 + 0x54) = 1;
    *(undefined1 *)(param_2 + 0x55) = local_20[0];
    iVar1 = FUN_08029092(auStack_38,local_2c,2);
    if (iVar1 == 0) {
      if (local_24 != 1) {
        return 3;
      }
      *(uint *)(param_2 + 0x50) = (uint)*local_2c[0];
    }
    else {
      if ((iVar1 != 1) && (iVar1 != 2)) {
        return 3;
      }
      *(undefined4 *)(param_2 + 0x50) = 0xffffffff;
    }
  }
  iVar1 = FUN_08028e00(param_1,auStack_38);
  if (iVar1 != 0) {
    return 3;
  }
  return 0;
}




/* 0x0802947c */
int FUN_0802947c(param_1, param_2, param_3, param_4, param_5, param_6, param_7)
char * param_1; uint param_2; int param_3; int param_4; int param_5; uint param_6; uint param_7;
{
  int iVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  uint local_38;
  char *local_34;
  uint uStack_30;
  int iStack_2c;
  int iStack_28;
  
  uVar4 = 0;
  local_38 = 0;
  if ((((param_1 == (char *)0x0) || (param_3 == 0)) || (param_2 == 0)) || (param_4 == 0)) {
    return 8;
  }
  pcVar5 = param_1 + param_2;
  if (pcVar5 < param_1) {
    return 1;
  }
  local_34 = param_1;
  uStack_30 = param_2;
  iStack_2c = param_3;
  iStack_28 = param_4;
  if (param_5 == 0) {
    if (0x2fffd < param_2) {
      return 1;
    }
LAB_080294da:
    *(undefined4 *)(param_3 + 0x378) = 0;
    do {
      if (((param_5 == 1) && (local_38 - param_7 == uVar4)) &&
         (iVar1 = FUN_0802a10e(&local_34,pcVar5,param_6 & 0xff), iVar1 != 0)) {
        return iVar1;
      }
      iVar3 = param_3 + *(int *)(param_3 + 0x378) * 0x128;
      iVar1 = FUN_080295a0(local_34,pcVar5,iVar3,param_4);
      if (iVar1 != 0) {
        return iVar1;
      }
      pcVar2 = local_34 + *(int *)(iVar3 + 0xe4);
      if (pcVar2 < local_34) {
        return 1;
      }
      if (pcVar5 < pcVar2) {
        return 1;
      }
      *(int *)(param_3 + 0x378) = *(int *)(param_3 + 0x378) + 1;
      local_34 = pcVar2;
      if ((*(int *)(iVar3 + 0x38) == *(int *)(iVar3 + 0x68)) &&
         (iVar1 = FUN_08006898(*(undefined4 *)(iVar3 + 0x30),*(undefined4 *)(iVar3 + 0x60)),
         iVar1 == 0)) break;
      uVar4 = uVar4 + 1;
      param_4 = 0;
    } while (uVar4 < 3);
    if (*(int *)(param_3 + 0x378) == 1) {
      return 1;
    }
    iVar1 = 0;
    if (param_5 == 1) {
      uVar4 = (param_7 - param_6) - 1;
      if (param_7 <= uVar4) goto LAB_08029572;
      iVar1 = FUN_0802a10e(&local_34,pcVar5,uVar4 & 0xff);
      if (iVar1 != 0) {
        return iVar1;
      }
    }
    for (; local_34 < pcVar5; local_34 = local_34 + 1) {
      if (*local_34 != -1) {
        iVar1 = 1;
      }
    }
  }
  else {
    iVar1 = FUN_080355a4(param_1,param_2,&local_38);
    if (iVar1 != 0) {
      return iVar1;
    }
    if ((param_7 < local_38) && (param_7 < 0x11)) goto LAB_080294da;
LAB_08029572:
    iVar1 = 3;
  }
  return iVar1;
}




/* 0x080295a0 */
undefined4 FUN_080295a0(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; int * param_3; undefined4 param_4;
{
  int iVar1;
  uint uVar2;
  undefined1 auStack_30 [12];
  uint local_24 [2];
  uint local_1c;
  
  if (((param_3 == (int *)0x0) || (param_1 == 0)) || (param_2 < param_1)) {
    return 8;
  }
  iVar1 = FUN_08029160(param_1,param_2,local_24);
  if (iVar1 == 0) {
    uVar2 = local_24[0] - param_1;
    param_3[0x37] = uVar2;
    if (uVar2 < 0x10000) {
      uVar2 = uVar2 + local_1c;
      param_3[0x39] = uVar2;
      if (((((local_1c <= uVar2) && (uVar2 < 0x10000)) &&
           ((iVar1 = FUN_08029092(local_24,auStack_30,0x10), iVar1 == 0 &&
            ((iVar1 = FUN_0802a0cc(auStack_30,param_3), iVar1 == 0 &&
             (iVar1 = FUN_08029092(auStack_30,param_3 + 4,2), iVar1 == 0)))))) &&
          (iVar1 = FUN_08029ee4(auStack_30,param_3 + 7), iVar1 == 0)) &&
         ((((iVar1 = FUN_080296e4(auStack_30,param_3 + 0xb,0), iVar1 == 0 &&
            (iVar1 = FUN_0802a030(auStack_30,param_3), iVar1 == 0)) &&
           (iVar1 = FUN_080296e4(auStack_30,param_3 + 0x17,param_4), iVar1 == 0)) &&
          (iVar1 = FUN_08029d98(auStack_30,param_3 + 0x3a), iVar1 == 0)))) {
        if (param_3[0x3a] != 0) {
          return 9;
        }
        *(undefined1 *)(param_3 + 0x21) = 0;
        param_3[0x35] = -1;
        if (((*param_3 == 0) ||
            (((iVar1 = FUN_0802a00e(auStack_30,param_3 + 0x1b,0x81), iVar1 == 0 &&
              (iVar1 = FUN_0802a00e(auStack_30,param_3 + 0x1e,0x82), iVar1 == 0)) &&
             ((*param_3 != 2 || (iVar1 = FUN_08029af8(auStack_30,param_3,0xa3), iVar1 == 0)))))) &&
           ((iVar1 = FUN_08028e00(local_24,auStack_30), iVar1 == 0 && (param_1 <= local_24[0])))) {
          if (((uint)param_3[0x37] <= local_24[0] - param_1) &&
             ((uVar2 = (local_24[0] - param_1) - param_3[0x37], param_3[0x38] = uVar2,
              uVar2 < 0x10000 && (iVar1 = FUN_08029f98(local_24,param_3), iVar1 == 0)))) {
            if (3 < (uint)param_3[7]) {
              return 9;
            }
            iVar1 = FUN_08029074(local_24);
            if (iVar1 == 0) {
              return 0;
            }
          }
        }
      }
    }
  }
  return 3;
}




/* 0x080296e4 */
int FUN_080296e4(param_1, param_2, param_3)
int param_1; int * param_2; longlong * param_3;
{
  byte bVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  bool bVar10;
  longlong lVar11;
  int local_88 [2];
  uint local_80;
  int local_7c;
  int local_78;
  undefined1 auStack_74 [12];
  undefined1 auStack_68 [12];
  int local_5c;
  int local_58;
  undefined1 auStack_54 [12];
  byte local_48 [16];
  int local_38;
  int local_30;
  int *local_2c;
  longlong *plStack_28;
  
  local_7c = DAT_0804cd58;
  local_38 = DAT_0804cd58;
  local_5c = 0;
  local_78 = 0;
  local_30 = param_1;
  local_2c = param_2;
  plStack_28 = param_3;
  if ((param_1 == 0) || (param_2 == (int *)0x0)) {
    iVar4 = 8;
  }
  else {
    if (param_3 != (longlong *)0x0) {
      *(undefined4 *)param_3 = 2;
      *(undefined4 *)((int)param_3 + 4) = 0;
    }
    iVar4 = FUN_08029092(param_1,local_88,0x10);
    uVar3 = local_80;
    if (iVar4 == 0) {
      local_2c[1] = local_88[0];
      local_2c[3] = local_80;
      if (param_3 != (longlong *)0x0) {
        iVar4 = local_88[0];
        for (uVar8 = 0; uVar8 < uVar3; uVar8 = uVar8 + 1) {
          if (uVar8 < 0x11) {
LAB_0802978e:
            if ((uVar3 < uVar8 + 4) || (iVar7 = FUN_08006898(iVar4,&DAT_0803ab4b,4), iVar7 != 0)) {
              if ((uVar3 < uVar8 + 6) || (iVar7 = FUN_08006898(iVar4,"SHA256",6), iVar7 != 0))
              goto LAB_0802993c;
              uVar6 = 2;
            }
            else {
              uVar6 = 1;
            }
            *(undefined4 *)(param_3 + 3) = uVar6;
          }
          else if ((uVar3 < uVar8 + 10) || (iVar7 = FUN_08006898(iVar4,"CRASH_DUMP",10), iVar7 != 0)
                  ) {
            if (uVar3 < uVar8 + 5) goto LAB_0802978e;
            iVar7 = FUN_08006898(iVar4,"DEBUG",5);
            if (iVar7 == 0) {
              lVar2 = 0;
              uVar9 = 0;
              local_58 = 0x3c;
              do {
                bVar1 = *(byte *)(local_88[0] + uVar8 + (uVar9 - 0x11));
                uVar5 = (uint)bVar1;
                local_48[uVar9] = bVar1;
                if (uVar5 - 0x41 < 6) {
                  uVar5 = uVar5 - 0x37;
                }
                else {
                  uVar5 = uVar5 - 0x30;
                  if (9 < uVar5) break;
                }
                local_48[uVar9] = (byte)uVar5;
                local_48[uVar9] = (byte)(uVar5 & 0xf);
                lVar11 = FUN_080063f0(uVar5 & 0xf,0,local_58);
                lVar2 = lVar11 + lVar2;
                local_58 = local_58 + -4;
                uVar9 = uVar9 + 1;
              } while (uVar9 < 0x10);
              *param_3 = lVar2;
            }
            else {
              iVar7 = FUN_08006898(iVar4,"SW_ID",5);
              if (iVar7 == 0) {
                lVar2 = 0;
                uVar9 = 0;
                local_58 = 0x3c;
                do {
                  bVar1 = *(byte *)(local_88[0] + uVar8 + (uVar9 - 0x11));
                  uVar5 = (uint)bVar1;
                  local_48[uVar9] = bVar1;
                  if (uVar5 - 0x41 < 6) {
                    uVar5 = uVar5 - 0x37;
                  }
                  else {
                    uVar5 = uVar5 - 0x30;
                    if (9 < uVar5) break;
                  }
                  local_48[uVar9] = (byte)uVar5;
                  local_48[uVar9] = (byte)(uVar5 & 0xf);
                  lVar11 = FUN_080063f0(uVar5 & 0xf,0,local_58);
                  lVar2 = lVar11 + lVar2;
                  local_58 = local_58 + -4;
                  uVar9 = uVar9 + 1;
                } while (uVar9 < 0x10);
                param_3[1] = lVar2;
              }
              else {
                iVar7 = FUN_08006898(iVar4,"HW_ID",5);
                if (iVar7 != 0) goto LAB_0802978e;
                lVar2 = 0;
                uVar9 = 0;
                local_58 = 0x3c;
                do {
                  bVar1 = *(byte *)(local_88[0] + uVar8 + (uVar9 - 0x11));
                  uVar5 = (uint)bVar1;
                  local_48[uVar9] = bVar1;
                  if (uVar5 - 0x41 < 6) {
                    uVar5 = uVar5 - 0x37;
                  }
                  else {
                    uVar5 = uVar5 - 0x30;
                    if (9 < uVar5) break;
                  }
                  local_48[uVar9] = (byte)uVar5;
                  local_48[uVar9] = (byte)(uVar5 & 0xf);
                  lVar11 = FUN_080063f0(uVar5 & 0xf,0,local_58);
                  lVar2 = lVar11 + lVar2;
                  local_58 = local_58 + -4;
                  uVar9 = uVar9 + 1;
                } while (uVar9 < 0x10);
                param_3[2] = lVar2;
              }
            }
          }
          else {
            lVar2 = 0;
            uVar9 = 0;
            local_58 = 0x3c;
            do {
              bVar1 = *(byte *)(local_88[0] + uVar8 + (uVar9 - 0x11));
              uVar5 = (uint)bVar1;
              local_48[uVar9] = bVar1;
              if (uVar5 - 0x41 < 6) {
                uVar5 = uVar5 - 0x37;
              }
              else {
                uVar5 = uVar5 - 0x30;
                if (9 < uVar5) break;
              }
              local_48[uVar9] = (byte)uVar5;
              local_48[uVar9] = (byte)(uVar5 & 0xf);
              lVar11 = FUN_080063f0(uVar5 & 0xf,0,local_58);
              lVar2 = lVar11 + lVar2;
              local_58 = local_58 + -4;
              uVar9 = uVar9 + 1;
            } while (uVar9 < 0x10);
            param_3[4] = lVar2;
          }
LAB_0802993c:
          iVar4 = iVar4 + 1;
        }
      }
      do {
        if (local_80 == 0) {
          if (local_78 != 0) goto LAB_0802999e;
          iVar7 = FUN_08028e00(local_30,local_88);
          bVar10 = false;
          iVar4 = local_5c;
          if (iVar7 == 0) goto LAB_080299a8;
        }
        else {
          iVar4 = FUN_08029092(local_88,auStack_68,0x11);
          bVar10 = iVar4 == 0;
        }
        do {
          do {
            do {
              do {
                if (!bVar10) goto LAB_0802971c;
                iVar4 = FUN_08029092(auStack_68,auStack_74,0x10);
                bVar10 = iVar4 == 0;
              } while (!bVar10);
              local_5c = local_5c + 1;
              iVar4 = FUN_08029092(auStack_74,auStack_54,6);
              bVar10 = iVar4 == 0;
            } while (!bVar10);
            iVar4 = FUN_08029092(auStack_74,auStack_54,0);
            bVar10 = iVar4 == 0;
          } while (!bVar10);
          iVar4 = FUN_08028e00(auStack_68,auStack_74);
          bVar10 = iVar4 == 0;
        } while (!bVar10);
      } while( true );
    }
LAB_0802971c:
    local_78 = 3;
LAB_0802999e:
    local_2c[1] = 0;
    local_2c[3] = 0;
    iVar4 = 0;
LAB_080299a8:
    *local_2c = iVar4;
    iVar4 = local_78;
  }
  if (local_38 != local_7c) {
    FUN_08010960();
  }
  return iVar4;
}




/* 0x080299dc */
undefined4 FUN_080299dc(param_1, param_2)
int param_1; uint * param_2;
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 local_28 [2];
  int local_20;
  undefined1 auStack_1c [8];
  int local_14;
  
  if ((param_1 == 0) || (param_2 == (uint *)0x0)) {
    uVar3 = 8;
  }
  else {
    iVar1 = FUN_08029092(param_1,auStack_1c,0x10);
    if (iVar1 == 0) {
      uVar2 = 0;
LAB_08029ac4:
      do {
        *param_2 = uVar2;
        do {
          if (local_14 == 0) {
            if (false) {
              return 0;
            }
            iVar1 = FUN_08028e00(param_1,auStack_1c);
            if (iVar1 == 0) {
              return 0;
            }
            goto LAB_08029a0a;
          }
          iVar1 = FUN_08029092(auStack_1c,local_28,6);
          if (iVar1 != 0) goto LAB_08029a0a;
          if (local_20 == 8) {
            iVar1 = FUN_08006898(&DAT_0803ab69,local_28[0],8);
            if (iVar1 == 0) {
              uVar2 = *param_2 | 1;
              goto LAB_08029ac4;
            }
            if (local_20 == 8) {
              iVar1 = FUN_08006898(&DAT_0803ab71,local_28[0],8);
              if (iVar1 == 0) {
                uVar2 = *param_2 | 2;
                goto LAB_08029ac4;
              }
              if (local_20 == 8) {
                iVar1 = FUN_08006898(&DAT_0803ab79,local_28[0],8);
                if (iVar1 == 0) {
                  uVar2 = *param_2 | 4;
                  goto LAB_08029ac4;
                }
                if (local_20 == 8) {
                  iVar1 = FUN_08006898(&DAT_0803ab81,local_28[0],8);
                  if (iVar1 == 0) {
                    uVar2 = *param_2 | 8;
                    goto LAB_08029ac4;
                  }
                  if ((local_20 == 8) &&
                     (iVar1 = FUN_08006898(&DAT_0803ab89,local_28[0],8), iVar1 == 0)) {
                    uVar2 = *param_2 | 0x10;
                    goto LAB_08029ac4;
                  }
                }
              }
            }
          }
        } while (((local_20 != 9) || (iVar1 = FUN_08006898(&DAT_0803abc8,local_28[0],9), iVar1 != 0)
                 ) && ((local_20 != 10 ||
                       (iVar1 = FUN_08006898(&DAT_0803abbe,local_28[0],10), iVar1 != 0))));
        uVar2 = *param_2 | 0x20;
      } while( true );
    }
LAB_08029a0a:
    uVar3 = 3;
  }
  return uVar3;
}




/* 0x08029af8 */
int FUN_08029af8(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  undefined4 local_60 [2];
  int local_58;
  undefined1 auStack_54 [12];
  undefined1 auStack_48 [12];
  undefined1 auStack_3c [8];
  int local_34;
  byte local_30 [4];
  undefined1 auStack_2c [12];
  undefined1 auStack_20 [12];
  
  iVar3 = 0;
  if ((param_1 == 0) || (param_2 == 0)) {
    iVar3 = 8;
  }
  else {
    *(undefined1 *)(param_2 + 0x88) = 0;
    *(undefined1 *)(param_2 + 0xb4) = 0;
    *(undefined1 *)(param_2 + 200) = 0;
    *(undefined1 *)(param_2 + 0xd0) = 0;
    *(undefined1 *)(param_2 + 0xd8) = 0;
    uVar1 = FUN_08029092(param_1,auStack_2c);
    if (uVar1 < 3) {
      if (uVar1 == 0) {
        *(undefined1 *)(param_2 + 0x84) = 1;
        iVar2 = FUN_08029092(auStack_2c,auStack_3c,0x10);
        do {
          bVar4 = iVar2 == 0;
          if (bVar4) {
            if (local_34 == 0) {
              iVar2 = FUN_08028e00(auStack_2c,auStack_3c);
              bVar4 = false;
              if (iVar2 == 0) {
                return iVar3;
              }
              goto LAB_08029c12;
            }
            iVar2 = FUN_08029092(auStack_3c,auStack_48,0x10);
            if ((iVar2 != 0) || (iVar2 = FUN_08029092(auStack_48,local_60,6), iVar2 != 0))
            goto LAB_08029b4e;
            iVar2 = FUN_08029092(auStack_48,auStack_20,1);
            if (iVar2 == 0) {
              iVar2 = FUN_08028e62(auStack_20,local_30);
              if (iVar2 != 0) goto LAB_08029b4e;
            }
            else {
              local_30[0] = 0;
            }
            iVar2 = FUN_08029092(auStack_48,auStack_54,0);
            if (iVar2 != 0) goto LAB_08029b4e;
            if (local_58 != 3) goto LAB_08029cc4;
            iVar2 = FUN_08006898(&DAT_0803ab30,local_60[0],3);
            if (iVar2 == 0) {
              uVar1 = FUN_08029366(auStack_54,param_2 + 0x88,local_30[0]);
              goto LAB_08029c10;
            }
            if (local_58 != 3) goto LAB_08029cc4;
            iVar2 = FUN_08006898(&DAT_0803ab33,local_60[0],3);
            if (iVar2 == 0) {
              if (local_30[0] != 0) {
                iVar3 = 3;
              }
              uVar1 = FUN_08029092(auStack_54,param_2 + 0xb8,4);
              if (uVar1 < 3) {
                *(undefined1 *)(param_2 + 0xb4) = 1;
                goto LAB_08029ccc;
              }
              goto LAB_08029b4e;
            }
            if (local_58 != 3) goto LAB_08029cc4;
            iVar2 = FUN_08006898(&DAT_0803ab36,local_60[0],3);
            if (iVar2 == 0) {
              *(undefined1 *)(param_2 + 200) = 1;
              uVar1 = FUN_08029d3c(auStack_54,param_2 + 0xc4);
LAB_08029c10:
              bVar4 = uVar1 == 0;
              goto LAB_08029c12;
            }
            if (local_58 != 3) goto LAB_08029cc4;
            iVar2 = FUN_08006898(&DAT_0803ab45,local_60[0],3);
            if (iVar2 == 0) {
              *(undefined1 *)(param_2 + 0xd0) = 1;
              uVar1 = FUN_080299dc(auStack_54,param_2 + 0xcc);
              goto LAB_08029c10;
            }
            if (local_58 != 3) {
LAB_08029cc4:
              uVar1 = (uint)local_30[0];
              goto LAB_08029c10;
            }
            iVar2 = FUN_08006898(&DAT_0803ab39,local_60[0],3);
            if (iVar2 != 0) {
              if (local_58 == 3) {
                iVar2 = FUN_08006898(&DAT_0803ab3c,local_60[0],3);
                if (iVar2 == 0) {
                  uVar1 = FUN_080293d4(auStack_54,param_2 + 0x84);
                  goto LAB_08029c10;
                }
                if ((local_58 == 3) &&
                   ((iVar2 = FUN_08006898(&DAT_0803ab3f,local_60[0],3), iVar2 == 0 ||
                    ((local_58 == 3 &&
                     ((iVar2 = FUN_08006898(&DAT_0803ab42,local_60[0],3), iVar2 == 0 ||
                      ((local_58 == 3 &&
                       (iVar2 = FUN_08006898(&DAT_0803ab48,local_60[0],3), iVar2 == 0))))))))))
                goto LAB_08029ccc;
              }
              goto LAB_08029cc4;
            }
            if (*(int *)(param_2 + 0x5c) == 0) {
              if (local_30[0] != 0) {
                uVar1 = FUN_08029cf8(auStack_54,param_2 + 0x5c);
                goto LAB_08029c10;
              }
              goto LAB_08029b4e;
            }
          }
          else {
LAB_08029c12:
            if (!bVar4) goto LAB_08029b4e;
          }
LAB_08029ccc:
          if (iVar3 != 0) {
            return iVar3;
          }
          iVar2 = FUN_08028e00(auStack_3c,auStack_48);
        } while( true );
      }
    }
    else {
LAB_08029b4e:
      iVar3 = 3;
    }
  }
  return iVar3;
}




/* 0x08029cf8 */
undefined8 FUN_08029cf8(param_1, param_2, param_3, param_4)
int param_1; undefined4 * param_2; undefined4 param_3; undefined4 param_4;
{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  
  uVar2 = 0;
  if ((param_2 == (undefined4 *)0x0) || (param_1 == 0)) {
    return CONCAT44(param_2,8);
  }
  *param_2 = 0;
  puStack_20 = param_2;
  uStack_1c = param_3;
  uStack_18 = param_4;
  do {
    if (*(int *)(param_1 + 8) == 0) goto LAB_08029d38;
    uVar1 = FUN_08029092(param_1,&puStack_20,0xa4);
    if (uVar1 == 0) {
      uVar2 = FUN_080296e4(&puStack_20,param_2,0);
      goto LAB_08029d38;
    }
  } while (uVar1 < 3);
  uVar2 = 3;
LAB_08029d38:
  return CONCAT44(puStack_20,uVar2);
}




/* 0x08029d3c */
undefined4 FUN_08029d3c(param_1, param_2)
int param_1; uint * param_2;
{
  int iVar1;
  undefined4 uVar2;
  byte *local_28;
  int local_24;
  undefined1 auStack_1c [16];
  
  uVar2 = 0;
  if ((param_1 == 0) || (param_2 == (uint *)0x0)) {
    uVar2 = 8;
  }
  else {
    iVar1 = FUN_08029092(param_1,auStack_1c,3);
    if (((iVar1 == 0) && (iVar1 = FUN_08028e1e(auStack_1c,&local_28), iVar1 == 0)) &&
       (local_24 != 0)) {
      *param_2 = (uint)*local_28 << 1;
      if ((local_24 == 2) && ((int)((uint)local_28[1] << 0x18) < 0)) {
        *param_2 = *param_2 | 1;
      }
    }
    else {
      uVar2 = 3;
    }
  }
  return uVar2;
}




/* 0x08029d98 */
undefined4 FUN_08029d98(param_1, param_2)
int param_1; undefined4 * param_2;
{
  int iVar1;
  char *local_58;
  uint local_54;
  uint local_50;
  undefined1 auStack_4c [12];
  undefined1 auStack_40 [12];
  uint local_34;
  int local_30;
  uint local_28;
  uint local_24;
  int local_20;
  undefined1 auStack_1c [12];
  
  if ((param_1 == 0) || (param_2 == (undefined4 *)0x0)) {
    return 8;
  }
  iVar1 = FUN_08029092(param_1,auStack_40,0x10);
  if ((((iVar1 == 0) && (iVar1 = FUN_08029092(auStack_40,auStack_4c,0x10), iVar1 == 0)) &&
      (iVar1 = FUN_08029092(auStack_4c,&local_58,6), iVar1 == 0)) &&
     ((iVar1 = FUN_08029092(auStack_4c,auStack_1c,0), iVar1 == 0 &&
      (iVar1 = FUN_08028e00(auStack_40,auStack_4c), iVar1 == 0)))) {
    *param_2 = 3;
    if ((local_50 == 9) && (iVar1 = FUN_08006898(&DAT_0803ab91,local_58,9), iVar1 == 0)) {
      iVar1 = FUN_08029092(auStack_40,&local_58,3);
      if (iVar1 != 0) {
        return 3;
      }
      iVar1 = FUN_08028e1e(&local_58,&local_34);
      if (iVar1 != 0) {
        return 3;
      }
      local_28 = local_34;
      local_20 = local_30;
      local_24 = local_34 + local_30;
      if (local_24 < local_34) {
        return 3;
      }
      if (local_54 < local_24) {
        return 3;
      }
      iVar1 = FUN_08029092(&local_28,auStack_4c,0x10);
      if (iVar1 != 0) {
        return 3;
      }
      iVar1 = FUN_08029092(auStack_4c,&local_58,2);
      if (iVar1 != 0) {
        return 3;
      }
      if (local_50 == 0) {
        return 3;
      }
      do {
        if (*local_58 != '\0') {
          if (0x200 < local_50) {
            return 3;
          }
          break;
        }
        local_58 = local_58 + 1;
        local_50 = local_50 - 1;
      } while (local_50 != 0);
      param_2[2] = local_58;
      param_2[1] = local_50;
      iVar1 = FUN_08029092(auStack_4c,&local_58,2);
      if (iVar1 != 0) {
        return 3;
      }
      if (local_50 == 0) {
        return 3;
      }
      do {
        if (*local_58 != '\0') {
          if (4 < local_50) {
            return 3;
          }
          break;
        }
        local_58 = local_58 + 1;
        local_50 = local_50 - 1;
      } while (local_50 != 0);
      param_2[4] = local_58;
      param_2[3] = local_50;
      iVar1 = FUN_08028e00(&local_28,auStack_4c);
      if (iVar1 != 0) {
        return 3;
      }
      *param_2 = 0;
    }
    iVar1 = FUN_08028e00(param_1,auStack_40);
    if (iVar1 == 0) {
      return 0;
    }
  }
  return 3;
}




/* 0x08029ee4 */
undefined4 FUN_08029ee4(param_1, param_2)
int param_1; undefined4 * param_2;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_38 [2];
  int local_30;
  undefined1 auStack_2c [12];
  undefined1 auStack_20 [16];
  
  if ((param_1 == 0) || (param_2 == (undefined4 *)0x0)) {
    return 8;
  }
  iVar1 = FUN_08029092(param_1,auStack_2c,0x10);
  if (iVar1 != 0) {
    return 3;
  }
  iVar1 = FUN_08029092(auStack_2c,local_38,6);
  if (iVar1 != 0) {
    return 3;
  }
  iVar1 = FUN_08029092(auStack_2c,auStack_20,0);
  if (iVar1 != 0) {
    return 3;
  }
  if (local_30 == 9) {
    iVar1 = FUN_08006898(&DAT_0803ab9a,local_38[0],9);
    uVar2 = 0;
    if (iVar1 == 0) goto LAB_08029f7c;
    if (local_30 == 9) {
      iVar1 = FUN_08006898(&DAT_0803aba3,local_38[0],9);
      if (iVar1 == 0) {
        uVar2 = 1;
        goto LAB_08029f7c;
      }
      if (local_30 == 9) {
        iVar1 = FUN_08006898(&DAT_0803abac,local_38[0],9);
        if (iVar1 == 0) {
          uVar2 = 2;
          goto LAB_08029f7c;
        }
        if ((local_30 == 9) && (iVar1 = FUN_08006898(&DAT_0803abb5,local_38[0],9), iVar1 == 0)) {
          uVar2 = 3;
          goto LAB_08029f7c;
        }
      }
    }
  }
  uVar2 = 4;
LAB_08029f7c:
  *param_2 = uVar2;
  iVar1 = FUN_08028e00(param_1,auStack_2c);
  if (iVar1 != 0) {
    return 3;
  }
  return 0;
}




/* 0x08029f98 */
undefined4 FUN_08029f98(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  undefined1 auStack_28 [12];
  char *local_1c;
  uint uStack_18;
  
  if ((param_1 == 0) || (param_2 == 0)) {
    return 8;
  }
  iVar1 = FUN_08029ee4(param_1,param_2 + 0xfc);
  if (iVar1 == 0) {
    if (3 < *(uint *)(param_2 + 0xfc)) {
      return 9;
    }
    if (((*(uint *)(param_2 + 0xfc) == *(uint *)(param_2 + 0x1c)) &&
        (iVar1 = FUN_08029092(param_1,auStack_28,3), iVar1 == 0)) &&
       (iVar1 = FUN_08028e1e(auStack_28,&local_1c), iVar1 == 0)) {
      for (; (uStack_18 != 0 && (*local_1c == '\0')); local_1c = local_1c + 1) {
        uStack_18 = uStack_18 - 1;
      }
      *(char **)(param_2 + 0x20) = local_1c;
      *(uint *)(param_2 + 0x28) = uStack_18;
      if (uStack_18 < 0x201) {
        *(char **)(param_2 + 0x100) = local_1c;
        *(uint *)(param_2 + 0x104) = uStack_18;
        return 0;
      }
      return 3;
    }
  }
  return 3;
}




/* 0x0802a00e */
undefined8 FUN_0802a00e(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  
  uVar3 = 0;
  uStack_18 = param_2;
  uStack_14 = param_3;
  uStack_10 = param_4;
  uVar1 = FUN_08029092(param_1,&uStack_18);
  if ((2 < uVar1) || ((uVar1 == 0 && (iVar2 = FUN_08028e1e(&uStack_18,param_2), iVar2 != 0)))) {
    uVar3 = 3;
  }
  return CONCAT44(uStack_18,uVar3);
}




/* 0x0802a030 */
undefined8 FUN_0802a030(param_1, param_2, param_3, param_4)
int param_1; int param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  
  uVar4 = 0;
  iStack_28 = param_2;
  if ((param_1 == 0) || (param_2 == 0)) {
    uVar4 = 8;
    goto LAB_0802a04e;
  }
  uStack_24 = param_3;
  uStack_20 = param_4;
  iVar1 = FUN_08029092(param_1,&iStack_28,0x10);
  if (iVar1 == 0) {
    iVar2 = param_2 + 0x40;
    iVar1 = FUN_08029092(&iStack_28,iVar2,0x17);
    if (iVar1 == 0) {
      uVar3 = 1;
    }
    else {
      if ((iVar1 != 1) || (iVar1 = FUN_08029092(&iStack_28,iVar2,0), iVar1 != 0)) goto LAB_0802a0c6;
      uVar3 = 0;
    }
    iVar1 = FUN_08028f54(iVar2,param_2 + 0x3c,uVar3);
    if (iVar1 == 0) {
      iVar2 = param_2 + 0x50;
      iVar1 = FUN_08029092(&iStack_28,iVar2,0x17);
      if (iVar1 == 0) {
        uVar3 = 1;
      }
      else {
        if ((iVar1 != 1) || (iVar1 = FUN_08029092(&iStack_28,iVar2,0), iVar1 != 0))
        goto LAB_0802a0c6;
        uVar3 = 0;
      }
      iVar1 = FUN_08028f54(iVar2,param_2 + 0x4c,uVar3);
      if ((iVar1 == 0) && (iVar1 = FUN_08028e00(param_1,&iStack_28), iVar1 == 0)) goto LAB_0802a04e;
    }
  }
LAB_0802a0c6:
  uVar4 = 3;
LAB_0802a04e:
  return CONCAT44(iStack_28,uVar4);
}




/* 0x0802a0cc */
undefined8 FUN_0802a0cc(param_1, param_2, param_3, param_4)
int param_1; uint * param_2; undefined4 param_3; undefined4 param_4;
{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  uint *puStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  
  uVar3 = 0;
  if ((param_1 == 0) || (param_2 == (uint *)0x0)) {
    return CONCAT44(param_2,8);
  }
  puStack_18 = param_2;
  uStack_14 = param_3;
  uStack_10 = param_4;
  iVar2 = FUN_08029092(param_1,&puStack_18,0xa0);
  if (iVar2 == 0) {
    iVar2 = FUN_08029092(&puStack_18,param_2 + 1,2);
    if (((iVar2 == 0) && (param_2[3] == 1)) &&
       (bVar1 = *(byte *)param_2[1], *param_2 = (uint)bVar1, bVar1 < 3)) goto LAB_0802a0e6;
  }
  else {
    *param_2 = 0;
  }
  uVar3 = 3;
LAB_0802a0e6:
  return CONCAT44(puStack_18,uVar3);
}




/* 0x0802a10e */
undefined4 FUN_0802a10e(param_1, param_2, param_3)
uint * param_1; uint param_2; uint param_3;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int local_20;
  
  uVar3 = 0;
  local_20 = 0;
  while( true ) {
    if (param_3 <= uVar3) {
      return 0;
    }
    iVar1 = FUN_08029300(*param_1,param_2,&local_20);
    if (((iVar1 != 0) || (uVar2 = local_20 + *param_1, uVar2 < *param_1)) ||
       (*param_1 = uVar2, param_2 < uVar2)) break;
    uVar3 = uVar3 + 1;
  }
  return 1;
}




/* 0x0802a150 */
undefined1 FUN_0802a150()
{
  return (char)*(undefined2 *)(DAT_0804dbb8 + 0x30);
}




/* 0x0802a160 */
undefined8 pm_battery_check(param_1, param_2, param_3, param_4)
undefined4 param_1; uint param_2; uint param_3; undefined4 param_4;
{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  uint local_28;
  uint local_24;
  char local_20;
  undefined3 uStack_1f;
  
  local_28 = param_2 & 0xffffff00;
  local_24 = param_3 & 0xffffff00;
  _local_20 = CONCAT31((int3)((uint)param_4 >> 8),1);
  uVar1 = FUN_0802a150();
  iVar2 = FUN_0802b68c(0);
  iVar3 = FUN_0802b68c(1);
  if ((iVar2 == 6) && (iVar3 == 1)) {
    local_24 = local_24 & 0xffffff00;
LAB_0802a1b0:
    iVar2 = FUN_0802a8bc(&local_28);
    if (iVar2 != 0) goto LAB_0802a1f4;
    if ((char)local_28 == '\0') {
      boot_log_message("battery good, boot up");
      iVar2 = FUN_0802ad4a(uVar1,*(undefined2 *)(DAT_0804dbb8 + 0xc));
    }
    else {
      iVar2 = FUN_0802a910(&local_20);
      if (iVar2 != 0) goto LAB_0802a1f4;
      if (local_20 == '\x01') {
        DAT_0804dbb4 = &DAT_0804dbc4;
        goto LAB_0802a1f4;
      }
    }
  }
  else {
    iVar2 = FUN_0802a9ba(&local_24);
    if (iVar2 != 0) goto LAB_0802a1f4;
    if ((char)local_24 != '\x01') goto LAB_0802a1b0;
    boot_log_message("debug board present");
  }
  DAT_0804dbb4 = &DAT_0804dbec;
LAB_0802a1f4:
  return CONCAT44(local_28,iVar2);
}




/* 0x0802a310 */
int pm_smb_init()
{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0802a960(&DAT_0804dbac);
  if ((iVar1 == 0) && (DAT_0804dbac == '\x01')) {
    if (DAT_0804dbae == '\0') {
      iVar1 = FUN_0802dd00();
      if (iVar1 != 0) {
        iVar2 = FUN_0802dcf4();
        if (iVar2 != 0) {
          boot_log_message("pm_smb_init failed");
          return iVar1;
        }
        DAT_0804dbb1 = 1;
        boot_log_message("Couldn\'t get smb_hw_info, skip enum and smb config");
        iVar1 = pm_set_usb100();
        return iVar1;
      }
    }
    else {
      FUN_0802a150();
      FUN_0802acce();
    }
    iVar1 = FUN_0802fa84();
    if (iVar1 != 0) {
      iVar1 = FUN_0802fa6e();
      DAT_0804dbb2 = (undefined1)iVar1;
      if (iVar1 == 0) {
        boot_log_message(&DAT_0802a454);
        DAT_0804dbb4 = &DAT_0804dbe4;
        return 0;
      }
      if (iVar1 == 1) {
        boot_log_message(&DAT_0802a458);
        DAT_0804dbb4 = &DAT_0804dbcc;
        return 0;
      }
      if (iVar1 == 2) {
        boot_log_message(&DAT_0802a45c);
        DAT_0804dbb4 = &DAT_0804dbd4;
        return 0;
      }
      if (iVar1 == 3) {
        boot_log_message("Float");
        DAT_0804dbb4 = &DAT_0804dbdc;
        return 0;
      }
      boot_log_message("unknown-->shutdown");
      DAT_0804dbb4 = &DAT_0804dbf4;
      return 0;
    }
  }
  else {
    if (iVar1 == 0 && DAT_0804dbac == '\0') {
      boot_log_message("boot but no charger, shutdown");
      DAT_0804dbb4 = &DAT_0804dbf4;
      return 0;
    }
    boot_log_message("error in charger detectiong");
  }
  return 0x3b;
}




/* 0x0802a51c */
void FUN_0802a51c(param_1, param_2, param_3)
undefined4 param_1; int param_2; int param_3;
{
  undefined4 *local_20;
  
  local_20 = *(undefined4 **)(&DAT_0805a14c + param_3 * 4);
  if (local_20 == (undefined4 *)0x0) {
    FUN_0802c644(8,&local_20);
    *local_20 = param_1;
    if (*(char *)(param_2 + 3) == '\x15') {
      *(undefined1 *)(local_20 + 1) = 1;
      FUN_0802bdf4(param_1,param_3);
    }
    else if (*(char *)(param_2 + 3) == '1') {
      *(undefined1 *)(local_20 + 1) = 0;
      FUN_0802e4f4(param_1,param_3);
    }
    *(undefined4 **)(&DAT_0805a14c + param_3 * 4) = local_20;
  }
  return;
}




/* 0x0802a574 */
undefined8 pm_set_usb100(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; uint param_3; uint param_4;
{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  uint uVar7;
  undefined4 local_30;
  uint local_2c;
  uint local_28;
  
  uVar7 = 0;
  bVar6 = false;
  local_28 = param_4 & 0xffffff00;
  _GHIDRA_FIELD(local_30, 1, uint24_t) = (undefined3)((uint)param_2 >> 8);
  local_30 = CONCAT31(_GHIDRA_FIELD(local_30, 1, uint24_t),1);
  local_2c = param_3 & 0xffffff00;
  uVar1 = FUN_0802a150();
  if ((((DAT_0804dbae == '\x01') && (DAT_0804dbad == '\x01')) && (DAT_0804dbaf == '\x01')) &&
     (DAT_0804dbb0 == '\0')) {
    uVar7 = FUN_0802aef8(uVar1);
  }
  uVar2 = FUN_0802a910(&local_30);
  uVar2 = uVar2 | uVar7;
  if (uVar2 != 0) goto LAB_0802a6c6;
  if ((char)local_30 != '\0') {
    if (DAT_0804dbae == '\x01') {
      uVar2 = FUN_0802adf2(uVar1,1);
    }
    iVar3 = FUN_0802c31c();
    do {
      if ((char)local_30 == '\0') goto LAB_0802a694;
      uVar7 = FUN_0802a8bc(&local_2c);
      if (((uVar2 | uVar7) == 0) && ((char)local_2c == '\0')) {
        DAT_0804dbb4 = &DAT_0804dbec;
        uVar2 = 0;
        break;
      }
      uVar4 = FUN_0802a960(&local_28);
      uVar2 = uVar2 | uVar7 | uVar4;
      if (((char)local_28 == '\0') || (uVar2 != 0)) {
LAB_0802a60e:
        DAT_0804dbb4 = &DAT_0804dbf4;
LAB_0802a682:
        local_30 = CONCAT31(_GHIDRA_FIELD(local_30, 1, uint24_t),1);
        goto LAB_0802a6c6;
      }
      if (((DAT_0804dbae != '\0') || (DAT_0804dbb1 == '\0')) &&
         ((iVar5 = FUN_0802facc(), iVar5 == 6 || (iVar5 == 4)))) {
        FUN_08016afc("UBS poll status",iVar5,0x42,0);
        if (DAT_0804dbae != '\x01') {
          boot_log_message("Set USB100 mode");
          uVar2 = FUN_0802deec(0);
          goto LAB_0802a60e;
        }
        uVar2 = pm_hw_atc(uVar1);
        goto LAB_0802a682;
      }
      bVar6 = !bVar6;
      if (iVar3 != 5) {
        FUN_0802c2a0(uVar1,iVar3,bVar6);
      }
      thunk_FUN_080199b4(500000);
      uVar2 = FUN_0802a910(&local_30);
    } while (uVar2 == 0);
    if ((char)local_30 != '\0') goto LAB_0802a6c6;
LAB_0802a694:
    if (((local_2c & 0xff) != 1) || (uVar2 != 0)) goto LAB_0802a6c6;
    iVar3 = FUN_0802fb44();
    if ((iVar3 == 0) &&
       (((FUN_0802f9d4(), DAT_0804dbae != '\0' || (DAT_0804dbb1 == '\0')) &&
        (FUN_0802f9c0(), DAT_0804dbae != '\0')))) {
      uVar2 = FUN_0802adf2(uVar1,0);
    }
  }
  DAT_0804dbb4 = &DAT_0804dbec;
LAB_0802a6c6:
  return CONCAT44(local_30,uVar2);
}




/* 0x0802a6f4 */
uint pm_hw_atc(param_1)
undefined4 param_1;
{
  uint uVar1;
  uint uVar2;
  
  uVar2 = 0;
  boot_log_message("-->hw ATC");
  if (DAT_0804dbb0 == '\x01') {
    uVar2 = FUN_0802ad4a(param_1,*(undefined2 *)(DAT_0804dbb8 + 0x12));
  }
  else if (DAT_0804dbad == '\0') {
    uVar1 = FUN_0802ada2(param_1,*(undefined2 *)(DAT_0804dbb8 + 0x12));
    uVar2 = FUN_0802adf2(param_1,3);
    uVar2 = uVar2 | uVar1;
  }
  else if (DAT_0804dbad == '\x01') {
    uVar2 = FUN_0802ad22(param_1,*(undefined2 *)(DAT_0804dbb8 + 0x12));
  }
  uVar1 = FUN_0802ac94(param_1,*(undefined2 *)(DAT_0804dbb8 + 6),
                       *(undefined2 *)(DAT_0804dbb8 + 0x2e));
  DAT_0804dbb4 = &DAT_0804dbf4;
  return uVar1 | uVar2;
}




/* 0x0802a7e0 */
undefined4 FUN_0802a7e0(param_1)
int * param_1;
{
  int iVar1;
  undefined4 uVar2;
  char local_28 [12];
  int local_1c;
  undefined1 auStack_14 [8];
  
  uVar2 = 0;
  iVar1 = FUN_08008c60();
  if ((iVar1 == 0) && (iVar1 = FUN_08008c14("VBATT",auStack_14), iVar1 == 0)) {
    iVar1 = FUN_08008d98(auStack_14,local_28);
    if (iVar1 != 0) {
      uVar2 = 0x1e;
    }
    if (local_28[0] == '\0') {
      uVar2 = 0x1e;
    }
    else {
      *param_1 = local_1c / 1000;
    }
  }
  else {
    uVar2 = 0x1e;
  }
  return uVar2;
}




/* 0x0802a830 */
undefined4 FUN_0802a830(param_1, param_2)
undefined1 param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0802a8a8();
  if (iVar1 == 1) {
    uVar2 = FUN_0802b97c(param_1,0,param_2);
  }
  else if (iVar1 == 0) {
    uVar2 = 0x16;
  }
  return uVar2;
}




/* 0x0802a858 */
undefined4 FUN_0802a858(param_1, param_2)
undefined1 param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0802a8a8();
  if (iVar1 == 1) {
    uVar2 = FUN_0802b9c8(param_1,0,param_2);
  }
  else if (iVar1 == 0) {
    uVar2 = 0x16;
  }
  return uVar2;
}




/* 0x0802a880 */
undefined4 FUN_0802a880(param_1, param_2)
undefined1 param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0802a8a8();
  if (iVar1 == 1) {
    uVar2 = FUN_0802ba1a(param_1,0,param_2);
  }
  else if (iVar1 == 0) {
    uVar2 = 0x16;
  }
  return uVar2;
}




/* 0x0802a8a8 */
undefined1 FUN_0802a8a8(param_1)
int param_1;
{
  if (*(int *)(&DAT_0805a14c + param_1 * 4) != 0) {
    return *(undefined1 *)(*(int *)(&DAT_0805a14c + param_1 * 4) + 4);
  }
  return 2;
}




/* 0x0802a8bc */
int FUN_0802a8bc(param_1, param_2, param_3, param_4)
undefined1 * param_1; uint param_2; uint param_3; uint param_4;
{
  undefined4 uVar1;
  int iVar2;
  undefined1 *puVar3;
  uint local_1c;
  uint local_18;
  uint local_14;
  
  local_1c = param_2 & 0xffffff00;
  local_18 = param_3 & 0xffffff00;
  local_14 = param_4 & 0xffffff00;
  puVar3 = param_1;
  uVar1 = FUN_0802a150();
  iVar2 = FUN_0802a8a8();
  if (iVar2 == 1) {
    iVar2 = FUN_0802b878(uVar1,0,&local_1c,&local_14,puVar3);
  }
  else {
    if (iVar2 != 0) goto LAB_0802a902;
    iVar2 = FUN_0802e0d6(uVar1,0,&local_1c,&local_18,&local_14);
  }
  if (iVar2 != 0) {
    return iVar2;
  }
LAB_0802a902:
  *param_1 = (undefined1)local_1c;
  return 0;
}




/* 0x0802a910 */
int FUN_0802a910(param_1)
undefined1 * param_1;
{
  int iVar1;
  uint local_18;
  
  local_18 = 0;
  iVar1 = FUN_0802a7e0(&local_18);
  if (iVar1 == 0) {
    DAT_0804dc00 = local_18;
    FUN_08016afc("battery voltage",local_18,0x42,0);
    if (local_18 < *(uint*)DAT_0804dbb8) {
      *param_1 = 1;
    }
    else {
      *param_1 = 0;
    }
  }
  return iVar1;
}




/* 0x0802a960 */
int FUN_0802a960(param_1, param_2, param_3, param_4)
undefined1 * param_1; undefined4 param_2; uint param_3; uint param_4;
{
  undefined4 uVar1;
  int iVar2;
  uint local_18;
  uint local_14;
  
  local_18 = param_3;
  local_14 = param_4;
  uVar1 = FUN_0802a150();
  local_18 = local_18 & 0xffffff00;
  iVar2 = FUN_0802a8a8(uVar1);
  if (iVar2 == 1) {
    iVar2 = FUN_0802b8d4(uVar1,0,&local_18);
    if (iVar2 != 0) {
      return iVar2;
    }
  }
  else {
    if (iVar2 != 0) {
      return 0;
    }
    iVar2 = FUN_0802e034(uVar1,0,&local_14);
    if (iVar2 != 0) {
      return iVar2;
    }
    if (((local_14 & 0xff) == 1) || ((local_14 & 0xff) == 3)) {
      _GHIDRA_FIELD(local_18, 0, byte) = 1;
    }
    else {
      _GHIDRA_FIELD(local_18, 0, byte) = 0;
    }
  }
  *param_1 = (undefined1)local_18;
  return 0;
}




/* 0x0802a9ba */
int FUN_0802a9ba(param_1, param_2, param_3, param_4)
undefined1 * param_1; uint param_2; uint param_3; uint param_4;
{
  undefined4 uVar1;
  int iVar2;
  undefined1 *puVar3;
  uint local_24;
  uint local_20;
  uint local_1c;
  
  local_24 = param_2 & 0xffffff00;
  local_20 = param_3 & 0xffffff00;
  local_1c = param_4 & 0xffffff00;
  puVar3 = param_1;
  uVar1 = FUN_0802a150();
  iVar2 = FUN_0802a8a8();
  if (iVar2 == 1) {
    iVar2 = FUN_0802b878(uVar1,0,&local_24,&local_1c,puVar3);
  }
  else {
    if (iVar2 != 0) goto LAB_0802aa04;
    iVar2 = FUN_0802e0d6(uVar1,0,&local_24,&local_20,&local_1c);
  }
  if (iVar2 != 0) {
    return iVar2;
  }
LAB_0802aa04:
  if ((char)local_1c == '\0') {
    *param_1 = 1;
  }
  else {
    *param_1 = 0;
  }
  return 0;
}




/* 0x0802aa1c */
int FUN_0802aa1c()
{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (DAT_0804dbb4 == (char *)0x0) {
      return iVar1;
    }
    DAT_0804dbfc = DAT_0804dbfd;
    DAT_0804dbfd = *(uint*)DAT_0804dbb4;
    if (*(code **)(DAT_0804dbb4 + 4) != (code *)0x0) {
      iVar1 = (**(code **)(DAT_0804dbb4 + 4))();
    }
  } while (((iVar1 == 0) && (DAT_0804dbfd != '\n')) && (DAT_0804dbfd != '\v'));
  FUN_08016afc("Current status",DAT_0804dbfd,0x42,0);
  return iVar1;
}




/* 0x0802aa70 */
uint pm_charge_init()
{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar1 = FUN_0802a150();
  boot_log_message("--> Charge init");
  DAT_0804dbad = FUN_0802a8a8(uVar1);
  uVar2 = FUN_0802ac94(uVar1,*(undefined2 *)(DAT_0804dbb8 + 6),*(undefined2 *)(DAT_0804dbb8 + 2));
  uVar3 = FUN_0802ad22(uVar1,*(undefined2 *)(DAT_0804dbb8 + 0x14));
  uVar4 = FUN_0802ae22(uVar1,*(undefined2 *)(DAT_0804dbb8 + 0x24));
  uVar5 = FUN_0802ad7a(uVar1,*(undefined2 *)(DAT_0804dbb8 + 0x22));
  uVar5 = uVar5 | uVar4 | uVar3 | uVar2;
  if (DAT_0804dbad == '\x01') {
    uVar2 = FUN_0802a880(uVar1,&DAT_0804dbaf);
    uVar3 = FUN_0802a830(uVar1,&DAT_0804dbae);
    uVar5 = uVar3 | uVar2 | uVar5;
  }
  if (DAT_0804dbad == '\0') {
    FUN_0802adf2(uVar1,2);
  }
  return uVar5;
}




/* 0x0802ab44 */
uint pm_usb_enum()
{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  uint in_r3 = 0;
  uint uVar6;
  uint local_20;
  
  uVar6 = 0;
  local_20 = in_r3;
  uVar1 = FUN_0802a150();
  if (DAT_0804dbae == '\0') {
    boot_log_message("Set USB500 mode");
    uVar6 = FUN_0802deec(1);
  }
  do {
    iVar2 = FUN_0802f9ea();
    if (DAT_0804dbae == '\0') {
LAB_0802ab9a:
      if (iVar2 == 0) {
LAB_0802abc8:
        boot_log_message("===== enum success =====");
        if (DAT_0804dbae == '\x01') {
          if (DAT_0804dbad == '\0') {
            uVar5 = FUN_0802adca(uVar1,*(undefined2 *)(DAT_0804dbb8 + 0x10));
LAB_0802abf0:
            uVar6 = uVar6 | uVar5;
          }
          else if (DAT_0804dbad == '\x01') {
            uVar5 = FUN_0802aef8(uVar1);
            goto LAB_0802abf0;
          }
          uVar5 = FUN_0802ad4a(uVar1,*(undefined2 *)(DAT_0804dbb8 + 0x10));
          uVar6 = uVar6 | uVar5;
        }
        uVar5 = pm_set_usb100();
LAB_0802abac:
        return uVar6 | uVar5;
      }
      if (iVar2 != 2) {
        boot_log_message("Enum fail-->HW ATC");
        uVar5 = pm_hw_atc(uVar1);
        goto LAB_0802abac;
      }
      break;
    }
    if ((DAT_0804dbad == '\x01') && (DAT_0804dbaf == '\x01')) {
      local_20 = local_20 & 0xffffff00;
      uVar3 = FUN_0802a150();
      iVar4 = FUN_0802a858(uVar3,&local_20);
      if (iVar4 == 0) {
        DAT_0804dbb0 = (char)local_20;
      }
      else {
        DAT_0804dbb0 = '\0';
      }
    }
    if (DAT_0804dbb0 != '\0') goto LAB_0802ab9a;
    if (iVar2 == 0) goto LAB_0802abc8;
  } while (iVar2 != 2);
  boot_log_message("Disconnected during enum");
  DAT_0804dbb4 = &DAT_0804dbf4;
  return uVar6;
}




/* 0x0802ac94 */
undefined4 FUN_0802ac94(param_1, param_2, param_3)
undefined1 param_1; undefined4 param_2; undefined4 param_3;
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0802a8a8();
  if (iVar1 == 1) {
    uVar2 = FUN_0802baa0(param_1,0,param_2,param_3);
  }
  else if (iVar1 == 0) {
    uVar2 = FUN_0802e198(param_1,0,param_2,param_3);
  }
  return uVar2;
}




/* 0x0802acce */
undefined4 FUN_0802acce(param_1)
undefined1 param_1;
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0802a8a8();
  if (iVar1 == 1) {
    uVar2 = FUN_0802bb6a(param_1,0);
  }
  else if (iVar1 == 0) {
    uVar2 = 0x16;
  }
  return uVar2;
}




/* 0x0802acf2 */
undefined4 FUN_0802acf2(param_1, param_2)
undefined1 param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0802a8a8();
  if (iVar1 == 1) {
    uVar2 = FUN_0802bba8(param_1,0,param_2);
  }
  else if (iVar1 == 0) {
    uVar2 = FUN_0802e264(param_1,0,param_2);
  }
  return uVar2;
}




/* 0x0802ad22 */
undefined4 FUN_0802ad22(param_1, param_2)
undefined1 param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0802a8a8();
  if (iVar1 == 1) {
    uVar2 = FUN_0802bc08(param_1,0,param_2);
  }
  else if (iVar1 == 0) {
    uVar2 = 0x16;
  }
  return uVar2;
}




/* 0x0802ad4a */
undefined4 FUN_0802ad4a(param_1, param_2)
undefined1 param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0802a8a8();
  if (iVar1 == 1) {
    uVar2 = FUN_0802bc4c(param_1,0,param_2);
  }
  else if (iVar1 == 0) {
    uVar2 = FUN_0802e2d0(param_1,0,param_2);
  }
  return uVar2;
}




/* 0x0802ad7a */
undefined4 FUN_0802ad7a(param_1, param_2)
undefined1 param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0802a8a8();
  if (iVar1 == 1) {
    uVar2 = FUN_0802bcb0(param_1,0,param_2);
  }
  else if (iVar1 == 0) {
    uVar2 = 0x16;
  }
  return uVar2;
}




/* 0x0802ada2 */
undefined4 FUN_0802ada2(param_1, param_2)
undefined1 param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0802a8a8();
  if (iVar1 == 1) {
    uVar2 = 0x16;
  }
  else if (iVar1 == 0) {
    uVar2 = FUN_0802e32e(param_1,0,param_2);
  }
  return uVar2;
}




/* 0x0802adca */
undefined4 FUN_0802adca(param_1, param_2)
undefined1 param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0802a8a8();
  if (iVar1 == 1) {
    uVar2 = 0x16;
  }
  else if (iVar1 == 0) {
    uVar2 = FUN_0802e388(param_1,0,param_2);
  }
  return uVar2;
}




/* 0x0802adf2 */
undefined4 FUN_0802adf2(param_1, param_2)
undefined1 param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0802a8a8();
  if (iVar1 == 1) {
    uVar2 = FUN_0802bd14(param_1,0,param_2);
  }
  else if (iVar1 == 0) {
    uVar2 = FUN_0802e444(param_1,0,param_2);
  }
  return uVar2;
}




/* 0x0802ae22 */
undefined4 FUN_0802ae22(param_1, param_2)
undefined1 param_1; undefined4 param_2;
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0802a8a8();
  if (iVar1 == 1) {
    uVar2 = FUN_0802bd68(param_1,0,param_2);
  }
  else if (iVar1 == 0) {
    uVar2 = 0x16;
  }
  return uVar2;
}




/* 0x0802aef8 */
undefined4 FUN_0802aef8(param_1)
undefined1 param_1;
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0802a8a8();
  if (iVar1 == 1) {
    uVar2 = FUN_0802bdb6(param_1,0);
  }
  else if (iVar1 == 0) {
    uVar2 = 0x16;
  }
  return uVar2;
}




/* 0x0802af1c */
undefined4 FUN_0802af1c(param_1)
int param_1;
{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 == 0) {
    uVar1 = 0xe;
  }
  else {
    thunk_FUN_080199b4();
  }
  return uVar1;
}




