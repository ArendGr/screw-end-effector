#include "mbed.h"
#include "ScrewEndEffectorInformatie.h"
#include "ArmInformatie.h"

#define Timer_Check     500ms //Dit is de tijd dat het programma wacht totdat er weer gekeken kan worden of een bepaalde functie is uitgevoerd

ScrewEndEffectorInformatie screwEndEffectorInformatie;
ArmInformatie armInformatie;
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
    double schroefLengte = 15;

    armInformatie.set_Request_Status(armInformatie.Meten); // zeg tegen de arm dat die moet gaan meten
    while (!screwEndEffectorInformatie.do_measurement(armInformatie.get_Huidige_Positie())); // wacht tot de het meten voltooid is 
    armInformatie.set_Request_Status(armInformatie.Wacht); // zeg tegen de arm dat die moet wachten

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