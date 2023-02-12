
cc_binary(
  name = "daytime",
  srcs = ["daytime_client.cc"],
  copts = [],
  deps = [
    "//cc/src/core:core"
  ],
)

cc_binary(
  name = "yum",
  srcs = ["cetty_server.cc"],
  copts = [],
  deps = ["//cc/src/cetty:cetty", "//cc/src/core:core"],
)

cc_binary(
  name = "biggrep",
  srcs = ["biggrep.cc"],
  copts = ["-std=c++2a"],
  deps = [
    "@com_github_gflags_gflags//:gflags",
    "@com_github_google_glog//:glog",
    "//cc/src/core:core"
  ],
)

cc_binary(
  name = "co",
  srcs = ["coapp.cc"],
  copts = [],
  deps = ["//cc/src/co:co", "//cc/src/core:core","@com_github_google_glog//:glog",],
)



cc_binary(
  name = "lisp",
  srcs = ["lisp.cc"],
  copts = [],
  deps = []
)

cc_binary(
  name = "s",
  srcs = ["s.cc"],
  copts = [],
  linkopts=["-lpthread"],
  deps = []
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
