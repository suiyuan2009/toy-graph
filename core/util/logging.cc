#include <sstream>
#include <string>
#include <time.h>

#include "core/util/logging.h"

namespace util {

std::string nowTime() {
  time_t rawtime;
  char buffer[20];
  time(&rawtime);
  struct tm * timeinfo = localtime(&rawtime);
  strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", timeinfo);
  return std::string(buffer);
}

std::string toString(LogLevel l) {
  switch (l) {
    case ERROR : return "ERROR";
    case INFO : return "INFO";
    case DEBUG : return "DEBUG";
    case WARNING : return "WARNING";
    default : return "DEBUG";
  }
}

std::ostringstream& Log::Get(LogLevel _level) {
  level = _level;
  os << nowTime();
  os << " " << toString(level) << ": ";
  return os;
}

Log::~Log() {
  //os << std::endl;
  fprintf(stderr, "%s", os.str().c_str());
  fflush(stderr);
}

}
