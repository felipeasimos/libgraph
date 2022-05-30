#ifndef EDGE_H
#define EDGE_H

#include "data.h"

typedef struct EDGE {

  struct NODE* parent;
  struct NODE* node;
  struct EDGE* prev;
  struct EDGE* next;
  struct DATA data;
} EDGE;

//! @relates EDGE
//! @brief free edge struct fields properly
//! @param[in] edge : edge struct to free
//! @param[in] format : data format struct
void edge_free(EDGE* edge, struct DATA_FORMAT* format);

//! @relates EDGE
//! @brief Initialize edge struct with parent node and reference node
//! @param[in] edge : pointer to edge struct
//! @param[in] args : argument for the data constructor
//! @param[in] format : data format being used
EDGE* edge_init(EDGE* edge, void* args, struct DATA_FORMAT* format);

//! @relates EDGE
//! @brief append new edge struct as 'next'
//! @details if NULL is given, a new edge struct will be created and returned, without a 'next' edge appended to it
//! @param[in] edge : pointer to edge struct
//! @param[in] args : argument for the data constructor
//! @param[in] format : data format being used
//! @return return new edge, be it one appended to an old one or not
EDGE* edge_append(EDGE* edge, void* args, struct DATA_FORMAT* format);

#endif
