/* Auto-generated: boot_config_emmc.c */
/* Functions: 1 */
#include "globals.h"

/* 0x08019628 */
void boot_read_cdt(param_1)
uint * param_1;
{
  ushort *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined2 *puVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int local_30 [2];
  
  iVar7 = 0;
  local_30[1] = 0;
  local_30[0] = 0;
  if ((param_1 == (uint *)0x0) || (param_1[1] == 0)) {
    ((code*)DAT_0804cd60)("boot_config_emmc.c",0x6f,0x300d);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar2 = FUN_08019964();
  if (iVar2 != 0) {
    iVar2 = FUN_08015bc0();
    (**(code **)(*(int *)(iVar2 + 4) + 0x28))(&DAT_0804ce68);
    iVar2 = FUN_08015bc0();
    local_30[0] = ((code *)**(undefined4 **)(iVar2 + 4))(0x1b);
    if (local_30[0] != 0) {
      FUN_0801453c(local_30[0] + 8,&DAT_08053f5c,0x36);
      iVar2 = FUN_08015e28(local_30[0],&DAT_08053f5c,0,0x36);
      if (iVar2 == 1) {
        FUN_080147d4(local_30[0] + 8,&DAT_08053f5c,0x36);
        iVar2 = FUN_08006e04(&DAT_08053f5c);
        if (iVar2 != 0x544443) {
          boot_log_message("Error: CDT is not programmed");
          ((code*)DAT_0804cd60)("boot_config_emmc.c",0x9d,0x305e);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        puVar4 = (undefined2 *)&DAT_08053f6a;
        uVar6 = (uint)_DAT_08053f6a;
        *param_1 = uVar6;
        if ((uVar6 == 0) || (0x7ff < uVar6)) {
          boot_log_message("Error: Platform ID is not programmed");
          ((code*)DAT_0804cd60)("boot_config_emmc.c",0xa8,0x305e);
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        for (uVar5 = 0xe; uVar5 < uVar6; uVar5 = uVar5 + 4) {
          FUN_08030b34(param_1[1] + uVar5,puVar4,4);
          uVar3 = FUN_08016020(param_1[1],iVar7,local_30 + 1);
          FUN_0801453c(local_30[0] + 8,uVar3,puVar4[1]);
          iVar2 = FUN_08015e28(local_30[0],uVar3,*puVar4,puVar4[1]);
          if (iVar2 != 1) {
            if (DAT_0804d158 == 1) {
              boot_log_message("Error: eMMC read fail");
              ((code*)DAT_0804cd60)("boot_config_emmc.c",200,0x305e);
              do {
                    /* WARNING: Do nothing block with infinite loop */
              } while( true );
            }
            break;
          }
          FUN_080147d4(local_30[0] + 8,uVar3,puVar4[1]);
          iVar7 = iVar7 + 1;
          puVar1 = puVar4 + 1;
          puVar4 = puVar4 + 2;
          *param_1 = *param_1 + (uint)*puVar1;
        }
      }
      else if (DAT_0804d158 == 1) {
        boot_log_message("Error: eMMC read fail");
        ((code*)DAT_0804cd60)("boot_config_emmc.c",0x90,0x305e);
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      iVar7 = FUN_08015bc0();
      (**(code **)(*(int *)(iVar7 + 4) + 8))(local_30);
    }
  }
  return;
}




