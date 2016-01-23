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
#include <log4c.h>
#include <log4c_port.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/**
 * An fake UART in a separate thread.
 */
static void *posixUart(void *arg)
{
    bool *alive = (bool *) arg;
    while(*alive)
    {
        while (Log4C_IsCharAvaliable())
        {
            printf("%c", Log4C_GetNextChar());
        }
    }
    pthread_exit(NULL);
}

int main(void)
{
    bool applicationActive = true;
    pthread_t fakeUartThread;

    if (pthread_create(&fakeUartThread, NULL, posixUart, &applicationActive))
    {
        return EXIT_FAILURE;
    }

    // While the program is active log some stuff. 
    LOG.error("Hello world! I am error number %u.\n", 22);
    LOG.warning("Okay I am a hot pie. You have been warned %d times.\n", -23);
    LOG.info("I am %s. Talk to the %s....\n", "TERMINAL", "KEYBOARD");
    LOG.debug("I like to fill up %s %u times.\n", "log files", 100000);
    sleep(1);

    // So the program wants to shut down. Lets see the stats before we go.
    applicationActive = false;
    if (pthread_join(fakeUartThread, NULL))
    {
        return EXIT_FAILURE;
    }

    printf("LOG STATS:\n");
    printf("LOG.stats.buffer.size:          %u\n", LOG.stats.buffer.size);
    printf("LOG.stats.buffer.highWaterMark: %u\n", LOG.stats.buffer.highWaterMark);
    printf("LOG.stats.buffer.overruns:      %u\n", LOG.stats.buffer.overruns);
    printf("LOG.stats.message.overruns:     %u\n", LOG.stats.message.overruns);

    return EXIT_SUCCESS;
}