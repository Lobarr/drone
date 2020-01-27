load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@io_bazel_rules_go//proto:def.bzl", "go_proto_library")
load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

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

cmake_external(
  name = "leveldb",
  lib_source = "@leveldb//:all",
  cache_entries = {
    "CMAKE_BUILD_TYPE": "Release" 
  },
  visibility = ["//visibility:public"],
)

cmake_external(
  name = "json",
  lib_source = "@json//:all",
  visibility = ["//visibility:public"],
)

cc_binary(
  name = "drone_daemon",
  srcs = ["main.cc", "fileController.hpp"],
  deps = [
    ":drone_proto_cc",
    ":leveldb"
  ],
  # data = [
  #   ":tmp/dronedb"
  # ]
)


