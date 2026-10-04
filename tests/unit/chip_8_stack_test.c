#include "../utils/message_macros.h"
#include "chip_8_stack.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void stack_should_initialize_empty(void) {
  UNIT_TESTING_MESSAGE();

  Stack stack = {0};

  assert(stack.capacity == 0 && "stack.capacity should be zero");
  assert(stack.count == 0 && "stack.count should be zero");
  assert(stack.items == NULL && "stack.items should be NULL");
}

void stack_should_alloc_on_first_push(void) {
  UNIT_TESTING_MESSAGE();

  Stack stack = {0};

  stack_push(&stack, 6969);

  assert(stack.capacity == STACK_DEFAULT_CAPACITY &&
         "stack.capacity should be STACK_DEFAULT_CAPACITY");
  assert(stack.count == 1 && "stack.count should be one");
  assert(stack.items != NULL && "stack.items should be different than NULL");

  stack_free(&stack);
}

void stack_should_increase_capacity_automatically_on_push(void) {
  UNIT_TESTING_MESSAGE();

  Stack stack = {0};

  const int ITEMS_AMOUNT = 248;

  for (int i = 0; i < ITEMS_AMOUNT; i++) {
    uint16_t random_item = (uint16_t)arc4random();

    stack_push(&stack, random_item);
  }

  assert(stack.capacity != STACK_DEFAULT_CAPACITY &&
         "stack.capacity should be different than STACK_DEFAULT_CAPACITY");
  assert(stack.capacity == 256 && "stack.capacity should be equals 256");
  assert(stack.count == ITEMS_AMOUNT &&
         "stack.count should be equals to items_amount");

  stack_free(&stack);
}

void stack_should_decrease_count_and_return_value_on_pop(void) {
  UNIT_TESTING_MESSAGE();

  Stack stack = {0};

  const int ITEMS_AMOUNT = 248;

  uint16_t last_random_item = 13;

  for (int i = 0; i < ITEMS_AMOUNT; i++) {
    uint16_t random_item = (uint16_t)arc4random();

    stack_push(&stack, random_item);

    last_random_item = random_item;
  }

  uint16_t pop_item = stack_pop(&stack);

  assert(stack.count == ITEMS_AMOUNT - 1 &&
         "stack.count should be equals to items_amount minus one");
  assert(last_random_item == pop_item &&
         "last_random_item should be equals to pop_item");

  stack_free(&stack);
}

void stack_should_decrease_capacity_automatically_on_pop(void) {
  UNIT_TESTING_MESSAGE();

  Stack stack = {0};

  const int ITEMS_AMOUNT = 248;
  const int REMOVE_ITEMS_AMOUNT = 17;

  for (int i = 0; i < ITEMS_AMOUNT; i++) {
    uint16_t random_item = (uint16_t)arc4random();

    stack_push(&stack, random_item);
  }

  for (int i = 0; i < REMOVE_ITEMS_AMOUNT; i++) {
    stack_pop(&stack);
  }

  assert(stack.capacity == 240 && "stack.capacity should be equals 240");
  assert(
      stack.count == ITEMS_AMOUNT - REMOVE_ITEMS_AMOUNT &&
      "stack.count should be equals to items_amount minus remove_items_amount");

  stack_free(&stack);
}

void stack_should_reset_to_inital_state_on_free(void) {
  UNIT_TESTING_MESSAGE();

  Stack stack = {0};

  const int ITEMS_AMOUNT = 248;
  const int REMOVE_ITEMS_AMOUNT = 17;

  for (int i = 0; i < ITEMS_AMOUNT; i++) {
    uint16_t random_item = (uint16_t)arc4random();

    stack_push(&stack, random_item);
  }

  for (int i = 0; i < REMOVE_ITEMS_AMOUNT; i++) {
    stack_pop(&stack);
  }

  stack_free(&stack);

  assert(stack.capacity == 0 && "stack.capacity should be zero");
  assert(stack.count == 0 && "stack.count should be zero");
  assert(stack.items == NULL && "stack.items should be NULL");
}

int stack_unit_test(void) {
  START_MESSAGE();

  stack_should_initialize_empty();
  stack_should_alloc_on_first_push();
  stack_should_increase_capacity_automatically_on_push();
  stack_should_decrease_count_and_return_value_on_pop();
  stack_should_decrease_capacity_automatically_on_pop();
  stack_should_reset_to_inital_state_on_free();

  return 0;
}

int main(void) {
  srand(time(NULL));

  stack_unit_test();

  return 0;
}
