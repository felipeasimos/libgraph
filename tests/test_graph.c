#include "ctdd.h"
#include "graph.h"
#include "data_format.h"
#include "node.h"

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
  graph_free(&graph);

  GRAPH* graph_ptr = NULL;
  graph_ptr = graph_init(NULL, n, &data_format);
  ctdd_check( graph_ptr );
  ctdd_check(graph_ptr->num_nodes == n);
  ctdd_check(graph_ptr->num_edges == 0);
  ctdd_check(graph_ptr->nodes != NULL);
  ctdd_check(graph_ptr->format.cmp == data_format.cmp);
  ctdd_check(graph_ptr->format.constructor == data_format.constructor);
  ctdd_check(graph_ptr->format.debug == data_format.debug);
  ctdd_check(graph_ptr->format.destructor == data_format.destructor);
  ctdd_check(graph_ptr->format.print == data_format.print);
  ctdd_check(graph_ptr->format.update == data_format.update);
  graph_free(graph_ptr);
  free( graph_ptr );
}

ctdd_test(test_graph_add_data) {

  GRAPH* graph = graph_init(NULL, 4, NULL);
  int i = 1337;
  graph_add_data(graph, &i);
  ctdd_check( graph->num_nodes == 5 );
  ctdd_check( *(int*)&graph->nodes[graph->num_nodes-1]->data.ptr == 1337 );
  graph_free(graph);
  free(graph);
}

ctdd_test_suite(test_graph) {
  ctdd_run_test(test_graph_init);
  ctdd_run_test(test_graph_add_data);
}
