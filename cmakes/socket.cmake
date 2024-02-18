include_directories(${SRC_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "-O0")
add_executable(socket_server src/study/socket/server.cpp)
add_executable(socket_client src/study/socket/client.cpp)

