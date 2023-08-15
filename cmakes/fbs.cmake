find_package(flatbuffers CONFIG REQUIRED)
include(${PROJECT_SOURCE_DIR}/vcpkg/cmakes/flatbuffers.cmake)

GenerateFlatbuffersMessage(
        SRCS FB_SRCS
        BINARIES FB_BINARIES
        FILES ${PROJECT_SOURCE_DIR}/src/tutorial/flatbuffers/protos/*.fbs
        OUTPUT ${PROJECT_BINARY_DIR}/gen/flatbuffers/cpp)

include_directories(${PROJECT_BINARY_DIR}/gen/flatbuffers/cpp)
add_executable(fbs src/tutorial/flatbuffers/fb.cpp)
target_link_libraries(fbs flatbuffers::flatbuffers)
