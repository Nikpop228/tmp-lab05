cmake_minimum_required(VERSION 3.16) 

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} --coverage")

project(tests_libs)

add_subdirectory(third-party/googletest)

add_subdirectory(banking)

add_subdirectory(tests)