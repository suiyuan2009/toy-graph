#ifndef CORE_FRAMEWORK_EDGE_H
#define CORE_FRAMEWORK_EDGE_H

#include "core/framework/graph.h"
#include "core/framework/message.h"

namespace framework {

class EdgeInterface {
public:
  virtual bool read(char* buf, int size, int& offset) = 0;
  virtual void scatter(GraphInterface* g, MessageInterface* msg) = 0;
};

}
#endif