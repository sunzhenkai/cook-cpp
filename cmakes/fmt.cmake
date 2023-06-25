include(${PROJECT_SOURCE_DIR}/external/fmt/load.cmake)
include(${PROJECT_SOURCE_DIR}/external/spdlog/load.cmake)

add_executable(tfmt src/sample/fmt/fmt.cpp)
#add_dependencies(tfmt fmt)
target_link_libraries(tfmt PkgConfig::PKG_SPDLOG PkgConfig::PKG_FMT)