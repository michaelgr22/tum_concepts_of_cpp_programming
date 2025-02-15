cmake_minimum_required(VERSION 3.13)
project(small-vector)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(small-vector small_vector.cpp)
target_compile_options(small-vector PRIVATE -Wall -Wextra -Wpedantic -Werror -fsanitize=address)
target_link_options(small-vector PRIVATE -fsanitize=address)