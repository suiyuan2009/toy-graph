#ifndef CORE_FRAMEWORK_GRAPH_H
#define CORE_FRAMEWORK_GRAPH_H

#include <vector>

#include "core/framework/vertex.h"
#include "core/platform/types.h"

namespace framework {

class GraphInterface {
public:
  GraphInterface(platform::ll vNum, platform::ll eNum);
  virtual bool getVertex(platform::ll idx, VertexInterface* v) = 0;
  virtual void updateVertex(VertexInterface* v) = 0;
  virtual void update() = 0;
  virtual ~GraphInterface() {};
protected:
  platform::ll vertexNum, edgeNum;
};

class SimpleGraph : public GraphInterface {
public:
  SimpleGraph(platform::ll vNum, platform::ll eNum);
  SimpleGraph() = delete;
  SimpleGraph(const SimpleGraph& sg) = delete;
  SimpleGraph& operator=(const SimpleGraph& sg) = delete;
  ~SimpleGraph() override;
  bool getVertex(platform::ll idx, VertexInterface* v) override;
  void updateVertex(VertexInterface* v) override;
  void update() override;
  void initVertex(platform::ll idx, VertexInterface* v);
private:
  std::vector<VertexInterface*> vertexes;
};



}
#endif
