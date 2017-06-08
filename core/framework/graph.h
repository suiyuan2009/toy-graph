#ifndef CORE_FRAMEWORK_GRAPH_H
#define CORE_FRAMEWORK_GRAPH_H

#include <vector>

#include "core/framework/vertex.h"
#include "core/platform/types.h"

namespace framework {

class GraphInterface {
public:
  GraphInterface(platform::int64 vNum, platform::int64 eNum);
  virtual bool getVertex(platform::int64 idx, VertexInterface* v) = 0;
  virtual void updateVertex(VertexInterface* v) = 0;
  virtual void update() = 0;
  virtual ~GraphInterface() {};
protected:
  platform::int64 vertexNum, edgeNum;
};

class SimpleGraph : public GraphInterface {
public:
  SimpleGraph(platform::int64 vNum, platform::int64 eNum);
  SimpleGraph() = delete;
  SimpleGraph(const SimpleGraph& sg) = delete;
  SimpleGraph& operator=(const SimpleGraph& sg) = delete;
  ~SimpleGraph() override;
  bool getVertex(platform::int64 idx, VertexInterface* v) override;
  void updateVertex(VertexInterface* v) override;
  void update() override;
  void initVertex(platform::int64 idx, VertexInterface* v);
private:
  std::vector<VertexInterface*> vertexes;
};



}
#endif
