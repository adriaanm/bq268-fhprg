/* Auto-generated: fhprg_8026734.c */
/* Functions: 14 */
#include "globals.h"

/* 0x08026734 */
void FUN_08026734(param_1)
int param_1;
{
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  
  pcVar3 = *(char **)(param_1 + 8);
  for (iVar2 = 0; pcVar1 = (char *)0x0, iVar2 < DAT_0804d658; iVar2 = iVar2 + 1) {
    pcVar1 = &DAT_08054d34 + iVar2 * 0x38;
    if ((((&DAT_08054d38)[iVar2 * 0xe] == 0) && (*pcVar1 != '\x01')) &&
       ((*(char *)(param_1 + 4) == '\b' || ((&DAT_08054d35)[iVar2 * 0x38] == *(char *)(param_1 + 4))
        ))) {
      if (*(char *)(param_1 + 6) == '\0') {
        if ((&DAT_08054d58)[iVar2 * 0xe] != 0) goto LAB_08026778;
      }
      else if ((*(char *)(param_1 + 6) != '\x01') || ((&DAT_08054d58)[iVar2 * 0xe] == 0)) {
LAB_08026778:
        if (pcVar3 == (char *)0x0) break;
        if (pcVar3 == pcVar1) {
          pcVar3 = (char *)0x0;
        }
      }
    }
  }
  *(char **)(param_1 + 8) = pcVar1;
  return;
}




/* 0x08026798 */
undefined4 FUN_08026798(param_1)
int param_1;
{
  int iVar1;
  
  if (*(int *)(param_1 + 0xc) == 0) goto LAB_080267a4;
  iVar1 = *(int *)(*(int *)(param_1 + 0xc) + 0x48);
  while( true ) {
    *(int *)(param_1 + 0xc) = iVar1;
    if (iVar1 != 0) {
      return 0;
    }
LAB_080267a4:
    FUN_08026734(param_1);
    if (*(int *)(param_1 + 8) == 0) break;
    iVar1 = *(int *)(*(int *)(param_1 + 8) + 0x2c);
  }
  return 0xffffffff;
}




/* 0x080267cc */
undefined4 FUN_080267cc(param_1, param_2, param_3)
undefined1 param_1; undefined1 param_2; undefined1 param_3;
{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)0x0;
  iVar2 = 0;
  do {
    if ((&DAT_08054e4c)[iVar2 * 0x11] == 0) {
      (&DAT_08054e4c)[iVar2 * 0x11] = 1;
      puVar1 = &DAT_08054e4c + iVar2 * 0x11;
      break;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 1);
  if (puVar1 != (undefined4 *)0x0) {
    *(undefined1 *)(puVar1 + 1) = param_1;
    *(undefined1 *)((int)puVar1 + 5) = param_2;
    *(undefined1 *)((int)puVar1 + 6) = param_3;
    puVar1[2] = 0;
    puVar1[3] = 0;
  }
  return 0;
}




/* 0x0802680c */
undefined4 FUN_0802680c(param_1)
undefined4 * param_1;
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (((param_1 != (undefined4 *)0x0) &&
      (*(undefined1 *)(param_1 + 2) = 0, *(byte *)((int)param_1 + 9) < 4)) &&
     (iVar2 = FUN_0802efd6(param_1[4],param_1[5],1,param_1[9]), iVar2 != 0)) {
    iVar2 = iVar2 + (uint)*(byte *)((int)param_1 + 9) * 0x10;
    cVar1 = *(char *)(iVar2 + 0x1c2);
    if ((cVar1 == '\x05') || (cVar1 == '\x0f')) {
      iVar2 = iVar2 + 0x1c6;
      uVar3 = FUN_08006e04(iVar2);
      *param_1 = uVar3;
      uVar3 = FUN_08006e04(iVar2);
      param_1[1] = uVar3;
      *(undefined1 *)(param_1 + 2) = 1;
      return 0;
    }
  }
  return 0xffffffff;
}




/* 0x08026860 */
undefined4 FUN_08026860(param_1)
int param_1;
{
  if (param_1 != 0) {
    return 0;
  }
  return 0xffffffff;
}




/* 0x0802686c */
undefined * FUN_0802686c(param_1)
undefined4 param_1;
{
  int iVar1;
  undefined *puVar2;
  
  DAT_0805a68c = param_1;
  iVar1 = FUN_08019c1c();
  puVar2 = (undefined *)0x0;
  if (iVar1 == 0) {
    DAT_0805a678 = 0;
    DAT_0805a67c = 0;
    DAT_0805a671 = 0;
    puVar2 = &DAT_0805a668;
    DAT_0805a672 = 0;
  }
  return puVar2;
}




/* 0x08026890 */
int * FUN_08026890(param_1)
int * param_1;
{
  int iVar1;
  int iVar2;
  
  if (param_1 != (int *)0x0) {
    if ((char)param_1[2] == '\0') {
      return (int *)0x0;
    }
    iVar1 = FUN_0802efd6(*param_1,0,1,param_1[9]);
    if ((((iVar1 != 0) && (*(char *)(iVar1 + 0x1fe) == 'U')) && (*(char *)(iVar1 + 0x1ff) == -0x56))
       && (*(char *)(iVar1 + 0x1c2) != '\0')) {
      iVar2 = FUN_08006e04(iVar1 + 0x1ca);
      if (iVar2 != 0) {
        *(undefined1 *)(param_1 + 6) = *(undefined1 *)(iVar1 + 0x1be);
        *(undefined1 *)((int)param_1 + 0x19) = *(undefined1 *)(iVar1 + 0x1c2);
        iVar2 = FUN_08006e04(iVar1 + 0x1c6);
        param_1[7] = iVar2 + *param_1;
        iVar2 = FUN_08006e04(iVar1 + 0x1ca);
        param_1[8] = iVar2;
        iVar2 = FUN_08006e04(iVar1 + 0x1da);
        if ((iVar2 == 0) || (*(char *)(iVar1 + 0x1d2) != '\x05')) {
          *(undefined1 *)(param_1 + 2) = 0;
        }
        else {
          iVar1 = FUN_08006e04(iVar1 + 0x1d6);
          *param_1 = iVar1 + param_1[1];
        }
        return param_1 + 6;
      }
    }
    *(undefined1 *)(param_1 + 2) = 0;
  }
  return (int *)0x0;
}




/* 0x0802692c */
int FUN_0802692c(param_1)
int param_1;
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  
  if (((param_1 != 0) && (*(byte *)(param_1 + 10) < 4)) &&
     (iVar1 = FUN_0802efd6(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x14),1,
                           *(undefined4 *)(param_1 + 0x24)), iVar1 != 0)) {
    uVar2 = (uint)*(byte *)(param_1 + 10);
    do {
      iVar4 = iVar1 + uVar2 * 0x10;
      if (*(char *)(iVar4 + 0x1c2) != '\0') {
        *(char *)(param_1 + 9) = (char)uVar2;
        *(char *)(param_1 + 10) = (char)uVar2 + '\x01';
        *(undefined1 *)(param_1 + 0x18) = *(undefined1 *)(iVar4 + 0x1be);
        *(undefined1 *)(param_1 + 0x19) = *(undefined1 *)(iVar4 + 0x1c2);
        uVar3 = FUN_08006e04(iVar4 + 0x1c6);
        *(undefined4 *)(param_1 + 0x1c) = uVar3;
        uVar3 = FUN_08006e04(iVar4 + 0x1ca);
        *(undefined4 *)(param_1 + 0x20) = uVar3;
        return param_1 + 0x18;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < 4);
  }
  return 0;
}




/* 0x0802698c */
ulonglong FUN_0802698c(param_1, param_2, param_3, param_4)
byte * param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_20;
  undefined4 local_1c;
  undefined4 uStack_18;
  
  iVar6 = 0;
  iVar8 = 0;
  local_20 = 0;
  uVar1 = 0;
  if (param_1 == (byte *)0x0) {
LAB_0802699a:
    return (ulonglong)uVar1;
  }
  while( true ) {
    uVar1 = (uint)*param_1;
    if (uVar1 != 0x2f) break;
    if (param_1[1] != 0x2f) goto LAB_080269aa;
    param_1 = param_1 + 1;
  }
  if (*param_1 == 0) goto LAB_0802699a;
LAB_080269aa:
  local_1c = param_3;
  uStack_18 = param_4;
  FUN_08026ea8(param_1);
  iVar2 = FUN_080260e8(param_1);
  if (((((iVar2 != 0) && (iVar3 = FUN_0802655c(), iVar3 == 0)) && (*(int *)(iVar2 + 0xc) == 0)) &&
      ((*(int *)(iVar2 + 8) == 0 &&
       (iVar3 = FUN_0802656e(*(undefined4 *)(iVar2 + 0x44)), iVar3 == 0)))) &&
     (iVar6 = FUN_080262e0(), iVar6 != 0)) {
    iVar7 = iVar2 + 0x14;
    iVar3 = FUN_08006906(iVar7);
    iVar4 = 0;
    for (; 1 < iVar3; iVar3 = iVar3 + -1) {
      if (((*(char *)(iVar7 + iVar4) == 'h') || (*(char *)(iVar7 + iVar4) == 'H')) &&
         (*(byte *)(iVar7 + iVar4 + 1) - 0x30 < 10)) {
        iVar8 = *(byte *)(iVar4 + iVar7 + 1) - 0x30;
        break;
      }
      iVar4 = iVar4 + 1;
    }
    iVar8 = FUN_08013c84(*(undefined4 *)(*(int *)(iVar2 + 0x44) + 0x1c),&local_20,iVar8);
    if ((iVar8 == 0) &&
       (iVar8 = FUN_08013bb0(*(undefined4 *)(*(int *)(iVar2 + 0x44) + 0x1c),local_20,&uStack_18,
                             &local_1c), iVar8 == 0)) {
      *(undefined4 *)(iVar6 + 0xc) = *(undefined4 *)(iVar2 + 0x40);
      *(undefined2 *)(iVar6 + 0x10) = (undefined2)local_1c;
      FUN_08025bf0(*(undefined4 *)(iVar2 + 0x44),iVar6);
      *(int *)(iVar6 + 0x18) = local_20;
      uVar5 = *(undefined4 *)(iVar2 + 0x44);
      *(int *)(iVar6 + 8) = iVar2;
      *(undefined4 *)(iVar6 + 0x14) = uVar5;
      FUN_08026b44(iVar2);
      goto LAB_08026a48;
    }
  }
  if (local_20 != 0) {
    FUN_08013a7c(*(undefined4 *)(*(int *)(iVar2 + 0x44) + 0x1c));
  }
  if (iVar6 != 0) {
    FUN_08026320(iVar6);
  }
LAB_08026a48:
  return CONCAT44(local_20,iVar6);
}




/* 0x08026a70 */
undefined4 thunk_FUN_08026a70(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  iVar1 = FUN_080267cc(param_1,2,param_2);
  if (iVar1 != 0) {
    do {
      iVar2 = FUN_080265a8(iVar1);
      if (iVar2 == 0) goto LAB_08026aae;
    } while ((*(char *)(*(int *)(iVar1 + 0xc) + 0x2a) != '\x03') ||
            (iVar3 = FUN_08006898(*(int *)(iVar1 + 0xc) + 0x2c,param_3,0x10), iVar3 != 0));
    uVar4 = FUN_0802698c(iVar2);
LAB_08026aae:
    FUN_08026594(iVar1);
  }
  return uVar4;
}




/* 0x08026a70 */
undefined4 FUN_08026a70(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  iVar1 = FUN_080267cc(param_1,2,param_2);
  if (iVar1 != 0) {
    do {
      iVar2 = FUN_080265a8(iVar1);
      if (iVar2 == 0) goto LAB_08026aae;
    } while ((*(char *)(*(int *)(iVar1 + 0xc) + 0x2a) != '\x03') ||
            (iVar3 = FUN_08006898(*(int *)(iVar1 + 0xc) + 0x2c,param_3,0x10), iVar3 != 0));
    uVar4 = FUN_0802698c(iVar2);
LAB_08026aae:
    FUN_08026594(iVar1);
  }
  return uVar4;
}




/* 0x08026aba */
undefined4 thunk_FUN_08026aba(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; int param_3;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  iVar1 = FUN_080267cc(param_1,2,param_2);
  if (iVar1 != 0) {
    do {
      iVar2 = FUN_080265a8(iVar1);
      if (iVar2 == 0) goto LAB_08026ae8;
    } while ((*(char *)(*(int *)(iVar1 + 0xc) + 0x2a) != '\x04') ||
            (*(int *)(iVar2 + 0x1c) != param_3));
    uVar3 = FUN_0802698c();
LAB_08026ae8:
    FUN_08026594(iVar1);
  }
  return uVar3;
}




/* 0x08026aba */
undefined4 FUN_08026aba(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; int param_3;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  iVar1 = FUN_080267cc(param_1,2,param_2);
  if (iVar1 != 0) {
    do {
      iVar2 = FUN_080265a8(iVar1);
      if (iVar2 == 0) goto LAB_08026ae8;
    } while ((*(char *)(*(int *)(iVar1 + 0xc) + 0x2a) != '\x04') ||
            (*(int *)(iVar2 + 0x1c) != param_3));
    uVar3 = FUN_0802698c();
LAB_08026ae8:
    FUN_08026594(iVar1);
  }
  return uVar3;
}




/* 0x08026af8 */
undefined4 * FUN_08026af8()
{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = 0;
  do {
    if ((&DAT_080586d0)[iVar1 * 0x13] == 0) {
      puVar2 = &DAT_080586d0 + iVar1 * 0x13;
      FUN_08006d14(puVar2,0x4c);
      *puVar2 = 1;
      DAT_0804e2a4 = DAT_0804e2a4 + 1;
      return puVar2;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x4a);
  return (undefined4 *)0x0;
}




