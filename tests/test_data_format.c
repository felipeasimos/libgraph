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

  DATA_FORMAT* data_ptr = NULL;
  data_ptr = data_format_init(data_ptr);
  ctdd_check( data_ptr );
  ctdd_check( data_ptr->constructor );
  ctdd_check( data_ptr->update );
  ctdd_check( data_ptr->destructor );
  ctdd_check( data_ptr->debug );
  ctdd_check( data_ptr->print );
  ctdd_check( data_ptr->cmp );
  ctdd_check( data_ptr );
  free( data_ptr );
}

ctdd_test_suite(test_data_format) {
  ctdd_run_test(test_data_format_init);
}
