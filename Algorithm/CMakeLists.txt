cmake_minimum_required(VERSION 3.19)
project(algorithm)

set(CMAKE_CXX_STANDARD 11)

add_executable(hash who_not_finish.cpp)
add_executable(insertion insertion_sort.cpp)
add_executable(merge merge_sort.cpp)
add_executable(sort sorts.cpp)
add_executable(test hackable.c)