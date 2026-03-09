# MCI eMMC Init Spec for MSM8909 SDCC

Tailored reference for the minimal programmer's eMMC initialization in MCI legacy mode.
Derived from ARM PL180 TRM (DDI0172), LK bootloader (`lk_src/platform/msm_shared/mmc.c`),
Linux `msm_sdcc.c`, and the decompiled original firehose programmer.

---

## 1. MCI Register Map

Base address: `0x07824000` (SDCC1). All offsets are from the MCI core base.

### Standard PL180 Registers

| Offset | Name           | R/W | Description |
|--------|----------------|-----|-------------|
| 0x000  | MCI_POWER      | R/W | Power control + software reset |
| 0x004  | MCI_CLK        | R/W | Clock divider, enable, bus width, flow control |
| 0x008  | MCI_ARGUMENT   | R/W | Command argument (written before MCI_CMD) |
| 0x00C  | MCI_CMD        | R/W | Command index + flags; writing fires the command |
| 0x010  | MCI_RESP_CMD   | R   | Index of last command that got a response |
| 0x014  | MCI_RESP_0     | R   | Response word 0 (short response = full R1/R3/R6) |
| 0x018  | MCI_RESP_1     | R   | Response word 1 (R2 only) |
| 0x01C  | MCI_RESP_2     | R   | Response word 2 (R2 only) |
| 0x020  | MCI_RESP_3     | R   | Response word 3 (R2 only) |
| 0x024  | MCI_DATA_TIMER | R/W | Data timeout (card bus clock cycles) |
| 0x028  | MCI_DATA_LENGTH| R/W | Total bytes for data transfer |
| 0x02C  | MCI_DATA_CTL   | R/W | Data transfer enable/direction/block size |
| 0x030  | MCI_DATA_COUNT | R   | Remaining bytes in current data transfer |
| 0x034  | MCI_STATUS     | R   | Status register (command/data/FIFO state) |
| 0x038  | MCI_CLEAR      | W   | Write-1-to-clear for MCI_STATUS bits |
| 0x03C  | MCI_INT_MASK0  | R/W | Interrupt enable mask 0 |
| 0x040  | MCI_INT_MASK1  | R/W | Interrupt enable mask 1 |
| 0x044  | MCI_FIFO_COUNT | R   | Number of words remaining in FIFO |
| 0x080  | MCI_FIFO       | R/W | Data FIFO port (up to 0x0BC, 16 words deep) |

### Qualcomm SDCC Extensions

| Offset | Name           | Description |
|--------|----------------|-------------|
| 0x050  | MCI_VERSION    | Controller version (determines delay method) |
| 0x058  | MCI_CCS_TIMER  | CCS timer (CE-ATA) |
| 0x06C  | MCI_STATUS2    | **Bit 0: MCLK_REG_WR_ACTIVE** (register write pending) |
| 0x078  | MCI_HC_MODE    | Bit 0: 0=MCI legacy, 1=SDHCI mode |
| 0x0DC  | MCI_PLL_STATUS | PLL lock status |
| 0x0E4  | MCI_PLL_DIVIDER| PLL divider |
| 0x0E8  | MCI_PLL_MODE   | PLL mode |

---

## 2. Register Bit Fields

### MCI_POWER (0x000)

| Bits | Name       | Description |
|------|------------|-------------|
| 1:0  | CTRL       | 00=off, 02=power-up, 03=power-on |
| 6    | OPEN_DRAIN | Open-drain CMD line (for card identification) |
| 7    | SW_RST     | Core software reset (QC extension) |

**Power sequence**: Write 0x80 (SW_RST), wait, then write 0x03 (power-on).

LK does NOT use OPEN_DRAIN. The original firehose sets bit 0 (OPEN_DRAIN) during
card identification, then clears it after CMD7 select.

### MCI_CLK (0x004)

| Bits  | Name          | Description |
|-------|---------------|-------------|
| 7:0   | CLK_DIV       | Divider: f_out = f_in / (2 * (DIV+1)). Bypassed if bit 10 set. |
| 8     | CLK_ENABLE    | Enable clock output to card |
| 9     | PWRSAVE       | Gate clock when bus idle (power save) |
| 11:10 | WIDEBUS       | Bus width: 00=1-bit, 10=4-bit, 01=8-bit (QC encoding!) |
| 12    | FLOW_ENA      | Hardware flow control (prevents FIFO overrun/underrun) |
| 13    | INVERT_OUT    | Invert output clock edge |
| 15:14 | SELECT_IN     | Clock select: 00=falling, 01=rising, 10=feedback, 11=loopback |
| 21    | IO_PAD_PWR_SWITCH | Dual voltage pad control (QC vendor bit) |

**LK initial config** (`mmc_boot_mci_clk_enable`):
```c
reg = 0;
reg |= (1 << 8);      /* CLK_ENABLE */
reg |= (1 << 12);     /* FLOW_ENA */
reg |= (2 << 14);     /* SELECT_IN = feedback = 0x8000 */
writel(reg, MCI_CLK);  /* = 0x9100 */
```

**Our initial config** (`sdcc_pre_init_slot`):
```c
clk |= 0x100;         /* CLK_ENABLE (bit 8) */
clk |= 0x8000;        /* SELECT_IN feedback (bits 15:14 = 10) */
clk |= 0x200000;      /* IO_PAD_PWR_SWITCH (bit 21, QC vendor) */
clk &= ~0xC00u;       /* WIDEBUS = 00 (1-bit) */
/* Result: 0x208100 */
```

**Important difference**: LK sets FLOW_ENA (bit 12 = 0x1000) from the start.
Our code does NOT set it during init. FLOW_ENA prevents FIFO overrun/underrun
during data transfers.

**QC bus width encoding** (different from standard PL180!):
| Value  | Width | Notes |
|--------|-------|-------|
| 0 << 10 | 1-bit | Default |
| 2 << 10 | 4-bit | 0x800 |
| 1 << 10 | 8-bit | 0x400 (swapped vs standard!) |

### MCI_CMD (0x00C)

| Bits | Name        | Description |
|------|-------------|-------------|
| 5:0  | CMD_INDEX   | Command number (0-63) |
| 6    | RESPONSE    | Expect a response (all except CMD0) |
| 7    | LONGRSP     | Expect 136-bit response (R2: CMD2, CMD9, CMD10) |
| 8    | INTERRUPT   | Wait for interrupt (not used) |
| 9    | PENDING     | Wait for CmdPend (stream mode) |
| 10   | CPSM_ENABLE | **Must be set to fire the command** |
| 11   | PROG_ENA    | Assert PROG_DONE when busy clears (for write commands) |
| 12   | DAT_CMD     | Data command flag (for CMD17/18/24/25) |

**Our sdcc_cleanup mapping** (verified correct):
| Our field name | Bit | LK constant |
|---------------|-----|-------------|
| data_present  | 10  | CPSM_ENABLE |
| crc_check     | 6   | RESPONSE |
| idx_check     | 7   | LONGRSP |
| ccs_enable    | 11  | PROG_ENA |
| dpe           | 12  | DAT_CMD |

### MCI_STATUS (0x034) — Read-only

| Bit | Name           | Hex        | Description |
|-----|----------------|------------|-------------|
| 0   | CMD_CRC_FAIL   | 0x0001     | Command CRC check failed (expected for R3) |
| 1   | DATA_CRC_FAIL  | 0x0002     | Data block CRC failed |
| 2   | CMD_TIMEOUT    | 0x0004     | No response within timeout |
| 3   | DATA_TIMEOUT   | 0x0008     | Data transfer timeout |
| 4   | TX_UNDERRUN    | 0x0010     | TX FIFO underrun |
| 5   | RX_OVERRUN     | 0x0020     | RX FIFO overrun |
| 6   | CMD_RESP_END   | 0x0040     | Response received, CRC OK |
| 7   | CMD_SENT       | 0x0080     | Command sent (no-response commands) |
| 8   | DATA_END       | 0x0100     | Data counter reached zero |
| 9   | START_BIT_ERR  | 0x0200     | Start bit not detected on data line |
| 10  | DATA_BLK_END   | 0x0400     | Data block sent/received, CRC OK |
| 11  | CMD_ACTIVE     | 0x0800     | Command transfer in progress |
| 12  | TX_ACTIVE      | 0x1000     | Data TX in progress |
| 13  | RX_ACTIVE      | 0x2000     | Data RX in progress |
| 14  | TX_FIFO_HALF_EMPTY | 0x4000 | TX FIFO half empty (can write) |
| 15  | RX_FIFO_HALF_FULL  | 0x8000 | RX FIFO half full (can burst-read) |
| 21  | RX_DATA_AVAIL  | 0x200000   | At least one word available in RX FIFO |
| 23  | PROG_DONE      | 0x800000   | Card programming complete (QC extension) |
| 24  | ATA_CMD_COMPL  | 0x1000000  | CE-ATA command complete |

**Clear mask** (written to MCI_CLEAR before each command):
- LK: `0x8007FF` (bits 0-10 + bit 23)
- Our code: `0x18007FF` (bits 0-10 + bits 23-24) — superset, harmless

### MCI_DATA_CTL (0x02C)

| Bits | Name        | Description |
|------|-------------|-------------|
| 0    | ENABLE      | Start data transfer |
| 1    | DIRECTION   | 0=write (host→card), 1=read (card→host) |
| 2    | MODE        | 0=block, 1=stream |
| 3    | DMA_ENABLE  | Enable DMA (we use PIO) |
| 7:4  | BLOCKSIZE   | Block size = 2^n bytes (9 = 512 bytes) |

### MCI_STATUS2 (0x06C) — QC Extension

| Bit | Name               | Description |
|-----|--------------------|-------------|
| 0   | MCLK_REG_WR_ACTIVE | **Register write still propagating** |

**Critical**: After writing MCI_POWER, MCI_CLK, or MCI_DATA_CTL, poll
MCI_STATUS2 bit 0 until it clears before doing anything else. This is what
`sdcc_enable_clock()` / `mmc_mclk_reg_wr_delay()` does.

---

## 3. MCI Controller Init Sequence

### LK Reference (`mmc_boot_init`, line 1900)

```
1. HC_MODE &= ~1                  — force MCI legacy mode
2. mclk_reg_wr_delay()            — wait for write to propagate
3. MCI_POWER |= 0x80              — software reset (CORE_SW_RST)
4. mclk_reg_wr_delay()
5. clock_init_mmc(slot)           — enable GCC clock gates (APPS_CBCR, AHB_CBCR)
6. clock_config_mmc(slot, 400000) — set SDCC1 input clock to 400 KHz
7. MCI_POWER = 0x03               — power on (PWR_ON | PWR_UP)
8. mclk_reg_wr_delay()
```

Then `mmc_boot_mci_clk_enable()` (called before first command):
```
9. MCI_CLK = CLK_ENABLE | FLOW_ENA | SELECT_IN_FEEDBACK
             (0x100 | 0x1000 | 0x8000 = 0x9100)
10. mclk_reg_wr_delay()
```

### Our Current Code (`sdcc_pre_init_slot`)

Steps 1-4 match LK. Steps 5-6 done in entry.S (`sdcc_clock_init`).
Then we deviate:

```
 MCI_CMD = 0                     — explicit CPSM clear (LK doesn't do this)
 MCI_DATA_CTL = 0                — explicit DPSM clear (LK doesn't do this)
 MCI_CLEAR = 0x18007FF           — clear all status (LK doesn't do this)
 MCI_INT_MASK0 = 0               — disable interrupts (LK doesn't do this)
 MCI_POWER = 0x03                — power on (matches LK)
 MCI_CLK = 0x208100              — CLK_ENABLE + FEEDBACK + vendor bit 21
                                   (MISSING: FLOW_ENA bit 12!)
```

### What's Different (potential issues)

1. **Missing FLOW_ENA (bit 12)**: LK sets `MMC_BOOT_MCI_CLK_ENA_FLOW` (0x1000)
   in `mmc_boot_mci_clk_enable()`. Our init never sets it. Without flow control,
   FIFO overruns during data transfers can silently corrupt data.

2. **Extra MCI_CMD/MCI_DATA_CTL clears**: Not harmful, but the SW_RST should
   already reset these. These extra writes just add sdcc_enable_clock() delays.

3. **LK calls `clock_init_mmc()` between SW_RST and power-on**: This ensures
   the GCC clocks are fully configured before the MCI core starts. Our SDCC
   clock init happens earlier in entry.S, before the MCI controller is touched.
   This should be equivalent since entry.S runs first.

---

## 4. eMMC Card Identification Sequence

All commands during identification use 400 KHz clock, 1-bit bus.

### CMD0 — GO_IDLE_STATE

| Field    | Value |
|----------|-------|
| Argument | 0x00000000 |
| MCI_CMD  | 0x400 (CMD0 + CPSM_ENABLE, no RESPONSE bit) |
| Response | None |
| Poll for | CMD_SENT (MCI_STATUS bit 7 = 0x80) |
| Effect   | Card → Idle state |

### CMD1 — SEND_OP_COND (retry until ready)

| Field    | Value |
|----------|-------|
| Argument | 0x40FF8000 (OCR: 2.7-3.6V + sector mode) |
| MCI_CMD  | 0x441 (CMD1 + RESPONSE + CPSM_ENABLE) |
| Response | R3 (OCR, no CRC — triggers CMD_CRC_FAIL, which is expected) |
| Poll for | CMD_CRC_FAIL (bit 0) — treat as success for CMD1 |
| Read     | MCI_RESP_0: OCR register |
| Check    | Bit 31 = 0 → card busy, retry. Bit 31 = 1 → ready |
| Timeout  | Retry up to 1 second total |
| Effect   | Card → Ready state |

**Important**: R3 response has no CRC field, so the controller always reports
CMD_CRC_FAIL. The response data in MCI_RESP_0 is still valid. Both LK and our
code treat CRC_FAIL as success for CMD1 (and CMD5, ACMD41).

### CMD2 — ALL_SEND_CID

| Field    | Value |
|----------|-------|
| Argument | 0x00000000 |
| MCI_CMD  | 0x4C2 (CMD2 + RESPONSE + LONGRSP + CPSM_ENABLE) |
| Response | R2 (136-bit CID) |
| Poll for | CMD_RESP_END (bit 6 = 0x40) |
| Read     | All four MCI_RESP_0..3 |
| Effect   | Card → Identification state |

### CMD3 — SET_RELATIVE_ADDR (host assigns RCA for eMMC)

| Field    | Value |
|----------|-------|
| Argument | 0x00020000 (RCA=2, shifted left 16) |
| MCI_CMD  | 0x443 (CMD3 + RESPONSE + CPSM_ENABLE) |
| Response | R1 (card status) |
| Effect   | Card → Standby state |

### CMD9 — SEND_CSD

| Field    | Value |
|----------|-------|
| Argument | RCA << 16 = 0x00020000 |
| MCI_CMD  | 0x4C9 (CMD9 + RESPONSE + LONGRSP + CPSM_ENABLE) |
| Response | R2 (136-bit CSD) |

### CMD7 — SELECT_CARD

| Field    | Value |
|----------|-------|
| Argument | RCA << 16 = 0x00020000 |
| MCI_CMD  | 0x447 (CMD7 + RESPONSE + CPSM_ENABLE) |
| Response | R1 (card status) |
| Effect   | Card → Transfer state |

### CMD8 — SEND_EXT_CSD (data transfer)

Before CMD8, set up data path:
```
MCI_CLK     |= FLOW_ENA (0x1000)     — enable flow control
MCI_DATA_TIMER = 0xFFFFFFFF           — max timeout
MCI_DATA_LENGTH = 512                 — 512 bytes
MCI_DATA_CTL = ENABLE | DIR_READ | BLKSIZE(9)
             = 0x01 | 0x02 | (9 << 4) = 0x93
```

| Field    | Value |
|----------|-------|
| Argument | 0x00000000 |
| MCI_CMD  | 0x1448 (CMD8 + RESPONSE + CPSM_ENABLE + DAT_CMD) |
| Response | R1 + 512 bytes data |
| Read data | PIO: poll RX_DATA_AVAIL (bit 21), read MCI_FIFO (0x80) |

---

## 5. Command Dispatch Sequence (MCI Mode)

This is the register-level sequence for every command. Both LK and our code
follow this pattern.

### Sending a Command

```
1. Write argument:         MCI_ARGUMENT (0x08) = cmd_arg
2. Clear status:           MCI_CLEAR (0x38) = 0x18007FF
3. Build & write command:  MCI_CMD (0x0C) = cmd_index | flags
4. Wait for propagation:   poll MCI_STATUS2 bit 0 until 0
```

### Polling for Completion

```
For CMD0 (no response):
  Poll MCI_STATUS for CMD_SENT (bit 7 = 0x80)
  Clear: MCI_CLEAR = 0x80

For commands with response:
  Poll MCI_STATUS for one of:
    CMD_RESP_END (bit 6 = 0x40)  → success, read response
    CMD_TIMEOUT  (bit 2 = 0x04)  → timeout error
    CMD_CRC_FAIL (bit 0 = 0x01)  → CRC error (expected for R3)
  Clear the corresponding bit via MCI_CLEAR
```

### Reading Response

```
Short (R1/R3/R6): resp = MCI_RESP_0 (0x14)
Long (R2):        resp[0..3] = MCI_RESP_0..3 (0x14..0x20)
```

### Post-Command Cleanup

```
MCI_CMD (0x0C) = 0                  — deassert CPSM
poll MCI_STATUS2 bit 0 until 0      — wait for write to propagate
```

---

## 6. Data Transfer (PIO Read)

For reading data blocks (CMD8/CMD17/CMD18):

```
1. MCI_DATA_TIMER = 0xFFFFFFFF
2. MCI_DATA_LENGTH = byte_count
3. MCI_DATA_CTL = ENABLE(0) | DIR_READ(1) | BLKSIZE(9<<4)
4. Send command (CMD8/CMD17/CMD18)
5. Poll loop:
   a. Read MCI_STATUS
   b. Check error bits: DATA_CRC_FAIL(1) | CMD_TIMEOUT(2) | RX_OVERRUN(5)
      → if any set: error recovery
   c. Check RX_DATA_AVAIL (bit 21 = 0x200000):
      If RX_FIFO_HALF_FULL (bit 15 = 0x8000) AND buf aligned:
        → burst read 8 words from MCI_FIFO
      Else:
        → read 1 word from MCI_FIFO
   d. Repeat until byte_count exhausted
6. Poll for DATA_END (bit 8 = 0x100) or DATA_BLK_END (bit 10 = 0x400)
```

### Data Transfer (PIO Write)

For writing data blocks (CMD24/CMD25):

```
1. MCI_DATA_TIMER = 0xFFFFFFFF
2. MCI_DATA_LENGTH = byte_count
3. MCI_DATA_CTL = ENABLE(0) | DIR_WRITE(0) | BLKSIZE(9<<4)
4. Send command (CMD24/CMD25)
5. Poll loop:
   a. Read MCI_STATUS
   b. Check error bits: DATA_CRC_FAIL(1) | TX_UNDERRUN(4)
      → if any set: error recovery
   c. Check TX_FIFO_HALF_EMPTY (bit 14 = 0x4000):
      → write words to MCI_FIFO
   d. Repeat until byte_count exhausted
6. Poll for PROG_DONE (bit 23 = 0x800000)
```

---

## 7. MCLK_REG_WR_ACTIVE Synchronization

**Critical QC-specific requirement**: After writing to MCI_POWER, MCI_CLK, or
MCI_DATA_CTL, the write crosses a clock domain boundary. MCI_STATUS2 bit 0
reads 1 while the write is propagating. Must poll until bit 0 = 0.

Our `sdcc_enable_clock(slot)` implements this (polls up to 1000 iterations).
LK's `mmc_mclk_reg_wr_delay()` does the same (with a version check: if
MCI_VERSION == 0, uses udelay instead).

**When to call**: After every write to MCI_POWER, MCI_CLK, MCI_CMD, MCI_DATA_CTL.

---

## 8. Timing Requirements

| Requirement | Value | Source |
|-------------|-------|--------|
| Identification clock | 100-400 KHz | JEDEC |
| 74 clocks after power-on before CMD0 | 185 us @ 400 KHz | JEDEC |
| CMD1 retry timeout | 1 second total | JEDEC |
| MCLK_REG_WR_ACTIVE poll timeout | ~1 ms | Linux msm_sdcc.c |
| MCI_POWER stabilization | ~2 ms | LK bootloader |

---

## 9. Differences Between Our Code and LK

### Confirmed Issues

1. **Missing FLOW_ENA (MCI_CLK bit 12)**: LK always sets this before data
   transfers. Our code never sets it in `sdcc_pre_init_slot`. The
   `mmc_classify_error` path toggles bit 9 (PWRSAVE), NOT bit 12 (FLOW_ENA).
   Without FLOW_ENA, the hardware cannot throttle the host when the FIFO is
   full/empty, leading to RX_OVERRUN or TX_UNDERRUN on data transfers.

2. **OPEN_DRAIN for card identification**: The original firehose sets MCI_POWER
   bit 6 (OPEN_DRAIN) during card identification (CMD0-CMD3), then clears it
   after CMD7. LK does not set OPEN_DRAIN. Our code does not set it either.
   Some eMMC devices may require OPEN_DRAIN on the CMD line during identification
   (shared bus protocol), but embedded eMMC (non-removable) typically doesn't need it.

### Verified Matches

- MCI_CMD bit encoding matches between our sdcc_cleanup and LK
- Status polling logic (CMD_SENT for CMD0, CRC_FAIL-is-OK for CMD1) matches
- Response reading from MCI_RESP_0..3 matches
- MCI_CLEAR values are compatible (ours is a superset of LK's)
- CPSM deassert (MCI_CMD=0) after each command matches

### Non-Issues

- Extra MCI_CMD/MCI_DATA_CTL clears in our init: harmless, SW_RST already does this
- Vendor bit 21 in MCI_CLK: original firehose sets it, LK doesn't. Both work.
- Our MCI_CLEAR constant (0x18007FF vs LK's 0x8007FF): ours clears one extra bit (24), harmless

---

## 10. Sources

- ARM PrimeCell MCI (PL180) Technical Reference Manual, DDI0172
- `lk_src/platform/msm_shared/mmc.c` — LK bootloader MCI driver (our local copy)
- `lk_src/platform/msm_shared/include/mmc.h` — LK MCI register defines
- Linux `drivers/mmc/host/msm_sdcc.c` — Qualcomm kernel driver (MCLK_REG_WR_ACTIVE)
- `src/fhprg/fhprg_80327f8.c` — Decompiled original firehose programmer
- JEDEC JESD84-A43 eMMC specification
