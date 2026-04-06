# MC Hammer — Automated Modal Hammer Project Plan

## Overview

An automated impact hammer system for structural dynamics testing (modal analysis). A stepper motor swings a PCB Piezotronics modal hammer on an arm, strikes a target structure, then retracts quickly to prevent double hits. The system is portable, tripod-mounted, and controlled via an Arduino with a small OLED display and rotary encoder knobs.

---

## Goals

- Repeatable, single-impact hits at user-defined force and cadence
- Portable, field-deployable system (pelican case / travel case)
- No machining required — 3D printing for custom brackets/mounts
- Prototype control logic in Wokwi (public simulation) before committing to hardware
- Leverage published research from university modal hammer automation projects

---

## System Architecture

```
[Power Supply]
      |
[Arduino Mega]
      |
 +---------+----------+-----------+-----------+
 |         |          |           |           |
[OLED]  [Closed-loop [Rotary    [Switches]  [Encoder
        Driver]     Encoders]              (position)]
           |
       [NEMA 34 Closed-loop
       Stepper Motor w/ Encoder]
           |
       [Hammer Arm]
           |
       [Modal Hammer tip]
```

### Signal Flow

1. User sets **hit force** and **hit interval** via rotary encoder knobs
2. User presses **HIT switch** to enter hit mode
3. Arduino winds up arm to **wind-up position** (configurable or hard-coded)
4. Arduino drives stepper to swing arm toward target at the programmed velocity
5. **Position encoder** detects zero crossing (user-defined hit point)
6. Arduino immediately reverses stepper at high speed to retract hammer
7. System waits for the programmed interval, then repeats
8. OLED displays current mode, hit count, force setting, and interval

---

## Mechanical Design

### Hammer Arm Assembly

- **Motor:** NEMA 34 closed-loop stepper motor (with integrated encoder), mounted to a 3D-printed or fabricated bracket. Motor + driver kit already owned.
- **Arm:** Lightweight aluminum or carbon fiber rod (or 3D-printed), attached directly to motor shaft via a D-shaft hub
- **Hammer tip:** PCB Piezotronics modal hammer (e.g., 086C03 or similar ICP hammer) attached to the end of the arm
- **Cable management:** Coiled or flex cable from hammer tip to BNC connector on enclosure

### Positioning / Tripod Mount

- Tripod: standard 3/8"-16 threaded tripod head
- Boom arm: mic boom arm (Rode Boom Arm or similar) for horizontal reach
- Sandbag attachment point on boom arm for counterweight stability
- 3D-printed clamp bracket attaches the enclosure/motor assembly to the boom arm

### Enclosure

- Pelican 1510 carry-on case (or similar) for transport
- Smaller secondary enclosure (e.g., Hammond 1590 series or 3D-printed) for the electronics/motor assembly that attaches to the tripod
- BNC output connector for hammer signal (pass-through to DAQ)

---

## Electronics

### Core Components

| Component | Purpose | Wokwi Simulatable |
|---|---|---|
| Arduino Mega 2560 | Main controller | Yes |
| NEMA 34 Closed-loop stepper motor | Hammer swing actuation | Yes (generic stepper) |
| Closed-loop driver (bundled with motor) | Step/dir interface + internal PID | No |
| Quadrature encoder (600 PPR) | Arm position feedback | Yes (rotary encoder) |
| SSD1306 OLED 128x64 (I2C) | Display | Yes |
| KY-040 Rotary Encoder x2 | Force knob, interval knob | Yes |
| Toggle switch | Power / enable | Yes (button) |
| Momentary switch | HIT mode on/off | Yes (button) |
| Momentary switch | ZERO position set | Yes (button) |
| 12V DC power supply | Stepper power | N/A |
| Buck converter (12V → 5V) | Arduino power from same supply | N/A |
| PCB Piezotronics modal hammer | Impact force transducer | N/A (physical only) |
| BNC connector (panel mount) | Signal output to DAQ | N/A |

### Pin Assignment (Arduino Mega — draft)

| Pin | Function |
|---|---|
| 2 | Encoder A (position) |
| 3 | Encoder B (position) |
| 4 | Knob 1 CLK (force) |
| 5 | Knob 1 DT (force) |
| 6 | Knob 1 SW (push button) |
| 7 | Knob 2 CLK (interval) |
| 8 | Knob 2 DT (interval) |
| 9 | Knob 2 SW (push button) |
| 10 | HIT mode switch |
| 11 | ZERO button |
| 12 | Power/enable switch |
| Driver STEP | 54 (A0) |
| Driver DIR  | 55 (A1) |
| Driver EN   | 56 (A2) |
| SDA | 20 |
| SCL | 21 |

---

## Software / Firmware

### State Machine

```
IDLE → (HIT switch ON) → ARMED → WINDING_UP → SWINGING → RETRACTING → WAITING → SWINGING ...
                                                                                     ↓
                                                                        (HIT switch OFF) → IDLE
```

### Key Parameters (user-adjustable)

| Parameter | Knob | Range | Notes |
|---|---|---|---|
| Hit velocity | Knob 1 | Slow–Fast | Maps to stepper speed during swing phase |
| Hit interval | Knob 2 | 1s–60s | Delay between hits |
| Wind-up angle | TBD | Fixed or configurable | How far back to pull before swinging |

### Key Functions

- `setZero()` — captures current encoder count as home position
- `windUp()` — drives motor backward to wind-up position
- `swing()` — drives motor at target velocity toward zero (hit point)
- `retract()` — full-speed reverse after zero crossing detected
- `waitInterval()` — non-blocking delay using millis()
- `updateDisplay()` — refreshes OLED with current state/settings

### Libraries (Arduino)

- `AccelStepper` — stepper motor control with acceleration (works with closed-loop driver via step/dir)
- `Encoder` — quadrature encoder reading
- `Adafruit_SSD1306` + `Adafruit_GFX` — OLED display
- `elapsedMillis` or millis()-based timing

---

## User Interface

### OLED Display Layout (128x64)

```
┌────────────────────┐
│ MODE: HIT          │
│ HITS: 42           │
│ FORCE: 7 / 10      │
│ INTERVAL: 5.0s     │
└────────────────────┘
```

### Controls

| Control | Type | Function |
|---|---|---|
| Power switch | Toggle | Master enable/disable |
| HIT switch | Toggle | Enter/exit hit mode |
| ZERO button | Momentary | Set current position as hit target |
| Force knob | Rotary encoder | Adjust swing velocity (1–10 scale) |
| Interval knob | Rotary encoder | Adjust time between hits |

---

## Wokwi Simulation

A public Wokwi project will be maintained at: *(link TBD — add after project creation)*

### Simulation Scope

- Full Arduino firmware logic (state machine, control flow)
- OLED display output
- Rotary encoder knob interaction
- Button/switch behavior
- Stepper motor stepping visualization

### Simulation Limitations

- No actual force feedback (no ICP hammer sensor in Wokwi)
- Stepper motor is generic (no real inertia/torque modeling)
- Encoder simulation is simplified

---

## References / Prior Work

- [x] University papers found — all use NEMA 34 closed-loop stepper + step/dir driver interface
- [ ] [An Open-Source, Scalable, Low-Cost Automatic Modal Hammer (2021)](https://link.springer.com/article/10.1007/s40799-021-00516-7) — Arduino-controlled; closest match to this build
- [ ] [Smart Automatic Modal Hammer (2024)](https://link.springer.com/article/10.1007/s42417-024-01461-6) — force/velocity regression for consistent excitation
- [ ] [AMH-ISMA System (2025)](https://link.springer.com/article/10.1007/s42417-025-02310-w) — NEMA 34 closed-loop + Raspberry Pi 5; confirms motor choice
- [ ] PCB Piezotronics application notes for ICP signal conditioning
- [ ] GitHub repos: search "automated impact hammer arduino"

---

## Folder Structure

```
mc-hammer/
├── PLAN.md              ← this file
├── BOM.md               ← bill of materials (build manually)
├── README.md
├── hardware/
│   ├── enclosure/       ← case design, panel cutout drawings
│   ├── mounting/        ← 3D print STL/STEP files, bracket designs
│   └── wiring/          ← wiring diagrams, schematics
├── software/
│   └── arduino/         ← main firmware (.ino and .h files)
├── wokwi/               ← diagram.json, wokwi.toml, sketch files
└── docs/
    └── references/      ← PDFs, links, prior art
```

---

## Milestones

- [ ] **M1 — Plan & BOM complete:** Component list finalized, suppliers identified
- [ ] **M2 — Wokwi prototype:** Core state machine and UI running in simulation
- [ ] **M3 — Bench prototype:** Hardware assembled and wired on breadboard/protoboard
- [ ] **M4 — Enclosure build:** Electronics housed, tripod mount working
- [ ] **M5 — Field test:** First real modal test hit, signal captured on DAQ
- [ ] **M6 — Refinement:** Tune retract logic, calibrate force mapping, document results

---

## Open Questions

- [ ] What encoder resolution is needed for reliable zero-crossing detection?
- [ ] Should wind-up angle be user-configurable or hard-coded? (start hard-coded, add later)
- [ ] What is the target force range in Newtons? (depends on test structure)
- [ ] Does the BNC cable from the hammer tip to the enclosure cause any mechanical issues?
- [ ] ICP power conditioning — does the DAQ supply ICP current, or do we need a signal conditioner in-box?
- [ ] Safety: what happens if the arm misses the target or overshoots? Need a soft/hard stop.
