#ifndef CORE_UTIL_LOGGING_H
#define CORE_UTIL_LOGGING_H

#include <sstream>

namespace util {

enum LogLevel {
  ERROR, WARNING, INFO, DEBUG
};

class Log {
public:
  ~Log();
  std::ostringstream& Get(LogLevel level = INFO);
private:
  std::ostringstream os;
  LogLevel level;
};

}

#define LOG(level) util::Log().Get(level)

#endif
