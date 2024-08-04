#ifndef ROCKET_C
#define ROCKET_C

#include "rocket.h"

void Rocket::initRocket()
{
    ioManager.init();

    // TODO GET SEA LEVEL INFO
    float pressure = getSeaLevelPressure();

    sensorManager.initSensors(pressure);
}

void Rocket::preflight()
{
    logger.log("preflight", "prefligth");
    ioManager.log(sensorManager.getSensorData(), 2, 0);

    // preflight checks
    int current_alt = sensorManager.getBaroAltitude();

    if (current_alt - prev_alt > 10)
    { // TODO SET THRESHHOLD
        state = ACTIVE_FLIGHT;
    }
    prev_alt = current_alt;
}

// TODO DECIDE IF REMOVE OR NOT
void Rocket::active_flight()
{
    ioManager.log(sensorManager.getSensorData(), 2, 0);
    // waiting on the launchpad and powered flight
}

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

void Rocket::landed()
{

    ioManager.log(sensorManager.getSensorData(), 2, 0);

    delay(1000);
}

// TODO MAYBE ADD SOME CONFIRMATION
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