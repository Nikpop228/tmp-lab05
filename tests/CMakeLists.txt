cmake_minimum_required(VERSION 3.30) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(tests)

enable_testing()

add_executable(tests tests.cpp)

target_link_libraries(tests Transaction Account gtest gmock)