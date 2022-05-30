#ifndef GRAPH_H
#define GRAPH_H

#include "data_format.h"
#include "edge.h"

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

//! @relates GRAPH
//! @brief Returns node at index
//! @details Returns NULL if there is no node at this idx
//! @param[in] graph : graph struct
//! @param[in] idx : index to return node from
struct NODE* graph_get(GRAPH* graph, unsigned long idx);

//! @relates GRAPH
//! @brief print graph struct to stdout
//! @param[in] graph : graph struct to print
void graph_print(GRAPH* graph);

//! @relates GRAPH
//! @brief print graph struct in debug form
//! @param[in] graph : graph struct to debug
void graph_debug(GRAPH* graph);

//! @relates GRAPH
//! @brief create a new one-way edge connecting \a a to \a b
//! @details fails if the nodes aren't in the same graph
//! @param[in] a : node to connect from
//! @param[in] b : node to connect to
//! @param[in] args : argument to construct edge data
//! @return return 1 if connection is successful. Return 0 otherwise
int graph_oriented_connect_nodes(struct NODE* a, struct NODE* b, void* args);

//! @relates GRAPH
//! @brief create a new bidirectional edge connecting \a a to \a b
//! @details fails if the nodes aren't in the same graph
//! @param[in] a : node to connect
//! @param[in] b : node to connect
//! @param[in] args : argument to construct edge data
//! @return return 1 if connection is successful. Return 0 otherwise
int graph_connect_nodes(struct NODE* a, struct NODE* b, void* args);

//! @relates GRAPH
//! @brief search for a connection of the given type from a to b
//! @param[in] a : node to connect
//! @param[in] b : node to connect
//! @param[in] type : connection type
//! @return return a edge struct with this connection type
//! (conforming to the order of arguments if oriented) and 
EDGE* graph_get_one_edge(struct NODE* a, struct NODE* b, enum EDGE_TYPE type);

char* graph_to_dot_str(GRAPH* graph);
int graph_to_dot_file(GRAPH* graph, FILE* file);
GRAPH* graph_from_dot_str(GRAPH* graph, char* dot_str);
GRAPH* graph_from_dot_file(GRAPH* graph, FILE* file);

#endif
