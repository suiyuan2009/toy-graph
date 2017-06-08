
#include <queue>
#include "core/framework/edge.h"
#include "core/platform/file.h"

namespace framework {

class ReaderInterface {
public:
  virtual bool get(EdgeInterface& edge) = 0;
  virtual ~ReaderInterface() = 0;
};

const int readerBufSize = 100;
class SimpleReader : public ReaderInterface {
public:
  SimpleReader() = delete;
  ~SimpleReader();
  SimpleReader(const SimpleReader& r) = delete;
  SimpleReader& operator=(const SimpleReader& r) = delete;
  SimpleReader(platform::FileInterface* f);
  bool get(EdgeInterface& edge);
private:
  platform::FileInterface* file;
  char* buf;
  int offset, bufSize;
};

}
