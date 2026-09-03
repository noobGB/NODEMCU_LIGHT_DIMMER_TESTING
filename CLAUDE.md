# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

A single-sketch PlatformIO/Arduino project for a NodeMCU (ESP8266) TRIAC AC dimmer. See
[README.md](README.md) for the phase-cut dimming method and wiring. All logic lives in
[src/main.cpp](src/main.cpp).

## Commands

```
pio run                        # build
pio run -t upload              # flash to a connected NodeMCU
pio device monitor -b 115200   # view serial output
```

No test suite or linter is configured (`test/` is the empty PlatformIO scaffold directory).

## Notes for changes

- `ACdimmer()` runs as an interrupt handler and is marked `ICACHE_RAM_ATTR` so it executes from
  IRAM rather than flash — timing here directly determines dimming accuracy, so avoid adding
  anything (Serial prints, floating point, function calls into flash-resident code) that would
  add latency inside it.
- The `map()` range (`0,1024,7200,200`) sets the usable dimming range in microseconds after each
  zero crossing; the actual bounds depend on line frequency (50/60Hz) and should be re-tuned if
  targeting a different mains frequency.
