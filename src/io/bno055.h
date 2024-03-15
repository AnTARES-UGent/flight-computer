/*
    IMU CLASS - 9 DOF IMU
    Datasheet
    https://cdn-learn.adafruit.com/downloads/pdf/adafruit-bno055-absolute-orientation-sensor.pdf
*/

class BNO055 {
    public:
        BNO055();
        void init();
        void read();
        int test();
        /*
            Incorrect return types, these functions should each return 3 floats XYZ
        */
        float getGyro();
        float getAccel();
        float getMag();      
};