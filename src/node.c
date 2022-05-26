#include "node.h"
#include "data_format.h"

#include <string.h>
#include <stdlib.h>

void node_free(NODE* node, struct DATA_FORMAT* format) {

  format->destructor(&node->data);
  free(node);
}

NODE* node_init(NODE* node) {
  node = node ? node : malloc(sizeof(NODE));
  memset(node, 0x00, sizeof(NODE));
  return node;
}
