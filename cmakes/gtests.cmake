set(GTEST_SRCS gtests/gtests_main.cpp)
aux_source_directory(gtests/brpc GTEST_SRCS)

#enable_testing()
find_package(GTest CONFIG REQUIRED)
find_package(Thrift CONFIG REQUIRED)
find_package(unofficial-brpc CONFIG REQUIRED)
find_package(leveldb CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(gflags CONFIG REQUIRED)
message(STATUS "CC - ${Thrift_FOUND} - ${CMAKE_PREFIX_PATH}")

add_executable(gt_main ${GTEST_SRCS})
target_link_libraries(gt_main PRIVATE
        GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
        unofficial::brpc::brpc-static
        leveldb::leveldb
        thrift::thrift
        gflags::gflags
        )
#add_test(AllTestsInMain gt_main)
