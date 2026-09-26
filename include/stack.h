#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stdio.h>

#ifndef STACK_DEFAULT_CAPACITY
#define STACK_DEFAULT_CAPACITY 16
#endif

typedef struct {
  size_t capacity;
  size_t count;
  uint16_t *items;
} Stack;

uint16_t stack_push(Stack *stack, uint16_t item);
uint16_t stack_pop(Stack *stack);
void stack_free(Stack *stack);

#endif
