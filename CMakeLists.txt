cmake_minimum_required(VERSION 3.16)
project(cook-cpp)

# versions
SET(SEASTAR_VERSION 20.05.0)

# set symbols
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS "-w -g -pthread -std=gnu++17 -fno-omit-frame-pointer")
SET(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS})
SET(CMAKE_CXX_FLAGS_RELEASE "-w -g -pthread -O2 -std=gnu++17 -fno-omit-frame-pointer")
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_definitions(-Wall -g)
set(SRC_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

message(STATUS "SRC_INCLUDE_DIR = ${SRC_INCLUDE_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR = ${CMAKE_CURRENT_LIST_DIR}")

# includes
include(${CMAKE_CURRENT_LIST_DIR}/external/utils.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/external/boost/check.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/external/seastar/check.cmake)

message(STATUS "CMakePrefixPath info ${CMAKE_PREFIX_PATH}")
message(STATUS "Boost_LIBRARIES info ${Boost_LIBRARIES}")
message(STATUS "libraries info yaml-cpp=${YAML_CPP_LIBRARIES}, fmt=${fmt_DIR}, "
        "openssl=${OPENSSL_ROOT_DIR}")

include_directories(${SRC_INCLUDE_DIR})


file(GLOB SOURCE_FILES src/*.cpp)
set(EXTRA_LIB
        Seastar::seastar
        fmt::fmt
        protobuf::libprotobuf
        cryptopp::cryptopp
        ${YAML_CPP_LIBRARIES}
        ${Boost_LIBRARIES}
        pthread
        dl
        z)

# executables
add_executable(hello src/sample/hello.cpp)

add_executable(fmt src/sample/fmt.cpp)
target_link_libraries(fmt fmt::fmt)

add_executable(boost src/sample/boost.cpp)
target_link_libraries(boost)

add_executable(sample src/tutorial/sample.cpp)
target_link_libraries(sample ${EXTRA_LIB})

add_executable(smp src/tutorial/smp.cpp)
target_link_libraries(smp ${EXTRA_LIB})