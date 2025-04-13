enable_testing()
find_package(GTest CONFIG REQUIRED)
set(GTestLibraries GTest::gtest GTest::gtest_main GTest::gmock
                   GTest::gmock_main)
find_package(Arrow CONFIG REQUIRED)
find_package(Parquet CONFIG REQUIRED)
find_package(ArrowDataset CONFIG REQUIRED)
find_package(ArrowAcero CONFIG REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -w")
file(GLOB_RECURSE ARROW_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
add_executable(arrow-example ${ARROW_SRCS})
target_link_libraries(
  arrow-example
  "$<IF:$<BOOL:${ARROW_BUILD_STATIC}>,Arrow::arrow_static,Arrow::arrow_shared>"
  "$<IF:$<BOOL:${ARROW_BUILD_STATIC}>,Parquet::parquet_static,Parquet::parquet_shared>"
  "$<IF:$<BOOL:${ARROW_BUILD_STATIC}>,ArrowDataset::arrow_dataset_static,ArrowDataset::arrow_dataset_shared>"
  "$<IF:$<BOOL:${ARROW_BUILD_STATIC}>,ArrowAcero::arrow_acero_static,ArrowAcero::arrow_acero_shared>"
  ${GTestLibraries})

add_test(AllTestsInMain arrow-example)
