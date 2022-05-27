#include "data_format.h"
#include "data.h"
#include <stdlib.h>
#include <stdio.h>

DATA_FORMAT* data_format_init(DATA_FORMAT* data_ptr) {
  data_ptr = data_ptr ? data_ptr : malloc(sizeof(DATA_FORMAT));
  data_ptr->constructor = default_constructor;
  data_ptr->update = default_update;
  data_ptr->destructor = default_destructor;
  data_ptr->debug = default_debug;
  data_ptr->print = default_print;
  data_ptr->cmp = default_cmp;
  return data_ptr;
}

void default_constructor(DATA* data, void* args) {

  data->len = sizeof(long);
  *(long*)&data->ptr = *(long*)&args;
}

void default_update(DATA* data, void* args) {

  data->len = sizeof(long);
  *(long*)&data->ptr = *(long*)&args;
}

void default_destructor(DATA* data) {
  data->ptr = NULL;
  data->len = 0;
}

char* default_debug(DATA* data) {
  char* debug_str = malloc(sizeof(char) * 50);
  snprintf(debug_str, 50, "[%ld](%p)", *(long*)&data->ptr, (void*)data);
  return debug_str;
}

char* default_print(DATA* data) {
  char* print_str = malloc(sizeof(char) * 15);
  sprintf(print_str, "%ld", *(long*)&data->ptr);
  return print_str;
}

int default_cmp(DATA* a, DATA* b) {
  long a_data = *(long*)&a->ptr;
  long b_data = *(long*)&b->ptr;
  if(a_data < b_data) {
    return 1;
  } else if(a_data > b_data) {
    return -1;
  }
  return 0;
}
