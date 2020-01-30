load("@io_bazel_rules_go//go:def.bzl", "go_binary", "go_library")



go_binary(
    name = "drone_db_service",
    embed = [":drone_db_service_library"],
    linkmode = "c-shared",
    visibility = ["//visibility:public"],
)
go_library(
    name = "drone_db_service_library",
    srcs = ["dbService.go"],
    cgo = True,
    importpath = "github.com/Lobarr/drone/services/db",
    visibility = ["//visibility:public"],
    deps = ["@com_github_syndtr_goleveldb//leveldb:go_default_library"],
)
