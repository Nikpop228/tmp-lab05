cmake_minimum_required(VERSION 3.30) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(tests_libs)

add_subdirectory(banking)
add_subdirectory(tests)
add_subdirectory(googletest)
