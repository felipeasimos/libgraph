#include "edge.h"
#include "data_format.h"
#include "node.h"

#include <string.h>
#include <stdlib.h>

void edge_free(EDGE* edge, DATA_FORMAT* format) {

  if(edge->type == OUT || edge->type == BI) {
    format->destructor(&edge->data);
  }
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
    if(edge->parent->edges[edge->type] == edge) {
      edge->parent->edges[edge->type] = edge->next;
    }
  }
}

EDGE* edge_init(EDGE* edge, enum EDGE_TYPE type, void* args, struct DATA_FORMAT* format) {

  edge = edge ? edge : malloc(sizeof(EDGE));
  memset(edge, 0x00, sizeof(EDGE));
  edge->type = type;

  switch(type) {
    case BI_REF:
    case IN: {
      edge->data.ptr = args;
      break;
    };
    case BI:
    case OUT: {
      format->constructor(&edge->data, args);
      break;
    };
  }
  return edge;
}

EDGE* edge_append(EDGE* edge, enum EDGE_TYPE type, void* args, struct DATA_FORMAT* format) {
  EDGE* new_edge = edge_init(NULL, type, args, format);

  if(!edge) return new_edge;

  new_edge->next = edge->next;
  new_edge->prev = edge;
  if(edge->next) edge->next->prev = new_edge;
  edge->next = new_edge;

  return edge;
}
