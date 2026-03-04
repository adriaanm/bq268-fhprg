/* Auto-generated: pm_utils.c */
/* Functions: 5 */
#include "globals.h"

/* 0x0802c644 */
void FUN_0802c644(param_1, param_2)
undefined4 param_1; int * param_2;
{
  int iVar1;
  
  iVar1 = FUN_0800b61e();
  if (iVar1 != 0) {
    ((code*)DAT_0804cd60)("pm_utils.c",0x2a);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (*param_2 != 0) {
    FUN_08006cd0(*param_2,param_1);
    return;
  }
  ((code*)DAT_0804cd60)("pm_utils.c",0x2b,0x3060);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x0802c688 */
undefined4 FUN_0802c688(param_1, param_2, param_3)
uint param_1; int param_2; uint param_3;
{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  puVar1 = (undefined4 *)FUN_0802c9f0(0);
  if (param_3 < *(byte *)(puVar1 + 7)) {
    if (param_2 == 4) {
      if (param_1 - 4 < 4) {
        uVar3 = 1 << (param_1 & 0xff);
        if (((puVar1[5] & uVar3) == 0) || (*(uint *)(puVar1[4] + param_3 * 4) == param_1)) {
          if (puVar1[5] == 0) {
            FUN_0802b282(*(undefined4 *)*puVar1,*(undefined2 *)puVar1[2],0x80,0x80,0);
          }
          uVar2 = *(uint *)(puVar1[4] + param_3 * 4);
          if (uVar2 != 0) {
            puVar1[5] = puVar1[5] & ~(1 << (uVar2 & 0xff));
          }
          *(uint *)(puVar1[4] + param_3 * 4) = param_1;
          puVar1[5] = puVar1[5] | uVar3;
        }
        else {
          uVar4 = 0x24;
        }
      }
    }
    else {
      uVar3 = *(uint *)(puVar1[4] + param_3 * 4);
      if (uVar3 != 0) {
        puVar1[5] = puVar1[5] & ~(1 << (uVar3 & 0xff));
        *(undefined4 *)(puVar1[4] + param_3 * 4) = 0;
        if (puVar1[5] == 0) {
          FUN_0802b282(*(undefined4 *)*puVar1,*(undefined2 *)puVar1[2],0x80,0,0);
        }
      }
    }
  }
  else {
    uVar4 = 0x54;
  }
  return uVar4;
}




/* 0x0802c736 */
int FUN_0802c736(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; uint param_3; undefined4 param_4;
{
  ushort uVar1;
  ushort uVar2;
  undefined4 *puVar3;
  int iVar4;
  ushort *puVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  
  puVar3 = (undefined4 *)FUN_0802c9f0(param_1 & 0xff);
  if (puVar3 == (undefined4 *)0x0) {
    iVar4 = 0x16;
  }
  else {
    uVar7 = param_2 & 0xff;
    if (uVar7 < *(byte *)(puVar3 + 7)) {
      if (param_3 < 8) {
        puVar5 = (ushort *)puVar3[1];
        iVar6 = puVar5[1] * param_2 + (uint)*puVar5;
        uVar1 = puVar5[0x14];
        uVar2 = puVar5[0xe];
        iVar4 = FUN_0802c688(param_3,4,uVar7,(uint)puVar5[1],param_4);
        if ((iVar4 == 0) && (iVar4 = FUN_0802c874(4,uVar7), iVar4 == 0)) {
          iVar4 = FUN_0802b282(*(undefined4 *)*puVar3,(uint)uVar1 + iVar6 & 0xffff,7,param_3,0);
          if (iVar4 == 0) {
            uVar8 = 0;
            FUN_0802b282(*(undefined4 *)*puVar3,(uint)uVar2 + iVar6 & 0xffff,1);
            iVar4 = FUN_0802c9b0(param_1,param_2,1,uVar8);
            return iVar4;
          }
        }
      }
      else {
        iVar4 = 0xe;
      }
    }
    else {
      iVar4 = 0x54;
    }
  }
  return iVar4;
}




/* 0x0802c7ce */
int FUN_0802c7ce(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; uint param_3; uint param_4;
{
  ushort uVar1;
  ushort uVar2;
  undefined4 *puVar3;
  int iVar4;
  ushort *puVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  
  puVar3 = (undefined4 *)FUN_0802c9f0(param_1 & 0xff);
  if (puVar3 == (undefined4 *)0x0) {
    iVar4 = 0x16;
  }
  else {
    uVar7 = param_2 & 0xff;
    if (uVar7 < *(byte *)(puVar3 + 7)) {
      if (param_3 < 8) {
        if (param_4 < 4) {
          puVar5 = (ushort *)puVar3[1];
          iVar6 = puVar5[1] * uVar7 + (uint)*puVar5;
          uVar1 = puVar5[0x13];
          uVar2 = puVar5[0xe];
          iVar4 = FUN_0802c688(param_3,6,uVar7);
          if ((iVar4 == 0) && (iVar4 = FUN_0802c874(6,uVar7), iVar4 == 0)) {
            iVar4 = FUN_0802b282(*(undefined4 *)*puVar3,(uint)uVar1 + iVar6 & 0xffff,7,param_3,0);
            if (iVar4 == 0) {
              uVar8 = 0;
              iVar4 = FUN_0802b282(*(undefined4 *)*puVar3,(uint)uVar2 + iVar6 & 0xffff,3,param_4);
              if (iVar4 == 0) {
                iVar4 = FUN_0802c9b0(param_1,param_2,1,uVar8);
                return iVar4;
              }
            }
          }
        }
        else {
          iVar4 = 0xf;
        }
      }
      else {
        iVar4 = 0xe;
      }
    }
    else {
      iVar4 = 0x54;
    }
  }
  return iVar4;
}




/* 0x0802c874 */
undefined4 FUN_0802c874(param_1, param_2)
int param_1; short param_2;
{
  undefined4 *puVar1;
  undefined4 uVar2;
  short *psVar3;
  
  puVar1 = (undefined4 *)FUN_0802c9f0(0);
  if (puVar1 != (undefined4 *)0x0) {
    psVar3 = (short *)puVar1[1];
    uVar2 = FUN_0802b282(*(undefined4 *)*puVar1,psVar3[1] * param_2 + *psVar3 + psVar3[0xe],0x70,
                         (uint)(param_1 << 0x1c) >> 0x18,0);
    return uVar2;
  }
  return 0x16;
}




