enable_testing()
find_package(GTest CONFIG REQUIRED)
set(GTestLibraries GTest::gtest GTest::gtest_main GTest::gmock
                   GTest::gmock_main)
find_package(Arrow CONFIG REQUIRED)

file(GLOB_RECURSE ARROW_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
add_executable(arrow-example ${arrow_SRCS})
target_link_libraries(
  arrow-example
  "$<IF:$<BOOL:${ARROW_BUILD_STATIC}>,Arrow::arrow_static,Arrow::arrow_shared>"
  ${GTestLibraries})

add_test(AllTestsInMain arrow-example)
