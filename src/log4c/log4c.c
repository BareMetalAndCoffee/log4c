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
#include "log4c.h"

#include <stdio.h>
#include <stdarg.h>

void Log4C_Error(char *fmt, ...);
void Log4C_Warning(char *fmt, ...);
void Log4C_Info(char *fmt, ...);
void Log4C_Debug(char *fmt, ...);

Log4C_t LOG = {
    .error = Log4C_Error,
    .warning = Log4C_Warning,
    .info = Log4C_Info,
    .debug = Log4C_Debug,
    .stats = {
        .buffer = {
            .size = 0,
            .highWaterMark = 0
        }
    }
};

void Log4C_Error(char *fmt, ...)
{
    va_list args;

    printf("ERROR: ");
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

void Log4C_Warning(char *fmt, ...)
{
    va_list args;

    printf("WARNING: ");
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

void Log4C_Info(char *fmt, ...)
{
    va_list args;

    printf("INFO: ");
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

}

void Log4C_Debug(char *fmt, ...)
{
    va_list args;

    printf("DEBUG: ");
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}
