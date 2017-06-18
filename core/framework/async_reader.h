#ifndef CORE_FRAMEWORK_ASYNC_READER_H
#define CORE_FRAMEWORK_ASYNC_READER_H

#include "core/framework/reader.h"
#include "core/lib/queue.h"
#include "core/lib/thread.h"
#include "core/util/logging.h"

namespace framework {

template <class T>
class AsyncReader : public SimpleReader {
public:
  AsyncReader(std::string filePath, int oneEdgeSize, int bufSize = 100,
      int queueSize = 100000);
  ~AsyncReader() override;
  bool readInToEdge(EdgeInterface* edge) override;
  void reset() override;
  void start() override;
  void readerThread();
private:
  int queueSize;
  lib::QueueInterface<T>* q;
  lib::ThreadInterface* reader;
};

template <class T>
AsyncReader<T>::AsyncReader(std::string filePath, int oneEdgeSize, int bufSize,
    int qs) : SimpleReader(filePath, oneEdgeSize, bufSize) {
  queueSize = qs;
  q = new lib::FixedSizeQueue<T>(queueSize);
  reader = new lib::SimpleThread<void()>(
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
  T edge;
  while (1) {
    if (offset >= readerBufSize) {
      file->sequentialRead(buf, readerBufSize, bufSize);
      if (bufSize == 0) {
        q->stop();
        return;
      }
      offset = 0;
    } else {
      if (offset + oneEdgeSize > bufSize) {
        q->stop();
        return;
      }
      edge.read((char*)buf + offset);
      q->push(edge);
      offset += oneEdgeSize;
    }
  }
}

template <class T>
bool AsyncReader<T>::readInToEdge(EdgeInterface* edge) {
  if (!q->pop(*((T*)edge))) {
    return false;
  }
  return true;
}

template <class T>
void AsyncReader<T>::reset() {
  reader->join();
  delete(q);
  delete(reader);
  SimpleReader::reset();
  q = new lib::FixedSizeQueue<T>(queueSize);
  reader = new lib::SimpleThread<void()>(
      std::bind(&AsyncReader<T>::readerThread, this));
}

template <class T>
void AsyncReader<T>::start() {
  reader->start();
}

}
#endif
