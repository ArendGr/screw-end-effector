//Pak bit vast

#include "mbed.h"
#include "ScrewEndEffectorInformatie.h"

void PakBitVast(ScrewEndEffectorInformatie& screwendeffector) 
{
    screwendeffector.set_BitjesKlemOpen(true); // zet de bitjes klem open

    screwendeffector.set_RPMmotor(10); // zet de motor rpm op 10 

    while (screwendeffector.get_SchroefAandrukStatus() == 1) // zo lang er geen druk op de kop is
    {
        // arm gaat naar benenden 
    }

    screwendeffector.set_BitjesKlemOpen(false); // zet de bitjesklem dicht

    screwendeffector.set_RPMmotor(0); // zet de motor rpm op 0

    // arm gaat naar boven

    wait_ns(10000); // wacht 3 seconden

    // zet arm stil
}

// laat bit los

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

// pak schroef op

#include "ScrewEndEffectorInformatie.h"

void PakSchrofOp(ScrewEndEffectorInformatie& screwendeffector) 
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

// laat schroef los

void LaatSchroefLos()
{
    // ga naar schroef schroef verwijder locatie
    // schuif de schroef in de klouw
    // ga naar boven 
}