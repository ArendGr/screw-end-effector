#include "ScrewEndEffectorInformatie.h"

void CheckSchroefData(ScrewEndEffectorInformatie& screwendeffector) 
{
    enum Schroefstatus { GeenBitjeAanwezig, BitjeAanwezig, SchroefAanwezig};
    int schroeflengte = 100;

    while (screwendeffector.get_SchroefTouch() == false) // zo lang de schroef plaat niet aangeraakt is
    {
        schroeflengte --;
        // arm gaat 1 mm naar benenden 
    }

    // arm gaat schroeflengte naar boven

    switch(Schroefstatus) 
    {
        case GeenBitjeAanwezig:
            screwendeffector.set_BitjeAanweezig(false);
            break;
        case BitjeAanwezig:
            screwendeffector.set_BitjeAanweezig(true);
            break;
        case SchroefAanwezig:
            screwendeffector.set_BitjeAanweezig(true);
            screwendeffector.set_Schroefaanwezig(true);
            break;
    }

}