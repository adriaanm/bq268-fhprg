/* Auto-generated: pm_smps_driver.c */
/* Functions: 6 */
#include "globals.h"

/* 0x0802e5dc */
void FUN_0802e5dc(param_1, param_2, param_3)
undefined4 param_1; ushort * param_2; uint param_3;
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 *local_38 [2];
  int local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24 [2];
  
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24[0] = 0x66;
  local_24[1] = 0x6b;
  cVar1 = (char)param_2[1];
  if ((cVar1 == '\x03') || (cVar1 == '\x1c')) {
    if ((*(char *)((int)param_2 + 3) != '\b') && (*(char *)((int)param_2 + 3) != '\t')) {
      return;
    }
  }
  else {
    if (cVar1 != '\"') {
      return;
    }
    cVar1 = *(char *)((int)param_2 + 3);
    if ((((cVar1 != '\r') && (cVar1 != '\x0e')) && (cVar1 != '\x0f')) && (cVar1 != '\x10')) {
      return;
    }
  }
  local_38[0] = *(undefined4 **)(&DAT_0805a2f8 + param_3 * 4);
  if (local_38[0] == (undefined4 *)0x0) {
    FUN_0802c644(0x10,local_38);
    *local_38[0] = param_1;
    iVar2 = FUN_0802e824(2);
    local_38[0][1] = iVar2;
    if (iVar2 == 0) {
      ((code*)DAT_0804cd60)("pm_smps_driver.c",0x7d,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (1 < param_3) {
      ((code*)DAT_0804cd60)("pm_smps_driver.c",0x80,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar2 = FUN_0802e848(local_24[param_3],param_3);
    local_38[0][2] = iVar2;
    if (iVar2 == 0) {
      ((code*)DAT_0804cd60)("pm_smps_driver.c",0x85,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    FUN_0802c644(iVar2 * 0xc,local_38[0] + 3);
    if (local_38[0][3] == 0) {
      ((code*)DAT_0804cd60)("pm_smps_driver.c",0x8a,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *(ushort *)(local_38[0][3] + 8) = *param_2;
    *(undefined4 **)(&DAT_0805a2f8 + param_3 * 4) = local_38[0];
    if (local_38[0] == (undefined4 *)0x0) {
      return;
    }
  }
  if ((uint)*param_2 < (uint)*(ushort *)(local_38[0][3] + 8)) {
    ((code*)DAT_0804cd60)("pm_smps_driver.c",0x98,0x3060);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar4 = (int)((uint)*param_2 - (uint)*(ushort *)(local_38[0][3] + 8)) /
          (int)(uint)*(ushort *)(local_38[0][1] + 2) & 0xffff;
  iVar2 = FUN_0802b658(param_3,&local_30);
  if (iVar2 != 0) {
    ((code*)DAT_0804cd60)("pm_smps_driver.c",0xa0,0x3060);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (((local_30 == 8) && (local_2c == 1)) && (3 < uVar4)) {
    uVar4 = uVar4 - 1 & 0xffff;
  }
  if ((uint)local_38[0][2] <= uVar4) {
    ((code*)DAT_0804cd60)("pm_smps_driver.c",0xa9,0x3060);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  *(char *)(local_38[0][3] + uVar4 * 0xc + 10) = (char)param_2[1];
  *(ushort *)(local_38[0][3] + uVar4 * 0xc + 8) = *param_2;
  cVar1 = (char)param_2[1];
  iVar2 = 0;
  if (cVar1 == '\x03') {
    uVar3 = 7;
LAB_0802e77e:
    iVar2 = FUN_0802e824(uVar3);
  }
  else {
    if (cVar1 == '\x1c') {
      if (*(char *)((int)param_2 + 3) == '\b') {
        uVar3 = 6;
      }
      else {
        if (*(char *)((int)param_2 + 3) != '\t') goto LAB_0802e782;
        uVar3 = 0x27;
      }
      goto LAB_0802e77e;
    }
    if (cVar1 == '\"') {
      cVar1 = *(char *)((int)param_2 + 3);
      if (((cVar1 == '\r') || (cVar1 == '\x0e')) || (cVar1 == '\x0f')) {
        uVar3 = 0x30;
      }
      else {
        if (cVar1 != '\x10') goto LAB_0802e782;
        uVar3 = 0x32;
      }
      goto LAB_0802e77e;
    }
  }
LAB_0802e782:
  *(int *)(local_38[0][3] + uVar4 * 0xc) = iVar2;
  if (iVar2 == 0) {
    ((code*)DAT_0804cd60)("pm_smps_driver.c",0xb5,0x3060);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  cVar1 = (char)param_2[1];
  iVar2 = 0;
  if (cVar1 == '\x03') {
    uVar3 = 0xf;
  }
  else if (cVar1 == '\x1c') {
    if (*(char *)((int)param_2 + 3) == '\b') {
      uVar3 = 0xe;
    }
    else {
      if (*(char *)((int)param_2 + 3) != '\t') goto LAB_0802e7e0;
      uVar3 = 0x28;
    }
  }
  else {
    if (cVar1 != '\"') goto LAB_0802e7e0;
    cVar1 = *(char *)((int)param_2 + 3);
    if (((cVar1 == '\r') || (cVar1 == '\x0e')) || (cVar1 == '\x0f')) {
      uVar3 = 0x2f;
    }
    else {
      if (cVar1 != '\x10') goto LAB_0802e7e0;
      uVar3 = 0x31;
    }
  }
  iVar2 = FUN_0802e824(uVar3);
LAB_0802e7e0:
  *(int *)(local_38[0][3] + uVar4 * 0xc + 4) = iVar2;
  if (iVar2 != 0) {
    return;
  }
  ((code*)DAT_0804cd60)("pm_smps_driver.c",0xba,0x3060);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x0802e824 */
undefined4 FUN_0802e824(param_1)
undefined4 param_1;
{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = thunk_FUN_080106aa(&DAT_0804dc18,0,param_1,&DAT_080585ec);
  uVar2 = 0;
  if (iVar1 == 0) {
    uVar2 = DAT_080585f4;
  }
  return uVar2;
}




/* 0x0802e848 */
uint FUN_0802e848(param_1)
undefined4 param_1;
{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  iVar1 = thunk_FUN_080106aa(&DAT_0804dc10,0,param_1,&DAT_080585e0);
  if (iVar1 == 0) {
    uVar2 = DAT_080585e8 & 0xff;
  }
  return uVar2;
}




/* 0x0802e86c */
undefined4 FUN_0802e86c(param_1)
undefined4 param_1;
{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = thunk_FUN_080106aa(&DAT_0804dc10,0,param_1,&DAT_080585e0);
  uVar2 = 0;
  if (iVar1 == 0) {
    uVar2 = DAT_080585e8;
  }
  return uVar2;
}




/* 0x0802e890 */
void pmic_common_init()
{
  undefined1 uVar1;
  int iVar2;
  char *pcVar3;
  
  pcVar3 = (char *)0x0;
  uVar1 = FUN_0802b68c(0);
  if (true) {
    switch(uVar1) {
    case 8:
      pcVar3 = "/boot/pmd9x45";
      break;
    case 9:
      pcVar3 = "/boot/pm8994";
      break;
    case 0xb:
      pcVar3 = "/boot/pm8916";
      break;
    case 0xd:
      pcVar3 = "/boot/pm8909";
      break;
    case 0x10:
      pcVar3 = "/boot/pm8950";
    }
  }
  if (pcVar3 == (char *)0x0) {
    FUN_0800b614(0,1,
                 "PMIC:  Initialization failed to identify PMIC device!  PMIC Model listed as: %d.",
                 uVar1);
    return;
  }
  iVar2 = dal_device_attach(pcVar3,&DAT_0804dc10);
  if (iVar2 != 0) {
    FUN_0800b614(0,1,"PMIC:  Initialization failed hProp_target handle retrieval!");
  }
  iVar2 = dal_device_attach("/boot/pmic/common",&DAT_0804dc18);
  if (iVar2 == 0) {
    return;
  }
  FUN_0800b614(0,1,"PMIC:  Initialization failed hProp_common handle retrieval!");
  return;
}




/* 0x0802e9f0 */
undefined4 FUN_0802e9f0(param_1, param_2)
undefined4 * param_1; undefined2 * param_2;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  
  iVar1 = DAT_0804cd58;
  local_14 = DAT_0804cd58;
  local_1c = 0;
  local_18 = 0;
  if (param_1 == (undefined4 *)0x0) {
    uVar2 = 0x6b;
  }
  else {
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)((int)param_2 + 3) = 0;
    *(undefined1 *)(param_2 + 2) = 0;
    *(undefined1 *)((int)param_2 + 5) = 0;
    *(undefined1 *)(param_2 + 3) = 0;
    *(undefined1 *)((int)param_2 + 7) = 0;
    FUN_0802b20e(*param_1,*param_2,7,&local_1c,0);
    if ((_GHIDRA_FIELD(local_18, 1, byte) == _GHIDRA_FIELD(local_18, 2, byte)) || ((char)local_18 == '\0')) {
      uVar2 = 0x30;
    }
    else {
      *(char *)(param_2 + 1) = (char)local_18;
      *(char *)((int)param_2 + 3) = _GHIDRA_FIELD(local_18, 1, byte);
      *(undefined1 *)(param_2 + 3) = _GHIDRA_FIELD(local_1c, 1, byte);
      *(undefined1 *)((int)param_2 + 7) = (undefined1)local_1c;
      *(undefined1 *)(param_2 + 2) = _GHIDRA_FIELD(local_1c, 3, byte);
      *(undefined1 *)((int)param_2 + 5) = _GHIDRA_FIELD(local_1c, 2, byte);
      uVar2 = 0;
    }
  }
  if (local_14 != iVar1) {
    FUN_08010960();
  }
  return uVar2;
}




