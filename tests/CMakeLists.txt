cmake_minimum_required(VERSION 3.16) 

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(COVERAGE "Check coverage" ON)

project(tests)

enable_testing()

add_executable(tests tests.cpp)

target_link_libraries(tests Transaction Account gtest gmock)

add_test(test tests)

if (COVERAGE)
  target_compile_options(check PRIVATE --coverage)
  target_link_libraries(check --coverage)
endif()

#add_custom_target()