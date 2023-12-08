#include "ScrewEndEffectorInformatie.h"


void ScrewEndEffectorInformatie::do_measurement(double posietie)
{
    while (conductorsensor.get_Touch() == false);
    double measurement = conductorsensor.calculate_Length(posietie);

    if (measurement == BitjesLengte) { // als het meet resultaat gelijk is aan lengte van het bitje
        BitjeAanweezig = true; // bitje is aanweezig 
        SchroefAanweezig = false; // Schroef is niet aanweezig
    }

    else if (measurement == (BitjesLengte + VerwachteSchroefLengte)){ // anders als het meet resultaat gelijk is aan de lengte van de schroef en het bitje
        BitjeAanweezig = true; // bitje is aanweezig
        SchroefAanweezig = true; // Schroef is aanweezig
        SchroefLengte = measurement - BitjesLengte;
    }

    else if (measurement == 0) { // anders als het meetrsultaat gelijk is aan nul
        BitjeAanweezig = false; // bitje is niet aanweezig
        SchroefAanweezig = false; // Schroef is niet aanweezig
    }
}

void ScrewEndEffectorInformatie::calibrate_measurement(double posietie)
{
    while (conductorsensor.get_Touch() == false);
    conductorsensor.calibrate(posietie);
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