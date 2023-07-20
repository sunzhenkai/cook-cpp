# includes
include_directories(${SRC_INCLUDE_DIR})

add_executable(sample_seastar src/tutorial/seastar/sample_seastar.cpp)

find_package(Seastar REQUIRED)
target_link_libraries(sample_seastar PRIVATE Seastar::seastar fmt::fmt)
