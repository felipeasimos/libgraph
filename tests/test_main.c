#include "ctdd.h"
#include <time.h>
#include <stdlib.h>

int main(void) {

  srand(time(NULL));
  ctdd_run_suite(test_data_format);
  ctdd_run_suite(test_data);
  ctdd_run_suite(test_stack);
  ctdd_run_suite(test_set);
  ctdd_run_suite(test_node);
  ctdd_run_suite(test_graph);
  ctdd_run_suite(test_dot_parser);
}
