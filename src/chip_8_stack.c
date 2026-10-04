#include <chip_8_stack.h>
#include <stdbool.h>
#include <stdlib.h>

uint16_t stack_push(chip_8_stack *stack, uint16_t item) {
  if (stack->count >= stack->capacity) {
    if (stack->capacity == 0)
      stack->capacity = STACK_DEFAULT_CAPACITY;
    else
      stack->capacity += STACK_DEFAULT_CAPACITY;

    stack->items =
        realloc(stack->items, stack->capacity * sizeof(*stack->items));
  }

  stack->items[stack->count++] = item;

  return item;
}

void stack_shrink(chip_8_stack *stack) {
  bool can_shrink = stack->count > STACK_DEFAULT_CAPACITY &&
                    stack->count < (stack->capacity - STACK_DEFAULT_CAPACITY);

  if (can_shrink) {
    size_t new_capacity = stack->capacity - STACK_DEFAULT_CAPACITY;

    printf("Shrinking stack from %ld to %ld\n", stack->capacity, new_capacity);

    stack->capacity = new_capacity;

    stack->items =
        realloc(stack->items, stack->capacity * sizeof(*stack->items));
  }
}

uint16_t stack_pop(chip_8_stack *stack) {
  if (stack->count == 0)
    return 0;

  uint16_t item = stack->items[--stack->count];

  stack_shrink(stack);

  return item;
}

void stack_free(chip_8_stack *stack) {
  if (stack->items != NULL) {
    free(stack->items);
    stack->items = NULL;
    stack->count = 0;
    stack->capacity = 0;
  }
}
