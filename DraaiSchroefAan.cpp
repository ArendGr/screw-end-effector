#include "mbed.h"
#include "ScrewEndEffectorInformatie.h"

// In de hieronder geschreven code wordt gebruikt gemaakt van het woord "motor", hiermee wordt de motor bedoelt die de schroef moet laten draaien
enum AandraaiStatus{ idle, ZachtDraaien, NormaalDraaien, HardDraaien}; // alle verschillende cases waartussen geswitched kan worden

bool DraaiSchroefAan(){ // De boolean geeft aan of het uitvoeren van de functie gelukt is

while (true) {
    switch(AandraaiStatus) { //Deze switchcase kan de status switchen tussen idle, Zachtdraaien, Normaaldraaien en Harddraaien

        case idle: // in deze staat gebeurd er niks en staat de motor uit
        ScrewEndEffectorInformatie.set_RPMmotor(0);

        break;
        case ZachtDraaien: // in deze staat draait de motor op gedefinieerde "langzame" snelheid


        break;    
        case NormaalDraaien: // in deze staat draait de motor op gedefinieerde "normale" snelheid


        break;
        case HardDraaien: // in deze staat draait de motor op gedefinieerde "snelle" snelheid


        break;

        }
    }
}; 