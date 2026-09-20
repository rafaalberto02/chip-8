#include "stack.h"
#include <stdbool.h>
#include <stdlib.h>

const size_t DEFAULT_CAPACITY = 16;

uint16_t stack_push(Stack *stack, uint16_t item) {
  if (stack->count >= stack->capacity) {
    if (stack->capacity == 0)
      stack->capacity = DEFAULT_CAPACITY;
    else
      stack->capacity += DEFAULT_CAPACITY;

    stack->items =
        realloc(stack->items, stack->capacity * sizeof(*stack->items));
  }

  stack->items[stack->count++] = item;

  return item;
}

uint16_t stack_pop(Stack *stack) {
  if (stack->count == 0)
    return 0;

  uint16_t item = stack->items[stack->count--];

  bool can_shrink = stack->count > DEFAULT_CAPACITY &&
                    stack->count < (stack->capacity - DEFAULT_CAPACITY);

  if (can_shrink) {
    stack->capacity -= DEFAULT_CAPACITY;

    stack->items =
        realloc(stack->items, stack->capacity * sizeof(*stack->items));
  }

  return item;
}
