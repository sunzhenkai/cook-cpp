include_directories(${SRC_INCLUDE_DIR})

find_package(fmt REQUIRED)

add_executable(basic src/basic/sample_a.cpp)
add_executable(sample_b src/basic/sample_b.cpp)
target_link_libraries(sample_b fmt::fmt)
add_executable(complex_example src/basic/complex_example.cpp)