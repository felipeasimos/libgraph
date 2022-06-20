#ifndef LIBGRAPH_NODE_H
#define LIBGRAPH_NODE_H

#include "data/data.h"

typedef struct NODE {

  // node's data
  unsigned long num_info;
  DATA data;

  struct GRAPH* graph;
  unsigned long graph_idx;

  unsigned long num_out_edges;
  unsigned long num_in_edges;
  unsigned long num_bi_edges;
  /*
  struct EDGE* in;
  struct EDGE* out;
  struct EDGE* bi;
  struct EDGE* bi_ref;
  */
  struct EDGE* edges[4];
} NODE;

typedef struct INFO_NODE {
  unsigned long data_size;
  void* data;
  unsigned long info_size;
  void* info;
} INFO_NODE;

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

//! @relates NODE
//! @brief print node struct to stdout
//! @param[in] node : node struct to print
void node_print(NODE* node, struct DATA_FORMAT* format);

//! @relates NODE
//! @brief print node struct to stdout in debug format
//! @param[in] node : node struct to print in debug format
void node_debug(NODE* node, struct DATA_FORMAT* format);

//! @relates NODE
//! @brief connect NODE a to NODE b with a one-way edge
//! @details the data format of the graph of each node will be used to create its respective edge struct
//! @param[in] a : node to connect from
//! @param[in] b : node to connect to
//! @param[in] args : argument to pass to the edge's data constructor
void node_connect_to(NODE* a, NODE* b, void* args);

//! @relates NODE
//! @brief connect NODE a to NODE with a bidirectional edge
//! @details the data format of the graph of each node will be used to create its respective edge struct
//! @param[in] a : node to connect
//! @param[in] b : node to connect
//! @param[in] args : argument to pass to the edge's data constructor
void node_connect(NODE* a, NODE* b, void* args);

//! @relates NODE
//! @brief get data struct from node
//! @details use it to avoid info layers
//! @param[in] node : node struct
//! @returns pointer to data
DATA* node_get_data(NODE* node);

//! @relates NODE
//! @brief add info layer struct to NODE
//! @param[in] node : node struct
//! @param[in] info : info data
void node_add_info(NODE* node, void* info);

//! @relates NODE
//! @brief get info struct from node
//! @param[in] node : node struct
//! @returns NULL if there is no info struct, otherwise return pointer to info struct
INFO_NODE* node_get_info(NODE* node);

//! @relates NODE
//! @brief remove info struct from NODE
//! @param[in] node : node struct
void node_remove_info(NODE* node);

#endif
