project(POSIX_EXAMPLE)

cmake_minimum_required(VERSION 2.8)

include_directories(
    ${LOG4C_SOURCE_DIR}
    ${LOG4C_SOURCE_DIR}/ports/posix
)

add_executable(posix_example
    main.c
)

target_link_libraries(posix_example log4c pthread)