find_package(unofficial-brpc CONFIG REQUIRED)
add_executable(sample_brpc src/tutorial/brpc/sample_brpc.cpp)
target_link_libraries(sample_brpc PRIVATE unofficial::brpc::brpc-static)
