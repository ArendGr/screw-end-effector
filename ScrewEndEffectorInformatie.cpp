#include "ScrewEndEffectorInformatie.h"

bool ScrewEndEffectorInformatie::pick_bitje()
{
    set_RPMmotor(10);
    set_BitjesKlemOpen(true);
    if (bithandler.get_pressure(SchroefAandrukStatus))
    {
        set_RPMmotor(0);
        set_BitjesKlemOpen(false);
        return true;
    }

    else 
    {
        return false;
    }

}

bool ScrewEndEffectorInformatie::drop_bitje()
{
    set_BitjesKlemOpen(false);
    if (bithandler.get_pressure(SchroefAandrukStatus))
    {
        set_BitjesKlemOpen(true);
        return true;
    }

    else 
    {
        return false;
    }
}

bool ScrewEndEffectorInformatie::pick_screw()
{
    set_RPMmotor(10);
    if (bithandler.get_pressure(SchroefAandrukStatus))
    {
        set_RPMmotor(0);
        return true;
    }

    else 
    {
        return false;
    }
}

 

bool ScrewEndEffectorInformatie::do_measurement(Positie posietie)
{
    if (conductorsensor.get_Touch() == true)
    {
        double measurement = conductorsensor.calculate_Length(posietie.y);

        if (measurement == BitjesLengte) // als het meet resultaat gelijk is aan lengte van het bitje
        { 
            BitjeAanweezig = true; // bitje is aanweezig 
            SchroefAanweezig = false; // Schroef is niet aanweezig
        }

        else if (measurement > (BitjesLengte + 1)) // anders als het meet resultaat gelijk is aan de lengte van de schroef en het bitje
        { 
            BitjeAanweezig = true; // bitje is aanweezig
            SchroefAanweezig = true; // Schroef is aanweezig
            SchroefLengte = measurement - BitjesLengte;
        }

        else if (measurement == 0) // anders als het meetrsultaat gelijk is aan nul
        { 
            BitjeAanweezig = false; // bitje is niet aanweezig
            SchroefAanweezig = false; // Schroef is niet aanweezig
        }

        return true;
    }

    else 
    {
        return false;
    }
}

bool ScrewEndEffectorInformatie::calibrate_measurement(Positie posietie)
{
    if (conductorsensor.get_Touch() == true) 
    {
        conductorsensor.calibrate(posietie.y);
        return true;
    }
    
    else 
    {
        return false;
    }
}

// Dit is het tweede gedeelte van de setters

void ScrewEndEffectorInformatie::set_BitjesKlemOpen( bool bitjesklemopen )
{
    BitjesKlemOpen = bitjesklemopen;
}

void ScrewEndEffectorInformatie::set_RPMmotor(double rpmmotor) {
    RPMmotor = rpmmotor;
}

void ScrewEndEffectorInformatie::set_SchroefAandrukStatus(int schroefaandrukstatus) {
    SchroefAandrukStatus = schroefaandrukstatus;
}

void ScrewEndEffectorInformatie::set_SchroefLengte(int schroeflengte) {
    SchroefLengte = schroeflengte;
}

void ScrewEndEffectorInformatie::set_Schroefaanwezig(bool schroefaanweezig) {
    SchroefAanweezig = schroefaanweezig;
}

void ScrewEndEffectorInformatie::set_BitjeAanweezig(bool bitjeaanweezig) {
    BitjeAanweezig = bitjeaanweezig;
}