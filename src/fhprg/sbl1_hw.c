/* Auto-generated: sbl1_hw.c */
/* Functions: 7 */
#include "globals.h"

/* 0x08031840 */
void sbl1_hw_init(param_1)
int * param_1;
{
  int iVar1;
  undefined1 auStack_88 [56];
  undefined1 auStack_50 [52];
  undefined4 local_1c;
  uint local_18 [2];
  
  local_18[0] = 0;
  boot_log_message("sbl1_ddr_set_params, Start");
  thunk_FUN_080192b8();
  iVar1 = FUN_08016020(*(undefined4 *)(*(int *)(*param_1 + 0x10) + 4),1,local_18);
  if ((0x800 < local_18[0]) || (iVar1 == 0)) {
    ((code*)DAT_0804cd60)("sbl1_hw.c",0x220,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_08030b34(0x8600190);
  iVar1 = thunk_FUN_00222780(0x8600190,local_18[0]);
  if (iVar1 != 1) {
    ((code*)DAT_0804cd60)("sbl1_hw.c",0x229,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_08031d18();
  thunk_FUN_00222248(auStack_88);
  FUN_08006bdc(auStack_50,auStack_88,0x38);
  boot_log_message("cpr_init, Start");
  thunk_FUN_080192b8();
  FUN_08016c94("cpr_init, Delta");
  boot_log_message("Pre_DDR_clock_init, Start");
  thunk_FUN_080192b8();
  iVar1 = thunk_FUN_0800ac84(local_1c);
  if (iVar1 != 1) {
    ((code*)DAT_0804cd60)("sbl1_hw.c",0x241,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_08016c94("Pre_DDR_clock_init, Delta");
  iVar1 = thunk_FUN_0800d330("/dev/icbcfg/boot");
  if (iVar1 != 0) {
    ((code*)DAT_0804cd60)("sbl1_hw.c",0x246,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_08016c94("sbl1_ddr_set_params, Delta");
  return;
}




/* 0x080319cc */
void FUN_080319cc()
{
  FUN_0801789c(&DAT_0804c034);
  FUN_0801789c(&DAT_0804c048);
  FUN_0801789c(&DAT_0804c05c);
  return;
}




/* 0x08031a74 */
void FUN_08031a74()
{
  int iVar1;
  
  iVar1 = thunk_FUN_0800a9d0();
  if (iVar1 != 1) {
    ((code*)DAT_0804cd60)("sbl1_hw.c",0x170,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return;
}




/* 0x08031aa8 */
undefined4 pm_device_init_status()
{
  return DAT_0804c090;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08031ab4 */
void sbl1_post_init(param_1)
int param_1;
{
  int iVar1;
  
  iVar1 = thunk_tsens_init();
  if (iVar1 != 0) {
    ((code*)DAT_0804cd60)("sbl1_hw.c",0x13a,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  thunk_FUN_0800aa5c();
  if (*(char *)(param_1 + 0x1e0) != '\x02') {
    boot_log_message("pm_device_init, Start");
    thunk_FUN_080192b8();
    iVar1 = thunk_pm_device_init_core();
    if (iVar1 != 0) {
      ((code*)DAT_0804cd60)("sbl1_hw.c",0x147,0x3056);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    FUN_08016c94("pm_device_init, Delta");
  }
  FUN_08014480();
  _DAT_01815008 = _DAT_01815008 & 0x2f;
  return;
}




/* 0x08031ccc */
void FUN_08031ccc(param_1, param_2)
int param_1; undefined4 param_2;
{
  FUN_08007f08(param_1 + 8,0,0x1d8);
  *(undefined4 *)(param_1 + 8) = 0xce473d94;
  *(undefined4 *)(param_1 + 0xc) = 0x3cb237ba;
  *(undefined4 *)(param_1 + 0x10) = 1;
  FUN_08030b34(param_1 + 0x30,param_2,0x50);
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined1 **)(param_1 + 0x28) = &LAB_08006000;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
  return;
}




/* 0x08031d18 */
void FUN_08031d18()
{
  int iVar1;
  undefined4 local_10;
  
  local_10 = 0;
  iVar1 = thunk_FUN_002225f4();
  if ((iVar1 == 1) && (iVar1 = FUN_08014da8(), iVar1 == 0)) {
    thunk_FUN_002225e4(&local_10);
    FUN_08031d74(0x8081000,local_10);
    iVar1 = thunk_FUN_00222650(0x8081000,local_10);
    if (iVar1 == 0) {
      ((code*)DAT_0804cd60)("sbl1_hw.c",0x2ca,0x3056);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
  }
  return;
}




