#ifndef CORE_FRAMEWORK_GRAPH_BUILDER_H
#define CORE_FRAMEWORK_GRAPH_BUILDER_H

#include "core/framework/graph.h"
#include "core/platform/types.h"

namespace framework {

class GraphInterface;

class GraphBuilderInterface {
public:
  virtual GraphInterface* build(platform::ll vertexNum) = 0;
};

template <class VertexT>
class SimpleGraphBuilder : public GraphBuilderInterface {
public:
  GraphInterface* build(platform::ll vertexNum) override;
};

}
#endif
