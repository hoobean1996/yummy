refresh:
	bazel run @hedron_compile_commands//:refresh_all

query:	
	bazel query 'kind(".*_library", //...)'
	bazel query 'kind(".*_binary", //...)'