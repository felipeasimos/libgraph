#ifndef EDGE_H
#define EDGE_H

#include "data.h"

typedef struct EDGE {

  struct NODE* parent;
  struct NODE* node;
  unsigned long node_idx;
  struct DATA data;
} EDGE;

//! @relates EDGE
//! @brief free edge struct fields properly
//! @param[in] edge : edge struct to free
//! @param[in] format : data format struct
void edge_free(EDGE* edge, struct DATA_FORMAT* format);

#endif
