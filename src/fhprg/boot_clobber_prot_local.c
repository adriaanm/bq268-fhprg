/* Auto-generated: boot_clobber_prot_local.c */
/* Functions: 4 */
#include "globals.h"

/* 0x0801453c */
void FUN_0801453c(param_1, param_2, param_3)
uint * param_1; uint param_2; uint param_3;
{
  if (param_2 + param_3 < param_2) {
    ((code*)DAT_0804cd60)("boot_clobber_prot_local.c",0x7a,0x303f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if ((param_1 != (uint *)0x0) && (*param_1 < 5)) {
    param_1[*param_1 * 2 + 1] = param_2;
    param_1[*param_1 * 2 + 2] = param_3;
    *param_1 = *param_1 + 1;
    return;
  }
  ((code*)DAT_0804cd60)("boot_clobber_prot_local.c",0x8d,0x303f);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x080147d4 */
void FUN_080147d4(param_1, param_2, param_3)
int * param_1; int param_2; int param_3;
{
  int iVar1;
  
  if (param_3 != 0) {
    if ((((param_1 == (int *)0x0) || (iVar1 = *param_1, iVar1 == 0)) ||
        (param_1[iVar1 * 2 + -1] != param_2)) || (param_1[iVar1 * 2] != param_3)) {
      ((code*)DAT_0804cd60)("boot_clobber_prot_local.c",0xd4,0x303f);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *param_1 = iVar1 + -1;
  }
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08014840 */
void FUN_08014840()
{
  FUN_0800aa60(3);
  return;
}




/* 0x08014850 */
void boot_config_data_table_init(param_1)
int * param_1;
{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_78 [96];
  int local_18;
  
  iVar1 = DAT_0804cd58;
  local_18 = DAT_0804cd58;
  FUN_080193b8();
  boot_log_message("boot_config_data_table_init, Start");
  thunk_FUN_080192b8();
  DAT_0804ce98 = DAT_0804cb24;
  DAT_0804ce9c = &DAT_0804c324;
  boot_read_cdt(&DAT_0804ce98);
  *(undefined4 **)(*param_1 + 0x10) = &DAT_0804ce98;
  uVar2 = FUN_08019314();
  snprintf_buf(auStack_78,0x60,"(%d Bytes)",uVar2);
  FUN_08016c9a("boot_config_data_table_init, Delta",auStack_78);
  if (local_18 != iVar1) {
    FUN_08010960();
    return;
  }
  return;
}




