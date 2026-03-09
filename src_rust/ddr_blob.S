/*
 * ddr_blob.S — DDR driver binary blobs extracted from fhprg_peek.bin.
 *
 * The DDR driver runs from IMEM SRAM (0x00220000). At startup, entry.S
 * copies these blobs to their correct addresses before calling DDR init.
 *
 * Code region: 0x00220000, 10516 bytes (ARM mode)
 * Data region: 0x00223000, 2416 bytes
 */

    /* DDR driver code — copied to 0x00220000 at runtime */
    .section .ddr_code, "a", %progbits
    .balign 4
    .global _ddr_code_start
_ddr_code_start:
    .incbin "tmp/ddr_driver.bin"
_ddr_code_end:
    .global _ddr_code_size
    .set _ddr_code_size, _ddr_code_end - _ddr_code_start

    /* DDR driver data — copied to 0x00223000 at runtime */
    .section .ddr_data, "a", %progbits
    .balign 4
    .global _ddr_data_start
_ddr_data_start:
    .incbin "tmp/ddr_data.bin"
_ddr_data_end:
    .global _ddr_data_size
    .set _ddr_data_size, _ddr_data_end - _ddr_data_start
