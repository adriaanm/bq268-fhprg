/* handlers.c — Firehose command handlers.
 *
 * These are the protocol-level functions that implement each firehose XML
 * command (configure, program, read, erase, etc.).  They parse XML attributes,
 * interact with storage, and send responses.
 *
 * Source: src/fhprg/fhprg_8021ff0.c
 */
#include "firehose.h"

/*========================================================================
 * Extra globals used by handlers (provided by data blob at link time)
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
extern char DAT_08022e28;       /* target name string */
extern char DAT_08022ea0;       /* memory name string */
extern char DAT_08023360;       /* "false" string for rawmode */
extern char DAT_0802387c;       /* "%s" format for digest prefix */
extern char DAT_08023880;       /* "%08X" format for CRC digest */
extern char DAT_080238b0;       /* "%02X" format for hash byte */
extern char DAT_08023e4c;       /* "DISK" filename compare string */
extern char DAT_08023e98;       /* format string for partition info */
extern char DAT_08023eb4;       /* attribute name string */
extern char DAT_08024130;       /* "%s" format for peek output */
extern char DAT_08024444;       /* "off" string for power command */
extern char DAT_08024e68;       /* "true" string for rawmode */
extern uint DAT_004a3000;       /* memory-mapped timer register */
#define _DAT_004a3000 DAT_004a3000
extern char DAT_08055e90;       /* device extra state base */
extern uint DAT_0803d71c;       /* CRC32 lookup table */

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


/* orig: 0x08022650 handle_benchmark */
undefined4 handle_benchmark()
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  bool bVar14;
  undefined8 uVar15;
  uint local_260;
  undefined1 auStack_24c [4];
  byte local_248 [512];
  undefined1 auStack_48 [32];
  int local_28;

  iVar1 = DAT_0804cd58;
  local_28 = DAT_0804cd58;
  FUN_08006d14(local_248,0x200);
  FUN_08006d14(auStack_48,0x20);
  uVar5 = DAT_0805845c;
  uVar4 = DAT_08058458;
  uVar3 = DAT_08055fbc;
  uVar2 = DAT_08055fb8;
  uVar9 = DAT_08054e90;
  uVar10 = 0x35a0;
  while (iVar8 = xml_advance(&DAT_08055ea0,uVar10), iVar8 == 2) {
    iVar8 = xml_attr_match(&DAT_08055ea0,"TestWritePerformance");
    if ((iVar8 != 0) && (xml_get_attr_value(&DAT_08055ea0,local_248,0x200,0), local_248[0] == 0x31)) {
      firehose_log("Going to test writes for lengths %llu to %llu for %llu trials. This can take a while."
                   ,uVar2,uVar4,uVar5,uVar2,uVar3,1000,0);
      storage_select_partition(&DAT_08058430,0);
      uVar15 = FUN_080060c0(uVar2,uVar3,uVar4,uVar5);
      storage_read_sectors(&DAT_08058430,uVar9,0,0,uVar15);
      uVar10 = uVar4;
      for (uVar12 = uVar5; uVar12 < uVar3 || uVar3 - uVar12 < (uint)(uVar10 <= uVar2);
          uVar12 = uVar12 * 2 + (uint)bVar14) {
        iVar8 = handler_poll_usb(0,uVar2 - uVar10);
        uVar13 = 0;
        uVar11 = 0;
        while( true ) {
          if (uVar11 != 0 || uVar11 < (999 < uVar13)) break;
          uVar15 = FUN_080060c0(uVar10,uVar12,uVar4,uVar5);
          iVar6 = storage_write_sectors(&DAT_08058430,uVar9,0,0,uVar15,auStack_24c);
          if (iVar6 != 1) {
            firehose_log("Failure in write during perf testing");
          }
          bVar14 = 0xfffffffe < uVar13;
          uVar13 = uVar13 + 1;
          uVar11 = uVar11 + bVar14;
        }
        iVar6 = handler_poll_usb(uVar13 - 1000,uVar11 - (999 >= uVar13));
        uVar15 = FUN_080060c0(iVar6 - iVar8,iVar6 - iVar8 >> 0x1f,uVar13,uVar11);
        firehose_log("Writing %llu bytes %d us",(int)((ulonglong)uVar15 >> 0x20),uVar10,uVar12,
                     (int)uVar15);
        bVar14 = CARRY4(uVar10,uVar10);
        uVar10 = uVar10 * 2;
      }
    }
    iVar8 = xml_attr_match(&DAT_08055ea0,"TestReadPerformance");
    if (iVar8 == 0) {
      uVar15 = xml_attr_match(&DAT_08055ea0,"TestDigestPerformance");
      uVar10 = (uint)((ulonglong)uVar15 >> 0x20);
      if ((int)uVar15 != 0) {
        xml_get_attr_value(&DAT_08055ea0,local_248,0x200,0);
        uVar10 = (uint)local_248[0];
        if (uVar10 == 0x31) {
          uVar12 = uVar4;
          for (local_260 = uVar5; uVar10 = uVar2 - uVar12,
              local_260 < uVar3 || uVar3 - local_260 < (uint)(uVar12 <= uVar2);
              local_260 = local_260 * 2 + (uint)bVar14) {
            iVar8 = 0;
            uVar10 = 0;
            for (uVar11 = 0; uVar11 == 0 && (999 < uVar10) <= uVar11; uVar11 = uVar11 + bVar14) {
              iVar6 = handler_poll_usb(uVar11 - (999 >= uVar10));
              sha256_hash(uVar9,uVar12,auStack_48);
              iVar7 = handler_poll_usb();
              bVar14 = 0xfffffffe < uVar10;
              uVar10 = uVar10 + 1;
              iVar8 = iVar8 + (iVar7 - iVar6);
            }
            uVar15 = FUN_080060c0(iVar8,iVar8 >> 0x1f,uVar10,uVar11);
            firehose_log("Hashing %llu bytes %d us",(int)((ulonglong)uVar15 >> 0x20),uVar12,
                         local_260,(int)uVar15);
            bVar14 = CARRY4(uVar12,uVar12);
            uVar12 = uVar12 * 2;
          }
        }
      }
    }
    else {
      xml_get_attr_value(&DAT_08055ea0,local_248,0x200,0);
      uVar10 = (uint)local_248[0];
      if (uVar10 == 0x31) {
        firehose_log("Going to test reads for lengths %llu to %llu for %llu trials. This can take a while."
                     ,uVar2,uVar4,uVar5,uVar2,uVar3,1000,0);
        storage_select_partition(&DAT_08058430,0);
        uVar12 = uVar4;
        for (uVar11 = uVar5; uVar10 = uVar2 - uVar12,
            uVar11 < uVar3 || uVar3 - uVar11 < (uint)(uVar12 <= uVar2);
            uVar11 = uVar11 * 2 + (uint)bVar14) {
          iVar8 = handler_poll_usb();
          uVar10 = 0;
          uVar13 = 0;
          while( true ) {
            if (uVar13 != 0 || uVar13 < (999 < uVar10)) break;
            uVar15 = FUN_080060c0(uVar12,uVar11,uVar4,uVar5);
            iVar6 = storage_read_sectors(&DAT_08058430,uVar9,0,0,uVar15);
            if (iVar6 != 1) {
              firehose_log("Failure in read during perf testing");
            }
            bVar14 = 0xfffffffe < uVar10;
            uVar10 = uVar10 + 1;
            uVar13 = uVar13 + bVar14;
          }
          iVar6 = handler_poll_usb(uVar10 - 1000,uVar13 - (999 >= uVar10));
          uVar15 = FUN_080060c0(iVar6 - iVar8,iVar6 - iVar8 >> 0x1f,uVar10,uVar13);
          firehose_log("Reading %llu bytes %d us",(int)((ulonglong)uVar15 >> 0x20),uVar12,uVar11,
                       (int)uVar15);
          bVar14 = CARRY4(uVar12,uVar12);
          uVar12 = uVar12 * 2;
        }
      }
    }
  }
  uVar9 = handle_response(1);
  if (local_28 != iVar1) {
    stack_canary_fail();
  }
  return uVar9;
}


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
  FUN_08006d14(local_22c,0x200);
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


/* orig: 0x08022ec8 handle_erase */
undefined4 handle_erase()
{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  char local_220 [4];
  undefined1 auStack_21c [512];
  int local_1c;

  iVar2 = DAT_0804cd58;
  local_1c = DAT_0804cd58;
  FUN_08006d14(auStack_21c,0x200);
  bVar1 = true;
  uVar4 = 0xffffffff;
  while (iVar3 = xml_advance(&DAT_08055ea0), iVar3 == 2) {
    iVar3 = xml_attr_match(&DAT_08055ea0,"storagedrive");
    if (iVar3 != 0) {
      xml_get_attr_value(&DAT_08055ea0,auStack_21c,0x200,0);
      uVar4 = parse_uint_from_str(auStack_21c,local_220);
      if (local_220[0] == '\0') {
        firehose_log("Failed to get storage drive number");
        bVar1 = false;
      }
    }
  }
  if (bVar1) {
    if (uVar4 == 0xffffffff) {
      firehose_log("No storage drive number");
    }
    else {
      iVar3 = storage_select_partition(&DAT_08058430,uVar4 & 0xff);
      if (iVar3 != 0) {
        iVar3 = storage_erase_partition(&DAT_08058430);
        handle_response(iVar3 == 1);
        if (iVar3 == 1) {
          uVar5 = 0;
        }
        else {
          uVar5 = 3;
        }
        goto LAB_08022f50;
      }
      firehose_log("Invalid physical partition %d",uVar4);
    }
  }
  handle_response(0);
  uVar5 = 1;
LAB_08022f50:
  if (local_1c != iVar2) {
    stack_canary_fail();
  }
  return uVar5;
}


/* orig: 0x08022ffc handle_firmwarewrite */
undefined4 handle_firmwarewrite()
{
  bool bVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  longlong lVar8;
  longlong lVar9;
  undefined8 uVar10;
  uint local_240;
  uint uStack_23c;
  char local_238 [4];
  undefined4 local_234;
  undefined1 auStack_230 [4];
  undefined1 auStack_22c [512];
  int local_2c;

  iVar2 = DAT_0804cd58;
  local_2c = DAT_0804cd58;
  lVar8 = 0;
  local_240 = 0;
  uStack_23c = 0;
  lVar9 = 0;
  FUN_08006d14(auStack_22c,0x200);
  bVar1 = true;
  while (uVar7 = (undefined4)((ulonglong)lVar9 >> 0x20), uVar10 = xml_advance(&DAT_08055ea0),
        (int)uVar10 == 2) {
    iVar4 = xml_attr_match(&DAT_08055ea0,"SECTOR_SIZE_IN_BYTES");
    if (iVar4 != 0) {
      xml_get_attr_value(&DAT_08055ea0,auStack_22c,0x200,0);
      lVar8 = parse_uint_from_str(auStack_22c,local_238);
      if (local_238[0] == '\0') {
        firehose_log("Failed to get Sector size value");
        bVar1 = false;
      }
    }
    iVar4 = xml_attr_match(&DAT_08055ea0,"num_partition_sectors");
    if (iVar4 != 0) {
      xml_get_attr_value(&DAT_08055ea0,auStack_22c,0x200,0);
      lVar9 = parse_uint_from_str(auStack_22c,local_238);
      if (local_238[0] == '\0') {
        firehose_log("Failed to get Number of sectors to write");
        bVar1 = false;
      }
    }
  }
  if (bVar1) {
    firehose_log("firmwarewrite cmd: Sector size %llu",(int)((ulonglong)uVar10 >> 0x20),(int)lVar8,
                 (int)((ulonglong)lVar8 >> 0x20));
    firehose_log("firmwarewrite cmd: Number of Sectors %llu",extraout_r1,(int)lVar9,uVar7);
    if (lVar8 != CONCAT44(DAT_0805845c,DAT_08058458)) {
      firehose_log("Disk sector size does not match xml\n");
      pcVar3 = "Disk sector size :%llu XML gave:%llu";
      uVar7 = extraout_r1_00;
      uVar5 = DAT_08058458;
      uVar6 = DAT_0805845c;
LAB_0802310c:
      firehose_log(pcVar3,uVar7,uVar5,uVar6);
      goto LAB_080230ce;
    }
    lVar8 = lVar8 * lVar9;
    uVar5 = (uint)lVar8;
    uVar6 = (uint)((ulonglong)lVar8 >> 0x20);
    firehose_log("Bytes to read from channel: %llu");
    if (lVar8 == 0) {
      firehose_log("Firmware Binary must be non-zero in size. Check binary");
      goto LAB_080230ce;
    }
    if (DAT_08055fbc <= uVar6 && (uint)(uVar5 <= DAT_08055fb8) <= DAT_08055fbc - uVar6) {
      pcVar3 = "Bytes to read > buffer capacity of %llubytes";
      uVar7 = extraout_r1_01;
      uVar5 = DAT_08055fb8;
      uVar6 = DAT_08055fbc;
      goto LAB_0802310c;
    }
    send_xml_response(1,1,"rawmode",0x73,&DAT_08023360);
    iVar4 = usb_read_complete(&local_234,extraout_r1_02,uVar5,uVar6,&local_240);
    if (iVar4 == 0) {
      if (uVar5 != local_240 || (uVar6 ^ uStack_23c) != 0) {
        firehose_log("Read Error.Bytes expected:%llu,read:%llu",uVar6 ^ uStack_23c,uVar5,uVar6,
                     local_240,uStack_23c);
        goto LAB_080231a4;
      }
      if (bVar1) {
        firehose_log("Channel read %llu bytes");
      }
      iVar4 = storage_fw_update(&DAT_08058430,local_234,(int)lVar9,uVar7,auStack_230);
      if (iVar4 == 0) goto LAB_080231a4;
      iVar4 = 1;
    }
    else {
      firehose_log("Failed to read full FW binary. Read %llu Bytes");
LAB_080231a4:
      iVar4 = 0;
    }
    send_xml_response(iVar4,1,"rawmode",0x73,"false");
    if (iVar4 != 0) {
      uVar7 = 0;
      goto LAB_08023190;
    }
  }
  else {
LAB_080230ce:
    handle_response(0);
  }
  uVar7 = 1;
LAB_08023190:
  if (local_2c != iVar2) {
    stack_canary_fail();
  }
  return uVar7;
}


/* orig: 0x080233ec handler_digest_cmd */
undefined4 handler_digest_cmd(param_1)
int param_1;
{
  longlong lVar1;
  bool bVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  longlong lVar7;
  longlong lVar8;
  int iVar9;
  char *pcVar10;
  undefined4 extraout_r1;
  undefined4 uVar11;
  int iVar12;
  ulonglong uVar13;
  undefined8 uVar14;
  uint uVar15;
  undefined1 auStack_3b0 [72];
  undefined1 auStack_368 [64];
  undefined1 auStack_328 [4];
  uint local_324;
  undefined8 local_320;
  char local_318 [4];
  uint local_314;
  undefined4 local_310;
  undefined4 local_30c;
  undefined1 *local_308;
  undefined1 *puStack_304;
  undefined8 local_300;
  int local_2f8;
  undefined4 local_2f4;
  undefined4 uStack_2f0;
  undefined4 local_2ec;
  undefined4 uStack_2e8;
  undefined *local_2e4;
  uint local_2e0;
  uint uStack_2dc;
  int local_2d8;
  undefined1 auStack_2d4 [512];
  char acStack_d4 [72];
  undefined1 auStack_8c [64];
  undefined1 auStack_4c [32];
  int local_2c;
  int local_28;

  local_2f8 = DAT_0804cd58;
  local_2c = DAT_0804cd58;
  local_28 = param_1;
  FUN_08006d14(auStack_2d4,0x200);
  local_324 = 0x200;
  uVar13 = 0;
  bVar2 = true;
  _GHIDRA_FIELD(local_320, 0, uint) = 0;
  _GHIDRA_FIELD(local_320, 4, uint) = 0;
  uVar15 = 0xffffffff;
  FUN_08006d14(auStack_8c,0x40);
  iVar12 = 0;
  FUN_08006d14(auStack_4c,0x20);
  FUN_08006d14(acStack_d4,0x48);
  local_314 = 0;
  local_30c = 0;
  local_2e0 = 0x4000;
  uStack_2dc = 0;
LAB_080234ee:
  while( true ) {
    iVar9 = xml_advance(&DAT_08055ea0);
    if (iVar9 != 2) break;
    iVar9 = xml_attr_match(&DAT_08055ea0,"start_sector");
    if (iVar9 == 0) {
      iVar9 = xml_attr_match(&DAT_08055ea0,"num_partition_sectors");
      if (iVar9 == 0) {
        iVar9 = xml_attr_match(&DAT_08055ea0,"physical_partition_number");
        if (iVar9 == 0) goto LAB_080234c0;
        xml_get_attr_value(&DAT_08055ea0,auStack_2d4,0x200,0);
        uVar15 = parse_uint_from_str(auStack_2d4,local_318);
        if (local_318[0] == '\0') {
          pcVar10 = "Failed to get physical_partition_number";
          goto LAB_080234e8;
        }
      }
      else {
        xml_get_attr_value(&DAT_08055ea0,auStack_2d4,0x200,0);
        uVar13 = parse_uint_from_str(auStack_2d4,local_318);
        if (local_318[0] == '\0') {
          pcVar10 = "Failed to get num_partition_sectors";
          goto LAB_080234e8;
        }
      }
    }
    else {
      xml_get_attr_value(&DAT_08055ea0,auStack_8c,0x40,0);
    }
  }
  if (bVar2) {
    if (uVar15 != 0xffffffff) {
      if (local_324 == DAT_08058458 && DAT_0805845c == (int)local_324 >> 0x1f) {
        local_300 = FUN_080060c0(DAT_08055fb8,DAT_08055fbc,local_324,(int)local_324 >> 0x1f);
        local_2e4 = &DAT_08058430;
        uVar14 = storage_select_partition(&DAT_08058430,uVar15 & 0xff);
        if ((int)uVar14 == 0) {
          firehose_log("Invalid physical partition %d",uVar15);
        }
        else {
          iVar9 = parse_sector_value(auStack_8c,(int)((ulonglong)uVar14 >> 0x20),0x40,0,&local_320);
          if (iVar9 != 0) {
            if (local_28 == 0) {
              FUN_080364e4(auStack_3b0);
            }
            local_310 = (&DAT_08054e90)[1 - DAT_08055fd4];
            local_308 = auStack_328;
            puStack_304 = auStack_368;
            local_2f4 = _GHIDRA_FIELD(local_320, 4, uint);
            uStack_2f0 = (undefined4)local_320;
            uVar5 = uVar13;
            uVar6 = local_300;
            lVar7 = CONCAT44(_GHIDRA_FIELD(local_320, 4, uint),(undefined4)local_320);
            lVar8 = 0;
            while( true ) {
              _GHIDRA_FIELD(local_320, 4, uint) = (undefined4)((ulonglong)lVar7 >> 0x20);
              _GHIDRA_FIELD(local_320, 0, uint) = (undefined4)lVar7;
              _GHIDRA_FIELD(local_300, 4, uint) = (uint)(uVar6 >> 0x20);
              _GHIDRA_FIELD(local_300, 0, uint) = (uint)uVar6;
              local_2ec = (undefined4)(uVar5 >> 0x20);
              uStack_2e8 = (undefined4)uVar5;
              uVar15 = (uint)(uVar13 >> 0x20);
              local_300 = uVar6;
              if (uVar13 == 0) break;
              if (uVar15 <= _GHIDRA_FIELD(local_300, 4, uint) &&
                  (uint)((uint)local_300 <= (uint)uVar13) <= uVar15 - _GHIDRA_FIELD(local_300, 4, uint)) {
                uVar6 = uVar13;
              }
              lVar1 = (uVar6 & 0xffffffff) * (ulonglong)local_324;
              uVar11 = (undefined4)lVar1;
              local_2d8 = (int)uVar6 * ((int)local_324 >> 0x1f) +
                          (int)(uVar6 >> 0x20) * local_324 + (int)((ulonglong)lVar1 >> 0x20);
              iVar12 = storage_read_sectors(local_2e4,local_310,(undefined4)local_320,_GHIDRA_FIELD(local_320, 4, uint),uVar6)
              ;
              local_320 = lVar7;
              if (iVar12 == 0) {
                pcVar10 = "emmc read failed";
                goto LAB_080236a2;
              }
              local_320 = uVar6 + local_320;
              if (local_28 == 0) {
                FUN_08036ee8(auStack_3b0,puStack_304,local_308,local_310,uVar11);
                uVar14 = CONCAT44(extraout_r1,local_30c);
              }
              else {
                uVar14 = FUN_08019a70(local_310,(int)local_320,uVar11,local_2d8,local_30c);
              }
              local_30c = (undefined4)uVar14;
              lVar1 = uVar13 - uVar6;
              uVar4 = uVar13 - uVar6;
              uVar3 = uVar13 - uVar6;
              lVar8 = uVar6 + lVar8;
              uVar15 = (uint)((ulonglong)lVar8 >> 0x20);
              uVar13 = uVar13 - uVar6;
              uVar5 = CONCAT44(local_2ec,uStack_2e8);
              uVar6 = local_300;
              lVar7 = local_320;
              if (uStack_2dc < uVar15 || uVar15 - uStack_2dc < (uint)(local_2e0 <= (uint)lVar8)) {
                uVar13 = uVar3;
                uVar5 = CONCAT44(local_2ec,uStack_2e8);
                lVar8 = 0;
                if (lVar1 != 0) {
                  firehose_log("%llu sectors more to hash",(int)((ulonglong)uVar14 >> 0x20),
                               (int)lVar1,(int)((ulonglong)lVar1 >> 0x20));
                  uVar5 = CONCAT44(local_2ec,uStack_2e8);
                  uVar13 = uVar4;
                  uVar6 = local_300;
                  lVar7 = local_320;
                  lVar8 = 0;
                }
              }
            }
            if (iVar12 == 1) {
              local_320 = lVar7;
              if (local_28 == 0) {
                FUN_0803649c(auStack_3b0,puStack_304,local_308,auStack_4c);
                uVar5 = CONCAT44(local_2ec,uStack_2e8);
              }
              local_2ec = (undefined4)(uVar5 >> 0x20);
              uStack_2e8 = (undefined4)uVar5;
              uVar15 = snprintf_buf(acStack_d4,0x48,&DAT_0802387c,"Digest ");
              if (local_28 == 0) {
                for (; (uVar15 < 0x48 && (local_314 < 0x20)); local_314 = local_314 + 1) {
                  iVar12 = snprintf_buf(acStack_d4 + uVar15,0x48 - uVar15,&DAT_080238b0,
                                        auStack_4c[local_314]);
                  uVar15 = uVar15 + iVar12;
                }
              }
              else {
                snprintf_buf(acStack_d4 + uVar15,0x48 - uVar15,&DAT_08023880,local_30c);
              }
              firehose_log("Hash start sector %llu num sectors %llu",local_2ec,uStack_2f0,local_2f4,
                           uStack_2e8,local_2ec);
              pcVar10 = acStack_d4;
LAB_080236a2:
              firehose_log(pcVar10);
              uVar5 = CONCAT44(local_2ec,uStack_2e8);
              uVar6 = local_300;
              lVar7 = local_320;
            }
            local_2ec = (undefined4)(uVar5 >> 0x20);
            uStack_2e8 = (undefined4)uVar5;
            local_300 = uVar6;
            local_320 = lVar7;
            handle_response(1);
            uVar11 = 0;
            goto LAB_080236ae;
          }
          firehose_log("Failed to parse start sector");
        }
      }
      else {
        firehose_log("Sector size in XML %d does not match disk sector size %d",local_324,
                     DAT_08058458,DAT_0805845c);
      }
      goto LAB_08023522;
    }
  }
  else {
LAB_08023522:
    handle_response(0);
  }
  uVar11 = 1;
LAB_080236ae:
  if (local_2c != local_2f8) {
    stack_canary_fail();
  }
  return uVar11;
LAB_080234c0:
  iVar9 = xml_attr_match(&DAT_08055ea0,"SECTOR_SIZE_IN_BYTES");
  if (iVar9 != 0) {
    xml_get_attr_value(&DAT_08055ea0,auStack_2d4,0x200,0);
    local_324 = parse_uint_from_str(auStack_2d4,local_318);
    if (local_318[0] == '\0') {
      pcVar10 = "Failed to get sector_size_in_bytes";
LAB_080234e8:
      firehose_log(pcVar10);
      bVar2 = false;
    }
  }
  goto LAB_080234ee;
}


/* orig: 0x080238b8 handle_getstorageinfo */
undefined4 handle_getstorageinfo()
{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  char local_220 [4];
  undefined1 auStack_21c [512];
  int local_1c;

  iVar2 = DAT_0804cd58;
  local_1c = DAT_0804cd58;
  FUN_08006d14(auStack_21c,0x200);
  bVar1 = true;
  uVar4 = 0xffffffff;
  while (iVar3 = xml_advance(&DAT_08055ea0), iVar3 == 2) {
    iVar3 = xml_attr_match(&DAT_08055ea0,"physical_partition_number");
    if (iVar3 != 0) {
      xml_get_attr_value(&DAT_08055ea0,auStack_21c,0x200,0);
      uVar4 = parse_uint_from_str(auStack_21c,local_220);
      if (local_220[0] == '\0') {
        firehose_log("Failed to get physical partition number");
        bVar1 = false;
      }
    }
  }
  if ((uVar4 != 0xffffffff) && (bVar1)) {
    iVar3 = storage_select_partition(&DAT_08058430,uVar4 & 0xff);
    if (iVar3 == 0) {
      firehose_log("Invalid physical partition %d",uVar4);
    }
    else {
      iVar3 = storage_log_partition_info(&DAT_08058430);
      if (iVar3 != 0) {
        handle_response(1);
        uVar5 = 0;
        goto LAB_08023938;
      }
    }
  }
  handle_response(0);
  uVar5 = 1;
LAB_08023938:
  if (local_1c != iVar2) {
    stack_canary_fail();
  }
  return uVar5;
}


/* orig: 0x080239d0 handle_nop */
undefined4 handle_nop()
{
  handle_response(1);
  return 0;
}


/* orig: 0x080239dc handle_patch */
undefined4 handle_patch()
{
  bool bVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined1 *puVar7;
  undefined4 extraout_r1;
  int extraout_r2;
  int extraout_r3;
  undefined4 uVar8;
  uint uVar9;
  int iVar10;
  undefined8 uVar11;
  longlong lVar12;
  undefined *puVar13;
  char local_314 [4];
  undefined4 local_310;
  undefined4 local_30c;
  undefined4 local_308;
  undefined4 uStack_304;
  undefined4 local_300;
  undefined4 local_2fc;
  undefined *local_2f8;
  int local_2f4;
  undefined4 *local_2f0;
  undefined1 auStack_2ec [3];
  undefined1 auStack_2e9 [513];
  undefined1 uStack_e8;
  undefined1 auStack_e7 [63];
  undefined1 auStack_a8 [64];
  undefined1 auStack_68 [64];
  int local_28;

  local_2f4 = DAT_0804cd58;
  local_28 = DAT_0804cd58;
  uVar9 = 0xffffffff;
  iVar10 = 0x200;
  local_308 = 0;
  uStack_304 = 0;
  bVar1 = true;
  FUN_08006d14(auStack_68,0x40);
  FUN_08006d14(&uStack_e8,0x40);
  FUN_08006d14(auStack_a8,0x40);
  FUN_08006d14(auStack_2e9 + 1,0x200);
  local_310 = 0;
  local_30c = 0;
  uVar5 = uVar9;
  uVar3 = uVar9;
  while (iVar4 = xml_advance(&DAT_08055ea0), iVar4 == 2) {
    iVar4 = xml_attr_match(&DAT_08055ea0,"byte_offset");
    if (iVar4 == 0) {
      iVar4 = xml_attr_match(&DAT_08055ea0,"physical_partition_number");
      if (iVar4 == 0) {
        iVar4 = xml_attr_match(&DAT_08055ea0,"size_in_bytes");
        if (iVar4 == 0) {
          iVar4 = xml_attr_match(&DAT_08055ea0,"start_sector");
          if (iVar4 != 0) {
            puVar7 = auStack_a8;
            goto LAB_08023b14;
          }
          iVar4 = xml_attr_match(&DAT_08055ea0,"SECTOR_SIZE_IN_BYTES");
          if (iVar4 == 0) {
            iVar4 = xml_attr_match(&DAT_08055ea0,"filename");
            if (iVar4 != 0) {
              puVar7 = auStack_68;
              goto LAB_08023b14;
            }
            iVar4 = xml_attr_match(&DAT_08055ea0,"value");
            if (iVar4 != 0) {
              puVar7 = &uStack_e8;
LAB_08023b14:
              xml_get_attr_value(&DAT_08055ea0,puVar7,0x40,0);
            }
          }
          else {
            xml_get_attr_value(&DAT_08055ea0,auStack_2e9 + 1,0x200,0);
            iVar10 = parse_uint_from_str(auStack_2e9 + 1,local_314);
            if (local_314[0] == '\0') {
              pcVar2 = "Failed to get sector_size_in_bytes";
              goto LAB_08023aea;
            }
          }
        }
        else {
          xml_get_attr_value(&DAT_08055ea0,auStack_2e9 + 1,0x200,0);
          uVar3 = parse_uint_from_str(auStack_2e9 + 1,local_314);
          if (local_314[0] == '\0') {
            pcVar2 = "Failed to get size_in_bytes";
            goto LAB_08023aea;
          }
        }
      }
      else {
        xml_get_attr_value(&DAT_08055ea0,auStack_2e9 + 1,0x200,0);
        uVar5 = parse_uint_from_str(auStack_2e9 + 1,local_314);
        if (local_314[0] == '\0') {
          pcVar2 = "Failed to get physical_partition_number";
          goto LAB_08023aea;
        }
      }
    }
    else {
      xml_get_attr_value(&DAT_08055ea0,auStack_2e9 + 1,0x200,0);
      uVar9 = parse_uint_from_str(auStack_2e9 + 1,local_314);
      if (local_314[0] == '\0') {
        pcVar2 = "Failed to get byte_offset";
LAB_08023aea:
        firehose_log(pcVar2);
        bVar1 = false;
      }
    }
  }
  if (!bVar1) goto LAB_08023b48;
  if ((((uVar9 == 0xffffffff) || (uVar5 == 0xffffffff)) || (uVar3 == 0xffffffff)) || (iVar10 == -1))
  goto LAB_08023c14;
  iVar4 = strncasecmp_fh(&DAT_08023e4c,auStack_68,0x40);
  if (iVar4 != 0) {
    uVar8 = 0;
    goto LAB_08023d36;
  }
  local_2f0 = &DAT_08058458;
  if (DAT_08058458 == iVar10 && DAT_0805845c == iVar10 >> 0x1f) {
    local_2f8 = &DAT_08058430;
    iVar10 = storage_select_partition(&DAT_08058430,uVar5 & 0xff);
    if (iVar10 == 0) {
      firehose_log("Invalid physical partition %d",uVar5);
      goto LAB_08023b48;
    }
    puVar13 = &DAT_08055e90;
    iVar4 = (&DAT_08054e90)[1 - DAT_08055fd4];
    storage_get_sector_count(local_2f8);
    snprintf_buf(auStack_2e9 + 1,0x200,&DAT_08023e98);
    str_find_replace(&uStack_e8,"NUM_DISK_SECTORS",auStack_2e9 + 1);
    str_find_replace(&uStack_e8,&DAT_08023eb4,"");
    str_find_replace(auStack_a8,"NUM_DISK_SECTORS",auStack_2e9 + 1);
    str_find_replace(auStack_a8,&DAT_08023eb4,"");
    eval_sector_expression(auStack_a8,&local_308);
    iVar10 = FUN_08006874(&uStack_e8,"CRC32");
    if (iVar10 == 0) {
      eval_sector_expression(&uStack_e8,&local_310);
LAB_08023cd4:
      storage_read_sectors(local_2f8,iVar4,local_308,uStack_304,1,0);
      if (uVar3 == 4) {
        local_30c = 0;
      }
      bounded_memcpy(iVar4 + uVar9,*(int *)(puVar13 + 0x128) - uVar9,&local_310,uVar3);
      storage_write_sectors(local_2f8,iVar4,local_308,uStack_304,1,0,auStack_2ec);
      firehose_log("Patched sector %llu with %08X",local_30c,local_308,uStack_304,local_310,
                   local_30c);
      uVar8 = handle_response(1);
      goto LAB_08023d36;
    }
    str_find_replace(&uStack_e8,"CRC32","");
    iVar10 = FUN_08006906(&uStack_e8);
    uVar5 = FUN_08006860(&uStack_e8,0x2c);
    uVar6 = FUN_080068f0(&uStack_e8,0x29);
    if ((uVar5 == 0) || (uVar6 == 0)) {
      firehose_log("Invalid CRC patch value");
    }
    else if (uVar5 <= uVar6) {
      bounded_memcpy(auStack_2e9 + 1,0x200,uVar5 + 1,(uVar6 - uVar5) + -1);
      auStack_2e9[uVar6 - uVar5] = 0;
      uVar11 = parse_uint_from_str(auStack_2e9 + 1,local_314);
      if (local_314[0] == '\0') {
        firehose_log("Failed to get crc_over_num_bytes");
        goto LAB_08023b48;
      }
      bounded_memmove(uVar5,0x200,uVar6,auStack_e7 + (iVar10 - uVar6));
      eval_sector_expression(&uStack_e8,&local_300);
      firehose_log("crc start sector %llu, over bytes %llu",extraout_r1,local_300,local_2fc,uVar11);
      lVar12 = FUN_080060c0((int)uVar11,(int)((ulonglong)uVar11 >> 0x20),*local_2f0,local_2f0[1]);
      storage_read_sectors(local_2f8,iVar4,local_300,local_2fc,
                   lVar12 + (ulonglong)(extraout_r2 != 0 || extraout_r3 != 0));
      local_310 = crc32_update_byte(iVar4,(int)uVar11);
      local_30c = 0;
      goto LAB_08023cd4;
    }
  }
  else {
    firehose_log("Sector size in XML %d does not match disk sector size %d",iVar10);
LAB_08023b48:
    handle_response(0);
  }
LAB_08023c14:
  uVar8 = 1;
LAB_08023d36:
  if (local_28 != local_2f4) {
    stack_canary_fail();
  }
  return uVar8;
}


/* orig: 0x08023f64 handle_peek */
undefined4 handle_peek()
{
  longlong lVar1;
  char *pcVar2;
  int iVar3;
  int extraout_r2;
  int extraout_r3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  bool bVar9;
  longlong lVar10;
  char local_438 [4];
  int local_434;
  undefined4 local_430;
  undefined1 auStack_42c [512];
  undefined1 local_22c [512];
  int local_2c;

  local_434 = DAT_0804cd58;
  local_2c = DAT_0804cd58;
  FUN_08006d14(auStack_42c,0x200);
  FUN_08006d14(local_22c,0x200);
  iVar8 = 0;
  bVar9 = true;
  lVar10 = 0;
  local_430 = 0x33;
LAB_08023ffc:
  while( true ) {
    uVar7 = (uint)((ulonglong)lVar10 >> 0x20);
    iVar3 = xml_advance(&DAT_08055ea0);
    if (iVar3 != 2) break;
    iVar3 = xml_attr_match(&DAT_08055ea0,"SizeInBytes");
    if (iVar3 == 0) goto LAB_08023fcc;
    xml_get_attr_value(&DAT_08055ea0,auStack_42c,0x200,0);
    lVar10 = parse_uint_from_str(auStack_42c,local_438);
    if (local_438[0] == '\0') {
      pcVar2 = "Failed to get size in bytes";
      goto LAB_08023ff6;
    }
  }
  if (bVar9) {
    if ((iVar8 != 0) && (lVar10 != 0)) {
      firehose_log("Using address %p",iVar8);
      uVar5 = 0;
      uVar6 = 0;
      while (lVar1 = CONCAT44(uVar6,uVar5),
            uVar6 <= uVar7 && (uint)((uint)lVar10 <= uVar5) <= uVar6 - uVar7) {
        snprintf_buf(auStack_42c,0x200,"0x%02X ",*(undefined1 *)(iVar8 + uVar5));
        safe_strlcat(local_22c,auStack_42c,0x200);
        bVar9 = 0xfffffffe < uVar5;
        uVar5 = uVar5 + 1;
        uVar6 = uVar6 + bVar9;
        FUN_080060c0(uVar5,uVar6,local_430,0);
        if ((extraout_r2 == 0 && extraout_r3 == 0) || (lVar10 + -1 == lVar1)) {
          firehose_log(&DAT_08024130,local_22c);
          local_22c[0] = 0;
        }
      }
      handle_response(1);
      uVar4 = 0;
      goto LAB_08024094;
    }
    firehose_log("Invalid parameters");
  }
  handle_response(0);
  uVar4 = 1;
LAB_08024094:
  if (local_2c != local_434) {
    stack_canary_fail();
  }
  return uVar4;
LAB_08023fcc:
  iVar3 = xml_attr_match(&DAT_08055ea0,"address64");
  if (iVar3 != 0) {
    xml_get_attr_value(&DAT_08055ea0,auStack_42c,0x200,0);
    iVar8 = parse_uint_from_str(auStack_42c,local_438);
    if (local_438[0] == '\0') {
      pcVar2 = "Failed to get address";
LAB_08023ff6:
      firehose_log(pcVar2);
      bVar9 = false;
    }
  }
  goto LAB_08023ffc;
}


/* orig: 0x08024134 handle_poke */
undefined4 handle_poke()
{
  int iVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined1 *puVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  bool bVar10;
  longlong lVar11;
  ulonglong uVar12;
  char local_230 [4];
  undefined1 auStack_22c [512];
  int local_2c;

  iVar1 = DAT_0804cd58;
  local_2c = DAT_0804cd58;
  FUN_08006d14(auStack_22c,0x200);
  puVar6 = (undefined1 *)0x0;
  bVar10 = true;
  lVar11 = 0;
  uVar12 = 0;
LAB_080241c2:
  while (uVar9 = (uint)((ulonglong)lVar11 >> 0x20), uVar8 = (uint)lVar11,
        iVar3 = xml_advance(&DAT_08055ea0), iVar3 == 2) {
    iVar3 = xml_attr_match(&DAT_08055ea0,"SizeInBytes");
    if (iVar3 != 0) {
      xml_get_attr_value(&DAT_08055ea0,auStack_22c,0x200,0);
      lVar11 = parse_uint_from_str(auStack_22c,local_230);
      goto LAB_0802420e;
    }
    iVar3 = xml_attr_match(&DAT_08055ea0,"address64");
    if (iVar3 == 0) goto LAB_080241e8;
    xml_get_attr_value(&DAT_08055ea0,auStack_22c,0x200,0);
    puVar6 = (undefined1 *)parse_uint_from_str(auStack_22c,local_230);
    if (local_230[0] == '\0') {
      pcVar2 = "Failed to get address";
      goto LAB_080241ba;
    }
  }
  if (bVar10) {
    if ((puVar6 == (undefined1 *)0x0) || (lVar11 == 0)) {
      firehose_log("Invalid parameters address %p size_in_bytes %llu",puVar6,uVar8,uVar9);
    }
    else {
      if (-uVar9 < (uint)(uVar8 < 9)) {
        firehose_log("Using address %p",puVar6);
        uVar5 = 0;
        for (uVar4 = 0; uVar4 <= uVar9 && (uint)(uVar8 <= uVar5) <= uVar4 - uVar9;
            uVar4 = uVar4 + bVar10) {
          *puVar6 = (char)uVar12;
          bVar10 = 0xfffffffe < uVar5;
          uVar5 = uVar5 + 1;
          uVar12 = uVar12 >> 8;
          puVar6 = puVar6 + 1;
        }
        handle_response(1,uVar5,(uVar4 - uVar9) - (uint)(uVar8 > uVar5));
        uVar7 = 0;
        goto LAB_08024266;
      }
      firehose_log("Cannot handle size in bytes greater than %llu",8);
    }
  }
  handle_response(0);
  uVar7 = 1;
LAB_08024266:
  if (local_2c != iVar1) {
    stack_canary_fail();
  }
  return uVar7;
LAB_080241e8:
  iVar3 = xml_attr_match(&DAT_08055ea0,"value");
  if (iVar3 != 0) {
    xml_get_attr_value(&DAT_08055ea0,auStack_22c,0x200,0);
    uVar12 = parse_uint_from_str(auStack_22c,local_230);
LAB_0802420e:
    if (local_230[0] == '\0') {
      pcVar2 = "Failed to get size in bytes";
LAB_080241ba:
      firehose_log(pcVar2);
      bVar10 = false;
    }
  }
  goto LAB_080241c2;
}


/* orig: 0x08024350 handle_power */
undefined4 handle_power()
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char local_220 [4];
  undefined1 auStack_21c [512];
  int local_1c;

  iVar1 = DAT_0804cd58;
  local_1c = DAT_0804cd58;
  FUN_08006d14(auStack_21c,0x200);
  iVar3 = 0;
  iVar4 = 0;
LAB_080243d6:
  do {
    while( true ) {
      iVar2 = xml_advance(&DAT_08055ea0);
      if (iVar2 != 2) {
        if (iVar4 == 1) {
          handle_response(1);
          transport_error_loop(iVar3);
          fatal_error_halt();
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        if (iVar4 != 2) {
          if (local_1c != iVar1) {
            stack_canary_fail();
          }
          return 1;
        }
        handle_response(1);
        transport_error_loop(iVar3);
        fatal_error_dma_reset();
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      iVar2 = xml_attr_match(&DAT_08055ea0,"value");
      if (iVar2 == 0) break;
      xml_get_attr_value(&DAT_08055ea0,auStack_21c,0x200,0);
      iVar2 = strncasecmp_fh(auStack_21c,"reset",5);
      if (iVar2 == 0) {
        iVar4 = 1;
      }
      else {
        iVar2 = strncasecmp_fh(auStack_21c,&DAT_08024444,3);
        if (iVar2 == 0) {
          iVar4 = 2;
        }
      }
    }
    iVar2 = xml_attr_match(&DAT_08055ea0,"delayinseconds");
  } while (iVar2 == 0);
  xml_get_attr_value(&DAT_08055ea0,auStack_21c,0x200,0);
  iVar3 = parse_uint_from_str(auStack_21c,local_220);
  if (local_220[0] != '\0') goto code_r0x080243d0;
  firehose_log("Failed to get delay time. Using default.");
  goto LAB_080243d4;
code_r0x080243d0:
  if (iVar3 < 1) {
LAB_080243d4:
    iVar3 = 1;
  }
  goto LAB_080243d6;
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
  int extraout_r2;
  uint uVar11;
  int extraout_r3;
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
  FUN_08006d14(local_2ec,0x200);
  iVar14 = 0x200;
  uVar13 = 0xffffffff;
  lVar2 = 0;
  local_310 = 0;
  uStack_30c = 0;
  FUN_08006d14(auStack_ec,0x40);
  FUN_08006d14(auStack_ac,0x40);
  local_314 = 0;
  local_300 = 1;
  FUN_08006d14(auStack_6c,0x20);
  FUN_08006d14(auStack_4c,0x20);
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
        lVar17 = FUN_080060c0(DAT_08055fb8,DAT_08055fbc,iVar14,iVar4);
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
                   (FUN_080060c0(local_308,uStack_304,iVar14,iVar4),
                   extraout_r2 == 0 && extraout_r3 == 0)) {
                  lVar19 = FUN_080060c0(uVar13,uVar8,iVar14,iVar4);
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
                        uVar18 = FUN_08006898(auStack_6c,auStack_4c,0x20);
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
  FUN_08006d14(auStack_26c,0x200);
  uVar9 = 0xffffffff;
  bVar1 = true;
  lVar10 = 0;
  local_298 = 0;
  uStack_294 = 0;
  local_280 = 0;
  uStack_27c = 0;
  FUN_08006d14(auStack_6c,0x40);
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
        local_288 = FUN_080060c0(DAT_08055fb8,DAT_08055fbc,iVar8,iVar8 >> 0x1f);
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


/* orig: 0x08024efc handle_setbootable */
undefined4 handle_setbootable()
{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  char local_220 [4];
  undefined1 auStack_21c [512];
  int local_1c;

  iVar2 = DAT_0804cd58;
  local_1c = DAT_0804cd58;
  FUN_08006d14(auStack_21c,0x200);
  bVar1 = true;
  uVar5 = 0xffffffff;
  while (iVar3 = xml_advance(&DAT_08055ea0), iVar3 == 2) {
    iVar3 = xml_attr_match(&DAT_08055ea0,"value");
    if (iVar3 != 0) {
      xml_get_attr_value(&DAT_08055ea0,auStack_21c,0x200,0);
      uVar5 = parse_uint_from_str(auStack_21c,local_220);
      if (local_220[0] == '\0') {
        firehose_log("Failed to get bootable drive");
        bVar1 = false;
      }
    }
  }
  if (!bVar1) {
    handle_response(0);
    uVar4 = 1;
    goto LAB_08024f86;
  }
  if (uVar5 == 0xffffffff) {
    firehose_log("Could not find bootable drive value.");
LAB_08024fb4:
    uVar4 = 0;
  }
  else {
    iVar3 = storage_select_partition(&DAT_08058430,uVar5 & 0xff);
    if (iVar3 == 0) {
      firehose_log("Failed to set bootable drive to %d.",uVar5);
      goto LAB_08024fb4;
    }
    storage_select_and_read(&DAT_08058430);
    storage_select_all(&DAT_08058430);
    firehose_log("Set bootable drive to %d.",uVar5);
    uVar4 = 1;
  }
  uVar4 = handle_response(uVar4);
LAB_08024f86:
  if (local_1c != iVar2) {
    stack_canary_fail();
  }
  return uVar4;
}


/* orig: 0x08025054 handle_storagextras */
undefined4 handle_storagextras()
{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  char *pcVar7;
  undefined1 auStack_428 [4];
  char local_424 [512];
  undefined1 auStack_224 [512];
  int local_24;

  iVar4 = DAT_0804cd58;
  local_24 = DAT_0804cd58;
  FUN_08006d14(auStack_224,0x200);
  FUN_08006d14(local_424,0x200);
  bVar2 = false;
  bVar1 = true;
  bVar3 = false;
  while (iVar5 = xml_advance(&DAT_08055ea0), iVar5 == 2) {
    iVar5 = xml_attr_match(&DAT_08055ea0,"commit");
    if (iVar5 == 0) {
      iVar5 = xml_attr_match(&DAT_08055ea0,"display");
      if (iVar5 == 0) {
        xml_get_attr_name(&DAT_08055ea0,auStack_224,0x200,0);
        xml_get_attr_value(&DAT_08055ea0,local_424,0x200,0);
        iVar5 = FUN_0803805c(&DAT_08058430,auStack_224,local_424);
        if (iVar5 == 0) {
          bVar1 = false;
          firehose_log("Invalid storage extra parameter %s",auStack_224);
        }
      }
      else {
        xml_get_attr_value(&DAT_08055ea0,local_424);
        if (local_424[0] == '1') {
          bVar3 = true;
        }
      }
    }
    else {
      xml_get_attr_value(&DAT_08055ea0,local_424,0x200,0);
      if (local_424[0] == '1') {
        bVar2 = true;
      }
    }
  }
  if (bVar1) {
    if (bVar3) {
      storage_log_drive_info(&DAT_08058430);
    }
    if (!bVar2) {
LAB_08025142:
      uVar6 = 1;
      goto LAB_08025144;
    }
    iVar5 = storage_select_partition(&DAT_08058430,0);
    if (iVar5 == 0) {
      pcVar7 = "Could not open partition for creating new drives";
    }
    else {
      iVar5 = storage_commit(&DAT_08058430,auStack_428);
      if (iVar5 != 0) {
        storage_select_all(&DAT_08058430);
        firehose_log("Set storage parameters successfully");
        goto LAB_08025142;
      }
      pcVar7 = "Failed to set storage extra parameters";
    }
    firehose_log(pcVar7);
  }
  uVar6 = 0;
LAB_08025144:
  uVar6 = handle_response(uVar6);
  if (local_24 != iVar4) {
    stack_canary_fail();
  }
  return uVar6;
}
