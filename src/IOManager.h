#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <LoRa.h>
#include <SD.h>
#include <ArduinoJson.h>
class IOManager
{

private:
    float frequency = 915E6;
    File logFile;
   
    void writeToSD(JsonDocument doc);
    void write_flash();

    void initSDCard();
    void initFlash();

    const int chipSelect = 10; // TODO SET THIS CORRECTLY
    void initTranceiver();
    #ifdef SIMULATION_MODE
        void printHex(char *data, int len);
    #endif

public:
    void closeOnBoardStorage();
    void log(const char *key, double value, int16_t printLevel, int16_t loglevel);
    void log(const char *key,const  char *msg, int16_t printLevel, int16_t loglevel);
    void log(const char *key, int32_t value, int16_t printLevel, int16_t loglevel);
    void log(JsonDocument obj, int16_t printLevel,int16_t loglevel);

    JsonDocument slowBsonReceive();
    // general data
    void init();
    void write();
    void transmit(JsonDocument obj);

    void dumpToFlash();

    // transceiver
    void read();
    bool available();
    bool hasNewPacket();
};

#endif