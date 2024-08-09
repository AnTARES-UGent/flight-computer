#include "IOManager.h"
/*
    Initialisation of the I/O of the rocket
*/
void IOManager::init()
{

    initTranceiver();
    log("init", "Transiever", 1, 0);
    initSDCard();
    log("init", "SD", 1, 0);

    initFlash();
    log("init", "Flash", 2, 0);
}



/*
    initialises the SD card reader/writer and opens the log file so we can write to it
*/
void IOManager::initSDCard()
{

    // TODO DECIDE HOW TO WRITE TO FILE
    if (!SD.begin(chipSelect))
    {
        log("INIT", "SD not initialized", 2, 2);
    }
    logFile = SD.open("log.bin", FILE_WRITE);
}

/*
    writes jsonDocument to the logfile (opened in initSDCard)
    @param doc jsonDocument that needs to be written

*/

void IOManager::writeToSD(JsonDocument doc)
{

    serializeJson(doc,logFile);

    logFile.flush();

}
/*
    Closes the onboard storage (safely) so that everything is written to it.
*/
void IOManager::closeOnBoardStorage()
{

    if (logFile)
    {
        logFile.close();
    }
}

/*
Initializes flash.

*/

void initFlash()
{
}


/*
    initialises the LoRa tranciever on the correct frequency
*/

void IOManager::initTranceiver()
{

    if (!LoRa.begin(frequency))
    {
        Serial.print("lora not found");
    }
}



/*
    transmits jsonDocument to the logfile (opened in initSDCard)
    @param doc jsonDocument that needs to be written

*/
void IOManager::transmit(JsonDocument data)
{
    LoRa.beginPacket();


    serializeJson(data,LoRa);
   // LoRa.print(data);
    LoRa.endPacket();
}

/*
    logs a message

    @param key           key of the message.
    @param msg          (String) message that you want to send.
    @param printlevel   The level that you want to print, 0 = write to onboard storage, 1 = transmit, 2 = write to onboard storage and transmit.
    @param loglevel     The loglevel is the severity of the log message itself.
*/
void IOManager::log(const char *key, const char *msg, int16_t printLevel, int16_t loglevel)
{
    JsonDocument doc;

    doc[key] = msg;

    log(doc, printLevel, loglevel);
}

/*
    logs a message
    
    @param key           key of the message.
    @param msg          (Double) message that you want to send.
    @param printlevel   The level that you want to print, 0 = write to onboard storage, 1 = transmit, 2 = write to onboard storage and transmit.
    @param loglevel     The loglevel is the severity of the log message itself.
*/
void IOManager::log(const char *key, double value, int16_t printLevel, int16_t loglevel)
{

    JsonDocument doc;
    doc[key] = value;
    log(doc, printLevel, loglevel);
}
/*
    logs a message
    
    @param key           key of the message.
    @param msg          (int32_t) message that you want to send.
    @param printlevel   The level that you want to print, 0 = write to onboard storage, 1 = transmit, 2 = write to onboard storage and transmit.
    @param loglevel     The loglevel is the severity of the log message itself.
*/
void IOManager::log(const char *key, int32_t value, int16_t printLevel, int16_t loglevel)
{
    JsonDocument doc;
    doc[key] = value;
    log(doc, printLevel, loglevel);
}

/*
    logs a jsonDocument

    @param obj           the jsonDocument that needs to be logged.
    @param printlevel   The level that you want to print, 0 = write to onboard storage, 1 = transmit, 2 = write to onboard storage and transmit.
    @param loglevel     The loglevel is the severity of the log message itself.
*/
void IOManager::log(JsonDocument obj, int16_t printLevel, int16_t loglevel)
{

    // TODO WRITE TO FLASH
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



/*
    TODO writes to the onboard storage

*/
void write()
{
}

/*
    waits until an packet is recieved via LoRa

 */
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

/*
initialising flash 

*/
void IOManager::initFlash()
{
}