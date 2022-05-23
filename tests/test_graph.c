#include "ctdd.h"
#include "graph.h"
#include "data_format.h"

#include <stdlib.h>

ctdd_test(test_graph_init) {
  GRAPH graph;
  DATA_FORMAT data_format;
  data_format_init(&data_format);
  unsigned long n = rand() % 20;
  graph_init(&graph, n, &data_format);
  ctdd_check(graph.num_nodes == n);
  ctdd_check(graph.num_edges == 0);
  ctdd_check(graph.nodes != NULL);
  ctdd_check(graph.format.cmp == data_format.cmp);
  ctdd_check(graph.format.constructor == data_format.constructor);
  ctdd_check(graph.format.debug == data_format.debug);
  ctdd_check(graph.format.destructor == data_format.destructor);
  ctdd_check(graph.format.print == data_format.print);
  ctdd_check(graph.format.update == data_format.update);
  graph_free_fields(&graph);
}

ctdd_test(test_graph_create) {
  unsigned long n = rand() % 20;
  DATA_FORMAT data_format;
  data_format_init(&data_format);
  GRAPH* graph = graph_create(n, &data_format);
  ctdd_check( graph );
  graph_free( graph );
}

ctdd_test_suite(test_graph) {
  ctdd_run_test(test_graph_init);
  ctdd_run_test(test_graph_create);
}
