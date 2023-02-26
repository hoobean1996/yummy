cc_test(
    name = "hello_test",
    size = "small",
    srcs = ["getpid_test.cc"],
    deps = [
        "@com_github_google_glog//:glog",
        "@com_google_googletest//:gtest_main",
    ],
)

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
    name = "copy",
    srcs = ["copy.cc"],
    deps = [
        "@com_github_google_glog//:glog",
    ],
)

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
    name = "tee",
    srcs = ["tee.cc"],
    copts = [],
    deps = ["@com_github_google_glog//:glog"],
)

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
    name = "readv",
    srcs = ["readv.cc"],
    copts = [],
    deps = ["@com_github_google_glog//:glog"],
)
# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
    name = "jmp",
    srcs = ["jmp.cc"],
    copts = [],
    deps = [],
)