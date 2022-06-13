include(${PROJECT_SOURCE_DIR}/external/fmt/check.cmake)

add_executable(tfmt src/sample/fmt/fmt.cpp)
target_link_libraries(tfmt fmt::fmt)