#ifndef CORE_PLATFORM_FILE_H
#define CORE_PLATFORM_FILE_H
#include <string>

namespace platform {

class FileInterface {
public:
  virtual ~FileInterface() = 0;
  virtual void sequentialRead(char* buffer, int size, int& bytes_read) = 0;
};

class PosixFile : public FileInterface {
public:
  PosixFile() = delete;
  PosixFile(const PosixFile& pf) = delete;
  PosixFile & operator=(const PosixFile& pf) = delete;
  PosixFile(std::string& path);
  ~PosixFile();
private:
  char* filePath;
  int fd;
  void sequentialRead(char* buffer, int size, int& bytes_read) override;
};

}
#endif
