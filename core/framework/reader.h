#ifndef CORE_FRAMEWORK_READER_H
#define CORE_FRAMEWORK_READER_H

#include <queue>
#include <string>
#include <vector>

#include "core/framework/edge.h"
#include "core/platform/file.h"

namespace framework {

class ReaderInterface {
public:
  virtual bool readInToEdge(EdgeInterface* edge) = 0;
  virtual bool readInToEdge(std::vector<EdgeInterface*>& edges, int& size) = 0;
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

class SimpleReader : public ReaderInterface {
public:
  ~SimpleReader() override;
  SimpleReader(std::string filePath, int oneEdgeSize, int bufSize = 100);
  virtual bool readInToEdge(EdgeInterface* edge) override;
  virtual bool readInToEdge(std::vector<EdgeInterface*>& edges,
      int& size) override;
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

}
#endif
