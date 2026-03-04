/* Auto-generated: fhprg_8020c28.c */
/* Functions: 14 */
#include "globals.h"

/* 0x08020c28 */
undefined4 * FUN_08020c28()
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = DAT_0804d620;
  for (iVar4 = 0; iVar4 < DAT_0804d620; iVar4 = iVar4 + 1) {
    if ((&DAT_87c27b88)[iVar4 * 7] == 0) {
      (&DAT_87c27b88)[iVar4 * 7] = 1;
      return &DAT_87c27b84 + iVar4 * 7;
    }
  }
  if (0x1f < DAT_0804d620) {
    return (undefined4 *)0x0;
  }
  iVar4 = DAT_0804d620 * 0x1c;
  iVar1 = DAT_0804d620 * 7;
  iVar2 = DAT_0804d620 * 7;
  DAT_0804d620 = DAT_0804d620 + 1;
  (&DAT_87c27b88)[iVar2] = 1;
  (&DAT_87c27b84)[iVar3 * 7] = iVar3;
  *(undefined4 *)(&DAT_87c27b9c + iVar4) = 0;
  return &DAT_87c27b84 + iVar1;
}




/* 0x08020c7c */
void FUN_08020c7c(param_1)
int param_1;
{
  *(undefined4 *)(param_1 + 4) = 0;
  return;
}




/* 0x08020c84 */
void FUN_08020c84()
{
  DAT_0804d620 = 0;
  return;
}




/* 0x08020c90 */
undefined4 * FUN_08020c90(param_1)
uint param_1;
{
  undefined4 *puVar1;
  
  if ((0x1f < param_1) || (puVar1 = &DAT_87c27b84 + param_1 * 7, (&DAT_87c27b88)[param_1 * 7] == 0))
  {
    puVar1 = (undefined4 *)0x0;
  }
  return puVar1;
}




/* 0x08020cac */
void FUN_08020cac()
{
  return;
}




/* 0x08020cb0 */
void FUN_08020cb0()
{
  int iVar1;
  
  FUN_08020d68();
  iVar1 = 0;
  do {
    (&DAT_0804d624)[iVar1] = 0;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 2);
  iVar1 = 0;
  do {
    (&DAT_87c27f10)[iVar1 * 0x51] = 0;
    (&DAT_87c27f04)[iVar1 * 0x51] = &PTR_LAB_0801d784_1_0803addc;
    (&DAT_87c27f14)[iVar1 * 0x51] = &PTR_LAB_0801cac8_1_0803c968;
    FUN_08021000("extfs");
    iVar1 = iVar1 + 1;
  } while (iVar1 < 2);
  return;
}




/* 0x08020d10 */
undefined4 FUN_08020d10(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; undefined4 param_3; undefined4 param_4;
{
  short local_18;
  ushort local_16;
  uint local_14;
  ushort local_10;
  ushort local_e;
  undefined4 uStack_c;
  
  local_14 = CONCAT22((short)(param_1 >> 0xb),(short)param_2) & 0xffff001f;
  _local_18 = CONCAT22((ushort)((param_2 << 0x17) >> 0x1c),(short)(param_2 >> 9) + 0x7bc);
  _local_10 = CONCAT22((ushort)((param_1 << 0x1b) >> 0x1a),(ushort)((param_1 << 0x15) >> 0x1a));
  uStack_c = param_4;
  FUN_080208cc(&local_18);
  return 0;
}




/* 0x08020d4c */
void FUN_08020d4c()
{
  return;
}




/* 0x08020d50 */
void FUN_08020d50()
{
  if (DAT_0804d62c == '\0') {
    DAT_0804d62c = '\x01';
  }
  return;
}




/* 0x08020d64 */
void FUN_08020d64()
{
  return;
}




/* 0x08020d68 */
void FUN_08020d68()
{
  int iVar1;
  undefined4 *puVar2;
  
  thunk_FUN_0801ea50();
  puVar2 = &DAT_87c2accc;
  iVar1 = 0;
  do {
    iVar1 = iVar1 + 1;
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  } while (iVar1 < 8);
  iVar1 = 0;
  do {
    FUN_08031660(&DAT_87c29e24 + iVar1 * 0x1d5);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 2);
  return;
}




/* 0x08020da0 */
void FUN_08020da0(param_1, param_2, param_3, param_4)
undefined2 * param_1; undefined2 param_2; undefined2 param_3; undefined2 param_4;
{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = FUN_080219a8();
  *param_1 = param_2;
  *(undefined4 *)(param_1 + 4) = 0;
  param_1[1] = 0;
  *(undefined4 *)(param_1 + 0xc) = uVar1;
  *(undefined4 *)(param_1 + 0xe) = uVar1;
  *(undefined4 *)(param_1 + 10) = 0;
  *(undefined4 *)(param_1 + 0x10) = uVar1;
  param_1[7] = param_3;
  param_1[6] = param_4;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
  iVar2 = 0;
  do {
    iVar3 = iVar2 + 1;
    *(undefined4 *)(param_1 + iVar2 * 2 + 0x20) = 0xffffffff;
    iVar2 = iVar3;
  } while (iVar3 < 0x10);
  return;
}




/* 0x08020dde */
undefined4 FUN_08020dde(param_1, param_2)
byte * param_1; int param_2;
{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  
  pbVar3 = param_1 + param_2;
  if (param_2 != 1) {
    if (param_2 != 2) {
      if (param_2 != 3) {
        if (param_2 != 4) {
          return 0;
        }
        pbVar3 = pbVar3 + -1;
        if (*pbVar3 < 0x80) {
          return 0;
        }
        if (0xbf < *pbVar3) {
          return 0;
        }
      }
      pbVar3 = pbVar3 + -1;
      if (*pbVar3 < 0x80) {
        return 0;
      }
      if (0xbf < *pbVar3) {
        return 0;
      }
    }
    bVar2 = pbVar3[-1];
    if (0xbf < bVar2) {
      return 0;
    }
    bVar1 = *param_1;
    if (bVar1 == 0xe0) {
      if (bVar2 < 0xa0) {
        return 0;
      }
    }
    else if (bVar1 == 0xed) {
      if (0x9f < bVar2) {
        return 0;
      }
    }
    else if (bVar1 == 0xf0) {
      if (bVar2 < 0x90) {
        return 0;
      }
    }
    else if (bVar1 == 0xf4) {
      if (0x8f < bVar2) {
        return 0;
      }
    }
    else if (bVar2 < 0x80) {
      return 0;
    }
  }
  if ((0x41 < *param_1 - 0x80) && (*param_1 < 0xf5)) {
    return 1;
  }
  return 0;
}




/* 0x08020e54 */
undefined4 FUN_08020e54(param_1)
char * param_1;
{
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    return 0;
  }
  return 0xffffffff;
}




