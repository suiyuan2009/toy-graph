#ifndef CORE_LIB_BUCKET_H
#define CORE_LIB_BUCKET_H

#include <vector>

#include "core/util/logging.h"

namespace lib {

// this class allows copy constructor.
template <class T>
class Bucket {
public:
  Bucket() {bucketSize = 0;}
  Bucket(int bucketSize);
  void push(T& t);
  T& operator[](int idx);
  bool full();
  bool empty();
  void clear();
  int size();
  void setSize(int size);
private:
  std::vector<T> buf;
  int bucketSize, itemNum;
};

template <class T>
Bucket<T>::Bucket(int bs) {
  if (bs <= 0) {
    LOG(util::ERROR) << "Bucket Size must be more than 0!";
  }
  bucketSize = bs;
  itemNum = 0;
  buf = std::vector<T>(bucketSize);
}

template <class T>
void Bucket<T>::push(T& t) {
  if (itemNum == bucketSize) {
    LOG(util::ERROR) << "bucket is full!";
  }
  //LOG(util::DEBUG) << "something pushed to bucket.";
  buf[itemNum++] = t;
}

template <class T>
bool Bucket<T>::full() {
  return itemNum == bucketSize;
}

template <class T>
bool Bucket<T>::empty() {
  return itemNum == 0;
}

template <class T>
void Bucket<T>::clear() {
  itemNum = 0;
}

template <class T>
int Bucket<T>::size() {
  return itemNum;
}

template <class T>
T& Bucket<T>::operator[](int idx) {
  return buf[idx];
}

template <class T>
void Bucket<T>::setSize(int size) {
  itemNum = size;
}

}
#endif
