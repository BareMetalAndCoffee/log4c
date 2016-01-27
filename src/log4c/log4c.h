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
#ifndef LOG4C_H
#define LOG4C_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Private structure - enabling OOP paradigm
 */
typedef struct Log4CInternal_t *const Log4C_Private;

/**
 * OOP Log4C structure.
 */
typedef struct
{
    /**
     * Not all ports... 
     */
    void (*const initialise)(void);
    
    /**
     * Methods that can be called by singleton LOG instance. These can be
     * overriden to complete custom behaviour. However, read the porting
     * guide to see if you can get what you want out of an existing port. 
     */
    void (*const error)(char *fmt, ...);
    void (*const warning)(char *fmt, ...);
    void (*const info)(char *fmt, ...);
    void (*const debug)(char *fmt, ...);

    /**
     * This function can be used in conjuction with LOG.getNextChar to print
     * out characters in the log buffer.
     * 
     * @return
     *      True if a character is avaliable, otherwise false
     */
    bool (*const isCharAvaliable)(void);

    /**
     * This function needs to be called to get the next character from the log. 
     * It is the responsibility of the implementor to call this function faster
     * that the log buffer fills up.
     * 
     * @return
     *      The next character from the log to print.
     */
    char (*const getNextChar)(void);

    /**
     * Public members of Log4C. Can be called at anytime to get a value.
     */
    struct
    {
        struct
        {
            const uint32_t size;
            uint32_t highWaterMark;
            uint32_t overruns;
        } buffer;
        struct
        {
            uint32_t overruns;
        } message;
    } stats;

    /**
     * Private members of Log4C. These can not be modified by outsiders....
     */
    Log4C_Private prv;
} Log4C_t;

/**
 * Global instance of Log4C. Assuming this module has been ported correctly
 * this global object can be used at any time.
 *
 * Please see porting instructions.
 */
extern Log4C_t LOG;

#endif /* LOG4C_H */