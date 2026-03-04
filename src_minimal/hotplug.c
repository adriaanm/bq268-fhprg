#include "firehose.h"

/* orig: 0x08025b74 FUN_08025b74 */
int FUN_08025b74(void)
{
    return 0;
}

/* orig: 0x08025c08 FUN_08025c08 */
int FUN_08025c08(void)
{
    return 0;
}

/* orig: 0x08025c80 FUN_08025c80 */
int FUN_08025c80(void)
{
    return 0;
}

/* orig: 0x08013918 FUN_08013918 */
int FUN_08013918(void)
{
    return 0;
}

/* orig: 0x0802ef24 FUN_0802ef24 */
int FUN_0802ef24(int param_1, int param_2, uint *param_3, int param_4)
{
    return 0;
}

/* orig: 0x08026b88 FUN_08026b88 */
void FUN_08026b88(void)
{
}

/* orig: 0x08026af8 FUN_08026af8 */
void FUN_08026af8(void)
{
}

/* orig: 0x08026dd8 FUN_08026dd8 */
uint *FUN_08026dd8(uint param_1, uint param_2, uint param_3, uint param_4)
{
    int iVar1;
    uint *puVar2;
    uint uVar3;
    uint local_18 = 0;
    uint local_14 = param_4 & 0xffff0000;
    iVar1 = FUN_08013bb0(param_1, param_2, &local_18, &local_14);
    if (iVar1 == 0) {
        uVar3 = local_14 & 0xffff;
        if (((uVar3 < 0x201) && (uVar3 != 0)) && (local_18 != 0)) {
            DAT_0805a448 = (undefined2)local_14;
            DAT_0805a44c = local_18;
            DAT_0805a450 = DAT_0805124c;
            DAT_0805a454 = DAT_08051250 / uVar3;
            if (local_18 < DAT_08051250 / uVar3) DAT_0805a454 = local_18;
            DAT_0805a440 = param_1;
            DAT_0805a444 = param_2;
            iVar1 = FUN_0802ef24(0, 0, &DAT_0805a440, 1);
            puVar2 = (uint *)0x0;
            if (iVar1 != 0) puVar2 = &DAT_0805a440;
            return puVar2;
        }
    }
    return (uint *)0x0;
}
