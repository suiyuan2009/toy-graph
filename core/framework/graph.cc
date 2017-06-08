#include <vector>

#include "core/framework/graph.h"
#include "core/framework/vertex.h"
#include "core/platform/malloc.h"
#include "core/platform/types.h"

namespace framework {

GraphInterface::GraphInterface(platform::int64 vNum, platform::int64 eNum) {
  vertexNum = vNum, edgeNum = eNum;
  vertexBufSize = framework::oneVertexSize * vNum;
  vertexBuf = platform::Malloc(vertexBufSize);
}

GraphInterface::~GraphInterface() {
  platform::Free(vertexBuf);
}

SimpleGraph::SimpleGraph(platform::int64 vNum, platform::int64 eNum):
    GraphInterface(vNum, eNum) {
}

void SimpleGraph::setVertex(VertexInterface* v) {
  vertex = v;
}

SimpleGraph::~SimpleGraph() {
  platform::Free(vertex);
}

void SimpleGraph::updateOneVertex(platform::int64 idx) {
  vertex->update((char*)vertexBuf, idx * oneVertexSize);
}

void SimpleGraph::initOneVertex(platform::int64 idx) {
  vertex->initOneVertex((char*)vertexBuf, idx * oneVertexSize);
}

void SimpleGraph::updateAllVertex() {
  for (platform::int64 i = 0; i < vertexNum; i++) {
    updateOneVertex(i);
  }
}

}
