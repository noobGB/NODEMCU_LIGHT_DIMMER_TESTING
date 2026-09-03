# NODEMCU_LIGHT_DIMMER_TESTING

A NodeMCU (ESP8266) sketch for phase-cut AC dimming of a resistive load (e.g. an incandescent
or dimmable LED bulb) using a TRIAC, driven off zero-cross detection.

## How it works

An external zero-cross detector circuit pulses GPIO12 (D6) at every AC zero crossing. That pulse
fires an interrupt (`ACdimmer`) which waits `Triac_Pulse_MicroSec_Delay` microseconds — read from
a potentiometer on `A0` and mapped to a 200–7200µs range — then fires an 80µs gate pulse on GPIO4
(D2) to trigger the TRIAC. A shorter delay after the zero crossing fires the TRIAC earlier in the
AC half-cycle, letting more power through (brighter); a longer delay fires it later (dimmer).

The interrupt handler is placed in IRAM (`ICACHE_RAM_ATTR`) since it must run with minimal, precise
latency relative to the zero-crossing pulse.

## Hardware

| Signal | NodeMCU pin |
|---|---|
| Zero-cross detection (input) | GPIO12 (D6) |
| Potentiometer wiper (analog in) | A0 |
| TRIAC gate trigger (output) | GPIO4 (D2) |

This sketch only generates the TRIAC gate pulse — it assumes external zero-cross detection and
TRIAC driver/opto-isolation circuitry are already wired up. **This drives mains AC voltage; treat
the zero-cross and TRIAC driver circuit with the same isolation/safety precautions as any
mains-voltage project.**

## Build and flash

This is a [PlatformIO](https://platformio.org/) project targeting a NodeMCU v2 (ESP8266) board.

```
pio run                        # build
pio run -t upload              # flash
pio device monitor -b 115200   # view serial output
```
