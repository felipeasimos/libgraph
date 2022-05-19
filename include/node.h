#ifndef NODE_H
#define NODE_H

#include "data.h"

struct EDGE;
struct GRAPH;

typedef struct NODE {

  // node's data
  unsigned long num_info;
  DATA data;

  struct GRAPH* graph;
  unsigned long graph_idx;

  struct EDGE* in;
  struct EDGE* out;
  unsigned long num_out_edges;
  unsigned long num_in_edges;
} NODE;

#endif
