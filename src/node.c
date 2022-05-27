#include "node.h"
#include "data_format.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void node_free(NODE* node, struct DATA_FORMAT* format) {
  format->destructor(&node->data);
}

NODE* node_init(NODE* node, void* args, struct DATA_FORMAT* format) {
  node = node ? node : malloc(sizeof(NODE));
  memset(node, 0x00, sizeof(NODE));
  if(format) {
    format->constructor(&node->data, args);
  } else {
    default_constructor(&node->data, args);
  }

  return node;
}

void node_print(NODE* node, struct DATA_FORMAT* format) {

  char* print_str = format->print(&node->data);
  printf("%s", print_str);
  free(print_str);
}
