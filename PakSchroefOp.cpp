#include "ScrewEndEffectorInformatie.h"

void PakSchrofOp(ScrewEndEffectorInformatie screwendeffector) 
{
    screwendeffector.set_RPMmotor(10); // zet de motor rpm op 10 

    while (screwendeffector.get_SchroefAandrukStatus() == 1) // zo lang er geen druk op de kop is
    {
        // arm gaat naar benenden 
    }

    screwendeffector.set_RPMmotor(0); // zet de motor rpm op 0

    // arm gaat naar boven

    wait_ns(10000); // wacht 3 seconden

    // zet arm stil
} 