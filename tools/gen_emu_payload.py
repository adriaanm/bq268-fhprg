#!/usr/bin/env python3
"""Generate a small dummy gzip payload for emulator testing."""
import gzip

# 4 sectors of zeros (2048 bytes) — small enough for fast emu, big enough to test write loop
data = b'\x00' * 512 * 4
gz = gzip.compress(data, compresslevel=1)

with open('tmp/emu_payload.bin.gz', 'wb') as f:
    f.write(gz)

with open('tmp/emu_payload.S', 'w') as f:
    f.write('.section .rodata.payload, "a"\n')
    f.write('.global aboot_payload_gz\n')
    f.write('.global aboot_payload_gz_len\n')
    f.write('aboot_payload_gz:\n')
    f.write('.incbin "tmp/emu_payload.bin.gz"\n')
    # Record actual gzip size BEFORE alignment padding
    f.write('.equ aboot_payload_gz_size, . - aboot_payload_gz\n')
    f.write('.balign 4\n')
    f.write('aboot_payload_gz_len:\n')
    f.write('.word aboot_payload_gz_size\n')

print(f"[gen_emu_payload] {len(data)} bytes -> {len(gz)} bytes gzipped")
