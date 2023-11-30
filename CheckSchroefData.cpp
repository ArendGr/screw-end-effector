#include "ScrewEndEffectorInformatie.h"

bool CheckSchroefData(ScrewEndEffectorInformatie& screwendeffector) 
{
    enum Schroefstatus { GeenBitjeAanwezig, BitjeAanwezig, SchroefAanwezig};
    Schroefstatus schroefstatus = GeenBitjeAanwezig;
    int schroeflengte = 100;

    while (screwendeffector.get_SchroefTouch() == false) // zo lang de schroef plaat niet aangeraakt is
    {
        schroeflengte --;
        // arm gaat 1 mm naar benenden 
    }

    // arm gaat schroeflengte naar boven

    if (schroeflengte == screwendeffector.BitjesLengte) {
        schroefstatus = BitjeAanwezig;
    }

    else if (schroeflengte == (screwendeffector.BitjesLengte + screwendeffector.VerwachteSchroefLengte)){
        schroefstatus = SchroefAanwezig;
    }

    else if (schroeflengte == 0) {
        schroefstatus = GeenBitjeAanwezig;
    }

    else {
        return false;
    }


    switch(schroefstatus)
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
            screwendeffector.set_SchroefLengte(schroeflengte);
            return true;

    }

}