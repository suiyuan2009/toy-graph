#ifndef CORE_FRAMEWORK_READER_H
#define CORE_FRAMEWORK_READER_H

#include "core/lib/bucket.h"

namespace framework {

template <class T>
class ReaderInterface {
public:
  virtual bool readInToEdge(T& edge) = 0;
  virtual bool readInToEdge(lib::Bucket<T>*& edges, int bucketSize) = 0;
  virtual void reset() = 0;
  virtual void start() = 0;
  virtual void stop() = 0;
  virtual ~ReaderInterface() {};
  ReaderInterface();
  ReaderInterface(const ReaderInterface& r) = delete;
  ReaderInterface& operator=(const ReaderInterface& r) = delete;
protected:
  bool isStop;
};

template <class T>
ReaderInterface<T>::ReaderInterface() {
  isStop = false;
}

}
#endif
