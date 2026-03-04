/* Auto-generated: boot_sd_ramdump.c */
/* Functions: 8 */
#include "globals.h"

/* 0x080171e0 */
void FUN_080171e0()
{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  undefined4 in_r3 = 0;
  uint uVar8;
  bool bVar9;
  bool bVar10;
  bool bVar11;
  longlong lVar12;
  char *pcVar13;
  
  DAT_0805221b = 0;
  DAT_0805231b = 0;
  DAT_0805241b = 0;
  DAT_0805251b = 0;
  DAT_0805201b = 0;
  DAT_0804cd74 = FUN_0801c288();
  uVar1 = FUN_080382c2(&DAT_0805221c,&DAT_08051f1c,0x100);
  if (0xff < uVar1) {
    ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x15f,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar1 = FUN_08038282(&DAT_0805221c,"errmax.txt",0x100);
  if (0xff < uVar1) {
    ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x162,0x3056,DAT_0804cd60,in_r3);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar2 = FUN_08014e78(&DAT_0805221c,0x241,0x1b6);
  iVar3 = FUN_0801da40();
  FUN_08019558();
  if (iVar3 == 0) goto LAB_08017574;
  thunk_FUN_0801cd04(iVar2);
  thunk_FUN_0801d244(&DAT_0805221c);
  uVar1 = FUN_080382c2(&DAT_0805231c,&DAT_0805241c,0x100);
  if (0xff < uVar1) {
    ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x17a,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar1 = FUN_08038282(&DAT_0805231c,"errfile.txt",0x100);
  if (0xff < uVar1) {
    ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x17d,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar3 = FUN_08014e78(&DAT_0805231c,0x241,0x1b6);
  if (iVar3 == -1) {
    return;
  }
  pcVar13 = "rawdump.bin";
  snprintf_buf(&DAT_0805211c,0x100,&DAT_080175d4,&DAT_0805241c);
  iVar2 = FUN_08014e78(&DAT_0805211c,0x241,0x1b6);
  if (iVar2 == -1) {
    iVar4 = snprintf_buf(&DAT_0805211c,0x100,&DAT_080175e0,"rawdump.bin");
    bVar11 = SBORROW4(iVar4,0xff);
    bVar9 = iVar4 + -0xff < 0;
    bVar10 = iVar4 == 0xff;
    if (0xff < iVar4) {
      ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x191,0x3056);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
LAB_08017320:
    if (!bVar10 && bVar9 == bVar11) {
      ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x19f,0x3056,DAT_0804cd60,pcVar13);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
LAB_080174fe:
    if (DAT_0805261c != 0) {
      FUN_08015a3c(1);
      uVar1 = snprintf_buf(&DAT_08052620,0x100,&DAT_080175f0,&DAT_0805211c);
      if (0xff < uVar1) {
        ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x20a,0x3056);
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      if (iVar3 != -1) {
        FUN_08014ea0(iVar3,&DAT_0805261c,uVar1 + 4);
        thunk_FUN_0801cd04(iVar3);
      }
      goto LAB_08017574;
    }
  }
  else {
    FUN_080176c4();
    FUN_08019930(iVar2);
    if (DAT_0805261c != 0) {
      iVar4 = snprintf_buf(&DAT_0805211c,0x100,&DAT_080175e0,"rawdump.bin");
      bVar11 = SBORROW4(iVar4,0xff);
      bVar9 = iVar4 + -0xff < 0;
      bVar10 = iVar4 == 0xff;
      goto LAB_08017320;
    }
    for (uVar1 = 0; uVar1 < DAT_0804cd74; uVar1 = uVar1 + 1) {
      uVar8 = uVar1 & 0xff;
      iVar4 = FUN_0801c238(uVar8);
      uVar5 = FUN_0801c260(uVar8);
      DAT_0805261c = 0;
      FUN_08019848(uVar1);
      FUN_08019930(iVar2);
      if (DAT_0805261c != 0) {
        iVar4 = snprintf_buf(&DAT_0805211c,0x100,&DAT_080175e0,"rawdump.bin");
        bVar11 = SBORROW4(iVar4,0xff);
        bVar9 = iVar4 + -0xff < 0;
        bVar10 = iVar4 == 0xff;
        if (0xff < iVar4) {
          ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x1b3,0x3056);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        goto LAB_08017320;
      }
      uVar6 = FUN_080382c2(&DAT_0805211c,&DAT_0805241c,0x100);
      if (0xff < uVar6) {
        ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x1ba,0x3056);
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      iVar7 = FUN_0801bfdc(uVar8);
      if (iVar7 == 0) {
        ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x1bf,0x300d);
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      uVar8 = FUN_08038282(&DAT_0805211c,iVar7,0x100);
      if (0xff < uVar8) {
        ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x1c3,0x3056);
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      iVar7 = FUN_08014e78(&DAT_0805211c,0x241,0x1b6);
      DAT_0805261c = 0;
      if (iVar7 == -1) break;
      if (iVar4 == 0) {
        if (uVar5 < 0x200) {
          ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x1d1,0x3056);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        FUN_08030b34(&DAT_08052720,0,0x200);
        FUN_08014ea0(iVar7,&DAT_08052720,0x200);
        uVar5 = uVar5 - 0x200;
        iVar4 = 0x200;
        if (DAT_0805261c == 0) goto LAB_08017462;
LAB_08017472:
        thunk_FUN_0801cd04(iVar7);
        thunk_FUN_0801d244(&DAT_0805211c);
        goto LAB_080174fe;
      }
LAB_08017462:
      FUN_08014ea0(iVar7,iVar4,uVar5);
      if (DAT_0805261c != 0) goto LAB_08017472;
      thunk_FUN_0801cd04(iVar7);
      iVar4 = uVar1 * 0x40 + -0x7838cb04;
      uVar8 = FUN_08006e04(iVar4);
      FUN_08006e1a(uVar8 | 1,iVar4);
      lVar12 = FUN_08006e30();
      FUN_08006e5e((int)(lVar12 + (ulonglong)uVar5),(int)(lVar12 + (ulonglong)uVar5 >> 0x20),
                   0x87c734e8);
      iVar4 = FUN_08006e04();
      FUN_08006e1a(iVar4 + 1,0x87c734f8);
      FUN_08019930(iVar2);
      if (DAT_0805261c != 0) {
        iVar4 = snprintf_buf(&DAT_0805211c,0x100,&DAT_080175e0,"rawdump.bin");
        if (0xff < iVar4) {
          ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x1f7,0x3056);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        goto LAB_080174fe;
      }
    }
  }
  FUN_08015a3c(0);
  thunk_FUN_0801cd04(iVar3);
  thunk_FUN_0801d244(&DAT_0805231c);
  uVar1 = FUN_08006e04();
  FUN_08006e1a(uVar1 | 1,0x87c734d0);
  FUN_08019930(iVar2);
LAB_08017574:
  thunk_FUN_0801cd04(iVar2);
  return;
}




/* 0x080175f8 */
void FUN_080175f8()
{
  int iVar1;
  
  iVar1 = thunk_FUN_08030c10();
  if (iVar1 == 0) {
    FUN_08030dac();
    return;
  }
  return;
}




/* 0x08017618 */
int FUN_08017618(param_1)
undefined4 param_1;
{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_080382c2(&DAT_08051f1c,param_1,0x100);
  if (0xff < uVar1) {
    ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x245,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar1 = FUN_080382c2(&DAT_0805201c,param_1,0x100);
  if (0xff < uVar1) {
    ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x248,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar1 = FUN_08038282(&DAT_0805201c,"rdcookie.txt",0x100);
  if (0xff < uVar1) {
    ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x24b,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar2 = FUN_08014e78(&DAT_0805201c,0);
  if (-1 < iVar2) {
    thunk_FUN_0801cd04();
  }
  return iVar2;
}




/* 0x080176c4 */
void FUN_080176c4()
{
  ulonglong uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  longlong lVar6;
  undefined4 local_20;
  undefined4 uStack_1c;
  int local_18;
  
  iVar2 = DAT_0804cd58;
  local_18 = DAT_0804cd58;
  local_20 = 0x5f776152;
  uStack_1c = 0x21706d44;
  FUN_08007f08(0x87c734c4,0,0x38);
  FUN_08007f08(0x87c734fc,0,0x500);
  FUN_08030b34(0x87c734c4,&local_20,8);
  FUN_08006e1a(0x1000,0x87c734cc);
  iVar3 = FUN_0801c288();
  uVar1 = (ulonglong)(iVar3 * 0x40 + 0x38);
  for (uVar5 = 0; uVar4 = FUN_0801c288(), uVar5 < uVar4; uVar5 = uVar5 + 1) {
    lVar6 = FUN_0801c260(uVar5 & 0xff);
    uVar1 = lVar6 + uVar1;
  }
  FUN_08006e5e((int)uVar1,(int)(uVar1 >> 0x20),0x87c734f0);
  FUN_08006e1a(0,0x87c734f8);
  if (local_18 != iVar2) {
    FUN_08010960(local_18,local_20,uStack_1c,local_18);
    return;
  }
  return;
}




/* 0x08017760 */
void FUN_08017760(param_1, param_2, param_3, param_4, param_5)
int param_1; undefined4 param_2; uint param_3; int param_4; uint param_5;
{
  int iVar1;
  undefined4 extraout_r1;
  uint uVar2;
  bool bVar3;
  
  for (; param_5 != 0; param_5 = param_5 - uVar2) {
    uVar2 = 0x200000;
    if (param_5 < 0x200001) {
      uVar2 = param_5;
    }
    iVar1 = FUN_0801bb3c(param_1,param_2,param_3,param_4,uVar2,0x1b);
    if (iVar1 != 1) {
      FUN_08017950();
    }
    FUN_08019524();
    bVar3 = CARRY4(param_3,uVar2);
    param_3 = param_3 + uVar2;
    param_1 = param_1 + uVar2;
    param_4 = param_4 + (uint)bVar3;
    param_2 = extraout_r1;
  }
  return;
}




/* 0x0801789c */
undefined4 FUN_0801789c(param_1)
int * param_1;
{
  if (*param_1 != param_1[1]) {
    FUN_08030b34(param_1[1],*param_1,param_1[2]);
  }
  FUN_08007f08(param_1[3],0,param_1[4]);
  return 1;
}




/* 0x080178bc */
void FUN_080178bc()
{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_080382c2(&DAT_0805201c,&DAT_08051f1c,0x100);
  if (0xff < uVar1) {
    ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x80,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar1 = FUN_08038282(&DAT_0805201c,"rtcookie.txt",0x100);
  if (0xff < uVar1) {
    ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x83,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar2 = FUN_08014e78(&DAT_0805201c,0);
  if (-1 < iVar2) {
    thunk_FUN_0801cd04();
    FUN_08007de0();
    thunk_FUN_00220358(0);
    return;
  }
  return;
}




/* 0x0801da40 */
uint FUN_0801da40()
{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 1;
  while( true ) {
    snprintf_buf(&DAT_0805251c,5,&DAT_0801dac8,uVar3);
    uVar1 = FUN_080382c2(&DAT_0805241c,&DAT_08051f1c,0x100);
    if (0xff < uVar1) {
      ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x10e,0x3056);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    uVar1 = FUN_08038282(&DAT_0805241c,&DAT_0805251c,0x100);
    if (0xff < uVar1) {
      ((code*)DAT_0804cd60)("boot_sd_ramdump.c",0x111,0x3056);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar2 = thunk_FUN_0801d184(&DAT_0805241c);
    if (iVar2 == 0) {
      iVar2 = thunk_FUN_0801cf5c(&DAT_0805241c,0x1b6);
      uVar1 = 0;
      if (iVar2 == 0) {
        uVar1 = uVar3;
      }
      return uVar1;
    }
    iVar2 = thunk_FUN_0801cd44();
    if (iVar2 != 0) break;
    uVar3 = uVar3 + 1;
    if (100 < uVar3) {
      return 0;
    }
  }
  return 0;
}




