#include "ScrewEndEffectorInformatie.h"

bool CheckSchroefData(ScrewEndEffectorInformatie& screwendeffector) 
{
    enum MeetStatus { GeenBitjeAanwezig, BitjeAanwezig, SchroefAanwezig};
    MeetStatus meetstatus = GeenBitjeAanwezig;

    // arm moet 100 mm boven de conductor plaat
    int meetresultaatinmm = 100; // het meetresultaat is 100mm

    while (screwendeffector.get_SchroefTouch() == false) // zo lang de schroef plaat niet aangeraakt is
    {
        meetresultaatinmm --; // het meet resultaat word 1 kleiner
        // arm gaat 1 mm naar benenden 
        thread_sleep_for(100); // wacht 0.1 seconden
    }

    // arm gaat terug naar start pozietie

    if (meetresultaatinmm == screwendeffector.BitjesLengte) { // als het meet resultaat gelijk is aan lengte van het bitje
        meetstatus = BitjeAanwezig; // de meet status is bitje aanwaanwezig 
    }

    else if (meetresultaatinmm == (screwendeffector.BitjesLengte + screwendeffector.VerwachteSchroefLengte)){ // anders als het meet resultaat gelijk is aan de lengte van de schroef en het bitje
        meetstatus = SchroefAanwezig; // de meet status is schroef aanwaanwezig 
    }

    else if (meetresultaatinmm == 0) { // anders als het meetrsultaat gelijk is aan nul
        meetstatus = GeenBitjeAanwezig; // de meet status is geen bitje aanwezig
    }

    else { // anders 
        return false; // geef fout terug
    }


    switch(meetstatus)
    {
        case GeenBitjeAanwezig:

            screwendeffector.set_BitjeAanweezig(false);
            screwendeffector.set_Schroefaanwezig(false);
            return true;

        case BitjeAanwezig:

            screwendeffector.set_BitjeAanweezig(true);
            screwendeffector.set_Schroefaanwezig(false);
            return true;

        case SchroefAanwezig:

            screwendeffector.set_BitjeAanweezig(true);
            screwendeffector.set_Schroefaanwezig(true);
            screwendeffector.set_SchroefLengte(meetresultaatinmm);
            return true;

    }

}