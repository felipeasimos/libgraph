#include "graph.h"
#include "node.h"

#include <stdlib.h>
#include <string.h>

void graph_free_fields(GRAPH* graph) {
  for(unsigned long i = 0; i < graph->num_nodes; i++) {
    graph->format.destructor(&graph->nodes[i]->data);
    node_free(graph->nodes[i], &graph->format);
  }
  free(graph->nodes);
}

void graph_free(GRAPH* graph) {
  graph_free_fields(graph);
  free(graph);
}

void graph_init_node(GRAPH* graph, unsigned long idx) {
  NODE* node = graph->nodes[idx];
  node_init(graph->nodes[idx]);
  graph->format.constructor(&node->data, NULL);
  node->graph = graph;
  node->graph_idx = idx;
}

GRAPH* graph_init(GRAPH* graph, unsigned long n, DATA_FORMAT* format) {

  graph = graph ? graph : malloc(sizeof(GRAPH));
  memcpy(&graph->format, format, sizeof(DATA_FORMAT));
  graph->num_nodes = n;
  graph->nodes = calloc(graph->num_nodes, sizeof(NODE));
  graph->num_edges = 0;
  for(unsigned long i = 0; i < graph->num_nodes; i++) {
    graph->nodes[i] = malloc(sizeof(NODE));
    graph_init_node(graph, i);
  }
  return graph;
}
