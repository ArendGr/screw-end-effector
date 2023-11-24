#include "mbed.h"
#include "ScrewEndEffectorInformatie.h"
#include "ArmInformatie.h"

#define Timer_Check     500ms //Dit is de tijd dat het programma wacht totdat er weer gekeken kan worden of een bepaalde functie is uitgevoerd

/*
* Verschilldende functies:
* 1. Pak Bit vast
* 2. Laat Bit los
* 3. Pak Schroef op
* 4. Laat Schroef los
* 5. Draai schroef aan
* 6. Draai schroef los ??Het is de vraag of deze erin blijft??
* 7. Controleren lengte schroef
* 8. Schroef Aanwezig? BOOL
*/

int main()
{
    // Initialise the digital pin LED1 as an output
#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;
#endif

    while (true) {
        led = !led;
        ThisThread::sleep_for(Timer_Check);
    }
}


bool PakBitVast() {

}
