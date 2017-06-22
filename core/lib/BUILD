package(default_visibility = ["//visibility:public"])

cc_library(
  name = "queue",
  hdrs = ["queue.h"],
  deps = ["//core/util:logging"],
)

cc_library(
  name = "thread",
  srcs = ["thread.cc"],
  hdrs = ["thread.h"],
)

cc_library(
  name = "thread_pool",
  srcs = ["thread_pool.cc"],
  hdrs = ["thread_pool.h"],
  deps = [":queue",
          ":thread",
          "//core/util:logging"],
)

cc_library(
  name = "bucket",
  hdrs = ["bucket.h"],
  deps = ["//core/util:logging"],
)

cc_test(
  name = "queue_test",
  srcs = ["queue_test.cc"],
  copts = ["-Iexternal/gtest/include"],
  deps = [":queue",
          ":thread",
          "@gtest//:main"],
)
