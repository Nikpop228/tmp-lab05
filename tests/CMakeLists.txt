cmake_minimum_required(VERSION 3.16) 

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

add_compile_options(--coverage)
project(tests)


#target_compile_options(check PRIVATE --coverage)
#target_link_libraries(check --coverage)

enable_testing()

add_executable(tests tests.cpp)

target_link_libraries(tests Transaction Account gtest gmock)

find_program(GCOVR_EXECUTABLE gcovr)

target_link_libraries(tests gcov)

    add_custom_target(coverage
        COMMAND
            ${GCOVR_EXECUTABLE}
                --root=${PROJECT_SOURCE_DIR}/include/
                --object-directory=${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS
            check)

add_test(test tests)