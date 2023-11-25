find_package(PkgConfig REQUIRED)
pkg_check_modules(cassandra_static REQUIRED IMPORTED_TARGET cassandra_static)
#pkg_check_modules(libuv-static REQUIRED IMPORTED_TARGET libuv-static)
find_package(gflags CONFIG REQUIRED)
find_package(libuv CONFIG REQUIRED)
#message(STATUS "libuv - ${libuv_INCLUDE_DIR} - ${libuv_LIBRARIES} - ${libuv_FOUND}")
#find_package(OpenSSL REQUIRED)
pkg_check_modules(openssl REQUIRED IMPORTED_TARGET openssl)
#message(STATUS "OpenSSL - ${OpenSSL_INCLUDE_DIR} - ${OpenSSL_LIBRARIES} - ${OpenSSL_FOUND}")
#find_package(ZLIB REQUIRED)
#message(STATUS "ZLIB - ${ZLIB_INCLUDE_DIR} - ${ZLIB_LIBRARIES} - ${ZLIB_FOUND}")
pkg_check_modules(zlib REQUIRED IMPORTED_TARGET zlib)

add_executable(cassandra_basic src/tutorial/cassandra/basic.cpp)
target_link_libraries(cassandra_basic PRIVATE
        PkgConfig::cassandra_static
        gflags::gflags
#        OpenSSL::SSL
#        OpenSSL::Crypto
        PkgConfig::openssl
        PkgConfig::zlib
#        ZLIB::ZLIB
        #        PkgConfig::libuv-static
        $<IF:$<TARGET_EXISTS:libuv::uv_a>,libuv::uv_a,libuv::uv>
)
