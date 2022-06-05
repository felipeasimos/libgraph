#include "hashmap/hashmap.h"
#include "data/data_format.h"

#include <stdlib.h>
#include <string.h>

HASHMAP* hashmap_init(unsigned long capacity) {
  HASHMAP* hashmap = malloc( sizeof(HASHMAP) + capacity * sizeof(HASHMAP_NODE*));
  hashmap->capacity = capacity;
  memset(hashmap->hashmap_nodes, 0x00, sizeof(HASHMAP_NODE*) * hashmap->capacity);
  return hashmap;
}

void hashmap_free(HASHMAP* hashmap, struct DATA_FORMAT* format) {
  for(unsigned long i = 0; i < hashmap->capacity; i++) {
      HASHMAP_NODE* next = NULL;
      for(HASHMAP_NODE* node = hashmap->hashmap_nodes[i]; node; node = next) {
        next = node->next;    
        format->destructor(&node->data);
        free(node);
      }
  }
  free(hashmap);
}
