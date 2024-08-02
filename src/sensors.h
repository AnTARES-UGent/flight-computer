#ifndef SENSORS_H
#define SENSORS_H

#include <arduino.h>
#include <Wire.h> //Needed for I2C to GPS

#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include <Adafruit_BMP3XX.h>


#include <IOManager.h>
#include <ArduinoJson.h>
class Sensors
{

  SFE_UBLOX_GNSS myGNSS;
  Adafruit_BMP3XX bmp;




  
  float seaLevelPressure = 1013.25;


private:
    void initGPS();
    void newGpsDataAvailable();
    void initBarometer(float sealevel_pressure);

    

public:
    JsonDocument getSensorData();
    void initSensors(float seaLevelPressure);
    void getGPSLatLong(int * latlong);
    int getBaroAltitude();


};

#endif