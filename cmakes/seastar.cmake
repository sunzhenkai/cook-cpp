# 20.05 59f7b32d892191bfae336afcdf6a6d4bd236c183
# 19.06 aa46d84646b381da03dd9126015292686bd078da
# 18.08 7dea64159e2b4a27a740e15d76665e7fccd1d689
set(SEASTAR_VERSION 89cc842f65922b888310d21e61cca9a454feaa84)
set(SEASTAR_GIT_REPOSITORY git@gitlab.mobvista.com:ml-platform/seastar.git)

# includes
include(${PROJECT_SOURCE_DIR}/external/utils.cmake)
include(${PROJECT_SOURCE_DIR}/external/boost/check.cmake)
include(${PROJECT_SOURCE_DIR}/external/openssl/check.cmake)
include(${PROJECT_SOURCE_DIR}/external/curl/check.cmake)
include(${PROJECT_SOURCE_DIR}/external/seastar/check.cmake)
include(${PROJECT_SOURCE_DIR}/external/spdlog/check.cmake)
#include(${PROJECT_SOURCE_DIR}/external/fmt/check.cmake)

include_directories(${SRC_INCLUDE_DIR})

set(EXTRA_LIB seastar::seastar
        fmt::fmt
        protobuf::protobuf
        spdlog::spdlog
        cryptopp::cryptopp
        ${YAML_CPP_LIBRARIES}
        ${Boost_LIBRARIES}
        pthread
        stdc++fs
        openssl::ssl
        openssl::crypto
        curl::curl
        dl
        z)

# executables
set(TARGETS socket metric future server)
foreach (TARGET IN LISTS TARGETS)
    add_executable(seastar_${TARGET} src/sample/seastar/seastar_${TARGET}.cpp)
    target_link_libraries(seastar_${TARGET} ${EXTRA_LIB})
endforeach ()
