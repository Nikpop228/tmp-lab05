cmake_minimum_required(VERSION 3.16) 

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(tests)

enable_testing()

add_executable(tests tests.cpp)

target_link_libraries(tests Transaction Account gtest gmock)

find_program(GCOVR_EXECUTABLE gcovr)
if(MYLIB_COVERAGE AND GCOVR_EXECUTABLE)
    message(STATUS "Измерение покрытия кода тестами включено")

    target_compile_options(mylib-unit-tests PRIVATE --coverage)
    target_link_libraries(mylib-unit-tests PRIVATE gcov)

    add_custom_target(coverage
        COMMAND
            ${GCOVR_EXECUTABLE}
                --root=${PROJECT_SOURCE_DIR}/include/
                --object-directory=${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS
            check
    )
elseif(MYLIB_COVERAGE AND NOT GCOVR_EXECUTABLE)
    set(MYLIB_COVERAGE OFF)
    message(WARNING "Для замеров покрытия кода тестами требуется программа gcovr")
endif()

add_test(test tests)