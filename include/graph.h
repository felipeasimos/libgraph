#ifndef GRAPH_H
#define GRAPH_H

#include "data_format.h"

#include <stdio.h>

typedef struct GRAPH {

  struct NODE** nodes; // array of nodes
  unsigned long num_edges;
  unsigned long num_nodes;
  DATA_FORMAT format;
} GRAPH;

//! @relates GRAPH
//! @brief Free graph fields properly
//! @param[in] graph : graph struct with fields to free
void graph_free_fields(GRAPH* graph);

//! @relates GRAPH
//! @brief Free graph structure and all its fields properly
//! @param[in] graph : graph struct to free
void graph_free(GRAPH* graph);

//! @relates GRAPH
//! @brief Initialize graph struct with n nodes that accepts the given data format.
//! @details Data constructors will be given the argument NULL
//! @param[in] graph : pointer to graph struct
//! @param[in] n : number of nodes in graph. Initially disconnected from one another
//! @param[in] format : data format used by the graph. The struct this points to will be copied
void graph_init(GRAPH* graph, unsigned long n, DATA_FORMAT* format);

//! @relates GRAPH
//! @brief Create and initialize graph struct with n nodes that accepts the given data format.
//! @details Data constructors will be given the argument NULL
//! @param[in] n : number of nodes in graph. Initially disconnected from one another
//! @param[in] format : data format used by the graph. The struct this points to will be copied
//! @return pointer to new graph struct
GRAPH* graph_create(unsigned long n, DATA_FORMAT* format);

#endif
