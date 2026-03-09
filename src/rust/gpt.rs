/// GPT partition table parser.
///
/// Reads the protective MBR and GPT header from eMMC, then parses
/// partition entries. Stores name (ASCII from UTF-16LE), start LBA,
/// and sector count for each partition.

use crate::emmc::Emmc;
use crate::sdcc::{SdccHw, Error};

const GPT_SIGNATURE: u64 = 0x5452415020494645; // "EFI PART"
const MAX_ENTRIES: usize = 32;

#[derive(Clone, Copy)]
pub struct GptEntry {
    pub name: [u8; 36],
    pub name_len: u8,
    pub start: u32,
    pub sectors: u32,
    pub attrs: u64,
}

impl GptEntry {
    pub const fn empty() -> Self {
        Self {
            name: [0u8; 36],
            name_len: 0,
            start: 0,
            sectors: 0,
            attrs: 0,
        }
    }

    pub fn name_bytes(&self) -> &[u8] {
        &self.name[..self.name_len as usize]
    }

    pub fn name_eq(&self, s: &[u8]) -> bool {
        self.name_bytes() == s
    }
}

/// Read the GPT from eMMC and return entries + count.
///
/// Uses the provided 512-byte sector buffer for temporary reads.
pub fn read_gpt<H: SdccHw>(
    emmc: &mut Emmc<H>,
    buf: &mut [u8; 512],
) -> Result<([GptEntry; MAX_ENTRIES], usize), Error> {
    let mut entries = [GptEntry::empty(); MAX_ENTRIES];

    // Read LBA 1 (GPT header)
    emmc.read(1, buf)?;

    // Validate signature at offset 0
    let sig = u64::from_le_bytes([
        buf[0], buf[1], buf[2], buf[3],
        buf[4], buf[5], buf[6], buf[7],
    ]);
    if sig != GPT_SIGNATURE {
        return Err(Error::InvalidState);
    }

    // Entry count at offset 80 (u32 LE)
    let num_entries = u32::from_le_bytes([buf[80], buf[81], buf[82], buf[83]]) as usize;
    // Entry size at offset 84 (u32 LE) — should be 128
    let entry_size = u32::from_le_bytes([buf[84], buf[85], buf[86], buf[87]]) as usize;
    // Partition entry start LBA at offset 72 (u64 LE)
    let entry_lba = u64::from_le_bytes([
        buf[72], buf[73], buf[74], buf[75],
        buf[76], buf[77], buf[78], buf[79],
    ]) as u32;

    let entries_per_sector = 512 / entry_size;
    let mut count = 0;

    // Read partition entry sectors
    let total_entry_sectors = (num_entries + entries_per_sector - 1) / entries_per_sector;
    for sec_idx in 0..total_entry_sectors {
        emmc.read(entry_lba + sec_idx as u32, buf)?;

        for ent_idx in 0..entries_per_sector {
            if count >= MAX_ENTRIES {
                break;
            }
            let global_idx = sec_idx * entries_per_sector + ent_idx;
            if global_idx >= num_entries {
                break;
            }

            let off = ent_idx * entry_size;

            // Check type GUID — skip zero (unused entry)
            let mut all_zero = true;
            for i in 0..16 {
                if buf[off + i] != 0 {
                    all_zero = false;
                    break;
                }
            }
            if all_zero {
                continue;
            }

            // Start LBA at offset 32 (u64 LE), end LBA at offset 40 (u64 LE)
            let start = u64::from_le_bytes([
                buf[off + 32], buf[off + 33], buf[off + 34], buf[off + 35],
                buf[off + 36], buf[off + 37], buf[off + 38], buf[off + 39],
            ]);
            let end = u64::from_le_bytes([
                buf[off + 40], buf[off + 41], buf[off + 42], buf[off + 43],
                buf[off + 44], buf[off + 45], buf[off + 46], buf[off + 47],
            ]);

            // Attributes at offset 48 (u64 LE)
            let attrs = u64::from_le_bytes([
                buf[off + 48], buf[off + 49], buf[off + 50], buf[off + 51],
                buf[off + 52], buf[off + 53], buf[off + 54], buf[off + 55],
            ]);

            // Name: UTF-16LE at offset 56, 72 bytes (36 UTF-16 code units)
            let mut entry = GptEntry::empty();
            entry.start = start as u32;
            entry.sectors = (end - start + 1) as u32;
            entry.attrs = attrs;

            let name_off = off + 56;
            let mut name_len: u8 = 0;
            for i in 0..36 {
                let lo = buf[name_off + i * 2];
                let hi = buf[name_off + i * 2 + 1];
                if lo == 0 && hi == 0 {
                    break;
                }
                // ASCII subset only
                if hi == 0 && lo >= 0x20 && lo < 0x7f {
                    entry.name[name_len as usize] = lo;
                } else {
                    entry.name[name_len as usize] = b'?';
                }
                name_len += 1;
            }
            entry.name_len = name_len;

            entries[count] = entry;
            count += 1;
        }
    }

    Ok((entries, count))
}
