#ifndef CHIP_8_H
#define CHIP_8_H

#include <chip_8_display.h>
#include <chip_8_stack.h>
#include <stdint.h>

/*
 * Keypad       Keyboard
 * +-+-+-+-+    +-+-+-+-+
 * |1|2|3|C|    |1|2|3|4|
 * +-+-+-+-+    +-+-+-+-+
 * |4|5|6|D|    |Q|W|E|R|
 * +-+-+-+-+ => +-+-+-+-+
 * |7|8|9|E|    |A|S|D|F|
 * +-+-+-+-+    +-+-+-+-+
 * |A|0|B|F|    |Z|X|C|V|
 * +-+-+-+-+    +-+-+-+-+
 */

#ifndef CHIP_8_REG_SIZE
#define CHIP_8_REG_SIZE 15
#endif

#ifndef CHIP_8_MEM_SIZE
#define CHIP_8_MEM_SIZE 4096
#endif

typedef struct {
  uint8_t registers[CHIP_8_REG_SIZE];

  /*
   * Address space is from 0x000 to 0xFFF.
   *    0x000-0x1FF: Originally reserved for the CHIP-8 interpreter
   *    0x050-0x0A0: Storage space for the 16 built-in characters (0 through F)
   *    0x200-0xFFF: Instructions from the ROM will be stored starting at 0x200
   * */
  uint8_t memory[CHIP_8_MEM_SIZE];

  /*
   * Both index and pc have a max address space of
   *    0xFFF = `1111 1111 1111` = 12 bits
   *
   * We can use a bitwise operator when setting the value to guarantee
   *    the 12 bits size: `index = value & 0x0FFF`
   * */
  uint16_t index;
  uint16_t pc;

  chip_8_display display;
  chip_8_stack stack;

  uint8_t delay_timer;
  uint8_t sound_time;
} chip_8;

chip_8 chip_8_create(void);

int chip_8_load_font(chip_8 *chip8);

int chip_8_load_rom(chip_8 *chip8, const char *file_name);

#endif
