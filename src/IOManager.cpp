#include <IOManager.h>

// initalization
void IOManager::init()
{

    initTranciever();
    log("init","Trans init",2,0);

}



void initSDCard()
{

}

void initFlash()
{
}

void IOManager::initTranciever()
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



void IOManager::log(char* key,char* msg,int16_t printLevel,int16_t loglevel){
    BSONObjBuilder builder;
    int32_t time = millis();

    builder.append(key, msg);
    builder.append("T",time); //time since startup
    builder.append("P",printLevel); //print level
    builder.append("L",loglevel); //print level
    log(builder.obj(),printLevel);

}


void IOManager::log(char* key,int32_t  value,int16_t printLevel,int16_t loglevel){
    BSONObjBuilder builder;
    int32_t time = millis();
    
    builder.append(key, value);
    builder.append("T",time); //time since startup
    builder.append("P",printLevel); //print level
    builder.append("L",loglevel); //print level
    log(builder.obj(),printLevel);

}


//TODO WRITE TO FLASH
void IOManager::log(BSONObject obj, int16_t  printLevel)
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

        transmit(bytes);
    }
}

void write()
{

}

void read()
{
}

bool available()
{

    
}