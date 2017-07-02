package(default_visibility = ["//visibility:public"])

cc_library(
name = "framework",
deps = ["async_reader",
        "edge",
        "vertex",
        "reader",
        "simple_reader",
        "writer",
        "graph",
        "graph_builder",
        "message"],
)


cc_library(
  name = "message",
  hdrs = ["message.h"],
)

cc_library(
  name = "edge",
  hdrs = ["edge.h"],
  deps = [":graph"],
)

cc_library(
  name = "vertex",
  hdrs = ["vertex.h"],
  deps = [":message"],
)

cc_library(
  name = "reader",
  hdrs = ["reader.h"],
  deps = ["//core/lib:bucket"],
)

cc_library(
  name = "simple_reader",
  hdrs = ["simple_reader.h"],
  deps = [":reader",
          "//core/platform:file",
          "//core/platform:malloc",
          "//core/util:logging"],
)

cc_library(
  name = "async_reader",
  hdrs = ["async_reader.h"],
  linkopts = ["-lpthread"],
  deps = [":simple_reader",
          "//core/lib:queue",
          "//core/lib:thread"],
)

cc_library(
  name = "writer",
  hdrs = ["writer.h"],
  srcs = ["writer.cc"],
  deps = ["//core/platform:file",
          "//core/platform:types",
          "//core/util:logging"],
)

cc_library(
  name = "graph",
  hdrs = ["graph.h"],
  srcs = ["graph.cc"],
  deps = ["//core/platform:types",
          ":vertex",
          "//core/platform:malloc",
          "//core/util:logging"],
)

cc_library(
  name = "graph_builder",
  hdrs = ["graph_builder.h"],
  deps = [":graph",
          "//core/util:logging"],
)
