message(STATUS "CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")
# document https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED COMPONENTS filesystem )
message(STATUS "${Boost_LIBRARY_DIRS} - ${Boost_LIBRARY_TARGETS} - ${Boost_INCLUDE_DIRS} - ${Boost_FOUND} - ${Boost_LIBRARIES}")
include_directories(${Boost_INCLUDE_DIRS})
add_executable(boost_sample src/sample/boost/sample.cpp)
target_link_libraries(boost_sample )