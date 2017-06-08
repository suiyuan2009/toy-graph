#include "core/platform/types.h"

namespace framework {

class VertexInterface {
public:
  VertexInterface(platform::ll idx);
  virtual void gather() = 0;
};

}
