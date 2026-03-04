/* Auto-generated: boot_config_data.c */
/* Functions: 1 */
#include "globals.h"

/* 0x08016020 */
undefined4 FUN_08016020(param_1, param_2, param_3)
uint param_1; int param_2; uint * param_3;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  ushort *puVar4;
  ushort *puVar5;
  
  *param_3 = 0;
  if (param_1 != 0) {
    puVar5 = (ushort *)(*(ushort *)(param_1 + 0xe) + param_1);
    if (CARRY4((uint)*(ushort *)(param_1 + 0xe),param_1)) {
      ((code*)DAT_0804cd60)("boot_config_data.c",199,0x3007);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    puVar4 = (ushort *)(param_1 + 0xe + param_2 * 4);
    iVar1 = FUN_08006e04(param_1);
    if (((((iVar1 == 0x544443) && (puVar4 < puVar5)) &&
         (uVar2 = (uint)*puVar4, puVar5 <= (ushort *)(uVar2 + param_1))) &&
        ((uVar2 < 0x800 && (uVar3 = (uint)puVar4[1], uVar3 != 0)))) &&
       ((uVar2 < uVar2 + uVar3 &&
        ((uVar2 + uVar3 < 0x800 && (*param_3 = uVar3, *puVar4 + param_1 != 0)))))) {
      return 0;
    }
  }
  ((code*)DAT_0804cd60)("boot_config_data.c",0xde,0x300d);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




