#!/usr/bin/env python3
"""
mbn_wrap.py — Add Qualcomm MBN hash table to a bare ELF for Sahara loading.

The Qualcomm PBL (Primary Boot Loader) requires an MBN hash table segment
in the ELF even on unlocked devices (status 0x23 = HashTableNotFound).

This script:
1. Reads a linked ELF (e.g., tmp/minimal.elf)
2. Strips section headers
3. Adds two NULL program headers (MBN header + hash table)
4. Fixes segment flags/alignment to match original fhprg_peek.bin
5. Computes SHA-256 hashes for each segment
6. Writes a Sahara-compatible ELF

Hash table layout (matching fhprg_peek.bin):
  - 40-byte MBN hash header
  - N × 32-byte SHA-256 hashes (one per program header)
  - 0x100 bytes signature (zeros for unlocked)
  - 0x1800 bytes cert chain (zeros for unlocked)
"""

import struct
import hashlib
import sys

# ELF constants
ELF32_EHDR_SIZE = 52
ELF32_PHDR_SIZE = 32
PT_NULL = 0
PT_LOAD = 1
PF_X = 1
PF_W = 2
PF_R = 4

# MBN constants
MBN_IMAGE_ID = 0x15       # firehose programmer
MBN_VERSION = 3
HASH_SIZE = 32             # SHA-256
SIG_SIZE = 0x100           # signature placeholder
CERT_CHAIN_SIZE = 0x1800   # cert chain placeholder
HASH_SEG_VADDR = 0x87c5a000  # from original fhprg_peek.bin

# Segment flags/alignment overrides to match original fhprg_peek.bin
# {vaddr: (flags, align)}
PF_QC_MAIN = 0x80000000  # Qualcomm-specific: marks main executable segment

# Segment flags/alignment overrides to match original fhprg_peek.bin
# {vaddr: (flags, align)}
SEG_OVERRIDES = {
    0x00220000: (PF_R | PF_X, 0x10),            # IMEM_CODE: R E
    0x00223000: (PF_R | PF_W, 0x8),             # IMEM_DATA: RW
    0x08006000: (PF_R | PF_X | PF_QC_MAIN, 0x20),  # CODE: R E + QC main flag
    0x0804c000: (PF_R | PF_W, 0x1000),           # DATA: RW
}


def parse_elf32_ehdr(data):
    fields = struct.unpack_from('<16sHHIIIIIHHHHHH', data, 0)
    return {
        'e_ident': fields[0],
        'e_type': fields[1],
        'e_machine': fields[2],
        'e_version': fields[3],
        'e_entry': fields[4],
        'e_phoff': fields[5],
        'e_shoff': fields[6],
        'e_flags': fields[7],
        'e_ehsize': fields[8],
        'e_phentsize': fields[9],
        'e_phnum': fields[10],
        'e_shentsize': fields[11],
        'e_shnum': fields[12],
        'e_shstrndx': fields[13],
    }


def pack_elf32_ehdr(h):
    return struct.pack('<16sHHIIIIIHHHHHH',
        h['e_ident'], h['e_type'], h['e_machine'], h['e_version'],
        h['e_entry'], h['e_phoff'], h['e_shoff'], h['e_flags'],
        h['e_ehsize'], h['e_phentsize'], h['e_phnum'],
        h['e_shentsize'], h['e_shnum'], h['e_shstrndx'])


def parse_elf32_phdr(data, offset):
    fields = struct.unpack_from('<IIIIIIII', data, offset)
    return {
        'p_type': fields[0],
        'p_offset': fields[1],
        'p_vaddr': fields[2],
        'p_paddr': fields[3],
        'p_filesz': fields[4],
        'p_memsz': fields[5],
        'p_flags': fields[6],
        'p_align': fields[7],
    }


def pack_elf32_phdr(p):
    return struct.pack('<IIIIIIII',
        p['p_type'], p['p_offset'], p['p_vaddr'], p['p_paddr'],
        p['p_filesz'], p['p_memsz'], p['p_flags'], p['p_align'])


def align_up(val, alignment):
    if alignment <= 1:
        return val
    return (val + alignment - 1) & ~(alignment - 1)


def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <input.elf> [output.elf]")
        sys.exit(1)

    in_path = sys.argv[1]
    out_path = sys.argv[2] if len(sys.argv) > 2 else in_path

    with open(in_path, 'rb') as f:
        elf_data = f.read()

    ehdr = parse_elf32_ehdr(elf_data)
    assert ehdr['e_ident'][:4] == b'\x7fELF', "Not an ELF file"
    assert ehdr['e_ident'][4] == 1, "Not ELF32"
    assert ehdr['e_machine'] == 40, "Not ARM"

    # Parse existing program headers
    orig_phdrs = []
    for i in range(ehdr['e_phnum']):
        off = ehdr['e_phoff'] + i * ehdr['e_phentsize']
        orig_phdrs.append(parse_elf32_phdr(elf_data, off))

    # Keep only LOAD segments
    load_phdrs = [p for p in orig_phdrs if p['p_type'] == PT_LOAD]
    print(f"[mbn] Input: {len(orig_phdrs)} phdrs, {len(load_phdrs)} LOAD segments")

    # Apply flag/alignment overrides and fix paddr
    for p in load_phdrs:
        if p['p_vaddr'] in SEG_OVERRIDES:
            flags, align = SEG_OVERRIDES[p['p_vaddr']]
            p['p_flags'] = flags
            p['p_align'] = align
        # PBL expects p_paddr == p_vaddr (original has this for all segments)
        p['p_paddr'] = p['p_vaddr']

    # Extra segments to match original fhprg_peek.bin layout
    extra_segs = [
        # BSS region at 0x08046000 (original has this, filesz=0, memsz=0x6000)
        {'p_type': PT_LOAD, 'p_offset': 0, 'p_vaddr': 0x08046000,
         'p_paddr': 0x08046000, 'p_filesz': 0, 'p_memsz': 0x6000,
         'p_flags': PF_R | PF_W, 'p_align': 0x4},
        # DDR decompression buffer (matches original)
        {'p_type': PT_LOAD, 'p_offset': 0, 'p_vaddr': 0x80000000,
         'p_paddr': 0x80000000, 'p_filesz': 0, 'p_memsz': 0x201400,
         'p_flags': PF_R | PF_W, 'p_align': 0x1000},
        # DDR region 2 (matches original)
        {'p_type': PT_LOAD, 'p_offset': 0, 'p_vaddr': 0x87c00000,
         'p_paddr': 0x87c00000, 'p_filesz': 0, 'p_memsz': 0x59e98,
         'p_flags': PF_R | PF_W, 'p_align': 0x4000},
    ]

    new_phdr_count = 2 + len(load_phdrs) + len(extra_segs)
    phdr_table_size = new_phdr_count * ELF32_PHDR_SIZE

    # NULL segment 0: covers ELF header + program headers
    null0_size = ELF32_EHDR_SIZE + phdr_table_size

    # Hash table: header (40) + hashes (32 * phdr_count) + sig + cert
    hash_data_size = HASH_SIZE * new_phdr_count
    hash_seg_content_size = 40 + hash_data_size + SIG_SIZE + CERT_CHAIN_SIZE
    hash_seg_offset = 0x1000

    # Place LOAD segment data after hash table
    data_start = hash_seg_offset + align_up(hash_seg_content_size, 0x1000)

    # Layout segment data sequentially
    segments = []
    cur_offset = data_start
    for p in load_phdrs:
        seg_data = b''
        if p['p_filesz'] > 0:
            seg_data = elf_data[p['p_offset']:p['p_offset'] + p['p_filesz']]
        # Align offset to segment's alignment (but at least 0x10)
        seg_align = max(p['p_align'], 0x10)
        cur_offset = align_up(cur_offset, seg_align)
        new_p = dict(p)
        new_p['p_offset'] = cur_offset
        segments.append((new_p, seg_data))
        cur_offset += len(seg_data)

    # Fix NOLOAD segment offsets to point to end of file data (filesz=0 anyway)
    end_offset = cur_offset
    for ns in extra_segs:
        ns['p_offset'] = end_offset

    # Build program header table in order matching original:
    # NULL, NULL, LOAD(IMEM_CODE), LOAD(IMEM_DATA), LOAD(CODE), LOAD(DATA),
    # LOAD(DDR1 noload), LOAD(DDR2 noload)
    all_phdrs = []

    # NULL 0: ELF header + phdrs
    # p_flags = 0x07000000: Qualcomm-specific flag (from fhprg_peek.bin)
    all_phdrs.append({
        'p_type': PT_NULL, 'p_offset': 0, 'p_vaddr': 0, 'p_paddr': 0,
        'p_filesz': null0_size, 'p_memsz': 0,
        'p_flags': 0x07000000, 'p_align': 0,
    })

    # NULL 1: hash table
    # p_flags = 0x02200000: Qualcomm-specific flag identifying hash segment
    all_phdrs.append({
        'p_type': PT_NULL, 'p_offset': hash_seg_offset,
        'p_vaddr': HASH_SEG_VADDR, 'p_paddr': HASH_SEG_VADDR,
        'p_filesz': hash_seg_content_size,
        'p_memsz': align_up(hash_seg_content_size, 0x1000),
        'p_flags': 0x02200000, 'p_align': 0x1000,
    })

    # LOAD segments + extra segments, sorted by vaddr to match original order:
    # IMEM_CODE(0x220000), IMEM_DATA(0x223000), CODE(0x8006000),
    # BSS(0x8046000), DATA(0x804c000), DDR1(0x80000000), DDR2(0x87c00000)
    all_load = [(p, d) for p, d in segments] + [(s, b'') for s in extra_segs]
    all_load.sort(key=lambda x: x[0]['p_vaddr'])
    for p, _ in all_load:
        all_phdrs.append(p)

    assert len(all_phdrs) == new_phdr_count

    # Build MBN hash header
    hash_hdr_addr = HASH_SEG_VADDR + 40
    sig_addr = HASH_SEG_VADDR + 40 + hash_data_size
    cert_addr = sig_addr + SIG_SIZE

    mbn_hash_hdr = struct.pack('<IIIIIIIIII',
        MBN_IMAGE_ID,
        MBN_VERSION,
        0,                   # sw_id
        hash_hdr_addr,       # hash_addr (VA)
        hash_data_size + SIG_SIZE + CERT_CHAIN_SIZE,  # total size after header
        hash_data_size,      # offset from hash_addr to signature
        sig_addr,            # sig_addr (VA)
        SIG_SIZE,            # sig_size
        cert_addr,           # cert_chain_addr (VA)
        CERT_CHAIN_SIZE,     # cert_chain_size
    )

    # Initial hash table with zero hashes (will be filled after layout)
    hash_seg_data = (mbn_hash_hdr
                     + b'\x00' * hash_data_size
                     + b'\x00' * SIG_SIZE
                     + b'\x00' * CERT_CHAIN_SIZE)
    assert len(hash_seg_data) == hash_seg_content_size

    # Sahara maxpkt workaround: PBL silently hangs when the last data
    # chunk of a LOAD segment is exactly 0x400 bytes (the Sahara maxpkt
    # size).  Pad any such segment with 4 zero bytes to avoid this.
    SAHARA_MAXPKT = 0x400
    for i, (new_p, seg_data) in enumerate(segments):
        if new_p['p_filesz'] > 0 and (new_p['p_filesz'] % SAHARA_MAXPKT) == 0:
            print(f"[mbn] WARNING: segment at 0x{new_p['p_vaddr']:08x} has filesz "
                  f"0x{new_p['p_filesz']:x} (multiple of 0x{SAHARA_MAXPKT:x})")
            print(f"[mbn]   Adding 4-byte Sahara padding to avoid PBL hang")
            seg_data = seg_data + b'\x00\x00\x00\x00'
            new_p['p_filesz'] += 4
            new_p['p_memsz'] = max(new_p['p_memsz'], new_p['p_filesz'])
            segments[i] = (new_p, seg_data)

    # Calculate total file size
    max_end = hash_seg_offset + len(hash_seg_data)
    for new_p, seg_data in segments:
        end = new_p['p_offset'] + len(seg_data)
        if end > max_end:
            max_end = end

    out = bytearray(max_end)

    # Write ELF header
    new_ehdr = dict(ehdr)
    new_ehdr['e_phoff'] = ELF32_EHDR_SIZE
    new_ehdr['e_phnum'] = new_phdr_count
    new_ehdr['e_phentsize'] = ELF32_PHDR_SIZE
    new_ehdr['e_shoff'] = 0
    new_ehdr['e_shnum'] = 0
    new_ehdr['e_shstrndx'] = 0
    new_ehdr['e_shentsize'] = 40  # must be 0x28 even with 0 sections (matches original)
    new_ehdr['e_flags'] = 0x5000002  # Version5 EABI, match original
    out[0:ELF32_EHDR_SIZE] = pack_elf32_ehdr(new_ehdr)

    # Write program headers
    for i, phdr in enumerate(all_phdrs):
        off = ELF32_EHDR_SIZE + i * ELF32_PHDR_SIZE
        out[off:off + ELF32_PHDR_SIZE] = pack_elf32_phdr(phdr)

    # Write hash table segment
    out[hash_seg_offset:hash_seg_offset + len(hash_seg_data)] = hash_seg_data

    # Write LOAD segment data
    for new_p, seg_data in segments:
        if seg_data:
            out[new_p['p_offset']:new_p['p_offset'] + len(seg_data)] = seg_data

    # Compute real SHA-256 hashes and update hash table
    for i, phdr in enumerate(all_phdrs):
        if phdr['p_filesz'] > 0 and i != 1:  # skip hash seg (circular)
            seg_bytes = bytes(out[phdr['p_offset']:phdr['p_offset'] + phdr['p_filesz']])
            h = hashlib.sha256(seg_bytes).digest()
        else:
            h = b'\x00' * HASH_SIZE
        hash_off = hash_seg_offset + 40 + i * HASH_SIZE
        out[hash_off:hash_off + HASH_SIZE] = h

    with open(out_path, 'wb') as f:
        f.write(out)

    print(f"[mbn] Output: {out_path} ({len(out)} bytes)")
    print(f"[mbn] {new_phdr_count} phdrs ({len(load_phdrs)} LOAD + {len(extra_segs)} NOLOAD + 2 NULL)")
    print(f"[mbn] Hash table: offset 0x{hash_seg_offset:x}, {hash_seg_content_size} bytes")
    print(f"[mbn] Entry: 0x{new_ehdr['e_entry']:08x}, Flags: 0x{new_ehdr['e_flags']:08x}")

    print(f"\n[mbn] Program Headers:")
    print(f"  {'Type':<8} {'Offset':>10} {'VirtAddr':>10} {'PhysAddr':>10} "
          f"{'FileSiz':>8} {'MemSiz':>8} {'Flg':>3} {'Align':>6}")
    for p in all_phdrs:
        t = {PT_NULL: 'NULL', PT_LOAD: 'LOAD'}.get(p['p_type'], f"0x{p['p_type']:x}")
        flg = ''
        if p['p_flags'] & PF_R: flg += 'R'
        if p['p_flags'] & PF_W: flg += 'W'
        if p['p_flags'] & PF_X: flg += 'E'
        print(f"  {t:<8} 0x{p['p_offset']:08x} 0x{p['p_vaddr']:08x} 0x{p['p_paddr']:08x} "
              f"0x{p['p_filesz']:05x} 0x{p['p_memsz']:05x} {flg:>3} 0x{p['p_align']:x}")


if __name__ == '__main__':
    main()
