#include "graph.h"

int main() {

  GRAPH* graph = graph_init(NULL, 0, NULL);
  long i;
  long n = 10;
  for(i = 0; i < n; i++) {
    graph_add_data(graph, (void*)i);
  }
  graph_print(graph);
  return 0;
}
