#ifndef CORE_FRAMEWORK_READER_H
#define CORE_FRAMEWORK_READER_H

#include <queue>
#include <string>

#include "core/framework/edge.h"
#include "core/platform/file.h"

namespace framework {

class ReaderInterface {
public:
  virtual bool readInToEdge(EdgeInterface* edge) = 0;
  virtual void reset() = 0;
  virtual ~ReaderInterface() {};
};

class SimpleReader : public ReaderInterface {
public:
  SimpleReader() = delete;
  ~SimpleReader() override;
  SimpleReader(const SimpleReader& r) = delete;
  SimpleReader& operator=(const SimpleReader& r) = delete;
  SimpleReader(std::string filePath, int oes, int bufSize = 100);
  bool readInToEdge(EdgeInterface* edge) override;
  void reset() override;
private:
  platform::FileInterface* file;
  void* buf;
  int readerBufSize; // size of buf
  int offset; // already read at offset
  int bufSize; // data size in buf
  int oneEdgeSize;
  std::string filePath;
};

}
#endif
