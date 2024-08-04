#ifndef LOGGER_H
#define LOGGER_H

#include "ioManager.h"

extern IOManager ioManager; // Defined in main.cpp

class Logger {
    public:
        void log(const char *key, int32_t msg);
        void warn(const char *key, int32_t msg);
        void err(const char *key, int32_t msg);

        void log(const char *key, const char *msg);
        void warn(const char *key, const char *msg);
        void err(const char *key, const char *msg);
};

#endif // LOGGER_H