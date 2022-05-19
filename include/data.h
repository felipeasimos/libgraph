#ifndef DATA_H
#define DATA_H

//! Points to user data.
//! Instead of directly handling user data, other data
//! structures in this library let #DATA handle it.
typedef struct DATA {

  //! Number of bytes this piece of user data occupies
  //! at the address pointed by #DATA.ptr
  unsigned long len;
  //! Points to memory space with user data
  void* ptr;
} DATA;

#endif
