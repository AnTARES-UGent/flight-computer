#include <arduino.h>
#include <Wire.h> //Needed for I2C to GPS
#include <sensors.h>
#include <IOManager.h>

#define PREFLIGHT 0
#define ACTIVE_FLIGHT 1
#define COAST_TO_APOAPSIS 2
#define FALLING_FLIGHT 3
#define LANDED 4

Sensors sensorManager;
IOManager ioManager;

int state = 0;
int prev_alt = 0;

void init();
void preflight();
void active_flight();
void coast_to_apoapsis();
void falling();
void landed();

float getSealevelPressure();



void log(const char *key, int32_t msg);
void warn(const char *key, int32_t msg);
void err(const char *key, int32_t msg);

void log(const char *key, const char *msg);
void warn(const char *key, const char *msg);
void err(const char *key, const char *msg);

int main()
{

    Serial.begin(115200);
    Serial.println("SparkFun u-blox Example");

    init();
    log("main", "finishing init");

    while (true)
    {

        switch (state)
        {
        case PREFLIGHT:

            preflight();

            break;

        case ACTIVE_FLIGHT:

            active_flight();

            break;

        case COAST_TO_APOAPSIS:

            coast_to_apoapsis();

            break;

        case FALLING_FLIGHT:

            falling();

            break;

        case LANDED:

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
    float pressure = getSealevelPressure();

    sensorManager.initSensors(pressure);
}

void preflight()
{
    ioManager.log(sensorManager.getSensorData(), 2);
    // preflight checks
    int current_alt = sensorManager.getBaroAltitude();

    if (current_alt - prev_alt > 10)
    { // TODO SET THRESHHOLD
        state = ACTIVE_FLIGHT;
    }
    prev_alt = current_alt;
}
// TODO DECIDE IF REMOVE OR NOT
void active_flight()
{
    ioManager.log(sensorManager.getSensorData(), 2);
    // waiting on the launchpad and powered flight
}

void coast_to_apoapsis()
{

    ioManager.log(sensorManager.getSensorData(), 2);

    int current_alt = sensorManager.getBaroAltitude();

    if (current_alt - prev_alt < 0)
    { // TODO SET THRESHHOLD
    
        state = FALLING;
    }
    prev_alt = current_alt;
}

void falling()
{
    ioManager.log(sensorManager.getSensorData(), 2);

    int current_alt = sensorManager.getBaroAltitude();

    if (abs(current_alt - prev_alt) < 10)//TODO CHANGE TRIGGER
    { // TODO SET THRESHHOLD

        ioManager.closeOnBoardStorage();//TODO TEST
        state = LANDED;
    }
    prev_alt = current_alt;
    // falling from apoapsis
}

void landed()
{
    ioManager.log(sensorManager.getSensorData(), 2);
    // TODO TRANSMIT GPS LAT LONG
    delay(1000);
}

// TODO MAYBE ADD SOME CONFIRMATION
float getSealevelPressure()
{

    bool requestingPressure = true;
    double pressure = 0.0;

    ioManager.log("msg", "req_sea", 1, 0);
    BSONObject pressure_obj = ioManager.slowBsonReceive();

    if (pressure_obj.getField("pressure").isDouble())
    {
        pressure = pressure_obj.getField("pressure").getDouble();
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



void log(const char *key, int32_t msg)
{
    ioManager.log(key, msg, 2, 0);
}

void warn(const char *key, int32_t msg)
{
    ioManager.log(key, msg, 2, 1);
}

void err(const char *key, int32_t msg)
{
    ioManager.log(key, msg, 2, 2);
}

void log(const char *key, const char *msg)
{
    ioManager.log(key, msg, 2, 0);
}

void warn(const char *key,const char *msg)
{
    ioManager.log(key, msg, 2, 1);
}

void err(const char *key, const char *msg)
{
    ioManager.log(key, msg, 2, 2);
}