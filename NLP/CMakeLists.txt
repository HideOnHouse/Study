cmake_minimum_required(VERSION 3.16)
project(heo_nlp C)

set(CMAKE_C_STANDARD 11)

add_executable(heo_nlp hancode.c)
add_executable(heo_nlp2 hfreq-cp949.c)
