#ifndef LIBGRAPH_DATA_H
#define LIBGRAPH_DATA_H

struct DATA_FORMAT;
//! @brief Points to user data.
//! @details Instead of directly handling user data, other data
//! structures in this library let #DATA handle it.
typedef struct DATA {

  //! @brief Number of bytes this piece of user data occupies
  //! at the address pointed by #DATA.ptr.
  unsigned long len;
  //! @brief Points to memory space with user data.
  void* ptr;
  //! @brief May point to struct containing this struct
  void* container;
} DATA;

//! @relates DATA
//! @brief Initializes data struct. If needed, it will allocate memory for one
//! @param[in] data : data struct to initialize. If NULL is given, it will allocate one
//! @param[in] ptr : Pointer to user data
//! @param[in] len : Size of user data in bytes
//! @return pointer to data struct
DATA* data_init(DATA* data, void* ptr, unsigned long len);

//! @relates DATA
//! @brief Allocate new memory space.
//! @details This functions makes sure to call the destructor inside #DATA_FORMAT
//! if #DATA.ptr isn't NULL in order to avoid memory leaks.
//! @param[in] data : Pointer to #DATA struct.
//! @param[in] new_len : Size of memory space to be allocated.
//! @param[in] format : #DATA_FORMAT struct, which contains the destructor's function pointer.
void data_alloc(DATA* data, unsigned long new_len, struct DATA_FORMAT* format);

#endif
