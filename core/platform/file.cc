#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#include "core/platform/file.h"
#include "core/platform/malloc.cc"

namespace platform {

PosixFile::PosixFile(std::string& path) {
  filePath = (char*)Malloc(path.size());
  strcpy(filePath, path.c_str());
  fd = open(filePath, O_RDONLY);
  if (fd == -1) {
    //do something.
  }
}

PosixFile::~PosixFile() {
  if (fd != -1) {
    if (close(fd) != 0) {
      //do something.
    }
  }
  Free(filePath);
}

void PosixFile::sequentialRead(char* buffer, int size, int& bytes_read) {
  if (fd == -1) {
    bytes_read = 0;
    return;
  }
  bytes_read = read(fd, buffer, size);
}

}
