workspace(name = "drone")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

http_archive(
    name = "rules_proto",
    sha256 = "602e7161d9195e50246177e7c55b2f39950a9cf7366f74ed5f22fd45750cd208",
    strip_prefix = "rules_proto-97d8af4dc474595af3900dd85cb3a29ad28cc313",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
        "https://github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
    ],
)
http_archive(
    name = "io_bazel_rules_go",
    urls = [
        "https://storage.googleapis.com/bazel-mirror/github.com/bazelbuild/rules_go/releases/download/v0.21.0/rules_go-v0.21.0.tar.gz",
        "https://github.com/bazelbuild/rules_go/releases/download/v0.21.0/rules_go-v0.21.0.tar.gz",
    ],
    sha256 = "b27e55d2dcc9e6020e17614ae6e0374818a3e3ce6f2024036e688ada24110444",
)
http_archive(
    name = "bazel_gazelle",
    urls = [
        "https://storage.googleapis.com/bazel-mirror/github.com/bazelbuild/bazel-gazelle/releases/download/v0.19.1/bazel-gazelle-v0.19.1.tar.gz",
        "https://github.com/bazelbuild/bazel-gazelle/releases/download/v0.19.1/bazel-gazelle-v0.19.1.tar.gz",
    ],
    sha256 = "86c6d481b3f7aedc1d60c1c211c6f76da282ae197c3b3160f54bd3a8f847896f",
)
git_repository(
    name = "com_google_protobuf",
    commit = "09745575a923640154bcf307fba8aedff47f240a",
    remote = "https://github.com/protocolbuffers/protobuf",
    shallow_since = "1558721209 -0700",
)
git_repository(
    name = "rules_cc",
    remote = "https://github.com/bazelbuild/rules_cc/",
    commit = "8774a4decd63f45a636f40a75700c06b7ea9d30a",
    shallow_since = "1579787417 -0800"
)
http_archive(
    name = "com_github_grpc_grpc",
    urls = [
        "https://github.com/grpc/grpc/archive/v1.26.0.tar.gz",
    ],
    strip_prefix = "grpc-1.26.0",
    # sha256 = "2fcb7f1ab160d6fd3aaade64520be3e5446fc4c6fa7ba6581afdc4e26094bd81",
)
http_archive(
    name = "bazel_skylib",
    url = "https://github.com/bazelbuild/bazel-skylib/releases/download/1.0.1/bazel-skylib-1.0.1.tar.gz",
    sha256 = "f1c8360c01fcf276778d3519394805dc2a71a64274a3a0908bc9edff7b5aebc8",
)
http_archive(
    name = "rules_proto_grpc",
    urls = ["https://github.com/rules-proto-grpc/rules_proto_grpc/archive/1.0.2.tar.gz"],
    sha256 = "5f0f2fc0199810c65a2de148a52ba0aff14d631d4e8202f41aff6a9d590a471b",
    strip_prefix = "rules_proto_grpc-1.0.2",
)

git_repository(
    name = "com_github_nelhage_rules_boost",
    commit = "9f9fb8b2f0213989247c9d5c0e814a8451d18d7f",
    remote = "https://github.com/nelhage/rules_boost",
    shallow_since = "1570056263 -0700",
)


load("@bazel_gazelle//:deps.bzl", "gazelle_dependencies", "go_repository")
go_repository(
    name = "org_golang_google_grpc",
    build_file_proto_mode = "disable",
    importpath = "google.golang.org/grpc",
    urls = [
        "https://github.com/grpc/grpc-go/archive/v1.27.0.tar.gz"
    ],
    strip_prefix = "grpc-go-1.27.0",
)
go_repository(
    name = "org_golang_x_net",
    importpath = "golang.org/x/net",
    version = "v0.0.0-20190311183353-d8887717615a",
    sum = "h1:oWX7TPOiFAMXLq8o0ikBYfCJVlRHBcsciT5bXOrH628=",
)
go_repository(
    name = "org_golang_x_text",
    importpath = "golang.org/x/text",
    version = "v0.3.0",
    sum = "h1:g61tztE5qeGQ89tm6NTjjM9VPIm088od1l6aSorWRWg="
)
go_repository(
    name = "com_github_syndtr_goleveldb",
    importpath = "github.com/syndtr/goleveldb",
    commit = "758128399b1df3a87e92df6c26c1d2063da8fabe"
)
go_repository(
    name = "com_github_golang_snappy",
    importpath = "github.com/golang/snappy",
    commit = "ff6b7dc882cf4cfba7ee0b9f7dcc1ac096c554aa"
)


load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
load("@io_bazel_rules_go//go:deps.bzl", "go_rules_dependencies", "go_register_toolchains")
load("@rules_proto_grpc//:repositories.bzl", "rules_proto_grpc_toolchains", "rules_proto_grpc_repos", "bazel_gazelle", "io_bazel_rules_go")
load("@rules_proto_grpc//cpp:repositories.bzl", rules_proto_grpc_cpp_repos="cpp_repos")
load("@rules_proto_grpc//go:repositories.bzl", rules_proto_grpc_go_repos="go_repos")
load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")

bazel_skylib_workspace()
boost_deps()
gazelle_dependencies(go_sdk = "go_sdk")
go_register_toolchains()
go_rules_dependencies()
grpc_deps()
io_bazel_rules_go()
bazel_gazelle()
protobuf_deps()
rules_proto_dependencies()
rules_proto_grpc_cpp_repos()
rules_proto_grpc_go_repos()
rules_proto_grpc_repos()
rules_proto_grpc_toolchains()
rules_proto_toolchains()
