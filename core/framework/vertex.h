#ifndef CORE_FRAMEWORK_VERTEX_H
#define CORE_FRAMEWORK_VERTEX_H

#include "core/framework/message.h"
#include "core/platform/types.h"

namespace framework {

const platform::int32 oneVertexSize = 8;
class VertexInterface {
public:
  virtual void update(char* buf, platform::int64 offset) = 0;
  virtual void initOneVertex(char* buf, platform::int64 offset) = 0;
  virtual void gather(char* buf, platform::int64 offset,
      MessageInterface* msg) = 0;
  virtual void get(char* buf, platform::int64 offset, MessageInterface* msg) = 0;
  virtual ~VertexInterface() {}
};

}
#endif
