/* Auto-generated: fs_cookie.c */
/* Functions: 7 */
#include "globals.h"

/* 0x080209c8 */
undefined4 FUN_080209c8(param_1, param_2, param_3)
char * param_1; int param_2; int param_3;
{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 == (char *)0x0) {
    ((code*)DAT_0804cd60)("fs_cookie.c",0x9f,0x302f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_3 == 0) {
    ((code*)DAT_0804cd60)("fs_cookie.c",0xa0);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_2 == 0) {
    ((code*)DAT_0804cd60)("fs_cookie.c",0xa1);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if ((*param_1 == '\x01') && (*(ushort *)(param_1 + 1) + 3 + param_2 <= *(uint *)(param_3 + 0xc)))
  {
    uVar1 = 1;
  }
  return uVar1;
}




/* 0x08020a2c */
undefined4 FUN_08020a2c(param_1)
undefined4 * param_1;
{
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    return 0;
  }
  return 0xffffffff;
}




/* 0x08020a40 */
uint FUN_08020a40(param_1)
char * param_1;
{
  int iVar1;
  uint uVar2;
  
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    iVar1 = *(int *)(param_1 + 8);
    if (iVar1 == 0) {
      uVar2 = *(int *)(*(int *)(param_1 + 4) + 4) + 0xc;
    }
    else {
      uVar2 = iVar1 + 3 + (uint)*(ushort *)(iVar1 + 1);
    }
    if (uVar2 < *(uint *)(*(int *)(param_1 + 4) + 8)) {
      *(uint *)(param_1 + 8) = uVar2;
      return uVar2;
    }
  }
  return 0;
}




/* 0x08020a74 */
char * FUN_08020a74(param_1)
int param_1;
{
  char *pcVar1;
  int iVar2;
  
  if (param_1 == 0) {
    if (true) {
      ((code*)DAT_0804cd60)("fs_cookie.c",0x15b,0x302f);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar2 = 0;
    do {
      pcVar1 = (char *)(&DAT_87c00a3c + iVar2 * 3);
      if (*pcVar1 == '\0') {
        *pcVar1 = '\x01';
        (&DAT_87c00a40)[iVar2 * 3] = &DAT_87c00a2c;
        (&DAT_87c00a44)[iVar2 * 3] = 0;
        break;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 == 0);
    if (iVar2 != 1) {
      return pcVar1;
    }
  }
  return (char *)0x0;
}




/* 0x08020ad0 */
undefined4 FUN_08020ad0(param_1)
int param_1;
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int *piVar4;
  int *piVar5;
  
  if (param_1 == 0) {
    uVar3 = 0xffffffff;
  }
  else {
    piVar4 = *(int **)(param_1 + 4);
    if (piVar4 == (int *)0x0) {
      ((code*)DAT_0804cd60)("fs_cookie.c",0xbe,0x302f);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    piVar5 = piVar4 + 3;
    *(int **)(param_1 + 8) = piVar5;
    if (((*piVar4 == 1) && (piVar4[1] == 0x4f435346)) && (piVar4[2] == 0x45494b4f)) {
      while (iVar1 = FUN_080209c8(piVar5,piVar5,param_1), iVar1 == 1) {
        piVar5 = (int *)((int)piVar5 + *(ushort *)((int)piVar5 + 1) + 3);
        *(int **)(param_1 + 8) = piVar5;
      }
      uVar2 = *(uint *)(param_1 + 8);
      if (*(uint *)(param_1 + 0xc) < uVar2) {
        ((code*)DAT_0804cd60)("fs_cookie.c",0xe2,0x302f);
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      FUN_08006cd0(uVar2,*(uint *)(param_1 + 0xc) - uVar2);
    }
    else {
      FUN_08006d14(piVar4,*(int *)(param_1 + 0xc) - (int)piVar4);
      *piVar4 = 1;
      piVar4[1] = 0x4f435346;
      piVar4[2] = 0x45494b4f;
    }
    uVar3 = 0;
  }
  return uVar3;
}




/* 0x08020b88 */
undefined4 FUN_08020b88(param_1)
int param_1;
{
  if (param_1 < 0) {
    return 0xffffffff;
  }
  if ((&DAT_87c00a2c)[param_1 * 7] != 1) {
    ((code*)DAT_0804cd60)("fs_cookie.c",0x1d6,0x302f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_08006d14(&DAT_87c00a2c + param_1 * 7,0x1c);
  return 0;
}




/* 0x08020bd4 */
undefined4 FUN_08020bd4(param_1)
int param_1;
{
  int iVar1;
  
  if (param_1 != 0) {
    return 0xffffffff;
  }
  if (true) {
    ((code*)DAT_0804cd60)("fs_cookie.c",0x1b9,0x302f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar1 = DAT_87c00a30 + 0xc;
  FUN_08006cd0(iVar1,DAT_87c00a38 - iVar1);
  DAT_87c00a3c = 0;
  DAT_87c00a40 = 0;
  DAT_87c00a44 = 0;
  DAT_87c00a34 = iVar1;
  return 0;
}




