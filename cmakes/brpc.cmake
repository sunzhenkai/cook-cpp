find_package(unofficial-brpc CONFIG REQUIRED)
find_package(Protobuf REQUIRED)
find_package(spdlog REQUIRED)
include(${PROJECT_SOURCE_DIR}/vcpkg/cmakes/protobuf.cmake)

# generate protocols
GenerateProtoBufMessage(
        SRCS PROTO_SRCS
        HEADERS PROTO_HDRS
        OUTPUT ${PROJECT_BINARY_DIR}/gen/protobuf/cpp
        IMPORT ${PROJECT_SOURCE_DIR}/src/tutorial/brpc/proto
        FILES ${PROJECT_SOURCE_DIR}/src/tutorial/brpc/proto/*.proto
)

include_directories(${PROTO_HDRS})
add_executable(sample_brpc src/tutorial/brpc/sample_brpc.cpp)
target_link_libraries(sample_brpc PRIVATE unofficial::brpc::brpc-static)

include_directories(${CMAKE_CURRENT_BINARY_DIR}) # include proto headers
add_executable(brpc_echo_client src/tutorial/brpc/echo_client.cpp ${PROTO_SRCS})
target_link_libraries(brpc_echo_client PRIVATE unofficial::brpc::brpc-static spdlog::spdlog)
add_executable(brpc_echo_service src/tutorial/brpc/echo_service.cpp ${PROTO_SRCS})
target_link_libraries(brpc_echo_service PRIVATE unofficial::brpc::brpc-static spdlog::spdlog)

