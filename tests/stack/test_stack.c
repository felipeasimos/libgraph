#include "ctdd.h"
#include "stack/stack.h"
#include "data/data_format.h"

#include <stdlib.h>

ctdd_test(test_stack_init) {

  unsigned long n = 10;
  STACK* stack = stack_init(n);
  ctdd_check(stack);
  ctdd_check(stack->max_size == n);
  ctdd_check(stack->size == 0);
  stack_free(stack, NULL);
}

ctdd_test(test_stack_push) {

  unsigned long n = 10;
  STACK* stack = NULL;
  stack = stack_init(n);

  for(unsigned long i = 0; i < n; i++) {
    ctdd_check(stack_push(stack, (void*)i, NULL));
    ctdd_check(stack->size == i+1);
  }
  ctdd_check(!stack_push(stack, (void*)0, NULL));
  stack_free(stack, NULL);
}

ctdd_test(test_stack_pop) {

  unsigned long n = 10;
  STACK* stack = NULL;
  stack = stack_init(n);
  ctdd_check(stack);
  for(unsigned long i = 0; i < n; i++) {
    ctdd_check(stack_push(stack, (void*)i, NULL));
  }
  ctdd_check(!stack_push(stack, (void*)0, NULL));
  for(unsigned long i = 0; i < n; i++) {
    DATA* data = NULL;
    ctdd_check(data = stack_pop(stack));
    default_destructor(data);
    free(data);
  }
  ctdd_check(!stack_pop(stack));
  stack_free(stack, NULL);
}

ctdd_test_suite(test_stack) {
  ctdd_run_test(test_stack_init);
  ctdd_run_test(test_stack_push);
  ctdd_run_test(test_stack_pop);
}
