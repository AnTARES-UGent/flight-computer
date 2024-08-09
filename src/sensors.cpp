#include <sensors.h>

// initing sensors

/*
    Initialises sensors  as follows: INA219 , GPS, barometer, magnetometer, gyro/accelerometer
    @param seaLevelPressure     the sealevel pressure on that day 
*/
void Sensors::initSensors(float seaLevelPressure)
{
    initINA219();
    initGPS();
    initBarometer(seaLevelPressure);
    
    initMagnetometer();
    initGyroAndAccel();
    
}


/*
    initialises GPS
*/
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


/*
    initialises barometer
     @param seaLevelPressure     the sealevel pressure on that day 
*/
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
/*
    reads the barometer for altitude
    @return (int) altitude calculated by the barometer

*/
int Sensors::getBaroAltitude()
{

#ifdef SIMULATION_MODE
    Serial.println("%BARO%");
    Serial.flush();

    while (!Serial.available())
        ;
    return Serial.parseInt();

#endif

    return bmp.readAltitude(seaLevelPressure);
}


/*
    initialises the INA219
*/
void Sensors::initINA219()
{
    if (!ina219.begin())
    {
        Serial.println("Failed to find INA219 chip");
        while (1)
            ; // TODO
    }
}


/*
    Gets the battery info.

    @param data     float array of length 4 where the battery info is inserted. Data is inserted as follows : shuntVoltage_mV, busVoltage_V, current_mA, power_mW

*/
void Sensors::getBatteryInfo(float *data)
{
#if SIMULATION_MODE
    Serial.println("%BATT%");
    Serial.flush();

    while (!Serial.available())
        ;

    data[0] = Serial.parseFloat();
    data[1] = Serial.parseFloat();
    data[2] = Serial.parseFloat();
    data[3] = Serial.parseFloat();

#else

    data[0] = ina219.getShuntVoltage_mV();
    data[1] = ina219.getBusVoltage_V();
    data[2] = ina219.getCurrent_mA();
    data[3] = ina219.getPower_mW();

#endif
}


/*
    Initialises the magnetometer.
*/
void Sensors::initMagnetometer()
{

    // TODO CONFIG
    if (!magnetometer.begin_I2C())
    { // hardware I2C mode, can pass in address & alt Wire

        Serial.println("Failed to find LIS3MDL chip");
        while (1)
            ;
    }
}


/*
    Gets the magnetometer data.

    @param data     float array of length 3 where the battery info is inserted. Data is inserted as follows : magnetic_X,magnetic_Y,magnetic_Z

*/
void Sensors::getMagnetoData(float *data)
{

#if SIMULATION_MODE
    Serial.println("%MAGNET%");
    Serial.flush();

    while (!Serial.available())
        ;

    data[0] = Serial.parseFloat();
    data[1] = Serial.parseFloat();
    data[2] = Serial.parseFloat();

#else

    sensors_event_t magnetoEvt;
    magnetometer.getEvent(&magnetoEvt);
    data[0] = magnetoEvt.magnetic.x;
    data[1] = magnetoEvt.magnetic.y;
    data[2] = magnetoEvt.magnetic.z;
#endif
}

/*

initialises the gyro and accelerometer
*/
void Sensors::initGyroAndAccel()
{
    // TODO CONFIG
    if (!gyroAccel.begin_I2C())
    { // hardware I2C mode, can pass in address & alt Wire

        Serial.println("Failed to find LIS3MDL chip");
        while (1)
            ;
    }

    accelerometer = gyroAccel.getAccelerometerSensor();
    gyroscope = gyroAccel.getGyroSensor();
    tempSensor = gyroAccel.getTemperatureSensor();
}
/*
    Gets the accelerometer data.

    @param data     float array of length 3 where the battery info is inserted. Data is inserted as follows : accel_X,accel_Y,accel_Z

*/
void Sensors::getAccelData(float *data)
{
#if SIMULATION_MODE
    Serial.println("%ACCEL%");
    Serial.flush();

    while (!Serial.available())
        ;

    data[0] = Serial.parseFloat();
    data[1] = Serial.parseFloat();
    data[2] = Serial.parseFloat();

#else

    sensors_event_t accelEvt;
    accelerometer->getEvent(&accelEvt);
    data[0] = accelEvt.acceleration.x;
    data[1] = accelEvt.acceleration.y;
    data[2] = accelEvt.acceleration.z;

#endif
}

/*
    Gets the gyroscope data.

    @param data     float array of length 3 where the battery info is inserted. Data is inserted as follows : gyro_X,gyro_Y,gyro_Z

*/
void Sensors::getGyroData(float *data)
{
#if SIMULATION_MODE
    Serial.println("%GYRO%");
    Serial.flush();

    while (!Serial.available())
        ;

    data[0] = Serial.parseFloat();
    data[1] = Serial.parseFloat();
    data[2] = Serial.parseFloat();

#else
    sensors_event_t gyroEvt;
    accelerometer->getEvent(&gyroEvt);
    data[0] = gyroEvt.gyro.x;
    data[1] = gyroEvt.gyro.y;
    data[2] = gyroEvt.gyro.z;

#endif
}



/*
    formats the sensordata in an jsonDocument

    @returns jsonDocument where all sensors are embedded in.

*/
JsonDocument Sensors::getSensorData()
{
    JsonDocument sensorData;

#ifdef SIMULATION_MODE
    sensorData["lat"] = 1000;
    sensorData["long"] = 1000;

#else
    sensorData["lat"] = myGNSS.getLatitude();
    sensorData["long"] = myGNSS.getLongitude();
    sensorData["alt"] = myGNSS.getAltitude();

#endif

    sensorData["baro"] = getBaroAltitude();

    float gyroData[3];
    float accelData[3];
    float magnetoData[3];

    getGyroData(gyroData);
    getAccelData(accelData);
    getMagnetoData(magnetoData);

    // gyroscope
    sensorData["gyroX"] = gyroData[0];
    sensorData["gyroY"] = gyroData[1];
    sensorData["gyroZ"] = gyroData[2];
    // accelerometer
    sensorData["accelX"] = accelData[0];
    sensorData["accelY"] = accelData[1];
    sensorData["accelZ"] = accelData[2];
    // magneto
    sensorData["magnetoX"] = magnetoData[0];
    sensorData["magnetoY"] = magnetoData[1];
    sensorData["magnetoZ"] = magnetoData[2];

    return sensorData;
}
