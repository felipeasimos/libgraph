#include "ctdd.h"
#include "set/set.h"
#include "data/data_format.h"

SET* set = NULL;
DATA_FORMAT format;

void init_set() {
  set = set_init(5);
  data_format_init(&format);
}

void free_set() {
  set_free(set, &format);
  set = NULL;
}

ctdd_test(test_set_init) {
  SET* set = NULL;
  set = set_init(5);
  ctdd_check( set );
  ctdd_check( set->capacity == 5 );
  ctdd_check( set->set_nodes );
  set_free(set, NULL);
}

ctdd_test_suite(test_set) {
  ctdd_run_test(test_set_init);
  ctdd_configure(init_set, free_set);
}
