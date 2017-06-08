#include "core/framework/graph.h"
#include "core/platform/types.h"

namespace framework {

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
