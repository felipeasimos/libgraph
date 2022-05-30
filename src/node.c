#include "node.h"
#include "data_format.h"
#include "edge.h"
#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void node_free(NODE* node, struct DATA_FORMAT* format) {
  format->destructor(&node->data);
  for(EDGE* edge = node->out; edge; edge = node->out) {
    edge_free( edge, format );
    free( edge );
  }
  for(EDGE* edge = node->in; edge; edge = node->in) {
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

  a->out = edge_append(a->out, args, &a->graph->format);
  a->out->node = b;
  a->out->parent = a;
  a->num_out_edges++;

  b->in = edge_append(b->in, args, &b->graph->format);
  b->in->node = a;
  b->in->parent = b;
  b->num_in_edges++;
}
