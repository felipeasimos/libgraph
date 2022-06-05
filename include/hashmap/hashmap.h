#ifndef LIBGRAPH_HASHMAP_H
#define LIBGRAPH_HASHMAP_H

#include "data/data.h"

typedef struct HASHMAP_NODE {

  struct HASHMAP_NODE* next;
  struct DATA data;
} HASHMAP_NODE;

typedef struct HASHMAP {

  unsigned long capacity;
  HASHMAP_NODE* hashmap_nodes[];
} HASHMAP;

HASHMAP* hashmap_init(unsigned long capacity);

void hashmap_free(HASHMAP* hashmap, struct DATA_FORMAT* format);

#endif
