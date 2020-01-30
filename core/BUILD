load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@io_bazel_rules_go//proto:def.bzl", "go_proto_library")
load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")
load("@rules_foreign_cc//tools/build_defs:boost_build.bzl", "boost_build")

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
  name = "rocksdb",
  lib_source = "@rocksdb//:all",
  # cache_entries = {
  #   "CMAKE_BUILD_TYPE": "Release" 
  # },
  cmake_options = ["-Wno-error=dev"],
  visibility = ["//visibility:public"],
)

cmake_external(
  name = "msgpack",
  lib_source = "@msgpack//:all",
  cache_entries = {
    # "MSGPACK_CXX": "ON"
  },
  headers_only = True,
  visibility = ["//visibility:public"],
)

boost_build(
    name = "boost_uuid",
    lib_source = "@boost//:all",
    static_libraries = ["libboost_uuid.a"],
    user_options = ["--with-uuid"],
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


