#ifndef CORE_FRAMEWORK_VERTEX_H
#define CORE_FRAMEWORK_VERTEX_H

#include "core/framework/message.h"

namespace framework {

class VertexInterface {
public:
  virtual void update() = 0;
  virtual void gather(MessageInterface* msg) = 0;
  virtual void get(MessageInterface* msg) = 0;
  virtual ~VertexInterface() {}
};

}
#endif
