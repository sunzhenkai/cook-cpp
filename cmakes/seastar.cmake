# includes
include(${PROJECT_SOURCE_DIR}/external/utils.cmake)
include(${PROJECT_SOURCE_DIR}/external/boost/check.cmake)
include(${PROJECT_SOURCE_DIR}/external/openssl/check.cmake)
include(${PROJECT_SOURCE_DIR}/external/curl/check.cmake)
include(${PROJECT_SOURCE_DIR}/external/seastar/check.cmake)
include(${PROJECT_SOURCE_DIR}/external/spdlog/check.cmake)

include_directories(${SRC_INCLUDE_DIR})

set(EXTRA_LIB
        seastar::seastar
        fmt::fmt
        protobuf::protobuf
        spdlog::spdlog
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
add_executable(seastar_socket src/sample/seastar/seastar_socket.cpp)
target_link_libraries(seastar_socket ${EXTRA_LIB})