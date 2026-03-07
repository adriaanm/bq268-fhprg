# LED Checkpoint Map — Minimal Programmer

## LED Conventions

| Pattern | Meaning |
|---------|---------|
| **Green pulse** (50ms, hw timer) | Init checkpoint in entry.S |
| **Red blinks N times + pause** | Exception: count blinks for fault type (see below) |
| **Green solid** | main() reached, USB initializing |
| **Red solid** | USB online, command loop active |
| **Red solid** (from _start) | Background — red turns on at entry, stays on through init |

**Rules:**
- Checkpoints (normal flow) and error/exception paths MUST use visually distinct LED patterns.
  Never reuse the same color for both — it causes confusion when debugging.
- Green = forward progress checkpoints only.
- Red N-blink pattern = exception/crash only (count blinks to identify fault type).
- When adding/removing checkpoints, update this file.

## Current Checkpoint Sequence (entry.S)

Checkpoints are 50ms green pulses (50ms on + 50ms off = 100ms each).
All 8 checkpoints add <1s total. Previous 0.5s blinks added 8s and
broke USB (see docs/usb_strategy.md).

| # | LED | Duration | What completed |
|---|-----|----------|----------------|
| 0 | Red ON | instant | PBL jumped to us (USB stays alive with PBL config) |
| 1 | Green pulse | 100ms | VBAR + DACR + TTBCR |
| 2 | Green pulse | 100ms | Stack + .data copy + BSS zero |
| 3 | Green pulse | 100ms | GPLL0 locked |
| 4 | Green pulse | 100ms | Early clock init (0x01830038 etc.) |
| 5 | Green pulse | 100ms | ddr_set_params |
| 6 | Green pulse | 100ms | bimc_clock_init |
| 7 | Green pulse | 100ms | (icb_config skipped) |
| 8 | Green pulse | 100ms | ddr_init |
| - | Green ON (solid) | until online | main() reached, USB init + polling |
| - | Red ON (solid) | ongoing | USB online, command loop |
| - | Red toggles | per cmd | USB diagnostic command processed |

## Init Order (matches original sbl1_hw_init)

0. Red LED on (USB stays alive with PBL's config — do NOT halt controller)
1. VBAR + DACR + TTBCR
2. Stack + .data + BSS zero
3. GPLL0 PLL lock (no early page table — PBL's page table works fine)
4. Early clock init
5. ddr_set_params
6. bimc_clock_init
7. (icb_config skipped — was causing ddr_init faults)
8. ddr_init
9. main() → setup_page_table → usb_init → usb_poll → banner → command loop

## USB Diagnostic Mode (main.c)

After entry.S completes, main() enters USB diagnostic mode:
1. Green ON (solid) = main() reached, USB controller reconfiguring
2. usb_poll() loop = waiting for SET_CONFIGURATION from host
3. If no SET_CONFIGURATION after 10s, error LED pattern (see below)
4. Green OFF + Red ON = online, banner sent
5. Command loop: red toggles on each command (activity indicator)

See `docs/minimal_programmer.md` for the full USB communication strategy.

## Exception Handler (DFSR diagnostic)

Pattern: **P× red blink, 1× green, N× red blink, 1× green, 2s pause, repeat**
- P = exception type: 1=undefined, 2=prefetch abort, 3=data abort
- N = fault status code (DFSR[3:0] for data abort, IFSR[3:0] for prefetch)
- Uses 300ms blink cadence (hw timer)
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
| P×red + green + N×red + green + pause | ARM exception — P=type, N=fault code |
| 3× red blink + pause | USB: no host activity at all (clocks wrong, controller not running) |
| 2× red blink + pause | USB: reset seen but no SET_CONFIGURATION (descriptor issue?) |
| Alternating red/green (500ms each) | USB: host events but no configuration (handle stale) |

## History of Confusing Patterns (avoid repeating)

- Both LEDs solid ON was used for exception handler AND for main() success indicator simultaneously.
  Result: impossible to distinguish crash from success.
- Green blinks used for checkpoints AND exception handler turned green on.
  Result: extra "checkpoint" appeared that was actually an exception.
- CPU-loop delays (`checkpoint_cpu`) become extremely slow with caches/MMU disabled.
  Use hardware timer (`MPM2_MPM_SLEEP_TIMETICK`) for reliable timing regardless of cache state.
- Uniform rapid-blink exception handler gives no info about fault type.
  Replaced with DFSR-based N-blink pattern.
- **0.5s checkpoint blinks (8 total = 8 seconds)** made USB communication impossible.
  Host handle timed out during the delay. Reduced to 50ms pulses.
