/* Auto-generated: fhprg_8025ea0.c */
/* Functions: 13 */
#include "globals.h"

/* 0x08025ea0 */
void FUN_08025ea0()
{
  DAT_080586c0 = 0;
  DAT_080586c4 = 0;
  DAT_080586c8 = 0;
  DAT_080586cc = 0;
  return;
}




/* 0x08025eb4 */
void FUN_08025eb4(param_1, param_2)
int param_1; int param_2;
{
  if (param_1 == 0) {
    DAT_080586c0 = DAT_080586c0 + param_2;
    return;
  }
  if (param_1 != 1) {
    if (param_1 != 2) {
      if (param_1 == 3) {
        DAT_080586cc = DAT_080586cc + param_2;
      }
      return;
    }
    DAT_080586c8 = DAT_080586c8 + param_2;
    return;
  }
  DAT_080586c4 = DAT_080586c4 + param_2;
  return;
}




/* 0x08025ee8 */
undefined4 thunk_FUN_08025ee8(param_1, param_2, param_3)
undefined4 param_1; undefined4 * param_2; undefined2 * param_3;
{
  int iVar1;
  int extraout_r3;
  
  iVar1 = FUN_08026516();
  if (((iVar1 == 0) && (param_2 != (undefined4 *)0x0)) && (param_3 != (undefined2 *)0x0)) {
    *param_2 = *(undefined4 *)(extraout_r3 + 0xc);
    *param_3 = *(undefined2 *)(extraout_r3 + 0x10);
    return 0;
  }
  return 0xffffffff;
}




/* 0x08025ee8 */
undefined4 FUN_08025ee8(param_1, param_2, param_3)
undefined4 param_1; undefined4 * param_2; undefined2 * param_3;
{
  int iVar1;
  int extraout_r3;
  
  iVar1 = FUN_08026516();
  if (((iVar1 == 0) && (param_2 != (undefined4 *)0x0)) && (param_3 != (undefined2 *)0x0)) {
    *param_2 = *(undefined4 *)(extraout_r3 + 0xc);
    *param_3 = *(undefined2 *)(extraout_r3 + 0x10);
    return 0;
  }
  return 0xffffffff;
}




/* 0x08025f0e */
undefined4 thunk_FUN_08025f0e(param_1, param_2, param_3, param_4)
int param_1; uint param_2; undefined4 param_3; int param_4;
{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0802652e();
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  if ((param_2 <= param_2 + param_4) && (param_2 + param_4 <= *(uint *)(param_1 + 0xc))) {
    uVar2 = FUN_08013ca4(*(undefined4 *)(*(int *)(param_1 + 0x14) + 0x1c),
                         *(undefined4 *)(param_1 + 0x18),
                         param_2 + *(int *)(*(int *)(param_1 + 8) + 0x3c),param_3,param_4);
    return uVar2;
  }
  return 0xfffffecf;
}




/* 0x08025f0e */
undefined4 FUN_08025f0e(param_1, param_2, param_3, param_4)
int param_1; uint param_2; undefined4 param_3; int param_4;
{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0802652e();
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  if ((param_2 <= param_2 + param_4) && (param_2 + param_4 <= *(uint *)(param_1 + 0xc))) {
    uVar2 = FUN_08013ca4(*(undefined4 *)(*(int *)(param_1 + 0x14) + 0x1c),
                         *(undefined4 *)(param_1 + 0x18),
                         param_2 + *(int *)(*(int *)(param_1 + 8) + 0x3c),param_3,param_4);
    return uVar2;
  }
  return 0xfffffecf;
}




/* 0x08025f4e */
undefined4 thunk_FUN_08025f4e(param_1, param_2, param_3, param_4)
int param_1; uint param_2; undefined4 param_3; int param_4;
{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0802652e();
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  if ((param_2 <= param_2 + param_4) && (param_2 + param_4 <= *(uint *)(param_1 + 0xc))) {
    uVar2 = FUN_0801422c(*(undefined4 *)(*(int *)(param_1 + 0x14) + 0x1c),
                         *(undefined4 *)(param_1 + 0x18),
                         param_2 + *(int *)(*(int *)(param_1 + 8) + 0x3c),param_3,param_4);
    return uVar2;
  }
  return 0xfffffecf;
}




/* 0x08025f4e */
undefined4 FUN_08025f4e(param_1, param_2, param_3, param_4)
int param_1; uint param_2; undefined4 param_3; int param_4;
{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0802652e();
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  if ((param_2 <= param_2 + param_4) && (param_2 + param_4 <= *(uint *)(param_1 + 0xc))) {
    uVar2 = FUN_0801422c(*(undefined4 *)(*(int *)(param_1 + 0x14) + 0x1c),
                         *(undefined4 *)(param_1 + 0x18),
                         param_2 + *(int *)(*(int *)(param_1 + 8) + 0x3c),param_3,param_4);
    return uVar2;
  }
  return 0xfffffecf;
}




/* 0x08025f8e */
undefined4 FUN_08025f8e(param_1, param_2, param_3, param_4)
int param_1; uint param_2; int param_3; int param_4;
{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0802652e();
  if ((iVar1 != 0) || (param_3 == 0)) {
    return 0xffffffff;
  }
  if ((param_2 <= param_2 + param_4) && (param_2 + param_4 <= *(uint *)(param_1 + 0xc))) {
    uVar2 = FUN_080141ec(*(undefined4 *)(*(int *)(param_1 + 0x14) + 0x1c),
                         *(undefined4 *)(param_1 + 0x18),
                         param_2 + *(int *)(*(int *)(param_1 + 8) + 0x3c),param_3,param_4);
    return uVar2;
  }
  return 0xfffffecf;
}




/* 0x08025fd4 */
undefined4 FUN_08025fd4(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  undefined4 local_28;
  
  local_28 = param_4;
  iVar1 = FUN_08013c4c(*(undefined4 *)(param_1 + 0x1c),*(undefined4 *)(param_1 + 0x20));
  if (iVar1 == 1) {
    *(undefined4 *)(param_1 + 0x24) = 1;
  }
  else {
    *(undefined4 *)(param_1 + 0x24) = 0;
  }
  DAT_08050edc = FUN_080259b0(param_1);
  if (DAT_08050edc == 0) {
    uVar5 = 0xffffffff;
  }
  else {
    uVar7 = 0;
    do {
      local_28 = 0;
      iVar1 = FUN_08013c84(*(undefined4 *)(param_1 + 0x1c),&local_28,uVar7);
      if (iVar1 == 0) {
        iVar1 = FUN_08025b74(DAT_08050edc,local_28,uVar7 & 0xff);
        if ((iVar1 != 0) &&
           (iVar2 = FUN_08026dd8(*(undefined4 *)(param_1 + 0x1c),local_28), iVar2 != 0)) {
          uVar6 = 0;
          iVar8 = 1;
          iVar3 = FUN_08026240();
          if (iVar3 == 0) {
            iVar3 = -1;
          }
          else {
            do {
              iVar4 = FUN_080262ac(iVar3);
              if ((iVar4 == 0) || (iVar4 = FUN_08025ac4(iVar4,iVar8,iVar1), iVar4 == 0)) break;
              uVar6 = uVar6 + 1;
              iVar8 = iVar8 + 1;
            } while (uVar6 < 0x40);
            FUN_08026232(iVar3);
            iVar3 = 0;
          }
          if (((iVar3 != 0) && (iVar3 = FUN_08026ec2(iVar1,iVar2), iVar3 != 0)) &&
             (iVar2 = FUN_080260ac(iVar2), iVar2 == 0)) {
            FUN_08025a54(1,iVar1);
          }
        }
        FUN_08013a7c(*(undefined4 *)(param_1 + 0x1c),local_28);
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 < 8);
    uVar5 = 0;
  }
  return uVar5;
}




/* 0x080260ac */
undefined4 FUN_080260ac(param_1)
undefined4 param_1;
{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0802efd6(0,0,1,param_1);
  if ((((iVar1 == 0) || (*(char *)(iVar1 + 0x1fe) != 'U')) || (*(char *)(iVar1 + 0x1ff) != -0x56))
     || ((*(char *)(iVar1 + 0xb) != '\0' || (*(char *)(iVar1 + 0xc) != '\x02')))) {
    iVar1 = -1;
  }
  else {
    iVar1 = 0;
  }
  uVar2 = 0;
  if (iVar1 != 0) {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}




/* 0x080260e8 */
int FUN_080260e8(param_1)
undefined4 param_1;
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = 0;
  do {
    if (DAT_0804d658 <= iVar3) {
      return iVar2;
    }
    if (((&DAT_08054d38)[iVar3 * 0xe] == 0) && ((&DAT_08054d34)[iVar3 * 0x38] != '\x01')) {
      iVar2 = (&DAT_08054d60)[iVar3 * 0xe];
      while (((iVar2 != 0 && (iVar1 = FUN_08006d64(iVar2 + 0x14,param_1), iVar1 != 0)) &&
             ((*(int *)(iVar2 + 0x10) == 0 ||
              (iVar1 = FUN_08006d64(*(int *)(iVar2 + 0x10),param_1), iVar1 != 0))))) {
        iVar2 = *(int *)(iVar2 + 0x48);
      }
      if (iVar2 != 0) {
        return iVar2;
      }
    }
    iVar3 = iVar3 + 1;
  } while( true );
}




/* 0x08026144 */
char * FUN_08026144(param_1)
int param_1;
{
  int iVar1;
  char *pcVar2;
  int iVar3;
  
  pcVar2 = (char *)0x0;
  if (param_1 == 0) {
    pcVar2 = (char *)0x0;
  }
  else {
    for (iVar3 = 0; iVar3 < DAT_0804d658; iVar3 = iVar3 + 1) {
      pcVar2 = &DAT_08054d34 + iVar3 * 0x38;
      if ((((&DAT_08054d38)[iVar3 * 0xe] == 0) && (*pcVar2 != '\x01')) &&
         (iVar1 = FUN_08006d64(&DAT_08054d3c + iVar3 * 0x38,param_1), iVar1 == 0)) break;
    }
    if (iVar3 == DAT_0804d658) {
      pcVar2 = (char *)0x0;
    }
  }
  return pcVar2;
}




