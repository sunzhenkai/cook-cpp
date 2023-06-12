include(${PROJECT_SOURCE_DIR}/external/boost/load.cmake)
include(${PROJECT_SOURCE_DIR}/external/brpc/load.cmake)

add_executable(sample_brpc src/tutorial/brpc/sample_brpc.cpp)
add_dependencies(sample_brpc brpc boost)
#target_link_libraries(sample_brpc brpc)
