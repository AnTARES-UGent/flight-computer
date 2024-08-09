#ifndef ROCKET_C
#define ROCKET_C

#include "rocket.h"



/*
    initialisation of the rocket, initialises I/O, gets sea level perssure and initialises the sensors.

*/
void Rocket::initRocket()
{   
    Wire.begin();
    ioManager.init();

    // TODO GET SEA LEVEL INFO
    float pressure = getSeaLevelPressure();

    sensorManager.initSensors(pressure);
}



/*
    Rocket is waiting at the launchpad
*/
void Rocket::preflight()
{
    logger.log("preflight", "preflight");
    ioManager.log(sensorManager.getSensorData(), 2, 0);

    // preflight checks
    int current_alt = sensorManager.getBaroAltitude();

    if (current_alt - prev_alt > 10)
    { // TODO SET THRESHHOLD + decide if to use here and not await_launch
        state = ACTIVE_FLIGHT;
    }
    prev_alt = current_alt;
}

// TODO decide of to rename to await_launch????
void Rocket::active_flight()
{
    ioManager.log(sensorManager.getSensorData(), 2, 0);
    // waiting on the launchpad and powered flight
}



/*

    When launched, this routine will execute until the rocket has reached apoapsis.
*/
void Rocket::coast_to_apoapsis()
{

    ioManager.log(sensorManager.getSensorData(), 2, 0);

    int current_alt = sensorManager.getBaroAltitude();

    if (current_alt - prev_alt < 0)
    { // TODO SET THRESHHOLD

        state = FALLING;
    }
    prev_alt = current_alt;
}


/*
    Executes when the rocket has reached apoapsis and is falling back down.
*/
void Rocket::falling()
{
    ioManager.log(sensorManager.getSensorData(), 2, 0);

    int current_alt = sensorManager.getBaroAltitude();

    if (abs(current_alt - prev_alt) < 10) // TODO CHANGE TRIGGER
    {                                     // TODO SET THRESHHOLD

        ioManager.closeOnBoardStorage(); // TODO TEST
        state = LANDED;
    }
    prev_alt = current_alt;
    // falling from apoapsis
}



/*
    Executes when the rocket has landed.

*/
void Rocket::landed()
{

    ioManager.log(sensorManager.getSensorData(), 2, 0);

    delay(1000);
}

// TODO MAYBE ADD SOME CONFIRMATION
/*
    gets the sealevel pressure for the barometer.
    
*/
float Rocket::getSeaLevelPressure()
{

    double pressure = 0.0;

    ioManager.log("msg", "req_sea", 1, 0);
    JsonDocument pressure_obj = ioManager.slowBsonReceive();

    if (pressure_obj.containsKey("pressure"))
    {
        pressure = pressure_obj["pressure"];
    }

    // this is with ack checks
    /*do
    {
        ioManager.log("msg", "req_sea", 1, 0);
        BSONObject pressure_obj = ioManager.slowBsonReceive();

        if (pressure_obj.getField("pressure").isDouble())
        {
            pressure = pressure_obj.getField("pressure").getDouble();
        }

        ioManager.log("check", pressure, 1, 0);

        BSONObject pressure_obj = ioManager.slowBsonReceive();

        if (pressure_obj.getField("ack").getString() == "K")
        {
            requestingPressure = false;
        }

    } while (requestingPressure);*/

    // ioManager.log("msg","req_sea", 1, 0);
    return pressure;
}

#endif // ROCKET_C