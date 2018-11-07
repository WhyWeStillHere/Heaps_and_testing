cmake_minimum_required(VERSION 3.12)
project(heaps_and_testing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -std=gnu++0x")

add_compile_options(
        -Dgtest_disable_pthreads=ON
)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES main.cpp Tests/Class.h Tests/test.cpp Tests/Heap.h)
add_executable(heaps_and_testing ${SOURCE_FILES} Tests/test.cpp)
target_link_libraries(heaps_and_testing gtest gtest_main)

