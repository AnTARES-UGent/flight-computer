#ifndef SENSORS_H
#define SENSORS_H

#include <arduino.h>
#include <Wire.h> //Needed for I2C to GPS

#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include <Adafruit_BMP3XX.h>

#include <IOManager.h>
#include <ArduinoJson.h>
#include <Adafruit_INA219.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM6DSOX.h>

class Sensors
{

  SFE_UBLOX_GNSS myGNSS;
  Adafruit_BMP3XX bmp;
  Adafruit_INA219 ina219;
  Adafruit_LIS3MDL magnetometer;

  Adafruit_Sensor *tempSensor, *accelerometer, *gyroscope;
  Adafruit_LSM6DSOX gyroAccel;

  float seaLevelPressure = 1013.25;



private:
  void initGPS();
  void initINA219();
  void initMagnetometer();
  void initGyroAndAccel();

  void newGpsDataAvailable();
  void initBarometer(float sealevel_pressure);

public:
  JsonDocument getSensorData();
  void initSensors(float seaLevelPressure);
  void getGPSLatLong(int *latlong);
  int getBaroAltitude();

  void getBatteryInfo(float *data);

  void getAccelData(float *data);
  void getGyroData(float *data);
  void getMagnetoData(float *data);
};

#endif