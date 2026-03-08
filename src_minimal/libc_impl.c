/* libc_impl.c — Minimal libc for freestanding build.
 *
 * Provides: memset, memcpy, delay_us.
 */
#include "firehose.h"

/*========================================================================
 * memset — fill memory with a byte value
 *========================================================================*/
void *memset(void *s, int c, unsigned int n)
{
    unsigned char *p = (unsigned char *)s;
    while (n--) *p++ = (unsigned char)c;
    return s;
}

/*========================================================================
 * memcpy — copy memory
 *========================================================================*/
void *memcpy(void *dest, const void *src, unsigned int n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s2 = (const unsigned char *)src;
    while (n--) *d++ = *s2++;
    return dest;
}

/*========================================================================
 * thunk_FUN_080199b4 — microsecond delay using ARM generic timer (CNTPCT)
 *
 * The QTimer runs at 19.2 MHz on MSM8909. Each tick = 1/19200000 sec.
 * delay_us = ticks * 19.2 ≈ ticks * 19 (close enough for init delays).
 *========================================================================*/
void thunk_FUN_080199b4(param_1)
uint param_1;
{
#ifdef EMU_BUILD
    (void)param_1;
#else
    uint64_t start, now, target;
    uint32_t lo, hi;
    __asm__ volatile("mrrc p15, 0, %0, %1, c14" : "=r"(lo), "=r"(hi));
    start = ((uint64_t)hi << 32) | lo;
    target = start + (uint64_t)param_1 * 19;
    do {
        __asm__ volatile("mrrc p15, 0, %0, %1, c14" : "=r"(lo), "=r"(hi));
        now = ((uint64_t)hi << 32) | lo;
    } while (now < target);
#endif
}

/*========================================================================
 * qtimer_init — timer initialization (done by SBL1, stub)
 *========================================================================*/
void qtimer_init(void)
{
}
