include_directories(${SRC_INCLUDE_DIR})

#find_package(fmt REQUIRED)
#find_package(Boost 1.76 COMPONENTS ALL)

add_executable(basic src/basic/sample_a.cpp)
add_executable(sample_b src/basic/sample_b.cpp)
#target_link_libraries(sample_b fmt::fmt)
#add_executable(template src/basic/template.cpp)
#target_link_libraries(template Boost::filesystem)

set(CMAKE_CXX_FLAGS "-O0")
add_executable(sample_c src/basic/sample_c.cpp)
add_executable(sample_d src/basic/sample_d.cpp)
add_executable(sample_e src/basic/sample_e.cpp)
add_executable(sample_f src/basic/sample_f.cpp)
add_executable(complex_example src/basic/complex_example.cpp)
add_executable(future_a src/tutorial/future/future_a.cpp)

# base
add_executable(base_mutex src/basic/base_mutex.cpp)
add_executable(base_chrono src/basic/base_chrono.cpp)
add_executable(basic_str src/basic/basic_str.cpp)
add_executable(basic_init_list src/basic/basic_init_list.cpp)
