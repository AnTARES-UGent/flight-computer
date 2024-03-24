/*
    GNSS CLASS - MAX-M10S breakout Sparkfun
    Product page: https://www.sparkfun.com/products/18037#:~:text=The%20SparkFun%20MAX%2DM10S%20Breakout,asset%20trackers%20and%20wearable%20devices.
    Library: https://github.com/sparkfun/SparkFun_u-blox_GNSS_v3/tree/main
*/

class MAX_M10S {
    public:
        MAX_M10S();
        void init();
        void read();
        int test();
        float getLatitude();
        float getLongitude();
        float getAltitude();
        float getSatellites();
};