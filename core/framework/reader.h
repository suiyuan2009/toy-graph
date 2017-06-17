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
  ReaderInterface() = delete;
  ReaderInterface(const ReaderInterface& r) = delete;
  ReaderInterface& operator=(const ReaderInterface& r) = delete;
};

class SimpleReader : public ReaderInterface {
public:
  ~SimpleReader() override;
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
