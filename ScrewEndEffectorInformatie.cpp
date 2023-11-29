#include "ScrewEndEffectorInformatie.h"
// Dit is het tweede gedeelte van de setters

void ScrewEndEffectorInformatie::set_BitjesKlemOpen( bool bitjesklemopen )
{
    BitjesKlemOpen = bitjesklemopen;
}

void ScrewEndEffectorInformatie::set_SchroefTouch(bool schroeftouch) {
    SchroefTouch = schroeftouch;
}

void ScrewEndEffectorInformatie::set_RPMmotor(double rpmmotor) {
    RPMmotor = rpmmotor;
}

void ScrewEndEffectorInformatie::set_SchroefAandrukStatus(int schroefaandrukstatus) {
    SchroefAandrukStatus = schroefaandrukstatus;
}

void ScrewEndEffectorInformatie::set_SchroefLengte(double schroeflengte) {
    SchroefLengte = schroeflengte;
}

void ScrewEndEffectorInformatie::set_Schroefaanwezig(bool schroefaanweezig) {
    SchroefAanweezig = schroefaanweezig;
}

void ScrewEndEffectorInformatie::set_BitjeAanweezig(bool bitjeaanweezig) {
    BitjeAanweezig = bitjeaanweezig;
}