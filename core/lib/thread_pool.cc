#include "core/lib/thread_pool.h"
#include "core/util/logging.h"

namespace lib {
ThreadPool::ThreadPool(int workerNum, int queueSize) {
  if (workerNum <= 0) {
    LOG(util::ERROR) << "worker number must be more than 0!";
  }
  isStop = false;
  q = new FixedSizeQueue<std::function<void()>>(queueSize);
  workers = std::vector<ThreadInterface*>(workerNum,
      new SimpleThread(Worker(*this)));
}

ThreadPool::~ThreadPool() {
  if (isStop == false) {
    isStop = true;
  }
  q->stop();
  for (int i = 0; i < (int)workers.size(); i++) {
    workers[i]->join();
  }
  delete(q);
}

void ThreadPool::enQueue(std::function<void()> f) {
  q->push(f);
}

void ThreadPool::start() {
  for (int i = 0; i < (int)workers.size(); i++) {
    workers[i]->start();
  }
}

void ThreadPool::stop() {
  isStop = true;
}

Worker::Worker(ThreadPool& _pool) : pool(_pool) {}

void Worker::operator()() {
  std::function<void()> task;
  while (1) {
    if (pool.isStop == true) {
      break;
    }
    if(!pool.q->pop(task)) {
      pool.stop();
      break;
    }
    task();
  }
}
} // namespace lib
