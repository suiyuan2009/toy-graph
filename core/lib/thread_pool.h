#ifndef CORE_LIB_THREAD_POOL_H
#define CORE_LIB_THREAD_POOL_H

#include "core/lib/queue.h"
#include "core/lib/thread.h"

namespace lib {

class ThreadPool;
class Worker {
public:
  Worker(ThreadPool& _pool);
  void operator()();
private:
  ThreadPool& pool;
};

class ThreadPool {
friend class Worker;
public:
  ThreadPool(int workerNum, int queueSize = 100);
  ThreadPool() = delete;
  ThreadPool(const ThreadPool& t) = delete;
  ThreadPool& operator=(const ThreadPool& t) = delete;
  ~ThreadPool();
  void enQueue(std::function<void()> f);
  void start();
  void stop();
private:
  bool isStop;
  QueueInterface<std::function<void()>>* q;
  std::vector<ThreadInterface*> workers;
};

}
#endif
