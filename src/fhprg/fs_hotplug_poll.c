/* Auto-generated: fs_hotplug_poll.c */
/* Functions: 8 */
#include "globals.h"

/* 0x08026c60 */
void FUN_08026c60(param_1, param_2)
uint param_1; undefined4 param_2;
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  char *pcVar5;
  
  iVar4 = 0;
LAB_08026cd4:
  if (DAT_0804d658 <= iVar4) {
    return;
  }
  pcVar5 = &DAT_08054d34 + iVar4 * 0x38;
  cVar1 = *pcVar5;
  if ((param_1 == 8) || ((byte)(&DAT_08054d35)[iVar4 * 0x38] == param_1))
  goto switchD_08026c8a_switchD;
  goto LAB_08026cd2;
switchD_08026c8a_switchD:
  switch(cVar1) {
  case '\0':
    iVar2 = FUN_08013ce4((&DAT_08054d50)[iVar4 * 0xe],(&DAT_08054d54)[iVar4 * 0xe]);
    if (iVar2 == 0) {
      uVar3 = 2;
    }
    else {
      uVar3 = 1;
    }
    FUN_08025c98(pcVar5,uVar3);
    break;
  case '\x01':
    if ((&DAT_08054d64)[iVar4 * 0xe] != 0) {
      ((code*)DAT_0804cd60)("fs_hotplug_poll.c",0x70,0x302f);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    break;
  case '\x02':
    FUN_08026d14(pcVar5,param_2);
    break;
  case '\x03':
    break;
  default:
    FUN_08015a50();
  }
  if (*pcVar5 == cVar1) {
LAB_08026cd2:
    iVar4 = iVar4 + 1;
  }
  goto LAB_08026cd4;
}




/* 0x08026d00 */
undefined4 thunk_FUN_08026d00(param_1)
int param_1;
{
  if (param_1 != 0) {
    FUN_08026c60();
    return 0;
  }
  return 0xffffffff;
}




/* 0x08026d00 */
undefined4 FUN_08026d00(param_1)
int param_1;
{
  if (param_1 != 0) {
    FUN_08026c60();
    return 0;
  }
  return 0xffffffff;
}




/* 0x08026d14 */
void FUN_08026d14(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  undefined4 uVar2;
  
  FUN_08026f34();
  if (*(int *)(param_1 + 0x20) != 0) {
    ((code*)DAT_0804cd60)("fs_hotplug_poll.c",0xec);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (*(int *)(param_1 + 0x2c) != 0) {
    ((code*)DAT_0804cd60)("fs_hotplug_poll.c",0xed);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  *(undefined4 *)(param_1 + 0x30) = 0;
  if (param_2 != 2) {
    iVar1 = FUN_08013c4c(*(undefined4 *)(param_1 + 0x1c),0,0x302f);
    if (iVar1 == 1) {
      if (param_2 != 0) goto LAB_08026da4;
    }
    else if ((iVar1 == 0) && (param_2 != 1)) goto LAB_08026da4;
  }
  uVar2 = FUN_08013bd4(*(undefined4 *)(param_1 + 0x1c),0);
  iVar1 = FUN_08013c84(*(undefined4 *)(param_1 + 0x1c),param_1 + 0x20,uVar2);
  if ((iVar1 != 0) ||
     (iVar1 = FUN_08013c68(*(undefined4 *)(param_1 + 0x1c),*(undefined4 *)(param_1 + 0x20)),
     iVar1 != 1)) goto LAB_08026da4;
  if (param_2 != 2) {
    iVar1 = FUN_08013c4c(*(undefined4 *)(param_1 + 0x1c),*(undefined4 *)(param_1 + 0x20));
    if (iVar1 == 1) {
      if (param_2 != 0) goto LAB_08026da4;
    }
    else if ((iVar1 != 0) || (param_2 != 1)) goto LAB_08026da4;
  }
  iVar1 = FUN_08025fd4(param_1);
  if (iVar1 == 0) {
    FUN_08025c98(param_1,3);
    return;
  }
LAB_08026da4:
  if (*(int *)(param_1 + 0x20) != 0) {
    FUN_08013a7c(*(undefined4 *)(param_1 + 0x1c));
    *(undefined4 *)(param_1 + 0x20) = 0;
  }
  return;
}




/* 0x08026dd8 */
undefined4 * FUN_08026dd8(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; uint param_4;
{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint local_18;
  uint local_14;
  
  local_18 = 0;
  local_14 = param_4 & 0xffff0000;
  iVar1 = FUN_08013bb0(param_1,param_2,&local_18,&local_14);
  if (iVar1 == 0) {
    uVar3 = local_14 & 0xffff;
    if (((uVar3 < 0x201) && (uVar3 != 0)) && (local_18 != 0)) {
      DAT_0805a448 = (undefined2)local_14;
      DAT_0805a44c = local_18;
      DAT_0805a450 = DAT_0805124c;
      DAT_0805a454 = DAT_08051250 / uVar3;
      if (local_18 < DAT_08051250 / uVar3) {
        DAT_0805a454 = local_18;
      }
      DAT_0805a440 = param_1;
      DAT_0805a444 = param_2;
      iVar1 = FUN_0802ef24(0,0,&DAT_0805a440,1);
      puVar2 = (undefined4 *)0x0;
      if (iVar1 != 0) {
        puVar2 = &DAT_0805a440;
      }
      return puVar2;
    }
  }
  return (undefined4 *)0x0;
}




/* 0x08026e44 */
void FUN_08026e44(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_1 + 0x30);
  if (*(int *)(param_1 + 0x30) == param_2) {
    uVar2 = 0;
    if (param_2 != 0) {
      uVar2 = *(undefined4 *)(param_2 + 0x1c);
    }
    *(undefined4 *)(param_1 + 0x30) = uVar2;
    return;
  }
  do {
    iVar3 = iVar1;
    if (iVar3 == 0) {
      return;
    }
    iVar1 = *(int *)(iVar3 + 0x1c);
  } while (*(int *)(iVar3 + 0x1c) != param_2);
  *(undefined4 *)(iVar3 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
  return;
}




/* 0x08026ea8 */
void FUN_08026ea8()
{
  int iVar1;
  
  iVar1 = FUN_08026144();
  if ((iVar1 != 0) && (*(int *)(iVar1 + 0x2c) == 0)) {
    FUN_08025fd4();
    return;
  }
  return;
}




/* 0x08026ec2 */
undefined4 FUN_08026ec2(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  iVar6 = 1;
  uVar5 = 0;
  iVar1 = FUN_0802686c(param_2);
  if (iVar1 == 0) {
    return 0xffffffff;
  }
LAB_08026f1e:
  do {
    iVar4 = FUN_0802692c(iVar1);
    if ((iVar4 == 0) || (iVar4 = FUN_08025c08(iVar4,iVar6,0x70,param_1), iVar4 == 0)) {
LAB_08026f28:
      FUN_08026860(iVar1);
      return 0;
    }
    iVar6 = iVar6 + 1;
    uVar5 = uVar5 + 1;
    iVar2 = FUN_0802680c(iVar1);
    if (iVar2 == 0) {
      iVar2 = 1;
      while (iVar3 = FUN_08026890(iVar1), iVar3 != 0) {
        if (0x3f < uVar5) goto LAB_08026f28;
        iVar3 = FUN_08025c08(iVar3,iVar2,0x65,iVar4);
        if (iVar3 == 0) goto LAB_08026f1e;
        iVar2 = iVar2 + 1;
        uVar5 = uVar5 + 1;
      }
    }
    if (0x3f < uVar5) goto LAB_08026f28;
  } while( true );
}




