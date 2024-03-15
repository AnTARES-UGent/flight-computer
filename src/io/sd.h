/*
    SD CARD CLASS
    Datasheet
    https://cdn-learn.adafruit.com/downloads/pdf/adafruit-micro-sd-breakout-board-card-tutorial.pdf
*/

class SD {
    public:
        SD();
        void init();
        void read();
        int test();
        void write();
        void erase();
};