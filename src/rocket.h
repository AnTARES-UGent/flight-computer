#include "IOManager.h"
#include "sensors.h"
#include "logger.h"

#define PREFLIGHT 0
#define ACTIVE_FLIGHT 1
#define COAST_TO_APOAPSIS 2
#define FALLING_FLIGHT 3
#define LANDED 4

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