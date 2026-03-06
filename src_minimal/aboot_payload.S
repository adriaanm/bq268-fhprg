/*
 * aboot_payload.S — Embedded gzipped aboot image.
 *
 * The payload is linked into .rodata.payload and placed at the end of
 * CODE by the linker script. At runtime, main() decompresses this into
 * a DDR buffer and writes it to the eMMC aboot partition.
 */

    .section .rodata.payload, "a", %progbits
    .balign 4

    .global aboot_payload_gz
    .global aboot_payload_gz_len

aboot_payload_gz:
#ifndef MINIMAL_NO_PAYLOAD
    .incbin "aboot_new.bin.gz"
#endif
aboot_payload_gz_end:

    .balign 4
aboot_payload_gz_len:
    .word aboot_payload_gz_end - aboot_payload_gz
