#include "mbed.h"

class ArmInformatie { // Dit is de informatie die van de arm naar de ScrewEndEffector
public:

enum Status
{
    Wacht,
    Pak_bitje,
    Pak_schroef,
    Verwijder_bitje,
    Verwijder_schroef,
    Schroeven,
    Meten
};

void set_Request_Status(Status status);

Status get_Actual_Status();

private:

Status Request_Status;
Status Actual_Status;

double Xpozitie, Ypozitie, Zpozitie;
   
};