#include <string>

#include "core/framework/writer.h"
#include "core/platform/malloc.h"
#include "core/util/logging.h"

namespace framework {

SimpleWriter::~SimpleWriter() {
  if (buf.size() != 0) {
    file->write(buf);
  }
  delete(file);
}

SimpleWriter::SimpleWriter(std::string& path) {
  file = new platform::PosixAppendWriteFile(path);
  buf.clear();
}

void SimpleWriter::write(std::string str) {
  //LOG(util::DEBUG) << "writer info: " << str;
  buf += str;
  if (buf.size() > writerBufSize) {
    file->write(buf);
    buf.clear();
  }
}

}
