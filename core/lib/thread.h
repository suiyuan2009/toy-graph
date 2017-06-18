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

template <typename T>
class SimpleThread : public ThreadInterface {
public:
  void start() override;
  void join() override;
  SimpleThread(std::function<T> f);
private:
  std::function<T> func;
  std::thread th;
};

template <typename T>
SimpleThread<T>::SimpleThread(std::function<T> f) {
  func = f;
  started = false;
}

template <typename T>
void SimpleThread<T>::start() {
  th=std::thread(func);
  started = true;
}

template <typename T>
void SimpleThread<T>::join() {
  if (started) {
    th.join();
    started = false;
  }
}

}
#endif
