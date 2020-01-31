load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@io_bazel_rules_go//proto:def.bzl", "go_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")


proto_library(
    name = "drone_proto",
    srcs = ["drone.proto"],
    visibility = ["//visibility:public"],
)

cc_grpc_library(
    name = "drone_proto_grpc",
    srcs = ["drone.proto"],
    deps = [":drone_proto_cc"],
)

cc_proto_library(
    name = "drone_proto_cc",
    deps = [":drone_proto"],
    visibility = ["//visibility:public"],
)

go_proto_library(
    name = "drone_proto_go",
    compilers = ["@io_bazel_rules_go//proto:go_grpc"],
    importpath = "github.com/lobarr/drone/core",
    proto = ":drone_proto",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "drone_daemon_library",
    srcs = [
        "main.cc",
        "fileController.cc",
        "fileContainer.cc",
        "serializeUtil.cc",
    ],
    hdrs = [
        "fileController.hpp",
        "fileContainer.hpp",
        "serializeUtil.hpp",
        "constants.hpp",
    ],
    deps = [
        ":drone_proto_cc",
        ":drone_proto_grpc",
        "@boost//:uuid",
        "@boost//:thread",
        "//services/db:drone_db_service.cc",
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "drone_daemon",
    deps = [
        ":drone_daemon_library",
    ],
)
