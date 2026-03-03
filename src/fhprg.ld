/* Linker script for fhprg_peek recompilation */
ENTRY(FUN_08008780)

MEMORY
{
    CODE (rx) : ORIGIN = 0x08006000, LENGTH = 0x100000
}

SECTIONS
{
    .text 0x08006000 :
    {
        *(.text)
        *(.rodata*)
        *(.rodata.str1.4)
    } > CODE

    /DISCARD/ :
    {
        *(.comment)
        *(.ARM.attributes)
    }
}
