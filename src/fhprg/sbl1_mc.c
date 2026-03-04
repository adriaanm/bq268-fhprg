/* Auto-generated: sbl1_mc.c */
/* Functions: 11 */
#include "globals.h"

/* 0x08031d74 */
void FUN_08031d74(param_1, param_2)
undefined4 param_1; uint param_2;
{
  int iVar1;
  int local_20;
  
  local_20 = 0;
  if ((param_2 == 0) || (0x800 < param_2)) {
    ((code*)DAT_0804cd60)("sbl1_mc.c",0x3da,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_08015b94(&DAT_0804ce58);
  local_20 = FUN_08015c72(0x1b);
  if (local_20 == 0) {
    ((code*)DAT_0804cd60)("sbl1_mc.c",0x3e2,0x300d);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_0801453c(local_20 + 8,param_1,param_2);
  iVar1 = FUN_08015e28(local_20,param_1,0,param_2);
  FUN_080147d4(local_20 + 8,param_1,param_2);
  if (iVar1 != 0) {
    FUN_08015ba8(&local_20);
    return;
  }
  ((code*)DAT_0804cd60)("sbl1_mc.c",0x3f4,0x3056);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08031e10 */
void boot_cei_config(param_1)
int param_1;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int local_80;
  undefined1 auStack_7c [96];
  int local_1c;
  
  iVar1 = DAT_0804cd58;
  local_1c = DAT_0804cd58;
  iVar4 = 0;
  local_80 = 0;
  iVar2 = FUN_08019b80();
  if (iVar2 == 0) {
    boot_log_message("cei_qfprom_blow_check, FALSE");
    boot_log_message("skip to load sec partition");
  }
  else {
    boot_log_message("cei_qfprom_blow_check, TRUE");
    FUN_080193b8();
    boot_log_message("Image Load, Start");
    thunk_FUN_080192b8();
    iVar2 = FUN_08018d6a(param_1 + 8,7);
    if (iVar2 == 1) {
      iVar4 = -0x780fe000;
    }
    else if (iVar2 == 2) {
      iVar4 = -0x780be000;
    }
    FUN_08015b94(&DAT_0804ce88);
    local_80 = FUN_08015c72(0x1b);
    if (local_80 != 0) {
      if (iVar4 == 0) {
        ((code*)DAT_0804cd60)("sbl1_mc.c",0x44d,0x3056);
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      iVar2 = FUN_08015e28(local_80,iVar4,0,0x800);
      if (iVar2 == 0) {
        ((code*)DAT_0804cd60)("sbl1_mc.c",0x457,0x3056);
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      FUN_08015ba8(&local_80);
    }
    uVar3 = FUN_08019314();
    snprintf_buf(auStack_7c,0x60,"(%d Bytes)",uVar3);
    FUN_08016c9a("SEC Image Loaded, Delta",auStack_7c);
  }
  if (local_1c != iVar1) {
    FUN_08010960();
    return;
  }
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08032114 */
void FUN_08032114(param_1)
int * param_1;
{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)*param_1;
  if (*(int *)(*piVar1 + 0x14) == 0) {
    ((code*)DAT_0804cd60)("sbl1_mc.c",0x4d6,0x300d);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_080164a4(piVar1[9],piVar1[10]);
  iVar2 = FUN_08016d68(*(undefined4 *)(*param_1 + 0x24),&DAT_080392b0);
  if (iVar2 == 0) {
    ((code*)DAT_0804cd60)("sbl1_mc.c",0x4e9,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return;
}




/* 0x080321ac */
void FUN_080321ac(param_1)
undefined4 param_1;
{
  int iVar1;
  
  iVar1 = thunk_FUN_002225f4();
  if (iVar1 == 1) {
    FUN_080319cc();
    FUN_080321c8(param_1);
    return;
  }
  return;
}




/* 0x080321c8 */
void FUN_080321c8(param_1, param_2, param_3, param_4)
int * param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  int iVar1;
  
  if (DAT_0804c010 == 0) {
    FUN_08007f08(0x87c68000,0,0x8000,param_4,param_3,param_4);
    iVar1 = FUN_08016ce0(*(undefined4 *)(*param_1 + 0x24),0x87c68000,0x87c6c000,0xe);
    if (iVar1 == 0) {
      ((code*)DAT_0804cd60)("sbl1_mc.c",799,0x3056);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    FUN_08032390(param_1,0x87c68000);
    FUN_08007e9c(0x87c68000);
    *(undefined4 *)(*param_1 + 0x24) = 0x87c68000;
    *(undefined4 *)(*param_1 + 0x28) = 0x8000;
    DAT_0804c010 = 1;
    thunk_FUN_0800b5e0(&DAT_87c2acec,0x20000,1);
    FUN_08016c58(0x87cdf600,0x87cdf640,0x9c0,&DAT_0805c0e0,&DAT_0805c120,0x800);
    DAT_0804c070 = 0x87cdf640;
    DAT_0804c074 = 0x9c0;
    DAT_0804c078 = 0x87cdf600;
  }
  return;
}




/* 0x08032280 */
void FUN_08032280(param_1)
int param_1;
{
  undefined4 *puVar1;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x30) != 0)) {
    FUN_08030b34(&DAT_08051b00,param_1,0x54);
    DAT_08051d48 = &DAT_08051b00;
    DAT_08051b60 = &DAT_08051d48;
    DAT_08051d5c = 0;
    DAT_08051d6c = *(undefined4 *)(param_1 + 0x14);
    DAT_08051d70 = *(undefined4 *)(param_1 + 0x18);
    FUN_08016e88(&DAT_08051b00);
    FUN_08030b34(&DAT_08051d78,*(undefined4 *)(param_1 + 0x30),0x50);
    FUN_08007f08(DAT_0804cea0 + 0x834,0,0x100);
    puVar1 = (undefined4 *)(DAT_0804cea0 + 0x834);
    ((uint*)&DAT_08051b60)[8] = puVar1;
    *puVar1 = 0;
    ((uint*)&DAT_08051b60)[8] = ((uint*)&DAT_08051b60)[8] + 4;
    DAT_08051d40 = 2;
    return;
  }
  ((code*)DAT_0804cd60)("sbl1_mc.c",0x140,0x300d);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x0803231c */
void FUN_0803231c()
{
  int local_8;
  
  local_8 = 0;
  FUN_08015b94(&DAT_0804ce58);
  local_8 = FUN_08015c72(0x1b);
  if (local_8 != 0) {
    FUN_08015ba8(&local_8);
    return;
  }
  ((code*)DAT_0804cd60)("sbl1_mc.c",0x48f,0x300d);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08032390 */
void FUN_08032390(param_1, param_2)
int * param_1; undefined4 param_2;
{
  uint *puVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  undefined1 auStack_70 [48];
  undefined1 auStack_40 [36];
  
  thunk_FUN_00222448(auStack_70);
  thunk_FUN_002223bc(auStack_40);
  FUN_08019094(&DAT_08051b54,auStack_70,auStack_40);
  *(undefined **)(*param_1 + 8) = &DAT_08051b54;
  FUN_08018f2c(param_1);
  puVar1 = (uint *)FUN_080160d0();
  for (uVar4 = 0; uVar4 < *puVar1; uVar4 = uVar4 + 1) {
    puVar2 = (undefined4 *)(puVar1[1] + uVar4 * 0x10);
    DAT_0804c014 = *puVar2;
    DAT_0804c018 = *puVar2;
    DAT_0804c01c = puVar2[2] << 10;
    iVar3 = FUN_08016dd4(param_2,&DAT_0804c014);
    if (iVar3 == 0) {
      ((code*)DAT_0804cd60)("sbl1_mc.c",0x2aa,0x3056);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
  }
  iVar3 = FUN_08016d68(param_2,&DAT_08039370);
  if (iVar3 == 0) {
    ((code*)DAT_0804cd60)("sbl1_mc.c",0x2b1,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return;
}




/* 0x08032580 */
void FUN_08032580()
{
  if (DAT_0804c000 == '\0') {
    return;
  }
  DAT_87c1b358 = 0x45525220;
  DAT_87c1b35c = 1;
  DAT_87c1b404 = 0x8000000;
  DAT_87c1b408 = 0x80000;
  DAT_87c1b3f4 = 0x8f600400;
  DAT_87c1b3f8 = &DAT_87c00000;
  DAT_87c1b3fc = 0xe0000;
  DAT_87c1b400 = 0x8f6e0400;
  DAT_87c1b40c = 0;
  DAT_87c1b410 = 0;
  FUN_08030b34();
  FUN_08030b34(DAT_87c1b400,DAT_87c1b404,DAT_87c1b408);
  FUN_08007de0();
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08032644 */
void FUN_08032644()
{
  undefined4 uVar1;
  
  FUN_0801471c();
  FUN_08018fa4(0);
  if (_DAT_87c73490 != 0) {
    uVar1 = FUN_0801615c();
    FUN_08007f08(_DAT_87c73490,0,uVar1);
  }
  if (_DAT_87c7348c != 0) {
    FUN_08007f08(_DAT_87c7348c,0,0xc94);
  }
  FUN_08007f08(0x87c71000,0,400);
  FUN_08007f08(0x87c73458,0,0x34);
  FUN_08007f08(&DAT_87c72878,0,0x400);
  return;
}




/* 0x080326a4 */
undefined1 FUN_080326a4(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  
  iVar1 = FUN_0801616c();
  if ((iVar1 == 1) && (param_1 != 0)) {
    iVar1 = FUN_08013a24(param_1,*(undefined4 *)(param_2 * 4 + -0x7838f000),DAT_0804cdf8);
    if (iVar1 == 0) {
      return 1;
    }
  }
  FUN_08032644();
  return 0;
}




