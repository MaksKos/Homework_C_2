cmake_minimum_required(VERSION 3.16)

project(Homework1 VERSION 1.0.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wpedantic -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic -pthread")

add_compile_options("-fsanitize=undefined")
add_link_options( "-fsanitize=undefined")

add_compile_options("--coverage")


add_subdirectory(lib/sort_employee)
add_subdirectory(lib/utils)


# compile console example of programm

#add_executable(employ lib/utils/src/main.c)
#target_link_libraries(employ sort utils)

# compile test for no thread library
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(tests test/tests.cpp)
target_link_libraries(tests ${GTEST_LIBRARIES} utils sort gcov)

# compile test for thread library
#add_executable(tests_thread tests/test.cpp)
#include_directories(${GTEST_INCLUDE_DIRS})
#target_link_libraries(tests_procs ${GTEST_LIBRARIES} utils word_search_procs gcov)