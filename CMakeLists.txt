cmake_minimum_required(VERSION 3.24)
project(cook-cpp)

message(STATUS "compile with ${CMAKE_CXX_COMPILER}, version ${CMAKE_CXX_COMPILER_VERSION}")
# set symbols
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS "-w -g -pthread -std=gnu++17 -fno-omit-frame-pointer")
SET(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS})
SET(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS})
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_INSTALL_PREFIX /tmp/cook-cpp)

add_definitions(-Wall -g)
set(SRC_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

message(STATUS "SRC_INCLUDE_DIR = ${SRC_INCLUDE_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR = ${CMAKE_CURRENT_LIST_DIR}")

# vcpkg
include(vcpkg/vcpkg.cmake)

include(cmakes/utils.cmake)

# cooking targets
#include(cmakes/basic.cmake)
#include(cmakes/mongo.cmake)
#include(cmakes/default.cmake)
#include(cmakes/fmt.cmake)
#include(cmakes/sample.cmake)
#include(cmakes/thread.cmake)
#include(cmakes/pb.cmake)
#include(cmakes/fbs.cmake)
#include(cmakes/gperftools.cmake)
#include(cmakes/seastar.cmake)
#include(cmakes/brpc.cmake)
#include(external/boost/load.cmake)
#include(cmakes/grpc.cmake)
