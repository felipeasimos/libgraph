#include "graph.h"
#include "node.h"
#include "edge.h"

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

void graph_init_node(GRAPH* graph, unsigned long idx, void* args) {
  NODE* node = node_init(NULL, NULL, &graph->format);
  graph->nodes[idx] = node;
  graph->format.constructor(&node->data, args);
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
    graph_init_node(graph, i, NULL);
  }
  return graph;
}

NODE* graph_add_data(GRAPH* graph, void* args) {

  graph->nodes = realloc(graph->nodes, sizeof(NODE*) * ++graph->num_nodes);
  graph_init_node(graph, graph->num_nodes-1, args);
  return graph->nodes[graph->num_nodes-1];
}

struct NODE* graph_search_data(GRAPH* graph, DATA* data) {

  for(unsigned long i = 0; i < graph->num_nodes; i++) {

    NODE* node = graph->nodes[i];
    if( !graph->format.cmp(&node->data, data) ) return node;
  }
  return NULL;
}

struct NODE* graph_get(GRAPH* graph, unsigned long idx) {
  return idx < graph->num_nodes ? graph->nodes[idx] : NULL;
}

void graph_print(GRAPH* graph) {
  for(unsigned long i = 0; i < graph->num_nodes; i++) {
    node_print(graph->nodes[i], &graph->format);
    if(graph->nodes[i]->edges[OUT]) printf(" -> ");
    for(EDGE* edge = graph->nodes[i]->edges[OUT]; edge; edge = edge->next) {
      node_print(edge->node, &graph->format);
      printf(" ");
    }
    printf("\n");
  }
}

void graph_debug(GRAPH* graph) {
  for(unsigned long i = 0; i < graph->num_nodes; i++) {
    node_debug(graph->nodes[i], &graph->format);
    if(graph->nodes[i]->edges[OUT]) printf(" -> ");
    for(EDGE* edge = graph->nodes[i]->edges[OUT]; edge; edge = edge->next) {
      node_debug(edge->node, &graph->format);
      printf(" ");
    }
    printf("\n");
  }
}

int graph_oriented_connect_nodes(struct NODE* a, struct NODE* b, void* args) {
  if(a->graph != b->graph || !a->graph) return 0;
  node_connect_to(a, b, args);
  return 1;
}

int graph_connect_nodes(struct NODE* a, struct NODE* b, void* args) {
  if(a->graph != b->graph || !a->graph) return 0;
  node_connect(a, b, args);
  return 1;
}

