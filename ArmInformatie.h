#include "mbed.h"

struct Positie { //Dit is de positie van het uiteinde van de robotarm waar de ScrewEndEffector op komt te zitten
    public:
    float x;
    float y;
    float z;
};

class ArmInformatie { // Dit is de informatie die van de arm naar de ScrewEndEffector
public:

enum Status { // Dit zijn de functies die de arm kan oproepen om uitgevoerd te worden
              // In dit programma wordt een arm gesimuleerd omdat er geen fysieke arm is om te te gebruiken, dus de functies worden in de main aangeroepen
    Wacht,
    Pak_bitje,
    Pak_schroef,
    Verwijder_bitje,
    Verwijder_schroef,
    Schroeven,
    Meten
};


private:
Positie huidige; // Dit is de huidige positie van de armkop
Positie oud;     // Dit is de vorige positie van de armkop
Positie Start;   // Dit is de startpositie van de armkop

Status Request_Status; // Dit is de status die verzocht is
Status Actual_Status; // Dit is de status die op het huidige moment gaande is
  

public:
// setters
    void set_Gemeten_Positie(Positie positie); //setter gemeten positie
    void set_Start(); //setter start positie
    void set_Request_Status(Status status); // setter request status

    double PositieVerschil(Positie huidige, Positie oud); // hier wordt het positieverschil berekend tussen de huidige positie en de vorige positie

// getters
    Positie get_Huidige_Positie(); // getter huidige positie
    Positie get_Vorige_Positie(Positie oud); // getter vorige positie
    Positie get_Start(); // getter startpositie
    Status get_Actual_Status(); // getter huidig actieve status


};