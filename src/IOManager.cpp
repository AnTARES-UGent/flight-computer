#include <IOManager.h>

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

void IOManager::writeToSD(char *data)
{

    logFile.write(data);
    logFile.flush();
    // TODO DOE ZEKER MET SYNC DING
}


void IOManager::closeOnBoardStorage(){


    if(logFile ){
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
void IOManager::transmit(char *data)
{
    LoRa.beginPacket();
    LoRa.print(data);
    LoRa.endPacket();
}

void IOManager::log(const char *key,const char *msg, int16_t printLevel, int16_t loglevel)
{
    BSONObjBuilder builder;
    int32_t time = millis();

    builder.append(key, msg);
    builder.append("T", time);       // time since startup
    builder.append("P", printLevel); // print level
    builder.append("L", loglevel);   // print level
    log(builder.obj(), printLevel);
}

void IOManager::log(const char *key, double value, int16_t printLevel, int16_t loglevel)
{
    BSONObjBuilder builder;
    int32_t time = millis();

    builder.append(key, value);
    builder.append("T", time);       // time since startup
    builder.append("P", printLevel); // print level
    builder.append("L", loglevel);   // print level

    log(builder.obj(), printLevel);
}

void IOManager::log(const char *key, int32_t value, int16_t printLevel, int16_t loglevel)
{
    BSONObjBuilder builder;
    int32_t time = millis();

    builder.append(key, value);
    builder.append("T", time);       // time since startup
    builder.append("P", printLevel); // print level
    builder.append("L", loglevel);   // print level
    log(builder.obj(), printLevel);
}

// TODO WRITE TO FLASH
void IOManager::log(BSONObject obj, int16_t printLevel)
{

    char *bytes = obj.rawData();

    if (printLevel == 0)
    { // write to flash
    }
    else if (printLevel == 1)
    { // transmit

        transmit(bytes);
    }
    else if (printLevel == 2)
    { // transmit and write
        obj.rawData();
        transmit(bytes);
    }
}

void write()
{
}

// waits until a packet is received
BSONObject IOManager::slowBsonReceive()
{
    while (!LoRa.parsePacket())
        ; // wait until packet is recieved

    const int bufferSize = 256; // Adjust this size based on your data
    char buffer[bufferSize];
    int index = 0;

    // Read the incoming bytes into the buffer
    while (LoRa.available() && index < bufferSize)
    {
        buffer[index++] = LoRa.read();
    }

    if (index < bufferSize)
    {
        buffer[index] = '\0'; // Null-terminate the buffer if there is space
    }

    BSONObject bo(buffer);

    return bo;
}

void IOManager::initFlash(){

}