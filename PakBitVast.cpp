#include "ScrewEndEffectorInformatie.h"

bool PakBitVas(ScrewEndEffectorInformatie screwendeffector) 
{
    screwendeffector.set_BitjesKlemOpen(true);
    screwendeffector.set_RPMmotor(10);
    bool PositieBereikt = false;

    while (!PositieBereikt) 
    {
    // arm gaat 1 mm naar benenden 
    
        if (screwendeffector.get_SchroefAandrukStatus() <= 2) 
        {
            screwendeffector.set_BitjesKlemOpen(false);
            screwendeffector.set_RPMmotor(0);
            PositieBereikt = true;
        }
    
    }
    // arm gaat naar boven
}