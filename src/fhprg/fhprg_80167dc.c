/* Auto-generated: fhprg_80167dc.c */
/* Functions: 27 */
#include "globals.h"

/* 0x080167dc */
void FUN_080167dc()
{
  int iVar1;
  uint uVar2;
  undefined1 auStack_70 [96];
  int local_10;
  
  iVar1 = DAT_0804cd58;
  local_10 = DAT_0804cd58;
  uVar2 = thunk_FUN_0800a784();
  snprintf_buf(auStack_70,0x60,"DDR Frequency, %d MHz",uVar2 / 1000);
  FUN_08016adc(auStack_70,0xffffffff,0x53);
  if (local_10 != iVar1) {
    FUN_08010960();
    return;
  }
  return;
}




/* 0x08016838 */
void FUN_08016838()
{
  FUN_0800f674(DAT_0804cf80);
  return;
}




/* 0x08016844 */
undefined4 FUN_08016844(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  undefined4 uVar1;
  
  uVar1 = FUN_0801610c();
  FUN_080169e0(param_2,uVar1,0x44,0);
  FUN_08016afc(param_2,uVar1,0x44,0);
  return uVar1;
}




/* 0x0801684a */
undefined4 FUN_0801684a(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  undefined4 uVar1;
  
  uVar1 = FUN_0801610c();
  FUN_080169e0(param_2,uVar1,0x44,param_3);
  FUN_08016afc(param_2,uVar1,0x44,param_3);
  return uVar1;
}




/* 0x08016872 */
void FUN_08016872()
{
  return;
}




/* 0x08016874 */
void FUN_08016874(param_1)
int param_1;
{
  FUN_08016838();
  if (param_1 == -0x2e3d4c5d) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return;
}




/* 0x0801688c */
undefined4 FUN_0801688c()
{
  return DAT_0804cdfc;
}




/* 0x0801689c */
void FUN_0801689c()
{
  int iVar1;
  undefined1 auStack_70 [96];
  int local_10;
  
  iVar1 = DAT_0804cd58;
  local_10 = DAT_0804cd58;
  snprintf_buf(auStack_70,0x60,&DAT_0801690c,"QC_IMAGE_VERSION_STRING=BOOT.BF.3.1.2-00023");
  FUN_08016adc(auStack_70,0xffffffff,0x53);
  snprintf_buf(auStack_70,0x60,&DAT_0801690c,"IMAGE_VARIANT_STRING=DAADANAZA");
  FUN_08016adc(auStack_70,0xffffffff,0x53,0);
  snprintf_buf(auStack_70,0x60,&DAT_0801690c,"OEM_IMAGE_VERSION_STRING=vBuild1PFW2");
  FUN_08016adc(auStack_70,0xffffffff,0x53,0);
  if (local_10 != iVar1) {
    FUN_08010960();
    return;
  }
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08016918 */
void FUN_08016918(param_1)
int param_1;
{
  int iVar1;
  undefined1 auStack_70 [96];
  int local_10;
  
  DAT_0804cdfc = *(undefined4 *)(param_1 + 8);
  FUN_08016944(param_1);
  FUN_080163e8(param_1);
  FUN_080169a4();
  FUN_0801689c();
  iVar1 = DAT_0804cd58;
  local_10 = DAT_0804cd58;
  snprintf_buf(auStack_70,0x60,"Boot Config, 0x%08x",_DAT_0005e02c & 0x3ff);
  FUN_08016adc(auStack_70,0xffffffff,0x53);
  if (local_10 != iVar1) {
    FUN_08010960();
    return;
  }
  return;
}




/* 0x08016944 */
void FUN_08016944(param_1)
undefined4 * param_1;
{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  puVar1 = (undefined4 *)FUN_0801688c();
  if ((puVar1 != (undefined4 *)0x0) && (0x85 < (uint)param_1[1])) {
    puVar1[2] = param_1[1];
    *puVar1 = *param_1;
    uVar2 = *param_1;
    puVar1[1] = uVar2;
    puVar1[3] = 1;
    FUN_08007f08(uVar2,0,param_1[1]);
    FUN_08016c38(&DAT_0804cee0,2);
    FUN_08016c38(s_Format__Log_Type___Time_microsec_0804cee7,0x3b);
    FUN_08016c38(&DAT_0804cee0,2);
    FUN_08016c38(s_Log_Type__B___Since_Boot_Power_O_0804cf23,0x44);
    FUN_08016c38(&DAT_0804cee0,2);
    return;
  }
  return;
}




/* 0x080169a4 */
undefined4 FUN_080169a4()
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (false) {
    uVar2 = 0x1a3;
    uVar3 = 0;
  }
  else {
    DAT_0804cf80 = (undefined4 *)0x0;
    iVar1 = uart_init();
    if (iVar1 == 1) {
      uVar2 = 0x1ab;
      uVar3 = 0;
    }
    else if (true) {
      if (DAT_0804e234 == '\x01') {
        DAT_0804cf80 = &DAT_0804e230;
        return 0;
      }
      if (DAT_0804e22c == 0) {
        uVar3 = 1;
        uVar2 = 0x1c0;
      }
      else {
        DAT_0804e230 = DAT_0804e22c;
        DAT_0804e234 = '\x01';
        DAT_0804e258 = 0;
        iVar1 = FUN_0800f7bc(&DAT_0804e230);
        if (iVar1 == 0) {
          iVar1 = FUN_08019d3c(&DAT_0804e230);
          if (iVar1 == 0) {
            iVar1 = FUN_0800f9dc(&DAT_0804e230);
            if (iVar1 == 0) {
              FUN_0803156c(&DAT_0804e230);
              DAT_0804cf80 = &DAT_0804e230;
              return 0;
            }
            uVar2 = 0x1da;
          }
          else {
            uVar2 = 0x1d4;
          }
          FUN_08038460(10,uVar2,0,0,0,0);
          FUN_0800f674(&DAT_0804e230);
          return 1;
        }
        uVar3 = 0;
        uVar2 = 0x1cf;
      }
    }
    else {
      uVar3 = 1;
      uVar2 = 0x1c9;
    }
  }
  FUN_08038460(10,uVar2,uVar3,0,0,0);
  return 1;
}




/* 0x080169b0 */
void boot_log_message(param_1)
undefined4 param_1;
{
  undefined4 uVar1;
  
  uVar1 = FUN_08016180();
  FUN_080169e0(param_1,uVar1,0x42,0);
  FUN_08016afc(param_1,uVar1,0x42,0);
  return;
}




/* 0x080169b6 */
void FUN_080169b6(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  undefined4 uVar1;
  
  uVar1 = FUN_08016180();
  FUN_080169e0(param_1,uVar1,0x42,param_2);
  FUN_08016afc(param_1,uVar1,0x42,param_2);
  return;
}




/* 0x080169e0 */
undefined8 FUN_080169e0(param_1, param_2, param_3, param_4)
int param_1; uint param_2; undefined4 param_3; int param_4;
{
  int *piVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uStack_28;
  int iStack_24;
  
  uStack_28 = param_3;
  iStack_24 = param_4;
  piVar1 = (int *)FUN_0801688c();
  iVar4 = 0;
  iVar6 = 0;
  iVar5 = 0;
  if (param_1 != 0) {
    iVar4 = FUN_080194dc(param_1);
  }
  if (param_4 != 0) {
    iVar6 = FUN_080194dc(param_4);
  }
  if (param_2 != 0xffffffff) {
    iVar5 = 0xc;
  }
  iVar5 = iVar5 + iVar4 + 6;
  if (param_4 != 0) {
    iVar5 = iVar5 + iVar6 + 3;
  }
  if ((piVar1 != (int *)0x0) && (piVar1[3] == 1)) {
    if ((uint)piVar1[2] <= (uint)(iVar5 + (piVar1[1] - *piVar1))) {
      piVar1[1] = *piVar1;
    }
    FUN_08016c38(&uStack_28,1);
    FUN_08016c38(&DAT_0804cee3,3);
    if (param_2 != 0xffffffff) {
      if (param_2 < 1000000000) {
        iVar5 = 8;
        uVar3 = param_2;
        do {
          (&DAT_08052ca8)[iVar5] = (char)uVar3 + (char)(uVar3 / 10) * -10 + '0';
          iVar5 = iVar5 + -1;
          uVar3 = uVar3 / 10;
        } while (-1 < iVar5);
        for (iVar5 = 0; ((&DAT_08052ca8)[iVar5] == '0' && (iVar5 < 8)); iVar5 = iVar5 + 1) {
          (&DAT_08052ca8)[iVar5] = 0x20;
        }
        pcVar2 = &DAT_08052ca8;
      }
      else {
        pcVar2 = s_OVERFLOW_0804cf68;
      }
      FUN_08016c38(pcVar2,9);
      FUN_08016c38(&DAT_0804cee3,3);
    }
    if (param_1 != 0) {
      FUN_08016c38(param_1,iVar4);
    }
    if (param_4 != 0) {
      FUN_08016c38(&DAT_0804cee3,3);
      FUN_08016c38(param_4,iVar6);
    }
    FUN_08016c38(&DAT_0804cee0,2);
  }
  return CONCAT44(param_2,param_1);
}




/* 0x08016adc */
undefined8 FUN_08016adc(param_1, param_2, param_3, param_4)
int param_1; uint param_2; undefined4 param_3; int param_4;
{
  int iVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined4 uStack_28;
  int iStack_24;
  
  FUN_080169e0();
  iVar6 = 0;
  iVar5 = 0;
  if (param_1 != 0) {
    uStack_28 = param_3;
    iStack_24 = param_4;
    iVar1 = FUN_080194dc();
    if (param_4 != 0) {
      iVar6 = FUN_080194dc(param_4);
    }
    if (param_2 != 0xffffffff) {
      iVar5 = 0xc;
    }
    iVar5 = iVar5 + iVar1 + 6;
    if (param_4 != 0) {
      iVar5 = iVar5 + iVar6 + 3;
    }
    if (DAT_0804cf74 == '\0') {
      FUN_08016cc4(&DAT_0804cf75,2);
      FUN_08016cc4(s_Format__Log_Type___Time_microsec_0804cf84,0x3b);
      FUN_08016cc4(&DAT_0804cf75,2);
      FUN_08016cc4(s_Log_Type__B___Since_Boot_Power_O_0804cfc0,0x44);
      FUN_08016cc4(&DAT_0804cf75,2);
      thunk_FUN_0800fa46(DAT_0804cf80,&DAT_08052cba,0x85);
      DAT_0804cf74 = '\x01';
    }
    FUN_08007f08(&DAT_08052cba,0,0x200);
    DAT_0804cf7c = &DAT_08052cba;
    FUN_08016cc4(&uStack_28,1);
    FUN_08016cc4(&DAT_0804cf78,3);
    if (param_2 != 0xffffffff) {
      if (param_2 < 1000000000) {
        iVar2 = 8;
        uVar4 = param_2;
        do {
          (&DAT_08052cb1)[iVar2] = (char)uVar4 + (char)(uVar4 / 10) * -10 + '0';
          iVar2 = iVar2 + -1;
          uVar4 = uVar4 / 10;
        } while (-1 < iVar2);
        for (iVar2 = 0; ((&DAT_08052cb1)[iVar2] == '0' && (iVar2 < 8)); iVar2 = iVar2 + 1) {
          (&DAT_08052cb1)[iVar2] = 0x20;
        }
        pcVar3 = &DAT_08052cb1;
      }
      else {
        pcVar3 = s_OVERFLOW_0804d005;
      }
      FUN_08016cc4(pcVar3,9);
      FUN_08016cc4(&DAT_0804cf78,3);
    }
    FUN_08016cc4(param_1,iVar1);
    if (param_4 != 0) {
      FUN_08016cc4(&DAT_0804cf78,3);
      FUN_08016cc4(param_4,iVar6);
    }
    FUN_08016cc4(&DAT_0804cf75,2);
    thunk_FUN_0800fa46(DAT_0804cf80,&DAT_08052cba,iVar5);
  }
  return CONCAT44(param_2,param_1);
}




/* 0x08016afc */
undefined8 FUN_08016afc(param_1, param_2, param_3, param_4)
int param_1; uint param_2; undefined4 param_3; int param_4;
{
  int iVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined4 uStack_28;
  int iStack_24;
  
  iVar6 = 0;
  iVar5 = 0;
  if (param_1 != 0) {
    uStack_28 = param_3;
    iStack_24 = param_4;
    iVar1 = FUN_080194dc();
    if (param_4 != 0) {
      iVar6 = FUN_080194dc(param_4);
    }
    if (param_2 != 0xffffffff) {
      iVar5 = 0xc;
    }
    iVar5 = iVar5 + iVar1 + 6;
    if (param_4 != 0) {
      iVar5 = iVar5 + iVar6 + 3;
    }
    if (DAT_0804cf74 == '\0') {
      FUN_08016cc4(&DAT_0804cf75,2);
      FUN_08016cc4(s_Format__Log_Type___Time_microsec_0804cf84,0x3b);
      FUN_08016cc4(&DAT_0804cf75,2);
      FUN_08016cc4(s_Log_Type__B___Since_Boot_Power_O_0804cfc0,0x44);
      FUN_08016cc4(&DAT_0804cf75,2);
      thunk_FUN_0800fa46(DAT_0804cf80,&DAT_08052cba,0x85);
      DAT_0804cf74 = '\x01';
    }
    FUN_08007f08(&DAT_08052cba,0,0x200);
    DAT_0804cf7c = &DAT_08052cba;
    FUN_08016cc4(&uStack_28,1);
    FUN_08016cc4(&DAT_0804cf78,3);
    if (param_2 != 0xffffffff) {
      if (param_2 < 1000000000) {
        iVar2 = 8;
        uVar4 = param_2;
        do {
          (&DAT_08052cb1)[iVar2] = (char)uVar4 + (char)(uVar4 / 10) * -10 + '0';
          iVar2 = iVar2 + -1;
          uVar4 = uVar4 / 10;
        } while (-1 < iVar2);
        for (iVar2 = 0; ((&DAT_08052cb1)[iVar2] == '0' && (iVar2 < 8)); iVar2 = iVar2 + 1) {
          (&DAT_08052cb1)[iVar2] = 0x20;
        }
        pcVar3 = &DAT_08052cb1;
      }
      else {
        pcVar3 = s_OVERFLOW_0804d005;
      }
      FUN_08016cc4(pcVar3,9);
      FUN_08016cc4(&DAT_0804cf78,3);
    }
    FUN_08016cc4(param_1,iVar1);
    if (param_4 != 0) {
      FUN_08016cc4(&DAT_0804cf78,3);
      FUN_08016cc4(param_4,iVar6);
    }
    FUN_08016cc4(&DAT_0804cf75,2);
    thunk_FUN_0800fa46(DAT_0804cf80,&DAT_08052cba,iVar5);
  }
  return CONCAT44(param_2,param_1);
}




/* 0x08016c38 */
void FUN_08016c38(param_1, param_2)
undefined4 param_1; int param_2;
{
  int iVar1;
  
  iVar1 = FUN_0801688c();
  FUN_08030b34(*(undefined4 *)(iVar1 + 4),param_1,param_2);
  *(int *)(iVar1 + 4) = *(int *)(iVar1 + 4) + param_2;
  return;
}




/* 0x08016c58 */
void FUN_08016c58(param_1)
undefined4 param_1;
{
  FUN_08016760(param_1);
  DAT_0804cdfc = param_1;
  return;
}




/* 0x08016c74 */
void FUN_08016c74(param_1)
undefined4 param_1;
{
  DAT_0804cdfc = param_1;
  return;
}




/* 0x08016c80 */
void FUN_08016c80(param_1)
undefined4 param_1;
{
  if (DAT_0804cdfc != 0) {
    *(undefined4 *)(DAT_0804cdfc + 0x10) = param_1;
  }
  return;
}




/* 0x08016c94 */
undefined4 FUN_08016c94(param_1)
undefined4 param_1;
{
  undefined4 uVar1;
  
  uVar1 = FUN_080193c4();
  FUN_080169e0(param_1,uVar1,0x44,0);
  FUN_08016afc(param_1,uVar1,0x44,0);
  return uVar1;
}




/* 0x08016c9a */
undefined4 FUN_08016c9a(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  undefined4 uVar1;
  
  uVar1 = FUN_080193c4();
  FUN_080169e0(param_1,uVar1,0x44,param_2);
  FUN_08016afc(param_1,uVar1,0x44,param_2);
  return uVar1;
}




/* 0x08016cc4 */
void FUN_08016cc4(param_1, param_2)
undefined4 param_1; int param_2;
{
  FUN_08030b34(DAT_0804cf7c,param_1,param_2);
  DAT_0804cf7c = DAT_0804cf7c + param_2;
  return;
}




/* 0x08016ce0 */
undefined4 FUN_08016ce0(param_1, param_2, param_3, param_4)
int param_1; int param_2; uint param_3; uint param_4;
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar2 = 0;
  uVar3 = 1;
  uVar1 = 0;
  do {
    if ((*(uint *)(param_1 + uVar1 * 4) & 1) != 0) {
      uVar2 = uVar2 + 1;
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 < 0x1000);
  if (param_4 < uVar2) {
    uVar3 = 0;
  }
  else {
    uVar1 = 0;
    DAT_0804cd20 = param_3;
    DAT_0804cd24 = param_4;
    do {
      *(undefined4 *)(param_2 + uVar1 * 4) = *(undefined4 *)(param_1 + uVar1 * 4);
      uVar2 = *(uint *)(param_1 + uVar1 * 4);
      if ((uVar2 & 1) != 0) {
        FUN_08030b34(DAT_0804cd20,uVar2 & 0xfffffc00,0x400);
        *(uint *)(param_2 + uVar1 * 4) =
             DAT_0804cd20 & 0xfffffc00 | *(uint *)(param_1 + uVar1 * 4) & 0x3ff;
        DAT_0804cd24 = DAT_0804cd24 - 1;
        DAT_0804cd20 = DAT_0804cd20 + 0x400;
      }
      uVar1 = uVar1 + 1;
    } while (uVar1 < 0x1000);
  }
  return uVar3;
}




/* 0x08016d68 */
undefined4 FUN_08016d68(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar3 = 1;
  uVar2 = 0;
  for (iVar1 = param_2; *(uint *)(iVar1 + 4) != 0xffffffff; iVar1 = iVar1 + 0x20) {
    if (((*(int *)(iVar1 + 0xc) == 2) || (*(int *)(iVar1 + 0xc) == 3)) &&
       ((*(uint *)(param_1 + (*(uint *)(iVar1 + 4) >> 0x14) * 4) & 1) == 0)) {
      uVar2 = uVar2 + 1;
    }
  }
  if (DAT_0804cd24 < uVar2) {
    uVar3 = 0;
  }
  else {
    for (; *(int *)(param_2 + 4) != -1; param_2 = param_2 + 0x20) {
      if ((*(int *)(param_2 + 0xc) == 0) || (*(int *)(param_2 + 0xc) == 1)) {
        FUN_08027c2c(param_1,param_2);
      }
      else {
        FUN_08027c78(param_1,param_2);
      }
    }
    FUN_08007b30();
  }
  return uVar3;
}




/* 0x08016dd4 */
undefined4 thunk_FUN_08016dd4()
{
  FUN_08016dd4();
  return 0;
}




/* 0x08016dd4 */
undefined4 FUN_08016dd4(param_1, param_2)
int param_1; int param_2;
{
  if ((*(int *)(param_2 + 0xc) == 0) || (*(int *)(param_2 + 0xc) == 1)) {
    FUN_08027c2c(param_1);
  }
  else {
    if (DAT_0804cd24 < ((*(uint *)(param_1 + (*(uint *)(param_2 + 4) >> 0x14) * 4) & 1) == 0)) {
      return 0;
    }
    FUN_08027c78(param_1);
  }
  FUN_08007b30();
  return 1;
}




