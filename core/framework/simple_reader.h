#ifndef CORE_FRAMEWORK_SIMPLE_READER_H
#define CORE_FRAMEWORK_SIMPLE_READER_H

#include <string>

#include "core/framework/reader.h"
#include "core/platform/file.h"
#include "core/platform/malloc.h"
#include "core/util/logging.h"

namespace framework {

template <class T>
class SimpleReader : public ReaderInterface<T> {
public:
  virtual ~SimpleReader();
  SimpleReader(std::string filePath, int oneEdgeSize, int bufSize = 100);
  virtual bool readInToEdge(T& edge) override;
  virtual bool readInToEdge(lib::Bucket<T>*& edges, int bucketSize) override;
  virtual void reset() override;
  virtual void start() override {}
  virtual void stop() override;
protected:
  platform::FileInterface* file;
  void* buf;
  int readerBufSize; // size of buf
  int offset; // already read at offset
  int bufSize; // data size in buf
  int oneEdgeSize;
  std::string filePath;
};

template <class T>
SimpleReader<T>::SimpleReader(std::string filePath, int oes, int bufSize)
    : ReaderInterface<T>() {
  oneEdgeSize = oes;
  readerBufSize = oes * bufSize;
  file = new platform::PosixReadFile(filePath);
  this->filePath = filePath;
  offset = readerBufSize;
  bufSize = 0;
  buf = platform::Malloc(readerBufSize);
}

template <class T>
SimpleReader<T>::~SimpleReader() {
  platform::Free(buf);
  delete(file);
}

template <class T>
bool SimpleReader<T>::readInToEdge(T& edge) {
  if (ReaderInterface<T>::isStop) {
    return false;
  }
  if (offset >= readerBufSize) {
    file->sequentialRead(buf, readerBufSize, bufSize);
    if (bufSize == 0) return false;
    offset = 0;
  }
  if (offset + oneEdgeSize > bufSize) {
    return false;
  }
  edge.read((char*)buf + offset);
  offset += oneEdgeSize;
  return true;
}

template <class T>
bool SimpleReader<T>::readInToEdge(lib::Bucket<T>*& bkt, int bucketSize) {
  if (ReaderInterface<T>::isStop) {
    return false;
  }
  if (bucketSize <= 0) {
    LOG(util::ERROR) << "bucketSize must be more than 0 in readInToEdge!";
  }
  int num = 0;
  bkt = new lib::Bucket<T>(bucketSize);
  while (num < bucketSize && readInToEdge((*bkt)[num])) {
    num++;
  }
  bkt->setSize(num);
  return num > 0;
}

template <class T>
void SimpleReader<T>::reset() {
  delete(file);
  file = new platform::PosixReadFile(filePath);
  offset = readerBufSize;
  bufSize = 0;
  ReaderInterface<T>::isStop = false;
}

template <class T>
void SimpleReader<T>::stop() {
  ReaderInterface<T>::isStop = true;
}

}
#endif
