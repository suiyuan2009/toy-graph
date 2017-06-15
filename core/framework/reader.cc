#include <string>

#include "core/framework/reader.h"
#include "core/platform/malloc.h"
#include "core/util/logging.h"

namespace framework {

SimpleReader::SimpleReader(std::string filePath, int oes, int bufSize) {
  oneEdgeSize = oes;
  readerBufSize = oes * bufSize;
  file = new platform::PosixReadFile(filePath);
  this->filePath = filePath;
  offset = readerBufSize;
  bufSize = 0;
  buf = platform::Malloc(readerBufSize);
}

SimpleReader::~SimpleReader() {
  platform::Free(buf);
  delete(file);
}

bool SimpleReader::get(EdgeInterface* edge) {
  if (offset >= readerBufSize) {
    file->sequentialRead(buf, readerBufSize, bufSize);
    if (bufSize == 0) return false;
    offset = 0;
  }
  return edge->read(buf, bufSize, offset);
}

void SimpleReader::reset() {
  LOG(util::DEBUG) << "try to close file first";
  delete(file);
  LOG(util::DEBUG) << "delete file, try to reset";
  file = new platform::PosixReadFile(filePath);
  offset = readerBufSize;
  bufSize = 0;
}

}
