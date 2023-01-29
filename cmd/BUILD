

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
  name = "biggrep",
  srcs = ["biggrep.cc"],
  copts = ["-std=c++17"],
  deps = ["@com_github_gflags_gflags//:gflags", "@com_github_google_glog//:glog"],
)

cc_binary(
  name = "epoll",
  srcs = ["epoll.cc"],
  copts = [],
  deps = [],
)

cc_binary(
  name = "daytimeserver",
  srcs = ["daytime_server.cc"],
  copts = [],
  deps = ["@com_github_google_glog//:glog"],
)
