#include <chip_8_display.h>
#include <string.h>

void draw_debug_grid(chip_8_display *display) {
  bool paint = false;

  for (size_t i = 0; i < sizeof(display->pixels); i++) {
    if (i % CHIP_8_DISPLAY_MAX_WIDTH == 0) {
      paint = !paint;
    }

    display->pixels[i] = paint;

    paint = !paint;
  }
}

void chip_8_display_draw(chip_8_display *display) { draw_debug_grid(display); }

void chip_8_display_wipe(chip_8_display *display) {
  memset(display->pixels, 0, sizeof(display->pixels));
}
