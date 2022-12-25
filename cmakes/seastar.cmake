# includes
include(${PROJECT_SOURCE_DIR}/external/boost/check.cmake)
include(${PROJECT_SOURCE_DIR}/external/openssl/check.cmake)
include(${PROJECT_SOURCE_DIR}/external/curl/check.cmake)
include(${PROJECT_SOURCE_DIR}/external/seastar/check.cmake)
include(${PROJECT_SOURCE_DIR}/external/spdlog/check.cmake)
include(${PROJECT_SOURCE_DIR}/external/fmt/check.cmake)

include_directories(${SRC_INCLUDE_DIR})

set(EXTRA_LIB seastar::seastar
        fmt::fmt
        protobuf::protobuf
        spdlog::spdlogd
        cryptopp::cryptopp
        yaml-cpp::yaml-cpp
        ${Boost_LIBRARIES}
        pthread
        stdc++fs
        openssl::ssl
        openssl::crypto
        curl::curl
        dl
        z)

# executables
set(TARGETS socket metric future server sample)
add_definitions(-DSEASTAR_SCHEDULING_GROUPS_COUNT=16)
foreach (TARGET IN LISTS TARGETS)
    add_executable(seastar_${TARGET} src/sample/seastar/seastar_${TARGET}.cpp)
    target_link_libraries(seastar_${TARGET} ${EXTRA_LIB})
endforeach ()
