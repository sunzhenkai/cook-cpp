find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

add_executable(tfmt src/sample/fmt/fmt.cpp)
target_link_libraries(tfmt fmt::fmt spdlog::spdlog)

add_executable(fmt_b src/tutorial/fmt/fmt_b.cpp)
target_link_libraries(fmt_b fmt::fmt spdlog::spdlog)
