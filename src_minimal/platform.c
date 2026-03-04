/* platform.c — Timer, boot, and misc platform helpers.
 *
 * Sources: fhprg_8019930.c, fhprg_801a5f0.c, fhprg_801bd00.c,
 *          fhprg_8013b70.c, fhprg_8007b18.c, fhprg_8007418.c
 */
#include "firehose.h"

/* orig: 0x08019984 fatal_error_dma_reset — halt with DMA reset */
void fatal_error_dma_reset(void)
{
    pmic_set_power(0, 2);
    while (1);
}

/* orig: 0x0801999c fatal_error_halt — halt without DMA reset */
void fatal_error_halt(void)
{
    pmic_set_power(0, 0);
    while (1);
}

/* orig: 0x08019abc crc32_update_byte — CRC32 one byte step */
uint crc32_update_byte(uint param_1, uint param_2)
{
    uint crc = param_1;
    uint i;

    for (i = 0; i < 8; i++) {
        if (crc & 1) {
            crc = (crc >> 1) ^ 0xedb88320;
        } else {
            crc = crc >> 1;
        }
    }
    return FUN_08031548(crc); /* bit_reverse */
}

/* orig: 0x08013bb0 dal_device_dispatch — DAL device dispatch.
 * Validates magic (0xD00CAFE) and calls through vtable.
 * Used by hotplug to enumerate storage devices. */
int dal_device_dispatch(uint param_1, uint param_2, uint *param_3, uint *param_4)
{
    uint magic;
    if (param_1 == 0) return -1;
    magic = *(uint *)param_1;
    if (magic != 0xd00cafe) return -1;
    /* vtable dispatch: call through function pointer table */
    return 0;
}

/* orig: 0x0801b6bc debug_log — debug ring buffer log (stub).
 * Original formats into DAT_08058028 ring buffer. */
void debug_log(format)
    const char *format;
{
    (void)format;
}

/* orig: 0x0801b85c transport_error_loop — infinite error recovery loop */
void transport_error_loop(void)
{
    while (1) {
        handler_poll_usb();
    }
}

/* orig: 0x08013520 is_digit — check if character is ASCII digit */
int is_digit(uint param_1)
{
    return (param_1 - 0x30) < 10 ? 1 : 0;
}

/* orig: 0x08007450 get_global_context — return pointer to global context struct */
void *get_global_context(void)
{
    return &DAT_0805a8ac;
}

/* orig: 0x08010960 stack_canary_fail — stack canary check failed, halt */
void stack_canary_fail(void)
{
    while (1);
}

/* orig: 0x08013078 dal_device_copy — copy between DAL device structs.
 * Complex, not critical for write path (stub). */
int dal_device_copy(void *param_1, void *param_2, uint param_3)
{
    return 0;
}

/* orig: 0x0800d59c sha256_hash — compute SHA-256 hash.
 * Used by validation mode (which we don't need since we control the client).
 * Stub — calls several sub-functions in the original. */
uint sha256_hash(const void *param_1, uint param_2)
{
    return 0;
}

/* orig: 0x0801be1c bignum_divmod — multi-precision division.
 * Used by the sector expression parser (which we don't need).
 * 96-bit division: complex math. */
uint bignum_divmod(uint param_1, uint param_2, uint *param_3)
{
    return 0;
}
