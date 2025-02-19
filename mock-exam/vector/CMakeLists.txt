cmake_minimum_required(VERSION 3.13)
project(exam-vector)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest CONFIG REQUIRED)

add_executable(tests tests/test.cpp)
target_link_libraries(tests GTest::gtest_main -fsanitize=address)
target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic -Werror -fsanitize=address)