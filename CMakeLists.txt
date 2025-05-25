cmake_minimum_required(VERSION 3.16) 

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(tests_libs)

add_subdirectory(third-party/googletest)

include_directories(third-party/googletest/include)
include_directories(third-party/googlemock/include)

add_subdirectory(banking)

add_subdirectory(tests)