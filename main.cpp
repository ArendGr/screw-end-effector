#include "mbed.h"
#include "ScrewEndEffectorInformatie.h"
#include "ArmInformatie.h"

#define Timer_Check     500ms //Dit is de tijd dat het programma wacht totdat er weer gekeken kan worden of een bepaalde functie is uitgevoerd

ScrewEndEffectorInformatie screwEndEffectorInformatie;
ArmInformatie armInformatie;

enum Status {defalt, Verwijder_schroef, Verwijder_bitje, Schroef_verwijderd, Pak_bitje, bitje_opgepakt, Pak_schroef, schroef_opgepakt, schroeven};
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

    double schroefLengteMetBit = 15;
    double bitLengte = 5;
    double meetTolerantie = .1;
    double meetResultaat = -1;

    Status status = defalt;

    bool entry = true;

    int number_of_try = 0;
    int max_number_of_try = 3;

    // setup

    while (true) 
    {   
        if (meetResultaat == -1) 
        {
            armInformatie.set_Request_Status(armInformatie.Meten); // zeg tegen de arm dat die moet gaan meten

            meetResultaat = screwEndEffectorInformatie.do_measurement(armInformatie.get_Huidige_Positie());
        }
        else 
        {
            switch (status) 
            {
                case defalt:
                {
                    
                }

                case Pak_bitje:
                {
                    if (entry) 
                    {
                        armInformatie.set_Request_Status(armInformatie.Pak_bitje); // zeg tegen de arm dat die een bitje moet gaan op pakken
                        entry = false;
                    }

                    if (screwEndEffectorInformatie.pick_bitje()) // als de arm klaar is met een bitje pakken
                    {  
                        entry = true;
                        meetResultaat = -1;
                        status = bitje_opgepakt; // zet de status op pak een schroef
                    }

                    break;
                }

                case bitje_opgepakt:
                {
                    if (meetResultaat < bitLengte + meetTolerantie && meetResultaat > bitLengte - meetTolerantie)
                    {
                        number_of_try = 0;
                        status = Pak_schroef;
                    }
                    else if (meetResultaat >= bitLengte + meetTolerantie || number_of_try >= max_number_of_try)
                    {
                        armInformatie.set_Request_Status(armInformatie.Wacht);
                    }
                    else 
                    {
                        number_of_try ++;
                        status = Pak_bitje;
                    }
                    break;
                }

                case Verwijder_schroef:
                {
                    if (entry)
                    {
                        armInformatie.set_Request_Status(armInformatie.Verwijder_schroef);
                        entry = false;
                    }

                    if (armInformatie.get_Actual_Status() == armInformatie.Verwijder_schroef)
                    {
                        entry = false;
                        status = Pak_schroef;
                    }
                    break;
                }

                case Schroef_verwijderd:
                {
                    if (meetResultaat < bitLengte + meetTolerantie && meetResultaat > bitLengte - meetTolerantie)
                    {
                        status = Pak_schroef;
                    }
                    else if (number_of_try >= max_number_of_try)
                    {
                        armInformatie.set_Request_Status(armInformatie.Wacht);
                    }
                    else 
                    {
                        number_of_try ++;
                        status = Pak_bitje;
                    }
                    break;
                }

                case Pak_schroef:
                {
                    if (entry)
                    {
                        armInformatie.set_Request_Status(armInformatie.Pak_schroef);
                        entry = false;
                    }

                    if (screwEndEffectorInformatie.pick_screw()) 
                    {
                        entry = true;
                        meetResultaat = -1;
                        status = schroef_opgepakt;
                    }
                    break;
                }

                case schroef_opgepakt:
                {
                    if (meetResultaat < schroefLengteMetBit + meetTolerantie && meetResultaat > schroefLengteMetBit - meetTolerantie)
                    {
                        number_of_try = 0;
                        status = schroeven;
                    }
                    else if (number_of_try >= max_number_of_try)
                    {
                        armInformatie.set_Request_Status(armInformatie.Wacht);
                    }
                    else if (meetResultaat < bitLengte + meetTolerantie)
                    {
                        number_of_try ++;
                        status = Pak_schroef;
                    }
                    else 
                    {
                        number_of_try ++;
                        status = Verwijder_schroef;
                    }
                    break;
                }

                case(schroeven):
                {
                    if () 
                    {

                    }

                    break;
                }
            }
        }
    }

}


int main()
{
    double schroefLengte = 15;

    

    armInformatie.set_Request_Status(armInformatie.Meten); // zeg tegen de arm dat die moet gaan meten
    while (!screwEndEffectorInformatie.do_measurement(armInformatie.get_Huidige_Positie())); // wacht tot de het meten voltooid is 

    while (screwEndEffectorInformatie.get_SchroefAanweezig()) // waneer er een schroef aanweezig is
    {
        armInformatie.set_Request_Status(armInformatie.Verwijder_schroef); // zeg tegen de arm dat die de schroef moet verwijderen
        while (armInformatie.get_Actual_Status() != armInformatie.Verwijder_schroef); // wacht tot de arm klaar is met verijwderen van de schroef

        armInformatie.set_Request_Status(armInformatie.Meten); // zeg tegen de arm dat die moet gaan meten
        while (!screwEndEffectorInformatie.do_measurement(armInformatie.get_Huidige_Positie())); // wacht tot de het meten voltooid is
    }

    while (screwEndEffectorInformatie.get_BitjeAanweezig()) // waneer er een bitje aanweezig is
    {
        armInformatie.set_Request_Status(armInformatie.Verwijder_bitje); // zeg tegen de arm dat die de schroef moet verwijderen
        while (!screwEndEffectorInformatie.drop_bitje());// wacht tot de arm klaar is met verijwderen van de schroef

        armInformatie.set_Request_Status(armInformatie.Meten); // zeg tegen de arm dat die moet gaan meten
        while (!screwEndEffectorInformatie.do_measurement(armInformatie.get_Huidige_Positie())); // wacht tot de het meten voltooid is
    }

    while (true) 
    {   
        while (!screwEndEffectorInformatie.get_BitjeAanweezig()) // waneer er geen bitje aanwezig is
        {
            armInformatie.set_Request_Status(armInformatie.Pak_bitje); // zeg tegen de arm dat die een bitje moet gaan op pakken 
            while (!screwEndEffectorInformatie.pick_bitje()); // wacht tot het bitje is opgepakt

            armInformatie.set_Request_Status(armInformatie.Meten); // zeg tegen de arm dat die moet gaan meten
            while (!screwEndEffectorInformatie.do_measurement(armInformatie.get_Huidige_Positie())); // wacht tot de het meten voltooid is
        }

        while (!(   screwEndEffectorInformatie.get_SchroefLengte() < schroefLengte + 1 
        &&          screwEndEffectorInformatie.get_SchroefLengte() > schroefLengte - 1)) // waneer de schroeflengte meer dan 1 mm afwijkt
        {   
            while (screwEndEffectorInformatie.get_SchroefAanweezig()) // waneer er een schroefaanwezig is
            {
                armInformatie.set_Request_Status(armInformatie.Verwijder_schroef);  // zeg tegen de arm dat die de schroef moet verwijderen
                while (armInformatie.get_Actual_Status() != armInformatie.Verwijder_schroef); // wacht tot de arm klaar is met verijwderen van de schroef

                armInformatie.set_Request_Status(armInformatie.Meten); // zeg tegen de arm dat die moet gaan meten
                while (!screwEndEffectorInformatie.do_measurement(armInformatie.get_Huidige_Positie())); // wacht tot de het meten voltooid is
            }

            while (!screwEndEffectorInformatie.get_SchroefAanweezig()) // waneer er geen schroef aanwezig is
            {
                armInformatie.set_Request_Status(armInformatie.Pak_schroef); // zeg tegen de arm dat die een schroef moet oppakken
                while (!screwEndEffectorInformatie.pick_screw()); // wacht tot de schroef is op gepakt

                armInformatie.set_Request_Status(armInformatie.Meten); // zeg tegen de arm dat die moet gaan meten
                while (!screwEndEffectorInformatie.do_measurement(armInformatie.get_Huidige_Positie())); // wacht tot de het meten voltooid is
            }
        }

        
       
      

    }
}