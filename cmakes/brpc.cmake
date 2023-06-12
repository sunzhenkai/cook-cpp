include(${PROJECT_SOURCE_DIR}/external/boost/load.cmake)
include(${PROJECT_SOURCE_DIR}/external/brpc/load.cmake)
message(STATUS "PKG_CONFIG_PATH=$ENV{PKG_CONFIG_PATH}")
message(STATUS "CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")

#find_package(brpc CONFIG REQUIRED PATHS /tmp/cpp-external-lib/brpc NO_DEFAULT_PATH)
#pkg_search_module(PKG_BRPC REQUIRED IMPORTED_TARGET brpc)

add_executable(sample_brpc src/tutorial/brpc/sample_brpc.cpp)
add_dependencies(sample_brpc brpc_lib boost_lib)
target_link_libraries(sample_brpc PUBLIC PkgConfig::PKG_BRPC PkgConfig::PKG_PROTOBUF PkgConfig::PKG_GFLAGS)
#target_link_libraries(sample_brpc PUBLIC brpc protobuf gflags)
