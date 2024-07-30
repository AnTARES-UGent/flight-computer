#include <arduino.h>
#include <Wire.h> //Needed for I2C to GPS
#include <sensors.h>
#include <IOManager.h>

Sensors sensor_manager;
IOManager io_man;

int state = 0;

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
    io_man.init();

    sensor_manager.initSensors(5.2);
}

void preflight()
{
}

void active_flight()
{
}

void coast_to_apoapsis()
{
}

void falling()
{
}

void landed()
{
}