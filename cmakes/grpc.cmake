include(${CMAKE_SOURCE_DIR}/external/grpc/load.cmake)

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/gen/protobuf/cpp)

GenerateProtobufMessage(proto_library
        PATH ${PROJECT_SOURCE_DIR}/src/tutorial/grpc/protos
        FILES ${PROJECT_SOURCE_DIR}/src/tutorial/grpc/protos/*.proto
        OUTPUT ${PROJECT_BINARY_DIR}/gen/protobuf/cpp)

add_executable(echo_grpc src/tutorial/grpc/sample_server.cpp ${proto_library_src})
target_link_libraries(echo_grpc grpc::grpc++)