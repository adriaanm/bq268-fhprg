/* libc_glue.h — Map decompiled FUN_ names to standard libc functions.
 *
 * The original firmware has its own implementations of these standard
 * functions. In a freestanding build, we declare them ourselves.
 * At link time they resolve to either the firmware's implementations
 * or to compiler builtins.
 */
#pragma once

#include <stdarg.h>

/* Freestanding libc declarations — these are builtins in clang/gcc */
typedef unsigned int size_t_fh;  /* avoid conflict with stddef size_t */
void *memcpy(void *dst, const void *src, size_t n);
void *memmove(void *dst, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
int   memcmp(const void *s1, const void *s2, size_t n);
size_t strlen(const char *s);
char *strchr(const char *s, int c);
char *strstr(const char *haystack, const char *needle);
char *strrchr(const char *s, int c);
int   snprintf(char *buf, size_t size, const char *fmt, ...);
int   vsnprintf(char *buf, size_t size, const char *fmt, va_list ap);

/* String functions */
#define FUN_08006906  strlen      /* orig: 0x08006906 */
#define FUN_08006898  memcmp      /* orig: 0x08006898 */
#define FUN_08006860  strchr      /* orig: 0x08006860 */
#define FUN_08006874  strstr      /* orig: 0x08006874 */
#define FUN_080068f0  strrchr     /* orig: 0x080068f0 */

/* Memory functions */
#define FUN_08006a30  memcpy      /* orig: 0x08006a30 */
#define FUN_08006d14  memset_zero /* orig: 0x08006d14 — memset(p, 0, n) wrapper */
#define FUN_08006bdc  memmove     /* orig: 0x08006bdc */

/* The original FUN_08006d14 is memset(p, 0, n) — two-arg form */
static inline void memset_zero(void *p, unsigned int n) {
    memset(p, 0, n);
}

/* snprintf — the original firmware's snprintf_buf */
#define snprintf_buf  snprintf    /* orig: 0x0800644c */
#define FUN_08006418  vsnprintf_wrapper /* orig: 0x08006418 — vsnprintf(buf, n, fmt, va_list*) */

/* The original FUN_08006418 takes a pointer to the va_list on stack.
 * In the decompiled code it's called as FUN_08006418(buf, size, fmt, &args).
 * We provide a wrapper that matches this calling convention. */
static inline int vsnprintf_wrapper(char *buf, unsigned int size,
                                     const char *fmt, va_list *ap) {
    return vsnprintf(buf, size, fmt, *ap);
}

/* 64-bit division — the original has a custom divmod for uint64_t.
 * With a real toolchain, the compiler handles this natively. */
/* FUN_080060c0 is __aeabi_uldivmod — just use C / and % operators */

/* ctype-like function used by XML tokenizer */
/* FUN_080060b0 returns pointer to ctype table; we provide our own */
