# Libgraph

[![Tests](https://github.com/asimos-bot/libgraph/workflows/Tests/badge.svg)](https://github.com/asimos-bot/libgraph/actions/workflows/main.yml)

Graph library for C. Features:

* General graph structure management. Using adjency lists internally.
* Convert graph to matrix representation.
* Conversion from and back `.dot` files.
* Algorithms like:
  * Topological ordering
  * Dijkstra shortest path

## API notation

* Struct initialization functions (`*_init`):
  * Must have an argument for an address where the struct can be initialized at
    * If NULL a struct will be dynamically allocated
    * return the address of the struct, no matter if it was statically or dynamically allocated
  * If struct contains a DATA struct as a field
    * There must be an argument for the data format being used for initialization
    * There must be an argument for the constructor parameter

* Struct destructor functions (`*_free`):
  * Don't deallocate struct itself
    * User must call `free(struct_ptr)` himself

* Memory layout
  * edges are stored in a linked list pointed by the node struct
  * nodes are dynamically allocated and have their pointers stored in the graph struct
