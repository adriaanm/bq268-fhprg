/* Auto-generated: boot_clobber_prot.c */
/* Functions: 7 */
#include "globals.h"

/* 0x080144b4 */
undefined4 FUN_080144b4(param_1, param_2)
uint param_1; int param_2;
{
  uint uVar1;
  
  uVar1 = 0;
  if (param_1 + param_2 < param_1) {
    ((code*)DAT_0804cd60)("boot_clobber_prot.c",0x70);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (0x1f < DAT_08052920) {
    ((code*)DAT_0804cd60)("boot_clobber_prot.c",0x93,0x303f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  for (; uVar1 < DAT_08052920; uVar1 = uVar1 + 1) {
    if (((uint)(&DAT_08052924)[uVar1 * 2] <= param_1) &&
       (param_1 + param_2 <= (uint)((&DAT_08052924)[uVar1 * 2] + (&DAT_08052928)[uVar1 * 2])))
    break;
  }
  if (DAT_08052920 == uVar1) {
    (&DAT_08052924)[DAT_08052920 * 2] = param_1;
    (&DAT_08052928)[DAT_08052920 * 2] = param_2;
    DAT_08052920 = DAT_08052920 + 1;
  }
  return 1;
}




/* 0x08014618 */
undefined4 FUN_08014618(param_1, param_2)
uint param_1; int param_2;
{
  uint uVar1;
  int iVar2;
  
  iVar2 = 0;
  if ((DAT_0804ce00 != (int *)0x0) &&
     (((*(uint*)DAT_0804ce00 != 0 || (((uint*)&DAT_0804ce00)[1] != 0)) && (param_2 != 0)))) {
    if (param_1 + param_2 < param_1) {
LAB_08014666:
      ((code*)DAT_0804cd60)("boot_clobber_prot.c",0x1ff,0x303f);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    while( true ) {
      uVar1 = ((uint*)&DAT_0804ce00)[iVar2 * 2];
      if ((uVar1 == 0) && (((uint*)&DAT_0804ce00)[iVar2 * 2 + 1] == 0)) {
        if (false) {
          return 0;
        }
        goto LAB_08014666;
      }
      if ((uVar1 <= param_1) && (param_1 + param_2 <= uVar1 + ((uint*)&DAT_0804ce00)[iVar2 * 2 + 1])) break;
      iVar2 = iVar2 + 1;
    }
  }
  return 1;
}




/* 0x08014694 */
int FUN_08014694(param_1, param_2, param_3)
uint * param_1; uint param_2; uint param_3;
{
  int iVar1;
  uint uVar2;
  
  if (param_1 == (uint *)0x0) {
    ((code*)DAT_0804cd60)("boot_clobber_prot_local.c",0xff,0x303f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (CARRY4(param_2,param_3)) {
    ((code*)DAT_0804cd60)("boot_clobber_prot_local.c",0x105);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  for (uVar2 = 0; uVar2 < *param_1; uVar2 = uVar2 + 1) {
    if (((param_1[uVar2 * 2 + 1] <= param_2) &&
        (param_2 + param_3 <= param_1[uVar2 * 2 + 1] + param_1[uVar2 * 2 + 2])) &&
       (param_3 <= param_1[uVar2 * 2 + 2])) {
      return 1;
    }
  }
  FUN_08014618(param_2,param_3);
  iVar1 = 1;
  if (param_2 + param_3 < param_2) {
    ((code*)DAT_0804cd60)("boot_clobber_prot.c",0x101);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar2 = 0;
  do {
    if (DAT_08052920 <= uVar2) {
      if (iVar1 != 0) {
        return iVar1;
      }
      break;
    }
    if ((param_2 < (uint)((&DAT_08052928)[uVar2 * 2] + (&DAT_08052924)[uVar2 * 2])) &&
       ((uint)(&DAT_08052924)[uVar2 * 2] < param_2 + param_3)) {
      iVar1 = 0;
    }
    uVar2 = uVar2 + 1;
  } while (iVar1 != 0);
  ((code*)DAT_0804cd60)("boot_clobber_prot.c",0x114,0x303f);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x0801471c */
void FUN_0801471c()
{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  FUN_08014778(&DAT_87c00000,0xe0000);
  if (DAT_0804ce00 != 0) {
    while ((iVar1 = *(int *)(DAT_0804ce00 + iVar2 * 8), iVar1 != 0 ||
           (*(int *)(DAT_0804ce00 + iVar2 * 8 + 4) != 0))) {
      FUN_08007f08(iVar1,0,*(undefined4 *)(DAT_0804ce00 + iVar2 * 8 + 4));
      iVar2 = iVar2 + 1;
    }
  }
  return;
}




/* 0x08014760 */
void FUN_08014760(param_1)
undefined4 param_1;
{
  DAT_0804ce00 = param_1;
  return;
}




/* 0x0801476c */
void FUN_0801476c(param_1)
undefined4 * param_1;
{
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = 0;
  }
  return;
}




/* 0x08014778 */
undefined4 FUN_08014778(param_1, param_2)
uint param_1; int param_2;
{
  uint uVar1;
  int iVar2;
  
  iVar2 = 0;
  if ((DAT_0804ce00 != (int *)0x0) &&
     (((*(uint*)DAT_0804ce00 != 0 || (((uint*)&DAT_0804ce00)[1] != 0)) && (param_2 != 0)))) {
    if (param_1 + param_2 < param_1) {
      return 0;
    }
    while( true ) {
      uVar1 = ((uint*)&DAT_0804ce00)[iVar2 * 2];
      if ((uVar1 == 0) && (((uint*)&DAT_0804ce00)[iVar2 * 2 + 1] == 0)) {
        return 0;
      }
      if ((uVar1 <= param_1) && (param_1 + param_2 <= uVar1 + ((uint*)&DAT_0804ce00)[iVar2 * 2 + 1])) break;
      iVar2 = iVar2 + 1;
    }
    ((uint*)&DAT_0804ce00)[iVar2 * 2 + 1] = 0;
  }
  return 1;
}




