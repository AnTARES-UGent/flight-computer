
#include <flightDataProcessing.h>
namespace FlightDataProcessing{
    

    //public functions
    double FlightDataProcessing::timeOfApoapsis(){

    }


    bool FlightDataProcessing::isFalling(){
        return this->isAltimeterFalling();
    }


    double FlightDataProcessing::timeUntilApoapsis(){
        // TODO read gyro data
        float xAcceleration = 0.0;
        float yAcceleration = 0.0;
        float zAcceleration = 0.0;


        


    }







    void FlightDataProcessing::updateBarometer(float altitude,float pressure,float temperature){

        this->prevAltitude  = this->altitude;

        this->altitude      = altitude;
        this->pressure      = pressure;
        this->temperature   = temperature;
    }


    // private functions
    bool FlightDataProcessing::isAltimeterFalling(){
        return this->prevAltitude > this->altitude;
    }
    


}