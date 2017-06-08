#include <vector>

#include "core/framework/graph.h"
#include "core/framework/vertex.h"
#include "core/platform/types.h"

namespace framework {

GraphInterface::GraphInterface(platform::ll vNum, platform::ll eNum) {
  vertexNum = vNum, edgeNum = eNum;
}

SimpleGraph::SimpleGraph(platform::ll vNum, platform::ll eNum):
    GraphInterface(vNum, eNum) {
 vertexes = std::vector<VertexInterface*>(vNum);
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

void SimpleGraph::updateVertex(VertexInterface* v) {
  v->update();
}

void SimpleGraph::update() {
  for (int i = 0; i < vertexNum; i++) {
    updateVertex(vertexes[i]);
  }
}

}
