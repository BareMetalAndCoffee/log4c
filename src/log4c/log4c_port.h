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
 * Porting values
 * 
 * Any of these defintions can be overwritten via compiler defintions
 */
#ifndef LOG4C_ERROR_STR
#define LOG4C_ERROR_STR         "ERROR: "
#endif

#ifndef LOG4C_WARNING_STR
#define LOG4C_WARNING_STR       "WARNING: "
#endif

#ifndef LOG4C_INFO_STR
#define LOG4C_INFO_STR          "INFO: "
#endif

#ifndef LOG4C_DEBUG_STR
#define LOG4C_DEBUG_STR         "DEBUG: "
#endif

/**
 * Porting values
 * 
 * Any of these defintions can be overwritten via compiler defintions
 */
#ifndef LOG4C_BUFFER_SIZE
#define LOG4C_BUFFER_SIZE       (500)
#endif

#ifndef LOG4C_MAX_MESSAGE_SIZE
#define LOG4C_MAX_MESSAGE_SIZE  (LOG4C_BUFFER_SIZE / 5)
#endif

/**
 * Critical section functions must be provided for multi-threaded mode to 
 * ensure that the internal ring buffer does not overflow or get corrupted.
 * 
 * Please see porting examples for what to define in this section.
 */
#ifndef LOG4C_ENTER_CRIT_SECTION
#define LOG4C_ENTER_CRIT_SECTION
#endif

#ifndef LOG4C_EXIT_CRIT_SECTION
#define LOG4C_EXIT_CRIT_SECTION
#endif

/**
 * This function can be used in conjuction with Log4C_GetNextChar to print
 * out characters in the log buffer.
 * 
 * @return
 *      True if a character is avaliable, otherwise false
 */
bool Log4C_IsCharAvaliable(void);

/**
 * This function needs to be called to get the next character from the log. 
 * It is the responsibility of the implementor to call this function faster
 * that the log buffer fills up.
 * 
 * @return
 *      The next character from the log to print.
 */
char Log4C_GetNextChar(void);

#define LO4C_ASSERT(cond_)

#endif /* LOG4C_PORT_H */