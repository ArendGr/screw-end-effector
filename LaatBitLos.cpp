#include "ScrewEndEffectorInformatie.h"

void PakBitVas(ScrewEndEffectorInformatie screwendeffector) 
{
    bool PositieBereikt = false;

    while (!PositieBereikt) 
    {
        // arm gaat 1 mm naar benenden 

        if (screwendeffector.get_SchroefAandrukStatus() <= 2) 
        {
            screwendeffector.set_BitjesKlemOpen(true);
            PositieBereikt = true;
        }
    
    }

    // arm gaat naar boven

    screwendeffector.set_BitjesKlemOpen(false);
}