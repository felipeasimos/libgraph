#include "data/data.h"
#include "data/data_format.h"
#include <stdlib.h>

DATA* data_init(DATA* data, void* ptr, unsigned long len) {
  data = data ? data : malloc(sizeof(DATA));
  data->ptr = ptr;
  data->len = len;
  return data;
}

void data_alloc(DATA* data, unsigned long new_len, DATA_FORMAT* format) {
  if(data->len == new_len) return;
  if(data->ptr != NULL) format->destructor(data);
  data->len = new_len;
  data->ptr = malloc(data->len);
}
