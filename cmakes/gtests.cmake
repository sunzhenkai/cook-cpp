set(GTEST_SRCS gtests/gtests_main.cpp)
aux_source_directory(gtests/brpc GTEST_SRCS)

enable_testing()
find_package(GTest CONFIG REQUIRED)
find_package(unofficial-brpc CONFIG REQUIRED)
add_executable(gt_main ${GTEST_SRCS})
target_link_libraries(gt_main PRIVATE
        GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
        unofficial::brpc::brpc-static)
add_test(AllTestsInMain gt_main)
