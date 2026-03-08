/* platform.c — Minimal platform stubs.
 *
 * These are referenced by the eMMC driver but never actually called
 * in the minimal programmer's code path. Kept as stubs to satisfy
 * the linker.
 */
#include "firehose.h"

/* orig: 0x08007450 get_global_context */
void *get_global_context(void)
{
    return &DAT_0805a8ac;
}
