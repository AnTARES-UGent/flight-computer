#ifndef SENSORS_H
#define SENSORS_H

#include <arduino.h>


#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include <Adafruit_BMP3XX.h>

#include <IOManager.h>
#include <ArduinoJson.h>
#include <Adafruit_INA219.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM6DSOX.h>

class Sensor {
  public:
    /*
      Abstract function to initialise sensor

      @returns bool Determines whether the initialisation was successful
    */
    virtual bool init() = 0;
    /*
      Abstract function to test sensor functionality

      @returns bool Determines whether the test was successful
    */
    virtual bool test() = 0;
}

class Magneto : public Sensor {
  Adafruit_LIS3MDL mm;
  public:
    bool init();
    bool test();

    void getData(float *data);
}

class Gnss : public Sensor {
  SFE_UBLOX_GNSS myGNSS;
  public:
    bool init();
    bool test();

    void newDataAvailable();
    void getLatLong(int *latlong);
}

/*
  ina219 power meter sensor
*/
class Power : public Sensor {
  Adafruit_INA219 ina219;
  public:
    bool init();
    bool test();

    void getData(float *data);
}

class Baro : public Sensor {
  Adafruit_BMP3XX bmp;
  private:
    const float seaLevelPressure;
  public:
    /*
      @param float    seaLevelPressure
    */
    Baro(float& _seaLevelPressure) : seaLevelPressure(_seaLevelPressure) {};
    /*
      ctor seaLevelPressure defaults to 1013.25 hPa
    */
    Baro() : seaLevelPressure(1013.25) {}
    bool init();
    bool test();

    int getAltitude();
}

class Imu : public Sensor {
  Adafruit_Sensor *tempSensor, *accelerometer, *gyroscope;
  Adafruit_LSM6DSOX gyroAccel;
  public:
    bool init();
    bool test();

    void getAccelData(float *data);
    void getGyroData(float* data);
}

// Won't compile with new layout
class Sensors
{
  public:
    JsonDocument getSensorData();
    void initSensors(float seaLevelPressure);
};

#endif