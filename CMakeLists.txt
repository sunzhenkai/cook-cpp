cmake_minimum_required(VERSION 3.24)
# or -DCMAKE_TOOLCHAIN_FILE=/home/wii/.local/vcpkg/scripts/buildsystems/vcpkg.cmake
# vcpkg
include(vcpkg/CMakeLists.txt)
project(cook-cpp)

message(STATUS "compile with ${CMAKE_CXX_COMPILER}, version ${CMAKE_CXX_COMPILER_VERSION} ${CMAKE_CURRENT_SOURCE_DIR}")
# set symbols
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#SET(CMAKE_CXX_FLAGS "-w -g -pthread -std=gnu++17 -fno-omit-frame-pointer")
SET(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS})
SET(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS})
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_INSTALL_PREFIX /tmp/cook-cpp)

add_definitions(-Wall -g)
set(SRC_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
include_directories(${SRC_INCLUDE_DIR})
include_directories(${SRC_DIR})

set(COMMON_SRCS)
aux_source_directory(src/utils COMMON_SRCS)

message(STATUS "SRC_INCLUDE_DIR=${SRC_INCLUDE_DIR}, SRC_DIR=${SRC_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR = ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "COMMON_SRCS = ${COMMON_SRCS}")

#AddLibrary(boost VERSION 1.82.0)
#AddLibrary(fmt VERSION 9.1.0)
#include(cmakes/utils.cmake)

include(cmakes/cassandra.cmake)
# cooking targets
include(cmakes/basic.cmake)
include(cmakes/socket.cmake)
#include(cmakes/arrow.cmake)
include(cmakes/study.cmake)
#include(cmakes/mongo.cmake)
#include(cmakes/default.cmake)
include(cmakes/fmt.cmake)
#include(cmakes/spdlog.cmake)
#include(cmakes/sample.cmake)
include(cmakes/thread.cmake)
#include(cmakes/pb.cmake)
#include(cmakes/fbs.cmake)
#include(cmakes/gperftools.cmake)
#include(cmakes/seastar.cmake)
#include(cmakes/brpc.cmake)
#include(cmakes/seastar.cmake)
#include(cmakes/brpc.cmake)
#include(cmakes/grpc.cmake)
include(cmakes/boost.cmake)
#include(cmakes/rapidjson.cmake)
#include(cmakes/gtests.cmake)

set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION ${Ppconsul_VERSION}
        SOVERSION "${Ppconsul_VERSION_MAJOR}.${Ppconsul_VERSION_MINOR}"
        COMPILE_PDB_NAME ${PROJECT_NAME}
        COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        FOLDER ${PROJECT_NAME}
)