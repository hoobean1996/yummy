# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "fs",
    srcs = ["fs.cc"],
    hdrs = ["fs.h"],
    deps = ["@com_github_google_glog//:glog"],
)

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
    name = "vfs",
    srcs = [
        "main.cc",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//cc/src/fs",
        "@com_github_google_glog//:glog",
    ],
)
