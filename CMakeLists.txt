cmake_minimum_required(VERSION 3.16)
project(study)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE file_list "NLP/*.c")

foreach(file_path ${file_list})
    string( REPLACE ".cpp" "_cpp" new_name ${file_path} )
    string( REPLACE ".c" "_c" new_name ${new_name} )
    get_filename_component(filename ${new_name} NAME)
    add_executable( ${filename} ${file_path} )
endforeach()


file(GLOB_RECURSE file_list "Algorithm/*.c*")

foreach(file_path ${file_list})
    string( REPLACE ".cpp" "_cpp" new_name ${file_path} )
    string( REPLACE ".c" "_c" new_name ${new_name} )
    get_filename_component(filename ${new_name} NAME)
    add_executable( ${filename} ${file_path} )
endforeach()

file(GLOB_RECURSE file_list "Misc/*.c*")

foreach(file_path ${file_list})
    string( REPLACE ".cpp" "_cpp" new_name ${file_path} )
    string( REPLACE ".c" "_c" new_name ${new_name} )
    get_filename_component(filename ${new_name} NAME)
    add_executable( ${filename} ${file_path} )
endforeach()

file(GLOB_RECURSE file_list "DataStructure/*.c*")

foreach(file_path ${file_list})
    string( REPLACE ".cpp" "_cpp" new_name ${file_path} )
    string( REPLACE ".c" "_c" new_name ${new_name} )
    get_filename_component(filename ${new_name} NAME)
    add_executable( ${filename} ${file_path} )
endforeach()
