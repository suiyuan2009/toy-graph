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

bool SimpleReader::readInToEdge(EdgeInterface* edge) {
  if (offset >= readerBufSize) {
    file->sequentialRead(buf, readerBufSize, bufSize);
    if (bufSize == 0) return false;
    offset = 0;
  }
  if (offset + oneEdgeSize > bufSize) {
    return false;
  }
  edge->read((char*)buf + offset);
  offset += oneEdgeSize;
  return true;
}

void SimpleReader::reset() {
  delete(file);
  file = new platform::PosixReadFile(filePath);
  offset = readerBufSize;
  bufSize = 0;
}

}
