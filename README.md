# Log4C [![Build Status](https://travis-ci.org/BareMetalAndCoffee/log4c.svg?branch=master)](https://travis-ci.org/BareMetalAndCoffee/log4c)

Like Log4J but worse because it is in C. You may have guessed this has been developed with embedded systems in mind.

## Usage
Simply include the header file and start logging. This assumes you have ported the logger correctly.

    #include <log4c.h>
    // While the program is active log some stuff. 
    LOG.error("Hello world! I am error number %u.\n", (uint32_t) 22);
    LOG.warning("Okay I am a hot pie. You have been warned %d times.\n", (int32_t) -23);
    LOG.info("I am %s. Talk to the %s....\n", "TERMINAL", "KEYBOARD");
    LOG.debug("I like to fill up %s %u times.\n", "log files", (uint32_t) 100000);

## Porting
Log4C is a global object that needs to be ported to your embedded software architecture. The most important thing is that you can write out faster than you can log. If you can do that you will not lose log messages. If not, the output will start to look like garbage because the data buffer is a ring buffer.

Please look at log4c.h for instructions on porting and the examples provided.
