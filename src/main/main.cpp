#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "bmp280.h"
#include "flightDataProcessing.h"
//sensors
BMP280 barometer; 
FlightDataProcessing::FlightDataProcessing dataProcessing;



//functions
void core1_main();
void pullDataFromSensors();


// main function of core 0
int main()
{
    multicore_launch_core1(core1_main); //start core 1
}


// main function of core 1
void core1_main()
{

}



void preFlightChecks(){
    //template/dummy 


    
}

void updateData(){

    //reading barometer
    float altitude    = barometer.getAltitude();
    float pressure    = barometer.getPressure();
    float temperature = barometer.getTemperature();

    dataProcessing.updateBarometer(altitude,pressure,temperature);


}