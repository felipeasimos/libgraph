#ifndef LIBGRAPH_EDGE_H
#define LIBGRAPH_EDGE_H

#include "data/data.h"

//! @relates EDGE
enum EDGE_TYPE {
  //! @brief hold the main data
  IN=0,
  //! @brief hold reference to IN edge
  OUT=1,
  BI=2,
  BI_REF=3
};

typedef struct EDGE {

  enum EDGE_TYPE type;
  struct NODE* parent;
  struct EDGE* mirror;
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
EDGE* edge_init(EDGE* edge, enum EDGE_TYPE type, void* args, struct DATA_FORMAT* format);

//! @relates EDGE
//! @brief append new edge struct as 'next'
//! @details if NULL is given, a new edge struct will be created and returned, without a 'next' edge appended to it
//! @param[in] edge : pointer to edge struct
//! @param[in] args : argument for the data constructor
//! @param[in] format : data format being used
//! @return return new edge, be it one appended to an old one or not
EDGE* edge_append(EDGE* edge, enum EDGE_TYPE type, void* args, struct DATA_FORMAT* format);

#endif
