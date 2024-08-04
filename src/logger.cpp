#ifndef LOGGER_C
#define LOGGER_C

#include "logger.h"

void Logger::log(const char *key, int32_t msg)
{
    ioManager.log(key, msg, 2, 0);
}

void Logger::warn(const char *key, int32_t msg)
{
    ioManager.log(key, msg, 2, 1);
}

void Logger::err(const char *key, int32_t msg)
{
    ioManager.log(key, msg, 2, 2);
}

void Logger::log(const char *key, const char *msg)
{
    ioManager.log(key, msg, 2, 0);
}

void Logger::warn(const char *key, const char *msg)
{
    ioManager.log(key, msg, 2, 1);
}

void Logger::err(const char *key, const char *msg)
{
    ioManager.log(key, msg, 2, 2);
}

#endif // LOGGER_C