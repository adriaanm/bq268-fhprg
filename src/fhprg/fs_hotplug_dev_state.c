/* Auto-generated: fs_hotplug_dev_state.c */
/* Functions: 3 */
#include "globals.h"

/* 0x08025c98 */
void FUN_08025c98(param_1, param_2)
char * param_1; undefined4 param_2;
{
  char cVar1;
  
  FUN_08026f34();
  if (false) {
switchD_08025cac_caseD_0:
    FUN_08015a50();
    return;
  }
  switch(param_2) {
  default:
    goto switchD_08025cac_caseD_0;
  case 1:
    if (*param_1 != '\0') {
      ((code*)DAT_0804cd60)("fs_hotplug_dev_state.c",0x59);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    cVar1 = '\x01';
    break;
  case 2:
    cVar1 = *param_1;
    if ((((cVar1 != '\0') && (cVar1 != '\x06')) && (cVar1 != '\a')) && (cVar1 != '\x05')) {
      ((code*)DAT_0804cd60)("fs_hotplug_dev_state.c",0x5e);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    cVar1 = '\x02';
    break;
  case 3:
    if (*param_1 != '\x02') {
      ((code*)DAT_0804cd60)("fs_hotplug_dev_state.c",0x66);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    cVar1 = '\x03';
    break;
  case 4:
    if (*param_1 != '\x03') {
      ((code*)DAT_0804cd60)("fs_hotplug_dev_state.c",0x6b);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    cVar1 = '\x04';
    break;
  case 5:
    if (*param_1 != '\x04') {
      ((code*)DAT_0804cd60)("fs_hotplug_dev_state.c",0x70);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    cVar1 = '\x05';
    break;
  case 6:
    cVar1 = '\x06';
    break;
  case 7:
    if (*param_1 != '\x05') {
      ((code*)DAT_0804cd60)("fs_hotplug_dev_state.c",0x79,0x302f);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    cVar1 = '\a';
  }
  *param_1 = cVar1;
  return;
}




/* 0x08025d64 */
undefined4 thunk_FUN_08025d64(param_1)
int param_1;
{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_08026516();
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  FUN_08026e44(*(undefined4 *)(param_1 + 0x14),param_1);
  uVar2 = FUN_08013a7c(*(undefined4 *)(*(int *)(param_1 + 0x14) + 0x1c),
                       *(undefined4 *)(param_1 + 0x18));
  *(undefined4 *)(param_1 + 0x18) = 0;
  FUN_08026b88(*(undefined4 *)(param_1 + 8));
  FUN_08026320(param_1);
  return uVar2;
}




/* 0x08025d64 */
undefined4 FUN_08025d64(param_1)
int param_1;
{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_08026516();
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  FUN_08026e44(*(undefined4 *)(param_1 + 0x14),param_1);
  uVar2 = FUN_08013a7c(*(undefined4 *)(*(int *)(param_1 + 0x14) + 0x1c),
                       *(undefined4 *)(param_1 + 0x18));
  *(undefined4 *)(param_1 + 0x18) = 0;
  FUN_08026b88(*(undefined4 *)(param_1 + 8));
  FUN_08026320(param_1);
  return uVar2;
}




