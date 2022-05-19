#ifndef EDGE_H
#define EDGE_H

struct NODE;

typedef struct EDGE {

  struct NODE* parent;
  struct NODE* node;
  struct EDGE* next;
  struct EDGE* prev;
} EDGE;

#endif
