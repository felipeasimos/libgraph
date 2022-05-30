#include "ctdd.h"
#include "graph.h"
#include "data_format.h"
#include "node.h"
#include "edge.h"

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
  long i = 1337;
  NODE* node = graph_add_data(graph, (void*)i);
  ctdd_check( graph->num_nodes == 5 );
  ctdd_check( graph->nodes[4] == node );
  ctdd_check( node->graph_idx == 4);
  ctdd_check( graph->nodes[graph->num_nodes-1]->data.ptr == (void*)i );

  graph_free(graph);
  free(graph);
}

ctdd_test(test_graph_search_data) {
  GRAPH* graph = graph_init(NULL, 0, NULL);
  int max = 5 + rand() % 20;
  long i = 0;
  for(; i < max; i++ ) {
    graph_add_data(graph, (void*)i);
    ctdd_check( graph->nodes[graph->num_nodes-1]->graph_idx == (unsigned long)i);
    ctdd_check( graph->nodes[graph->num_nodes-1]->data.ptr == (void*)i);
    ctdd_check( graph->nodes[graph->num_nodes-1]->data.len == sizeof(long) );
  }
  ctdd_check( graph->num_nodes == (unsigned long)max );
  DATA data;
  graph->format.constructor(&data, (void*)i);
  ctdd_check( data.ptr == (void*)i);
  ctdd_check( !graph_search_data(graph, &data) );
  for(i = 0; i < max; i++) {
    graph->format.update(&data, (void*)i);
    ctdd_check( data.ptr == (void*)i );
    NODE* result = graph_search_data(graph, &data);
    ctdd_check( result );
    ctdd_check( result->graph_idx == (unsigned long)i);
    ctdd_check( result->data.len == sizeof(long) );
    ctdd_check( result->data.ptr == data.ptr );
    ctdd_check( graph->nodes[result->graph_idx] == result);
  }
  graph_free(graph);
  free(graph);
}

ctdd_test(test_graph_get) {
  GRAPH* graph = graph_init(NULL, 0, NULL);
  int max = 5 + rand() % 20;
  long i;
  for(i = 0; i < max; i++) {
    graph_add_data(graph, (void*)i);
  }
  for(i = 0; i < max; i++) {
    ctdd_check( graph_get(graph, i) == graph->nodes[i]);
  }
  for(; i < max<<1; i++) {
    ctdd_check(!graph_get(graph, i));
  }
  graph_free(graph);
  free( graph ); 
}

ctdd_test(test_graph_oriented_connect_nodes) {
  GRAPH* graph = graph_init(NULL, 0, NULL);
  int max = 5 + rand() % 20;
  long i;
  for( i = 0; i < max; i++ ) {
    graph_add_data(graph, (void*)i);
  }
  ctdd_check( graph_oriented_connect_nodes(
      graph_get(graph, 0),
      graph_get(graph, 1),
      (void*)2) );
  ctdd_check( graph_oriented_connect_nodes(
      graph_get(graph, 2),
      graph_get(graph, 4),
      (void*)5) );
  ctdd_check( graph_get(graph, 0)->edges[OUT]->node == graph_get(graph, 1));
  ctdd_check( graph_get(graph, 1)->edges[IN]->node == graph_get(graph, 0));
  ctdd_check( graph_get(graph, 0)->num_out_edges == 1 );
  ctdd_check( graph_get(graph, 0)->num_in_edges == 0 );
  ctdd_check( graph_get(graph, 1)->num_in_edges == 1 );
  ctdd_check( graph_get(graph, 1)->num_out_edges == 0 );
  ctdd_check( graph->nodes[0]->edges[OUT]->data.ptr == (void*)2);
  ctdd_check( graph->nodes[1]->edges[IN]->data.ptr == graph_get(graph, 0)->edges[OUT]);

  ctdd_check( graph_get(graph, 2)->edges[OUT]->node == graph_get(graph, 4));
  ctdd_check( graph_get(graph, 4)->edges[IN]->node == graph_get(graph, 2));
  ctdd_check( graph_get(graph, 2)->num_out_edges == 1 );
  ctdd_check( graph_get(graph, 2)->num_in_edges == 0 );
  ctdd_check( graph_get(graph, 4)->num_in_edges == 1 );
  ctdd_check( graph_get(graph, 4)->num_out_edges == 0 );
  ctdd_check( graph->nodes[2]->edges[OUT]->data.ptr == (void*)5);

  graph_free( graph );
  free( graph );
}

ctdd_test(test_graph_connect_nodes) {
  GRAPH* graph = graph_init(NULL, 0, NULL);
  int max = 5 + rand() % 20;
  long i;
  for( i = 0; i < max; i++ ) {
    graph_add_data(graph, (void*)i);
  }
  ctdd_check( graph_connect_nodes(
      graph_get(graph, 0),
      graph_get(graph, 1),
      (void*)2) );
  ctdd_check( graph_connect_nodes(
      graph_get(graph, 2),
      graph_get(graph, 4),
      (void*)5) );
  ctdd_check( graph_get(graph, 0)->edges[BI]->node == graph_get(graph, 1));
  ctdd_check( graph_get(graph, 1)->edges[BI_REF]->data.ptr == graph_get(graph, 0)->edges[BI]);
  ctdd_check( graph_get(graph, 0)->num_bi_edges == 1 );
  ctdd_check( graph_get(graph, 1)->num_bi_edges == 1 );
  ctdd_check( graph->nodes[0]->edges[BI]->data.ptr == (void*)2);

  ctdd_check( graph_get(graph, 2)->edges[BI]->node == graph_get(graph, 4));
  ctdd_check( graph_get(graph, 4)->edges[BI_REF]->data.ptr == graph_get(graph, 2)->edges[BI]);
  ctdd_check( graph_get(graph, 2)->num_bi_edges == 1 );
  ctdd_check( graph_get(graph, 2)->num_bi_edges == 1 );
  ctdd_check( graph->nodes[2]->edges[BI]->data.ptr == (void*)5);

  graph_free( graph );
  free( graph );
}

ctdd_test_suite(test_graph) {
  ctdd_run_test(test_graph_init);
  ctdd_run_test(test_graph_add_data);
  ctdd_run_test(test_graph_search_data);
  ctdd_run_test(test_graph_get);
  ctdd_run_test(test_graph_oriented_connect_nodes);
  ctdd_run_test(test_graph_connect_nodes);
}
