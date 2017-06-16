#ifndef CORE_FRAMEWORK_VERTEX_H
#define CORE_FRAMEWORK_VERTEX_H

#include <string>

#include "core/framework/message.h"
#include "core/platform/types.h"

namespace framework {

class VertexInterface {
public:
  virtual void update(void* buf) = 0;
  virtual void init(void* buf) = 0;
  virtual void gather(void* buf, MessageInterface* msg) = 0;
  virtual void getValue(void* buf, MessageInterface* msg) = 0;
  virtual ~VertexInterface() {}
  virtual std::string getOutput(void* buf, platform::int64 idx) = 0;
};

}
#endif
