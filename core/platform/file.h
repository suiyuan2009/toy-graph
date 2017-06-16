#ifndef CORE_PLATFORM_FILE_H
#define CORE_PLATFORM_FILE_H
#include <string>

namespace platform {

class FileInterface {
public:
  virtual ~FileInterface() {};
  virtual void sequentialRead(void* buffer, int size, int& bytes_read) = 0;
  virtual void write(std::string& str) = 0;
};

class PosixFile : public FileInterface {
public:
  PosixFile() = delete;
  PosixFile(const PosixFile& pf) = delete;
  PosixFile & operator=(const PosixFile& pf) = delete;
  PosixFile(std::string& path);
  virtual ~PosixFile() override;
  virtual void sequentialRead(void*, int, int&) override {};
  virtual void write(std::string&) override {};
protected:
  char* filePath;
  int fd;
};

class PosixReadFile : public PosixFile {
public:
  PosixReadFile(std::string& path);
  void sequentialRead(void* buffer, int size, int& bytes_read) override;
};

class PosixAppendWriteFile : public PosixFile {
public:
  PosixAppendWriteFile(std::string& path);
  void write(std::string& str) override;
};

}
#endif
