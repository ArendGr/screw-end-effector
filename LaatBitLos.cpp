#include "ScrewEndEffectorInformatie.h"

void LaatBitLos(ScrewEndEffectorInformatie& screwendeffector) 
{
    while (screwendeffector.get_SchroefAandrukStatus() == 1) // zo lang er geen druk op de kop is
    {
        // arm gaat naar benenden 
    }

    screwendeffector.set_BitjesKlemOpen(true); // zet de bitjes klem open

    // arm gaat naar boven

    wait_ns(3000); // wacht 3 seconden

    // zet arm stil

    screwendeffector.set_BitjesKlemOpen(false); // zet de bitjes klem dicht
}