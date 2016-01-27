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
#include "log4c_port.h"

pthread_mutex_t LOG4C_POSIX_MUTEX;

void Log4C_PosixPortInitialisation(void)
{
    pthread_mutex_init(&LOG4C_POSIX_MUTEX, NULL);
}