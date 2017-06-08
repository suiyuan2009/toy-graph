#ifndef CORE_FRAMEWORK_VERTEX_H
#define CORE_FRAMEWORK_VERTEX_H

#include "core/platform/types.h"

namespace framework {

class VertexInterface {
public:
  VertexInterface(platform::ll idx);
  virtual void gather() = 0;
};

}
#endif
