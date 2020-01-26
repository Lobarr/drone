load("@rules_proto//proto:defs.bzl", "proto_library")
load("@io_bazel_rules_go//proto:def.bzl", "go_proto_library")

proto_library(
  name = "drone_proto",
  srcs = ["drone.proto"],
  visibility = ["//visibility:public"],
)

cc_proto_library(
  name = "drone_proto_cc",
  deps = [":drone_proto"]
)

go_proto_library(
  name = "drone_proto_go",
  compilers = ["@io_bazel_rules_go//proto:go_grpc"],
  importpath = "github.com/lobarr/drone/core",
  proto = ":drone_proto",
  visibility = ["//visibility:public"],
)
