#ifndef CORE_LIB_QUEUE_H
#define CORE_LIB_QUEUE_H

#include <condition_variable>
#include <mutex>
#include <vector>

#include "core/util/logging.h"

namespace lib {

template <class T>
class QueueInterface {
public:
  virtual void push(T& item) = 0;
  virtual T pop() = 0;
  virtual ~QueueInterface(){};
  QueueInterface() {}
  QueueInterface(const QueueInterface& q) = delete;
  QueueInterface& operator=(const QueueInterface& q) = delete;
};

template <class T>
class FixedSizeQueue : public QueueInterface<T> {
public:
  FixedSizeQueue(int size);
  void push(T& item) override;
  T pop() override;
private:
  std::vector<T> q;
  std::mutex qmtx;
  std::condition_variable not_full, not_empty;
  // qFront is the next pop item position, qEnd is the next push item positon.
  int qFront, qEnd, qSize, countItem;
};

template <class T>
FixedSizeQueue<T>::FixedSizeQueue(int size) {
  if (size <= 0) {
    LOG(util::ERROR) << "FixedSizeQueue's size must be more than 0.";
  }
  qSize = size;
  q = std::vector<T>(qSize);
  qFront = qEnd = countItem = 0;
}

template <class T>
void FixedSizeQueue<T>::push(T& item) {
  std::unique_lock<std::mutex> ulock(qmtx);
  not_full.wait(ulock, [this](){return this->countItem < this->qSize;});
  countItem++;
  q[qEnd] = item;
  qEnd++;
  if (qEnd == qSize) {
    qEnd = 0;
  }
  not_empty.notify_all();
}

template <class T>
T FixedSizeQueue<T>::pop() {
  std::unique_lock<std::mutex> ulock(qmtx);
  not_empty.wait(ulock, [this](){return this->countItem > 0;});
  countItem--;
  T& ret = q[qFront++];
  if (qFront == qSize) {
    qFront = 0;
  }
  not_full.notify_all();
  return ret;
}

}
#endif
