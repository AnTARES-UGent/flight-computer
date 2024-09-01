#include "IOManager.h"
#include "sensors.h"
#include "logger.h"
#include <Wire.h> //Needed for I2C to GPS

#define PREFLIGHT 0

#define COAST_TO_APOAPSIS 1
#define FALLING_FLIGHT 2
#define LANDED 3

// Defined in main.cpp
extern IOManager ioManager; 
extern Sensors sensorManager; 
extern Logger logger; 

class Rocket {
    public:
        int state = 0;
        int prev_alt = 0;
        int alt = 0;

        void initRocket();
        void preflight();
        void active_flight();
        void coast_to_apoapsis();
        void falling();
        void landed();

        // IOManager?
        float getSeaLevelPressure();
};