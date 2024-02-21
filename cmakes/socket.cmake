include_directories(${SRC_INCLUDE_DIR})

set(SOCKET_SRCS)
aux_source_directory(src/study/socket/basic SOCKET_SRCS)
message(STATUS "socket srcs ${SOCKET_SRCS}")
set(CMAKE_CXX_FLAGS "-O0")

add_executable(socket_echo_server src/study/socket/echo_server.cpp ${SOCKET_SRCS})
add_executable(socket_echo_client src/study/socket/echo_client.cpp ${SOCKET_SRCS})
