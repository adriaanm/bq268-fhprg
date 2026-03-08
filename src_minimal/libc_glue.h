/* libc_glue.h — Map decompiled FUN_ names to standard libc functions.
 *
 * In a freestanding build, we declare the libc functions ourselves.
 * Implementations are in libc_impl.c.
 */
#pragma once

#include <stddef.h>

/* Freestanding libc declarations */
void *memcpy(void *dst, const void *src, size_t n);
void *memset(void *s, int c, size_t n);

/* Ghidra name mappings */
#define FUN_08006a30  memcpy

/* memset_zero — the original firmware's memset(p, 0, n) two-arg form */
static inline void memset_zero(void *p, unsigned int n) {
    memset(p, 0, n);
}
