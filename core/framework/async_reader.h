#ifndef CORE_FRAMEWORK_ASYNC_READER_H
#define CORE_FRAMEWORK_ASYNC_READER_H

#include <vector>

#include "core/framework/reader.h"
#include "core/lib/bucket.h"
#include "core/lib/queue.h"
#include "core/lib/thread.h"
#include "core/util/logging.h"

namespace framework {

template <class T>
class AsyncReader : public SimpleReader {
public:
  AsyncReader(std::string filePath, int oneEdgeSize, int bufSize = 100,
      int queueSize = 10, int bucketSize = 10000);
  ~AsyncReader() override;
  bool readInToEdge(std::vector<EdgeInterface*>& edges, int& size) override;
  void reset() override;
  void start() override;
  void stop() override;
  void readerThread();
private:
  int queueSize, bucketSize;
  lib::QueueInterface<lib::Bucket<T>>* q;
  lib::ThreadInterface* reader;
  lib::Bucket<T> tmpBucket;
};

template <class T>
AsyncReader<T>::AsyncReader(std::string filePath, int oneEdgeSize, int bufSize,
    int qs, int bs) : SimpleReader(filePath, oneEdgeSize, bufSize) {
  queueSize = qs;
  bucketSize = bs;
  q = new lib::FixedSizeQueue<lib::Bucket<T>>(queueSize,
      lib::Bucket<T>(bucketSize));
  reader = new lib::SimpleThread(
      std::bind(&AsyncReader<T>::readerThread, this));
  tmpBucket = lib::Bucket<T>(bucketSize);
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
  lib::Bucket<T> bkt(bucketSize);
  while (1) {
    if (isStop) {
      q->stop();
      return;
    }
    if (offset >= readerBufSize) {
      file->sequentialRead(buf, readerBufSize, bufSize);
      if (bufSize == 0) {
        if (!bkt.empty()) {
          q->push(bkt);
          bkt.clear();
        }
        q->stop();
        return;
      }
      offset = 0;
    } else {
      if (offset + oneEdgeSize > bufSize) {
        if (!bkt.empty()) {
          q->push(bkt);
          bkt.clear();
        }
        q->stop();
        return;
      }
      edge.read((char*)buf + offset);
      bkt.push(edge);
      if (bkt.full()) {
        q->push(bkt);
        bkt.clear();
      }
      offset += oneEdgeSize;
    }
  }
}

template <class T>
bool AsyncReader<T>::readInToEdge(std::vector<EdgeInterface*>& edges,
    int& num) {
  if (!q->pop(tmpBucket)) {
    return false;
  }
  if (tmpBucket.empty()) {
    return false;
  }
  if (edges.size() < bucketSize) {
    LOG(util::ERROR) <<
      "vector passed to readInToEdge 's size must not be less than bucketSize.";
  }
  for (int i = 0; i < tmpBucket.size(); i++) {
    (*(T*)edges[i]) = tmpBucket[i];
  }
  num = tmpBucket.size();
  return true;
}

template <class T>
void AsyncReader<T>::reset() {
  reader->join();
  delete(q);
  delete(reader);
  SimpleReader::reset();
  q = new lib::FixedSizeQueue<lib::Bucket<T>>(queueSize,
      lib::Bucket<T>(bucketSize));
  reader = new lib::SimpleThread(
      std::bind(&AsyncReader<T>::readerThread, this));
  isStop = false;
}

template <class T>
void AsyncReader<T>::start() {
  reader->start();
}

template <class T>
void AsyncReader<T>::stop() {
  isStop = true;
  reader->join();
}

}
#endif
