/* Auto-generated: fhprg_802196c.c */
/* Functions: 16 */
#include "globals.h"

/* 0x0802196c */
void FUN_0802196c()
{
  int iVar1;
  
  iVar1 = 0;
  do {
    (&DAT_87c28520)[iVar1 * 6] = 0;
    (&DAT_87c2850c)[iVar1 * 6] = &PTR_LAB_08030f44_1_0803b0ec;
    FUN_08021000("romfs");
    iVar1 = iVar1 + 1;
  } while (iVar1 < 2);
  return;
}




/* 0x080219a8 */
int FUN_080219a8()
{
  uint uVar1;
  undefined8 uVar2;
  
  uVar2 = FUN_080219d0();
  uVar1 = FUN_080060c0((int)uVar2,(int)((ulonglong)uVar2 >> 0x20),1000,0);
  if (uVar1 < 0x25980600) {
    uVar1 = 0;
  }
  return uVar1 + 0x12d53d80;
}




/* 0x080219d0 */
undefined4 FUN_080219d0()
{
  return 0;
}




/* 0x080219d8 */
int FUN_080219d8()
{
  int iVar1;
  
  iVar1 = DAT_0804d644;
  if (DAT_0804d644 != 0) {
    DAT_0804d644 = *(int *)(DAT_0804d644 + 0x18);
    FUN_08006d14(iVar1,0x15c);
    *(undefined4 *)(iVar1 + 0x1c) = 1;
  }
  return iVar1;
}




/* 0x080219fc */
undefined4 FUN_080219fc(param_1)
int param_1;
{
  return *(undefined4 *)(param_1 + 0x1c);
}




/* 0x08021a00 */
void FUN_08021a00()
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  DAT_0804d644 = (undefined4 *)0x0;
  iVar2 = 0;
  do {
    iVar3 = iVar2 + 1;
    iVar1 = iVar2 * 0x57;
    (&DAT_87c28558)[iVar2 * 0x57] = 0;
    (&DAT_87c2853c)[iVar2 * 0x57] = 0;
    (&DAT_87c28548)[iVar2 * 0xae] = 0;
    (&DAT_87c2854c)[iVar2 * 0x57] = 0;
    (&DAT_87c28554)[iVar2 * 0x57] = DAT_0804d644;
    DAT_0804d644 = &DAT_87c2853c + iVar1;
    iVar2 = iVar3;
  } while (iVar3 < 0x10);
  return;
}




/* 0x08021b38 */
undefined4 * FUN_08021b38(param_1, param_2, param_3)
int * param_1; uint param_2; int param_3;
{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = 0;
  while( true ) {
    if ((((&DAT_87c28548)[iVar1 * 0xae] != 0) && ((ushort)(&DAT_87c28540)[iVar1 * 0xae] == param_2))
       && ((&DAT_87c28544)[iVar1 * 0x57] == param_3)) break;
    iVar1 = iVar1 + 1;
    if (0xf < iVar1) {
      puVar2 = (undefined4 *)0x0;
      if ((*(int *)(*param_1 + 0x14) != 0) &&
         (puVar2 = (undefined4 *)FUN_080219d8(), puVar2 != (undefined4 *)0x0)) {
        *(short *)(puVar2 + 1) = (short)param_2;
        puVar2[2] = param_3;
        *puVar2 = param_1;
        puVar2[4] = 0;
        iVar1 = (**(code **)(*param_1 + 0x14))(param_1,puVar2,param_3);
        if (iVar1 != 0) {
          FUN_08021c68(puVar2);
          puVar2 = (undefined4 *)0x0;
        }
      }
      return puVar2;
    }
  }
  (&DAT_87c28558)[iVar1 * 0x57] = (&DAT_87c28558)[iVar1 * 0x57] + 1;
  return &DAT_87c2853c + iVar1 * 0x57;
}




/* 0x08021bb0 */
undefined4 * FUN_08021bb0(param_1, param_2, param_3, param_4, param_5)
int * param_1; uint param_2; uint param_3; undefined4 param_4; int param_5;
{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar3 = 0;
  while( true ) {
    if ((((ushort)(&DAT_87c28548)[iVar3 * 0xae] != 0) &&
        ((((param_3 == 0 || (((ushort)(&DAT_87c28548)[iVar3 * 0xae] & 0xf000) == (param_3 & 0xf000))
           ) && ((ushort)(&DAT_87c28540)[iVar3 * 0xae] == param_2)) &&
         (((&DAT_87c28544)[iVar3 * 0x57] == -1 && ((&DAT_87c2855c)[iVar3 * 0x57] == param_5)))))) &&
       (iVar1 = FUN_08006898(param_4,&DAT_87c28560 + iVar3 * 0x15c,param_5), iVar1 == 0)) break;
    iVar3 = iVar3 + 1;
    if (0xf < iVar3) {
      puVar2 = (undefined4 *)0x0;
      if ((*(int *)(*param_1 + 0x18) != 0) &&
         (puVar2 = (undefined4 *)FUN_080219d8(), puVar2 != (undefined4 *)0x0)) {
        *(short *)(puVar2 + 1) = (short)param_2;
        *puVar2 = param_1;
        puVar2[2] = 0xffffffff;
        puVar2[4] = 0;
        iVar3 = (**(code **)(*param_1 + 0x18))(param_1,puVar2,param_3,param_4,param_5);
        if (iVar3 != 0) {
          FUN_08021c68(puVar2);
          puVar2 = (undefined4 *)0x0;
        }
      }
      return puVar2;
    }
  }
  (&DAT_87c28558)[iVar3 * 0x57] = (&DAT_87c28558)[iVar3 * 0x57] + 1;
  return &DAT_87c2853c + iVar3 * 0x57;
}




/* 0x08021c60 */
void FUN_08021c60(param_1)
int param_1;
{
  *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 1;
  return;
}




/* 0x08021c68 */
void FUN_08021c68(param_1)
undefined4 * param_1;
{
  int iVar1;
  code *pcVar2;
  
  iVar1 = param_1[7];
  param_1[7] = iVar1 + -1;
  if (iVar1 + -1 < 0) {
    FUN_08015a50();
  }
  if (param_1[7] == 0) {
    if (param_1[4] != 0) {
      FUN_08015a50();
    }
    pcVar2 = *(code **)(*(int *)*param_1 + 0x1c);
    if (pcVar2 != (code *)0x0) {
      (*pcVar2)((int *)*param_1,param_1);
    }
    *(undefined2 *)(param_1 + 3) = 0;
    param_1[6] = DAT_0804d644;
    DAT_0804d644 = param_1;
  }
  return;
}




/* 0x08021ca4 */
undefined4 FUN_08021ca4()
{
  FUN_08031170();
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08021cb4 */
undefined4 FUN_08021cb4(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  int extraout_r2;
  int iVar1;
  
  FUN_0801a27c(param_1,param_2,0);
  iVar1 = extraout_r2;
  if ((_DAT_01002004 & 3) == 1) {
    iVar1 = 1;
  }
  if ((_DAT_01001004 & 3) == 1) {
    iVar1 = iVar1 + 2;
  }
  if ((_DAT_01000004 & 3) == 1) {
    iVar1 = iVar1 + 4;
  }
  DAT_0804cd50 = 5;
  switch(iVar1) {
  case 0:
    DAT_0804cd50 = 0;
    break;
  case 1:
    DAT_0804cd50 = 1;
    break;
  case 2:
    DAT_0804cd50 = 2;
    break;
  case 3:
    DAT_0804cd50 = 3;
    break;
  case 4:
    DAT_0804cd50 = 4;
    break;
  default:
    return 5;
  }
  return DAT_0804cd50;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08021cfc */
uint FUN_08021cfc()
{
  uint uVar1;
  
  _DAT_01010000 = 0;
  uVar1 = (uint)((_DAT_01010004 & 3) == 1);
  DAT_0804cd4c = 2;
  if ((uVar1 != 0) && (uVar1 != 1)) {
    return 2;
  }
  DAT_0804cd4c = uVar1;
  return uVar1;
}




/* 0x08021d18 */
undefined4 FUN_08021d18(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  undefined4 uVar1;
  undefined1 *puVar2;
  int extraout_r2;
  int iVar3;
  
  FUN_0801a298(param_1,param_2,0);
  if (DAT_0804cd50 == 0 && DAT_0804cd4c == 0) {
    puVar2 = &DAT_0105c000;
  }
  else {
    puVar2 = &DAT_01051000;
  }
  iVar3 = extraout_r2;
  if ((*(uint *)(puVar2 + 4) & 3) == 1) {
    iVar3 = 1;
  }
  uVar1 = 2;
  if (iVar3 == 0) {
    return 0;
  }
  if (iVar3 == 1) {
    uVar1 = 1;
  }
  return uVar1;
}




/* 0x08021d54 */
char FUN_08021d54(param_1, param_2)
undefined4 param_1; undefined4 * param_2;
{
  int iVar1;
  undefined1 auStack_20 [8];
  undefined4 local_18;
  undefined1 auStack_14 [8];
  
  *param_2 = &DAT_08053f94;
  if (((DAT_0804d15c == '\0') && (iVar1 = dal_device_attach(param_1,auStack_14), iVar1 == 0)) &&
     (iVar1 = thunk_FUN_080106aa(auStack_14,"num_channels",0,auStack_20), iVar1 == 0)) {
    DAT_08053f94 = local_18;
    iVar1 = thunk_FUN_080106aa(auStack_14,"num_segments",0,auStack_20);
    if (iVar1 == 0) {
      DAT_08053f98 = local_18;
      iVar1 = thunk_FUN_080106aa(auStack_14,"map_ddr_region_count",0,auStack_20);
      if (iVar1 == 0) {
        DAT_08053f9c = local_18;
        iVar1 = thunk_FUN_080106aa(auStack_14,"map_ddr_regions",0,auStack_20);
        if (iVar1 == 0) {
          DAT_08053fa0 = local_18;
          iVar1 = thunk_FUN_080106aa(auStack_14,"bimc_hal_info",0,auStack_20);
          if (iVar1 == 0) {
            DAT_08053fa4 = local_18;
            iVar1 = thunk_FUN_080106aa(auStack_14,"channel_map",0,auStack_20);
            if (iVar1 == 0) {
              DAT_08053fa8 = local_18;
              iVar1 = thunk_FUN_080106aa(auStack_14,"safe_reset_seg",0,auStack_20);
              if (iVar1 == 0) {
                DAT_08053fac = local_18;
                DAT_08053fb0 = 0;
                DAT_0804d15c = '\x01';
              }
            }
          }
        }
      }
    }
  }
  return DAT_0804d15c;
}




/* 0x08021e7c */
void FUN_08021e7c(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 * param_3; undefined4 param_4;
{
  int iVar1;
  undefined4 uStack_18;
  undefined4 *puStack_14;
  undefined4 local_10;
  
  uStack_18 = param_2;
  puStack_14 = param_3;
  local_10 = param_4;
  iVar1 = thunk_FUN_080106aa(param_1,param_2,0,&uStack_18);
  if (iVar1 != 0) {
    *param_3 = param_4;
    return;
  }
  *param_3 = local_10;
  return;
}




