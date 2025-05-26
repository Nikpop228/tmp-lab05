cmake_minimum_required(VERSION 3.16) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(--coverage)
add_link_options(--coverage)

project(tests_libs)

add_subdirectory(third-party/googletest)

add_subdirectory(banking)

add_subdirectory(tests)