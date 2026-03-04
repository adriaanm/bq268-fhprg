/* Linker script to place modified FUN_08034228 at code cave address */
ENTRY(FUN_08034228)

SECTIONS
{
    .text 0x0803dc8c :
    {
        *(.text.FUN_08034228)
    }

    /DISCARD/ :
    {
        *(.comment)
        *(.ARM.attributes)
        *(.ARM.exidx*)
    }
}

/* Function symbols are provided by fhprg_wp_bypass_syms.o
 * with .thumb_set to ensure BL (not BLX) is emitted */
