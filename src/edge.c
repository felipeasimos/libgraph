#include "edge.h"
#include "data_format.h"
#include "node.h"

#include <string.h>
#include <stdlib.h>

void edge_free(EDGE* edge, DATA_FORMAT* format) {

  format->destructor(&edge->data);
  // connect next edge back
  if(edge->next) {
    edge->next->prev = edge->prev;
  }
  // connect previous edge forward
  if(edge->prev) {
    edge->prev->next = edge->next;
  }
  // connect next as root edge if this is the root
  if(edge->parent) {
    if(edge->parent->out == edge) {
      edge->parent->out = edge->next;
    }
    if(edge->parent->in == edge) {
      edge->parent->in = edge->next;
    }
  }
}

EDGE* edge_init(EDGE* edge, void* args, struct DATA_FORMAT* format) {

  edge = edge ? edge : malloc(sizeof(EDGE));
  memset(edge, 0x00, sizeof(EDGE));
  format->constructor(&edge->data, args);
  return edge;
}

EDGE* edge_append(EDGE* edge, void* args, struct DATA_FORMAT* format) {
  EDGE* new_edge = edge_init(NULL, args, format);

  if(!edge) return new_edge;

  new_edge->next = edge->next;
  if(edge->next) edge->next->prev = new_edge;
  return edge;
}
