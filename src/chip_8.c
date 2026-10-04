#include <chip_8.h>
#include <stdio.h>
#include <stdlib.h>

const unsigned int CHIP_8_ROM_MEM_OFFSET = 0x200;
const unsigned int CHIP_8_FONT_MEM_OFFSET = 0x50;

#ifndef CHIP_8_FONTSET_SIZE
#define CHIP_8_FONTSET_SIZE 80
#endif

const uint8_t CHIP_8_FONTSET[CHIP_8_FONTSET_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

chip_8 chip_8_create(void) {
  chip_8 emulator = {0};
  chip_8_display display = {0};
  chip_8_stack stack = {0};

  emulator.pc = CHIP_8_ROM_MEM_OFFSET;
  emulator.display = display;
  emulator.stack = stack;

  return emulator;
}

int chip_8_load_font(chip_8 *chip8) {
  for (unsigned int i = 0; i < CHIP_8_FONTSET_SIZE; i++) {
    chip8->memory[CHIP_8_FONT_MEM_OFFSET + i] = CHIP_8_FONTSET[i];
  }

  return 1;
}

int chip_8_load_rom(chip_8 *chip8, const char *file_name) {
  FILE *rom_file;

  rom_file = fopen(file_name, "rb");

  if (rom_file == NULL) {
    perror("errno");

    fprintf(stderr, "[File %s] could not be opened\n", file_name);

    return -1;
  }

  if (fseek(rom_file, 0, SEEK_END) == -1) {
    perror("errno");

    fprintf(stderr, "[File %s] could not seek to end\n", file_name);

    fclose(rom_file);

    return -1;
  }

  long rom_size = ftell(rom_file);

  if (rom_size == -1) {
    perror("errno");

    fprintf(stderr, "[File %s] could not get file_size\n", file_name);

    fclose(rom_file);

    return -1;
  }

  if (rom_size > CHIP_8_MEM_SIZE - CHIP_8_ROM_MEM_OFFSET) {
    perror("errno");

    fprintf(stderr, "[File %s] has size %ld bigger than %u\n", file_name,
            rom_size, (CHIP_8_MEM_SIZE - CHIP_8_ROM_MEM_OFFSET));

    fclose(rom_file);

    return -1;
  }

  rewind(rom_file);

  fread(&chip8->memory[CHIP_8_ROM_MEM_OFFSET], sizeof(uint8_t), rom_size,
        rom_file);

  fclose(rom_file);

  return 1;
}
