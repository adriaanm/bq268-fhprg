/* Auto-generated: pm_gpio_driver.c */
/* Functions: 1 */
#include "globals.h"

/* 0x0802d56c */
void FUN_0802d56c(param_1, param_2, param_3)
undefined4 param_1; int param_2; uint param_3;
{
  char cVar1;
  int iVar2;
  undefined4 *local_20;
  undefined4 *local_1c [4];
  
  if (true) {
    switch(*(undefined1 *)(param_2 + 2)) {
    case 2:
      if (*(char *)(param_2 + 3) == ' ') {
        FUN_0802b0d4();
        return;
      }
      FUN_0802a51c();
      return;
    case 3:
    case 0x1c:
    case 0x22:
      FUN_0802e5dc();
      return;
    case 4:
    case 0x21:
      FUN_0802bea4();
      return;
    case 5:
      FUN_0802ed04();
      return;
    case 6:
      FUN_0802af30();
      return;
    case 7:
      local_1c[1] = *(undefined4 **)(&DAT_0805a29c + param_3 * 4);
      if (local_1c[1] == (undefined4 *)0x0) {
        FUN_0802c644(4,local_1c + 1);
        *(undefined4 **)(&DAT_0805a29c + param_3 * 4) = local_1c[1];
      }
      if (*(char *)(param_2 + 3) == '\x01') {
        *local_1c[1] = param_1;
      }
      return;
    case 0x10:
      local_1c[0] = (undefined4 *)0x6e;
      local_1c[1] = (undefined4 *)0x6f;
      local_20 = *(undefined4 **)(&DAT_0805a1a0 + param_3 * 4);
      if (local_20 == (undefined4 *)0x0) {
        FUN_0802c644(0xc,&local_20);
        *local_20 = param_1;
        iVar2 = FUN_0802e824(0x19);
        local_20[1] = iVar2;
        if (iVar2 == 0) {
          ((code*)DAT_0804cd60)("pm_gpio_driver.c",0x3e,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        if (1 < param_3) {
          ((code*)DAT_0804cd60)("pm_gpio_driver.c",0x41,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        cVar1 = FUN_0802e848(local_1c[param_3],param_3);
        *(char *)(local_20 + 2) = cVar1;
        if (cVar1 == '\0') {
          ((code*)DAT_0804cd60)("pm_gpio_driver.c",0x44,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        *(undefined4 **)(&DAT_0805a1a0 + param_3 * 4) = local_20;
      }
      return;
    case 0x11:
      FUN_0802c8ac();
      return;
    case 0x13:
      if (*(char *)(param_2 + 3) != '\v') {
        FUN_0802c3a4(param_1,param_3);
        return;
      }
      local_1c[1] = *(undefined4 **)(&DAT_0805a264 + param_3 * 4);
      if (local_1c[1] == (undefined4 *)0x0) {
        FUN_0802c644(0xc,local_1c + 1);
        *local_1c[1] = param_1;
        iVar2 = FUN_0802e824(0x2e);
        local_1c[1][1] = iVar2;
        if (iVar2 == 0) {
          ((code*)DAT_0804cd60)("pm_pwm_driver.c",0x3d,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        cVar1 = FUN_0802e848(0x84,param_3);
        *(char *)(local_1c[1] + 2) = cVar1;
        if (cVar1 == '\0') {
          ((code*)DAT_0804cd60)("pm_pwm_driver.c",0x40,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        *(undefined4 **)(&DAT_0805a264 + param_3 * 4) = local_1c[1];
      }
      return;
    case 0x15:
      local_1c[0] = (undefined4 *)0x76;
      local_1c[1] = (undefined4 *)0x77;
      local_20 = *(undefined4 **)(&DAT_0805a314 + param_3 * 4);
      if (local_20 == (undefined4 *)0x0) {
        FUN_0802c644(0x10,&local_20);
        *local_20 = param_1;
        iVar2 = FUN_0802e824(0x1d);
        local_20[2] = iVar2;
        if (iVar2 == 0) {
          ((code*)DAT_0804cd60)("pm_vib_driver.c",0x3c,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        iVar2 = FUN_0802e86c(0x20);
        local_20[3] = iVar2;
        if (iVar2 == 0) {
          ((code*)DAT_0804cd60)("pm_vib_driver.c",0x3f,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        if (1 < param_3) {
          ((code*)DAT_0804cd60)("pm_vib_driver.c",0x42,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        iVar2 = FUN_0802e848(local_1c[param_3],param_3);
        local_20[1] = iVar2;
        if (iVar2 == 0) {
          ((code*)DAT_0804cd60)("pm_vib_driver.c",0x46,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        *(undefined4 **)(&DAT_0805a314 + param_3 * 4) = local_20;
      }
      return;
    case 0x16:
      FUN_0802ca18();
      return;
    case 0x17:
      local_1c[1] = *(undefined4 **)(&DAT_0805a34c + param_3 * 4);
      if (local_1c[1] == (undefined4 *)0x0) {
        FUN_0802c644(0xc,local_1c + 1);
        *local_1c[1] = param_1;
        iVar2 = FUN_0802e824(0x1e);
        local_1c[1][1] = iVar2;
        if (iVar2 == 0) {
          ((code*)DAT_0804cd60)("pm_wled_driver.c",0x42,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        cVar1 = FUN_0802e848(0x85,param_3);
        *(char *)(local_1c[1] + 2) = cVar1;
        if (cVar1 == '\0') {
          ((code*)DAT_0804cd60)("pm_wled_driver.c",0x46,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        *(undefined4 **)(&DAT_0805a34c + param_3 * 4) = local_1c[1];
      }
      return;
    case 0x19:
      local_1c[0] = (undefined4 *)0x74;
      local_1c[1] = (undefined4 *)0x75;
      local_20 = *(undefined4 **)(&DAT_0805a280 + param_3 * 4);
      if (local_20 == (undefined4 *)0x0) {
        FUN_0802c644(0xc,&local_20);
        *local_20 = param_1;
        iVar2 = FUN_0802e824(0x1b);
        local_20[1] = iVar2;
        if (iVar2 == 0) {
          ((code*)DAT_0804cd60)("pm_rgb_driver.c",0x3b,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        if (1 < param_3) {
          ((code*)DAT_0804cd60)("pm_rgb_driver.c",0x3e,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        cVar1 = FUN_0802e848(local_1c[param_3],param_3);
        *(char *)(local_20 + 2) = cVar1;
        if (cVar1 == '\0') {
          ((code*)DAT_0804cd60)("pm_rgb_driver.c",0x41,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        *(undefined4 **)(&DAT_0805a280 + param_3 * 4) = local_20;
      }
      return;
    case 0x20:
      local_1c[1] = *(undefined4 **)(&DAT_0805a1bc + param_3 * 4);
      if (local_1c[1] == (undefined4 *)0x0) {
        FUN_0802c644(0xc,local_1c + 1);
        *local_1c[1] = param_1;
        iVar2 = FUN_0802e824(0x2c);
        local_1c[1][1] = iVar2;
        if (iVar2 == 0) {
          ((code*)DAT_0804cd60)("pm_ibb_driver.c",0x3e,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        cVar1 = FUN_0802e848(0x82,param_3);
        *(char *)(local_1c[1] + 2) = cVar1;
        if (cVar1 == '\0') {
          ((code*)DAT_0804cd60)("pm_ibb_driver.c",0x41,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        *(undefined4 **)(&DAT_0805a1bc + param_3 * 4) = local_1c[1];
      }
      return;
    case 0x24:
      local_1c[1] = *(undefined4 **)(&DAT_0805a1d8 + param_3 * 4);
      if (local_1c[1] == (undefined4 *)0x0) {
        FUN_0802c644(0xc,local_1c + 1);
        *local_1c[1] = param_1;
        iVar2 = FUN_0802e824(0x2d);
        local_1c[1][1] = iVar2;
        if (iVar2 == 0) {
          ((code*)DAT_0804cd60)("pm_lab_driver.c",0x40,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        cVar1 = FUN_0802e848(0x83,param_3);
        *(char *)(local_1c[1] + 2) = cVar1;
        if (cVar1 == '\0') {
          ((code*)DAT_0804cd60)("pm_lab_driver.c",0x43,0x3060);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        *(undefined4 **)(&DAT_0805a1d8 + param_3 * 4) = local_1c[1];
      }
      return;
    }
  }
  return;
}




