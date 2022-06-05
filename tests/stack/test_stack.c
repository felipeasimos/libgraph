#include "ctdd.h"
#include "stack/stack.h"
#include "data/data_format.h"

#include <stdlib.h>

unsigned long n = 10;
STACK* stack = NULL;

void init_stack() {
  stack = stack_init(n);
}

void init_stack_with_data() {

  init_stack();
  for(unsigned long i = 0; i < n; i++) {
    stack_push(stack, (void*)i, NULL);
  }
}

void free_stack() {
  stack_free(stack, NULL);
  stack = NULL;
}

ctdd_test(test_stack_init) {

  unsigned long n = 10;
  STACK* stack = stack_init(n);
  ctdd_check(stack);
  ctdd_check(stack->max_size == n);
  ctdd_check(stack->size == 0);
  stack_free(stack, NULL);
}

ctdd_test(test_stack_push) {
  for(unsigned long i = 0; i < n; i++) {
    ctdd_check(stack_push(stack, (void*)i, NULL));
    ctdd_check(stack->size == i+1);
  }
  ctdd_check(!stack_push(stack, (void*)0, NULL));
}

ctdd_test(test_stack_pop) {

  for(unsigned long i = 0; i < n; i++) {
    DATA* data = NULL;
    ctdd_check(data = stack_pop(stack));
    default_destructor(data);
    free(data);
  }
  ctdd_check(!stack_pop(stack));
}

ctdd_test_suite(test_stack) {
  ctdd_configure(init_stack, free_stack);
  ctdd_run_test(test_stack_init);
  ctdd_run_test(test_stack_push);
  ctdd_configure(init_stack_with_data, free_stack);
  ctdd_run_test(test_stack_pop);
}
