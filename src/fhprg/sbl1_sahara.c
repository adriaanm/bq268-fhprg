/* Auto-generated: sbl1_sahara.c */
/* Functions: 2 */
#include "globals.h"

/* 0x080326e0 */
void FUN_080326e0(param_1, param_2, param_3)
char * param_1; uint param_2; int param_3;
{
  code *pcVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  
  iVar2 = DAT_0804cdf8;
  pcVar1 = DAT_0804cd60;
  iVar4 = 0;
  if (99 < param_2) {
    ((code*)DAT_0804cd60)("sbl1_sahara.c",0x299,0x303a);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar5 = 0;
  do {
    if (param_2 <= uVar5) {
      return;
    }
    pcVar3 = param_1 + iVar4;
    if ((param_1 + (0xa000 - iVar2) < pcVar3) || (pcVar3 < param_1)) {
      (*pcVar1)("sbl1_sahara.c",0x2a2,0x3056);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *(char **)(uVar5 * 4 + -0x7838f000) = pcVar3;
    if (*(int *)(param_3 + 0x18) << 0xb < 0) {
      if (*(int *)(param_3 + 0x10) != 0) {
        iVar4 = ((*(int *)(param_3 + 0x10) - 1U >> 0xc) + 1) * iVar2 + iVar4;
      }
    }
    else {
      if ((uint)(*(int *)(param_3 + 0x18) << 5) >> 0x1d == 2) {
        pcVar6 = pcVar3 + iVar2;
        do {
          if (*pcVar3 != '\0') goto LAB_0803276a;
          pcVar3 = pcVar3 + 1;
        } while (pcVar3 < pcVar6);
        if (false) goto LAB_0803276a;
      }
      iVar4 = iVar4 + iVar2;
    }
LAB_0803276a:
    uVar5 = uVar5 + 1;
    param_3 = param_3 + 0x20;
  } while( true );
}




/* 0x08032794 */
void FUN_08032794()
{
  ((code*)DAT_0804cd60)("sbl1_sahara.c",0x541,0x302f);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




