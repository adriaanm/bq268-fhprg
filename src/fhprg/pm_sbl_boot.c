/* Auto-generated: pm_sbl_boot.c */
/* Functions: 2 */
#include "globals.h"

/* 0x0802b2d8 */
uint thunk_pm_device_init_core()
{
  int iVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int iStack_60;
  int aiStack_5c [4];
  undefined1 auStack_4c [12];
  int iStack_40;
  int aiStack_20 [2];
  
  uVar11 = 0;
  aiStack_5c[0] = 0;
  aiStack_5c[1] = 0;
  aiStack_5c[2] = 0;
  aiStack_5c[3] = 0;
  iVar1 = FUN_0800e614(1);
  if (iVar1 != 0) {
    uVar11 = 9;
  }
  FUN_0800b604(0);
  if ((DAT_0804d39c != 0) ||
     (iVar2 = FUN_0800b7ea(0,0x200006f,0x10000,&DAT_0804d39c), iVar1 = 0, iVar2 == 0)) {
    if ((DAT_0804d39c & 1) == 0) {
      (**(code **)(*(int *)(DAT_0804d39c + 4) + 0x38))(DAT_0804d39c,0);
      iVar1 = iStack_60;
    }
    else {
      (**(code **)(*(int *)((DAT_0804d39c & 0xfffffffe) + 4) + 0x2c))
                (0xe,DAT_0804d39c & 0xfffffffe,0,&iStack_60);
      iVar1 = iStack_60;
    }
  }
  if (iVar1 == 0x3a) {
    boot_log_message("pm_device_init, TEST - MSM8909 detected");
    uVar3 = FUN_0800b7ea(0,0x2000139,0x10000,aiStack_20);
    if (uVar3 == 0) {
      uVar3 = (**(code **)(*(int *)(aiStack_20[0] + 4) + 0x28))(aiStack_20[0],aiStack_5c);
      if (uVar3 == 0) goto LAB_0802b340;
      pcVar4 = "pm_device_init, ERROR DALPlatform Failed";
    }
    else {
      pcVar4 = "pm_device_init, ERROR DALAttach Failed";
    }
    boot_log_message(pcVar4);
    uVar11 = uVar11 | uVar3 & 0xff;
  }
  else {
    boot_log_message("pm_device_init, WARNING - CHIPINFO is NOT MSM8909");
  }
LAB_0802b340:
  if (aiStack_5c[0] == 1) {
    if (aiStack_5c[2] == 2) goto LAB_0802b3c6;
  }
  else if (aiStack_5c[0] == 8) {
    if ((aiStack_5c[2] == 2) || (aiStack_5c[2] == 4)) goto LAB_0802b3c6;
  }
  else if ((aiStack_5c[0] == 0x15) && (aiStack_5c[2] == 1)) {
LAB_0802b3c6:
    uVar3 = FUN_0802ea74("/boot/pm8916");
    pcVar4 = "pm_device_init, INFO - PM8916 is selected";
    goto LAB_0802b3ac;
  }
  uVar3 = FUN_0802ea74("/boot/pm8909");
  pcVar4 = "pm_device_init, INFO - PM8909 is selected";
LAB_0802b3ac:
  boot_log_message(pcVar4);
  iVar1 = FUN_0800e51c();
  if (iVar1 == 0) {
    uVar5 = FUN_0802eb4c();
    FUN_0802b190();
    pmic_common_init();
    uVar6 = FUN_0802d0b8();
    uVar7 = FUN_0802d920();
    pm_set_val();
    uVar8 = FUN_0802cb2c();
    FUN_0802cfe0();
    iStack_60 = 1;
    uVar9 = FUN_0802d228(0,0,0x2810,2000);
    iStack_60 = 1;
    uVar10 = FUN_0802d228(0,2,0x2810,2000);
    uVar10 = uVar10 | uVar9;
    iVar1 = FUN_0802b68c(0);
    if ((iVar1 == 0xd) && (iVar1 = FUN_0802b5dc(0,auStack_4c), iVar1 == 0)) {
      uVar9 = FUN_0802b248(0,0x141,(uint)(iStack_40 << 0x10) >> 0x18,1);
      uVar10 = uVar10 | uVar9;
    }
    return uVar10 | uVar8 | uVar7 | uVar6 | uVar5 | uVar3 | uVar11;
  }
  ((code*)DAT_0804cd60)("pm_sbl_boot.c",0xc2,0x3060);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x0802b2d8 */
uint pm_device_init_core()
{
  int iVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int local_60;
  int local_5c [4];
  undefined1 auStack_4c [12];
  int local_40;
  int local_20 [2];
  
  uVar11 = 0;
  local_5c[0] = 0;
  local_5c[1] = 0;
  local_5c[2] = 0;
  local_5c[3] = 0;
  iVar1 = FUN_0800e614(1);
  if (iVar1 != 0) {
    uVar11 = 9;
  }
  FUN_0800b604(0);
  if ((DAT_0804d39c != 0) ||
     (iVar2 = FUN_0800b7ea(0,0x200006f,0x10000,&DAT_0804d39c), iVar1 = 0, iVar2 == 0)) {
    if ((DAT_0804d39c & 1) == 0) {
      (**(code **)(*(int *)(DAT_0804d39c + 4) + 0x38))(DAT_0804d39c,0);
      iVar1 = local_60;
    }
    else {
      (**(code **)(*(int *)((DAT_0804d39c & 0xfffffffe) + 4) + 0x2c))
                (0xe,DAT_0804d39c & 0xfffffffe,0,&local_60);
      iVar1 = local_60;
    }
  }
  if (iVar1 == 0x3a) {
    boot_log_message("pm_device_init, TEST - MSM8909 detected");
    uVar3 = FUN_0800b7ea(0,0x2000139,0x10000,local_20);
    if (uVar3 == 0) {
      uVar3 = (**(code **)(*(int *)(local_20[0] + 4) + 0x28))(local_20[0],local_5c);
      if (uVar3 == 0) goto LAB_0802b340;
      pcVar4 = "pm_device_init, ERROR DALPlatform Failed";
    }
    else {
      pcVar4 = "pm_device_init, ERROR DALAttach Failed";
    }
    boot_log_message(pcVar4);
    uVar11 = uVar11 | uVar3 & 0xff;
  }
  else {
    boot_log_message("pm_device_init, WARNING - CHIPINFO is NOT MSM8909");
  }
LAB_0802b340:
  if (local_5c[0] == 1) {
    if (local_5c[2] == 2) goto LAB_0802b3c6;
  }
  else if (local_5c[0] == 8) {
    if ((local_5c[2] == 2) || (local_5c[2] == 4)) goto LAB_0802b3c6;
  }
  else if ((local_5c[0] == 0x15) && (local_5c[2] == 1)) {
LAB_0802b3c6:
    uVar3 = FUN_0802ea74("/boot/pm8916");
    pcVar4 = "pm_device_init, INFO - PM8916 is selected";
    goto LAB_0802b3ac;
  }
  uVar3 = FUN_0802ea74("/boot/pm8909");
  pcVar4 = "pm_device_init, INFO - PM8909 is selected";
LAB_0802b3ac:
  boot_log_message(pcVar4);
  iVar1 = FUN_0800e51c();
  if (iVar1 == 0) {
    uVar5 = FUN_0802eb4c();
    FUN_0802b190();
    pmic_common_init();
    uVar6 = FUN_0802d0b8();
    uVar7 = FUN_0802d920();
    pm_set_val();
    uVar8 = FUN_0802cb2c();
    FUN_0802cfe0();
    local_60 = 1;
    uVar9 = FUN_0802d228(0,0,0x2810,2000);
    local_60 = 1;
    uVar10 = FUN_0802d228(0,2,0x2810,2000);
    uVar10 = uVar10 | uVar9;
    iVar1 = FUN_0802b68c(0);
    if ((iVar1 == 0xd) && (iVar1 = FUN_0802b5dc(0,auStack_4c), iVar1 == 0)) {
      uVar9 = FUN_0802b248(0,0x141,(uint)(local_40 << 0x10) >> 0x18,1);
      uVar10 = uVar10 | uVar9;
    }
    return uVar10 | uVar8 | uVar7 | uVar6 | uVar5 | uVar3 | uVar11;
  }
  ((code*)DAT_0804cd60)("pm_sbl_boot.c",0xc2,0x3060);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




