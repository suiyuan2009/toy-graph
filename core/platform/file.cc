#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#include "core/platform/file.h"
#include "core/platform/malloc.h"
#include "core/util/logging.h"

namespace platform {

PosixFile::PosixFile(std::string& path) {
  filePath = (char*)Malloc(path.size() * sizeof(char) + 1);
  strcpy(filePath, path.c_str());
}

PosixFile::~PosixFile() {
  if (fd != -1) {
    if (close(fd) != 0) {
      LOG(util::ERROR) << "file " << filePath << " can't be closed!";
    }
  }
  Free(filePath);
}

PosixReadFile::PosixReadFile(std::string& path) : PosixFile(path) {
  fd = open(filePath, O_RDONLY);
  if (fd == -1) {
    LOG(util::ERROR) << "file " << filePath << " can't be opened!";
  } else {
    LOG(util::INFO) << "file " << filePath << " success opened to read.";
  }
}

void PosixReadFile::sequentialRead(void* buffer, int size, int& bytes_read) {
  if (fd == -1) {
    bytes_read = 0;
    return;
  }
  bytes_read = read(fd, buffer, size);
}

PosixAppendWriteFile::PosixAppendWriteFile(std::string& path)
    : PosixFile(path) {
  fd = open(filePath, O_WRONLY | O_CREAT, 0666);
  if (fd == -1) {
    LOG(util::ERROR) << "file " << filePath << " can't be opened!";
  } else {
    LOG(util::INFO) << "file " << path << " success opened to write.";
  }
}

void PosixAppendWriteFile::write(std::string& str) {
  char* tmp = (char*)Malloc(str.size() * sizeof(char) + 1);
  strcpy(tmp, str.c_str());
  int debug;
  if ((debug = ::write(fd, tmp, str.size())) != (int)str.size()) {
    LOG(util::ERROR) << "file " << filePath << " write error!";
  }
  Free(tmp);
}

}
