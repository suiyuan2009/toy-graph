package(default_visibility = ["//core:__subpackages__"])

cc_library(
  name = "malloc",
  hdrs = ["malloc.h"],
)

cc_library(
  name = "types",
  hdrs = ["types.h"],
)

cc_library(
  name = "file",
  srcs = ["file.cc"],
  hdrs = ["file.h"],
  deps = [":malloc"],
)
