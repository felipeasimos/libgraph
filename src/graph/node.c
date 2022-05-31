#include "graph/node.h"
#include "data/data_format.h"
#include "graph/edge.h"
#include "graph/graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void node_free(NODE* node, struct DATA_FORMAT* format) {
  format->destructor(&node->data);
  // since there are 4 types of edges
  for(int i = 0; i < 4; i++) {
    while(node->edges[i]) edge_free(node->edges[i], format);
  }
}

NODE* node_init(NODE* node, void* args, struct DATA_FORMAT* format) {
  node = node ? node : malloc(sizeof(NODE));
  memset(node, 0x00, sizeof(NODE));
  if(format) {
    format->constructor(&node->data, args);
  } else {
    default_constructor(&node->data, args);
  }

  return node;
}

void node_print(NODE* node, struct DATA_FORMAT* format) {

  char* print_str = format->print(&node->data);
  printf("%s", print_str); free(print_str); }

void node_debug(NODE* node, struct DATA_FORMAT* format) {

  char* debug_str = format->debug(&node->data);
  printf("%s", debug_str);
  free(debug_str);
}

void node_connect_to(NODE* a, NODE* b, void* args) {

  EDGE* a_edge = NULL;
  a->edges[OUT] = edge_append(a->edges[OUT], OUT, args, &a->graph->format);
  a_edge = a->edges[OUT]->next ? a->edges[OUT]->next : a->edges[OUT];
  a_edge->parent = a;
  a->num_out_edges++;

  EDGE* b_edge = NULL;
  b->edges[IN] = edge_append(b->edges[IN], IN, NULL, &b->graph->format);
  b_edge = b->edges[IN]->next ? b->edges[IN]->next : b->edges[IN];
  b_edge->parent = b;
  b->num_in_edges++;

  b_edge->mirror = a_edge;
  a_edge->mirror = b_edge;
}

void node_connect(NODE* a, NODE* b, void* args) {

  EDGE* a_edge = NULL;
  a->edges[BI] = edge_append(a->edges[BI], BI, args, &a->graph->format);
  a_edge = a->edges[BI]->next ? a->edges[BI]->next : a->edges[BI];
  a_edge->parent = a;
  a->num_bi_edges++;

  EDGE* b_edge = NULL;
  b->edges[BI_REF] = edge_append(b->edges[BI_REF], BI_REF, NULL, &b->graph->format);
  b_edge = b->edges[BI_REF]->next ? b->edges[BI_REF]->next : b->edges[BI_REF];
  b_edge->parent = b;
  b->num_bi_edges++;

  b_edge->mirror = a_edge;
  a_edge->mirror = b_edge;
}
