#include "node.h"
#include "data_format.h"

#include <string.h>
#include <stdlib.h>

void node_free(NODE* node, struct DATA_FORMAT* format) {

  format->destructor(&node->data);
  free(node);
}

void node_init(NODE* node) {
  memset(node, 0x00, sizeof(NODE));
}

NODE* node_create() {
  NODE* node = malloc(sizeof(NODE));
  node_init(node);
  return node;
}
