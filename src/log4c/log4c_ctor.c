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
#include "log4c_in.h"
#include "log4c_out.h"
#include "log4c_prv.h"
#include <log4c_port.h>

static void InitialiseLog4C(void);

struct Log4CInternal_t Log4C_Internals = {
    .buffer = {0},
    .count = 0,
    .in = 0,
    .out = 0,
    .isInitialised = false
};

Log4C_t LOG = {
    .initialise = InitialiseLog4C,
    .error = Log4cIn_LogErrorMessage,
    .warning = Log4cIn_LogWarningMessage,
    .info = Log4cIn_LogInfoMessage,
    .debug = Log4cIn_LogDebugMessage,
    .isCharAvaliable = Log4cOut_IsCharAvaliable,
    .getNextChar = Log4cOut_GetNextChar,
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

static void InitialiseLog4C(void)
{
    if (!LOG.prv->isInitialised)
    {
        LOG4C_PORT_INITIALISATION();
        LOG.prv->isInitialised = true;
    }

    /**
     * Validate the porting of log4c. These are just some simple checks to ensure
     * that the port has a possibility of running.
     */
    #ifndef LOG4C_BUFFER_SIZE
    #error "LOG4C Compilation Error: Please define LOG4C_BUFFER_SIZE in you log4c_port."
    #else
    LOG4C_STATIC_ASSERT(LOG4C_BUFFER_SIZE > 0);
    #endif

    #ifndef LOG4C_MAX_MESSAGE_SIZE
    #error "LOG4C Compilation Error: Please define LOG4C_MAX_MESSAGE_SIZE in you log4c_port."
    #else
    LOG4C_STATIC_ASSERT(LOG4C_MAX_MESSAGE_SIZE > 0);
    #endif

    /**
     * Critical section functions must be provided for multi-threaded mode to 
     * ensure that the internal ring buffer does not overflow or get corrupted.
     * 
     * Please see porting examples for what to define in this section.
     */
    #ifndef LOG4C_ENTER_CRIT_SECTION
    #error "LOG4C Compilation Error: Please define LOG4C_ENTER_CRIT_SECTION in you log4c_port."
    #endif

    #ifndef LOG4C_EXIT_CRIT_SECTION
    #error "LOG4C Compilation Error: Please define LOG4C_EXIT_CRIT_SECTION in you log4c_port."
    #endif

    #ifndef LOG4C_PORT_INITIALISATION
    #error "LOG4C Compilation Error: Please define LOG4C_PORT_INITIALISATION in you log4c_port."
    #endif

    #ifndef LOG4C_ASSERT
    #error "LOG4C Compilation Error: Please define LOG4C_ASSERT in you log4c_port."
    #endif
}
