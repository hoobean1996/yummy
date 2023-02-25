# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "cetty",
    srcs = [
        "acceptor.cc",
        "buffer.cc",
        "channel.cc",
        "connection.cc",
        "event_loop.cc",
        "poller.cc",
        "server.cc",
        "tcp_server.cc",
        "addr.cc",
        "client.cc",
    ],
    hdrs = [
        "acceptor.h",
        "buffer.h",
        "channel.h",
        "connection.h",
        "event_loop.h",
        "poller.h",
        "server.h",
        "tcp_server.h",
        "addr.h",
        "client.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@com_github_google_glog//:glog",
    ],
)
