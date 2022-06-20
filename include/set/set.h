#ifndef LIBGRAPH_SET_H
#define LIBGRAPH_SET_H

#include "data/data.h"

typedef struct SET_NODE {

  struct SET_NODE* next;
  struct SET_NODE* prev;
  struct DATA data;
} SET_NODE;

typedef struct SET {

  unsigned long capacity;
  SET_NODE* set_nodes[];
} SET;

SET* set_init(unsigned long capacity);

void set_free(SET* set, struct DATA_FORMAT* format);

int set_contains(SET* set, DATA* data, struct DATA_FORMAT* format);

void set_set(SET* set, DATA* data, struct DATA_FORMAT* format);

int set_remove(SET* set, DATA* data, struct DATA_FORMAT* format);

#endif
