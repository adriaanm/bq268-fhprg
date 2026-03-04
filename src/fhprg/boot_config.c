/* Auto-generated: boot_config.c */
/* Functions: 7 */
#include "globals.h"

/* 0x0801495c */
void boot_load_image(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  undefined1 auStack_b4 [12];
  undefined4 local_a8;
  undefined1 auStack_8c [96];
  int local_2c;
  
  iVar1 = DAT_0804cd58;
  local_2c = DAT_0804cd58;
  uVar6 = 0;
  local_a8 = 0;
  if (param_2 == 0) {
    ((code*)DAT_0804cd60)("boot_config.c",0x95,0x300d);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_08014e28(param_1,*(undefined4 *)(param_2 + 0x2c));
  if ((*(code **)(param_2 + 0x34) != (code *)0x0) &&
     (iVar2 = (**(code **)(param_2 + 0x34))(param_1), iVar2 == 1)) {
    *(undefined4 *)(param_2 + 0x14) = 0;
  }
  if (*(int *)(param_2 + 0x40) != 0) {
    FUN_08014760();
  }
  iVar2 = param_1 + *(int *)(param_1 + 0x14) * 0x70;
  *(undefined4 *)(iVar2 + 0x20) = *(undefined4 *)(param_2 + 0x10);
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
  FUN_080193b8();
  if (*(int *)(param_2 + 0x14) == 1) {
    uVar6 = thunk_FUN_08016180();
    boot_log_message("Image Load, Start");
    iVar3 = *(int *)(param_2 + 0xc);
    if (iVar3 == 0) {
      iVar3 = FUN_08019964();
      if (iVar3 == 0) {
        FUN_08032794(auStack_b4,**(undefined4 **)(param_2 + 0x38),0,*(undefined4 *)(param_2 + 0x10),
                     *(undefined4 *)(param_2 + 0x18),*(undefined4 *)(param_2 + 0x20),param_1);
      }
      else {
        if (*(int *)(param_2 + 8) == 0x1b) {
          iVar3 = *(int *)(param_2 + 0x38);
          if (iVar3 == 0) {
            ((code*)DAT_0804cd60)("boot_config.c",0xcf,0x300d);
            do {
                    /* WARNING: Do nothing block with infinite loop */
            } while( true );
          }
          iVar4 = FUN_08015bc0();
          (**(code **)(*(int *)(iVar4 + 4) + 0x28))(iVar3);
        }
        FUN_080165d8(*(undefined4 *)(param_2 + 8),auStack_b4);
        if (*(int *)(param_2 + 0x18) == 1) {
          FUN_08014364(auStack_b4);
          iVar3 = FUN_080142b8(param_1,*(undefined4 *)(param_2 + 0x10));
          if (iVar3 != 0) {
            ((code*)DAT_0804cd60)("boot_config.c",0xe0);
            do {
                    /* WARNING: Do nothing block with infinite loop */
            } while( true );
          }
        }
      }
      uVar5 = FUN_08016178(param_1);
      FUN_08030b34(iVar2 + 0x30,uVar5,0x50);
      *(undefined4 *)(iVar2 + 0x28) = local_a8;
      *(undefined4 *)(iVar2 + 0x2c) = 0;
    }
    else if (iVar3 == 1) {
      iVar3 = FUN_08019964();
      if (iVar3 == 0) {
        if (*(uint *)(param_2 + 0x44) == 1) {
          FUN_08018c18();
        }
        FUN_08032794(auStack_b4,**(undefined4 **)(param_2 + 0x38),1,*(undefined4 *)(param_2 + 0x10),
                     *(undefined4 *)(param_2 + 0x18),*(undefined4 *)(param_2 + 0x20),param_1);
        FUN_08018c18(0);
        uVar5 = FUN_08016178(param_1);
        FUN_08030b34(iVar2 + 0x30,uVar5,0x50);
        uVar5 = FUN_08017c14();
        *(undefined4 *)(iVar2 + 0x28) = uVar5;
        *(undefined4 *)(iVar2 + 0x2c) = 0;
        uVar5 = FUN_08017c10();
      }
      else {
        FUN_080155d4(*(uint *)(param_2 + 0x18) & 0xff,*(uint *)(param_2 + 0x44) & 0xff);
        if (*(int *)(param_2 + 0x38) == 0) {
          ((code*)DAT_0804cd60)("boot_config.c",0x108,0x300d);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        FUN_0801503c(*(int *)(param_2 + 0x38),auStack_b4);
        if (*(int *)(param_2 + 0x18) == 1) {
          FUN_08014364(auStack_b4);
          FUN_08016164();
          FUN_080195a4();
          iVar3 = FUN_080142b8(param_1,*(undefined4 *)(param_2 + 0x10));
          if (iVar3 != 0) {
            ((code*)DAT_0804cd60)("boot_config.c",0x11d);
            do {
                    /* WARNING: Do nothing block with infinite loop */
            } while( true );
          }
          FUN_08018fa4(1);
          FUN_080155e0();
        }
        FUN_08016574();
        FUN_080155d4(0);
        uVar5 = FUN_08016178(param_1);
        FUN_08030b34(iVar2 + 0x30,uVar5,0x50);
        uVar7 = FUN_08016138();
        *(undefined8 *)(iVar2 + 0x28) = uVar7;
        uVar5 = FUN_0801612c();
      }
      *(undefined4 *)(iVar2 + 0x24) = uVar5;
    }
    else if (iVar3 != 2) {
      ((code*)DAT_0804cd60)("boot_config.c",0x166,0x3056);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
  }
  if (*(int *)(param_2 + 0x3c) == 0) {
    ((code*)DAT_0804cd60)("boot_config.c",0x16a,0x300d);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (*(int *)(param_2 + 0x14) == 1) {
    uVar5 = FUN_08019314();
    snprintf_buf(auStack_8c,0x60,"(%d Bytes)",uVar5);
    FUN_0801684a(uVar6,*(undefined4 *)(param_2 + 0x3c),auStack_8c);
  }
  if (((*(int *)(param_2 + 0x1c) == 1) && (*(int *)(param_2 + 0x20) == 0)) &&
     (*(int *)(param_2 + 0x14) == 1)) {
    if (*(int *)(param_2 + 0x18) != 1) {
      ((code*)DAT_0804cd60)("boot_config.c",0x187,0x3056);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (*(code **)(param_2 + 0x24) == (code *)0x0) {
      ((code*)DAT_0804cd60)("boot_config.c",0x18a,0x300d);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    (**(code **)(param_2 + 0x24))(param_1);
  }
  FUN_08014e28(param_1,*(undefined4 *)(param_2 + 0x30));
  if (((*(int *)(param_2 + 0x20) == 1) && (*(int *)(param_2 + 0x1c) == 0)) &&
     (*(int *)(param_2 + 0x14) == 1)) {
    if (*(int *)(param_2 + 0x18) != 1) {
      ((code*)DAT_0804cd60)("boot_config.c",0x19e,0x3056);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (*(code **)(param_2 + 0x28) == (code *)0x0) {
      ((code*)DAT_0804cd60)("boot_config.c",0x1a1,0x300d);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    (**(code **)(param_2 + 0x28))(param_1);
  }
  if (local_2c == iVar1) {
    return;
  }
  FUN_08010960();
  return;
}




/* 0x08014c60 */
int FUN_08014c60(param_1)
uint param_1;
{
  int iVar1;
  
  iVar1 = 0;
  for (; param_1 != 0; param_1 = param_1 & param_1 - 1) {
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08014d88 */
bool FUN_08014d88()
{
  bool bVar1;
  
  bVar1 = (_DAT_0193d100 & 0x10) != 0;
  if (bVar1) {
    _DAT_0193d100 = _DAT_0193d100 & 0xffffffef;
  }
  return bVar1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08014da8 */
undefined4 FUN_08014da8()
{
  if (_DAT_0193d100 << 0x1b < 0) {
    return 1;
  }
  return 0;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08014dbc */
void FUN_08014dbc()
{
  _DAT_0193d100 = _DAT_0193d100 | 0x10;
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08014e0c */
void FUN_08014e0c()
{
  _DAT_0193d100 = _DAT_0193d100 & 0xfffffff0 | 1;
  thunk_FUN_00220358(1);
  return;
}




/* 0x08031f88 */
void FUN_08031f88(param_1)
undefined4 param_1;
{
  int iVar1;
  int *piVar2;
  undefined4 unaff_r4 = 0;
  undefined4 unaff_r5 = 0;
  undefined4 unaff_r6 = 0;
  undefined4 unaff_lr = 0;
  
  DAT_0804c004 = _DAT_004a3000 * 0x1e + (_DAT_004a3000 >> 1);
  FUN_080089e0(0x100);
  FUN_08007ef0(0x55555555);
  thunk_FUN_0800a790();
  do {
  } while (_DAT_08600944 == 0x53444247);
  FUN_080163a8();
  FUN_08019200(&DAT_08051b60);
  iVar1 = thunk_qtimer_init();
  if (iVar1 != 0) {
    ((code*)DAT_0804cd60)("sbl1_mc.c",0x58e,0x3056);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_08016918(&DAT_0804c070);
  FUN_08016ebc(param_1);
  FUN_08016c80(0);
  FUN_08016adc("SBL1, Start",DAT_0804c004,0x42,0);
  FUN_08016c74(DAT_0804c078);
  FUN_08032280(param_1);
  FUN_08031ccc(&DAT_08051b60,&DAT_08051d78);
  FUN_08032114(&DAT_08051b60);
  iVar1 = FUN_08018dec(&DAT_08051b60);
  if (iVar1 != 0) {
    ((code*)DAT_0804cd60)("sbl1_mc.c",0x5a1,0x302e);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar1 = FUN_08018f7c(2);
  if (iVar1 != 0) {
    ((code*)DAT_0804cd60)("sbl1_mc.c",0x5a5,iVar1);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  thunk_FUN_0800b5e0(&DAT_0805a8b0,0x1800,0);
  thunk_FUN_0800b604(0);
  FUN_08019408(&DAT_08051b60,&DAT_08051d78);
  FUN_08017aa4(&DAT_08051b60,&DAT_0804cb28,DAT_0804cc18);
  if (DAT_0804c008 != 0) {
    FUN_08014dbc();
    thunk_FUN_00220358(1);
  }
  FUN_080144b4(&LAB_08006000,0x7b000);
  FUN_080144b4(&DAT_87c00000,0xe0000);
  FUN_080144b4(&DAT_00220000,0x4000);
  FUN_080144b4(0x87d00000,0x100000);
  FUN_080144b4(&DAT_08600000,0x4000);
  if ((true) && (true)) {
    for (piVar2 = &DAT_0804c194; *piVar2 != 0; piVar2 = piVar2 + 0x19) {
      if (*piVar2 == 0x15) {
        boot_load_image(&DAT_08051b60,piVar2);
      }
    }
    return;
  }
  ((code*)DAT_0804cd60)("boot_config.c",0x1cd,0x300d,DAT_0804cd60,unaff_r4,unaff_r5,unaff_r6,unaff_lr);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




