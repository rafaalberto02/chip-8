#ifndef CHIP_8_STACK_H
#define CHIP_8_STACK_H

#include <stdint.h>
#include <stdio.h>

#ifndef STACK_DEFAULT_CAPACITY
#define STACK_DEFAULT_CAPACITY 16
#endif

typedef struct {
  size_t capacity;
  size_t count;
  uint16_t *items;
} chip_8_stack;

uint16_t stack_push(chip_8_stack *stack, uint16_t item);
uint16_t stack_pop(chip_8_stack *stack);
void stack_free(chip_8_stack *stack);

#endif
