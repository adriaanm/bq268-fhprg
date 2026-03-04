/*
 * dispatch.c - Firehose Command Router
 *
 * This module contains the core XML command dispatcher that parses incoming
 * Firehose XML commands and routes them to appropriate handler functions
 * (configure, program, read, erase, patch, etc.) based on tag names.
 *
 * The dispatcher is the main state machine entry point that processes the
 * XML stream and orchestrates all command handling.
 */

#include "firehose.h"

/* orig: 0x0802f130 firehose_dispatch */
undefined4 firehose_dispatch()
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 auStack_218 [512];
  int local_18;

  iVar1 = DAT_0804cd58;
  local_18 = DAT_0804cd58;
  iVar2 = FUN_08038db4();
  FUN_08006d14(auStack_218,0x200);
  if (iVar2 == 0) {
LAB_0802f176:
    uVar3 = 1;
  }
  else {
    if (iVar2 == 4) {
      xml_get_tag_name(&DAT_08055ea0,auStack_218,0x200,0);
      iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f2e8);
      if (iVar2 != 0) goto LAB_0802f176;
    }
    else if (iVar2 == 1) {
      iVar2 = xml_tag_match(&DAT_08055ea0,"configure");
      if (iVar2 != 0) {
        uVar3 = handle_configure();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,"program");
      if (iVar2 != 0) {
        uVar3 = handle_program();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,"firmwarewrite");
      if (iVar2 != 0) {
        uVar3 = handle_firmwarewrite();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,"patch");
      if (iVar2 != 0) {
        uVar3 = handle_patch();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,"setbootablestoragedrive");
      if (iVar2 != 0) {
        uVar3 = handle_setbootable();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f334);
      if ((iVar2 != 0) || (iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f338), iVar2 != 0)) {
        uVar3 = handle_storagextras();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,"power");
      if (iVar2 != 0) {
        uVar3 = handle_power();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,"benchmark");
      if (iVar2 != 0) {
        uVar3 = handle_benchmark();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f354);
      if (iVar2 != 0) {
        uVar3 = handle_read();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,"getstorageinfo");
      if (iVar2 != 0) {
        uVar3 = handle_getstorageinfo();
        goto LAB_0802f2a6;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,"getcrc16digest");
      if (iVar2 == 0) {
        iVar2 = xml_tag_match(&DAT_08055ea0,"getsha256digest");
        if (iVar2 == 0) {
          iVar2 = xml_tag_match(&DAT_08055ea0,"erase");
          if (iVar2 != 0) {
            uVar3 = handle_erase();
            goto LAB_0802f2a6;
          }
          iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f394);
          if (iVar2 != 0) {
            uVar3 = handle_peek();
            goto LAB_0802f2a6;
          }
          iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f39c);
          if (iVar2 != 0) {
            uVar3 = handle_poke();
            goto LAB_0802f2a6;
          }
          iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f3a4);
          if (iVar2 != 0) {
            uVar3 = handle_nop();
            goto LAB_0802f2a6;
          }
          iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f3a8);
          if (((iVar2 == 0) && (iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f2e8), iVar2 == 0)) &&
             (iVar2 = xml_tag_match(&DAT_08055ea0,"patches"), iVar2 == 0)) {
            iVar2 = xml_get_tag_name(&DAT_08055ea0,auStack_218,0x200,0);
            if (iVar2 == 0) {
              firehose_log("WARNING: Ignoring unrecognized tag too long to display. Continuing.");
            }
            else {
              firehose_log("WARNING: Ignoring unrecognized tag \'%s\'. Continuing.",auStack_218);
            }
            uVar3 = handle_response(1);
            goto LAB_0802f2a6;
          }
          goto LAB_0802f2a4;
        }
        uVar3 = 0;
      }
      else {
        uVar3 = 1;
      }
      uVar3 = FUN_080233ec(uVar3);
      goto LAB_0802f2a6;
    }
LAB_0802f2a4:
    uVar3 = 0;
  }
LAB_0802f2a6:
  if (local_18 != iVar1) {
    FUN_08010960();
  }
  return uVar3;
}

/* orig: 0x0802f838 FUN_0802f838 */
void FUN_0802f838(param_1)
int param_1;
{
  if (param_1 == 0) {
    DAT_0804d3a4 = 1;
  }
  else {
    DAT_0804d3a4 = 2;
  }
  return;
}
