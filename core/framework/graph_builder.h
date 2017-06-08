#ifndef CORE_FRAMEWORK_GRAPH_BUILDER_H
#define CORE_FRAMEWORK_GRAPH_BUILDER_H

#include "core/framework/graph.h"
#include "core/platform/types.h"

namespace framework {

class GraphBuilderInterface {
public:
  virtual GraphInterface* build(platform::ll vertexNum,
      platform::ll edgeNum) = 0;
  virtual ~GraphBuilderInterface() {}
};

template <class VertexT>
class SimpleGraphBuilder : public GraphBuilderInterface {
public:
  GraphInterface* build(platform::ll vertexNum, platform::ll edgeNum) override;
};

template <class VertexT>
GraphInterface* SimpleGraphBuilder<VertexT>::build(platform::ll vertexNum,
    platform::ll edgeNum) {
  SimpleGraph* simpleGraph = new SimpleGraph(vertexNum, edgeNum);
  for (platform::ll i = 0; i < vertexNum; i++) {
    simpleGraph->initVertex(i,  new VertexT(i));
  }
  return simpleGraph;
}

}
#endif
