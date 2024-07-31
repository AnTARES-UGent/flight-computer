#ifndef IOMANAGER_H
#define IOMANAGER_H
#include <ardubsonObject.h>
#include <ardubsonObjBuilder.h>
#include <LoRa.h>
class IOManager{

    private:
        float frequency = 915E6;
        void write_sd();
        void write_flash();
        
        void initSDCard();
        void initFlash();
        
        
        void initTranciever();
        




    public:

        void log(char* key,char* msg,int16_t printLevel,int16_t loglevel);
        void log(char* key,int32_t  value,int16_t  printLevel,int16_t loglevel);
        void log(BSONObject obj, int16_t  printLevel );

        //general data
        void init();
        void write();
        void transmit(char* data);
        

        void dumpToFlash();


        // tranciever
        void read();
        bool available();







};

#endif