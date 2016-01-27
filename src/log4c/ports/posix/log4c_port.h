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
#ifndef LOG4C_PORT_H
#define LOG4C_PORT_H

/**
 * Define the ring buffer and max log message size.
 */
#define LOG4C_BUFFER_SIZE       (1024)
#define LOG4C_MAX_MESSAGE_SIZE  (LOG4C_BUFFER_SIZE / 5)

/**
 * Using mutex to provide critical section protection when using POSIX.
 */
#include <pthread.h>
extern pthread_mutex_t LOG4C_POSIX_MUTEX;
#define LOG4C_ENTER_CRIT_SECTION    pthread_mutex_lock(&LOG4C_POSIX_MUTEX);
#define LOG4C_EXIT_CRIT_SECTION     pthread_mutex_unlock(&LOG4C_POSIX_MUTEX);

/**
 * Define an initialisation function for POSIX.
 */
extern void Log4C_PosixPortInitialisation(void);
#define LOG4C_PORT_INITIALISATION Log4C_PosixPortInitialisation

/**
 * Using standard assert for POSIX port.
 */
#include <assert.h>
#define LOG4C_ASSERT(cond_) assert((cond_))

#endif /* LOG4C_PORT_H */