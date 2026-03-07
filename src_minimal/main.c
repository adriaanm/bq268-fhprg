/* main.c — Embedded payload mode: USB diagnostic console.
 *
 * This runs after entry.S has initialized hardware (BIMC clocks, DDR, SDCC).
 * Instead of flashing aboot, it provides a USB diagnostic interface for
 * probing registers, memory, and debugging the DDR init sequence.
 *
 * Protocol (text over USB bulk):
 *   r XXXXXXXX          — read 32-bit word at hex address
 *   w XXXXXXXX YYYYYYYY — write 32-bit value to hex address
 *   d XXXXXXXX NNNN     — hex dump NNNN bytes from address
 *   i                    — dump CP15 and system info
 *   t                    — test DDR read/write
 */

#ifdef MINIMAL_EMBEDDED_PAYLOAD

#include "firehose.h"
#include "msm8909.h"
#include "usb.h"

/*========================================================================
 * External symbols from aboot_payload.S (keep linker happy)
 *========================================================================*/
extern const unsigned char aboot_payload_gz[];
extern const unsigned int  aboot_payload_gz_len;

/*========================================================================
 * GPIO LED helpers — MSM8909 TLMM
 *========================================================================*/

#define REG32(addr)  (*(volatile unsigned int *)(addr))

static void led_init(int gpio)
{
    REG32(GPIO_CFG_ADDR(gpio)) =
          (GPIO_NO_PULL << GPIO_PULL_SHIFT)
        | (0            << GPIO_FUNC_SHIFT)
        | (GPIO_2MA     << GPIO_DRV_SHIFT)
        | (GPIO_OE_ENABLE << GPIO_OE_SHIFT);
}

static void led_on(int gpio)
{
    REG32(GPIO_IN_OUT_ADDR(gpio)) = GPIO_OUT_BIT;
}

static void led_off(int gpio)
{
    REG32(GPIO_IN_OUT_ADDR(gpio)) = 0;
}

/*========================================================================
 * Page table setup — create our own L1 page table in OCIMEM
 *
 * PBL's page table may not map all regions we need (e.g. USB at 0x07Fxxxxx).
 * Rather than guessing what PBL mapped, create a complete table.
 * 16KB, 16KB-aligned, covers full 4GB address space.
 *========================================================================*/
unsigned int page_table[4096] __attribute__((aligned(16384)));

/* Section descriptor: 1MB mapping, AP=full access, domain 0.
 * Device memory: TEX=0 C=0 B=1 (Device, non-cacheable)
 * Normal memory: TEX=0 C=1 B=1 (Write-Back, Write-Allocate) */
#define SECT_DEV(addr)  (((addr) & 0xFFF00000u) | (3 << 10) | (1 << 2) | 2)
#define SECT_MEM(addr)  (((addr) & 0xFFF00000u) | (3 << 10) | (1 << 3) | (1 << 2) | 2)
#define SECT_NC(addr)   (((addr) & 0xFFF00000u) | (3 << 10) | 2)  /* strongly ordered */

/*========================================================================
 * Early page table setup — called from entry.S before GPLL0
 *
 * Maps 128MB IO region (0x000-0x07F) as Device, OCIMEM as Normal,
 * SYSTEM_IMEM as Device.  Does NOT map DDR (not initialized yet).
 * Ensures all peripheral regions are accessible with correct memory
 * attributes regardless of what PBL's page table covers.
 *========================================================================*/
void setup_early_page_table(void)
{
    int i;

    /* Start with all fault entries */
    for (i = 0; i < 4096; i++)
        page_table[i] = 0;

    /* 0x00000000-0x07FFFFFF: 128MB IO (Boot ROM, IMEM, BIMC, TLMM, GCC, PERIPH_SS) */
    for (i = 0; i < 0x80; i++)
        page_table[i] = SECT_DEV(i << 20);

    /* 0x08000000-0x080FFFFF: OCIMEM (code + data + BSS + stack) */
    page_table[0x80] = SECT_MEM(0x08000000);

    /* 0x08600000: SYSTEM_IMEM (DDR config destination) */
    page_table[0x86] = SECT_DEV(0x08600000);

    /* DDR not mapped yet — not initialized */

    /* Clean page table from D-cache to physical memory */
    {
        unsigned int a;
        for (a = (unsigned int)page_table;
             a < (unsigned int)page_table + sizeof(page_table);
             a += 32)
            __asm__ volatile("mcr p15, 0, %0, c7, c14, 1" :: "r"(a));
    }
    __asm__ volatile("dsb" ::: "memory");

    /* Switch TTBR0 to our page table */
    {
        unsigned int ttbr0_val = (unsigned int)page_table
                               | (1 << 0)   /* IRGN[0] = 1 → IRGN=01 */
                               | (1 << 3);  /* RGN = 01 */
        __asm__ volatile("mcr p15, 0, %0, c2, c0, 0" :: "r"(ttbr0_val));
    }

    /* Invalidate entire TLB */
    __asm__ volatile("mcr p15, 0, %0, c8, c7, 0" :: "r"(0));

    __asm__ volatile("dsb" ::: "memory");
    __asm__ volatile("isb");
}

static void setup_page_table(void)
{
    int i;

    /* Start with all fault entries */
    for (i = 0; i < 4096; i++)
        page_table[i] = 0;

    /* 0x00000000-0x002FFFFF: Boot ROM + IMEM (DDR blob at 0x00220000) */
    for (i = 0; i <= 2; i++)
        page_table[i] = SECT_DEV(i << 20);

    /* 0x00400000-0x004FFFFF: BIMC + MPM2 timetick */
    page_table[4] = SECT_DEV(0x00400000);

    /* 0x01000000-0x010FFFFF: TLMM (GPIO) */
    page_table[0x10] = SECT_DEV(0x01000000);

    /* 0x01800000-0x018FFFFF: GCC (clocks) */
    page_table[0x18] = SECT_DEV(0x01800000);

    /* 0x07800000-0x07FFFFFF: PERIPH_SS (SDCC at 0x07824000, USB at 0x07FD9000) */
    for (i = 0x78; i <= 0x7F; i++)
        page_table[i] = SECT_DEV(i << 20);

    /* 0x08000000-0x080FFFFF: OCIMEM (code + data + BSS + stack) */
    page_table[0x80] = SECT_MEM(0x08000000);

    /* 0x08600000: SYSTEM_IMEM (DDR config destination) */
    page_table[0x86] = SECT_DEV(0x08600000);

    /* 0x80000000-0x87FFFFFF: DDR (128MB) */
    for (i = 0x800; i <= 0x87F; i++)
        page_table[i] = SECT_MEM(i << 20);

    /* Clean page table from D-cache to physical memory.
     * The HW page table walker reads from physical RAM, not cache.
     * DCCIMVAC = Data Cache Clean and Invalidate by MVA to PoC. */
    {
        unsigned int a;
        for (a = (unsigned int)page_table;
             a < (unsigned int)page_table + sizeof(page_table);
             a += 32)
            __asm__ volatile("mcr p15, 0, %0, c7, c14, 1" :: "r"(a));
    }
    __asm__ volatile("dsb" ::: "memory");

    /* Switch TTBR0 to our page table.
     * Set cacheable walk bits: IRGN=01 (WB-WA), RGN=01 (WB-WA)
     * so future walks can use cache. */
    {
        unsigned int ttbr0_val = (unsigned int)page_table
                               | (1 << 0)   /* IRGN[0] = 1 → IRGN=01 */
                               | (1 << 3);  /* RGN = 01 */
        __asm__ volatile("mcr p15, 0, %0, c2, c0, 0" :: "r"(ttbr0_val));
    }

    /* Invalidate entire TLB */
    __asm__ volatile("mcr p15, 0, %0, c8, c7, 0" :: "r"(0));

    /* Ensure everything takes effect */
    __asm__ volatile("dsb" ::: "memory");
    __asm__ volatile("isb");
}

/*========================================================================
 * ICB config — BIMC QoS/arbitration registers
 *========================================================================*/
void icb_config(void)
{
    REG32(0x00449210) = 0x00000001;
    REG32(0x00450230) = 0x00000000;

    REG32(0x00408210) = 0x00000012;
    REG32(0x0040c210) = 0x00000012;
    REG32(0x00410210) = 0x00000012;
    REG32(0x00414210) = 0x00000012;
    REG32(0x00418210) = 0x80000012;
    REG32(0x0041c210) = 0x00000012;
    REG32(0x00420210) = 0x00000012;

    REG32(0x00408270) = 0x00043210;
    REG32(0x00408274) = 0x00043210;
    REG32(0x00408a04) = 0x00000014;
    REG32(0x00408a08) = 0x00000064;
    REG32(0x00408a24) = 0x0000ffce;
    REG32(0x00408a28) = 0x0000ff9c;
    REG32(0x00408a40) = 0x80000000;
    REG32(0x00408300) = 0x01000000;
    REG32(0x00408800) = 0x02000000;
    REG32(0x00408a00) = 0xfc000001;

    REG32(0x00410a04) = 0x00000014;
    REG32(0x00410a08) = 0x00000064;
    REG32(0x00410a24) = 0x0000ffce;
    REG32(0x00410a28) = 0x0000ff9c;
    REG32(0x00410a40) = 0x80000000;
    REG32(0x00410300) = 0x01000000;
    REG32(0x00410800) = 0x02000000;
    REG32(0x00410a00) = 0xfc000001;

    REG32(0x00400904) = 0x00000206;
    REG32(0x00400908) = 0x00600060;
    REG32(0x0040090c) = 0x00270027;
    REG32(0x00400940) = 0x00000010;
    REG32(0x00400900) = 0x00000001;
}

/*========================================================================
 * Simple formatting helpers (no printf/snprintf needed)
 *========================================================================*/

static const char hex_chars[] = "0123456789abcdef";

/* Append hex word (8 chars) to buffer, return new position */
static int put_hex32(char *buf, int pos, unsigned int val)
{
    int i;
    for (i = 28; i >= 0; i -= 4)
        buf[pos++] = hex_chars[(val >> i) & 0xF];
    return pos;
}

/* Append hex byte (2 chars) to buffer */
static int put_hex8(char *buf, int pos, unsigned char val)
{
    buf[pos++] = hex_chars[(val >> 4) & 0xF];
    buf[pos++] = hex_chars[val & 0xF];
    return pos;
}

/* Append string to buffer */
static int put_str(char *buf, int pos, const char *s)
{
    while (*s)
        buf[pos++] = *s++;
    return pos;
}

/* Append decimal number to buffer */
static int put_dec(char *buf, int pos, unsigned int val)
{
    char tmp[12];
    int i = 0;
    if (val == 0) {
        buf[pos++] = '0';
        return pos;
    }
    while (val > 0) {
        tmp[i++] = '0' + (val % 10);
        val /= 10;
    }
    while (i > 0)
        buf[pos++] = tmp[--i];
    return pos;
}

/* Parse hex string to uint32. Returns 0 on empty input. */
static unsigned int parse_hex(const char *s)
{
    unsigned int val = 0;
    while (*s) {
        char c = *s++;
        if (c >= '0' && c <= '9')      val = (val << 4) | (c - '0');
        else if (c >= 'a' && c <= 'f')  val = (val << 4) | (c - 'a' + 10);
        else if (c >= 'A' && c <= 'F')  val = (val << 4) | (c - 'A' + 10);
        else break;
    }
    return val;
}

/* Skip whitespace, return pointer to next non-space char */
static const char *skip_ws(const char *s)
{
    while (*s == ' ' || *s == '\t') s++;
    return s;
}

/* Skip non-whitespace, return pointer to next space/null */
static const char *skip_nonws(const char *s)
{
    while (*s && *s != ' ' && *s != '\t' && *s != '\r' && *s != '\n') s++;
    return s;
}

/*========================================================================
 * CP15 register read helpers
 *========================================================================*/

static unsigned int read_sctlr(void)
{
    unsigned int val;
    __asm__ volatile("mrc p15, 0, %0, c1, c0, 0" : "=r"(val));
    return val;
}

static unsigned int read_ttbr0(void)
{
    unsigned int val;
    __asm__ volatile("mrc p15, 0, %0, c2, c0, 0" : "=r"(val));
    return val;
}

static unsigned int read_ttbr1(void)
{
    unsigned int val;
    __asm__ volatile("mrc p15, 0, %0, c2, c0, 1" : "=r"(val));
    return val;
}

static unsigned int read_ttbcr(void)
{
    unsigned int val;
    __asm__ volatile("mrc p15, 0, %0, c2, c0, 2" : "=r"(val));
    return val;
}

static unsigned int read_dacr(void)
{
    unsigned int val;
    __asm__ volatile("mrc p15, 0, %0, c3, c0, 0" : "=r"(val));
    return val;
}

static unsigned int read_dfsr(void)
{
    unsigned int val;
    __asm__ volatile("mrc p15, 0, %0, c5, c0, 0" : "=r"(val));
    return val;
}

static unsigned int read_dfar(void)
{
    unsigned int val;
    __asm__ volatile("mrc p15, 0, %0, c6, c0, 0" : "=r"(val));
    return val;
}

static unsigned int read_vbar(void)
{
    unsigned int val;
    __asm__ volatile("mrc p15, 0, %0, c12, c0, 0" : "=r"(val));
    return val;
}

/*========================================================================
 * USB response buffer
 *========================================================================*/

static char resp[4096] __attribute__((aligned(32)));
static char cmd_buf[512] __attribute__((aligned(32)));

/*========================================================================
 * Command: info dump
 *========================================================================*/
static void cmd_info(void)
{
    int p = 0;

    p = put_str(resp, p, "=== MSM8909 Diagnostic Console ===\r\n");

    p = put_str(resp, p, "SCTLR:  "); p = put_hex32(resp, p, read_sctlr()); p = put_str(resp, p, "\r\n");
    p = put_str(resp, p, "TTBR0:  "); p = put_hex32(resp, p, read_ttbr0()); p = put_str(resp, p, "\r\n");
    p = put_str(resp, p, "TTBR1:  "); p = put_hex32(resp, p, read_ttbr1()); p = put_str(resp, p, "\r\n");
    p = put_str(resp, p, "TTBCR:  "); p = put_hex32(resp, p, read_ttbcr()); p = put_str(resp, p, "\r\n");
    p = put_str(resp, p, "DACR:   "); p = put_hex32(resp, p, read_dacr());  p = put_str(resp, p, "\r\n");
    p = put_str(resp, p, "DFSR:   "); p = put_hex32(resp, p, read_dfsr());  p = put_str(resp, p, "\r\n");
    p = put_str(resp, p, "DFAR:   "); p = put_hex32(resp, p, read_dfar());  p = put_str(resp, p, "\r\n");
    p = put_str(resp, p, "VBAR:   "); p = put_hex32(resp, p, read_vbar());  p = put_str(resp, p, "\r\n");

    /* Page table entries for key address ranges */
    unsigned int ttbr0 = read_ttbr0() & 0xFFFFC000u;
    unsigned int ttbcr_n = read_ttbcr() & 7;
    p = put_str(resp, p, "\r\nPage table base: ");
    p = put_hex32(resp, p, ttbr0);
    p = put_str(resp, p, " (N=");
    p = put_dec(resp, p, ttbcr_n);
    p = put_str(resp, p, ")\r\n");

    /* Dump page table entries for interesting addresses */
    static const struct { unsigned int addr; const char *name; } pte_addrs[] = {
        { 0x00000000, "0x000 (boot ROM)" },
        { 0x00200000, "0x002 (IMEM)" },
        { 0x00400000, "0x004 (BIMC)" },
        { 0x00800000, "0x008 (LPASS)" },
        { 0x01000000, "0x010 (TLMM)" },
        { 0x01800000, "0x018 (GCC)" },
        { 0x07800000, "0x078 (PERIPH)" },
        { 0x07F00000, "0x07F (USB)" },
        { 0x08000000, "0x080 (OCIMEM)" },
        { 0x80000000, "0x800 (DDR)" },
        { 0x80100000, "0x801 (DDR+1M)" },
        { 0x87C00000, "0x87C (DDR hi)" },
    };
    int i;
    p = put_str(resp, p, "\r\nL1 page table entries:\r\n");
    for (i = 0; i < (int)(sizeof(pte_addrs)/sizeof(pte_addrs[0])); i++) {
        unsigned int idx = pte_addrs[i].addr >> 20;
        volatile unsigned int *pte = (volatile unsigned int *)(ttbr0 + idx * 4);
        p = put_str(resp, p, "  [");
        p = put_str(resp, p, pte_addrs[i].name);
        p = put_str(resp, p, "] = ");
        p = put_hex32(resp, p, *pte);
        p = put_str(resp, p, "\r\n");
    }

    p = put_str(resp, p, "> ");
    usb_write(resp, p);
}

/*========================================================================
 * Command: read word
 *========================================================================*/
static void cmd_read(const char *args)
{
    unsigned int addr = parse_hex(args);
    volatile unsigned int *ptr = (volatile unsigned int *)addr;
    unsigned int val;
    int p = 0;

    __asm__ volatile("dsb" ::: "memory");
    val = *ptr;

    p = put_hex32(resp, p, addr);
    p = put_str(resp, p, ": ");
    p = put_hex32(resp, p, val);
    p = put_str(resp, p, "\r\n> ");

    usb_write(resp, p);
}

/*========================================================================
 * Command: write word
 *========================================================================*/
static void cmd_write(const char *args)
{
    const char *p1 = skip_ws(args);
    unsigned int addr = parse_hex(p1);
    const char *p2 = skip_ws(skip_nonws(p1));
    unsigned int val = parse_hex(p2);
    volatile unsigned int *ptr = (volatile unsigned int *)addr;
    int p = 0;

    *ptr = val;
    __asm__ volatile("dsb" ::: "memory");

    p = put_str(resp, p, "OK ");
    p = put_hex32(resp, p, addr);
    p = put_str(resp, p, " = ");
    p = put_hex32(resp, p, val);
    p = put_str(resp, p, "\r\n> ");

    usb_write(resp, p);
}

/*========================================================================
 * Command: hex dump
 *========================================================================*/
static void cmd_dump(const char *args)
{
    const char *p1 = skip_ws(args);
    unsigned int addr = parse_hex(p1);
    const char *p2 = skip_ws(skip_nonws(p1));
    unsigned int len = parse_hex(p2);
    unsigned int i;
    int p = 0;

    if (len == 0) len = 0x40;
    if (len > 0x400) len = 0x400;  /* cap at 1KB per dump */

    volatile unsigned char *src = (volatile unsigned char *)addr;

    for (i = 0; i < len; i++) {
        if ((i & 0xF) == 0) {
            if (i > 0) { p = put_str(resp, p, "\r\n"); }
            p = put_hex32(resp, p, addr + i);
            p = put_str(resp, p, ": ");
        }
        p = put_hex8(resp, p, src[i]);
        p = put_str(resp, p, " ");

        /* Flush buffer if getting full */
        if (p > 3800) {
            usb_write(resp, p);
            p = 0;
        }
    }
    p = put_str(resp, p, "\r\n> ");
    usb_write(resp, p);
}

/*========================================================================
 * Command: DDR test
 *
 * WARNING: If DDR address is not mapped in the page table, this will
 * trigger a data abort. Check 'i' output first to verify the PTE for
 * 0x800 exists. Use 'r 80000000' to test a single read first.
 *========================================================================*/
static void cmd_ddr_test(void)
{
    volatile unsigned int *ddr = (volatile unsigned int *)SDRAM_START_ADDR;
    unsigned int ttbr0 = read_ttbr0() & 0xFFFFC000u;
    unsigned int pte = *(volatile unsigned int *)(ttbr0 + (0x800 * 4));
    int p = 0;

    p = put_str(resp, p, "DDR test at ");
    p = put_hex32(resp, p, SDRAM_START_ADDR);
    p = put_str(resp, p, "\r\n");
    p = put_str(resp, p, "PTE[0x800] = ");
    p = put_hex32(resp, p, pte);
    p = put_str(resp, p, "\r\n");

    if ((pte & 3) == 0) {
        p = put_str(resp, p, "FAULT: no page table entry for DDR!\r\n");
        p = put_str(resp, p, "DDR access would cause data abort.\r\n");
        usb_write(resp, p);
        return;
    }

    /* Write test pattern */
    ddr[0] = 0xDEADBEEF;
    ddr[1] = 0xCAFEBABE;
    ddr[2] = 0x12345678;
    ddr[3] = 0x00000000;
    __asm__ volatile("dsb" ::: "memory");

    /* Read back */
    p = put_str(resp, p, "  [0] = "); p = put_hex32(resp, p, ddr[0]);
    p = put_str(resp, p, (ddr[0] == 0xDEADBEEF) ? " OK\r\n" : " FAIL\r\n");
    p = put_str(resp, p, "  [1] = "); p = put_hex32(resp, p, ddr[1]);
    p = put_str(resp, p, (ddr[1] == 0xCAFEBABE) ? " OK\r\n" : " FAIL\r\n");
    p = put_str(resp, p, "  [2] = "); p = put_hex32(resp, p, ddr[2]);
    p = put_str(resp, p, (ddr[2] == 0x12345678) ? " OK\r\n" : " FAIL\r\n");
    p = put_str(resp, p, "  [3] = "); p = put_hex32(resp, p, ddr[3]);
    p = put_str(resp, p, (ddr[3] == 0x00000000) ? " OK\r\n" : " FAIL\r\n");

    p = put_str(resp, p, "> ");
    usb_write(resp, p);
}

/*========================================================================
 * main — entry point from assembly
 *
 * At this point entry.S has already:
 *   - Set up early page table (IO + OCIMEM, no DDR)
 *   - Locked GPLL0 and enabled early clocks
 *   - Called ddr_set_params, bimc_clock_init, ddr_init (533 MHz)
 *   - DDR is initialized and available
 *========================================================================*/
void main(void)
{
    int n, p;
    static const char banner[] = "=== MSM8909 Diag Console ===\r\n> ";

    (void)aboot_payload_gz;
    (void)aboot_payload_gz_len;

    led_init(LED_RED_GPIO);
    led_init(LED_GREEN_GPIO);
    led_off(LED_RED_GPIO);
    led_off(LED_GREEN_GPIO);

    /* Inherit PBL's USB session — online immediately, no re-enumeration.
     * PBL's page table already maps DDR — no setup_page_table() needed. */
    usb_init();

    /* Send banner */
    usb_write(banner, sizeof(banner) - 1);

    /* Command loop */
    for (;;) {
        n = usb_read(cmd_buf, sizeof(cmd_buf) - 1);
        if (n <= 0)
            continue;

        cmd_buf[n] = '\0';

        /* Strip trailing newlines */
        while (n > 0 && (cmd_buf[n-1] == '\r' || cmd_buf[n-1] == '\n'))
            cmd_buf[--n] = '\0';

        if (n == 0) {
            usb_write("> ", 2);  /* no prior TX, just RX→TX — safe */
            continue;
        }

        /* Toggle red LED on each command (activity indicator) */
        led_on(LED_RED_GPIO);

        switch (cmd_buf[0]) {
        case 'i': case 'I':
            cmd_info();
            break;
        case 'r': case 'R':
            cmd_read(skip_ws(cmd_buf + 1));
            break;
        case 'w': case 'W':
            cmd_write(cmd_buf + 1);
            break;
        case 'd': case 'D':
            cmd_dump(cmd_buf + 1);
            break;
        case 't': case 'T':
            cmd_ddr_test();
            break;
        default:
            p = 0;
            p = put_str(resp, p, "? unknown cmd\r\n> ");
            usb_write(resp, p);
            break;
        }

        led_off(LED_RED_GPIO);
    }
}

#endif /* MINIMAL_EMBEDDED_PAYLOAD */
