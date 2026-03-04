/* Auto-generated: crc.c */
/* Functions: 2 */
#include "globals.h"

/* 0x0801a524 */
uint FUN_0801a524(param_1, param_2, param_3)
ushort param_1; byte * param_2; uint param_3;
{
  uint uVar1;
  
  if (param_2 != (byte *)0x0) {
    uVar1 = (uint)(ushort)~param_1;
    for (; param_3 != 0; param_3 = param_3 - 1 & 0xffff) {
      uVar1 = ((uint)*(ushort *)(&DAT_0803c120 + ((uint)*param_2 ^ uVar1 >> 8) * 2) ^ uVar1 << 8) &
              0xffff;
      param_2 = param_2 + 1;
    }
    return ~uVar1 & 0xffff;
  }
  ((code*)DAT_0804cd60)("crc.c",0x2a7,0x302f);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x0801a574 */
uint FUN_0801a574(param_1, param_2, param_3)
uint param_1; byte * param_2; uint param_3;
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  if (param_2 != (byte *)0x0) {
    uVar2 = ~param_1 & 0x3fffffff;
    for (; 7 < param_3; param_3 = param_3 - 8 & 0xffff) {
      uVar2 = *(uint *)(&DAT_0803bd20 + (((uint)*param_2 ^ uVar2 >> 0x16) & 0xff) * 4) ^ uVar2 << 8;
      param_2 = param_2 + 1;
    }
    if (param_3 != 0) {
      uVar1 = (uint)*param_2 << 0x16;
      while (bVar4 = param_3 != 0, param_3 = param_3 - 1 & 0xffff, bVar4) {
        uVar3 = uVar2 ^ uVar1;
        uVar2 = uVar2 << 1;
        if ((int)(uVar3 << 2) < 0) {
          uVar2 = uVar2 ^ 0x6030b9c7;
        }
        uVar1 = uVar1 << 1;
      }
    }
    return ~uVar2 & 0x3fffffff;
  }
  ((code*)DAT_0804cd60)("crc.c",0x250,0x302f);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




