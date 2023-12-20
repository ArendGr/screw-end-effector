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

 

double ScrewEndEffectorInformatie::do_measurement(Positie positie)
{
    if (conductorsensor.get_Touch() == true)
    {
        SchroefLengte = conductorsensor.calculate_Length(positie.y);
        return SchroefLengte;
    }
    else {
        return -1;
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