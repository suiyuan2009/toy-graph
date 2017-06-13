#ifndef CORE_FRAMEWORK_GRAPH_BUILDER_H
#define CORE_FRAMEWORK_GRAPH_BUILDER_H

#include <iostream>

#include "core/framework/graph.h"
#include "core/platform/types.h"
#include "core/util/logging.h"

namespace framework {

class GraphBuilderInterface {
public:
  virtual GraphInterface* build(platform::int64 vertexNum,
      platform::int64 edgeNum) = 0;
  virtual ~GraphBuilderInterface() {}
};

template <class VertexT>
class SimpleGraphBuilder : public GraphBuilderInterface {
public:
  GraphInterface* build(platform::int64 vertexNum,
      platform::int64 edgeNum) override;
};

template <class VertexT>
GraphInterface* SimpleGraphBuilder<VertexT>::build(platform::int64 vertexNum,
    platform::int64 edgeNum) {
  SimpleGraph* simpleGraph = new SimpleGraph(vertexNum, edgeNum);
  VertexInterface* vertex = new VertexT();
  simpleGraph->setVertex(vertex);
  LOG(util::INFO)<<"start init every vertex.";
  for (platform::int64 i = 0; i < vertexNum; i++) {
    simpleGraph->initOneVertex(i);
  }
  LOG(util::INFO)<<"finish init every vertex.";
  return simpleGraph;
}

}
#endif
