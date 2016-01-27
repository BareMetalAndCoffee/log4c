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

struct Log4CInternal_t Log4C_Internals = {
    .buffer = {0},
    .count = 0,
    .in = 0,
    .out = 0
};

Log4C_t LOG = {
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
