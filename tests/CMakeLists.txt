cmake_minimum_required(VERSION 3.16) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(tests)

enable_testing()

add_executable(tests tests.cpp)

add_subdirectory(googletest)

target_link_libraries(tests Transaction Account gtest gmock)