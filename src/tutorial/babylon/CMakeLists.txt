find_package(babylon CONFIG REQUIRED)

file(GLOB_RECURSE BABYLON_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
add_executable(babylon-example ${BABYLON_SRCS})
target_link_libraries(babylon-example babylon::babylon)
