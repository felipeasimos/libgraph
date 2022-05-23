#include "data.h"
#include "data_format.h"
#include <stdlib.h>

void data_init(DATA* data, void* ptr, unsigned long len) {
  data->ptr = ptr;
  data->len = len;
  data->container = NULL;
}

DATA* data_create(void* ptr, unsigned long len) {

  DATA* data = malloc(sizeof(DATA));
  data_init(data, ptr, len);
  return data;
}

void data_alloc(DATA* data, unsigned long new_len, DATA_FORMAT* format) {
  if(data->len == new_len) return;
  if(data->ptr != NULL) format->destructor(data);
  data->len = new_len;
  data->ptr = malloc(data->len);
}
