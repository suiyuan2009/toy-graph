#include "core/util/commandline.h"
#include "gtest/gtest.h"
#include <string.h>

char* convertString2Charp(std::string s) {
  char *cstr = new char[s.length() + 1];
  strcpy(cstr, s.c_str());
  return cstr;
}

TEST(CommandLine, JustATest) {
  util::CommandLine* cmdl = new util::CommandLine();
  cmdl->addOption("opt1")->addOption("opt2");
  int argc = 5;
  char* argv[] = {convertString2Charp("gtest"),
                  convertString2Charp("--opt1"),
                  convertString2Charp("abc"),
                  convertString2Charp("--opt2"),
                  convertString2Charp("bcd")};
  cmdl->parseCommandLine(argc, argv);
  EXPECT_EQ(cmdl->getOptVal("opt1"), "abc");
  EXPECT_EQ(cmdl->getOptVal("opt2"), "bcd");
}
