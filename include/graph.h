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
//! @brief Free graph structure and all its fields properly
//! @param[in] graph : graph struct to free
void graph_free(GRAPH* graph);

//! @relates GRAPH
//! @brief Initialize graph struct with n nodes that accepts the given data format.
//! @details Data constructors will be given the argument NULL
//! @param[in] graph : pointer to graph struct
//! @param[in] n : number of nodes in graph. Initially disconnected from one another
//! @param[in] format : data format used by the graph. The struct this points to will be copied
GRAPH* graph_init(GRAPH* graph, unsigned long n, DATA_FORMAT* format);

//! @relates GRAPH
//! @brief Add new node to graph using constructor arguments
//! @param[in] graph : pointer to graph struct
//! @param[in] args : argument to construct new data
//! @return pointer to new node struct
struct NODE* graph_add_data(GRAPH* graph, void* args);

//! @relates GRAPH
//! @brief Return struct where node.data == data
//! @details Will return NULL in case no node is found.
//! Match where format->cmp(data, node.data) == 0 will be returned
//! @param[in] graph : graph struct
//! @param[in] data : data to compare against
struct NODE* graph_search_data(GRAPH* graph, DATA* data);

void graph_print(GRAPH* graph);
void graph_debug(GRAPH* graph);
char* graph_to_dot_str(GRAPH* graph);
int graph_to_dot_file(GRAPH* graph, FILE* file);
GRAPH* graph_from_dot_str(GRAPH* graph, char* dot_str);
GRAPH* graph_from_dot_file(GRAPH* graph, FILE* file);

#endif
