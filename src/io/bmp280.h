/*
    BAROMETER BMP280 CLASS
    Datasheet
    https://cdn-learn.adafruit.com/downloads/pdf/adafruit-bmp280-barometric-pressure-plus-temperature-sensor-breakout.pdf
*/


class BMP280 {
    public:
        BMP280();
        void init();
        void read();
        int test();
        float getTemperature();
        float getPressure();
        float getAltitude();
};