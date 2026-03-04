/* Auto-generated: boot_flash_dev_sdcc.c */
/* Functions: 3 */
#include "globals.h"

/* 0x08015d0c */
void FUN_08015d0c(param_1, param_2, param_3)
undefined4 param_1; code * param_2; undefined4 * param_3;
{
  DAT_08054620 = &DAT_08039970;
  DAT_08054624 = &PTR_LAB_0801b92c_1_0804d404;
  FUN_08018fb0(*param_3);
  thunk_FUN_08026370();
  FUN_08015c34(&DAT_08054620);
  FUN_08015cc8(&DAT_08054620);
  DAT_08054628 = (*param_2)();
  if (DAT_08054628 == 0) {
    ((code*)DAT_0804cd60)("boot_flash_dev_sdcc.c",0x2d5,0x300d);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return;
}




/* 0x08018fb0 */
void FUN_08018fb0(param_1)
int param_1;
{
  char cVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  
  if (param_1 == 0) {
    ((code*)DAT_0804cd60)("boot_flash_dev_sdcc.c",0x21f,0x300d);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  psVar2 = *(short **)(param_1 + 0x14);
  if (psVar2 == (short *)0x0) {
    iVar3 = FUN_08016e20();
    if (iVar3 == 0) {
      ((code*)DAT_0804cd60)("boot_flash_dev_sdcc.c",0x22c,0x3003);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (*(int *)(iVar3 + 0xc) != 4) {
      return;
    }
    DAT_080543f8 = (undefined2)*(undefined4 *)(iVar3 + 0x2c);
    iVar4 = *(int *)(iVar3 + 0x24);
    if (iVar4 == 1) {
      DAT_080543f6 = 1;
    }
    else if (iVar4 == 2) {
      DAT_080543f6 = 2;
    }
    else if ((iVar4 == 5) || (iVar4 == 6)) {
      DAT_080543f6 = (undefined1)iVar4;
    }
    else {
      DAT_080543f6 = 0;
    }
    if (*(int *)(iVar3 + 0x30) == 1) {
      DAT_080543fb = 2;
    }
    iVar4 = *(int *)(iVar3 + 0x34);
    if (iVar4 == 0) {
      DAT_080543f4 = 0;
    }
    else if (iVar4 == 1) {
      DAT_080543f4 = 1;
    }
    else if (iVar4 == 2) {
      DAT_080543f4 = 2;
    }
    else if (iVar4 == 3) {
      DAT_080543f4 = 3;
    }
    iVar3 = *(int *)(iVar3 + 8);
    if (iVar3 == 0) {
      DAT_080543fa = 0;
    }
    else if (iVar3 == 1) {
      DAT_080543fa = 1;
    }
    else if (iVar3 == 2) {
      DAT_080543fa = 2;
    }
    DAT_080543fc = 0;
    *(undefined2 **)(param_1 + 0x14) = &DAT_080543f4;
    psVar2 = &DAT_080543f4;
  }
  if ((psVar2 != (short *)0x0) &&
     ((((cVar1 = (char)psVar2[1], cVar1 == '\x02' || (cVar1 == '\x06')) || (cVar1 == '\x01')) ||
      (cVar1 == '\x05')))) {
    DAT_0804d65c = (int)*psVar2;
    DAT_0804d660 = (undefined1)psVar2[1];
    DAT_0804d662 = psVar2[2];
  }
  return;
}




/* 0x0801b878 */
void FUN_0801b878(param_1)
int param_1;
{
  int iVar1;
  
  if (param_1 == -1) {
    ((code*)DAT_0804cd60)("boot_flash_dev_sdcc.c",0x105,0x304e);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar1 = FUN_08025d9c();
  if (iVar1 != 0) {
    ((code*)DAT_0804cd60)("boot_flash_dev_sdcc.c",0x109,0x304c);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return;
}




