#ifndef CORE_LIB_THREAD_H
#define CORE_LIB_THREAD_H

#include <thread>

namespace lib {

class ThreadInterface {
public:
  virtual void start() = 0;
  virtual void join() = 0;
  ThreadInterface(const ThreadInterface& t) = delete;
  ThreadInterface& operator=(const ThreadInterface& t) = delete;
};

}
#endif
