/* Auto-generated: fhprg_8037820.c */
/* Functions: 77 */
#include "globals.h"

/* 0x08037820 */
void FUN_08037820()
{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = FUN_08037758(1);
  DAT_0804d1b4 = (int *)(iVar2 + DAT_0804d1c0);
  if (*(int *)(DAT_0804d1b8 + 0x80) != 1) {
    FUN_08015a50();
  }
  if (*(uint*)DAT_0804d1b4 != 1) {
    iVar3 = *(int *)(DAT_0804d1b8 + 0x84) + *(int *)(DAT_0804d1b8 + 0x88);
    ((uint*)&DAT_0804d1b4)[1] = iVar3;
    iVar2 = thunk_FUN_08037940();
    piVar1 = DAT_0804d1b4;
    ((uint*)&DAT_0804d1b4)[2] = iVar2 - iVar3;
    *piVar1 = 1;
  }
  return;
}




/* 0x08037868 */
undefined4 FUN_08037868()
{
  int iVar1;
  
  if (DAT_0804d1d0 == '\x03') {
    return 3;
  }
  FUN_080379bc();
  FUN_08037a34();
  iVar1 = FUN_08037758(2);
  DAT_0804d1b8 = iVar1 + DAT_0804d1c0;
  FUN_08037a0c();
  iVar1 = FUN_08037758(8);
  DAT_0804d1cc = iVar1 + DAT_0804d1c0;
  if (*(uint*)DAT_0804d1b4 != 1) {
    FUN_08015a50();
  }
  FUN_08037a30();
  iVar1 = FUN_08037758(7);
  FUN_08037bea(iVar1 + DAT_0804d1c0,0,8);
  FUN_08007bec();
  DAT_0804d1d0 = 3;
  iVar1 = FUN_08037bee(3,0xb2002,0xffff0000);
  if (iVar1 == 0) {
    FUN_08015a50();
  }
  if (((true) && (true)) && (true)) {
    DAT_08054290 = 0x60000;
    DAT_08054294 = FUN_080378f0(0x60000,0x4000);
    DAT_0805429c = 0x4000;
    DAT_080542a0 = 0x4000;
    DAT_08054298 = 0;
    return 0;
  }
  return 0xffffffff;
}




/* 0x080378ec */
int FUN_080378ec(param_1)
int param_1;
{
  if (param_1 == 0x60000) {
    param_1 = 0x60000;
  }
  return param_1;
}




/* 0x080378f0 */
int FUN_080378f0(param_1)
int param_1;
{
  if (param_1 == 0x60000) {
    param_1 = 0x60000;
  }
  return param_1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x080378fc */
int FUN_080378fc()
{
  if (DAT_0804d608 == -1) {
    DAT_0804d608 = _DAT_0193d000;
  }
  return DAT_0804d608;
}




/* 0x08037918 */
undefined4 FUN_08037918()
{
  return 0;
}




/* 0x0803791c */
int thunk_FUN_0803791c()
{
  int *piVar1;
  
  piVar1 = (int *)FUN_080378fc();
  if (((piVar1 != (int *)0x0) && (piVar1 != (int *)0xffffffff)) && (*piVar1 == 0x49494953)) {
    return piVar1[2];
  }
  return -0x78300000;
}




/* 0x0803791c */
int FUN_0803791c()
{
  int *piVar1;
  
  piVar1 = (int *)FUN_080378fc();
  if (((piVar1 != (int *)0x0) && (piVar1 != (int *)0xffffffff)) && (*piVar1 == 0x49494953)) {
    return piVar1[2];
  }
  return -0x78300000;
}




/* 0x08037940 */
int thunk_FUN_08037940()
{
  int *piVar1;
  
  piVar1 = (int *)FUN_080378fc();
  if (((piVar1 != (int *)0x0) && (piVar1 != (int *)0xffffffff)) && (*piVar1 == 0x49494953)) {
    return piVar1[1];
  }
  return 0x100000;
}




/* 0x08037940 */
int FUN_08037940()
{
  int *piVar1;
  
  piVar1 = (int *)FUN_080378fc();
  if (((piVar1 != (int *)0x0) && (piVar1 != (int *)0xffffffff)) && (*piVar1 == 0x49494953)) {
    return piVar1[1];
  }
  return 0x100000;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08037964 */
void FUN_08037964()
{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  
  iVar2 = FUN_08037748();
  iVar3 = FUN_080377b8();
  iVar1 = *(int *)(iVar2 + iVar3 + -0xff8) * 0x30;
  puVar4 = (undefined4 *)(iVar2 + iVar3 + iVar1 + -0xfe0);
  if (0x1000 < iVar1 + 0x30U) {
    FUN_08015a50();
  }
  *puVar4 = 0x49494953;
  puVar4[1] = 0x100000;
  puVar4[2] = 0x87d00000;
  puVar4[3] = 0;
  _DAT_0193d000 = puVar4;
  _DAT_0193d004 = 0;
  return;
}




/* 0x080379bc */
void FUN_080379bc()
{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (DAT_0804d1c0 == -1) {
    uVar1 = FUN_080377b8();
    uVar2 = FUN_0803779c();
    DAT_0804d1c0 = FUN_080378ec(uVar2,uVar1);
  }
  return;
}




/* 0x08037a0c */
void FUN_08037a0c()
{
  int iVar1;
  
  if ((DAT_0804d1b4 == -1) && (DAT_0804d1c0 != -1)) {
    iVar1 = FUN_08037758(1);
    DAT_0804d1b4 = iVar1 + DAT_0804d1c0;
  }
  return;
}




/* 0x08037a30 */
void FUN_08037a30()
{
  return;
}




/* 0x08037a34 */
void FUN_08037a34()
{
  if (DAT_0804d1ac == 0) {
    DAT_0804d1ac = FUN_08037918();
  }
  return;
}




/* 0x08037a4c */
void smem_init()
{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  undefined4 *puVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined1 auStack_38 [8];
  int local_30;
  undefined1 auStack_2c [8];
  
  uVar9 = 0x1000;
  iVar2 = dal_device_attach("/core/mproc/smem",auStack_2c);
  if ((iVar2 != 0) ||
     (iVar2 = thunk_FUN_080106aa(auStack_2c,"smem_toc_vers",0,auStack_38), iVar2 != 0)) {
    FUN_08015a50();
  }
  iVar2 = local_30;
  iVar3 = thunk_FUN_080106aa(auStack_2c,"smem_partitions",0,auStack_38);
  if (iVar3 != 0) {
    FUN_08015a50();
  }
  uVar8 = 0;
  iVar3 = 0;
  do {
    uVar8 = uVar8 + 1;
    piVar4 = (int *)(local_30 + iVar3 * 0x20);
    iVar3 = iVar3 + 1;
    uVar9 = uVar9 + *piVar4;
    if ((char)piVar4[2] == '\b') break;
  } while (*(char *)((int)piVar4 + 9) != '\b');
  if (*(uint *)(DAT_0804d1b4 + 8) < uVar9) {
    FUN_08015a50();
  }
  if (0x1000 < uVar8 * 0x30 + 0x20) {
    FUN_08015a50();
  }
  iVar3 = DAT_0804d1b4;
  *(int *)(DAT_0804d1b4 + 8) = *(int *)(DAT_0804d1b4 + 8) + -0x1000;
  puVar10 = (undefined4 *)(DAT_0804d1c0 + *(int *)(iVar3 + 4) + *(int *)(iVar3 + 8));
  puVar10[2] = uVar8;
  *puVar10 = 0x434f5424;
  puVar10[1] = iVar2;
  puVar10[8] = *(int *)(DAT_0804d1b4 + 8) + *(int *)(DAT_0804d1b4 + 4);
  puVar10[9] = 0x1000;
  puVar10[10] = 1;
  *(undefined2 *)(puVar10 + 0xb) = 8;
  *(undefined2 *)((int)puVar10 + 0x2e) = 8;
  puVar10[0xc] = 0;
  uVar9 = 0;
  do {
    uVar5 = uVar9 + 1;
    (puVar10 + 8)[uVar9 + 8] = 0;
    uVar9 = uVar5;
  } while (uVar5 < 4);
  for (uVar9 = 1; iVar2 = DAT_0804d1b4, uVar9 < uVar8; uVar9 = uVar9 + 1) {
    iVar3 = local_30 + uVar9 * 0x20;
    piVar4 = (int *)(iVar3 + -0x20);
    *(int *)(DAT_0804d1b4 + 8) = *(int *)(DAT_0804d1b4 + 8) - *piVar4;
    piVar1 = puVar10 + uVar9 * 0xc + 8;
    *piVar1 = *(int *)(iVar2 + 8) + *(int *)(iVar2 + 4);
    iVar2 = 0;
    puVar10[uVar9 * 0xc + 9] = *piVar4;
    puVar10[uVar9 * 0xc + 10] = *(undefined4 *)(iVar3 + -0x1c);
    *(ushort *)(puVar10 + uVar9 * 0xc + 0xb) = (ushort)*(byte *)(iVar3 + -0x18);
    *(ushort *)((int)puVar10 + uVar9 * 0x30 + 0x2e) = (ushort)*(byte *)(iVar3 + -0x17);
    puVar10[uVar9 * 0xc + 0xc] = *(undefined4 *)(iVar3 + -0x14);
    uVar5 = 0;
    do {
      uVar7 = uVar5 + 1;
      piVar1[uVar5 + 8] = piVar4[uVar5 + 4];
      iVar2 = iVar2 + piVar4[uVar5 + 4];
      uVar5 = uVar7;
    } while (uVar7 < 4);
    if (puVar10[uVar9 * 0xc + 9] != 0) {
      puVar6 = (undefined4 *)(*piVar1 + DAT_0804d1c0);
      *puVar6 = 0x54525024;
      *(ushort *)(puVar6 + 1) = (ushort)*(byte *)(iVar3 + -0x18);
      *(ushort *)((int)puVar6 + 6) = (ushort)*(byte *)(iVar3 + -0x17);
      iVar3 = *piVar4;
      puVar6[2] = iVar3 - iVar2;
      puVar6[3] = 0x20;
      puVar6[4] = iVar3 - iVar2;
    }
  }
  return;
}




/* 0x08037be8 */
void FUN_08037be8()
{
  return;
}




/* 0x08037bea */
void FUN_08037bea()
{
  return;
}




/* 0x08037bec */
void FUN_08037bec()
{
  return;
}




/* 0x08037bee */
undefined4 FUN_08037bee(param_1, param_2, param_3)
int param_1; uint param_2; uint param_3;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  
  uVar4 = 1;
  if ((param_1 == 3) || (param_1 - 0x6bU < 0x19)) {
    iVar1 = FUN_080373b8(param_1,0x80);
    if (iVar1 == 0) {
      FUN_08015a50();
    }
    *(uint *)(iVar1 + 0x1c) = *(uint *)(iVar1 + 0x1c) | param_2 & param_3;
    FUN_08007bec();
    uVar2 = 0;
    do {
      uVar3 = *(uint *)(iVar1 + uVar2 * 4) & param_3;
      if ((uVar3 != 0) && (uVar3 != (param_2 & param_3))) {
        uVar4 = 0;
        uVar2 = 0x20;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < 0x20);
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}




/* 0x08037c40 */
undefined4 FUN_08037c40(param_1)
int param_1;
{
  if (*(char *)(param_1 + 0x26) != '\b') {
    *(undefined1 *)(param_1 + 0x26) = 8;
    return 1;
  }
  return 0;
}




/* 0x08037c56 */
undefined4 FUN_08037c56(param_1)
int param_1;
{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 auStack_48 [4];
  int local_44;
  
  iVar3 = *(int *)(param_1 + (uint)*(byte *)(param_1 + 0x26) * 4 + 4);
  if (((iVar3 == 0) || (iVar1 = FUN_08033ee8(iVar3,auStack_48), iVar1 != 0)) ||
     (iVar3 = FUN_08033d44(iVar3,0,local_44 + -1), iVar3 != 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}




/* 0x08037c88 */
undefined4 FUN_08037c88()
{
  firehose_log("would have committed here");
  return 1;
}




/* 0x08037cb0 */
undefined4 FUN_08037cb0(param_1)
int param_1;
{
  int iVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  int *in_stack_00000000;
  
  iVar1 = FUN_08033fe0(0,0);
  if (iVar1 == 0) {
    firehose_log("Could not open User partition. Check card.");
    if (in_stack_00000000 != (int *)0x0) {
      *in_stack_00000000 = 1;
    }
  }
  else {
    FUN_08033d28();
    uVar4 = 0;
    do {
      iVar1 = param_1 + uVar4 * 4;
      if ((*(int *)(iVar1 + 4) != 0) && (iVar2 = FUN_08033d28(), iVar2 != 0)) {
        if (*in_stack_00000000 != 0) {
          *in_stack_00000000 = iVar2;
        }
        firehose_log("Failed to close all handles and deinit device");
        if (in_stack_00000000 == (int *)0x0) {
          return 0;
        }
        firehose_log("Deinit error %d",*in_stack_00000000);
        return 0;
      }
      *(undefined4 *)(iVar1 + 4) = 0;
      uVar4 = uVar4 + 1;
    } while (uVar4 < 8);
    iVar1 = FUN_08027328(param_1);
    if (iVar1 == 0) {
      pcVar3 = "Failed to Re-Initialize HW. Please Powercycle device and try";
    }
    else {
      if (false) {
        return 0;
      }
      iVar1 = FUN_08033fe0(0);
      if (iVar1 != 0) {
        firehose_log("FW Update Successful. FW Version updated from \'0x%X\' to \'0x%X\'",0,0);
        FUN_08033d28(iVar1);
        return 1;
      }
      pcVar3 = "Could not open User partition after reset. Check card.";
    }
    firehose_log(pcVar3);
    if (in_stack_00000000 != (int *)0x0) {
      *in_stack_00000000 = 1;
    }
  }
  return 0;
}




/* 0x08037e88 */
void FUN_08037e88(param_1)
int param_1;
{
  firehose_log("DRIVE4_SIZE_IN_KB %d",*(uint *)(param_1 + 0x30) >> 1);
  firehose_log("DRIVE5_SIZE_IN_KB %d",*(uint *)(param_1 + 0x34) >> 1);
  firehose_log("DRIVE6_SIZE_IN_KB %d",*(uint *)(param_1 + 0x38) >> 1);
  firehose_log("DRIVE7_SIZE_IN_KB %d",*(uint *)(param_1 + 0x3c) >> 1);
  firehose_log("ENH_SIZE %d",*(undefined4 *)(param_1 + 0x40));
  firehose_log("ENH_START_ADDR %d",*(undefined4 *)(param_1 + 0x44));
  firehose_log("GPP_ENH_FLAG %d",*(undefined1 *)(param_1 + 0x48));
  return;
}




/* 0x08037f64 */
undefined4 FUN_08037f64(param_1)
int param_1;
{
  int iVar1;
  undefined1 auStack_48 [4];
  undefined4 local_44;
  
  iVar1 = *(int *)(param_1 + (uint)*(byte *)(param_1 + 0x26) * 4 + 4);
  if ((iVar1 == 0) || (iVar1 = FUN_08033ee8(iVar1,auStack_48), iVar1 != 0)) {
    local_44 = 0;
  }
  return local_44;
}




/* 0x08037f88 */
undefined4 FUN_08037f88(param_1)
int param_1;
{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_48 [4];
  undefined4 local_44;
  undefined4 local_3c;
  undefined4 local_2c;
  
  iVar1 = *(int *)(param_1 + (uint)*(byte *)(param_1 + 0x26) * 4 + 4);
  uVar2 = 0;
  if (iVar1 != 0) {
    iVar1 = FUN_08033ee8(iVar1,auStack_48);
    if (iVar1 == 0) {
      firehose_log("num_partition_sectors=%d",local_44);
      firehose_log("SECTOR_SIZE_IN_BYTES=%d",local_3c);
      firehose_log("num_physical_partitions=%d",local_2c);
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}




/* 0x08038014 */
undefined4 FUN_08038014(param_1, param_2, param_3, param_4, param_5)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4; undefined2 param_5;
{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + (uint)*(byte *)(param_1 + 0x26) * 4 + 4);
  if ((iVar1 != 0) && (iVar1 = FUN_08034170(iVar1,param_3,param_2,param_5), iVar1 == 0)) {
    return 1;
  }
  return 0;
}




/* 0x0803803c */
undefined4 FUN_0803803c(param_1)
int param_1;
{
  int iVar1;
  
  if ((*(int *)(param_1 + (uint)*(byte *)(param_1 + 0x26) * 4 + 4) != 0) &&
     (iVar1 = FUN_08034202(), iVar1 == 0)) {
    return 1;
  }
  return 0;
}




/* 0x0803805c */
undefined4 FUN_0803805c(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_18;
  
  local_18 = param_4;
  iVar2 = FUN_08038236(param_2,"DRIVE4_SIZE_IN_KB");
  if (iVar2 == 0) {
    iVar2 = FUN_0803823e(param_3,&local_18);
    *(int *)(param_1 + 0x30) = iVar2 * 2;
    if ((char)local_18 != '\0') {
      return 1;
    }
    *(undefined4 *)(param_1 + 0x30) = 0;
  }
  else {
    iVar2 = FUN_08038236(param_2,"DRIVE5_SIZE_IN_KB");
    if (iVar2 == 0) {
      iVar2 = FUN_0803823e(param_3,&local_18);
      *(int *)(param_1 + 0x34) = iVar2 * 2;
      if ((char)local_18 != '\0') {
        return 1;
      }
      *(undefined4 *)(param_1 + 0x34) = 0;
    }
    else {
      iVar2 = FUN_08038236(param_2,"DRIVE6_SIZE_IN_KB");
      if (iVar2 == 0) {
        iVar2 = FUN_0803823e(param_3,&local_18);
        *(int *)(param_1 + 0x38) = iVar2 * 2;
        if ((char)local_18 != '\0') {
          return 1;
        }
        *(undefined4 *)(param_1 + 0x38) = 0;
      }
      else {
        iVar2 = FUN_08038236(param_2,"DRIVE7_SIZE_IN_KB");
        if (iVar2 == 0) {
          iVar2 = FUN_0803823e(param_3,&local_18);
          *(int *)(param_1 + 0x3c) = iVar2 * 2;
          if ((char)local_18 != '\0') {
            return 1;
          }
          *(undefined4 *)(param_1 + 0x3c) = 0;
        }
        else {
          iVar2 = FUN_08038236(param_2,"ENH_SIZE");
          if (iVar2 == 0) {
            uVar3 = FUN_0803823e(param_3,&local_18);
            *(undefined4 *)(param_1 + 0x40) = uVar3;
            if ((char)local_18 != '\0') {
              return 1;
            }
            *(undefined4 *)(param_1 + 0x40) = 0;
          }
          else {
            iVar2 = FUN_08038236(param_2,"ENH_START_ADDR");
            if (iVar2 == 0) {
              uVar3 = FUN_0803823e(param_3,&local_18);
              *(undefined4 *)(param_1 + 0x44) = uVar3;
              if ((char)local_18 != '\0') {
                return 1;
              }
              *(undefined4 *)(param_1 + 0x44) = 0;
            }
            else {
              iVar2 = FUN_08038236(param_2,"GPP_ENH_FLAG");
              if (iVar2 == 0) {
                uVar1 = FUN_0803823e(param_3,&local_18);
                *(undefined1 *)(param_1 + 0x48) = uVar1;
                if ((char)local_18 != '\0') {
                  return 1;
                }
                *(undefined1 *)(param_1 + 0x48) = 0;
              }
            }
          }
        }
      }
    }
  }
  return 0;
}




/* 0x080381d8 */
undefined4 mmc_write_wrapper(param_1, param_2, param_3, param_4, param_5, param_6, param_7)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4; undefined2 param_5; undefined4 param_6; int * param_7;
{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + (uint)*(byte *)(param_1 + 0x26) * 4 + 4);
  if (iVar1 != 0) {
    iVar1 = mmc_write_with_wp_check(iVar1,param_3,param_2,param_5);
    if (iVar1 == 0) {
      return 1;
    }
    if (param_7 != (int *)0x0) {
      *param_7 = iVar1;
    }
  }
  return 0;
}




/* 0x08038206 */
undefined4 FUN_08038206(param_1, param_2)
int param_1; uint param_2;
{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_50 [28];
  int local_34;
  
  if ((((param_2 < 8) && (param_2 != 3)) &&
      (iVar1 = FUN_08033ee8(*(undefined4 *)(param_1 + 4),auStack_50), iVar1 == 0)) &&
     (param_2 <= local_34 - 1U)) {
    uVar2 = 1;
    *(char *)(param_1 + 0x26) = (char)param_2;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}




/* 0x08038236 */
undefined4 FUN_08038236(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  strncmp_fh(param_1,param_2,0xffffffff);
  return 0;
}




/* 0x0803823e */
undefined4 FUN_0803823e(param_1, param_2, param_3, param_4)
char * param_1; undefined1 * param_2; undefined4 param_3; char * param_4;
{
  longlong lVar1;
  char *local_10;
  
  if (param_2 != (undefined1 *)0x0) {
    if (*param_1 != '\0') {
      local_10 = param_4;
      lVar1 = thunk_FUN_080071ec(param_1,&local_10,0);
      if (((*local_10 == '\0') && (lVar1 != -0x80000000)) && (lVar1 != 0x7fffffff)) {
        *param_2 = 1;
        return 0;
      }
      *param_2 = 0;
      return 0;
    }
    *param_2 = 0;
  }
  return 0;
}




/* 0x08038282 */
int FUN_08038282(param_1, param_2, param_3)
char * param_1; char * param_2; int param_3;
{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  bool bVar6;
  
  iVar5 = param_3;
  for (pcVar1 = param_1; (bVar6 = iVar5 != 0, iVar5 = iVar5 + -1, bVar6 && (*pcVar1 != '\0'));
      pcVar1 = pcVar1 + 1) {
  }
  param_3 = param_3 - ((int)pcVar1 - (int)param_1);
  pcVar3 = pcVar1;
  pcVar4 = param_2;
  if (param_3 == 0) {
    iVar5 = FUN_08006906(param_2);
  }
  else {
    for (; *pcVar4 != '\0'; pcVar4 = pcVar4 + 1) {
      pcVar2 = pcVar3;
      if (param_3 != 1) {
        param_3 = param_3 + -1;
        pcVar2 = pcVar3 + 1;
        *pcVar3 = *pcVar4;
      }
      pcVar3 = pcVar2;
    }
    *pcVar3 = '\0';
    iVar5 = (int)pcVar4 - (int)param_2;
  }
  return iVar5 + ((int)pcVar1 - (int)param_1);
}




/* 0x080382c2 */
char * FUN_080382c2(param_1, param_2, param_3)
char * param_1; char * param_2; int param_3;
{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  
  pcVar2 = param_2;
  iVar4 = param_3;
  if (param_3 != 0) {
    do {
      iVar4 = iVar4 + -1;
      if (iVar4 == 0) goto LAB_080382e6;
      pcVar3 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = param_1 + 1;
      *param_1 = cVar1;
      param_1 = pcVar2;
      pcVar2 = pcVar3;
    } while (cVar1 != '\0');
    if (iVar4 != 0) goto LAB_080382f4;
LAB_080382e6:
    if (param_3 != 0) {
      *param_1 = '\0';
    }
  }
  do {
    pcVar3 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar3;
  } while (cVar1 != '\0');
LAB_080382f4:
  return pcVar3 + (-1 - (int)param_2);
}




/* 0x080382fa */
int strncmp_fh(param_1, param_2, param_3)
byte * param_1; byte * param_2; int param_3;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  while( true ) {
    if (param_3 == 0) {
      return 0;
    }
    uVar2 = (uint)*param_1;
    uVar3 = (uint)*param_2;
    uVar1 = uVar2;
    if (uVar2 - 0x41 < 0x1a) {
      uVar1 = uVar2 + 0x20 & 0xff;
    }
    if (uVar3 - 0x41 < 0x1a) {
      uVar3 = uVar3 + 0x20 & 0xff;
    }
    if (uVar1 - uVar3 != 0) break;
    if (uVar2 == 0) {
      return 0;
    }
    param_3 = param_3 + -1;
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
  }
  return uVar1 - uVar3;
}




/* 0x08038338 */
undefined4 FUN_08038338(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  uVar1 = 0;
  iVar4 = 0;
  for (uVar2 = 0; uVar2 < param_3; uVar2 = uVar2 + 1) {
    uVar5 = *(uint *)(param_1 + uVar2 * 4);
    uVar3 = uVar5 + uVar1;
    uVar6 = *(uint *)(param_2 + uVar2 * 4);
    uVar1 = (iVar4 + (uint)CARRY4(uVar5,uVar1)) - (uint)(uVar3 < uVar6);
    *(uint *)(param_1 + uVar2 * 4) = uVar3 - uVar6;
    iVar4 = (int)uVar1 >> 0x1f;
  }
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0803836c */
undefined4 FUN_0803836c(param_1, param_2, param_3, param_4, param_5, param_6, param_7)
undefined4 param_1; int param_2; int param_3; undefined4 param_4; uint param_5; undefined4 param_6; int param_7;
{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined1 *puVar5;
  
  puVar5 = &DAT_87c74800 + param_3 * 0x40 + param_2 * 0x80;
  uVar2 = 1 << (param_2 + param_3 * 0x10 & 0xffU);
  if ((param_2 == 0) && ((_DAT_078d91ac & 1) != 0)) {
    do {
    } while (DAT_0804deec != 0);
    uVar1 = 5;
  }
  else if (param_5 < 0x100001) {
    if ((_DAT_078d91b8 & uVar2) == 0) {
      FUN_0802f02c(param_2,param_3,param_4,param_5,param_6,param_7);
      iVar4 = param_2 * 0x1040 + -0x7838b700 + param_3 * 0x820;
      *(int *)(puVar5 + 8) = iVar4;
      *(undefined4 *)(puVar5 + 0xc) = 0;
      thunk_FUN_080300b8(param_4,param_5);
      uVar3 = 0;
      do {
        thunk_FUN_080300b8(iVar4 + uVar3 * 0x20,0x20);
        uVar3 = uVar3 + 1;
      } while (uVar3 < 0x41);
      thunk_FUN_080300b8(puVar5,0x40);
      DataMemoryBarrier(0x1f);
      if (param_7 == 0) {
        iVar4 = 0;
        do {
          iVar4 = iVar4 + 1;
          if (4 < iVar4) {
            iVar4 = 0;
          }
          _DAT_078d91b0 = uVar2;
        } while ((uVar2 & (_DAT_078d91b8 | _DAT_078d91bc)) == 0);
      }
      uVar1 = 0;
    }
    else {
      do {
      } while (DAT_0804deec != 0);
      uVar1 = 7;
    }
  }
  else {
    do {
    } while (DAT_0804deec != 0);
    uVar1 = 3;
  }
  return uVar1;
}




/* 0x08038460 */
void FUN_08038460(param_1, param_2, param_3, param_4, param_5, param_6)
undefined2 param_1; undefined2 param_2; uint param_3; undefined4 param_4; undefined4 param_5; undefined4 param_6;
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 local_18 [3];
  
  if (param_3 < 3) {
    local_18[2] = param_6;
    local_18[0] = param_4;
    local_18[1] = param_5;
    uVar3 = param_3 * 4 + 0xc;
    if ((DAT_08050920 == (undefined4 *)0x0) || (DAT_08050b24 < uVar3)) {
      DAT_08050920 = &DAT_08050924;
      DAT_08050b24 = 0x200;
    }
    puVar2 = DAT_08050920;
    DAT_08050b24 = DAT_08050b24 - (short)uVar3;
    puVar1 = DAT_08050920 + param_3 + 3;
    *(uint*)DAT_08050920 = 0x1234abcd;
    DAT_08050920 = puVar1;
    *(undefined2 *)(puVar2 + 1) = param_1;
    *(undefined2 *)((int)puVar2 + 6) = param_2;
    *(short *)(puVar2 + 2) = (short)param_3;
    *(short *)((int)puVar2 + 10) = DAT_08050b26;
    DAT_08050b26 = DAT_08050b26 + 1;
    puVar2 = puVar2 + 3;
    for (uVar3 = 0; uVar3 < param_3; uVar3 = uVar3 + 1 & 0xff) {
      *puVar2 = local_18[uVar3];
      puVar2 = puVar2 + 1;
    }
  }
  return;
}




/* 0x080384dc */
undefined4 FUN_080384dc(param_1)
int param_1;
{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    if ((param_1 == 1) || (param_1 == 2)) {
      return 0xfffffbf4;
    }
    if (param_1 == 3) {
      return 0xfffffffc;
    }
    uVar1 = 0xfffffffb;
  }
  return uVar1;
}




/* 0x08038500 */
undefined4 FUN_08038500(param_1, param_2)
int * param_1; undefined2 * param_2;
{
  undefined2 *puVar1;
  int iVar2;
  int iVar3;
  
  if ((((param_1 == (int *)0x0) || (param_2 == (undefined2 *)0x0)) || (*param_1 == 0)) ||
     (param_1[1] == 0)) {
    return 0xffffffff;
  }
  iVar2 = 8;
  do {
    if (*(char *)(*param_1 + iVar2 + -1) != ' ') break;
    iVar2 = iVar2 + -1;
  } while (0 < iVar2);
  for (iVar3 = 0; iVar3 < iVar2; iVar3 = iVar3 + 1) {
    *param_2 = *(undefined2 *)(&DAT_0803d50a + (uint)*(byte *)(*param_1 + iVar3) * 2);
    param_2 = param_2 + 1;
  }
  iVar2 = 3;
  do {
    if (*(char *)(param_1[1] + iVar2 + -1) != ' ') break;
    iVar2 = iVar2 + -1;
  } while (0 < iVar2);
  puVar1 = param_2;
  if (iVar2 != 0) {
    puVar1 = param_2 + 1;
    *param_2 = 0x2e;
  }
  for (iVar3 = 0; iVar3 < iVar2; iVar3 = iVar3 + 1) {
    *puVar1 = *(undefined2 *)(&DAT_0803d50a + (uint)*(byte *)(param_1[1] + iVar3) * 2);
    puVar1 = puVar1 + 1;
  }
  *puVar1 = 0;
  return 0;
}




/* 0x0803857c */
undefined8 FUN_0803857c(param_1, param_2, param_3, param_4)
int param_1; short * param_2; int * param_3; undefined4 param_4;
{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  iVar7 = 0;
  iVar9 = -1;
  if ((((param_3 == (int *)0x0) || (param_2 == (short *)0x0)) || (*param_3 == 0)) ||
     (param_3[1] == 0)) {
    iVar6 = 0;
    goto LAB_080385b0;
  }
  bVar1 = 1 < param_1;
  for (iVar6 = 0; param_2[iVar6] != 0; iVar6 = iVar6 + 1) {
    if (0x7f < (ushort)param_2[iVar6]) {
      bVar1 = true;
    }
  }
  if (0xc < iVar6) {
    bVar1 = true;
  }
  FUN_08006cc0(*param_3,8,0x20,param_4,param_1,param_2,param_3);
  FUN_08006cc0(param_3[1],3,0x20);
  iVar8 = iVar6;
  if (*param_2 == 0x2e) {
    for (iVar2 = 0; (iVar2 < iVar6 && (param_2[iVar2] == 0x2e)); iVar2 = iVar2 + 1) {
      iVar7 = iVar7 + 1;
    }
  }
  for (; 0 < iVar8; iVar8 = iVar8 + -1) {
    if (param_2[iVar8 + -1] == 0x2e) {
      if (iVar8 != iVar7) {
        iVar9 = iVar8 + -1;
        if (3 < iVar6 - iVar8) {
          bVar1 = true;
        }
        iVar7 = 0;
        goto LAB_0803863c;
      }
      break;
    }
  }
  goto LAB_08038612;
  while( true ) {
    if ((uVar4 == 0x20) || (iVar2 = FUN_08027444(uVar3 & 0xff), iVar2 == 0)) {
      uVar4 = 0x5f;
      bVar1 = true;
    }
    iVar8 = iVar8 + 1;
    *(char *)(param_3[1] + iVar7) = (char)uVar4;
    iVar7 = iVar7 + 1;
    if (2 < iVar7) break;
LAB_0803863c:
    uVar3 = (uint)(ushort)param_2[iVar8];
    if (uVar3 - 0x61 < 0x1a) {
      uVar3 = uVar3 - 0x20;
    }
    uVar4 = uVar3 & 0xffff;
    if (uVar4 == 0) break;
  }
LAB_08038612:
  iVar7 = iVar6;
  if (iVar9 != -1) {
    iVar7 = iVar9;
  }
  if (iVar7 < 9) {
    if (!bVar1) {
      iVar7 = 0;
      iVar8 = 0;
      do {
        uVar3 = (uint)(ushort)param_2[iVar7];
        if (uVar3 - 0x61 < 0x1a) {
          uVar3 = uVar3 - 0x20;
        }
        uVar4 = uVar3 & 0xffff;
        if (uVar4 == 0) break;
        if (uVar4 == 0x2e) {
          if (iVar7 == iVar9) break;
        }
        else if (uVar4 == 0x20) goto LAB_080386c6;
        iVar2 = FUN_08027444();
        if (iVar2 == 0) goto LAB_080386c6;
        iVar7 = iVar7 + 1;
        *(char *)(*param_3 + iVar8) = (char)uVar3;
        iVar8 = iVar8 + 1;
      } while (iVar8 < 8);
    }
    if (!bVar1) goto LAB_080385b0;
  }
LAB_080386c6:
  uVar3 = FUN_0801a574(param_1,param_2,(uint)(iVar6 << 0x14) >> 0x10);
  iVar7 = 7;
  do {
    uVar4 = uVar3 & 0xf;
    if (uVar4 < 10) {
      cVar5 = '0';
    }
    else {
      cVar5 = '7';
    }
    uVar3 = uVar3 >> 4;
    *(char *)(*param_3 + iVar7) = (char)uVar4 + cVar5;
    iVar7 = iVar7 + -1;
  } while (-1 < iVar7);
LAB_080385b0:
  return CONCAT44(param_1,iVar6);
}




/* 0x080386f8 */
void FUN_080386f8(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  int iStack_c;
  int local_8;
  
  iStack_c = param_2;
  local_8 = param_1;
  FUN_080206c8(&local_8,param_1 + 0x800,&iStack_c,param_2 + param_3,0);
  FUN_080384dc();
  return;
}




/* 0x08038716 */
void FUN_08038716(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  int iVar1;
  int local_1c;
  int iStack_18;
  
  local_1c = param_1;
  iStack_18 = param_2;
  iVar1 = FUN_08006906();
  FUN_080207c4(&local_1c,local_1c + iVar1 + 1,&iStack_18,param_2 + param_3 * 2,0);
  FUN_080384dc();
  return;
}




/* 0x08038772 */
undefined4 FUN_08038772(param_1, param_2)
int * param_1; undefined4 * param_2;
{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = *param_1;
  iVar2 = 0;
  for (iVar1 = 0; iVar1 < *(int *)(iVar3 + 0x10); iVar1 = iVar1 + 1) {
    iVar2 = iVar2 + *(int *)(*(int *)(iVar3 + 0xc) + iVar1 * 0xc + 8);
  }
  *param_2 = 1;
  param_2[1] = iVar2;
  param_2[2] = 0;
  param_2[3] = 0;
  param_2[5] = 0;
  param_2[6] = 0;
  uVar4 = *(undefined4 *)(iVar3 + 0x10);
  param_2[7] = 0;
  param_2[8] = 0;
  param_2[4] = uVar4;
  param_2[0xb] = iVar2;
  param_2[0xc] = 0xffffffff;
  param_2[9] = 0x88;
  param_2[10] = 0xffffffff;
  param_2[0xd] = 300;
  param_2[0xe] = 1;
  param_2[0xf] = 1;
  param_2[0x10] = 0xffffffff;
  param_2[0x11] = 1;
  param_2[0x12] = 0x20;
  *(undefined1 *)(param_2 + 0x13) = 1;
  *(undefined1 *)((int)param_2 + 0x4d) = 1;
  return 0;
}




/* 0x080387d8 */
undefined4 FUN_080387d8(param_1)
int param_1;
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = *(int *)(param_1 + 8);
  iVar4 = **(int **)(param_1 + 0xc);
  if (iVar2 == 0) {
LAB_08038808:
    FUN_08021c60(*(int **)(param_1 + 0xc));
    iVar2 = *(int *)(param_1 + 0xc);
  }
  else {
    if (iVar2 == 1) {
      cVar1 = **(char **)(param_1 + 4);
LAB_08038800:
      if (cVar1 == '.') goto LAB_08038808;
    }
    else if ((iVar2 == 2) && (**(char **)(param_1 + 4) == '.')) {
      cVar1 = (*(char **)(param_1 + 4))[1];
      goto LAB_08038800;
    }
    iVar2 = 0;
    while ((iVar2 < *(int *)(iVar4 + 0x10) &&
           ((iVar3 = FUN_08006906(*(undefined4 *)(*(int *)(iVar4 + 0xc) + iVar2 * 0xc)),
            iVar3 != *(int *)(param_1 + 8) ||
            (iVar3 = FUN_08006898(*(undefined4 *)(*(int *)(iVar4 + 0xc) + iVar2 * 0xc),
                                  *(undefined4 *)(param_1 + 4)), iVar3 != 0))))) {
      iVar2 = iVar2 + 1;
    }
    if (*(int *)(iVar4 + 0x10) == iVar2) {
      return 0xfffffc16;
    }
    iVar2 = FUN_08021b38(iVar4,*(undefined2 *)(iVar4 + 4),iVar2 + 10);
    if (iVar2 == 0) {
      return 0xfffffffb;
    }
  }
  *(int *)(param_1 + 0x10) = iVar2;
  return 0;
}




/* 0x080388d0 */
undefined4 FUN_080388d0(param_1, param_2, param_3)
int * param_1; int * param_2; int param_3;
{
  int iVar1;
  undefined *puVar2;
  
  iVar1 = *param_2;
  if (iVar1 < 1) {
    return 0xfffffffb;
  }
  if (iVar1 == 1) {
    puVar2 = &DAT_0803893c;
  }
  else if (iVar1 == 2) {
    puVar2 = &DAT_08038940;
  }
  else {
    if (*(int *)(*param_1 + 0x10) <= iVar1 + -3) {
      return 0xffff8000;
    }
    puVar2 = *(undefined **)(*(int *)(*param_1 + 0xc) + iVar1 * 0xc + -0x24);
  }
  iVar1 = FUN_08006906(puVar2);
  if (0x88 < iVar1) {
    return 0xfffffbf4;
  }
  FUN_080382c2(param_3,puVar2,0x89);
  *(undefined4 *)(param_3 + 0xb8) = 0;
  *param_2 = *param_2 + 1;
  return 0;
}




/* 0x08038948 */
undefined4 FUN_08038948()
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 auStack_418 [512];
  undefined1 auStack_218 [512];
  int local_18;
  
  iVar1 = DAT_0804cd58;
  local_18 = DAT_0804cd58;
  FUN_08006d14(auStack_418,0x200);
  FUN_08006d14(auStack_218,0x200);
  do {
    iVar2 = FUN_08038db4(&DAT_08055ea0);
    if (iVar2 == 0) goto LAB_080389ae;
  } while (iVar2 != 1);
  iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_080389ec);
  if (iVar2 == 0) {
LAB_080389ae:
    uVar3 = 1;
  }
  else {
    do {
      iVar2 = FUN_08038db4(&DAT_08055ea0);
      if (iVar2 == 0) goto LAB_080389ae;
    } while (iVar2 != 1);
    xml_get_tag_name(&DAT_08055ea0,auStack_418,0x200,0);
    do {
      while( true ) {
        iVar2 = FUN_08038db4(&DAT_08055ea0);
        if (iVar2 == 0) goto LAB_080389ae;
        if (iVar2 == 4) break;
        if (iVar2 == 3) goto LAB_080389ae;
      }
      xml_get_tag_name(&DAT_08055ea0,auStack_218,0x200,0);
      iVar2 = strncmp_fh(auStack_418,auStack_218,0x200);
    } while (iVar2 != 0);
    uVar3 = 0;
  }
  if (local_18 != iVar1) {
    FUN_08010960();
  }
  return uVar3;
}




/* 0x08038b44 */
int FUN_08038b44(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar3 = 0;
  while( true ) {
    if (param_3 <= uVar3) {
      return 0;
    }
    uVar1 = *(ushort *)(param_1 + uVar3 * 2);
    uVar4 = (uint)uVar1;
    uVar5 = uVar4;
    if (uVar4 - 0x61 < 0x1a) {
      uVar5 = uVar4 - 0x20;
    }
    uVar2 = *(ushort *)(param_2 + uVar3 * 2);
    uVar7 = (uint)uVar2;
    uVar6 = uVar7;
    if (uVar7 - 0x61 < 0x1a) {
      uVar6 = uVar7 - 0x20;
    }
    if (uVar5 != uVar6) break;
    if ((uVar4 == 0) && (uVar7 == 0)) {
      return 0;
    }
    uVar3 = uVar3 + 1;
  }
  return (uint)uVar1 - (uint)uVar2;
}




/* 0x08038b92 */
int FUN_08038b92(param_1)
short * param_1;
{
  int iVar1;
  
  iVar1 = 0;
  while (*param_1 != 0) {
    iVar1 = iVar1 + 1;
    param_1 = param_1 + 1;
  }
  return iVar1;
}




/* 0x08038ba4 */
undefined4 FUN_08038ba4(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  bool bVar5;
  
  uVar1 = 0;
  iVar4 = 400;
  uVar3 = 0;
  do {
    bVar5 = iVar4 == 0;
    iVar4 = iVar4 + -1;
    if (bVar5) break;
    thunk_FUN_080199b4(1);
    iVar2 = DAT_0804d44c + (uint)DAT_0805462c * 0x1000 + param_2 * 0x8000;
    if (param_1 == 0) {
      iVar2 = iVar2 + 0x400000;
    }
    else {
      iVar2 = iVar2 + 0xc00000;
    }
    uVar1 = *(uint *)(iVar2 + 8);
  } while (uVar1 == 0);
  if ((int)(uVar1 << 0x1c) < 0) {
    uVar3 = 7;
  }
  else if ((uVar1 & 1) == 0) {
    if ((*(uint *)(DAT_0804d44c + 41000) & 1) == 0) {
      uVar3 = 8;
    }
    else {
      uVar3 = 2;
    }
  }
  else if ((int)(uVar1 << 0x1e) < 0) {
    uVar3 = 5;
  }
  else if ((int)(uVar1 << 0x1d) < 0) {
    uVar3 = 6;
  }
  return uVar3;
}




/* 0x08038c24 */
undefined4 FUN_08038c24(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  DAT_08055f99 = '\0';
  FUN_0802f900(param_1,param_3,&LAB_08028888,&DAT_08055f88);
  while (DAT_08055f99 == '\0') {
    FUN_0802f57c();
  }
  return 0;
}




/* 0x08038c54 */
void FUN_08038c54(param_1, param_2, param_3)
int param_1; int param_2; int param_3;
{
  int iVar1;
  uint uVar2;
  undefined4 local_18;
  
  iVar1 = DAT_0804d44c;
  uVar2 = 0;
  local_18 = 0;
  do {
    if (param_3 == 0) break;
    param_3 = param_3 + -1;
    *(undefined1 *)((int)&local_18 + uVar2) = *(undefined1 *)(param_2 + uVar2);
    uVar2 = uVar2 + 1;
  } while (uVar2 < 4);
  *(undefined4 *)(DAT_0804d44c + (uint)DAT_0805462c * 0x1000 + param_1 * 0x8000 + 0x400010) =
       local_18;
  if (param_3 != 0) {
    uVar2 = 0;
    local_18 = 0;
    do {
      param_3 = param_3 + -1;
      *(undefined1 *)((int)&local_18 + uVar2) = *(undefined1 *)(param_2 + uVar2 + 4);
      uVar2 = uVar2 + 1;
      if (3 < uVar2) break;
    } while (param_3 != 0);
    *(undefined4 *)(iVar1 + (uint)DAT_0805462c * 0x1000 + param_1 * 0x8000 + 0x400014) = local_18;
  }
  return;
}




/* 0x08038cc0 */
int thunk_FUN_08038cc0(param_1, param_2, param_3)
short * param_1; short * param_2; int param_3;
{
  short sVar1;
  short *psVar2;
  short *psVar3;
  int iVar4;
  
  psVar2 = param_2;
  iVar4 = param_3;
  if (param_3 != 0) {
    do {
      iVar4 = iVar4 + -1;
      if (iVar4 == 0) goto LAB_08038ce4;
      psVar3 = psVar2 + 1;
      sVar1 = *psVar2;
      psVar2 = param_1 + 1;
      *param_1 = sVar1;
      param_1 = psVar2;
      psVar2 = psVar3;
    } while (sVar1 != 0);
    if (iVar4 != 0) goto LAB_08038cf2;
LAB_08038ce4:
    if (param_3 != 0) {
      *param_1 = 0;
    }
  }
  do {
    psVar3 = psVar2 + 1;
    sVar1 = *psVar2;
    psVar2 = psVar3;
  } while (sVar1 != 0);
LAB_08038cf2:
  return ((int)psVar3 - (int)param_2 >> 1) + -1;
}




/* 0x08038cc0 */
int FUN_08038cc0(param_1, param_2, param_3)
short * param_1; short * param_2; int param_3;
{
  short sVar1;
  short *psVar2;
  short *psVar3;
  int iVar4;
  
  psVar2 = param_2;
  iVar4 = param_3;
  if (param_3 != 0) {
    do {
      iVar4 = iVar4 + -1;
      if (iVar4 == 0) goto LAB_08038ce4;
      psVar3 = psVar2 + 1;
      sVar1 = *psVar2;
      psVar2 = param_1 + 1;
      *param_1 = sVar1;
      param_1 = psVar2;
      psVar2 = psVar3;
    } while (sVar1 != 0);
    if (iVar4 != 0) goto LAB_08038cf2;
LAB_08038ce4:
    if (param_3 != 0) {
      *param_1 = 0;
    }
  }
  do {
    psVar3 = psVar2 + 1;
    sVar1 = *psVar2;
    psVar2 = psVar3;
  } while (sVar1 != 0);
LAB_08038cf2:
  return ((int)psVar3 - (int)param_2 >> 1) + -1;
}




/* 0x08038cfa */
bool FUN_08038cfa(param_1, param_2, param_3, param_4)
int * param_1; int param_2; uint param_3; uint param_4;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  uVar3 = param_1[0xe];
  uVar2 = param_1[0x10] - uVar3;
  uVar1 = ((param_1[0x11] - param_1[0xf]) - (uint)((uint)param_1[0x10] < uVar3)) +
          (uint)(0xfffffffe < uVar2);
  bVar4 = uVar1 < param_4 || param_4 - uVar1 < (uint)(uVar2 + 1 <= param_3);
  if (bVar4) {
    FUN_08027bf8(param_2,param_3,*param_1 + uVar3,uVar2);
    *(undefined1 *)(param_2 + uVar2) = 0;
  }
  return bVar4;
}




/* 0x08038d38 */
bool FUN_08038d38(param_1, param_2, param_3, param_4)
int * param_1; int param_2; uint param_3; uint param_4;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  uVar3 = param_1[0x12];
  uVar2 = param_1[0x14] - uVar3;
  uVar1 = ((param_1[0x15] - param_1[0x13]) - (uint)((uint)param_1[0x14] < uVar3)) +
          (uint)(0xfffffffe < uVar2);
  bVar4 = uVar1 < param_4 || param_4 - uVar1 < (uint)(uVar2 + 1 <= param_3);
  if (bVar4) {
    FUN_08027bf8(param_2,param_3,*param_1 + uVar3,uVar2);
    *(undefined1 *)(param_2 + uVar2) = 0;
  }
  return bVar4;
}




/* 0x08038d76 */
bool xml_get_tag_name(param_1, param_2, param_3, param_4)
int * param_1; int param_2; uint param_3; uint param_4;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  uVar3 = param_1[10];
  uVar2 = param_1[0xc] - uVar3;
  uVar1 = ((param_1[0xd] - param_1[0xb]) - (uint)((uint)param_1[0xc] < uVar3)) +
          (uint)(0xfffffffe < uVar2);
  bVar4 = uVar1 < param_4 || param_4 - uVar1 < (uint)(uVar2 + 1 <= param_3);
  if (bVar4) {
    FUN_08027bf8(param_2,param_3,*param_1 + uVar3,uVar2);
    *(undefined1 *)(param_2 + uVar2) = 0;
  }
  return bVar4;
}




/* 0x08038db4 */
int FUN_08038db4(param_1)
int * param_1;
{
  char cVar1;
  byte bVar2;
  bool bVar3;
  undefined1 uVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  
  iVar11 = 0;
  bVar3 = false;
  uVar13 = param_1[2];
  uVar12 = param_1[3];
  do {
    uVar9 = param_1[6];
    uVar10 = param_1[7];
    if (uVar12 < uVar10 || uVar10 - uVar12 < (uint)(uVar13 <= uVar9)) {
      return iVar11;
    }
    iVar6 = *param_1;
    cVar1 = (char)param_1[4];
    uVar8 = (uint)*(byte *)(iVar6 + uVar9);
    if (cVar1 == '\0') {
      if (uVar8 == 0x3c) {
        if (param_1[8] == 0 && param_1[9] == 0) {
          uVar4 = 1;
        }
        else {
LAB_08038e30:
          uVar4 = 5;
        }
LAB_08038ff2:
        *(undefined1 *)(param_1 + 4) = uVar4;
      }
      else {
        piVar5 = (int *)FUN_080060b0();
        bVar2 = *(byte *)(*piVar5 + uVar8);
LAB_08038f3e:
        if ((bVar2 & 1) == 0) {
LAB_08038f40:
          bVar3 = true;
        }
      }
    }
    else if (cVar1 == '\x01') {
      piVar5 = (int *)FUN_080060b0();
      if (((*(byte *)(*piVar5 + uVar8) & 0x98) == 0) && (uVar8 != 0x3f)) {
        if (uVar8 != 0x21) goto LAB_08038f40;
LAB_08038e50:
        uVar4 = 0xe;
        goto LAB_08038ff2;
      }
LAB_08038e4c:
      uVar4 = 2;
LAB_08038efe:
      *(undefined1 *)(param_1 + 4) = uVar4;
      param_1[10] = uVar9;
      param_1[0xb] = uVar10;
    }
    else if (cVar1 == '\x02') {
      if (uVar8 == 0x3e) {
        uVar4 = 3;
      }
      else {
        piVar5 = (int *)FUN_080060b0();
        if ((*(byte *)(*piVar5 + uVar8) & 1) == 0) {
          if ((*(byte *)(*piVar5 + uVar8) & 0x38) != 0) goto LAB_08038ff4;
          if (uVar8 != 0x2f) goto LAB_08038f40;
          uVar4 = 8;
        }
        else {
          uVar4 = 9;
        }
      }
      *(undefined1 *)(param_1 + 4) = uVar4;
      param_1[0xc] = uVar9;
      param_1[0xd] = uVar10;
      iVar11 = 1;
      iVar6 = param_1[8] + 1;
      iVar7 = param_1[9] + (uint)(0xfffffffe < (uint)param_1[8]);
LAB_08038f5c:
      param_1[8] = iVar6;
      param_1[9] = iVar7;
    }
    else if (cVar1 == '\x03') {
      piVar5 = (int *)FUN_080060b0();
      if ((*(byte *)(*piVar5 + uVar8) & 0x98) == 0) {
        if (uVar8 == 0x3c) goto LAB_08038e30;
      }
      else {
        *(undefined1 *)(param_1 + 4) = 4;
        param_1[0x16] = uVar9;
        param_1[0x17] = uVar10;
      }
    }
    else if (cVar1 == '\x04') {
      if (uVar8 == 0x3c) {
        iVar11 = 3;
        *(undefined1 *)(param_1 + 4) = 5;
      }
    }
    else if (cVar1 == '\x05') {
      if (uVar8 == 0x2f) {
        uVar4 = 6;
        goto LAB_08038ff2;
      }
      piVar5 = (int *)FUN_080060b0();
      if ((*(byte *)(*piVar5 + uVar8) & 0x98) != 0) goto LAB_08038e4c;
      if (uVar8 == 0x21) goto LAB_08038e50;
    }
    else if (cVar1 == '\x06') {
      piVar5 = (int *)FUN_080060b0();
      if ((*(byte *)(*piVar5 + uVar8) & 0x98) != 0) {
        uVar4 = 7;
        goto LAB_08038efe;
      }
    }
    else if (cVar1 == '\a') {
      if (uVar8 == 0x3e) {
        *(undefined1 *)(param_1 + 4) = 0;
        param_1[0xc] = uVar9;
        param_1[0xd] = uVar10;
LAB_08038f52:
        iVar11 = 4;
        iVar6 = param_1[8] + -1;
        iVar7 = param_1[9] + -1 + (uint)(param_1[8] != 0);
        goto LAB_08038f5c;
      }
    }
    else if (cVar1 == '\t') {
      if ((uVar8 == 0x2f) || (uVar8 == 0x3f)) {
        uVar4 = 8;
        goto LAB_08038ff2;
      }
      piVar5 = (int *)FUN_080060b0();
      bVar2 = *(byte *)(*piVar5 + uVar8);
      if ((bVar2 & 0x98) == 0) goto LAB_08038f3e;
      *(undefined1 *)(param_1 + 4) = 10;
      param_1[0xe] = uVar9;
      param_1[0xf] = uVar10;
    }
    else if (cVar1 == '\b') {
      if (uVar8 == 0x3e) {
        *(undefined1 *)(param_1 + 4) = 0;
        goto LAB_08038f52;
      }
    }
    else if (cVar1 == '\n') {
      if (uVar8 == 0x3d) {
        *(undefined1 *)(param_1 + 4) = 0xb;
        param_1[0x10] = uVar9;
        param_1[0x11] = uVar10;
      }
    }
    else if (cVar1 == '\v') {
      if (uVar8 == 0x22) {
        uVar4 = 0xc;
        goto LAB_08038ff2;
      }
    }
    else {
      if (cVar1 == '\f') {
        *(undefined1 *)(param_1 + 4) = 0xd;
        param_1[0x12] = uVar9;
        param_1[0x13] = uVar10;
      }
      else if (cVar1 != '\r') {
        if (cVar1 == '\x0e') {
          if (uVar8 == 0x2d) {
            uVar8 = uVar9 + 1;
            uVar10 = uVar10 + (0xfffffffe < uVar9);
            param_1[6] = uVar8;
            param_1[7] = uVar10;
            if ((uVar10 <= uVar12 && (uint)(uVar13 <= uVar8) <= uVar10 - uVar12) &&
               (*(char *)(iVar6 + uVar8) == '-')) {
              uVar4 = 0xf;
              goto LAB_08038ff2;
            }
          }
        }
        else if (cVar1 == '\x0f') {
          *(undefined1 *)(param_1 + 4) = 0x10;
          param_1[0x1a] = uVar9;
          param_1[0x1b] = uVar10;
        }
        else if (cVar1 == '\x10') {
          if (uVar8 == 0x2d) {
            *(undefined1 *)(param_1 + 4) = 0x11;
            param_1[0x1c] = uVar9;
            param_1[0x1d] = uVar10;
          }
        }
        else if (cVar1 == '\x11') {
          if (uVar8 == 0x2d) {
            uVar8 = uVar9 + 1;
            uVar10 = uVar10 + (0xfffffffe < uVar9);
            param_1[6] = uVar8;
            param_1[7] = uVar10;
            if ((uVar10 <= uVar12 && (uint)(uVar13 <= uVar8) <= uVar10 - uVar12) &&
               (*(char *)(iVar6 + uVar8) == '>')) {
              iVar11 = 5;
              *(undefined1 *)(param_1 + 4) = 0;
              goto LAB_08038ff4;
            }
          }
          uVar4 = 0x10;
          goto LAB_08038ff2;
        }
        goto LAB_08038ff4;
      }
      if (uVar8 == 0x22) {
        *(undefined1 *)(param_1 + 4) = 9;
        param_1[0x14] = uVar9;
        param_1[0x15] = uVar10;
        iVar11 = 2;
      }
    }
LAB_08038ff4:
    uVar10 = param_1[6];
    param_1[6] = uVar10 + 1;
    param_1[7] = param_1[7] + (uint)(0xfffffffe < uVar10);
    if (iVar11 != 0) {
      return iVar11;
    }
    if (bVar3) {
      return 0;
    }
  } while( true );
}




/* 0x08039030 */
void FUN_08039030(param_1, param_2, param_3, param_4)
undefined4 * param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  *param_1 = param_2;
  param_1[2] = param_3;
  param_1[3] = param_4;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  *(undefined1 *)(param_1 + 4) = 0;
  return;
}




/* 0x08039044 */
void FUN_08039044(param_1, param_2, param_3, param_4)
undefined4 * param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  *param_1 = param_2;
  param_1[2] = param_3;
  param_1[3] = param_4;
  param_1[4] = 0;
  param_1[5] = 0;
  *(undefined1 *)(param_1 + 6) = 0;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  *(undefined1 *)(param_1 + 0x16) = 0;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  param_1[0x1a] = 0;
  param_1[0x1b] = 0;
  return;
}




/* 0x0803906c */
undefined4 FUN_0803906c(param_1, param_2)
int * param_1; int param_2;
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_1[0xe];
  iVar2 = param_1[0x10];
  iVar1 = strncmp_fh(param_2,*param_1 + param_1[0xe]);
  if ((iVar1 == 0) && (*(char *)(param_2 + (iVar2 - iVar3)) == '\0')) {
    return 1;
  }
  return 0;
}




/* 0x08039092 */
undefined4 xml_tag_match(param_1, param_2)
int * param_1; int param_2;
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_1[10];
  iVar2 = param_1[0xc];
  iVar1 = strncmp_fh(param_2,*param_1 + param_1[10]);
  if ((iVar1 == 0) && (*(char *)(param_2 + (iVar2 - iVar3)) == '\0')) {
    return 1;
  }
  return 0;
}




/* 0x080390d8 */
void FUN_080390d8(param_1)
undefined4 param_1;
{
  FUN_08039110(param_1,&DAT_080390e0);
  return;
}




/* 0x080390e4 */
void FUN_080390e4(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  FUN_08039110(param_1,"</%s>",param_2);
  return;
}




/* 0x080390f4 */
void FUN_080390f4(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  FUN_08039110(param_1,&DAT_080390fc,param_2);
  return;
}




/* 0x08039100 */
void FUN_08039100(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  FUN_08039110(param_1,&DAT_08039108,param_2);
  return;
}




/* 0x08039110 */
void FUN_08039110(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uStack_8 = param_3;
  uStack_4 = param_4;
  FUN_08039122(param_1,param_2,&uStack_8);
  return;
}




/* 0x08039122 */
undefined4 FUN_08039122(param_1, param_2, param_3)
int * param_1; undefined4 param_2; undefined4 param_3;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  if ((uint)param_1[5] <= (uint)param_1[3] &&
      (uint)((uint)param_1[2] <= (uint)param_1[4]) <= (uint)(param_1[5] - param_1[3])) {
    uVar1 = FUN_08006418(param_1[4] + *param_1,param_1[2] - param_1[4],param_2,param_3);
    uVar2 = param_1[4];
    uVar3 = (param_1[3] - param_1[5]) - (uint)((uint)param_1[2] < uVar2);
    uVar4 = (int)uVar1 >> 0x1f;
    if (uVar4 <= uVar3 && (uint)(param_1[2] - uVar2 <= uVar1) <= uVar4 - uVar3) {
      param_1[4] = uVar2 + uVar1;
      param_1[5] = param_1[5] + uVar4 + (uint)CARRY4(uVar2,uVar1);
      return 1;
    }
  }
  return 0;
}




/* 0x08039174 */
void FUN_08039174(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  FUN_08039110(param_1," %s=\"%s\"",param_2,param_3);
  return;
}




/* 0x0803918c */
bool FUN_0803918c(param_1, param_2, param_3, param_4, param_5, param_6)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4; uint param_5; int param_6;
{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  
  uVar1 = FUN_08006906(param_2);
  uVar2 = uVar1 + *(uint *)(param_1 + 0x10);
  uVar1 = *(int *)(param_1 + 0x14) + (uint)CARRY4(uVar1,*(uint *)(param_1 + 0x10)) +
          param_6 + (uint)(0xfffffffb < param_5) + (uint)CARRY4(uVar2,param_5 + 4);
  bVar3 = uVar1 < *(uint *)(param_1 + 0xc) ||
          *(uint *)(param_1 + 0xc) - uVar1 < (uint)(uVar2 + param_5 + 4 <= *(uint *)(param_1 + 8));
  if (bVar3) {
    FUN_08039110(param_1,&DAT_080391e8,param_2);
    FUN_080391f0(param_1,param_3,param_5,param_6);
    FUN_08039110(param_1,&DAT_080391ec);
  }
  return bVar3;
}




/* 0x080391f0 */
undefined4 FUN_080391f0(param_1, param_2, param_3, param_4)
int * param_1; undefined4 param_2; uint param_3; int param_4;
{
  uint uVar1;
  
  uVar1 = param_1[5] + param_4 + (uint)CARRY4(param_1[4],param_3);
  if ((uint)param_1[3] <= uVar1 &&
      (uint)(param_1[4] + param_3 <= (uint)param_1[2]) <= param_1[3] - uVar1) {
    return 0;
  }
  FUN_08027bf8(*param_1 + param_1[4],param_1[2],param_2,param_3);
  uVar1 = param_1[4];
  param_1[4] = uVar1 + param_3;
  param_1[5] = param_1[5] + param_4 + (uint)CARRY4(uVar1,param_3);
  return 1;
}




/* 0x08039234 */
void FUN_08039234(param_1)
int param_1;
{
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined1 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x4c) = 0;
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(param_1 + 0x14);
  *(undefined1 *)(param_1 + 0x58) = *(undefined1 *)(param_1 + 0x18);
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0x40);
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(param_1 + 0x44);
  *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(param_1 + 0x48);
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(param_1 + 0x4c);
  return;
}




/* 0x08039248 */
undefined * FUN_08039248(param_1, param_2)
undefined4 param_1; char * param_2;
{
  int iVar1;
  
  if (((param_2 != (char *)0x0) && (*param_2 != '\0')) &&
     (iVar1 = FUN_08006d64(&DAT_0803e308), iVar1 != 0)) {
    return (undefined *)0x0;
  }
  return &DAT_0803e310;
}




/* 0x08039274 */
undefined * FUN_08039274(param_1, param_2)
undefined4 param_1; char * param_2;
{
  int iVar1;
  
  if (((param_2 != (char *)0x0) && (*param_2 != '\0')) &&
     (iVar1 = FUN_08006d64(&DAT_0803e428), iVar1 != 0)) {
    return (undefined *)0x0;
  }
  return &DAT_0803e430;
}




/* 0x080392a4 */
undefined8 FUN_080392a4(param_1, param_2)
int param_1; int param_2;
{
  return CONCAT44(param_1 - (param_1 / param_2) * param_2,param_1 / param_2);
}



