/* Linker script for fhprg_peek recompilation
 *
 * Per-function section placement: each .text.FUN_xxx is placed at its
 * original virtual address via tmp/fhprg_sections.ld (auto-generated).
 * Symbol resolution via tmp/fhprg_provides.ld (auto-generated).
 */
ENTRY(processEntry_entry)

INCLUDE "tmp/fhprg_provides.ld"

MEMORY
{
    THUNKS (rx) : ORIGIN = 0x00220000, LENGTH = 0x10000
    CODE   (rx) : ORIGIN = 0x08006000, LENGTH = 0x46000
    DATA   (rw) : ORIGIN = 0x0804c000, LENGTH = 0x20000
}

SECTIONS
{
    /* Per-function placements (generated) */
    INCLUDE "tmp/fhprg_sections.ld"

    /* Catch-all for any sections not explicitly placed */
    .text.remainder : {
        *(.text)
        *(.text.*)
    } > CODE

    .rodata : {
        *(.rodata*)
    } > CODE

    .data : {
        *(.data)
    } > DATA

    .bss : {
        *(.bss)
    } > DATA

    .got : { *(.got) *(.got.plt) } > CODE

    /DISCARD/ :
    {
        *(.comment)
        *(.ARM.attributes)
        *(.ARM.exidx*)
        *(.eh_frame)
        *(.rel.*)
    }
}
