#include "mbed.h"
#include "ArmInformatie.h"
#include "ConductorSensor.h"
#include "Bithandler.h"


class ScrewEndEffectorInformatie { // Dit is de informatie die van de ScrewEndEffector naar de arm gaat
private:
ConductorSensor conductorsensor;
Bithandler bithandler;

// data
bool BitjesKlemOpen;
bool Schroeftouch;
double RPMmotor; // De RPM van de motor
int SchroefAandrukStatus; // int 0 = default, int 1 = geen duk, int 2 = minimaale druk, int 3 = goede druk, 4 = maximale druk, 
double SchroefLengte; 
bool BitjeAanwezig, SchroefAanwezig;
double BitjesLengte = 5;

public:
//functions
bool pick_bitje(); // functie om een bitje op tepakken returns true als het voltooid is anders false
bool drop_bitje(); // functie om een bitje weg te zetten returns true als het voltooid is anders false
bool pick_screw(); // functie om een schroef op te pakken returns true als het voltooid is anders false


double do_measurement(Positie posietie); // functie om meeting te doen returns meetresultaat als het voltooid is anders -1
bool calibrate_measurement(Positie positie); // functie om de conductor sesnsor te calibreren returns true als het voltooid is anders false

//setters
void set_BitjesKlemOpen( bool bitjesklemopen );
void set_SchroefTouch( bool SchroefTouch );
void set_RPMmotor( double rpmmotor );
void set_SchroefAandrukStatus( int schroefaandrukstatus );
void set_SchroefLengte(int schroeflengte);
void set_Schroefaanwezig(bool schroefaanwezig);
void set_BitjeAanweezig(bool bitjeaanwezig);


//getters
bool get_SchroefTouch() { return Schroeftouch; };
double get_RPMmotor(){ return RPMmotor; };
int get_SchroefAandrukStatus(){ return SchroefAandrukStatus; };
int get_SchroefLengte(){ return SchroefLengte; };
bool get_BitjeAanweezig(){ return BitjeAanwezig; };
bool get_SchroefAanweezig(){ return SchroefAanwezig; };

};