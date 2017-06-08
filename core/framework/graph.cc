#include <vector>

#include "core/framework/graph.h"
#include "core/framework/vertex.h"
#include "core/platform/types.h"

namespace framework {

SimpleGraph::SimpleGraph(platform::ll vNum) {
 vertexNum = vNum;
 vertexes = std::vector<VertexInterface*>(vertexNum);
}

SimpleGraph::~SimpleGraph() {
  vertexes.clear();
}

bool SimpleGraph::getVertex(platform::ll idx, VertexInterface* v) {
  if (idx >= vertexNum) {
    return false;
  }
  v = vertexes[idx];
  return true;
}

}
