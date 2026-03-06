❯ ./bq268-edl --verbose --show-logs printgpt
[usb] opened 05c6:9008 bulk-in=0x01 bulk-out=0x01
[sahara] loader: loader/fhprg_peek.bin (278980 bytes)
[sahara] HELLO_REQ: version=2 mode=0x0 cmdpacketlen=1024
[sahara] cmd_ready rx 8 bytes: 0b 00 00 00 08 00 00 00
[sahara] sending SWITCH_MODE → mode=0x3
[sahara] HELLO_REQ (post-switch): version=2 mode=0x3 cmdpacketlen=1024
[... omitted ...]
[sahara] END_TRANSFER: imageID=0xd status=0x0
[sahara] END_TRANSFER OK
[sahara] complete — Firehose programmer running
[firehose] >> <?xml version="1.0" ?><data><configure MemoryName="eMMC" Verbose="0" AlwaysValidate="0" MaxDigestTableSizeInBytes="2048" MaxPayloadSizeToTargetInBytes="1048576" ZLPAwareHost="1" SkipStorageInit="0" SkipWrite="0" />
</data>
[firehose] << ACK logs=[logbuf@0x08058028 fh@0x08054E90]
[firehose] configured: write_chunk=1048576 read_chunk=4096 target="8909"
[firehose] drain 99 bytes
[firehose] >> <?xml version="1.0" ?><data><read SECTOR_SIZE_IN_BYTES="512" num_partition_sectors="34" physical_partition_number="0" start_sector="0" />
</data>
[firehose] << ACK logs=[]
[firehose] read [0+34] = 17408 bytes SHA256=75e532e52ecbd0e2...
Disk: 7634944 sectors × 512 = 3.6 GiB
Backup GPT: LBA 7634943
Usable: LBA 34 – 7634910

Name                      Start    Sectors       Size  Type GUID
----                      -----    -------       ----  ---------
modem                    131072     135168      66.0M  EBD0A0A2-B9E5-4433-87C0-68B6B72699C7
DDR                      266240         64      32.0K  20A0C19C-286A-42FA-9CE7-F64C3226A794
fsg                      266304       3072       1.5M  638FF8E2-22C9-E33B-8F5D-0E81686A68CB
sec                      269376         32      16.0K  303E6AC3-AF15-4C54-9E9B-D9A8FBECF401
boot                     269408      65536      32.0M  20117F86-E985-4357-B9EE-374BC1D8487D
system                   334944    1843200     900.0M  97D7B011-54DA-4835-B3C4-917AD6E73D74
persist                 2178144      65536      32.0M  6C95E238-E343-4BA8-B489-8681ED22AD0B
cache                   2243680     225280     110.0M  5594C694-C871-4B5F-90B1-690A6F68E0F7
recovery                2468960      65536      32.0M  9D72D4E4-9958-42DA-AC26-BEA7A90B0434
devinfo                 2534496       2048       1.0M  1B81E7E6-F50D-419B-A739-2AEEF8DA3335
cmnlib                  2536544        512     256.0K  73471795-AB54-43F9-A847-4F72EA5CBEF5
cmnlibbak               2537056        512     256.0K  73471795-AB54-43F9-A847-4F72EA5CBEF5
keymaster               2537568       1024     512.0K  E8B7CF6E-5694-4627-8A2A-899B09F2DBEA
keymasterbak            2538592       1024     512.0K  E8B7CF6E-5694-4627-8A2A-899B09F2DBEA
sbl1                    2621440       1024     512.0K  DEA0BA2C-CBDD-4805-B4F9-F428251C3E98
sbl1bak                 2622464       1024     512.0K  DEA0BA2C-CBDD-4805-B4F9-F428251C3E98
aboot                   2623488       2048       1.0M  400FFDCD-22E0-47E7-9A23-F16ED9382388
abootbak                2625536       2048       1.0M  400FFDCD-22E0-47E7-9A23-F16ED9382388
rpm                     2627584       1024     512.0K  098DF793-D712-413D-9D4E-89D711772228
rpmbak                  2628608       1024     512.0K  098DF793-D712-413D-9D4E-89D711772228
tz                      2629632       4096       2.0M  A053AA7F-40B8-4B1C-BA08-2F68AC71A4F4
tzbak                   2633728       4096       2.0M  A053AA7F-40B8-4B1C-BA08-2F68AC71A4F4
devcfg                  2637824        512     256.0K  F65D4B16-343D-4E25-AAFC-BE99B6556A6D
apdp                    2638336        512     256.0K  E6E98DA2-E22A-4D12-AB33-169E7DEAA507
pad                     2638848       2048       1.0M  EBD0A0A2-B9E5-4433-87C0-68B6B72699C7
modemst1                2640896       3072       1.5M  EBBEADAF-22C9-E33B-8F5D-0E81686A68CB
modemst2                2643968       3072       1.5M  0A288B1F-22C9-E33B-8F5D-0E81686A68CB
misc                    2647040      16384       8.0M  82ACC91F-357C-4A68-9C8F-689E1B1A23A1
fsc                     2663424          2       1.0K  57B90A16-22C9-E33B-8F5D-0E81686A68CB
ssd                     2663426         16       8.0K  2C86E742-745E-4FDD-BFD8-B6A7AC638772
splash                  2663442      20480      10.0M  20117F86-E985-4357-B9EE-374BC1D8487D
keystore                2683922       1024     512.0K  DE7D4029-0F5B-41C8-AE7E-F6C023A02B33
oem                     2684946      16384       8.0M  7DB6AC55-ECB5-4E02-80DA-4D335B973332
config                  2701330       1024     512.0K  91B72D4D-71E0-4CBF-9B8E-236381CFF17A
vendor                  2702354     512000     250.0M  3C160A98-F525-45F6-AF0B-9598B4C95B75
userdata                3214354    4420557       2.1G  1B81E7E6-F50D-419B-A739-2AEEF8DA3335

