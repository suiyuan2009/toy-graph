package(default_visibility = ["//visibility:public"])

cc_library(
  name = "framework",
  deps = ["edge",
          "vertex",
          "reader",
          "writer",
          "graph",
          "graph_builder",
          "message",
          ],
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
  srcs = ["reader.cc"],
  deps = [":edge",
          ":vertex",
          "//core/platform:types",
          "//core/platform:file",
          ],
)

cc_library(
  name = "writer",
  hdrs = ["writer.h"],
  srcs = ["writer.cc"],
  deps = ["//core/platform:file",
          "//core/platform:types"],
)

cc_library(
  name = "graph",
  hdrs = ["graph.h"],
  srcs = ["graph.cc"],
  deps = ["//core/platform:types",
          ":vertex",
          "//core/platform:malloc"],
)

cc_library(
  name = "graph_builder",
  hdrs = ["graph_builder.h"],
  deps = [":graph",
          "//core/util:logging"],
)
