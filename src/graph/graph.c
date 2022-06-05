#include "graph/graph.h"
#include "graph/node.h"
#include "graph/edge.h"

#include <stdlib.h>
#include <string.h>

void graph_free(GRAPH* graph) {
  for(unsigned long i = 0; i < graph->num_nodes; i++) {
    graph->format.destructor(&graph->nodes[i]->data);
    node_free(graph->nodes[i], &graph->format);
    free(graph->nodes[i]);
  }
  free(graph->nodes);
}

void graph_init_node(GRAPH* graph, unsigned long idx, void* args) {
  NODE* node = node_init(NULL, NULL, &graph->format);
  graph->nodes[idx] = node;
  graph->format.constructor(&node->data, args);
  node->graph = graph;
  node->graph_idx = idx;
}

GRAPH* graph_init(GRAPH* graph, unsigned long n, DATA_FORMAT* format) {

  graph = graph ? graph : malloc(sizeof(GRAPH));
  if( format ) {
    memcpy(&graph->format, format, sizeof(DATA_FORMAT));
  } else {
    data_format_init(&graph->format);
  }
  graph->num_nodes = n;
  graph->nodes = calloc(graph->num_nodes, sizeof(NODE*));
  graph->num_edges = 0;
  for(unsigned long i = 0; i < graph->num_nodes; i++) {
    graph_init_node(graph, i, NULL);
  }
  return graph;
}

NODE* graph_add_data(GRAPH* graph, void* args) {

  graph->nodes = realloc(graph->nodes, sizeof(NODE*) * ++graph->num_nodes);
  graph_init_node(graph, graph->num_nodes-1, args);
  return graph->nodes[graph->num_nodes-1];
}

struct NODE* graph_search_data(GRAPH* graph, DATA* data) {

  for(unsigned long i = 0; i < graph->num_nodes; i++) {

    NODE* node = graph->nodes[i];
    if( !graph->format.cmp(&node->data, data) ) return node;
  }
  return NULL;
}

struct NODE* graph_get(GRAPH* graph, unsigned long idx) {
  return idx < graph->num_nodes ? graph->nodes[idx] : NULL;
}

void graph_print(GRAPH* graph) {
  for(unsigned long i = 0; i < graph->num_nodes; i++) {
    node_print(graph->nodes[i], &graph->format);
    if(graph->nodes[i]->edges[OUT]) printf(" -> ");
    for(EDGE* edge = graph->nodes[i]->edges[OUT]; edge; edge = edge->next) {
      node_print(edge->mirror->parent, &graph->format);
      printf(" ");
    }
    printf("\n");
  }
}

void graph_debug(GRAPH* graph) {
  for(unsigned long i = 0; i < graph->num_nodes; i++) {
    node_debug(graph->nodes[i], &graph->format);
    if(graph->nodes[i]->edges[OUT]) printf(" -> ");
    for(EDGE* edge = graph->nodes[i]->edges[OUT]; edge; edge = edge->next) {
      node_debug(edge->mirror->parent, &graph->format);
      printf(" ");
    }
    printf("\n");
  }
}

int graph_oriented_connect_nodes(struct NODE* a, struct NODE* b, void* args) {
  if(a->graph != b->graph || !a->graph) return 0;
  node_connect_to(a, b, args);
  return 1;
}

int graph_connect_nodes(struct NODE* a, struct NODE* b, void* args) {
  if(a->graph != b->graph || !a->graph) return 0;
  node_connect(a, b, args);
  return 1;
}

EDGE* graph_get_one_edge(struct NODE* a, struct NODE* b, enum EDGE_TYPE type) {

  for(EDGE* edge = a->edges[type]; edge; edge = edge->next) {
    if(edge->mirror->parent == b) return edge;
  }
  return NULL;
}

EDGE** graph_get_edges(struct NODE* a, struct NODE* b, enum EDGE_TYPE type, unsigned long* num_edges) {

  EDGE** edges = NULL;
  *num_edges = 0;

  for(EDGE* edge = a->edges[type]; edge; edge = edge->next) {
    if(edge->mirror->parent == b) {
      edges = realloc(edges, (*num_edges)++);
      edges[(*num_edges)-1] = edge;
    }
  }
  return edges;
}

int graph_oriented_disconnect_nodes(struct NODE* a, struct NODE* b) {

  EDGE* out_edge = NULL;
  for(out_edge = a->edges[OUT]; out_edge && out_edge->mirror->parent != b; out_edge = out_edge->next);
  if(!out_edge) return 0;
  edge_free(out_edge, &a->graph->format);
  return 1;
}

int graph_disconnect_nodes(struct NODE* a, struct NODE* b) {

  EDGE* bi_edge = NULL;
  for(bi_edge = a->edges[BI]; bi_edge && bi_edge->mirror->parent != b; bi_edge = bi_edge->next);
  if(!bi_edge) return 0;
  edge_free(bi_edge, &a->graph->format);
  return 1;
}

void graph_remove_node(struct NODE* a) {

  GRAPH* graph = a->graph;

  for(unsigned idx = a->graph_idx+1; idx < graph->num_nodes; idx++) {
    graph->nodes[idx-1] = graph->nodes[idx];
    graph->nodes[idx-1]->graph_idx = idx-1;
  }
  node_free(a, &graph->format);
  graph->nodes = realloc(graph->nodes, sizeof(NODE*) * (--graph->num_nodes));
  free(a);
}

int graph_to_dot_file(GRAPH* graph, FILE* file) {

  fprintf(file, "digraph G {\n");
  for(unsigned long i = 0; i < graph->num_nodes; i++) {

    NODE* parent = graph->nodes[i];
    char* parent_identifier = graph->format.print(&parent->data);
    if(!parent->edges[OUT] && !parent->edges[BI]) {
      if(!fprintf(file, "\t\"%s\";\n", parent_identifier)) {
        free(parent_identifier);
        return 0;
      }
    }
    for(EDGE* edge = parent->edges[OUT]; edge; edge = edge->next) {

      NODE* node = edge->mirror->parent;
      char* node_identifier = graph->format.print(&node->data);
      char* edge_identifier = graph->format.print(&edge->data);
      int res = fprintf(file, "\t\"%s\" -> \"%s\" [dir=\"forward\", label=\"%s\"];\n",
          parent_identifier,
          node_identifier,
          edge_identifier
          );
      free(node_identifier);
      free(edge_identifier);
      if(!res) {
        free(parent_identifier);
        return 0;
      }
    }
    for(EDGE* edge = parent->edges[BI]; edge; edge = edge->next) {

      NODE* node = edge->mirror->parent;
      char* node_identifier = graph->format.print(&node->data);
      char* edge_identifier = graph->format.print(&edge->data);
      int res = fprintf(file, "\t\"%s\" -> \"%s\" [dir=\"none\", label=\"%s\"];\n",
          parent_identifier,
          node_identifier,
          edge_identifier
          );
      free(node_identifier);
      free(edge_identifier);
      if(!res) {
        free(parent_identifier);
        return 0;
      }
    }
    free(parent_identifier);
  }
  fprintf(file, "}");
  return 1;
}

int* graph_to_matrix(GRAPH* graph) {
  if(!graph->num_nodes) return NULL;
  int* matrix = calloc(graph->num_nodes * graph->num_nodes, sizeof(int*));
  memset(matrix, 0x00, graph->num_nodes * graph->num_nodes);
  // for every OUT and BI connection, write to the matrix
  for(NODE* node = graph_get(graph, 0); node; node = graph_get(graph, node->graph_idx+1)) {
    unsigned long parent_idx = node->graph_idx;
    for(EDGE* edge = node->edges[OUT]; edge; edge = edge->next) {
      unsigned long target_idx = edge->mirror->parent->graph_idx;
      matrix[ parent_idx * graph->num_nodes + target_idx ] = 1;
    }
    for(EDGE* edge = node->edges[BI]; edge; edge = edge->next) {

      unsigned long target_idx = edge->mirror->parent->graph_idx;
      matrix[ parent_idx * graph->num_nodes + target_idx ] = 1;
      matrix[ target_idx * graph->num_nodes + parent_idx ] = 1;
    }
  }
  return matrix;
}

int graph_topological_sort(GRAPH* graph) {
  return graph != NULL;
}
