#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#include "core/platform/file.h"
#include "core/platform/malloc.h"
#include "core/util/logging.h"

namespace platform {

PosixFile::PosixFile(std::string& path) {
  filePath = (char*)Malloc(path.size());
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
  fd = open(filePath, O_WRONLY | O_APPEND | O_CREAT);
  if (fd == -1) {
    LOG(util::ERROR) << "file " << filePath << " can't be opened!";
  }
}

void PosixAppendWriteFile::write(std::string& str) {
  char* tmp = (char*)Malloc(str.size());
  strcpy(tmp, str.c_str());
  if (::write(fd, tmp, str.size()) == -1) {
    LOG(util::ERROR) << "file " << filePath << " can't append write!";
  }
}

}
