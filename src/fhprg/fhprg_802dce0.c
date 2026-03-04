/* Auto-generated: fhprg_802dce0.c */
/* Functions: 14 */
#include "globals.h"

/* 0x0802dce0 */
undefined4 FUN_0802dce0(param_1)
uint param_1;
{
  if (2 < param_1) {
    return 0;
  }
  return *(undefined4 *)(&DAT_08050860 + param_1 * 4);
}




/* 0x0802dcf4 */
undefined4 FUN_0802dcf4()
{
  return DAT_0805085c;
}




/* 0x0802dd00 */
undefined4 FUN_0802dd00()
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  pm_smb1360_init();
  DAT_080508f8 = (int *)FUN_0802dcf4();
  if ((((DAT_080508f8 == (int *)0x0) || (iVar1 = ((uint*)&DAT_080508f8)[1], iVar1 == 0)) ||
      (*(uint*)DAT_080508f8 == 0)) || ((*(int *)(iVar1 + 0x24) == 0 || (*(int *)(iVar1 + 0x1c) == 0)))) {
    uVar2 = 0x7d;
  }
  else {
    DAT_080508f0 = 1;
    DAT_080508fc = *(undefined4 *)(*(uint*)DAT_080508f8 + 8);
    DAT_08050900 = *(undefined4 *)(*(uint*)DAT_080508f8 + 0xc);
    iVar1 = FUN_0800ce64(*(undefined4 *)(*(uint*)DAT_080508f8 + 4),&DAT_080508f4);
    if (iVar1 == 0) {
      iVar1 = FUN_0800cf6c(DAT_080508f4,2);
      if (iVar1 != 0) {
        uVar2 = 5;
        FUN_0800cdc8(DAT_080508f4);
      }
    }
    else {
      uVar2 = 5;
    }
  }
  return uVar2;
}




/* 0x0802dd64 */
undefined1 FUN_0802dd64(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  
  uVar1 = 0;
  if (DAT_080508f0 != '\0') {
    iVar2 = FUN_08021ff0(param_1,*(undefined4 *)(*(int *)(DAT_080508f8 + 4) + 0x24),
                         *(undefined1 *)(*(int *)(DAT_080508f8 + 4) + 0x28),param_1,param_3,param_4)
    ;
    if (iVar2 == -1) {
      uVar1 = 0xe;
    }
    else {
      iVar3 = *(int *)(DAT_080508f8 + 4);
      uVar5 = (uint)*(byte *)(iVar3 + 0x19);
      iVar3 = FUN_08037390(*(undefined1 *)(iVar3 + 0x17),iVar2 << uVar5 & 0xff,
                           (1 << ((*(byte *)(iVar3 + 0x18) - uVar5) + 1 & 0xff)) + -1 << uVar5 &
                           0xff);
      uVar1 = 0;
      if (iVar3 != 0) {
        iVar3 = *(int *)(DAT_080508f8 + 4);
        uVar5 = (uint)*(byte *)(iVar3 + 0x19);
        uVar4 = FUN_08037390(*(undefined1 *)(iVar3 + 0x17),iVar2 << uVar5 & 0xff,
                             (1 << ((*(byte *)(iVar3 + 0x18) - uVar5) + 1 & 0xff)) + -1 << uVar5 &
                             0xff);
        snprintf_buf(&DAT_0805a2b8,0x3f,"In %s,result = %d line = %d failed\n",
                     "pm_smb_set_ibat_fast",uVar4,0x15d);
        boot_log_message(&DAT_0805a2b8);
        uVar1 = 5;
      }
    }
  }
  return uVar1;
}




/* 0x0802de28 */
undefined1 FUN_0802de28(param_1, param_2, param_3, param_4)
undefined4 param_1; undefined4 param_2; undefined4 param_3; undefined4 param_4;
{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  
  uVar1 = 0;
  if (DAT_080508f0 != '\0') {
    iVar2 = FUN_08021ff0(param_1,*(undefined4 *)(*(int *)(DAT_080508f8 + 4) + 0x1c),
                         *(undefined1 *)(*(int *)(DAT_080508f8 + 4) + 0x20),param_1,param_3,param_4)
    ;
    if (iVar2 == -1) {
      uVar1 = 0xe;
    }
    else {
      iVar3 = *(int *)(DAT_080508f8 + 4);
      uVar5 = (uint)*(byte *)(iVar3 + 0x16);
      iVar3 = FUN_08037390(*(undefined1 *)(iVar3 + 0x14),iVar2 << uVar5 & 0xff,
                           (1 << ((*(byte *)(iVar3 + 0x15) - uVar5) + 1 & 0xff)) + -1 << uVar5 &
                           0xff);
      uVar1 = 0;
      if (iVar3 != 0) {
        iVar3 = *(int *)(DAT_080508f8 + 4);
        uVar5 = (uint)*(byte *)(iVar3 + 0x16);
        uVar4 = FUN_08037390(*(undefined1 *)(iVar3 + 0x14),iVar2 << uVar5 & 0xff,
                             (1 << ((*(byte *)(iVar3 + 0x15) - uVar5) + 1 & 0xff)) + -1 << uVar5 &
                             0xff);
        snprintf_buf(&DAT_0805a2b8,0x3f,"In %s,result = %d line = %d failed\n","pm_smb_set_icl",
                     uVar4,0x145);
        boot_log_message(&DAT_0805a2b8);
        uVar1 = 5;
      }
    }
  }
  return uVar1;
}




/* 0x0802deec */
longlong FUN_0802deec(param_1, param_2, param_3, param_4)
int param_1; uint param_2; undefined4 param_3; uint param_4;
{
  undefined1 uVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint local_18;
  
  local_18 = param_4 & 0xffffff00;
  bVar2 = false;
  uVar5 = 0;
  if (DAT_080508f0 == '\0') goto LAB_0802dffc;
  iVar3 = *(int *)(DAT_080508f8 + 4);
  if (param_1 == 2) {
    iVar3 = FUN_08037390(*(undefined1 *)(iVar3 + 0x10),*(undefined1 *)(iVar3 + 0x11),
                         *(undefined1 *)(iVar3 + 0x11),param_4,param_2,param_3);
    if (iVar3 == 0) goto LAB_0802dfbe;
    uVar1 = *(undefined1 *)(*(int *)(DAT_080508f8 + 4) + 0x11);
    param_2 = FUN_08037390(*(undefined1 *)(*(int *)(DAT_080508f8 + 4) + 0x10),uVar1,uVar1);
    uVar5 = 0x111;
  }
  else {
    iVar3 = FUN_08037390(*(undefined1 *)(iVar3 + 0x10),0,*(undefined1 *)(iVar3 + 0x11),param_4,
                         param_2,param_3);
    iVar4 = *(int *)(DAT_080508f8 + 4);
    if (iVar3 == 0) {
      iVar3 = FUN_080372d0(*(undefined1 *)(iVar4 + 0xe),&local_18);
      iVar4 = *(int *)(DAT_080508f8 + 4);
      if (iVar3 == 0) {
        if ((((*(byte *)(iVar4 + 0xf) & (byte)local_18) == 0) || (bVar2 = true, param_1 != 1)) &&
           (bVar2 || param_1 != 0)) {
          iVar3 = FUN_08037390(*(undefined1 *)(iVar4 + 0x12),*(undefined1 *)(iVar4 + 0x13),
                               *(undefined1 *)(iVar4 + 0x13));
          if (iVar3 == 0) {
LAB_0802dfbe:
            iVar3 = FUN_08037390(*(undefined1 *)(*(int *)(DAT_080508f8 + 4) + 0xc),0,
                                 *(undefined1 *)(*(int *)(DAT_080508f8 + 4) + 0xd));
            if (iVar3 == 0) {
              return (ulonglong)param_2 << 0x20;
            }
            param_2 = FUN_08037390(*(undefined1 *)(*(int *)(DAT_080508f8 + 4) + 0xc),0,
                                   *(undefined1 *)(*(int *)(DAT_080508f8 + 4) + 0xd));
            uVar5 = 0x12e;
          }
          else {
            uVar1 = *(undefined1 *)(*(int *)(DAT_080508f8 + 4) + 0x13);
            param_2 = FUN_08037390(*(undefined1 *)(*(int *)(DAT_080508f8 + 4) + 0x12),uVar1,uVar1);
            uVar5 = 0x128;
          }
        }
        else {
          iVar3 = FUN_08037390(*(undefined1 *)(iVar4 + 0x12),0,*(undefined1 *)(iVar4 + 0x13));
          if (iVar3 == 0) goto LAB_0802dfbe;
          param_2 = FUN_08037390(*(undefined1 *)(*(int *)(DAT_080508f8 + 4) + 0x12),0,
                                 *(undefined1 *)(*(int *)(DAT_080508f8 + 4) + 0x13));
          uVar5 = 0x123;
        }
      }
      else {
        param_2 = FUN_080372d0(*(undefined1 *)(iVar4 + 0xe),&local_18);
        uVar5 = 0x119;
      }
    }
    else {
      param_2 = FUN_08037390(*(undefined1 *)(iVar4 + 0x10),0,*(undefined1 *)(iVar4 + 0x11));
      uVar5 = 0x116;
    }
  }
  snprintf_buf(&DAT_0805a2b8,0x3f,"In %s,result = %d line = %d failed\n","pm_smb_set_icl_mode",
               param_2,uVar5);
  boot_log_message(&DAT_0805a2b8);
  uVar5 = 5;
LAB_0802dffc:
  return CONCAT44(param_2,uVar5);
}




/* 0x0802e034 */
uint FUN_0802e034(param_1, param_2, param_3, param_4)
undefined4 param_1; uint param_2; undefined1 * param_3; uint param_4;
{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  undefined4 *puVar4;
  ushort *puVar5;
  uint uVar6;
  uint uVar7;
  uint local_20;
  uint local_1c;
  
  local_20 = (uint)param_3 & 0xffffff00;
  local_1c = param_4 & 0xffffff00;
  puVar4 = (undefined4 *)FUN_0802e594();
  puVar5 = (ushort *)puVar4[1];
  uVar1 = puVar5[1];
  uVar2 = *puVar5;
  uVar3 = puVar5[0x13];
  if (puVar4 == (undefined4 *)0x0) {
    uVar6 = 0x16;
  }
  else if (param_2 < *(byte *)(puVar4 + 2)) {
    if (param_3 == (undefined1 *)0x0) {
      uVar6 = 0x73;
    }
    else {
      uVar7 = FUN_0802b1e8(*(undefined4 *)*puVar4,
                           (uint)puVar5[0xe] + (uint)uVar2 + uVar1 * param_2 + 0x300 & 0xffff,
                           &local_20,0);
      uVar6 = FUN_0802b1e8(*(undefined4 *)*puVar4,
                           (uint)uVar3 + (uint)uVar2 + uVar1 * param_2 + 0x400 & 0xffff,&local_1c,0)
      ;
      uVar6 = uVar6 | uVar7;
      if ((int)(local_20 << 0x18) < 0) {
        *param_3 = 1;
        if ((int)(local_1c << 0x18) < 0) {
          *param_3 = 3;
          uVar6 = 0;
        }
      }
      else if ((int)(local_1c << 0x18) < 0) {
        *param_3 = 2;
      }
      else {
        *param_3 = 0;
      }
    }
  }
  else {
    uVar6 = 0x78;
  }
  return uVar6;
}




/* 0x0802e0d6 */
undefined4 FUN_0802e0d6(param_1, param_2, param_3, param_4, param_5)
undefined4 param_1; uint param_2; undefined1 * param_3; undefined1 * param_4; undefined1 * param_5;
{
  undefined4 *puVar1;
  undefined4 uVar2;
  ushort *puVar3;
  uint local_20;
  
  local_20 = (uint)param_4 & 0xffffff00;
  puVar1 = (undefined4 *)FUN_0802e594();
  puVar3 = (ushort *)puVar1[1];
  if (puVar1 == (undefined4 *)0x0) {
    uVar2 = 0x16;
  }
  else if (param_2 < *(byte *)(puVar1 + 2)) {
    if (((param_3 == (undefined1 *)0x0) || (param_4 == (undefined1 *)0x0)) ||
       (param_5 == (undefined1 *)0x0)) {
      uVar2 = 0x73;
    }
    else {
      uVar2 = FUN_0802b1e8(*(undefined4 *)*puVar1,
                           param_2 * puVar3[1] + 0x200 + (uint)*puVar3 + (uint)puVar3[0xd] & 0xffff,
                           &local_20,0);
      if ((int)(local_20 << 0x18) < 0) {
        *param_3 = 1;
      }
      else {
        *param_3 = 0;
      }
      if ((int)(local_20 << 0x1e) < 0) {
        *param_4 = 1;
      }
      else {
        *param_4 = 0;
      }
      if ((local_20 & 1) == 0) {
        *param_5 = 0;
      }
      else {
        *param_5 = 1;
      }
    }
  }
  else {
    uVar2 = 0x78;
  }
  return uVar2;
}




/* 0x0802e198 */
uint FUN_0802e198(param_1, param_2, param_3, param_4)
undefined4 param_1; uint param_2; uint param_3; uint param_4;
{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  undefined4 *puVar5;
  ushort *puVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  
  uVar10 = 0;
  puVar5 = (undefined4 *)FUN_0802e594();
  if (puVar5 == (undefined4 *)0x0) {
    uVar7 = 0x16;
  }
  else {
    puVar6 = (ushort *)puVar5[1];
    uVar1 = *puVar6;
    uVar2 = puVar6[7];
    uVar3 = puVar6[1];
    uVar4 = puVar6[8];
    if (param_2 < *(byte *)(puVar5 + 2)) {
      iVar8 = FUN_0802e86c(0x2b);
      if (iVar8 == 0) {
        uVar7 = 0x73;
      }
      else {
        uVar7 = (uint)*(ushort *)(iVar8 + 0x26);
        if (param_3 < uVar7) {
          uVar10 = 0xe;
          param_3 = uVar7;
        }
        else if (*(ushort *)(iVar8 + 6) < param_3) {
          uVar10 = 0xe;
          param_3 = (uint)*(ushort *)(iVar8 + 6);
        }
        if (param_4 < *(ushort *)(iVar8 + 0x2a)) {
          uVar10 = 0xf;
          param_4 = (uint)*(ushort *)(iVar8 + 0x2a);
        }
        if (*(ushort *)(iVar8 + 0x2c) < param_4) {
          uVar10 = 0xf;
          param_4 = (uint)*(ushort *)(iVar8 + 0x2c);
        }
        if (param_3 < param_4) {
          uVar9 = FUN_0802b282(*(undefined4 *)*puVar5,
                               (uint)uVar1 + (uint)uVar2 + param_2 * uVar3 & 0xffff,0xf,
                               (param_3 - uVar7) / 0x32 & 0xff,0);
          uVar7 = FUN_0802b282(*(undefined4 *)*puVar5,
                               (uint)uVar4 + (uint)uVar1 + param_2 * uVar3 & 0xffff,0xf,
                               (param_4 - *(ushort *)(iVar8 + 0x2a)) / 100 & 0xff,0);
          uVar7 = uVar7 | uVar9 | uVar10;
        }
        else {
          uVar7 = 0xe;
        }
      }
    }
    else {
      uVar7 = 0x78;
    }
  }
  return uVar7;
}




/* 0x0802e264 */
uint FUN_0802e264(param_1, param_2, param_3)
undefined4 param_1; short param_2; int param_3;
{
  short sVar1;
  short sVar2;
  short sVar3;
  undefined4 *puVar4;
  short *psVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  short sVar9;
  undefined4 uVar10;
  
  puVar4 = (undefined4 *)FUN_0802e594();
  psVar5 = (short *)puVar4[1];
  sVar1 = psVar5[1];
  sVar2 = *psVar5;
  sVar3 = psVar5[0xc];
  sVar9 = psVar5[0xb] + sVar2 + sVar1 * param_2;
  if (puVar4 != (undefined4 *)0x0) {
    if (param_3 == 0) {
      uVar6 = FUN_0802b282(*(undefined4 *)*puVar4,sVar9,0xff,0xa5,0);
      uVar10 = 0;
      uVar7 = *(undefined4 *)*puVar4;
    }
    else {
      uVar6 = FUN_0802b282(*(undefined4 *)*puVar4,sVar9,0xff,0xa5,0);
      uVar10 = 0x20;
      uVar7 = *(undefined4 *)*puVar4;
    }
    uVar8 = FUN_0802b282(uVar7,sVar3 + sVar2 + sVar1 * param_2,0xff,uVar10,0);
    return uVar8 | uVar6;
  }
  return 0x16;
}




/* 0x0802e2d0 */
uint FUN_0802e2d0(param_1, param_2, param_3)
undefined4 param_1; uint param_2; uint param_3;
{
  undefined4 *puVar1;
  uint uVar2;
  ushort *puVar3;
  uint uVar4;
  
  uVar4 = 0;
  puVar1 = (undefined4 *)FUN_0802e594();
  puVar3 = (ushort *)puVar1[1];
  if (puVar1 == (undefined4 *)0x0) {
    return 0x16;
  }
  if (*(byte *)(puVar1 + 2) <= param_2) {
    return 0x78;
  }
  if (param_3 < 0xcb3) {
    if (param_3 < 100) {
      uVar4 = 0xe;
      param_3 = 100;
    }
  }
  else {
    uVar4 = 0xe;
    param_3 = 0xcb2;
  }
  uVar2 = FUN_0802b282(*(undefined4 *)*puVar1,
                       puVar3[1] * param_2 + (uint)*puVar3 + (uint)puVar3[3] & 0xffff,0x3f,
                       (param_3 - 100) / 0x32 & 0xff,0);
  return uVar2 | uVar4;
}




/* 0x0802e32e */
uint FUN_0802e32e(param_1, param_2, param_3)
undefined4 param_1; uint param_2; uint param_3;
{
  undefined4 *puVar1;
  uint uVar2;
  ushort *puVar3;
  uint uVar4;
  
  uVar4 = 0;
  puVar1 = (undefined4 *)FUN_0802e594();
  puVar3 = (ushort *)puVar1[1];
  if (puVar1 == (undefined4 *)0x0) {
    return 0x16;
  }
  if (*(byte *)(puVar1 + 2) <= param_2) {
    return 0x78;
  }
  if (param_3 < 0xc9) {
    if (param_3 < 0x32) {
      uVar4 = 0xe;
      param_3 = 0x32;
    }
  }
  else {
    uVar4 = 0xe;
    param_3 = 200;
  }
  uVar2 = FUN_0802b282(*(undefined4 *)*puVar1,
                       puVar3[1] * param_2 + (uint)*puVar3 + (uint)puVar3[9] & 0xffff,0xf,
                       (param_3 - 0x32) / 10 & 0xff,0);
  return uVar2 | uVar4;
}




/* 0x0802e388 */
uint FUN_0802e388(param_1, param_2, param_3)
undefined4 param_1; uint param_2; uint param_3;
{
  ushort uVar1;
  ushort uVar2;
  undefined4 *puVar3;
  ushort *puVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  
  uVar9 = 0;
  uVar8 = 0;
  puVar3 = (undefined4 *)FUN_0802e594();
  puVar4 = (ushort *)puVar3[1];
  uVar6 = (uint)*puVar4;
  uVar1 = puVar4[0x10];
  iVar7 = param_2 * puVar4[1] + 0x300;
  uVar2 = puVar4[0x12];
  if (puVar3 == (undefined4 *)0x0) {
    return 0x16;
  }
  if (*(byte *)(puVar3 + 2) <= param_2) {
    return 0x78;
  }
  if (param_3 < 0x5dd) {
    if (param_3 < 100) {
      uVar8 = 0xe;
      goto LAB_0802e402;
    }
    if (param_3 == 100) goto LAB_0802e402;
    if (param_3 == 0x96) {
      uVar9 = 1;
      goto LAB_0802e402;
    }
  }
  else {
    uVar8 = 0xe;
    param_3 = 0x5dc;
  }
  uVar9 = param_3 / 100 & 0xff;
LAB_0802e402:
  uVar9 = FUN_0802b282(*(undefined4 *)*puVar3,puVar4[0x11] + uVar6 + iVar7 & 0xffff,0x1f,uVar9,0);
  uVar5 = FUN_0802b282(*(undefined4 *)*puVar3,uVar6 + uVar1 + iVar7 & 0xffff,0x80,0x80,0);
  uVar6 = FUN_0802b282(*(undefined4 *)*puVar3,uVar2 + uVar6 + iVar7 & 0xffff,0x80,0x80,0);
  return uVar6 | uVar5 | uVar9 | uVar8;
}




/* 0x0802e444 */
uint FUN_0802e444(param_1, param_2, param_3)
undefined4 param_1; uint param_2; uint param_3;
{
  undefined4 *puVar1;
  ushort *puVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  
  puVar1 = (undefined4 *)FUN_0802e594();
  puVar2 = (ushort *)puVar1[1];
  uVar5 = (uint)*puVar2;
  iVar4 = param_2 * puVar2[1];
  uVar7 = uVar5 + puVar2[4] + iVar4 & 0xffff;
  uVar8 = puVar2[5] + uVar5 + iVar4 & 0xffff;
  if (puVar1 == (undefined4 *)0x0) {
    return 0x16;
  }
  if (param_2 < *(byte *)(puVar1 + 2)) {
    if (3 < param_3) {
      return 0xe;
    }
    if (param_3 == 0) {
      uVar6 = 0;
      uVar3 = *(undefined4 *)*puVar1;
      uVar8 = uVar7;
    }
    else {
      if (param_3 == 1) {
        uVar8 = FUN_0802b282(*(undefined4 *)*puVar1,puVar2[0x14] + uVar5 + iVar4 + 0x600 & 0xffff,
                             0x80,0x80,0);
        uVar5 = FUN_0802b282(*(undefined4 *)*puVar1,uVar7,0x80,0x80,0);
        return uVar5 | uVar8;
      }
      if (param_3 == 2) {
        uVar6 = 0;
        uVar3 = *(undefined4 *)*puVar1;
      }
      else {
        if (param_3 != 3) {
          return 0xe;
        }
        uVar6 = 0x80;
        uVar3 = *(undefined4 *)*puVar1;
      }
    }
    uVar8 = FUN_0802b282(uVar3,uVar8,0x80,uVar6,0);
    return uVar8;
  }
  return 0x78;
}




