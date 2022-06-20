#ifndef LIBGRAPH_STACK_H
#define LIBGRAPH_STACK_H

#include "data/data.h"

typedef struct STACK {

  unsigned long max_size;
  unsigned long size;
  DATA stack[];
} STACK;

//! @relates STACK
//! @brief creates stack with given maximum capacity
//! @param[in] max_size : max number of data structs in #STACK.stack field
//! @return pointer to allocated stack struct
STACK* stack_init(unsigned long max_size);

//! @relates STACK
//! @brief free stack struct properly
//! @param[in] stack : pointer to graph struct
//! @param[in] format : data format
void stack_free(STACK* stack, struct DATA_FORMAT* format);

//! @relates STACK
//! @brief push new data to top of stack
//! @param[in] stack : stack struct
//! @param[in] args : argument for constructor
//! @param[in] format : data format being used
//! @return 1 on success (enough space), otherwise 0
int stack_push(STACK* stack, void* args, struct DATA_FORMAT* format);

//! @relates STACK
//! @brief get data on top of stack
//! @details returns NULL if stack is empty
//! @param[in] stack : stack struct
//! @returns pointer to data on top of stack
DATA* stack_peek(STACK* stack);

//! @relates STACK
//! @brief pop data from the top of stack
//! @param[in] stack : stack struct
//! @return dynamically allocated copy of the data at the top of the stack. return NULL if #STACK.size == 0
DATA* stack_pop(STACK* stack);

#endif
