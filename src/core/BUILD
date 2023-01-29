# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
  name = "core",
  srcs = ["core.cc", "core_socket.cc"],
  hdrs = ["core.h", "core_socket.h"],
  deps = ["@com_github_google_glog//:glog"],
  visibility = ["//visibility:public"],
)