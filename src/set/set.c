#include "set/set.h"
#include "data/data_format.h"

#include <stdlib.h>
#include <string.h>

SET* set_init(unsigned long capacity) {
  SET* set = malloc( sizeof(SET) + capacity * sizeof(SET_NODE*));
  set->capacity = capacity;
  memset(set->set_nodes, 0x00, sizeof(SET_NODE*) * set->capacity);
  return set;
}

void set_free(SET* set, struct DATA_FORMAT* format) {
  for(unsigned long i = 0; i < set->capacity; i++) {
      SET_NODE* next = NULL;
      for(SET_NODE* node = set->set_nodes[i]; node; node = next) {
        next = node->next;    
        format->destructor(&node->data);
        free(node);
      }
  }
  free(set);
}

int set_contains(SET* set, struct DATA* data, struct DATA_FORMAT* format) {
  unsigned long key = format->key(data);
  unsigned long idx = key % set->capacity;
  for(SET_NODE* node = set->set_nodes[idx]; node; node = node->next) {
    if( key == format->key(&node->data) ) {
      return 1;
    }
  }
  return 0;
}

void set_set(SET* set, DATA* data, struct DATA_FORMAT* format) {
  unsigned long key = format->key(data);
  unsigned long idx = format->key(data) % set->capacity;
  SET_NODE* node = set->set_nodes[idx];
  // no node list at this idx
  if(!node) {
    set->set_nodes[idx] = malloc(sizeof(SET));
    memset(set->set_nodes[idx], 0x00, sizeof(SET_NODE));
    memcpy(&set->set_nodes[idx]->data, data, sizeof(DATA));
    return;
  }
  // look for node with same key
  for(; node; node = node->next ) {
    if( format->key(&node->data) == key ) {
      memcpy(&node->data, data, sizeof(DATA));
      return;
    }
  }
  // create new node
  if(!node) {
    node = malloc(sizeof(SET));
    node->prev = NULL;
    node->next = set->set_nodes[idx];
    set->set_nodes[idx]->prev = node;
    memcpy(&set->set_nodes[idx]->data, data, sizeof(DATA));
  }
}

int set_remove(SET* set, DATA* data, struct DATA_FORMAT* format) {

  unsigned long key = format->key(data);
  unsigned long idx = key % set->capacity;
  for(SET_NODE* node = set->set_nodes[idx]; node; node = node->next) {
    if( key == format->key(&node->data) ) {

      if( node->next ) {
        node->next->prev = node->prev;
      }
      if( node->prev ) {
        node->prev->next = node->next;
      }
      format->destructor(&node->data);
      free(node);
      return 1;
    }
  }
  return 0; 
}
