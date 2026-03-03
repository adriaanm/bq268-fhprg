# Partition 3 Write Restriction in Firehose Programmer

## Overview

The Qualcomm Firehose programmer (`fhprg_peek.bin`, msm8909 ARM32 Thumb2) contains a hardcoded restriction that blocks all writes to physical partition 3. This document describes the restriction mechanism, how it was confirmed via emulation, and the patch target.

## Restriction mechanism

The write restriction is enforced at two levels in the binary.

### Gate 1: `FUN_08038206` — partition selector (primary gate)

Address: `0x08038206` (48 bytes, Thumb2)

This function is called from the `<program>` handler (`FUN_08024484`) before any write is attempted. It validates the `physical_partition_number` XML attribute:

```c
undefined4 FUN_08038206(int param_1, uint param_2) {
    if ((param_2 < 8) && (param_2 != 3) &&
        (iVar1 = FUN_08033ee8(*(undefined4 *)(param_1 + 4), auStack_50), iVar1 == 0) &&
        (param_2 <= local_34 - 1U)) {
        *(char *)(param_1 + 0x26) = (char)param_2;  // set active partition
        return 1;  // success
    }
    return 0;  // fail
}
```

The `param_2 != 3` check is the explicit exclusion of partition 3. When this returns 0, the program handler logs "Invalid physical partition %d" and sends a NAK response.

### Gate 2: `FUN_08027328` — handler table initialization

Address: `0x08027328`

During device initialization, the handler table at `DAT_08058430` is populated with per-partition function pointers. The init loop explicitly skips slot 3:

```c
do { iVar3++; if (7 < iVar3) break; } while (iVar3 == 3);
```

This leaves `DAT_08058430 + 0x10` (the partition 3 handler pointer) as NULL. Even if Gate 1 were bypassed, `FUN_080381d8` would dereference a null handler and return failure.

### Gate 3: write-protect flag (eMMC level)

`FUN_08034228` checks a write-protect byte at `puVar3[0x24] + 0xa0` in the eMMC extended CSD structure. If set, writes fail with error `0x1b`. This is a hardware-level protection that may or may not be active depending on the eMMC configuration.

## Emulation confirmation

The restriction was confirmed using a Unicorn Engine harness (`tools/fhprg_emu.py`) that loads the binary, hooks I/O functions, and feeds XML `<program>` commands directly into the native command dispatcher.

### Test results

```
$ python3 tools/fhprg_emu.py --compare

Partition 0 (normal):
  Partition gate: partition=0: ALLOWED
  Writes: 1, ACKs: 2, NAKs: 0

Partition 3 (aboot):
  Partition gate: partition=3: BLOCKED (== 3, aboot protection)
  Writes: 0, ACKs: 0, NAKs: 1
  Log: Invalid physical partition 3

CONFIRMED: FUN_08038206 at 0x08038206 blocks partition 3 writes.
```

### What the emulator exercises natively

The following code paths run as native Thumb2 instructions in Unicorn (not hooked):

- XML tokenizer (`FUN_08038db4`) — character-by-character parser with ctype lookups
- Tag name comparison (`FUN_08039092` → `FUN_080382fa`) — case-insensitive strncmp
- Attribute name/value extraction (`FUN_0803906c`, `FUN_08038d38`)
- Command dispatcher (`FUN_0802f130`) — tag routing to handler functions
- Program handler attribute parsing loop (`FUN_08024484`, partial)

### What is hooked

| Function | Address | Hook behavior |
|----------|---------|---------------|
| `FUN_08038206` | `0x08038206` | Emulates real restriction logic, logs result |
| `FUN_080381d8` | `0x080381d8` | Logs write (sector, count), returns success |
| `FUN_08038014` | `0x08038014` | Returns success (readback verify) |
| `FUN_08021ca4` | `0x08021ca4` | Supplies fake sector data |
| `FUN_08037084` | `0x08037084` | Logs ACK/NAK response |
| `FUN_08027674` | `0x08027674` | Captures log messages |
| `FUN_08033ee8` | `0x08033ee8` | Returns fake partition info |
| `FUN_08028c10` | `0x08028c10` | Parses sector numbers from XML attribute strings |
| `FUN_08010960` | `0x08010960` | Bypasses stack canary panic |

## Patch target

To allow writes to partition 3, two changes are needed in the recompiled binary:

1. **`FUN_08038206`**: Remove the `param_2 != 3` condition so the partition selector accepts partition 3.

2. **`FUN_08027328`**: Remove the `while (iVar3 == 3) iVar3++` skip so the handler table is populated for slot 3.

Gate 3 (the eMMC write-protect flag) depends on hardware state and may not require a software patch.

## Key addresses

| Symbol | Address | Description |
|--------|---------|-------------|
| `FUN_08038206` | `0x08038206` | Partition selector — primary write gate |
| `FUN_08027328` | `0x08027328` | Handler table init — skips slot 3 |
| `FUN_08024484` | `0x08024484` | `<program>` command handler |
| `FUN_0802f130` | `0x0802f130` | XML command dispatcher |
| `FUN_080381d8` | `0x080381d8` | Storage write wrapper |
| `DAT_08058430` | `0x08058430` | Storage device struct (handler table) |
| `DAT_08055ea0` | `0x08055ea0` | XML parser state |

## Reproducing

```bash
# Install dependencies
apt-get install -y python3-unicorn python3-capstone python3-pyelftools

# Run comparison
python3 tools/fhprg_emu.py --compare

# Verbose trace
python3 tools/fhprg_emu.py --compare -v

# Test specific partition
python3 tools/fhprg_emu.py --start-sector 2623488 --num-sectors 8192 --partition 3
```
