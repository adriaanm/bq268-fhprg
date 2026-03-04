/* Auto-generated: sbl1_config.c */
/* Functions: 3 */
#include "globals.h"

/* 0x08030c40 */
void boot_qsee_exec(param_1)
int * param_1;
{
  int *piVar1;
  int iVar2;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 uStack_20;
  undefined4 local_1c;
  
  DAT_00223b90 = 0;
  DAT_00223b88 = (code *)0x0;
  DAT_00223b8c = 0;
  boot_log_message("QSEE Execution, Start");
  thunk_FUN_080192b8();
  FUN_08007de0();
  FUN_08016c94("QSEE Execution, Delta");
  sbl1_main_ctl();
  FUN_08031a74();
  if (DAT_0804c008 != 0) {
    FUN_08014dbc();
    thunk_FUN_00220358(1);
  }
  piVar1 = param_1 + 2;
  DAT_00223b88 = (code *)FUN_08018d94(piVar1,7);
  DAT_00223b8c = 0;
  DAT_00223b90 = FUN_08018d6a(piVar1,7);
  if (DAT_00223b88 == (code *)0x0 && DAT_00223b8c == 0) {
    ((code*)DAT_0804cd60)("sbl1_config.c",0x1e8,0x300d);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if ((DAT_00223b90 != 2) && (DAT_00223b90 != 1)) {
    ((code*)DAT_0804cd60)("sbl1_config.c",0x1ec,0x303d);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  local_38 = 0x87e80000;
  local_34 = 0x87e80000;
  local_30 = 0x600;
  local_2c = 2;
  local_28 = 0x30;
  local_24 = 0x40;
  uStack_20 = 0;
  local_1c = 0;
  iVar2 = FUN_08016dd4(*(undefined4 *)(*param_1 + 0x24),&local_38);
  if (iVar2 == 0) {
    ((code*)DAT_0804cd60)("sbl1_config.c",0x1fe,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (DAT_00223b90 == 2) {
    if (DAT_00223b8c != 0) {
      ((code*)DAT_0804cd60)("sbl1_config.c",0x20c,0x3061);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (-1 < _DAT_0005c054 << 0x11) {
      ((code*)DAT_0804cd60)("sbl1_config.c",0x210,0x3063);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    thunk_FUN_00220388(DAT_00223b88,piVar1);
  }
  else {
    ((code*)DAT_00223b88)(piVar1);
  }
  return;
}




/* 0x0803166c */
undefined4 FUN_0803166c()
{
  int iVar1;
  int local_8;
  
  local_8 = 0;
  iVar1 = FUN_08016484(&local_8);
  if (iVar1 != 0) {
    ((code*)DAT_0804cd60)("sbl1_config.c",0x226,0x302e);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar1 = FUN_08014da8();
  if ((iVar1 == 1) && (local_8 == 0)) {
    return 1;
  }
  return 0;
}




/* 0x080316d4 */
void sbl1_main_ctl()
{
  boot_log_message("SBL1, End");
  FUN_08016844(DAT_0804c004,"SBL1, Delta");
  FUN_08019330();
  FUN_080167dc();
  FUN_08016872(&DAT_0804c070);
  if (DAT_0804cea0 != 0) {
    FUN_08016874(*(undefined4 *)(DAT_0804cea0 + 8));
    return;
  }
  return;
}




