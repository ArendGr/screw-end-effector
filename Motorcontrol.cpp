#include "mbed.h"
#include "ScrewEndEffectorInformatie.h"
#include "Motorcontrol.h"

// In de hieronder geschreven code wordt gebruikt gemaakt van het woord "motor", hiermee wordt de motor bedoelt die de schroef moet laten draaien
enum AandraaiStatus{ idle, ZachtDraaien, NormaalDraaien, HardDraaien}; // alle verschillende cases waartussen geswitched kan worden
AandraaiStatus status = idle;

ScrewEndEffectorInformatie informatie;

Timer statuscheck;

bool Schroefmoment(int& mmIngedrukt) { // Hier wordt bepaald naar welke staat van het aandraaien van schroef er moet komen te staan
    //In het geval van een foutmelding, wordt idle meegegeven met dat de schroef er niet in is gekomen, daarin wordt de motor uitgezet en wordt de boolean functie met false teruggestuurd
    if ((mmIngedrukt == 1) && (ScrewEndEffectorInformatie.get_SchroefAandrukStatus() == 0)) { // De schroef heeft nog geen contact gemaakt met het contactoppervlak, probeer het nog een keer (3x proberen maximaal)
        return false;
    }
    else if ((mmIngedrukt == 1) && (ScrewEndEffectorInformatie.get_SchroefAandrukStatus() == 1)) { // De schroef heet contact gemaakt
        AandraaiStatus AandraaiStatus_state = AandraaiStatus::NormaalDraaien;
        return true;
    }

}


bool DraaiSchroefAan(){ // De boolean geeft aan of het uitvoeren van de functie gelukt is met true

    AandraaiStatus AandraaiStatus_state = AandraaiStatus::ZachtDraaien; // Hier wordt de staat op zachtdraaien gezet (beginstand bij aanroepen van deze gehele functie)
    bool SchroefIsErin = false; // Dit geeft aan dat de schroef er nog niet in is, omdat de functie net is aangeroepen
    int mmIngedrukt = 0;
    int Fouten = 0;

    statuscheck.start(); // begin met tellen

// Hieronder staat een while loop, dit blijft aan totdat het aandraaien van de schroef gelukt is of er een foutmelding gegeven wordt
while (true) {
    /*
    * Hieronder wordt de wisseling tussen de switch cases aangestuurd
    * Eerst wordt een bepaalde tijd gewacht totdat er geswitched kan worden, dit zorgt ervoor dat er geen onverwachte uitvoeringen gedaan worden door minescule overwachte imputs
    * Dit kan in het uiteindelijke totaalsysteem aangepast worden
    */

    if (statuscheck.read_ms() > 100) { // Wacht minstens 0.1s voordat er van case geswitched kan worden
        mmIngedrukt++; // Als eerste wordt de switch van ZachtDraaien aangehouden, dan na 0.1s komt de functie hier om de status te evalueren, maar is de schroef er al wel 1mm ingedrukt
        if (!Schroefmoment(mmIngedrukt)) { 
            mmIngedrukt = mmIngedrukt - 1; // De schroef heeft nog geen contact gemaakt, probeer opnieuw
            Fouten++; // Er is +1 fout opgetreden
        }
        statuscheck.reset();
    }

    if (Fouten > 2) { // Er zijn 3 foute pogingen gemaakt, Er is iets mis, dus return met niets
        return false;
        break;
    }

    switch(status) { //Deze switchcase kan de status switchen tussen idle (niet draaien), Zachtdraaien, Normaaldraaien en Harddraaien

        case idle: // in deze staat gebeurd er niks en staat de motor uit
        informatie.set_RPMmotor(0);
        // Functie: Duw de schroef met 0 m/s aan
        if (SchroefIsErin == true) { // Als de schroef erin is, dan wordt deze boolean functie teruggeven met true, hierboven wordt de RPM al op 0 gezet
            // Functie: laat schroef los
            return true;
            break;
        }
        else {
            // Functie: haal schroef eruit
            return false;
            break;
        }

        break;
        case ZachtDraaien: // in deze staat draait de motor op gedefinieerde "langzame" snelheid
            ScrewEndEffectorInformatie.set_RPMmotor(1);
            // Functie: Duw de schroef met 0.1 m/s aan

        break;    
        case NormaalDraaien: // in deze staat draait de motor op gedefinieerde "normale" snelheid
            ScrewEndEffectorInformatie.set_RPMmotor(2);
            // Functie: Duw de schroef met 0.1 m/s aan

        break;
        case HardDraaien: // in deze staat draait de motor op gedefinieerde "snelle" snelheid
            ScrewEndEffectorInformatie.set_RPMmotor(3);
            // Functie: Duw de schroef met 0.1 m/s aan

        break;

        }
    }
}; 

AandraaiStatus AandraaiStatus_state = AandraaiStatus::idle; // Hier wordt de staat op idle gezet (eindstand).. Als de taak klaar is of er is een error mag er niet meer aangedraaid worden