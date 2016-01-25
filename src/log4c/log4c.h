/**
 * This file is part of Log4C.
 * 
 * Log4C is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Log4C is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Log4C.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LOG4C_H
#define LOG4C_H

#include <stdint.h>
#include <stdbool.h>

typedef struct Log4CInternal_t *const Log4C_Private;

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
            uint32_t overruns;
        } buffer;
        struct
        {
            uint32_t overruns;
        } message;
    } stats;
    Log4C_Private prv;
} Log4C_t;

/**
 * Global instance of Log4C. Assuming this module has been ported correctly
 * this global object can be used at any time.
 *
 * Please see porting instructions.
 */
extern Log4C_t LOG;

#endif /* LOG4C_H */