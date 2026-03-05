/* handlers.c — Firehose command handlers (minimal: read/write only).
 *
 * Only handlers needed for full partition read/write:
 *   configure, program, read, getsha256digest (stub)
 *
 * Removed: benchmark, erase, firmwarewrite, getstorageinfo, nop, patch,
 *          peek, poke, power, setbootable, storagextras
 *
 * Source: src/fhprg/fhprg_8021ff0.c
 */
#include "firehose.h"

/*========================================================================
 * Extra globals used by handlers
 *========================================================================*/
extern uint DAT_0805845c;       /* disk sector size high word */
extern uint DAT_08055fb8;       /* buffer capacity low */
extern uint DAT_08055fbc;       /* buffer capacity high */
extern uint DAT_08057ff8;       /* max digest table size low */
extern uint DAT_08057ffc;       /* max digest table size high */
extern char DAT_08058480;       /* skip_write flag */
extern char DAT_08058481;       /* always_validate flag */
extern char DAT_08058482;       /* verbose flag */
extern int  DAT_08058484;       /* ack_raw_data_every_num_packets */
extern int  DAT_08055fd4;       /* storage device index offset */
extern volatile uint DAT_004a3000; /* memory-mapped timer register */
#define _DAT_004a3000 DAT_004a3000
extern char DAT_08055e90;       /* device extra state base */

/* orig: 0x08022178 handler_validate_attr */
int handler_validate_attr(param_1, param_2, param_3, param_4, param_5, param_6)
int param_1; undefined4 param_2; int param_3; undefined4 param_4; uint param_5; uint param_6;
{
  longlong lVar1;
  longlong lVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;

  param_1 = param_1 + param_3 * 4;
  uVar9 = *(uint *)(param_1 + -4);
  lVar1 = (ulonglong)uVar9 * (ulonglong)param_5;
  uVar8 = (uint)((ulonglong)lVar1 >> 0x20);
  lVar2 = (ulonglong)*(uint *)(param_1 + -8) * (ulonglong)param_6;
  uVar7 = (uint)((ulonglong)lVar2 >> 0x20);
  uVar4 = (uint)CARRY4((uint)lVar1,(uint)lVar2);
  uVar3 = uVar4 + uVar8;
  lVar1 = (ulonglong)param_6 * (ulonglong)uVar9;
  uVar6 = (uint)lVar1;
  uVar9 = uVar3 + uVar7;
  uVar4 = uVar9 + uVar6 >> 0x1e |
          ((uint)CARRY4(uVar4,uVar8) + (uint)CARRY4(uVar3,uVar7) + (uint)CARRY4(uVar9,uVar6)) * 4;
  uVar3 = (int)((ulonglong)lVar1 >> 0x20) * 4;
  iVar5 = uVar3 + uVar4;
  if (CARRY4(uVar3,uVar4)) {
    iVar5 = -1;
  }
  return iVar5;
}


/* orig: 0x08022440 handler_poll_usb */
int handler_poll_usb()
{
  do {
  } while (false);
  return _DAT_004a3000 * 0x1e + (_DAT_004a3000 >> 1);
}


/* handle_benchmark (0x08022650) — REMOVED */
/* handle_erase (0x08022ec8) — REMOVED */
/* handle_firmwarewrite (0x08022ffc) — REMOVED */
/* handle_getstorageinfo (0x080238b8) — REMOVED */
/* handle_nop (0x080239d0) — REMOVED */
/* handle_patch (0x080239dc) — REMOVED */
/* handle_peek (0x08023f64) — REMOVED */
/* handle_poke (0x08024134) — REMOVED */
/* handle_power (0x08024350) — REMOVED */
/* handle_setbootable (0x08024efc) — REMOVED */
/* handle_storagextras (0x08025054) — REMOVED */


/* orig: 0x08022a00 handle_configure */
undefined4 handle_configure()
{
  ulonglong uVar1;
  char *pcVar2;
  int iVar3;
  undefined4 uVar4;
  longlong lVar5;
  ulonglong uVar6;
  char local_26c [4];
  undefined4 local_268;
  undefined4 uStack_264;
  char *local_260;
  undefined4 local_25c;
  undefined4 uStack_258;
  char *local_254;
  undefined4 local_250;
  undefined4 uStack_24c;
  char *local_248;
  undefined4 uStack_244;
  undefined4 local_240;
  char *pcStack_23c;
  undefined4 local_238;
  undefined *puStack_234;
  int local_230;
  char local_22c [512];
  int local_2c;

  local_230 = DAT_0804cd58;
  local_2c = DAT_0804cd58;
  memset_zero(local_22c,0x200);
  lVar5 = CONCAT44(DAT_08055fbc,DAT_08055fb8);
  uVar1 = CONCAT44(DAT_08057ffc,DAT_08057ff8);
  uVar4 = 1;
  DAT_08058480 = 0;
  DAT_08058484 = 0;
  DAT_08058481 = 0;
  DAT_08058482 = 0;
LAB_08022be2:
  DAT_08055fbc = (undefined4)((ulonglong)lVar5 >> 0x20);
  DAT_08055fb8 = (undefined4)lVar5;
  DAT_08057ffc = (undefined4)(uVar1 >> 0x20);
  DAT_08057ff8 = (undefined4)uVar1;
  iVar3 = xml_advance(&DAT_08055ea0);
  if (iVar3 != 2) {
    firehose_log("logbuf@0x%08X fh@0x%08X",&DAT_08058028,&DAT_08054e90);
    local_238 = 0x73;
    puStack_234 = &DAT_08022e28;
    local_240 = 1;
    pcStack_23c = "TargetName";
    local_250 = 100;
    uStack_24c = 0x1000;
    local_248 = "Version";
    uStack_244 = 100;
    local_260 = "MaxPayloadSizeToTargetInBytesSupported";
    local_254 = "MaxXMLSizeInBytes";
    local_25c = 100;
    uStack_258 = 0x100000;
    local_268 = DAT_08055fb8;
    uStack_264 = DAT_08055fbc;
    uVar4 = send_xml_response(uVar4,8,"MinVersionSupported",100,1,"MemoryName",0x73,&DAT_08022ea0,
                         "MaxPayloadSizeFromTargetInBytes",100,0x1000,
                         "MaxPayloadSizeToTargetInBytes",0x74);
    if (local_2c != local_230) {
      stack_canary_fail();
    }
    return uVar4;
  }
  iVar3 = xml_attr_match(&DAT_08055ea0,"MaxPayloadSizeToTargetInBytes");
  if (iVar3 == 0) {
    iVar3 = xml_attr_match(&DAT_08055ea0,"MaxDigestTableSizeInBytes");
    if (iVar3 == 0) {
      iVar3 = xml_attr_match(&DAT_08055ea0,"ZlpAwareHost");
      if (iVar3 == 0) {
        iVar3 = xml_attr_match(&DAT_08055ea0,"SkipWrite");
        if (iVar3 == 0) {
          iVar3 = xml_attr_match(&DAT_08055ea0,"AckRawData");
          if (iVar3 == 0) {
            iVar3 = xml_attr_match(&DAT_08055ea0,"AckRawDataEveryNumPackets");
            if (iVar3 == 0) {
              iVar3 = xml_attr_match(&DAT_08055ea0,"AlwaysValidate");
              if (iVar3 == 0) {
                iVar3 = xml_attr_match(&DAT_08055ea0,"Verbose");
                uVar1 = CONCAT44(DAT_08057ffc,DAT_08057ff8);
                lVar5 = CONCAT44(DAT_08055fbc,DAT_08055fb8);
                if (iVar3 != 0) {
                  xml_get_attr_value(&DAT_08055ea0,local_22c,0x200,0);
                  uVar1 = CONCAT44(DAT_08057ffc,DAT_08057ff8);
                  lVar5 = CONCAT44(DAT_08055fbc,DAT_08055fb8);
                  if (local_22c[0] == '1') {
                    DAT_08058482 = 1;
                    uVar1 = CONCAT44(DAT_08057ffc,DAT_08057ff8);
                    lVar5 = CONCAT44(DAT_08055fbc,DAT_08055fb8);
                  }
                }
              }
              else {
                xml_get_attr_value(&DAT_08055ea0,local_22c,0x200,0);
                uVar1 = CONCAT44(DAT_08057ffc,DAT_08057ff8);
                lVar5 = CONCAT44(DAT_08055fbc,DAT_08055fb8);
                if (local_22c[0] == '1') {
                  DAT_08058481 = 1;
                  uVar1 = CONCAT44(DAT_08057ffc,DAT_08057ff8);
                  lVar5 = CONCAT44(DAT_08055fbc,DAT_08055fb8);
                }
              }
            }
            else {
              xml_get_attr_value(&DAT_08055ea0,local_22c,0x200,0);
              DAT_08058484 = parse_uint_from_str(local_22c,local_26c);
              uVar1 = CONCAT44(DAT_08057ffc,DAT_08057ff8);
              lVar5 = CONCAT44(DAT_08055fbc,DAT_08055fb8);
              if (local_26c[0] == '\0') {
                DAT_08058484 = 0;
                pcVar2 = "Failed to get ack_raw_data_every";
                goto LAB_08022b90;
              }
            }
          }
          else {
            xml_get_attr_value(&DAT_08055ea0,local_22c,0x200,0);
            uVar1 = CONCAT44(DAT_08057ffc,DAT_08057ff8);
            lVar5 = CONCAT44(DAT_08055fbc,DAT_08055fb8);
            if (local_22c[0] == '1') {
              DAT_08058484 = 1;
              uVar1 = CONCAT44(DAT_08057ffc,DAT_08057ff8);
              lVar5 = CONCAT44(DAT_08055fbc,DAT_08055fb8);
            }
          }
        }
        else {
          xml_get_attr_value(&DAT_08055ea0,local_22c,0x200,0);
          uVar1 = CONCAT44(DAT_08057ffc,DAT_08057ff8);
          lVar5 = CONCAT44(DAT_08055fbc,DAT_08055fb8);
          if (local_22c[0] == '1') {
            DAT_08058480 = 1;
            firehose_log("skipping write");
            uVar1 = CONCAT44(DAT_08057ffc,DAT_08057ff8);
            lVar5 = CONCAT44(DAT_08055fbc,DAT_08055fb8);
          }
        }
      }
      else {
        xml_get_attr_value(&DAT_08055ea0,local_22c,0x200,0);
        uVar1 = CONCAT44(DAT_08057ffc,DAT_08057ff8);
        lVar5 = CONCAT44(DAT_08055fbc,DAT_08055fb8);
        if (local_22c[0] == '0') {
          dispatch_set_state(0);
          uVar1 = CONCAT44(DAT_08057ffc,DAT_08057ff8);
          lVar5 = CONCAT44(DAT_08055fbc,DAT_08055fb8);
        }
      }
      goto LAB_08022be2;
    }
    xml_get_attr_value(&DAT_08055ea0,local_22c,0x200,0);
    uVar6 = parse_uint_from_str(local_22c,local_26c);
    lVar5 = CONCAT44(DAT_08055fbc,DAT_08055fb8);
    uVar1 = CONCAT44(DAT_08057ffc,DAT_08057ff8);
    if (local_26c[0] == '\0') {
      pcVar2 = "Failed to get max hash table size";
      goto LAB_08022b90;
    }
    if (uVar6 == 0) goto LAB_08022be2;
    if ((uint)-(int)(uVar6 >> 0x20) < (uint)((uint)uVar6 < 0x2001)) {
      uVar1 = uVar6 >> 5;
      lVar5 = CONCAT44(DAT_08055fbc,DAT_08055fb8);
      goto LAB_08022be2;
    }
    pcVar2 = "Host\'s hash buffer size is too large";
  }
  else {
    xml_get_attr_value(&DAT_08055ea0,local_22c,0x200,0);
    lVar5 = parse_uint_from_str(local_22c,local_26c);
    uVar1 = CONCAT44(DAT_08057ffc,DAT_08057ff8);
    if (local_26c[0] == '\0') {
      pcVar2 = "Failed to get max payload size";
    }
    else if (lVar5 == 0) {
      pcVar2 = "Host\'s payload to target size is zero";
    }
    else {
      if ((uint)-(int)((ulonglong)lVar5 >> 0x20) < (uint)((uint)lVar5 < 0x100001))
      goto LAB_08022be2;
      pcVar2 = "Host\'s payload to target size is too large";
    }
  }
LAB_08022b90:
  firehose_log(pcVar2);
  uVar4 = 0;
  uVar1 = CONCAT44(DAT_08057ffc,DAT_08057ff8);
  lVar5 = CONCAT44(DAT_08055fbc,DAT_08055fb8);
  goto LAB_08022be2;
}



/* orig: 0x080233ec handler_digest_cmd — STUB (v2 will implement fully).
 * The Go client sends getsha256digest for verification after read/write.
 * For now, just NAK it. */
undefined4 handler_digest_cmd()
{
    firehose_log("getsha256digest not implemented in minimal programmer");
    handle_response(0);
    return 0;
}


/* orig: 0x08024484 handle_program */
int handle_program()
{
  undefined1 *puVar1;
  longlong lVar2;
  longlong lVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  uint uVar7;
  uint uVar8;
  undefined4 uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  bool bVar16;
  longlong lVar17;
  undefined8 uVar18;
  longlong lVar19;
  int local_32c;
  undefined4 local_328;
  undefined4 uStack_324;
  undefined4 local_320;
  undefined *local_31c;
  char local_318 [4];
  int local_314;
  uint local_310;
  uint uStack_30c;
  uint local_308;
  uint uStack_304;
  int local_300;
  int local_2fc;
  undefined *local_2f4;
  int *local_2f0;
  char local_2ec [512];
  undefined1 auStack_ec [64];
  undefined1 auStack_ac [64];
  undefined1 auStack_6c [32];
  undefined1 auStack_4c [32];
  int local_2c;

  local_2fc = DAT_0804cd58;
  local_2c = DAT_0804cd58;
  memset_zero(local_2ec,0x200);
  iVar14 = 0x200;
  uVar13 = 0xffffffff;
  lVar2 = 0;
  local_310 = 0;
  uStack_30c = 0;
  memset_zero(auStack_ec,0x40);
  memset_zero(auStack_ac,0x40);
  local_314 = 0;
  local_300 = 1;
  memset_zero(auStack_6c,0x20);
  memset_zero(auStack_4c,0x20);
  bVar16 = true;
  iVar15 = 0;
  while (iVar4 = xml_advance(&DAT_08055ea0), iVar4 == 2) {
    iVar4 = xml_attr_match(&DAT_08055ea0,"start_sector");
    if (iVar4 == 0) {
      iVar4 = xml_attr_match(&DAT_08055ea0,"num_partition_sectors");
      if (iVar4 != 0) {
        puVar1 = auStack_ac;
        goto LAB_08024502;
      }
      iVar4 = xml_attr_match(&DAT_08055ea0,"physical_partition_number");
      if (iVar4 == 0) {
        iVar4 = xml_attr_match(&DAT_08055ea0,"SECTOR_SIZE_IN_BYTES");
        if (iVar4 == 0) {
          iVar4 = xml_attr_match(&DAT_08055ea0,"read_back_verify");
          if ((iVar4 != 0) && (xml_get_attr_value(&DAT_08055ea0,local_2ec,0x200,0), local_2ec[0] == '1'))
          {
            local_314 = 1;
          }
        }
        else {
          xml_get_attr_value(&DAT_08055ea0,local_2ec,0x200,0);
          iVar14 = parse_uint_from_str(local_2ec,local_318);
          if (local_318[0] == '\0') {
            pcVar6 = "Failed to get sector size";
            goto LAB_0802455e;
          }
        }
      }
      else {
        xml_get_attr_value(&DAT_08055ea0,local_2ec,0x200,0);
        uVar13 = parse_uint_from_str(local_2ec,local_318);
        if (local_318[0] == '\0') {
          pcVar6 = "Failed to get physical partition number";
LAB_0802455e:
          firehose_log(pcVar6);
          bVar16 = false;
        }
      }
    }
    else {
      puVar1 = auStack_ec;
LAB_08024502:
      xml_get_attr_value(&DAT_08055ea0,puVar1,0x40,0);
    }
  }
  if (bVar16) {
    if (uVar13 != 0xffffffff) {
      iVar4 = iVar14 >> 0x1f;
      if (DAT_08058458 == iVar14 && DAT_0805845c == iVar4) {
        local_2f4 = &DAT_08055e90;
        lVar17 = (longlong)(CONCAT44(DAT_08055fbc,DAT_08055fb8) / CONCAT44(iVar4,iVar14));
        uVar7 = (uint)((ulonglong)lVar17 >> 0x20);
        local_31c = &DAT_08058430;
        uVar18 = storage_select_partition(&DAT_08058430,uVar13 & 0xff);
        if ((int)uVar18 == 0) {
          firehose_log("Invalid physical partition %d",uVar13);
        }
        else {
          uVar18 = parse_sector_value(auStack_ec,(int)((ulonglong)uVar18 >> 0x20),0x40,0);
          if ((int)uVar18 == 0) {
            pcVar6 = "Failed to parse start sector";
          }
          else {
            iVar12 = parse_sector_value(auStack_ac,(int)((ulonglong)uVar18 >> 0x20),0x40,0);
            if (iVar12 != 0) {
              firehose_log("start %llu, num %llu",uStack_30c,0,0);
              send_xml_response(1,1,"rawmode",0x73);
              local_32c = 1;
              local_2f0 = &DAT_08058484;
              while( true ) {
                uStack_324 = (undefined4)((ulonglong)lVar2 >> 0x20);
                local_328 = (undefined4)lVar2;
                if (local_310 == 0 && uStack_30c == 0) break;
                lVar19 = CONCAT44(uStack_30c,local_310);
                if (uVar7 < uStack_30c || uStack_30c - uVar7 < (uint)((uint)lVar17 <= local_310)) {
                  lVar19 = lVar17;
                }
                uVar10 = (uint)(lVar19 * iVar14);
                uVar11 = (uint)((ulonglong)(lVar19 * iVar14) >> 0x20);
                iVar12 = usb_read_complete(&local_320);
                debug_log("toread %d read %d",uStack_304,uVar10,uVar11);
                uVar8 = uStack_304;
                uVar13 = local_308;
                if (iVar12 != 0) {
                  if (local_2f4[0x148] == '\x01') {
                    firehose_log("Encountered RAW data transport error in validation mode.");
                  }
                  else {
                    transport_error_loop(10);
                    send_xml_response(0,2,"rawmode",0x73);
                  }
                  goto LAB_08024840;
                }
                if ((uStack_304 < uVar11 || uVar11 - uStack_304 < (uint)(local_308 <= uVar10)) &&
                   (CONCAT44(uStack_304,local_308) % CONCAT44(iVar4,iVar14) == 0)) {
                  lVar19 = (longlong)(CONCAT44(uVar8,uVar13) / CONCAT44(iVar4,iVar14));
                  iVar12 = (int)((ulonglong)lVar19 >> 0x20);
                  uVar13 = (uint)lVar19;
                  debug_log("rx %llu start %llu",uStack_324,uVar13,iVar12);
                  if (lVar19 != CONCAT44(uStack_30c,local_310)) {
                    uVar8 = (uStack_30c - iVar12) - (uint)(local_310 < uVar13);
                    lVar3 = CONCAT44(uVar8,local_310 - uVar13);
                    if (uVar7 < uVar8 || uVar8 - uVar7 < (uint)((uint)lVar17 <= local_310 - uVar13))
                    {
                      lVar3 = lVar17;
                    }
                    transport_set_pending((int)(lVar3 * iVar14),(int)((ulonglong)(lVar3 * iVar14) >> 0x20));
                  }
                  if (local_32c == 1) {
                    if (DAT_08058480 == '\x01') goto LAB_080247c4;
                    uVar18 = storage_write_sectors(local_31c,local_320,local_328,uStack_324);
                    uVar9 = (undefined4)((ulonglong)uVar18 >> 0x20);
                    iVar5 = (int)uVar18;
                    if (iVar5 == 0) {
                      pcVar6 = "Write failed Sector %llu, Errno %d";
LAB_080247b6:
                      firehose_log(pcVar6,uVar9,local_328,uStack_324);
LAB_080247be:
                      local_32c = 0;
                    }
                    else {
                      if (iVar5 == 1) {
                        if (local_300 == 1) {
                          local_300 = 0;
                        }
                        else if (local_314 != 1) goto LAB_080247c4;
                        sha256_hash(local_320,local_308,auStack_6c);
                        storage_read_sectors(local_31c,local_320,local_328,uStack_324);
                        sha256_hash(local_320,local_308,auStack_4c);
                        uVar18 = memcmp(auStack_6c,auStack_4c,0x20);
                        uVar9 = (undefined4)((ulonglong)uVar18 >> 0x20);
                        if ((int)uVar18 != 0) {
                          pcVar6 = "Read back verify failed at sector %d,num sectors %d";
                          goto LAB_080247b6;
                        }
                      }
                      else if (iVar5 == 0) goto LAB_080247be;
LAB_080247c4:
                      lVar2 = lVar19 + lVar2;
                    }
                  }
                  bVar16 = local_310 < uVar13;
                  local_310 = local_310 - uVar13;
                  uStack_30c = (uStack_30c - iVar12) - (uint)bVar16;
                  if (DAT_08058482 == '\x01') {
                    firehose_log("%d bytes received, %d sectors more to go",local_310,local_308,
                                 uStack_304);
                  }
                  if ((*local_2f0 != 0) && (iVar15 = iVar15 + 1, *local_2f0 == iVar15)) {
                    handle_response(local_32c);
                    iVar15 = 0;
                  }
                }
              }
              firehose_log("Finished sector address %llu",0,local_328,uStack_324);
              send_xml_response(local_32c,1,"rawmode",0x73);
              if (local_32c == 1) {
                iVar12 = 0;
                goto LAB_08024840;
              }
              goto LAB_0802483a;
            }
            pcVar6 = "Failed to parse num_partition_sectors";
          }
          firehose_log(pcVar6);
        }
      }
      else {
        firehose_log("Sector size in XML %d does not match disk sector size %d",iVar14);
      }
      goto LAB_080245b2;
    }
  }
  else {
LAB_080245b2:
    handle_response(0);
  }
LAB_0802483a:
  iVar12 = 1;
LAB_08024840:
  if (local_2c != local_2fc) {
    stack_canary_fail();
  }
  return iVar12;
}



/* orig: 0x08024b04 handle_read */
undefined4 handle_read()
{
  bool bVar1;
  longlong lVar2;
  longlong lVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  undefined4 extraout_r1;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  longlong lVar10;
  uint local_298;
  undefined4 uStack_294;
  undefined4 local_290;
  undefined *local_28c;
  undefined8 local_288;
  uint local_280;
  undefined4 uStack_27c;
  char local_278 [4];
  int local_274;
  undefined *local_270;
  undefined1 auStack_26c [512];
  undefined1 auStack_6c [64];
  int local_2c;

  local_274 = DAT_0804cd58;
  local_2c = DAT_0804cd58;
  iVar8 = 0x200;
  memset_zero(auStack_26c,0x200);
  uVar9 = 0xffffffff;
  bVar1 = true;
  lVar10 = 0;
  local_298 = 0;
  uStack_294 = 0;
  local_280 = 0;
  uStack_27c = 0;
  memset_zero(auStack_6c,0x40);
LAB_08024be4:
  while( true ) {
    iVar5 = xml_advance(&DAT_08055ea0);
    if (iVar5 != 2) break;
    iVar5 = xml_attr_match(&DAT_08055ea0,"start_sector");
    if (iVar5 == 0) {
      iVar5 = xml_attr_match(&DAT_08055ea0,"num_partition_sectors");
      if (iVar5 == 0) {
        iVar5 = xml_attr_match(&DAT_08055ea0,"physical_partition_number");
        if (iVar5 == 0) goto LAB_08024bb6;
        xml_get_attr_value(&DAT_08055ea0,auStack_26c,0x200,0);
        uVar9 = parse_uint_from_str(auStack_26c,local_278);
        if (local_278[0] == '\0') {
          pcVar4 = "Failed to get physical_partition_number";
          goto LAB_08024bde;
        }
      }
      else {
        xml_get_attr_value(&DAT_08055ea0,auStack_26c,0x200,0);
        lVar10 = parse_uint_from_str(auStack_26c,local_278);
        if (local_278[0] == '\0') {
          pcVar4 = "Failed to get num_partition_sectors";
          goto LAB_08024bde;
        }
      }
    }
    else {
      xml_get_attr_value(&DAT_08055ea0,auStack_6c,0x40,0);
    }
  }
  if (bVar1) {
    if (uVar9 != 0xffffffff) {
      if (DAT_08058458 == iVar8 && DAT_0805845c == iVar8 >> 0x1f) {
        local_270 = &DAT_08055e90;
        local_288 = (longlong)(CONCAT44(DAT_08055fbc,DAT_08055fb8) / CONCAT44(iVar8 >> 0x1f,iVar8));
        local_28c = &DAT_08058430;
        iVar5 = storage_select_partition(&DAT_08058430,uVar9 & 0xff);
        if (iVar5 == 0) {
          firehose_log("Invalid physical partition %d",uVar9);
        }
        else {
          iVar5 = parse_sector_value(auStack_6c,&local_298,0x40,0,&local_298);
          if (iVar5 != 0) {
            send_xml_response(1,1,"rawmode",0x73,&DAT_08024e68);
            iVar5 = 1;
            lVar2 = local_288;
            while( true ) {
              _GHIDRA_FIELD(local_288, 4, uint) = (uint)((ulonglong)lVar2 >> 0x20);
              _GHIDRA_FIELD(local_288, 0, uint) = (uint)lVar2;
              uVar9 = (uint)((ulonglong)lVar10 >> 0x20);
              local_288 = lVar2;
              if (lVar10 == 0) break;
              if (uVar9 <= _GHIDRA_FIELD(local_288, 4, uint) &&
                  (uint)((uint)local_288 <= (uint)lVar10) <= uVar9 - _GHIDRA_FIELD(local_288, 4, uint)) {
                lVar2 = lVar10;
              }
              lVar3 = CONCAT44(uStack_294,&DAT_08054e90);
              local_290 = (&DAT_08054e90)[1 - *(int *)(local_270 + 0x144)];
              if (iVar5 == 1) {
                iVar6 = storage_read_sectors(local_28c,local_290,local_298,uStack_294,lVar2);
                lVar3 = CONCAT44(uStack_294,local_298);
                if (iVar6 == 0) {
                  local_280 = local_298;
                  uStack_27c = uStack_294;
                  iVar5 = 0;
                }
                else {
                  lVar3 = lVar2 + lVar3;
                  local_298 = (uint)lVar3;
                }
              }
              uStack_294 = (undefined4)((ulonglong)lVar3 >> 0x20);
              xml_send_and_wait(local_290,(int)lVar3,(int)(lVar2 * iVar8),
                           (int)((ulonglong)(lVar2 * iVar8) >> 0x20));
              lVar10 = lVar10 - lVar2;
              lVar2 = local_288;
            }
            if (iVar5 == 0) {
              firehose_log("Read failed at sector %llu",0,local_280,uStack_27c);
              uVar7 = extraout_r1;
            }
            else {
              uVar7 = 0;
            }
            firehose_log("Finished sector address %d",uVar7,local_298,uStack_294);
            send_xml_response(iVar5,1,"rawmode",0x73,"false");
            if (iVar5 == 1) {
              uVar7 = 0;
              goto LAB_08024d3c;
            }
            goto LAB_08024d36;
          }
          firehose_log("Failed to parse start sector");
        }
      }
      else {
        firehose_log("Sector size in XML %d does not match disk sector size %d",iVar8,DAT_08058458);
      }
      goto LAB_08024c12;
    }
  }
  else {
LAB_08024c12:
    handle_response(0);
  }
LAB_08024d36:
  uVar7 = 1;
LAB_08024d3c:
  if (local_2c != local_274) {
    stack_canary_fail();
  }
  return uVar7;
LAB_08024bb6:
  iVar5 = xml_attr_match(&DAT_08055ea0,"SECTOR_SIZE_IN_BYTES");
  if (iVar5 != 0) {
    xml_get_attr_value(&DAT_08055ea0,auStack_26c,0x200,0);
    iVar8 = parse_uint_from_str(auStack_26c,local_278);
    if (local_278[0] == '\0') {
      pcVar4 = "Failed to get sector_size_in_bytes";
LAB_08024bde:
      firehose_log(pcVar4);
      bVar1 = false;
    }
  }
  goto LAB_08024be4;
}
