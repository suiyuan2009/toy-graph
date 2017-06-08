#ifndef CORE_FRAMEWORK_GRAPH_BUILDER_H
#define CORE_FRAMEWORK_GRAPH_BUILDER_H

#include <iostream>

#include "core/framework/graph.h"
#include "core/platform/types.h"

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
  GraphInterface* build(platform::int64 vertexNum, platform::int64 edgeNum) override;
};

template <class VertexT>
GraphInterface* SimpleGraphBuilder<VertexT>::build(platform::int64 vertexNum,
    platform::int64 edgeNum) {
  SimpleGraph* simpleGraph = new SimpleGraph(vertexNum, edgeNum);
  std::cout<<"finish vector init, start init every vertex, vertex size is "<<
    sizeof(VertexT)<<std::endl;
  for (platform::int64 i = 0; i < vertexNum; i++) {
    simpleGraph->initVertex(i,  new VertexT());
  }
  return simpleGraph;
}

}
#endif
