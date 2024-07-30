#ifndef IOMANAGER_H
#define IOMANAGER_H


class IOManager{

    private:
        void write_sd();
        void write_flash();
        void transmit();
        




    public:

        //general data
        void init();
        void write();

        void dumpFlash();


        // tranciever
        void read();
        bool available();







};

#endif