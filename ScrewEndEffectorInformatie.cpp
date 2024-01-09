#include "ScrewEndEffectorInformatie.h"

bool ScrewEndEffectorInformatie::pick_bitje()
{
    set_RPMmotor(10); // zet de rpm van de motor op 10

    set_BitjesKlemOpen(true); // zet de klem van de bitjes houder open

    if (bithandler.get_pressure(SchroefAandrukStatus)) // als er druk op de kop is
    {
        set_RPMmotor(0); // zet de motor rpm op 0

        set_BitjesKlemOpen(false); // zet de klem van de bitjes houder dicht

        return true; // return dat het oppakken voltooid is
    }
    else 
    {
        return false; // return dat het oppakken nog niet voltooid is
    }

}

bool ScrewEndEffectorInformatie::drop_bitje()
{
    set_BitjesKlemOpen(false); // zet de bitjes klem dicht

    if (bithandler.get_pressure(SchroefAandrukStatus)) // als er duk op de kop is
    {
        set_BitjesKlemOpen(true); // zet de bitjes kelm open

        return true; // return dat het bitje verwijderen voltooid is
    }
    else 
    {
        return false; // return dat het bitje verwijderen nog niet voltooid is
    }
}

bool ScrewEndEffectorInformatie::pick_screw()
{
    set_RPMmotor(10); // zet de motor rpm op 10

    if (bithandler.get_pressure(SchroefAandrukStatus)) // als er druk op de kop is
    {
        set_RPMmotor(0); // zet de motor rpm op 0

        return true; // return dat het schroef oppakken voltooid is
    }
    else 
    {
        return false; // return dat ht schroef oppakken nog niet voltooid is
    }
}

 

double ScrewEndEffectorInformatie::do_measurement(Positie positie)
{
    if (conductorsensor.get_Touch()) // als of de schroef aangeraakt is
    {
        SchroefLengte = conductorsensor.calculate_Length(positie.y); // bereken de schroef lengte met de pozitie van de arm in de y richting


        return SchroefLengte; // geef de schroef lengte terug
    }
    else {
        return -1;
    }
}

bool ScrewEndEffectorInformatie::calibrate_measurement(Positie posietie)
{
    if (conductorsensor.get_Touch()) // als de kop aangeraakt is
    {
        conductorsensor.calibrate(posietie.y); // calibreer de sensor  met de pozitie van de arm in de y richting

        return true; // return dat het clalibreren voltooid is
    }
    else 
    {
        return false; // return dat het calibreren nog niet voltooid is
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

void ScrewEndEffectorInformatie::set_SchroefTouch(bool SchroefTouch) {
    SchroefTouch = Schroeftouch;
}

void ScrewEndEffectorInformatie::set_Schroefaanwezig(bool schroefaanweezig) {
    SchroefAanweezig = schroefaanweezig;
}

void ScrewEndEffectorInformatie::set_BitjeAanweezig(bool bitjeaanweezig) {
    BitjeAanweezig = bitjeaanweezig;
}