#include "graph.h"
#include "node.h"

#include <stdlib.h>
#include <string.h>

void graph_free(GRAPH* graph) {
  for(unsigned long i = 0; i < graph->num_nodes; i++) {
    graph->format.destructor(&graph->nodes[i]->data);
    node_free(graph->nodes[i], &graph->format);
    free(graph->nodes[i]);
  }
  free(graph->nodes);
}

void graph_init_node(GRAPH* graph, unsigned long idx) {
  NODE* node = node_init(NULL, NULL, &graph->format);
  graph->nodes[idx] = node;
  graph->format.constructor(&node->data, NULL);
  node->graph = graph;
  node->graph_idx = idx;
}

GRAPH* graph_init(GRAPH* graph, unsigned long n, DATA_FORMAT* format) {

  graph = graph ? graph : malloc(sizeof(GRAPH));
  if( format ) {
    memcpy(&graph->format, format, sizeof(DATA_FORMAT));
  } else {
    data_format_init(&graph->format);
  }
  graph->num_nodes = n;
  graph->nodes = calloc(graph->num_nodes, sizeof(NODE*));
  graph->num_edges = 0;
  for(unsigned long i = 0; i < graph->num_nodes; i++) {
    graph_init_node(graph, i);
  }
  return graph;
}

void graph_add_data(GRAPH* graph, void* args) {

  graph->nodes = realloc(graph->nodes, sizeof(NODE*) * ++graph->num_nodes);
  graph->nodes[graph->num_nodes-1] = node_init(NULL, args, &graph->format);
}
