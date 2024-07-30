#ifndef IOMANAGER_H
#define IOMANAGER_H


class IOManager{

    private:
        void write_sd();
        void write_flash();
        
        void initSDCard();
        void initFlash();

        




    public:

        //general data
        void init();
        void write();

        void transmit();
        

        void dumpToFlash();


        // tranciever
        void read();
        bool available();







};

#endif