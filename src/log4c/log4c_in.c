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
#include "log4c_in.h"
#include "log4c.h"
#include "log4c_prv.h"

#include <stdio.h>
#include <stdarg.h>

static inline void writeToBuffer(char *str);
static inline void writeMessageToBuffer(char *fmt, va_list *args);

void Log4cIn_LogErrorMessage(char *fmt, ...)
{
    va_list args;
    LOG4C_ASSERT(LOG.prv->isInitialised);
    va_start(args, fmt);
    writeToBuffer("ERROR: ");
    writeMessageToBuffer(fmt, &args);
    va_end(args);
}

void Log4cIn_LogWarningMessage(char *fmt, ...)
{
    va_list args;
    LOG4C_ASSERT(LOG.prv->isInitialised);
    va_start(args, fmt);
    writeToBuffer("WARNING: ");
    writeMessageToBuffer(fmt, &args);
    va_end(args);
}

void Log4cIn_LogInfoMessage(char *fmt, ...)
{
    va_list args;
    LOG4C_ASSERT(LOG.prv->isInitialised);
    va_start(args, fmt);
    writeToBuffer("INFO: ");
    writeMessageToBuffer(fmt, &args);
    va_end(args);

}

void Log4cIn_LogDebugMessage(char *fmt, ...)
{
    va_list args;
    LOG4C_ASSERT(LOG.prv->isInitialised);
    va_start(args, fmt);
    writeToBuffer("DEBUG: ");
    writeMessageToBuffer(fmt, &args);
    va_end(args);
}

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

            if (LOG.prv->in > LOG.stats.buffer.size - 1)
            {
                LOG.prv->in = 0;
            }
            if (LOG.prv->count > LOG.stats.buffer.size - 1)
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

static inline void writeMessageToBuffer(char *fmt, va_list *args)
{
    char message[LOG4C_MAX_MESSAGE_SIZE];
    {
        int charactersWritten = vsnprintf(message, LOG4C_MAX_MESSAGE_SIZE, fmt, *args);

        LOG4C_ASSERT(charactersWritten < LOG4C_MAX_MESSAGE_SIZE);
        if (charactersWritten > LOG4C_MAX_MESSAGE_SIZE)
        {
           LOG.stats.message.overruns++;
        }
    }
    writeToBuffer(message);
}
