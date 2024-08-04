#include "IOManager.h"

// initalization
void IOManager::init()
{

    initTranceiver();
    log("init", "Transiever", 1, 0);
    initSDCard();
    log("init", "SD", 1, 0);

    initFlash();
    log("init", "Flash", 2, 0);
}

void IOManager::initSDCard()
{

    // TODO DECIDE HOW TO WRITE TO FILE
    if (!SD.begin(chipSelect))
    {
        log("INIT", "SD not initialized", 2, 2);
    }
    logFile = SD.open("log.bin", FILE_WRITE);
}

void IOManager::writeToSD(JsonDocument doc)
{

    serializeJson(doc,logFile);

    logFile.flush();
    // TODO DOE ZEKER MET SYNC DING
}

void IOManager::closeOnBoardStorage()
{

    if (logFile)
    {
        logFile.close();
    }
}

void initFlash()
{
}

void IOManager::initTranceiver()
{

    if (!LoRa.begin(frequency))
    {
        Serial.print("lora not found");
    }
}


// TODO NEEDS TESTING
void IOManager::transmit(JsonDocument data)
{
    LoRa.beginPacket();


    serializeJson(data,LoRa);
   // LoRa.print(data);
    LoRa.endPacket();
}

void IOManager::log(const char *key, const char *msg, int16_t printLevel, int16_t loglevel)
{
    JsonDocument doc;

    doc[key] = msg;

    log(doc, printLevel, loglevel);
}

void IOManager::log(const char *key, double value, int16_t printLevel, int16_t loglevel)
{

    JsonDocument doc;
    doc[key] = value;
    log(doc, printLevel, loglevel);
}

void IOManager::log(const char *key, int32_t value, int16_t printLevel, int16_t loglevel)
{
    JsonDocument doc;
    doc[key] = value;
    log(doc, printLevel, loglevel);
}

// TODO WRITE TO FLASH
void IOManager::log(JsonDocument obj, int16_t printLevel, int16_t loglevel)
{
    int32_t time = millis();
    obj["T"] = time;
    obj["P"] = printLevel;
    obj["L"] = loglevel;
   

#ifdef SIMULATION_MODE
    serializeJson(obj, Serial);

#else
    if (printLevel == 0)
    { // write to flash

        writeToSD(obj);
    }
    else if (printLevel == 1)
    { // transmit

        transmit(obj);
    }
    else if (printLevel == 2)
    { // transmit and write

        writeToSD(obj);
        transmit(obj);
    }
#endif
}

void write()
{
}

// waits until a packet is received
JsonDocument IOManager::slowBsonReceive()
{
    while (!LoRa.parsePacket())
        ; // wait until packet is recieved


    JsonDocument doc;
    if (LoRa.available())
    {
        deserializeJson(doc, LoRa);
    }

    return doc;
}

void IOManager::initFlash()
{
}