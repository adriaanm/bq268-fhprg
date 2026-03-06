# LED Checkpoint Map — Minimal Programmer

## LED Conventions

| Pattern | Meaning |
|---------|---------|
| **Green blink** (hw timer, 0.5s on/off) | Init checkpoint (early, before clock changes) |
| **Green blink** (CPU loop) | Init checkpoint (after clock changes may affect timetick) |
| **Red blinks N times + pause** (CPU loop) | Exception: DFSR[3:0] = fault type (count the blinks) |
| **Both LEDs dark** | main() reached (turns off both LEDs) |
| **Red solid** (from _start) | Background — red turns on at entry, stays on through init |

**Rules:**
- Checkpoints (normal flow) and error/exception paths MUST use visually distinct LED patterns.
  Never reuse the same color for both — it causes confusion when debugging.
- Green = forward progress checkpoints only.
- Red N-blink pattern = exception/crash only (count blinks to identify fault type).
- When adding/removing checkpoints, update this file.

## Current Checkpoint Sequence (entry.S)

| # | LED | Trigger | Timer | What completed |
|---|-----|---------|-------|----------------|
| 0 | Red ON (solid) | _start | instant | PBL jumped to us |
| 1 | Green blink | checkpoint (hw) | 0.5s | VBAR + DACR + TTBCR |
| 2 | Green blink | checkpoint (hw) | 0.5s | Stack + .data copy + BSS zero |
| 3 | Green blink | checkpoint (hw) | 0.5s | GPLL0 locked |
| 4 | Green blink | checkpoint_cpu | hw timer | Early clock init (0x01830038 etc.) |
| 5 | Green blink | checkpoint_cpu | hw timer | ddr_set_params |
| 6 | Green blink | checkpoint_cpu | hw timer | bimc_clock_init |
| 7 | Green blink | checkpoint_cpu | hw timer | (icb_config skipped) |
| 8 | Green blink | checkpoint_cpu | hw timer | ddr_init |
| - | 2× Red blink + 3× Green blink | main() arrival | hw timer | main() reached (200ms cadence) |
| - | Green ON (solid) | main() | | setup_page_table + USB initializing |
| - | Red ON (500ms) | USB online | hw timer | USB SET_CONFIGURATION received |
| - | Red toggles | command loop | per cmd | USB diagnostic command processed |

## Init Order (matches original sbl1_hw_init)

1. VBAR + DACR + TTBCR
2. Stack + .data + BSS zero
3. GPLL0 PLL lock (no early page table — PBL's page table works fine)
4. Early clock init
5. ddr_set_params
6. bimc_clock_init
7. (icb_config skipped — was causing ddr_init faults)
8. ddr_init
9. main() → setup_page_table (adds DDR mappings to new L1 table) → USB

## USB Diagnostic Mode (main.c)

After entry.S completes, main() enters USB diagnostic mode:
1. Green ON = main() reached, USB controller initializing
2. Green OFF + Red ON 500ms = USB SET_CONFIGURATION received (host connected)
3. Command loop: red toggles on each command (activity indicator)

## Exception Handler (DFSR diagnostic)

- Reads DFSR[3:0] (fault status code)
- Turns OFF green LED
- Blinks red LED N times (N = DFSR[3:0]), then long pause, repeats
- Uses CPU-loop delays (timetick may not be running)
- ARM-mode vectors at `_vectors` label

### Fault Type Reference (DFSR[3:0])

| Blinks | Fault Type |
|--------|------------|
| 1 | Alignment fault |
| 5 | Translation fault (section) |
| 7 | Translation fault (page) |
| 8 | External abort (section) |
| 13 | Permission fault (section) |
| 15 | Permission fault (page) |

## Error Indicators

| Pattern | Meaning |
|---------|---------|
| Fast red blink (200ms, hw timer) | DDR blob not loaded (signature mismatch at 0x00220000) |
| Red N-blink + pause (CPU loop) | ARM exception — count blinks for DFSR[3:0] fault type |

## History of Confusing Patterns (avoid repeating)

- Both LEDs solid ON was used for exception handler AND for main() success indicator simultaneously.
  Result: impossible to distinguish crash from success.
- Green blinks used for checkpoints AND exception handler turned green on.
  Result: extra "checkpoint" appeared that was actually an exception.
- CPU-loop delays (`checkpoint_cpu`) become extremely slow with caches/MMU disabled.
  Use hardware timer (`MPM2_MPM_SLEEP_TIMETICK`) for reliable timing regardless of cache state.
- Uniform rapid-blink exception handler gives no info about fault type.
  Replaced with DFSR-based N-blink pattern.
