package(default_visibility = ["//visibility:public"])

cc_library(
  name = "commandline",
  hdrs = ["commandline.h"],
  srcs = ["commandline.cc"],
  deps = [":logging"],
)

cc_library(
  name = "logging",
  hdrs = ["logging.h"],
  srcs = ["logging.cc"],
)

cc_test(
  name = "commandline_test",
  srcs = ["commandline_test.cc"],
  copts = ["-Iexternal/gtest/include"],
  deps = ["@gtest//:main",
          ":commandline"],
)
