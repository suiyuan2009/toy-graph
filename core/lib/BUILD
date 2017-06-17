package(default_visibility = ["//visibility:public"])

cc_library(
  name = "queue",
  hdrs = ["queue.h"],
  deps = ["//core/util:logging"],
)

cc_test(
  name = "queue_test",
  srcs = ["queue_test.cc"],
  copts = ["-Iexternal/gtest/include"],
  deps = [":queue",
          "@gtest//:main"],
)
