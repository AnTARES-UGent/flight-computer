#ifndef FLIGHTDATAPROCESSING_H
#define FLIGHTDATAPROCESSING_H



namespace FlightDataProcessing{



    class FlightDataProcessing{


        private:

            float altitude = -1.0;
            float pressure;
            float temperature;
            float prevAltitude;


            

            bool isAltimeterFalling();


        // couple of apoapsis detection functions, some numerical some not 
        public:
            double timeOfApoapsis();
            bool isFalling();
            double timeUntilApoapsis();


            void updateBarometer(float altitude,float pressure,float temperature);




    };


}


#endif