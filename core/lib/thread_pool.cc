#include "core/lib/thread_pool.h"
#include "core/util/logging.h"

namespace lib {
ThreadPool::ThreadPool(int workerNum, int queueSize) {
  if (workerNum <= 0) {
    LOG(util::ERROR) << "worker number must be more than 0!";
  }
  isStop = false;
  q = new FixedSizeQueue<std::function<void()>>(queueSize);
  workers = std::vector<ThreadInterface*>(workerNum);
  for (int i = 0; i < workerNum; i++) {
    workers[i] = new SimpleThread(Worker(*this));
  }
}

ThreadPool::~ThreadPool() {
  q->stop();
  for (int i = 0; i < (int)workers.size(); i++) {
    workers[i]->join();
    delete(workers[i]);
  }
  if (isStop == false) {
    isStop = true;
  }
  delete(q);
}

void ThreadPool::enQueue(std::function<void()> f) {
  q->push(f);
}

void ThreadPool::start() {
  LOG(util::INFO) << "try to start " << workers.size() << " workers.";
  for (int i = 0; i < (int)workers.size(); i++) {
    workers[i]->start();
    LOG(util::INFO) << "worker " << i << " started.";
  }
  LOG(util::INFO) << "all workers started.";
}

void ThreadPool::stop() {
  q->stop();
  for (int i = 0; i < (int)workers.size(); i++) {
    workers[i]->join();
  }
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
      pool.isStop = true;
      break;
    }
    task();
  }
}
} // namespace lib
