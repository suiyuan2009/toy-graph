#ifndef CORE_PLATFORM_MALLOC_H
#define CORE_PLATFORM_MALLOC_H
#include <stdlib.h>

namespace platform {

inline void* Malloc(size_t size) {
  return malloc(size);
}

inline void Free(void* buffer) {
  free(buffer);
}

}
#endif
