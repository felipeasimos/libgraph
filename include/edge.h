#ifndef EDGE_H
#define EDGE_H

#include "data.h"

struct NODE;

typedef struct EDGE {

  struct NODE* parent;
  struct NODE* node;
  struct EDGE* next;
  struct EDGE* prev;
  struct DATA data;
} EDGE;

#endif
