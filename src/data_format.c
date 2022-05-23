#include "data_format.h"
#include "data.h"
#include <stdlib.h>
#include <stdio.h>

void data_format_init(DATA_FORMAT* data_ptr) {
  data_ptr->constructor = default_constructor;
  data_ptr->update = default_update;
  data_ptr->destructor = default_destructor;
  data_ptr->debug = default_debug;
  data_ptr->print = default_print;
  data_ptr->cmp = default_cmp;
}

DATA_FORMAT* data_format_create() {
  DATA_FORMAT* data_format = malloc(sizeof(DATA_FORMAT));
  data_format_init(data_format);
  return data_format;
}

void default_constructor(DATA* data, void* args) {

  if(!args) return;
  data->len = sizeof(int);
  data->ptr = malloc(data->len);
  *(int*)data->ptr = *(int*)args;
}

void default_update(DATA* data, void* args) {

  data->len = sizeof(int);
  *(int*)data->ptr = *(int*)args;
}

void default_destructor(DATA* data) {
  data->ptr = NULL;
  data->len = 0;
}

char* default_debug(DATA* data) {
  char* debug_str = malloc(sizeof(char) * 50);
  snprintf(debug_str, 50, "[%d](%p)", *(int*)data->ptr, data->ptr);
  return debug_str;
}

char* default_print(DATA* data) {
  char* print_str = malloc(sizeof(char) * 15);
  sprintf(print_str, "%d", *(int*)data->ptr);
  return print_str;
}

int default_cmp(DATA* a, DATA* b) {
  int a_data = *(int*)a->ptr;
  int b_data = *(int*)b->ptr;
  if(a_data < b_data) {
    return 1;
  } else if(a_data > b_data) {
    return -1;
  }
  return 0;
}
