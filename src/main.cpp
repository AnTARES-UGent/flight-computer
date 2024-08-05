#include <Arduino.h>
#include <Wire.h> //Needed for I2C to GPS

#include "sensors.h"
#include "IOManager.h"
#include "rocket.h"
#include "logger.h"

IOManager ioManager;
Rocket rocket;
Logger logger;
Sensors sensorManager;

void setup()
{

#ifdef SIMULATION_MODE

    Serial.begin(115200);
    Serial.println("SIMULATION_MODE");
    while (!Serial.available())
        ;
    Serial.parseInt(); // small thingy so that we wait until the simulator is detected
    rocket.state = PREFLIGHT;

    rocket.prev_alt = 9;
#else
    rocket.initRocket();
    logger.log("main", "finishing init");
    rocket.prev_alt = sensorManager.getBaroAltitude();

#endif
}

void loop()
{

    /*#ifdef SIMULATION_MODE
      Serial.println("%STATE%");
       Serial.flush();

       while (!Serial.available());
       int read_state = Serial.parseInt();

       if(read_state >=0){
           state = read_state;
       }


   #endif*/

    switch (rocket.state)
    {
    case PREFLIGHT:

        rocket.preflight();

        break;

    case ACTIVE_FLIGHT:

        rocket.active_flight();

        break;

    case COAST_TO_APOAPSIS:

        rocket.coast_to_apoapsis();

        break;

    case FALLING_FLIGHT:

        rocket.falling();

        break;

    case LANDED:

        rocket.landed();

        break;

    default:
#ifdef SIMULATION_MODE
        Serial.println("default");
#endif
        break;
    }
}