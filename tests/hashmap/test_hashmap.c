#include "ctdd.h"
#include "hashmap/hashmap.h"

ctdd_test(test_hashmap_init) {
  HASHMAP* hashmap = NULL;
  hashmap = hashmap_init(5);
  ctdd_check( hashmap );
  ctdd_check( hashmap->capacity == 5 );
  ctdd_check( hashmap->hashmap_nodes );
  hashmap_free(hashmap, NULL);
}

ctdd_test_suite(test_hashmap) {
  ctdd_run_test(test_hashmap_init);
}
