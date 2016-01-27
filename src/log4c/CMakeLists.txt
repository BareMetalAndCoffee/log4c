project(LOG4C C)

include_directories(
    ports/posix
)

add_library(log4c
    log4c.h
    log4c_prv.h
    log4c_ctor.c
    log4c_in.c
    log4c_in.h
    log4c_out.c
    log4c_out.h
    ports/posix/log4c_port.c
    ports/posix/log4c_port.h
)
