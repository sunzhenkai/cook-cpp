# includes
include_directories(${SRC_INCLUDE_DIR})
find_package(Seastar REQUIRED)

add_executable(sample_seastar src/tutorial/seastar/sample_seastar.cpp)
target_link_libraries(sample_seastar PRIVATE Seastar::seastar fmt::fmt)

add_executable(seastar_in_out src/tutorial/seastar/seastar_in_out.cpp)
target_link_libraries(seastar_in_out PRIVATE Seastar::seastar fmt::fmt)
