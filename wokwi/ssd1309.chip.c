// Wokwi Custom Chip - SSD1309 2.42" OLED (I2C, 128x64)
// Wokwi handles SSD1306-compatible display rendering via the "display"
// property in ssd1309.chip.json — this stub is intentionally minimal.
//
// Source: https://wokwi.com/projects/379290021266593793
// SPDX-License-Identifier: MIT
// Copyright 2023 Arvind Patil

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
} chip_state_t;

void chip_init() {
  chip_state_t *chip = malloc(sizeof(chip_state_t));
  (void)chip;
}
