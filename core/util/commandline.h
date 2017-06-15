#ifndef CORE_UTIL_COMMANDLINE_H
#define CORE_UTIL_COMMANDLINE_H

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace util {

class CommandLine {
public:
  CommandLine* addOption(std::string opt);
  std::string getOptVal(std::string opt);
  void parseCommandLine(int argc, char* argv[]);
private:
  std::unordered_set<std::string> opts;
  std::unordered_map<std::string, std::string> values;
};

}
#endif
