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
  virtual bool pop(T& item) = 0;
  virtual void stop() = 0;
  virtual ~QueueInterface(){};
  QueueInterface() {}
  QueueInterface(const QueueInterface& q) = delete;
  QueueInterface& operator=(const QueueInterface& q) = delete;
protected:
  bool isStop;
};

template <class T>
class FixedSizeQueue : public QueueInterface<T> {
public:
  FixedSizeQueue(int size, T initValue);
  void push(T& item) override;
  bool pop(T& item) override;
  void stop() override;
private:
  std::vector<T> q;
  std::mutex qmtx;
  std::condition_variable not_full, not_empty;
  // qFront is the next pop item position, qEnd is the next push item positon.
  int qFront, qEnd, qSize, countItem;
};

template <class T>
FixedSizeQueue<T>::FixedSizeQueue(int size, T initValue) {
  if (size <= 0) {
    LOG(util::ERROR) << "FixedSizeQueue's size must be more than 0.";
  }
  qSize = size;
  q = std::vector<T>(qSize, initValue);
  qFront = qEnd = countItem = 0;
  QueueInterface<T>::isStop = false;
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
  ulock.unlock();
  not_empty.notify_all();
}

template <class T>
bool FixedSizeQueue<T>::pop(T& ret) {
  std::unique_lock<std::mutex> ulock(qmtx);
  while (countItem == 0) {
    if (QueueInterface<T>::isStop == true) {
      return false;
    }
    not_empty.wait(ulock);
  }
  countItem--;
  ret = q[qFront++];
  if (qFront == qSize) {
    qFront = 0;
  }
  ulock.unlock();
  not_full.notify_all();
  return true;
}

template <class T>
void FixedSizeQueue<T>::stop() {
  std::unique_lock<std::mutex> ulock(qmtx);
  QueueInterface<T>::isStop = true;
  ulock.unlock();
  not_empty.notify_all();
}

}
#endif
