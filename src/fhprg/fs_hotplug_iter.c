/* Auto-generated: fs_hotplug_iter.c */
/* Functions: 1 */
#include "globals.h"

/* 0x080266cc */
int FUN_080266cc(param_1)
int param_1;
{
  char cVar1;
  int iVar2;
  
  while( true ) {
    while( true ) {
      FUN_08026798(param_1);
      iVar2 = *(int *)(param_1 + 0xc);
      if (iVar2 == 0) {
        return 0;
      }
      cVar1 = *(char *)(param_1 + 5);
      if (cVar1 != '\x01') break;
      if (*(char *)(iVar2 + 0x2a) == '\x02') {
        return iVar2;
      }
    }
    if ((cVar1 != '\x02') && (cVar1 != '\x03')) {
      ((code*)DAT_0804cd60)("fs_hotplug_iter.c",0xbf,0x302f);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    cVar1 = *(char *)(iVar2 + 0x2a);
    if (cVar1 == '\x04') {
      return iVar2;
    }
    if (cVar1 == '\x03') break;
    if (cVar1 == '\x05') {
      return iVar2;
    }
  }
  return iVar2;
}




