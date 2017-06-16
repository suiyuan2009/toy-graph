#include "core/util/commandline.h"
#include "core/util/logging.h"

namespace util {

CommandLine& CommandLine::addOption(std::string opt) {
  opts.insert("--" + opt);
  return *this;
}

std::string CommandLine::getOptVal(std::string opt) {
  if (values.find("--" + opt) == values.end()) {
    LOG(ERROR) << "can't find value of " << opt;
  }
  return values["--" + opt];
}

void CommandLine::parseCommandLine(int argc, char* argv[]) {
  for (int i = 1; i + 1 < argc; i += 2) {
    if (opts.find(std::string(argv[i])) == opts.end()) {
      continue;
    }
    LOG(DEBUG) << std::string(argv[i]) << ", value is: "
               << std::string(argv[i + 1]);
    values[std::string(argv[i])] = std::string(argv[i + 1]);
  }
}

}
