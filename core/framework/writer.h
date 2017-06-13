#ifndef CORE_FRAMEWORK_WRITER_H
#define CORE_FRAMEWORK_WRITER_H

#include <string>

#include "core/platform/file.h"
#include "core/platform/types.h"

namespace framework {

class WriterInterface {
public:
  virtual ~WriterInterface() {};
  virtual void write(std::string str) = 0;
};

const int writerBufSize = 1024;
class SimpleWriter : public WriterInterface {
public:
  SimpleWriter(std::string& path);
  ~SimpleWriter() override;
  void write(std::string str) override;
private:
  platform::FileInterface* file;
  std::string buf;
};

}
#endif
