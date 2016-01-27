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
#ifndef LOG4C_PRIVATE_H
#define LOG4C_PRIVATE_H

#include <stdint.h>
#include <log4c_port.h>

struct Log4CInternal_t {
    volatile uint8_t buffer[LOG4C_BUFFER_SIZE];
    volatile uint32_t in;
    volatile uint32_t out;
    volatile uint32_t count;
};

#endif /* LOG4C_PRIVATE_H */