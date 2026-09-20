#ifndef CHIP_8_H
#define CHIP_8_H

#include <stdbool.h>
#include <stdint.h>
#include "stack.h"

struct chip_8 {
  uint8_t memory[4096];
  bool display[64 * 32];

  uint16_t pc;
  uint16_t index;

  Stack stack;

  uint8_t delay_timer;
  uint8_t sound_time;

  uint8_t registers[16];
};

#endif
