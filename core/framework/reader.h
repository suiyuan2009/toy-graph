#ifndef CORE_FRAMEWORK_READER_H
#define CORE_FRAMEWORK_READER_H

#include <queue>
#include <string>

#include "core/framework/edge.h"
#include "core/platform/file.h"

namespace framework {

const int readerBufSize = 100;

class ReaderInterface {
public:
  virtual bool get(EdgeInterface* edge) = 0;
  virtual ~ReaderInterface() {};
};

class SimpleReader : public ReaderInterface {
public:
  SimpleReader() = delete;
  ~SimpleReader() override;
  SimpleReader(const SimpleReader& r) = delete;
  SimpleReader& operator=(const SimpleReader& r) = delete;
  SimpleReader(std::string filePath);
  bool get(EdgeInterface* edge) override;
private:
  platform::FileInterface* file;
  char* buf;
  int offset, bufSize;
};

}
#endif