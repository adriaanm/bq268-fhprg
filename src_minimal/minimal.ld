/*
 * minimal.ld — Linker script for minimal embedded-payload firehose programmer.
 *
 * Memory map (from fhprg_peek.bin ELF program headers):
 *
 *   0x00220000  IMEM   — DDR driver code (loaded directly by Sahara)
 *   0x00223000  IMEM   — DDR driver data (loaded directly by Sahara)
 *   0x08006000  CODE   — OCIMEM, main program (280 KB)
 *   0x0804c000  DATA   — OCIMEM, initialized data + BSS
 *   0x80000000  DDR    — Decompression buffer (2 MB, no file content)
 *
 * Sahara/PBL loads each LOAD segment to its physical address.
 * The DDR driver blobs are loaded directly to IMEM by Sahara,
 * matching the original fhprg_peek.bin ELF layout.
 */

ENTRY(_start)

MEMORY
{
    /* IMEM SRAM — DDR driver loaded here by Sahara */
    IMEM_CODE (rwx) : ORIGIN = 0x00220000, LENGTH = 0x3000
    IMEM_DATA (rw)  : ORIGIN = 0x00223000, LENGTH = 0x1000

    /* OCIMEM — main program code + embedded payload */
    CODE (rx)  : ORIGIN = 0x08006000, LENGTH = 0x46000  /* 280 KB */

    /* OCIMEM — initialized data and BSS */
    DATA (rw)  : ORIGIN = 0x0804c000, LENGTH = 0x11000  /* 68 KB */

    /* DDR — decompression buffer (no file content, BSS only) */
    DDR  (rw)  : ORIGIN = 0x80000000, LENGTH = 0x200000  /* 2 MB */
}

SECTIONS
{
    /*------------------------------------------------------------------
     * Entry point and main code in OCIMEM
     *------------------------------------------------------------------*/
    /*------------------------------------------------------------------
     * Code layout with reserved addresses for DDR blob callbacks.
     *
     * The DDR blob contains thunks that call back to hardcoded
     * addresses: 0x08006bdc (memcpy) and 0x08006d14 (memset_zero).
     * Entry code first, then pad, then callbacks, then rest of code.
     *------------------------------------------------------------------*/
    .text.early 0x08006000 : {
        *(.text.entry)       /* entry.S — must be first */
    } > CODE

    .ddr_cb_memmove 0x08006b04 : {
        *(.ddr_cb_memmove)
    } > CODE

    .ddr_cb_memcpy 0x08006bdc : {
        *(.ddr_cb_memcpy)
    } > CODE

    .ddr_cb_fast_memcpy 0x08006c40 : {
        *(.ddr_cb_fast_memcpy)
    } > CODE

    .ddr_cb_memset 0x08006d14 : {
        *(.ddr_cb_memset)
    } > CODE

    .ddr_cb_get_ttb 0x08007edc : {
        *(.ddr_cb_get_ttb)
    } > CODE

    .text : {
        *(.text .text.*)     /* all other code */
    } > CODE

    .rodata : {
        *(.rodata .rodata.*)
    } > CODE

    /*------------------------------------------------------------------
     * DDR driver blobs — loaded directly to IMEM by Sahara
     * (VMA == LMA, no runtime copy needed)
     *------------------------------------------------------------------*/
    .ddr_code : {
        *(.ddr_code)
    } > IMEM_CODE

    .ddr_data : {
        *(.ddr_data)
    } > IMEM_DATA

    /*------------------------------------------------------------------
     * Embedded payload — placed at end of CODE region
     *------------------------------------------------------------------*/
    .payload : {
        *(.rodata.payload)
    } > CODE

    /*------------------------------------------------------------------
     * Initialized data — stored in CODE, copied to DATA at runtime
     * (entry.S should handle this, or we keep data tiny enough to skip)
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
        *(.mmio_timer)      /* MMIO timer placeholder */
        *(.mmio_qtimer)     /* QTimer placeholder */
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
        *(.ddr_buf)
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
