#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"


void core1_main();
// main functie van core 0
int main()
{
    multicore_launch_core1(core1_main); //start core 1
}


// main functie van core 1
void core1_main()
{

}