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

struct Log4CInternal_t {
    volatile uint8_t buffer[LOG4C_BUFFER_SIZE];
    volatile uint32_t in;
    volatile uint32_t out;
    volatile uint32_t count;
};

struct Log4CInternal_t Log4C_Internals = {
    .buffer = {0},
    .count = 0,
    .in = 0,
    .out = 0
};

Log4C_t LOG = {
    .error = Log4C_Error,
    .warning = Log4C_Warning,
    .info = Log4C_Info,
    .debug = Log4C_Debug,
    .stats = {
        .buffer = {
            .size = LOG4C_BUFFER_SIZE,
            .highWaterMark = 0,
            .overruns = 0
        },
        .message = {
            .overruns = 0
        }
    },
    .prv = &Log4C_Internals
};

static inline void writeToBuffer(char *str)
{
    LOG4C_ENTER_CRIT_SECTION;
    {
        int i = 0;
        while (str[i] != '\0')
        {
            LOG.prv->buffer[LOG.prv->in] = str[i++];
            if (LOG.prv->in >= LOG4C_BUFFER_SIZE - 1)
            {
                LOG.prv->in = 0;
            }
            else
            {
                LOG.prv->in++;
            }
            if (LOG.prv->count >= LOG4C_BUFFER_SIZE - 1)
            {
                LOG.stats.buffer.overruns++;
            }
            else
            {
                LOG.prv->count++;
                if (LOG.prv->count > LOG.stats.buffer.highWaterMark)
                {
                    LOG.stats.buffer.highWaterMark = LOG.prv->count;
                }
            }
        }
    }
    LOG4C_EXIT_CRIT_SECTION; 
}

static inline void writeMessageToBuffer(char *prefix, char *fmt, ...)
{
    char message[LOG4C_MAX_MESSAGE_SIZE];
    {
        va_list args;
        va_start(args, fmt);
        if (vsnprintf(message, LOG4C_MAX_MESSAGE_SIZE, fmt, args) > LOG4C_MAX_MESSAGE_SIZE)
        {
           LOG.stats.message.overruns++; 
        }
        va_end(args);
    }
    writeToBuffer(prefix);
    writeToBuffer(message);
}

void Log4C_Error(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    writeMessageToBuffer(LOG4C_ERROR_STR, fmt, args);
    va_end(args);
}

void Log4C_Warning(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    writeMessageToBuffer(LOG4C_WARNING_STR, fmt, args);
    va_end(args);
}

void Log4C_Info(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    writeMessageToBuffer(LOG4C_INFO_STR, fmt, args);
    va_end(args);

}

void Log4C_Debug(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    writeMessageToBuffer(LOG4C_DEBUG_STR, fmt, args);
    va_end(args);
}
