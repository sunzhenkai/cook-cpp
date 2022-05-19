# versions
SET(SEASTAR_VERSION 20.05.0)

# includes
include(${PROJECT_SOURCE_DIR}/external/utils.cmake)
include(${PROJECT_SOURCE_DIR}/external/boost/check.cmake)
include(${PROJECT_SOURCE_DIR}/external/openssl/check.cmake)
include(${PROJECT_SOURCE_DIR}/external/curl/check.cmake)
include(${PROJECT_SOURCE_DIR}/external/seastar/check.cmake)

message(STATUS "CMakePrefixPath info ${CMAKE_PREFIX_PATH}")
message(STATUS "Boost_LIBRARIES info ${Boost_LIBRARIES}")
message(STATUS "libraries info yaml-cpp=${YAML_CPP_LIBRARIES}, fmt=${fmt_DIR}, "
        "openssl=${OPENSSL_ROOT_DIR}")

include_directories(${SRC_INCLUDE_DIR})


file(GLOB SOURCE_FILES src/*.cpp)
set(EXTRA_LIB
        seastar::seastar
        fmt::fmt
        protobuf::protobuf
        cryptopp::cryptopp
        ${YAML_CPP_LIBRARIES}
        ${Boost_LIBRARIES}
        pthread
        openssl::ssl
        openssl::crypto
        curl::curl
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

add_executable(curl_sample src/tutorial/curl/curl_sample.cpp)
target_link_libraries(curl_sample ${EXTRA_LIB})