load("@io_bazel_rules_go//go:def.bzl", "go_binary")

load("@io_bazel_rules_go//go:def.bzl", "go_test")


load("@io_bazel_rules_go//go:def.bzl", "go_library")


go_test(
  name = "parser_test",
  srcs = ["token_test.go", "parser_test.go", "ast_test.go"],
  deps = ["//go/parser:parser"],
)


go_library(
  name = "parser",
  srcs = ["lexer.go", "token.go", "parser.go", "ast.go"],
  importpath = "github.com/yummy/go/parser",
  visibility = ["//visibility:public"],
)
