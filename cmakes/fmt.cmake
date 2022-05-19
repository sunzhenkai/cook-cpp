find_package(fmt REQUIRED)

add_executable(tfmt src/sample/fmt/fmt.cpp)
target_link_libraries(tfmt fmt::fmt)