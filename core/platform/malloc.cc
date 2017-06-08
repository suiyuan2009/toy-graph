#include <stdlib.h>

namespace platform {

void* Malloc(size_t size) {
  return malloc(size);
}

void Free(void* buffer) {
  free(buffer);
}

}
