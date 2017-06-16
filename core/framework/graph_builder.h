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
      platform::int64 edgeNum, int oneVertexSize) = 0;
  virtual ~GraphBuilderInterface() {}
};

template <class VertexT>
class SimpleGraphBuilder : public GraphBuilderInterface {
public:
  GraphInterface* build(platform::int64 vertexNum,
      platform::int64 edgeNum, int oneVertexSize) override;
};

template <class VertexT>
GraphInterface* SimpleGraphBuilder<VertexT>::build(platform::int64 vertexNum,
    platform::int64 edgeNum, int ovs) {
  VertexInterface* vertex = new VertexT();
  SimpleGraph* simpleGraph = new SimpleGraph(vertexNum, edgeNum, ovs, vertex);
  return simpleGraph;
}

}
#endif
