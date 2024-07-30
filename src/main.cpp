#include <arduino.h>
#include <Wire.h> //Needed for I2C to GPS
#include <sensors.h>
#include <IOManager.h>

Sensors sensorManager;
IOManager ioManager;

int state = 0;



void init();
void preflight();
void active_flight();
void coast_to_apoapsis();
void falling();
void landed();




int main()
{

    Serial.begin(115200);
    Serial.println("SparkFun u-blox Example");

    init();

    while (true)
    {

        switch (state)
        {
        case 0:

            preflight();

            break;

        case 2:

            active_flight();

            break;

        case 3:

            coast_to_apoapsis();

            break;

        case 4:

            falling();

            break;

        case 5:

            landed();

            break;

        default:
            break;
        }
    }

    return 0;
}

void init()
{
    ioManager.init();
    // TODO GET SEA LEVEL INFO
    sensorManager.initSensors(5.2);
}

void preflight()
{
    //preflight checks 



}

void active_flight()
{
    //waiting on the launchpad and powered flight

}

void coast_to_apoapsis()
{
    //motor cutoff

}

void falling()
{

    //falling from apoapsis
}

void landed()
{
    int latlong[2];
    sensorManager.getGPSLatLong(latlong);
    //TODO TRANSMIT GPS LAT LONG
    delay(1000);

}