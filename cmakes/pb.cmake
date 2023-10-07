find_package(Protobuf CONFIG REQUIRED)
include(${PROJECT_SOURCE_DIR}/vcpkg/cmakes/protobuf.cmake)
GenerateProtoBufMessage(
        FILES ${PROJECT_SOURCE_DIR}/src/tutorial/pb/protos/*.proto
        ${PROJECT_SOURCE_DIR}/src/tutorial/pb/protos/package/*.proto
        OUTPUT ${PROJECT_BINARY_DIR}/gen/protobuf/cpp
        IMPORT ${PROJECT_SOURCE_DIR}/src/tutorial/pb/protos
        SRCS PB_SRCS
        HEADERS PB_HEADERS
)

include_directories(${PB_HEADERS})
add_executable(test_pb src/tutorial/pb/test_pb.cpp ${PB_SRCS})
target_link_libraries(test_pb protobuf::libprotobuf protobuf::libprotobuf-lite)

add_executable(test_pb_b src/tutorial/pb/test_pb_b.cpp ${PB_SRCS})
target_link_libraries(test_pb_b protobuf::libprotobuf protobuf::libprotobuf-lite)