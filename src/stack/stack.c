#include "stack/stack.h"
#include "data/data_format.h"

#include <stdlib.h>
#include <string.h>

STACK* stack_init(unsigned long max_size) {
  STACK* stack = malloc(sizeof(STACK) + sizeof(DATA) * max_size);
  memset(stack, 0x00, sizeof(STACK));
  stack->max_size = max_size;
  return stack;
}

void stack_free(STACK* stack, DATA_FORMAT* format) {
  if(format) {
    for(unsigned long i = 0; i < stack->size; i++) {
      format->destructor(&stack->stack[i]);
    }
  } else {
    for(unsigned long i = 0; i < stack->size; i++) {
      default_destructor(&stack->stack[i]);
    }
  }
  free(stack);
}

int stack_push(STACK* stack, void* args, struct DATA_FORMAT* format) {
  if(stack->size >= stack->max_size) return 0;
  if(format) {
    format->constructor(&stack->stack[stack->size++], args);
  } else {
    default_constructor(&stack->stack[stack->size++], args);
  }
  return 1;
}

DATA* stack_peek(STACK* stack) {
  return stack->size ? &stack->stack[stack->size-1] : NULL;
}

DATA* stack_pop(STACK* stack) {
  if(!stack->size) return NULL;

  DATA* data = malloc(sizeof(DATA));
  memcpy(data, &stack->stack[--stack->size], sizeof(DATA));
  return data;
}
