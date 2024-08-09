#ifndef LOGGER_C
#define LOGGER_C

#include "logger.h"


/*
    log a message to the system
    @param  key     the key where it needs to be logged
    @param  msg     (int32_t) the message that needs to be logged

*/
void Logger::log(const char *key, int32_t msg)
{
    ioManager.log(key, msg, 2, 0);
}


/*
    log a warning to the system
    @param  key     the key where it needs to be logged
    @param  msg     (int32_t) the message that needs to be logged

*/

void Logger::warn(const char *key, int32_t msg)
{
    ioManager.log(key, msg, 2, 1);
}


/*
    log an error to the system
    @param  key     the key where it needs to be logged
    @param  msg     (int32_t) the message that needs to be logged

*/

void Logger::err(const char *key, int32_t msg)
{
    ioManager.log(key, msg, 2, 2);
}

/*
    log to the system
    @param  key     the key where it needs to be logged
    @param  msg     (String) the message that needs to be logged

*/
void Logger::log(const char *key, const char *msg)
{
    ioManager.log(key, msg, 2, 0);
}

/*
    log a warning to the system
    @param  key     the key where it needs to be logged
    @param  msg     (String) the message that needs to be logged

*/
void Logger::warn(const char *key, const char *msg)
{
    ioManager.log(key, msg, 2, 1);
}

/*
    log an error to the system
    @param  key     the key where it needs to be logged
    @param  msg     (String) the message that needs to be logged

*/

void Logger::err(const char *key, const char *msg)
{
    ioManager.log(key, msg, 2, 2);
}

#endif // LOGGER_C