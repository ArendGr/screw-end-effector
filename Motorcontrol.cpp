#include "mbed.h"
#include "ScrewEndEffectorInformatie.h"
#include "ArmInformatie.h"
#include "Motorcontrol.h"
#include <cmath>

// In de hieronder geschreven code wordt gebruikt gemaakt van het woord "motor", hiermee wordt de motor bedoelt die de schroef moet laten draaien
enum AandraaiStatus{ idle, ZachtDraaien, NormaalDraaien, HardDraaien}; // alle verschillende cases waartussen geswitched kan worden
AandraaiStatus status = idle;

ScrewEndEffectorInformatie CEEinformatie;
ArmInformatie Arminformatie;

Timer statuscheck;

bool Schroefmoment(int& mmIngedrukt) { // Hier wordt bepaald naar welke staat van het aandraaien van schroef er moet komen te staan
    //In het geval van een foutmelding, wordt idle meegegeven met dat de schroef er niet in is gekomen, daarin wordt de motor uitgezet en wordt de boolean functie met false teruggestuurd

    /*
    * SchroefAandrukStatus() van 0 betekend dat er geen druk is gedetecteerd in de sensoren
    * SchroefAandrukStatus() van 1 betekend dat er lichte druk is geidentificeerd
    * SchroefAandrukStatus() van 2 betekend dat er een ideale druk is voor het aanschroeven
    * SchroefAandrukStatus() van 3 betekend dat er een te hoge druk is voor het aanschroeven
    */
    
    if ((mmIngedrukt == 1) && (CEEinformatie.get_SchroefAandrukStatus() == 0)) { // De schroef heeft nog geen contact gemaakt met het contactoppervlak, probeer het nog een keer (3x proberen maximaal)
        return false;
    }
    else if ((mmIngedrukt == 1) && (CEEinformatie.get_SchroefAandrukStatus() < 1)) { // De schroef heeft contact gemaakt
        status = AandraaiStatus::NormaalDraaien;
        return true;
    }

    if (() && ()) {


    }

    if (() && ()) {


    }

}

double ArmDuwSnelheid () {

}


void DraaiSchroefAan(){ // De boolean geeft aan of het uitvoeren van de functie gelukt is met true

    status = AandraaiStatus::ZachtDraaien; // Hier wordt de staat op zachtdraaien gezet (beginstand bij aanroepen van deze gehele functie)
    bool SchroefIsErin = false; // Dit geeft aan dat de schroef er nog niet in is, omdat de functie net is aangeroepen
    int mmIngedrukt = 0;
    int Fouten = 0;
    bool fout = false;

    statuscheck.start(); // begin met tellen

// Hieronder staat een while loop, dit blijft aan totdat het aandraaien van de schroef gelukt is of er een foutmelding gegeven wordt
while (true) {
    /*
    * Hieronder wordt de wisseling tussen de switch cases aangestuurd
    * Eerst wordt een bepaalde tijd gewacht totdat er geswitched kan worden, dit zorgt ervoor dat er geen onverwachte uitvoeringen gedaan worden door minescule overwachte imputs
    * Dit kan in het uiteindelijke totaalsysteem aangepast worden
    */

    if (statuscheck.read_ms() > 50) { // Wacht minstens 0.05s voordat er van case geswitched kan worden
        mmIngedrukt++; // Als eerste wordt de switch van ZachtDraaien aangehouden, dan na 0.1s komt de functie hier om de status te evalueren, maar is de schroef er al wel 1mm ingedrukt
        if (!Schroefmoment(mmIngedrukt)) { 
            mmIngedrukt = mmIngedrukt - 1; // De schroef heeft nog geen contact gemaakt, probeer opnieuw
            fout = true;
            Fouten++; // Er is +1 fout opgetreden
        }
        else { 
            fout = false; 
            if (Fouten > 0) {Fouten = 0;} // als er geen fout is en de vorige keer was er wel een fout, begint de teller weer bij 0
        }

        statuscheck.reset();
    }

    if ((Fouten > 2) && fout) { // Er zijn 3 foute pogingen achter elkaar gemaakt, Er is iets mis, nu gaat het programma uit de functie, hier moet later een error functie voor komen
        return;
    }

    switch(status) { //Deze switchcase kan de status switchen tussen idle (niet draaien), Zachtdraaien, Normaaldraaien en Harddraaien

        case idle: // in deze staat gebeurd er niks en staat de motor uit
        CEEinformatie.set_RPMmotor(0); // dit is 0% rpm speed
        // Functie: Duw de schroef met 0 m/s aan
        if (SchroefIsErin == true) { // Als de schroef erin is, dan wordt deze boolean functie teruggeven met true, hierboven wordt de RPM al op 0 gezet
            // Functie: laat schroef los
            return;
        }

        break;
        case ZachtDraaien: // in deze staat draait de motor op gedefinieerde "langzame" snelheid
            CEEinformatie.set_RPMmotor(20); // dit is 20% rpm speed
            // Functie: Duw de schroef met 0.1 m/s aan

        break;    
        case NormaalDraaien: // in deze staat draait de motor op gedefinieerde "normale" snelheid
            CEEinformatie.set_RPMmotor(50); // dit is 50% rpm speed
            // Functie: Duw de schroef met 0.1 m/s aan

        break;
        case HardDraaien: // in deze staat draait de motor op gedefinieerde "snelle" snelheid
            CEEinformatie.set_RPMmotor(80); // dit is 80% rpm speed
            // Functie: Duw de schroef met 0.1 m/s aan

        break;

        }
    }
    status = AandraaiStatus::idle; // Hier wordt de staat op idle gezet (eindstand).. Als de taak klaar is of er is een error mag er niet meer aangedraaid worden
}; 

