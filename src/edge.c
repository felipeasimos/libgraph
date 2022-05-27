#include "edge.h"
#include "data_format.h"
#include "node.h"

void edge_free(EDGE* edge, DATA_FORMAT* format) {

  format->destructor(&edge->data);
}
