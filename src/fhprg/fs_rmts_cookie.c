/* Auto-generated: fs_rmts_cookie.c */
/* Functions: 9 */
#include "globals.h"

/* 0x0801cdac */
void thunk_FUN_0801cdac(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; uint param_3;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint auStack_28 [2];
  
  auStack_28[0] = param_3 & 0xffff0000;
  auStack_28[1] = 0;
  FUN_080209bc();
  uVar3 = 0;
  do {
    uVar4 = (&DAT_08039734)[uVar3];
    iVar1 = FUN_080218a0(uVar4);
    if (iVar1 != 0) {
      iVar2 = FUN_08025ee8(iVar1,auStack_28 + 1,auStack_28);
      if (iVar2 == 0) {
        if (0x200 < (ushort)auStack_28[0]) {
          ((code*)DAT_0804cd60)("fs_rmts_cookie.c",0x2ca,0x302f);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        iVar2 = FUN_08025f0e(iVar1,0,&DAT_87c00800,1);
        if ((iVar2 == 0) && (iVar2 = FUN_08021780(uVar4,&DAT_87c00800,0x200), iVar2 != 0)) {
          FUN_08025f4e(iVar1,0,&DAT_87c00800,1);
        }
      }
      FUN_08025d64(iVar1);
    }
    uVar3 = uVar3 + 1;
  } while (uVar3 < 4);
  return;
}




/* 0x0801cdac */
void FUN_0801cdac(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; uint param_3;
{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint local_28 [2];
  
  local_28[0] = param_3 & 0xffff0000;
  local_28[1] = 0;
  FUN_080209bc();
  uVar3 = 0;
  do {
    uVar4 = (&DAT_08039734)[uVar3];
    iVar1 = FUN_080218a0(uVar4);
    if (iVar1 != 0) {
      iVar2 = FUN_08025ee8(iVar1,local_28 + 1,local_28);
      if (iVar2 == 0) {
        if (0x200 < (ushort)local_28[0]) {
          ((code*)DAT_0804cd60)("fs_rmts_cookie.c",0x2ca,0x302f);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        iVar2 = FUN_08025f0e(iVar1,0,&DAT_87c00800,1);
        if ((iVar2 == 0) && (iVar2 = FUN_08021780(uVar4,&DAT_87c00800,0x200), iVar2 != 0)) {
          FUN_08025f4e(iVar1,0,&DAT_87c00800,1);
        }
      }
      FUN_08025d64(iVar1);
    }
    uVar3 = uVar3 + 1;
  } while (uVar3 < 4);
  return;
}




/* 0x080214bc */
void FUN_080214bc(param_1, param_2)
undefined4 param_1; char * param_2;
{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  ushort local_50 [2];
  int local_4c [2];
  ushort local_44 [4];
  ushort local_3c [4];
  int local_34 [2];
  int local_2c [2];
  
  iVar10 = 0;
  iVar11 = 0;
  if (param_2 == (char *)0x0) {
    ((code*)DAT_0804cd60)("fs_rmts_cookie.c",0x1f1,0x302f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (*param_2 != '\x01') {
    ((code*)DAT_0804cd60)("fs_rmts_cookie.c",0x1f2,0x302f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (*(short *)(param_2 + 1) == 5) {
    cVar4 = param_2[3];
    cVar1 = param_2[4];
    cVar2 = param_2[5];
    cVar3 = param_2[6];
    if (cVar1 == '\0') {
      if (cVar2 != '\x02') {
        return;
      }
      if (cVar3 != '\x01') {
        return;
      }
    }
    else {
      if (cVar1 != '\x01') {
        return;
      }
      if (cVar2 != '\x02') {
        return;
      }
      if (cVar3 != '\0') {
        return;
      }
    }
    uVar5 = FUN_080218f0(param_1,cVar1,cVar4);
    uVar6 = FUN_080218f0(param_1,cVar2,cVar4);
    uVar7 = FUN_080218f0(param_1,cVar3,cVar4);
    iVar8 = FUN_080218a0(uVar5);
    if (iVar8 != 0) {
      iVar10 = FUN_080218a0(uVar6);
      if (iVar10 == 0) {
        FUN_08015a50();
      }
      iVar11 = FUN_08025ee8(iVar8,local_4c,local_50);
      if (iVar11 != 0) {
        FUN_08015a50();
      }
      iVar11 = FUN_08025ee8(iVar10,local_2c,local_44);
      if (iVar11 != 0) {
        FUN_08015a50();
      }
      if (local_4c[0] != local_2c[0]) {
        FUN_08015a50();
      }
      if (local_50[0] != local_44[0]) {
        FUN_08015a50();
      }
      iVar11 = FUN_080218a0(uVar7);
      if (iVar11 == 0) {
        FUN_08015a50();
      }
      iVar9 = FUN_08025ee8(iVar11,local_34,local_3c);
      if (iVar9 != 0) {
        FUN_08015a50();
      }
      if (local_4c[0] != local_34[0]) {
        FUN_08015a50();
      }
      if (local_50[0] != local_3c[0]) {
        FUN_08015a50();
      }
      if (0x800 < local_50[0]) {
        ((code*)DAT_0804cd60)("fs_rmts_cookie.c",0x25b,0x302f);
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      if (0x800 < local_44[0]) {
        FUN_08015a50();
      }
      iVar9 = FUN_0802184c(iVar10,&DAT_87c00000,0x800);
      if (iVar9 == 0) {
        iVar9 = FUN_0802167c(iVar8,iVar10,0,0,local_4c[0],local_50[0]);
        if (iVar9 != local_4c[0]) {
          FUN_08015a50();
        }
        FUN_08006cd0(&DAT_87c00000,0x800);
        FUN_0801a464(iVar8,&DAT_87c00000);
        FUN_0801a464(iVar11,&DAT_87c00000);
      }
    }
    FUN_08025d64(iVar8);
    FUN_08025d64(iVar11);
    FUN_08025d64(iVar10);
  }
  return;
}




/* 0x0802167c */
uint FUN_0802167c(param_1, param_2, param_3, param_4, param_5, param_6)
undefined4 param_1; undefined4 param_2; int param_3; int param_4; uint param_5; uint param_6;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  if (param_6 == 0) {
    ((code*)DAT_0804cd60)("fs_rmts_cookie.c",0x17f,0x302f,DAT_0804cd60,param_1,param_2,param_3,param_4);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar2 = 0;
  while( true ) {
    if (param_5 <= uVar2) {
      return uVar2;
    }
    uVar3 = param_5 - uVar2;
    if (0x800 / param_6 < param_5 - uVar2) {
      uVar3 = 0x800 / param_6;
    }
    iVar1 = FUN_08025f0e(param_1,param_3 + uVar2,&DAT_87c00000);
    if (iVar1 != 0) break;
    iVar1 = FUN_08025f4e(param_2,param_4 + uVar2,&DAT_87c00000,uVar3 & 0xffff);
    if (iVar1 != 0) {
      return uVar2;
    }
    uVar2 = uVar2 + uVar3;
  }
  return uVar2;
}




/* 0x08021700 */
void FUN_08021700(param_1, param_2)
int param_1; int param_2;
{
  undefined2 uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  if (param_1 == 0) {
    ((code*)DAT_0804cd60)("fs_rmts_cookie.c",0x14e,0x302f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_2 != 0) {
    FUN_08006cd0(param_2,0x10);
    uVar2 = FUN_08006e04(param_1);
    FUN_08006e1a(uVar2,param_2);
    uVar1 = *(undefined2 *)(param_1 + 4);
    *(char *)(param_2 + 4) = (char)uVar1;
    *(char *)(param_2 + 5) = (char)((ushort)uVar1 >> 8);
    uVar1 = *(undefined2 *)(param_1 + 6);
    *(char *)(param_2 + 6) = (char)uVar1;
    *(char *)(param_2 + 7) = (char)((ushort)uVar1 >> 8);
    uVar3 = 0;
    do {
      iVar4 = param_1 + uVar3;
      iVar5 = param_2 + uVar3;
      uVar3 = uVar3 + 1;
      *(undefined1 *)(iVar5 + 8) = *(undefined1 *)(iVar4 + 8);
    } while (uVar3 < 8);
    return;
  }
  ((code*)DAT_0804cd60)("fs_rmts_cookie.c",0x14f);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08021780 */
int FUN_08021780(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar1 = FUN_08020964(param_2,param_3);
  if (iVar1 < 0) {
    FUN_08015a50();
  }
  iVar2 = FUN_08020a74(iVar1);
  if (iVar2 == 0) {
    FUN_08015a50();
  }
  pbVar3 = (byte *)FUN_08020a40(iVar2);
  if (pbVar3 != (byte *)0x0) {
    iVar4 = 1;
    do {
      if ((&DAT_08039814)[(uint)*pbVar3 * 8] == '\0') {
        ((code*)DAT_0804cd60)("fs_rmts_cookie.c",0x298,0x302f);
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      if (*(code **)(&DAT_08039818 + (uint)*pbVar3 * 8) == (code *)0x0) {
        ((code*)DAT_0804cd60)("fs_rmts_cookie.c",0x29c,0x302f);
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      (**(code **)(&DAT_08039818 + (uint)*pbVar3 * 8))(param_1);
      pbVar3 = (byte *)FUN_08020a40(iVar2);
    } while (pbVar3 != (byte *)0x0);
  }
  iVar2 = FUN_08020a2c(iVar2);
  if (iVar2 != 0) {
    ((code*)DAT_0804cd60)("fs_rmts_cookie.c",0x2a1,0x302f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (iVar4 != 0) {
    FUN_08020bd4(iVar1);
  }
  iVar1 = FUN_08020b88(iVar1);
  if (iVar1 != 0) {
    ((code*)DAT_0804cd60)("fs_rmts_cookie.c",0x2a6,0x302f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return iVar4;
}




/* 0x0802184c */
undefined4 FUN_0802184c(param_1, param_2)
undefined4 param_1; int param_2;
{
  int iVar1;
  
  iVar1 = FUN_08025f0e(param_1,0,param_2,1);
  if (iVar1 != 0) {
    FUN_08015a50();
  }
  if ((((*(char *)(param_2 + 0x28) == 'I') && (*(char *)(param_2 + 0x29) == 'M')) &&
      (*(char *)(param_2 + 0x2a) == 'G')) &&
     (((*(char *)(param_2 + 0x2b) == 'E' && (*(char *)(param_2 + 0x2c) == 'F')) &&
      ((*(char *)(param_2 + 0x2d) == 'S' && (*(char *)(param_2 + 0x2e) == 'G')))))) {
    return 1;
  }
  return 0;
}




/* 0x080218a0 */
int FUN_080218a0(param_1, param_2, param_3, param_4)
int param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  iVar3 = 0;
  uVar1 = 0;
  do {
    if ((&DAT_08039794)[uVar1 * 2] == param_1) {
      iVar2 = (&DAT_08039798)[uVar1 * 2];
      goto LAB_080218c4;
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 < 0x10);
  iVar2 = 0;
LAB_080218c4:
  iStack_20 = param_1;
  uStack_1c = param_2;
  uStack_18 = param_3;
  uStack_14 = param_4;
  if (iVar2 != 0) {
    FUN_08021700(iVar2,&iStack_20);
    iVar3 = FUN_08026a70(1,0,&iStack_20);
  }
  if (iVar3 == 0) {
    iVar3 = FUN_08026aba(1,0,param_1);
  }
  return iVar3;
}




/* 0x080218f0 */
undefined4 FUN_080218f0(param_1, param_2, param_3)
int param_1; int param_2; uint param_3;
{
  uint uVar1;
  
  uVar1 = 0;
  while ((&DAT_08039744)[uVar1 * 5] != param_1) {
    uVar1 = uVar1 + 1;
    if (3 < uVar1) {
      return 0;
    }
  }
  if ((byte)(&DAT_08039754)[uVar1 * 0x14] != param_3) {
    ((code*)DAT_0804cd60)("fs_rmts_cookie.c",0xd9);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_2 != 0) {
    if (param_2 == 1) {
      return (&DAT_0803974c)[uVar1 * 5];
    }
    if (param_2 == 2) {
      return (&DAT_08039750)[uVar1 * 5];
    }
    ((code*)DAT_0804cd60)("fs_rmts_cookie.c",0xea,0x302f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return (&DAT_08039748)[uVar1 * 5];
}




