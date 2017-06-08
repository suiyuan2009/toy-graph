#include "core/framework/graph_builder.h"
#include "core/platform/types.h"

namespace framework {

template <class VertexT>
GraphInterface* SimpleGraphBuilder<VertexT>::build(platform::ll vertexNum) {
  SimpleGraphBuilder* simpleGraph = new SimpleGraph(vertexNum);
  for (platform::ll i = 0; i < vertexNum; i++) {
    simpleGraph->vertexes[i] = new VertexT(i);
  }
  return simpleGraph;
}

}
