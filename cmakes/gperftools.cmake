include(${CMAKE_SOURCE_DIR}/external/gperftools/load.cmake)

add_executable(gperf ${PROJECT_SOURCE_DIR}/src/tutorial/gperftools/pf.cpp)
target_link_libraries(gperf gperftools::tcmalloc_and_profiler)