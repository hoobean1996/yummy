cc_binary(
    name = "cettry_server",
    srcs = ["cetty_server.cc"],
    copts = [],
    deps = [
        "//cc/src/cetty",
        "//cc/src/core",
    ],
)

cc_binary(
    name = "cetty_client",
    srcs = ["cetty_client.cc"],
    deps = [
        "//cc/src/cetty",
        "//cc/src/core",
    ],
)

cc_binary(
    name = "biggrep",
    srcs = ["biggrep.cc"],
    copts = ["-std=c++2a"],
    deps = [
        "//cc/src/core",
        "@com_github_gflags_gflags//:gflags",
        "@com_github_google_glog//:glog",
    ],
)

cc_binary(
    name = "co",
    srcs = ["coapp.cc"],
    copts = [],
    deps = [
        "//cc/src/co",
        "//cc/src/core",
        "@com_github_google_glog//:glog",
    ],
)

cc_binary(
    name = "lisp",
    srcs = ["lisp.cc"],
    copts = [],
    deps = [],
)
