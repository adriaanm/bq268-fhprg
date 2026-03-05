/* dispatch.c — Firehose command router (minimal: read/write only).
 *
 * Only dispatches: configure, program, read, getsha256digest.
 * All other tags get a NAK response.
 *
 * Source: src/fhprg/fhprg_802efa4.c
 */
#include "firehose.h"

/* orig: 0x0802f130 firehose_dispatch — main XML command router.
 *
 * Called in a loop by the main firehose state machine. Each call:
 *   1. Calls xml_advance() to parse the next XML token
 *   2. If it's an open tag, matches against known command names
 *   3. Dispatches to the appropriate handler
 *   4. Returns 0 (continue) or 1 (done)
 */
undefined4 firehose_dispatch()
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 auStack_218 [512];
  int local_18;

  iVar1 = DAT_0804cd58;
  local_18 = DAT_0804cd58;
  iVar2 = xml_advance();
  FUN_08006d14(auStack_218,0x200);
  if (iVar2 == 0) {
LAB_done:
    uVar3 = 1;
  }
  else {
    if (iVar2 == 4) {
      /* Close tag — check if it's the wrapper element */
      xml_get_tag_name(&DAT_08055ea0,auStack_218,0x200,0);
      iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f2e8);
      if (iVar2 != 0) goto LAB_done;
    }
    else if (iVar2 == 1) {
      /* Open tag — dispatch by name */
      iVar2 = xml_tag_match(&DAT_08055ea0,"configure");
      if (iVar2 != 0) {
        uVar3 = handle_configure();
        goto LAB_ret;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,"program");
      if (iVar2 != 0) {
        uVar3 = handle_program();
        goto LAB_ret;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f354);
      if (iVar2 != 0) {
        uVar3 = handle_read();
        goto LAB_ret;
      }
      iVar2 = xml_tag_match(&DAT_08055ea0,"getsha256digest");
      if (iVar2 != 0) {
        uVar3 = handler_digest_cmd();
        goto LAB_ret;
      }
      /* Ignore ?xml, data, patches wrapper tags silently */
      iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f3a8);
      if (iVar2 != 0) goto LAB_continue;
      iVar2 = xml_tag_match(&DAT_08055ea0,&DAT_0802f2e8);
      if (iVar2 != 0) goto LAB_continue;
      iVar2 = xml_tag_match(&DAT_08055ea0,"patches");
      if (iVar2 != 0) goto LAB_continue;
      /* Anything else: log warning and NAK */
      iVar2 = xml_get_tag_name(&DAT_08055ea0,auStack_218,0x200,0);
      if (iVar2 == 0) {
        firehose_log("WARNING: Ignoring unrecognized tag too long to display. Continuing.");
      }
      else {
        firehose_log("WARNING: Ignoring unrecognized tag \'%s\'. Continuing.",auStack_218);
      }
      uVar3 = handle_response(0);
      goto LAB_ret;
    }
LAB_continue:
    uVar3 = 0;
  }
LAB_ret:
  if (local_18 != iVar1) {
    stack_canary_fail();
  }
  return uVar3;
}

/* orig: 0x0802f838 dispatch_set_state — set dispatch execution state.
 * 0 = idle (state 1), nonzero = processing (state 2) */
void dispatch_set_state(param_1)
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
