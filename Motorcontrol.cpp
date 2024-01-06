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
Positie positie;

Timer statuscheck;

 /*
    * SchroefAandrukStatus() van 0 betekend dat er geen druk is gedetecteerd in de sensoren
    * SchroefAandrukStatus() van 1 betekend dat er lichte druk is geidentificeerd
    * SchroefAandrukStatus() van 2 betekend dat er een ideale druk is voor het aanschroeven
    * SchroefAandrukStatus() van 3 betekend dat er een te hoge druk is voor het aanschroeven
    */

bool Schroefmoment() {// Hier wordt bepaald naar welke staat van het aandraaien van schroef er moet komen te staan
    //In het geval van een foutmelding, wordt idle meegegeven met dat de schroef er niet in is gekomen, daarin wordt de motor uitgezet en wordt de boolean functie met false teruggestuurd

    // Meet de afstand tussen de huidige en vorige positie
    double schroeflengte;
    double afstandsverschil = Arminformatie.PositieVerschil(Arminformatie.get_Huidige_Positie(), Arminformatie.get_Vorige_Positie(positie));

    bool goedbezig;
    switch(CEEinformatie.get_SchroefAandrukStatus()) {
        case 0:
            if (status == idle) {
            // geen contact en de schroevendraaier draait niet
            goedbezig = false; // probeer opnieuw 
            }
            else if (status == ZachtDraaien) {
            // geen contact gemaakt en de schroevendraaier draait zacht, probeer opnieuw, geen foutmelding
            goedbezig = true;
            }
            else { 
            // geen reden om te controleren voor specefiek normaal of harddraaien, als de schroef nog geen contact heeft gemaakt, mag de schroefendraaier niet harder dan zacht
            status = AandraaiStatus::idle;
            goedbezig = false; // probeer opnieuw
            }
        break;
        case 1:
            if (status == idle) {
            // de schroef is niet aan het draaien, maar er wordt wel lichte druk gedetecteerd
            status = AandraaiStatus::ZachtDraaien;
            goedbezig = true;
            }
            else if (status == ZachtDraaien) {
            // er is contact gemaakt, probeer nu normaal te draaien
            status = AandraaiStatus::NormaalDraaien;
            goedbezig = true;
            }
            else if (status == NormaalDraaien) {
            // geen harde druk en het draaien gaat lekker, ga verder
            goedbezig = true;
            }
            else if (status == HardDraaien) {
            // geen harde druk en het draaien gaat lekker, ga verder
            goedbezig = true;    
            }
        break;
         case 2:
            if (status == idle) {
            // de schroef is niet aan het draaien en er is normale druk, gooi foutmelding
            goedbezig = false;
            }
            else if (status == ZachtDraaien) {
            // de schroef is zachtjes ergens in aan het draaien en er is normale druk gedetecteerd. draai nu op normale snelheid    
            status = AandraaiStatus::NormaalDraaien;    
            goedbezig = true;    
            }
            else if (status == NormaalDraaien) {
            // de schroef is op normale snelheid met normale druk aan het schroeven, draai nu op harde snelheid
            status = AandraaiStatus::HardDraaien;
            goedbezig = true;
            }
            else if (status == HardDraaien) {
            // de schroef is nu hard aan het draaien met normale druk, ga zo door
            goedbezig = true;    
            }
        break;
         case 3:
            if (status == idle) {
            // de schroef draait niet maar er is een harde druk gedetecteerd. gooi foutmelding
            goedbezig = false;
            }
            else if (status == ZachtDraaien) {
                if(afstandsverschil > (schroeflengte - 0.001)) {
                    // de schroef is erin!
                    status = AandraaiStatus::idle;
                    goedbezig = true;
                } else {
                    // de schroef is er nog in, maar is wel een hoge druk, doe niks
                    status = AandraaiStatus::idle;
                    goedbezig = false;
                }

            }
            else if (status == NormaalDraaien) {
                if(afstandsverschil > (schroeflengte - 0.001)) {
                    // de schroef is erin!
                    status = AandraaiStatus::idle;
                    goedbezig = true;
                } else {
                    // de schroef is er nog in, maar is wel een hoge druk, probeer zacht te draaien
                    status = AandraaiStatus::ZachtDraaien;
                    goedbezig = true;
                }
            }
            else if (status == HardDraaien) {
                // de schroef is hard aan het draaien met een te hoge druk, ga zachter draaien, geen foutmelding
                status = AandraaiStatus::NormaalDraaien;
                    goedbezig = true;
            }
        break;
    }

    return goedbezig;
}


void DraaiSchroefAan() { // De boolean geeft aan of het uitvoeren van de functie gelukt is met true

    status = AandraaiStatus::ZachtDraaien; // Hier wordt de staat op zachtdraaien gezet (beginstand bij aanroepen van deze gehele functie)
    bool SchroefIsErin = false; // Dit geeft aan dat de schroef er nog niet in is, omdat de functie net is aangeroepen
    int Fouten = 0;
    bool fout = false;
    bool aangeraakt = false;
    double schroeflengte;
    Positie start; // start positie
    Positie huidige; // huidige positie
    statuscheck.start(); // begin met tellen
    double verschil = 0; 
    bool error = false; // geen errors

// Hieronder staat een while loop, dit blijft aan totdat het aandraaien van de schroef gelukt is of er een foutmelding gegeven wordt
while ((verschil <= schroeflengte) && !error) {
    /*
    * Hieronder wordt de wisseling tussen de switch cases aangestuurd
    * Eerst wordt een bepaalde tijd gewacht totdat er geswitched kan worden, dit zorgt ervoor dat er geen onverwachte uitvoeringen gedaan worden door minescule overwachte imputs
    * Dit kan in het uiteindelijke totaalsysteem aangepast worden
    */
    if (!aangeraakt && CEEinformatie.get_SchroefAandrukStatus() == 1) {

        // Als er nog geen eerder contact gemaakt is, en er wordt voor het eerst een druk gemeten, dan wordt de positie vastgelegd
        // vervolgens wordt met deze informatie de positieverschil berekend

        Arminformatie.set_Start();
        start = Arminformatie.get_Start();
        aangeraakt = true;
    } else if (aangeraakt) {
        huidige = Arminformatie.get_Huidige_Positie();
        verschil = abs(sqrt(pow(huidige.x - start.x, 2) + pow(huidige.y - start.y, 2) + pow(huidige.z - start.z, 2)));
    } 


    if (statuscheck.read_ms() > 50) { // Wacht minstens 0.05s voordat er van case geswitched kan worden    
        if (!Schroefmoment()) { 
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
        error = true;
        return;
        break;
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

