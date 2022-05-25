include(${CMAKE_SOURCE_DIR}/external/protobuf/check.cmake)

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/gen/protobuf/cpp)

GenerateProtobufMessage(proto_library
        PATH ${PROJECT_SOURCE_DIR}/src/tutorial/pb/protos
        FILES ${PROJECT_SOURCE_DIR}/src/tutorial/pb/protos/*.proto
        OUTPUT ${PROJECT_BINARY_DIR}/gen/protobuf/cpp)

message(STATUS "ckpt; ${proto_library_src}")
add_executable(test_pb src/tutorial/pb/test_pb.cpp ${proto_library_src})
target_link_libraries(test_pb protobuf::protobuf)