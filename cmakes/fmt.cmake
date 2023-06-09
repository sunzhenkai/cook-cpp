#include(${PROJECT_SOURCE_DIR}/external/fmt/check.cmake)
include(${PROJECT_SOURCE_DIR}/external/spdlog/check.cmake)

add_executable(tfmt src/sample/fmt/fmt.cpp)
#add_dependencies(tfmt fmt)
target_link_libraries(tfmt fmt::fmt spdlog::spdlogd)