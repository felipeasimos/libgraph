#include "node.h"
#include "data_format.h"
#include "edge.h"
#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void node_free(NODE* node, struct DATA_FORMAT* format) {
  format->destructor(&node->data);
  for(EDGE* edge = node->edges[OUT]; edge; edge = node->edges[OUT]) {
    edge_free( edge, format );
    free( edge );
  }
  for(EDGE* edge = node->edges[IN]; edge; edge = node->edges[IN]) {
    edge_free( edge, format );
    free( edge );
  }
  for(EDGE* edge = node->edges[BI]; edge; edge = node->edges[BI]) {
    edge_free( edge, format );
    free( edge );
  }
  for(EDGE* edge = node->edges[BI_REF]; edge; edge = node->edges[BI_REF]) {
    edge_free( edge, format );
    free( edge );
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

  EDGE* edge = NULL;
  a->edges[OUT] = edge_append(a->edges[OUT], OUT, args, &a->graph->format);
  edge = a->edges[OUT]->next ? a->edges[OUT]->next : a->edges[OUT];
  edge->node = b;
  edge->parent = a;
  a->num_out_edges++;

  b->edges[IN] = edge_append(b->edges[IN], IN, edge, &b->graph->format);
  edge = b->edges[IN]->next ? b->edges[IN]->next : b->edges[IN];
  edge->node = a;
  edge->parent = b;
  b->num_in_edges++;
}

void node_connect(NODE* a, NODE* b, void* args) {

  EDGE* edge = NULL;
  a->edges[BI] = edge_append(a->edges[BI], BI, args, &a->graph->format);
  edge = a->edges[BI]->next ? a->edges[BI]->next : a->edges[BI];
  edge->node = b;
  edge->parent = a;
  a->num_bi_edges++;

  b->edges[BI_REF] = edge_append(b->edges[BI_REF], BI_REF, edge, &b->graph->format);
  edge = b->edges[BI_REF]->next ? b->edges[BI_REF]->next : b->edges[BI_REF];
  edge->node = a;
  edge->parent = b;
  b->num_bi_edges++;
}
