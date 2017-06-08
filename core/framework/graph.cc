#include <vector>

#include "core/framework/graph.h"
#include "core/framework/vertex.h"
#include "core/platform/types.h"

namespace framework {

GraphInterface::GraphInterface(platform::int64 vNum, platform::int64 eNum) {
  vertexNum = vNum, edgeNum = eNum;
}

SimpleGraph::SimpleGraph(platform::int64 vNum, platform::int64 eNum):
    GraphInterface(vNum, eNum) {
 vertexes = std::vector<VertexInterface*>(vNum);
}

SimpleGraph::~SimpleGraph() {
  vertexes.clear();
}

bool SimpleGraph::getVertex(platform::int64 idx, VertexInterface* v) {
  if (idx >= vertexNum) {
    return false;
  }
  v = vertexes[idx];
  return true;
}

void SimpleGraph::updateVertex(VertexInterface* v) {
  v->update();
}

void SimpleGraph::initVertex(platform::int64 idx, VertexInterface* v) {
  delete(vertexes[idx]);
  vertexes[idx] = v;
}

void SimpleGraph::update() {
  for (int i = 0; i < vertexNum; i++) {
    updateVertex(vertexes[i]);
  }
}

}
