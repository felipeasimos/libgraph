#ifndef NODE_H
#define NODE_H

#include "data.h"

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

//! @relates NODE
//! @brief Free node struct fields properly
//! @param[in] node : node struct to free
//! @param[in] format : data format struct
void node_free(NODE* node, struct DATA_FORMAT* format);

//! @relates NODE
//! @brief Initialize node struct, associating it with a graph
//! @param[in] node : pointer to node struct
//! @param[in] args : argument for the data constructor
//! @param[in] format : data format being used
NODE* node_init(NODE* node, void* args, struct DATA_FORMAT* format);

#endif
