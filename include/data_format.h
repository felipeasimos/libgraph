#ifndef DATA_FORMAT_H
#define DATA_FORMAT_H

#include "data.h"

//! @brief Hold functions responsible for interactions with
//! #DATA structs.
//! @details Mind that default implementations will
//! be used for NULL function pointers. These default implementations
//! use the data pointer as an long integer (as it being the data itself) \a long.
typedef struct DATA_FORMAT {
  //! @brief Initialize an address containing space for a #DATA struct.
  //! @details Mind that this function uses \a void* so the user
  //! has more freedom when defining a function for it.
  void (*constructor)(DATA*, void*);
  //! @brief Update an already initialized #DATA struct.
  //! @details Mind that this function uses \a void*, so the user
  //! has more freedom when defining a function for it.
  void (*update)(DATA*, void*);
  //! @brief Called when a #DATA struct will be destroyed.
  //! @details This function must NOT deallocate the struct,
  //! as it could have been statically allocated.
  //! However, it must deallocate any dynamically
  //! allocated members at #DATA.ptr
  void (*destructor)(DATA*);
  //! @brief Called to return a debugging string that will
  //! be send to stderr and deallocated.
  char* (*debug)(DATA*);
  //! @brief Called to return a string to print user data.
  char* (*print)(DATA*);
  //! @brief Compare one #DATA struct with another.
  //! @details Must return 1 if \a a < \a b , 0 if \a a == \a b and -1 if \a a > \a b.
  int (*cmp)(DATA* a, DATA* b);
} DATA_FORMAT;

//! @relates DATA_FORMAT
//! @brief Initialize a #DATA_FORMAT struct with default values.
//! @param[in] data_format_ptr : Pointer to uninitialized #DATA_FORMAT struct.
DATA_FORMAT* data_format_init(DATA_FORMAT* data_format_ptr);

void default_constructor(DATA* data, void* args);
void default_update(DATA* data, void* args);
void default_destructor(DATA* data);
char* default_debug(DATA* data);
char* default_print(DATA* data);
int default_cmp(DATA* a, DATA* b);

#endif
