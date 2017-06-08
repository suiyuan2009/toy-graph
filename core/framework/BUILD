package(default_visibility = ["//visibility:public"])

cc_library(
  name = "framework",
  deps = ["edge",
          "vertex",
          "reader",
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
  name = "graph",
  hdrs = ["graph.h",
          "graph_builder.h"
          ],
  srcs = ["graph.cc"],
  deps = ["//core/platform:types",
          ":vertex"],
)

cc_library(
  name = "graph_builder",
  hdrs = ["graph_builder.h"],
  srcs = ["graph_builder.cc"],
  deps = [":graph"],
)
