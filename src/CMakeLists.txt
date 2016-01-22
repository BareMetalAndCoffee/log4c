project(LOG4C_BUILDER)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "-Wall -Werror")

add_subdirectory(lib)
add_subdirectory(log4c)
add_subdirectory(examples)