/* Auto-generated: boot_sdcc_hotplug.c */
/* Functions: 11 */
#include "globals.h"

/* 0x0801bb3c */
undefined4 FUN_0801bb3c(param_1, param_2, param_3, param_4, param_5, param_6)
int param_1; undefined4 param_2; uint param_3; uint param_4; uint param_5; uint param_6;
{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint extraout_r2;
  int extraout_r2_00;
  uint uVar5;
  int *piVar6;
  undefined4 uVar7;
  code *pcVar8;
  
  uVar7 = 0;
  iVar2 = (short)*(undefined4 *)(&DAT_08039660 + (param_6 & 0xffff) * 4) * 0xc;
  piVar6 = (int *)(&DAT_08053ec0 + iVar2);
  uVar5 = *(uint *)(&DAT_08053ec8 + iVar2);
  if ((uVar5 == 0) || (0x1000 < uVar5)) {
    ((code*)DAT_0804cd60)("boot_sdcc_hotplug.c",0x2ac,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  pcVar8 = DAT_0804cd60;
  uVar1 = FUN_080060c0(param_3,param_4,uVar5,0,0,DAT_0804cd60,param_1,param_2,param_3);
  FUN_080060c0(param_3,param_4,uVar5,0);
  if (uVar5 <= extraout_r2) {
    (*pcVar8)("boot_sdcc_hotplug.c",0x2b0,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar4 = param_4 + CARRY4(param_3,param_5);
  if (uVar4 <= param_4 && (uint)(param_3 <= param_3 + param_5) <= uVar4 - param_4) {
    (*pcVar8)("boot_sdcc_hotplug.c",0x2b2,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar4 = FUN_080060c0(param_3 + param_5,param_4 + CARRY4(param_3,param_5),uVar5,0);
  FUN_080060c0(param_3 + param_5,param_4 + CARRY4(param_3,param_5),uVar5,0);
  if (param_5 == 0) {
    return 1;
  }
  if (*piVar6 == 0) {
    return uVar7;
  }
  if (extraout_r2 != 0) {
    iVar2 = thunk_FUN_08025f0e(*piVar6,uVar1,&DAT_08052ec0,1);
    if (iVar2 != 0) {
      return uVar7;
    }
    if (uVar4 == uVar1) {
      if (uVar5 < param_5 + extraout_r2) {
        return uVar7;
      }
      FUN_08030b34(&DAT_08052ec0 + extraout_r2,param_1,param_5);
      iVar2 = thunk_FUN_08025f4e(*piVar6,uVar1,&DAT_08052ec0,1);
      goto joined_r0x0801bc42;
    }
    FUN_08030b34(&DAT_08052ec0 + extraout_r2,param_1,uVar5 - extraout_r2);
    param_1 = param_1 + (uVar5 - extraout_r2);
    iVar2 = thunk_FUN_08025f4e(*piVar6,uVar1,&DAT_08052ec0,1);
    if (iVar2 != 0) {
      return uVar7;
    }
    uVar1 = uVar1 + 1;
  }
  for (; uVar1 < uVar4; uVar1 = uVar1 + uVar3) {
    uVar3 = uVar4 - uVar1;
    if (0xffff < uVar3) {
      uVar3 = 0xffff;
    }
    uVar3 = uVar3 & 0xffff;
    iVar2 = thunk_FUN_08025f4e(*piVar6,uVar1,param_1,uVar3);
    if (iVar2 != 0) {
      uVar7 = 0;
      break;
    }
    param_1 = uVar3 * uVar5 + param_1;
  }
  if (uVar1 != uVar4) {
    return uVar7;
  }
  if (extraout_r2_00 == 0) {
    return 1;
  }
  iVar2 = thunk_FUN_08025f0e(*piVar6,uVar4,&DAT_08052ec0,1);
  if (iVar2 != 0) {
    return uVar7;
  }
  FUN_08030b34(&DAT_08052ec0,param_1,extraout_r2_00);
  iVar2 = thunk_FUN_08025f4e(*piVar6,uVar4,&DAT_08052ec0,1);
joined_r0x0801bc42:
  if (iVar2 == 0) {
    return 1;
  }
  return uVar7;
}




/* 0x08021e98 */
uint FUN_08021e98(param_1)
uint param_1;
{
  bool bVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  
  uVar8 = 0;
  uVar7 = 0;
  if (param_1 == 0) {
    ((code*)DAT_0804cd60)("boot_sdcc_hotplug.c",0x103,0x3013);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar3 = FUN_08016e54();
  if (iVar3 != 5) {
    if (iVar3 != 4) {
      if (iVar3 == 8) {
        uVar7 = 7;
      }
      goto LAB_08021eda;
    }
    uVar8 = 1;
  }
  uVar7 = 1;
LAB_08021eda:
  if (DAT_0804d00f == '\0') {
    sVar2 = thunk_FUN_08026d00(uVar7,uVar8);
    if (sVar2 != 0) {
      ((code*)DAT_0804cd60)("boot_sdcc_hotplug.c",0x11c,0x3046);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    DAT_0804d00f = '\x01';
  }
  uVar6 = (uint)(short)*(undefined4 *)(&DAT_08039660 + (param_1 & 0xffff) * 4);
  if (uVar6 == 0xffffffff) {
    ((code*)DAT_0804cd60)("boot_sdcc_hotplug.c",0x122,0x3008);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (0xc < uVar6) {
    ((code*)DAT_0804cd60)("boot_sdcc_hotplug.c",0x123);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  puVar5 = (undefined4 *)(&DAT_0804d010 + uVar6 * 0x14);
  bVar1 = true;
  if (puVar5 == (undefined4 *)0x0) {
    ((code*)DAT_0804cd60)("boot_sdcc_hotplug.c",0xcd,0x300d);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar4 = 1;
  do {
    if (*(char *)((int)puVar5 + uVar4) != '\0') {
      bVar1 = false;
      break;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < 0x14);
  if (bVar1) {
    uVar8 = thunk_FUN_08026aba(uVar7,uVar8,*puVar5);
  }
  else {
    uVar8 = thunk_FUN_08026a70(uVar7,uVar8);
  }
  *(undefined4 *)(&DAT_08053ec0 + uVar6 * 0xc) = uVar8;
  if (*(int *)(&DAT_08053ec0 + uVar6 * 0xc) == 0) {
    uVar6 = 0xffffffff;
  }
  else {
    iVar3 = uVar6 * 0xc;
    sVar2 = FUN_08025ee8(*(int *)(&DAT_08053ec0 + uVar6 * 0xc),&DAT_08053ec4 + iVar3,
                         &DAT_08053ec8 + iVar3);
    if (sVar2 != 0) {
      ((code*)DAT_0804cd60)("boot_sdcc_hotplug.c",0x145,0x3046);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if ((*(int *)(&DAT_08053ec4 + iVar3) == 0) && (*(int *)(&DAT_08053ec8 + iVar3) == 0)) {
      ((code*)DAT_0804cd60)("boot_sdcc_hotplug.c",0x148,0x3048);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
  }
  return uVar6;
}




/* 0x08025d9c */
undefined4 FUN_08025d9c(param_1)
uint param_1;
{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = 0xffffffff;
  if (param_1 == 0xffffffff) {
    ((code*)DAT_0804cd60)("boot_sdcc_hotplug.c",0x24b,0x304e);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (0xc < param_1) {
    ((code*)DAT_0804cd60)("boot_sdcc_hotplug.c",0x24d);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if ((*(int *)(&DAT_08053ec0 + param_1 * 0xc) != 0) &&
     (iVar2 = thunk_FUN_08025d64(*(int *)(&DAT_08053ec0 + param_1 * 0xc)), uVar1 = 0, iVar2 != 0)) {
    ((code*)DAT_0804cd60)("boot_sdcc_hotplug.c",0x254,0x304c);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return uVar1;
}




/* 0x08025e10 */
undefined4 FUN_08025e10(param_1)
uint param_1;
{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = 0xffffffff;
  if (0x1b < param_1) {
    ((code*)DAT_0804cd60)("boot_sdcc_hotplug.c",0x218);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar3 = (uint)(short)*(undefined4 *)(&DAT_08039660 + (param_1 & 0xffff) * 4);
  if (uVar3 == 0xffffffff) {
    ((code*)DAT_0804cd60)("boot_sdcc_hotplug.c",0x21c,0x3008);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (0xc < uVar3) {
    ((code*)DAT_0804cd60)("boot_sdcc_hotplug.c",0x21d);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if ((*(int *)(&DAT_08053ec0 + uVar3 * 0xc) != 0) &&
     (iVar2 = thunk_FUN_08025d64(*(int *)(&DAT_08053ec0 + uVar3 * 0xc)), uVar1 = 0, iVar2 != 0)) {
    ((code*)DAT_0804cd60)("boot_sdcc_hotplug.c",0x224,0x304c);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return uVar1;
}




/* 0x0802619c */
int FUN_0802619c(param_1, param_2, param_3, param_4)
uint param_1; undefined4 param_2; undefined4 param_3; uint param_4;
{
  uint uVar1;
  int iVar2;
  int iVar3;
  int local_18;
  uint local_14;
  
  iVar3 = 0;
  local_18 = 0;
  local_14 = param_4 & 0xffff0000;
  if (0x1b < param_1) {
    ((code*)DAT_0804cd60)("boot_sdcc_hotplug.c",0x356);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar1 = (uint)(short)*(undefined4 *)(&DAT_08039660 + (param_1 & 0xffff) * 4);
  if (uVar1 != 0xffffffff) {
    if (0xc < uVar1) {
      ((code*)DAT_0804cd60)("boot_sdcc_hotplug.c",0x35b);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if ((*(int *)(&DAT_08053ec0 + uVar1 * 0xc) != 0) &&
       (iVar2 = thunk_FUN_08025ee8(*(int *)(&DAT_08053ec0 + uVar1 * 0xc),&local_18,&local_14),
       iVar2 == 0)) {
      iVar3 = (local_14 & 0xffff) * local_18;
    }
    return iVar3;
  }
  ((code*)DAT_0804cd60)("boot_sdcc_hotplug.c",0x35a,0x3008);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08026232 */
undefined4 FUN_08026232(param_1)
int param_1;
{
  if (param_1 != 0) {
    return 0;
  }
  return 0xffffffff;
}




/* 0x08026240 */
undefined4 * FUN_08026240(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  DAT_0805a438 = param_1;
  uStack_10 = param_3;
  uStack_c = param_4;
  iVar1 = FUN_08019c1c();
  if (iVar1 == 0) {
    iVar1 = FUN_0802efd6(0,0,1,DAT_0805a438);
    iVar3 = -1;
    if (iVar1 != 0) {
      iVar2 = 0;
      do {
        if (*(char *)(iVar1 + iVar2 * 0x10 + 0x1c2) == -0x12) {
          iVar3 = 0;
          break;
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < 4);
    }
    if (iVar3 != 0) {
      return (undefined4 *)0x0;
    }
  }
  DAT_0805a418 = (uint)*(ushort *)(DAT_0805a438 + 8);
  iVar1 = FUN_0802248c(1,0,&uStack_10,&DAT_0805a418);
  if (iVar1 == 0) {
    return &DAT_0805a418;
  }
  iVar1 = FUN_0802248c(*(int *)(DAT_0805a438 + 0xc) + -1,0,&uStack_10,&DAT_0805a418);
  if (iVar1 != 0) {
    return (undefined4 *)0x0;
  }
  return &DAT_0805a418;
}




/* 0x080262ac */
int * FUN_080262ac(param_1)
int param_1;
{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  if (param_1 != 0) {
    while (piVar1 = (int *)FUN_080225f8(param_1), piVar1 != (int *)0x0) {
      iVar4 = 0;
      iVar3 = 0x10;
      piVar2 = piVar1;
      do {
        if (*piVar2 != 0) {
          iVar4 = -1;
          break;
        }
        piVar2 = piVar2 + 1;
        iVar3 = iVar3 + -4;
      } while (0 < iVar3);
      if (iVar4 != 0) {
        return piVar1;
      }
    }
  }
  return (int *)0x0;
}




/* 0x080262e0 */
undefined4 * FUN_080262e0()
{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)0x0;
  iVar1 = 0;
  do {
    if ((&DAT_08054cb4)[iVar1 * 8] == 0) {
      puVar2 = &DAT_08054cb4 + iVar1 * 8;
      break;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 4);
  if (puVar2 != (undefined4 *)0x0) {
    FUN_08006d14(puVar2,0x20);
    *puVar2 = 1;
    DAT_0804d654 = DAT_0804d654 + 1;
  }
  return puVar2;
}




/* 0x08026320 */
void FUN_08026320(param_1)
int param_1;
{
  if (param_1 == 0) {
    FUN_08015a50();
  }
  if (DAT_0804d654 < 1) {
    FUN_08015a50();
  }
  DAT_0804d654 = DAT_0804d654 + -1;
  FUN_08006d14(param_1,0x20);
  return;
}




/* 0x0802634c */
void FUN_0802634c()
{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined1 *puVar7;
  undefined1 *extraout_r3;
  undefined1 *extraout_r3_00;
  undefined1 uVar8;
  undefined4 unaff_r4 = 0;
  
  DAT_0804d654 = 0;
  FUN_08006d14(&DAT_08054cb4,0x80);
  FUN_080263c0();
  DAT_0804d658 = 0;
  FUN_08006d14(&DAT_08054d34,0x118);
  puVar7 = &DAT_08054d34;
  uVar6 = 1;
  iVar5 = 0;
  do {
    iVar2 = iVar5 + 1;
    (&DAT_08054d34)[iVar5 * 0x38] = 1;
    iVar5 = iVar2;
  } while (iVar2 < 5);
  iVar5 = 0;
  while (iVar5 = FUN_08013b74(8,iVar5,uVar6,puVar7,unaff_r4), iVar2 = DAT_0804d658, iVar5 != 0) {
    iVar1 = DAT_0804d658 * 0x38;
    DAT_0804d658 = DAT_0804d658 + 1;
    (&DAT_08054d34)[iVar1] = 0;
    (&DAT_08054d50)[iVar2 * 0xe] = iVar5;
    uVar6 = FUN_08013c04(iVar5);
    uVar8 = 0;
    switch(uVar6) {
    case 0:
      break;
    case 1:
      uVar8 = 1;
      break;
    case 2:
      uVar8 = 2;
      break;
    case 3:
      uVar8 = 3;
      break;
    case 4:
      uVar8 = 4;
      break;
    case 5:
      uVar8 = 5;
      break;
    case 6:
      uVar8 = 6;
      break;
    case 7:
      uVar8 = 7;
      break;
    case 8:
      uVar8 = 8;
      break;
    default:
      FUN_08015a50();
    }
    (&DAT_08054d35)[iVar1] = uVar8;
    iVar3 = FUN_08013bec((&DAT_08054d50)[iVar2 * 0xe]);
    if (iVar3 == 0) {
      FUN_08015a50();
    }
    uVar4 = FUN_080382c2(&DAT_08054d3c + iVar1,iVar3,0x14);
    uVar6 = extraout_r2;
    puVar7 = extraout_r3;
    if (0x14 < uVar4) {
      FUN_08015a50();
      uVar6 = extraout_r2_00;
      puVar7 = extraout_r3_00;
    }
    (&DAT_08054d58)[iVar2 * 0xe] = 0;
  }
  return;
}




