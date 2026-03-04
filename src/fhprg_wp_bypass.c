/*
 * Modified FUN_08034228 — eMMC write function with WP bypass + CMD29.
 *
 * Changes from original:
 *   1. WP check (EXT_CSD[160]) REMOVED — always proceed to write
 *   2. CMD29 CLR_WRITE_PROT added before writing
 *   3. Cached WP byte zeroed for any downstream checks
 *
 * The struct passed to FUN_08033656 has this layout (from sp):
 *   +0x00: cmd_type (0x18=write or 0x19=????)
 *   +0x04: sector_number
 *   +0x08: flag byte (1)
 *   +0x1c: 0
 *   +0x24: 1
 */

typedef unsigned int uint;
typedef unsigned char undefined1;
typedef unsigned int undefined4;

/* External functions */
extern int FUN_08034fb0(void);
extern int FUN_08033656(uint *dev, void *cmd_struct, undefined4 buf, int nsectors);
extern int FUN_08032b94(uint *dev, void *cmd_struct);

/* Write command struct — matches original stack layout */
typedef struct {
    unsigned int cmd_type;      /* +0x00: 0x18 or 0x19 */
    int          sector;        /* +0x04 */
    unsigned char flag;         /* +0x08 */
    unsigned char _pad1[3];     /* +0x09 */
    unsigned int _reserved[4];  /* +0x0c to +0x1b */
    unsigned int field_1c;      /* +0x1c */
    unsigned int _reserved2;    /* +0x20 */
    unsigned int field_24;      /* +0x24 */
} write_cmd_t;

int FUN_08034228(undefined4 *param_1, int param_2, undefined4 param_3, int param_4)
{
    int iVar2;
    uint *puVar3;
    volatile write_cmd_t wcmd;
    char cVar1;

    if (((param_1 == (undefined4 *)0x0) ||
         (puVar3 = (uint *)*param_1, puVar3 == (uint *)0x0)) ||
        (2 < *puVar3)) {
        return 0x14;
    }

    /* -- WP CHECK REMOVED --
     * Original: if (*(char *)(puVar3[0x24] + 0xa0) != '\0') return 0x1b;
     * Instead, zero the cached byte to bypass any downstream checks. */
    *(volatile char *)(puVar3[0x24] + 0xa0) = '\0';

    /* CMD29 CLR_WRITE_PROT for the target sector */
    {
        volatile unsigned int cmd29[10];
        cmd29[0] = 29;         /* CMD29 */
        cmd29[1] = param_2;   /* sector address */
        cmd29[2] = 1;         /* R1B response */
        cmd29[3] = 0;
        cmd29[4] = 0;
        cmd29[5] = 0;
        cmd29[6] = 0;
        cmd29[7] = 1;         /* busy wait */
        cmd29[8] = 0;
        cmd29[9] = 0;
        FUN_08032b94(puVar3, (void *)cmd29);
    }

    cVar1 = (char)puVar3[2];
    if (cVar1 == '\0') {
        iVar2 = 0x15;
    }
    else if (((cVar1 == '\x01') || (cVar1 == '\x05')) ||
             ((cVar1 == '\x02' || (cVar1 == '\x06')))) {
        iVar2 = FUN_08034fb0();
        if (iVar2 == 0) {
            wcmd.cmd_type = (param_4 == 1) ? 0x18 : 0x19;
            wcmd.flag = 1;
            wcmd.field_1c = 0;
            wcmd.sector = param_2;
            if (((char)puVar3[2] != '\x05') && ((char)puVar3[2] != '\x06')) {
                wcmd.sector = param_2 * puVar3[9];
            }
            wcmd.field_24 = 1;
            iVar2 = FUN_08033656(puVar3, (void *)&wcmd, param_3, param_4);
        }
    }
    else {
        iVar2 = 0x10;
    }
    return iVar2;
}
