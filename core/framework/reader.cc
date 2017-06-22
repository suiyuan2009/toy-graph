#include <string>
#include <vector>

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

bool SimpleReader::readInToEdge(std::vector<EdgeInterface*>& edges, int& num) {
  int size = edges.size();
  if (size == 0) {
    LOG(util::ERROR)
        << "edges passed to readInToEdge size must be more than 0.";
    return false;
  }
  num = 0;
  while (num < size && !readInToEdge(edges[num])) {
    num++;
  }
  return num > 0;
}

void SimpleReader::reset() {
  delete(file);
  file = new platform::PosixReadFile(filePath);
  offset = readerBufSize;
  bufSize = 0;
}

}
