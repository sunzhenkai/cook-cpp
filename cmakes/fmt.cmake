include(${PROJECT_SOURCE_DIR}/external/fmt/load.cmake)

add_executable(tfmt src/sample/fmt/fmt.cpp)
add_dependencies(tfmt fmt)
#target_link_libraries(tfmt fmt::fmt)