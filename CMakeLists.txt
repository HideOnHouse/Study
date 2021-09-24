# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.16)
project(study)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE c_list "NLP/*.c")

foreach(file_path ${c_list})
    string( REPLACE ".c" "" new_name ${file_path} )
    get_filename_component(filename ${new_name} NAME)
    add_executable( ${filename} ${file_path} )
endforeach()


file(GLOB_RECURSE cpp_list "Algorithm/*.c*")

foreach(file_path ${cpp_list})
    string( REPLACE ".cpp" "" new_name ${file_path} )
    get_filename_component(filename ${new_name} NAME)
    add_executable( ${filename} ${file_path} )
endforeach()

file(GLOB_RECURSE cpp_list "Misc/*.c*")

foreach(file_path ${cpp_list})
    string( REPLACE ".c" "" new_name ${file_path} )
    get_filename_component(filename ${new_name} NAME)
    add_executable( ${filename} ${file_path} )
endforeach()
