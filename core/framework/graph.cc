#include <string>

#include "core/framework/graph.h"
#include "core/framework/message.h"
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
  delete(vertex);
}

void SimpleGraph::scatter(platform::int64 idx, MessageInterface* msg) {
  vertex->gather(vertexBuf, idx * oneVertexSize, msg);
}

void SimpleGraph::updateOneVertex(platform::int64 idx) {
  vertex->update(vertexBuf, idx * oneVertexSize);
}

void SimpleGraph::initOneVertex(platform::int64 idx) {
  vertex->initOneVertex(vertexBuf, idx * oneVertexSize);
}

void SimpleGraph::getVertexInfo(platform::int64 idx, MessageInterface* msg) {
  vertex->get(vertexBuf, idx * oneVertexSize, msg);
}

void SimpleGraph::updateAllVertex() {
  for (platform::int64 i = 0; i < vertexNum; i++) {
    updateOneVertex(i);
  }
}

platform::int64 SimpleGraph::getEdgeNum() {
  return edgeNum;
}

platform::int64 SimpleGraph::getVertexNum() {
  return vertexNum;
}

std::string SimpleGraph::getVertexOutput(platform::int64 idx) {
  return vertex->getOutput(vertexBuf, idx * oneVertexSize);
}

}
