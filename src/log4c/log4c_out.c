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
#include "log4c_prv.h"
#include <log4c_port.h>

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
    if (LOG.prv->out > LOG.stats.buffer.size - 1)
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
