cmake_minimum_required(VERSION 3.16) 

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} --coverage")
#add_compile_options(--coverage)
#set(CMAKE_C_FLAGS_PROFILE --coverage) 
#set(CMAKE_CXX_FLAGS_PROFILE --coverage)


project(tests)

#if(CMAKE_BUILD_TYPE MATCHES Debug)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0 -g")
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov")
#endif()

enable_testing()

add_executable(tests tests.cpp)

target_link_libraries(tests Transaction Account gtest gmock)

add_test(test tests)