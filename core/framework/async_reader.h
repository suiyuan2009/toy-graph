#ifndef CORE_FRAMEWORK_ASYNC_READER_H
#define CORE_FRAMEWORK_ASYNC_READER_H

#include <vector>

#include "core/framework/simple_reader.h"
#include "core/lib/queue.h"
#include "core/lib/thread.h"

namespace framework {

template <class T>
class AsyncReader : public SimpleReader<T> {
public:
  AsyncReader(std::string filePath, int oneEdgeSize, int bufSize = 100,
      int queueSize = 30, int bucketSize = 10000);
  ~AsyncReader() override;
  bool readInToEdge(lib::Bucket<T>*& edges, int bucketSize) override;
  void reset() override;
  void start() override;
  void stop() override;
  void readerThread();
private:
  int queueSize, bucketSize;
  lib::QueueInterface<lib::Bucket<T>*>* q;
  lib::ThreadInterface* reader;
};

template <class T>
AsyncReader<T>::AsyncReader(std::string filePath, int oneEdgeSize, int bufSize,
    int qs, int bs) : SimpleReader<T>(filePath, oneEdgeSize, bufSize) {
  queueSize = qs;
  bucketSize = bs;
  q = new lib::FixedSizeQueue<lib::Bucket<T>*>(queueSize, nullptr);
  reader = new lib::SimpleThread(
      std::bind(&AsyncReader<T>::readerThread, this));
}

template <class T>
AsyncReader<T>::~AsyncReader() {
  reader->join();
  delete(q);
  delete(reader);
}

template <class T>
void AsyncReader<T>::readerThread() {
  while (1) {
    if (ReaderInterface<T>::isStop) {
      q->stop();
      return;
    }
    lib::Bucket<T>* bkt = nullptr;
    if(!SimpleReader<T>::readInToEdge(bkt, bucketSize)) {
      delete(bkt);
      q->stop();
      return;
    }
    q->push(bkt);
  }
}

template <class T>
bool AsyncReader<T>::readInToEdge(lib::Bucket<T>*& edges, int bktSize) {
  if (bktSize != bucketSize) {
    LOG(util::ERROR) << "bucketSize must be equal to constructor's bucketSize";
  }
  if (!q->pop(edges)) {
    return false;
  }
  if (edges->empty()) {
    return false;
  }
  return true;
}

template <class T>
void AsyncReader<T>::reset() {
  reader->join();
  delete(q);
  delete(reader);
  SimpleReader<T>::reset();
  q = new lib::FixedSizeQueue<lib::Bucket<T>*>(queueSize, nullptr);
  reader = new lib::SimpleThread(
      std::bind(&AsyncReader<T>::readerThread, this));
  ReaderInterface<T>::isStop = false;
}

template <class T>
void AsyncReader<T>::start() {
  reader->start();
}

template <class T>
void AsyncReader<T>::stop() {
  ReaderInterface<T>::isStop = true;
  reader->join();
}

}
#endif
