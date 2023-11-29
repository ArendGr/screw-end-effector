#include "ScrewEndEffectorInformatie.h"

void CheckSchroefData(ScrewEndEffectorInformatie& screwendeffector) 
{
    int schroeflengte = 100;

    while (screwendeffector.get_SchroefTouch() == false) // zo lang de schroef plaat niet aangeraakt is
    {
        schroeflengte --;
        // arm gaat 1 mm naar benenden 
    }

    // arm gaat schroeflengte naar boven

    case:
}