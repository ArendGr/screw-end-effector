#include "mbed.h"
#include "ScrewEndEffectorInformatie.h"
#include "ArmInformatie.h"
#include "Motorcontrol.h"

#define Timer_Check     500ms //Dit is de tijd dat het programma wacht totdat er weer gekeken kan worden of een bepaalde functie is uitgevoerd

ScrewEndEffectorInformatie screwEndEffectorInformatie;
ArmInformatie armInformatie;
DraaiSchroefAaninformatie DSAI;

enum Status {idle, Verwijder_schroef, Schroef_verwijderd, Verwijder_bitje, Bitje_verwijderd, Pak_bitje, bitje_opgepakt, Pak_schroef, schroef_opgepakt, schroeven};

/*
* Verschilldende functies:
* 1. Pak Bit vast
* 2. Laat Bit los
* 3. Pak Schroef op
* 4. Laat Schroef los
* 5. Draai schroef aan
* 6. Draai schroef los ??Het is de vraag of deze erin blijft??
* 7. Controleren lengte schroef
* 8. Schroef Aanwezig? BOOL
*/





int main()
{

    double schroefLengteMetBit = 15; // de lengte van een bitje en een schroef (dit dit toevoegen aan arminformatie?)
    double bitLengte = 5; // de lengte van een bitje (dit toevoegen aan arminformatie?)
    double meetTolerantie = .1; // de meet tolerantie van het systeem (dit toevoegen aan conductor sensor?)
    double meetResultaat = -1; // het opgeslagen meetresultaat

    Status status = Schroef_verwijderd; // de status ven het systeem is standaard controleren of een schroef is verijderd

    bool entry = true;

    int number_of_try = 0; // het aantal poogingen
    int max_number_of_try = 3; // het maximaal aantal poogingen

    bool startup = true; // is het stysteem aan het opstarten standaad ja

    while (number_of_try <= max_number_of_try) // terwijl het maximaal toegestaan poogingen niet overschreeden is (een stopknop toevoegen?)
    {   
        if (meetResultaat == -1) // als er geen meet resulaat is 
        {
            armInformatie.set_Request_Status(armInformatie.Meten); // zeg tegen de arm dat die moet gaan meten

            meetResultaat = screwEndEffectorInformatie.do_measurement(armInformatie.get_Huidige_Positie()); // sla het meet resultaat op
        }
        else 
        {
            switch (status)
            {
                case idle: {
                    break;
                }

                case Verwijder_bitje: // verwijder een bitje uit de kop
                {
                    if (entry)
                    {
                        armInformatie.set_Request_Status(armInformatie.Verwijder_bitje); // zeg tegen de arm dat die een bitje moet verwijderen
                        entry = false;
                    }

                    if (screwEndEffectorInformatie.drop_bitje()) // als het bitje verwijderd is
                    {
                        entry = true;
                        meetResultaat = -1; // reset het meetresultaat
                        status = Bitje_verwijderd;
                    }

                    break;
                }

                case Bitje_verwijderd: // controleer of er geen bitje in de kop zit
                {
                    if (meetResultaat < meetTolerantie) // als er geen bitje aanwezig is
                    {
                        startup = false;
                        number_of_try = 0; // reset het aantal poogingen
                        status = Pak_bitje;
                    }
                    else 
                    {
                        number_of_try ++; // tel een op bij het aantalpoogingen
                        status = Verwijder_bitje;
                    }

                    break;
                }

                case Pak_bitje: // pak een bitje
                {
                    if (entry) 
                    {
                        armInformatie.set_Request_Status(armInformatie.Pak_bitje); // zeg tegen de arm dat die een bitje moet gaan op pakken
                        entry = false;
                    }

                    if (screwEndEffectorInformatie.pick_bitje()) // als de arm klaar is met een bitje pakken
                    {  
                        entry = true;
                        meetResultaat = -1; // resten het meetresultaat
                        status = bitje_opgepakt; // zet de status op pak een schroef
                    }

                    break;
                }

                case bitje_opgepakt: // controleer of het bitje opgepakt is
                {
                    if (meetResultaat < bitLengte + meetTolerantie && meetResultaat > bitLengte - meetTolerantie) // als er een bitje in de kop zit
                    {
                        startup = false; // het systeem is klaar met opstarten
                        number_of_try = 0; // resten het aantal poogingen
                        status = Pak_schroef;
                    }
                    else if (meetResultaat >= bitLengte + meetTolerantie) // anders als er iets in de kop zit dat langer is dan een bitje
                    {
                        number_of_try = max_number_of_try + 1; // zet het aantal pogingen op maximaal
                    }
                    else
                    {
                        number_of_try ++; // tel een op bij het aantalpoogingen
                        status = Pak_bitje;
                    }

                    break;
                }

                case Verwijder_schroef: // verwijder een schroef van de kop
                {
                    if (entry)
                    {
                        armInformatie.set_Request_Status(armInformatie.Verwijder_schroef); // zeg tegen de arm dat die een schroef moet verwijderen
                        entry = false;
                    }

                    if (armInformatie.get_Actual_Status() == armInformatie.Verwijder_schroef) // als de kop zecht dat die klaar is met het verwijderen van de schroef
                    {
                        entry = true;
                        meetResultaat = -1; // reset het meetresultaat
                        status = Pak_schroef;
                    }

                    break;
                }

                case Schroef_verwijderd: // controleer of de schroef is verwijderd
                {
                    if (meetResultaat < bitLengte + meetTolerantie && meetResultaat > bitLengte - meetTolerantie) // als er geen schroef op het bitje zit
                    {
                        if (startup) // als het systeem aan het opstarten is
                        {
                            status = Bitje_verwijderd;
                        }
                        else 
                        {
                            status = Pak_schroef;
                        }
                    }
                    else if (startup && meetResultaat < meetTolerantie) // als het systeem aan het opstarten is en eer geen bitje en schroef op de kop zit
                    {
                        startup = false; // het systeem is klaar met opstarten
                        status = Pak_bitje;
                    }
                    else 
                    {
                        number_of_try ++; // tel een op bij het aantalpoogingen
                        status = Verwijder_schroef;
                    }

                    break;
                }

                case Pak_schroef: // pak een schroef op
                {
                    if (entry)
                    {
                        armInformatie.set_Request_Status(armInformatie.Pak_schroef); // zeg tegen de arm dat die een schroef moet oppakken
                        entry = false;
                    }

                    if (screwEndEffectorInformatie.pick_screw()) // als er een bitje opgepakt is
                    {
                        entry = true;
                        meetResultaat = -1; // reset het meet resultaat
                        status = schroef_opgepakt;
                    }

                    break;
                }

                case schroef_opgepakt: // controleer of de schroef is opgepakt
                {
                    if (meetResultaat < schroefLengteMetBit + meetTolerantie && meetResultaat > schroefLengteMetBit - meetTolerantie) // als de schroef is opgepakt
                    {
                        number_of_try = 0; // reset het aantal poogingen
                        status = schroeven;
                    }
                    else if (meetResultaat < bitLengte + meetTolerantie) // als er geen schroef op het bitje zit
                    {
                        number_of_try ++; // tel een op bij het aantalpoogingen
                        status = Pak_schroef;
                    }
                    else 
                    {
                        number_of_try ++; // tel een op bij het aantalpoogingen
                        status = Verwijder_schroef;
                    }

                    break;
                }

                case(schroeven):
                {
                    if (entry) {
                        DSAI.set_laatstestaat(0);
                        entry = false;
                    }

                    if (DSAI.DraaiSchroefAan() == false) {
                        number_of_try ++; // tel een op bij het aantalpoogingen
                    } else {
                        number_of_try = 0; // reset het aantal poogingen
                    }

                    if (DSAI.get_laatstestaat() == 2) {
                        DSAI.set_laatstestaat(0);
                        entry = true;
                        status = idle;
                    }
                    break;
                }
            }
        }
    }

    armInformatie.set_Request_Status(armInformatie.Wacht); // zeg dat de arm stil moet staan


}


