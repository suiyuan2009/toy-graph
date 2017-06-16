#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "core/util/commandline.h"

namespace tool {

struct triple {
  uint a, b;
  uint c;
};

void toBinary(std::string inFile, std::string outFile) {
  std::ifstream fin(inFile.c_str());
  std::ofstream fout(outFile.c_str(), std::ios::binary);
  std::string s;
  long long cnt = 0;
  while (getline(fin, s)) {
    if (s[0] < '0' || s[0] > '9') {
      continue;
    }
    std::stringstream ss;
    ss << s;
    triple num;
    ss >> num.a >> num.b >> num.c;
    fout.write((char*)(&num), sizeof(triple));
    cnt ++;
    if ((cnt & ((1 << 20) - 1)) == (1 << 20) -1) {
      std::cout<<cnt<<std::endl;
    }
  }
  std::cout<<cnt<<std::endl;
  fin.close();
  fout.close();
}

}

int main(int argc, char* argv[]) {
  util::CommandLine cmdl = util::CommandLine();
  cmdl.addOption("input").addOption("output");
  cmdl.parseCommandLine(argc, argv);
  std::string inFile = cmdl.getOptVal("input");
  std::string outFile = cmdl.getOptVal("output");
  tool::toBinary(inFile, outFile);
  return 0;
}
