load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@io_bazel_rules_go//proto:def.bzl", "go_proto_library")

proto_library(
    name = "drone_proto",
    srcs = ["drone.proto"],
    visibility = ["//visibility:public"],
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
    ],
    deps = [
        ":drone_proto_cc",
        ":drone_db_service_cc",
        "@boost//:uuid",
    ],
    visibility = ["//visibility:public"],
)

cc_import(
    name = "drone_db_service_cc",
    hdrs = ["services/db/drone_db_service.h"],
    shared_library = "//services/db:libdrone_db_service.so",
)

cc_binary(
    name = "drone_daemon",
    deps = [":drone_daemon_library"],
)
