/*
 * minimal.ld — Linker script for Rust minimal programmer.
 *
 * Same memory layout as src_minimal/minimal.ld.
 * Rust staticlib linked with assembly objects.
 */

ENTRY(_start)

MEMORY
{
    /* IMEM SRAM — DDR driver loaded here by Sahara */
    IMEM_CODE (rwx) : ORIGIN = 0x00220000, LENGTH = 0x3000
    IMEM_DATA (rw)  : ORIGIN = 0x00223000, LENGTH = 0x1000

    /* OCIMEM — main program code */
    CODE (rx)  : ORIGIN = 0x08006000, LENGTH = 0x46000  /* 280 KB */

    /* OCIMEM — initialized data and BSS */
    DATA (rw)  : ORIGIN = 0x0804c000, LENGTH = 0x11000  /* 68 KB */

    /* DDR — buffers (no file content, BSS only) */
    DDR  (rw)  : ORIGIN = 0x80000000, LENGTH = 0x200000  /* 2 MB */
}

SECTIONS
{
    /*------------------------------------------------------------------
     * Entry point and main code in OCIMEM
     *------------------------------------------------------------------*/
    .text.early 0x08006000 : {
        KEEP(*(.text.entry))       /* entry.S — must be first */
    } > CODE

    /* DDR blob callback stubs at fixed addresses */
    .ddr_cb_memmove 0x08006b04 : {
        KEEP(*(.ddr_cb_memmove))
    } > CODE

    .ddr_cb_memcpy 0x08006bdc : {
        KEEP(*(.ddr_cb_memcpy))
    } > CODE

    .ddr_cb_fast_memcpy 0x08006c40 : {
        KEEP(*(.ddr_cb_fast_memcpy))
    } > CODE

    .ddr_cb_memset 0x08006d14 : {
        KEEP(*(.ddr_cb_memset))
    } > CODE

    .ddr_cb_get_ttb 0x08007edc : {
        KEEP(*(.ddr_cb_get_ttb))
    } > CODE

    .ddr_cb_pagetable 0x08016dd4 : {
        KEEP(*(.ddr_cb_pagetable))
    } > CODE

    .ddr_cb_busconfig 0x08016f5c : {
        KEEP(*(.ddr_cb_busconfig))
    } > CODE

    .ddr_cb_memtest 0x0801ad44 : {
        KEEP(*(.ddr_cb_memtest))
    } > CODE

    .ddr_cb_memtest_wrap 0x0801afc4 : {
        KEEP(*(.ddr_cb_memtest_wrap))
    } > CODE

    .text : {
        *(.text .text.*)
    } > CODE

    .rodata : {
        *(.rodata .rodata.*)
    } > CODE

    /*------------------------------------------------------------------
     * DDR driver blobs — loaded directly to IMEM by Sahara
     *------------------------------------------------------------------*/
    .ddr_code : {
        KEEP(*(.ddr_code))
    } > IMEM_CODE

    .ddr_data : {
        KEEP(*(.ddr_data))
    } > IMEM_DATA

    /*------------------------------------------------------------------
     * Initialized data — stored in CODE, copied to DATA at runtime
     *------------------------------------------------------------------*/
    .data : {
        _data_start = .;
        *(.data .data.*)
        _data_end = .;
    } > DATA AT> CODE
    _data_load = LOADADDR(.data);

    /*------------------------------------------------------------------
     * BSS — zero-initialized by entry.S
     *------------------------------------------------------------------*/
    .bss (NOLOAD) : {
        __bss_start = .;
        *(.bss .bss.* COMMON)
        *(.mmio_timer)
        *(.mmio_qtimer)
        . = ALIGN(4);
        __bss_end = .;
    } > DATA

    /*------------------------------------------------------------------
     * Stack — top of DATA region
     *------------------------------------------------------------------*/
    _stack_top = ORIGIN(DATA) + LENGTH(DATA);

    /*------------------------------------------------------------------
     * DDR buffer — no file content, just reserve address space
     *------------------------------------------------------------------*/
    .ddr_buf (NOLOAD) : {
        KEEP(*(.ddr_buf))
        KEEP(*(.ddr_bss))
    } > DDR

    /*------------------------------------------------------------------
     * Discard unwanted sections
     *------------------------------------------------------------------*/
    /DISCARD/ : {
        *(.comment)
        *(.note.*)
        *(.ARM.attributes)
        *(.ARM.exidx*)
    }
}
