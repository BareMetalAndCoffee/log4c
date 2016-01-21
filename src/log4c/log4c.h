/**
 * 
 * 
 */
#ifndef LOG4C_H
#define LOG4C_H

#include <stdint.h>

typedef struct
{
    void (*error)(char *fmt, ...);
    void (*warning)(char *fmt, ...);
    void (*info)(char *fmt, ...);
    void (*debug)(char *fmt, ...);
    struct
    {
        struct
        {
            uint32_t size;
            uint32_t highWaterMark;
        } buffer;
    } stats;
} Log4C_t;

/**
 * Global instance of Log4C. Assuming this module has been ported correctly
 * this global object can be used at any time.
 */
extern Log4C_t LOG;

#endif /* LOG4C_H */