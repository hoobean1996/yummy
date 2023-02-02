cc_binary(
  name = "daytime",
  srcs = ["daytime_client.cc"],
  copts = [],
  deps = [
    "//src/core:core"
  ],
)

cc_binary(
  name = "yum",
  srcs = ["cetty_server.cc"],
  copts = [],
  deps = ["//src/cetty:cetty", "//src/core:core"],
)

cc_binary(
  name = "biggrep",
  srcs = ["biggrep.cc"],
  copts = ["-std=c++17"],
  deps = [
    "@com_github_gflags_gflags//:gflags",
    "@com_github_google_glog//:glog",
    "//src/core:core"
  ],
)

cc_binary(
  name = "co",
  srcs = ["coapp.cc"],
  copts = [],
  deps = ["//src/co:co", "//src/core:core","@com_github_google_glog//:glog",],
)