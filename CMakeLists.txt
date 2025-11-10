cmake_minimum_required(VERSION 3.13)

project(CanBusSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
    else()
        message(WARNING "clang-tidy not found; skipping static analysis")
    endif()
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} Qt6::Widgets)

enable_testing()
add_subdirectory(external/googletest)
include_directories(external/googletest/googletest/include)

add_executable(unit_tests tests/test_main.cpp)
target_link_libraries(unit_tests gtest gtest_main)

add_test(NAME SampleTest COMMAND unit_tests)
