#include "mbed.h"

struct Positie {
    public:
    float x;
    float y;
    float z;
};

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


private:
Positie huidige;
Positie oud;

Status Request_Status;
Status Actual_Status;
  

public:
    void set_Gemeten_Positie(Positie positie);

    double PositieVerschil(Positie huidige, Positie oud);

    Positie get_Huidige_Positie(Positie huidige);
    Positie get_Vorige_Positie(Positie oud);


    void set_Request_Status(Status status);

    Status get_Actual_Status();


};