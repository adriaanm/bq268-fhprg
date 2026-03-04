/* Auto-generated: fhprg_801c2f8.c */
/* Functions: 10 */
#include "globals.h"

/* 0x0801c2f8 */
void FUN_0801c2f8()
{
  int iVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int local_70 [21];
  
  iVar3 = 0;
  FUN_08006bdc(local_70,&DAT_08039514,0x50);
  FUN_0801c22c();
  iVar1 = FUN_0801c158();
  if (iVar1 != 0) {
    local_70[0] = 0;
    local_70[1] = 0;
    local_70[2] = 0;
    local_70[3] = 0;
    thunk_FUN_08030dac();
  }
  for (; local_70[iVar3 * 4] != 0; iVar3 = iVar3 + 1) {
    FUN_0801bf34(1,0,local_70[iVar3 * 4],0,local_70[iVar3 * 4 + 1],0,local_70[iVar3 * 4 + 2],
                 local_70[iVar3 * 4 + 3]);
  }
  FUN_0801bfac(0x60000,0,0x5000);
  FUN_08016f18(0,&DAT_87c1b420);
  FUN_0801bf34(1,0,&DAT_87c1b420,0,8,0,"Pmic PON stat","PMIC_PON.BIN");
  DAT_87c1b418 = pm_device_init_status();
  FUN_0801bf34(1,0,&DAT_87c1b418,0,4,0,"Reset Status Region","RST_STAT.BIN");
  FUN_08031d74(0x87c71190,0x800);
  FUN_0801bf34(1,0,0x87c71190,0,0x800,0,"DDR Training Data","DDR_DATA.BIN");
  puVar2 = (uint *)FUN_080160d0();
  for (uVar5 = 0; uVar5 < *puVar2; uVar5 = uVar5 + 1) {
    iVar1 = *(int *)(puVar2[1] + uVar5 * 0x10 + 8) * 0x100000;
    if (*(int *)(puVar2[1] + uVar5 * 0x10) == -0x80000000) {
      FUN_0801bf34(1,"DDRCS0.BIN",0x80000000,0,iVar1,0," DDR CS0 Memory","DDRCS0.BIN");
      for (uVar4 = 0; uVar4 < *puVar2; uVar4 = uVar4 + 1) {
        iVar3 = *(int *)(puVar2[1] + uVar4 * 0x10);
        if (iVar1 + -0x80000000 == iVar3) {
          FUN_0801bf34(1,0,iVar3,0,*(int *)(puVar2[1] + uVar4 * 0x10 + 8) << 0x14,0,
                       " DDR CS1 Memory ","DDRCS1.BIN");
        }
      }
    }
  }
  return;
}




/* 0x0801c56c */
void FUN_0801c56c(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  FUN_08017760(0x87c734c4,param_2,0,0,0x38);
  return;
}




/* 0x0801c584 */
void FUN_0801c584(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  FUN_08017760(0x87c734fc,param_2,0x38,0,DAT_0804ce10 << 6);
  return;
}




/* 0x0801c5e8 */
int FUN_0801c5e8(param_1, param_2)
undefined4 param_1; uint param_2;
{
  int iVar1;
  undefined1 auStack_20 [14];
  byte local_12;
  
  iVar1 = ((code *)*(uint*)DAT_08050d08)(param_1,&DAT_87c29afc,0x59);
  if (iVar1 == 0) {
    iVar1 = FUN_0801e52a(&DAT_87c29afc,auStack_20);
    if (iVar1 == 0) {
      if (param_2 >> 0xc != 0) {
        return -5;
      }
      if ((param_2 & 0x92) == 0) {
        local_12 = local_12 | 1;
      }
      else {
        local_12 = local_12 & 0xfe;
      }
      if ((int)(param_2 << 0x16) < 0) {
        local_12 = local_12 | 2;
      }
      else {
        local_12 = local_12 & 0xfd;
      }
      FUN_0801e502(&DAT_87c29afc,local_12);
    }
    iVar1 = FUN_08025820();
  }
  return iVar1;
}




/* 0x0801c65c */
void FUN_0801c65c(param_1)
uint param_1;
{
  undefined4 uVar1;
  
  FUN_0801d94c();
  uVar1 = FUN_0801e196();
  if (7 < param_1) {
    FUN_08015a50();
  }
  (&DAT_87c2accc)[param_1] = 0;
  FUN_08025820(uVar1);
  return;
}




/* 0x0801c692 */
void FUN_0801c692(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  undefined4 uVar1;
  
  uVar1 = FUN_08025740();
  FUN_0801e232(uVar1,param_2,param_3);
  FUN_08025820();
  return;
}




/* 0x0801c6ac */
undefined4 FUN_0801c6ac(param_1, param_2)
uint param_1; undefined4 param_2;
{
  undefined4 uVar1;
  
  if (8 < param_1) {
    return 0xffffffff;
  }
  uVar1 = FUN_0801d94c();
  FUN_0801ea34(uVar1,param_2);
  uVar1 = FUN_08025820();
  return uVar1;
}




/* 0x0801c6cc */
int FUN_0801c6cc(param_1, param_2)
char * param_1; int param_2;
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_20 [2];
  undefined2 local_18;
  undefined2 local_16;
  undefined2 local_14;
  undefined1 local_12;
  
  if ((((*param_1 == '\0') || (param_1[1] != ':')) || (param_1[2] != '/')) || (param_1[3] != '\0'))
  {
    iVar1 = ((code *)*(uint*)DAT_08050d08)(param_1,&DAT_87c29afc,0x59);
    if (iVar1 != 0) {
      return iVar1;
    }
    iVar1 = FUN_0801e52a(&DAT_87c29afc,local_20);
    if (iVar1 != 0) {
      iVar1 = FUN_08025820();
      return iVar1;
    }
    FUN_08027ec2(param_2 + 8,local_12);
    *(undefined4 *)(param_2 + 0xc) = local_20[0];
    uVar2 = FUN_08020d10(local_16,local_18);
    *(undefined4 *)(param_2 + 0x20) = uVar2;
    *(undefined4 *)(param_2 + 0x1c) = uVar2;
    uVar2 = FUN_08020d10(0,local_14);
  }
  else {
    *(ushort *)(param_2 + 8) = *(ushort *)(param_2 + 8) & 0xfff | 0x4000;
    uVar2 = 0;
    *(undefined4 *)(param_2 + 0xc) = 0;
    *(undefined4 *)(param_2 + 0x20) = 0;
    *(undefined4 *)(param_2 + 0x1c) = 0;
  }
  *(undefined4 *)(param_2 + 0x18) = uVar2;
  return 0;
}




/* 0x0801c758 */
void FUN_0801c758(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; int param_3;
{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = FUN_0801d94c();
  if (param_3 << 0x15 < 0) {
    param_2 = 0;
    uVar2 = 2;
  }
  else {
    uVar2 = 0;
  }
  FUN_0801e2be(uVar1,param_2,uVar2);
  FUN_08025820();
  return;
}




/* 0x0801c840 */
undefined4 * FUN_0801c840(param_1)
char * param_1;
{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  uVar1 = FUN_08006906();
  if ((((*param_1 != '\0') && (param_1[1] == ':')) && (param_1[2] == '/')) && (2 < uVar1)) {
    for (; param_1[uVar1 - 1] == '/'; uVar1 = uVar1 - 1) {
    }
    if (uVar1 < 0x10d) {
      iVar2 = 0;
      do {
        if ((&DAT_87c2a570)[iVar2 * 0x1d5] != 0) {
          puVar3 = &DAT_87c29e24 + iVar2 * 0x1d5;
          (&DAT_87c2a570)[iVar2 * 0x1d5] = 0;
          goto LAB_0801c8a2;
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < 2);
      puVar3 = (undefined4 *)0x0;
LAB_0801c8a2:
      if (puVar3 != (undefined4 *)0x0) {
        *puVar3 = 0;
        FUN_08020e68(puVar3 + 0x18e,0x111,param_1,uVar1);
        FUN_080382c2((int)puVar3 + uVar1 + 0x638,&DAT_0801c8fc,-(uVar1 - 0x111));
        if (((*param_1 != '\0') && (param_1[1] == ':')) &&
           ((param_1[2] == '/' && (param_1[3] == '\0')))) {
          puVar3[0x1d4] = 0;
          return puVar3;
        }
        puVar3[0x1d4] = 2;
        return puVar3;
      }
    }
  }
  return (undefined4 *)0x0;
}




