#include <string>

#include "core/framework/graph.h"
#include "core/framework/message.h"
#include "core/framework/vertex.h"
#include "core/platform/malloc.h"
#include "core/platform/types.h"
#include "core/util/logging.h"

namespace framework {

GraphInterface::GraphInterface(platform::int64 vNum, platform::int64 eNum,
    int ovs) {
  oneVertexSize = ovs;
  vertexNum = vNum, edgeNum = eNum;
  vertexBufSize = oneVertexSize * vNum;
  LOG(util::INFO) << "vertex buf size is " << vertexBufSize
                  << ", this is where to save vertex info during computation.";
  vertexBuf = platform::Malloc(vertexBufSize);
}

GraphInterface::~GraphInterface() {
  platform::Free(vertexBuf);
}

SimpleGraph::SimpleGraph(platform::int64 vNum, platform::int64 eNum, int ovs,
    VertexInterface* v, bool _use_locking) : GraphInterface(vNum, eNum, ovs) {
  vertex = v;
  use_locking = _use_locking;
  if (use_locking) {
    mtx = std::vector<std::mutex>(1000003);
  }
}

SimpleGraph::~SimpleGraph() {
  delete(vertex);
}

void SimpleGraph::scatter(platform::int64 idx, MessageInterface* msg) {
  if (use_locking) {
    std::unique_lock<std::mutex> ulock(mtx[idx%1000003]);
    vertex->gather((char*)vertexBuf + idx * oneVertexSize, msg);
  } else {
    vertex->gather((char*)vertexBuf + idx * oneVertexSize, msg);
  }
}

void SimpleGraph::initAllVertex() {
  for (platform::int64 idx = 0; idx < vertexNum; idx++) {
    vertex->init((char*)vertexBuf + idx * oneVertexSize);
  }
}

void SimpleGraph::getVertexInfo(platform::int64 idx, MessageInterface* msg) {
  vertex->getValue((char*)vertexBuf + idx * oneVertexSize, msg);
}

void SimpleGraph::updateAllVertex() {
  for (platform::int64 i = 0; i < vertexNum; i++) {
    vertex->update((char*)vertexBuf + i * oneVertexSize);
  }
}

platform::int64 SimpleGraph::getEdgeNum() {
  return edgeNum;
}

platform::int64 SimpleGraph::getVertexNum() {
  return vertexNum;
}

std::string SimpleGraph::getVertexOutput(platform::int64 idx) {
  return vertex->getOutput((char*)vertexBuf + idx * oneVertexSize, idx);
}

}
