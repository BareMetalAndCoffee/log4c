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
#include <sched.h>
#include <unistd.h>

/**
 * An fake UART in a separate thread.
 */
static void *posixUart(void *arg)
{
    bool *alive = (bool *) arg;
    while(*alive)
    {
        while (LOG.isCharAvaliable())
        {
            printf("%c", LOG.getNextChar());
        }
        (void) sched_yield();
    }
    pthread_exit(NULL);
}

/**
 * A thread in an application logging stuff.
 */
static void *applicationThread(void *arg)
{
    bool *alive = (bool *) arg;
    while(*alive)
    {
        // While the program is active log some stuff. 
        LOG.error("Hello world! I am error number %u.\n", (uint32_t) 22);
        LOG.warning("Okay I am a hot pie. You have been warned %d times.\n", (int32_t) -23);
        LOG.info("I am %s. Talk to the %s....\n", "TERMINAL", "KEYBOARD");
        LOG.debug("I like to fill up %s %u times.\n", "log files", (uint32_t) 100000);
        sleep(1);
    }
    pthread_exit(NULL);
}


int main(void)
{
    bool applicationActive = true;
    pthread_t fakeUartThread;
    pthread_t fakeApplicationThread;

    LOG.initialise();

    if (pthread_create(&fakeUartThread, NULL, posixUart, &applicationActive))
    {
        return EXIT_FAILURE;
    }
    if (pthread_create(&fakeApplicationThread, NULL, applicationThread, &applicationActive))
    {
        return EXIT_FAILURE;
    }

    sleep(5);

    // So the program wants to shut down. Lets see the stats before we go.
    applicationActive = false;
    if (pthread_join(fakeUartThread, NULL))
    {
        return EXIT_FAILURE;
    }
    if (pthread_join(fakeApplicationThread, NULL))
    {
        return EXIT_FAILURE;
    }

    fflush(stdout);
    printf("\n\nLOG STATS:\n");
    printf("LOG.stats.buffer.size:          %u\n", LOG.stats.buffer.size);
    printf("LOG.stats.buffer.highWaterMark: %u\n", LOG.stats.buffer.highWaterMark);
    printf("LOG.stats.buffer.overruns:      %u\n", LOG.stats.buffer.overruns);
    printf("LOG.stats.message.overruns:     %u\n", LOG.stats.message.overruns);

    return EXIT_SUCCESS;
}