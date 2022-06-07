include(${CMAKE_SOURCE_DIR}/external/flatbuffers/check.cmake)

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/gen/flatbuffers/cpp)

GenerateFlatbuffersMessage(fbs_library
        PATH ${PROJECT_SOURCE_DIR}/src/tutorial/flatbuffers/protos
        FILES ${PROJECT_SOURCE_DIR}/src/tutorial/flatbuffers/protos/*.fbs
        OUTPUT ${PROJECT_BINARY_DIR}/gen/flatbuffers/cpp)

add_executable(fbs src/tutorial/flatbuffers/fb.cpp ${fbs_library_src})
target_link_libraries(fbs flatbuffers::flatbuffers)