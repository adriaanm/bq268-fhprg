/* Auto-generated: fhprg_8017aec.c */
/* Functions: 38 */
#include "globals.h"

/* 0x08017aec */
undefined4 FUN_08017aec(param_1)
int param_1;
{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((*(uint **)(param_1 + 0xc) != (uint *)0x0) &&
     ((**(uint **)(param_1 + 0xc) & *(uint *)(param_1 + 0x10)) != 0)) {
    uVar1 = 1;
  }
  return uVar1;
}




/* 0x08017b04 */
undefined4 FUN_08017b04(param_1, param_2)
undefined4 param_1; uint param_2;
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  iVar1 = FUN_08017a64();
  if (iVar1 == 0) {
    uVar3 = 0x3059;
  }
  else if (((DAT_0804ceb0 == 1) && (iVar2 = FUN_08017aec(iVar1), iVar2 != 0)) &&
          (*(uint *)(iVar1 + 0x2c) < param_2)) {
    *(uint *)(iVar1 + 0x2c) = param_2;
  }
  return uVar3;
}




/* 0x08017b38 */
undefined4 FUN_08017b38(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  
  if ((((param_1 == 1) && (-1 < param_2 << 0xb)) &&
      (uVar1 = (uint)(param_2 << 8) >> 0x1d, uVar1 != 3)) &&
     (((uint)(param_2 << 5) >> 0x1d != 2 && (uVar1 != 4)))) {
    return 1;
  }
  return 0;
}




/* 0x08017b5c */
undefined4 FUN_08017b5c(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  int extraout_r2;
  uint uVar4;
  uint uVar5;
  
  uVar5 = 0;
  while( true ) {
    if (*(ushort *)(param_1 + 0x2c) <= uVar5) {
      return 0;
    }
    puVar3 = (undefined4 *)(param_2 + 0x14 + uVar5 * 0x20);
    iVar1 = FUN_08017b38(*puVar3,puVar3[6]);
    if ((((iVar1 != 0) && (*(int *)(extraout_r2 + 0x14) != 0)) &&
        (uVar4 = *(uint *)(extraout_r2 + 0x10), uVar4 != 0)) &&
       ((((uVar2 = *(uint *)(extraout_r2 + 0xc), uVar4 < ~uVar2 &&
          (uVar2 <= *(uint *)(param_1 + 0x18))) && (*(uint *)(param_1 + 0x18) < uVar2 + uVar4)) ||
        (((uVar2 = *(uint *)(extraout_r2 + 8), uVar4 < ~uVar2 &&
          (uVar2 <= *(uint *)(param_1 + 0x18))) && (*(uint *)(param_1 + 0x18) < uVar2 + uVar4))))))
    break;
    uVar5 = uVar5 + 1;
  }
  return 1;
}




/* 0x08017bbc */
int FUN_08017bbc(param_1)
undefined4 param_1;
{
  int iVar1;
  
  DAT_0804cd88 = param_1;
  iVar1 = FUN_08018214();
  if (iVar1 != 0) {
    sahara_send_hello();
    FUN_0801847c();
    DAT_0804cdd4 = 0;
    DAT_0804cd7d = 0;
    DAT_0804cd7e = 0;
  }
  return iVar1;
}




/* 0x08017be4 */
void FUN_08017be4()
{
  (**(code **)(DAT_0804cdb0 + 8))();
  if ((((DAT_0804cd85 != '\x02') && (DAT_0804cd85 != '\x01')) && (DAT_0804cd85 != '\n')) &&
     (DAT_0804cd85 != '\v')) {
    DAT_0804cdb0 = 0;
  }
  DAT_0804cd85 = 0;
  DAT_0804cd79 = 1;
  return;
}




/* 0x08017c10 */
undefined4 FUN_08017c10()
{
  return 1;
}




/* 0x08017c14 */
undefined4 FUN_08017c14()
{
  return *(undefined4 *)(DAT_0804cd94 + 0x44);
}




/* 0x08017c20 */
void FUN_08017c20(param_1, param_2)
int param_1; int param_2;
{
  undefined4 uVar1;
  int iVar2;
  int local_10;
  
  local_10 = 0;
  if ((param_2 == 0xc) && (*(int *)(param_1 + 4) == 0xc)) {
    if (*(int *)(param_1 + 8) == DAT_0804cd9c) {
      FUN_080183f0(DAT_0804cda4,DAT_0804cda0,0);
      iVar2 = FUN_080181dc(DAT_0804cda4,DAT_0804cda0,&local_10);
      if (local_10 == 6) {
        uVar1 = 0x17;
      }
      else if (local_10 == 0) {
        if (iVar2 == DAT_0804cda0) {
          DAT_0804cd85 = 0xb;
          return;
        }
        uVar1 = 10;
      }
      else {
        uVar1 = 0xc;
      }
    }
    else {
      uVar1 = 0x20;
    }
  }
  else {
    uVar1 = 5;
  }
  FUN_08017d48(uVar1);
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08017c80 */
void FUN_08017c80()
{
  int iVar1;
  undefined4 uVar2;
  int local_10;
  
  local_10 = 0;
  _DAT_87c72878 = 0xe;
  _DAT_87c7287c = 0x10;
  _DAT_87c72880 = DAT_0804cd9c;
  _DAT_87c72884 = DAT_0804cda0;
  FUN_080183f0(&DAT_87c72878,0x10,0);
  iVar1 = FUN_080181dc(&DAT_87c72878,_DAT_87c7287c,&local_10);
  if (local_10 == 6) {
    uVar2 = 0x17;
  }
  else if (local_10 == 0) {
    if (_DAT_87c7287c == iVar1) {
      if (DAT_0804cda0 == 0) {
        return;
      }
      DAT_0804cd85 = 0xc;
      return;
    }
    uVar2 = 10;
  }
  else {
    uVar2 = 0xc;
  }
  FUN_08017d48(uVar2);
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08017ce0 */
void FUN_08017ce0()
{
  int iVar1;
  int local_10;
  
  local_10 = 0;
  _DAT_87c72878 = 6;
  _DAT_87c7287c = 0xc;
  _DAT_87c72880 = DAT_0804cd98;
  do {
    FUN_080183f0(&DAT_87c72878,_DAT_87c7287c,0);
    iVar1 = FUN_080181dc(&DAT_87c72878,_DAT_87c7287c,&local_10);
    if (local_10 == 6) {
      DAT_0804cd85 = 2;
                    /* WARNING: Subroutine does not return */
      FUN_08018be4();
    }
  } while ((local_10 != 0) || (_DAT_87c7287c != iVar1));
  if ((DAT_0804cd98 == 1) || (*(uint*)DAT_0804cd8c == 7)) {
    (**(code **)(DAT_0804cdb0 + 0x74))();
    FUN_08017be4();
  }
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08017d48 */
void FUN_08017d48(param_1)
int param_1;
{
  int iVar1;
  int iVar2;
  int local_18;
  
  iVar2 = 0;
  local_18 = 0;
  _DAT_87c72878 = 4;
  _DAT_87c7287c = 0x10;
  _DAT_87c72880 = *(uint*)DAT_0804cd8c;
  _DAT_87c72884 = param_1;
  *(int *)(DAT_0804cd88 + 4) = param_1;
  FUN_080183f0(&DAT_87c72878,_DAT_87c7287c,0);
  iVar1 = FUN_080181dc(&DAT_87c72878,_DAT_87c7287c,&local_18);
  if (local_18 == 6) {
    iVar2 = 0x17;
  }
  else if (local_18 == 0) {
    if (_DAT_87c7287c != iVar1) {
      iVar2 = 10;
    }
  }
  else {
    iVar2 = 0xc;
  }
  if (param_1 != 0 || iVar2 != 0) {
    DAT_0804cd85 = 2;
  }
  if (iVar2 != 0) {
    *(int *)(DAT_0804cd88 + 4) = iVar2;
                    /* WARNING: Subroutine does not return */
    FUN_08018be4();
  }
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08017db8 */
void sahara_send_hello()
{
  int iVar1;
  int local_18;
  
  local_18 = 0;
  _DAT_87c72878 = 1;
  _DAT_87c7287c = 0x30;
  _DAT_87c72880 = DAT_0804cdb4;
  _DAT_87c72884 = DAT_0804cdb8;
  _DAT_87c72888 = 0x400;
  _DAT_87c7288c = DAT_0804cd98;
  _DAT_87c72890 = 0;
  _DAT_87c72894 = 0;
  _DAT_87c72898 = 0;
  _DAT_87c7289c = 0;
  _DAT_87c728a0 = 0;
  _DAT_87c728a4 = 0;
  do {
    while( true ) {
      do {
        FUN_080183f0(&DAT_87c72878,_DAT_87c7287c,0);
        iVar1 = FUN_080181dc(&DAT_87c72878,_DAT_87c7287c,&local_18);
      } while (local_18 == 6);
      if (local_18 != 0xb) break;
      (**(code **)(DAT_0804cdb0 + 4))();
    }
  } while ((local_18 != 0) || (_DAT_87c7287c != iVar1));
  DAT_0804cd85 = 1;
  boot_log_message("Sahara: Hello pkt sent");
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x08017e44 */
void FUN_08017e44(param_1, param_2, param_3, param_4)
int param_1; int param_2; undefined4 param_3; int param_4;
{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int local_18;
  
  local_18 = param_4;
  if (param_2 == 0x30) {
    if (*(int *)(param_1 + 4) != 0x30) goto LAB_08017e4e;
  }
  else if ((param_2 != 0x14) || (*(int *)(param_1 + 8) != 1)) {
LAB_08017e4e:
    iVar2 = 5;
    goto LAB_08017ebe;
  }
  iVar2 = *(int *)(param_1 + 0x10);
  if (iVar2 == 0) {
    uVar3 = *(uint *)(param_1 + 8);
    if (uVar3 < *(uint *)(param_1 + 0xc)) {
      iVar2 = 4;
    }
    else if ((DAT_0804cdb4 < uVar3) || (uVar3 < DAT_0804cdb8)) {
      iVar2 = 2;
    }
    else {
      uVar3 = DAT_0804cd98;
      if ((param_2 == 0x14) || (uVar3 = *(uint *)(param_1 + 0x14), *(uint *)(param_1 + 0x14) < 4)) {
        DAT_0804cd98 = uVar3;
        if (DAT_0804cd98 != 2) {
          if (DAT_0804cd98 != 3) {
            FUN_080186fc();
            return;
          }
          local_18 = 0;
          _DAT_87c72878 = 0xb;
          _DAT_87c7287c = 8;
          FUN_080183f0(&DAT_87c72878,8,0);
          iVar2 = FUN_080181dc(&DAT_87c72878,_DAT_87c7287c,&local_18);
          if (local_18 == 6) {
            uVar1 = 0x17;
          }
          else if (local_18 == 0) {
            if (_DAT_87c7287c == iVar2) {
              DAT_0804cd85 = 0xb;
              return;
            }
            uVar1 = 10;
          }
          else {
            uVar1 = 0xc;
          }
          FUN_08017d48(uVar1);
          return;
        }
        if ((DAT_0804cd7a != '\0') && (iVar2 = ((code *)*(uint*)DAT_0804cdac)(), iVar2 != 0)) {
          _DAT_87c72878 = 9;
          ((code *)((uint*)&DAT_0804cdac)[1])();
          _DAT_87c7287c = 0x10;
          _DAT_87c72880 = ((code *)((uint*)&DAT_0804cdac)[2])();
          _DAT_87c72884 = ((code *)((uint*)&DAT_0804cdac)[3])();
          FUN_080183f0(&DAT_87c72878,_DAT_87c7287c,0);
          iVar2 = FUN_080181dc(&DAT_87c72878,_DAT_87c7287c,&stack0xfffffff0);
          if (false) {
            uVar1 = 0x17;
          }
          else if (true) {
            uVar1 = 10;
            if (_DAT_87c7287c == iVar2) {
              DAT_0804cd85 = 10;
              return;
            }
          }
          else {
            uVar1 = 0xc;
          }
          FUN_08017d48(uVar1);
          return;
        }
        iVar2 = 0x1b;
      }
      else {
        iVar2 = 0x18;
      }
    }
  }
LAB_08017ebe:
  FUN_08017d48(iVar2);
  return;
}




/* 0x08017f14 */
void FUN_08017f14(param_1, param_2)
int param_1; int param_2;
{
  undefined4 uVar1;
  int iVar2;
  int local_18;
  
  local_18 = 0;
  if ((param_2 == 0x18) && (*(int *)(param_1 + 4) == 0x18)) {
    iVar2 = (**(code **)(DAT_0804cdac + 0x10))
                      (*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc),
                       *(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x14));
    if ((iVar2 == 0) ||
       (iVar2 = (**(code **)(DAT_0804cdac + 0x14))
                          (*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc),
                           *(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x14)),
       iVar2 != 0)) {
      uVar1 = 0x19;
    }
    else {
      iVar2 = FUN_080181dc(*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0x10),&local_18);
      if (local_18 == 6) {
        uVar1 = 0x17;
      }
      else if (local_18 == 0) {
        if (iVar2 == *(int *)(param_1 + 0x10) && *(int *)(param_1 + 0x14) == 0) {
          return;
        }
        uVar1 = 10;
      }
      else {
        uVar1 = 0xc;
      }
    }
  }
  else {
    uVar1 = 5;
  }
  FUN_08017d48(uVar1);
  return;
}




/* 0x08017ff0 */
void FUN_08017ff0(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int local_20;
  
  iVar4 = 0;
  local_20 = 0;
  if ((param_2 == 0x10) && (*(int *)(param_1 + 4) == 0x10)) {
    iVar1 = (**(code **)(DAT_0804cdac + 0x10))
                      (*(undefined4 *)(param_1 + 8),0,*(undefined4 *)(param_1 + 0xc));
    if (iVar1 == 0) {
      iVar4 = 0x19;
    }
    else {
      iVar1 = (**(code **)(DAT_0804cdac + 0x14))
                        (*(undefined4 *)(param_1 + 8),0,*(undefined4 *)(param_1 + 0xc));
      if (iVar1 == 0) {
        iVar4 = FUN_080181dc(*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc),&local_20);
        if (local_20 == 6) {
LAB_0801807e:
          iVar4 = 0x17;
        }
        else if (local_20 == 0) {
          if (*(int *)(param_1 + 0xc) == iVar4) {
            return;
          }
LAB_08018086:
          iVar4 = 10;
        }
        else {
LAB_0801807a:
          iVar4 = 0xc;
        }
      }
      else {
        iVar1 = *(int *)(param_1 + 8);
        uVar5 = *(uint *)(param_1 + 0xc);
        do {
          if (uVar5 == 0) {
            return;
          }
          uVar3 = 0x1000;
          if (uVar5 < 0x1001) {
            uVar3 = uVar5;
          }
          DAT_0804cda8 = (**(code **)(DAT_0804cdac + 0x18))(iVar1,uVar3);
          if (DAT_0804cda8 == 0) {
            iVar4 = 0x19;
            FUN_08017d48(0x19);
          }
          uVar2 = FUN_080181dc(DAT_0804cda8,uVar3,&local_20);
          if (local_20 == 6) goto LAB_0801807e;
          if (local_20 != 0) goto LAB_0801807a;
          if (uVar2 != uVar3) goto LAB_08018086;
          uVar5 = uVar5 - uVar3;
          iVar1 = iVar1 + uVar3;
        } while (iVar4 == 0);
      }
    }
  }
  else {
    iVar4 = 5;
  }
  FUN_08017d48(iVar4);
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x080180c0 */
void FUN_080180c0(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 param_3;
{
  int iVar1;
  undefined4 uVar2;
  int local_10;
  
  local_10 = 0;
  _DAT_87c72878 = 3;
  _DAT_87c7287c = 0x14;
  _DAT_87c72880 = param_1;
  _DAT_87c72884 = param_2;
  _DAT_87c72888 = param_3;
  FUN_080183f0(&DAT_87c72878,0x14,0);
  iVar1 = FUN_080181dc(&DAT_87c72878,_DAT_87c7287c,&local_10);
  if (local_10 == 6) {
    uVar2 = 0x17;
  }
  else if (local_10 == 0) {
    if (_DAT_87c7287c == iVar1) {
      return;
    }
    uVar2 = 10;
  }
  else {
    uVar2 = 0xc;
  }
  FUN_08017d48(uVar2);
  return;
}




/* 0x08018110 */
int FUN_08018110(param_1, param_2, param_3, param_4, param_5)
int param_1; uint param_2; uint param_3; undefined4 * param_4; undefined4 param_5;
{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = (**(code **)(DAT_0804cdb0 + 0x18))();
  if (param_3 < param_2) {
LAB_08018152:
    iVar2 = 0;
    *param_4 = 8;
  }
  else {
    iVar2 = (**(code **)(DAT_0804cdb0 + 0x68))();
    if (iVar2 == 0) {
      iVar2 = param_2 - uVar1 * (param_2 / uVar1);
      if (iVar2 != 0) {
        param_2 = param_2 + (uVar1 - iVar2);
      }
      if (param_3 < param_2) goto LAB_08018152;
    }
    DAT_0804cdc4 = 0;
    DAT_0804cdc8 = 0;
    DAT_0804cd7b = '\0';
    (**(code **)(DAT_0804cdb0 + 0x10))(param_1,param_2,&LAB_08018bf8,param_4,param_5);
    if (DAT_0804cd81 != '\0') {
      (**(code **)(DAT_0804cdd4 + 8))(DAT_0804cdd8,DAT_0804cddc);
      DAT_0804cd81 = '\0';
    }
    while (iVar2 = DAT_0804cdc4, DAT_0804cd7b == '\0') {
      (**(code **)(DAT_0804cdb0 + 0xc))();
    }
    *param_4 = DAT_0804cdc8;
    if (param_1 != -0x2153) {
      FUN_08018c94(iVar2,0);
    }
    iVar3 = (**(code **)(DAT_0804cdb0 + 0x68))();
    if ((iVar3 == 1) && (DAT_0804cd84 == '\x01')) {
      DAT_0804cde4 = DAT_0804cde4 - iVar2;
    }
  }
  return iVar2;
}




/* 0x080181dc */
undefined4 FUN_080181dc(param_1, param_2, param_3)
undefined4 param_1; undefined4 param_2; undefined4 * param_3;
{
  undefined4 uVar1;
  
  DAT_0804cdcc = 0;
  DAT_0804cdd0 = 0;
  DAT_0804cd7c = '\0';
  (**(code **)(DAT_0804cdb0 + 0x14))(param_1,param_2,&LAB_08018cc8,param_3);
  while (uVar1 = DAT_0804cdcc, DAT_0804cd7c == '\0') {
    (**(code **)(DAT_0804cdb0 + 0xc))();
  }
  *param_3 = DAT_0804cdd0;
  return uVar1;
}




/* 0x08018214 */
int FUN_08018214()
{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  code *pcVar6;
  int iVar7;
  
  iVar7 = 1;
  if (DAT_0804cd88 == 0) {
    return 0;
  }
  iVar4 = *(int *)(DAT_0804cd88 + 8);
  if ((((((((iVar4 == 0) || (iVar1 = *(int *)(DAT_0804cd88 + 0x10), iVar1 == 0)) ||
          (DAT_0804cd8c = iVar4, DAT_0804cdb0 = iVar1, *(int *)(iVar4 + 8) == 0)) ||
         ((*(int *)(iVar1 + 4) == 0 || (*(int *)(iVar1 + 8) == 0)))) || (*(int *)(iVar1 + 0xc) == 0)
        ) || (((*(int *)(iVar1 + 0x10) == 0 || (*(int *)(iVar1 + 0x14) == 0)) ||
              ((*(int *)(iVar1 + 0x18) == 0 ||
               (((*(int *)(iVar1 + 0x1c) == 0 || (*(int *)(iVar1 + 0x20) == 0)) ||
                (*(int *)(iVar1 + 0x24) == 0)))))))) ||
      (((*(int *)(iVar1 + 0x28) == 0 || (*(code **)(iVar1 + 0x2c) == (code *)0x0)) ||
       ((*(int *)(iVar1 + 0x30) == 0 ||
        (((((*(int *)(iVar1 + 0x34) == 0 || (*(int *)(iVar1 + 0x38) == 0)) ||
           ((*(int *)(iVar1 + 0x3c) == 0 ||
            (((*(int *)(iVar1 + 0x40) == 0 || (*(int *)(iVar1 + 0x44) == 0)) ||
             (*(int *)(iVar1 + 0x48) == 0)))))) ||
          ((*(int *)(iVar1 + 0x4c) == 0 || (*(int *)(iVar1 + 0x50) == 0)))) ||
         (*(int *)(iVar1 + 100) == 0)))))))) ||
     (((*(int *)(iVar1 + 0x6c) == 0 || (*(int *)(iVar1 + 0x70) == 0)) ||
      (*(int *)(iVar1 + 0x74) == 0)))) goto LAB_0801838e;
  iVar1 = (**(code **)(iVar1 + 0x2c))();
  iVar4 = DAT_0804cd8c;
  *(char *)(DAT_0804cd8c + 0xd) = (char)iVar1;
  DAT_0804cdd4 = *(int *)(DAT_0804cd88 + 0x14);
  if (((DAT_0804cdd4 == 0) || (*(int *)(DAT_0804cdd4 + 0x1c) == 0)) &&
     (*(int *)(DAT_0804cd88 + 0xc) != 2)) {
LAB_0801837e:
    iVar7 = 0;
  }
  else {
    if (iVar1 != 0) {
      if (*(int *)(iVar4 + 4) == 1) {
        DAT_0804cd7d = 1;
      }
      else if (*(int *)(iVar4 + 4) == 0) {
        DAT_0804cd7e = 1;
      }
    }
    DAT_0804cdac = *(int **)(DAT_0804cd88 + 0x18);
    if (DAT_0804cdac == (int *)0x0) {
      DAT_0804cd7a = 0;
    }
    else {
      if (((*(uint*)DAT_0804cdac == 0) || (((uint*)&DAT_0804cdac)[1] == 0)) ||
         (((((uint*)&DAT_0804cdac)[4] == 0 || ((((uint*)&DAT_0804cdac)[2] == 0 || (((uint*)&DAT_0804cdac)[3] == 0)))) ||
          ((((uint*)&DAT_0804cdac)[5] == 0 || (((uint*)&DAT_0804cdac)[6] == 0)))))) goto LAB_0801837e;
      DAT_0804cd7a = 1;
    }
    if (*(int *)(iVar4 + 4) != 0) {
      if (*(int *)(iVar4 + 4) == 1) {
        puVar2 = *(undefined4 **)(iVar4 + 8);
        DAT_0804cd94 = puVar2;
        if (puVar2[0xe] != 0) {
          *puVar2 = 0;
          (**(code **)(DAT_0804cdb0 + 0x34))(puVar2 + 1,0,0x34);
          puVar2 = DAT_0804cd94;
          ((uint*)&DAT_0804cd94)[0xf] = 0;
          (**(code **)(DAT_0804cdb0 + 0x34))(puVar2 + 0x10,0,4);
          (**(code **)(DAT_0804cdb0 + 0x34))(DAT_0804cd94 + 0x11,0,4);
          uVar5 = 0xc94;
          uVar3 = ((uint*)&DAT_0804cd94)[0xe];
          pcVar6 = *(code **)(DAT_0804cdb0 + 0x34);
          goto LAB_08018364;
        }
      }
      else if (*(int *)(DAT_0804cd88 + 0xc) == 2) goto LAB_08018368;
      goto LAB_0801837e;
    }
    puVar2 = *(undefined4 **)(iVar4 + 8);
    DAT_0804cd90 = puVar2;
    *puVar2 = 0;
    if (puVar2[1] == 0) goto LAB_0801837e;
    uVar5 = (**(code **)(DAT_0804cdb0 + 0x38))();
    pcVar6 = *(code **)(DAT_0804cdb0 + 0x34);
    uVar3 = ((uint*)&DAT_0804cd90)[1];
LAB_08018364:
    (*pcVar6)(uVar3,0,uVar5);
LAB_08018368:
    iVar4 = DAT_0804cd88;
    *(undefined1 *)(*(int *)(DAT_0804cd88 + 8) + 0xc) = 0;
    DAT_0804cd98 = *(undefined4 *)(iVar4 + 0xc);
    DAT_0804cd85 = 0;
    DAT_0804cd79 = 0;
    iVar4 = (**(code **)(DAT_0804cdb0 + 4))();
    if (iVar4 != 0) goto LAB_0801837e;
  }
  if (DAT_0804cd88 == 0) {
    return iVar7;
  }
  if (iVar7 != 0) {
    *(undefined4 *)(DAT_0804cd88 + 4) = 0;
    return iVar7;
  }
LAB_0801838e:
  *(undefined4 *)(DAT_0804cd88 + 4) = 0x24;
  return 0;
}




/* 0x0801839c */
undefined4 FUN_0801839c(param_1, param_2)
uint param_1; uint param_2;
{
  uint in_stack_00000018 = 0;
  ushort in_stack_0000001c;
  
  if (((((((param_1 & 0xff) == 0x7f) && ((param_1 << 0x10) >> 0x18 == 0x45)) &&
        ((param_1 << 8) >> 0x18 == 0x4c)) && ((param_1 >> 0x18 == 0x46 && ((param_2 & 0xff) == 1))))
      && (((param_2 << 8) >> 0x18 == 1 &&
          (((in_stack_00000018 & 0xffff) == 0x34 && (in_stack_00000018 >> 0x10 == 0x20)))))) &&
     ((in_stack_0000001c != 0 && (in_stack_0000001c < 0x65)))) {
    return 1;
  }
  return 0;
}




/* 0x080183f0 */
void FUN_080183f0(param_1, param_2, param_3)
byte * param_1; undefined4 param_2; undefined4 param_3;
{
  int iVar1;
  
  if (99 < DAT_0804cdbc) {
    DAT_0804cdbc = 0;
  }
  *(uint *)(DAT_0804cdbc * 0x14 + -0x7838d388) = (uint)*param_1;
  iVar1 = DAT_0804cdbc * 0x14;
  *(undefined1 *)(iVar1 + -0x7838d384) = DAT_0804cd85;
  *(undefined4 *)(iVar1 + -0x7838d380) = param_2;
  *(undefined4 *)(iVar1 + -0x7838d37c) = param_3;
  *(int *)(iVar1 + -0x7838d378) = DAT_0804cdc0;
  DAT_0804cdbc = DAT_0804cdbc + 1;
  DAT_0804cdc0 = DAT_0804cdc0 + 1;
  return;
}




/* 0x0801842c */
void FUN_0801842c(param_1, param_2)
undefined4 param_1; undefined4 param_2;
{
  int iVar1;
  
  if (99 < DAT_0804cdbc) {
    DAT_0804cdbc = 0;
  }
  *(undefined4 *)(DAT_0804cdbc * 0x14 + -0x7838d388) = 0;
  iVar1 = DAT_0804cdbc * 0x14;
  *(undefined1 *)(iVar1 + -0x7838d384) = DAT_0804cd85;
  *(undefined4 *)(iVar1 + -0x7838d380) = param_1;
  *(undefined4 *)(iVar1 + -0x7838d37c) = param_2;
  *(int *)(iVar1 + -0x7838d378) = DAT_0804cdc0;
  DAT_0804cdbc = DAT_0804cdbc + 1;
  DAT_0804cdc0 = DAT_0804cdc0 + 1;
  return;
}




/* 0x08018468 */
undefined4 FUN_08018468()
{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (DAT_0804cd82 == '\x01') {
    uVar1 = 0x12;
  }
  return uVar1;
}



/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* 0x0801847c */
void FUN_0801847c()
{
  int iVar1;
  int local_20 [2];
  
  local_20[1] = 0;
  do {
    if (DAT_0804cd79 != '\0') {
      DAT_0804cd85 = 0;
      return;
    }
    local_20[0] = 0;
    iVar1 = FUN_08018110(&DAT_87c72878,0x400,0x400,local_20 + 1);
    if (iVar1 == 0) goto LAB_080185d0;
    FUN_080183f0(&DAT_87c72878,iVar1,1);
    if (false) {
switchD_080184b6_caseD_3:
      if (false) goto LAB_080185d0;
LAB_080185d8:
      if (DAT_0804cd85 != '\x01') goto LAB_080185de;
      goto LAB_080185e2;
    }
    switch(_DAT_87c72878 & 0xff) {
    case 2:
      if (DAT_0804cd85 == '\x01') {
        FUN_08017e44(&DAT_87c72878,iVar1);
        break;
      }
LAB_080185de:
      iVar1 = 1;
      goto LAB_080185ac;
    default:
      goto switchD_080184b6_caseD_3;
    case 5:
      if (DAT_0804cd85 == '\x03') {
        if ((iVar1 != 8) || (_DAT_87c7287c != 8)) goto LAB_080184ec;
        FUN_08017ce0();
        DAT_0804cd79 = '\x01';
        break;
      }
      goto LAB_080185d8;
    case 7:
      if ((((DAT_0804cd85 != '\x01') && (DAT_0804cd85 != '\x02')) && (DAT_0804cd85 != '\n')) &&
         (DAT_0804cd85 != '\v')) goto LAB_080185de;
      if ((iVar1 == 8) && (_DAT_87c7287c == 8)) {
        local_20[0] = 0;
        _DAT_87c72878 = 8;
        FUN_080183f0(&DAT_87c72878,8,0);
        FUN_080181dc(&DAT_87c72878,_DAT_87c7287c,local_20);
                    /* WARNING: Subroutine does not return */
        FUN_08018be4();
      }
LAB_080184ec:
      iVar1 = 5;
      goto LAB_080185ac;
    case 10:
      if (DAT_0804cd85 != '\n') goto LAB_080185d8;
      FUN_08017ff0(&DAT_87c72878,iVar1);
      break;
    case 0xc:
      if ((DAT_0804cd85 != '\v') && (DAT_0804cd85 != '\n')) goto LAB_080185d8;
      if ((iVar1 != 0xc) || (_DAT_87c7287c != 0xc)) goto LAB_080184ec;
      if (_DAT_87c72880 < 4) {
        DAT_0804cd98 = _DAT_87c72880;
      }
      DAT_0804cd85 = '\x01';
      break;
    case 0xd:
      if (DAT_0804cd85 != '\v') goto LAB_080185d8;
      local_20[0] = 0;
      if ((iVar1 == 0xc) && (_DAT_87c7287c == 0xc)) {
        DAT_0804cda4 = (**(code **)(DAT_0804cdb0 + 0x24))(_DAT_87c72880,&DAT_0804cda0,local_20);
        DAT_0804cd9c = _DAT_87c72880;
        iVar1 = local_20[0];
        if (local_20[0] == 0) {
          FUN_08017c80();
          break;
        }
      }
      else {
        local_20[0] = 5;
        iVar1 = 5;
      }
LAB_080185ac:
      FUN_08017d48(iVar1);
      break;
    case 0xf:
      if (DAT_0804cd85 != '\f') goto LAB_080185d8;
      FUN_08017c20(&DAT_87c72878,iVar1);
      break;
    case 0x11:
      if (DAT_0804cd85 != '\n') goto LAB_080185d8;
      FUN_08017f14(&DAT_87c72878,iVar1);
    }
LAB_080185d0:
    if (DAT_0804cd85 == '\x01') {
LAB_080185e2:
      sahara_send_hello();
    }
  } while( true );
}




/* 0x080185fc */
int FUN_080185fc(param_1, param_2, param_3, param_4)
int param_1; uint param_2; uint param_3; int param_4;
{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int local_3c [2];
  int local_34;
  uint local_30;
  uint uStack_2c;
  int iStack_28;
  
  local_3c[0] = 0;
  local_34 = param_1;
  local_30 = param_2;
  uStack_2c = param_3;
  iStack_28 = param_4;
  FUN_080192d0();
  uVar7 = local_30;
  if (param_3 < local_30) {
LAB_080186d8:
    iVar1 = 8;
  }
  else {
    iVar1 = FUN_08018c24(local_34,local_30);
    uVar2 = (**(code **)(DAT_0804cdb0 + 0x28))();
    uVar8 = uVar2;
    while (iVar1 == 0) {
      if (uVar7 == 0) {
        FUN_080192e0(local_30);
        return 0;
      }
      uVar5 = uVar7;
      if (uVar2 < uVar7) {
        uVar5 = uVar2;
      }
      iVar3 = (**(code **)(DAT_0804cdb0 + 0x68))();
      if (((iVar3 != 1) || (DAT_0804cd84 != '\x01')) && (uVar8 == uVar2)) {
        FUN_080180c0(*(uint*)DAT_0804cd8c,local_34,uVar5);
        uVar8 = 0;
      }
      if (DAT_0804cd85 == '\x02') {
        return 0xd;
      }
      uVar4 = FUN_08018110(param_4,uVar5,param_3,local_3c,1);
      FUN_0801842c(uVar4,1);
      if (local_3c[0] == 6) {
        return 0x16;
      }
      if (local_3c[0] != 0) {
        return 0xc;
      }
      uVar6 = uVar5;
      if ((uVar4 != uVar5) &&
         ((iVar3 = (**(code **)(DAT_0804cdb0 + 0x68))(), iVar3 != 1 ||
          (uVar6 = uVar4, uVar5 <= uVar4)))) goto LAB_080186d8;
      if ((DAT_0804cd7d != '\0') && (DAT_0804cd80 != '\0')) {
        DAT_0804cd81 = 1;
        DAT_0804cdd8 = param_4;
        DAT_0804cddc = uVar6;
      }
      uVar7 = uVar7 - uVar6;
      param_4 = param_4 + uVar6;
      local_34 = local_34 + uVar6;
      param_3 = param_3 - uVar6;
      uVar8 = uVar8 + uVar6;
    }
  }
  return iVar1;
}




/* 0x080186fc */
void FUN_080186fc()
{
  int iVar1;
  
  if (*(int *)(DAT_0804cd8c + 4) == 0) {
    iVar1 = FUN_08018740();
  }
  else {
    if (*(int *)(DAT_0804cd8c + 4) != 1) {
      iVar1 = 9;
      goto LAB_08018720;
    }
    iVar1 = FUN_08018834();
  }
  if (iVar1 == 0) {
    iVar1 = (**(code **)(DAT_0804cdb0 + 0x5c))();
  }
LAB_08018720:
  if ((DAT_0804cd85 != '\x02') && (FUN_08017d48(iVar1), DAT_0804cd85 != '\x02')) {
    *(undefined1 *)(DAT_0804cd8c + 0xc) = 1;
    DAT_0804cd85 = '\x03';
  }
  return;
}




/* 0x08018740 */
int FUN_08018740()
{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  
  uVar1 = (**(code **)(DAT_0804cdb0 + 0x18))();
  DAT_0804cd85 = 4;
  iVar2 = (**(code **)(DAT_0804cdb0 + 0x38))();
  *(uint*)DAT_0804cd90 = *(uint*)DAT_0804cd8c;
  iVar3 = FUN_080185fc(0,iVar2,0x400,&DAT_87c72878);
  if (iVar3 == 0) {
    (**(code **)(DAT_0804cdb0 + 0x30))(((uint*)&DAT_0804cd90)[1],&DAT_87c72878,iVar2);
    iVar9 = ((uint*)&DAT_0804cd90)[1];
    DAT_0804cd85 = 5;
    iVar3 = (**(code **)(DAT_0804cdb0 + 0x54))(iVar9);
    uVar4 = (**(code **)(DAT_0804cdb0 + 0x44))(iVar9);
    uVar5 = (**(code **)(DAT_0804cdb0 + 0x40))(iVar9);
    iVar6 = (**(code **)(DAT_0804cdb0 + 0x3c))(iVar9);
    iVar7 = uVar4 - uVar1 * (uVar4 / uVar1);
    uVar8 = uVar4;
    if ((iVar7 == 0) || (uVar1 = uVar1 - iVar7, uVar8 = uVar1 + uVar4, !CARRY4(uVar1,uVar4))) {
      if (*(uint*)DAT_0804cd8c != iVar6) {
        iVar2 = (**(code **)(DAT_0804cdb0 + 0x60))();
        if (iVar2 != 0) {
          return 0;
        }
        return 6;
      }
      iVar6 = (**(code **)(DAT_0804cdb0 + 0x20))(uVar5,uVar8);
      if (iVar6 != 0) {
        iVar3 = FUN_080185fc(iVar3 + iVar2,uVar4,uVar8,uVar5);
        if (iVar3 == 0) {
          if (DAT_0804cd7e == '\0') {
            return 0;
          }
          iVar2 = (**(code **)(DAT_0804cdd4 + 0x1c))(iVar9);
          if (iVar2 != 0) {
            return 0;
          }
          return 0x25;
        }
        goto LAB_080187fe;
      }
      iVar2 = (**(code **)(DAT_0804cdb0 + 0x60))();
      if (iVar2 != 0) {
        return 0;
      }
    }
    iVar3 = 0x12;
  }
  else {
LAB_080187fe:
    if (iVar3 == 0x16) {
      DAT_0804cd85 = 2;
                    /* WARNING: Subroutine does not return */
      FUN_08018be4();
    }
  }
  return iVar3;
}




/* 0x08018834 */
int FUN_08018834()
{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  int *piVar8;
  undefined4 *puVar9;
  int iVar10;
  uint uVar11;
  undefined4 *puVar12;
  uint uVar13;
  uint uVar14;
  int local_58;
  undefined4 *local_54;
  int local_34;
  undefined4 local_30;
  undefined4 local_2c [2];
  
  iVar5 = DAT_0804cd94;
  uVar14 = 0xffffffff;
  puVar7 = *(undefined4 **)(DAT_0804cd94 + 0x38);
  puVar9 = (undefined4 *)(DAT_0804cd94 + 4);
  local_30 = 0;
  local_2c[0] = 0;
  uVar1 = (**(code **)(DAT_0804cdb0 + 0x18))();
  if (puVar7 == (undefined4 *)0x0) {
    iVar2 = 0x11;
  }
  else {
    DAT_0804cd85 = 6;
    local_34 = 0;
    iVar2 = FUN_080185fc(0,0x34,0x400,&DAT_87c72878);
    if (iVar2 == 0) {
      (**(code **)(DAT_0804cdb0 + 0x30))(puVar9,&DAT_87c72878,0x34);
      FUN_08006bdc(&local_58,iVar5 + 0x14,0x24);
      iVar2 = FUN_0801839c(*puVar9,*(undefined4 *)(iVar5 + 8),*(undefined4 *)(iVar5 + 0xc),
                           *(undefined4 *)(iVar5 + 0x10));
      if (iVar2 == 0) {
        iVar2 = 0x14;
      }
      else {
        puVar12 = puVar7 + 5;
        *(undefined4 *)(DAT_0804cd94 + 0x44) = *(undefined4 *)(iVar5 + 0x1c);
        DAT_0804cd85 = 7;
        local_34 = *(int *)(iVar5 + 0x20);
        iVar2 = FUN_080185fc(local_34,(uint)*(ushort *)(iVar5 + 0x2e) *
                                      (uint)*(ushort *)(iVar5 + 0x30),0xc80,puVar12);
        if (iVar2 == 0) {
          uVar11 = 0;
          *puVar7 = 0xefbeadde;
          puVar7[1] = 0x98765432;
          puVar7[2] = 5;
          puVar7[3] = (uint)*(ushort *)(iVar5 + 0x30);
          puVar7[4] = *(undefined4 *)(iVar5 + 0x1c);
          DAT_0804cd85 = 9;
          local_54 = puVar12;
          do {
            if (*(ushort *)(iVar5 + 0x30) <= uVar11) {
              if ((int)uVar14 < 0) {
                iVar2 = 0x23;
                goto LAB_08018b90;
              }
              break;
            }
            if ((uint)(local_54[uVar11 * 8 + 6] << 5) >> 0x1d == 2) {
              uVar3 = (**(code **)(DAT_0804cdb0 + 100))();
              *(undefined4 *)(DAT_0804cd94 + 0x3c) = uVar3;
              uVar14 = uVar11;
            }
            uVar11 = uVar11 + 1;
          } while ((int)uVar14 < 0);
          local_34 = local_54[uVar14 * 8 + 1];
          iVar10 = *(int *)(DAT_0804cd94 + 0x3c);
          uVar6 = local_54[uVar14 * 8 + 4];
          iVar4 = uVar6 - uVar1 * (uVar6 / uVar1);
          uVar11 = uVar6;
          if (((iVar4 == 0) || (uVar11 = uVar6 + (uVar1 - iVar4), uVar6 <= uVar11)) &&
             (uVar6 < 0xa001)) {
            if (uVar6 != 0) {
              iVar2 = FUN_080185fc(local_34,uVar6,uVar11,iVar10);
            }
            if (iVar2 == 0) {
              if (DAT_0804cd7d != '\0') {
                DAT_0804cd7f = '\0';
                iVar2 = (**(code **)(DAT_0804cdd4 + 0x1c))(iVar10);
                if (iVar2 == 0) {
                  iVar2 = 0x21;
                  goto LAB_08018b90;
                }
                iVar2 = (**(code **)(DAT_0804cdb0 + 0x38))();
                (**(code **)(DAT_0804cdd4 + 0x18))(iVar10 + iVar2,puVar7[3],puVar12);
                iVar2 = FUN_08018ce8(puVar9,puVar7);
                if (iVar2 != 0) goto LAB_08018b90;
              }
              iVar2 = FUN_08018468(uVar14);
              if (iVar2 == 0) {
                *(undefined4 *)(DAT_0804cd94 + 0x4c) = 0;
                DAT_0804cd84 = 1;
                DAT_0804cde0 = iVar2;
                iVar4 = (**(code **)(DAT_0804cdb0 + 0x68))();
                if (((iVar4 == 1) &&
                    (iVar2 = (**(code **)(DAT_0804cdb0 + 0x6c))
                                       (puVar12,puVar7[3],&local_34,&DAT_0804cde4), iVar2 == 0)) &&
                   (DAT_0804cde4 != 0)) {
                  FUN_080180c0(*(uint*)DAT_0804cd8c,local_34);
                }
                uVar11 = 0;
LAB_08018b7a:
                if ((*(ushort *)(iVar5 + 0x30) <= uVar11) || (iVar2 != 0)) goto LAB_08018b86;
                if ((uVar14 != uVar11) || (DAT_0804cd7d == '\0' && DAT_0804cd82 == '\0')) {
                  piVar8 = local_54 + uVar11 * 8;
                  iVar4 = FUN_08017b38(*piVar8,piVar8[6]);
                  if (iVar4 == 0) {
                    if ((uint)(piVar8[6] << 8) >> 0x1d == 4) {
                      if (DAT_0804cd78 != '\0') {
                        iVar2 = 0x10;
                        goto LAB_08018b86;
                      }
                      DAT_0804cd78 = '\x01';
                      *(uint *)(DAT_0804cd94 + 0x40) = uVar11;
                    }
                    else if ((((*piVar8 == 6) ||
                              ((*piVar8 == 0 && ((uint)(piVar8[6] << 5) >> 0x1d == 7)))) &&
                             (DAT_0804cd7d != '\0')) && (DAT_0804cd7f != '\x01')) goto LAB_08018a7e;
                  }
                  else {
                    local_34 = piVar8[1];
                    local_58 = piVar8[3];
                    uVar13 = piVar8[4];
                    iVar4 = uVar13 - uVar1 * (uVar13 / uVar1);
                    uVar6 = uVar13;
                    if (((iVar4 != 0) && (uVar6 = (uVar1 - iVar4) + uVar13, uVar6 < uVar13)) ||
                       (iVar4 = (**(code **)(DAT_0804cdb0 + 0x20))(local_58,uVar6), iVar4 == 0)) {
                      iVar2 = 0x12;
                      goto LAB_08018b86;
                    }
                    if (piVar8[5] != 0) {
                      if (uVar13 != 0) {
                        if ((DAT_0804cd7d != '\0') && ((uint)(piVar8[6] << 5) >> 0x1d != 2)) {
                          iVar2 = (**(code **)(DAT_0804cdd4 + 4))();
                          if (iVar2 == 0) goto LAB_08018a7e;
                          DAT_0804cd80 = 1;
                        }
                        iVar2 = FUN_080185fc(local_34,uVar13,uVar6,local_58);
                        if (iVar2 != 0) goto LAB_08018b86;
                        if ((*(int *)(DAT_0804cd94 + 0x3c) == 0) &&
                           ((uint)(piVar8[6] << 5) >> 0x1d == 2)) {
                          *(int *)(DAT_0804cd94 + 0x3c) = local_58;
                        }
                        if ((DAT_0804cd7d != '\0') && ((uint)(piVar8[6] << 5) >> 0x1d != 2)) {
                          if ((DAT_0804cd7f == '\x01') &&
                             (((DAT_0804cd81 != '\x01' ||
                               (iVar2 = (**(code **)(DAT_0804cdd4 + 8))(DAT_0804cdd8,DAT_0804cddc),
                               iVar2 != 0)) &&
                              (DAT_0804cdd8 = (**(code **)(DAT_0804cdd4 + 0xc))(), DAT_0804cdd8 != 0
                              )))) {
                            iVar2 = (**(code **)(DAT_0804cdb0 + 0x70))(uVar11,&local_30);
                            iVar4 = (**(code **)(DAT_0804cdd4 + 0x10))(DAT_0804cdd8,local_30);
                            if (iVar4 != 0) {
                              DAT_0804cd80 = 0;
                              DAT_0804cd81 = '\0';
                              goto LAB_08018b0e;
                            }
                          }
LAB_08018a7e:
                          iVar2 = 0x22;
LAB_08018b86:
                          DAT_0804cd84 = 0;
                          DAT_0804cd83 = 0;
                          if (iVar2 == 0) {
                            DAT_0804cd83 = 0;
                            DAT_0804cd84 = 0;
                            return 0;
                          }
                          goto LAB_08018b90;
                        }
LAB_08018b0e:
                        FUN_08018c94(0,2);
                      }
                      iVar4 = piVar8[5] - piVar8[4];
                      if (iVar4 != 0) {
                        (**(code **)(DAT_0804cdb0 + 0x34))(piVar8[3] + piVar8[4],0,iVar4);
                        FUN_08018c94(iVar4,1);
                      }
                    }
                  }
                }
                uVar11 = uVar11 + 1;
                goto LAB_08018b7a;
              }
            }
          }
          else {
            iVar2 = 0x12;
          }
        }
      }
    }
  }
LAB_08018b90:
  iVar5 = (**(code **)(DAT_0804cdb0 + 0x68))();
  if (iVar5 == 1) {
    for (; DAT_0804cde4 != 0; DAT_0804cde4 = DAT_0804cde4 - iVar5) {
      local_58 = 1;
      iVar5 = FUN_08018110(0xffffdead,DAT_0804cde4,DAT_0804cde4,local_2c);
    }
  }
  if (iVar2 != 0x16) {
    return iVar2;
  }
  DAT_0804cd85 = 2;
                    /* WARNING: Subroutine does not return */
  FUN_08018be4();
}




/* 0x08018be4 */
void FUN_08018be4()
{
  code *pcVar1;
  
  pcVar1 = *(code **)(DAT_0804cdb0 + 0x1c);
  FUN_08017be4();
  (*pcVar1)();
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




/* 0x08018c18 */
void FUN_08018c18(param_1)
undefined1 param_1;
{
  DAT_0804cd82 = param_1;
  return;
}




/* 0x08018c24 */
undefined4 FUN_08018c24(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  int local_24;
  
  uVar4 = 0;
  local_24 = 0;
  iVar1 = (**(code **)(DAT_0804cdb0 + 0x68))();
  if ((iVar1 == 1) && (DAT_0804cd84 == '\x01')) {
    if (DAT_0804cde0 != 0) {
      for (uVar3 = param_1 - DAT_0804cde0; uVar3 != 0; uVar3 = uVar3 - uVar2) {
        uVar2 = FUN_08018110(0xffffdead,uVar3,uVar3,&local_24,1);
        if (local_24 == 6) {
          uVar4 = 0x16;
          break;
        }
        if (local_24 != 0) {
          uVar4 = 0xc;
          break;
        }
        if (uVar3 < uVar2) {
          uVar4 = 8;
          break;
        }
      }
    }
    DAT_0804cde0 = param_1 + param_2;
  }
  return uVar4;
}




/* 0x08018c94 */
void FUN_08018c94(param_1, param_2)
int param_1; int param_2;
{
  int iVar1;
  int iVar2;
  
  if (DAT_0804cd83 == '\x01') {
    iVar2 = DAT_0804cde8;
    iVar1 = param_1;
    if (((param_2 != 0) && (iVar2 = param_1, iVar1 = DAT_0804cde8, param_2 != 1)) &&
       (iVar2 = 0, param_2 == 2)) {
      iVar2 = DAT_0804cde8;
      iVar1 = 0;
    }
    DAT_0804cde8 = iVar1;
    *(int *)(DAT_0804cd94 + 0x4c) = *(int *)(DAT_0804cd94 + 0x4c) + iVar2;
  }
  return;
}




/* 0x08018ce8 */
undefined4 FUN_08018ce8(param_1, param_2)
undefined4 * param_1; int param_2;
{
  int iVar1;
  undefined1 auStack_38 [36];
  
  DAT_0804cd7f = 0;
  if (param_1 != (undefined4 *)0x0) {
    FUN_08006bdc(auStack_38,param_1 + 4,0x24);
    iVar1 = FUN_0801839c(*param_1,param_1[1],param_1[2],param_1[3]);
    if (iVar1 != 0) {
      iVar1 = (**(code **)(DAT_0804cdd4 + 4))();
      if ((((iVar1 == 0) || (iVar1 = (**(code **)(DAT_0804cdd4 + 8))(param_1,0x34), iVar1 == 0)) ||
          (iVar1 = (**(code **)(DAT_0804cdd4 + 8))(param_2 + 0x14,*(int *)(param_2 + 0xc) << 5),
          iVar1 == 0)) ||
         ((iVar1 = (**(code **)(DAT_0804cdd4 + 0xc))(), iVar1 == 0 ||
          (iVar1 = (**(code **)(DAT_0804cdd4 + 0x10))(iVar1,0), iVar1 == 0)))) {
        return 0x22;
      }
      iVar1 = FUN_08017b5c(param_1,param_2);
      if (iVar1 != 0) {
        DAT_0804cd7f = 1;
        return 0;
      }
    }
  }
  return 0x14;
}




/* 0x08018d6a */
undefined4 FUN_08018d6a(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  
  uVar1 = 0;
  do {
    if (*(int *)(param_1 + uVar1 * 0x70 + 0x18) == param_2) {
      return *(undefined4 *)(param_1 + uVar1 * 0x70 + 0x1c);
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 < 4);
  return 0;
}




/* 0x08018d94 */
undefined4 FUN_08018d94(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  
  uVar1 = 0;
  do {
    if (*(int *)(param_1 + uVar1 * 0x70 + 0x18) == param_2) {
      return *(undefined4 *)(param_1 + uVar1 * 0x70 + 0x20);
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 < 4);
  return 0;
}




/* 0x08018dbe */
int FUN_08018dbe(param_1, param_2)
int param_1; int param_2;
{
  uint uVar1;
  
  uVar1 = 0;
  do {
    if (*(int *)(param_1 + uVar1 * 0x70 + 0x18) == param_2) {
      return param_1 + uVar1 * 0x70 + 0x28;
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 < 4);
  return 0;
}




/* 0x08018dec */
undefined4 FUN_08018dec()
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0x302e;
  iVar1 = thunk_FUN_080355fc(&DAT_08052c68);
  if ((iVar1 == 0) && (iVar1 = thunk_FUN_08035908(&DAT_08052c50), iVar1 == 0)) {
    uVar2 = 0;
  }
  return uVar2;
}




