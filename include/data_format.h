#ifndef DATA_FORMAT_H
#define DATA_FORMAT_H

#include "data.h"
#include <stdint.h>

//! @struct DATA_FORMAT
//! @brief Hold functions responsible for interactions with
//! #DATA structs.
//! @details Mind default that implementations will
//! be used for NULL function pointers.
typedef struct DATA_FORMAT {
  //! Initialize an address containing a #DATA struct.
  //! Mind that this function uses varargs, so the user
  //! has more freedom when defining a function for it.
  void (*constructor)(DATA*, ...);
  //! Update an already initialized #DATA struct.
  //! Mind that this function uses varargs, so the user
  //! has more freedom when defining a function for it.
  void (*update)(DATA*, ...);
  //! Called when a #DATA struct will be destroyed.
  //! This function must NOT deallocate the struct,
  //! as it could have been statically allocated.
  //! However, it must deallocate any dynamically
  //! allocated members at #DATA.ptr
  void (*destructor)(DATA*);
  //! Called to print a #DATA struct to stderr with
  //! debugging purpose.
  //! Althought one could just output to stdout,
  //! beware this might not print when segmentation
  //! faults happen after a call due buffering.
  void (*debug)(DATA*);
  //! Called to print a #DATA struct.
  //! Not necessarily #DATA_FORMAT.debug related, may
  //! be used to just visualize data in the final program.
  void (*print)(DATA*);
  //! Compare one #DATA struct with another.
  //! Must return 1 if \a a < \a b , 0 if \a a == \a b and -1 if \a a > \a b.
  void (*cmp)(DATA* a, DATA* b);
} DATA_FORMAT;

//! @relates DATA_FORMAT
//! Initialize a #DATA_FORMAT struct with default values.
//! @param[in] data_ptr
void data_format_init(DATA* data_ptr);
//! @relates DATA_FORMAT
//! Allocate memory for a #DATA_FORMAT struct and initialize
//! it with #data_format_init.
//! @param[out] data_format
DATA_FORMAT* data_format_create();

void default_constructor(DATA*, ...);
void default_update(DATA*, ...);
void default_destructor(DATA*);
void default_debug(DATA*);
void default_print(DATA*);

#endif
