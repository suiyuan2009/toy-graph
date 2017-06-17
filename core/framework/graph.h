#ifndef CORE_FRAMEWORK_GRAPH_H
#define CORE_FRAMEWORK_GRAPH_H

#include <string>

#include "core/framework/message.h"
#include "core/framework/vertex.h"
#include "core/platform/types.h"

namespace framework {

class GraphInterface {
public:
  GraphInterface(platform::int64 vNum, platform::int64 eNum, int oneVertexSize);
  virtual void updateAllVertex() = 0;
  virtual void initAllVertex() = 0;
  virtual void getVertexInfo(platform::int64 idx, MessageInterface* msg) = 0;
  virtual std::string getVertexOutput(platform::int64 idx) = 0;
  virtual void scatter(platform::int64 idx, MessageInterface* msg) = 0;
  virtual platform::int64 getEdgeNum() = 0;
  virtual platform::int64 getVertexNum() = 0;
  virtual ~GraphInterface();
  GraphInterface() = delete;
  GraphInterface& operator=(const GraphInterface& g) = delete;
  GraphInterface(const GraphInterface& g) = delete;
protected:
  platform::int64 vertexNum, edgeNum, vertexBufSize;
  void* vertexBuf;
  int oneVertexSize;
};

class SimpleGraph : public GraphInterface {
public:
  SimpleGraph(platform::int64 vNum, platform::int64 eNum, int initOneVertex,
             VertexInterface* v);
  ~SimpleGraph() override;
  void updateAllVertex() override;
  void initAllVertex() override;
  void getVertexInfo(platform::int64 idx, MessageInterface* msg) override;
  void scatter(platform::int64 idx, MessageInterface* msg) override;
  platform::int64 getEdgeNum() override;
  platform::int64 getVertexNum() override;
  std::string getVertexOutput(platform::int64 idx) override;
private:
  VertexInterface* vertex;
};

}
#endif
