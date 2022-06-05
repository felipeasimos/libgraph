#ifndef LIBGRAPH_HASHMAP_H
#define LIBGRAPH_HASHMAP_H

#include "data/data.h"

typedef struct HASHMAP_NODE {

  struct HASHMAP_NODE* next;
  struct DATA data;
} HASHMAP_NODE;

typedef struct HASHMAP {

  HASHMAP_NODE* hashmap_nodes;
  unsigned long capacity;
} HASHMAP;

HASHMAP_NODE* hashmap_init(HASHMAP* hashmap, unsigned long capacity);

#endif
