include(${PROJECT_SOURCE_DIR}/external/boost/load.cmake)
include(${PROJECT_SOURCE_DIR}/external/brpc/load.cmake)
message(STATUS "PKG_CONFIG_PATH=$ENV{PKG_CONFIG_PATH}")

#find_package(brpc CONFIG REQUIRED PATHS /tmp/cpp-external-lib/brpc NO_DEFAULT_PATH)
pkg_search_module(PKG_BRPC REQUIRED IMPORTED_TARGET libbrpc)

add_executable(sample_brpc src/tutorial/brpc/sample_brpc.cpp)
add_dependencies(sample_brpc brpc boost)
#target_link_libraries(sample_brpc libbrpc)
target_link_libraries(sample_brpc PkgConfig::PKG_BRPC)
#target_link_libraries(sample_brpc brpc)
