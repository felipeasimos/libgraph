#include "ctdd.h"
#include "node.h"

#include <stdlib.h>

ctdd_test(test_node_init) {
  NODE node = {
    .graph_idx = 1,
    .graph = (void*)0x24324,
    .data = {
      .len = 2,
      .ptr = (void*)0x43243
    },
    .in = (void*)0x2323,
    .out = (void*)0x3423,
    .num_out_edges = 3,
    .num_in_edges = 4,
    .num_info = 6
  };
  long arg = 1337;
  node_init(&node, (void*)arg, NULL);
  ctdd_check( !node.graph );
  ctdd_check( !node.graph_idx );
  ctdd_check( node.data.len == sizeof(long) );
  ctdd_check( node.data.ptr == (void*)arg );
  ctdd_check( !node.in );
  ctdd_check( !node.out );
  ctdd_check( !node.num_out_edges );
  ctdd_check( !node.num_in_edges );
  ctdd_check( !node.num_info );
}

ctdd_test_suite(test_node) {
  ctdd_run_test(test_node_init);
}
