#include "mbed.h"

class ScrewEndEffectorInformatie { // Dit is de informatie die van de ScrewEndEffector naar de arm gaat
private:
bool BitjesKlemOpen;
bool SchroefTouch; // Is de schroevendraaier vast in het systeem?
double RPMmotor; // De RPM van de motor
int SchroefAandrukStatus; // int 0 = default, int 1 = Zacht aandrukken, int 2 = normaal aandrukken, int 3 = hard aandrukken 
double SchroefLengte; 
bool BitjeAanweezig, SchroefAanweezig;

public:
//setters
void set_BitjesKlemOpen( bool bitjesklemopen );
void set_SchroefTouch( bool schroeftouch );
void set_RPMmotor( double rpmmotoer );
void set_SchroefAandrukStatus( int schroefaandrukstatus );
void set_SchroefLengte(double schroeflengte);
void set_Schroefaanwezig(bool schroefaanweezig);
void set_BitjeAanweezig(bool bitjeaanweezig);


//getters
bool get_SchroefTouch() { return SchroefTouch; };
double get_RPMmotor(){ return RPMmotor; };
int get_SchroefAandrukStatus(){ return SchroefAandrukStatus; };
double get_SchroefLengte(){ return SchroefLengte; };
bool get_BitjeAanweezig(){ return BitjeAanweezig; };
bool get_SchroefAanweezig(){ return SchroefAanweezig; };

};