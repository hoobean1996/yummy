# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
  name = "cetty",
  srcs = ["channel.cc", "poller.cc", "event_loop.cc", "acceptor.cc", "buffer.cc", "connection.cc", "server.cc"],
  hdrs = ["channel.h", "poller.h", "event_loop.h", "acceptor.h", "buffer.h", "connection.h", "server.h"],
  deps = [
    "@com_github_google_glog//:glog"
  ],
  visibility = ["//visibility:public"],
)