
#include "log4c.h"

void Log4C_Error(char *fmt, ...);
void Log4C_Warning(char *fmt, ...);
void Log4C_Info(char *fmt, ...);
void Log4C_Debug(char *fmt, ...);


Log4C_t LOG = {
    .error = Log4C_Error,
    .warning = Log4C_Warning,
    .info = Log4C_Info,
    .debug = Log4C_Debug,
    .stats = {
        .buffer = {
            .size = 0,
            .highWaterMark = 0
        }
    }
};

void Log4C_Error(char *fmt, ...)
{
    
}

void Log4C_Warning(char *fmt, ...)
{
    
}

void Log4C_Info(char *fmt, ...)
{
    
}

void Log4C_Debug(char *fmt, ...)
{
    
}