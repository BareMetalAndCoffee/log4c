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
#include "log4c_port.h"

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
            LOG.prv->buffer[LOG.prv->in] = str[i];
            LOG.prv->in++;
            i++;

            if (LOG.prv->in > LOG4C_BUFFER_SIZE - 1)
            {
                LOG.prv->in = 0;
            }
            if (LOG.prv->count > LOG4C_BUFFER_SIZE - 1)
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

static void writeMessageToBuffer(char *fmt, va_list *args)
{
    char message[LOG4C_MAX_MESSAGE_SIZE];
    {
        int characterWritten; = vsprintf(message, fmt, *args);

        LO4C_ASSERT(characterWritten > LOG4C_MAX_MESSAGE_SIZE);
        if (characterWritten > LOG4C_MAX_MESSAGE_SIZE)
        {
           LOG.stats.message.overruns++;
        }
    }
    writeToBuffer(message);
}

void Log4C_Error(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    writeToBuffer(LOG4C_ERROR_STR);
    writeMessageToBuffer(fmt, &args);
    va_end(args);
}

void Log4C_Warning(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    writeToBuffer(LOG4C_WARNING_STR);
    writeMessageToBuffer(fmt, &args);
    va_end(args);
}

void Log4C_Info(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    writeToBuffer(LOG4C_INFO_STR);
    writeMessageToBuffer(fmt, &args);
    va_end(args);

}

void Log4C_Debug(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    writeToBuffer(LOG4C_DEBUG_STR);
    writeMessageToBuffer(fmt, &args);
    va_end(args);
}

bool Log4C_IsCharAvaliable(void)
{
    uint32_t count = 0;
    LOG4C_ENTER_CRIT_SECTION;
    count = LOG.prv->count;
    LOG4C_EXIT_CRIT_SECTION;
    return count > 0;
}

char Log4C_GetNextChar(void)
{
    char character = '\0';
    LOG4C_ENTER_CRIT_SECTION;
    character = LOG.prv->buffer[LOG.prv->out];
    LOG.prv->out++;
    if (LOG.prv->out > LOG4C_BUFFER_SIZE - 1)
    {
        LOG.prv->out = 0;
    }
    if (LOG.prv->count > 0)
    {
        LOG.prv->count--;
    }
    LOG4C_EXIT_CRIT_SECTION;
    return character;
}
