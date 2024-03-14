include_directories(${SRC_INCLUDE_DIR})
add_executable(s01 src/study/others/s01.cpp)
#set(CMAKE_CXX_FLAGS "-O0")
#set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -latomic")

# atomic
add_executable(atomic_a src/study/atomic/atomic_a.cpp)
TARGET_LINK_LIBRARIES(atomic_a atomic)