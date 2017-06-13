#include <sstream>
#include <string>
#include <time.h>

#include "core/util/logging.h"

namespace util {

char* nowTime() {
  time_t now = time(0);
  return ctime(&now);
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
  os << "- " << nowTime();
  os << " " << toString(level) << ": ";
  return os;
}

Log::~Log() {
  os << std::endl;
  fprintf(stderr, "%s", os.str().c_str());
  fflush(stderr);
}

}
