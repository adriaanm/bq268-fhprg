/* hotplug.c — Storage device enumeration.
 *
 * Hotplug discovers and initializes storage devices (eMMC, SD cards).
 * Called during handle_configure to set up the device table.
 *
 * Most of this is boilerplate device enumeration that isn't critical
 * for understanding the write path. The important output is that
 * DAT_08058430 (the storage context) gets its device handles populated.
 *
 * Sources: fs_ext_hfat.c, fs_extfs.c, fs_hotplug_parser.c,
 *          fs_hotplug_partition.c, fhprg_8026734.c
 */
#include "firehose.h"

/* orig: 0x08025b74 hfat_open — open HFAT filesystem (stub) */
int hfat_open(void)
{
    return 0;
}

/* orig: 0x08025c08 hfat_read — read from HFAT filesystem (stub) */
int hfat_read(void)
{
    return 0;
}

/* orig: 0x08025c80 hfat_close — close HFAT filesystem (stub) */
int hfat_close(void)
{
    return 0;
}

/* orig: 0x08013918 extfs_open — open external filesystem (stub).
 * Called from transport_read_data for validation mode. */
int extfs_open(void)
{
    return 0;
}

/* orig: 0x0802ef24 hotplug_parse_mbr — parse MBR/GPT partition table (stub) */
int hotplug_parse_mbr(int param_1, int param_2, uint *param_3, int param_4)
{
    return 0;
}

/* orig: 0x08026b88 hotplug_partition_init — initialize partition table (stub) */
void hotplug_partition_init(void)
{
}

/* orig: 0x08026af8 hotplug_dev_alloc — allocate hotplug device (stub) */
void hotplug_dev_alloc(void)
{
}

/* orig: 0x08026dd8 hotplug_poll_device — poll for device presence.
 * Uses DAL device dispatch to detect the storage device and populate
 * the hotplug state globals (sector size, capacity, etc.). */
uint *hotplug_poll_device(uint param_1, uint param_2, uint param_3, uint param_4)
{
    int iVar1;
    uint *puVar2;
    uint uVar3;
    uint local_18 = 0;
    uint local_14 = param_4 & 0xffff0000;
    iVar1 = dal_device_dispatch(param_1, param_2, &local_18, &local_14);
    if (iVar1 == 0) {
        uVar3 = local_14 & 0xffff;
        if (((uVar3 < 0x201) && (uVar3 != 0)) && (local_18 != 0)) {
            DAT_0805a448 = (undefined2)local_14; /* sector size */
            DAT_0805a44c = local_18;              /* total sectors */
            DAT_0805a450 = DAT_0805124c;
            DAT_0805a454 = DAT_08051250 / uVar3;
            if (local_18 < DAT_08051250 / uVar3) DAT_0805a454 = local_18;
            DAT_0805a440 = param_1;
            DAT_0805a444 = param_2;
            iVar1 = hotplug_parse_mbr(0, 0, &DAT_0805a440, 1);
            puVar2 = (uint *)0x0;
            if (iVar1 != 0) puVar2 = &DAT_0805a440;
            return puVar2;
        }
    }
    return (uint *)0x0;
}
