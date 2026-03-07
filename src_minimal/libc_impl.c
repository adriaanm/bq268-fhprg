/* libc_impl.c — Minimal libc and platform stubs for freestanding build.
 *
 * Provides: bit_reverse, delay, strtoll, qtimer_init, get_ctype_table,
 * memcpy, memset, and miscellaneous globals.
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
 * memmove — overlap-safe memory copy
 *========================================================================*/
void *memmove(void *dest, const void *src, unsigned int n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s2 = (const unsigned char *)src;
    if (d < s2) {
        while (n--) *d++ = *s2++;
    } else {
        d += n; s2 += n;
        while (n--) *--d = *--s2;
    }
    return dest;
}

/*========================================================================
 * strlen — string length
 *========================================================================*/
unsigned int strlen(const char *s)
{
    const char *p = s;
    while (*p) p++;
    return (unsigned int)(p - s);
}

/*========================================================================
 * vsnprintf / snprintf — minimal printf-style formatting
 *
 * Supports: %s, %d, %u, %x, %llu, %lld, %llx, %c, %%
 * No width/padding — sufficient for firehose XML attributes.
 *========================================================================*/
#include <stdarg.h>

static char *fmt_uint(char *buf, char *end, unsigned int val, int base)
{
    char tmp[12];
    int i = 0;
    if (val == 0) tmp[i++] = '0';
    while (val && i < 11) {
        int d = val % base;
        tmp[i++] = (d < 10) ? '0' + d : 'a' + d - 10;
        val /= base;
    }
    while (i-- > 0 && buf < end)
        *buf++ = tmp[i];
    return buf;
}

static char *fmt_uint64(char *buf, char *end, unsigned long long val, int base)
{
    char tmp[24];
    int i = 0;
    if (val == 0) tmp[i++] = '0';
    while (val && i < 23) {
        int d = (int)(val % base);
        tmp[i++] = (d < 10) ? '0' + d : 'a' + d - 10;
        val /= base;
    }
    while (i-- > 0 && buf < end)
        *buf++ = tmp[i];
    return buf;
}

int vsnprintf(char *buf, unsigned int size, const char *fmt, va_list ap)
{
    char *out = buf;
    char *end = buf + (size ? size - 1 : 0);

    if (!size) return 0;

    while (*fmt && out < end) {
        if (*fmt != '%') { *out++ = *fmt++; continue; }
        fmt++;
        if (*fmt == '%') { *out++ = '%'; fmt++; continue; }
        if (*fmt == 'c') {
            *out++ = (char)va_arg(ap, int);
            fmt++; continue;
        }
        if (*fmt == 's') {
            const char *s = va_arg(ap, const char *);
            if (!s) s = "(null)";
            while (*s && out < end) *out++ = *s++;
            fmt++; continue;
        }

        /* Check for 'll' prefix */
        int is_ll = 0;
        if (fmt[0] == 'l' && fmt[1] == 'l') { is_ll = 1; fmt += 2; }

        if (*fmt == 'd') {
            if (is_ll) {
                long long v = va_arg(ap, long long);
                if (v < 0) { if (out < end) *out++ = '-'; v = -v; }
                out = fmt_uint64(out, end, (unsigned long long)v, 10);
            } else {
                int v = va_arg(ap, int);
                if (v < 0) { if (out < end) *out++ = '-'; v = -v; }
                out = fmt_uint(out, end, (unsigned int)v, 10);
            }
            fmt++; continue;
        }
        if (*fmt == 'u') {
            if (is_ll)
                out = fmt_uint64(out, end, va_arg(ap, unsigned long long), 10);
            else
                out = fmt_uint(out, end, va_arg(ap, unsigned int), 10);
            fmt++; continue;
        }
        if (*fmt == 'x' || *fmt == 'X') {
            if (is_ll)
                out = fmt_uint64(out, end, va_arg(ap, unsigned long long), 16);
            else
                out = fmt_uint(out, end, va_arg(ap, unsigned int), 16);
            fmt++; continue;
        }

        /* Unknown specifier — output literally */
        if (out < end) *out++ = '%';
        if (is_ll && out < end) *out++ = 'l';
        if (is_ll && out < end) *out++ = 'l';
    }

    *out = '\0';
    return (int)(out - buf);
}

int snprintf(char *buf, unsigned int size, const char *fmt, ...)
{
    va_list ap;
    int n;
    va_start(ap, fmt);
    n = vsnprintf(buf, size, fmt, ap);
    va_end(ap);
    return n;
}

/*========================================================================
 * bit_reverse — reverse all 32 bits
 *========================================================================*/
uint bit_reverse(param_1)
uint param_1;
{
    uint v = param_1;
    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    v = ((v >> 4) & 0x0f0f0f0f) | ((v & 0x0f0f0f0f) << 4);
    v = ((v >> 8) & 0x00ff00ff) | ((v & 0x00ff00ff) << 8);
    v = (v >> 16) | (v << 16);
    return v;
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
    /* EMU_BUILD: no-op (no CP15 counter in Unicorn) */
    (void)param_1;
#else
    uint64_t start, now, target;
    /* Read CNTPCT (64-bit physical counter) via CP15 */
    uint32_t lo, hi;
    __asm__ volatile("mrrc p15, 0, %0, %1, c14" : "=r"(lo), "=r"(hi));
    start = ((uint64_t)hi << 32) | lo;
    target = start + (uint64_t)param_1 * 19;  /* ~19.2 ticks per us */
    do {
        __asm__ volatile("mrrc p15, 0, %0, %1, c14" : "=r"(lo), "=r"(hi));
        now = ((uint64_t)hi << 32) | lo;
    } while (now < target);
#endif
}

/*========================================================================
 * thunk_FUN_080071ec — strtoll (simplified)
 *
 * Used by parse_uint_from_str. The original firmware's implementation
 * parses decimal/hex strings to 64-bit integers.
 *========================================================================*/
longlong thunk_FUN_080071ec(param_1, param_2, param_3)
const char *param_1; char **param_2; int param_3;
{
    const char *s = param_1;
    longlong result = 0;
    int neg = 0;

    /* skip whitespace */
    while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r') s++;

    if (*s == '-') { neg = 1; s++; }
    else if (*s == '+') { s++; }

    /* detect base */
    int base = param_3;
    if (base == 0) {
        if (*s == '0' && (s[1] == 'x' || s[1] == 'X')) {
            base = 16; s += 2;
        } else if (*s == '0') {
            base = 8; s++;
        } else {
            base = 10;
        }
    } else if (base == 16 && *s == '0' && (s[1] == 'x' || s[1] == 'X')) {
        s += 2;
    }

    while (*s) {
        int digit;
        if (*s >= '0' && *s <= '9') digit = *s - '0';
        else if (*s >= 'a' && *s <= 'f') digit = *s - 'a' + 10;
        else if (*s >= 'A' && *s <= 'F') digit = *s - 'A' + 10;
        else break;
        if (digit >= base) break;
        result = result * base + digit;
        s++;
    }

    if (param_2) *param_2 = (char *)s;
    return neg ? -result : result;
}

/*========================================================================
 * qtimer_init — timer initialization (done by SBL1, stub for now)
 *========================================================================*/
void qtimer_init(void)
{
    /* Timer is already configured by the SBL1 init blob */
}

/*========================================================================
 * get_ctype_table — character classification table for XML parser
 *
 * Only needed in protocol mode, but provide a minimal one anyway
 * to avoid link errors if something references it.
 *========================================================================*/
static const unsigned char ctype_table[256] = {
    /* 0x00-0x08: control chars */
    0,0,0,0,0,0,0,0,0,
    /* 0x09: tab — whitespace */
    0x01,
    /* 0x0A: newline — whitespace */
    0x01,
    /* 0x0B-0x0C */
    0x01, 0x01,
    /* 0x0D: CR — whitespace */
    0x01,
    /* 0x0E-0x1F */
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /* 0x20: space — whitespace */
    0x01,
    /* 0x21-0x2F: punctuation */
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /* 0x30-0x39: digits — 0x18 (alpha-like for XML names) */
    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
    /* 0x3A-0x40 */
    0,0,0,0,0,0,0,
    /* 0x41-0x5A: uppercase — 0x98 (letter) */
    0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,
    0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,
    0x98,0x98,0x98,0x98,0x98,0x98,
    /* 0x5B-0x5E */
    0,0,0,0,
    /* 0x5F: underscore — 0x18 (name char) */
    0x18,
    /* 0x60 */
    0,
    /* 0x61-0x7A: lowercase — 0x98 (letter) */
    0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,
    0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,
    0x98,0x98,0x98,0x98,0x98,0x98,
    /* 0x7B-0xFF: zeros */
};
static const unsigned char *ctype_ptr = ctype_table;

int *get_ctype_table(void)
{
    return (int *)&ctype_ptr;
}

/*========================================================================
 * Missing globals referenced by compiled code
 *========================================================================*/

/* QTimer MMIO at 0x004a1000 — mapped by linker script */
volatile uint _DAT_004a1000 __attribute__((section(".mmio_qtimer"))) = 0;

/* Partition table — 32 entries × 3 words each (iterated by mmc_read_ext_csd
 * and mmc_release_slot from 0x08059efc to 0x0805a070 in 12-byte strides).
 * In firehose mode, this is defined in globals.c instead. */
#ifdef MINIMAL_EMBEDDED_PAYLOAD
uint DAT_08059efc[96] = {0};
#endif

/* In embedded mode, protocol-layer functions are guarded out.
 * Provide stubs for functions still referenced by always-compiled code. */
#ifdef MINIMAL_EMBEDDED_PAYLOAD
int handler_poll_usb(void)
{
    return 0;
}

int pmic_set_power(param_1, param_2)
uint param_1; uint param_2;
{
    (void)param_1; (void)param_2;
    return 0;
}
#endif
