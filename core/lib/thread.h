#ifndef CORE_LIB_THREAD_H
#define CORE_LIB_THREAD_H

#include <functional>
#include <thread>

namespace lib {

class ThreadInterface {
public:
  virtual void start() = 0;
  virtual void join() = 0;
  virtual ~ThreadInterface(){}
  ThreadInterface(){}
  ThreadInterface(const ThreadInterface& t) = delete;
  ThreadInterface& operator=(const ThreadInterface& t) = delete;
protected:
  bool started;
};

class SimpleThread : public ThreadInterface {
public:
  void start() override;
  void join() override;
  SimpleThread(std::function<void()> f);
private:
  std::function<void()> func;
  std::thread th;
};

}
#endif
