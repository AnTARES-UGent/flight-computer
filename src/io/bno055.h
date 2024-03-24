/*
    IMU CLASS - 9 DOF IMU
    Datasheet
    https://cdn-learn.adafruit.com/downloads/pdf/adafruit-bno055-absolute-orientation-sensor.pdf
*/

class BNO055 {
    public:
        BNO055();
        
        void init();
        int test();

        float getGyroX();
        float getGyroY();
        float getGyroZ();
        float getAccelX();
        float getAccelY();
        float getAccelZ();
        float getMagX();
        float getMagY();
        float getMagZ();
};