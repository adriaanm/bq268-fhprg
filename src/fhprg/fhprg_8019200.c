/* Auto-generated: fhprg_8019200.c */
/* Functions: 10 */
#include "globals.h"

/* 0x08019200 */
void FUN_08019200()
{
  int *piVar1;
  
  if ((DAT_0804cea0 != (int *)0x0) && (*(uint*)DAT_0804cea0 != -0x3e0724c0)) {
    FUN_08007f08(DAT_0804cea0,0xffffffff,200);
    piVar1 = DAT_0804cea0;
    *(uint*)DAT_0804cea0 = -0x3e0724c0;
    piVar1[1] = 1;
  }
  return;
}




/* 0x080192b8 */
void thunk_FUN_080192b8()
{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0801688c();
  if (iVar1 != 0) {
    uVar2 = FUN_080161b0();
    *(undefined4 *)(iVar1 + 0x14) = uVar2;
    *(undefined4 *)(iVar1 + 0x18) = 1;
  }
  return;
}




/* 0x080192b8 */
void FUN_080192b8()
{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0801688c();
  if (iVar1 != 0) {
    uVar2 = FUN_080161b0();
    *(undefined4 *)(iVar1 + 0x14) = uVar2;
    *(undefined4 *)(iVar1 + 0x18) = 1;
  }
  return;
}




/* 0x080192d0 */
void FUN_080192d0()
{
  DAT_0804cd10 = FUN_08019320();
  return;
}




/* 0x080192e0 */
void FUN_080192e0(param_1)
int param_1;
{
  int iVar1;
  
  iVar1 = FUN_08019320();
  DAT_0804cd14 = (iVar1 - DAT_0804cd10) * 0x1e + ((uint)(iVar1 - DAT_0804cd10) >> 1) + DAT_0804cd14;
  DAT_0804cd18 = DAT_0804cd18 + param_1;
  DAT_0804cd1c = DAT_0804cd1c + param_1;
  return;
}




/* 0x08019314 */
undefined4 FUN_08019314()
{
  return DAT_0804cd1c;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08019320 */
undefined4 FUN_08019320()
{
  do {
  } while (false);
  return 0;
}




/* 0x08019330 */
void FUN_08019330()
{
  int iVar1;
  uint uVar2;
  undefined1 auStack_70 [96];
  int local_10;
  
  iVar1 = DAT_0804cd58;
  local_10 = DAT_0804cd58;
  uVar2 = 0;
  if ((DAT_0804cd14 != 0) && (DAT_0804cd18 != 0)) {
    uVar2 = ((DAT_0804cd18 / DAT_0804cd14) * 1000000) / 1000;
  }
  snprintf_buf(auStack_70,0x60,"Throughput, %d KB/s  (%d Bytes,  %d us)",uVar2,DAT_0804cd18,
               DAT_0804cd14);
  FUN_08016adc(auStack_70,0xffffffff,0x53);
  if (local_10 != iVar1) {
    FUN_08010960();
    return;
  }
  return;
}




/* 0x080193b8 */
void FUN_080193b8()
{
  DAT_0804cd1c = 0;
  return;
}




/* 0x080193c4 */
int FUN_080193c4()
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar1 = FUN_0801688c();
  if ((iVar1 != 0) && (*(int *)(iVar1 + 0x18) == 1)) {
    *(undefined4 *)(iVar1 + 0x18) = 0;
    uVar2 = FUN_080161b0();
    uVar3 = *(uint *)(iVar1 + 0x14);
    if ((uVar3 < 0x8421214) && ((uVar2 < 0x8421214 && (uVar3 <= uVar2)))) {
      iVar4 = (uVar2 - uVar3) * 0x1e + (uVar2 - uVar3 >> 1);
    }
    else {
      iVar4 = -1;
    }
  }
  return iVar4;
}




