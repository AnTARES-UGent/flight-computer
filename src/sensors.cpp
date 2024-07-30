#include <sensors.h>

// initing sensors
void Sensors::initSensors(float seaLevelPressure)
{
    Wire.begin();
    initGPS();
}

// GPS

void Sensors::initGPS()
{
    while (myGNSS.begin() == false)
    {
        Serial.println("GPS not found");


    }

    while(!myGNSS.getGnssFixOk()){
         Serial.println("acquiring GPS signal.... fix type=" + myGNSS.getFixType());


    }



}





void Sensors::getGPSLatLong(int *latlong)
{

    // latitude
    latlong[0] = myGNSS.getLatitude();
    // latitude = latitude / 10000000;
    // longitude
    latlong[1] = myGNSS.getLongitude();
    // longitude = longitude / 10000000;
}




// BMP390

void Sensors::initBarometer(float sealevel_pressure)
{
    seaLevelPressure = sealevel_pressure;

    if (!bmp.begin_I2C())
    { // hardware I2C mode, can pass in address & alt Wire

        Serial.println("barometer not found");
    }
    //TODO CHECK THIS IF ITS RIGHT
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}


int Sensors::getBaroAltitude(){
    return bmp.readAltitude(seaLevelPressure);
}


