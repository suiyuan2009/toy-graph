#ifndef CORE_FRAMEWORK_VERTEX_H
#define CORE_FRAMEWORK_VERTEX_H

#include <string>

#include "core/framework/message.h"
#include "core/platform/types.h"

namespace framework {

const platform::int32 oneVertexSize = 8;
class VertexInterface {
public:
  virtual void update(void* buf, platform::int64 offset) = 0;
  virtual void initOneVertex(void* buf, platform::int64 offset) = 0;
  virtual void gather(void* buf, platform::int64 offset,
      MessageInterface* msg) = 0;
  virtual void get(void* buf, platform::int64 offset,
      MessageInterface* msg) = 0;
  virtual ~VertexInterface() {}
  virtual std::string getOutput(void* buf, platform::int64 offset,
      platform::int64 idx) = 0;
};

}
#endif
