project(SINGLE_THREAD_EXAMPLE)

cmake_minimum_required(VERSION 2.8)

include_directories(
    ${LOG4C_SOURCE_DIR}
)

add_executable(single_thread_example
    main.c
)

target_link_libraries(single_thread_example log4c)