#include "ctdd.h"
#include "data_format.h"

#include <stdlib.h>

ctdd_test(test_data_format_init) {
  DATA_FORMAT data;
  data_format_init(&data);
  ctdd_check( data.constructor );
  ctdd_check( data.update );
  ctdd_check( data.destructor );
  ctdd_check( data.debug );
  ctdd_check( data.print );
  ctdd_check( data.cmp );
}

ctdd_test(test_data_format_create) {
  DATA_FORMAT* data = NULL;
  data = data_format_create();
  ctdd_check( data );
  ctdd_check( data->constructor );
  ctdd_check( data->update );
  ctdd_check( data->destructor );
  ctdd_check( data->debug );
  ctdd_check( data->print );
  ctdd_check( data->cmp );
  free( data );
}

ctdd_test_suite(test_data_format) {
  ctdd_run_test(test_data_format_init);
  ctdd_run_test(test_data_format_create);
}
