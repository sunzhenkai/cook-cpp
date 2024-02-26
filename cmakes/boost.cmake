message(STATUS "CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")
# document https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED COMPONENTS filesystem)
message(STATUS "FindBoost: ${Boost_LIBRARY_DIRS} - ${Boost_LIBRARY_TARGETS} - ${Boost_INCLUDE_DIRS} - ${Boost_FOUND} - ${Boost_LIBRARIES}")
set(BOOST_LIBRARIES Boost::boost Boost::filesystem)
#include_directories(${Boost_INCLUDE_DIRS})

add_executable(boost_sample src/sample/boost/sample.cpp)
target_link_libraries(boost_sample ${BOOST_LIBRARIES})

add_executable(boost_preprocess src/sample/boost/preprocess.cpp)
target_link_libraries(boost_preprocess ${BOOST_LIBRARIES})
