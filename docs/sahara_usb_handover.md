# Sahara → Firehose USB Handover Spec

## Purpose

Document the unknowns, knowns, and testable hypotheses about USB controller
state during the PBL → programmer handover on MSM8909 (ChipIdea USB 2.0 HS).

The minimal programmer (`src_minimal/`) currently does USBCMD reset + full
re-enumeration. The host Go client sleeps 1.5s after Sahara DONE_RSP and
reuses the same VID:PID handle. This works with the stock programmer but
not yet with ours. This document maps out exactly what we know, what we
don't, and what experiments can resolve each unknown.

---

## 1. What We Don't Know (PBL Black Box)

The PBL (Primary Boot Loader) runs Sahara over USB, loads our ELF, then
jumps to our entry point. We cannot inspect PBL code. These are the unknowns:

### 1.1 Controller State at Jump

```
UNKNOWN: Does the PBL leave RS=1 (controller running) at the moment of jump?

  Possible answers:
    A. RS=1, controller still running, D+ asserted, last Sahara dTD completed
       → We inherit a live USB session
    B. RS=0, PBL stopped the controller before jumping
       → D+ deasserted, host may or may not have seen disconnect yet
    C. PBL does its own USBCMD reset before jumping
       → Controller in reset state, DEVICEADDR=0, toggles=DATA0

  Impact: Determines whether "inherit session" is even possible.
  Test: Read USB_USBCMD (0x078D9140) immediately in entry.S, before any
        USB init. Report via LED or store in a known OCIMEM address.

  *** RESULT (2026-03-07): RS=1 (green LED). PBL leaves controller running. ***
  Answer is A. Inherit approach is viable.
```

### 1.2 ENDPOINTLISTADDR and dQH Location

```
UNKNOWN: Where is PBL's dQH table? What are its contents?

  Possible answers:
    A. In OCIMEM (0x08xxxxxx) — we might clobber it with our code/data
    B. In PBL-private SRAM (0x00xxxxxx) — accessible but not in our region
    C. In a region we never touch — safe to read but not modify

  Impact: If we want to inherit the session, we need to either:
    - Keep PBL's dQH table intact and modify entries in-place, or
    - Copy it to our own table and atomically swap ENDPOINTLISTADDR

  Test: Read USB_ENDPOINTLISTADDR (0x078D9158) in entry.S. Dump the
        64 bytes at that address to see EP0/EP1 queue head contents.

  *** RESULT (2026-03-07): NOT in OCIMEM (top byte != 0x08). ***
  *** But dQH is readable — EP1 OUT has non-zero max packet size. ***
  Answer is B or C. PBL's dQH is in PBL-private SRAM, safe from our BSS.

  *** RESULT (2026-03-07): ENDPOINTLISTADDR swap to OCIMEM dQH works ***
  *** while RS=1. Flush + copy PBL dQH + write new addr → readback OK. ***
  *** BUT: USB DMA CANNOT access OCIMEM. Prime never completes with    ***
  *** OCIMEM dQH or dTDs. Must use DDR or PBL's SRAM for USB DMA.     ***

  *** RESULT (2026-03-07): INHERIT PATH WORKS with DDR buffers!        ***
  *** Keep PBL's dQH (in PBL SRAM), link dTD in DDR into PBL's        ***
  *** dQH[3] (EP1 IN), prime → host receives banner. No reset needed.  ***
  *** USB DMA can reach DDR (0x80000000+) but not OCIMEM (0x0804xxxx). ***
```

### 1.3 Data Toggle State

```
UNKNOWN: What are the data toggles for EP0 IN/OUT and EP1 IN/OUT?

  The Sahara protocol uses bulk EP1 for payload transfer. After the final
  Sahara DONE_RSP packet, the host's EP1 OUT toggle is at some value
  (DATA0 or DATA1). We don't know which.

  Possible answers:
    A. DATA0 on all endpoints (Sahara does an even number of transfers)
    B. DATA1 on EP1 OUT (odd number of bulk OUT packets in Sahara)
    C. Varies depending on programmer ELF size (different packet counts)

  Impact: If we reset toggles (via USBCMD reset or ENDPTCTRL reset bits),
          the device side goes to DATA0. If the host is at DATA1, every
          packet is silently rejected (host thinks it's a retransmission).

  Resolution paths:
    - USBCMD reset → D+ deassert → host disconnect → bus reset → both
      sides reset to DATA0 → SET_CONFIGURATION resets again → synchronized
    - Inherit → must match whatever PBL left
    - Can read toggle from dQH overlay area (Token field, bit 6) if we
      know the dQH address
```

### 1.4 USB Device Address

```
UNKNOWN: What USB address did the host assign during PBL enumeration?

  Possible answers:
    A. Address 1 (typical for single-device USB)
    B. Any address 1-127 (host chooses)

  Impact: If we inherit the session, we must keep DEVICEADDR unchanged.
          If we do USBCMD reset, DEVICEADDR is cleared to 0 and the host
          will assign a new address during re-enumeration.

  Test: Read USB_DEVICEADDR (0x078D9154) in entry.S.

  *** RESULT (2026-03-07): DEVICEADDR = 0x38000000 → address 7 (bits 31:25). ***
  *** Note: reading this register from the diag console kills the USB       ***
  *** connection (possibly a side effect of the read touching USBADRA).     ***
```

### 1.5 ULPI PHY State

```
UNKNOWN: What ULPI PHY register values did PBL configure?

  The original programmer writes these ULPI registers after BCR:
    0x80 = 0x33, 0x81 = 0x33, 0x82 = 0x07, 0x83 = 0x13
  These are vendor-specific tuning/trim values. We don't know if PBL
  uses the same values or different ones.

  Possible answers:
    A. PBL uses identical values (same SoC, same code)
    B. PBL uses different tuning (older/different calibration)
    C. Values are read from eFuses and may vary per-chip

  Impact: If we skip BCR (USBCMD-only reset), PHY state is preserved
          from PBL. If PBL's PHY config works for Sahara, it works for us.
          If we do BCR reset, we must reconfigure ULPI.

  Test: Read ULPI registers 0x80-0x83 via viewport (0x078D9170) before
        doing any USB init. Compare with what the original programmer writes.
```

### 1.6 Clock Configuration

```
UNKNOWN: Which USB clocks does PBL enable? Are they the same 3 CBCRs
         the original programmer uses?

  The original enables/disables these GCC registers:
    0x01841000 - GCC_USB_HS_BCR (param_1=0 in FUN_0801a704)
    0x0184103C - GCC_USB_HS_PHY_CFG_AHB_CBCR (param_1=1)
    0x01841034 - GCC_USB2A_PHY_SLEEP_CBCR (param_1=2)

  And FUN_0800abf4 enables all 3 CBCRs:
    0x01841004 - GCC_USB_HS_SYSTEM_CBCR
    0x01841008 - GCC_USB_HS_AHB_CBCR
    0x01841030 - (third CBCR)

  Possible answers:
    A. PBL enables the same clocks — we can skip clock init
    B. PBL enables a subset — we need to enable the rest
    C. PBL's clock tree is different (different root PLL)

  Impact: If we do BCR reset, we must disable clocks before assert,
          re-enable after deassert (clock domain crossing issue).
          If we skip BCR, clocks from PBL are fine.

  Test: Read all USB CBCR registers in entry.S to confirm PBL state.

  *** RESULT (2026-03-07): PBL clocks are sufficient for inherit path.   ***
  *** SYSTEM_CBCR=0x4ff1 (enabled), AHB_CBCR=0x2000cff0, 0x30=0x20008000 ***
  *** PHY_CFG_AHB_CBCR=0, PHY_SLEEP_CBCR=0 (both disabled/zeroed).      ***
  *** Answer: PBL enables enough clocks — we can skip clock init.         ***
```

### 1.7 Pending Transfers

```
UNKNOWN: Are there any pending/active dTDs when PBL jumps to us?

  Possible answers:
    A. No — PBL completes all transfers before jumping
    B. Yes — PBL jumps with a receive dTD still primed (listening for
       the next Sahara packet that will never come)
    C. PBL flushes endpoints before jumping

  Impact: If there are active dTDs, writing to controller registers while
          DMA is in flight could cause bus errors or memory corruption.
          Must flush endpoints before modifying dQH.

  Test: Read USB_ENDPTSTAT (0x078D91B8) and USB_ENDPTPRIME (0x078D91B0)
        in entry.S. Non-zero means active transfers.

  *** RESULT (2026-03-07): ENDPTSTAT is non-zero (green LED). ***
  Answer is B. PBL leaves primed transfer(s). Must flush before dQH swap.
  *** After flush, USB events still arrive (host is talking). ***
```

---

## 2. What We Know from the Decompiled Original

### 2.1 Original Programmer USB Init (FUN_0801aba0)

The original programmer does a **full USB re-initialization**, not an inherit.
Here is the exact sequence from `src/fhprg/fhprg_801a5f0.c:489`:

```
Step  Function             Register/Action                    Notes
─────────────────────────────────────────────────────────────────────────────
 1    FUN_0800a80c()       Disable 3 CBCRs:                   Clock teardown before BCR
                           0x01841004=0, 0x01841008=0,
                           0x01841030=0
                           (only if 0x01841004 bit 31 clear)

 2    FUN_0801a704(0)      0x01841000 = 1                     Assert BCR (GCC_USB_HS_BCR)
 3    FUN_0801a704(1)      0x0184103C = 1                     Assert PHY_CFG_AHB_CBCR? (or disable)
 4    delay(10ms)
 5    FUN_0801a728(1)      0x0184103C = 0                     Deassert/enable PHY_CFG_AHB_CBCR
 6    delay(75ms)
 7    FUN_0801a728(0)      0x01841000 = 0                     Deassert BCR
 8    delay(10ms)

 9    FUN_0800abf4()       Enable 3 CBCRs:                    Clock restore after BCR
                           0x01841004=1, 0x01841008=1,
                           0x01841030=1
                           (via FUN_0800b140 with vote enable)

10    PORTSC = 0x80000000                                     ULPI PHY select

11   FUN_0801a704(2)      0x01841034 = 1                     Assert PHY_SLEEP_CBCR? (or enable)

12   ULPI write 0x80=0x33                                     PHY tuning reg 0
13   ULPI write 0x81=0x33                                     PHY tuning reg 1
14   ULPI write 0x82=0x07                                     PHY tuning reg 2
15   ULPI write 0x83=0x13                                     PHY tuning reg 3

16   delay(10ms)

17   FUN_0801a728(2)      0x01841034 = 0                     Deassert PHY_SLEEP_CBCR
18   delay(75ms)

19   FUN_0801a948()        ULPI write 0x96=0x03               Unknown PHY reg
                           0x078D90A0 |= 0x80                 PHY enable bit
                           0x078D9140 |= 0x02000000           USBCMD |= ITC=8? or RS-related
```

**Key observations:**
- Does BCR reset (full hardware reset of USB subsystem)
- Carefully sequences clock disable → BCR assert → BCR deassert → clock enable
- Reconfigures ULPI PHY after BCR (writes to regs 0x80-0x83, 0x96)
- Sets PORTSC to ULPI mode
- Does NOT do USBCMD RST (bit 1) — the BCR does a deeper reset
- Does NOT explicitly set ENDPOINTLISTADDR here (done elsewhere)
- Does NOT explicitly set DEVICEADDR (re-enumeration will assign it)
- Final step sets RS bit via `0x078D9140 |= 0x02000000` (if that's USBCMD)

### 2.2 Original's Post-Init: Endpoint Setup

After `FUN_0801aba0`, the calling chain continues through:
- `FUN_0801a754`: Complex state machine for PHY negotiation (FS/HS detection)
  - Uses ULPI reads/writes to registers 0x84, 0x87, 0x91, 0x93
  - Checks for device attachment (ULPI reg 0x87 bit 1)
  - Configures OpMode via ULPI reg 0x0A (OTG control)
  - 100-iteration timeout loop
- `FUN_0802fff8`: Endpoint configuration (max packet size, dQH setup)
- `FUN_0802f9ea`: Two-phase enumeration poll
  - Phase 1: 10,000 iterations × 3ms = 30s max
  - Phase 2: 1,000 iterations × 3ms = 3s max (fallback)
- `pm_usb_enum()` at 0x0802ab44: Orchestrates the full enumeration

### 2.3 Original's dQH Table

The original places dQH at `0x87C74800` (in DDR). This means:
- It initializes DDR before USB
- dQH table is in cached DDR (must do cache maintenance for DMA coherency)
- dTD pool starts at `0x87C74900`
- Index calculation involves endpoint × 0x1040 offsets

### 2.4 Original's Enumeration Handling

The original has a full interrupt-driven USB stack:
- `FUN_0801aa38`: Interrupt handler for transfer completion
  - Reads ENDPTCOMPLETE, processes completed dTDs
  - Invokes per-endpoint callbacks
- Setup packet handling and descriptor responses (similar to our minimal impl)
- Supports disconnect detection and re-enumeration

### 2.5 Original vs Minimal: Key Differences

| Aspect | Original | Minimal |
|--------|----------|---------|
| Reset type | BCR (full HW reset) | USBCMD RST (controller only) |
| ULPI PHY config | Full reconfiguration (0x80-0x83, 0x96) | None (inherits PBL) |
| Clock management | Disable → BCR → enable (careful sequencing) | None (inherits PBL) |
| dQH location | DDR (0x87C74800) | OCIMEM (BSS-allocated) |
| dTD management | Pool with linked lists | Single static dTD per direction |
| Transfer mode | Interrupt-driven with callbacks | Polling |
| PHY negotiation | State machine (FUN_0801a754) | None |
| Enumeration wait | 10000+1000 iterations × 3ms | 10s timeout |

---

## 3. What We Know from the Minimal Programmer

### 3.1 Current Init Sequence (usb.c:432)

```
1. Clear RS bit (USB_USBCMD &= ~1)          Stop controller, D+ deasserts
2. delay(2ms)
3. Flush all endpoints (USB_ENDPTFLUSH=0xFFFFFFFF)
4. USBCMD reset (USB_USBCMD = 0x00080002)   RST=1, ITC=8
5. Poll until RST bit clears
6. USB_PORTSC = 0x80000000                   Restore ULPI PHY select
7. Set device mode (USB_USBMODE = 2)
8. Zero + init dQH table (EP0 only)
9. USB_ENDPOINTLISTADDR = &dqh_table
10. USB_USBINTR = 0                          Disable interrupts (poll mode)
11. USB_USBMODE |= 0x08                      Setup lockout
12. Clear USB_ENDPTSETUPSTAT
13. USB_AHB_MODE = 8                         AHB burst config
14. USB_USBCMD |= 1                          Set RS, D+ asserts, host sees reconnect
15. Read PORTSC for speed detection
```

### 3.2 Assumptions We're Making

1. **PBL's PHY config is sufficient** — We don't reconfigure ULPI registers.
   The original does (0x80=0x33, 0x81=0x33, 0x82=0x07, 0x83=0x13). If PBL
   uses different values, our PHY tuning may be suboptimal.

2. **PBL's clocks are still running** — We don't touch any GCC USB registers.
   If USBCMD reset somehow affects clock gating, we'd be stuck.

3. **USBCMD reset is sufficient** — We don't do BCR. The original does BCR.
   USBCMD reset preserves PHY state; BCR resets everything. Since we inherit
   PBL's PHY config, USBCMD-only reset should be fine.

4. **D+ deassert during USBCMD reset triggers host re-enumeration** — The
   host sees disconnect, then reconnect when we set RS=1. Both sides reset
   data toggles. SET_CONFIGURATION synchronizes everything.

5. **The host handle survives** — The Go client opens device by VID:PID. After
   our D+ blip, Linux may re-enumerate the device with a new device node. The
   Go client's 1.5s sleep + `OpenDeviceWithVIDPID` reopens the new node.
   BUT: the Go client opens the device ONCE in `cmd/connect.go` and passes
   the handle to both Sahara and Firehose. It does NOT reopen after Sahara.

6. **OCIMEM dQH table works** — DMA from the USB controller can access OCIMEM.
   The original uses DDR. We haven't confirmed USB DMA can reach our OCIMEM
   addresses.

7. **No cache issues with OCIMEM** — OCIMEM may or may not be cacheable
   depending on PBL's page table. We do cache maintenance anyway.

### 3.3 What Actually Happens (Observed Behavior)

- Device reaches `main()` (solid red LED confirms this)
- `usb_init()` completes (init_progress = 0x07)
- No USB events seen (usb_seen_events = 0x00)
- Host sees... what? We don't have USB protocol analyzer data
- No banner received by host
- Go client gets ENODEV or timeout

---

## 4. External Research: ChipIdea USB 2.0 Controller

### 4.1 Controller Architecture

The MSM8909 USB HS controller is a **ChipIdea ci13xxx** (sometimes called
ci_hdrc in Linux), implementing the EHCI device-mode register interface.
Base address: `0x078D9000`. This is NOT DWC3 (which is used on newer
Qualcomm SoCs like MSM8996+).

Linux kernel driver: `drivers/usb/chipidea/` (core.c, udc.c).
Qualcomm platform glue: `drivers/usb/chipidea/ci13xxx_msm.c`.

### 4.2 USBCMD Reset (bit 1) Behavior

From the Linux kernel ChipIdea driver and EHCI specification:

**What USBCMD RST clears:**
| State | Cleared? |
|-------|----------|
| ENDPOINTLISTADDR | Yes — set to 0 |
| DEVICEADDR | Yes — set to 0 |
| Data toggles (all EPs) | Yes — reset to DATA0 |
| PORTSC (PHY select) | Yes — must rewrite 0x80000000 for ULPI |
| USBMODE (device/host) | Yes — must rewrite |
| USBINTR | Yes — all interrupts disabled |
| GENCONFIG/GENCONFIG2 | Yes — Qualcomm wrapper registers reset |
| RS (Run/Stop) bit | Yes — cleared, D+ deasserts |
| PHY state/clocks | No — PHY untouched |
| Clock registers (GCC) | No — separate domain |
| ULPI PHY registers | No — accessed only via viewport |

**D+ behavior during USBCMD RST:**
The RS bit controls the internal 1.5kΩ D+ pullup. When RST clears RS:
- D+ goes low → bus enters SE0 state
- If SE0 lasts > 2.5μs (hub minimum) or > 100μs (reliable), host detects disconnect
- USBCMD RST takes ~1ms to complete → D+ is low for at least 1ms → disconnect is guaranteed

From `drivers/usb/chipidea/udc.c`:
```c
// ci_udc_pullup:
if (is_on)
    hw_write(ci, OP_USBCMD, USBCMD_RS, USBCMD_RS);  // D+ up
else
    hw_write(ci, OP_USBCMD, USBCMD_RS, 0);           // D+ down
```

### 4.3 BCR Reset vs USBCMD Reset

| | USBCMD RST (bit 1) | BCR (GCC_USB_HS_BCR) |
|---|---|---|
| Scope | Controller logic only | Entire USB subsystem |
| PHY state | Preserved | Reset |
| ULPI regs | Preserved | Reset (need reconfiguration) |
| Clock requirement | None | Must disable clocks before assert |
| Recovery | Write PORTSC, USBMODE, ENDPOINTLISTADDR | Full clock + PHY + controller reinit |
| D+ behavior | Deasserts (RS cleared) | Deasserts (everything reset) |
| Time to recover | ~1ms + re-enumeration | ~200ms + ULPI config + re-enumeration |

### 4.4 Data Toggle Synchronization

Per USB 2.0 specification:

| Event | Host resets? | Device resets? |
|-------|-------------|---------------|
| USB bus reset (SE0 >10ms) | All EPs → DATA0 | All EPs → DATA0 |
| SET_CONFIGURATION | All EPs → DATA0 | All EPs → DATA0 |
| SET_INTERFACE | Affected EPs → DATA0 | Affected EPs → DATA0 |
| CLEAR_FEATURE(EP_HALT) | → DATA0 | → DATA0 |
| ENDPTCTRL reset bit | **NOT reset** | → DATA0 |
| USBCMD RST | **NOT reset** (host unaware) | → DATA0 |

**Key insight:** After USBCMD RST + D+ deassert, the host detects disconnect.
When D+ reasserts (RS=1), the host sees a "new" device, sends bus reset,
then enumerates. Both bus reset and SET_CONFIGURATION reset toggles on both
sides. So the full cycle is: USBCMD RST → disconnect → reconnect → bus reset
→ enumeration → SET_CONFIGURATION → toggles synchronized.

This means USBCMD RST is safe for toggle synchronization IF the host goes
through full re-enumeration.

### 4.5 ULPI Viewport (0x078D9170)

Indirect access to external USB PHY registers:

```
Write: reg[ADDR] = DATA
  viewport = 0x60000000 | (ADDR << 16) | DATA
  poll until bit 30 clears

Read: DATA = reg[ADDR]
  viewport = 0x40000000 | (ADDR << 16)
  poll until bit 30 clears
  DATA = (viewport >> 8) & 0xFF
```

Key ULPI registers:
| Addr | Name | Reset value |
|------|------|-------------|
| 0x04 | Function Control | XcvrSelect, TermSelect, OpMode, SuspendM |
| 0x07 | Interface Control | ClockSuspendM |
| 0x0A | OTG Control | DpPulldown, DmPulldown, DrvVbus |
| 0x80-0x83 | Vendor-specific | Tuning/trim (Qualcomm PHY specific) |
| 0x87 | Vendor-specific | Bit 1 = device attached? |
| 0x96 | Vendor-specific | Unknown (original writes 0x03) |

### 4.6 ENDPOINTLISTADDR and dQH Table

- Must be **2048-byte (2KB) aligned** (bits [10:0] = 0)
- Table has 32 entries: 16 endpoints × 2 directions (OUT/IN)
- Each entry is 64 bytes (dQH structure)
- Total table size = 32 × 64 = 2048 bytes

Entry indexing:
```
EP0 OUT = index 0    EP0 IN = index 1
EP1 OUT = index 2    EP1 IN = index 3
...
EPn OUT = index 2n   EPn IN = index 2n+1
```

### 4.7 Host-Side Behavior (Linux)

When D+ deasserts and reasserts:
1. Hub detects port status change (SE0 > 2.5μs)
2. Linux USB core calls `usb_disconnect()` → old device node invalidated
3. Hub detects new connection (D+ asserted)
4. Linux enumerates: bus reset → GET_DESCRIPTOR → SET_ADDRESS → SET_CONFIGURATION
5. **New device node created** — old file descriptors get ENODEV

This means the Go client's USB handle from Sahara **will become invalid**
after our USBCMD reset. The client must re-open the device.

**Current Go client behavior** (`client/sahara/sahara.go:248-251`):
```go
// After Sahara DONE_RSP:
time.Sleep(1500 * time.Millisecond)
return nil  // Same handle passed to firehose code
```

The client does NOT re-open the device. It sleeps 1.5s hoping the programmer
boots and is ready. If the programmer causes a USB disconnect/reconnect, the
old handle is dead. This works with the stock programmer because... why?

**Hypothesis**: The stock programmer's BCR + full reinit causes disconnect +
reconnect within the 1.5s window. The old gousb handle's underlying libusb
context sees the device reappear at the same bus/port and the handle remains
valid. OR: the host's usbfs driver rebinds the same device node after
re-enumeration of the same VID:PID at the same port. Need to verify.

---

## 5. Testable Hypotheses

### H1: PBL Leaves RS=1 (Controller Running)

**Test:** In entry.S, immediately after PBL jumps to us, read USB_USBCMD
(0x078D9140) and store bits 0-1 (RS and RST) in a known location. Report
via LED pattern.

**If RS=1:** Inherit approach is theoretically possible.
**If RS=0:** PBL already stopped the controller. We must restart.

### H2: PBL's dQH Table is in Accessible Memory

**Test:** Read USB_ENDPOINTLISTADDR (0x078D9158) in entry.S. Dump 128 bytes
starting at that address (EP0 OUT + EP0 IN dQH entries). Check if the
memory is readable and contains plausible dQH data.

### H3: Go Client Handle Survives Disconnect/Reconnect

**Test:** With the current minimal programmer (which does USBCMD reset),
add debug logging to the Go client around USB reads after Sahara. Check
whether the handle returns ENODEV or just timeouts. Try adding a
re-open-by-VID:PID after the 1.5s sleep.

**If ENODEV:** Must modify Go client to reopen.
**If timeout:** Handle is alive but device isn't responding. Different problem.

### H4: USB DMA Can Access Our OCIMEM dQH Table

**Test:** After USBCMD reset, we write ENDPOINTLISTADDR pointing to our
OCIMEM-resident dQH table. If the controller can DMA from there, setup
packets will be delivered. If not, the controller hangs or ignores packets.

Verify by checking if USB_ENDPTSETUPSTAT ever gets a bit set (indicating
a setup packet was received). If yes, DMA works. If no events at all
after 10s, DMA to OCIMEM may be blocked.

### H5: USBCMD Reset Preserves Working PHY Configuration

**Test:** Before and after USBCMD reset, read ULPI registers 0x80-0x83, 0x96
via viewport. If values are unchanged, PHY config survives USBCMD reset
(as expected from documentation).

### H6: The Original Programmer Also Causes Host Disconnect

**Test:** Run the stock `fhprg_peek.bin` through Sahara while monitoring
`dmesg -w` on the host. Look for USB disconnect/reconnect messages.
Record the timing between disconnect and reconnect.

**If disconnect seen:** Confirms BCR reset causes disconnect. Go client's
handle survival mechanism is the key to understand.
**If no disconnect:** The original programmer has a different USB handover
that we're missing entirely.

### H7: D+ Deassert Duration Matters

**Test:** Measure time between RS=0 (step 1 of our init) and RS=1 (step 14).
Currently we do USBCMD reset in between, which adds ~1ms. Total D+ low
time is probably ~5-10ms. If we minimize this, does the host even notice?

USB spec says hub detects disconnect after 2.5μs of SE0. Our gap is ~1000×
longer. The host WILL see a disconnect. Minimizing it won't help.

### H8: The Go Client Works Because gousb Rebinds

**Test:** Modify the Go client to log the USB bus address and device address
before and after the 1.5s sleep. If the device address changes, the host
re-enumerated. If gousb's `OpenDeviceWithVIDPID` implicitly reopens, the
handle might "work" despite the reconnect because gousb abstracts the
underlying fd.

Actually, the Go client calls `Open()` once and passes the `Device` struct
through. It does NOT call `OpenDeviceWithVIDPID` again after Sahara. So
if the underlying fd is invalidated, reads/writes will fail.

### H9: Stock Programmer Doesn't Cause Disconnect (Inherit Path)

**Counter-hypothesis to H6:** The stock programmer might NOT do BCR reset
on this specific code path. `FUN_0801aba0` does BCR, but maybe there's
a different entry point that skips it.

**Test:** Trace the call chain from programmer entry to USB-ready state.
Check if there's a conditional that skips BCR when USB is already
initialized (e.g., checking if clocks are already on).

Note from decompiled code: `FUN_0800a80c` (clock disable before BCR) checks
`if (-1 < _DAT_01841004)` — this is `if (bit 31 of CBCR is clear)`.
Bit 31 of a CBCR is CLK_OFF (1 = clock is off). So the condition is:
"if clock is running, proceed with disable + BCR". If PBL left the clock
running, the original WILL do BCR. If PBL somehow stopped the clock,
the original skips the disable step but still does BCR assert.

Similarly, `FUN_0800abf4` (clock enable after BCR) checks
`if ((_DAT_01841004 & 1) == 0)` — "if CBCR enable bit is not set,
enable it". This is a conditional enable, not unconditional.

---

## 6. Decision Tree: What Init Strategy to Use

```
READ USB_USBCMD in entry.S
│
├── RS=1 (controller running, D+ asserted)
│   │
│   ├── Option A: Inherit session
│   │   ├── Read ENDPOINTLISTADDR → find PBL dQH
│   │   ├── Read toggle state from dQH overlay
│   │   ├── Set up our own dQH table matching PBL's toggles
│   │   ├── Atomically swap ENDPOINTLISTADDR
│   │   ├── DO NOT touch ENDPTCTRL (preserves toggles)
│   │   ├── DO NOT touch USBCMD (preserves RS)
│   │   ├── Host sees no disconnect → same handle works
│   │   └── Risk: Any timing glitch → silent data corruption
│   │
│   └── Option B: USBCMD reset (current approach)
│       ├── RS=0 → D+ deasserts → host disconnect
│       ├── USBCMD RST → clean state
│       ├── Fresh dQH, RS=1 → D+ asserts → host re-enumerates
│       ├── Go client handle dies → must reopen device
│       └── CONFIRMED CORRECT by USB spec, but needs client fix
│
└── RS=0 (controller stopped)
    │
    ├── Option C: USBCMD reset (current approach works)
    │
    └── Option D: BCR + full reinit (match original)
        ├── Most conservative — replicates known-working path
        ├── Requires ULPI PHY reconfiguration
        ├── Requires clock sequencing
        └── Takes ~200ms longer
```

---

## 7. Recommended Experiments (Priority Order)

1. **Dump PBL controller state** (H1, H2, H4) — Read USB_USBCMD,
   USB_ENDPOINTLISTADDR, USB_ENDPTSTAT, USB_DEVICEADDR, USB_PORTSC
   in entry.S. Store in known memory. Report first byte of USBCMD via LED.
   This resolves H1, H2, and informs all other decisions.

2. **Monitor host dmesg during stock programmer** (H6) — Plug in device,
   watch `dmesg -w` for disconnect/reconnect events during Sahara→Firehose
   transition with the stock programmer. This tells us if the stock
   programmer also causes a host-visible disconnect.

3. **Check Go client error type** (H3) — Add error logging to the Go client.
   After 1.5s sleep, attempt a small read and log the exact error. ENODEV
   vs timeout tells us if the handle died.

4. **Read ULPI PHY registers** (H5) — Before any init, read ULPI regs
   0x80-0x83 via viewport. Compare with stock programmer values.

5. **Try inherit approach** (H1, depends on experiment 1) — If PBL leaves
   RS=1, try the inherit path: read ENDPOINTLISTADDR, set up matching dQH,
   swap, no RS toggle. See if bulk I/O works.

6. **Try BCR + full reinit** (match original) — As fallback, replicate the
   original's full sequence: clock disable → BCR → clock enable → ULPI →
   PORTSC → RS=1. Fix Go client to reopen if needed.

---

## 8. Final Implementation: PBL Session Inheritance

Based on the hardware probing results (sections 1.1-1.7), we implemented the
**inherit approach** — no controller reset, no re-enumeration.

### What We Confirmed

| Question | Result |
|----------|--------|
| RS=1 at jump? | **Yes** — PBL leaves controller running |
| dQH location? | PBL SRAM (not OCIMEM) — safe from our BSS |
| Pending transfers? | **Yes** — ENDPTSTAT non-zero, must flush |
| USB DMA to OCIMEM? | **No** — prime never completes with OCIMEM buffers |
| USB DMA to DDR? | **Yes** — works perfectly |

### Implementation (`src_minimal/usb.c`)

```
usb_init():
  1. Read ENDPOINTLISTADDR → PBL's dQH table base
  2. Calculate dQH pointers: EP1 OUT = base+128, EP1 IN = base+192
  3. Disable USB interrupts (USBINTR=0)
  4. Flush all endpoints (ENDPTFLUSH=0xFFFFFFFF, poll until clear)
  5. Clear USBSTS + ENDPTCOMPLETE
  6. Set usb_online=1 immediately

usb_read(buf, maxlen):
  1. Queue dTD (in DDR) on PBL's dQH[2] (EP1 OUT)
  2. DMA target = DDR staging buffer (usb_rx_buf)
  3. Prime ENDPTPRIME, poll ENDPTCOMPLETE
  4. memcpy from DDR staging buffer to caller's buffer

usb_write(buf, len):
  1. memcpy from caller's buffer to DDR staging buffer (usb_tx_buf)
  2. Queue dTD (in DDR) on PBL's dQH[3] (EP1 IN)
  3. Prime ENDPTPRIME, poll ENDPTCOMPLETE
```

### Key Design Decisions

1. **Keep PBL's dQH** — Don't swap ENDPOINTLISTADDR. PBL's dQH is in PBL
   SRAM where USB DMA can reach it. Swapping to OCIMEM fails silently.

2. **DDR staging buffers** — All dTDs and data buffers in `.ddr_bss` section.
   Callers pass OCIMEM pointers (stack/BSS); driver copies to/from DDR.

3. **No EP0 handling** — PBL handled enumeration. We never see setup packets.
   Removed all descriptor tables, setup handler, and address assignment code.

4. **No clock/PHY management** — PBL's USB clocks and ULPI PHY config are
   inherited as-is. No BCR reset, no ULPI viewport writes.

5. **No data toggle concerns** — We don't reset the controller, so device-side
   toggles stay in sync with the host. No bus reset, no re-enumeration.

### Hardware Bug: dqh->current == dqh->next

When reusing the same dTD for consecutive transfers on the same endpoint,
the ChipIdea controller sees `dqh->current` (set by hardware to the last
executed dTD) equal to `dqh->next` (set by software for the new transfer).
This is undefined behavior per the ChipIdea spec and causes the controller
to hang silently — prime succeeds but transfer never completes.

Fix: clear `dqh->current = 0` before writing `dqh->next` in `prime_ep()`.

### PBL Controller State (Register Dump)

Register values read from the running diagnostic console after USB init:

| Register | Address | Value | Decoded |
|----------|---------|-------|---------|
| USBCMD | 0x078D9140 | 0x02080001 | RS=1 (running), ITC=8μframes |
| USBSTS | (cleared) | — | Cleared during init |
| DEVICEADDR | 0x078D9154 | 0x38000000 | Address 7 (bits 31:25) |
| ENDPOINTLISTADDR | 0x078D9158 | 0x00206000 | PBL dQH in PBL SRAM |
| PORTSC | 0x078D9184 | 0x88000205 | High-speed, ULPI, port enabled |
| USBMODE | 0x078D91A8 | 0x0000001A | Device mode, SLOM, SDIS |

### PBL Clock State

| Register | Address | Value | Status |
|----------|---------|-------|--------|
| GCC_USB_HS_SYSTEM_CBCR | 0x01841004 | 0x00004ff1 | Enabled, running |
| GCC_USB_HS_AHB_CBCR | 0x01841008 | 0x2000cff0 | Bit 0=0 (not voted) |
| GCC_USB_HS_CBCR (0x30) | 0x01841030 | 0x20008000 | Bit 0=0 (not voted) |
| GCC_USB_HS_PHY_CFG_AHB_CBCR | 0x0184103C | 0x00000000 | Disabled |
| GCC_USB2A_PHY_SLEEP_CBCR | 0x01841034 | 0x00000000 | Disabled |

Note: The original programmer enables all 3 CBCRs (0x01841004, 0x01841008,
0x01841030) after BCR deassert. PBL only has SYSTEM_CBCR fully enabled.
The AHB and 0x30 CBCRs have bit 0=0 but appear functional (USB works).

### What Was Removed

- USBCMD reset sequence
- Full dQH table in OCIMEM
- EP0 setup packet handler
- USB device/config/string descriptors
- ULPI viewport write function
- USB clock enable/disable (BCR sequence)
- `usb_poll()`, `usb_get_status()`, `usb_get_init_progress()`, `usb_get_ulpi_timeouts()`
- Speed detection and high-speed/full-speed packet size handling
