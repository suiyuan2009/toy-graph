#ifndef CORE_FRAMEWORK_GRAPH_H
#define CORE_FRAMEWORK_GRAPH_H

#include <vector>

#include "core/framework/graph_builder.h"
#include "core/framework/vertex.h"
#include "core/platform/types.h"

namespace framework {

class GraphInterface {
public:
  virtual bool getVertex(platform::ll idx, VertexInterface* v) = 0;
  virtual ~GraphInterface() = 0;
};

class SimpleGraph : public GraphInterface {
public:
  SimpleGraph(platform::ll vNum);
  SimpleGraph() = delete;
  SimpleGraph(const SimpleGraph& sg) = delete;
  SimpleGraph& operator=(const SimpleGraph& sg) = delete;
  ~SimpleGraph() override;
  bool getVertex(platform::ll idx, VertexInterface* v) override;
private:
  int vertexNum;
  std::vector<VertexInterface*> vertexes;
friend class GraphBuilderInterface;
};

}
#endif
