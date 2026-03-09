/*
 * ddr_config.S — Embedded DDR configuration data from CDT entry[1].
 *
 * This is the 760-byte DDR config blob extracted from the original
 * fhprg_peek.bin CDT (Config Data Table) at file offset 0x3b780.
 *
 * Structure:
 *   [0]  = 1          (version)
 *   [4]  = 0x44445200 ("DDR\0" magic)
 *   [32] = 5          (DDR type: LPDDR3)
 *
 * See docs/ddr_init.md for full documentation.
 */

    .section .rodata.ddr_config, "a", %progbits
    .balign 4

    .global ddr_config_data
    .global ddr_config_data_len

ddr_config_data:
    .incbin "src_minimal/ddr_config.bin"
ddr_config_data_end:

    .balign 4
ddr_config_data_len:
    .word ddr_config_data_end - ddr_config_data
