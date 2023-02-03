include(${PROJECT_SOURCE_DIR}/external/incubator-brpc/load.cmake)

add_executable(sample_brpc src/tutorial/brpc/sample_brpc.cpp)
#target_link_libraries(sample_brpc fmt::fmt)