#include <chip_8.h>
#include <chip_8_display.h>
#include <math.h>
#include <raylib.h>
#include <stdio.h>

#ifndef DISPLAY_SCALE_FACTOR
#define DISPLAY_SCALE_FACTOR 32
#endif

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Missing file argument\n");

    return -1;
  }

  chip_8 emulator = chip_8_create();

  chip_8_load_font(&emulator);
  chip_8_load_rom(&emulator, argv[1]);

  InitWindow(CHIP_8_DISPLAY_MAX_WIDTH * DISPLAY_SCALE_FACTOR,
             CHIP_8_DISPLAY_MAX_HEIGHT * DISPLAY_SCALE_FACTOR,
             "Chip 8 - Emulator");

  while (!WindowShouldClose()) {
    BeginDrawing();
    {
      ClearBackground(BLACK);

      chip_8_display_wipe(&emulator.display);
      chip_8_display_draw(&emulator.display);

      for (size_t i = 0; i < sizeof(emulator.display.pixels); i++) {
        size_t posX = (i % CHIP_8_DISPLAY_MAX_WIDTH) * DISPLAY_SCALE_FACTOR;

        size_t posY =
            floor(i * 1.0 / CHIP_8_DISPLAY_MAX_WIDTH) * DISPLAY_SCALE_FACTOR;

        if (emulator.display.pixels[i]) {
          DrawRectangle(posX, posY, 1 * DISPLAY_SCALE_FACTOR,
                        1 * DISPLAY_SCALE_FACTOR, LIGHTGRAY);
        }
      }
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
