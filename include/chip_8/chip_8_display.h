#ifndef CHIP_8_DISPLAY_H
#define CHIP_8_DISPLAY_H

#include <stdbool.h>

#ifndef CHIP_8_DISPLAY_MAX_WIDTH
#define CHIP_8_DISPLAY_MAX_WIDTH 64
#endif

#ifndef CHIP_8_DISPLAY_MAX_HEIGHT
#define CHIP_8_DISPLAY_MAX_HEIGHT 32
#endif

#ifndef CHIP_8_DISPLAY_MAX_PIXELS
#define CHIP_8_DISPLAY_MAX_PIXELS                                              \
  (CHIP_8_DISPLAY_MAX_WIDTH * CHIP_8_DISPLAY_MAX_HEIGHT)
#endif

typedef struct {
  bool pixels[CHIP_8_DISPLAY_MAX_PIXELS];
} chip_8_display;

void chip_8_display_draw(chip_8_display *display);

void chip_8_display_wipe(chip_8_display *display);

#endif
