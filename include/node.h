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
//! @brief Free node fields properly
//! @param[in] node : node struct with fields to free
void node_free_fields(NODE* node, struct DATA_FORMAT* format);

//! @relates NODE
//! @brief Free node struct and all of its fields properly
//! @param[in] node : node struct to free
void node_free(NODE* node, struct DATA_FORMAT* format);

//! @relates NODE
//! @brief Initialize node struct, associating it with a graph
//! @param[in] node : pointer to node struct
NODE* node_init(NODE* node);

//! @relates NODE
//! @brief Disconnect from outer neighbour of \a a
//! @param[in] a : in neighbour of \a b
//! @param[in] b : in neighbour of \a a
void node_oriented_disconnect(NODE* a, NODE* b);

//! @relates NODE
//! @brief Disconnect node from all out and in neighbours
//! @param[in] node : node to isolate
void node_isolate(NODE* node);

//! @relates NODE
//! @brief Disconnect in and out connections between \a and \b
//! @param[in] a : node
//! @param[in] b : node
void node_disconnect(NODE* a, NODE* b);
 
#endif
