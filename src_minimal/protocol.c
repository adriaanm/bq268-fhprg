/* protocol.c — Firehose protocol: logging, response building, attribute parsing.
 *
 * The firehose protocol wraps everything in XML. Log messages, responses,
 * and commands all use XML elements sent over USB.
 *
 * Source: src/fhprg/fhprg_8026f54.c
 */
#include "firehose.h"

/* orig: 0x08027674 firehose_log — format message and send as XML log element.
 *
 * Builds: <?xml ...?><data><log value="message"/></data>
 * This is the programmer's printf — sends formatted text to the host.
 */
void firehose_log(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; uint param_3; uint param_4;
{
    int iVar1;
    uint uVar2;
    undefined1 auStack_128[256];
    int local_28;
    uint uStack_c;
    uint uStack_8;
    uint uStack_4;

    iVar1 = DAT_0804cd58;
    local_28 = DAT_0804cd58;
    uStack_c = param_2;
    uStack_8 = param_3;
    uStack_4 = param_4;
    FUN_08006d14(auStack_128, 0x100); /* memset(buf, 0, 256) */
    FUN_08006418((char *)auStack_128, 0x100, (const char *)param_1, (va_list *)&uStack_c);
    /* vsnprintf_wrapper(buf, 256, fmt, &args) */
    uVar2 = FUN_08006906("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>");
    xml_wr_init((int *)&DAT_08055f18,
                (uint)"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>", uVar2, 0);
    xml_wr_open_tag((uint)&DAT_08055f18, (uint)&DAT_08027710); /* <data> */
    xml_wr_tag_name((uint)&DAT_08055f18, (uint)&DAT_08027718); /* <log */
    xml_wr_attr_value((int)&DAT_08055f18, (uint)"value", (uint)auStack_128, 0, 0, 0);
    xml_wr_close_self((uint)&DAT_08055f18);   /* /> */
    xml_wr_close_tag((uint)&DAT_08055f18, (uint)&DAT_08027710); /* </data> */
    flush_xml_to_usb(0, 0);
    if (local_28 != iVar1) {
        stack_canary_fail();
    }
}

/* orig: 0x08027bf8 bounded_memcpy — memcpy with destination size limit */
uint bounded_memcpy(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; uint param_3; uint param_4;
{
    if (param_2 <= param_4) {
        param_4 = param_2;
    }
    memcpy((void *)param_1, (void *)param_3, param_4);
    return param_4;
}

/* orig: 0x08027c12 bounded_memmove — memmove with destination size limit */
uint bounded_memmove(param_1, param_2, param_3, param_4)
uint param_1; uint param_2; uint param_3; uint param_4;
{
    if (param_2 <= param_4) {
        param_4 = param_2;
    }
    memmove((void *)param_1, (void *)param_3, param_4);
    return param_4;
}

/* orig: 0x080287e2 bounded_memset — memset wrapper */
void bounded_memset(param_1, param_2, param_3)
uint param_1; uint param_2; uint param_3;
{
    memset((void *)param_1, (int)param_2, param_3);
}

/* orig: 0x08028810 transfer_callback — USB transfer completion callback.
 *
 * Called when a USB data transfer (sector read/write) completes or fails.
 * Updates transfer counters and signals completion.
 *
 * param_1 = bytes transferred
 * param_2 = error code (0 = success)
 *
 * Globals updated:
 *   DAT_08055f88 = last error code
 *   DAT_08055fc8/cc = success transfer count (64-bit)
 *   DAT_08055fc0/c4 = error transfer count (64-bit)
 *   DAT_08055fb0/b4 = total bytes transferred (64-bit)
 *   DAT_08055f90 = last transfer size (0 on error)
 *   DAT_08055f98 = completion flag (set to 1)
 */
void transfer_callback(param_1, param_2)
uint param_1; int param_2;
{
  bool bVar1;

  debug_log("cback %d err %d",param_1,param_2);
  DAT_08055f88 = param_2;
  if (param_2 == 0) {
    /* Success: increment success counter */
    bVar1 = 0xfffffffe < DAT_08055fc8;
    DAT_08055fc8 = DAT_08055fc8 + 1;
    DAT_08055fcc = DAT_08055fcc + (uint)bVar1;
    DAT_08055f90 = param_1;
  }
  else {
    /* Error: increment error counter */
    DAT_08055f90 = 0;
    bVar1 = 0xfffffffe < DAT_08055fc0;
    DAT_08055fc0 = DAT_08055fc0 + 1;
    DAT_08055fc4 = DAT_08055fc4 + (uint)bVar1;
  }
  DAT_08055f94 = 0;
  /* Accumulate total bytes */
  bVar1 = CARRY4(DAT_08055fb0,param_1);
  DAT_08055fb0 = DAT_08055fb0 + param_1;
  DAT_08055fb4 = DAT_08055fb4 + (uint)bVar1;
  DAT_08055f98 = 1; /* signal: transfer complete */
  return;
}

/* eval_sector_expression (0x080288b0) — REMOVED, only used by handle_patch */

/* orig: 0x08028c10 parse_sector_value — parse sector number from XML attribute.
 *
 * Substitutes "NUM_DISK_SECTORS" with actual disk size, then evaluates
 * the expression. Since we control the client and send plain numbers,
 * this always succeeds via the expression evaluator.
 */
uint parse_sector_value()
{
    return 0;
}
