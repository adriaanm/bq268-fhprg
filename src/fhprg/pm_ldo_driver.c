/* Auto-generated: pm_ldo_driver.c */
/* Functions: 3 */
#include "globals.h"

/* 0x0802bea4 */
void FUN_0802bea4(param_1, param_2, param_3)
undefined4 param_1; ushort * param_2; uint param_3;
{
  int iVar1;
  uint uVar2;
  undefined4 *local_28;
  undefined4 local_24 [2];
  
  local_24[0] = 0x68;
  local_24[1] = 0x6c;
  local_28 = *(undefined4 **)(&DAT_0805a1f4 + param_3 * 4);
  if (local_28 == (undefined4 *)0x0) {
    FUN_0802c644(0x18,&local_28);
    *local_28 = param_1;
    iVar1 = FUN_0802e824(3);
    local_28[1] = iVar1;
    if (iVar1 == 0) {
      ((code*)DAT_0804cd60)("pm_ldo_driver.c",0x4c,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (1 < param_3) {
      ((code*)DAT_0804cd60)("pm_ldo_driver.c",0x4f,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar1 = FUN_0802e848(local_24[param_3],param_3);
    local_28[2] = iVar1;
    if (iVar1 == 0) {
      ((code*)DAT_0804cd60)("pm_ldo_driver.c",0x54,0x3060);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    FUN_0802c644(iVar1 * 0xc,local_28 + 3);
    *(ushort *)(local_28[3] + 8) = *param_2;
    FUN_0802c644(local_28[2],local_28 + 5);
    *(undefined4 **)(&DAT_0805a1f4 + param_3 * 4) = local_28;
    if (local_28 == (undefined4 *)0x0) {
      return;
    }
  }
  if ((uint)*param_2 < (uint)*(ushort *)(local_28[3] + 8)) {
    ((code*)DAT_0804cd60)("pm_ldo_driver.c",0x6a,0x3060);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar2 = (int)((uint)*param_2 - (uint)*(ushort *)(local_28[3] + 8)) /
          (int)(uint)*(ushort *)(local_28[1] + 2);
  if ((uint)local_28[2] <= uVar2) {
    ((code*)DAT_0804cd60)("pm_ldo_driver.c",0x70,0x3060);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  *(undefined1 *)(local_28[5] + uVar2) = *(undefined1 *)((int)param_2 + 3);
  if ((uint)local_28[2] <= uVar2) {
    ((code*)DAT_0804cd60)("pm_ldo_driver.c",0x76,0x3060);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  *(char *)(local_28[3] + uVar2 * 0xc + 10) = (char)param_2[1];
  *(ushort *)(local_28[3] + uVar2 * 0xc + 8) = *param_2;
  iVar1 = FUN_0802c0c6(param_2);
  *(int *)(local_28[3] + uVar2 * 0xc) = iVar1;
  if (iVar1 != 0) {
    iVar1 = FUN_0802c010(param_2);
    *(int *)(local_28[3] + uVar2 * 0xc + 4) = iVar1;
    if (iVar1 != 0) {
      return;
    }
    ((code*)DAT_0804cd60)("pm_ldo_driver.c",0x86,0x3060);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  ((code*)DAT_0804cd60)("pm_ldo_driver.c",0x81,0x3060);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x0802c010 */
undefined4 FUN_0802c010(param_1)
int param_1;
{
  byte bVar1;
  undefined4 uVar2;
  
  if (*(char *)(param_1 + 2) != '\x04') {
    if (*(char *)(param_1 + 2) != '!') {
      return 0;
    }
    bVar1 = *(byte *)(param_1 + 3);
    if (bVar1 != 0xb) {
      if (bVar1 < 0xc) {
        if (false) {
          return 0;
        }
        switch(bVar1) {
        default:
          goto switchD_0802c028_caseD_0;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
          goto switchD_0802c028_caseD_1;
        case 8:
        case 9:
        case 10:
          goto switchD_0802c028_caseD_8;
        }
      }
      if (bVar1 != 0x29) {
        if (bVar1 < 0x2a) {
          if (bVar1 == 0x14) {
switchD_0802c028_caseD_1:
            uVar2 = 0x35;
            goto LAB_0802c0bc;
          }
          if (bVar1 < 0x15) {
            if (bVar1 != 0xc) {
              if (bVar1 != 0x13) {
                return 0;
              }
              goto switchD_0802c028_caseD_1;
            }
          }
          else {
            if (bVar1 == 0x15) goto switchD_0802c028_caseD_1;
            if (bVar1 != 0x28) {
              return 0;
            }
          }
        }
        else if ((((bVar1 != 0x2a) && (bVar1 != 0x2b)) && (bVar1 != 0x2c)) && (bVar1 != 0x2d)) {
          return 0;
        }
      }
    }
switchD_0802c028_caseD_8:
    uVar2 = 0x33;
    goto LAB_0802c0bc;
  }
  bVar1 = *(byte *)(param_1 + 3);
  if (bVar1 != 10) {
    if (bVar1 < 0xb) {
      if (false) {
switchD_0802c028_caseD_0:
        return 0;
      }
      switch(bVar1) {
      default:
        goto switchD_0802c028_caseD_0;
      case 1:
      case 2:
      case 3:
        uVar2 = 0x11;
        break;
      case 4:
      case 6:
        uVar2 = 0x12;
        break;
      case 5:
      case 7:
        uVar2 = 0x13;
        break;
      case 8:
      case 9:
        goto switchD_0802c042_caseD_8;
      }
      goto LAB_0802c0bc;
    }
    if (bVar1 != 0x28) {
      if (bVar1 < 0x29) {
        if ((bVar1 != 0xb) && (bVar1 != 0xc)) {
          if ((bVar1 != 0x10) && (bVar1 != 0x18)) {
            return 0;
          }
          uVar2 = 0x15;
          goto LAB_0802c0bc;
        }
      }
      else if (((bVar1 != 0x29) && (bVar1 != 0x2a)) && ((bVar1 != 0x2b && (bVar1 != 0x2c)))) {
        return 0;
      }
    }
  }
switchD_0802c042_caseD_8:
  uVar2 = 0x14;
LAB_0802c0bc:
  uVar2 = FUN_0802e824(uVar2);
  return uVar2;
}




/* 0x0802c0c6 */
undefined4 FUN_0802c0c6(param_1)
int param_1;
{
  byte bVar1;
  undefined4 uVar2;
  
  if (*(char *)(param_1 + 2) != '\x04') {
    if (*(char *)(param_1 + 2) != '!') {
      return 0;
    }
    bVar1 = *(byte *)(param_1 + 3);
    if (bVar1 != 0xb) {
      if (bVar1 < 0xc) {
        if (false) {
          return 0;
        }
        switch(bVar1) {
        default:
          goto switchD_0802c0de_caseD_0;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
          goto switchD_0802c0de_caseD_1;
        case 8:
        case 9:
        case 10:
          goto switchD_0802c0de_caseD_8;
        }
      }
      if (bVar1 != 0x29) {
        if (bVar1 < 0x2a) {
          if (bVar1 == 0x14) {
switchD_0802c0de_caseD_1:
            uVar2 = 0x36;
            goto LAB_0802c172;
          }
          if (bVar1 < 0x15) {
            if (bVar1 != 0xc) {
              if (bVar1 != 0x13) {
                return 0;
              }
              goto switchD_0802c0de_caseD_1;
            }
          }
          else {
            if (bVar1 == 0x15) goto switchD_0802c0de_caseD_1;
            if (bVar1 != 0x28) {
              return 0;
            }
          }
        }
        else if ((((bVar1 != 0x2a) && (bVar1 != 0x2b)) && (bVar1 != 0x2c)) && (bVar1 != 0x2d)) {
          return 0;
        }
      }
    }
switchD_0802c0de_caseD_8:
    uVar2 = 0x34;
    goto LAB_0802c172;
  }
  bVar1 = *(byte *)(param_1 + 3);
  if (bVar1 != 10) {
    if (bVar1 < 0xb) {
      if (false) {
switchD_0802c0de_caseD_0:
        return 0;
      }
      switch(bVar1) {
      default:
        goto switchD_0802c0de_caseD_0;
      case 1:
      case 2:
      case 3:
        uVar2 = 9;
        break;
      case 4:
      case 6:
        uVar2 = 10;
        break;
      case 5:
      case 7:
        uVar2 = 0xb;
        break;
      case 8:
      case 9:
        goto switchD_0802c0f8_caseD_8;
      }
      goto LAB_0802c172;
    }
    if (bVar1 != 0x28) {
      if (bVar1 < 0x29) {
        if ((bVar1 != 0xb) && (bVar1 != 0xc)) {
          if ((bVar1 != 0x10) && (bVar1 != 0x18)) {
            return 0;
          }
          uVar2 = 0xd;
          goto LAB_0802c172;
        }
      }
      else if (((bVar1 != 0x29) && (bVar1 != 0x2a)) && ((bVar1 != 0x2b && (bVar1 != 0x2c)))) {
        return 0;
      }
    }
  }
switchD_0802c0f8_caseD_8:
  uVar2 = 0xc;
LAB_0802c172:
  uVar2 = FUN_0802e824(uVar2);
  return uVar2;
}




