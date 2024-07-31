#ifndef IOMANAGER_H
#define IOMANAGER_H
#include <ardubsonObject.h>
#include <ardubsonObjBuilder.h>
#include <LoRa.h>
#include <SD.h>
class IOManager
{

private:
    float frequency = 915E6;
    File logFile;


    void writeToSD(char* data);
    void write_flash();

    void initSDCard();
    void initFlash();

    const int chipSelect = 10; // TODO SET THIS CORRECTLY
    void initTranceiver();
    

public:
    void closeOnBoardStorage();
    void log(char *key, double value, int16_t printLevel, int16_t loglevel);
    void log(char *key, char *msg, int16_t printLevel, int16_t loglevel);
    void log(char *key, int32_t value, int16_t printLevel, int16_t loglevel);
    void log(BSONObject obj, int16_t printLevel);

    BSONObject slowBsonReceive();
    // general data
    void init();
    void write();
    void transmit(char *data);

    void dumpToFlash();

    // transceiver
    void read();
    bool available();
    bool hasNewPacket();
};

#endif