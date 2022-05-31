#include "ctdd.h"
#include "data/data.h"
#include "data/data_format.h"
#include <stdlib.h>

ctdd_test(test_data_init) {
  DATA data;
  int user_data = 1;
    
  data_init(&data, &user_data, sizeof(int));
  ctdd_check( data.ptr == &user_data );
  ctdd_check( data.len == sizeof(int) );

  DATA* data_ptr = NULL;
  data_ptr = data_init(data_ptr, &user_data, sizeof(int));
  ctdd_check( data_ptr );
  ctdd_check( data_ptr->ptr == &user_data );
  ctdd_check( data_ptr->len == sizeof(int) );
  free(data_ptr);
}

ctdd_test(test_data_alloc) {
  int user_data = 1;
  DATA* data = NULL;
  data = data_init(NULL, &user_data, sizeof(int));
  DATA_FORMAT* format = data_format_init(NULL);
  data_alloc(data, 2, format);
  ctdd_check( data->len == 2 );
  ctdd_check( data->ptr != &user_data );
  ctdd_check( data->ptr != NULL );
  free(data->ptr);
  free(data);
  free(format);
}

ctdd_test_suite(test_data) {
  ctdd_run_test(test_data_init);
  ctdd_run_test(test_data_alloc);
}
