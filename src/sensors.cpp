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

    while (!myGNSS.getGnssFixOk())
    {
        Serial.println("acquiring GPS signal.... fix type=" + myGNSS.getFixType());
    }
}

// BMP390

void Sensors::initBarometer(float sealevel_pressure)
{
    seaLevelPressure = sealevel_pressure;

    if (!bmp.begin_I2C())
    { // hardware I2C mode, can pass in address & alt Wire

        Serial.println("barometer not found");
    }
    // TODO CHECK THIS IF ITS RIGHT
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}

int Sensors::getBaroAltitude()
{

#ifdef SIMULATION_MODE
    Serial.println("%BARO%");
    Serial.flush();

    while (!Serial.available());
    return Serial.parseInt();

    
#endif

    return bmp.readAltitude(seaLevelPressure);
}

JsonDocument Sensors::getSensorData()
{
    JsonDocument filter;



#ifdef SIMULATION_MODE
    filter["lat"] = 1000;
    filter["long"] = 1000;

#else
    filter["lat"] = myGNSS.getLatitude();
    filter["long"] =  myGNSS.getLongitude();
    filter["alt"] = myGNSS.getAltitude();


#endif

    filter["baro"] = getBaroAltitude();
    


    return filter;
}