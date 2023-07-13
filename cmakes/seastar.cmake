# includes
include(${PROJECT_SOURCE_DIR}/external/fmt/load.cmake)
include(${PROJECT_SOURCE_DIR}/external/seastar/load.cmake)
include_directories(${SRC_INCLUDE_DIR})


add_executable(sample_seastar src/tutorial/seastar/sample_seastar.cpp)
add_dependencies(sample_seastar seastar_lib fmt_lib)

#target_link_libraries(sample_seastar /tmp/cpp-external-lib/seastar/lib/libseastar.a)
#target_link_libraries(sample_seastar PRIVATE PkgConfig::PKG_SEASTAR PkgConfig::PKG_FMT)

#set(EXTRA_LIB seastar::seastar
#        fmt::fmt
#        protobuf::protobuf
#        spdlog::spdlogd
#        cryptopp::cryptopp
#        yaml-cpp::yaml-cpp
#        ${Boost_LIBRARIES}
#        pthread
#        stdc++fs
#        openssl::ssl
#        openssl::crypto
#        curl::curl
#        dl
#        z)
#
## executables
#set(TARGETS socket metric future server sample)
#add_definitions(-DSEASTAR_SCHEDULING_GROUPS_COUNT=16)
#foreach (TARGET IN LISTS TARGETS)
#    add_executable(seastar_${TARGET} src/sample/seastar/seastar_${TARGET}.cpp)
#    target_link_libraries(seastar_${TARGET} ${EXTRA_LIB})
#endforeach ()
