/* Auto-generated: fhprg_80263c0.c */
/* Functions: 9 */
#include "globals.h"

/* 0x080263c0 */
void FUN_080263c0()
{
  FUN_08006d14(&DAT_080586d0,0x15f8);
  DAT_0804e2a4 = 0;
  return;
}




/* 0x080264c4 */
undefined4 FUN_080264c4(param_1)
int param_1;
{
  char cVar1;
  int iVar2;
  
  cVar1 = *(char *)(param_1 + 0x2a);
  if (cVar1 != '\x02') {
    if (cVar1 == '\x03') {
      if ((*(char *)(param_1 + 0x2a) == '\x03') &&
         (iVar2 = FUN_08006898(param_1 + 0x2c,&DAT_0803b365,0x10), iVar2 == 0)) {
        return 1;
      }
      return 0;
    }
    if (cVar1 == '\x04') {
      if (*(char *)(param_1 + 0x2a) != '\x04') {
        return 0;
      }
      iVar2 = *(int *)(param_1 + 0x2c);
      if (iVar2 == 0xb) {
        return 1;
      }
      if (iVar2 < 0xc) {
        if (iVar2 == 1) {
          return 1;
        }
        if (iVar2 == 4) {
          return 1;
        }
        if (iVar2 == 6) {
          return 1;
        }
      }
      else {
        if (iVar2 == 0xc) {
          return 1;
        }
        if (iVar2 == 0xe) {
          return 1;
        }
      }
      return 0;
    }
    if (cVar1 == '\x05') {
      return 1;
    }
  }
  return 0;
}




/* 0x08026516 */
undefined4 FUN_08026516(param_1)
int * param_1;
{
  if (((param_1 != (int *)0x0) && (*param_1 == 1)) && (param_1[5] != 0)) {
    return 0;
  }
  return 0xffffffff;
}




/* 0x0802652e */
undefined4 FUN_0802652e(param_1)
int param_1;
{
  int iVar1;
  
  iVar1 = FUN_08026516();
  if ((((iVar1 == 0) && (iVar1 = FUN_0802656e(*(undefined4 *)(param_1 + 0x14)), iVar1 == 0)) &&
      (iVar1 = FUN_0802655c(*(undefined4 *)(param_1 + 8)), iVar1 == 0)) &&
     ((*(int *)(param_1 + 4) == 0 && (*(int *)(param_1 + 0x18) != 0)))) {
    return 0;
  }
  return 0xffffffff;
}




/* 0x0802655c */
undefined4 FUN_0802655c(param_1)
int param_1;
{
  if ((param_1 != 0) && (*(int *)(param_1 + 0x44) != 0)) {
    return 0;
  }
  return 0xffffffff;
}




/* 0x0802656e */
undefined4 FUN_0802656e(param_1)
undefined1 * param_1;
{
  if (param_1 != (undefined1 *)0x0) {
    switch(*param_1) {
    case 0:
    case 1:
      break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      return 0;
    default:
      FUN_08015a50();
      return 0;
    }
  }
  return 0xffffffff;
}




/* 0x08026594 */
undefined4 FUN_08026594(param_1)
int param_1;
{
  if (param_1 != 0) {
    FUN_08006d14(param_1,0x44);
    return 0;
  }
  return 0xffffffff;
}




/* 0x080265a8 */
int FUN_080265a8(param_1)
int param_1;
{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  
  if (param_1 == 0) {
    iVar4 = 0;
  }
  else {
    iVar3 = param_1 + 0x10;
    FUN_08006d14(iVar3,0x34);
    cVar1 = *(char *)(param_1 + 5);
    if (cVar1 == '\0') {
      iVar4 = FUN_08026674(param_1);
    }
    else {
      if ((cVar1 == '\x01') || (cVar1 == '\x02')) {
        iVar6 = FUN_080266cc(param_1);
      }
      else {
        if (cVar1 != '\x03') {
          return 0;
        }
        do {
          FUN_080266cc(param_1);
          if (*(int *)(param_1 + 0xc) == 0) {
            iVar6 = 0;
            goto LAB_08026604;
          }
          iVar4 = FUN_080264c4();
        } while (iVar4 == 0);
        iVar6 = *(int *)(param_1 + 0xc);
      }
LAB_08026604:
      iVar4 = 0;
      if (iVar6 != 0) {
        FUN_080382c2(iVar3,iVar6 + 0x14,0x14);
        *(undefined1 *)(param_1 + 0x24) = *(undefined1 *)(*(int *)(iVar6 + 0x44) + 1);
        uVar5 = FUN_080264c4(iVar6);
        *(undefined4 *)(param_1 + 0x28) = uVar5;
        if (*(char *)(iVar6 + 0x2a) == '\x04') {
          iVar4 = *(int *)(iVar6 + 0x2c);
          if ((iVar4 == 5) || (iVar4 == 0xf)) {
            iVar4 = 0xffff;
          }
        }
        else {
          iVar4 = 0;
        }
        *(int *)(param_1 + 0x2c) = iVar4;
        *(undefined1 *)(param_1 + 0x30) = *(undefined1 *)(iVar6 + 0x29);
        if ((*(char *)(iVar6 + 0x2a) == '\x01') || (*(char *)(iVar6 + 0x2a) == '\x02')) {
          uVar2 = 1;
        }
        else {
          uVar2 = 0;
        }
        *(undefined1 *)(param_1 + 0x31) = uVar2;
        *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(iVar6 + 4);
        *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(iVar6 + 8);
        *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(iVar6 + 0xc);
        *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(*(int *)(iVar6 + 0x44) + 0x24);
        iVar4 = iVar3;
      }
    }
  }
  return iVar4;
}




/* 0x08026674 */
int FUN_08026674(param_1)
int param_1;
{
  char *pcVar1;
  
  FUN_08026734();
  if (*(int *)(param_1 + 8) != 0) {
    FUN_080382c2(param_1 + 0x10,*(int *)(param_1 + 8) + 8,0x14);
    pcVar1 = *(char **)(param_1 + 8);
    *(char *)(param_1 + 0x24) = pcVar1[1];
    *(uint *)(param_1 + 0x34) = (uint)(*pcVar1 == '\x04');
    *(uint *)(param_1 + 0x38) = (uint)(*pcVar1 == '\a');
    *(uint *)(param_1 + 0x3c) = (uint)(*pcVar1 == '\x06');
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(pcVar1 + 0x24);
    return param_1 + 0x10;
  }
  return 0;
}




