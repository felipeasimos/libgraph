#ifndef GRAPH_H
#define GRAPH_H

#include "data_format.h"

struct NODE;

typedef struct GRAPH {

  struct NODE* nodes; // array of nodes
  unsigned long num_edges;
  unsigned long num_nodes;
  DATA_FORMAT format;
} GRAPH;

//! Creates empty graph that accepts the given data format
GRAPH* graph_create(DATA_FORMAT* format);

#endif
